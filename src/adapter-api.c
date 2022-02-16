#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

#define RET_SAFECOPY_TYPED(dest, src)                                         \
    do {                                                                      \
        (dest).has_type = true;                                               \
        (dest).done.typed = (discord_on_generic)(src).done;                   \
        (dest).fail = (src).fail;                                             \
        (dest).data = (src).data;                                             \
        (dest).cleanup = (src).cleanup;                                       \
        (dest).high_p = (src).high_p;                                         \
        (dest).sync = (src).sync;                                             \
    } while (0)

#define RET_SAFECOPY_TYPELESS(dest, src)                                      \
    do {                                                                      \
        (dest).has_type = false;                                              \
        (dest).done.typeless = (src).done;                                    \
        (dest).fail = (src).fail;                                             \
        (dest).data = (src).data;                                             \
        (dest).cleanup = (src).cleanup;                                       \
        (dest).high_p = (src).high_p;                                         \
        (dest).sync = (void *)(src).sync;                                     \
    } while (0)

/**
 * @brief Helper for setting attributes for a specs-generated return struct
 *
 * @param req request handler to be initialized
 * @param type datatype of the struct
 * @param ret request attributes
 */
#define REQUEST_INIT(req, type, ret)                                          \
    do {                                                                      \
        (req).gnrc.size = sizeof(struct type);                                \
        (req).gnrc.init = (void (*)(void *))type##_init;                      \
        (req).gnrc.from_json =                                                \
            (size_t(*)(const char *, size_t, void *))type##_from_json;        \
        (req).gnrc.cleanup = (void (*)(void *))type##_cleanup;                \
        if (ret) RET_SAFECOPY_TYPED(req.ret, *ret);                           \
    } while (0)

/**
 * @brief Helper for setting attributes for a specs-generated list
 *
 * @param req request handler to be initialized
 * @param type datatype of the list
 * @param ret request attributes
 */
#define REQUEST_LIST_INIT(req, type, ret)                                     \
    do {                                                                      \
        (req).gnrc.size = sizeof(struct type);                                \
        (req).gnrc.from_json =                                                \
            (size_t(*)(const char *, size_t, void *))type##_from_json;        \
        (req).gnrc.cleanup = (void (*)(void *))type##_cleanup;                \
        if (ret) RET_SAFECOPY_TYPED(req.ret, *ret);                           \
    } while (0)

/**
 * @brief Helper for setting request attributes expecting no response
 *
 * @param req request handler to be initialized
 * @param ret request attributes
 */
#define REQUEST_BLANK_INIT(req, ret)                                          \
    if (ret) RET_SAFECOPY_TYPELESS(req.ret, *ret)

#define NOT_EMPTY_STR(str) (str && *str)

/******************************************************************************
 * Functions specific to Discord Application Commands
 ******************************************************************************/

CCORDcode
discord_get_global_application_commands(
    struct discord *client,
    u64snowflake application_id,
    struct discord_ret_application_commands *ret)
{
    struct discord_request req;

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_application_commands, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/applications/%" PRIu64 "/commands",
                               application_id);
}

CCORDcode
discord_create_global_application_command(
    struct discord *client,
    u64snowflake application_id,
    struct discord_create_global_application_command *params,
    struct discord_ret_application_command *ret)
{
    struct discord_request req;
    struct sized_buffer body;
    char buf[4096];

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->name), CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->description),
                 CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_application_command, ret);

    body.size = discord_create_global_application_command_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/applications/%" PRIu64 "/commands",
                               application_id);
}

CCORDcode
discord_get_global_application_command(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake command_id,
    struct discord_ret_application_command *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, command_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_application_command, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/applications/%" PRIu64 "/commands/%" PRIu64,
                               application_id, command_id);
}

CCORDcode
discord_edit_global_application_command(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake command_id,
    struct discord_edit_global_application_command *params,
    struct discord_ret_application_command *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[4096];

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, command_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_edit_global_application_command_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_application_command, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/applications/%" PRIu64 "/commands/%" PRIu64,
                               application_id, command_id);
}

CCORDcode
discord_delete_global_application_command(struct discord *client,
                                          u64snowflake application_id,
                                          u64snowflake command_id,
                                          struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, command_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/applications/%" PRIu64 "/commands/%" PRIu64,
                               application_id, command_id);
}

CCORDcode
discord_bulk_overwrite_global_application_command(
    struct discord *client,
    u64snowflake application_id,
    struct discord_application_commands *params,
    struct discord_ret_application_commands *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[8192];

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_application_commands_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_LIST_INIT(req, discord_application_commands, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PUT,
                               "/applications/%" PRIu64 "/commands",
                               application_id);
}

CCORDcode
discord_get_guild_application_commands(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    struct discord_ret_application_commands *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_application_commands, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands",
                               application_id, guild_id);
}

CCORDcode
discord_create_guild_application_command(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    struct discord_create_guild_application_command *params,
    struct discord_ret_application_command *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[4096];

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->name), CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(params->description),
                 CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_application_command_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_application_command, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands",
                               application_id, guild_id);
}

CCORDcode
discord_get_guild_application_command(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    u64snowflake command_id,
    struct discord_ret_application_command *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, command_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_application_command, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands/%" PRIu64,
                               application_id, guild_id, command_id);
}

CCORDcode
discord_edit_guild_application_command(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    u64snowflake command_id,
    struct discord_edit_guild_application_command *params,
    struct discord_ret_application_command *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[4096];

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, command_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_edit_guild_application_command_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_application_command, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands/%" PRIu64,
                               application_id, guild_id, command_id);
}

CCORDcode
discord_delete_guild_application_command(struct discord *client,
                                         u64snowflake application_id,
                                         u64snowflake guild_id,
                                         u64snowflake command_id,
                                         struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, command_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands/%" PRIu64,
                               application_id, guild_id, command_id);
}

CCORDcode
discord_bulk_overwrite_guild_application_command(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    struct discord_application_commands *params,
    struct discord_ret_application_commands *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[8192];

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_application_commands_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_LIST_INIT(req, discord_application_commands, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PUT,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands",
                               application_id, guild_id);
}

CCORDcode
discord_get_guild_application_command_permissions(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    struct discord_ret_guild_application_command_permissions *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_application_command_permissions, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands/permissions",
                               application_id, guild_id);
}

CCORDcode
discord_get_application_command_permissions(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    u64snowflake command_id,
    struct discord_ret_application_command_permission *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, command_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_application_command_permission, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands/%" PRIu64 "/permissions",
                               application_id, guild_id, command_id);
}

CCORDcode
discord_edit_application_command_permissions(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    u64snowflake command_id,
    struct discord_edit_application_command_permissions *params,
    struct discord_ret_application_command_permission *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[8192];

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, command_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_edit_application_command_permissions_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_application_command_permission, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PUT,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands/%" PRIu64 "/permissions",
                               application_id, guild_id, command_id);
}

CCORDcode
discord_batch_edit_application_command_permissions(
    struct discord *client,
    u64snowflake application_id,
    u64snowflake guild_id,
    struct discord_guild_application_command_permissions *params,
    struct discord_ret_guild_application_command_permissions *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[8192];

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_guild_application_command_permissions_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_LIST_INIT(req, discord_application_command_permissions, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PUT,
                               "/applications/%" PRIu64 "/guilds/%" PRIu64
                               "/commands/permissions",
                               application_id, guild_id);
}

/******************************************************************************
 * Functions specific to Discord Audit Log
 ******************************************************************************/

/* FIXME: when response JSON is too large, jsmn crashes on error, most likely
 * json_extract() is handling the tokens incorrectly. */
CCORDcode
discord_get_guild_audit_log(struct discord *client,
                            u64snowflake guild_id,
                            struct discord_get_guild_audit_log *params,
                            struct discord_ret_audit_log *ret)
{
    struct discord_request req = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    if (params) {
        size_t offset = 0;

        if (params->user_id) {
            offset += snprintf(query + offset, sizeof(query) - offset,
                               "?user_id=%" PRIu64, params->user_id);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
        if (params->action_type) {
            offset += snprintf(query + offset, sizeof(query) - offset,
                               "%saction_type=%d", *query ? "&" : "?",
                               params->action_type);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
        if (params->before) {
            offset += snprintf(query + offset, sizeof(query) - offset,
                               "%sbefore=%" PRIu64, *query ? "&" : "?",
                               params->before);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
        if (params->limit) {
            offset +=
                snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                         *query ? "&" : "?", params->limit);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
    }

    REQUEST_INIT(req, discord_audit_log, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/audit-logs%s", guild_id,
                               query);
}

/******************************************************************************
 * Functions specific to Discord Channel
 ******************************************************************************/

CCORDcode
discord_get_channel(struct discord *client,
                    u64snowflake channel_id,
                    struct discord_ret_channel *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64, channel_id);
}

CCORDcode
discord_modify_channel(struct discord *client,
                       u64snowflake channel_id,
                       struct discord_modify_channel *params,
                       struct discord_ret_channel *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_channel_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/channels/%" PRIu64, channel_id);
}

CCORDcode
discord_delete_channel(struct discord *client,
                       u64snowflake channel_id,
                       struct discord_ret_channel *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64, channel_id);
}

CCORDcode
discord_get_channel_messages(struct discord *client,
                             u64snowflake channel_id,
                             struct discord_get_channel_messages *params,
                             struct discord_ret_messages *ret)
{
    struct discord_request req = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    if (params) {
        size_t offset = 0;
        if (params->limit) {
            offset += snprintf(query + offset, sizeof(query) - offset,
                               "limit=%d", params->limit);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
        if (params->around) {
            offset += snprintf(query + offset, sizeof(query) - offset,
                               "%saround=%" PRIu64, *query ? "&" : "",
                               params->around);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
        if (params->before) {
            offset += snprintf(query + offset, sizeof(query) - offset,
                               "%sbefore=%" PRIu64, *query ? "&" : "",
                               params->before);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
        if (params->after) {
            offset +=
                snprintf(query + offset, sizeof(query) - offset,
                         "%safter=%" PRIu64, *query ? "&" : "", params->after);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
    }

    REQUEST_LIST_INIT(req, discord_messages, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64 "/messages%s%s",
                               channel_id, *query ? "?" : "", query);
}

CCORDcode
discord_get_channel_message(struct discord *client,
                            u64snowflake channel_id,
                            u64snowflake message_id,
                            struct discord_ret_message *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_message, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64 "/messages/%" PRIu64,
                               channel_id, message_id);
}

CCORDcode
discord_create_message(struct discord *client,
                       u64snowflake channel_id,
                       struct discord_create_message *params,
                       struct discord_ret_message *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        req.attachments = params->attachments;
    }
    else {
        method = HTTP_POST;
    }

    REQUEST_INIT(req, discord_message, ret);

    return discord_adapter_run(&client->adapter, &req, &body, method,
                               "/channels/%" PRIu64 "/messages", channel_id);
}

CCORDcode
discord_crosspost_message(struct discord *client,
                          u64snowflake channel_id,
                          u64snowflake message_id,
                          struct discord_ret_message *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_message, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_POST,
                               "/channels/%" PRIu64 "/messages/%" PRIu64
                               "/crosspost",
                               channel_id, message_id);
}

CCORDcode
discord_create_reaction(struct discord *client,
                        u64snowflake channel_id,
                        u64snowflake message_id,
                        u64snowflake emoji_id,
                        const char emoji_name[],
                        struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    char *pct_emoji_name;
    char emoji_endpoint[256];
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    REQUEST_BLANK_INIT(req, ret);

    code = discord_adapter_run(&client->adapter, &req, NULL, HTTP_PUT,
                               "/channels/%" PRIu64 "/messages/%" PRIu64
                               "/reactions/%s/@me",
                               channel_id, message_id, emoji_endpoint);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_delete_own_reaction(struct discord *client,
                            u64snowflake channel_id,
                            u64snowflake message_id,
                            u64snowflake emoji_id,
                            const char emoji_name[],
                            struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    char *pct_emoji_name;
    char emoji_endpoint[256];
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    REQUEST_BLANK_INIT(req, ret);

    code = discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/messages/%" PRIu64
                               "/reactions/%s/@me",
                               channel_id, message_id, emoji_endpoint);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_delete_user_reaction(struct discord *client,
                             u64snowflake channel_id,
                             u64snowflake message_id,
                             u64snowflake user_id,
                             u64snowflake emoji_id,
                             const char emoji_name[],
                             struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    char *pct_emoji_name;
    char emoji_endpoint[256];
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    REQUEST_BLANK_INIT(req, ret);

    code = discord_adapter_run(
        &client->adapter, &req, NULL, HTTP_DELETE,
        "/channels/%" PRIu64 "/messages/%" PRIu64 "/reactions/%s/%" PRIu64,
        channel_id, message_id, emoji_endpoint, user_id);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_get_reactions(struct discord *client,
                      u64snowflake channel_id,
                      u64snowflake message_id,
                      u64snowflake emoji_id,
                      const char emoji_name[],
                      struct discord_get_reactions *params,
                      struct discord_ret_users *ret)
{
    struct discord_request req = { 0 };
    char emoji_endpoint[256];
    char query[1024] = "";
    char *pct_emoji_name;
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    if (params) {
        size_t offset = 0;

        if (params->after) {
            CCORD_EXPECT(client, params->after != 0, CCORD_BAD_PARAMETER, "");

            offset += snprintf(query + offset, sizeof(query) - offset,
                               "?after=%" PRIu64, params->after);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
        if (params->limit) {
            CCORD_EXPECT(client, params->limit > 0 && params->limit <= 100,
                         CCORD_BAD_PARAMETER, "");

            offset +=
                snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                         *query ? "&" : "?", params->limit);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
    }

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    REQUEST_LIST_INIT(req, discord_users, ret);

    code = discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64 "/messages/%" PRIu64
                               "/reactions/%s%s",
                               channel_id, message_id, emoji_endpoint, query);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_delete_all_reactions(struct discord *client,
                             u64snowflake channel_id,
                             u64snowflake message_id,
                             struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/messages/%" PRIu64
                               "/reactions",
                               channel_id, message_id);
}

CCORDcode
discord_delete_all_reactions_for_emoji(struct discord *client,
                                       u64snowflake channel_id,
                                       u64snowflake message_id,
                                       u64snowflake emoji_id,
                                       const char emoji_name[],
                                       struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    char *pct_emoji_name;
    char emoji_endpoint[256];
    CCORDcode code;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    pct_emoji_name =
        emoji_name ? curl_escape(emoji_name, strlen(emoji_name)) : NULL;

    if (emoji_id)
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
                 pct_emoji_name, emoji_id);
    else
        snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

    REQUEST_BLANK_INIT(req, ret);

    code = discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/messages/%" PRIu64
                               "/reactions/%s",
                               channel_id, message_id, emoji_endpoint);

    curl_free(pct_emoji_name);

    return code;
}

CCORDcode
discord_edit_message(struct discord *client,
                     u64snowflake channel_id,
                     u64snowflake message_id,
                     struct discord_edit_message *params,
                     struct discord_ret_message *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[16384]; /**< @todo dynamic buffer */

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_edit_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_message, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/channels/%" PRIu64 "/messages/%" PRIu64,
                               channel_id, message_id);
}

CCORDcode
discord_delete_message(struct discord *client,
                       u64snowflake channel_id,
                       u64snowflake message_id,
                       struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/messages/%" PRIu64,
                               channel_id, message_id);
}

/** @todo add duplicated ID verification */
CCORDcode
discord_bulk_delete_messages(struct discord *client,
                             u64snowflake channel_id,
                             struct snowflakes *messages,
                             struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    u64unix_ms now = discord_timestamp(client);
    struct sized_buffer body;
    char buf[4096] = "";
    int i;

    CCORD_EXPECT(client, messages != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, messages->size >= 2 && messages->size <= 100,
                 CCORD_BAD_PARAMETER, "");

    for (i = 0; i < messages->size; ++i) {
        u64unix_ms tstamp = (messages->array[i] >> 22) + 1420070400000;

        CCORD_EXPECT(client, now <= tstamp || now - tstamp <= 1209600000,
                     CCORD_BAD_PARAMETER,
                     "Messages should not be older than 2 weeks.");
    }

    body.size = snowflakes_to_json(buf, sizeof(buf), messages);
    body.start = buf;

    CCORD_EXPECT(client, buf != NULL, CCORD_BAD_JSON, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/channels/%" PRIu64 "/messages/bulk-delete",
                               channel_id);
}

CCORDcode
discord_edit_channel_permissions(
    struct discord *client,
    u64snowflake channel_id,
    u64snowflake overwrite_id,
    struct discord_edit_channel_permissions *params,
    struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, overwrite_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_edit_channel_permissions_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PUT,
                               "/channels/%" PRIu64 "/permissions/%" PRIu64,
                               channel_id, overwrite_id);
}

CCORDcode
discord_get_channel_invites(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_ret_invites *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_invites, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64 "/invites", channel_id);
}

CCORDcode
discord_create_channel_invite(struct discord *client,
                              u64snowflake channel_id,
                              struct discord_create_channel_invite *params,
                              struct discord_ret_invite *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];
    size_t len;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    if (params)
        len = discord_create_channel_invite_to_json(buf, sizeof(buf), params);
    else
        len = snprintf(buf, sizeof(buf), "{}");
    body.start = buf;
    body.size = len;

    REQUEST_INIT(req, discord_invite, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/channels/%" PRIu64 "/invites", channel_id);
}

CCORDcode
discord_delete_channel_permission(struct discord *client,
                                  u64snowflake channel_id,
                                  u64snowflake overwrite_id,
                                  struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, overwrite_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/permissions/%" PRIu64,
                               channel_id, overwrite_id);
}

CCORDcode
discord_follow_news_channel(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_follow_news_channel *params,
                            struct discord_ret_followed_channel *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[256]; /* should be more than enough for this */

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->webhook_channel_id != 0, CCORD_BAD_PARAMETER,
                 "");

    body.size = discord_follow_news_channel_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/channels/%" PRIu64 "/followers", channel_id);
}

CCORDcode
discord_trigger_typing_indicator(struct discord *client,
                                 u64snowflake channel_id,
                                 struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_POST,
                               "/channels/%" PRIu64 "/typing", channel_id);
}

CCORDcode
discord_get_pinned_messages(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_ret_messages *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_messages, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64 "/pins", channel_id);
}

CCORDcode
discord_pin_message(struct discord *client,
                    u64snowflake channel_id,
                    u64snowflake message_id,
                    struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_PUT,
                               "/channels/%" PRIu64 "/pins/%" PRIu64,
                               channel_id, message_id);
}

CCORDcode
discord_unpin_message(struct discord *client,
                      u64snowflake channel_id,
                      u64snowflake message_id,
                      struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/pins/%" PRIu64,
                               channel_id, message_id);
}

CCORDcode
discord_group_dm_add_recipient(struct discord *client,
                               u64snowflake channel_id,
                               u64snowflake user_id,
                               struct discord_group_dm_add_recipient *params,
                               struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_group_dm_add_recipient_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PUT,
                               "/channels/%" PRIu64 "/recipients/%" PRIu64,
                               channel_id, user_id);
}

CCORDcode
discord_group_dm_remove_recipient(struct discord *client,
                                  u64snowflake channel_id,
                                  u64snowflake user_id,
                                  struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/recipients/%" PRIu64,
                               channel_id, user_id);
}

CCORDcode
discord_start_thread_with_message(
    struct discord *client,
    u64snowflake channel_id,
    u64snowflake message_id,
    struct discord_start_thread_with_message *params,
    struct discord_ret_channel *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_start_thread_with_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/channels/%" PRIu64 "/messages/%" PRIu64
                               "/threads",
                               channel_id, message_id);
}

CCORDcode
discord_start_thread_without_message(
    struct discord *client,
    u64snowflake channel_id,
    struct discord_start_thread_without_message *params,
    struct discord_ret_channel *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_start_thread_without_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/channels/%" PRIu64 "/threads", channel_id);
}

CCORDcode
discord_join_thread(struct discord *client,
                    u64snowflake channel_id,
                    struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_PUT,
                               "/channels/%" PRIu64 "/thread-members/@me",
                               channel_id);
}

CCORDcode
discord_add_thread_member(struct discord *client,
                          u64snowflake channel_id,
                          u64snowflake user_id,
                          struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_PUT,
                               "/channels/%" PRIu64 "/thread-members/" PRIu64,
                               channel_id, user_id);
}

CCORDcode
discord_leave_thread(struct discord *client,
                     u64snowflake channel_id,
                     struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/thread-members/@me",
                               channel_id);
}

CCORDcode
discord_remove_thread_member(struct discord *client,
                             u64snowflake channel_id,
                             u64snowflake user_id,
                             struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/channels/%" PRIu64 "/thread-members/" PRIu64,
                               channel_id, user_id);
}

CCORDcode
discord_list_thread_members(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_ret_thread_members *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_thread_members, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64 "/thread-members",
                               channel_id);
}

CCORDcode
discord_list_active_threads(struct discord *client,
                            u64snowflake channel_id,
                            struct discord_ret_thread_response_body *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_thread_response_body, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64 "/threads/active",
                               channel_id);
}

CCORDcode
discord_list_public_archived_threads(
    struct discord *client,
    u64snowflake channel_id,
    u64unix_ms before,
    int limit,
    struct discord_ret_thread_response_body *ret)
{
    struct discord_request req = { 0 };
    char query[1024] = "";
    size_t offset = 0;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    if (before) {
        offset += snprintf(query + offset, sizeof(query) - offset,
                           "before=%" PRIu64, before);
        ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (limit) {
        offset += snprintf(query + offset, sizeof(query) - offset,
                           "%slimit=%d", *query ? "&" : "", limit);
        ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }

    REQUEST_INIT(req, discord_thread_response_body, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64
                               "/threads/archived/public%s%s",
                               channel_id, *query ? "?" : "", query);
}

CCORDcode
discord_list_private_archived_threads(
    struct discord *client,
    u64snowflake channel_id,
    u64unix_ms before,
    int limit,
    struct discord_ret_thread_response_body *ret)
{
    struct discord_request req = { 0 };
    char query[1024] = "";
    size_t offset = 0;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    if (before) {
        offset += snprintf(query + offset, sizeof(query) - offset,
                           "before=%" PRIu64, before);
        ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (limit) {
        offset += snprintf(query + offset, sizeof(query) - offset,
                           "%slimit=%d", *query ? "&" : "", limit);
        ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }

    REQUEST_INIT(req, discord_thread_response_body, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64
                               "/threads/archived/private%s%s",
                               channel_id, *query ? "?" : "", query);
}

CCORDcode
discord_list_joined_private_archived_threads(
    struct discord *client,
    u64snowflake channel_id,
    u64unix_ms before,
    int limit,
    struct discord_ret_thread_response_body *ret)
{
    struct discord_request req = { 0 };
    char query[1024] = "";
    size_t offset = 0;

    CCORD_EXPECT(client, channel_id != 0, CCORD_BAD_PARAMETER, "");

    if (before) {
        offset += snprintf(query + offset, sizeof(query) - offset,
                           "before=%" PRIu64, before);
        ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (limit) {
        offset += snprintf(query + offset, sizeof(query) - offset,
                           "%slimit=%d", *query ? "&" : "", limit);
        ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }

    REQUEST_INIT(req, discord_thread_response_body, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/channels/%" PRIu64
                               "/users/@me/threads/archived/private%s%s",
                               channel_id, *query ? "?" : "", query);
}

/******************************************************************************
 * Functions specific to Discord Emoji
 ******************************************************************************/

CCORDcode
discord_list_guild_emojis(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_ret_emojis *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_emojis, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/emojis", guild_id);
}

CCORDcode
discord_get_guild_emoji(struct discord *client,
                        u64snowflake guild_id,
                        u64snowflake emoji_id,
                        struct discord_ret_emoji *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, emoji_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_emoji, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id,
                               emoji_id);
}

CCORDcode
discord_create_guild_emoji(struct discord *client,
                           u64snowflake guild_id,
                           struct discord_create_guild_emoji *params,
                           struct discord_ret_emoji *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[2048];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_emoji_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_emoji, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/guilds/%" PRIu64 "/emojis", guild_id);
}

CCORDcode
discord_modify_guild_emoji(struct discord *client,
                           u64snowflake guild_id,
                           u64snowflake emoji_id,
                           struct discord_modify_guild_emoji *params,
                           struct discord_ret_emoji *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[2048];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, emoji_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_emoji_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_emoji, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id,
                               emoji_id);
}

CCORDcode
discord_delete_guild_emoji(struct discord *client,
                           u64snowflake guild_id,
                           u64snowflake emoji_id,
                           struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, emoji_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id,
                               emoji_id);
}

/******************************************************************************
 * Functions specific to Discord Gateway
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

/******************************************************************************
 * Functions specific to Discord Guild Template
 ******************************************************************************/

CCORDcode
discord_get_guild_template(struct discord *client,
                           char *code,
                           struct discord_ret_guild_template *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, NOT_EMPTY_STR(code), CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_guild_template, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/templates/%s", code);
}

CCORDcode
discord_create_guild_template(struct discord *client,
                              u64snowflake guild_id,
                              struct discord_create_guild_template *params,
                              struct discord_ret_guild_template *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[256];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_create_guild_template_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_guild_template, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/guilds/%" PRIu64 "/templates", guild_id);
}

CCORDcode
discord_sync_guild_template(struct discord *client,
                            u64snowflake guild_id,
                            char *code,
                            struct discord_ret_guild_template *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_guild_template, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_PUT,
                               "/guilds/%" PRIu64 "/templates/%s", guild_id,
                               code);
}

/******************************************************************************
 * Functions specific to Discord Guild
 ******************************************************************************/

CCORDcode
discord_create_guild(struct discord *client,
                     struct discord_create_guild *params,
                     struct discord_ret_guild *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[4096];

    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_guild, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/guilds");
}

CCORDcode
discord_get_guild(struct discord *client,
                  u64snowflake guild_id,
                  struct discord_ret_guild *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_guild, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64, guild_id);
}

CCORDcode
discord_get_guild_preview(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_ret_guild_preview *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_guild_preview, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/preview", guild_id);
}

CCORDcode
discord_modify_guild(struct discord *client,
                     u64snowflake guild_id,
                     struct discord_modify_guild *params,
                     struct discord_ret_guild *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_guild, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64, guild_id);
}

CCORDcode
discord_delete_guild(struct discord *client,
                     u64snowflake guild_id,
                     struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/guilds/%" PRIu64, guild_id);
}

CCORDcode
discord_get_guild_channels(struct discord *client,
                           u64snowflake guild_id,
                           struct discord_ret_channels *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_channels, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/channels", guild_id);
}

CCORDcode
discord_create_guild_channel(struct discord *client,
                             u64snowflake guild_id,
                             struct discord_create_guild_channel *params,
                             struct discord_ret_channel *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[2048];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_channel_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/guilds/%" PRIu64 "/channels", guild_id);
}

CCORDcode
discord_modify_guild_channel_positions(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_guild_channel_positions *params,
    struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_channel_positions_to_json(
        buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64 "/channels", guild_id);
}

CCORDcode
discord_get_guild_member(struct discord *client,
                         u64snowflake guild_id,
                         u64snowflake user_id,
                         struct discord_ret_guild_member *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_guild_member, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/members/%" PRIu64,
                               guild_id, user_id);
}

CCORDcode
discord_list_guild_members(struct discord *client,
                           u64snowflake guild_id,
                           struct discord_list_guild_members *params,
                           struct discord_ret_guild_members *ret)
{
    struct discord_request req = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    if (params) {
        size_t offset = 0;

        if (params->limit) {
            offset += snprintf(query + offset, sizeof(query) - offset,
                               "limit=%d", params->limit);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
        if (params->after) {
            offset +=
                snprintf(query + offset, sizeof(query) - offset,
                         "%safter=%" PRIu64, *query ? "&" : "", params->after);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
    }

    REQUEST_LIST_INIT(req, discord_guild_members, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/members%s%s", guild_id,
                               *query ? "?" : "", query);
}

CCORDcode
discord_search_guild_members(struct discord *client,
                             u64snowflake guild_id,
                             struct discord_search_guild_members *params,
                             struct discord_ret_guild_members *ret)
{
    struct discord_request req = { 0 };
    char query[1024] = "";

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    if (params) {
        size_t offset = 0;
        if (params->query) {
            char *pe_query = curl_escape(params->query, strlen(params->query));

            offset += snprintf(query + offset, sizeof(query) - offset,
                               "query=%s", pe_query);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");

            curl_free(pe_query);
        }
        if (params->limit) {
            offset += snprintf(query + offset, sizeof(query) - offset,
                               "%slimit=%d", *query ? "&" : "", params->limit);
            ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
        }
    }

    REQUEST_LIST_INIT(req, discord_guild_members, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/members/search%s%s",
                               guild_id, *query ? "?" : "", query);
}

CCORDcode
discord_add_guild_member(struct discord *client,
                         u64snowflake guild_id,
                         u64snowflake user_id,
                         struct discord_add_guild_member *params,
                         struct discord_ret_guild_member *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->access_token != NULL, CCORD_BAD_PARAMETER,
                 "");

    body.size = discord_add_guild_member_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_guild_member, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PUT,
                               "/guilds/%" PRIu64 "/members/%" PRIu64,
                               guild_id, user_id);
}

CCORDcode
discord_modify_guild_member(struct discord *client,
                            u64snowflake guild_id,
                            u64snowflake user_id,
                            struct discord_modify_guild_member *params,
                            struct discord_ret_guild_member *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[2048];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_guild_member_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_guild_member, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64 "/members/%" PRIu64,
                               guild_id, user_id);
}
CCORDcode
discord_modify_current_member(struct discord *client,
                              u64snowflake guild_id,
                              struct discord_modify_current_member *params,
                              struct discord_ret_guild_member *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[512];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->nick != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_modify_current_member_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_guild_member, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64 "/members/@me", guild_id);
}
CCORDcode
discord_modify_current_user_nick(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_current_user_nick *params,
    struct discord_ret_guild_member *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
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

    REQUEST_INIT(req, discord_guild_member, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64 "/members/@me/nick",
                               guild_id);
}

CCORDcode
discord_add_guild_member_role(struct discord *client,
                              u64snowflake guild_id,
                              u64snowflake user_id,
                              u64snowflake role_id,
                              struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_PUT,
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
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
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
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/guilds/%" PRIu64 "/members/%" PRIu64,
                               guild_id, user_id);
}

CCORDcode
discord_get_guild_bans(struct discord *client,
                       u64snowflake guild_id,
                       struct discord_ret_bans *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_bans, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/bans", guild_id);
}

CCORDcode
discord_get_guild_ban(struct discord *client,
                      u64snowflake guild_id,
                      u64snowflake user_id,
                      struct discord_ret_ban *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_ban, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
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
    struct discord_request req = { 0 };
    struct sized_buffer body;
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

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PUT,
                               "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                               user_id);
}
CCORDcode
discord_remove_guild_ban(struct discord *client,
                         u64snowflake guild_id,
                         u64snowflake user_id,
                         struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                               user_id);
}

CCORDcode
discord_get_guild_roles(struct discord *client,
                        u64snowflake guild_id,
                        struct discord_ret_roles *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_roles, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/roles", guild_id);
}

CCORDcode
discord_create_guild_role(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_create_guild_role *params,
                          struct discord_ret_role *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_guild_role_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_role, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/guilds/%" PRIu64 "/roles", guild_id);
}

CCORDcode
discord_modify_guild_role_positions(
    struct discord *client,
    u64snowflake guild_id,
    struct discord_modify_guild_role_positions *params,
    struct discord_ret_roles *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[4096];

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size =
        discord_modify_guild_role_positions_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_LIST_INIT(req, discord_roles, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64 "/roles", guild_id);
}

CCORDcode
discord_modify_guild_role(struct discord *client,
                          u64snowflake guild_id,
                          u64snowflake role_id,
                          struct discord_modify_guild_role *params,
                          struct discord_ret_role *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[2048] = "{}";
    size_t len;

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    if (params)
        len = discord_modify_guild_role_to_json(buf, sizeof(buf), params);
    else
        len = snprintf(buf, sizeof(buf), "{}");
    body.size = len;
    body.start = buf;

    REQUEST_INIT(req, discord_role, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                               role_id);
}

CCORDcode
discord_delete_guild_role(struct discord *client,
                          u64snowflake guild_id,
                          u64snowflake role_id,
                          struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, role_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                               role_id);
}

CCORDcode
discord_begin_guild_prune(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_begin_guild_prune *params,
                          struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[4096];
    size_t len;

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    if (params)
        len = discord_begin_guild_prune_to_json(buf, sizeof(buf), params);
    else
        len = snprintf(buf, sizeof(buf), "{}");
    body.size = len;
    body.start = buf;

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/guilds/%" PRIu64 "/prune", guild_id);
}

CCORDcode
discord_get_guild_invites(struct discord *client,
                          u64snowflake guild_id,
                          struct discord_ret_invites *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_LIST_INIT(req, discord_invites, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/invites", guild_id);
}

CCORDcode
discord_delete_guild_integrations(struct discord *client,
                                  u64snowflake guild_id,
                                  u64snowflake integration_id,
                                  struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, integration_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/guilds/%" PRIu64 "/integrations/%" PRIu64,
                               guild_id, integration_id);
}

CCORDcode
discord_get_guild_vanity_url(struct discord *client,
                             u64snowflake guild_id,
                             struct discord_ret_invite *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_invite, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/vanity-url", guild_id);
}

CCORDcode
discord_get_guild_welcome_screen(struct discord *client,
                                 u64snowflake guild_id,
                                 struct discord_ret_welcome_screen *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_welcome_screen, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/guilds/%" PRIu64 "/welcome-screen", guild_id);
}

/******************************************************************************
 * Functions specific to Discord Interaction
 ******************************************************************************/

CCORDcode
discord_create_interaction_response(
    struct discord *client,
    u64snowflake interaction_id,
    const char interaction_token[],
    struct discord_interaction_response *params,
    struct discord_ret_interaction_response *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
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
        req.attachments = params->data->attachments;
    }
    else {
        method = HTTP_POST;
    }

    REQUEST_INIT(req, discord_interaction_response, ret);

    return discord_adapter_run(&client->adapter, &req, &body, method,
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
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");

    REQUEST_INIT(req, discord_interaction_response, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
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
    struct discord_request req = { 0 };
    struct sized_buffer body;
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
        req.attachments = params->attachments;
    }
    else {
        method = HTTP_PATCH;
    }

    REQUEST_INIT(req, discord_interaction_response, ret);

    return discord_adapter_run(&client->adapter, &req, &body, method,
                               "/webhooks/%" PRIu64 "/%s/messages/@original",
                               application_id, interaction_token);
}

CCORDcode
discord_delete_original_interaction_response(struct discord *client,
                                             u64snowflake application_id,
                                             const char interaction_token[],
                                             struct discord_ret *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
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
    struct discord_request req = { 0 };
    struct sized_buffer body;
    enum http_method method;
    char buf[16384]; /**< @todo dynamic buffer */
    char query[4096] = "";

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    if (params->thread_id) {
        size_t ret;

        ret = snprintf(query, sizeof(query), "thread_id=%" PRIu64,
                       params->thread_id);
        ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
    }

    body.size =
        discord_create_followup_message_to_json(buf, sizeof(buf), params);
    body.start = buf;

    if (params->attachments) {
        method = HTTP_MIMEPOST;
        req.attachments = params->attachments;
    }
    else {
        method = HTTP_POST;
    }

    REQUEST_INIT(req, discord_webhook, ret);

    return discord_adapter_run(&client->adapter, &req, &body, method,
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
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_message, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
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
    struct discord_request req = { 0 };
    struct sized_buffer body;
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
        req.attachments = params->attachments;
    }
    else {
        method = HTTP_PATCH;
    }

    REQUEST_INIT(req, discord_message, ret);

    return discord_adapter_run(&client->adapter, &req, &body, method,
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
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, application_id != 0, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, NOT_EMPTY_STR(interaction_token), CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, message_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                               application_id, interaction_token, message_id);
}

/******************************************************************************
 * Functions specific to Discord Invite
 ******************************************************************************/

CCORDcode
discord_get_invite(struct discord *client,
                   char *invite_code,
                   struct discord_get_invite *params,
                   struct discord_ret_invite *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, NOT_EMPTY_STR(invite_code), CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_get_invite_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_invite, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_GET,
                               "/invites/%s", invite_code);
}

CCORDcode
discord_delete_invite(struct discord *client,
                      char *invite_code,
                      struct discord_ret_invite *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, NOT_EMPTY_STR(invite_code), CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_invite, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_DELETE,
                               "/invites/%s", invite_code);
}

/******************************************************************************
 * Functions specific to Discord User
 ******************************************************************************/

CCORDcode
discord_get_current_user(struct discord *client, struct discord_ret_user *ret)
{
    struct discord_request req = { 0 };

    REQUEST_INIT(req, discord_user, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/users/@me");
}

CCORDcode
discord_get_user(struct discord *client,
                 u64snowflake user_id,
                 struct discord_ret_user *ret)
{
    struct discord_request req = { 0 };

    CCORD_EXPECT(client, user_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_INIT(req, discord_user, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/users/%" PRIu64, user_id);
}

CCORDcode
discord_modify_current_user(struct discord *client,
                            struct discord_modify_current_user *params,
                            struct discord_ret_user *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_modify_current_user_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_user, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_PATCH,
                               "/users/@me");
}

CCORDcode
discord_get_current_user_guilds(struct discord *client,
                                struct discord_ret_guilds *ret)
{
    struct discord_request req = { 0 };

    REQUEST_LIST_INIT(req, discord_guilds, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/users/@me/guilds");
}

CCORDcode
discord_leave_guild(struct discord *client,
                    u64snowflake guild_id,
                    struct discord_ret *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body = { "{}", 2 };

    CCORD_EXPECT(client, guild_id != 0, CCORD_BAD_PARAMETER, "");

    REQUEST_BLANK_INIT(req, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_DELETE,
                               "/users/@me/guilds/%" PRIu64, guild_id);
}

CCORDcode
discord_create_dm(struct discord *client,
                  struct discord_create_dm *params,
                  struct discord_ret_channel *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[128];

    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_dm_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/users/@me/channels");
}

CCORDcode
discord_create_group_dm(struct discord *client,
                        struct discord_create_group_dm *params,
                        struct discord_ret_channel *ret)
{
    struct discord_request req = { 0 };
    struct sized_buffer body;
    char buf[1024];

    CCORD_EXPECT(client, params != NULL, CCORD_BAD_PARAMETER, "");
    CCORD_EXPECT(client, params->access_tokens != NULL, CCORD_BAD_PARAMETER,
                 "");
    CCORD_EXPECT(client, params->nicks != NULL, CCORD_BAD_PARAMETER, "");

    body.size = discord_create_group_dm_to_json(buf, sizeof(buf), params);
    body.start = buf;

    REQUEST_INIT(req, discord_channel, ret);

    return discord_adapter_run(&client->adapter, &req, &body, HTTP_POST,
                               "/users/@me/channels");
}

CCORDcode
discord_get_user_connections(struct discord *client,
                             struct discord_ret_connections *ret)
{
    struct discord_request req = { 0 };

    REQUEST_LIST_INIT(req, discord_connections, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/users/@me/connections");
}

/******************************************************************************
 * Functions specific to Discord Voice
 ******************************************************************************/

CCORDcode
discord_list_voice_regions(struct discord *client,
                           struct discord_ret_voice_regions *ret)
{
    struct discord_request req = { 0 };

    REQUEST_LIST_INIT(req, discord_voice_regions, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/voice/regions");
}

/******************************************************************************
 * Functions specific to Discord Webhook
 ******************************************************************************/

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

    REQUEST_INIT(req, discord_webhook, ret);

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

    REQUEST_LIST_INIT(req, discord_webhooks, ret);

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

    REQUEST_LIST_INIT(req, discord_webhooks, ret);

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

    REQUEST_INIT(req, discord_webhook, ret);

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

    REQUEST_INIT(req, discord_webhook, ret);

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

    REQUEST_INIT(req, discord_webhook, ret);

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

    REQUEST_INIT(req, discord_webhook, ret);

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

    REQUEST_BLANK_INIT(req, ret);

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

    REQUEST_BLANK_INIT(req, ret);

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
        req.attachments = params->attachments;
    }
    else {
        method = HTTP_POST;
    }

    REQUEST_BLANK_INIT(req, ret);

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

    REQUEST_INIT(req, discord_message, ret);

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
        req.attachments = params->attachments;
    }
    else {
        method = HTTP_PATCH;
    }

    REQUEST_INIT(req, discord_message, ret);

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

    REQUEST_BLANK_INIT(req, ret);

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

    REQUEST_INIT(req, discord_guild_member, ret);

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
