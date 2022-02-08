#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <inttypes.h>

#include "greatest.h"

#define JSONB_HEADER
#include "json-build.h"

#include "header.h"

TEST
check_primitives_list_json_encoding(void)
{
    int array[] = { INT_MIN, -1, 0, 1, INT_MAX };
    struct integers list = { 0 };
    char buf[1024], expect[1024];

    list.size = sizeof(array) / sizeof(int);
    list.array = array;

    sprintf(expect, "[%d,-1,0,1,%d]", INT_MIN, INT_MAX);

    ASSERTm(buf, integers_to_json(buf, sizeof(buf), &list) != 0);
    ASSERT_STR_EQ(expect, buf);

    PASS();
}

TEST
check_nested_object_json_encoding(void)
{
    struct foo foo = { 0 };
    struct foo child1 = { 0 }, child2 = { 0 }, child3 = { 0 }, child4 = { 0 },
               child5 = { 0 }, child6 = { 0 };
    char buf[1024];

    foo.id = "1234";
    foo.name = "Marcel";
    foo.b = 12;
    foo.child = &child1;

    child1.id = "4321";
    child1.name = "Lecram";
    child1.b = 21;
    child1.child = &child2;

    child2.child = &child3;
    child3.child = &child4;
    child4.child = &child5;
    child5.child = &child6;

    ASSERTm(buf, foo_to_json(buf, sizeof(buf), &foo) != 0);
    ASSERT_STR_EQ("{\"id\":\"1234\",\"name\":\"Marcel\",\"b\":12,\"child\":{"
                  "\"id\":\"4321\",\"name\":\"Lecram\",\"b\":21,\"child\":{"
                  "\"child\":{\"child\":{\"child\":{\"child\":{}}}}}}}",
                  buf);

    PASS();
}

TEST
check_deep_nested_object_json_encoding(void)
{
    struct foo foo = { 0 }, *p = &foo;
    jsonb b;

    char json[JSONB_MAX_DEPTH * sizeof("{,}\"child\":")];
    char buf[sizeof(json)];
    int i;

    jsonb_init(&b);
    /* create 'expected' json string */
    jsonb_object(&b, json, sizeof(json));
    for (i = 0; i < JSONB_MAX_DEPTH - 1; ++i) {
        jsonb_key(&b, json, sizeof(json), "child", sizeof("child") - 1);
        jsonb_object(&b, json, sizeof(json));
    }
    jsonb_object(&b, json, sizeof(json));
    for (i = 0; i < JSONB_MAX_DEPTH - 1; ++i)
        jsonb_object_pop(&b, json, sizeof(json));
    jsonb_object_pop(&b, json, sizeof(json));

    /* create deep-nested struct that will be encoded to json */
    for (i = 0; i < JSONB_MAX_DEPTH - 1; ++i) {
        p->child = calloc(1, sizeof *p->child);
        p = p->child;
    }

    ASSERTm(buf, foo_to_json(buf, sizeof(buf), &foo) != 0);
    ASSERT_STR_EQ(json, buf);

    foo_cleanup(&foo);

    PASS();
}

TEST
check_nested_list_json_encoding(void)
{
    struct bars bars = { 0 };
    struct bars child1 = { 0 }, child2 = { 0 }, child3 = { 0 }, child4 = { 0 },
                child5 = { 0 };
    char buf[1024];

    bars.size = 1;
    bars.array = &child1;

    child1.size = 1;
    child1.array = &child2;

    child2.size = 1;
    child2.array = &child3;

    child3.size = 1;
    child3.array = &child4;

    child4.size = 1;
    child4.array = &child5;

    ASSERTm(buf, bars_to_json(buf, sizeof(buf), &bars) != 0);
    ASSERT_STR_EQ("[[[[[[]]]]]]", buf);

    PASS();
}

SUITE(json_encoding)
{
    RUN_TEST(check_primitives_list_json_encoding);
    RUN_TEST(check_nested_object_json_encoding);
    RUN_TEST(check_deep_nested_object_json_encoding);
    RUN_TEST(check_nested_list_json_encoding);
}

TEST
check_deep_nested_object_json_decoding(void)
{
    struct foo foo = { 0 };
    jsonb b;

    char json[JSONB_MAX_DEPTH * sizeof("{,}\"child\":")];
    char buf[sizeof(json)];
    int i;

    jsonb_init(&b);
    /* create 'expected' json string */
    jsonb_object(&b, json, sizeof(json));
    for (i = 0; i < JSONB_MAX_DEPTH - 1; ++i) {
        jsonb_key(&b, json, sizeof(json), "child", sizeof("child") - 1);
        jsonb_object(&b, json, sizeof(json));
    }
    jsonb_object(&b, json, sizeof(json));
    for (i = 0; i < JSONB_MAX_DEPTH - 1; ++i)
        jsonb_object_pop(&b, json, sizeof(json));
    jsonb_object_pop(&b, json, sizeof(json));

    ASSERT_FALSE(0 == foo_from_json(json, sizeof(json), &foo));
    ASSERTm(buf, foo_to_json(buf, sizeof(buf), &foo) != 0);
    ASSERT_STR_EQ(json, buf);

    foo_cleanup(&foo);

    PASS();
}

TEST
check_deep_nested_list_json_decoding(void)
{
    struct bars bars = { 0 };

    char json[JSONB_MAX_DEPTH * sizeof("[],")];
    char buf[sizeof(json)];
    jsonb b;
    int i;

    jsonb_init(&b);
    for (i = 0; i < JSONB_MAX_DEPTH; ++i)
        jsonb_array(&b, json, sizeof(json));
    for (i = 0; i < JSONB_MAX_DEPTH - 1; ++i)
        jsonb_array_pop(&b, json, sizeof(json));
    jsonb_array_pop(&b, json, sizeof(json));

    ASSERT_FALSE(0 == bars_from_json(json, sizeof(json), &bars));
    ASSERTm(buf, bars_to_json(buf, sizeof(buf), &bars) != 0);
    ASSERT_STR_EQ(json, buf);

    bars_cleanup(&bars);

    PASS();
}

SUITE(json_decoding)
{
    RUN_TEST(check_deep_nested_object_json_decoding);
    RUN_TEST(check_deep_nested_list_json_decoding);
}

TEST
check_channel_decoding(void)
{
    struct discord_channel channel = { 0 };

    const char json[] =
        "{\"type\":0,\"topic\":null,\"rate_limit_per_user\":0,\"position\":0,"
        "\"permission_overwrites\":[],\"parent_id\":null,\"nsfw\":false,"
        "\"name\":\"oi\",\"last_message_id\":null,\"id\":"
        "\"939234041079681094\",\"guild_id\":\"744351581478191194\",\"guild_"
        "hashes\":{\"version\":1,\"roles\":{\"hash\":\"clz3qQji6k0\"},"
        "\"metadata\":{\"hash\":\"2kz4n0cOSHI\"},\"channels\":{\"hash\":"
        "\"XXnR3q/DxXc\"}}}";
    char buf[sizeof(json)];

    ASSERT_FALSE(0 == discord_channel_from_json(json, sizeof(json), &channel));
    ASSERT_FALSEm(buf, !discord_channel_to_json(buf, sizeof(buf), &channel));
    ASSERT_EQ(0, channel.type);
    ASSERT_EQ(NULL, channel.topic);
    ASSERT_EQ(0, channel.rate_limit_per_user);
    ASSERT_EQ(0, channel.position);
    ASSERT_FALSE(NULL == channel.permission_overwrites);
    ASSERT_EQ(0, channel.permission_overwrites->size);
    ASSERT_EQ(0, channel.parent_id);
    ASSERT_EQ(false, channel.nsfw);
    ASSERT_STR_EQ("oi", channel.name);
    ASSERT_EQ(0, channel.last_message_id);
    ASSERT_EQ(939234041079681094, channel.id);
    ASSERT_EQ(744351581478191194, channel.guild_id);

    discord_channel_cleanup(&channel);

    PASS();
}

SUITE(discord_api)
{
    RUN_TEST(check_channel_decoding);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(json_encoding);
    RUN_SUITE(json_decoding);
    RUN_SUITE(discord_api);

    GREATEST_MAIN_END();
}
