#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace guild {

void
get(client *client, const uint64_t guild_id, dati *p_guild)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle = {&dati_from_json_v, (void*)p_guild};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/guilds/%llu", guild_id);
}

channel::dati**
get_channels(client *client, const uint64_t guild_id)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return NULL;
  }

  channel::dati **new_channels = NULL;

  struct resp_handle resp_handle = 
    {&channel::dati_list_from_json_v, (void*)&new_channels};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/guilds/%llu/channels", guild_id);

  return new_channels;
}

namespace create_channel {

void run(client *client, const uint64_t guild_id, params *params, channel::dati *p_channel)
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
    .ok_cb = p_channel ? channel::dati_from_json_v : NULL,
    .ok_obj = p_channel,
  };

  struct sized_buffer req_body = {payload, strlen(payload)};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &req_body,
    HTTP_POST, "/guilds/%llu/channels", guild_id);
}

} // namespace create_channel

namespace modify_member {

void 
run(client *client, const uint64_t guild_id, const uint64_t user_id, params *params, member::dati *p_member)
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
  modify_member::params_use_default_inject_settings(params);
  modify_member::params_to_json(payload, sizeof(payload), params);

  struct resp_handle resp_handle = {
    .ok_cb = p_member ? member::dati_from_json_v : NULL,
    .ok_obj = p_member,
  };

  struct sized_buffer req_body = {payload, strlen(payload)};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &req_body,
    HTTP_PATCH, "/guilds/%llu/members/%llu", guild_id, user_id);
}

} // namespace modify_member

namespace create_role {

void run(client *client, const uint64_t guild_id, params *params, role::dati *p_role)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  char payload[MAX_PAYLOAD_LEN];
  create_role::params_use_default_inject_settings(params);
  create_role::params_to_json(payload, sizeof(payload), params);

  struct resp_handle resp_handle = {
    .ok_cb = p_role ? role::dati_from_json_v : NULL,
    .ok_obj = p_role,
  };

  struct sized_buffer req_body = {payload, strlen(payload)};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &req_body,
    HTTP_POST, "/guilds/%llu/roles", guild_id);
}

} // namespace create_role

namespace member {

namespace get_list {

dati**
run(client *client, const uint64_t guild_id, struct params *params)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return NULL;
  }

  if (params->limit < 1 || params->limit > 1000) {
    D_PUTS("'limit' value should be in an interval of (1-1000)");
    return NULL;
  }

  char limit_query[64];
  snprintf(limit_query, sizeof(limit_query),
      "?limit=%d", params->limit);

  char after_query[64] = "";
  if (params->after) {
    snprintf(after_query, sizeof(after_query),
        "&after=%" PRIu64 , params->after);
  }

  dati **new_members = NULL;

  struct resp_handle resp_handle =
    {dati_list_from_json_v, (void*)&new_members};
  
  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%llu/members%s%s", guild_id, limit_query, after_query);

  return new_members;
}

} // namespace get_list

void remove(client *client, const uint64_t guild_id, const uint64_t user_id)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  user_agent::run(
    &client->ua,
    NULL,
    NULL,
    HTTP_DELETE,
    "/guilds/%llu/members/%llu", guild_id, user_id);
}

} // namespace member

namespace ban {

void
get(client *client, const uint64_t guild_id, const uint64_t user_id, dati *p_ban)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  struct resp_handle resp_handle = {&dati_from_json_v, (void*)p_ban};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%llu/bans/%llu", guild_id, user_id);
}

//@todo modifiable query string parameters
dati**
get_list(client *client, const uint64_t guild_id)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return NULL;
  }

  dati **new_bans = NULL;

  struct resp_handle resp_handle =
    {&dati_list_from_json_v, (void*)&new_bans};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%llu/bans", guild_id);

  return new_bans;
}

void
create(client *client, const uint64_t guild_id, const uint64_t user_id, int delete_message_days, const char reason[])
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

  user_agent::run( 
    &client->ua,
    NULL,
    &req_body,
    HTTP_PUT,
    "/guilds/%llu/bans/%llu", guild_id, user_id);
}

void
remove(client *client, const uint64_t guild_id, const uint64_t user_id, const char reason[])
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }
  if(reason && strlen(reason) > MAX_REASON_LEN) {
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

  user_agent::run( 
    &client->ua,
    NULL,
    &req_body,
    HTTP_DELETE, 
    "/guilds/%llu/bans/%llu", guild_id, user_id);
}

} // namespace ban

} // namespace guild
} // namespace discord
