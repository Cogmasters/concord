#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_get_guild_template(struct discord *client,
                           const char template_code[],
                           struct discord_ret_guild_template *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, NOT_EMPTY_STR(template_code), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_INIT(attr, discord_guild_template, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/templates/%s", template_code);
}

CCORDcode
discord_create_guild_from_guild_template(
    struct discord *client,
    const char template_code[],
    struct discord_create_guild_from_guild_template *params,
    struct discord_ret_guild *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[256] = { 0 };

    CCORD_EXPECT(client, NOT_EMPTY_STR(template_code), CCORD_BAD_PARAMETER,
                 "");

    body.size = discord_create_guild_from_guild_template_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/guilds/templates/%s", template_code);
}

CCORDcode
discord_get_guild_templates(struct discord *client,
                            u64snowflake guild_id,
                            struct discord_ret_guild_templates *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_guild_templates, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/templates", guild_id);
}

CCORDcode
discord_create_guild_template(struct discord *client,
                              u64snowflake guild_id,
                              struct discord_create_guild_template *params,
                              struct discord_ret_guild_template *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[256];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_create_guild_template_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild_template, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/guilds/%" PRIu64 "/templates", guild_id);
}

CCORDcode
discord_sync_guild_template(struct discord *client,
                            u64snowflake guild_id,
                            const char template_code[],
                            struct discord_ret_guild_template *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(template_code), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_INIT(attr, discord_guild_template, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_PUT,
                            "/guilds/%" PRIu64 "/templates/%s", guild_id,
                            template_code);
}

CCORDcode
discord_modify_guild_template(struct discord *client,
                              u64snowflake guild_id,
                              const char template_code[],
                              struct discord_modify_guild_template *params,
                              struct discord_ret_guild_template *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024] = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(template_code), CCORD_BAD_PARAMETER,
                 "");

    body.size =
        discord_modify_guild_template_from_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_guild_template, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/templates/%s", guild_id,
                            template_code);
}

CCORDcode
discord_delete_guild_template(struct discord *client,
                              u64snowflake guild_id,
                              const char template_code[],
                              struct discord_ret_guild_template *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(template_code), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_INIT(attr, discord_guild_template, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/templates/%s", guild_id,
                            template_code);
}
