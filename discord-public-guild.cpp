#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "ntl.h"

namespace discord {
namespace guild {

void
json_load(char *str, size_t len, void *p_guild)
{
  dati *guild = (dati*)p_guild;

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

void
json_list_load(char *str, size_t len, void *p_guilds)
{
  json_token **toks = NULL;
  json_scanf(str, len, "[]%A", &toks);

  dati **new_guilds = (dati**)ntl_dup((void**)toks, sizeof(dati));
  for (size_t i=0; toks[i]; ++i) {
    json_load(toks[i]->start, toks[i]->length, new_guilds[i]);
  }
  
  free(toks);

  *(dati ***)p_guilds = new_guilds;
}

dati*
init()
{
  dati *new_guild = (dati*)calloc(1, sizeof *new_guild);
  return new_guild;
}

void
cleanup(dati *guild) {
  free(guild);
}

void
list_cleanup(dati **guilds) {
  free(guilds);
}

void
get(client *client, const char guild_id[], dati *p_guild)
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
