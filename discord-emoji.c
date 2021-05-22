#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64 */

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


ORCAcode
discord_list_guild_emojis(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  NTL_T(struct discord_emoji) *p_emojis)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_emojis) {
    log_error("Missing 'p_emojis'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_emoji_list_from_json_v, 
    .ok_obj = p_emojis
  };

  return discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%"PRIu64"/emojis", guild_id);
}

ORCAcode
discord_get_guild_emoji(
  struct discord *client, 
  const u64_snowflake_t guild_id,
  const u64_snowflake_t emoji_id,
  struct discord_emoji *p_emoji)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!emoji_id) {
    log_error("Missing 'emoji_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_emoji) {
    log_error("Missing 'p_emoji'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_emoji_from_json_v, 
    .ok_obj = p_emoji
  };

  return discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%"PRIu64"/emojis/%"PRIu64, guild_id, emoji_id);
}
