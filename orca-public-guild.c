#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <liborca.h>

#include "orca-common.h"

orca_guild_t*
orca_guild_init()
{
  orca_guild_t *new_guild = calloc(1, sizeof *new_guild);
  if (NULL == new_guild) return NULL;

  new_guild->id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->id) goto cleanupA;

  new_guild->name = malloc(MAX_NAME_LEN);
  if (NULL == new_guild->name) goto cleanupB;

  new_guild->icon = malloc(MAX_HASH_LEN);
  if (NULL == new_guild->icon) goto cleanupC;

  new_guild->discovery_splash = malloc(MAX_HASH_LEN);
  if (NULL == new_guild->discovery_splash) goto cleanupD;

  new_guild->owner_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->owner_id) goto cleanupE;

  new_guild->permissions_new = malloc(SNOWFLAKE_INCREMENT);
  if (NULL == new_guild->permissions_new) goto cleanupF;

  new_guild->region = malloc(MAX_REGION_LEN);
  if (NULL == new_guild->region) goto cleanupG;

  new_guild->afk_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->afk_channel_id) goto cleanupH;

  new_guild->embed_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->embed_channel_id) goto cleanupI;

  new_guild->application_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->application_id) goto cleanupJ;

  new_guild->widget_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->widget_channel_id) goto cleanupK;

  new_guild->system_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->system_channel_id) goto cleanupL;

  new_guild->rules_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->rules_channel_id) goto cleanupM;

  new_guild->joined_at = malloc(SNOWFLAKE_TIMESTAMP);
  if (NULL == new_guild->joined_at) goto cleanupN;

  new_guild->vanity_url_code = malloc(SNOWFLAKE_INCREMENT);
  if (NULL == new_guild->vanity_url_code) goto cleanupO;

  new_guild->description = malloc(MAX_DESCRIPTION_LEN);
  if (NULL == new_guild->description) goto cleanupP;

  new_guild->banner = malloc(MAX_HASH_LEN);
  if (NULL == new_guild->banner) goto cleanupQ;

  new_guild->preferred_locale = malloc(MAX_LOCALE_LEN);
  if (NULL == new_guild->preferred_locale) goto cleanupR;

  new_guild->public_updates_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_guild->public_updates_channel_id) goto cleanupS; 


  return new_guild;

cleanupS:
  free(new_guild->preferred_locale);
cleanupR:
  free(new_guild->banner);
cleanupQ:
  free(new_guild->description);
cleanupP:
  free(new_guild->vanity_url_code);
cleanupO:
  free(new_guild->joined_at);
cleanupN:
  free(new_guild->rules_channel_id);
cleanupM:
  free(new_guild->system_channel_id);
cleanupL:
  free(new_guild->widget_channel_id);
cleanupK:
  free(new_guild->application_id);
cleanupJ:
  free(new_guild->embed_channel_id);
cleanupI:
  free(new_guild->afk_channel_id);
cleanupH:
  free(new_guild->region);
cleanupG:
  free(new_guild->permissions_new);
cleanupF:
  free(new_guild->owner_id);
cleanupE:
  free(new_guild->discovery_splash);
cleanupD:
  free(new_guild->icon);
cleanupC:
  free(new_guild->name);
cleanupB:
  free(new_guild->id);
cleanupA:
  free(new_guild);

  return NULL;
}

void
orca_guild_cleanup(orca_guild_t *guild)
{
  free(guild->id);
  free(guild->name);
  free(guild->icon);
  free(guild->discovery_splash);
  free(guild->owner_id);
  free(guild->permissions_new);
  free(guild->region);
  free(guild->afk_channel_id);
  free(guild->embed_channel_id);
  free(guild->application_id);
  free(guild->widget_channel_id);
  free(guild->system_channel_id);
  free(guild->rules_channel_id);
  free(guild->joined_at);
  free(guild->vanity_url_code);
  free(guild->description);
  free(guild->banner);
  free(guild->preferred_locale);
  free(guild->public_updates_channel_id);
  free(guild);
}

static void
_orca_load_guild(void **p_guild, struct api_response_s *res_body)
{
  orca_guild_t *guild = *p_guild;

  jscon_scanf(res_body->str,
     "%s[id]" \
     "%s[name]" \
     "%s[icon]" \
     "%b[owner]" \
     "%d[permissions]" \
     "%s[permissions_new]",
      guild->id,
      guild->name,
      guild->icon,
      &guild->owner,
      &guild->permissions,
      guild->permissions_new);

  *p_guild = guild;
}

void
orca_get_guild(orca_t *client, char guild_id[], orca_guild_t **p_guild)
{
  Orca_api_request( 
    &client->api,
    (void**)p_guild,
    &_orca_load_guild,
    GET, GUILD, guild_id);
}
