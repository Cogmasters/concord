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

void
json_list_load(char *str, size_t len, void *p_guilds)
{
  json_token **toks = NULL;
  json_scanf(str, len, "[]%A", &toks);

  data **new_guilds = (data**)ntl_dup((void**)toks, sizeof(data));
  for (size_t i=0; toks[i]; ++i) {
<<<<<<< HEAD
    json_load(toks[i]->start, toks[i]->length, new_guilds[i]);
=======
    json_load(new_guilds[i], toks[i]->start, toks[i]->length);
>>>>>>> 988e328ba24deaea824cc0c5a1a3ad47cfcf002f
  }
  
  free(toks);

  *(data ***)p_guilds = new_guilds;
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
list_cleanup(data **guilds) {
  free(guilds);
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
