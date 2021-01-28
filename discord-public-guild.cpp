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

  size_t n = ntl_length((void**)toks);
  dati **new_guilds = (dati**)ntl_calloc(n, sizeof(dati*));
  for (size_t i=0; toks[i]; ++i) {
    new_guilds[i] = init();
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
    HTTP_GET, GUILD, guild_id);
}

namespace member {

void
json_load(char *str, size_t len, void *p_member)
{
  dati *member = (dati*)p_member;

  json_scanf(str, len,
     "[user]%F"
     "[nick]%s"
     "[joined_at]%s"
     "[premium_since]%s"
     "[deaf]%b"
     "[mute]%b"
     "[pending]%b",
      &user::json_load, member->user,
      member->nick,
      member->joined_at,
      member->premium_since,
      &member->deaf,
      &member->mute,
      &member->pending);

  D_NOTOP_PUTS("Member object loaded with API response"); 
}

void
json_list_load(char *str, size_t len, void *p_members)
{
  json_token **toks = NULL;
  json_scanf(str, len, "[]%A", &toks);

  size_t n = ntl_length((void**)toks);
  dati **new_members = (dati**)ntl_calloc(n, sizeof(dati*));
  for (size_t i=0; toks[i]; ++i) {
    new_members[i] = init();
    json_load(toks[i]->start, toks[i]->length, new_members[i]);
  }
  
  free(toks);

  *(dati ***)p_members = new_members;
}

dati*
init()
{
  dati *new_member = (dati*)calloc(1, sizeof *new_member);
  return new_member;
}

void
cleanup(dati *member) {
  free(member);
}

void
list_cleanup(dati **members) {
  for (int i=0; members[i]; ++i) {
    user::cleanup(members[i]->user);
  }
  free(members);
}


//@todo modifiable query string parameters
dati**
get_list(client *client, const char guild_id[])
{
  if (IS_EMPTY_STRING(guild_id)) {
    D_PUTS("Missing 'guild_id'");
    return NULL;
  }

  dati **new_members = NULL;
  
  user_agent::run( 
    &client->ua,
    (void*)&new_members,
    &json_list_load,
    NULL,
    HTTP_GET, GUILD MEMBERS "?limit=100", guild_id);

  return new_members;
}

} // namespace member

} // namespace guild
} // namespace discord
