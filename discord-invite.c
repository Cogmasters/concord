#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_get_invite(struct discord *client,
                   char *invite_code,
                   struct discord_get_invite_params *params,
                   struct discord_invite *p_invite)
{
  if (!invite_code) {
    logconf_error(client->conf, "Missing 'invite_code'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_invite) {
    logconf_error(client->conf, "Missing 'p_invite'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret =
    discord_get_invite_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_invite_from_json_v,
                              .ok_obj = &p_invite },
    &(struct sized_buffer){ payload, ret }, HTTP_GET, "/invites/%s",
    invite_code);
}

ORCAcode
discord_delete_invite(struct discord *client,
                      char *invite_code,
                      struct discord_invite *p_invite)
{
  if (!invite_code) {
    logconf_error(client->conf, "Missing 'invite_code'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb =
                                p_invite ? &discord_invite_from_json_v : NULL,
                              .ok_obj = &p_invite },
    NULL, HTTP_DELETE, "/invites/%s", invite_code);
}
