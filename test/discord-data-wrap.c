#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "greatest.h"
#include "discord.h"
#include "discord-internal.h"
#include "jsmn.h"
#include "jsmn-find.h"

/* A real (zeroed) struct discord backs the test client: the data-wrap
 * layer only ever touches its registry, and using the genuine type keeps
 * member access compiler-checked instead of relying on layout overlap. */
struct test_client {
    struct reflectc *registry;
    struct discord *client;
    struct discord storage;
};

static void
init_test_client(struct test_client *tc)
{
    if (!tc) return;
    memset(tc, 0, sizeof(*tc));
    tc->storage.registry = reflectc_init();
    tc->registry = tc->storage.registry;
    tc->client = &tc->storage;
}

static void
dispose_test_client(struct test_client *tc)
{
    if (!tc || !tc->registry) return;
    reflectc_dispose(tc->registry);
    tc->registry = NULL;
    tc->client = NULL;
}

TEST
to_json_roundtrip_components(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT_NEQ(NULL, tc.registry);

    struct discord_component button = {
        .type = DISCORD_COMPONENT_BUTTON,
        .style = DISCORD_BUTTON_PRIMARY,
        .custom_id = "action_button",
        .label = "Click me",
    };
    struct discord_component button_array[] = { button };
    struct discord_components button_children = {
        .size = (int)(sizeof(button_array) / sizeof *button_array),
        .array = button_array,
        .realsize = (int)(sizeof(button_array) / sizeof *button_array),
    };

    struct discord_component row = {
        .type = DISCORD_COMPONENT_ACTION_ROW,
        .components = &button_children,
    };
    struct discord_component row_array[] = { row };
    struct discord_components rows = {
        .size = (int)(sizeof(row_array) / sizeof *row_array),
        .array = row_array,
        .realsize = (int)(sizeof(row_array) / sizeof *row_array),
    };

    struct discord_create_message original = {
        .content = "Testing components",
        .components = &rows,
        .flags = DISCORD_MESSAGE_EPHEMERAL,
    };

    original.components = &rows;

    char *json = NULL;
    size_t json_cap = 0;
    CCORDcode code = discord_data_to_json(
        struct discord_create_message, tc.client, &original, &json, &json_cap);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT_NEQ(NULL, json);
    ASSERT(json_cap > 0);

    ASSERT(strstr(json, "\"components\"") != NULL);
    ASSERT(strstr(json, "\"custom_id\":\"action_button\"") != NULL);
    ASSERT(strstr(json, "\"flags\":") != NULL);

    size_t json_len = strlen(json);
    struct discord_create_message parsed = { 0 };
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_create_message, tc.client,
                                     json, json_len, &parsed));
    ASSERT_NEQ(NULL, parsed.content);
    ASSERT_STR_EQ(original.content, parsed.content);
    ASSERT_NEQ(NULL, parsed.components);
    ASSERT_EQ(1, parsed.components->size);
    ASSERT_NEQ(NULL, parsed.components->array);
    ASSERT_EQ(DISCORD_COMPONENT_ACTION_ROW, parsed.components->array[0].type);
    ASSERT(parsed.components->array[0].components != NULL);
    ASSERT_EQ(1, parsed.components->array[0].components->size);
    ASSERT(parsed.components->array[0].components->array != NULL);
    ASSERT_EQ(DISCORD_COMPONENT_BUTTON,
              parsed.components->array[0].components->array[0].type);
    ASSERT_EQ(DISCORD_BUTTON_PRIMARY,
              parsed.components->array[0].components->array[0].style);
    ASSERT(parsed.components->array[0].components->array[0].label != NULL);
    ASSERT_STR_EQ("Click me",
                  parsed.components->array[0].components->array[0].label);
    ASSERT(parsed.components->array[0].components->array[0].custom_id != NULL);
    ASSERT_STR_EQ("action_button",
                  parsed.components->array[0].components->array[0].custom_id);
    ASSERT_EQ(DISCORD_MESSAGE_EPHEMERAL, parsed.flags);

    discord_data_cleanup(tc.client, &parsed);
    discord_data_unwrap(tc.client, &original);
    free(json);
    dispose_test_client(&tc);
    PASS();
}

TEST
strings_roundtrip(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    char *values_array[] = { "foo", "bar", "baz" };
    struct strings values = {
        .size = (int)(sizeof(values_array) / sizeof *values_array),
        .array = values_array,
        .realsize = (int)(sizeof(values_array) / sizeof *values_array),
    };

    char *json = NULL;
    size_t json_cap = 0;
    CCORDcode code = discord_data_to_json(struct strings, tc.client, &values,
                                          &json, &json_cap);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT(json != NULL);
    ASSERT_EQ(strlen("[\"foo\",\"bar\",\"baz\"]"), strlen(json));
    ASSERT_STR_EQ("[\"foo\",\"bar\",\"baz\"]", json);

    struct strings parsed = { 0 };
    CCORDcode parse_code = discord_data_from_json(struct strings, tc.client,
                                                  json, strlen(json), &parsed);
    if (parse_code != CCORD_OK) {
        FAILm(discord_code_as_string(parse_code));
    }
    ASSERT_EQ(values.size, parsed.size);
    ASSERT(parsed.array != NULL);
    char **parsed_values = parsed.array;
    ASSERT_STR_EQ("foo", parsed_values[0]);
    ASSERT_STR_EQ("bar", parsed_values[1]);
    ASSERT_STR_EQ("baz", parsed_values[2]);

    discord_data_cleanup(tc.client, &parsed);
    discord_data_unwrap(tc.client, &values);
    free(json);
    dispose_test_client(&tc);
    PASS();
}

TEST
optional_bool_serialization(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    struct discord_create_message message = {
        .content = "No TTS",
    };

    char *json = NULL;
    size_t json_cap = 0;
    CCORDcode code = discord_data_to_json(
        struct discord_create_message, tc.client, &message, &json, &json_cap);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT(json != NULL);
    ASSERT(strstr(json, "\"tts\"") == NULL);
    free(json);

    message.tts = true;
    json = NULL;
    json_cap = 0;
    code = discord_data_to_json(struct discord_create_message, tc.client,
                                &message, &json, &json_cap);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT(strstr(json, "\"tts\":true") != NULL);

    discord_data_unwrap(tc.client, &message);
    free(json);
    dispose_test_client(&tc);
    PASS();
}

TEST
embeds_roundtrip(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    struct discord_embed embed = {
        .title = "Title",
        .description = "Description",
    };
    struct discord_embeds embeds = {
        .size = 1,
        .array = &embed,
        .realsize = 1,
    };

    struct discord_create_message message = {
        .embeds = &embeds,
    };

    char *json = NULL;
    size_t json_cap = 0;
    CCORDcode code = discord_data_to_json(
        struct discord_create_message, tc.client, &message, &json, &json_cap);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT(json != NULL);
    ASSERT(strstr(json, "\"embeds\"") != NULL);
    ASSERT(strstr(json, "\"title\":\"Title\"") != NULL);

    struct discord_create_message parsed = { 0 };
    ASSERT_EQ(CCORD_OK,
              discord_data_from_json(struct discord_create_message, tc.client,
                                     json, strlen(json), &parsed));
    ASSERT(parsed.embeds != NULL);
    ASSERT_EQ(1, parsed.embeds->size);
    ASSERT(parsed.embeds->array != NULL);
    ASSERT(parsed.embeds->array[0].title != NULL);
    ASSERT_STR_EQ("Title", parsed.embeds->array[0].title);

    discord_data_cleanup(tc.client, &parsed);
    discord_data_unwrap(tc.client, &message);
    free(json);
    dispose_test_client(&tc);
    PASS();
}

TEST
snowflakes_parse_numeric(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    const char *json = "[\"123\",\"456\"]";
    struct snowflakes parsed = { 0 };
    CCORDcode code = discord_data_from_json(struct snowflakes, tc.client, json,
                                            strlen(json), &parsed);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT_EQ(2, parsed.size);
    ASSERT(parsed.array != NULL);
    ASSERT_EQ(123, parsed.array[0]);
    ASSERT_EQ(456, parsed.array[1]);

    discord_data_cleanup(tc.client, &parsed);
    dispose_test_client(&tc);
    PASS();
}

TEST
snowflakes_parse_numeric_primitives(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    const char *json = "[1,2,3]";
    struct snowflakes parsed = { 0 };
    CCORDcode code = discord_data_from_json(struct snowflakes, tc.client, json,
                                            strlen(json), &parsed);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT_EQ(3, parsed.size);
    ASSERT(parsed.array != NULL);
    ASSERT_EQ(1, parsed.array[0]);
    ASSERT_EQ(2, parsed.array[1]);
    ASSERT_EQ(3, parsed.array[2]);

    discord_data_cleanup(tc.client, &parsed);
    dispose_test_client(&tc);
    PASS();
}

TEST
flags_parse_u64bitmask(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    const char *json = "{\"content\":\"x\",\"flags\":64}";
    struct discord_create_message parsed = { 0 };
    CCORDcode code = discord_data_from_json(
        struct discord_create_message, tc.client, json, strlen(json), &parsed);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT_EQ(DISCORD_MESSAGE_EPHEMERAL, parsed.flags);

    discord_data_cleanup(tc.client, &parsed);
    dispose_test_client(&tc);
    PASS();
}

TEST
snowflakes_preserve_order(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    const char *json = "[\"321\",\"123\",\"999\"]";
    struct snowflakes parsed = { 0 };
    CCORDcode code = discord_data_from_json(struct snowflakes, tc.client, json,
                                            strlen(json), &parsed);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT_EQ(3, parsed.size);
    ASSERT(parsed.array != NULL);
    ASSERT_EQ(321, parsed.array[0]);
    ASSERT_EQ(123, parsed.array[1]);
    ASSERT_EQ(999, parsed.array[2]);

    discord_data_cleanup(tc.client, &parsed);
    dispose_test_client(&tc);
    PASS();
}

TEST
components_empty_array(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    const char *json = "{\"content\":\"x\",\"components\":[]}";
    struct discord_create_message parsed = { 0 };
    CCORDcode code = discord_data_from_json(
        struct discord_create_message, tc.client, json, strlen(json), &parsed);
    if (code != CCORD_OK) {
        FAILm(discord_code_as_string(code));
    }
    ASSERT(parsed.components != NULL);
    ASSERT_EQ(0, parsed.components->size);

    discord_data_cleanup(tc.client, &parsed);
    dispose_test_client(&tc);
    PASS();
}

TEST
message_from_jsmnf_payload(void)
{
    struct test_client tc;
    init_test_client(&tc);
    ASSERT(tc.registry != NULL);

    const char *json =
        "{\"id\":\"1\",\"channel_id\":\"2\",\"content\":\"hi\"}";
    jsmnf_table *pairs = NULL;
    size_t pairs_len = 0;
    jsmnf_loader loader;
    jsmnf_init(&loader);
    ASSERT(jsmnf_load_auto(&loader, json, strlen(json), &pairs, &pairs_len)
           > 0);

    struct discord_message parsed = { 0 };
    struct discord_data_wrap *wrap =
        discord_data_wrap_from(struct discord_message, tc.client, &parsed);
    ASSERT_EQ(CCORD_OK, discord_data_wrap_from_jsmnf(loader.root, json,
                                                     strlen(json), wrap));

    ASSERT_EQ(2, parsed.channel_id);
    ASSERT(parsed.content != NULL);
    ASSERT_STR_EQ("hi", parsed.content);

    discord_data_cleanup(tc.client, &parsed);
    free(pairs);
    dispose_test_client(&tc);
    PASS();
}

SUITE(data_wrap_core)
{
    RUN_TEST(optional_bool_serialization);
    RUN_TEST(flags_parse_u64bitmask);
}

SUITE(data_wrap_arrays)
{
    RUN_TEST(to_json_roundtrip_components);
    RUN_TEST(strings_roundtrip);
    RUN_TEST(embeds_roundtrip);
    RUN_TEST(snowflakes_parse_numeric);
    RUN_TEST(snowflakes_parse_numeric_primitives);
    RUN_TEST(snowflakes_preserve_order);
    RUN_TEST(components_empty_array);
    RUN_TEST(message_from_jsmnf_payload);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    GREATEST_MAIN_BEGIN();
    RUN_SUITE(data_wrap_core);
    RUN_SUITE(data_wrap_arrays);
    GREATEST_MAIN_END();
}
