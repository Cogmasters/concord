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
    log_error("Missing 'interaction_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    log_error("Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret = discord_interaction_response_to_json(payload, sizeof(payload), params);

  return discord_adapter_run( 
           &client->adapter,
           &(struct ua_resp_handle){ 
             .ok_cb = p_response ? &discord_interaction_response_from_json_v : NULL, 
             .ok_obj = &p_response 
           },
           &(struct sized_buffer){ payload, ret },
           HTTP_POST, 
           "/interactions/%"PRIu64"/%s/callback", interaction_id, interaction_token);
}

ORCAcode
discord_get_original_interaction_response(
  struct discord *client,
  const u64_snowflake_t interaction_id,
  const char interaction_token[],
  struct discord_interaction_response *p_response)
{
  if (!interaction_id) {
    log_error("Missing 'interaction_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    log_error("Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_response) {
    log_error("Missing 'p_response'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run( 
           &client->adapter,
           &(struct ua_resp_handle){ 
             .ok_cb = &discord_interaction_response_from_json_v, 
             .ok_obj = &p_response 
           },
           NULL,
           HTTP_GET, 
           "/webhooks/%"PRIu64"/%s/messages/@original", interaction_id, interaction_token);
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
    log_error("Missing 'interaction_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    log_error("Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_response ? &discord_interaction_response_from_json_v : NULL,
    .ok_obj = &p_response
  };

  if (!params->file) /* content-type is application/json */
  {
    char payload[16384]; /**< @todo dynamic buffer */
    size_t ret = discord_edit_original_interaction_response_params_to_json(payload, sizeof(payload), params);

    return discord_adapter_run(
             &client->adapter,
             &resp_handle,
             &(struct sized_buffer){ payload, ret },
             HTTP_POST,
             "/webhooks/%"PRIu64"/%s/messages/@original", 
             interaction_id, interaction_token);
  }

  /* content-type is multipart/form-data */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");
  ua_curl_mime_setopt(client->adapter.ua, params->file, &discord_file_to_mime);

  ORCAcode code;
  code = discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_MIMEPOST, 
           "/webhooks/%"PRIu64"/%s/messages/@original", 
           interaction_id, interaction_token);

  /*set back to default */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");
  ua_curl_mime_setopt(client->adapter.ua, NULL, NULL);

  return code;
}

ORCAcode
discord_delete_original_interaction_response(
  struct discord *client,
  const u64_snowflake_t interaction_id,
  const char interaction_token[])
{
  if (!interaction_id) {
    log_error("Missing 'interaction_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    log_error("Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run( 
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE, 
           "/webhooks/%"PRIu64"/%s/messages/@original", interaction_id, interaction_token);
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
    log_error("Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    log_error("Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[4096]="";
  size_t ret=0;

#if 0
  if (params->wait) { /* according tot he docs this is always true */
    ret = snprintf(query, sizeof(query), "wait=1");
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }
#endif
  if (params->thread_id) { 
    ret += snprintf(query+ret, sizeof(query)-ret, "%sthread_id=%"PRIu64, 
        ret ? "&" : "", params->thread_id);
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_webhook ? &discord_webhook_from_json_v : NULL,
    .ok_obj = &p_webhook
  };

  if (!params->file) /* content-type is application/json */
  {
    char payload[16384]; /**< @todo dynamic buffer */
    ret = discord_create_followup_message_params_to_json(payload, sizeof(payload), params);

    return discord_adapter_run(
             &client->adapter,
             &resp_handle,
             &(struct sized_buffer){ payload, ret },
             HTTP_POST,
             "/webhooks/%"PRIu64"/%s%s%s", 
             application_id, interaction_token, *query ? "?" : "", query);
  }

  /* content-type is multipart/form-data */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");
  ua_curl_mime_setopt(client->adapter.ua, params->file, &discord_file_to_mime);

  ORCAcode code;
  code = discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_MIMEPOST, 
           "/webhooks/%"PRIu64"/%s%s%s", 
           application_id, interaction_token, *query ? "?" : "", query);

  /*set back to default */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");
  ua_curl_mime_setopt(client->adapter.ua, NULL, NULL);

  return code;
}

ORCAcode
discord_get_followup_message(
  struct discord *client,
  const u64_snowflake_t application_id,
  const char interaction_token[],
  const u64_snowflake_t message_id,
  struct discord_message *p_message)
{
  if (!application_id) {
    log_error("Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    log_error("Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_message) {
    log_error("Missing 'p_message'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           &(struct ua_resp_handle){
             .ok_cb = &discord_message_from_json_v,
             .ok_obj = &p_message
           },
           NULL,
           HTTP_GET,
           "/webhooks/%"PRIu64"/%s/%"PRIu64, 
           application_id, interaction_token, message_id);
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
    log_error("Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    log_error("Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_message ? &discord_message_from_json_v : NULL,
    .ok_obj = &p_message
  };

  if (!params->file) /* content-type is application/json */
  {
    char payload[16384]; /**< @todo dynamic buffer */
    size_t ret = discord_edit_followup_message_params_to_json(payload, sizeof(payload), params);

    return discord_adapter_run(
             &client->adapter,
             &resp_handle,
             &(struct sized_buffer){ payload, ret },
             HTTP_POST,
             "/webhooks/%"PRIu64"/%s/messages/%"PRIu64, 
             application_id, interaction_token, message_id);
  }

  /* content-type is multipart/form-data */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");
  ua_curl_mime_setopt(client->adapter.ua, params->file, &discord_file_to_mime);

  ORCAcode code;
  code = discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_MIMEPOST, 
           "/webhooks/%"PRIu64"/%s/messages/%"PRIu64, 
           application_id, interaction_token, message_id);

  /*set back to default */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");
  ua_curl_mime_setopt(client->adapter.ua, NULL, NULL);

  return code;
}

ORCAcode
discord_delete_followup_message(
  struct discord *client,
  const u64_snowflake_t application_id,
  const char interaction_token[],
  const u64_snowflake_t message_id)
{
  if (!application_id) {
    log_error("Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(interaction_token)) {
    log_error("Missing 'interaction_token'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/webhooks/%"PRIu64"/%s/messages/%"PRIu64, 
           application_id, interaction_token, message_id);
}
