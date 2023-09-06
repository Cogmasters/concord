#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"
#include "queriec.h"

CCORDcode
discord_create_guild(struct discord *client,
                     struct discord_create_guild *params,
                     struct discord_ret_guild *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST, "/guilds");
}

CCORDcode
discord_get_guild(struct discord *client,
                  u64snowflake guild_id,
                  struct discord_ret_guild *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_guild, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64, guild_id);
}

CCORDcode
discord_get_guild_preview(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_ret_guild_preview *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_guild_preview, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/preview", guild_id);
}

CCORDcode
discord_modify_guild(struct discord *client,
                     u64snowflake guild_id,
                     struct discord_modify_guild *params,
                     struct discord_ret_guild *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64, guild_id);
}

CCORDcode
discord_delete_guild(struct discord *client,
                     u64snowflake guild_id,
                     struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64, guild_id);
}

CCORDcode
discord_get_guild_channels(struct discord *client,
                           u64snowflake guild_id,
                           struct discord_ret_channels *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_channels, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/channels", guild_id);
}

CCORDcode
discord_create_guild_channel(struct discord *client,
                             u64snowflake guild_id,
                             struct discord_create_guild_channel *params,
                             struct discord_ret_channel *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[2048];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_channel_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_channel, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/guilds/%" PRIu64 "/channels", guild_id);
}

CCORDcode
discord_modify_guild_channel_positions(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_guild_channel_positions *params,
    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_channel_positions_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/channels", guild_id);
}

CCORDcode
discord_get_guild_member(struct discord *client,
                         u64snowflake guild_id,
                         u64snowflake user_id,
                         struct discord_ret_guild_member *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                            user_id);
}

CCORDcode
discord_list_guild_members(struct discord *client,
                           u64snowflake guild_id,
                           struct discord_list_guild_members *params,
                           struct discord_ret_guild_members *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (params) {
        int res;

        char buf[32];
        if (params->limit) {
            res = queriec_snprintf_add(&queriec, query, "limit", sizeof("limit"),
                                       buf, sizeof(buf), "%d", params->limit);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
        if (params->after) {
            res = queriec_snprintf_add(&queriec, query, "after", sizeof("after"),
                                       buf, sizeof(buf), "%" PRIu64,
                                       params->after);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
    }

    DISCORD_ATTR_LIST_INIT(attr, discord_guild_members, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/members%s%s", guild_id,
                            query);
}

CCORDcode
discord_search_guild_members(struct discord *client,
                             u64snowflake guild_id,
                             struct discord_search_guild_members *params,
                             struct discord_ret_guild_members *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (params) {
        int res;

        char buf[32];
        if (params->query) {
            char *pe_query =
                curl_escape(params->query, (int)strlen(params->query));

            res = queriec_snprintf_add(&queriec, query, "query",
                                       sizeof("query"), buf, sizeof(buf), "%s",
                                       pe_query);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");

            curl_free(pe_query);
        }
        if (params->limit) {
            res = queriec_snprintf_add(&queriec, query, "limit", sizeof("limit"),
                                       buf, sizeof(buf), "%d", params->limit);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
    }

    DISCORD_ATTR_LIST_INIT(attr, discord_guild_members, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/members/search%s%s", guild_id,
                            query);
}

CCORDcode
discord_add_guild_member(struct discord *client,
                         u64snowflake guild_id,
                         u64snowflake user_id,
                         struct discord_add_guild_member *params,
                         struct discord_ret_guild_member *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->access_token != NULL, CCORD_BAD_PARAMETER,
                 "");

    body.size = discord_add_guild_member_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PUT,
                            "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                            user_id);
}

CCORDcode
discord_modify_guild_member(struct discord *client,
                            u64snowflake guild_id,
                            u64snowflake user_id,
                            struct discord_modify_guild_member *params,
                            struct discord_ret_guild_member *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[2048];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_member_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                            user_id);
}
CCORDcode
discord_modify_current_member(struct discord *client,
                              u64snowflake guild_id,
                              struct discord_modify_current_member *params,
                              struct discord_ret_guild_member *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[512];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->nick != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_modify_current_member_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/members/@me", guild_id);
}
CCORDcode
discord_modify_current_user_nick(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_current_user_nick *params,
    struct discord_ret_guild_member *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[512];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->nick != NULL, CCORD_BAD_PARAMETER, "");

    logconf_warn(&client->conf,
                 "This endpoint is now deprecated by Discord. Please use "
                 "discord_modify_current_member instead");

    body.size =
        discord_modify_current_user_nick_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/members/@me/nick", guild_id);
}

CCORDcode
discord_add_guild_member_role(struct discord *client,
                              u64snowflake guild_id,
                              u64snowflake user_id,
                              u64snowflake role_id,
                              struct discord_add_guild_member_role *params,
                              struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_PUT,
                            "/guilds/%" PRIu64 "/members/%" PRIu64
                            "/roles/%" PRIu64,
                            guild_id, user_id, role_id);
}

CCORDcode
discord_remove_guild_member_role(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake user_id,
    u64snowflake role_id,
    struct discord_remove_guild_member_role *params,
    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/members/%" PRIu64
                            "/roles/%" PRIu64,
                            guild_id, user_id, role_id);
}

CCORDcode
discord_remove_guild_member(struct discord *client,
                            u64snowflake guild_id,
                            u64snowflake user_id,
                            struct discord_remove_guild_member *params,
                            struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                            user_id);
}

CCORDcode
discord_get_guild_bans(struct discord *client,
                       u64snowflake guild_id,
                       struct discord_ret_bans *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_bans, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/bans", guild_id);
}

CCORDcode
discord_get_guild_ban(struct discord *client,
                      u64snowflake guild_id,
                      u64snowflake user_id,
                      struct discord_ret_ban *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_ban, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                            user_id);
}

CCORDcode
discord_create_guild_ban(struct discord *client,
                         u64snowflake guild_id,
                         u64snowflake user_id,
                         struct discord_create_guild_ban *params,
                         struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[256];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client,
                 params->delete_message_days >= 0
                     && params->delete_message_days <= 7,
                 CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_ban_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PUT,
                            "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                            user_id);
}
CCORDcode
discord_remove_guild_ban(struct discord *client,
                         u64snowflake guild_id,
                         u64snowflake user_id,
                         struct discord_remove_guild_ban *params,
                         struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                            user_id);
}

CCORDcode
discord_get_guild_roles(struct discord *client,
                        u64snowflake guild_id,
                        struct discord_ret_roles *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_roles, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/roles", guild_id);
}

CCORDcode
discord_create_guild_role(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_create_guild_role *params,
                          struct discord_ret_role *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_role_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_role, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/guilds/%" PRIu64 "/roles", guild_id);
}

CCORDcode
discord_modify_guild_role_positions(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_guild_role_positions *params,
    struct discord_ret_roles *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_modify_guild_role_positions_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_LIST_INIT(attr, discord_roles, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/roles", guild_id);
}

CCORDcode
discord_modify_guild_role(struct discord *client,
                          u64snowflake guild_id,
                          u64snowflake role_id,
                          struct discord_modify_guild_role *params,
                          struct discord_ret_role *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[2048];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_role_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_role, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                            role_id);
}

CCORDcode
discord_delete_guild_role(struct discord *client,
                          u64snowflake guild_id,
                          u64snowflake role_id,
                          struct discord_delete_guild_role *params,
                          struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                            role_id);
}

CCORDcode
discord_get_guild_prune_count(struct discord *client,
                              u64snowflake guild_id,
                              struct discord_get_guild_prune_count *params,
                              struct discord_ret_prune_count *ret)
{
    struct discord_attributes attr = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (params) {
        int res;

        char buf[1024];
        if (params->days) {
            res = queriec_snprintf_add(&queriec, query, "days", sizeof("days"),
                                       buf, sizeof(buf), "%d", params->days);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
        if (params->include_roles && params->include_roles->size) {
            char roles[1024];
            int i = 0, offset = 0;

            for (; i < params->include_roles->size - 1; ++i) {
                offset += snprintf(roles + offset, sizeof(roles) - (size_t)offset,
                                   "%" PRIu64 ",", params->include_roles->array[i]);
                ASSERT_NOT_OOB(offset, sizeof(roles));
            }
            offset += snprintf(roles + offset, sizeof(roles) - (size_t)offset,
                               "%" PRIu64 ",", params->include_roles->array[i]);
            ASSERT_NOT_OOB(offset, sizeof(roles));

            res = queriec_snprintf_add(&queriec, query, "include_roles",
                                       sizeof("include_roles"), roles,
                                       sizeof(roles), "%s", roles);
            ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
        }
    }

    DISCORD_ATTR_INIT(attr, discord_prune_count, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/prune%s%s", guild_id,
                            query);
}

CCORDcode
discord_begin_guild_prune(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_begin_guild_prune *params,
                          struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_begin_guild_prune_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/guilds/%" PRIu64 "/prune", guild_id);
}

CCORDcode
discord_get_guild_voice_regions(struct discord *client,
                                u64snowflake guild_id,
                                struct discord_ret_voice_regions *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_voice_regions, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/regions", guild_id);
}

CCORDcode
discord_get_guild_invites(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_ret_invites *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_invites, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/invites", guild_id);
}

CCORDcode
discord_get_guild_integrations(struct discord *client,
                               u64snowflake guild_id,
                               struct discord_ret_integrations *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_integrations, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/integrations", guild_id);
}

CCORDcode
discord_delete_guild_integrations(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake integration_id,
    struct discord_delete_guild_integrations *params,
    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, integration_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/integrations/%" PRIu64,
                            guild_id, integration_id);
}

CCORDcode
discord_get_guild_widget_settings(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_ret_guild_widget_settings *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_guild_widget_settings, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/widget", guild_id);
}

CCORDcode
discord_modify_guild_widget(struct discord *client,
                            u64snowflake guild_id,
                            struct discord_guild_widget_settings *params,
                            struct discord_ret_guild_widget_settings *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[512];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_guild_widget_settings_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild_widget_settings, ret,
                      params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/widget", guild_id);
}

CCORDcode
discord_get_guild_widget(struct discord *client,
                         u64snowflake guild_id,
                         struct discord_ret_guild_widget *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_guild_widget_settings, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/widget.json", guild_id);
}

CCORDcode
discord_get_guild_vanity_url(struct discord *client,
                             u64snowflake guild_id,
                             struct discord_ret_invite *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_invite, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/vanity-url", guild_id);
}

/* TODO: handle ContentType: image/png and add 'struct discord_png' */
#if 0
CCORDcode
discord_get_guild_widget_image(struct discord *client,
                               u64snowflake guild_id,
                               struct discord_get_guild_widget_image *params,
                               struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    char *query = (params && params->style) ? params->style : "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/widget.png%s%s", guild_id,
                            *query ? "?" : "", query);
}
#endif

CCORDcode
discord_get_guild_welcome_screen(struct discord *client,
                                 u64snowflake guild_id,
                                 struct discord_ret_welcome_screen *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_welcome_screen, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/welcome-screen", guild_id);
}

CCORDcode
discord_modify_guild_welcome_screen(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_guild_welcome_screen *params,
    struct discord_ret_welcome_screen *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_modify_guild_welcome_screen_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_welcome_screen, ret,
                      params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/welcome-screen", guild_id);
}

CCORDcode
discord_modify_current_user_voice_state(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_current_user_voice_state *params,
    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[512];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_current_user_voice_state_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/voice-states/@me", guild_id);
}

CCORDcode
discord_modify_user_voice_state(struct discord *client,
                                u64snowflake guild_id,
                                u64snowflake user_id,
                                struct discord_modify_user_voice_state *params,
                                struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[512];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_modify_user_voice_state_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/voice-states/%" PRIu64,
                            guild_id, user_id);
}
