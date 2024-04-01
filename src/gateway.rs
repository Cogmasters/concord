#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

/******************************************************************************
 * Custom functions
 ******************************************************************************/

CCORDcode
discord_disconnect_guild_member(struct discord *client,
                                u64snowflake guild_id,
                                u64snowflake user_id,
                                struct discord_modify_guild_member *params,
                                struct discord_ret_guild_member *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[128];
    jsonb b;

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    jsonb_init(&b);
    jsonb_object(&b, buf, sizeof(buf));
    {
        jsonb_key(&b, buf, sizeof(buf), "channel_id",
                  sizeof("channel_id") - 1);
        jsonb_null(&b, buf, sizeof(buf));
        jsonb_object_pop(&b, buf, sizeof(buf));
    }

    body.start = buf;
    body.size = b.pos;

    DISCORD_ATTR_INIT(attr, discord_guild_member, ret,
                      params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                            user_id);
}

/******************************************************************************
 * REST functions
 ******************************************************************************/

static size_t
_ccord_szbuf_from_json(const char str[], size_t len, void *p_buf)
{
    struct ccord_szbuf *buf = p_buf;
    return buf->size = cog_strndup(str, len, &buf->start);
}

CCORDcode
discord_get_gateway(struct discord *client, struct ccord_szbuf *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, ret != NULL, CCORD_BAD_PARAMETER, "");

    attr.response.from_json = &_ccord_szbuf_from_json;
    attr.dispatch.has_type = true;
    attr.dispatch.sync = ret;

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET, "/gateway");
}

CCORDcode
discord_get_gateway_bot(struct discord *client, struct ccord_szbuf *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, ret != NULL, CCORD_BAD_PARAMETER, "");

    attr.response.from_json = &_ccord_szbuf_from_json;
    attr.dispatch.has_type = true;
    attr.dispatch.sync = ret;

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/gateway/bot");
}
