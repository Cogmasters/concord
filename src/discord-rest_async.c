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

    if (QUEUE_EMPTY(&async->queues->recycling)) { /* new context struct */
        cxt = _discord_context_init();
    }
    else { /* fetch a context struct from queues->recycling */
        QUEUE(struct discord_context) *qelem =
            QUEUE_HEAD(&async->queues->recycling);

        QUEUE_REMOVE(qelem);
        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
    }
    QUEUE_INIT(&cxt->entry);

    return cxt;
}

static int
_discord_on_rest_perform(struct io_poller *io, CURLM *mhandle, void *p_rest)
{
    (void)io;
    (void)mhandle;
    return discord_rest_perform(p_rest);
}

static void
_discord_on_curl_setopt(struct ua_conn *conn, void *p_token)
{
    struct ccord_szbuf *token = p_token;
    char auth[128];
    int len;

    len = snprintf(auth, sizeof(auth), "Bot %.*s", (int)token->size,
                   token->start);
    ASSERT_NOT_OOB(len, sizeof(auth));

    ua_conn_add_header(conn, "Authorization", auth);

#ifdef CCORD_DEBUG_HTTP
    curl_easy_setopt(ua_conn_get_easy_handle(conn), CURLOPT_VERBOSE, 1L);
#endif
}

void
discord_async_init(struct discord_async *async,
                   struct logconf *conf,
                   struct ccord_szbuf_readonly *token)
{
    logconf_branch(&async->conf, conf, "DISCORD_ASYNC");

    async->ua = ua_init(&(struct ua_attr){ .conf = conf });
    ua_set_url(async->ua, DISCORD_API_BASE_URL);
    ua_set_opt(async->ua, token, &_discord_on_curl_setopt);

    /* queues are malloc'd to guarantee a client cloned by
     * discord_clone() will share the same queue with the original */
    async->queues = malloc(sizeof *async->queues);
    QUEUE_INIT(&async->queues->recycling);
    QUEUE_INIT(&async->queues->pending);
    QUEUE_INIT(&async->queues->finished);

    async->mhandle = curl_multi_init();
    async->io_poller = io_poller_create();
    io_poller_curlm_add(async->io_poller, async->mhandle,
                        &_discord_on_rest_perform,
                        CONTAINEROF(async, struct discord_rest, async));

    async->retry_limit = 3; /* FIXME: shouldn't be a hard limit */
}

void
discord_async_cleanup(struct discord_async *async)
{
    QUEUE *const cxt_queues[] = { &async->queues->recycling,
                                  &async->queues->pending,
                                  &async->queues->finished };

    for (size_t i = 0; i < sizeof(cxt_queues) / sizeof *cxt_queues; ++i) {
        QUEUE(struct discord_context) queue, *qelem;
        struct discord_context *cxt;

        QUEUE_MOVE(cxt_queues[i], &queue);
        while (!QUEUE_EMPTY(&queue)) {
            qelem = QUEUE_HEAD(&queue);
            QUEUE_REMOVE(qelem);

            cxt = QUEUE_DATA(qelem, struct discord_context, entry);
            _discord_context_cleanup(cxt);
        }
    }
    free(async->queues);

    /* cleanup curl's multi handle */
    io_poller_curlm_del(async->io_poller, async->mhandle);
    curl_multi_cleanup(async->mhandle);
    /* cleanup REST io_poller */
    io_poller_destroy(async->io_poller);
    /* cleanup User-Agent handle */
    ua_cleanup(async->ua);
}

static void
_discord_context_to_multipart(curl_mime *mime, void *p_cxt)
{
    struct discord_context *cxt = p_cxt;
    curl_mimepart *part;
    char name[64];

    /* json part */
    if (cxt->body.start && cxt->body.size) {
        part = curl_mime_addpart(mime);
        curl_mime_data(part, cxt->body.start, cxt->body.size);
        curl_mime_type(part, "application/json");
        curl_mime_name(part, "payload_json");
    }

    /* attachment part */
    for (int i = 0; i < cxt->attachments.size; ++i) {
        int len = snprintf(name, sizeof(name), "files[%d]", i);
        ASSERT_NOT_OOB(len, sizeof(name));

        if (cxt->attachments.array[i].content) {
            part = curl_mime_addpart(mime);
            curl_mime_data(part, cxt->attachments.array[i].content,
                           cxt->attachments.array[i].size
                               ? cxt->attachments.array[i].size
                               : CURL_ZERO_TERMINATED);
            curl_mime_filename(part, !cxt->attachments.array[i].filename
                                         ? "a.out"
                                         : cxt->attachments.array[i].filename);
            curl_mime_type(part, !cxt->attachments.array[i].content_type
                                     ? "application/octet-stream"
                                     : cxt->attachments.array[i].content_type);
            curl_mime_name(part, name);
        }
        else if (cxt->attachments.array[i].filename) {
            CURLcode code;

            /* fetch local file by the filename */
            part = curl_mime_addpart(mime);
            code =
                curl_mime_filedata(part, cxt->attachments.array[i].filename);
            if (code != CURLE_OK) {
                char errbuf[256];
                snprintf(errbuf, sizeof(errbuf), "%s (file: %s)",
                         curl_easy_strerror(code),
                         cxt->attachments.array[i].filename);
                perror(errbuf);
            }
            curl_mime_type(part, !cxt->attachments.array[i].content_type
                                     ? "application/octet-stream"
                                     : cxt->attachments.array[i].content_type);
            curl_mime_name(part, name);
        }
    }
}

CCORDcode
discord_async_start_bucket_request(struct discord_async *async,
                                   struct discord_bucket *b)
{
    struct discord_context *cxt = discord_bucket_remove_context(b);
    CURL *ehandle;

    b->performing_cxt = cxt;
    cxt->conn = ua_conn_start(async->ua);
    ehandle = ua_conn_get_easy_handle(cxt->conn);

    if (HTTP_MIMEPOST == cxt->method) {
        ua_conn_add_header(cxt->conn, "Content-Type", "multipart/form-data");
        ua_conn_set_mime(cxt->conn, cxt, &_discord_context_to_multipart);
    }
    else {
        ua_conn_add_header(cxt->conn, "Content-Type", "application/json");
    }

    ua_conn_setup(cxt->conn, &(struct ua_conn_attr){
                                 .method = cxt->method,
                                 .body = cxt->body.start,
                                 .body_size = cxt->body.size,
                                 .endpoint = cxt->endpoint,
                                 .base_url = NULL,
                             });

    /* link 'cxt' to 'ehandle' for easy retrieval */
    curl_easy_setopt(ehandle, CURLOPT_PRIVATE, cxt);

    /* initiate libcurl transfer */
    return (curl_multi_add_handle(async->mhandle, ehandle) != CURLM_OK)
               ? CCORD_CURLM_INTERNAL
               : CCORD_OK;
}

bool
discord_async_retry_context(struct discord_async *async,
                            struct discord_context *cxt)
{
    if (!cxt->retry || cxt->retry_attempt++ >= async->retry_limit)
        return false;

    cxt->b->performing_cxt = NULL;
    ua_conn_reset(cxt->conn);

    /* FIXME: wait_ms > 0 should be dealt with aswell */
    if (cxt->wait_ms <= 0) discord_bucket_add_context(cxt->b, cxt, true);

    return true;
}

void
discord_async_cancel_context(struct discord_async *async,
                             struct discord_context *cxt)
{
    struct discord_refcounter *rc = &CLIENT(async, rest.async)->refcounter;

    if (cxt->conn) ua_conn_stop(cxt->conn);

    if (cxt->dispatch.keep)
        discord_refcounter_decr(rc, (void *)cxt->dispatch.keep);
    if (cxt->dispatch.data) discord_refcounter_decr(rc, cxt->dispatch.data);

    cxt->b->performing_cxt = NULL;
    cxt->body.size = 0;
    cxt->method = 0;
    *cxt->endpoint = '\0';
    *cxt->key = '\0';
    cxt->conn = NULL;
    cxt->retry_attempt = 0;
    discord_attachments_cleanup(&cxt->attachments);
    memset(cxt, 0, sizeof(struct discord_attributes));

    QUEUE_REMOVE(&cxt->entry);
    QUEUE_INIT(&cxt->entry);
    QUEUE_INSERT_TAIL(&async->queues->recycling, &cxt->entry);
}

/* Only fields required at _discord_context_to_multipart() are duplicated */
static void
_discord_attachments_dup(struct discord_attachments *dest,
                         struct discord_attachments *src)
{
    __carray_init(dest, (size_t)src->size, struct discord_attachment, , );
    for (int i = 0; i < src->size; ++i) {
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
                            struct discord_attributes *attr,
                            struct ccord_szbuf *body,
                            enum http_method method,
                            char endpoint[DISCORD_ENDPT_LEN],
                            char key[DISCORD_ROUTE_LEN])
{
    struct discord_rest *rest = CONTAINEROF(async, struct discord_rest, async);
    struct discord *client = CLIENT(rest, rest);
    struct discord_context *cxt = _discord_context_get(async);

    cxt->method = method;

    memcpy(cxt, attr, sizeof *attr);

    if (attr->attachments.size)
        _discord_attachments_dup(&cxt->attachments, &attr->attachments);

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

    cxt->cond = NULL;

    if (attr->dispatch.keep) {
        CCORDcode code = discord_refcounter_incr(&client->refcounter,
                                                 (void *)attr->dispatch.keep);

        ASSERT_S(code == CCORD_OK,
                 "'.keep' data must be a Concord callback parameter");
    }
    if (attr->dispatch.data
        && CCORD_UNAVAILABLE
               == discord_refcounter_incr(&client->refcounter,
                                          attr->dispatch.data))
    {
        discord_refcounter_add_client(&client->refcounter, attr->dispatch.data,
                                      attr->dispatch.cleanup, false);
    }

    /* context will be assigned to its bucket at the REST thread  */
    QUEUE_INSERT_TAIL(&rest->async.queues->pending, &cxt->entry);

    io_poller_wakeup(async->io_poller);

    return cxt;
}
