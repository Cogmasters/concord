#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

namespace discord {

void
Discord_guild_load(void *p_guild, char *str, size_t len)
{
  guild::data *guild = (guild::data*)p_guild;

  json_scanf(str, len,
     "[id]%s"
     "[name]%s"
     "[icon]%s"
     "[owner]%b"
     "[permissions]%d"
     "[permissions_new]%s",
      guild->id,
      guild->name,
      guild->icon,
      &guild->owner,
      &guild->permissions,
      guild->permissions_new);

  D_NOTOP_PUTS("Guild object loaded with API response"); 
}

namespace guild {

struct data*
init()
{
  struct data *new_guild = (struct data*)calloc(1, sizeof *new_guild);
  return new_guild;
}

void
cleanup(struct data *guild) {
  free(guild);
}

void
get(discord_t *client, const char guild_id[], struct data *p_guild)
{
  if (IS_EMPTY_STRING(guild_id)) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  Discord_api_request( 
    &client->api,
    (void*)p_guild,
    &Discord_guild_load,
    NULL,
    GET, GUILD, guild_id);
}

} // namespace guild
} // namespace discord
