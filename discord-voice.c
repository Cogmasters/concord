#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"

ORCAcode
discord_list_voice_regions(struct discord *client, NTL_T(struct discord_voice_region) *p_voice_regions)
{
  if (!p_voice_regions) {
    log_error("Missing 'p_voice_regions'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_voice_region_list_from_json_v, 
    .ok_obj = p_voice_regions 
  };

  return discord_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/voice/regions");
}
