#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_list_guild_scheduled_events(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_list_guild_scheduled_events *params,
    struct discord_ret_guild_scheduled_events *ret)
{
    struct discord_attributes attr = { 0 };
    const char *query =
        (params && params->with_user_count) ? "?with_user_count=1" : "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_guild_scheduled_events, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/scheduled-events%s", guild_id,
                            query);
}

CCORDcode
discord_create_guild_scheduled_event(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_create_guild_scheduled_event *params,
    struct discord_ret_guild_scheduled_event *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->name), CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->privacy_level != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->scheduled_start_time != 0,
                 CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->entity_type != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_guild_scheduled_event, ret);

    body.size =
        discord_create_guild_scheduled_event_to_json(buf, sizeof(buf), params);
    body.start = buf;

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/guilds/%" PRIu64 "/scheduled-events", guild_id);
}

CCORDcode
discord_get_guild_scheduled_event(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake guild_scheduled_event_id,
    struct discord_get_guild_scheduled_event *params,
    struct discord_ret_guild_scheduled_event *ret)
{
    struct discord_attributes attr = { 0 };
    const char *query =
        (params && params->with_user_count) ? "?with_user_count=1" : "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_scheduled_event_id != 0, CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_INIT(attr, discord_guild_scheduled_event, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/scheduled-events/%" PRIu64
                            "/%s",
                            guild_id, guild_scheduled_event_id, query);
}

CCORDcode
discord_modify_guild_scheduled_event(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake guild_scheduled_event_id,
    struct discord_modify_guild_scheduled_event *params,
    struct discord_ret_guild_scheduled_event *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_scheduled_event_id != 0, CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_INIT(attr, discord_guild_scheduled_event, ret);

    body.size =
        discord_modify_guild_scheduled_event_to_json(buf, sizeof(buf), params);
    body.start = buf;

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/scheduled-events/%" PRIu64,
                            guild_id, guild_scheduled_event_id);
}

CCORDcode
discord_delete_guild_scheduled_event(struct discord *client,
                                     u64snowflake guild_id,
                                     u64snowflake guild_scheduled_event_id,
                                     struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_scheduled_event_id != 0, CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/scheduled-events/%" PRIu64,
                            guild_id, guild_scheduled_event_id);
}

CCORDcode
discord_get_guild_scheduled_event_users(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake guild_scheduled_event_id,
    struct discord_get_guild_scheduled_event_users *params,
    struct discord_ret_guild_scheduled_event_users *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_scheduled_event_id != 0, CCORD_BAD_PARAMETER,
                 "");

    if (params) {
        int offset = 0;

        if (params->limit) {
            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "limit=%d", params->limit);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
        if (params->with_member) {
            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "%swith_member=%d", *query ? "&" : "",
                               params->with_member);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
        if (params->before) {
            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "%sbefore=%" PRIu64, *query ? "&" : "",
                               params->before);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
        if (params->after) {
            offset +=
                snprintf(query + offset, sizeof(query) - (size_t)offset,
                         "%safter=%" PRIu64, *query ? "&" : "", params->after);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
    }

    DISCORD_ATTR_LIST_INIT(attr, discord_guild_scheduled_event_users, ret);

    return discord_rest_run(
        &client->rest, &attr, NULL, HTTP_GET,
        "/guilds/%" PRIu64 "/scheduled-events/%" PRIu64 "/users%s%s", guild_id,
        guild_scheduled_event_id, *query ? "?" : "", query);
}
