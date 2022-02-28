#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_create_webhook(struct discord *client,
                       u64snowflake channel_id,
                       struct discord_create_webhook *params,
                       struct discord_ret_webhook *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->name), CCORD_BAD_PARAMETER, "");

    body.size = discord_create_webhook_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_REQ_INIT(req, discord_webhook, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/channels/%" PRIu64 "/webhooks", channel_id);
}

CCORDcode
discord_get_channel_webhooks(struct discord *client,
                             u64snowflake channel_id,
                             struct discord_ret_webhooks *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_REQ_LIST_INIT(req, discord_webhooks, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64 "/webhooks", channel_id);
}

CCORDcode
discord_get_guild_webhooks(struct discord *client,
                           u64snowflake guild_id,
                           struct discord_ret_webhooks *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_REQ_LIST_INIT(req, discord_webhooks, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/webhooks", guild_id);
}

CCORDcode
discord_get_webhook(struct discord *client,
                    u64snowflake webhook_id,
                    struct discord_ret_webhook *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_REQ_INIT(req, discord_webhook, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/webhooks/%" PRIu64, webhook_id);
}

CCORDcode
discord_get_webhook_with_token(struct discord *client,
                               u64snowflake webhook_id,
                               const char webhook_token[],
                               struct discord_ret_webhook *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_REQ_INIT(req, discord_webhook, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/webhooks/%" PRIu64 "/%s", webhook_id,
                               webhook_token);
}

CCORDcode
discord_modify_webhook(struct discord *client,
                       u64snowflake webhook_id,
                       struct discord_modify_webhook *params,
                       struct discord_ret_webhook *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_webhook_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_REQ_INIT(req, discord_webhook, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/webhooks/%" PRIu64, webhook_id);
}

CCORDcode
discord_modify_webhook_with_token(
    struct discord *client,
    u64snowflake webhook_id,
    const char webhook_token[],
    struct discord_modify_webhook_with_token *params,
    struct discord_ret_webhook *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");

    body.size =
        discord_modify_webhook_with_token_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_REQ_INIT(req, discord_webhook, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/webhooks/%" PRIu64 "/%s", webhook_id,
                               webhook_token);
}

CCORDcode
discord_delete_webhook(struct discord *client,
                       u64snowflake webhook_id,
                       struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_REQ_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/webhooks/%" PRIu64, webhook_id);
}

CCORDcode
discord_delete_webhook_with_token(struct discord *client,
                                  u64snowflake webhook_id,
                                  const char webhook_token[],
                                  struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_REQ_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/webhooks/%" PRIu64 "/%s", webhook_id,
                               webhook_token);
}

CCORDcode
discord_execute_webhook(struct discord *client,
                        u64snowflake webhook_id,
                        const char webhook_token[],
                        struct discord_execute_webhook *params,
                        struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */
    char query[4096] = "";
    size_t len = 0;

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    if (params->wait) {
        len = snprintf(query, sizeof(query), "wait=1");
        ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
    }
    if (params->thread_id) {
        len +=
            snprintf(query + len, sizeof(query) - len, "%sthread_id=%" PRIu64,
                     len ? "&" : "", params->thread_id);
        ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
    }

    body.size = discord_execute_webhook_to_json(buf, sizeof(buf), params);
    body.start = buf;

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        req.attachments = *params->attachments;
    }
    else {
        method = HTTP_POST;
    }

    DISCORD_REQ_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, &body, method,
                               "/webhooks/%" PRIu64 "/%s%s%s", webhook_id,
                               webhook_token, *query ? "?" : "", query);
}

CCORDcode
discord_get_webhook_message(struct discord *client,
                            u64snowflake webhook_id,
                            const char webhook_token[],
                            u64snowflake message_id,
                            struct discord_ret_message *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_REQ_INIT(req, discord_message, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/webhooks/%" PRIu64 "/%s/%" PRIu64, webhook_id,
                               webhook_token, message_id);
}

CCORDcode
discord_edit_webhook_message(struct discord *client,
                             u64snowflake webhook_id,
                             const char webhook_token[],
                             u64snowflake message_id,
                             struct discord_edit_webhook_message *params,
                             struct discord_ret_message *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_edit_webhook_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        req.attachments = *params->attachments;
    }
    else {
        method = HTTP_PATCH;
    }

    DISCORD_REQ_INIT(req, discord_message, ret);

    return discord_adapter_run(&client->adapter, &req, &body, method,
                               "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                               webhook_id, webhook_token, message_id);
}

CCORDcode
discord_delete_webhook_message(struct discord *client,
                               u64snowflake webhook_id,
                               const char webhook_token[],
                               u64snowflake message_id,
                               struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_REQ_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                               webhook_id, webhook_token, message_id);
}

/******************************************************************************
 * Miscellaneous
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

struct _discord_get_channel_at_pos_cxt {
    enum discord_channel_types type;
    int position;
    struct discord_ret_channel ret;
};

/* XXX: placeholder until channel is obtained via cache at
 *      discord-get_channel_at_pos() */
static void
_done_get_channels(struct discord *client,
                   void *data,
                   const struct discord_channels *chs)
{
    struct _discord_get_channel_at_pos_cxt *cxt = data;

    const struct discord_channel *found_ch = NULL;
    int i, pos; /* calculate position */

    for (i = 0, pos = 0; i < chs->size; ++i) {
        if (cxt->type == chs->array[i].type && pos++ == cxt->position) {
            found_ch = &chs->array[i];
            break;
        }
    }

    /* TODO: the following should be replaced by a discord_set_timeout()
     * implementation */
    if (found_ch) {
        if (cxt->ret.done) cxt->ret.done(client, cxt->ret.data, found_ch);
    }
    else if (cxt->ret.fail) {
        cxt->ret.fail(client, CCORD_BAD_PARAMETER, cxt->ret.data);
    }

    discord_refcount_decr(&client->adapter, cxt->ret.data);
}

CCORDcode
discord_get_channel_at_pos(struct discord *client,
                           u64snowflake guild_id,
                           enum discord_channel_types type,
                           int position,
                           struct discord_ret_channel *ret)
{
    struct _discord_get_channel_at_pos_cxt *cxt;
    struct discord_ret_channels _ret = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, ret != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, ret->done != NULL, CCORD_BAD_PARAMETER, "");

    cxt = malloc(sizeof *cxt);
    cxt->type = type;
    cxt->position = position;
    cxt->ret = *ret;

    _ret.done = &_done_get_channels;
    _ret.fail = ret->fail;
    _ret.data = cxt;
    _ret.cleanup = &free;

    /* TODO: the following should be replaced by a discord_set_timeout()
     * implementation */
    if (ret->data) {
        discord_refcount_incr(&client->adapter, ret->data, ret->cleanup);
    }

    /* TODO: fetch channel via caching, and return if results are non-existent
     */
    return discord_get_guild_channels(client, guild_id, &_ret);
}
