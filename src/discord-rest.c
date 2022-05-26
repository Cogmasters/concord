#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "carray.h"
#include "threadpool.h"

#include "discord.h"
#include "discord-internal.h"

static void
_discord_rest_try_add_request(struct discord_ratelimiter *rl,
                              struct discord_bucket *b)
{
    /* skip if bucket is already busy performing */
    if (b->performing_cxt) return;

    if (!b->remaining) {
        discord_bucket_try_timeout(rl, b);
    }
    else if (!QUEUE_EMPTY(&b->pending_queue)) {
        struct discord_async *async =
            &CONTAINEROF(rl, struct discord_rest, ratelimiter)->async;

        discord_async_start_bucket_request(async, b);
    }
}

static CCORDcode
_discord_rest_start_pending(struct discord_rest *rest)
{
    QUEUE(struct discord_context) queue, *qelem;
    struct discord_context *cxt;
    struct discord_bucket *b;

    /* match pending contexts to their buckets */
    QUEUE_MOVE(&rest->async.queues->pending, &queue);
    while (!QUEUE_EMPTY(&queue)) {
        qelem = QUEUE_HEAD(&queue);
        QUEUE_REMOVE(qelem);

        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
        b = discord_bucket_get(&rest->ratelimiter, cxt->key);
        discord_bucket_add_context(b, cxt, cxt->dispatch.high_p);
    }

    /* TODO: replace foreach with a mechanism that loops only busy buckets */
    discord_ratelimiter_foreach_bucket(&rest->ratelimiter,
                                       &_discord_rest_try_add_request);

    /* FIXME: redundant return value (constant) */
    return CCORD_OK;
}

/* return true if there should be a retry attempt */
static void
_discord_rest_info_extract(struct discord_rest *rest,
                           struct discord_context *cxt,
                           struct ua_info *info)
{
    ua_info_extract(cxt->conn, info);

    if (info->code != CCORD_HTTP_CODE) { /* CCORD_OK or internal error */
        cxt->retry = false;
    }
    else {
        switch (info->httpcode) {
        case HTTP_FORBIDDEN:
        case HTTP_NOT_FOUND:
        case HTTP_BAD_REQUEST:
            info->code = CCORD_DISCORD_JSON_CODE;
            cxt->retry = false;
            break;
        case HTTP_UNAUTHORIZED:
            logconf_fatal(
                &rest->conf,
                "UNAUTHORIZED: Please provide a valid authentication token");
            info->code = CCORD_DISCORD_BAD_AUTH;
            cxt->retry = false;
            break;
        case HTTP_METHOD_NOT_ALLOWED:
            logconf_fatal(
                &rest->conf,
                "METHOD_NOT_ALLOWED: The server couldn't recognize the "
                "received HTTP method");
            cxt->retry = false;
            break;
        case HTTP_TOO_MANY_REQUESTS: {
            struct ua_szbuf_readonly body = ua_info_get_body(info);
            struct jsmnftok message = { 0 };
            double retry_after = 1.0;
            bool is_global = false;
            jsmn_parser parser;
            jsmntok_t tokens[16];

            jsmn_init(&parser);
            if (0 < jsmn_parse(&parser, body.start, body.size, tokens,
                               sizeof(tokens) / sizeof *tokens))
            {
                jsmnf_loader loader;
                jsmnf_pair pairs[16];

                jsmnf_init(&loader);
                if (0 < jsmnf_load(&loader, body.start, tokens, parser.toknext,
                                   pairs, sizeof(pairs) / sizeof *pairs))
                {
                    jsmnf_pair *f;

                    if ((f = jsmnf_find(pairs, body.start, "global", 6)))
                        is_global = ('t' == body.start[f->v.pos]);
                    if ((f = jsmnf_find(pairs, body.start, "message", 7)))
                        message = f->v;
                    if ((f = jsmnf_find(pairs, body.start, "retry_after", 11)))
                        retry_after = strtod(body.start + f->v.pos, NULL);
                }
            }

            cxt->wait_ms = (int64_t)(1000 * retry_after);
            if (cxt->wait_ms < 0) cxt->wait_ms = 0;

            logconf_warn(&rest->conf,
                         "429 %sRATELIMITING (wait: %" PRId64 " ms) : %.*s",
                         is_global ? "GLOBAL " : "", cxt->wait_ms, message.len,
                         body.start + message.pos);

            cxt->retry = true;
            break;
        }
        default:
            cxt->retry = (info->httpcode >= 500); /* retry if Server Error */
            break;
        }
    }
}

/* parse request response and prepare callback that should be triggered
 * at _discord_rest_trigger_response() */
static CCORDcode
_discord_rest_select_response(struct discord_rest *rest,
                              struct discord_context *cxt,
                              CURLcode ecode)
{
    switch (ecode) {
    case CURLE_OK: {
        struct ua_szbuf_readonly body;
        struct ua_info info;

        _discord_rest_info_extract(rest, cxt, &info);
        body = ua_info_get_body(&info);

        if (info.code != CCORD_OK) {
            logconf_error(&rest->conf, "%.*s", (int)body.size, body.start);
        }
        else if (cxt->dispatch.has_type
                 && cxt->dispatch.sync != DISCORD_SYNC_FLAG) {
            if (cxt->dispatch.sync) {
                cxt->response.data = cxt->dispatch.sync;
            }
            else {
                cxt->response.data = calloc(1, cxt->response.size);
                discord_refcounter_add_internal(
                    &CLIENT(rest, rest)->refcounter, cxt->response.data,
                    cxt->response.cleanup, true);
            }

            /* initialize ret */
            if (cxt->response.init) cxt->response.init(cxt->response.data);
            /* populate ret */
            if (cxt->response.from_json)
                cxt->response.from_json(body.start, body.size,
                                        cxt->response.data);
        }

        discord_ratelimiter_build(&rest->ratelimiter, cxt->b, cxt->key, &info);
        ua_info_cleanup(&info);
    } break;
    case CURLE_READ_ERROR:
        logconf_warn(&rest->conf, "%s (CURLE code: %d)",
                     curl_easy_strerror(ecode), ecode);

        cxt->retry = true;
        cxt->code = CCORD_CURLE_INTERNAL;

        break;
    default:
        logconf_error(&rest->conf, "%s (CURLE code: %d)",
                      curl_easy_strerror(ecode), ecode);

        cxt->retry = false;
        cxt->code = CCORD_CURLE_INTERNAL;

        break;
    }

    return cxt->code;
}

static CCORDcode
_discord_rest_trigger_response(struct discord_rest *rest,
                               struct discord_context *cxt)
{
    struct discord *client = CLIENT(rest, rest);
    struct discord_response resp = { .data = cxt->dispatch.data,
                                     .keep = cxt->dispatch.keep,
                                     .code = cxt->code };

    if (cxt->code != CCORD_OK) {
        cxt->dispatch.fail(client, &resp);
    }
    else if (cxt->dispatch.done.typed) {
        if (!cxt->dispatch.has_type) {
            cxt->dispatch.done.typeless(client, &resp);
        }
        else {
            cxt->dispatch.done.typed(client, &resp, cxt->response.data);
            discord_refcounter_decr(&client->refcounter, cxt->response.data);
        }
    }

    /* enqueue request for retry or recycle */
    if (!discord_async_retry_context(&rest->async, cxt))
        discord_async_cancel_context(&rest->async, cxt);

    return resp.code;
}

void
discord_rest_perform_callbacks(struct discord_rest *rest)
{
    if (0 == pthread_mutex_trylock(&rest->manager->lock)) {
        if (!QUEUE_EMPTY(&rest->async.queues->finished)) {
            QUEUE(struct discord_context) queue, *qelem;
            struct discord_context *cxt;

            QUEUE_MOVE(&rest->async.queues->finished, &queue);
            do {
                qelem = QUEUE_HEAD(&queue);
                cxt = QUEUE_DATA(qelem, struct discord_context, entry);
                _discord_rest_trigger_response(rest, cxt);
            } while (!QUEUE_EMPTY(&queue));

            io_poller_wakeup(rest->async.io_poller);
        }
        pthread_mutex_unlock(&rest->manager->lock);
    }
}

CCORDcode
discord_rest_perform(struct discord_rest *rest)
{
    CCORDcode code;
    int alive = 0;

    if (CURLM_OK != curl_multi_socket_all(rest->async.mhandle, &alive))
        return CCORD_CURLM_INTERNAL;

    /* ask for any messages/informationals from the individual transfers */
    pthread_mutex_lock(&rest->manager->lock);
    while (1) {
        int msgq = 0;
        struct CURLMsg *msg = curl_multi_info_read(rest->async.mhandle, &msgq);

        if (!msg) break;

        if (CURLMSG_DONE == msg->msg) {
            struct discord_context *cxt;

            curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE, &cxt);
            curl_multi_remove_handle(rest->async.mhandle, msg->easy_handle);

            _discord_rest_select_response(rest, cxt, msg->data.result);
            if (cxt->dispatch.sync)
                pthread_cond_signal(cxt->cond);
            else
                QUEUE_INSERT_TAIL(&rest->async.queues->finished, &cxt->entry);
        }
    }

    code = _discord_rest_start_pending(rest);
    pthread_mutex_unlock(&rest->manager->lock);

    return code;
}

static void
_discord_rest_manager(void *p_rest)
{
    struct discord *client = CLIENT(p_rest, rest);
    struct discord_rest *rest = p_rest;

    struct discord_timers *const timers[] = { &rest->timers };
    int64_t now, trigger;
    int poll_result;

    discord_rest_perform(rest);

    now = (int64_t)discord_timestamp_us(client);

    trigger = discord_timers_get_next_trigger(timers, 1, now, 60000000);
    poll_result = io_poller_poll(rest->async.io_poller, (int)(trigger / 1000));

    now = (int64_t)discord_timestamp_us(client);
    if (0 == poll_result) {
        trigger = discord_timers_get_next_trigger(timers, 1, now, 1000);
        if (trigger > 0 && trigger < 1000) cog_sleep_us((long)trigger);
    }
    discord_timers_run(client, &rest->timers);
    io_poller_perform(rest->async.io_poller);

    threadpool_add(rest->manager->tpool, _discord_rest_manager, rest, 0);
}

void
discord_rest_init(struct discord_rest *rest,
                  struct logconf *conf,
                  struct ccord_szbuf_readonly *token)
{
    if (!token->size)
        logconf_branch(&rest->conf, conf, "DISCORD_WEBHOOK");
    else
        logconf_branch(&rest->conf, conf, "DISCORD_HTTP");

    discord_timers_init(&rest->timers);
    discord_async_init(&rest->async, &rest->conf, token);
    discord_ratelimiter_init(&rest->ratelimiter, &rest->conf);

    rest->manager = malloc(sizeof *rest->manager);
    ASSERT_S(!pthread_mutex_init(&rest->manager->lock, NULL),
             "Couldn't initialize REST manager mutex");
    rest->manager->tpool = threadpool_create(1, 1024, 0);
    ASSERT_S(
        !threadpool_add(rest->manager->tpool, &_discord_rest_manager, rest, 0),
        "Couldn't initialize REST managagement thread");
}

void
discord_rest_cleanup(struct discord_rest *rest)
{
    /* cleanup REST managing thread */
    threadpool_destroy(rest->manager->tpool, threadpool_graceful);
    pthread_mutex_destroy(&rest->manager->lock);
    free(rest->manager);

    /* cleanup discovered buckets */
    discord_timers_cleanup(CLIENT(rest, rest), &rest->timers);
    discord_ratelimiter_cleanup(&rest->ratelimiter);

    /* cleanup context queues */
    discord_async_cleanup(&rest->async);
}

/* enqueue a request to be executed asynchronously */
static CCORDcode
_discord_rest_start_context(struct discord_rest *rest,
                            struct discord_attributes *attr,
                            struct ccord_szbuf *body,
                            enum http_method method,
                            char endpoint[DISCORD_ENDPT_LEN],
                            char key[DISCORD_ROUTE_LEN])
{
    struct discord_context *cxt;
    CCORDcode code;

    pthread_mutex_lock(&rest->manager->lock);

    cxt = discord_async_start_context(&rest->async, attr, body, method,
                                      endpoint, key);

    if (!cxt->dispatch.sync) {
        code = CCORD_OK;
    }
    else {
        cxt->cond = &(pthread_cond_t)PTHREAD_COND_INITIALIZER;
        pthread_cond_wait(cxt->cond, &rest->manager->lock);
        code = _discord_rest_trigger_response(rest, cxt);
    }

    pthread_mutex_unlock(&rest->manager->lock);

    return code;
}

/* template function for performing requests */
CCORDcode
discord_rest_run(struct discord_rest *rest,
                 struct discord_attributes *attr,
                 struct ccord_szbuf *body,
                 enum http_method method,
                 char endpoint_fmt[],
                 ...)
{
    char endpoint[DISCORD_ENDPT_LEN], key[DISCORD_ROUTE_LEN];
    va_list args;
    int len;

    /* have it point somewhere */
    if (!attr) {
        static struct discord_attributes blank = { 0 };
        attr = &blank;
    }
    if (!body) {
        static struct ccord_szbuf blank = { 0 };
        body = &blank;
    }

    /* build the endpoint string */
    va_start(args, endpoint_fmt);
    len = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
    ASSERT_NOT_OOB(len, sizeof(endpoint));
    va_end(args);

    /* build the bucket's key */
    va_start(args, endpoint_fmt);
    discord_ratelimiter_build_key(method, key, endpoint_fmt, args);
    va_end(args);

    return _discord_rest_start_context(rest, attr, body, method, endpoint,
                                       key);
}
