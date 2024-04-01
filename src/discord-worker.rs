#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#include "threadpool.h"

#include "discord.h"
#include "discord-internal.h"
#include "discord-worker.h"

/** true after threadpool initialization */
static _Bool once;

/** global threadpool manager */
threadpool_t *g_tpool;

int
discord_worker_global_init(void)
{
    static int nthreads;
    static int queue_size;
    const char *val;
    char *p_end;

    if (once) return 1;

    /* get threadpool thread amount */
    if (!nthreads) {
        if ((val = getenv("CCORD_THREADPOOL_SIZE")))
            nthreads = (int)strtol(val, &p_end, 10);
        if (nthreads < 2 || ERANGE == errno || p_end == val) nthreads = 2;
    }
    /* get threadpool queue size */
    if (!queue_size) {
        if ((val = getenv("CCORD_THREADPOOL_QUEUE_SIZE")))
            queue_size = (int)strtol(val, &p_end, 10);
        if (queue_size < 8 || ERANGE == errno || p_end == val) queue_size = 8;
    }

    /* initialize threadpool */
    g_tpool = threadpool_create(nthreads, queue_size, 0);

    once = 1;

    return 0;
}

struct discord_worker_context {
    struct discord *client;
    void *data;
    void (*callback)(void *data);
};

static void
_discord_worker_cb(void *p_cxt)
{
    struct discord_worker_context *cxt = p_cxt;

    pthread_mutex_lock(&cxt->client->workers->lock);
    ++cxt->client->workers->count;
    pthread_mutex_unlock(&cxt->client->workers->lock);

    cxt->callback(cxt->data);

    pthread_mutex_lock(&cxt->client->workers->lock);
    --cxt->client->workers->count;
    pthread_cond_signal(&cxt->client->workers->cond);
    pthread_mutex_unlock(&cxt->client->workers->lock);

    free(cxt);
}

CCORDcode
discord_worker_add(struct discord *client,
                   void (*callback)(void *data),
                   void *data)
{
    struct discord_worker_context *cxt = malloc(sizeof *cxt);
    *cxt = (struct discord_worker_context){ client, data, callback };

    return 0 == threadpool_add(g_tpool, _discord_worker_cb, cxt, 0)
               ? CCORD_OK
               : CCORD_FULL_WORKER;
}

CCORDcode
discord_worker_join(struct discord *client)
{
    pthread_mutex_lock(&client->workers->lock);
    while (client->workers->count != 0) {
        pthread_cond_wait(&client->workers->cond, &client->workers->lock);
    }
    pthread_mutex_unlock(&client->workers->lock);
    return CCORD_OK;
}

void
discord_worker_global_cleanup(void)
{
    /* cleanup thread-pool manager */
    threadpool_destroy(g_tpool, threadpool_graceful);
    once = 0;
}
