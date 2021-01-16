#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

discord_user_t*
discord_user_init()
{
  discord_user_t *new_user = calloc(1, sizeof *new_user);
  return new_user;
}

void
discord_user_cleanup(discord_user_t *user) {
  free(user);
}

void
Discord_public_load_user(void *p_user, char *str, size_t len)
{
  discord_user_t *user = p_user;

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

  D_PUTS("User loaded with API response"); 
}

void
discord_get_user(discord_t *client, const char user_id[], discord_user_t *p_user)
{
  if (IS_EMPTY_STRING(user_id)) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  Discord_api_request( 
    &client->api,
    (void*)p_user,
    &Discord_public_load_user,
    NULL,
    GET, USER, user_id);
}

void 
discord_get_client_user(discord_t *client, discord_user_t *p_user)
{
  Discord_api_request( 
    &client->api,
    (void*)p_user,
    &Discord_public_load_user,
    NULL,
    GET, USER, "@me");
}
