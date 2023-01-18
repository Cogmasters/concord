/* TODO: should be able to disable gateway from discord_run() */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "discord.h"

#include "greatest.h"

static struct discord *CLIENT;

TEST
check_sync_fetch_object(void)
{
    struct discord_ret_user ret = { 0 };
    struct discord_user bot;

    discord_user_init(&bot);

    ret.sync = &bot;
    ASSERT_EQ(CCORD_OK, discord_get_current_user(CLIENT, &ret));
    discord_user_cleanup(&bot);

    ret.sync = DISCORD_SYNC_FLAG;
    ASSERT_EQ(CCORD_OK, discord_get_current_user(CLIENT, &ret));

    PASS();
}

TEST
check_sync_fetch_array(void)
{
    struct discord_ret_guilds ret = { 0 };
    struct discord_guilds guilds = { 0 };

    ret.sync = &guilds;
    ASSERT_EQ(CCORD_OK, discord_get_current_user_guilds(CLIENT, &ret));
    discord_guilds_cleanup(&guilds);

    ret.sync = DISCORD_SYNC_FLAG;
    ASSERT_EQ(CCORD_OK, discord_get_current_user_guilds(CLIENT, &ret));

    PASS();
}

TEST
check_sync_fetch_nothing(void *data)
{
    u64snowflake ch_id = *(u64snowflake *)data;
    struct discord_ret ret = { 0 };

    if (!ch_id) SKIPm("Missing channel_id from config.json");

    ret.sync = true;
    ASSERT_EQ(CCORD_OK, discord_trigger_typing_indicator(CLIENT, ch_id, &ret));

    PASS();
}

TEST
check_sync_trigger_error_on_bogus_parameter(void)
{
    const u64snowflake BOGUS_ID = 123;
    struct discord_ret_channel ret = { 0 };

    ret.sync = DISCORD_SYNC_FLAG;
    ASSERT_NEQ(CCORD_OK, discord_delete_channel(CLIENT, BOGUS_ID, NULL, &ret));

    PASS();
}

SUITE(synchronous)
{
    char *path[] = { "test", "channel_id" };

    /* get test-channel id */
    struct ccord_szbuf_readonly json =
        discord_config_get_field(CLIENT, path, 2);
    u64snowflake channel_id = strtoull(json.start, NULL, 10);

    RUN_TEST(check_sync_fetch_object);
    RUN_TEST(check_sync_fetch_array);
    RUN_TEST1(check_sync_fetch_nothing, &channel_id);
    RUN_TEST(check_sync_trigger_error_on_bogus_parameter);
}

void
on_done(struct discord *client, struct discord_response *resp)
{
    *(CCORDcode *)resp->data = resp->code;
    discord_shutdown(client);
}

void
on_done1(struct discord *client,
         struct discord_response *resp,
         const void *obj)
{
    (void)obj;
    on_done(client, resp);
}

#define DONE1_CAST(_type)                                                     \
    void (*)(struct discord *, struct discord_response *, const _type *)

TEST
check_async_fetch_object(void)
{
    struct discord_ret_user ret = { 0 };
    CCORDcode result = CCORD_OK;

    ret.done = (DONE1_CAST(struct discord_user))on_done1;
    ret.fail = on_done;
    ret.data = &result;
    discord_get_current_user(CLIENT, &ret);

    discord_run(CLIENT);
    ASSERT_EQ(CCORD_OK, result);

    PASS();
}

TEST
check_async_fetch_array(void)
{
    struct discord_ret_guilds ret = { 0 };
    CCORDcode result = CCORD_OK;

    ret.done = (DONE1_CAST(struct discord_guilds))on_done1;
    ret.fail = on_done;
    ret.data = &result;
    discord_get_current_user_guilds(CLIENT, &ret);

    discord_run(CLIENT);
    ASSERT_EQ(CCORD_OK, result);

    PASS();
}

TEST
check_async_fetch_nothing(void *data)
{
    u64snowflake ch_id = *(u64snowflake *)data;
    struct discord_ret ret = { 0 };
    CCORDcode result = CCORD_OK;

    if (!ch_id) SKIPm("Missing channel_id from config.json");

    ret.fail = ret.done = on_done;
    ret.data = &result;
    discord_trigger_typing_indicator(CLIENT, ch_id, &ret);

    discord_run(CLIENT);
    ASSERT_EQ(CCORD_OK, result);

    PASS();
}

TEST
check_async_trigger_error_on_bogus_parameter(void)
{
    const u64snowflake BOGUS_ID = 123;
    struct discord_ret_channel ret = { 0 };
    CCORDcode result = CCORD_OK;

    ret.done = (DONE1_CAST(struct discord_channel))on_done1;
    ret.fail = on_done;
    ret.data = &result;
    discord_delete_channel(CLIENT, BOGUS_ID, NULL, &ret);

    discord_run(CLIENT);
    ASSERT_NEQ(CCORD_OK, result);

    PASS();
}

SUITE(asynchronous)
{
    char *path[] = { "test", "channel_id" };

    /* get test-channel id */
    struct ccord_szbuf_readonly json =
        discord_config_get_field(CLIENT, path, 2);
    u64snowflake channel_id = strtoull(json.start, NULL, 10);

    RUN_TEST(check_async_fetch_object);
    RUN_TEST(check_async_fetch_array);
    RUN_TEST1(check_async_fetch_nothing, &channel_id);
    RUN_TEST(check_async_trigger_error_on_bogus_parameter);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    ccord_global_init();
    CLIENT = discord_config_init("test_config.json");
    assert(CLIENT != NULL && "Couldn't initialize client");

    RUN_SUITE(synchronous);
    RUN_SUITE(asynchronous);

    discord_cleanup(CLIENT);
    ccord_global_cleanup();
    GREATEST_MAIN_END();
}
