#define _GNU_SOURCE /* asprintf() */
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
#include "cee-utils.h"


#define CURLE_CHECK(conn, ecode)                           \
  VASSERT_S(CURLE_OK == ecode, "[%s] (CURLE code: %d) %s", \
      conn->tag,                                           \
      ecode,                                               \
      IS_EMPTY_STRING(conn->errbuf)                        \
        ? curl_easy_strerror(ecode)                        \
        : conn->errbuf)

struct user_agent {
  /**
   * whether this is the original user agent or a clone
   */
  bool is_original;
  /** 
   * the user agent request header
   */
  struct curl_slist *req_header;
  /**
   * a pool of connection nodes for easy reuse
   * @note conns are wrappers around basic CURL functionalities,
   *        each active conn is responsible for a HTTP request
   */
  struct {
    struct _ua_conn **pool;
    size_t amt; ///< amount of connections node in pool
  } *conn;
  /** 
   * the base_url for every conn
   */
  struct sized_buffer base_url;
  /**
   * synchronize conn pool and shared ratelimiting
   */
  struct {
    uint64_t        blockuntil_tstamp; ///< lock every active conn from conn_pool until timestamp
    pthread_mutex_t lock;
  } *shared;
  /**
   * struct used for logging
   */
  struct logconf *p_config;
  /**
   * user arbitrary data accessed by setopt_cb
   * @see ua_curl_easy_setopt()
   */
  void *data;
  void (*setopt_cb)(CURL *ehandle, void *data);
  /** 
   * user arbitrary data accessed by mime_cb
   *
   * @todo this is temporary, we should implement a non-curl reliant 
   *        way of sending MIME type data 
   * @see ua_curl_mime_setopt()
   */
  void       *data2;
  curl_mime  *mime; 
  curl_mime* (*mime_cb)(CURL *ehandle, void *data2);
};

struct _ua_conn {
  struct ua_info info;
  /** 
   * the curl's easy handle used to perform requests
   */
  CURL *ehandle;
  /** 
   * true if current conn is performing a request
   */
  bool is_busy;
  /** 
   * capture curl error messages
   * @note should only be accessed after a error code returns
   * @see https://curl.se/libcurl/c/CURLOPT_ERRORBUFFER.html
   */
  char errbuf[CURL_ERROR_SIZE];
  /**
   * unique identification tag for logging purposes
   */
  char tag[32];
};

const char*
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

const char*
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
      if (!httpcode)
        return "Curl couldn't fetch a HTTP response.";
      return "Unusual HTTP method.";
  }
}

const char*
http_method_print(enum http_method method)
{
  switch(method) {
  case HTTP_DELETE:   return "DELETE";
  case HTTP_GET:      return "GET";
  case HTTP_POST:     return "POST";
  case HTTP_MIMEPOST: return "MIMEPOST";
  case HTTP_PATCH:    return "PATCH";
  case HTTP_PUT:      return "PUT";
  case HTTP_INVALID:
  default:            return "INVALID_HTTP_METHOD";
  }
}

enum http_method
http_method_eval(char method[])
{
  if (STREQ(method, "DELETE"))   return HTTP_DELETE;
  if (STREQ(method, "GET"))      return HTTP_GET;
  if (STREQ(method, "POST"))     return HTTP_POST;
  if (STREQ(method, "MIMEPOST")) return HTTP_MIMEPOST;
  if (STREQ(method, "PATCH"))    return HTTP_PATCH;
  if (STREQ(method, "PUT"))      return HTTP_PUT;
  return HTTP_INVALID;
}

void
ua_reqheader_add(struct user_agent *ua, const char field[],  const char value[])
{
  char buf[4096];
  size_t ret = snprintf(buf, sizeof(buf), "%s: %s", field, value);
  ASSERT_S(ret < sizeof(buf), "Out of bounds write attempt");

  /* check for match in existing fields */
  size_t field_len = strlen(field);
  char *ptr;
  struct curl_slist *node = ua->req_header;
  while (NULL != node) {
    if (!(ptr = strchr(node->data, ':')))
      ERR("Missing ':' in header:\n\t%s", node->data);
    if (field_len == ptr - node->data
        && 0 == strncasecmp(node->data, field, field_len)) 
    {
      if (strlen(node->data) < ret) {
        free(node->data);
        node->data = strdup(buf);
      }
      else {
        memcpy(node->data, buf, ret+1);
      }
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

/**
 * @todo needs to be tested
 */
void
ua_reqheader_del(struct user_agent *ua, const char field[])
{
  struct curl_slist *node = ua->req_header;
  size_t field_len = strlen(field);
  char *ptr;
  if (!(ptr = strchr(node->data, ':')))
    ERR("Missing ':' in header: %s", node->data);
  if (field_len == ptr - node->data
      && 0 == strncasecmp(node->data, field, field_len)) 
  {
    free(node->data);
    free(node);
    ua->req_header = NULL;
    return; /* EARLY EXIT */
  }

  do { // iterate linked list to try and find field match
    if (node->next) {
      if (!(ptr = strchr(node->next->data, ':')))
        ERR("Missing ':' in header: %s", node->next->data);
      if (field_len == ptr - node->next->data
          && 0 == strncasecmp(node->next->data, field, field_len)) {
        free(node->next->data);
        free(node->next);
        node->next = NULL;
        return; /* EARLY EXIT */
      }
    }
    node = node->next;
  } while (node != NULL);

  log_warn("[%s] Couldn't find field '%s' in existing request header", logconf_tag(ua->p_config, ua), field);
}

char*
ua_reqheader_str(struct user_agent *ua, char *buf, size_t bufsize) 
{
  struct curl_slist *node = ua->req_header;
  size_t ret=0;
  while (NULL != node) {
    ret += snprintf(buf+ret, bufsize-ret, "%s\r\n", node->data);
    VASSERT_S(ret < bufsize, "[%s] Out of bounds write attempt", logconf_tag(ua->p_config, ua));
    node = node->next;
  }
  if (!ret) return NULL;

  buf[ret-1] = '\0';
  return buf;
}

/**
 * get http response header by lines
 * @see: https://curl.se/libcurl/c/CURLOPT_HEADERFUNCTION.html 
 */
static size_t
conn_respheader_cb(char *buf, size_t size, size_t nmemb, void *p_userdata)
{
  size_t bufsize = size * nmemb;
  struct ua_resp_header *header = p_userdata;

  char *ptr;
  if (!(ptr = strchr(buf, ':'))) { // returns if can't find ':' field/value delimiter
    return bufsize;
  }

  ptrdiff_t delim_idx = ptr - buf; // get ':' position
  if (!(ptr = strstr(ptr + 1, "\r\n"))) { //returns if can't find CRLF match
    return bufsize;
  }

  if (header->bufsize < (header->length + bufsize + 1)) {
    header->bufsize = header->length + bufsize + 1;
    header->buf = realloc(header->buf, header->bufsize);
  }
  memcpy(&header->buf[header->length], buf, bufsize);

  // get the field part of the string
  header->pairs[header->size].field.idx = header->length;
  header->pairs[header->size].field.size = delim_idx;

  // offsets blank characters
  size_t bufoffset=1; // starts after the ':' delimiter
  while (delim_idx + bufoffset < bufsize) {
    if (!isspace(buf[delim_idx + bufoffset]))
      break; /* EARLY BREAK (not blank character) */
    ++bufoffset;
  }

  // get the value part of the string
  header->pairs[header->size].value.idx = header->length + (delim_idx + bufoffset);
  header->pairs[header->size].value.size = (ptr - buf) - (delim_idx + bufoffset);

  header->length += bufsize;

  ++header->size; // update header amount of field/value header
  ASSERT_S(header->size < UA_MAX_HEADER_SIZE, "Out of bounds write attempt");

  return bufsize;
}

/**
 * get http response body in chunks
 * @see: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
 */
static size_t
conn_respbody_cb(char *buf, size_t size, size_t nmemb, void *p_userdata)
{
  size_t bufchunk_size = size * nmemb;
  struct ua_resp_body *body = p_userdata;

  //increase response body memory block size only if necessary
  if (body->bufsize < (body->length + bufchunk_size + 1)) {
    body->bufsize = body->length + bufchunk_size + 1;
    body->buf = realloc(body->buf, body->bufsize);
  }
  memcpy(&body->buf[body->length], buf, bufchunk_size);
  body->length += bufchunk_size;
  body->buf[body->length] = '\0';
  return bufchunk_size;
}

void
ua_curl_easy_setopt(struct user_agent *ua, void *data, void (setopt_cb)(CURL *ehandle, void *data)) 
{
  ua->setopt_cb = setopt_cb;
  ua->data = data;
}

void
ua_curl_mime_setopt(struct user_agent *ua, void *data, curl_mime* (mime_cb)(CURL *ehandle, void *data)) 
{
  ua->mime_cb = mime_cb;
  ua->data2 = data;
}

static struct _ua_conn*
conn_init(struct user_agent *ua)
{
  struct _ua_conn *new_conn = calloc(1, sizeof(struct _ua_conn));
  snprintf(new_conn->tag, sizeof(new_conn->tag), "%s#%zu", logconf_tag(ua->p_config, ua), ua->conn->amt);

  CURL *new_ehandle = curl_easy_init(); // will be assigned to new_conn

  CURLcode ecode;
  //set error buffer for capturing CURL error descriptions
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_ERRORBUFFER, new_conn->errbuf);
  CURLE_CHECK(new_conn, ecode);
  //set ptr to request header we will be using for API communication
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HTTPHEADER, ua->req_header);
  CURLE_CHECK(new_conn, ecode);

  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  CURLE_CHECK(new_conn, ecode);

  //set response body callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION, &conn_respbody_cb);
  CURLE_CHECK(new_conn, ecode);

  //set ptr to response body to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, &new_conn->info.resp_body);
  CURLE_CHECK(new_conn, ecode);

  //set response header callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION, &conn_respheader_cb);
  CURLE_CHECK(new_conn, ecode);

  //set ptr to response header to be filled at callback
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, &new_conn->info.resp_header);
  CURLE_CHECK(new_conn, ecode);

  // execute user-defined curl_easy_setopts
  if (ua->setopt_cb) {
    (*ua->setopt_cb)(new_ehandle, ua->data);
  }

  new_conn->ehandle = new_ehandle;

  return new_conn;
}

static void
conn_cleanup(struct _ua_conn *conn)
{
  curl_easy_cleanup(conn->ehandle);
  ua_info_cleanup(&conn->info);
  free(conn);
}

static void
conn_reset(struct _ua_conn *conn)
{
  conn->is_busy = false;
  conn->info.httpcode = 0;
  conn->info.req_tstamp = 0;
  conn->info.resp_body.length = 0;
  conn->info.resp_header.length = 0;
  conn->info.resp_header.size = 0;
  *conn->errbuf = '\0';
}

static struct _ua_conn*
get_conn(struct user_agent *ua)
{
  pthread_mutex_lock(&ua->shared->lock);
  struct _ua_conn *ret_conn=NULL;

  size_t i=0;
  while (i < ua->conn->amt) {
    if (!ua->conn->pool[i]->is_busy) {
      ret_conn = ua->conn->pool[i];
      break; /* EARLY BREAK */
    }
    ++i;
  }
  if (!ret_conn) { // no available conn, create new
    ++ua->conn->amt;
    ua->conn->pool = realloc(ua->conn->pool, \
                        ua->conn->amt * sizeof *ua->conn->pool);
    ret_conn = ua->conn->pool[ua->conn->amt-1] = conn_init(ua);
  }
  VASSERT_S(NULL != ret_conn, "[%s] (Internal error) Couldn't fetch conn", logconf_tag(ua->p_config, ua));
  ret_conn->is_busy = true;
  pthread_mutex_unlock(&ua->shared->lock);
  return ret_conn;
}

struct user_agent*
ua_init(struct logconf *config) 
{
  struct user_agent *new_ua = calloc(1, sizeof *new_ua);
  new_ua->conn = calloc(1, sizeof *new_ua->conn);
  new_ua->shared = calloc(1, sizeof *new_ua->shared);

  // default header
  ua_reqheader_add(new_ua, "User-Agent", "orca (http://github.com/cee-studio/orca)");
  ua_reqheader_add(new_ua, "Content-Type", "application/json");
  ua_reqheader_add(new_ua, "Accept", "application/json");

  logconf_add_id(config, new_ua, "USER_AGENT");
  new_ua->p_config = config;

  if (pthread_mutex_init(&new_ua->shared->lock, NULL))
    ERR("[%s] Couldn't initialize mutex", logconf_tag(new_ua->p_config, new_ua));

  new_ua->is_original = true;

  return new_ua;
}

struct user_agent*
ua_clone(struct user_agent *orig_ua) 
{
  struct user_agent *clone_ua = malloc(sizeof(struct user_agent));

  pthread_mutex_lock(&orig_ua->shared->lock);
  memcpy(clone_ua, orig_ua, sizeof(struct user_agent));

  // copy orig_ua header into clone_ua
  struct curl_slist *orig_node = orig_ua->req_header;
  clone_ua->req_header = curl_slist_append(NULL, orig_node->data);
  while (NULL != orig_node->next) {
    orig_node = orig_node->next;
    curl_slist_append(clone_ua->req_header, orig_node->data);
  }

  // use a different base_url context than the original
  clone_ua->base_url.size = asprintf(&clone_ua->base_url.start, "%.*s",
                              (int)orig_ua->base_url.size, orig_ua->base_url.start);

  pthread_mutex_unlock(&orig_ua->shared->lock);

  clone_ua->is_original = false;

  return clone_ua;
}

void
ua_cleanup(struct user_agent *ua)
{
  curl_slist_free_all(ua->req_header);

  if (ua->base_url.start) {
    free(ua->base_url.start);
  }

  if (ua->is_original) 
  {
    if (ua->conn->pool) {
      for (size_t i=0; i < ua->conn->amt; ++i)
        conn_cleanup(ua->conn->pool[i]);
      free(ua->conn->pool);
    }
    free(ua->conn);

    pthread_mutex_destroy(&ua->shared->lock);
    free(ua->shared);
  }

  free(ua);
}

const char*
ua_get_url(struct user_agent *ua) {
  return ua->base_url.start;
}

void
ua_set_url(struct user_agent *ua, const char *base_url) {
  if (ua->base_url.start) free(ua->base_url.start);
  ua->base_url.size = asprintf(&ua->base_url.start, "%s", base_url);
}

/* set specific http method used for the request */
static void
set_method(
  struct user_agent *ua,
  struct _ua_conn *conn, 
  enum http_method method, 
  struct sized_buffer *req_body)
{
  // resets any preexisting CUSTOMREQUEST
  curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, NULL);

  CURLcode ecode;
  switch (method) {
  case HTTP_DELETE:
      ecode = curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, "DELETE");
      CURLE_CHECK(conn, ecode);
      break;
  case HTTP_GET:
      ecode = curl_easy_setopt(conn->ehandle, CURLOPT_HTTPGET, 1L);
      CURLE_CHECK(conn, ecode);
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
      ERR("[%s] Unknown http method (code: %d)", method, conn->tag);
  }
  
  //set ptr to payload that will be sent via POST/PUT/PATCH
  curl_easy_setopt(conn->ehandle, CURLOPT_POSTFIELDS, req_body->start);
  curl_easy_setopt(conn->ehandle, CURLOPT_POSTFIELDSIZE, req_body->size);
}

static void
set_url(struct user_agent *ua, struct _ua_conn *conn, char endpoint[], va_list args)
{
  size_t url_len = 1 + ua->base_url.size;

  va_list tmp;
  va_copy (tmp, args);
  url_len += 1 + vsnprintf(NULL, 0, endpoint, tmp);
  va_end(tmp);

  if (url_len > conn->info.req_url.size) {
    void *tmp = realloc(conn->info.req_url.start, url_len);
    ASSERT_S(NULL != tmp, "Couldn't increase buffer's length");

    conn->info.req_url = (struct sized_buffer){
      .start = tmp,
      .size  = url_len
    };
  }

  size_t ret = snprintf(conn->info.req_url.start, conn->info.req_url.size, "%.*s", (int)ua->base_url.size, ua->base_url.start);
  ASSERT_S(ret < conn->info.req_url.size, "Out of bounds write attempt");
  ret += vsnprintf(conn->info.req_url.start+ret, conn->info.req_url.size-ret, endpoint, args);
  ASSERT_S(ret < conn->info.req_url.size, "Out of bounds write attempt");

  CURLcode ecode = curl_easy_setopt(conn->ehandle, CURLOPT_URL, conn->info.req_url.start);
  CURLE_CHECK(conn, ecode);

  log_trace("[%s] Request URL: %s", conn->tag, conn->info.req_url.start);
}

static int
send_request(struct user_agent *ua, struct _ua_conn *conn)
{
  pthread_mutex_lock(&ua->shared->lock);
  
  // enforces global ratelimiting with ua_block_ms();
  cee_sleep_ms(ua->shared->blockuntil_tstamp - cee_timestamp_ms());
  CURLcode ecode;
  
  ecode = curl_easy_perform(conn->ehandle);
#ifdef BEARSSL
  if (CURLE_READ_ERROR == ecode 
      && 0 == strcmp(conn->errbuf, "SSL: EOF without close notify"))
    log_warn("The remote server closes connection without terminating ssl");
  else
    CURLE_CHECK(conn, ecode);
#else
  CURLE_CHECK(conn, ecode);
#endif
  conn->info.req_tstamp = cee_timestamp_ms();

  //get response's code
  int httpcode=0;
  ecode = curl_easy_getinfo(conn->ehandle, CURLINFO_RESPONSE_CODE, &httpcode);
  CURLE_CHECK(conn, ecode);

  char *resp_url=NULL;
  ecode = curl_easy_getinfo(conn->ehandle, CURLINFO_EFFECTIVE_URL, &resp_url);
  CURLE_CHECK(conn, ecode);

  log_http(
    ua->p_config, 
    &conn->info.loginfo,
    ua,
    resp_url, 
    (struct sized_buffer){conn->info.resp_header.buf, conn->info.resp_header.length},
    (struct sized_buffer){conn->info.resp_body.buf, conn->info.resp_body.length},
    "HTTP_RCV_%s(%d)", http_code_print(httpcode), httpcode);

  pthread_mutex_unlock(&ua->shared->lock);

  return httpcode;
}

static ORCAcode
perform_request(
  struct user_agent *ua,
  struct _ua_conn *conn, 
  struct ua_resp_handle *resp_handle)
{
  conn->info.httpcode = send_request(ua, conn);

  /* triggers response related callbacks */
  if (conn->info.httpcode >= 500 && conn->info.httpcode < 600) {
    log_error("[%s] "ANSICOLOR("SERVER ERROR", ANSI_FG_RED)" (%d)%s - %s [@@@_%zu_@@@]",
        conn->tag,
        conn->info.httpcode,
        http_code_print(conn->info.httpcode),
        http_reason_print(conn->info.httpcode),
        conn->info.loginfo.counter);

    if (resp_handle) {
      if (resp_handle->err_cb) {
        (*resp_handle->err_cb)(
          conn->info.resp_body.buf,
          conn->info.resp_body.length,
          resp_handle->err_obj);
      }
      else if (resp_handle->cxt_err_cb) {
        (*resp_handle->cxt_err_cb)(
          resp_handle->cxt,
          conn->info.resp_body.buf,
          conn->info.resp_body.length,
          resp_handle->err_obj);
      }
    }
    return ORCA_HTTP_CODE;
  }
  if (conn->info.httpcode >= 400) {
    log_error("[%s] "ANSICOLOR("CLIENT ERROR", ANSI_FG_RED)" (%d)%s - %s [@@@_%zu_@@@]",
        conn->tag,
        conn->info.httpcode,
        http_code_print(conn->info.httpcode),
        http_reason_print(conn->info.httpcode),
        conn->info.loginfo.counter);

    if (resp_handle) {
      if(resp_handle->err_cb) {
        (*resp_handle->err_cb)(
          conn->info.resp_body.buf,
          conn->info.resp_body.length,
          resp_handle->err_obj);
      }
      else if (resp_handle->cxt_err_cb) {
        (*resp_handle->cxt_err_cb)(
          resp_handle->cxt,
          conn->info.resp_body.buf,
          conn->info.resp_body.length,
          resp_handle->err_obj);
      }
    }
    return ORCA_HTTP_CODE;
  }
  if (conn->info.httpcode >= 300) {
    log_warn("[%s] "ANSICOLOR("REDIRECTING", ANSI_FG_YELLOW)" (%d)%s - %s [@@@_%zu_@@@]",
        conn->tag,
        conn->info.httpcode,
        http_code_print(conn->info.httpcode),
        http_reason_print(conn->info.httpcode),
        conn->info.loginfo.counter);
    return ORCA_HTTP_CODE;
  }
  if (conn->info.httpcode >= 200) {
    log_info("[%s] "ANSICOLOR("SUCCESS", ANSI_FG_GREEN)" (%d)%s - %s [@@@_%zu_@@@]",
        conn->tag,
        conn->info.httpcode,
        http_code_print(conn->info.httpcode),
        http_reason_print(conn->info.httpcode),
        conn->info.loginfo.counter);

    if (resp_handle) {
      if (resp_handle->ok_cb) {
        (*resp_handle->ok_cb)(
          conn->info.resp_body.buf,
          conn->info.resp_body.length,
          resp_handle->ok_obj);
      }
      else if (resp_handle->cxt_ok_cb) {
        (*resp_handle->cxt_ok_cb)(
          resp_handle->cxt,
          conn->info.resp_body.buf,
          conn->info.resp_body.length,
          resp_handle->ok_obj);
      }
    }
    return ORCA_OK;
  }
  if (conn->info.httpcode >= 100) {
    log_info("[%s] "ANSICOLOR("INFO", ANSI_FG_GRAY)" (%d)%s - %s [@@@_%zu_@@@]",
        conn->tag,
        conn->info.httpcode,
        http_code_print(conn->info.httpcode),
        http_reason_print(conn->info.httpcode),
        conn->info.loginfo.counter);
    return conn->info.httpcode;
  }
  if (!conn->info.httpcode) {
    log_error("[%s] No http response received by libcurl", 
        conn->tag);
    return ORCA_NO_RESPONSE;
  }
  log_error("[%s] Unusual HTTP response code: %d", conn->tag, conn->info.httpcode);
  return ORCA_UNUSUAL_HTTP_CODE;
}

// make the main thread wait for a specified amount of time
void
ua_block_ms(struct user_agent *ua, const uint64_t wait_ms) 
{
  pthread_mutex_lock(&ua->shared->lock);
  ua->shared->blockuntil_tstamp = cee_timestamp_ms() + wait_ms;
  pthread_mutex_unlock(&ua->shared->lock);
}

/* template function for performing requests */
ORCAcode
ua_vrun(
  struct user_agent *ua,
  struct ua_info *info,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], va_list args)
{
  const char *method_str = http_method_print(http_method);
  static struct sized_buffer blank_req_body = {"", 0};
  if (NULL == req_body) {
    req_body = &blank_req_body;
  }

  struct _ua_conn *conn = get_conn(ua);
  set_url(ua, conn, endpoint, args); //set the request url

  char buf[1024]="";
  ua_reqheader_str(ua, buf, sizeof(buf));

  log_http(
    ua->p_config, 
    &conn->info.loginfo,
    ua,
    conn->info.req_url.start, 
    (struct sized_buffer){buf, sizeof(buf)},
    *req_body,
    "HTTP_SEND_%s", method_str);

  log_trace("[%s] "ANSICOLOR("SEND", ANSI_FG_GREEN)" %s [@@@_%zu_@@@]", 
      conn->tag,
      method_str,
      conn->info.loginfo.counter);

  set_method(ua, conn, http_method, req_body); //set the request method
  ORCAcode code = perform_request(ua, conn, resp_handle);

  pthread_mutex_lock(&ua->shared->lock);
  if (info) {
    memcpy(info, &conn->info, sizeof(struct ua_info));
    asprintf(&info->resp_body.buf, "%.*s", \
        (int)conn->info.resp_body.length, conn->info.resp_body.buf);
    asprintf(&info->resp_header.buf, "%.*s", \
        (int)conn->info.resp_header.length, conn->info.resp_header.buf);
    asprintf(&info->req_url.start, "%.*s", \
        (int)conn->info.req_url.size, conn->info.req_url.start);
  }

  conn_reset(conn); // reset for next iteration
  if (ua->mime) { /// @todo this is temporary
    curl_mime_free(ua->mime); 
    ua->mime = NULL;
  }
  pthread_mutex_unlock(&ua->shared->lock);

  return code;
}

/* template function for performing requests */
ORCAcode
ua_run(
  struct user_agent *ua,
  struct ua_info *info,
  struct ua_resp_handle *resp_handle,
  struct sized_buffer *req_body,
  enum http_method http_method, char endpoint[], ...)
{
  va_list args;
  va_start(args, endpoint);

  ORCAcode code = ua_vrun(
                    ua, 
                    info,
                    resp_handle, 
                    req_body, 
                    http_method, endpoint, args);

  va_end(args);
  return code;
}

void
ua_info_cleanup(struct ua_info *info) 
{
  if (info->req_url.start)
    free(info->req_url.start);
  if (info->resp_body.buf)
    free(info->resp_body.buf);
  if (info->resp_header.buf)
    free(info->resp_header.buf);
  memset(info, 0, sizeof(struct ua_info));
}

/**
 * attempt to get value from matching response header field
 */
struct sized_buffer
ua_info_respheader_field(struct ua_info *info, char field[])
{
  const size_t len = strlen(field);
  struct sized_buffer h_field; // header field
  for (int i=0; i < info->resp_header.size; ++i) {
    h_field = (struct sized_buffer){
      info->resp_header.buf + info->resp_header.pairs[i].field.idx,
      info->resp_header.pairs[i].field.size
    };
    if (len == h_field.size && 0 == strncasecmp(field, h_field.start, len)) {
      return (struct sized_buffer){
        info->resp_header.buf + info->resp_header.pairs[i].value.idx,
        info->resp_header.pairs[i].value.size
      };
    }
  }
  return (struct sized_buffer){NULL, 0};
}

struct sized_buffer
ua_info_get_resp_body(struct ua_info *info) {
  return (struct sized_buffer){info->resp_body.buf, info->resp_body.length};
}
