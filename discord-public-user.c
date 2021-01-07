#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

discord_user_t*
discord_user_init()
{
  discord_user_t *new_user = calloc(1, sizeof *new_user);
  if (NULL == new_user) return NULL;

  new_user->id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_user->id) goto cleanupA;

  new_user->username = malloc(MAX_USERNAME_LEN);
  if (NULL == new_user->username) goto cleanupB;

  new_user->discriminator = malloc(MAX_DISCRIMINATOR_LEN);
  if (NULL == new_user->discriminator) goto cleanupC;

  new_user->avatar = malloc(MAX_HASH_LEN);
  if (NULL == new_user->avatar) goto cleanupD;

  new_user->locale = malloc(MAX_LOCALE_LEN);
  if (NULL == new_user->locale) goto cleanupE;

  new_user->email = malloc(MAX_EMAIL_LEN);
  if (NULL == new_user->email) goto cleanupF;

  return new_user;

cleanupF:
  free(new_user->locale);
cleanupE:
  free(new_user->avatar);
cleanupD:
  free(new_user->discriminator);
cleanupC:
  free(new_user->username);
cleanupB:
  free(new_user->id);
cleanupA:
  free(new_user);

  return NULL;
}

void
discord_user_cleanup(discord_user_t *user)
{
  free(user->id);
  free(user->username);
  free(user->discriminator);
  free(user->avatar);
  free(user->locale);
  free(user->email);
  free(user);
}

static void
_discord_load_user(void **p_user, struct api_response_s *res_body)
{
  discord_user_t *user = *p_user;

  jscon_scanf(res_body->str,
     "%s[id]" \
     "%s[username]" \
     "%s[discriminator]" \
     "%s[avatar]" \
     "%b[bot]" \
     "%b[system]" \
     "%b[mfa_enabled]" \
     "%s[locale]" \
     "%b[verified]" \
     "%s[email]" \
     "%d[flags]" \
     "%d[premium_type]" \
     "%d[public_flags]",
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

  *p_user = user;
}

void
discord_get_user(discord_t *discord, char user_id[], discord_user_t **p_user)
{
  Discord_api_request( 
    &discord->api,
    (void**)p_user,
    &_discord_load_user,
    GET, USERS, user_id);
}

void 
discord_get_client(discord_t *discord, discord_user_t **p_client)
{
  Discord_api_request( 
    &discord->api,
    (void**)p_client,
    &_discord_load_user,
    GET, USERS, "@me");
}
