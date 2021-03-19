#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace guild {

namespace get_guild {
void
run(client *client, const u64_snowflake_t guild_id, dati *p_guild)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle =
    { .ok_cb = &dati_from_json_v, .ok_obj = (void*)p_guild};

  adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/guilds/%llu", guild_id);
}
} // namespace get_guild

namespace get_channels {
void
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  NTL_T(channel::dati) *p_channels)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle = 
    { .ok_cb = &channel::dati_list_from_json_v, .ok_obj = (void*)p_channels};

  adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/guilds/%llu/channels", guild_id);
}
} // namespace get_channels

namespace create_channel {
void run(
  client *client, 
  const u64_snowflake_t guild_id, 
  params *params, 
  channel::dati *p_channel)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id");
    return;
  }
  if (IS_EMPTY_STRING(params->name)) {
    D_PUTS("Missing channel name (params.name)");
    return;
  }
  if (!orka_str_bounds_check(params->topic, 1024)) {
    D_PUTS("'params.topic' exceeds threshold of 1024");
    return;
  }

  char payload[MAX_PAYLOAD_LEN];
  create_channel::params_use_default_inject_settings(params);
  create_channel::params_to_json(payload, sizeof(payload), params);

  struct resp_handle resp_handle = {
    .ok_cb = p_channel ? &channel::dati_from_json_v : NULL,
    .ok_obj = p_channel,
  };

  struct sized_buffer req_body = {payload, strlen(payload)};

  adapter::run( 
    &client->adapter,
    &resp_handle,
    &req_body,
    HTTP_POST, "/guilds/%llu/channels", guild_id);
}
} // namespace create_channel

namespace get_guild_member {
void 
run(client *client, u64_snowflake_t guild_id, u64_snowflake_t user_id, member::dati **p_member) 
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }
  if (p_member == NULL || *p_member == NULL) {
    D_PUTS("'p_member' cannot be NULL");
    return;
  }

  struct resp_handle resp_handle = {
    .ok_cb = member::dati_from_json_v, .ok_obj = *p_member
  };

  adapter::run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, "/guilds/%llu/members/%llu", guild_id, user_id);
  D_PRINT("permssion %s\n", (*p_member)->permissions);
}
} // namespace get_guild_member

namespace list_guild_members {
void
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  struct params *params, 
  NTL_T(member::dati) *p_members)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (params->limit < 1 || params->limit > 1000) {
    D_PUTS("'limit' value should be in an interval of (1-1000)");
    return;
  }

  char limit_query[64];
  snprintf(limit_query, sizeof(limit_query),
      "?limit=%d", params->limit);

  char after_query[64] = "";
  if (params->after) {
    snprintf(after_query, sizeof(after_query),
        "&after=%" PRIu64 , params->after);
  }

  struct resp_handle resp_handle =
    { .ok_cb = &member::dati_list_from_json_v, .ok_obj = (void*)p_members};
  
  adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%llu/members%s%s", guild_id, limit_query, after_query);
}
} // namespace list_guild_members

namespace modify_guild_member {
void 
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id, 
  params *params, 
  member::dati *p_member)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  char payload[MAX_PAYLOAD_LEN];
  params_use_default_inject_settings(params);
  params_to_json(payload, sizeof(payload), params);

  struct resp_handle resp_handle = {
    .ok_cb = p_member ? &member::dati_from_json_v : NULL,
    .ok_obj = p_member,
  };

  struct sized_buffer req_body = {payload, strlen(payload)};

  adapter::run( 
    &client->adapter,
    &resp_handle,
    &req_body,
    HTTP_PATCH, "/guilds/%llu/members/%llu", guild_id, user_id);
}
} // namespace modify_guild_member

namespace remove_guild_member {
void run(
  client *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  adapter::run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_DELETE,
    "/guilds/%llu/members/%llu", guild_id, user_id);
}
} // namespace remove_guild_member

namespace get_guild_bans {
void
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  NTL_T(ban::dati) *p_bans)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle =
    { .ok_cb = &ban::dati_list_from_json_v, .ok_obj = (void*)p_bans};

  adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, "/guilds/%llu/bans", guild_id);
}
} // namespace get_guild_bans

namespace get_guild_ban {
void
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id, 
  ban::dati *p_ban)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  struct resp_handle resp_handle =
    { .ok_cb = &ban::dati_from_json_v, .ok_obj = (void*)p_ban};

  adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, "/guilds/%llu/bans/%llu", guild_id, user_id);
}
} // namespace get_guild_ban

namespace create_guild_ban {
void
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id, 
  int delete_message_days, 
  const char reason[])
{
  const int MAX_DELETE_MESSAGE_DAYS = 7;
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }
  if (reason && strlen(reason) > MAX_REASON_LEN) {
    D_PRINT("Reason length exceeds %u characters threshold (%zu)",
        MAX_REASON_LEN, strlen(reason));
    return;
  }
  if (delete_message_days < 0 || delete_message_days > MAX_DELETE_MESSAGE_DAYS) {
    D_PRINT("'delete_message_days' is outside the interval (0, %d)",
        MAX_DELETE_MESSAGE_DAYS);
    return;
  }

  void *A[2] = {0}; // pointer availability array.
  if (delete_message_days > 0)
    A[0] = (void *)&delete_message_days;
  if (!IS_EMPTY_STRING(reason))
    A[1] = (void *)reason;

  char payload[MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof(payload),
                        "(delete_message_days):d"
                        "(reason):s"
                        "@arg_switches",
                        &delete_message_days,
                        reason,
                        A, sizeof(A));

  struct sized_buffer req_body = {payload, (size_t)ret};

  adapter::run( 
    &client->adapter,
    NULL,
    &req_body,
    HTTP_PUT, "/guilds/%llu/bans/%llu", guild_id, user_id);
}
} // namespace create_guild_ban

namespace remove_guild_ban {
void
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t user_id, 
  const char reason[])
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }
  if (!orka_str_bounds_check(reason, MAX_REASON_LEN)) {
    D_PRINT("Reason length exceeds %u characters threshold (%zu)",
        MAX_REASON_LEN, strlen(reason));
    return;
  }

  void *A[1] = {0}; // pointer availability array.
  if(!IS_EMPTY_STRING(reason))
    A[0] = (void *)reason;

  char payload[MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof (payload),
                        "(reason):s"
                        "@arg_switches",
                        reason,
                        A, sizeof(A));

  struct sized_buffer req_body = {payload, (size_t)ret};

  adapter::run( 
    &client->adapter,
    NULL,
    &req_body,
    HTTP_DELETE, "/guilds/%llu/bans/%llu", guild_id, user_id);
}
} // namespace remove_guild_ban

namespace get_guild_roles {
void
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  NTL_T(role::dati) *p_roles)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle =
    { .ok_cb = &role::dati_list_from_json_v, .ok_obj = (void*)p_roles};

  adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, "/guilds/%llu/roles", guild_id);
}
} // namespace get_guild_roles

namespace create_guild_role {
void 
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  params *params, 
  role::dati *p_role)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  char payload[MAX_PAYLOAD_LEN];
  params_use_default_inject_settings(params);
  params_to_json(payload, sizeof(payload), params);

  struct resp_handle resp_handle = {
    .ok_cb = p_role ? &role::dati_from_json_v : NULL,
    .ok_obj = p_role,
  };

  struct sized_buffer req_body = {payload, strlen(payload)};

  adapter::run( 
    &client->adapter,
    &resp_handle,
    &req_body,
    HTTP_POST, "/guilds/%llu/roles", guild_id);
}
} // namespace create_guild_role

namespace delete_guild_role {
void 
run(
  client *client, 
  const u64_snowflake_t guild_id, 
  const u64_snowflake_t role_id)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!role_id) {
    D_PUTS("Missing 'role_id'");
    return;
  }

  adapter::run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_DELETE, "/guilds/%llu/roles/%llu", guild_id, role_id);
}
} // namespace delete_guild_role

} // namespace guild
} // namespace discord
