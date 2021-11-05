#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_create_interaction_response(
  struct discord *client,
  const u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_interaction_response *params,
  struct discord_interaction_response *p_response)
{
  if (!interaction_id) {
    logconf_error(client->conf, "Missing 'interaction_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    logconf_error(client->conf, "Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret =
    discord_interaction_response_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = p_response ? &discord_interaction_response_from_json_v : NULL,
      .ok_obj = &p_response },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/interactions/%" PRIu64 "/%s/callback", interaction_id,
    interaction_token);
}

ORCAcode
discord_get_original_interaction_response(
  struct discord *client,
  const u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_interaction_response *p_response)
{
  if (!interaction_id) {
    logconf_error(client->conf, "Missing 'interaction_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    logconf_error(client->conf, "Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_response) {
    logconf_error(client->conf, "Missing 'p_response'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb =
                                &discord_interaction_response_from_json_v,
                              .ok_obj = &p_response },
    NULL, HTTP_GET, "/webhooks/%" PRIu64 "/%s/messages/@original",
    interaction_id, interaction_token);
}

ORCAcode
discord_edit_original_interaction_response(
  struct discord *client,
  const u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_edit_original_interaction_response_params *params,
  struct discord_interaction_response *p_response)
{
  if (!interaction_id) {
    logconf_error(client->conf, "Missing 'interaction_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    logconf_error(client->conf, "Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_response ? &discord_interaction_response_from_json_v : NULL,
    .ok_obj = &p_response
  };

  char payload[16384]; /**< @todo dynamic buffer */
  size_t ret = discord_edit_original_interaction_response_params_to_json(
    payload, sizeof(payload), params);
  struct sized_buffer body = { payload, ret };

  /* content-type is application/json */
  if (!params->attachments) {
    return discord_adapter_run(&client->adapter, &resp_handle, &body,
                               HTTP_POST,
                               "/webhooks/%" PRIu64 "/%s/messages/@original",
                               interaction_id, interaction_token);
  }

  /* content-type is multipart/form-data */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");
  ua_curl_mime_setopt(client->adapter.ua,
                      (void *[2]){ params->attachments, &body },
                      &_discord_params_to_mime);

  ORCAcode code;
  code =
    discord_adapter_run(&client->adapter, &resp_handle, NULL, HTTP_MIMEPOST,
                        "/webhooks/%" PRIu64 "/%s/messages/@original",
                        interaction_id, interaction_token);

  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");

  return code;
}

ORCAcode
discord_delete_original_interaction_response(
  struct discord *client,
  const u64_snowflake_t interaction_id,
  const char interaction_token[])
{
  if (!interaction_id) {
    logconf_error(client->conf, "Missing 'interaction_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    logconf_error(client->conf, "Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64 "/%s/messages/@original",
                             interaction_id, interaction_token);
}

ORCAcode
discord_create_followup_message(
  struct discord *client,
  const u64_snowflake_t application_id,
  const char interaction_token[],
  struct discord_create_followup_message_params *params,
  struct discord_webhook *p_webhook)
{
  if (!application_id) {
    logconf_error(client->conf, "Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    logconf_error(client->conf, "Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[4096] = "";
  size_t ret = 0;

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
  ret = discord_create_followup_message_params_to_json(
    payload, sizeof(payload), params);
  struct sized_buffer body = { payload, ret };

  /* content-type is application/json */
  if (!params->attachments) {
    return discord_adapter_run(&client->adapter, &resp_handle, &body,
                               HTTP_POST, "/webhooks/%" PRIu64 "/%s%s%s",
                               application_id, interaction_token,
                               *query ? "?" : "", query);
  }

  /* content-type is multipart/form-data */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");
  ua_curl_mime_setopt(client->adapter.ua,
                      (void *[2]){ params->attachments, &body },
                      &_discord_params_to_mime);

  ORCAcode code;
  code =
    discord_adapter_run(&client->adapter, &resp_handle, NULL, HTTP_MIMEPOST,
                        "/webhooks/%" PRIu64 "/%s%s%s", application_id,
                        interaction_token, *query ? "?" : "", query);

  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");

  return code;
}

ORCAcode
discord_get_followup_message(struct discord *client,
                             const u64_snowflake_t application_id,
                             const char interaction_token[],
                             const u64_snowflake_t message_id,
                             struct discord_message *p_message)
{
  if (!application_id) {
    logconf_error(client->conf, "Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    logconf_error(client->conf, "Missing 'interaction_token'");
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
    NULL, HTTP_GET, "/webhooks/%" PRIu64 "/%s/%" PRIu64, application_id,
    interaction_token, message_id);
}

ORCAcode
discord_edit_followup_message(
  struct discord *client,
  const u64_snowflake_t application_id,
  const char interaction_token[],
  const u64_snowflake_t message_id,
  struct discord_edit_followup_message_params *params,
  struct discord_message *p_message)
{
  if (!application_id) {
    logconf_error(client->conf, "Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    logconf_error(client->conf, "Missing 'interaction_token'");
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
  size_t ret = discord_edit_followup_message_params_to_json(
    payload, sizeof(payload), params);
  struct sized_buffer body = { payload, ret };

  /* content-type is application/json */
  if (!params->attachments) {
    return discord_adapter_run(&client->adapter, &resp_handle, &body,
                               HTTP_POST,
                               "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                               application_id, interaction_token, message_id);
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
                        application_id, interaction_token, message_id);

  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");

  return code;
}

ORCAcode
discord_delete_followup_message(struct discord *client,
                                const u64_snowflake_t application_id,
                                const char interaction_token[],
                                const u64_snowflake_t message_id)
{
  if (!application_id) {
    logconf_error(client->conf, "Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    logconf_error(client->conf, "Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/webhooks/%" PRIu64 "/%s/messages/%" PRIu64,
                             application_id, interaction_token, message_id);
}
