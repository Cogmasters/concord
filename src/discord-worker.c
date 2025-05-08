#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#include "threadpool.h"

#include "discord.h"
#include "discord-internal.h"
#include "discord-worker.h"

threadpool_t *g_tpool;

CCORDcode
discord_worker_global_init(long flags)
{
    static int nthreads;
    static int queue_size;
    const char *val;
    char *p_end;
    (void)flags;

    if (g_tpool) {
        logmod_log(
            WARN, NULL,
            "Threadpool already initialized, skipping global initialization");
        return CCORD_OK;
    }

    if (!nthreads) {
        if ((val = getenv("CCORD_THREADPOOL_SIZE")))
            nthreads = (int)strtol(val, &p_end, 10);
        if (nthreads < 2 || ERANGE == errno || p_end == val) nthreads = 2;
    }
    if (!queue_size) {
        if ((val = getenv("CCORD_THREADPOOL_QUEUE_SIZE")))
            queue_size = (int)strtol(val, &p_end, 10);
        if (queue_size < 8 || ERANGE == errno || p_end == val) queue_size = 8;
    }

    if (!(g_tpool = threadpool_create(nthreads, queue_size, 0))) {
        fprintf(stderr, "Couldn't create threadpool\n");
        return CCORD_GLOBAL_INIT;
    }

    return CCORD_OK;
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
    threadpool_destroy(g_tpool, threadpool_graceful);
    g_tpool = NULL;
}
