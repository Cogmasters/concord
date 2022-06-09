#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_create_interaction_response(
    struct discord *client,
    u64snowflake interaction_id,
    const char interaction_token[],
    struct discord_interaction_response *params,
    struct discord_ret_interaction_response *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    enum http_method method;
    char buf[4096];

    CCORD_EXPECT(client, interaction_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_interaction_response_to_json(buf, sizeof(buf), params);
    body.start = buf;

    if (params->data && params->data->attachments) {
        method = HTTP_MIMEPOST;
        attr.attachments = *params->data->attachments;
    }
    else {
        method = HTTP_POST;
    }

    DISCORD_ATTR_INIT(attr, discord_interaction_response, ret);

    return discord_rest_run(&client->rest, &attr, &body, method,
                            "/interactions/%" PRIu64 "/%s/callback",
                            interaction_id, interaction_token);
}

CCORDcode
discord_get_original_interaction_response(
    struct discord *client,
    u64snowflake application_id,
    const char interaction_token[],
    struct discord_ret_interaction_response *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_INIT(attr, discord_interaction_response, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/webhooks/%" PRIu64 "/%s/messages/@original",
                            application_id, interaction_token);
}

CCORDcode
discord_edit_original_interaction_response(
    struct discord *client,
    u64snowflake application_id,
    const char interaction_token[],
    struct discord_edit_original_interaction_response *params,
    struct discord_ret_interaction_response *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_edit_original_interaction_response_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        attr.attachments = *params->attachments;
    }
    else {
        method = HTTP_PATCH;
    }

    DISCORD_ATTR_INIT(attr, discord_interaction_response, ret);

    return discord_rest_run(&client->rest, &attr, &body, method,
                            "/webhooks/%" PRIu64 "/%s/messages/@original",
                            application_id, interaction_token);
}

CCORDcode
discord_delete_original_interaction_response(struct discord *client,
                                             u64snowflake application_id,
                                             const char interaction_token[],
                                             struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/webhooks/%" PRIu64 "/%s/messages/@original",
                            application_id, interaction_token);
}

CCORDcode
discord_create_followup_message(struct discord *client,
                                u64snowflake application_id,
                                const char interaction_token[],
                                struct discord_create_followup_message *params,
                                struct discord_ret_webhook *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */
    char query[4096] = "";

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    if (params->thread_id) {
        int offset = snprintf(query, sizeof(query), "thread_id=%" PRIu64,
                              params->thread_id);
        ASSERT_NOT_OOB(offset, sizeof(query));
    }

    body.size =
        discord_create_followup_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        attr.attachments = *params->attachments;
    }
    else {
        method = HTTP_POST;
    }

    DISCORD_ATTR_INIT(attr, discord_webhook, ret);

    return discord_rest_run(&client->rest, &attr, &body, method,
                            "/webhooks/%" PRIu64 "/%s%s%s", application_id,
                            interaction_token, *query ? "?" : "", query);
}

CCORDcode
discord_get_followup_message(struct discord *client,
                             u64snowflake application_id,
                             const char interaction_token[],
                             u64snowflake message_id,
                             struct discord_ret_message *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_INIT(attr, discord_message, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/webhooks/%" PRIu64 "/%s/%" PRIu64,
                            application_id, interaction_token, message_id);
}

CCORDcode
discord_edit_followup_message(struct discord *client,
                              u64snowflake application_id,
                              const char interaction_token[],
                              u64snowflake message_id,
                              struct discord_edit_followup_message *params,
                              struct discord_ret_message *ret)
{
    struct discord_attributes attr = { 0 };
    struct ccord_szbuf body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_edit_followup_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        attr.attachments = *params->attachments;
    }
    else {
        method = HTTP_PATCH;
    }

    DISCORD_ATTR_INIT(attr, discord_message, ret);

    return discord_rest_run(&client->rest, &attr, &body, method,
                            "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                            application_id, interaction_token, message_id);
}

CCORDcode
discord_delete_followup_message(struct discord *client,
                                u64snowflake application_id,
                                const char interaction_token[],
                                u64snowflake message_id,
                                struct discord_ret *ret)
{
    struct discord_attributes attr = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    DISCORD_ATTR_BLANK_INIT(attr, ret);

    return discord_rest_run(&client->rest, &attr, NULL, HTTP_DELETE,
                            "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                            application_id, interaction_token, message_id);
}
