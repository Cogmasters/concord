#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

static struct discord_context *
_discord_context_init(void)
{
    return calloc(1, sizeof(struct discord_context));
}

static void
_discord_context_cleanup(struct discord_context *cxt)
{
    discord_attachments_cleanup(&cxt->attachments);
    if (cxt->body.start) free(cxt->body.start);
    free(cxt);
}

static struct discord_context *
_discord_context_get(struct discord_async *async)
{
    struct discord_context *cxt;

    if (QUEUE_EMPTY(async->idle_contexts)) { /* create new context struct */
        cxt = _discord_context_init();
    }
    else { /* recycle a context struct from idle_contexts */
        QUEUE(struct discord_context) *qelem =
            QUEUE_HEAD(async->idle_contexts);

        QUEUE_REMOVE(qelem);
        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
    }
    QUEUE_INIT(&cxt->entry);

    return cxt;
}

static int
_on_io_poller_curl(struct io_poller *io, CURLM *mhandle, void *user_data)
{
    (void)io;
    (void)mhandle;
    return discord_rest_async_perform(user_data);
}

void
discord_async_init(struct discord_async *async, struct logconf *conf)
{
    struct discord_rest *rest = CONTAINEROF(async, struct discord_rest, async);

    logconf_branch(&async->conf, conf, "DISCORD_ASYNC");

    /* idle_contexts is malloc'd to guarantee a client cloned by
     * discord_clone() will share the same queue with the original */
    async->idle_contexts = malloc(sizeof *async->idle_contexts);
    QUEUE_INIT(async->idle_contexts);

    async->mhandle = curl_multi_init();
    io_poller_curlm_add(rest->io_poller, async->mhandle, &_on_io_poller_curl,
                        rest);
}

void
discord_async_cleanup(struct discord_async *async)
{
    QUEUE(struct discord_context) queue, *qelem;
    struct discord_context *cxt;

    QUEUE_MOVE(async->idle_contexts, &queue);
    while (!QUEUE_EMPTY(&queue)) {
        qelem = QUEUE_HEAD(&queue);
        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
        QUEUE_REMOVE(&cxt->entry);
        _discord_context_cleanup(cxt);
    }
    free(async->idle_contexts);

    /* cleanup curl's multi handle */
    io_poller_curlm_del(CLIENT(async, rest.async)->rest.io_poller,
                        async->mhandle);
    curl_multi_cleanup(async->mhandle);
}

CCORDcode
discord_async_add_request(struct discord_async *async,
                          struct discord_context *cxt,
                          struct ua_conn *conn)
{
    CURL *ehandle = ua_conn_get_easy_handle(conn);
    CURLMcode mcode;

    cxt->conn = conn;
    cxt->b->performing_cxt = cxt;

    /* link 'cxt' to 'ehandle' for easy retrieval */
    curl_easy_setopt(ehandle, CURLOPT_PRIVATE, cxt);

    /* initiate libcurl transfer */
    mcode = curl_multi_add_handle(async->mhandle, ehandle);

    return mcode ? CCORD_CURLM_INTERNAL : CCORD_OK;
}

bool
discord_async_retry_context(struct discord_async *async,
                            struct discord_context *cxt,
                            int64_t wait_ms)
{
    struct discord_rest *rest = CONTAINEROF(async, struct discord_rest, async);

    if (rest->retry_limit < cxt->retry_attempt++) return false;

    CURL *ehandle = ua_conn_get_easy_handle(cxt->conn);

    curl_multi_remove_handle(async->mhandle, ehandle);
    ua_conn_reset(cxt->conn);

    /* FIXME: wait_ms > 0 should be dealt with aswell */
    if (wait_ms <= 0) discord_bucket_add_context(cxt->b, cxt, true);

    return true;
}

void
discord_async_recycle_context(struct discord_async *async,
                              struct discord_context *cxt)
{
    if (!cxt) return;

    struct discord_refcounter *rc = &CLIENT(async, rest.async)->refcounter;
    CURL *ehandle = ua_conn_get_easy_handle(cxt->conn);

    curl_multi_remove_handle(async->mhandle, ehandle);
    if (cxt->conn) ua_conn_stop(cxt->conn);

    if (cxt->dispatch.keep) {
        discord_refcounter_decr(rc, (void *)cxt->dispatch.keep);
    }
    if (cxt->dispatch.data) {
        discord_refcounter_decr(rc, cxt->dispatch.data);
    }

    cxt->body.size = 0;
    cxt->method = 0;
    *cxt->endpoint = '\0';
    *cxt->key = '\0';
    cxt->conn = NULL;
    cxt->retry_attempt = 0;
    discord_attachments_cleanup(&cxt->attachments);
    memset(cxt, 0, sizeof(struct discord_request));

    QUEUE_INSERT_TAIL(async->idle_contexts, &cxt->entry);
}

/* Only the fields that are required at _discord_rest_request_to_multipart()
 *        are duplicated */
static void
_discord_attachments_dup(struct discord_attachments *dest,
                         struct discord_attachments *src)
{
    int i;

    if (!src->size) return;

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

struct discord_context *
discord_async_start_context(struct discord_async *async,
                            struct discord_request *req,
                            struct ccord_szbuf *body,
                            enum http_method method,
                            char endpoint[DISCORD_ENDPT_LEN],
                            char key[DISCORD_ROUTE_LEN])
{
    struct discord_rest *rest = CONTAINEROF(async, struct discord_rest, async);
    struct discord *client = CLIENT(rest, rest);
    struct discord_context *cxt = _discord_context_get(async);

    cxt->method = method;

    memcpy(cxt, req, sizeof *req);
    _discord_attachments_dup(&cxt->attachments, &req->attachments);

    if (body) {
        /* copy request body */
        if (body->size > cxt->body.realsize) {
            /* needs to increase buffer size */
            void *tmp = realloc(cxt->body.start, body->size);
            ASSERT_S(tmp != NULL, "Out of memory");

            cxt->body.start = tmp;
            cxt->body.realsize = body->size;
        }
        memcpy(cxt->body.start, body->start, body->size);
        cxt->body.size = body->size;
    }

    /* copy endpoint over to cxt */
    memcpy(cxt->endpoint, endpoint, sizeof(cxt->endpoint));
    /* copy bucket's key */
    memcpy(cxt->key, key, sizeof(cxt->key));
    /* bucket pertaining to the request */
    cxt->b = discord_bucket_get(&rest->ratelimiter, key);

    if (req->dispatch.keep) {
        CCORDcode code = discord_refcounter_incr(&client->refcounter,
                                                 (void *)req->dispatch.keep);

        ASSERT_S(code == CCORD_OK,
                 "'.keep' data must be a Concord callback parameter");
    }
    if (req->dispatch.data
        && CCORD_UNAVAILABLE
               == discord_refcounter_incr(&client->refcounter,
                                          req->dispatch.data))
    {
        discord_refcounter_add_client(&client->refcounter, req->dispatch.data,
                                      req->dispatch.cleanup, false);
    }

    io_poller_wakeup(rest->io_poller);
    return cxt;
}
