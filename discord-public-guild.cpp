#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace guild {

void
from_json(char *str, size_t len, void *p_guild)
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
      &guild::list_from_json, &guild->members,
      &channel::list_from_json, &guild->channels,
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
list_from_json(char *str, size_t len, void *p_guilds)
{
  struct ntl_deserializer d;
  d.elem_size = sizeof(dati);
  d.init_elem = &init_dati;
  d.elem_from_buf = &from_json;
  d.ntl_recipient_p = (void***)p_guilds;
  orka_str_to_ntl(str, len, &d);
}

void
init_dati(void *p_guild) 
{
  dati *guild = (dati*)p_guild;
  memset(guild, 0, sizeof(dati));
}

dati*
alloc_dati()
{
  dati *new_guild = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_guild);
  return new_guild;
}

void
cleanup_dati(void *p_guild) 
{
  dati *guild = (dati*)p_guild;
  if (guild->members)
    member::free_list(guild->members);
  if (guild->channels)
    channel::free_list(guild->channels);

  DS_NOTOP_PUTS("Guild object fields cleared"); 
}

void
free_dati(dati *guild) 
{
  cleanup_dati((void*)guild);
  free(guild);
}

void
free_list(dati **guilds) {
  ntl_free((void**)guilds, &cleanup_dati);
}

void
get(client *client, const uint64_t guild_id, dati *p_guild)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle = {&from_json, (void*)p_guild};

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
    {&channel::list_from_json, (void*)&new_channels};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/guilds/%llu/channels", guild_id);

  return new_channels;
}

namespace member {

void
from_json(char *str, size_t len, void *p_member)
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
      &user::from_json, member->user,
      member->nick,
      &orka_iso8601_to_unix_ms, &member->joined_at,
      &orka_iso8601_to_unix_ms, &member->premium_since,
      &member->deaf,
      &member->mute,
      &member->pending);

  DS_NOTOP_PUTS("Member object loaded with API response"); 
}

void
list_from_json(char *str, size_t len, void *p_members)
{
  struct ntl_deserializer d; 
  d.elem_size = sizeof(dati);
  d.init_elem = &init_dati;
  d.elem_from_buf = &from_json;
  d.ntl_recipient_p = (void***)p_members;
  orka_str_to_ntl(str, len, &d);
}

void
init_dati(void *p_member)
{
  dati *member = (dati*)p_member;
  memset(member, 0, sizeof(dati));
  member->user = user::alloc_dati();
}

dati*
alloc_dati()
{
  dati *new_member = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_member);
  return new_member;
}

void
cleanup_dati(void *p_member) 
{
  dati *member = (dati*)p_member;
  user::free_dati(member->user);

  DS_NOTOP_PUTS("Member object fields cleared"); 
}

void
free_dati(dati *member) 
{
  cleanup_dati((void*)member);
  free(member);
}

void
free_list(dati **members) {
  ntl_free((void**)members, &cleanup_dati);
}

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
    {&list_from_json, (void*)&new_members};
  
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
from_json(char *str, size_t len, void *p_ban)
{
  dati *ban = (dati*)p_ban;

  json_scanf(str, len,
     "[reason]%s"
     "[user]%F",
      ban->reason,
      &user::from_json, ban->user);

  DS_NOTOP_PUTS("Ban object loaded with API response"); 
}

void
list_from_json(char *str, size_t len, void *p_bans)
{
  struct ntl_deserializer d;
  d.elem_size = sizeof(dati);
  d.init_elem = &init_dati;
  d.elem_from_buf = &from_json;
  d.ntl_recipient_p = (void***)p_bans;
  orka_str_to_ntl(str, len, &d);
}

void
init_dati(void *p_ban)
{
  dati *ban = (dati*)p_ban;
  memset(ban, 0, sizeof(dati));
  ban->user = user::alloc_dati();
}

dati*
alloc_dati()
{
  dati *new_ban = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_ban);
  return new_ban;
}

void
cleanup_dati(void *p_ban)
{
  dati *ban = (dati*)p_ban;
  user::free_dati(ban->user);

  DS_NOTOP_PUTS("Ban object fields cleared"); 
}

void
free_dati(dati *ban) 
{
  free_dati(ban);
  free(ban);
}

void
free_list(dati **bans) {
  ntl_free((void**)bans, &cleanup_dati);
}

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

  struct resp_handle resp_handle = {&from_json, (void*)p_ban};

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
    {&list_from_json, (void*)&new_bans};

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
                        "@",
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
                        "@",
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
