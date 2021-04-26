#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


void
discord_list_guild_emojis(struct discord *client, const uint64_t guild_id, NTL_T(struct discord_emoji) *p_emojis)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return;
  }

  struct ua_resp_handle resp_handle =
    { .ok_cb = &discord_emoji_list_from_json_v, .ok_obj = (void*)p_emojis};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%"PRIu64"/emojis", guild_id);
}
