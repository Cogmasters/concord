#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_create_webhook(struct discord *client,
                       const u64_snowflake_t channel_id,
                       struct discord_create_webhook_params *params,
                       struct discord_webhook *p_webhook)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params || IS_EMPTY_STRING(params->name)) {
    logconf_error(client->conf, "Missing 'params.name'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_webhook) {
    logconf_error(client->conf, "Missing 'p_webhook'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret =
    discord_create_webhook_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_webhook_from_json_v,
                              .ok_obj = &p_webhook },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/channels/%" PRIu64 "/webhooks", channel_id);
}

ORCAcode
discord_get_channel_webhooks(struct discord *client,
                             const u64_snowflake_t channel_id,
                             NTL_T(struct discord_webhook) * p_webhooks)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_webhooks) {
    logconf_error(client->conf, "Missing 'p_webhooks'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_webhook_list_from_json_v,
                              .ok_obj = p_webhooks },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/webhooks", channel_id);
}

ORCAcode
discord_get_guild_webhooks(struct discord *client,
                           const u64_snowflake_t guild_id,
                           NTL_T(struct discord_webhook) * p_webhooks)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_webhooks) {
    logconf_error(client->conf, "Missing 'p_webhooks'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_webhook_list_from_json_v,
                              .ok_obj = p_webhooks },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/webhooks", guild_id);
}

ORCAcode
discord_get_webhook(struct discord *client,
                    const u64_snowflake_t webhook_id,
                    struct discord_webhook *p_webhook)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_webhook) {
    logconf_error(client->conf, "Missing 'p_webhook'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_webhook_from_json_v,
                              .ok_obj = &p_webhook },
    NULL, HTTP_GET, "/webhooks/%" PRIu64, webhook_id);
}

ORCAcode
discord_get_webhook_with_token(struct discord *client,
                               const u64_snowflake_t webhook_id,
                               const char webhook_token[],
                               struct discord_webhook *p_webhook)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(webhook_token)) {
    logconf_error(client->conf, "Missing 'webhook_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_webhook) {
    logconf_error(client->conf, "Missing 'p_webhook'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_webhook_from_json_v,
                              .ok_obj = &p_webhook },
    NULL, HTTP_GET, "/webhooks/%" PRIu64 "/%s", webhook_id, webhook_token);
}

ORCAcode
discord_modify_webhook(struct discord *client,
                       const u64_snowflake_t webhook_id,
                       struct discord_modify_webhook_params *params,
                       struct discord_webhook *p_webhook)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret =
    discord_modify_webhook_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_webhook_from_json_v,
                              .ok_obj = &p_webhook },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH, "/webhooks/%" PRIu64,
    webhook_id);
}

ORCAcode
discord_modify_webhook_with_token(
  struct discord *client,
  const u64_snowflake_t webhook_id,
  const char webhook_token[],
  struct discord_modify_webhook_with_token_params *params,
  struct discord_webhook *p_webhook)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(webhook_token)) {
    logconf_error(client->conf, "Missing 'webhook_token'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret = discord_modify_webhook_with_token_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_webhook_from_json_v,
                              .ok_obj = &p_webhook },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/webhooks/%" PRIu64 "/%s", webhook_id, webhook_token);
}

ORCAcode
discord_delete_webhook(struct discord *client,
                       const u64_snowflake_t webhook_id)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64, webhook_id);
}

ORCAcode
discord_delete_webhook_with_token(struct discord *client,
                                  const u64_snowflake_t webhook_id,
                                  const char webhook_token[])
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(webhook_token)) {
    logconf_error(client->conf, "Missing 'webhook_token'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64 "/%s", webhook_id,
                             webhook_token);
}

ORCAcode
discord_execute_webhook(struct discord *client,
                        const u64_snowflake_t webhook_id,
                        const char webhook_token[],
                        struct discord_execute_webhook_params *params,
                        struct discord_webhook *p_webhook)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(webhook_token)) {
    logconf_error(client->conf, "Missing 'webhook_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[4096] = "";
  size_t ret = 0;

  if (params->wait) {
    ret = snprintf(query, sizeof(query), "wait=1");
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
  if (params->thread_id) {
    ret += snprintf(query + ret, sizeof(query) - ret, "%sthread_id=%" PRIu64,
                    ret ? "&" : "", params->thread_id);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_webhook ? &discord_webhook_from_json_v : NULL,
    .ok_obj = &p_webhook
  };

  char payload[16384]; /**< @todo dynamic buffer */
  ret =
    discord_execute_webhook_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer body = { payload, ret };

  /* content-type is application/json */
  if (!params->attachments) {

    return discord_adapter_run(&client->adapter, &resp_handle, &body,
                               HTTP_POST, "/webhooks/%" PRIu64 "/%s%s%s",
                               webhook_id, webhook_token, *query ? "?" : "",
                               query);
  }

  /* content-type is multipart/form-data */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");
  ua_curl_mime_setopt(client->adapter.ua,
                      (void *[2]){ params->attachments, &body },
                      &_discord_params_to_mime);

  ORCAcode code;
  code =
    discord_adapter_run(&client->adapter, &resp_handle, NULL, HTTP_MIMEPOST,
                        "/webhooks/%" PRIu64 "/%s%s%s", webhook_id,
                        webhook_token, *query ? "?" : "", query);

  /*set back to default */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");

  return code;
}

ORCAcode
discord_get_webhook_message(struct discord *client,
                            const u64_snowflake_t webhook_id,
                            const char webhook_token[],
                            const u64_snowflake_t message_id,
                            struct discord_message *p_message)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(webhook_token)) {
    logconf_error(client->conf, "Missing 'webhook_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_message) {
    logconf_error(client->conf, "Missing 'p_message'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_message_from_json_v,
                              .ok_obj = &p_message },
    NULL, HTTP_GET, "/webhooks/%" PRIu64 "/%s/%" PRIu64, webhook_id,
    webhook_token, message_id);
}

ORCAcode
discord_edit_webhook_message(
  struct discord *client,
  const u64_snowflake_t webhook_id,
  const char webhook_token[],
  const u64_snowflake_t message_id,
  struct discord_edit_webhook_message_params *params,
  struct discord_message *p_message)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(webhook_token)) {
    logconf_error(client->conf, "Missing 'webhook_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_message ? &discord_message_from_json_v : NULL,
    .ok_obj = &p_message
  };

  char payload[16384]; /**< @todo dynamic buffer */
  size_t ret = discord_edit_webhook_message_params_to_json(
    payload, sizeof(payload), params);
  struct sized_buffer body = { payload, ret };

  /* content-type is application/json */
  if (!params->attachments) {
    return discord_adapter_run(
      &client->adapter, &resp_handle, &(struct sized_buffer){ payload, ret },
      HTTP_POST, "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64, webhook_id,
      webhook_token, message_id);
  }

  /* content-type is multipart/form-data */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");
  ua_curl_mime_setopt(client->adapter.ua,
                      (void *[2]){ params->attachments, &body },
                      &_discord_params_to_mime);

  ORCAcode code;
  code =
    discord_adapter_run(&client->adapter, &resp_handle, NULL, HTTP_MIMEPOST,
                        "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                        webhook_id, webhook_token, message_id);

  /*set back to default */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");

  return code;
}

ORCAcode
discord_delete_webhook_message(struct discord *client,
                               const u64_snowflake_t webhook_id,
                               const char webhook_token[],
                               const u64_snowflake_t message_id)
{
  if (!webhook_id) {
    logconf_error(client->conf, "Missing 'webhook_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(webhook_token)) {
    logconf_error(client->conf, "Missing 'webhook_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                             webhook_id, webhook_token, message_id);
}
