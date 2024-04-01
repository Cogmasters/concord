#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

/******************************************************************************
 * REST functions
 ******************************************************************************/

CCORDcode
discord_get_sticker(struct discord *client,
                    u64snowflake sticker_id,
                    struct discord_ret_sticker *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, sticker_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_sticker, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/stickers/%" PRIu64, sticker_id);
}

CCORDcode
discord_list_nitro_sticker_packs(
    struct discord *client, struct discord_ret_list_nitro_sticker_packs *ret)
{
    struct discord_attributes attr = { 0 };

    DISCORD_ATTR_INIT(attr, discord_list_nitro_sticker_packs, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/sticker-packs");
}

CCORDcode
discord_list_guild_stickers(struct discord *client,
                            u64snowflake guild_id,
                            struct discord_ret_stickers *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_stickers, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/stickers", guild_id);
}

CCORDcode
discord_get_guild_sticker(struct discord *client,
                          u64snowflake guild_id,
                          u64snowflake sticker_id,
                          struct discord_ret_sticker *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, sticker_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_sticker, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/stickers/%" PRIu64, guild_id,
                            sticker_id);
}

CCORDcode
discord_modify_guild_sticker(struct discord *client,
                             u64snowflake guild_id,
                             u64snowflake sticker_id,
                             struct discord_modify_guild_sticker *params,
                             struct discord_ret_sticker *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, sticker_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_sticker_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_sticker, ret,
                      params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/stickers/%" PRIu64, guild_id,
                            sticker_id);
}

CCORDcode
discord_delete_guild_sticker(struct discord *client,
                             u64snowflake guild_id,
                             u64snowflake sticker_id,
                             struct discord_delete_guild_sticker *params,
                             struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, sticker_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/guilds/%" PRIu64 "/stickers/%" PRIu64, guild_id,
                            sticker_id);
}
