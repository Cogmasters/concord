#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdiscord.h"
#include "discord-common.h"
#include "orka-utils.h"


void
discord_list_guild_emojis(struct discord_client *client, const uint64_t guild_id, NTL_T(struct discord_emoji_dati) *p_emojis)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle =
    { .ok_cb = &discord_emoji_dati_list_from_json_v, .ok_obj = (void*)p_emojis};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%llu/emojis", guild_id);
}
