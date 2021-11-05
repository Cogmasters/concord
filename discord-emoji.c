#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64 */

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_list_guild_emojis(struct discord *client,
                          const u64_snowflake_t guild_id,
                          NTL_T(struct discord_emoji) * p_emojis)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_emojis) {
    logconf_error(client->conf, "Missing 'p_emojis'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_emoji_list_from_json_v,
                              .ok_obj = p_emojis },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/emojis", guild_id);
}

ORCAcode
discord_get_guild_emoji(struct discord *client,
                        const u64_snowflake_t guild_id,
                        const u64_snowflake_t emoji_id,
                        struct discord_emoji *p_emoji)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!emoji_id) {
    logconf_error(client->conf, "Missing 'emoji_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_emoji) {
    logconf_error(client->conf, "Missing 'p_emoji'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_emoji_from_json_v,
                              .ok_obj = &p_emoji },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id, emoji_id);
}

ORCAcode
discord_create_guild_emoji(struct discord *client,
                           const u64_snowflake_t guild_id,
                           struct discord_create_guild_emoji_params *params,
                           struct discord_emoji *p_emoji)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char *payload = NULL;
  size_t ret =
    json_ainject(&payload, "(name):s,(image):s,(roles):F", params->name,
                 params->image, &ja_u64_list_to_json, params->roles);

  if (!payload) {
    logconf_error(client->conf, "Couldn't create JSON Payload");
    return ORCA_BAD_JSON;
  }

  ORCAcode code;
  code =
    discord_adapter_run(&client->adapter,
                        &(struct ua_resp_handle){
                          .ok_cb = p_emoji ? &discord_emoji_from_json_v : NULL,
                          .ok_obj = &p_emoji },
                        &(struct sized_buffer){ payload, ret }, HTTP_POST,
                        "/guilds/%" PRIu64 "/emojis", guild_id);

  free(payload);

  return code;
}

ORCAcode
discord_modify_guild_emoji(struct discord *client,
                           const u64_snowflake_t guild_id,
                           const u64_snowflake_t emoji_id,
                           struct discord_modify_guild_emoji_params *params,
                           struct discord_emoji *p_emoji)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!emoji_id) {
    logconf_error(client->conf, "Missing 'emoji_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  void *A[2] = {}; /* pointer availability array */
  if (params->name) A[0] = params->name;
  if (params->roles) A[1] = params->roles;

  char *payload = NULL;
  size_t ret = json_ainject(&payload,
                            "(name):s"
                            "(roles):F"
                            "@arg_switches",
                            params->name, &ja_u64_list_to_json, params->roles,
                            A, sizeof(A));

  if (!payload) {
    logconf_error(client->conf, "Couldn't create JSON Payload");
    return ORCA_BAD_JSON;
  }

  ORCAcode code;
  code = discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb =
                                p_emoji ? &discord_emoji_from_json_v : NULL,
                              .ok_obj = &p_emoji },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id, emoji_id);

  free(payload);

  return code;
}

ORCAcode
discord_delete_guild_emoji(struct discord *client,
                           const u64_snowflake_t guild_id,
                           const u64_snowflake_t emoji_id)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!emoji_id) {
    logconf_error(client->conf, "Missing 'emoji_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/emojis/%" PRIu64, guild_id,
                             emoji_id);
}
