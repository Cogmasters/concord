#include <string.h>

#include "threadpool.h"
#include "test-utils.h"

#define TASK_COUNT 32

static int g_done[TASK_COUNT];

static void mark_done(void *arg)
{
    int *flag = (int *)arg;
    *flag = 1;
}

TEST submit_and_drain(void)
{
    memset(g_done, 0, sizeof(g_done));

    threadpool_t *pool = threadpool_create(4, 64, 0);
    ASSERT_NEQ(NULL, pool);

    for (int i = 0; i < TASK_COUNT; i++) {
        int r = threadpool_add(pool, mark_done, &g_done[i], 0);
        ASSERT_EQ(0, r);
    }

    /* Graceful destroy waits for all pending tasks to complete. */
    threadpool_destroy(pool, threadpool_graceful);

    int done = 0;
    for (int i = 0; i < TASK_COUNT; i++) done += g_done[i];
    ASSERT_EQ(TASK_COUNT, done);
    PASS();
}

TEST single_thread_single_task(void)
{
    int flag = 0;
    threadpool_t *pool = threadpool_create(1, 4, 0);
    ASSERT_NEQ(NULL, pool);

    ASSERT_EQ(0, threadpool_add(pool, mark_done, &flag, 0));
    threadpool_destroy(pool, threadpool_graceful);
    ASSERT_EQ(1, flag);
    PASS();
}

SUITE(threadpool)
{
    RUN_TEST(submit_and_drain);
    RUN_TEST(single_thread_single_task);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(threadpool);
    GREATEST_MAIN_END();
}
