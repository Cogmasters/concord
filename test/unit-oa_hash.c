/* Declarations only — implementation is in libdiscord.a */
#define OA_HASH_HEADER
#include "oa_hash.h"
#undef OA_HASH_HEADER

#include "test-utils.h"

TEST set_and_get(void)
{
    struct oa_hash ht;
    struct oa_hash_entry buckets[8];
    oa_hash_init(&ht, buckets, 8);

    int val = 42;
    ASSERT_NEQ(NULL, oa_hash_set(&ht, "key", 3, &val));

    int *got = oa_hash_get(&ht, "key", 3);
    ASSERT_NEQ(NULL, got);
    ASSERT_EQ(42, *got);
    ASSERT_EQ(1, (int)ht.length);
    PASS();
}

TEST get_miss(void)
{
    struct oa_hash ht;
    struct oa_hash_entry buckets[8];
    oa_hash_init(&ht, buckets, 8);

    ASSERT_EQ(NULL, oa_hash_get(&ht, "absent", 6));
    PASS();
}

TEST set_overwrites_existing(void)
{
    struct oa_hash ht;
    struct oa_hash_entry buckets[8];
    oa_hash_init(&ht, buckets, 8);

    int v1 = 1, v2 = 2;
    oa_hash_set(&ht, "k", 1, &v1);
    oa_hash_set(&ht, "k", 1, &v2);

    int *got = oa_hash_get(&ht, "k", 1);
    ASSERT_NEQ(NULL, got);
    ASSERT_EQ(2, *got);
    ASSERT_EQ(1, (int)ht.length); /* no duplicate */
    PASS();
}

TEST remove_entry(void)
{
    struct oa_hash ht;
    struct oa_hash_entry buckets[8];
    oa_hash_init(&ht, buckets, 8);

    int val = 99;
    oa_hash_set(&ht, "x", 1, &val);
    ASSERT_EQ(1, oa_hash_remove(&ht, "x", 1));
    ASSERT_EQ(NULL, oa_hash_get(&ht, "x", 1));
    ASSERT_EQ(0, (int)ht.length);
    PASS();
}

TEST remove_absent_returns_zero(void)
{
    struct oa_hash ht;
    struct oa_hash_entry buckets[8];
    oa_hash_init(&ht, buckets, 8);

    ASSERT_EQ(0, oa_hash_remove(&ht, "nope", 4));
    PASS();
}

TEST rehash(void)
{
    struct oa_hash ht;
    struct oa_hash_entry small[4], big[16];
    oa_hash_init(&ht, small, 4);

    int v = 1;
    oa_hash_set(&ht, "a", 1, &v);
    oa_hash_set(&ht, "b", 1, &v);

    struct oa_hash_entry *old = oa_hash_rehash(&ht, big, 16);
    ASSERT_NEQ(NULL, old);
    ASSERT_EQ(16, (int)ht.capacity);

    /* values survive rehash */
    ASSERT_NEQ(NULL, oa_hash_get(&ht, "a", 1));
    ASSERT_NEQ(NULL, oa_hash_get(&ht, "b", 1));
    PASS();
}

SUITE(oa_hash)
{
    RUN_TEST(set_and_get);
    RUN_TEST(get_miss);
    RUN_TEST(set_overwrites_existing);
    RUN_TEST(remove_entry);
    RUN_TEST(remove_absent_returns_zero);
    RUN_TEST(rehash);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(oa_hash);
    GREATEST_MAIN_END();
}
