#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


ORCAcode
discord_create_guild(
  struct discord *client,
  struct discord_create_guild_params *params,
  struct discord_guild *p_guild)
{
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_guild ? &discord_guild_from_json_v : NULL,
    .ok_obj = p_guild
  };

  char payload[4096];
  size_t ret = discord_create_guild_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST, 
           "/guilds");
}

ORCAcode
discord_get_guild(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  struct discord_guild *p_guild)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_guild) {
    log_error("Missing 'p_guild'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_guild_from_json_v, 
    .ok_obj = p_guild 
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/guilds/%"PRIu64, guild_id);
}

ORCAcode
discord_modify_guild(
  struct discord *client,
  const u64_snowflake_t guild_id,
  struct discord_modify_guild_params *params,
  struct discord_guild *p_guild)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_guild ? discord_guild_from_json_v : NULL,
    .ok_obj = p_guild
  };

  char payload[4096];
  size_t ret = discord_modify_guild_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_PATCH, 
           "/guilds/%"PRIu64, guild_id);
}

ORCAcode
discord_delete_guild(
  struct discord *client,
  const u64_snowflake_t guild_id)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run( 
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE, 
           "/guilds/%"PRIu64, guild_id);
}

ORCAcode
discord_get_guild_channels(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  NTL_T(struct discord_channel) *p_channels)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_channels) {
    log_error("Missing 'p_channels'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_channel_list_from_json_v, 
    .ok_obj = p_channels 
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/guilds/%"PRIu64"/channels", guild_id);
}

ORCAcode 
discord_create_guild_channel(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  struct discord_create_guild_channel_params *params, 
  struct discord_channel *p_channel)
{
  if (!guild_id) {
    log_error("Missing 'guild_id");
    return ORCA_MISSING_PARAMETER;
  }
  if (IS_EMPTY_STRING(params->name)) {
    log_error("Missing channel name (params.name)");
    return ORCA_BAD_PARAMETER;
  }
  if (!orka_str_bounds_check(params->topic, 1024)) {
    log_error("'params.topic' exceeds threshold of 1024");
    return ORCA_BAD_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_channel ? &discord_channel_from_json_v : NULL,
    .ok_obj = p_channel,
  };

  char payload[MAX_PAYLOAD_LEN];
  size_t ret = discord_create_guild_channel_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST, 
           "/guilds/%"PRIu64"/channels", guild_id);
}

ORCAcode 
discord_get_guild_member(struct discord *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, struct discord_guild_member *p_member) 
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_member) {
    log_error("Missing 'p_member'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = discord_guild_member_from_json_v, 
    .ok_obj = p_member
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/guilds/%"PRIu64"/members/%"PRIu64, guild_id, user_id);
}

ORCAcode
discord_list_guild_members(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  struct discord_list_guild_members_params *params, 
  NTL_T(struct discord_guild_member) *p_members)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_members) {
    log_error("Missing 'p_members'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (params->limit < 1 || params->limit > 1000) {
    log_error("'limit' value should be in an interval of (1-1000)");
    return ORCA_BAD_PARAMETER;
  }

  char limit_query[64];
  snprintf(limit_query, sizeof(limit_query),
      "?limit=%d", params->limit);

  char after_query[64] = "";
  if (params->after) {
    snprintf(after_query, sizeof(after_query),
        "&after=%"PRIu64, params->after);
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_guild_member_list_from_json_v, 
    .ok_obj = p_members 
  };
  
  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/guilds/%"PRIu64"/members%s%s", 
           guild_id, limit_query, after_query);
}

ORCAcode 
discord_modify_guild_member(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id, 
  struct discord_modify_guild_member_params *params, 
  struct discord_guild_member *p_member)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_member ? &discord_guild_member_from_json_v : NULL,
    .ok_obj = p_member,
  };

  char payload[MAX_PAYLOAD_LEN];
  size_t ret = discord_modify_guild_member_params_to_json(payload, sizeof(payload), params);

  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_PATCH, 
           "/guilds/%"PRIu64"/members/%"PRIu64, guild_id, user_id);
}

ORCAcode
discord_add_guild_member_role(
  struct discord *client,
  const u64_snowflake_t guild_id,
  const u64_snowflake_t user_id,
  const u64_snowflake_t role_id)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!role_id) {
    log_error("Missing 'role_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_PUT,
           "/guilds/%"PRIu64"/members/%"PRIu64"/roles/%"PRIu64, 
           guild_id, user_id, role_id);
}

ORCAcode
discord_remove_guild_member_role(
  struct discord *client,
  const u64_snowflake_t guild_id,
  const u64_snowflake_t user_id,
  const u64_snowflake_t role_id)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!role_id) {
    log_error("Missing 'role_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/guilds/%"PRIu64"/members/%"PRIu64"/roles/%"PRIu64, 
           guild_id, user_id, role_id);
}

ORCAcode 
discord_remove_guild_member(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/guilds/%"PRIu64"/members/%"PRIu64, guild_id, user_id);
}

ORCAcode
discord_get_guild_bans(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  NTL_T(struct discord_guild_ban) *p_bans)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_bans) {
    log_error("Missing 'p_bans'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_guild_ban_list_from_json_v, 
    .ok_obj = p_bans 
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/guilds/%"PRIu64"/bans", guild_id);
}

ORCAcode
discord_get_guild_ban(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id, 
  struct discord_guild_ban *p_ban)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_ban) {
    log_error("Missing 'p_ban'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_guild_ban_from_json_v, 
    .ok_obj = p_ban
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/guilds/%"PRIu64"/bans/%"PRIu64, guild_id, user_id);
}

ORCAcode
discord_create_guild_ban(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id, 
  int delete_message_days, 
  const char reason[])
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (delete_message_days < 0 || delete_message_days > 7) {
    log_error("'delete_message_days' is outside the interval (0, 7)");
    return ORCA_BAD_PARAMETER;
  }

  void *A[2]={}; // pointer availability array.
  A[0] = (void *)&delete_message_days;
  if (!IS_EMPTY_STRING(reason)) {
    if (!orka_str_bounds_check(reason, MAX_REASON_LEN)) {
      log_error("Reason length exceeds %d characters threshold (%zu)",
          MAX_REASON_LEN, strlen(reason));
      return ORCA_BAD_PARAMETER;
    }
    A[1] = (void *)reason;
  }


  char payload[MAX_PAYLOAD_LEN];
  size_t ret = json_inject(payload, sizeof(payload),
                        "(delete_message_days):d"
                        "(reason):s"
                        "@arg_switches",
                        &delete_message_days,
                        reason,
                        A, sizeof(A));

  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run( 
           &client->adapter,
           NULL,
           &req_body,
           HTTP_PUT, 
           "/guilds/%"PRIu64"/bans/%"PRIu64, guild_id, user_id);
}
ORCAcode
discord_remove_guild_ban(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id, 
  const char reason[])
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[MAX_PAYLOAD_LEN]="";
  size_t ret=0;
  if(!IS_EMPTY_STRING(reason)) {
    if (!orka_str_bounds_check(reason, MAX_REASON_LEN)) {
      log_error("Reason length exceeds %d characters threshold (%zu)",
          MAX_REASON_LEN, strlen(reason));
      return ORCA_BAD_PARAMETER;
    }
    ret = json_inject(payload, sizeof(payload), "(reason):s", reason);
  }
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run( 
           &client->adapter,
           NULL,
           &req_body,
           HTTP_DELETE, 
           "/guilds/%"PRIu64"/bans/%"PRIu64, guild_id, user_id);
}

ORCAcode
discord_get_guild_roles(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  NTL_T(struct discord_guild_role) *p_roles)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_roles) {
    log_error("Missing 'p_roles'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_guild_role_list_from_json_v, 
    .ok_obj = p_roles 
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/guilds/%"PRIu64"/roles", guild_id);
}

ORCAcode 
discord_create_guild_role(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  struct discord_create_guild_role_params *params, 
  struct discord_guild_role *p_role)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_role ? &discord_guild_role_from_json_v : NULL,
    .ok_obj = p_role,
  };

  char payload[MAX_PAYLOAD_LEN];
  size_t ret = discord_create_guild_role_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST, 
           "/guilds/%"PRIu64"/roles", guild_id);
}

ORCAcode 
discord_delete_guild_role(
  struct discord *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t role_id)
{
  if (!guild_id) {
    log_error("Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!role_id) {
    log_error("Missing 'role_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE, 
           "/guilds/%"PRIu64"/roles/%"PRIu64, guild_id, role_id);
}
