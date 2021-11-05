#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h> /* isspace() */
#include <string.h>
#include <strings.h>
#include <pthread.h>
/* #include <curl/curl.h> (implicit) */

#include "user-agent.h"
#include "cee-utils.h"

#define CURLE_LOG(conn, ecode)                                                \
  do {                                                                        \
    log_fatal("[%s] (CURLE code: %d) %s", conn->conf->id, ecode,              \
              IS_EMPTY_STRING(conn->errbuf) ? curl_easy_strerror(ecode)       \
                                            : conn->errbuf);                  \
  } while (0)

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
    /** amount of connections node in pool */
    size_t amt;
  } * conn;
  /**
   * the base_url for every conn
   */
  struct sized_buffer base_url;
  /**
   * synchronize conn pool and shared ratelimiting
   */
  struct {
    /** lock every active conn from conn_pool until timestamp */
    uint64_t blockuntil_tstamp;
    pthread_mutex_t lock;
  } * shared;

  /** used for logging */
  struct logconf conf;

  /**
   * user arbitrary data accessed by setopt_cb
   * @see ua_curl_easy_setopt()
   */
  void *data;
  void (*setopt_cb)(CURL *ehandle, void *data);
  /**
   * user arbitrary data accessed by mime_cb
   * @see ua_curl_mime_setopt()
   */
  void *data2;
  curl_mime *mime;
  void (*mime_cb)(curl_mime *mime, void *data2);
};

struct _ua_conn {
  struct logconf *conf; /* ptr to struct user_agent conf */
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
};

const char *
http_code_print(int httpcode)
{
  switch (httpcode) {
  case HTTP_OK: return "OK";
  case HTTP_CREATED: return "CREATED";
  case HTTP_NO_CONTENT: return "NO_CONTENT";
  case HTTP_NOT_MODIFIED: return "NOT_MODIFIED";
  case HTTP_BAD_REQUEST: return "BAD_REQUEST";
  case HTTP_UNAUTHORIZED: return "UNAUTHORIZED";
  case HTTP_FORBIDDEN: return "FORBIDDEN";
  case HTTP_NOT_FOUND: return "NOT_FOUND";
  case HTTP_METHOD_NOT_ALLOWED: return "METHOD_NOT_ALLOWED";
  case HTTP_UNPROCESSABLE_ENTITY: return "UNPROCESSABLE_ENTITY";
  case HTTP_TOO_MANY_REQUESTS: return "TOO_MANY_REQUESTS";
  case HTTP_GATEWAY_UNAVAILABLE: return "GATEWAY_UNAVAILABLE";
  default:
    if (httpcode >= 500) return "5xx_SERVER_ERROR";
    if (httpcode >= 400) return "4xx_CLIENT_ERROR";
    if (httpcode >= 300) return "3xx_REDIRECTING";
    if (httpcode >= 200) return "2xx_SUCCESS";
    if (httpcode >= 100) return "1xx_INFO";
    return "UNUSUAL_HTTP_CODE";
  }
}

const char *
http_reason_print(int httpcode)
{
  switch (httpcode) {
  case HTTP_OK: return "The request was completed succesfully.";
  case HTTP_CREATED: return "The entity was created succesfully.";
  case HTTP_NO_CONTENT:
    return "The request completed succesfully but returned no content.";
  case HTTP_NOT_MODIFIED:
    return "The entity was not modified (no action was taken).";
  case HTTP_BAD_REQUEST:
    return "The request was improperly formatted, or the server couldn't "
           "understand it.";
  case HTTP_UNAUTHORIZED:
    return "The Authorization header was missing or invalid.";
  case HTTP_FORBIDDEN:
    return "The Authorization token you passed did not have permission to the "
           "resource.";
  case HTTP_NOT_FOUND:
    return "The resource at the location specified doesn't exist.";
  case HTTP_METHOD_NOT_ALLOWED:
    return "The HTTP method used is not valid for the location specified.";
  case HTTP_TOO_MANY_REQUESTS: return "You got ratelimited.";
  case HTTP_GATEWAY_UNAVAILABLE:
    return "There was not a gateway available to process your request. Wait a "
           "bit and retry.";
  default:
    if (httpcode >= 500)
      return "The server had an error processing your request.";
    if (httpcode >= 400)
      return "Client side error, request couldn't be processed.";
    if (httpcode >= 300)
      return "Client requires taking additional action to complete the "
             "request";
    if (httpcode >= 200)
      return "The action request was received, understood and accepted.";
    if (httpcode >= 100)
      return "The request was received and understood. The client must wait "
             "for a final response.";
    if (!httpcode) return "Curl couldn't fetch a HTTP response.";
    return "Unusual HTTP method.";
  }
}

const char *
http_method_print(enum http_method method)
{
  switch (method) {
  case HTTP_DELETE: return "DELETE";
  case HTTP_GET: return "GET";
  case HTTP_POST: return "POST";
  case HTTP_MIMEPOST: return "MIMEPOST";
  case HTTP_PATCH: return "PATCH";
  case HTTP_PUT: return "PUT";
  case HTTP_INVALID:
  default: return "INVALID_HTTP_METHOD";
  }
}

enum http_method
http_method_eval(char method[])
{
  if (STREQ(method, "DELETE")) return HTTP_DELETE;
  if (STREQ(method, "GET")) return HTTP_GET;
  if (STREQ(method, "POST")) return HTTP_POST;
  if (STREQ(method, "MIMEPOST")) return HTTP_MIMEPOST;
  if (STREQ(method, "PATCH")) return HTTP_PATCH;
  if (STREQ(method, "PUT")) return HTTP_PUT;
  return HTTP_INVALID;
}

void
ua_reqheader_add(struct user_agent *ua, const char field[], const char value[])
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
    if (field_len == ptr - node->data &&
        0 == strncasecmp(node->data, field, field_len))
    {
      if (strlen(node->data) < ret) {
        free(node->data);
        node->data = strdup(buf);
      }
      else {
        memcpy(node->data, buf, ret + 1);
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
  if (field_len == ptr - node->data &&
      0 == strncasecmp(node->data, field, field_len))
  {
    free(node->data);
    free(node);
    ua->req_header = NULL;
    return; /* EARLY EXIT */
  }

  do { /* iterate linked list to try and find field match */
    if (node->next) {
      if (!(ptr = strchr(node->next->data, ':')))
        ERR("Missing ':' in header: %s", node->next->data);
      if (field_len == ptr - node->next->data &&
          0 == strncasecmp(node->next->data, field, field_len))
      {
        free(node->next->data);
        free(node->next);
        node->next = NULL;
        return; /* EARLY EXIT */
      }
    }
    node = node->next;
  } while (node != NULL);

  logconf_warn(&ua->conf,
               "Couldn't find field '%s' in existing request header", field);
}

char *
ua_reqheader_str(struct user_agent *ua, char *buf, size_t bufsize)
{
  struct curl_slist *node = ua->req_header;
  size_t ret = 0;
  while (NULL != node) {
    ret += snprintf(buf + ret, bufsize - ret, "%s\r\n", node->data);
    VASSERT_S(ret < bufsize, "[%s] Out of bounds write attempt", ua->conf.id);
    node = node->next;
  }
  if (!ret) return NULL;

  buf[ret - 1] = '\0';
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
  if (!(ptr = strchr(buf, ':')))
  { /* returns if can't find ':' field/value delimiter */
    return bufsize;
  }

  ptrdiff_t delim_idx = ptr - buf; /* get ':' position */
  if (!(ptr = strstr(ptr + 1, "\r\n"))) { /*returns if can't find CRLF match */
    return bufsize;
  }

  if (header->bufsize < (header->len + bufsize + 1)) {
    header->bufsize = header->len + bufsize + 1;
    header->buf = realloc(header->buf, header->bufsize);
  }
  memcpy(&header->buf[header->len], buf, bufsize);

  /* get the field part of the string */
  header->pairs[header->size].field.idx = header->len;
  header->pairs[header->size].field.size = delim_idx;

  /* offsets blank characters */
  size_t bufoffset = 1; /* starts after the ':' delimiter */
  while (delim_idx + bufoffset < bufsize) {
    if (!isspace(buf[delim_idx + bufoffset]))
      break; /* EARLY BREAK (not blank character) */
    ++bufoffset;
  }

  /* get the value part of the string */
  header->pairs[header->size].value.idx =
    header->len + (delim_idx + bufoffset);
  header->pairs[header->size].value.size =
    (ptr - buf) - (delim_idx + bufoffset);

  header->len += bufsize;

  ++header->size; /* update header amount of field/value header */
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

  /*increase response body memory block size only if necessary */
  if (body->bufsize < (body->len + bufchunk_size + 1)) {
    body->bufsize = body->len + bufchunk_size + 1;
    body->buf = realloc(body->buf, body->bufsize);
  }
  memcpy(&body->buf[body->len], buf, bufchunk_size);
  body->len += bufchunk_size;
  body->buf[body->len] = '\0';
  return bufchunk_size;
}

void
ua_curl_easy_setopt(struct user_agent *ua,
                    void *data,
                    void(setopt_cb)(CURL *ehandle, void *data))
{
  ua->setopt_cb = setopt_cb;
  ua->data = data;
}

void
ua_curl_mime_setopt(struct user_agent *ua,
                    void *data,
                    void(mime_cb)(curl_mime *mime, void *data))
{
  ua->mime_cb = mime_cb;
  ua->data2 = data;
}

static struct _ua_conn *
conn_init(struct user_agent *ua)
{
  struct _ua_conn *new_conn = calloc(1, sizeof(struct _ua_conn));
  new_conn->conf = &ua->conf;

  CURL *new_ehandle = curl_easy_init(); /* will be assigned to new_conn */

  /*set error buffer for capturing CURL error descriptions */
  curl_easy_setopt(new_ehandle, CURLOPT_ERRORBUFFER, new_conn->errbuf);
  /*set ptr to request header we will be using for API communication */
  curl_easy_setopt(new_ehandle, CURLOPT_HTTPHEADER, ua->req_header);
  /*enable follow redirections */
  curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  /*set response body callback */
  curl_easy_setopt(new_ehandle, CURLOPT_WRITEFUNCTION, &conn_respbody_cb);
  /*set ptr to response body to be filled at callback */
  curl_easy_setopt(new_ehandle, CURLOPT_WRITEDATA, &new_conn->info.body);
  /*set response header callback */
  curl_easy_setopt(new_ehandle, CURLOPT_HEADERFUNCTION, &conn_respheader_cb);
  /*set ptr to response header to be filled at callback */
  curl_easy_setopt(new_ehandle, CURLOPT_HEADERDATA, &new_conn->info.header);
  /* execute user-defined curl_easy_setopts */
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
  conn->info.body.len = 0;
  conn->info.header.len = 0;
  conn->info.header.size = 0;
  *conn->errbuf = '\0';
}

static struct _ua_conn *
get_conn(struct user_agent *ua)
{
  pthread_mutex_lock(&ua->shared->lock);
  struct _ua_conn *ret_conn = NULL;

  size_t i = 0;
  while (i < ua->conn->amt) {
    if (!ua->conn->pool[i]->is_busy) {
      ret_conn = ua->conn->pool[i];
      break; /* EARLY BREAK */
    }
    ++i;
  }
  if (!ret_conn) { /* no available conn, create new */
    ++ua->conn->amt;
    ua->conn->pool =
      realloc(ua->conn->pool, ua->conn->amt * sizeof *ua->conn->pool);
    ret_conn = ua->conn->pool[ua->conn->amt - 1] = conn_init(ua);
  }
  VASSERT_S(NULL != ret_conn, "[%s] (Internal error) Couldn't fetch conn",
            ua->conf.id);
  ret_conn->is_busy = true;
  pthread_mutex_unlock(&ua->shared->lock);
  return ret_conn;
}

struct user_agent *
ua_init(struct logconf *conf)
{
  struct user_agent *new_ua = calloc(1, sizeof *new_ua);
  new_ua->conn = calloc(1, sizeof *new_ua->conn);
  new_ua->shared = calloc(1, sizeof *new_ua->shared);

  /* default header */
  ua_reqheader_add(new_ua, "User-Agent",
                   "Orca (https://github.com/cee-studio/orca)");
  ua_reqheader_add(new_ua, "Content-Type", "application/json");
  ua_reqheader_add(new_ua, "Accept", "application/json");

  logconf_branch(&new_ua->conf, conf, "USER_AGENT");

  if (pthread_mutex_init(&new_ua->shared->lock, NULL)) {
    logconf_fatal(&new_ua->conf, "Couldn't initialize mutex");
    ABORT();
  }

  new_ua->is_original = true;

  return new_ua;
}

struct user_agent *
ua_clone(struct user_agent *orig_ua)
{
  struct user_agent *clone_ua = malloc(sizeof(struct user_agent));

  pthread_mutex_lock(&orig_ua->shared->lock);
  memcpy(clone_ua, orig_ua, sizeof(struct user_agent));

  /* copy orig_ua header into clone_ua */
  struct curl_slist *orig_node = orig_ua->req_header;
  clone_ua->req_header = curl_slist_append(NULL, orig_node->data);
  while (NULL != orig_node->next) {
    orig_node = orig_node->next;
    curl_slist_append(clone_ua->req_header, orig_node->data);
  }

  /* use a different base_url context than the original */
  clone_ua->base_url.size =
    asprintf(&clone_ua->base_url.start, "%.*s", (int)orig_ua->base_url.size,
             orig_ua->base_url.start);

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

  if (ua->is_original) {
    if (ua->conn->pool) {
      size_t i;
      for (i = 0; i < ua->conn->amt; ++i)
        conn_cleanup(ua->conn->pool[i]);
      free(ua->conn->pool);
    }
    free(ua->conn);

    pthread_mutex_destroy(&ua->shared->lock);
    free(ua->shared);
    logconf_cleanup(&ua->conf);
  }

  free(ua);
}

const char *
ua_get_url(struct user_agent *ua)
{
  return ua->base_url.start;
}

void
ua_set_url(struct user_agent *ua, const char *base_url)
{
  if (ua->base_url.start) free(ua->base_url.start);
  ua->base_url.size = asprintf(&ua->base_url.start, "%s", base_url);
}

/* set specific http method used for the request */
static void
set_method(struct user_agent *ua,
           struct _ua_conn *conn,
           enum http_method method,
           struct sized_buffer *req_body)
{
  /* resets any preexisting CUSTOMREQUEST */
  curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, NULL);

  switch (method) {
  case HTTP_DELETE:
    curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, "DELETE");
    break;
  case HTTP_GET:
    curl_easy_setopt(conn->ehandle, CURLOPT_HTTPGET, 1L);
    return; /* EARLY RETURN */
  case HTTP_POST: curl_easy_setopt(conn->ehandle, CURLOPT_POST, 1L); break;
  case HTTP_MIMEPOST: /*@todo this is temporary */
    ASSERT_S(NULL != ua->mime_cb, "Missing 'ua->mime_cb' callback");
    ASSERT_S(NULL == ua->mime, "'ua->mime' not freed");
    ua->mime = curl_mime_init(conn->ehandle);
    (*ua->mime_cb)(ua->mime, ua->data2);
    curl_easy_setopt(conn->ehandle, CURLOPT_MIMEPOST, ua->mime);
    return; /* EARLY RETURN */
  case HTTP_PATCH:
    curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, "PATCH");
    break;
  case HTTP_PUT:
    curl_easy_setopt(conn->ehandle, CURLOPT_CUSTOMREQUEST, "PUT");
    break;
  default:
    logconf_fatal(conn->conf, "Unknown http method (code: %d)", method);
    ABORT();
  }

  /*set ptr to payload that will be sent via POST/PUT/PATCH */
  curl_easy_setopt(conn->ehandle, CURLOPT_POSTFIELDS, req_body->start);
  curl_easy_setopt(conn->ehandle, CURLOPT_POSTFIELDSIZE, req_body->size);
}

static void
set_url(struct user_agent *ua, struct _ua_conn *conn, char endpoint[])
{
  size_t url_len = 2 + ua->base_url.size + strlen(endpoint);

  if (url_len > conn->info.req_url.size) {
    void *tmp = realloc(conn->info.req_url.start, url_len);
    ASSERT_S(NULL != tmp, "Couldn't increase buffer's length");
    conn->info.req_url =
      (struct sized_buffer){ .start = tmp, .size = url_len };
  }

  size_t ret = snprintf(conn->info.req_url.start, conn->info.req_url.size,
                        "%.*s", (int)ua->base_url.size, ua->base_url.start);
  ASSERT_S(ret < conn->info.req_url.size, "Out of bounds write attempt");
  ret += snprintf(conn->info.req_url.start + ret,
                  conn->info.req_url.size - ret, "%s", endpoint);
  ASSERT_S(ret < conn->info.req_url.size, "Out of bounds write attempt");

  CURLcode ecode =
    curl_easy_setopt(conn->ehandle, CURLOPT_URL, conn->info.req_url.start);
  if (ecode != ORCA_OK) CURLE_LOG(conn, ecode);

  logconf_trace(conn->conf, "Request URL: %s", conn->info.req_url.start);
}

static CURLcode
send_request(struct user_agent *ua, struct _ua_conn *conn, int *httpcode)
{
  CURLcode ecode;
  char *resp_url = NULL;

  /* enforces global ratelimiting with ua_block_ms(); */
  pthread_mutex_lock(&ua->shared->lock);
  cee_sleep_ms(ua->shared->blockuntil_tstamp - cee_timestamp_ms());

  ecode = curl_easy_perform(conn->ehandle);
  conn->info.req_tstamp = cee_timestamp_ms();
  /* get response's code */
  curl_easy_getinfo(conn->ehandle, CURLINFO_RESPONSE_CODE, httpcode);
  /* get response's url */
  curl_easy_getinfo(conn->ehandle, CURLINFO_EFFECTIVE_URL, &resp_url);

  logconf_http(
    &ua->conf, &conn->info.loginfo, resp_url,
    (struct sized_buffer){ conn->info.header.buf, conn->info.header.len },
    (struct sized_buffer){ conn->info.body.buf, conn->info.body.len },
    "HTTP_RCV_%s(%d)", http_code_print(*httpcode), *httpcode);
  pthread_mutex_unlock(&ua->shared->lock);

  return ecode;
}

static ORCAcode
perform_request(struct user_agent *ua,
                struct _ua_conn *conn,
                struct ua_resp_handle *resp_handle)
{
  CURLcode ecode = send_request(ua, conn, &conn->info.httpcode);
  if (ecode != CURLE_OK) {
    CURLE_LOG(conn, ecode);
    return ORCA_CURLE_INTERNAL;
  }

  /* triggers response related callbacks */
  if (conn->info.httpcode >= 500 && conn->info.httpcode < 600) {
    logconf_error(
      conn->conf,
      ANSICOLOR("SERVER ERROR", ANSI_FG_RED) " (%d)%s - %s [@@@_%zu_@@@]",
      conn->info.httpcode, http_code_print(conn->info.httpcode),
      http_reason_print(conn->info.httpcode), conn->info.loginfo.counter);

    if (resp_handle) {
      if (resp_handle->err_cb) {
        (*resp_handle->err_cb)(conn->info.body.buf, conn->info.body.len,
                               resp_handle->err_obj);
      }
      else if (resp_handle->cxt_err_cb) {
        (*resp_handle->cxt_err_cb)(resp_handle->cxt, conn->info.body.buf,
                                   conn->info.body.len, resp_handle->err_obj);
      }
    }
    return ORCA_HTTP_CODE;
  }
  if (conn->info.httpcode >= 400) {
    logconf_error(
      conn->conf,
      ANSICOLOR("CLIENT ERROR", ANSI_FG_RED) " (%d)%s - %s [@@@_%zu_@@@]",
      conn->info.httpcode, http_code_print(conn->info.httpcode),
      http_reason_print(conn->info.httpcode), conn->info.loginfo.counter);

    if (resp_handle) {
      if (resp_handle->err_cb) {
        (*resp_handle->err_cb)(conn->info.body.buf, conn->info.body.len,
                               resp_handle->err_obj);
      }
      else if (resp_handle->cxt_err_cb) {
        (*resp_handle->cxt_err_cb)(resp_handle->cxt, conn->info.body.buf,
                                   conn->info.body.len, resp_handle->err_obj);
      }
    }
    return ORCA_HTTP_CODE;
  }
  if (conn->info.httpcode >= 300) {
    logconf_warn(
      conn->conf,
      ANSICOLOR("REDIRECTING", ANSI_FG_YELLOW) " (%d)%s - %s [@@@_%zu_@@@]",
      conn->info.httpcode, http_code_print(conn->info.httpcode),
      http_reason_print(conn->info.httpcode), conn->info.loginfo.counter);
    return ORCA_HTTP_CODE;
  }
  if (conn->info.httpcode >= 200) {
    logconf_info(
      conn->conf,
      ANSICOLOR("SUCCESS", ANSI_FG_GREEN) " (%d)%s - %s [@@@_%zu_@@@]",
      conn->info.httpcode, http_code_print(conn->info.httpcode),
      http_reason_print(conn->info.httpcode), conn->info.loginfo.counter);

    if (resp_handle) {
      if (resp_handle->ok_cb) {
        (*resp_handle->ok_cb)(conn->info.body.buf, conn->info.body.len,
                              resp_handle->ok_obj);
      }
      else if (resp_handle->cxt_ok_cb) {
        (*resp_handle->cxt_ok_cb)(resp_handle->cxt, conn->info.body.buf,
                                  conn->info.body.len, resp_handle->ok_obj);
      }
    }
    return ORCA_OK;
  }
  if (conn->info.httpcode >= 100) {
    logconf_info(
      conn->conf, ANSICOLOR("INFO", ANSI_FG_GRAY) " (%d)%s - %s [@@@_%zu_@@@]",
      conn->info.httpcode, http_code_print(conn->info.httpcode),
      http_reason_print(conn->info.httpcode), conn->info.loginfo.counter);
    return conn->info.httpcode;
  }
  if (!conn->info.httpcode) {
    logconf_error(conn->conf, "No http response received by libcurl");
    return ORCA_NO_RESPONSE;
  }
  logconf_error(conn->conf, "Unusual HTTP response code: %d",
                conn->info.httpcode);
  return ORCA_UNUSUAL_HTTP_CODE;
}

/* make the main thread wait for a specified amount of time */
void
ua_block_ms(struct user_agent *ua, const uint64_t wait_ms)
{
  pthread_mutex_lock(&ua->shared->lock);
  ua->shared->blockuntil_tstamp = cee_timestamp_ms() + wait_ms;
  pthread_mutex_unlock(&ua->shared->lock);
}

/* template function for performing requests */
ORCAcode
ua_run(struct user_agent *ua,
       struct ua_info *info,
       struct ua_resp_handle *resp_handle,
       struct sized_buffer *req_body,
       enum http_method http_method,
       char endpoint[])
{
  const char *method_str = http_method_print(http_method);
  static struct sized_buffer blank_req_body = { "", 0 };
  if (NULL == req_body) {
    req_body = &blank_req_body;
  }

  struct _ua_conn *conn = get_conn(ua);
  set_url(ua, conn, endpoint); /*set the request url */

  char buf[1024] = "";
  ua_reqheader_str(ua, buf, sizeof(buf));

  logconf_http(&ua->conf, &conn->info.loginfo, conn->info.req_url.start,
               (struct sized_buffer){ buf, sizeof(buf) }, *req_body,
               "HTTP_SEND_%s", method_str);

  logconf_trace(conn->conf,
                ANSICOLOR("SEND", ANSI_FG_GREEN) " %s [@@@_%zu_@@@]",
                method_str, conn->info.loginfo.counter);

  set_method(ua, conn, http_method, req_body); /*set the request method */
  ORCAcode code = perform_request(ua, conn, resp_handle);

  pthread_mutex_lock(&ua->shared->lock);
  if (info) {
    memcpy(info, &conn->info, sizeof(struct ua_info));
    asprintf(&info->body.buf, "%.*s", (int)conn->info.body.len,
             conn->info.body.buf);
    asprintf(&info->header.buf, "%.*s", (int)conn->info.header.len,
             conn->info.header.buf);
    asprintf(&info->req_url.start, "%.*s", (int)conn->info.req_url.size,
             conn->info.req_url.start);
  }

  conn_reset(conn); /* reset for next iteration */
  if (ua->mime) { /**< @todo this is temporary */
    curl_mime_free(ua->mime);
    ua->mime = NULL;
  }
  pthread_mutex_unlock(&ua->shared->lock);

  return code;
}

void
ua_info_cleanup(struct ua_info *info)
{
  if (info->req_url.start) free(info->req_url.start);
  if (info->body.buf) free(info->body.buf);
  if (info->header.buf) free(info->header.buf);
  memset(info, 0, sizeof(struct ua_info));
}

/**
 * attempt to get value from matching response header field
 */
struct sized_buffer
ua_info_header_get(struct ua_info *info, char field[])
{
  const size_t len = strlen(field);
  struct sized_buffer h_field; /* header field */
  int i;
  for (i = 0; i < info->header.size; ++i) {
    h_field = (struct sized_buffer){ info->header.buf +
                                       info->header.pairs[i].field.idx,
                                     info->header.pairs[i].field.size };
    if (len == h_field.size && 0 == strncasecmp(field, h_field.start, len)) {
      return (struct sized_buffer){ info->header.buf +
                                      info->header.pairs[i].value.idx,
                                    info->header.pairs[i].value.size };
    }
  }
  return (struct sized_buffer){ NULL, 0 };
}

struct sized_buffer
ua_info_get_body(struct ua_info *info)
{
  return (struct sized_buffer){ info->body.buf, info->body.len };
}
