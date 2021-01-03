#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

discord_guild_t*
discord_guild_init()
{
  discord_guild_t *new_guild = calloc(1, sizeof *new_guild);

  new_guild->id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  new_guild->name = malloc(MAX_NAME_LEN);
  new_guild->icon = malloc(MAX_HASH_LEN);
  /* missing new_guild->splash */
  new_guild->discovery_splash = malloc(MAX_HASH_LEN);
  new_guild->owner_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  new_guild->permissions_new = malloc(SNOWFLAKE_INCREMENT);
  new_guild->region = malloc(MAX_REGION_LEN);
  new_guild->afk_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  new_guild->embed_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  new_guild->application_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  new_guild->widget_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  new_guild->system_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  new_guild->rules_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  new_guild->joined_at = malloc(SNOWFLAKE_TIMESTAMP);
  new_guild->vanity_url_code = malloc(SNOWFLAKE_INCREMENT);
  new_guild->description = malloc(MAX_DESCRIPTION_LEN);
  new_guild->banner = malloc(MAX_HASH_LEN);
  new_guild->preferred_locale = malloc(MAX_LOCALE_LEN);
  new_guild->public_updates_channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);

  return new_guild;
}

void
discord_guild_destroy(discord_guild_t *guild)
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
_discord_load_guild(void **p_guild, struct api_response_s *res_body)
{
  discord_guild_t *guild = *p_guild;

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
discord_get_guild(discord_t *discord, char guild_id[], discord_guild_t **p_guild)
{
  Discord_api_request( 
    &discord->api,
    (void**)p_guild,
    &_discord_load_guild,
    GET, GUILDS, guild_id);
}
