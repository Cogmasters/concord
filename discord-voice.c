#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_list_voice_regions(struct discord *client,
                           NTL_T(struct discord_voice_region) *
                             p_voice_regions)
{
  if (!p_voice_regions) {
    logconf_error(client->conf, "Missing 'p_voice_regions'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_voice_region_list_from_json_v,
                              .ok_obj = p_voice_regions },
    NULL, HTTP_GET, "/voice/regions");
}
