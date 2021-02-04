#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

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
     "[owner]%b"
     "[permissions]%d",
      &orka_strtoull, &guild->id,
      guild->name,
      guild->icon,
      &guild->owner,
      &guild->permissions);

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
    new_guilds[i] = init();
    json_load(buf[i]->start, buf[i]->size, new_guilds[i]);
  }
  
  free(buf);

  *(dati ***)p_guilds = new_guilds;
}

dati*
init()
{
  dati *new_guild = (dati*)calloc(1, sizeof(dati));
  return new_guild;
}

void
cleanup(dati *guild) {
  free(guild);
}

void
list_cleanup(dati **guilds) {
  for(int i=0; guilds[i]; ++i) {
    cleanup(guilds[i]);
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
    HTTP_GET, GUILD, guild_id);
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
    new_members[i] = init();
    json_load(buf[i]->start, buf[i]->size, new_members[i]);
  }
  
  free(buf);

  *(dati ***)p_members = new_members;
}

dati*
init()
{
  dati *new_member = (dati*)calloc(1, sizeof(dati));
  new_member->user = user::init();
  return new_member;
}

void
cleanup(dati *member) {
  user::cleanup(member->user);
  free(member);
}

void
list_cleanup(dati **members) {
  for (int i=0; members[i]; ++i) {
    cleanup(members[i]);
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
    HTTP_GET, GUILD MEMBERS "?limit=100", guild_id);

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
    HTTP_DELETE, GUILD MEMBER, guild_id, user_id);
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
    new_bans[i] = init();
    json_load(buf[i]->start, buf[i]->size, new_bans[i]);
  }

  free(buf);

  *(dati ***)p_bans = new_bans;
}

dati*
init()
{
  dati *new_ban = (dati*)calloc(1, sizeof(dati));
  new_ban->user = user::init();
  return new_ban;
}

void
cleanup(dati *ban) {
  user::cleanup(ban->user);
  free(ban);
}

void
list_cleanup(dati **bans) {
  for (int i=0; bans[i]; ++i) {
    cleanup(bans[i]);
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
    HTTP_GET, GUILD BAN, guild_id, user_id);
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
    HTTP_GET, GUILD BANS, guild_id);

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

  struct sized_buffer body = {buf, (size_t)(str - buf)};

  user_agent::run( 
    &client->ua,
    NULL,
    &body,
    HTTP_PUT, GUILD BAN, guild_id, user_id);
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

  struct sized_buffer body = {buf, (size_t)(str - buf)};

  user_agent::run( 
    &client->ua,
    NULL,
    &body,
    HTTP_DELETE, GUILD BAN, guild_id, user_id);
}

} // namespace ban

} // namespace guild
} // namespace discord
