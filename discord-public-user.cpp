#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "ntl.h"

namespace discord {
namespace user {

void
json_load(char *str, size_t len, void *p_user)
{
  dati *user = (dati*)p_user;

  json_scanf(str, len,
     "[id]%s"
     "[username]%s"
     "[discriminator]%s"
     "[avatar]%s"
     "[bot]%b"
     "[system]%b"
     "[mfa_enabled]%b"
     "[locale]%s"
     "[verified]%b"
     "[email]%s"
     "[flags]%d"
     "[premium_type]%d"
     "[public_flags]%d",
      user->id,
      user->username,
      user->discriminator,
      user->avatar,
      &user->bot,
      &user->sys,
      &user->mfa_enabled,
      user->locale,
      &user->verified,
      user->email,
      &user->flags,
      &user->premium_type,
      &user->public_flags);

  D_NOTOP_PUTS("User object loaded with API response"); 
}

void
json_list_load(char *str, size_t len, void *p_users)
{
  json_token **toks = NULL;
  json_scanf(str, len, "[]%A", &toks);

  size_t n = ntl_length((void**)toks);
  dati **new_users = (dati**)ntl_calloc(n, sizeof(dati*));
  for (size_t i=0; toks[i]; ++i) {
    new_users[i] = init();
    json_load(toks[i]->start, toks[i]->length, new_users[i]);
  }
  
  free(toks);

  *(dati ***)p_users = new_users;
}

dati*
init()
{
  dati *new_user = (dati*)calloc(1, sizeof *new_user);
  return new_user;
}

void
cleanup(dati *user) {
  free(user);
}

void
list_cleanup(dati **guilds) {
  free(guilds);
}

void
get(client *client, const char user_id[], dati *p_user)
{
  if (IS_EMPTY_STRING(user_id)) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  user_agent::run( 
    &client->ua,
    (void*)p_user,
    &json_load,
    NULL,
    HTTP_GET, USER, user_id);
}

namespace me {

void 
get(client *client, dati *p_user)
{
  user_agent::run( 
    &client->ua,
    (void*)p_user,
    &json_load,
    NULL,
    HTTP_GET, USER, "@me");
}

guild::dati**
get_guilds(client *client)
{
  guild::dati **new_guilds = NULL;

  user_agent::run( 
    &client->ua,
    (void*)&new_guilds,
    &guild::json_list_load,
    NULL,
    HTTP_GET, USER GUILDS, "@me");

  return new_guilds;
}

} // namespace me

} // namespace user
} // namespace discord
