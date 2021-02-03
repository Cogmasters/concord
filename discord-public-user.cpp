#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace user {

void
json_load(char *str, size_t len, void *p_user)
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
  struct sized_buffer **buf = NULL;
  json_scanf(str, len, "[]%A", &buf);

  size_t n = ntl_length((void**)buf);
  dati **new_users = (dati**)ntl_calloc(n, sizeof(dati*));
  for (size_t i=0; buf[i]; ++i) {
    new_users[i] = init();
    json_load(buf[i]->start, buf[i]->size, new_users[i]);
  }
  
  free(buf);

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
list_cleanup(dati **users) {
  for(int i = 0; users[i]; i++) {
    cleanup(users[i]);
  }
  free(users);
}

void
get(client *client, const uint64_t user_id, dati *p_user)
{
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  struct resp_handle resp_handle = {&json_load, (void*)p_user};
  struct sized_buffer body = {NULL, 0};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &body,
    HTTP_GET, USER, user_id);
}

namespace me {

void 
get(client *client, dati *p_user)
{
  struct resp_handle resp_handle = {&json_load, (void*)p_user};
  struct sized_buffer body = {NULL, 0};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &body,
    HTTP_GET, ME);
}

guild::dati**
get_guilds(client *client)
{
  guild::dati **new_guilds = NULL;

  struct resp_handle resp_handle =
    {&guild::json_list_load, (void*)&new_guilds};
  struct sized_buffer body = {NULL, 0};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &body,
    HTTP_GET, ME GUILDS);

  return new_guilds;
}

} // namespace me

} // namespace user
} // namespace discord
