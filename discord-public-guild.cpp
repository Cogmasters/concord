#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"
#include "ntl.h"

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

void
json_list_load(void *p_guild_list, char *str, size_t len)
{
  ASSERT_S(NULL == *(data **)p_guild_list, "List is already initialized, otherwise it should be set to NULL");

  json_token **toks = NULL;
  json_scanf(str, len, "[]%A", &toks);

  // get amount of elements
  size_t amt=0;
  while (toks[amt] != NULL) {
    ++amt;
  }

  data *new_guilds = (data*)ntl_malloc(amt, sizeof(data));
  for (size_t i=0; i < amt; ++i) {
    json_load(new_guilds+i, toks[i]->start, toks[i]->length);
  }

  for (int i=0; new_guilds+i /* null terminated */; ++i){
    D_PRINT("%s", new_guilds[i].id);
  }

  *(data **)p_guild_list = new_guilds;
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
