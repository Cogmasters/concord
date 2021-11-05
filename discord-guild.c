#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_create_guild(struct discord *client,
                     struct discord_create_guild_params *params,
                     struct discord_guild *p_guild)
{
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret =
    discord_create_guild_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb =
                                p_guild ? &discord_guild_from_json_v : NULL,
                              .ok_obj = &p_guild },
    &(struct sized_buffer){ payload, ret }, HTTP_POST, "/guilds");
}

ORCAcode
discord_get_guild(struct discord *client,
                  const u64_snowflake_t guild_id,
                  struct discord_guild *p_guild)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_guild) {
    logconf_error(client->conf, "Missing 'p_guild'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_guild_from_json_v,
                              .ok_obj = &p_guild },
    NULL, HTTP_GET, "/guilds/%" PRIu64, guild_id);
}

ORCAcode
discord_get_guild_preview(struct discord *client,
                          const u64_snowflake_t guild_id,
                          struct discord_guild_preview *p_guild_preview)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_guild_preview) {
    logconf_error(client->conf, "Missing 'p_guild_preview'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_guild_preview_from_json_v,
                              .ok_obj = &p_guild_preview },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/preview", guild_id);
}

ORCAcode
discord_modify_guild(struct discord *client,
                     const u64_snowflake_t guild_id,
                     struct discord_modify_guild_params *params,
                     struct discord_guild *p_guild)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret =
    discord_modify_guild_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb =
                                p_guild ? &discord_guild_from_json_v : NULL,
                              .ok_obj = &p_guild },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH, "/guilds/%" PRIu64,
    guild_id);
}

ORCAcode
discord_delete_guild(struct discord *client, const u64_snowflake_t guild_id)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64, guild_id);
}

ORCAcode
discord_get_guild_channels(struct discord *client,
                           const u64_snowflake_t guild_id,
                           NTL_T(struct discord_channel) * p_channels)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_channels) {
    logconf_error(client->conf, "Missing 'p_channels'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_channel_list_from_json_v,
                              .ok_obj = p_channels },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/channels", guild_id);
}

ORCAcode
discord_create_guild_channel(
  struct discord *client,
  const u64_snowflake_t guild_id,
  struct discord_create_guild_channel_params *params,
  struct discord_channel *p_channel)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[2048];
  size_t ret = discord_create_guild_channel_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_channel ? &discord_channel_from_json_v
                                                 : NULL,
                              .ok_obj = &p_channel },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/guilds/%" PRIu64 "/channels", guild_id);
}

ORCAcode
discord_modify_guild_channel_positions(
  struct discord *client,
  const u64_snowflake_t guild_id,
  NTL_T(struct discord_modify_guild_channel_positions_params) params)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret = discord_modify_guild_channel_positions_params_list_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter, NULL, &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/guilds/%" PRIu64 "/channels", guild_id);
}

ORCAcode
discord_get_guild_member(struct discord *client,
                         u64_snowflake_t guild_id,
                         u64_snowflake_t user_id,
                         struct discord_guild_member *p_member)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_member) {
    logconf_error(client->conf, "Missing 'p_member'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = discord_guild_member_from_json_v,
                              .ok_obj = &p_member },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id, user_id);
}

ORCAcode
discord_list_guild_members(struct discord *client,
                           const u64_snowflake_t guild_id,
                           struct discord_list_guild_members_params *params,
                           NTL_T(struct discord_guild_member) * p_members)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_members) {
    logconf_error(client->conf, "Missing 'p_members'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[1024] = "";
  if (params) {
    size_t offset = 0;
    if (params->limit) {
      offset += snprintf(query + offset, sizeof(query) - offset, "limit=%d",
                         params->limit);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->after) {
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "%safter=%" PRIu64,
                 (*query) ? "&" : "", params->after);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_guild_member_list_from_json_v,
                              .ok_obj = p_members },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/members%s%s", guild_id,
    (*query) ? "?" : "", query);
}

ORCAcode
discord_search_guild_members(
  struct discord *client,
  const u64_snowflake_t guild_id,
  struct discord_search_guild_members_params *params,
  NTL_T(struct discord_guild_member) * p_members)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_members) {
    logconf_error(client->conf, "Missing 'p_members'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[1024] = "";
  if (params) {
    size_t offset = 0;
    if (params->query) {
      char *pe_query = url_encode(params->query);
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "query=%s", pe_query);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
      free(pe_query);
    }
    if (params->limit) {
      offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                         (*query) ? "&" : "", params->limit);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_guild_member_list_from_json_v,
                              .ok_obj = p_members },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/members/search%s%s", guild_id,
    (*query) ? "?" : "", query);
}

ORCAcode
discord_add_guild_member(struct discord *client,
                         const u64_snowflake_t guild_id,
                         const u64_snowflake_t user_id,
                         struct discord_add_guild_member_params *params,
                         struct discord_guild_member *p_member)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params || !params->access_token) {
    logconf_error(client->conf, "Missing 'params.access_token'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret =
    discord_add_guild_member_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = discord_guild_member_from_json_v,
                              .ok_obj = &p_member },
    &(struct sized_buffer){ payload, ret }, HTTP_PUT,
    "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id, user_id);
}

ORCAcode
discord_modify_guild_member(struct discord *client,
                            const u64_snowflake_t guild_id,
                            const u64_snowflake_t user_id,
                            struct discord_modify_guild_member_params *params,
                            struct discord_guild_member *p_member)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[2048];
  size_t ret = discord_modify_guild_member_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = p_member ? &discord_guild_member_from_json_v : NULL,
      .ok_obj = &p_member,
    },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id, user_id);
}
ORCAcode
discord_modify_current_member(
  struct discord *client,
  const u64_snowflake_t guild_id,
  struct discord_modify_current_member_params *params,
  struct discord_guild_member *p_member)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->nick) {
    logconf_error(client->conf, "Missing 'params.nick'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[512];
  size_t ret = discord_modify_current_member_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = p_member ? &discord_guild_member_from_json_v : NULL,
      .ok_obj = &p_member },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/guilds/%" PRIu64 "/members/@me", guild_id);
}
ORCAcode
discord_modify_current_user_nick(
  struct discord *client,
  const u64_snowflake_t guild_id,
  struct discord_modify_current_user_nick_params *params,
  struct discord_guild_member *p_member)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params->nick) {
    logconf_error(client->conf, "Missing 'params.nick'");
    return ORCA_MISSING_PARAMETER;
  }

  logconf_warn(client->conf,
               "This endpoint is now deprecated by Discord. Please use "
               "discord_modify_current_member instead");

  char payload[512];
  size_t ret = discord_modify_current_user_nick_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = p_member ? &discord_guild_member_from_json_v : NULL,
      .ok_obj = &p_member },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/guilds/%" PRIu64 "/members/@me/nick", guild_id);
}

ORCAcode
discord_add_guild_member_role(struct discord *client,
                              const u64_snowflake_t guild_id,
                              const u64_snowflake_t user_id,
                              const u64_snowflake_t role_id)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!role_id) {
    logconf_error(client->conf, "Missing 'role_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/guilds/%" PRIu64 "/members/%" PRIu64
                             "/roles/%" PRIu64,
                             guild_id, user_id, role_id);
}

ORCAcode
discord_remove_guild_member_role(struct discord *client,
                                 const u64_snowflake_t guild_id,
                                 const u64_snowflake_t user_id,
                                 const u64_snowflake_t role_id)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!role_id) {
    logconf_error(client->conf, "Missing 'role_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/members/%" PRIu64
                             "/roles/%" PRIu64,
                             guild_id, user_id, role_id);
}

ORCAcode
discord_remove_guild_member(struct discord *client,
                            const u64_snowflake_t guild_id,
                            const u64_snowflake_t user_id)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/members/%" PRIu64, guild_id,
                             user_id);
}

ORCAcode
discord_get_guild_bans(struct discord *client,
                       const u64_snowflake_t guild_id,
                       NTL_T(struct discord_ban) * p_bans)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_bans) {
    logconf_error(client->conf, "Missing 'p_bans'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_ban_list_from_json_v,
                              .ok_obj = p_bans },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/bans", guild_id);
}

ORCAcode
discord_get_guild_ban(struct discord *client,
                      const u64_snowflake_t guild_id,
                      const u64_snowflake_t user_id,
                      struct discord_ban *p_ban)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_ban) {
    logconf_error(client->conf, "Missing 'p_ban'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_ban_from_json_v,
                              .ok_obj = &p_ban },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id, user_id);
}

ORCAcode
discord_create_guild_ban(struct discord *client,
                         const u64_snowflake_t guild_id,
                         const u64_snowflake_t user_id,
                         struct discord_create_guild_ban_params *params)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (params->delete_message_days < 0 || params->delete_message_days > 7) {
    logconf_error(client->conf,
      "'delete_message_days' is outside the interval (client->conf, 0, 7)");
    return ORCA_BAD_PARAMETER;
  }

  char payload[256];
  size_t ret =
    discord_create_guild_ban_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter, NULL, &(struct sized_buffer){ payload, ret }, HTTP_PUT,
    "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id, user_id);
}
ORCAcode
discord_remove_guild_ban(struct discord *client,
                         const u64_snowflake_t guild_id,
                         const u64_snowflake_t user_id)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/bans/%" PRIu64, guild_id,
                             user_id);
}

ORCAcode
discord_get_guild_roles(struct discord *client,
                        const u64_snowflake_t guild_id,
                        NTL_T(struct discord_role) * p_roles)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_roles) {
    logconf_error(client->conf, "Missing 'p_roles'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_role_list_from_json_v,
                              .ok_obj = p_roles },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/roles", guild_id);
}

ORCAcode
discord_create_guild_role(struct discord *client,
                          const u64_snowflake_t guild_id,
                          struct discord_create_guild_role_params *params,
                          struct discord_role *p_role)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret =
    discord_create_guild_role_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = p_role ? &discord_role_from_json_v : NULL, .ok_obj = &p_role },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/guilds/%" PRIu64 "/roles", guild_id);
}

ORCAcode
discord_modify_guild_role_positions(
  struct discord *client,
  const u64_snowflake_t guild_id,
  NTL_T(struct discord_modify_guild_role_positions_params) params,
  NTL_T(struct discord_role) * p_roles)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret = discord_modify_guild_role_positions_params_list_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_roles ? &discord_role_list_from_json_v
                                               : NULL,
                              .ok_obj = p_roles },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/guilds/%" PRIu64 "/roles", guild_id);
}

ORCAcode
discord_modify_guild_role(struct discord *client,
                          const u64_snowflake_t guild_id,
                          const u64_snowflake_t role_id,
                          struct discord_modify_guild_role_params *params,
                          struct discord_role *p_role)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!role_id) {
    logconf_error(client->conf, "Missing 'role_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[2048] = "{}";
  size_t ret;
  if (params)
    ret = discord_modify_guild_role_params_to_json(payload, sizeof(payload),
                                                   params);
  else
    ret = sprintf(payload, "{}");

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = p_role ? &discord_role_from_json_v : NULL, .ok_obj = &p_role },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id, role_id);
}

ORCAcode
discord_delete_guild_role(struct discord *client,
                          const u64_snowflake_t guild_id,
                          const u64_snowflake_t role_id)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!role_id) {
    logconf_error(client->conf, "Missing 'role_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/roles/%" PRIu64, guild_id,
                             role_id);
}
ORCAcode
discord_begin_guild_prune(struct discord *client,
                          const u64_snowflake_t guild_id,
                          struct discord_begin_guild_prune_params *params)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[DISCORD_MAX_PAYLOAD_LEN];
  size_t ret;

  if (params)
    ret = discord_begin_guild_prune_params_to_json(payload, sizeof(payload),
                                                   params);
  else
    ret = sprintf(payload, "{}");

  return discord_adapter_run(&client->adapter, NULL,
                             &(struct sized_buffer){ payload, ret }, HTTP_POST,
                             "/guilds/%" PRIu64 "/prune", guild_id);
}

ORCAcode
discord_get_guild_invites(struct discord *client,
                          const u64_snowflake_t guild_id,
                          NTL_T(struct discord_invite) * p_invites)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_invites) {
    logconf_error(client->conf, "Missing 'p_invites'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_invite_list_from_json_v,
                              .ok_obj = p_invites },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/invites", guild_id);
}
ORCAcode
discord_delete_guild_integrations(struct discord *client,
                                  const u64_snowflake_t guild_id,
                                  const u64_snowflake_t integration_id)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!integration_id) {
    logconf_error(client->conf, "Missing 'integration_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/guilds/%" PRIu64 "/integrations/%" PRIu64,
                             guild_id, integration_id);
}

ORCAcode
discord_get_guild_vanity_url(struct discord *client,
                             const u64_snowflake_t guild_id,
                             struct discord_invite *p_invite)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_invite) {
    logconf_error(client->conf, "Missing 'p_invites'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_invite_from_json_v,
                              .ok_obj = &p_invite },
    NULL, HTTP_GET, "/guilds/%" PRIu64 "/vanity-url", guild_id);
}

ORCAcode
discord_get_guild_welcome_screen(struct discord *client,
                                 const u64_snowflake_t guild_id,
                                 struct discord_welcome_screen *p_screen)
{
  if (!guild_id) {
    logconf_error(client->conf, "Missing 'guild_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_screen) {
    logconf_error(client->conf, "Missing 'p_screen'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter,
                             &(struct ua_resp_handle){
                               .ok_cb = &discord_welcome_screen_from_json_v,
                               .ok_obj = &p_screen,
                             },
                             NULL, HTTP_GET,
                             "/guilds/%" PRIu64 "/welcome-screen", guild_id);
}
