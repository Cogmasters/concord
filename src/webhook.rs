#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"
#include "queriec.h"

CCORDcode
discord_create_webhook(struct discord *client,
                       u64snowflake channel_id,
                       struct discord_create_webhook *params,
                       struct discord_ret_webhook *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->name), CCORD_BAD_PARAMETER, "");

    body.size = discord_create_webhook_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_webhook, ret, params->reason);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_POST,
                            "/channels/%" PRIu64 "/webhooks", channel_id);
}

CCORDcode
discord_get_channel_webhooks(struct discord *client,
                             u64snowflake channel_id,
                             struct discord_ret_webhooks *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_webhooks, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/channels/%" PRIu64 "/webhooks", channel_id);
}

CCORDcode
discord_get_guild_webhooks(struct discord *client,
                           u64snowflake guild_id,
                           struct discord_ret_webhooks *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_LIST_INIT(attr, discord_webhooks, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/guilds/%" PRIu64 "/webhooks", guild_id);
}

CCORDcode
discord_get_webhook(struct discord *client,
                    u64snowflake webhook_id,
                    struct discord_ret_webhook *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_webhook, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/webhooks/%" PRIu64, webhook_id);
}

CCORDcode
discord_get_webhook_with_token(struct discord *client,
                               u64snowflake webhook_id,
                               const char webhook_token[],
                               struct discord_ret_webhook *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_INIT(attr, discord_webhook, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/webhooks/%" PRIu64 "/%s", webhook_id,
                            webhook_token);
}

CCORDcode
discord_modify_webhook(struct discord *client,
                       u64snowflake webhook_id,
                       struct discord_modify_webhook *params,
                       struct discord_ret_webhook *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_webhook_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_webhook, ret,
                      params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
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
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    char buf[1024];

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");

    body.size =
        discord_modify_webhook_with_token_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_webhook, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, HTTP_PATCH,
                            "/webhooks/%" PRIu64 "/%s", webhook_id,
                            webhook_token);
}

CCORDcode
discord_delete_webhook(struct discord *client,
                       u64snowflake webhook_id,
                       struct discord_delete_webhook *params,
                       struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, params ? params->reason : NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/webhooks/%" PRIu64, webhook_id);
}

CCORDcode
discord_delete_webhook_with_token(struct discord *client,
                                  u64snowflake webhook_id,
                                  const char webhook_token[],
                                  struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
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
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */
    char query[4096] = "";
    char qbuf[32];
    int res;

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    struct queriec queriec;
    queriec_init(&queriec, sizeof(query));

    if (params->wait) {
        res = queriec_add(&queriec, query, "wait", sizeof("wait"), "1", 1);
        ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
    }
    if (params->thread_id) {
        res = queriec_snprintf_add(&queriec, query, "thread_id", sizeof("thread_id"),
                                       qbuf, sizeof(qbuf), "%" PRIu64, params->thread_id);
        ASSERT_S(res != QUERIEC_ERROR_NOMEM, "Out of bounds write attempt");
    }

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        DISCORD_ATTACHMENTS_IDS_INIT(params->attachments);
        attr.attachments = *params->attachments;
    }
    else {
        method = HTTP_POST;
    }

    body.size = discord_execute_webhook_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, method,
                            "/webhooks/%" PRIu64 "/%s%s%s", webhook_id,
                            webhook_token, query);
}

CCORDcode
discord_get_webhook_message(struct discord *client,
                            u64snowflake webhook_id,
                            const char webhook_token[],
                            u64snowflake message_id,
                            struct discord_ret_message *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_message, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
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
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        DISCORD_ATTACHMENTS_IDS_INIT(params->attachments);
        attr.attachments = *params->attachments;
    }
    else {
        method = HTTP_PATCH;
    }

    body.size = discord_edit_webhook_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    DISCORD_ATTR_INIT(attr, discord_message, ret, NULL);

    return discord_rest_run(&client->rest, &attr, &body, method,
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
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, webhook_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(webhook_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret, NULL);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                            webhook_id, webhook_token, message_id);
}
