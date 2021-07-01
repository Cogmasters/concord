#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"


ORCAcode 
discord_get_invite(
  struct discord *client, 
  char *invite_code, 
  struct discord_get_invite_params *params, 
  struct discord_invite *p_invite)
{
  if (!invite_code) {
    log_error("Missing 'invite_code'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_invite) {
    log_error("Missing 'p_invite'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_invite_from_json_v, 
    .ok_obj = p_invite
  };

  char payload[DISCORD_MAX_PAYLOAD_LEN];
  size_t ret = discord_get_invite_params_to_json(payload, sizeof(payload), params);

  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_GET, 
           "/invites/%s", invite_code);
}

ORCAcode 
discord_delete_invite(
  struct discord *client, 
  char *invite_code, 
  struct discord_invite *p_invite)
{
  if (!invite_code) {
    log_error("Missing 'invite_code'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = p_invite ? &discord_invite_from_json_v : NULL, 
    .ok_obj = p_invite
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_DELETE, 
           "/invites/%s", invite_code);
}
