#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

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

    DISCORD_ATTR_INIT(attr, discord_guild, ret);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST, "/guilds");
}

CCORDcode
discord_get_guild(struct discord *client,
                  u64snowflake guild_id,
                  struct discord_ret_guild *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_guild, ret);

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

    DISCORD_ATTR_INIT(attr, discord_guild_preview, ret);

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

    DISCORD_ATTR_INIT(attr, discord_guild, ret);

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

    DISCORD_ATTR_BLANK_INIT(attr, ret);

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

    DISCORD_ATTR_LIST_INIT(attr, discord_channels, ret);

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

    DISCORD_ATTR_INIT(attr, discord_channel, ret);

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

    DISCORD_ATTR_BLANK_INIT(attr, ret);

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

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret);

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

    if (params) {
        int offset = 0;

        if (params->limit) {
            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "limit=%d", params->limit);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
        if (params->after) {
            offset +=
                snprintf(query + offset, sizeof(query) - (size_t)offset,
                         "%safter=%" PRIu64, *query ? "&" : "", params->after);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
    }

    DISCORD_ATTR_LIST_INIT(attr, discord_guild_members, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/members%s%s", guild_id,
                            *query ? "?" : "", query);
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

    if (params) {
        int offset = 0;

        if (params->query) {
            char *pe_query =
                curl_escape(params->query, (int)strlen(params->query));

            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "query=%s", pe_query);
            ASSERT_NOT_OOB(offset, sizeof(query));

            curl_free(pe_query);
        }
        if (params->limit) {
            offset += snprintf(query + offset, sizeof(query) - (size_t)offset,
                               "%slimit=%d", *query ? "&" : "", params->limit);
            ASSERT_NOT_OOB(offset, sizeof(query));
        }
    }

    DISCORD_ATTR_LIST_INIT(attr, discord_guild_members, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/members/search%s%s", guild_id,
                            *query ? "?" : "", query);
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

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret);

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

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret);

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

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret);

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

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/members/@me/nick", guild_id);
}

CCORDcode
discord_add_guild_member_role(struct discord *client,
                              u64snowflake guild_id,
                              u64snowflake user_id,
                              u64snowflake role_id,
                              struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_PUT,
                            "/guilds/%" PRIu64 "/members/%" PRIu64
                            "/roles/%" PRIu64,
                            guild_id, user_id, role_id);
}

CCORDcode
discord_remove_guild_member_role(struct discord *client,
                                 u64snowflake guild_id,
                                 u64snowflake user_id,
                                 u64snowflake role_id,
                                 struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/members/%" PRIu64
                            "/roles/%" PRIu64,
                            guild_id, user_id, role_id);
}

CCORDcode
discord_remove_guild_member(struct discord *client,
                            u64snowflake guild_id,
                            u64snowflake user_id,
                            struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

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

    DISCORD_ATTR_LIST_INIT(attr, discord_bans, ret);

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

    DISCORD_ATTR_INIT(attr, discord_ban, ret);

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

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PUT,
                            "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                            user_id);
}
CCORDcode
discord_remove_guild_ban(struct discord *client,
                         u64snowflake guild_id,
                         u64snowflake user_id,
                         struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

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

    DISCORD_ATTR_LIST_INIT(attr, discord_roles, ret);

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

    DISCORD_ATTR_INIT(attr, discord_role, ret);

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

    DISCORD_ATTR_LIST_INIT(attr, discord_roles, ret);

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
    char buf[2048] = "{}";
    size_t len = 2;

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    if (params)
        len = discord_modify_guild_role_to_json(buf, sizeof(buf), params);

    body.size = len;
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_role, ret);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                            role_id);
}

CCORDcode
discord_delete_guild_role(struct discord *client,
                          u64snowflake guild_id,
                          u64snowflake role_id,
                          struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                            role_id);
}

CCORDcode
discord_begin_guild_prune(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_begin_guild_prune *params,
                          struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096] = "{}";
    size_t len = 2;

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    if (params)
        len = discord_begin_guild_prune_to_json(buf, sizeof(buf), params);

    body.size = len;
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/guilds/%" PRIu64 "/prune", guild_id);
}

CCORDcode
discord_get_guild_invites(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_ret_invites *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_invites, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/invites", guild_id);
}

CCORDcode
discord_delete_guild_integrations(struct discord *client,
                                  u64snowflake guild_id,
                                  u64snowflake integration_id,
                                  struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, integration_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/integrations/%" PRIu64,
                            guild_id, integration_id);
}

CCORDcode
discord_get_guild_vanity_url(struct discord *client,
                             u64snowflake guild_id,
                             struct discord_ret_invite *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_invite, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/vanity-url", guild_id);
}

CCORDcode
discord_get_guild_welcome_screen(struct discord *client,
                                 u64snowflake guild_id,
                                 struct discord_ret_welcome_screen *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_welcome_screen, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/welcome-screen", guild_id);
}
