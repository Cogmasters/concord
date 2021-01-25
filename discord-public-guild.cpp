#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

namespace discord {
namespace guild {

void
json_load(void *p_guild, char *str, size_t len)
{
  data *guild = (data*)p_guild;

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

data*
init()
{
  data *new_guild = (data*)calloc(1, sizeof *new_guild);
  return new_guild;
}

void
cleanup(data *guild) {
  free(guild);
}

void
get(client *client, const char guild_id[], data *p_guild)
{
  if (IS_EMPTY_STRING(guild_id)) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  user_agent::run( 
    &client->ua,
    (void*)p_guild,
    &json_load,
    NULL,
    GET, GUILD, guild_id);
}

} // namespace guild
} // namespace discord
