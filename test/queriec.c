#include <stdio.h>

#include "queriec.h"

#include "greatest.h"

TEST
valid_single_query(void)
{
    char query[64] = "";

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    int res = queriec_add(&queriec, query, "test", sizeof("test"), "true", sizeof("true"));
    ASSERT_EQ(QUERIEC_OK, res);

    ASSERT_STR_EQ("?test=true", query);

    PASS();
}

TEST
valid_multiple_queries(void)
{
    char query[64] = "";

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    int res = queriec_add(&queriec, query, "test", sizeof("test"), "true", sizeof("true"));
    ASSERT_EQ(QUERIEC_OK, res);

    res = queriec_add(&queriec, query, "test2", sizeof("test2"), "false", sizeof("false"));
    ASSERT_EQ(QUERIEC_OK, res);

    ASSERT_STR_EQ("?test=true&test2=false", query);

    PASS();
}

TEST
valid_overflow_check(void)
{
    char query[12] = "";

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    int res = queriec_add(&queriec, query, "test", sizeof("test"), "true", sizeof("true"));
    ASSERT_EQ(QUERIEC_OK, res);

    res = queriec_add(&queriec, query, "test2", sizeof("test2"), "false", sizeof("false"));
    ASSERT_EQ(QUERIEC_ERROR_NOMEM, res);

    ASSERT_STR_EQ("?test=true", query);

    PASS();
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();

    RUN_TEST(valid_single_query);
    RUN_TEST(valid_multiple_queries);
    RUN_TEST(valid_overflow_check);

    GREATEST_MAIN_END();
}