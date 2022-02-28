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
                                struct discord_ret_guild_member *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
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

    DISCORD_REQ_INIT(req, discord_guild_member, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64 "/members/%" PRIu64,
                               guild_id, user_id);
}

/******************************************************************************
 * REST functions
 ******************************************************************************/

CCORDcode
discord_get_gateway(struct discord *client, struct sized_buffer *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, ret != NULL, CCORD_BAD_PARAMETER, "");

    req.gnrc.from_json =
        (size_t(*)(const char *, size_t, void *))cog_sized_buffer_from_json;
    req.ret.has_type = true;
    req.ret.sync = ret;

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/gateway");
}

CCORDcode
discord_get_gateway_bot(struct discord *client, struct sized_buffer *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, ret != NULL, CCORD_BAD_PARAMETER, "");

    req.gnrc.from_json =
        (size_t(*)(const char *, size_t, void *))cog_sized_buffer_from_json;
    req.ret.has_type = true;
    req.ret.sync = ret;

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/gateway/bot");
}
