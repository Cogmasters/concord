#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#include "discord-worker.h"
#include "threadpool.h"

/** true after threadpool initialization */
static _Bool once;

/** request thread and optional callback execution thread */
static threadpool_t *tpool;

int
discord_worker_global_init(void)
{
    static int nthreads = 0;
    static int queue_size = 0;
    const char *val;
    char *p_end;

    if (once) return 1;

    /* get threadpool thread amount */
    val = getenv("CCORD_THREADPOOL_SIZE");
    if (val != NULL) {
        nthreads = (int)strtol(val, &p_end, 10);
    }
    if (nthreads < 2 || ERANGE == errno || p_end == val) {
        nthreads = 2;
    }
    /* get threadpool queue size */
    val = getenv("CCORD_THREADPOOL_QUEUE_SIZE");
    if (val != NULL) {
        queue_size = (int)strtol(val, &p_end, 10);
    }
    if (queue_size < 8 || ERANGE == errno || p_end == val) {
        queue_size = 8;
    }

    /* initialize threadpool */
    tpool = threadpool_create(nthreads, queue_size, 0);

    once = 1;

    return 0;
}

int
discord_worker_add(struct discord *client,
                   void (*callback)(void *data),
                   void *data)
{
    (void)client;
    return threadpool_add(tpool, callback, data, 0);
}

void
discord_worker_global_cleanup(void)
{
    /* cleanup thread-pool manager */
    threadpool_destroy(tpool, threadpool_graceful);
    once = 0;
}
