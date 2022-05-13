#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

static void
_discord_context_cleanup(struct discord_context *cxt)
{
    discord_attachments_cleanup(&cxt->attachments);
    if (cxt->body.buf.start) free(cxt->body.buf.start);
    free(cxt);
}

static struct discord_context *
_discord_context_init(QUEUE *cxt_idle_queue)
{
    struct discord_context *cxt;

    if (QUEUE_EMPTY(cxt_idle_queue)) { /* create new context struct */
        cxt = calloc(1, sizeof(struct discord_context));
    }
    else { /* recycle a context struct from idleq */
        QUEUE(struct discord_context) *qelem = QUEUE_HEAD(cxt_idle_queue);
        QUEUE_REMOVE(qelem);
        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
    }
    QUEUE_INIT(&cxt->entry);

    return cxt;
}

QUEUE *
discord_context_queue_init(void)
{
    QUEUE(struct discord_context) *new_cxt_queue = malloc(sizeof(QUEUE));
    QUEUE_INIT(new_cxt_queue);
    return new_cxt_queue;
}

void
discord_context_queue_cleanup(QUEUE *cxt_queue)
{
    QUEUE(struct discord_context) queue, *qelem;
    struct discord_context *cxt;

    QUEUE_MOVE(cxt_queue, &queue);
    while (!QUEUE_EMPTY(&queue)) {
        qelem = QUEUE_HEAD(&queue);
        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
        QUEUE_REMOVE(&cxt->entry);
        _discord_context_cleanup(cxt);
    }
    free(cxt_queue);
}

void
discord_context_bucket_enqueue(struct discord_bucket *b,
                               struct discord_context *cxt,
                               bool high_priority)
{
    if (high_priority)
        QUEUE_INSERT_HEAD(&b->waitq, &cxt->entry);
    else
        QUEUE_INSERT_TAIL(&b->waitq, &cxt->entry);
}

struct discord_context *
discord_context_bucket_dequeue(struct discord_bucket *b)
{
    QUEUE(struct discord_context) *qelem = QUEUE_HEAD(&b->waitq);
    QUEUE_REMOVE(qelem);
    QUEUE_INIT(qelem);

    return QUEUE_DATA(qelem, struct discord_context, entry);
}

CURLMcode
discord_context_send(struct discord_adapter *adapter,
                     struct discord_context *cxt,
                     struct ua_conn *conn)
{
    CURL *ehandle = ua_conn_get_easy_handle(conn);
    CURLMcode mcode;

    cxt->conn = conn;
    cxt->b->busy = cxt;

    /* link 'cxt' to 'ehandle' for easy retrieval */
    curl_easy_setopt(ehandle, CURLOPT_PRIVATE, cxt);

    /* initiate libcurl transfer */
    mcode = curl_multi_add_handle(adapter->mhandle, ehandle);

    io_poller_curlm_enable_perform(CLIENT(adapter, adapter)->io_poller,
                                   adapter->mhandle);

    return mcode;
}

void
discord_context_to_curlmime(curl_mime *mime, void *p_cxt)
{
    struct discord_context *cxt = p_cxt;
    struct discord_attachments *atchs = &cxt->attachments;
    struct ccord_szbuf *body = &cxt->body.buf;
    curl_mimepart *part;
    char name[64];

    /* json part */
    if (body->start && body->size) {
        part = curl_mime_addpart(mime);
        curl_mime_data(part, body->start, body->size);
        curl_mime_type(part, "application/json");
        curl_mime_name(part, "payload_json");
    }

    /* attachment part */
    for (int i = 0; i < atchs->size; ++i) {
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

bool
discord_context_retry_enqueue(struct discord_adapter *adapter,
                              struct discord_context *cxt,
                              int64_t wait_ms)
{
    if (adapter->retry_limit < cxt->retry_attempt++) return false;

    CURL *ehandle = ua_conn_get_easy_handle(cxt->conn);

    curl_multi_remove_handle(adapter->mhandle, ehandle);
    ua_conn_reset(cxt->conn);
    if (wait_ms <= 0) discord_context_bucket_enqueue(cxt->b, cxt, true);

    return true;
}

void
discord_context_recycle_enqueue(struct discord_adapter *adapter,
                                struct discord_context *cxt)
{
    CURL *ehandle = ua_conn_get_easy_handle(cxt->conn);

    curl_multi_remove_handle(adapter->mhandle, ehandle);
    if (cxt->conn) ua_conn_stop(cxt->conn);

    discord_refcounter_decr(CLIENT(adapter, adapter)->refcounter,
                            cxt->dispatch.data);

    cxt->b = NULL;
    cxt->body.buf.size = 0;
    cxt->method = 0;
    *cxt->endpoint = '\0';
    *cxt->key = '\0';
    cxt->conn = NULL;
    cxt->retry_attempt = 0;
    discord_attachments_cleanup(&cxt->attachments);
    memset(cxt, 0, sizeof(struct discord_request));

    QUEUE_INSERT_TAIL(adapter->idleq, &cxt->entry);
}

/* Only the fields that are required at discord_context_to_curlmime()
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
discord_context_populate(struct discord_adapter *adapter,
                         struct discord_request *req,
                         struct ccord_szbuf *body,
                         enum http_method method,
                         char endpoint[DISCORD_ENDPT_LEN],
                         char key[DISCORD_ROUTE_LEN])
{
    struct discord *client = CLIENT(adapter, adapter);
    struct discord_context *cxt = _discord_context_init(adapter->idleq);

    cxt->method = method;

    memcpy(cxt, req, sizeof *req);
    _discord_attachments_dup(&cxt->attachments, &req->attachments);

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
    /* copy bucket's key */
    memcpy(cxt->key, key, sizeof(cxt->key));
    /* bucket pertaining to the request */
    cxt->b = discord_bucket_get(adapter->ratelimiter, key);

    if (req->dispatch.data)
        discord_refcounter_incr(client->refcounter, req->dispatch.data,
                                req->dispatch.cleanup, false);

    io_poller_curlm_enable_perform(client->io_poller, adapter->mhandle);

    return cxt;
}
