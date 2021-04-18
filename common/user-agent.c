#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h> /* isspace() */
#include <string.h>
#include <strings.h>
#include <pthread.h>
//#include <curl/curl.h> /* implicit */

#include "user-agent.h"
#include "orka-utils.h"


#define CURLE_CHECK(ecode) VASSERT_S(CURLE_OK == ecode, "Code: %d\n\tDescription: %s", ecode, curl_easy_strerror(ecode))


struct user_agent {
  struct logconf *p_config;

  struct curl_slist *req_header; // the request header sent to the api

  struct ua_conn **conn_pool; // connection pool for reuse
  int num_notbusy; // num of available conns
  size_t num_conn; // amount of conns created

  char base_url[UA_MAX_URL_LEN];

  uint64_t blockuntil_tstamp; // for global ratelimiting purposes
  pthread_mutex_t lock;

  void *data; // user arbitrary data for setopt_cb
  void (*setopt_cb)(CURL *ehandle, void *data); // set custom easy_setopts

  void *data2; // @todo this is temporary
  curl_mime *mime; // @todo this is temporary
  curl_mime* (*mime_cb)(CURL *ehandle, void *data); // @todo this is temporary
};

struct conn_resp_header {
  char field[UA_MAX_HEADER_SIZE][UA_MAX_HEADER_LEN];
  char value[UA_MAX_HEADER_SIZE][UA_MAX_HEADER_LEN];
  int size;
};

struct conn_resp_body {
  struct sized_buffer content; //the api response string
  size_t real_size; //the literal array size
};

struct ua_conn {
  CURL *ehandle; //the curl's easy handle used to perform requests
  bool is_busy; // true if current conn is performing a request
  ua_status_t status; //the conn request's status

  char req_url[UA_MAX_URL_LEN]; //request's url
  uint64_t req_tstamp; // timestamp of when its request completed

  struct conn_resp_header resp_header; //the key/field response header
  struct conn_resp_body resp_body; //the response body

  void *data; //user arbitrary data
};


/* attempt to get value from matching response header field */
char*
ua_respheader_value(struct ua_conn *conn, char field[])
{
  for (int i=0; i < conn->resp_header.size; ++i) {
    if (0 == strcasecmp(field, conn->resp_header.field[i])) {
      return conn->resp_header.value[i]; //found header field, return its value
    }
  }
  return NULL; //couldn't find header field
}

void
ua_reqheader_add(struct user_agent *ua, char field[],  char value[])
{
  char buf[UA_MAX_HEADER_LEN];
  int ret = snprintf(buf, sizeof(buf), "%s: %s", field, value);
  ASSERT_S(ret < UA_MAX_HEADER_LEN, "Out of bounds write attempt");

  /* check for match in existing fields */
  size_t len = strlen(field);
  struct curl_slist *node = ua->req_header;
  while (NULL != node) {
    if (0 == strncasecmp(node->data, field, len)) {
      free(node->data);
      node->data = strndup(buf, sizeof(buf));
      return; /* EARLY RETURN */
    }
    node = node->next;
  }

  /* couldn't find match, we will create a new field */
  if (NULL == ua->req_header) 
    ua->req_header = curl_slist_append(NULL, buf);
  else
    curl_slist_append(ua->req_header, buf);
}

// @todo this needs some testing
void
ua_reqheader_del(struct user_agent *ua, char field[])
{
  struct curl_slist *node = ua->req_header;
  size_t len = strlen(field);
  if (0 == strncasecmp(node->data, field, len)) {
    free(node->data);
    free(node);
    ua->req_header = NULL;

    return; /* EARLY EXIT */
  }

  do { // iterate linked list to try and find field match
    if (node->next && 0 == strncasecmp(node->next->data, field, len)) {
      free(node->next->data);
      free(node->next);
      node->next = NULL;

      return; /* EARLY EXIT */
    }
    node = node->next;
  } while (node != NULL);

  log_warn("Couldn't find field '%s' in existing request header", field);
}

/* get http response header by lines
* @see: https://curl.se/libcurl/c/CURLOPT_HEADERFUNCTION.html */
static size_t
conn_respheader_cb(char *buf, size_t size, size_t nmemb, void *p_userdata)
{
  size_t bufsize = size * nmemb;
  struct conn_resp_header *resp_header = p_userdata;

  char *ptr;
  if (!(ptr = strchr(buf, ':'))) { // returns if can't find ':' field/value separator
    return bufsize;
  }

  ptrdiff_t separator_idx = ptr - buf; // get ':' index

  int ret = snprintf(resp_header->field[resp_header->size], UA_MAX_HEADER_LEN, "%.*s", (int)separator_idx, buf);
  ASSERT_S(ret < UA_MAX_HEADER_LEN, "Out of bounds write attempt");

  if (!(ptr = strstr(ptr + 1, "\r\n"))) {//returns if can't find CRLF match
    return bufsize;
  }

  // offsets blank characters
  int offset=1; // starts after the ':' separator
  while (separator_idx + offset < bufsize) {
    if (!isspace(buf[separator_idx + offset]))
      break; /* EARLY BREAK (not blank character) */
    ++offset;
  }

  // get the value part of the string
  const int value_size = bufsize - (separator_idx + offset);
  ret = snprintf(resp_header->value[resp_header->size], UA_MAX_HEADER_LEN, "%.*s", value_size, &buf[separator_idx + offset]);
  ASSERT_S(ret < UA_MAX_HEADER_LEN, "Out of bounds write attempt");

  ++resp_header->size; //update header amount of field/value resp_header
  ASSERT_S(resp_header->size < UA_MAX_HEADER_SIZE, "Out of bounds write attempt");

  return bufsize;
}

/* get http response body in chunks
* @see: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
static size_t
conn_respbody_cb(char *buf, size_t size, size_t nmemb, void *p_userdata)
{
  size_t bufchunk_size = size * nmemb;
  struct conn_resp_body *body = p_userdata;

  //increase response body memory block size only if necessary
  if (body->real_size < (body->content.size + bufchunk_size + 1)) {
    body->real_size = body->content.size + bufchunk_size + 1;
    body->content.start = realloc(body->content.start, body->real_size);
  }
  memcpy(&body->content.start[body->content.size], buf, bufchunk_size);
  body->content.size += bufchunk_size;
  body->content.start[body->content.size] = '\0';
  return bufchunk_size;
}

void
ua_easy_setopt(struct user_agent *ua, void *data, void (setopt_cb)(CURL *ehandle, void *data)) 
{
  ua->setopt_cb = setopt_cb;
  ua->data = data;
}

void
ua_mime_setopt(struct user_agent *ua, void *data, curl_mime* (mime_cb)(CURL *ehandle, void *data)) 
{
  ua->mime_cb = mime_cb;
  ua->data2 = data;
}

static struct ua_conn*
conn_init(struct user_agent *ua)
{
  struct ua_conn *new_conn = calloc(1, sizeof(struct ua_conn));

  CURL *new_ehandle = curl_easy_init(); // will be given to new_conn

  CURLcode ecode;

  //set ptr to request header we will be using for API communication
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HTTPHEADER, ua->req_header);
  CURLE_CHECK(ecode);

  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  CURLE_CHECK(ecode);

  //set response body callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION, &conn_respbody_cb);
  CURLE_CHECK(ecode);

  //set ptr to response body to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, &new_conn->resp_body);
  CURLE_CHECK(ecode);

  //set response header callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION, &conn_respheader_cb);
  CURLE_CHECK(ecode);

  //set ptr to response header to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, &new_conn->resp_header);
  CURLE_CHECK(ecode);

  // execute user-defined curl_easy_setopts
  if (ua->setopt_cb) {
    (*ua->setopt_cb)(new_ehandle, ua->data);
  }

  new_conn->ehandle = new_ehandle;

  return new_conn;
}

static void
conn_cleanup(struct ua_conn *conn)
{
  curl_easy_cleanup(conn->ehandle);
  if (conn->resp_body.content.start)
    free(conn->resp_body.content.start);
  free(conn);
}

static void
conn_soft_reset(struct ua_conn *conn)
{
  conn->req_tstamp = 0;
  if (conn->resp_body.content.start)
    *conn->resp_body.content.start = '\0';
  conn->resp_body.content.size = 0;
  conn->resp_header.size = 0;
}

static void
conn_full_reset(struct user_agent *ua, struct ua_conn *conn)
{
  pthread_mutex_lock(&ua->lock);

  conn_soft_reset(conn); // just to be sure
  conn->data = NULL;
  conn->is_busy = false;
  conn->status = 0;

  ++ua->num_notbusy;
  if (ua->mime) { // @todo this is temporary
    curl_mime_free(ua->mime); 
    ua->mime = NULL;
  }
  pthread_mutex_unlock(&ua->lock);
}

static struct ua_conn*
get_conn(struct user_agent *ua)
{
  struct ua_conn *ret_conn = NULL;

  pthread_mutex_lock(&ua->lock);
  if (!ua->num_notbusy) { // no available conn, create new
    ++ua->num_conn;

    ua->conn_pool = realloc(ua->conn_pool, ua->num_conn * sizeof *ua->conn_pool);
    ua->conn_pool[ua->num_conn-1] = conn_init(ua);

    ret_conn = ua->conn_pool[ua->num_conn-1];
  }
  else { // available conn, pick one
    for (size_t i=0; i < ua->num_conn; ++i) {
      if (!ua->conn_pool[i]->is_busy) {
        --ua->num_notbusy;
        ret_conn = ua->conn_pool[i];
        break; /* EARLY BREAK */
      }
    }
  }
  ASSERT_S(NULL != ret_conn, "Internal thread synchronization error (couldn't fetch conn)");

  ret_conn->is_busy = true;
  pthread_mutex_unlock(&ua->lock);

  return ret_conn;
}

void*
ua_conn_set_data(struct ua_conn *conn, void *data) {
  return conn->data = data;
}

void*
ua_conn_get_data(struct ua_conn *conn) {
  return conn->data;
}

struct sized_buffer
ua_conn_get_resp_body(struct ua_conn *conn) {
  return conn->resp_body.content;
}

ua_status_t 
ua_conn_get_status(struct ua_conn *conn) {
  return conn->status;
}

uint64_t
ua_conn_timestamp(struct ua_conn *conn) {
  return conn->req_tstamp;
}

struct user_agent*
ua_init(const char base_url[], struct logconf *config) 
{
  struct user_agent *new_ua = calloc(1, sizeof *new_ua);

  ua_set_url(new_ua, base_url);

  // default header
  char user_agent[] = "orca (http://github.com/cee-studio/orca)";
  ua_reqheader_add(new_ua, "User-Agent", user_agent);
  ua_reqheader_add(new_ua, "Content-Type", "application/json");
  ua_reqheader_add(new_ua, "Accept", "application/json");

  logconf_add_id(config, new_ua, "USER_AGENT");
  new_ua->p_config = config;

  if (pthread_mutex_init(&new_ua->lock, NULL))
    ERR("Couldn't initialize mutex");

  return new_ua;
}

void
ua_cleanup(struct user_agent *ua)
{
  curl_slist_free_all(ua->req_header);
  if (ua->conn_pool) {
    for (size_t i=0; i < ua->num_conn; ++i)
      conn_cleanup(ua->conn_pool[i]);
    free(ua->conn_pool);
  }
  pthread_mutex_destroy(&ua->lock);
  free(ua);
}

char*
ua_get_url(struct user_agent *ua) {
  return ua->base_url;
}

void
ua_set_url(struct user_agent *ua, const char base_url[])
{
  int ret = snprintf(ua->base_url, sizeof(ua->base_url), "%s", base_url);
  ASSERT_S(ret < sizeof(ua->base_url), "Out of bounds write attempt");
}

char*
http_code_print(int httpcode)
{
  switch (httpcode) {
  case HTTP_OK:                   return "OK";
  case HTTP_CREATED:              return "CREATED";
  case HTTP_NO_CONTENT:           return "NO_CONTENT";
  case HTTP_NOT_MODIFIED:         return "NOT_MODIFIED";
  case HTTP_BAD_REQUEST:          return "BAD_REQUEST";
  case HTTP_UNAUTHORIZED:         return "UNAUTHORIZED";
  case HTTP_FORBIDDEN:            return "FORBIDDEN";
  case HTTP_NOT_FOUND:            return "NOT_FOUND";
  case HTTP_METHOD_NOT_ALLOWED:   return "METHOD_NOT_ALLOWED";
  case HTTP_UNPROCESSABLE_ENTITY: return "UNPROCESSABLE_ENTITY";
  case HTTP_TOO_MANY_REQUESTS:    return "TOO_MANY_REQUESTS";
  case HTTP_GATEWAY_UNAVAILABLE:  return "GATEWAY_UNAVAILABLE";
  default:
      if (httpcode >= 500) return "5xx_SERVER_ERROR";
      if (httpcode >= 400) return "4xx_CLIENT_ERROR";
      if (httpcode >= 300) return "3xx_REDIRECTING";
      if (httpcode >= 200) return "2xx_SUCCESS";
      if (httpcode >= 100) return "1xx_INFO";
      return "UNUSUAL_HTTP_CODE";
  }
}

char*
http_reason_print(int httpcode)
{
  switch (httpcode) {
  case HTTP_OK:
      return "The request was completed succesfully.";
  case HTTP_CREATED:
      return "The entity was created succesfully.";
  case HTTP_NO_CONTENT:
      return "The request completed succesfully but returned no content.";
  case HTTP_NOT_MODIFIED:
      return "The entity was not modified (no action was taken).";
  case HTTP_BAD_REQUEST:
      return "The request was improperly formatted, or the server couldn't understand it.";
  case HTTP_UNAUTHORIZED:
      return "The Authorization header was missing or invalid.";
  case HTTP_FORBIDDEN:
      return "The Authorization token you passed did not have permission to the resource.";
  case HTTP_NOT_FOUND:
      return "The resource at the location specified doesn't exist.";
  case HTTP_METHOD_NOT_ALLOWED:
      return "The HTTP method used is not valid for the location specified.";
  case HTTP_TOO_MANY_REQUESTS:
      return "You got ratelimited.";
  case HTTP_GATEWAY_UNAVAILABLE:
      return "There was not a gateway available to process your request. Wait a bit and retry.";
  case CURL_NO_RESPONSE:
      return "Curl couldn't fetch a HTTP response.";
  default:
      if (httpcode >= 500) 
        return "The server had an error processing your request.";
      if (httpcode >= 400)
        return "Client side error, request couldn't be processed.";
      if (httpcode >= 300)
        return "Client requires taking additional action to complete the request";
      if (httpcode >= 200)
        return "The action request was received, understood and accepted.";
      if (httpcode >= 100)
        return "The request was received and understood. The client must wait for a final response.";

      return "Unusual HTTP method.";
  }
}

char*
http_method_print(enum http_method method)
{
  switch(method) {
  case HTTP_DELETE:   return "DELETE";
  case HTTP_GET:      return "GET";
  case HTTP_POST:     return "POST";
  case HTTP_MIMEPOST: return "MIMEPOST";
  case HTTP_PATCH:    return "PATCH";
  case HTTP_PUT:      return "PUT";
  default:
      log_error("Invalid HTTP method (code: %d)", method);
      return "INVALID_HTTP_METHOD";
  }
}

/* set specific http method used for the request */
static void
set_method(
  struct user_agent *ua, //@todo unnecessary after multipart_inject()
  struct ua_conn *conn, 
  enum http_method method, 
  struct sized_buffer *req_body)
{
  // resets any preexisting CUSTOMREQUEST
  curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, NULL);

  CURLcode ecode;
  switch (method) {
  case HTTP_DELETE:
      ecode = curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, "DELETE");
      CURLE_CHECK(ecode);
      break;
  case HTTP_GET:
      ecode = curl_easy_setopt(conn->ehandle, CURLOPT_HTTPGET, 1L);
      CURLE_CHECK(ecode);
      return; /* EARLY RETURN */
  case HTTP_POST:
      curl_easy_setopt(conn->ehandle, CURLOPT_POST, 1L);
      break;
  case HTTP_MIMEPOST: //@todo this is temporary
      ASSERT_S(NULL != ua->mime_cb, "Missing 'ua->mime_cb' callback");
      ASSERT_S(NULL == ua->mime, "'ua->mime' not freed");

      ua->mime = (*ua->mime_cb)(conn->ehandle, ua->data2);
      curl_easy_setopt(conn->ehandle, CURLOPT_MIMEPOST, ua->mime);
      return; /* EARLY RETURN */
  case HTTP_PATCH:
      curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, "PATCH");
      break;
  case HTTP_PUT:
      curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, "PUT");
      break;
  default:
      ERR("Unknown http method (code: %d)", method);
  }
  
  //set ptr to payload that will be sent via POST/PUT/PATCH
  curl_easy_setopt(conn->ehandle, CURLOPT_POSTFIELDS, req_body->start);
  curl_easy_setopt(conn->ehandle, CURLOPT_POSTFIELDSIZE, req_body->size);
}

static void
set_url(struct user_agent *ua, struct ua_conn *conn, char endpoint[], va_list args)
{
  //create the url route
  char url_route[UA_MAX_URL_LEN];
  int ret = vsnprintf(url_route, sizeof(url_route), endpoint, args);
  ASSERT_S(ret < sizeof(url_route), "oob write of url_route");

  ret = snprintf(conn->req_url, sizeof(conn->req_url), "%s%s", ua->base_url, url_route);
  ASSERT_S(ret < sizeof(conn->req_url), "Out of bounds write attempt");

  CURLcode ecode = curl_easy_setopt(conn->ehandle, CURLOPT_URL, conn->req_url);
  CURLE_CHECK(ecode);

  log_trace("Request URL: %s", conn->req_url);
}

static void noop_iter_start_cb(void *a)
{return;}
static void noop_iter_end_cb(void *a, struct ua_conn *b)
{return;}
static ua_status_t noop_success_cb(void *a, int b, struct ua_conn *c)
{return UA_SUCCESS;}
static ua_status_t noop_retry_cb(void *a, int b, struct ua_conn *c) 
{return UA_RETRY;}
static ua_status_t noop_abort_cb(void *a, int b, struct ua_conn *c) 
{return UA_ABORT;}

static int
send_request(struct user_agent *ua, struct ua_conn *conn)
{
  pthread_mutex_lock(&ua->lock);
  
  // enforces global ratelimiting with ua_block_ms();
  orka_sleep_ms(ua->blockuntil_tstamp - orka_timestamp_ms());
  CURLcode ecode;
  
  ecode = curl_easy_perform(conn->ehandle);
  CURLE_CHECK(ecode);

  conn->req_tstamp = orka_timestamp_ms();

  //get response's code
  int httpcode=0;
  ecode = curl_easy_getinfo(conn->ehandle, CURLINFO_RESPONSE_CODE, &httpcode);
  CURLE_CHECK(ecode);

  char *resp_url=NULL;
  ecode = curl_easy_getinfo(conn->ehandle, CURLINFO_EFFECTIVE_URL, &resp_url);
  CURLE_CHECK(ecode);

  log_http(
    ua->p_config, 
    ua,
    resp_url, 
    conn->resp_body.content,
    "HTTP_RESPONSE %s(%d)", http_code_print(httpcode), httpcode);

  pthread_mutex_unlock(&ua->lock);

  return httpcode;
}

static void
perform_request(
  struct user_agent *ua,
  struct ua_conn *conn, 
  struct ua_resp_handle *resp_handle,
  struct ua_callbacks *p_cbs)
{
  struct ua_callbacks cbs;
  if (p_cbs)
    memcpy(&cbs, p_cbs, sizeof(struct ua_callbacks));
  else
    memset(&cbs, 0, sizeof(struct ua_callbacks));

  /* SET DEFAULT CALLBACKS */
  if (!cbs.on_iter_start) cbs.on_iter_start = &noop_iter_start_cb;
  if (!cbs.on_iter_end) cbs.on_iter_end = &noop_iter_end_cb;
  if (!cbs.on_1xx) cbs.on_1xx = &noop_success_cb;
  if (!cbs.on_2xx) cbs.on_2xx = &noop_success_cb;
  if (!cbs.on_3xx) cbs.on_3xx = &noop_success_cb;
  if (!cbs.on_4xx) cbs.on_4xx = &noop_abort_cb;
  if (!cbs.on_5xx) cbs.on_5xx = &noop_retry_cb;

  if (cbs.on_startup) {
    int ret = (*cbs.on_startup)(cbs.data);
    if (!ret) return; /* EARLY RETURN */
  }

  do {
    /* triggers on every start of loop iteration */
    (*cbs.on_iter_start)(cbs.data);

    int httpcode = send_request(ua, conn);

    /* triggers response related callbacks */
    if (httpcode >= 500) { // SERVER ERROR
      conn->status = (*cbs.on_5xx)(cbs.data, httpcode, conn);

      if (resp_handle) {
        if (resp_handle->err_cb) {
          (*resp_handle->err_cb)(
            conn->resp_body.content.start,
            conn->resp_body.content.size,
            resp_handle->err_obj);
        }
        else if (resp_handle->cxt_err_cb) {
          (*resp_handle->cxt_err_cb)(
            resp_handle->cxt,
            conn->resp_body.content.start,
            conn->resp_body.content.size,
            resp_handle->err_obj);
        }
      }
    }
    else if (httpcode >= 400) { // CLIENT ERROR
      conn->status = (*cbs.on_4xx)(cbs.data, httpcode, conn);

      if (resp_handle) {
        if(resp_handle->err_cb) {
          (*resp_handle->err_cb)(
            conn->resp_body.content.start,
            conn->resp_body.content.size,
            resp_handle->err_obj);
        }
        else if (resp_handle->cxt_err_cb) {
          (*resp_handle->cxt_err_cb)(
            resp_handle->cxt,
            conn->resp_body.content.start,
            conn->resp_body.content.size,
            resp_handle->err_obj);
        }
      }
    }
    else if (httpcode >= 300) { // REDIRECTING
      conn->status = (*cbs.on_3xx)(cbs.data, httpcode, conn);
    }
    else if (httpcode >= 200) { // SUCCESS RESPONSES
      conn->status = (*cbs.on_2xx)(cbs.data, httpcode, conn);

      if (resp_handle) {
        if (resp_handle->ok_cb) {
          (*resp_handle->ok_cb)(
            conn->resp_body.content.start,
            conn->resp_body.content.size,
            resp_handle->ok_obj);
        }
        else if (resp_handle->cxt_ok_cb) {
          (*resp_handle->cxt_ok_cb)(
            resp_handle->cxt,
            conn->resp_body.content.start,
            conn->resp_body.content.size,
            resp_handle->ok_obj);
        }
      }
    }
    else if (httpcode >= 100) { // INFO RESPONSE
      conn->status = (*cbs.on_1xx)(cbs.data, httpcode, conn);
    }
    else if (httpcode == CURL_NO_RESPONSE){
      log_error("No http response received by libcurl");
      conn->status = UA_FAILURE;
    }
    else {
      ERR("Unusual HTTP response code: %d", httpcode);
    }

    switch (conn->status) {
    case UA_SUCCESS:
        log_info(ANSICOLOR("SUCCESS (%d)%s", 32)" - %s",
            httpcode,
            http_code_print(httpcode),
            http_reason_print(httpcode));
        break;
    case UA_FAILURE:
        log_warn(ANSICOLOR("FAILURE (%d)%s", 31)" - %s",
            httpcode,
            http_code_print(httpcode),
            http_reason_print(httpcode));
        break;
    case UA_RETRY:
        log_info(ANSICOLOR("RETRY (%d)%s", 33)" - %s",
            httpcode,
            http_code_print(httpcode),
            http_reason_print(httpcode));
        break;
    case UA_ABORT:
    default:
        ERR(ANSICOLOR("ABORT (%d)%s", 31)" - %s",
            httpcode,
            http_code_print(httpcode),
            http_reason_print(httpcode));
    }

    (*cbs.on_iter_end)(cbs.data, conn);
    
    conn_soft_reset(conn); // reset conn fields for its next iteration
  } while (UA_RETRY == conn->status);

  conn_full_reset(ua, conn);
}

// make the main thread wait for a specified amount of time
void
ua_block_ms(struct user_agent *ua, const uint64_t wait_ms) 
{
  pthread_mutex_lock(&ua->lock);
  ua->blockuntil_tstamp = orka_timestamp_ms() + wait_ms;
  pthread_mutex_unlock(&ua->lock);
}

/* template function for performing requests */
void 
ua_vrun(
  struct user_agent *ua,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct ua_callbacks *cbs,
  enum http_method http_method, char endpoint[], va_list args)
{
  static struct sized_buffer blank_req_body = {"", 0};
  if (NULL == req_body) {
    req_body = &blank_req_body;
  }
  struct ua_conn *conn = get_conn(ua);
  set_url(ua, conn, endpoint, args); //set the request url

  log_http(
    ua->p_config, 
    ua,
    conn->req_url, 
    *req_body,
    "HTTP_REQUEST %s", http_method_print(http_method));

  set_method(ua, conn, http_method, req_body); //set the request method

  perform_request(ua, conn, resp_handle, cbs);
}

/* template function for performing requests */
void 
ua_run(
  struct user_agent *ua,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  struct ua_callbacks *cbs,
  enum http_method http_method, char endpoint[], ...)
{
  va_list args;
  va_start(args, endpoint);

  ua_vrun(
    ua, 
    resp_handle, 
    req_body, 
    cbs, 
    http_method, endpoint, args);

  va_end(args);
}
