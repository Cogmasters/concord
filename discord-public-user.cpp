#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace user {
#ifdef M
void
dati_from_json(char *str, size_t len, void *p_user)
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
dati_list_from_json(char *str, size_t len, void *p_users)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init;
  d.elem_from_buf = &dati_from_json;
  d.ntl_recipient_p = (void***)p_users;
  orka_str_to_ntl(str, len, &d);
}

void
dati_init(void *p_user) {
  memset(p_user, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *new_user = (dati*)malloc(sizeof(dati));
  dati_init((void*)new_user);
  return new_user;
}

void
dati_cleanup(void *p_user)
{
  DS_NOTOP_PUTS("User object fields cleared"); 
}

void
dati_free(dati *user) 
{
  dati_cleanup((void*)user);
  free(user);
}

void
dati_list_free(dati **users) {
  ntl_free((void**)users, &dati_cleanup);
}
#endif

void
get(client *client, const uint64_t user_id, dati *p_user)
{
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  struct resp_handle resp_handle = {&dati_from_json_v, (void*)p_user};

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
  struct resp_handle resp_handle = {&dati_from_json_v, (void*)p_user};

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
    {&guild::dati_list_from_json, (void*)&new_guilds};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/users/@me/guilds");

  return new_guilds;
}

void leave_guild(client *client, const u64_snowflake_t guild_id)
{
  struct sized_buffer body = { "{}", 2 };

  user_agent::run(
    &client->ua,
    NULL,
    &body,
    HTTP_DELETE,
    "/users/@me/guilds/%llu", guild_id);
}

} // namespace me

} // namespace user
} // namespace discord
