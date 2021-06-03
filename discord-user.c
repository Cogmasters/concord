#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


ORCAcode 
discord_get_current_user(struct discord *client, struct discord_user *p_user)
{
  if (!p_user) {
    log_error("Missing 'p_user'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_user_from_json_v, 
    .ok_obj = p_user
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/users/@me");
}

ORCAcode
discord_get_user(struct discord *client, const u64_snowflake_t user_id, struct discord_user *p_user)
{
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_user) {
    log_error("Missing 'p_user'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_user_from_json_v, 
    .ok_obj = p_user
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/users/%"PRIu64, user_id);
}

ORCAcode
discord_modify_current_user(struct discord *client, struct discord_modify_current_user_params *params, struct discord_user *p_user)
{
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = p_user ? &discord_user_from_json_v : NULL, 
    .ok_obj = p_user
  };

  char payload[MAX_PAYLOAD_LEN];
  size_t ret = discord_modify_current_user_params_to_json(payload, sizeof(payload), params);

  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_PATCH,
           "/users/@me");
}

/* @todo this is a temporary solution for wrapping with JS */
static void 
json_to_sb(char *json, size_t len, void *p_sb_user)
{
  struct sized_buffer *sb_user = (struct sized_buffer*)p_sb_user;
  sb_user->start = strndup(json, len);
}

ORCAcode /* @todo this is a temporary solution for easily wrapping JS */
sb_discord_get_current_user(struct discord *client, struct sized_buffer *p_sb_user)
{
  if (!p_sb_user) {
    log_error("Missing 'p_sb_user'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = &json_to_sb, 
    .ok_obj = p_sb_user
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/users/@me");
}

ORCAcode
discord_get_current_user_guilds(struct discord *client, NTL_T(struct discord_guild) *p_guilds)
{
  if (!p_guilds) {
    log_error("Missing 'p_guilds'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_guild_list_from_json_v, 
    .ok_obj = p_guilds
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/users/@me/guilds");
}

ORCAcode 
discord_leave_guild(struct discord *client, const u64_snowflake_t guild_id)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }

  struct sized_buffer req_body = {"{}", 2};

  return discord_adapter_run(
           &client->adapter,
           NULL,
           &req_body,
           HTTP_DELETE,
           "/users/@me/guilds/%"PRIu64, guild_id);
}

ORCAcode 
discord_create_dm(struct discord *client, const u64_snowflake_t recipient_id, struct discord_channel *p_dm_channel)
{
  if (!recipient_id) {
    log_error("Missing 'recipient_id'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_dm_channel ? &discord_channel_from_json_v : NULL,
    .ok_obj = p_dm_channel
  };

  char payload[256];
  size_t ret = json_inject(payload, sizeof(payload), \
      "(recipient_id):s_as_u64", &recipient_id);

  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST,
           "/users/@me/channels");
}

ORCAcode
discord_create_group_dm(struct discord *client, struct discord_create_group_dm_params *params, struct discord_channel *p_dm_channel)
{
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->access_tokens) {
    log_error("Missing 'params.access_tokens'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->nicks) {
    log_error("Missing 'params.nicks'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_dm_channel ? &discord_channel_from_json_v : NULL,
    .ok_obj = p_dm_channel
  };

  char payload[1024];
  size_t ret = discord_create_group_dm_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST,
           "/users/@me/channels");
}

ORCAcode
discord_get_user_connections(struct discord *client, NTL_T(struct discord_connection) *p_connections)
{
  if (!p_connections) {
    log_error("Missing 'p_connections'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = &discord_connection_list_from_json_v,
    .ok_obj = p_connections
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/users/@me/connections");
}
