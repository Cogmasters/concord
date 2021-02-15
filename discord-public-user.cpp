#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace user {

void
from_json(char *str, size_t len, void *p_user)
{
  dati *user = (dati*)p_user;

  json_scanf(str, len,
     "[id]%F"
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
      &orka_strtoull, &user->id,
      user->username,
      user->discriminator,
      user->avatar,
      &user->bot,
      &user->System,
      &user->mfa_enabled,
      user->locale,
      &user->verified,
      user->email,
      &user->flags,
      &user->premium_type,
      &user->public_flags);

  DS_NOTOP_PUTS("User object loaded with API response"); 
}

void
list_from_json(char *str, size_t len, void *p_users)
{
  struct ntl_deserializer deserializer = {
    .elem_size = sizeof(dati),
    .init_elem = &init_dati,
    .elem_from_buf = &from_json,
    .ntl_recipient_p = (void***)p_users
  };
  orka_str_to_ntl(str, len, &deserializer);
}

void
init_dati(void *p_user) {
  memset(p_user, 0, sizeof(dati));
}

dati*
alloc_dati()
{
  dati *new_user = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_user);
  return new_user;
}

void
cleanup_dati(void *p_user)
{
  DS_NOTOP_PUTS("User object free'd"); 
}

void
free_dati(dati *user) 
{
  cleanup_dati((void*)user);
  free(user);
}

void
free_list(dati **users) {
  ntl_free((void**)users, &cleanup_dati);
}

void
get(client *client, const uint64_t user_id, dati *p_user)
{
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  struct resp_handle resp_handle = {&from_json, (void*)p_user};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/%llu", user_id);
}

namespace me {

void 
get(client *client, dati *p_user)
{
  struct resp_handle resp_handle = {&from_json, (void*)p_user};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/@me");
}

guild::dati**
get_guilds(client *client)
{
  guild::dati **new_guilds = NULL;

  struct resp_handle resp_handle =
    {&guild::list_from_json, (void*)&new_guilds};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/users/@me/guilds");

  return new_guilds;
}

} // namespace me

} // namespace user
} // namespace discord
