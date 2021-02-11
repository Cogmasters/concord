#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace guild {

void
json_load(char *str, size_t len, void *p_guild)
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
     //"[channels]%F" // @todo add channel::json_load and channel::json_list_load
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
      &guild::json_list_load, &guild->members,
      //&channel::json_list_load, &guild->channels, // @todo add channel::json_load and channel::json_list_load
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

  D_NOTOP_PUTS("Guild object loaded with API response"); 
}

void
json_list_load(char *str, size_t len, void *p_guilds)
{
  struct sized_buffer **buf = NULL;
  json_scanf(str, len, "[]%A", &buf);

  size_t n = ntl_length((void**)buf);
  dati **new_guilds = (dati**)ntl_calloc(n, sizeof(dati*));
  for (size_t i=0; buf[i]; ++i) {
    new_guilds[i] = alloc_dati();
    json_load(buf[i]->start, buf[i]->size, new_guilds[i]);
  }
  
  free(buf);

  *(dati ***)p_guilds = new_guilds;
}

void
init_dati(dati *guild) {
  memset(guild, 0, sizeof(dati));
}

dati*
alloc_dati()
{
  dati *new_guild = (dati*)malloc(sizeof(dati));
  init_dati(new_guild);
  return new_guild;
}

void
free_dati(dati *guild) 
{
  //@todo cleanup_dati(guild);
  free(guild);
}

void
free_list(dati **guilds) {
  for(int i=0; guilds[i]; ++i) {
    free_dati(guilds[i]);
  }
  free(guilds);
}

void
get(client *client, const uint64_t guild_id, dati *p_guild)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle = {&json_load, (void*)p_guild};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/guilds/%llu", guild_id);
}

namespace member {

void
json_load(char *str, size_t len, void *p_member)
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
      &user::json_load, member->user,
      member->nick,
      &orka_iso8601_to_unix_ms, &member->joined_at,
      &orka_iso8601_to_unix_ms, &member->premium_since,
      &member->deaf,
      &member->mute,
      &member->pending);

  D_NOTOP_PUTS("Member object loaded with API response"); 
}

void
json_list_load(char *str, size_t len, void *p_members)
{
  struct sized_buffer **buf = NULL;
  json_scanf(str, len, "[]%A", &buf);

  size_t n = ntl_length((void**)buf);
  dati **new_members = (dati**)ntl_calloc(n, sizeof(dati*));
  for (size_t i=0; buf[i]; ++i) {
    new_members[i] = alloc_dati();
    json_load(buf[i]->start, buf[i]->size, new_members[i]);
  }
  
  free(buf);

  *(dati ***)p_members = new_members;
}

void
init_dati(dati *member)
{
  memset(member, 0, sizeof(dati));
  member->user = user::alloc_dati();
}

dati*
alloc_dati()
{
  dati *new_member = (dati*)malloc(sizeof(dati));
  init_dati(new_member);
  return new_member;
}

void
cleanup_dati(dati *member) {
  user::free_dati(member->user);
}

void
free_dati(dati *member) 
{
  cleanup_dati(member);
  free(member);
}

void
free_list(dati **members) {
  for (int i=0; members[i]; ++i) {
    free_dati(members[i]);
  }
  free(members);
}

//@todo modifiable query string parameters
dati**
get_list(client *client, const uint64_t guild_id)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return NULL;
  }

  dati **new_members = NULL;

  struct resp_handle resp_handle =
    {&json_list_load, (void*)&new_members};
  
  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%llu/members?limit=100", guild_id);

  return new_members;
}

void remove(client *client, const uint64_t guild_id, const uint64_t user_id)
{
  if (!guild_id) {
    D_PUTS("Can't delete message: missing 'guild_id'");
    return;
  }
  if (!user_id) {
    D_PUTS("Can't delete message: missing 'user_id'");
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
json_load(char *str, size_t len, void *p_ban)
{
  dati *ban = (dati*)p_ban;

  json_scanf(str, len,
     "[reason]%s"
     "[user]%F",
      ban->reason,
      &user::json_load, ban->user);

  D_NOTOP_PUTS("Ban object loaded with API response"); 
}

void
json_list_load(char *str, size_t len, void *p_bans)
{
  struct sized_buffer **buf = NULL;
  json_scanf(str, len, "[]%A", &buf);

  size_t n = ntl_length((void**)buf);
  dati **new_bans = (dati**)ntl_calloc(n, sizeof(dati*));
  for (size_t i=0; buf[i]; ++i) {
    new_bans[i] = alloc_dati();
    json_load(buf[i]->start, buf[i]->size, new_bans[i]);
  }

  free(buf);

  *(dati ***)p_bans = new_bans;
}

void
init_dati(dati *ban)
{
  memset(ban, 0, sizeof(dati));
  ban->user = user::alloc_dati();
}

dati*
alloc_dati()
{
  dati *new_ban = (dati*)malloc(sizeof(dati));
  init_dati(new_ban);
  return new_ban;
}

void
cleanup_dati(dati *ban) {
  user::free_dati(ban->user);
}

void
free_dati(dati *ban) 
{
  free_dati(ban);
  free(ban);
}

void
free_list(dati **bans) {
  for (int i=0; bans[i]; ++i) {
    free_dati(bans[i]);
  }
  free(bans);
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

  struct resp_handle resp_handle = {&json_load, (void*)p_ban};

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
    {&json_list_load, (void*)&new_bans};

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

  char buf[MAX_PAYLOAD_LEN];
  buf[0] = '\0';
  char *str = buf;
  str += sprintf(str, "{");

  if(delete_message_days > 0) {
    str += sprintf(str, "\"delete_message_days\":%d", delete_message_days);
  }

  if(!IS_EMPTY_STRING(reason)) {
    if(delete_message_days > 0) {
      str += sprintf(str, ",");
    }
    str += sprintf(str, "\"reason\":\"%s\"", reason);
  }

  str += sprintf(str, "}");

  struct sized_buffer req_body = {buf, (size_t)(str - buf)};

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

  char buf[MAX_PAYLOAD_LEN];
  buf[0] = '\0';
  char *str = buf;
  str += sprintf(str, "{");

  if(!IS_EMPTY_STRING(reason)) {
    str += sprintf(str, "\"reason\":\"%s\"", reason);
  }

  str += sprintf(str, "}");

  struct sized_buffer req_body = {buf, (size_t)(str - buf)};

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
