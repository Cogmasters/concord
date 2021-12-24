#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "discord.h"
#include "discord-internal.h"

/* MT-Unsafe alternative to discord_timestamp() */
#define NOW(p_adapter) (CLIENT(p_adapter, adapter)->gw.timer->now)

static void
setopt_cb(struct ua_conn *conn, void *p_token)
{
  struct sized_buffer *token = p_token;
  char auth[128];
  int ret;

  ret =
    snprintf(auth, sizeof(auth), "Bot %.*s", (int)token->size, token->start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");

  ua_conn_add_header(conn, "Authorization", auth);

#if 0 /* enable for debugging */
  curl_easy_setopt(ua_conn_get_easy_handle(conn), CURLOPT_VERBOSE, 1L);
#endif
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

  if (adapter->async.obj.size) free(adapter->async.obj.start);

  free(adapter->async.idleq);
}

static ORCAcode _discord_adapter_run_sync(struct discord_adapter *adapter,
                                          struct discord_request_attr *attr,
                                          struct sized_buffer *body,
                                          enum http_method method,
                                          char endpoint[]);

static ORCAcode _discord_adapter_run_async(struct discord_adapter *adapter,
                                           struct discord_request_attr *attr,
                                           struct sized_buffer *body,
                                           enum http_method method,
                                           char endpoint[]);

/* template function for performing requests */
ORCAcode
discord_adapter_run(struct discord_adapter *adapter,
                    struct discord_request_attr *attr,
                    struct sized_buffer *body,
                    enum http_method method,
                    char endpoint_fmt[],
                    ...)
{
  static struct discord_request_attr blank_attr = { 0 };
  char endpoint[2048];
  va_list args;
  int ret;

  /* have it point somewhere */
  if (!attr) attr = &blank_attr;

  /* build the endpoint string */
  va_start(args, endpoint_fmt);

  ret = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
  ASSERT_S(ret < sizeof(endpoint), "Out of bounds write attempt");

  va_end(args);

  /* enqueue asynchronous request */
  if (true == adapter->async_enable) {
    adapter->async_enable = false;
    return _discord_adapter_run_async(adapter, attr, body, method, endpoint);
  }

  /* perform blocking request */
  return _discord_adapter_run_sync(adapter, attr, body, method, endpoint);
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

static void _discord_context_set_timeout(struct discord_adapter *adapter,
                                         u64_unix_ms_t timeout,
                                         struct discord_context *cxt);

/* return true if there should be a retry attempt */
static bool
_discord_adapter_get_info(struct discord_adapter *adapter,
                          struct discord_context *cxt,
                          struct ua_info *info)
{
  if (info->code != ORCA_HTTP_CODE) {
    /** ORCA_OK or internal error */
    return false;
  }

  switch (info->httpcode) {
  case HTTP_FORBIDDEN:
  case HTTP_NOT_FOUND:
  case HTTP_BAD_REQUEST:
    info->code = ORCA_DISCORD_JSON_CODE;
    return false;
  case HTTP_UNAUTHORIZED:
    logconf_fatal(&adapter->conf,
                  "UNAUTHORIZED: Please provide a valid authentication token");
    info->code = ORCA_DISCORD_BAD_AUTH;
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
    int64_t wait_ms = 0LL;

    json_extract(body.start, body.size,
                 "(global):b (message):.*s (retry_after):lf", &is_global,
                 sizeof(message), message, &retry_after);

    if (is_global) {
      struct discord *client = CLIENT(adapter, adapter);
      u64_unix_ms_t global;

      global = discord_adapter_get_global_wait(adapter);
      wait_ms = (int64_t)(global - discord_timestamp(client));

      logconf_warn(&adapter->conf,
                   "429 GLOBAL RATELIMITING (wait: %" PRId64 " ms) : %s",
                   wait_ms, message);

      /* TODO: this blocks the event loop, which means Gateway's heartbeating
       * won't work */
      cee_sleep_ms(wait_ms);

      return true;
    }

    wait_ms = (int64_t)(1000 * retry_after);

    if (cxt) {
      /* non-blocking timeout */
      u64_unix_ms_t timeout = NOW(adapter) + wait_ms;

      logconf_warn(&adapter->conf,
                   "429 RATELIMITING (timeout: %" PRId64 " ms) : %s", wait_ms,
                   message);

      _discord_context_set_timeout(adapter, timeout, cxt);

      /* timed-out requests will be retried anyway */
      return false;
    }

    logconf_warn(&adapter->conf,
                 "429 RATELIMITING (wait: %" PRId64 " ms) : %s", wait_ms,
                 message);

    cee_sleep_ms(wait_ms);

    return true;
  }
  default:
    if (info->httpcode >= 500) {
      /* TODO: server error, implement retry up to X amount logic */
    }
    return true;
  }
}

/* SYNCHRONOUS REQUEST LOGIC */

/* perform a blocking request */
static ORCAcode
_discord_adapter_run_sync(struct discord_adapter *adapter,
                          struct discord_request_attr *attr,
                          struct sized_buffer *body,
                          enum http_method method,
                          char endpoint[])
{
  struct ua_conn_attr conn_attr = { method, body, endpoint };
  /* throw-away for ua_conn_set_mime() */
  struct discord_context cxt = { 0 };
  char route[DISCORD_ROUTE_LEN];
  struct discord_bucket *b;
  struct ua_conn *conn;
  ORCAcode code;
  bool retry;

  discord_bucket_get_route(method, endpoint, route);

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

      cee_sleep_ms(wait_ms);
    }

    /* perform blocking request, and check results */
    switch (code = ua_conn_easy_perform(conn)) {
    case ORCA_OK: {
      struct discord *client = CLIENT(adapter, adapter);
      struct ua_info info = { 0 };
      struct sized_buffer body;

      ua_info_extract(conn, &info);
      retry = _discord_adapter_get_info(adapter, NULL, &info);

      body = ua_info_get_body(&info);
      if (ORCA_OK == info.code && attr->obj) {
        if (attr->init) attr->init(attr->obj);

        attr->from_json(body.start, body.size, attr->obj);
      }

      /* in the off-chance of having consecutive blocking calls, update
       *        timestamp used for ratelimiting
       * TODO: redundant for REST-only clients
       * TODO: create discord_timestamp_update() */
      ws_timestamp_update(client->gw.ws);

      discord_bucket_build(adapter, b, route, &info);
      ua_info_cleanup(&info);
    } break;
    case ORCA_CURLE_INTERNAL:
      logconf_error(&adapter->conf, "Curl internal error, will retry again");
      retry = true;
      break;
    default:
      logconf_error(&adapter->conf, "ORCA code: %d", code);
      retry = false;
      break;
    }

    ua_conn_reset(conn);
  } while (retry);
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
_discord_context_stop(struct discord_context *cxt)
{
  ua_conn_stop(cxt->conn);

  cxt->bucket = NULL;
  cxt->done = NULL;
  *cxt->endpoint = '\0';
  *cxt->route = '\0';
  cxt->conn = NULL;

  if (cxt->attr.attachments) {
    discord_attachment_list_free(cxt->attr.attachments);
  }
  memset(&cxt->attr, 0, sizeof(struct discord_request_attr));
}

static void
_discord_context_populate(struct discord_context *cxt,
                          struct discord_adapter *adapter,
                          struct discord_request_attr *attr,
                          struct sized_buffer *body,
                          enum http_method method,
                          char endpoint[])
{
  cxt->method = method;
  cxt->done = adapter->async.attr.done;

  memcpy(&cxt->attr, attr, sizeof(struct discord_request_attr));
  if (attr->attachments) {
    cxt->attr.attachments = _discord_attachment_list_dup(attr->attachments);
  }
  if (cxt->attr.size > adapter->async.obj.size) {
    void *tmp = realloc(adapter->async.obj.start, cxt->attr.size);
    VASSERT_S(tmp != NULL, "Couldn't increase buffer %zu -> %zu (bytes)",
              adapter->async.obj.size, cxt->attr.size);

    adapter->async.obj.start = tmp;
    adapter->async.obj.size = cxt->attr.size;
  }
  cxt->attr.obj = adapter->async.obj.start;

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

  /* generate bucket route */
  discord_bucket_get_route(method, endpoint, cxt->route);

  /* bucket pertaining to the request */
  cxt->bucket = discord_bucket_get(adapter, cxt->route);
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
static ORCAcode
_discord_adapter_run_async(struct discord_adapter *adapter,
                           struct discord_request_attr *attr,
                           struct sized_buffer *body,
                           enum http_method method,
                           char endpoint[])
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

  _discord_context_populate(cxt, adapter, attr, body, method, endpoint);

  if (adapter->async.attr.high_p)
    QUEUE_INSERT_HEAD(&cxt->bucket->waitq, &cxt->entry);
  else
    QUEUE_INSERT_TAIL(&cxt->bucket->waitq, &cxt->entry);

  /* reset for next call */
  memset(&adapter->async.attr, 0, sizeof(struct discord_async_attr));

  return ORCA_OK;
}

/* add a request to libcurl's multi handle */
static ORCAcode
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

  return mcode ? ORCA_CURLM_INTERNAL : ORCA_OK;
}

/* check and enqueue requests that have been timed out */
static ORCAcode
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

  return ORCA_OK;
}

/* send a standalone request to update stale bucket values */
static ORCAcode
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
static ORCAcode
_discord_adapter_send_batch(struct discord_adapter *adapter,
                            struct discord_bucket *b)
{
  struct discord_context *cxt;
  ORCAcode code = ORCA_OK;
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
    if (code != ORCA_OK) break;
  }

  return code;
}

static ORCAcode
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

  return ORCA_OK;
}

static ORCAcode
_discord_adapter_check_action(struct discord_adapter *adapter,
                              struct CURLMsg *msg)
{
  struct discord_context *cxt;
  ORCAcode code;
  bool retry;

  curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE, &cxt);
  switch (msg->data.result) {
  case CURLE_OK: {
    struct ua_info info = { 0 };
    struct sized_buffer body;

    ua_info_extract(cxt->conn, &info);
    retry = _discord_adapter_get_info(adapter, cxt, &info);

    body = ua_info_get_body(&info);
    if (info.code != ORCA_OK) {
      /* TODO: failure callback */
    }
    else if (cxt->done) {
      struct discord *client = CLIENT(adapter, adapter);

      if (cxt->attr.init) cxt->attr.init(cxt->attr.obj);

      /* fill obj fields with JSON values */
      if (cxt->attr.from_json) {
        cxt->attr.from_json(body.start, body.size, cxt->attr.obj);
      }

      cxt->done(client, cxt->attr.obj);

      /* cleanup obj fields */
      if (cxt->attr.cleanup) cxt->attr.cleanup(cxt->attr.obj);
    }

    code = info.code;

    discord_bucket_build(adapter, cxt->bucket, cxt->route, &info);
    ua_info_cleanup(&info);
  } break;
  case CURLE_READ_ERROR:
    logconf_warn(&adapter->conf, "Read error, will retry again");
    retry = true;

    code = ORCA_CURLE_INTERNAL;

    break;
  default:
    logconf_error(&adapter->conf, "(CURLE code: %d)", msg->data.result);
    retry = false;

    code = ORCA_CURLE_INTERNAL;

    break;
  }

  /* remove from busy queue */
  QUEUE_REMOVE(&cxt->entry);

  /* enqueue request for retry or recycle */
  if (retry) {
    ua_conn_reset(cxt->conn);
    QUEUE_INSERT_HEAD(&cxt->bucket->waitq, &cxt->entry);
  }
  else {
    _discord_context_stop(cxt);
    QUEUE_INSERT_TAIL(adapter->async.idleq, &cxt->entry);
  }

  return code;
}

ORCAcode
discord_adapter_perform(struct discord_adapter *adapter)
{
  int is_running = 0;
  CURLMcode mcode;
  ORCAcode code;
  int numfds = 0;

  code = _discord_adapter_check_timeouts(adapter);
  if (code != ORCA_OK) return code;

  code = _discord_adapter_check_pending(adapter);
  if (code != ORCA_OK) return code;

  if (CURLM_OK == (mcode = curl_multi_perform(adapter->mhandle, &is_running)))
  {
    mcode = curl_multi_wait(adapter->mhandle, NULL, 0, 2, &numfds);
  }

  if (mcode != CURLM_OK) return ORCA_CURLM_INTERNAL;

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

  return ORCA_OK;
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
