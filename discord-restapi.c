#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

/**
 * @brief Shortcut for setting attributes for a specs-generated struct
 *
 * @param type datatype of the struct
 * @param obj pointer to specs-generated struct
 */
#define REQUEST_ATTR_INIT(type, obj)                                          \
  {                                                                           \
    obj, sizeof *obj, type##_init_v, type##_from_json_v, type##_cleanup_v     \
  }

/**
 * @brief Shortcut for setting attributes for a specs-generated list
 *
 * @param type datatype of the list
 * @param list pointer to specs-generated null terminated list
 */
#define REQUEST_ATTR_LIST_INIT(type, list)                                    \
  {                                                                           \
    list, sizeof **list, NULL, type##_list_from_json_v,                       \
      (void (*)(void *))type##_list_free_v                                    \
  }

/******************************************************************************
 * Functions specific to Discord Application Commands
 ******************************************************************************/

ORCAcode
discord_get_global_application_commands(
  struct discord *client,
  u64_snowflake_t application_id,
  struct discord_application_command ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_application_command, ret);

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/applications/%" PRIu64 "/commands",
                             application_id);
}

ORCAcode
discord_create_global_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  struct discord_create_global_application_command_params *params,
  struct discord_application_command *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_application_command, ret);
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->name), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->description),
              ORCA_BAD_PARAMETER);

  body.size = discord_create_global_application_command_params_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/applications/%" PRIu64 "/commands",
                             application_id);
}

ORCAcode
discord_get_global_application_command(struct discord *client,
                                       u64_snowflake_t application_id,
                                       u64_snowflake_t command_id,
                                       struct discord_application_command *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_application_command, ret);

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, command_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/applications/%" PRIu64 "/commands/%" PRIu64,
                             application_id, command_id);
}

ORCAcode
discord_edit_global_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t command_id,
  struct discord_edit_global_application_command_params *params,
  struct discord_application_command *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_application_command, ret);
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, command_id != 0, ORCA_BAD_PARAMETER);

  body.size = discord_edit_global_application_command_params_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/applications/%" PRIu64 "/commands/%" PRIu64,
                             application_id, command_id);
}

ORCAcode
discord_delete_global_application_command(struct discord *client,
                                          u64_snowflake_t application_id,
                                          u64_snowflake_t command_id)
{
  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, command_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/applications/%" PRIu64 "/commands/%" PRIu64,
                             application_id, command_id);
}

ORCAcode
discord_bulk_overwrite_global_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  struct discord_application_command **params,
  struct discord_application_command ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_application_command, ret);
  struct sized_buffer body;
  char buf[8192];

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_application_command_list_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PUT,
                             "/applications/%" PRIu64 "/commands",
                             application_id);
}

ORCAcode
discord_get_guild_application_commands(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_application_command ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_application_command, ret);

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands",
                             application_id, guild_id);
}

ORCAcode
discord_create_guild_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_create_guild_application_command_params *params,
  struct discord_application_command *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_application_command, ret);
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->name), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->description),
              ORCA_BAD_PARAMETER);

  body.size = discord_create_guild_application_command_params_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands",
                             application_id, guild_id);
}

ORCAcode
discord_get_guild_application_command(struct discord *client,
                                      u64_snowflake_t application_id,
                                      u64_snowflake_t guild_id,
                                      u64_snowflake_t command_id,
                                      struct discord_application_command *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_application_command, ret);

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, command_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands/%" PRIu64,
                             application_id, guild_id, command_id);
}

ORCAcode
discord_edit_guild_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  u64_snowflake_t command_id,
  struct discord_edit_guild_application_command_params *params,
  struct discord_application_command *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_application_command, ret);
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, command_id != 0, ORCA_BAD_PARAMETER);

  body.size = discord_edit_guild_application_command_params_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands/%" PRIu64,
                             application_id, guild_id, command_id);
}

ORCAcode
discord_delete_guild_application_command(struct discord *client,
                                         u64_snowflake_t application_id,
                                         u64_snowflake_t guild_id,
                                         u64_snowflake_t command_id)
{
  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, command_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands/%" PRIu64,
                             application_id, guild_id, command_id);
}

ORCAcode
discord_bulk_overwrite_guild_application_command(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_application_command **params,
  struct discord_application_command ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_application_command, ret);
  struct sized_buffer body;
  char buf[8192];

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_application_command_list_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PUT,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands",
                             application_id, guild_id);
}

ORCAcode
discord_get_guild_application_command_permissions(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_guild_application_command_permissions ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_application_command_permissions, ret);

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands/permissions",
                             application_id, guild_id);
}

ORCAcode
discord_get_application_command_permissions(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  u64_snowflake_t command_id,
  struct discord_guild_application_command_permissions *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_application_command_permissions, ret);

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, command_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands/%" PRIu64 "/permissions",
                             application_id, guild_id, command_id);
}

ORCAcode
discord_edit_application_command_permissions(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  u64_snowflake_t command_id,
  struct discord_edit_application_command_permissions_params *params,
  struct discord_guild_application_command_permissions *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_application_command_permissions, ret);
  struct sized_buffer body;
  char buf[8192];

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, command_id != 0, ORCA_BAD_PARAMETER);

  body.size = discord_edit_application_command_permissions_params_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PUT,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands/%" PRIu64 "/permissions",
                             application_id, guild_id, command_id);
}

ORCAcode
discord_batch_edit_application_command_permissions(
  struct discord *client,
  u64_snowflake_t application_id,
  u64_snowflake_t guild_id,
  struct discord_guild_application_command_permissions **params,
  struct discord_guild_application_command_permissions ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_application_command_permissions, ret);
  struct sized_buffer body;
  char buf[8192];

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_guild_application_command_permissions_list_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PUT,
                             "/applications/%" PRIu64 "/guilds/%" PRIu64
                             "/commands/permissions",
                             application_id, guild_id);
}

/******************************************************************************
 * Functions specific to Discord Audit Log
 ******************************************************************************/

ORCAcode
discord_get_guild_audit_log(struct discord *client,
                            u64_snowflake_t guild_id,
                            struct discord_get_guild_audit_log_params *params,
                            struct discord_audit_log *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_audit_log, ret);
  char query[1024] = "";

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  if (params) {
    size_t offset = 0;

    if (params->user_id) {
      offset += snprintf(query + offset, sizeof(query) - offset,
                         "?user_id=%" PRIu64, params->user_id);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->action_type) {
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "%saction_type=%d",
                 *query ? "&" : "?", params->action_type);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->before) {
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "%sbefore=%" PRIu64,
                 *query ? "&" : "?", params->before);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->limit) {
      offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                         *query ? "&" : "?", params->limit);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
  }

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/audit-logs%s", guild_id,
                             query);
}

/******************************************************************************
 * Functions specific to Discord Channel
 ******************************************************************************/

ORCAcode
discord_get_channel(struct discord *client,
                    u64_snowflake_t channel_id,
                    struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64, channel_id);
}

ORCAcode
discord_modify_channel(struct discord *client,
                       u64_snowflake_t channel_id,
                       struct discord_modify_channel_params *params,
                       struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_modify_channel_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/channels/%" PRIu64, channel_id);
}

ORCAcode
discord_delete_channel(struct discord *client,
                       u64_snowflake_t channel_id,
                       struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64, channel_id);
}

ORCAcode
discord_get_channel_messages(
  struct discord *client,
  u64_snowflake_t channel_id,
  struct discord_get_channel_messages_params *params,
  struct discord_message ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_message, ret);
  char query[1024] = "";

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  if (params) {
    size_t offset = 0;
    if (params->limit) {
      offset += snprintf(query + offset, sizeof(query) - offset, "limit=%d",
                         params->limit);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->around) {
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "%saround=%" PRIu64,
                 *query ? "&" : "", params->around);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->before) {
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "%sbefore=%" PRIu64,
                 *query ? "&" : "", params->before);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->after) {
      offset += snprintf(query + offset, sizeof(query) - offset,
                         "%safter=%" PRIu64, *query ? "&" : "", params->after);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
  }

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64 "/messages%s%s", channel_id,
                             *query ? "?" : "", query);
}

ORCAcode
discord_get_channel_message(struct discord *client,
                            u64_snowflake_t channel_id,
                            u64_snowflake_t message_id,
                            struct discord_message *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_message, ret);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64 "/messages/%" PRIu64,
                             channel_id, message_id);
}

ORCAcode
discord_create_message(struct discord *client,
                       u64_snowflake_t channel_id,
                       struct discord_create_message_params *params,
                       struct discord_message *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_message, ret);
  struct sized_buffer body;
  enum http_method method;
  char buf[16384]; /**< @todo dynamic buffer */

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_create_message_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  if (params->attachments) {
    method = HTTP_MIMEPOST;
    attr.attachments = params->attachments;
  }
  else {
    method = HTTP_POST;
  }

  return discord_adapter_run(&client->adapter, &attr, &body, method,
                             "/channels/%" PRIu64 "/messages", channel_id);
}

ORCAcode
discord_crosspost_message(struct discord *client,
                          u64_snowflake_t channel_id,
                          u64_snowflake_t message_id,
                          struct discord_message *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_message, ret);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_POST,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/crosspost",
                             channel_id, message_id);
}

ORCAcode
discord_create_reaction(struct discord *client,
                        u64_snowflake_t channel_id,
                        u64_snowflake_t message_id,
                        u64_snowflake_t emoji_id,
                        const char emoji_name[])
{
  char *pct_emoji_name;
  char emoji_endpoint[256];
  ORCAcode code;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  pct_emoji_name = emoji_name ? url_encode((char *)emoji_name) : NULL;

  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  code = discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s/@me",
                             channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_own_reaction(struct discord *client,
                            u64_snowflake_t channel_id,
                            u64_snowflake_t message_id,
                            u64_snowflake_t emoji_id,
                            const char emoji_name[])
{
  char *pct_emoji_name;
  char emoji_endpoint[256];
  ORCAcode code;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  pct_emoji_name = emoji_name ? url_encode((char *)emoji_name) : NULL;

  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  code = discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s/@me",
                             channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_user_reaction(struct discord *client,
                             u64_snowflake_t channel_id,
                             u64_snowflake_t message_id,
                             u64_snowflake_t user_id,
                             u64_snowflake_t emoji_id,
                             const char emoji_name[])
{
  char *pct_emoji_name;
  char emoji_endpoint[256];
  ORCAcode code;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);

  pct_emoji_name = emoji_name ? url_encode((char *)emoji_name) : NULL;

  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  code = discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s/%" PRIu64,
                             channel_id, message_id, emoji_endpoint, user_id);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_get_reactions(struct discord *client,
                      u64_snowflake_t channel_id,
                      u64_snowflake_t message_id,
                      u64_snowflake_t emoji_id,
                      const char emoji_name[],
                      struct discord_get_reactions_params *params,
                      struct discord_user ***ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_LIST_INIT(discord_user, ret);
  char query[1024] = "";
  char emoji_endpoint[256];
  char *pct_emoji_name;
  ORCAcode code;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  if (params) {
    size_t len;

    if (params->limit <= 0 || params->limit > 100) {
      logconf_error(&client->conf, "'params.limit' should be between [1-100]");
      return ORCA_BAD_PARAMETER;
    }

    if (params->after) {
      len = query_inject(query, sizeof(query),
                         "(after):F"
                         "(limit):d",
                         &cee_u64tostr, &params->after, &params->limit);
    }
    else {
      len = query_inject(query, sizeof(query), "(limit):d", &params->limit);
    }
    ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
  }

  pct_emoji_name = emoji_name ? url_encode((char *)emoji_name) : NULL;

  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  code = discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s%s",
                             channel_id, message_id, emoji_endpoint, query);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_all_reactions(struct discord *client,
                             u64_snowflake_t channel_id,
                             u64_snowflake_t message_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions",
                             channel_id, message_id);
}

ORCAcode
discord_delete_all_reactions_for_emoji(struct discord *client,
                                       u64_snowflake_t channel_id,
                                       u64_snowflake_t message_id,
                                       u64_snowflake_t emoji_id,
                                       const char emoji_name[])
{
  char *pct_emoji_name;
  char emoji_endpoint[256];
  ORCAcode code;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  pct_emoji_name = emoji_name ? url_encode((char *)emoji_name) : NULL;

  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  code = discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s",
                             channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_edit_message(struct discord *client,
                     u64_snowflake_t channel_id,
                     u64_snowflake_t message_id,
                     struct discord_edit_message_params *params,
                     struct discord_message *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_message, ret);
  struct sized_buffer body;
  char buf[16384]; /**< @todo dynamic buffer */

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_edit_message_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/channels/%" PRIu64 "/messages/%" PRIu64,
                             channel_id, message_id);
}

ORCAcode
discord_delete_message(struct discord *client,
                       u64_snowflake_t channel_id,
                       u64_snowflake_t message_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64,
                             channel_id, message_id);
}

/** @todo add duplicated ID verification */
ORCAcode
discord_bulk_delete_messages(struct discord *client,
                             u64_snowflake_t channel_id,
                             u64_snowflake_t **messages)
{
  u64_unix_ms_t now = discord_timestamp(client);
  struct sized_buffer body;
  char *buf = NULL;
  ORCAcode code;
  size_t count;
  int i;

  ORCA_EXPECT(client, messages != NULL, ORCA_BAD_PARAMETER);

  count = ntl_length_max((ntl_t)messages, 101);
  ORCA_EXPECT(client, count >= 2 && count <= 100, ORCA_BAD_PARAMETER);

  for (i = 0; i < count; ++i) {
    u64_unix_ms_t tstamp = (*messages[i] >> 22) + 1420070400000;

    ORCA_EXPECT(client, now <= tstamp || now - tstamp <= 1209600000,
                ORCA_BAD_PARAMETER,
                "Messages should not be older than 2 weeks.");
  }

  body.size =
    json_ainject(&buf, "(messages):F", ja_u64_list_to_json, messages);
  body.start = buf;

  ORCA_EXPECT(client, buf != NULL, ORCA_BAD_JSON);

  code = discord_adapter_run(&client->adapter, NULL, &body, HTTP_POST,
                             "/channels/%" PRIu64 "/messages/bulk-delete",
                             channel_id);

  free(buf);

  return code;
}

ORCAcode
discord_edit_channel_permissions(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t overwrite_id,
  struct discord_edit_channel_permissions_params *params)
{
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, overwrite_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_edit_channel_permissions_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, NULL, &body, HTTP_PUT,
                             "/channels/%" PRIu64 "/permissions/%" PRIu64,
                             channel_id, overwrite_id);
}

ORCAcode
discord_get_channel_invites(struct discord *client,
                            u64_snowflake_t channel_id,
                            struct discord_invite ***ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_invite, ret);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64 "/invites", channel_id);
}

ORCAcode
discord_create_channel_invite(
  struct discord *client,
  u64_snowflake_t channel_id,
  struct discord_create_channel_invite_params *params,
  struct discord_invite *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_invite, ret);
  struct sized_buffer body;
  char buf[1024];
  size_t len;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);

  if (params)
    len =
      discord_create_channel_invite_params_to_json(buf, sizeof(buf), params);
  else
    len = sprintf(buf, "{}");
  body.start = buf;
  body.size = len;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/channels/%" PRIu64 "/invites", channel_id);
}

ORCAcode
discord_delete_channel_permission(struct discord *client,
                                  u64_snowflake_t channel_id,
                                  u64_snowflake_t overwrite_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, overwrite_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/permissions/%" PRIu64,
                             channel_id, overwrite_id);
}

ORCAcode
discord_follow_news_channel(struct discord *client,
                            u64_snowflake_t channel_id,
                            struct discord_follow_news_channel_params *params,
                            struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);
  struct sized_buffer body;
  char buf[256]; /* should be more than enough for this */

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params->webhook_channel_id != 0, ORCA_BAD_PARAMETER);

  body.size =
    discord_follow_news_channel_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/channels/%" PRIu64 "/followers", channel_id);
}

ORCAcode
discord_trigger_typing_indicator(struct discord *client,
                                 u64_snowflake_t channel_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_POST,
                             "/channels/%" PRIu64 "/typing", channel_id);
}

ORCAcode
discord_get_pinned_messages(struct discord *client,
                            u64_snowflake_t channel_id,
                            struct discord_message ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_message, ret);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64 "/pins", channel_id);
}

ORCAcode
discord_pin_message(struct discord *client,
                    u64_snowflake_t channel_id,
                    u64_snowflake_t message_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/channels/%" PRIu64 "/pins/%" PRIu64, channel_id,
                             message_id);
}

ORCAcode
discord_unpin_message(struct discord *client,
                      u64_snowflake_t channel_id,
                      u64_snowflake_t message_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/pins/%" PRIu64, channel_id,
                             message_id);
}

ORCAcode
discord_group_dm_add_recipient(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t user_id,
  struct discord_group_dm_add_recipient_params *params)
{
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_group_dm_add_recipient_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, NULL, &body, HTTP_PUT,
                             "/channels/%" PRIu64 "/recipients/%" PRIu64,
                             channel_id, user_id);
}

ORCAcode
discord_group_dm_remove_recipient(struct discord *client,
                                  u64_snowflake_t channel_id,
                                  u64_snowflake_t user_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/recipients/%" PRIu64,
                             channel_id, user_id);
}

ORCAcode
discord_start_thread_with_message(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t message_id,
  struct discord_start_thread_with_message_params *params,
  struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_start_thread_with_message_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/threads",
                             channel_id, message_id);
}

ORCAcode
discord_start_thread_without_message(
  struct discord *client,
  u64_snowflake_t channel_id,
  struct discord_start_thread_without_message_params *params,
  struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_start_thread_without_message_params_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/channels/%" PRIu64 "/threads", channel_id);
}

ORCAcode
discord_join_thread(struct discord *client, u64_snowflake_t channel_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/channels/%" PRIu64 "/thread-members/@me",
                             channel_id);
}

ORCAcode
discord_add_thread_member(struct discord *client,
                          u64_snowflake_t channel_id,
                          u64_snowflake_t user_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/channels/%" PRIu64 "/thread-members/" PRIu64,
                             channel_id, user_id);
}

ORCAcode
discord_leave_thread(struct discord *client, u64_snowflake_t channel_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/thread-members/@me",
                             channel_id);
}

ORCAcode
discord_remove_thread_member(struct discord *client,
                             u64_snowflake_t channel_id,
                             u64_snowflake_t user_id)
{
  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/thread-members/" PRIu64,
                             channel_id, user_id);
}

ORCAcode
discord_list_thread_members(struct discord *client,
                            u64_snowflake_t channel_id,
                            struct discord_thread_member ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_thread_member, ret);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64 "/thread-members",
                             channel_id);
}

ORCAcode
discord_list_active_threads(struct discord *client,
                            u64_snowflake_t channel_id,
                            struct discord_thread_response_body *body)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_thread_response_body, body);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, body != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64 "/threads/active",
                             channel_id);
}

ORCAcode
discord_list_public_archived_threads(struct discord *client,
                                     u64_snowflake_t channel_id,
                                     u64_unix_ms_t before,
                                     int limit,
                                     struct discord_thread_response_body *body)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_thread_response_body, body);
  char query[1024] = "";
  size_t offset = 0;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, body != NULL, ORCA_BAD_PARAMETER);

  if (before) {
    offset += snprintf(query + offset, sizeof(query) - offset,
                       "before=%" PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                       *query ? "&" : "", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64
                             "/threads/archived/public%s%s",
                             channel_id, *query ? "?" : "", query);
}

ORCAcode
discord_list_private_archived_threads(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_unix_ms_t before,
  int limit,
  struct discord_thread_response_body *body)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_thread_response_body, body);
  char query[1024] = "";
  size_t offset = 0;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, body != NULL, ORCA_BAD_PARAMETER);

  if (before) {
    offset += snprintf(query + offset, sizeof(query) - offset,
                       "before=%" PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                       *query ? "&" : "", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64
                             "/threads/archived/private%s%s",
                             channel_id, *query ? "?" : "", query);
}

ORCAcode
discord_list_joined_private_archived_threads(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_unix_ms_t before,
  int limit,
  struct discord_thread_response_body *body)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_thread_response_body, body);
  char query[1024] = "";
  size_t offset = 0;

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, body != NULL, ORCA_BAD_PARAMETER);

  if (before) {
    offset += snprintf(query + offset, sizeof(query) - offset,
                       "before=%" PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                       *query ? "&" : "", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64
                             "/users/@me/threads/archived/private%s%s",
                             channel_id, *query ? "?" : "", query);
}

/******************************************************************************
 * Functions specific to Discord Emoji
 ******************************************************************************/

ORCAcode
discord_list_guild_emojis(struct discord *client,
                          u64_snowflake_t guild_id,
                          struct discord_emoji ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_emoji, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/emojis", guild_id);
}

ORCAcode
discord_get_guild_emoji(struct discord *client,
                        u64_snowflake_t guild_id,
                        u64_snowflake_t emoji_id,
                        struct discord_emoji *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_emoji, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, emoji_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id,
                             emoji_id);
}

ORCAcode
discord_create_guild_emoji(struct discord *client,
                           u64_snowflake_t guild_id,
                           struct discord_create_guild_emoji_params *params,
                           struct discord_emoji *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_emoji, ret);
  struct sized_buffer body;
  char buf[2048];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_create_guild_emoji_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/guilds/%" PRIu64 "/emojis", guild_id);
}

ORCAcode
discord_modify_guild_emoji(struct discord *client,
                           u64_snowflake_t guild_id,
                           u64_snowflake_t emoji_id,
                           struct discord_modify_guild_emoji_params *params,
                           struct discord_emoji *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_emoji, ret);
  struct sized_buffer body;
  char buf[2048];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, emoji_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_modify_guild_emoji_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id,
                             emoji_id);
}

ORCAcode
discord_delete_guild_emoji(struct discord *client,
                           u64_snowflake_t guild_id,
                           u64_snowflake_t emoji_id)
{
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, emoji_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id,
                             emoji_id);
}

/******************************************************************************
 * Functions specific to Discord Gateway
 ******************************************************************************/

ORCAcode
discord_get_gateway(struct discord *client, struct sized_buffer *ret)
{
  struct discord_request_attr attr = { ret, sizeof(struct sized_buffer), NULL,
                                       (void (*)(char *, size_t, void *))
                                         & cee_sized_buffer_from_json };

  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/gateway");
}

ORCAcode
discord_get_gateway_bot(struct discord *client, struct sized_buffer *ret)
{
  struct discord_request_attr attr = { ret, sizeof(struct sized_buffer), NULL,
                                       (void (*)(char *, size_t, void *))
                                         & cee_sized_buffer_from_json };

  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/gateway/bot");
}

/******************************************************************************
 * Functions specific to Discord Guild Template
 ******************************************************************************/

ORCAcode
discord_get_guild_template(struct discord *client,
                           char *code,
                           struct discord_guild_template *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_template, ret);

  ORCA_EXPECT(client, !IS_EMPTY_STRING(code), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/templates/%s", code);
}

ORCAcode
discord_create_guild_template(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_create_guild_template_params *params,
  struct discord_guild_template *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_template, ret);
  struct sized_buffer body;
  char buf[256];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_create_guild_template_params_to_json_v(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/guilds/%" PRIu64 "/templates", guild_id);
}

ORCAcode
discord_sync_guild_template(struct discord *client,
                            u64_snowflake_t guild_id,
                            char *code,
                            struct discord_guild_template *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_template, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_PUT,
                             "/guilds/%" PRIu64 "/templates/%s", guild_id,
                             code);
}

/******************************************************************************
 * Functions specific to Discord Guild
 ******************************************************************************/

ORCAcode
discord_create_guild(struct discord *client,
                     struct discord_create_guild_params *params,
                     struct discord_guild *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_guild, ret);
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_create_guild_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/guilds");
}

ORCAcode
discord_get_guild(struct discord *client,
                  u64_snowflake_t guild_id,
                  struct discord_guild *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_guild, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64, guild_id);
}

ORCAcode
discord_get_guild_preview(struct discord *client,
                          u64_snowflake_t guild_id,
                          struct discord_guild_preview *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_preview, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/preview", guild_id);
}

ORCAcode
discord_modify_guild(struct discord *client,
                     u64_snowflake_t guild_id,
                     struct discord_modify_guild_params *params,
                     struct discord_guild *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_guild, ret);
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_modify_guild_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64, guild_id);
}

ORCAcode
discord_delete_guild(struct discord *client, u64_snowflake_t guild_id)
{
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64, guild_id);
}

ORCAcode
discord_get_guild_channels(struct discord *client,
                           u64_snowflake_t guild_id,
                           struct discord_channel ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_channel, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/channels", guild_id);
}

ORCAcode
discord_create_guild_channel(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_create_guild_channel_params *params,
  struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);
  struct sized_buffer body;
  char buf[2048];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_create_guild_channel_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/guilds/%" PRIu64 "/channels", guild_id);
}

ORCAcode
discord_modify_guild_channel_positions(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_modify_guild_channel_positions_params **params)
{
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_modify_guild_channel_positions_params_list_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, NULL, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64 "/channels", guild_id);
}

ORCAcode
discord_get_guild_member(struct discord *client,
                         u64_snowflake_t guild_id,
                         u64_snowflake_t user_id,
                         struct discord_guild_member *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_member, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                             user_id);
}

ORCAcode
discord_list_guild_members(struct discord *client,
                           u64_snowflake_t guild_id,
                           struct discord_list_guild_members_params *params,
                           struct discord_guild_member ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_guild_member, ret);
  char query[1024] = "";

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  if (params) {
    size_t offset = 0;

    if (params->limit) {
      offset += snprintf(query + offset, sizeof(query) - offset, "limit=%d",
                         params->limit);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->after) {
      offset += snprintf(query + offset, sizeof(query) - offset,
                         "%safter=%" PRIu64, *query ? "&" : "", params->after);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
  }

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/members%s%s", guild_id,
                             *query ? "?" : "", query);
}

ORCAcode
discord_search_guild_members(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_search_guild_members_params *params,
  struct discord_guild_member ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_guild_member, ret);
  char query[1024] = "";

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  if (params) {
    size_t offset = 0;
    if (params->query) {
      char *pe_query = url_encode(params->query);

      offset +=
        snprintf(query + offset, sizeof(query) - offset, "query=%s", pe_query);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");

      free(pe_query);
    }
    if (params->limit) {
      offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                         *query ? "&" : "", params->limit);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
  }

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/members/search%s%s",
                             guild_id, *query ? "?" : "", query);
}

ORCAcode
discord_add_guild_member(struct discord *client,
                         u64_snowflake_t guild_id,
                         u64_snowflake_t user_id,
                         struct discord_add_guild_member_params *params,
                         struct discord_guild_member *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_member, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params->access_token != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_add_guild_member_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PUT,
                             "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                             user_id);
}

ORCAcode
discord_modify_guild_member(struct discord *client,
                            u64_snowflake_t guild_id,
                            u64_snowflake_t user_id,
                            struct discord_modify_guild_member_params *params,
                            struct discord_guild_member *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_member, ret);
  struct sized_buffer body;
  char buf[2048];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_modify_guild_member_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                             user_id);
}
ORCAcode
discord_modify_current_member(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_modify_current_member_params *params,
  struct discord_guild_member *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_member, ret);
  struct sized_buffer body;
  char buf[512];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params->nick != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_modify_current_member_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64 "/members/@me", guild_id);
}
ORCAcode
discord_modify_current_user_nick(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_modify_current_user_nick_params *params,
  struct discord_guild_member *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_member, ret);
  struct sized_buffer body;
  char buf[512];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params->nick != NULL, ORCA_BAD_PARAMETER);

  logconf_warn(&client->conf,
               "This endpoint is now deprecated by Discord. Please use "
               "discord_modify_current_member instead");

  body.size =
    discord_modify_current_user_nick_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64 "/members/@me/nick", guild_id);
}

ORCAcode
discord_add_guild_member_role(struct discord *client,
                              u64_snowflake_t guild_id,
                              u64_snowflake_t user_id,
                              u64_snowflake_t role_id)
{
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, role_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/guilds/%" PRIu64 "/members/%" PRIu64
                             "/roles/%" PRIu64,
                             guild_id, user_id, role_id);
}

ORCAcode
discord_remove_guild_member_role(struct discord *client,
                                 u64_snowflake_t guild_id,
                                 u64_snowflake_t user_id,
                                 u64_snowflake_t role_id)
{
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, role_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/members/%" PRIu64
                             "/roles/%" PRIu64,
                             guild_id, user_id, role_id);
}

ORCAcode
discord_remove_guild_member(struct discord *client,
                            u64_snowflake_t guild_id,
                            u64_snowflake_t user_id)
{
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                             user_id);
}

ORCAcode
discord_get_guild_bans(struct discord *client,
                       u64_snowflake_t guild_id,
                       struct discord_ban ***ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_LIST_INIT(discord_ban, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/bans", guild_id);
}

ORCAcode
discord_get_guild_ban(struct discord *client,
                      u64_snowflake_t guild_id,
                      u64_snowflake_t user_id,
                      struct discord_ban *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_ban, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                             user_id);
}

ORCAcode
discord_create_guild_ban(struct discord *client,
                         u64_snowflake_t guild_id,
                         u64_snowflake_t user_id,
                         struct discord_create_guild_ban_params *params)
{
  struct sized_buffer body;
  char buf[256];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client,
              params->delete_message_days >= 0
                && params->delete_message_days <= 7,
              ORCA_BAD_PARAMETER);

  body.size =
    discord_create_guild_ban_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, NULL, &body, HTTP_PUT,
                             "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                             user_id);
}
ORCAcode
discord_remove_guild_ban(struct discord *client,
                         u64_snowflake_t guild_id,
                         u64_snowflake_t user_id)
{
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                             user_id);
}

ORCAcode
discord_get_guild_roles(struct discord *client,
                        u64_snowflake_t guild_id,
                        struct discord_role ***ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_LIST_INIT(discord_role, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/roles", guild_id);
}

ORCAcode
discord_create_guild_role(struct discord *client,
                          u64_snowflake_t guild_id,
                          struct discord_create_guild_role_params *params,
                          struct discord_role *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_role, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);

  body.size =
    discord_create_guild_role_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/guilds/%" PRIu64 "/roles", guild_id);
}

ORCAcode
discord_modify_guild_role_positions(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_modify_guild_role_positions_params **params,
  struct discord_role ***ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_LIST_INIT(discord_role, ret);
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_modify_guild_role_positions_params_list_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64 "/roles", guild_id);
}

ORCAcode
discord_modify_guild_role(struct discord *client,
                          u64_snowflake_t guild_id,
                          u64_snowflake_t role_id,
                          struct discord_modify_guild_role_params *params,
                          struct discord_role *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_role, ret);
  struct sized_buffer body;
  char buf[2048] = "{}";
  size_t len;

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, role_id != 0, ORCA_BAD_PARAMETER);

  if (params)
    len = discord_modify_guild_role_params_to_json(buf, sizeof(buf), params);
  else
    len = sprintf(buf, "{}");
  body.size = len;
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                             role_id);
}

ORCAcode
discord_delete_guild_role(struct discord *client,
                          u64_snowflake_t guild_id,
                          u64_snowflake_t role_id)
{
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, role_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                             role_id);
}
ORCAcode
discord_begin_guild_prune(struct discord *client,
                          u64_snowflake_t guild_id,
                          struct discord_begin_guild_prune_params *params)
{
  struct sized_buffer body;
  char buf[4096];
  size_t len;

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);

  if (params)
    len = discord_begin_guild_prune_params_to_json(buf, sizeof(buf), params);
  else
    len = sprintf(buf, "{}");
  body.size = len;
  body.start = buf;

  return discord_adapter_run(&client->adapter, NULL, &body, HTTP_POST,
                             "/guilds/%" PRIu64 "/prune", guild_id);
}

ORCAcode
discord_get_guild_invites(struct discord *client,
                          u64_snowflake_t guild_id,
                          struct discord_invite ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_invite, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/invites", guild_id);
}

ORCAcode
discord_delete_guild_integrations(struct discord *client,
                                  u64_snowflake_t guild_id,
                                  u64_snowflake_t integration_id)
{
  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, integration_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/integrations/%" PRIu64,
                             guild_id, integration_id);
}

ORCAcode
discord_get_guild_vanity_url(struct discord *client,
                             u64_snowflake_t guild_id,
                             struct discord_invite *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_invite, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/vanity-url", guild_id);
}

ORCAcode
discord_get_guild_welcome_screen(struct discord *client,
                                 u64_snowflake_t guild_id,
                                 struct discord_welcome_screen *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_welcome_screen, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/welcome-screen", guild_id);
}

/******************************************************************************
 * Functions specific to Discord Interaction
 ******************************************************************************/

ORCAcode
discord_create_interaction_response(
  struct discord *client,
  u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_interaction_response *params,
  struct discord_interaction_response *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_interaction_response, ret);
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, interaction_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(interaction_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_interaction_response_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/interactions/%" PRIu64 "/%s/callback",
                             interaction_id, interaction_token);
}

ORCAcode
discord_get_original_interaction_response(
  struct discord *client,
  u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_interaction_response *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_interaction_response, ret);

  ORCA_EXPECT(client, interaction_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(interaction_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/webhooks/%" PRIu64 "/%s/messages/@original",
                             interaction_id, interaction_token);
}

ORCAcode
discord_edit_original_interaction_response(
  struct discord *client,
  u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_edit_original_interaction_response_params *params,
  struct discord_interaction_response *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_interaction_response, ret);
  struct sized_buffer body;
  enum http_method method;
  char buf[16384]; /**< @todo dynamic buffer */

  ORCA_EXPECT(client, interaction_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(interaction_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_edit_original_interaction_response_params_to_json(
    buf, sizeof(buf), params);
  body.start = buf;

  if (params->attachments) {
    method = HTTP_MIMEPOST;
    attr.attachments = params->attachments;
  }
  else {
    method = HTTP_POST;
  }

  return discord_adapter_run(&client->adapter, &attr, &body, method,
                             "/webhooks/%" PRIu64 "/%s/messages/@original",
                             interaction_id, interaction_token);
}

ORCAcode
discord_delete_original_interaction_response(
  struct discord *client,
  u64_snowflake_t interaction_id,
  const char interaction_token[])
{
  ORCA_EXPECT(client, interaction_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(interaction_token), ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64 "/%s/messages/@original",
                             interaction_id, interaction_token);
}

ORCAcode
discord_create_followup_message(
  struct discord *client,
  u64_snowflake_t application_id,
  const char interaction_token[],
  struct discord_create_followup_message_params *params,
  struct discord_webhook *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_webhook, ret);
  struct sized_buffer body;
  enum http_method method;
  char buf[16384]; /**< @todo dynamic buffer */
  char query[4096] = "";

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(interaction_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  if (params->thread_id) {
    size_t ret;

    ret =
      snprintf(query, sizeof(query), "thread_id=%" PRIu64, params->thread_id);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }

  body.size =
    discord_create_followup_message_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  if (params->attachments) {
    method = HTTP_MIMEPOST;
    attr.attachments = params->attachments;
  }
  else {
    method = HTTP_POST;
  }

  return discord_adapter_run(&client->adapter, &attr, &body, method,
                             "/webhooks/%" PRIu64 "/%s%s%s", application_id,
                             interaction_token, *query ? "?" : "", query);
}

ORCAcode
discord_get_followup_message(struct discord *client,
                             u64_snowflake_t application_id,
                             const char interaction_token[],
                             u64_snowflake_t message_id,
                             struct discord_message *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_message, ret);

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(interaction_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/webhooks/%" PRIu64 "/%s/%" PRIu64,
                             application_id, interaction_token, message_id);
}

ORCAcode
discord_edit_followup_message(
  struct discord *client,
  u64_snowflake_t application_id,
  const char interaction_token[],
  u64_snowflake_t message_id,
  struct discord_edit_followup_message_params *params,
  struct discord_message *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_message, ret);
  struct sized_buffer body;
  enum http_method method;
  char buf[16384]; /**< @todo dynamic buffer */

  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(interaction_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_edit_followup_message_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  if (params->attachments) {
    method = HTTP_MIMEPOST;
    attr.attachments = params->attachments;
  }
  else {
    method = HTTP_POST;
  }

  return discord_adapter_run(&client->adapter, &attr, &body, method,
                             "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                             application_id, interaction_token, message_id);
}

ORCAcode
discord_delete_followup_message(struct discord *client,
                                u64_snowflake_t application_id,
                                const char interaction_token[],
                                u64_snowflake_t message_id)
{
  ORCA_EXPECT(client, application_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(interaction_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                             application_id, interaction_token, message_id);
}

/******************************************************************************
 * Functions specific to Discord Invite
 ******************************************************************************/

ORCAcode
discord_get_invite(struct discord *client,
                   char *invite_code,
                   struct discord_get_invite_params *params,
                   struct discord_invite *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_invite, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, !IS_EMPTY_STRING(invite_code), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_get_invite_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_GET,
                             "/invites/%s", invite_code);
}

ORCAcode
discord_delete_invite(struct discord *client,
                      char *invite_code,
                      struct discord_invite *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_invite, ret);

  ORCA_EXPECT(client, !IS_EMPTY_STRING(invite_code), ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_DELETE,
                             "/invites/%s", invite_code);
}

/******************************************************************************
 * Functions specific to Discord User
 ******************************************************************************/

ORCAcode
discord_get_current_user(struct discord *client, struct discord_user *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_user, ret);

  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/users/@me");
}

ORCAcode
discord_get_user(struct discord *client,
                 u64_snowflake_t user_id,
                 struct discord_user *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_user, ret);

  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/users/%" PRIu64, user_id);
}

ORCAcode
discord_modify_current_user(struct discord *client,
                            struct discord_modify_current_user_params *params,
                            struct discord_user *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_user, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_modify_current_user_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/users/@me");
}

ORCAcode
discord_get_current_user_guilds(struct discord *client,
                                struct discord_guild ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_guild, ret);

  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/users/@me/guilds");
}

ORCAcode
discord_leave_guild(struct discord *client, u64_snowflake_t guild_id)
{
  struct sized_buffer body = { "{}", 2 };

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, &body, HTTP_DELETE,
                             "/users/@me/guilds/%" PRIu64, guild_id);
}

ORCAcode
discord_create_dm(struct discord *client,
                  struct discord_create_dm_params *params,
                  struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);
  struct sized_buffer body;
  char buf[128];

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_create_dm_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/users/@me/channels");
}

ORCAcode
discord_create_group_dm(struct discord *client,
                        struct discord_create_group_dm_params *params,
                        struct discord_channel *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_channel, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params->access_tokens != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params->nicks != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_create_group_dm_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/users/@me/channels");
}

ORCAcode
discord_get_user_connections(struct discord *client,
                             struct discord_connection ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_connection, ret);

  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/users/@me/connections");
}

/******************************************************************************
 * Functions specific to Discord Voice
 ******************************************************************************/

ORCAcode
discord_list_voice_regions(struct discord *client,
                           struct discord_voice_region ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_voice_region, ret);

  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/voice/regions");
}

/******************************************************************************
 * Functions specific to Discord Webhook
 ******************************************************************************/

ORCAcode
discord_create_webhook(struct discord *client,
                       u64_snowflake_t channel_id,
                       struct discord_create_webhook_params *params,
                       struct discord_webhook *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_webhook, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->name), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  body.size = discord_create_webhook_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                             "/channels/%" PRIu64 "/webhooks", channel_id);
}

ORCAcode
discord_get_channel_webhooks(struct discord *client,
                             u64_snowflake_t channel_id,
                             struct discord_webhook ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_webhook, ret);

  ORCA_EXPECT(client, channel_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/channels/%" PRIu64 "/webhooks", channel_id);
}

ORCAcode
discord_get_guild_webhooks(struct discord *client,
                           u64_snowflake_t guild_id,
                           struct discord_webhook ***ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_LIST_INIT(discord_webhook, ret);

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/webhooks", guild_id);
}

ORCAcode
discord_get_webhook(struct discord *client,
                    u64_snowflake_t webhook_id,
                    struct discord_webhook *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_webhook, ret);

  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/webhooks/%" PRIu64, webhook_id);
}

ORCAcode
discord_get_webhook_with_token(struct discord *client,
                               u64_snowflake_t webhook_id,
                               const char webhook_token[],
                               struct discord_webhook *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_webhook, ret);

  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(webhook_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/webhooks/%" PRIu64 "/%s", webhook_id,
                             webhook_token);
}

ORCAcode
discord_modify_webhook(struct discord *client,
                       u64_snowflake_t webhook_id,
                       struct discord_modify_webhook_params *params,
                       struct discord_webhook *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_webhook, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);

  body.size = discord_modify_webhook_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/webhooks/%" PRIu64, webhook_id);
}

ORCAcode
discord_modify_webhook_with_token(
  struct discord *client,
  u64_snowflake_t webhook_id,
  const char webhook_token[],
  struct discord_modify_webhook_with_token_params *params,
  struct discord_webhook *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_webhook, ret);
  struct sized_buffer body;
  char buf[1024];

  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(webhook_token), ORCA_BAD_PARAMETER);

  body.size =
    discord_modify_webhook_with_token_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/webhooks/%" PRIu64 "/%s", webhook_id,
                             webhook_token);
}

ORCAcode
discord_delete_webhook(struct discord *client,
                       u64_snowflake_t webhook_id)
{
  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64, webhook_id);
}

ORCAcode
discord_delete_webhook_with_token(struct discord *client,
                                  u64_snowflake_t webhook_id,
                                  const char webhook_token[])
{
  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(webhook_token), ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64 "/%s", webhook_id,
                             webhook_token);
}

ORCAcode
discord_execute_webhook(struct discord *client,
                        u64_snowflake_t webhook_id,
                        const char webhook_token[],
                        struct discord_execute_webhook_params *params,
                        struct discord_webhook *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_webhook, ret);
  struct sized_buffer body;
  enum http_method method;
  char buf[16384]; /**< @todo dynamic buffer */
  char query[4096] = "";
  size_t len = 0;

  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(webhook_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  if (params->wait) {
    len = snprintf(query, sizeof(query), "wait=1");
    ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
  }
  if (params->thread_id) {
    len += snprintf(query + len, sizeof(query) - len, "%sthread_id=%" PRIu64,
                    len ? "&" : "", params->thread_id);
    ASSERT_S(len < sizeof(query), "Out of bounds write attempt");
  }

  body.size = discord_execute_webhook_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  if (params->attachments) {
    method = HTTP_MIMEPOST;
    attr.attachments = params->attachments;
  }
  else {
    method = HTTP_POST;
  }

  return discord_adapter_run(&client->adapter, &attr, &body, method,
                             "/webhooks/%" PRIu64 "/%s%s%s", webhook_id,
                             webhook_token, *query ? "?" : "", query);
}

ORCAcode
discord_get_webhook_message(struct discord *client,
                            u64_snowflake_t webhook_id,
                            const char webhook_token[],
                            u64_snowflake_t message_id,
                            struct discord_message *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_message, ret);

  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(webhook_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                             "/webhooks/%" PRIu64 "/%s/%" PRIu64, webhook_id,
                             webhook_token, message_id);
}

ORCAcode
discord_edit_webhook_message(
  struct discord *client,
  u64_snowflake_t webhook_id,
  const char webhook_token[],
  u64_snowflake_t message_id,
  struct discord_edit_webhook_message_params *params,
  struct discord_message *ret)
{
  struct discord_request_attr attr = REQUEST_ATTR_INIT(discord_message, ret);
  struct sized_buffer body;
  enum http_method method;
  char buf[16384]; /**< @todo dynamic buffer */

  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(webhook_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);

  body.size =
    discord_edit_webhook_message_params_to_json(buf, sizeof(buf), params);
  body.start = buf;

  if (params->attachments) {
    method = HTTP_MIMEPOST;
    attr.attachments = params->attachments;
  }
  else {
    method = HTTP_POST;
  }

  return discord_adapter_run(&client->adapter, &attr, &body, method,
                             "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                             webhook_id, webhook_token, message_id);
}

ORCAcode
discord_delete_webhook_message(struct discord *client,
                               u64_snowflake_t webhook_id,
                               const char webhook_token[],
                               u64_snowflake_t message_id)
{
  ORCA_EXPECT(client, webhook_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(webhook_token), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, message_id != 0, ORCA_BAD_PARAMETER);

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                             webhook_id, webhook_token, message_id);
}

/******************************************************************************
 * Miscellaneous
 ******************************************************************************/

ORCAcode
discord_disconnect_guild_member(struct discord *client,
                                u64_snowflake_t guild_id,
                                u64_snowflake_t user_id,
                                struct discord_guild_member *ret)
{
  struct discord_request_attr attr =
    REQUEST_ATTR_INIT(discord_guild_member, ret);
  struct sized_buffer body;
  char buf[128];

  ORCA_EXPECT(client, guild_id != 0, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, user_id != 0, ORCA_BAD_PARAMETER);

  body.size = json_inject(buf, sizeof(buf), "(channel_id):null");
  body.start = buf;

  return discord_adapter_run(&client->adapter, &attr, &body, HTTP_PATCH,
                             "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                             user_id);
}
