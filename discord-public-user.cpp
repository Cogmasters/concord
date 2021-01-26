#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

namespace discord {
namespace user {

void
json_load(char *str, size_t len, void *p_user)
{
  data *user = (data*)p_user;

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

data*
init()
{
  data *new_user = (data*)calloc(1, sizeof *new_user);
  return new_user;
}

void
cleanup(data *user) {
  free(user);
}

void
get(client *client, const char user_id[], data *p_user)
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
    GET, USER, user_id);
}

namespace me {

void 
get(client *client, data *p_user)
{
  user_agent::run( 
    &client->ua,
    (void*)p_user,
    &json_load,
    NULL,
    GET, USER, "@me");
}

guild::data**
get_guilds(client *client)
{
  guild::data **new_guilds = NULL;

  user_agent::run( 
    &client->ua,
    (void*)&new_guilds,
    &guild::json_list_load,
    NULL,
    GET, USER GUILDS, "@me");

  return new_guilds;
}

} // namespace me

} // namespace user
} // namespace discord
