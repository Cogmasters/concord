#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_get_guild_template(struct discord *client,
                           char *code,
                           struct discord_guild_template *p_template)
{
  if (!code) {
    logconf_error(client->conf, "Missing 'code'");
    return ORCA_MISSING_PARAMETER;
  }

  if (!p_template) {
    logconf_error(client->conf, "Missing 'p_template'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = discord_guild_template_from_json_v,
                              .ok_obj = &p_template },
    NULL, HTTP_GET, "/guilds/templates/%s", code);
}

ORCAcode
discord_create_guild_template(
  struct discord *client,
  u64_snowflake_t guild_id,
  struct discord_create_guild_template_params *params,
  struct discord_guild_template *p_template)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }

  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  if (!p_template) {
    logconf_error(client->conf, "Missing 'p_template'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[256];
  size_t ret = discord_create_guild_template_params_to_json_v(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_guild_template_from_json_v,
                              .ok_obj = &p_template },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/guilds/%" PRIu64 "/templates", guild_id);
}

ORCAcode
discord_sync_guild_template(struct discord *client,
                            u64_snowflake_t guild_id,
                            char *code,
                            struct discord_guild_template *p_template)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }

  if (!p_template) {
    logconf_error(client->conf, "Missing 'p_template'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_guild_template_from_json_v,
                              .ok_obj = &p_template },
    NULL, HTTP_PUT, "/guilds/%" PRIu64 "/templates/%s", guild_id, code);
}
