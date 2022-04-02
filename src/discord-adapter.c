#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "carray.h"

#include "discord.h"
#include "discord-internal.h"

/* No-lock alternative to discord_timestamp() */
#define NOW(p_adapter) (CLIENT(p_adapter, adapter)->gw.timer->now)

static void
setopt_cb(struct ua_conn *conn, void *p_token)
{
    struct sized_buffer *token = p_token;
    char auth[128];
    int len;

    len = snprintf(auth, sizeof(auth), "Bot %.*s", (int)token->size,
                   token->start);
    ASSERT_NOT_OOB(len, sizeof(auth));

    ua_conn_add_header(conn, "Authorization", auth);

#ifdef CCORD_DEBUG_ADAPTER
    curl_easy_setopt(ua_conn_get_easy_handle(conn), CURLOPT_VERBOSE, 1L);
#endif /* CCORD_DEBUG_ADAPTER */
}

static int
on_io_poller_curl(struct io_poller *io, CURLM *mhandle, void *user_data)
{
    (void)io;
    (void)mhandle;
    return discord_adapter_perform(user_data);
}

void
discord_adapter_init(struct discord_adapter *adapter,
                     struct logconf *conf,
                     struct sized_buffer *token)
{
    const struct sized_buffer key_null = { "null", 4 },
                              key_miss = { "miss", 4 };
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
    io_poller_curlm_add(CLIENT(adapter, adapter)->io_poller, adapter->mhandle,
                        on_io_poller_curl, adapter);

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
    adapter->idleq = malloc(sizeof(QUEUE));
    QUEUE_INIT(adapter->idleq);

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
    QUEUE *qelem;

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
    QUEUE_MOVE(adapter->idleq, &queue);
    while (!QUEUE_EMPTY(&queue)) {
        qelem = QUEUE_HEAD(&queue);
        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
        QUEUE_REMOVE(&cxt->entry);
        _discord_context_cleanup(cxt);
    }

    free(adapter->idleq);
}

static CCORDcode _discord_adapter_run_sync(struct discord_adapter *adapter,
                                           struct discord_request *req,
                                           struct sized_buffer *body,
                                           enum http_method method,
                                           char endpoint[DISCORD_ENDPT_LEN],
                                           char route[DISCORD_ROUTE_LEN]);

static CCORDcode _discord_adapter_run_async(struct discord_adapter *adapter,
                                            struct discord_request *req,
                                            struct sized_buffer *body,
                                            enum http_method method,
                                            char endpoint[DISCORD_ENDPT_LEN],
                                            char route[DISCORD_ROUTE_LEN]);

/* template function for performing requests */
CCORDcode
discord_adapter_run(struct discord_adapter *adapter,
                    struct discord_request *req,
                    struct sized_buffer *body,
                    enum http_method method,
                    char endpoint_fmt[],
                    ...)
{
    static struct discord_request blank_req = { 0 };
    char endpoint[DISCORD_ENDPT_LEN];
    char route[DISCORD_ROUTE_LEN];
    va_list args;
    int len;

    /* have it point somewhere */
    if (!req) req = &blank_req;

    /* build the endpoint string */
    va_start(args, endpoint_fmt);
    len = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
    ASSERT_NOT_OOB(len, sizeof(endpoint));
    va_end(args);

    /* build the ratelimiting route */
    va_start(args, endpoint_fmt);
    discord_bucket_get_route(method, route, endpoint_fmt, args);
    va_end(args);

    if (req->ret.sync) { /* perform blocking request */
        if (req->ret.has_type && req->ret.sync != DISCORD_SYNC_FLAG)
            req->gnrc.data = req->ret.sync;

        return _discord_adapter_run_sync(adapter, req, body, method, endpoint,
                                         route);
    }

    /* enqueue asynchronous request */
    return _discord_adapter_run_async(adapter, req, body, method, endpoint,
                                      route);
}

static void
_discord_context_to_mime(curl_mime *mime, void *p_cxt)
{
    struct discord_context *cxt = p_cxt;
    struct discord_attachments *atchs = &cxt->req.attachments;
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
    for (i = 0; i < atchs->size; ++i) {
        int len = snprintf(name, sizeof(name), "files[%d]", i);
        ASSERT_NOT_OOB(len, sizeof(name));

        if (atchs->array[i].content) {
            part = curl_mime_addpart(mime);
            curl_mime_data(part, atchs->array[i].content,
                           atchs->array[i].size ? atchs->array[i].size
                                                : CURL_ZERO_TERMINATED);
            curl_mime_filename(part, !atchs->array[i].filename
                                         ? "a.out"
                                         : atchs->array[i].filename);
            curl_mime_type(part, !atchs->array[i].content_type
                                     ? "application/octet-stream"
                                     : atchs->array[i].content_type);
            curl_mime_name(part, name);
        }
        else if (atchs->array[i].filename) {
            CURLcode code;

            /* fetch local file by the filename */
            part = curl_mime_addpart(mime);
            code = curl_mime_filedata(part, atchs->array[i].filename);
            if (code != CURLE_OK) {
                char errbuf[256];
                snprintf(errbuf, sizeof(errbuf), "%s (file: %s)",
                         curl_easy_strerror(code), atchs->array[i].filename);
                perror(errbuf);
            }
            curl_mime_type(part, !atchs->array[i].content_type
                                     ? "application/octet-stream"
                                     : atchs->array[i].content_type);
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
        logconf_fatal(
            &adapter->conf,
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
        jsmnf *root = jsmnf_init();

        if (jsmnf_start(root, body.start, body.size) >= 0) {
            jsmnf *f;

            f = jsmnf_find(root, "global", sizeof("global") - 1);
            if (f) is_global = (body.start[f->val->start] == 't');
            f = jsmnf_find(root, "message", sizeof("message") - 1);
            if (f)
                snprintf(message, sizeof(message), "%.*s",
                         f->val->end - f->val->start,
                         body.start + f->val->start);
            f = jsmnf_find(root, "retry_after", sizeof("retry_after") - 1);
            if (f) retry_after = strtod(body.start + f->val->start, NULL);
        }

        *wait_ms = (int64_t)(1000 * retry_after);

        logconf_warn(&adapter->conf,
                     "429 %s RATELIMITING (wait: %" PRId64 " ms) : %s",
                     is_global ? "GLOBAL" : "", *wait_ms, message);

        jsmnf_cleanup(root);

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
                          struct discord_request *req,
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
        cxt.req.attachments = req->attachments;
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
            logconf_info(&adapter->conf,
                         "[%.4s] RATELIMITING (wait %" PRId64 " ms)", b->hash,
                         wait_ms);
            cog_sleep_ms(wait_ms);

            wait_ms = 0LL; /* reset */
        }

        /* perform blocking request, and check results */
        switch (code = ua_conn_easy_perform(conn)) {
        case CCORD_OK: {
            struct discord *client = CLIENT(adapter, adapter);
            struct ua_info info = { 0 };
            struct sized_buffer resp;

            ua_info_extract(conn, &info);
            retry = _discord_adapter_get_info(adapter, &info, &wait_ms);

            resp = ua_info_get_body(&info);
            if (info.code != CCORD_OK) {
                logconf_error(&client->conf, "%.*s", (int)resp.size,
                              resp.start);
            }
            else if (req->gnrc.data) {
                /* initialize ret */
                if (req->gnrc.init) req->gnrc.init(req->gnrc.data);

                /* populate ret */
                if (req->gnrc.from_json)
                    req->gnrc.from_json(resp.start, resp.size, req->gnrc.data);
            }

            code = info.code;

            /* in the off-chance of having consecutive blocking calls, update
             *        timestamp used for ratelimiting
             * TODO: redundant for REST-only clients
             * TODO: create discord_timestamp_update() */
            ws_timestamp_update(client->gw.ws);

            discord_bucket_build(adapter, b, route, &info);

            if (wait_ms > 0) cog_sleep_ms(wait_ms);

            ua_info_cleanup(&info);
        } break;
        case CCORD_CURLE_INTERNAL:
            logconf_error(&adapter->conf,
                          "Curl internal error, will retry again");
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

/* TODO: make this kind of function gencodecs generated (optional)
 *
 * Only the fields that are required at _discord_context_to_mime()
 *        are duplicated*/
static void
_discord_attachments_dup(struct discord_attachments *dest,
                         struct discord_attachments *src)
{
    int i;

    __carray_init(dest, (size_t)src->size, struct discord_attachment, , );
    for (i = 0; i < src->size; ++i) {
        carray_insert(dest, i, src->array[i]);
        if (src->array[i].content) {
            dest->array[i].size = src->array[i].size
                                      ? src->array[i].size
                                      : strlen(src->array[i].content) + 1;

            dest->array[i].content = malloc(dest->array[i].size);
            memcpy(dest->array[i].content, src->array[i].content,
                   dest->array[i].size);
        }
        if (src->array[i].filename)
            dest->array[i].filename = strdup(src->array[i].filename);
        if (src->array[i].content_type)
            dest->array[i].content_type = strdup(src->array[i].content_type);
    }
}

static void
_discord_context_reset(struct discord_context *cxt)
{
    ua_conn_stop(cxt->conn);

    cxt->bucket = NULL;
    cxt->body.buf.size = 0;
    cxt->method = 0;
    *cxt->endpoint = '\0';
    *cxt->route = '\0';
    cxt->conn = NULL;
    cxt->retry_attempt = 0;

    discord_attachments_cleanup(&cxt->req.attachments);

    memset(&cxt->req, 0, sizeof(struct discord_request));
}

static void
_discord_context_populate(struct discord_context *cxt,
                          struct discord_adapter *adapter,
                          struct discord_request *req,
                          struct sized_buffer *body,
                          enum http_method method,
                          char endpoint[DISCORD_ENDPT_LEN],
                          char route[DISCORD_ROUTE_LEN])
{
    cxt->method = method;

    memcpy(&cxt->req, req, sizeof(struct discord_request));
    _discord_attachments_dup(&cxt->req.attachments, &req->attachments);

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

void
discord_refcount_incr(struct discord_adapter *adapter,
                      void *data,
                      void (*cleanup)(void *data))
{
    struct discord_refcount *ref = NULL;

    HASH_FIND_PTR(adapter->refcounts, &data, ref);
    if (NULL == ref) {
        ref = calloc(1, sizeof *ref);
        ref->data = data;
        ref->cleanup = cleanup;

        HASH_ADD_PTR(adapter->refcounts, data, ref);
    }

    ++ref->visits;
}

void
discord_refcount_decr(struct discord_adapter *adapter, void *data)
{
    struct discord_refcount *ref = NULL;

    HASH_FIND_PTR(adapter->refcounts, &data, ref);
    if (ref && --ref->visits <= 0) {
        if (ref->cleanup) ref->cleanup(ref->data);

        HASH_DEL(adapter->refcounts, ref);
        free(ref);
    }
}

/* enqueue a request to be executed asynchronously */
static CCORDcode
_discord_adapter_run_async(struct discord_adapter *adapter,
                           struct discord_request *req,
                           struct sized_buffer *body,
                           enum http_method method,
                           char endpoint[DISCORD_ENDPT_LEN],
                           char route[DISCORD_ROUTE_LEN])
{
    struct discord_context *cxt;

    if (QUEUE_EMPTY(adapter->idleq)) {
        /* create new request handler */
        cxt = calloc(1, sizeof(struct discord_context));
    }
    else {
        /* get from idle requests queue */
        QUEUE *qelem = QUEUE_HEAD(adapter->idleq);
        QUEUE_REMOVE(qelem);

        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
    }
    QUEUE_INIT(&cxt->entry);

    _discord_context_populate(cxt, adapter, req, body, method, endpoint,
                              route);

    if (req->ret.high_p)
        QUEUE_INSERT_HEAD(&cxt->bucket->waitq, &cxt->entry);
    else
        QUEUE_INSERT_TAIL(&cxt->bucket->waitq, &cxt->entry);

    if (req->ret.data)
        discord_refcount_incr(adapter, req->ret.data, req->ret.cleanup);

    io_poller_curlm_enable_perform(CLIENT(adapter, adapter)->io_poller,
                                   adapter->mhandle);

    return CCORD_OK;
}

/* add a request to libcurl's multi handle */
static CCORDcode
_discord_adapter_send(struct discord_adapter *adapter,
                      struct discord_bucket *b)
{
    struct discord_context *cxt;
    QUEUE *qelem;

    struct ua_conn_attr conn_attr = { 0 };
    CURLMcode mcode;
    CURL *ehandle;

    qelem = QUEUE_HEAD(&b->waitq);
    QUEUE_REMOVE(qelem);
    QUEUE_INIT(qelem);

    cxt = QUEUE_DATA(qelem, struct discord_context, entry);
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

    io_poller_curlm_enable_perform(CLIENT(adapter, adapter)->io_poller,
                                   adapter->mhandle);

    QUEUE_INSERT_TAIL(&cxt->bucket->busyq, &cxt->entry);

    return mcode ? CCORD_CURLM_INTERNAL : CCORD_OK;
}

/* send a batch of requests */
static CCORDcode
_discord_adapter_send_batch(struct discord_adapter *adapter,
                            struct discord_bucket *b)
{
    CCORDcode code = CCORD_OK;
    long i;

    for (i = b->remaining; i > 0; --i) {
        if (QUEUE_EMPTY(&b->waitq)) break;

        code = _discord_adapter_send(adapter, b);
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
        if (!QUEUE_EMPTY(&b->busyq) || QUEUE_EMPTY(&b->waitq)) {
            continue;
        }

        /* if bucket is outdated then its necessary to send a single
         *      request to fetch updated values */
        if (b->reset_tstamp < NOW(adapter)) {
            _discord_adapter_send(adapter, b);
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
            logconf_error(&client->conf, "%.*s", (int)body.size, body.start);

            if (cxt->req.ret.fail)
                cxt->req.ret.fail(client, info.code, cxt->req.ret.data);
        }
        else if (cxt->req.ret.done.typed) {
            void *ret = calloc(1, cxt->req.gnrc.size);

            /* initialize ret */
            if (cxt->req.gnrc.init) cxt->req.gnrc.init(ret);

            /* populate ret */
            if (cxt->req.gnrc.from_json)
                cxt->req.gnrc.from_json(body.start, body.size, ret);

            if (cxt->req.ret.has_type)
                cxt->req.ret.done.typed(client, cxt->req.ret.data, ret);
            else
                cxt->req.ret.done.typeless(client, cxt->req.ret.data);

            /* cleanup ret */
            if (cxt->req.gnrc.cleanup) cxt->req.gnrc.cleanup(ret);
            free(ret);
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

        if (cxt->req.ret.fail) {
            cxt->req.ret.fail(client, code, cxt->req.ret.data);
        }

        break;
    }

    /* enqueue request for retry or recycle */
    QUEUE_REMOVE(&cxt->entry);
    if (retry && cxt->retry_attempt++ < adapter->retry_limit) {
        ua_conn_reset(cxt->conn);

        if (wait_ms <= 0) {
            QUEUE_INSERT_HEAD(&cxt->bucket->waitq, &cxt->entry);
        }
    }
    else {
        discord_refcount_decr(adapter, cxt->req.ret.data);
        _discord_context_reset(cxt);
        QUEUE_INSERT_TAIL(adapter->idleq, &cxt->entry);
    }

    return code;
}

CCORDcode
discord_adapter_perform(struct discord_adapter *adapter)
{
    CURLMcode mcode;
    CCORDcode code;
    int alive = 0;

    if (CCORD_OK != (code = _discord_adapter_check_pending(adapter)))
        return code;

    if (CURLM_OK != (mcode = curl_multi_socket_all(adapter->mhandle, &alive)))
        return CCORD_CURLM_INTERNAL;

    /* ask for any messages/informationals from the individual transfers */
    while (1) {
        int msgq = 0;
        struct CURLMsg *msg = curl_multi_info_read(adapter->mhandle, &msgq);

        if (!msg) break;
        if (CURLMSG_DONE != msg->msg) continue;

        curl_multi_remove_handle(adapter->mhandle, msg->easy_handle);

        /* check for request action */
        _discord_adapter_check_action(adapter, msg);
    }

    return CCORD_OK;
}

void
discord_adapter_stop_all(struct discord_adapter *adapter)
{
    struct discord_context *cxt;
    struct discord_bucket *b;
    QUEUE *qelem;

    /* cancel bucket's on-going transfers */
    for (b = adapter->buckets; b != NULL; b = b->hh.next) {
        CURL *ehandle;

        while (!QUEUE_EMPTY(&b->busyq)) {
            qelem = QUEUE_HEAD(&b->busyq);
            QUEUE_REMOVE(qelem);

            cxt = QUEUE_DATA(qelem, struct discord_context, entry);
            ehandle = ua_conn_get_easy_handle(cxt->conn);

            curl_multi_remove_handle(adapter->mhandle, ehandle);

            /* set for recycling */
            ua_conn_stop(cxt->conn);
            QUEUE_INSERT_TAIL(adapter->idleq, qelem);
        }

        /* cancel pending tranfers */
        QUEUE_ADD(adapter->idleq, &b->waitq);
        QUEUE_INIT(&b->waitq);
    }
}
