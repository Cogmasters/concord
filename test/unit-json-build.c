#include <string.h>

#include "json-build.h"
#include "test-utils.h"

TEST empty_object(void)
{
    jsonb b;
    char buf[32] = "";
    jsonb_init(&b);
    ASSERT_EQ(JSONB_OK,  jsonb_object(&b, buf, sizeof(buf)));
    ASSERT_EQ(JSONB_END, jsonb_object_pop(&b, buf, sizeof(buf)));
    ASSERT_STR_EQ("{}", buf);
    PASS();
}

TEST object_string_field(void)
{
    jsonb b;
    char buf[64] = "";
    jsonb_init(&b);
    ASSERT_EQ(JSONB_OK, jsonb_object(&b, buf, sizeof(buf)));
    ASSERT_EQ(JSONB_OK, jsonb_key(&b, buf, sizeof(buf), "k", 1));
    ASSERT_EQ(JSONB_OK, jsonb_string(&b, buf, sizeof(buf), "v", 1));
    ASSERT_EQ(JSONB_END, jsonb_object_pop(&b, buf, sizeof(buf)));
    ASSERT_STR_EQ("{\"k\":\"v\"}", buf);
    PASS();
}

TEST object_number_field(void)
{
    jsonb b;
    char buf[64] = "";
    jsonb_init(&b);
    ASSERT_EQ(JSONB_OK, jsonb_object(&b, buf, sizeof(buf)));
    ASSERT_EQ(JSONB_OK, jsonb_key(&b, buf, sizeof(buf), "n", 1));
    ASSERT_EQ(JSONB_OK, jsonb_number(&b, buf, sizeof(buf), 42.0));
    ASSERT_EQ(JSONB_END, jsonb_object_pop(&b, buf, sizeof(buf)));
    ASSERT_STR_EQ("{\"n\":42}", buf);
    PASS();
}

TEST empty_array(void)
{
    jsonb b;
    char buf[16] = "";
    jsonb_init(&b);
    ASSERT_EQ(JSONB_OK,  jsonb_array(&b, buf, sizeof(buf)));
    ASSERT_EQ(JSONB_END, jsonb_array_pop(&b, buf, sizeof(buf)));
    ASSERT_STR_EQ("[]", buf);
    PASS();
}

TEST array_with_values(void)
{
    jsonb b;
    char buf[64] = "";
    jsonb_init(&b);
    ASSERT_EQ(JSONB_OK, jsonb_array(&b, buf, sizeof(buf)));
    ASSERT_EQ(JSONB_OK, jsonb_number(&b, buf, sizeof(buf), 1.0));
    ASSERT_EQ(JSONB_OK, jsonb_number(&b, buf, sizeof(buf), 2.0));
    ASSERT_EQ(JSONB_END, jsonb_array_pop(&b, buf, sizeof(buf)));
    ASSERT_STR_EQ("[1,2]", buf);
    PASS();
}

TEST buffer_overflow_guard(void)
{
    jsonb b;
    /* 10 bytes fits {"k": (5 chars) but not "value_too_long" (16 chars) */
    char buf[10] = "";
    jsonb_init(&b);
    ASSERT_EQ(JSONB_OK, jsonb_object(&b, buf, sizeof(buf)));
    ASSERT_EQ(JSONB_OK, jsonb_key(&b, buf, sizeof(buf), "k", 1));
    jsonbcode rc = jsonb_string(&b, buf, sizeof(buf), "value_too_long", 14);
    ASSERT_EQ(JSONB_ERROR_NOMEM, rc);
    PASS();
}

SUITE(json_build)
{
    RUN_TEST(empty_object);
    RUN_TEST(object_string_field);
    RUN_TEST(object_number_field);
    RUN_TEST(empty_array);
    RUN_TEST(array_with_values);
    RUN_TEST(buffer_overflow_guard);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(json_build);
    GREATEST_MAIN_END();
}
