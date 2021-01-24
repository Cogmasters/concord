#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "discord-common.h"


namespace discord {

void
Discord_user_load(void *p_data, char *str, size_t len)
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

namespace user {

struct data*
init()
{
  struct data *new_data = (struct data*)calloc(1, sizeof *new_data);
  return new_data;
}

void
cleanup(struct data *data) {
  free(data);
}

void
get(discord_t *client, const char user_id[], struct data *p_data)
{
  if (IS_EMPTY_STRING(user_id)) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  Discord_api_request( 
    &client->api,
    (void*)p_data,
    &Discord_user_load,
    NULL,
    GET, USER, user_id);
}

void 
get_self(discord_t *client, struct data *p_data)
{
  Discord_api_request( 
    &client->api,
    (void*)p_data,
    &Discord_user_load,
    NULL,
    GET, USER, "@me");
}

} // namespace user

} // namespace discord
