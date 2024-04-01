#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_list_auto_moderation_rules_for_guild(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_ret_auto_moderation_rules *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_auto_moderation_rules, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/auto-moderation/rules",
                            guild_id);
}

CCORDcode
discord_get_auto_moderation_rule(struct discord *client,
                                 u64snowflake guild_id,
                                 u64snowflake auto_moderation_rule_id,
                                 struct discord_ret_auto_moderation_rule *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, auto_moderation_rule_id != 0, CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_INIT(attr, discord_auto_moderation_rule, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64
                            "/auto-moderation/rules/%" PRIu64,
                            guild_id, auto_moderation_rule_id);
}

CCORDcode
discord_create_auto_moderation_rule(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_create_auto_moderation_rule *params,
    struct discord_ret_auto_moderation_rule *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->name), CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->event_type != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->trigger_type != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->actions != NULL, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_auto_moderation_rule, ret, params->reason);

    body.size =
        discord_create_auto_moderation_rule_to_json(buf, sizeof(buf), params);
    body.start = buf;

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/guilds/%" PRIu64 "/auto-moderation/rules",
                            guild_id);
}

CCORDcode
discord_modify_auto_moderation_rule(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake auto_moderation_rule_id,
    struct discord_modify_auto_moderation_rule *params,
    struct discord_ret_auto_moderation_rule *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, auto_moderation_rule_id != 0, CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->name), CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->event_type != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->actions != NULL, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_auto_moderation_rule, ret, params->reason);

    body.size =
        discord_modify_auto_moderation_rule_to_json(buf, sizeof(buf), params);
    body.start = buf;

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64
                            "/auto-moderation/rules/%" PRIu64,
                            guild_id, auto_moderation_rule_id);
}

CCORDcode
discord_delete_auto_moderation_rule(
    struct discord *client,
    u64snowflake guild_id,
    u64snowflake auto_moderation_rule_id,
    struct discord_delete_auto_moderation_rule *params,
    struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, auto_moderation_rule_id != 0, CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64
                            "/auto-moderation/rules/%" PRIu64,
                            guild_id, auto_moderation_rule_id);
}
