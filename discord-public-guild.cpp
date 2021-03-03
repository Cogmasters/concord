#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace guild {
#if 0
void
dati_from_json(char *str, size_t len, void *p_guild)
{
  dati *guild = (dati*)p_guild;

  json_scanf(str, len,
     "[id]%F"
     "[name]%s"
     "[icon]%s"
     "[icon_hash]%s"
     "[splash]%s"
     "[discovery_splash]%s"
     "[owner]%b"
     "[owner_id]%F"
     "[permissions]%d"
     "[region]%s"
     "[afk_channel_id]%F"
     "[afk_timeout]%d"
     "[widget_enabled]%b"
     "[widget_channel_id]%F"
     "[verification_level]%d"
     "[default_message_notifications]%d"
     "[explicit_content_filter]%d"
     "[mfa_level]%d"
     "[application_id]%F"
     "[system_channel_id]%F"
     "[system_channel_flags]%d"
     "[rules_channel_id]%F"
     "[joined_at]%F"
     "[large]%b"
     "[unavailable]%b"
     "[member_count]%d"
     "[members]%F"
     "[channels]%F"
     "[max_presences]%d"
     "[max_members]%d"
     "[vanity_url_code]%s"
     "[description]%s"
     "[banner]%s"
     "[premium_tier]%d"
     "[premium_subscription_count]%d"
     "[preferred_locale]%s"
     "[public_updates_channel_id]%F"
     "[max_video_channel_users]%d"
     "[approximate_member_count]%d"
     "[approximate_presence_count]%d",
      &orka_strtoull, &guild->id,
      guild->name,
      guild->icon,
      guild->icon_hash,
      guild->splash,
      guild->discovery_splash,
      &guild->owner,
      &orka_strtoull, &guild->owner_id,
      &guild->permissions,
      guild->region,
      &orka_strtoull, &guild->afk_channel_id,
      &guild->afk_timeout,
      &guild->widget_enabled,
      &orka_strtoull, &guild->widget_channel_id,
      &guild->verification_level,
      &guild->default_message_notifications,
      &guild->explicit_content_filter,
      &guild->mfa_level,
      &orka_strtoull, &guild->application_id,
      &orka_strtoull, &guild->system_channel_id,
      &guild->system_channel_flags,
      &orka_strtoull, &guild->rules_channel_id,
      &orka_iso8601_to_unix_ms, &guild->joined_at,
      &guild->large,
      &guild->unavailable,
      &guild->member_count,
      &guild::dati_list_from_json, &guild->members,
      &channel::dati_list_from_json, &guild->channels,
      &guild->max_presences,
      &guild->max_members,
      guild->vanity_url_code,
      guild->description,
      guild->banner,
      &guild->premium_tier,
      &guild->premium_subscription_count,
      guild->preferred_locale,
      &orka_strtoull, &guild->public_updates_channel_id,
      &guild->max_video_channel_users,
      &guild->approximate_member_count,
      &guild->approximate_presence_count);

  DS_NOTOP_PUTS("Guild object loaded with API response"); 
}

void
dati_list_from_json(char *str, size_t len, void *p_guilds)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init;
  d.elem_from_buf = &dati_from_json;
  d.ntl_recipient_p = (void***)p_guilds;
  orka_str_to_ntl(str, len, &d);
}

void
dati_init(void *p_guild) 
{
  dati *guild = (dati*)p_guild;
  memset(guild, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *new_guild = (dati*)malloc(sizeof(dati));
  dati_init((void*)new_guild);
  return new_guild;
}

void
dati_cleanup(void *p_guild) 
{
  dati *guild = (dati*)p_guild;
  if (guild->members)
    member::dati_list_free(guild->members);
  if (guild->channels)
    channel::dati_list_free(guild->channels);

  DS_NOTOP_PUTS("Guild object fields cleared"); 
}

void
dati_free(dati *guild) 
{
  dati_cleanup((void*)guild);
  free(guild);
}

void
dati_list_free(dati **guilds) {
  ntl_free((void**)guilds, &dati_cleanup);
}
#endif

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
    {&channel::dati_list_from_json, (void*)&new_channels};

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
#if 0
  void *A[10] = {0}; // pointer availability array.
  A[0] = (void *)params->name;
  A[1] = (void *)&params->type;
  if (!IS_EMPTY_STRING(params->topic))
    A[2] = (void *)&params->topic;
  if (params->bitrate)
    A[3] = (void *)&params->bitrate;
  if (params->user_limit)
    A[4] = (void *)&params->user_limit;
  if (params->rate_limit_per_user)
    A[5] = (void *)&params->rate_limit_per_user;
  A[6] = (void *)&params->position;
  if (params->permission_overwrites)
    A[7] = (void *)params->permission_overwrites;
  if (params->parent_id)
    A[8] = (void *)&params->parent_id;
  A[9] = (void *)&params->nsfw;

  json_inject(payload, sizeof(payload),
      "(name):s"
      "(type):d"
      "(topic):s"
      "(bitrate):d"
      "(user_limit):d"
      "(rate_limit_per_user):d"
      "(position):d"
      "(permission_overwrites):F"
      "(parent_id):s_as_u64"
      "(nsfw):b"
      "@arg_switches",
      params->name,
      &params->type,
      params->topic,
      &params->user_limit,
      &params->bitrate,
      &params->rate_limit_per_user,
      &params->position,
      &channel::overwrite::dati_list_to_json, params->permission_overwrites,
      &params->parent_id,
      &params->nsfw,
      A, sizeof(A));
#endif
  char payload[MAX_PAYLOAD_LEN];
  create_channel::params_use_default_inject_settings(params);
  create_channel::params_to_json(payload, sizeof(payload), params);

  struct resp_handle resp_handle = {
    .ok_cb = p_channel ? channel::dati_from_json : NULL,
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
#if 0
void
dati_from_json(char *str, size_t len, void *p_member)
{
  dati *member = (dati*)p_member;

  json_scanf(str, len,
     "[user]%F"
     "[nick]%s"
     "[joined_at]%F"
     "[premium_since]%F"
     "[deaf]%b"
     "[mute]%b"
     "[pending]%b",
      &user::dati_from_json, member->user,
      member->nick,
      &orka_iso8601_to_unix_ms, &member->joined_at,
      &orka_iso8601_to_unix_ms, &member->premium_since,
      &member->deaf,
      &member->mute,
      &member->pending);

  DS_NOTOP_PUTS("Member object loaded with API response"); 
}

void
dati_list_from_json(char *str, size_t len, void *p_members)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init;
  d.elem_from_buf = &dati_from_json;
  d.ntl_recipient_p = (void***)p_members;
  orka_str_to_ntl(str, len, &d);
}

void
dati_init(void *p_member)
{
  dati *member = (dati*)p_member;
  memset(member, 0, sizeof(dati));
  member->user = user::dati_alloc();
}

dati*
dati_alloc()
{
  dati *new_member = (dati*)malloc(sizeof(dati));
  dati_init((void*)new_member);
  return new_member;
}

void
dati_cleanup(void *p_member) 
{
  dati *member = (dati*)p_member;
  user::dati_free(member->user);

  DS_NOTOP_PUTS("Member object fields cleared"); 
}

void
dati_free(dati *member) 
{
  dati_cleanup((void*)member);
  free(member);
}

void
dati_list_free(dati **members) {
  ntl_free((void**)members, &dati_cleanup);
}
#endif

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
#if 0
void
dati_from_json(char *str, size_t len, void *p_ban)
{
  dati *ban = (dati*)p_ban;

  json_scanf(str, len,
     "[reason]%s"
     "[user]%F",
      ban->reason,
      &user::dati_from_json, ban->user);

  DS_NOTOP_PUTS("Ban object loaded with API response"); 
}

void
dati_list_from_json(char *str, size_t len, void *p_bans)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init;
  d.elem_from_buf = &dati_from_json;
  d.ntl_recipient_p = (void***)p_bans;
  orka_str_to_ntl(str, len, &d);
}

void
dati_init(void *p_ban)
{
  dati *ban = (dati*)p_ban;
  memset(ban, 0, sizeof(dati));
  ban->user = user::dati_alloc();
}

dati*
dati_alloc()
{
  dati *new_ban = (dati*)malloc(sizeof(dati));
  dati_init((void*)new_ban);
  return new_ban;
}

void
dati_cleanup(void *p_ban)
{
  dati *ban = (dati*)p_ban;
  user::dati_free(ban->user);

  DS_NOTOP_PUTS("Ban object fields cleared"); 
}

void
dati_free(dati *ban) 
{
  dati_free(ban);
  free(ban);
}

void
dati_list_free(dati **bans) {
  ntl_free((void**)bans, &dati_cleanup);
}
#else
// these functions are generated by specs/guild.ban.json
#endif

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
