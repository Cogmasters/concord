#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "discord-common.h"


namespace discord {
namespace user {

void
json_load(void *p_data, char *str, size_t len)
{
  user::data *data = (discord::user::data*)p_data;

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
      data->id,
      data->username,
      data->discriminator,
      data->avatar,
      &data->bot,
      &data->sys,
      &data->mfa_enabled,
      data->locale,
      &data->verified,
      data->email,
      &data->flags,
      &data->premium_type,
      &data->public_flags);

  D_NOTOP_PUTS("User object loaded with API response"); 
}

user::data*
init()
{
  user::data *new_data = (user::data*)calloc(1, sizeof *new_data);
  return new_data;
}

void
cleanup(user::data *data) {
  free(data);
}

void
get(discord::client *client, const char user_id[], user::data *p_data)
{
  if (IS_EMPTY_STRING(user_id)) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  user_agent::run( 
    &client->ua,
    (void*)p_data,
    &user::json_load,
    NULL,
    GET, USER, user_id);
}

void 
get_self(discord::client *client, user::data *p_data)
{
  user_agent::run( 
    &client->ua,
    (void*)p_data,
    &user::json_load,
    NULL,
    GET, USER, "@me");
}

} // namespace user

} // namespace discord
