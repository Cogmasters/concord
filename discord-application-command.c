#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"


ORCAcode
discord_create_global_application_command(
  struct discord *client,
  const u64_snowflake_t application_id,
  struct discord_create_global_application_command_params *params,
  struct discord_application_command *p_app_cmd)
{
  if (!application_id) {
    log_error("Missing 'application_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(params->name)) {
    log_error("Missing 'params.name'");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(params->description)) {
    log_error("Missing 'params.description'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret = discord_create_global_application_command_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run( 
           &client->adapter,
           &(struct ua_resp_handle){
             .ok_cb = p_app_cmd ? &discord_application_command_from_json_v : NULL,
             .ok_obj = &p_app_cmd
           },
           &(struct sized_buffer){ payload, ret },
           HTTP_POST, 
           "/applications/"PRIu64"/commands", application_id);
}
