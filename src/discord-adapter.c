#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "discord.h"
#include "discord-internal.h"

/* No-lock alternative to discord_timestamp() */
#define NOW(p_adapter) (CLIENT(p_adapter, adapter)->gw.timer->now)

static void
setopt_cb(struct ua_conn *conn, void *p_token)
{
  struct sized_buffer *token = p_token;
  char auth[128];
  size_t len;

  len =
    snprintf(auth, sizeof(auth), "Bot %.*s", (int)token->size, token->start);
  ASSERT_S(len < sizeof(auth), "Out of bounds write attempt");

  ua_conn_add_header(conn, "Authorization", auth);

#if 0 /* enable for debugging */
  curl_easy_setopt(ua_conn_get_easy_handle(conn), CURLOPT_VERBOSE, 1L);
#endif
}

static void
on_io_poller_curl(CURLM *multi, void *user_data)
{
  (void) multi;
  discord_adapter_perform(user_data);
}

void
discord_adapter_init(struct discord_adapter *adapter,
                     struct logconf *conf,
                     struct sized_buffer *token)
{
  const struct sized_buffer key_null = { "null", 4 }, key_miss = { "miss", 4 };
  struct ua_attr attr = { 0 };

  attr.conf = conf;
  adapter->ua = ua_init(&attr);
  ua_set_url(adapter->ua, DISCORD_API_BASE_URL);

  if (!token->size) {
    /* no token means a webhook-only client */
    logconf_branch(&adapter->conf, conf, "DISCORD_WEBHOOK");
  }
  else {
    /* bot client */
    logconf_branch(&adapter->conf, conf, "DISCORD_HTTP");
    ua_set_opt(adapter->ua, token, &setopt_cb);
  }

  adapter->mhandle = curl_multi_init();
  io_poller_curlm_add(CLIENT(adapter, adapter)->io_poller, adapter->mhandle, on_io_poller_curl, adapter);

  /* global ratelimiting resources */
  adapter->global = calloc(1, sizeof *adapter->global);
  if (pthread_rwlock_init(&adapter->global->rwlock, NULL))
    ERR("Couldn't initialize pthread rwlock");
  if (pthread_mutex_init(&adapter->global->lock, NULL))
    ERR("Couldn't initialize pthread mutex");

  /* initialize 'singleton' buckets */
  adapter->b_null = discord_bucket_init(adapter, &key_null, 1L);
  adapter->b_miss = discord_bucket_init(adapter, &key_miss, LONG_MAX);

  /* idleq is malloc'd to guarantee a client cloned by discord_clone() will
   * share the same queue with the original */
  adapter->async.idleq = malloc(sizeof(QUEUE));
  QUEUE_INIT(adapter->async.idleq);
  /* initialize min-heap for handling request timeouts */
  heap_init(&adapter->async.timeouts);

  adapter->retry_limit = 3; /**< hard limit for now */
}

static void
_discord_context_cleanup(struct discord_context *cxt)
{
  if (cxt->body.buf.start) free(cxt->body.buf.start);
  free(cxt);
}

void
discord_adapter_cleanup(struct discord_adapter *adapter)
{
  struct discord_context *cxt;
  QUEUE queue;
  QUEUE *q;

  /* cleanup User-Agent handle */
  ua_cleanup(adapter->ua);

  io_poller_curlm_del(CLIENT(adapter, adapter)->io_poller, adapter->mhandle);
  curl_multi_cleanup(adapter->mhandle);

  /* move pending requests to idle */
  discord_adapter_stop_all(adapter);

  discord_buckets_cleanup(adapter);

  /* cleanup global resources */
  pthread_rwlock_destroy(&adapter->global->rwlock);
  pthread_mutex_destroy(&adapter->global->lock);
  free(adapter->global);

  /* cleanup idle requests queue */
  QUEUE_MOVE(adapter->async.idleq, &queue);
  while (!QUEUE_EMPTY(&queue)) {
    q = QUEUE_HEAD(&queue);
    cxt = QUEUE_DATA(q, struct discord_context, entry);
    QUEUE_REMOVE(&cxt->entry);
    _discord_context_cleanup(cxt);
  }

  if (adapter->async.ret.size) free(adapter->async.ret.start);

  free(adapter->async.idleq);
}

static CCORDcode _discord_adapter_run_sync(struct discord_adapter *adapter,
                                           struct discord_request_attr *attr,
                                           struct sized_buffer *body,
                                           enum http_method method,
                                           char endpoint[DISCORD_ENDPT_LEN],
                                           char route[DISCORD_ROUTE_LEN]);

static CCORDcode _discord_adapter_run_async(struct discord_adapter *adapter,
                                            struct discord_request_attr *attr,
                                            struct sized_buffer *body,
                                            enum http_method method,
                                            char endpoint[DISCORD_ENDPT_LEN],
                                            char route[DISCORD_ROUTE_LEN]);

/* template function for performing requests */
CCORDcode
discord_adapter_run(struct discord_adapter *adapter,
                    struct discord_request_attr *attr,
                    struct sized_buffer *body,
                    enum http_method method,
                    char endpoint_fmt[],
                    ...)
{
  static struct discord_request_attr blank_attr = { 0 };
  char endpoint[DISCORD_ENDPT_LEN];
  char route[DISCORD_ROUTE_LEN];
  va_list args;
  size_t len;

  /* have it point somewhere */
  if (!attr) attr = &blank_attr;

  /* build the endpoint string */
  va_start(args, endpoint_fmt);
  len = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
  ASSERT_S(len < sizeof(endpoint), "Out of bounds write attempt");
  va_end(args);

  /* build the ratelimiting route */
  va_start(args, endpoint_fmt);
  discord_bucket_get_route(method, route, endpoint_fmt, args);
  va_end(args);

  /* enqueue asynchronous request */
  if (true == adapter->async_enable) {
    adapter->async_enable = false;
    return _discord_adapter_run_async(adapter, attr, body, method, endpoint,
                                      route);
  }

  /* perform blocking request */
  return _discord_adapter_run_sync(adapter, attr, body, method, endpoint,
                                   route);
}

void
discord_adapter_async_next(struct discord_adapter *adapter,
                           struct discord_async_attr *attr)
{
  adapter->async_enable = true;

  if (attr)
    memcpy(&adapter->async.attr, attr, sizeof(struct discord_async_attr));
  else
    memset(&adapter->async.attr, 0, sizeof(struct discord_async_attr));
}

static void
_discord_adapter_set_errbuf(struct discord_adapter *adapter,
                            struct sized_buffer *body)
{
  size_t len;

  len = snprintf(adapter->errbuf, sizeof(adapter->errbuf), "%.*s",
                 (int)body->size, body->start);
  ASSERT_S(len < sizeof(adapter->errbuf), "Out of bounds write attempt");
}

static void
_discord_context_to_mime(curl_mime *mime, void *p_cxt)
{
  struct discord_context *cxt = p_cxt;
  struct discord_attachment **atchs = cxt->attr.attachments;
  struct sized_buffer *body = &cxt->body.buf;
  curl_mimepart *part;
  char name[64];
  int i;

  /* json part */
  if (body->start && body->size) {
    part = curl_mime_addpart(mime);
    curl_mime_data(part, body->start, body->size);
    curl_mime_type(part, "application/json");
    curl_mime_name(part, "payload_json");
  }

  /* attachment part */
  for (i = 0; atchs[i]; ++i) {
    snprintf(name, sizeof(name), "files[%d]", i);
    if (atchs[i]->content) {
      part = curl_mime_addpart(mime);
      curl_mime_data(part, atchs[i]->content,
                     atchs[i]->size ? atchs[i]->size : CURL_ZERO_TERMINATED);
      curl_mime_filename(part, IS_EMPTY_STRING(atchs[i]->filename)
                                 ? "a.out"
                                 : atchs[i]->filename);
      curl_mime_type(part, IS_EMPTY_STRING(atchs[i]->content_type)
                             ? "application/octet-stream"
                             : atchs[i]->content_type);
      curl_mime_name(part, name);
    }
    else if (!IS_EMPTY_STRING(atchs[i]->filename)) {
      /* fetch local file by the filename */
      part = curl_mime_addpart(mime);
      curl_mime_filedata(part, atchs[i]->filename);
      curl_mime_type(part, IS_EMPTY_STRING(atchs[i]->content_type)
                             ? "application/octet-stream"
                             : atchs[i]->content_type);
      curl_mime_name(part, name);
    }
  }
}

/* return true if there should be a retry attempt */
static bool
_discord_adapter_get_info(struct discord_adapter *adapter,
                          struct ua_info *info,
                          int64_t *wait_ms)
{
  if (info->code != CCORD_HTTP_CODE) {
    /** CCORD_OK or internal error */
    return false;
  }

  switch (info->httpcode) {
  case HTTP_FORBIDDEN:
  case HTTP_NOT_FOUND:
  case HTTP_BAD_REQUEST:
    info->code = CCORD_DISCORD_JSON_CODE;
    return false;
  case HTTP_UNAUTHORIZED:
    logconf_fatal(&adapter->conf,
                  "UNAUTHORIZED: Please provide a valid authentication token");
    info->code = CCORD_DISCORD_BAD_AUTH;
    return false;
  case HTTP_METHOD_NOT_ALLOWED:
    logconf_fatal(&adapter->conf,
                  "METHOD_NOT_ALLOWED: The server couldn't recognize the "
                  "received HTTP method");
    return false;
  case HTTP_TOO_MANY_REQUESTS: {
    struct sized_buffer body = ua_info_get_body(info);
    double retry_after = 1.0;
    bool is_global = false;
    char message[256] = "";

    json_extract(body.start, body.size,
                 "(global):b (message):.*s (retry_after):lf", &is_global,
                 sizeof(message), message, &retry_after);

    if (is_global) {
      struct discord *client = CLIENT(adapter, adapter);
      u64_unix_ms_t global;

      global = discord_adapter_get_global_wait(adapter);
      *wait_ms = (int64_t)(global - discord_timestamp(client));

      logconf_warn(&adapter->conf,
                   "429 GLOBAL RATELIMITING (wait: %" PRId64 " ms) : %s",
                   *wait_ms, message);
    }
    else {
      *wait_ms = (int64_t)(1000 * retry_after);

      logconf_warn(&adapter->conf,
                   "429 RATELIMITING (wait: %" PRId64 " ms) : %s", *wait_ms,
                   message);
    }

    return true;
  }
  default:
    if (info->httpcode >= 500) { /* Server Error */
      return true;
    }
    return false;
  }
}

/* SYNCHRONOUS REQUEST LOGIC */

/* perform a blocking request */
static CCORDcode
_discord_adapter_run_sync(struct discord_adapter *adapter,
                          struct discord_request_attr *attr,
                          struct sized_buffer *body,
                          enum http_method method,
                          char endpoint[DISCORD_ENDPT_LEN],
                          char route[DISCORD_ROUTE_LEN])
{
  struct ua_conn_attr conn_attr = { method, body, endpoint, NULL };
  /* throw-away for ua_conn_set_mime() */
  struct discord_context cxt = { 0 };
  struct discord_bucket *b;
  struct ua_conn *conn;
  int retry_attempt = 0;
  bool retry;
  CCORDcode code;

  b = discord_bucket_get(adapter, route);
  conn = ua_conn_start(adapter->ua);

  if (HTTP_MIMEPOST == method) {
    cxt.attr.attachments = attr->attachments;
    cxt.body.buf = *body;

    ua_conn_add_header(conn, "Content-Type", "multipart/form-data");
    ua_conn_set_mime(conn, &cxt, &_discord_context_to_mime);
  }
  else {
    ua_conn_add_header(conn, "Content-Type", "application/json");
  }

  ua_conn_setup(conn, &conn_attr);

  pthread_mutex_lock(&b->lock);
  do {
    int64_t wait_ms = discord_bucket_get_wait(adapter, b);

    if (wait_ms > 0) {
      /* block thread's runtime for delay amount */
      logconf_info(&adapter->conf, "[%.4s] RATELIMITING (wait %" PRId64 " ms)",
                   b->hash, wait_ms);
      cog_sleep_ms(wait_ms);

      wait_ms = 0LL; /* reset */
    }

    /* perform blocking request, and check results */
    switch (code = ua_conn_easy_perform(conn)) {
    case CCORD_OK: {
      struct discord *client = CLIENT(adapter, adapter);
      struct ua_info info = { 0 };
      struct sized_buffer body;

      ua_info_extract(conn, &info);
      retry = _discord_adapter_get_info(adapter, &info, &wait_ms);

      body = ua_info_get_body(&info);
      if (info.code != CCORD_OK) {
        _discord_adapter_set_errbuf(adapter, &body);
      }
      else if (attr->ret) {
        /* initialize ret */
        if (attr->init) attr->init(attr->ret);

        /* populate ret */
        if (attr->from_json) attr->from_json(body.start, body.size, attr->ret);
      }

      code = info.code;

      /* in the off-chance of having consecutive blocking calls, update
       *        timestamp used for ratelimiting
       * TODO: redundant for REST-only clients
       * TODO: create discord_timestamp_update() */
      ws_timestamp_update(client->gw.ws);

      discord_bucket_build(adapter, b, route, &info);

      if (wait_ms) cog_sleep_ms(wait_ms);

      ua_info_cleanup(&info);
    } break;
    case CCORD_CURLE_INTERNAL:
      logconf_error(&adapter->conf, "Curl internal error, will retry again");
      retry = true;
      break;
    default:
      logconf_error(&adapter->conf, "CCORD code: %d", code);
      retry = false;
      break;
    }

    ua_conn_reset(conn);

  } while (retry && retry_attempt++ < adapter->retry_limit);
  pthread_mutex_unlock(&b->lock);

  /* reset conn and mark it as free to use */
  ua_conn_stop(conn);

  return code;
}

/* ASYNCHRONOUS REQUEST LOGIC */

/* TODO: make this kind of function specs generated (optional)
 *
 * Only the fields that are required at _discord_context_to_mime()
 *        are duplicated*/
static struct discord_attachment **
_discord_attachment_list_dup(struct discord_attachment **src)
{
  size_t i, len = ntl_length((ntl_t)src);
  struct discord_attachment **dest;

  dest = (struct discord_attachment **)ntl_calloc(len, sizeof **dest);

  for (i = 0; src[i]; ++i) {
    memcpy(dest[i], src[i], sizeof **dest);
    if (src[i]->content) {
      dest[i]->content = strdup(src[i]->content);
    }
    if (src[i]->filename) {
      dest[i]->filename = strdup(src[i]->filename);
    }
    if (src[i]->content_type) {
      dest[i]->content_type = strdup(src[i]->content_type);
    }
  }

  return dest;
}

static int
timer_less_than(const struct heap_node *ha, const struct heap_node *hb)
{
  const struct discord_context *a =
    CONTAINEROF(ha, struct discord_context, node);
  const struct discord_context *b =
    CONTAINEROF(hb, struct discord_context, node);

  return a->timeout_ms <= b->timeout_ms;
}

static void
_discord_context_reset(struct discord_context *cxt)
{
  cxt->bucket = NULL;
  cxt->done = NULL;
  cxt->fail = NULL;
  cxt->body.buf.size = 0;
  cxt->method = 0;
  *cxt->endpoint = '\0';
  *cxt->route = '\0';
  cxt->conn = NULL;
  cxt->timeout_ms = 0;
  cxt->retry_attempt = 0;

  if (cxt->attr.attachments)
    discord_attachment_list_free(cxt->attr.attachments);

  memset(&cxt->attr, 0, sizeof(struct discord_request_attr));
  memset(&cxt->udata, 0, sizeof cxt->udata);
}

static void
_discord_context_populate(struct discord_context *cxt,
                          struct discord_adapter *adapter,
                          struct discord_request_attr *attr,
                          struct sized_buffer *body,
                          enum http_method method,
                          char endpoint[DISCORD_ENDPT_LEN],
                          char route[DISCORD_ROUTE_LEN])
{
  cxt->method = method;
  /* user callbacks */
  cxt->done = adapter->async.attr.done;
  cxt->fail = adapter->async.attr.fail;
  /* user data */
  cxt->udata.data = adapter->async.attr.data;
  cxt->udata.cleanup = adapter->async.attr.cleanup;

  memcpy(&cxt->attr, attr, sizeof(struct discord_request_attr));
  if (attr->attachments) {
    cxt->attr.attachments = _discord_attachment_list_dup(attr->attachments);
  }

  if (cxt->attr.size) {
    if (cxt->attr.size > adapter->async.ret.size) {
      void *tmp = realloc(adapter->async.ret.start, cxt->attr.size);
      VASSERT_S(tmp != NULL, "Couldn't increase buffer %zu -> %zu (bytes)",
                adapter->async.ret.size, cxt->attr.size);

      adapter->async.ret.start = tmp;
      adapter->async.ret.size = cxt->attr.size;
    }

    cxt->attr.ret = &adapter->async.ret.start;
  }

  if (body) {
    /* copy request body */
    if (body->size > cxt->body.memsize) {
      /* needs to increase buffer size */
      void *tmp = realloc(cxt->body.buf.start, body->size);
      ASSERT_S(tmp != NULL, "Out of memory");

      cxt->body.buf.start = tmp;
      cxt->body.memsize = body->size;
    }
    memcpy(cxt->body.buf.start, body->start, body->size);
    cxt->body.buf.size = body->size;
  }

  /* copy endpoint over to cxt */
  memcpy(cxt->endpoint, endpoint, sizeof(cxt->endpoint));

  /* copy bucket route */
  memcpy(cxt->route, route, DISCORD_ROUTE_LEN);

  /* bucket pertaining to the request */
  cxt->bucket = discord_bucket_get(adapter, route);
}

static void
_discord_context_set_timeout(struct discord_adapter *adapter,
                             u64_unix_ms_t timeout,
                             struct discord_context *cxt)
{
  cxt->bucket->freeze = true;

  cxt->timeout_ms = timeout;

  heap_insert(&adapter->async.timeouts, &cxt->node, &timer_less_than);
}

/* true if a timeout has been set, false otherwise */
static bool
_discord_context_timeout(struct discord_adapter *adapter,
                         struct discord_context *cxt)
{
  u64_unix_ms_t now = NOW(adapter);
  u64_unix_ms_t timeout = discord_bucket_get_timeout(adapter, cxt->bucket);

  if (now > timeout) return false;

  logconf_info(&adapter->conf, "[%.4s] RATELIMITING (timeout %" PRId64 " ms)",
               cxt->bucket->hash, (int64_t)(timeout - now));

  _discord_context_set_timeout(adapter, timeout, cxt);

  return true;
}

/* enqueue a request to be executed asynchronously */
static CCORDcode
_discord_adapter_run_async(struct discord_adapter *adapter,
                           struct discord_request_attr *attr,
                           struct sized_buffer *body,
                           enum http_method method,
                           char endpoint[DISCORD_ENDPT_LEN],
                           char route[DISCORD_ROUTE_LEN])
{
  struct discord_context *cxt;

  if (QUEUE_EMPTY(adapter->async.idleq)) {
    /* create new request handler */
    cxt = calloc(1, sizeof(struct discord_context));
  }
  else {
    /* get from idle requests queue */
    QUEUE *q = QUEUE_HEAD(adapter->async.idleq);
    QUEUE_REMOVE(q);

    cxt = QUEUE_DATA(q, struct discord_context, entry);
  }
  QUEUE_INIT(&cxt->entry);

  _discord_context_populate(cxt, adapter, attr, body, method, endpoint, route);

  if (adapter->async.attr.high_p)
    QUEUE_INSERT_HEAD(&cxt->bucket->waitq, &cxt->entry);
  else
    QUEUE_INSERT_TAIL(&cxt->bucket->waitq, &cxt->entry);

  /* reset for next call */
  memset(&adapter->async.attr, 0, sizeof(struct discord_async_attr));

  return CCORD_OK;
}

/* add a request to libcurl's multi handle */
static CCORDcode
_discord_adapter_send(struct discord_adapter *adapter,
                      struct discord_context *cxt)
{
  struct ua_conn_attr conn_attr = { 0 };
  CURLMcode mcode;
  CURL *ehandle;

  cxt->conn = ua_conn_start(adapter->ua);

  conn_attr.method = cxt->method;
  conn_attr.body = &cxt->body.buf;
  conn_attr.endpoint = cxt->endpoint;

  if (HTTP_MIMEPOST == cxt->method) {
    ua_conn_add_header(cxt->conn, "Content-Type", "multipart/form-data");
    ua_conn_set_mime(cxt->conn, cxt, &_discord_context_to_mime);
  }
  else {
    ua_conn_add_header(cxt->conn, "Content-Type", "application/json");
  }
  ua_conn_setup(cxt->conn, &conn_attr);

  ehandle = ua_conn_get_easy_handle(cxt->conn);

  /* link 'cxt' to 'ehandle' for easy retrieval */
  curl_easy_setopt(ehandle, CURLOPT_PRIVATE, cxt);

  /* initiate libcurl transfer */
  mcode = curl_multi_add_handle(adapter->mhandle, ehandle);

  QUEUE_INSERT_TAIL(&cxt->bucket->busyq, &cxt->entry);

  return mcode ? CCORD_CURLM_INTERNAL : CCORD_OK;
}

/* check and enqueue requests that have been timed out */
static CCORDcode
_discord_adapter_check_timeouts(struct discord_adapter *adapter)
{
  struct discord_context *cxt;
  struct heap_node *hmin;

  while (1) {
    hmin = heap_min(&adapter->async.timeouts);
    if (!hmin) break;

    cxt = CONTAINEROF(hmin, struct discord_context, node);
    if (cxt->timeout_ms > NOW(adapter)) {
      /* current timestamp is lesser than lowest timeout */
      break;
    }

    heap_remove(&adapter->async.timeouts, hmin, &timer_less_than);

    cxt->bucket->freeze = false;
    QUEUE_INSERT_HEAD(&cxt->bucket->waitq, &cxt->entry);
  }

  return CCORD_OK;
}

/* send a standalone request to update stale bucket values */
static CCORDcode
_discord_adapter_send_single(struct discord_adapter *adapter,
                             struct discord_bucket *b)
{
  struct discord_context *cxt;
  QUEUE *q;

  q = QUEUE_HEAD(&b->waitq);
  QUEUE_REMOVE(q);
  QUEUE_INIT(q);

  cxt = QUEUE_DATA(q, struct discord_context, entry);

  return _discord_adapter_send(adapter, cxt);
}

/* send a batch of requests */
static CCORDcode
_discord_adapter_send_batch(struct discord_adapter *adapter,
                            struct discord_bucket *b)
{
  struct discord_context *cxt;
  CCORDcode code = CCORD_OK;
  QUEUE *q;
  long i;

  for (i = b->remaining; i > 0; --i) {
    if (QUEUE_EMPTY(&b->waitq)) break;

    q = QUEUE_HEAD(&b->waitq);
    QUEUE_REMOVE(q);
    QUEUE_INIT(q);

    cxt = QUEUE_DATA(q, struct discord_context, entry);

    /* timeout request if ratelimiting is necessary */
    if (_discord_context_timeout(adapter, cxt)) break;

    code = _discord_adapter_send(adapter, cxt);
    if (code != CCORD_OK) break;
  }

  return code;
}

static CCORDcode
_discord_adapter_check_pending(struct discord_adapter *adapter)
{
  struct discord_bucket *b;

  /* iterate over buckets in search of pending requests */
  for (b = adapter->buckets; b != NULL; b = b->hh.next) {
    /* skip timed-out, busy and non-pending buckets */
    if (b->freeze || !QUEUE_EMPTY(&b->busyq) || QUEUE_EMPTY(&b->waitq)) {
      continue;
    }

    /* if bucket is outdated then its necessary to send a single
     *      request to fetch updated values */
    if (b->reset_tstamp < NOW(adapter)) {
      _discord_adapter_send_single(adapter, b);
      continue;
    }

    /* send remainder or trigger timeout */
    _discord_adapter_send_batch(adapter, b);
  }

  return CCORD_OK;
}

static CCORDcode
_discord_adapter_check_action(struct discord_adapter *adapter,
                              struct CURLMsg *msg)
{
  struct discord *client = CLIENT(adapter, adapter);
  struct discord_context *cxt;
  int64_t wait_ms = 0LL;
  CCORDcode code;
  bool retry;

  curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE, &cxt);

  switch (msg->data.result) {
  case CURLE_OK: {
    struct ua_info info = { 0 };
    struct sized_buffer body;

    ua_info_extract(cxt->conn, &info);
    retry = _discord_adapter_get_info(adapter, &info, &wait_ms);

    body = ua_info_get_body(&info);
    if (info.code != CCORD_OK) {
      _discord_adapter_set_errbuf(adapter, &body);

      if (cxt->fail) {
        struct discord_async_err err = { info.code, cxt->udata.data };

        cxt->fail(client, &err);
      }
    }
    else if (cxt->done) {
      void **p_ret = cxt->attr.ret;
      struct discord_async_ret ret = { p_ret ? *p_ret : NULL,
                                       cxt->udata.data };

      /* initialize ret */
      if (cxt->attr.init) cxt->attr.init(*p_ret);

      /* populate ret */
      if (cxt->attr.from_json)
        cxt->attr.from_json(body.start, body.size, *p_ret);

      cxt->done(client, &ret);

      /* cleanup ret */
      if (cxt->attr.cleanup) cxt->attr.cleanup(*p_ret);
    }

    code = info.code;

    discord_bucket_build(adapter, cxt->bucket, cxt->route, &info);
    ua_info_cleanup(&info);
  } break;
  case CURLE_READ_ERROR:
    logconf_warn(&adapter->conf, "Read error, will retry again");
    retry = true;

    code = CCORD_CURLE_INTERNAL;

    break;
  default:
    logconf_error(&adapter->conf, "(CURLE code: %d)", msg->data.result);
    retry = false;

    code = CCORD_CURLE_INTERNAL;

    if (cxt->fail) {
      struct discord_async_err err = { code, cxt->udata.data };

      cxt->fail(client, &err);
    }

    break;
  }

  /* enqueue request for retry or recycle */
  QUEUE_REMOVE(&cxt->entry);
  if (retry && cxt->retry_attempt++ < adapter->retry_limit) {
    ua_conn_reset(cxt->conn);

    if (wait_ms) {
      u64_unix_ms_t timeout = NOW(adapter) + wait_ms;

      _discord_context_set_timeout(adapter, timeout, cxt);
    }
    else {
      QUEUE_INSERT_HEAD(&cxt->bucket->waitq, &cxt->entry);
    }
  }
  else {
    if (cxt->udata.cleanup) cxt->udata.cleanup(cxt->udata.data);

    ua_conn_stop(cxt->conn);
    _discord_context_reset(cxt);

    QUEUE_INSERT_TAIL(adapter->async.idleq, &cxt->entry);
  }

  return code;
}

CCORDcode
discord_adapter_perform(struct discord_adapter *adapter)
{
  int is_running = 0;
  CURLMcode mcode;
  CCORDcode code;

  code = _discord_adapter_check_timeouts(adapter);
  if (code != CCORD_OK) return code;

  code = _discord_adapter_check_pending(adapter);
  if (code != CCORD_OK) return code;

  mcode = curl_multi_socket_all(adapter->mhandle, &is_running);

  if (mcode != CURLM_OK) return CCORD_CURLM_INTERNAL;

  /* ask for any messages/informationals from the individual transfers */
  do {
    int msgq = 0;
    struct CURLMsg *msg = curl_multi_info_read(adapter->mhandle, &msgq);

    if (!msg) break;
    if (CURLMSG_DONE != msg->msg) continue;

    curl_multi_remove_handle(adapter->mhandle, msg->easy_handle);

    /* check for request action */
    _discord_adapter_check_action(adapter, msg);
  } while (1);

  return CCORD_OK;
}

void
discord_adapter_stop_all(struct discord_adapter *adapter)
{
  struct discord_context *cxt;
  struct discord_bucket *b;
  struct heap_node *hmin;
  QUEUE *q;

  /* cancel pending timeouts */
  while ((hmin = heap_min(&adapter->async.timeouts)) != NULL) {
    cxt = CONTAINEROF(hmin, struct discord_context, node);

    heap_remove(&adapter->async.timeouts, hmin, &timer_less_than);

    cxt->bucket->freeze = false;

    QUEUE_INSERT_TAIL(adapter->async.idleq, &cxt->entry);
  }

  /* cancel bucket's on-going transfers */
  for (b = adapter->buckets; b != NULL; b = b->hh.next) {
    CURL *ehandle;

    while (!QUEUE_EMPTY(&b->busyq)) {
      q = QUEUE_HEAD(&b->busyq);
      QUEUE_REMOVE(q);

      cxt = QUEUE_DATA(q, struct discord_context, entry);
      ehandle = ua_conn_get_easy_handle(cxt->conn);

      curl_multi_remove_handle(adapter->mhandle, ehandle);

      /* set for recycling */
      ua_conn_stop(cxt->conn);
      QUEUE_INSERT_TAIL(adapter->async.idleq, q);
    }

    /* cancel pending tranfers */
    QUEUE_ADD(adapter->async.idleq, &b->waitq);
    QUEUE_INIT(&b->waitq);
  }
}
