#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <liborca.h>

#include "orca-common.h"

orca_user_t*
orca_user_init()
{
  orca_user_t *new_user = calloc(1, sizeof *new_user);
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
orca_user_cleanup(orca_user_t *user)
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
_orca_load_user(void **p_user, struct api_response_s *res_body)
{
  orca_user_t *user = *p_user;

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
orca_get_user(orca_t *client, char user_id[], orca_user_t **p_user)
{
  Orca_api_request( 
    &client->api,
    (void**)p_user,
    &_orca_load_user,
    GET, USER, user_id);
}

void 
orca_get_client(orca_t *client, orca_user_t **p_user)
{
  Orca_api_request( 
    &client->api,
    (void**)p_user,
    &_orca_load_user,
    GET, USER, "@me");
}
