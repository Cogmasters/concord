#include "cog-utils.h"
#include "test-utils.h"

TEST strndup_basic(void)
{
    char *dest = NULL;
    size_t len = cog_strndup("hello", 5, &dest);
    ASSERT_EQ(5, (int)len);
    ASSERT_STR_EQ("hello", dest);
    free(dest);
    PASS();
}

TEST strndup_truncate(void)
{
    char *dest = NULL;
    size_t len = cog_strndup("hello world", 5, &dest);
    ASSERT_EQ(5, (int)len);
    ASSERT_STR_EQ("hello", dest);
    free(dest);
    PASS();
}

TEST strtou64_valid(void)
{
    uint64_t val = 0;
    int ok = cog_strtou64("12345", 5, &val);
    ASSERT_EQ(1, ok);
    ASSERT_EQ((uint64_t)12345, val);
    PASS();
}

TEST strtou64_zero(void)
{
    uint64_t val = 99;
    int ok = cog_strtou64("0", 1, &val);
    ASSERT_EQ(1, ok);
    ASSERT_EQ((uint64_t)0, val);
    PASS();
}

TEST u64tostr_roundtrip(void)
{
    char buf[32] = "";
    uint64_t in = 987654321ULL, out = 0;
    int n = cog_u64tostr(buf, sizeof(buf), &in);
    ASSERT_GT(n, 0);
    ASSERT_EQ(1, cog_strtou64(buf, (size_t)n, &out));
    ASSERT_EQ(in, out);
    PASS();
}

TEST iso8601_roundtrip(void)
{
    /* Use a timestamp at a second boundary (0 ms fractional part) so
     * the roundtrip is exact regardless of sub-second precision. */
    char buf[64] = "";
    uint64_t ms_in = 1700000000000ULL, ms_out = 0;
    int n = cog_unix_ms_to_iso8601(buf, sizeof(buf), ms_in);
    ASSERT_GT(n, 0);
    ASSERT_EQ(1, cog_iso8601_to_unix_ms(buf, (size_t)n, &ms_out));
    ASSERT_EQ(ms_in, ms_out);
    PASS();
}

SUITE(cog_utils)
{
    RUN_TEST(strndup_basic);
    RUN_TEST(strndup_truncate);
    RUN_TEST(strtou64_valid);
    RUN_TEST(strtou64_zero);
    RUN_TEST(u64tostr_roundtrip);
    RUN_TEST(iso8601_roundtrip);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(cog_utils);
    GREATEST_MAIN_END();
}
