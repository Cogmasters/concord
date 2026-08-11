#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"
#include "queriec.h"

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
    DISCORD_ATTR_LIST_INIT(attr, discord_guild_scheduled_events, ret, NULL);
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
    struct ccord_szbuf body = { 0 };
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->name), CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->privacy_level != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->scheduled_start_time != 0,
                 CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->entity_type != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT_OK(client, discord_create_guild_scheduled_event_to_json(
                                &body.start, &body.size, params));
    DISCORD_ATTR_INIT(attr, discord_guild_scheduled_event, ret,
                      params->reason);
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
    DISCORD_ATTR_INIT(attr, discord_guild_scheduled_event, ret, NULL);
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
    struct ccord_szbuf body = { 0 };
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_scheduled_event_id != 0, CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT_OK(client, discord_modify_guild_scheduled_event_to_json(
                                &body.start, &body.size, params));
    DISCORD_ATTR_INIT(attr, discord_guild_scheduled_event, ret,
                      params ? params->reason : NULL);
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
    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);
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
    struct queriec queriec;
    char query[1024] = "";
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_scheduled_event_id != 0, CCORD_BAD_PARAMETER,
                 "");
    DISCORD_ATTR_LIST_INIT(attr, discord_guild_scheduled_event_users, ret,
                           NULL);
    queriec_init(&queriec, sizeof(query));
    if (params) {
        int res;
        char buf[32];
        if (params->limit) {
            res =
                queriec_snprintf_add(&queriec, query, "limit", sizeof("limit"),
                                     buf, sizeof(buf), "%d", params->limit);
            CCORD_EXPECT(client, res != QUERIEC_ERROR_NOMEM,
                         CCORD_MALFORMED_PAYLOAD,
                         "Out of bounds write attempt");
        }
        if (params->with_member) {
            res = queriec_snprintf_add(&queriec, query, "with_member",
                                       sizeof("with_member"), buf, sizeof(buf),
                                       "%d", params->with_member);
            CCORD_EXPECT(client, res != QUERIEC_ERROR_NOMEM,
                         CCORD_MALFORMED_PAYLOAD,
                         "Out of bounds write attempt");
        }
        if (params->before) {
            res = queriec_snprintf_add(&queriec, query, "before",
                                       sizeof("before"), buf, sizeof(buf),
                                       "%" PRIu64, params->before);
            CCORD_EXPECT(client, res != QUERIEC_ERROR_NOMEM,
                         CCORD_MALFORMED_PAYLOAD,
                         "Out of bounds write attempt");
        }
        if (params->after) {
            res = queriec_snprintf_add(&queriec, query, "after",
                                       sizeof("after"), buf, sizeof(buf),
                                       "%" PRIu64, params->after);
            CCORD_EXPECT(client, res != QUERIEC_ERROR_NOMEM,
                         CCORD_MALFORMED_PAYLOAD,
                         "Out of bounds write attempt");
        }
    }
    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/scheduled-events/%" PRIu64
                            "/users%s",
                            guild_id, guild_scheduled_event_id, query);
}
