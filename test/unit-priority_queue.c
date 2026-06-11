#include "priority_queue.h"
#include "test-utils.h"

static int cmp_int(const void *a, const void *b)
{
    int ia = *(const int *)a, ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

TEST min_queue_pop_order(void)
{
    priority_queue *q = priority_queue_create(sizeof(int), 0, cmp_int,
                                              priority_queue_min);
    ASSERT_NEQ(NULL, q);

    int keys[] = { 5, 1, 3, 2, 4 };
    for (int i = 0; i < 5; i++)
        priority_queue_push(q, &keys[i], NULL);

    ASSERT_EQ(5, (int)priority_queue_length(q));

    int prev = 0;
    for (int i = 0; i < 5; i++) {
        int k = 0;
        ASSERT_NEQ(0, (int)priority_queue_pop(q, &k, NULL));
        ASSERT_GTE(k, prev); /* min-heap: each pop is >= the previous */
        prev = k;
    }
    ASSERT_EQ(0, (int)priority_queue_length(q));
    priority_queue_destroy(q);
    PASS();
}

TEST max_queue_pop_order(void)
{
    priority_queue *q = priority_queue_create(sizeof(int), 0, cmp_int,
                                              priority_queue_max);
    ASSERT_NEQ(NULL, q);

    int keys[] = { 3, 1, 4, 1, 5 };
    for (int i = 0; i < 5; i++)
        priority_queue_push(q, &keys[i], NULL);

    int prev = 99999;
    for (int i = 0; i < 5; i++) {
        int k = 0;
        ASSERT_NEQ(0, (int)priority_queue_pop(q, &k, NULL));
        ASSERT_LTE(k, prev); /* max-heap: each pop is <= the previous */
        prev = k;
    }
    priority_queue_destroy(q);
    PASS();
}

TEST single_element(void)
{
    priority_queue *q = priority_queue_create(sizeof(int), 0, cmp_int,
                                              priority_queue_min);
    ASSERT_NEQ(NULL, q);

    int k = 7;
    priority_queue_push(q, &k, NULL);
    ASSERT_EQ(1, (int)priority_queue_length(q));

    int got = 0;
    ASSERT_NEQ(0, (int)priority_queue_pop(q, &got, NULL));
    ASSERT_EQ(7, got);
    ASSERT_EQ(0, (int)priority_queue_length(q));

    priority_queue_destroy(q);
    PASS();
}

TEST empty_pop_returns_zero(void)
{
    priority_queue *q = priority_queue_create(sizeof(int), 0, cmp_int,
                                              priority_queue_min);
    ASSERT_NEQ(NULL, q);

    int k = 0;
    /* pop on empty queue returns 0 (invalid id) */
    ASSERT_EQ(0, (int)priority_queue_pop(q, &k, NULL));

    priority_queue_destroy(q);
    PASS();
}

SUITE(prio_queue)
{
    RUN_TEST(min_queue_pop_order);
    RUN_TEST(max_queue_pop_order);
    RUN_TEST(single_element);
    RUN_TEST(empty_pop_returns_zero);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(prio_queue);
    GREATEST_MAIN_END();
}
