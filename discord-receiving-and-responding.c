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
