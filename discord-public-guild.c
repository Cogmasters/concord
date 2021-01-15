#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

discord_guild_t*
discord_guild_init()
{
  discord_guild_t *new_guild = calloc(1, sizeof *new_guild);
  return new_guild;
}

void
discord_guild_cleanup(discord_guild_t *guild) {
  free(guild);
}

void
discord_get_guild(discord_t *client, const char guild_id[], discord_guild_t *p_guild)
{
  if (IS_EMPTY_STRING(guild_id)) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  Discord_api_request( 
    &client->api,
    (void*)p_guild,
    &Discord_api_load_guild,
    NULL,
    GET, GUILD, guild_id);
}
