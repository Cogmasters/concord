#include "anomap.h"
#include "test-utils.h"

ANOMAP_DECLARE_COMPARE_FUNCTION(cmp_int, int)

TEST insert_and_lookup(void)
{
    struct anomap *m = anomap_create(sizeof(int), sizeof(int), cmp_int);
    ASSERT_NEQ(NULL, m);

    int k = 42, v = 100;
    enum anomap_operation op = anomap_do(m, anomap_insert, &k, &v);
    ASSERT(op & anomap_insert);

    int got = 0;
    op = anomap_do(m, anomap_getval, &k, &got);
    ASSERT(op & anomap_getval);
    ASSERT_EQ(100, got);

    anomap_destroy(m);
    PASS();
}

TEST lookup_miss(void)
{
    struct anomap *m = anomap_create(sizeof(int), sizeof(int), cmp_int);
    ASSERT_NEQ(NULL, m);

    int k = 1, v = 0;
    enum anomap_operation op = anomap_do(m, anomap_getval, &k, &v);
    ASSERT_EQ(0, (int)op);

    anomap_destroy(m);
    PASS();
}

TEST insert_and_delete(void)
{
    struct anomap *m = anomap_create(sizeof(int), sizeof(int), cmp_int);
    ASSERT_NEQ(NULL, m);

    int k = 7, v = 99;
    anomap_do(m, anomap_insert, &k, &v);
    ASSERT_EQ(1, (int)anomap_length(m));

    enum anomap_operation op = anomap_do(m, anomap_delete, &k, NULL);
    ASSERT(op & anomap_delete);
    ASSERT_EQ(0, (int)anomap_length(m));

    /* key is no longer found */
    op = anomap_do(m, anomap_getval, &k, &v);
    ASSERT_EQ(0, (int)op);

    anomap_destroy(m);
    PASS();
}

TEST upsert_updates_value(void)
{
    struct anomap *m = anomap_create(sizeof(int), sizeof(int), cmp_int);
    ASSERT_NEQ(NULL, m);

    int k = 5, v1 = 10, v2 = 20, got = 0;
    anomap_do(m, anomap_insert, &k, &v1);
    anomap_do(m, anomap_upsert, &k, &v2);

    anomap_do(m, anomap_getval, &k, &got);
    ASSERT_EQ(20, got);
    ASSERT_EQ(1, (int)anomap_length(m));

    anomap_destroy(m);
    PASS();
}

TEST multiple_entries_length(void)
{
    struct anomap *m = anomap_create(sizeof(int), sizeof(int), cmp_int);
    ASSERT_NEQ(NULL, m);

    for (int i = 0; i < 16; i++) {
        int v = i * 2;
        anomap_do(m, anomap_insert, &i, &v);
    }
    ASSERT_EQ(16, (int)anomap_length(m));

    anomap_clear(m);
    ASSERT_EQ(0, (int)anomap_length(m));

    anomap_destroy(m);
    PASS();
}

SUITE(anomap)
{
    RUN_TEST(insert_and_lookup);
    RUN_TEST(lookup_miss);
    RUN_TEST(insert_and_delete);
    RUN_TEST(upsert_updates_value);
    RUN_TEST(multiple_entries_length);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(anomap);
    GREATEST_MAIN_END();
}
