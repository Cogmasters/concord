/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
/**
 * @file specs-code/discord/permissions.c
 * @author cee-studio
 * @date 01 Jul 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/permissions
 */

#include "specs.h"


enum discord_permissions_bitwise_flags discord_permissions_bitwise_flags_from_string(char *s){
  if(strcasecmp("ZERO", s) == 0) return DISCORD_PERMISSIONS_ZERO;
  if(strcasecmp("CREATE_INSTANT_INVITE", s) == 0) return DISCORD_PERMISSIONS_CREATE_INSTANT_INVITE;
  if(strcasecmp("KICK_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_KICK_MEMBERS;
  if(strcasecmp("BAN_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_BAN_MEMBERS;
  if(strcasecmp("ADMINISTRATOR", s) == 0) return DISCORD_PERMISSIONS_ADMINISTRATOR;
  if(strcasecmp("MANAGE_CHANNELS", s) == 0) return DISCORD_PERMISSIONS_MANAGE_CHANNELS;
  if(strcasecmp("MANAGE_GUILD", s) == 0) return DISCORD_PERMISSIONS_MANAGE_GUILD;
  if(strcasecmp("ADD_REACTIONS", s) == 0) return DISCORD_PERMISSIONS_ADD_REACTIONS;
  if(strcasecmp("VIEW_AUDIT_LOG", s) == 0) return DISCORD_PERMISSIONS_VIEW_AUDIT_LOG;
  if(strcasecmp("PRIORITY_SPEAKER", s) == 0) return DISCORD_PERMISSIONS_PRIORITY_SPEAKER;
  if(strcasecmp("STREAM", s) == 0) return DISCORD_PERMISSIONS_STREAM;
  if(strcasecmp("VIEW_CHANNEL", s) == 0) return DISCORD_PERMISSIONS_VIEW_CHANNEL;
  if(strcasecmp("SEND_MESSAGES", s) == 0) return DISCORD_PERMISSIONS_SEND_MESSAGES;
  if(strcasecmp("SEND_TTS_MESSAGES", s) == 0) return DISCORD_PERMISSIONS_SEND_TTS_MESSAGES;
  if(strcasecmp("MANAGE_MESSAGES", s) == 0) return DISCORD_PERMISSIONS_MANAGE_MESSAGES;
  if(strcasecmp("EMBED_LINKS", s) == 0) return DISCORD_PERMISSIONS_EMBED_LINKS;
  if(strcasecmp("ATTACH_FILES", s) == 0) return DISCORD_PERMISSIONS_ATTACH_FILES;
  if(strcasecmp("READ_MESSAGE_HISTORY", s) == 0) return DISCORD_PERMISSIONS_READ_MESSAGE_HISTORY;
  if(strcasecmp("MENTION_EVERYONE", s) == 0) return DISCORD_PERMISSIONS_MENTION_EVERYONE;
  if(strcasecmp("USE_EXTERNAL_EMOJIS", s) == 0) return DISCORD_PERMISSIONS_USE_EXTERNAL_EMOJIS;
  if(strcasecmp("VIEW_GUILD_INSIGHTS", s) == 0) return DISCORD_PERMISSIONS_VIEW_GUILD_INSIGHTS;
  if(strcasecmp("CONNECT", s) == 0) return DISCORD_PERMISSIONS_CONNECT;
  if(strcasecmp("SPEAK", s) == 0) return DISCORD_PERMISSIONS_SPEAK;
  if(strcasecmp("MUTE_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_MUTE_MEMBERS;
  if(strcasecmp("DEAFEN_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_DEAFEN_MEMBERS;
  if(strcasecmp("MOVE_MEMBERS", s) == 0) return DISCORD_PERMISSIONS_MOVE_MEMBERS;
  if(strcasecmp("USE_VAD", s) == 0) return DISCORD_PERMISSIONS_USE_VAD;
  if(strcasecmp("CHANGE_NICKNAME", s) == 0) return DISCORD_PERMISSIONS_CHANGE_NICKNAME;
  if(strcasecmp("MANAGE_NICKNAMES", s) == 0) return DISCORD_PERMISSIONS_MANAGE_NICKNAMES;
  if(strcasecmp("MANAGE_ROLES", s) == 0) return DISCORD_PERMISSIONS_MANAGE_ROLES;
  if(strcasecmp("MANAGE_WEBHOOKS", s) == 0) return DISCORD_PERMISSIONS_MANAGE_WEBHOOKS;
  if(strcasecmp("MANAGE_EMOJIS", s) == 0) return DISCORD_PERMISSIONS_MANAGE_EMOJIS;
  abort();
}
char* discord_permissions_bitwise_flags_to_string(enum discord_permissions_bitwise_flags v){
  if (v == DISCORD_PERMISSIONS_ZERO) return "ZERO";
  if (v == DISCORD_PERMISSIONS_CREATE_INSTANT_INVITE) return "CREATE_INSTANT_INVITE";
  if (v == DISCORD_PERMISSIONS_KICK_MEMBERS) return "KICK_MEMBERS";
  if (v == DISCORD_PERMISSIONS_BAN_MEMBERS) return "BAN_MEMBERS";
  if (v == DISCORD_PERMISSIONS_ADMINISTRATOR) return "ADMINISTRATOR";
  if (v == DISCORD_PERMISSIONS_MANAGE_CHANNELS) return "MANAGE_CHANNELS";
  if (v == DISCORD_PERMISSIONS_MANAGE_GUILD) return "MANAGE_GUILD";
  if (v == DISCORD_PERMISSIONS_ADD_REACTIONS) return "ADD_REACTIONS";
  if (v == DISCORD_PERMISSIONS_VIEW_AUDIT_LOG) return "VIEW_AUDIT_LOG";
  if (v == DISCORD_PERMISSIONS_PRIORITY_SPEAKER) return "PRIORITY_SPEAKER";
  if (v == DISCORD_PERMISSIONS_STREAM) return "STREAM";
  if (v == DISCORD_PERMISSIONS_VIEW_CHANNEL) return "VIEW_CHANNEL";
  if (v == DISCORD_PERMISSIONS_SEND_MESSAGES) return "SEND_MESSAGES";
  if (v == DISCORD_PERMISSIONS_SEND_TTS_MESSAGES) return "SEND_TTS_MESSAGES";
  if (v == DISCORD_PERMISSIONS_MANAGE_MESSAGES) return "MANAGE_MESSAGES";
  if (v == DISCORD_PERMISSIONS_EMBED_LINKS) return "EMBED_LINKS";
  if (v == DISCORD_PERMISSIONS_ATTACH_FILES) return "ATTACH_FILES";
  if (v == DISCORD_PERMISSIONS_READ_MESSAGE_HISTORY) return "READ_MESSAGE_HISTORY";
  if (v == DISCORD_PERMISSIONS_MENTION_EVERYONE) return "MENTION_EVERYONE";
  if (v == DISCORD_PERMISSIONS_USE_EXTERNAL_EMOJIS) return "USE_EXTERNAL_EMOJIS";
  if (v == DISCORD_PERMISSIONS_VIEW_GUILD_INSIGHTS) return "VIEW_GUILD_INSIGHTS";
  if (v == DISCORD_PERMISSIONS_CONNECT) return "CONNECT";
  if (v == DISCORD_PERMISSIONS_SPEAK) return "SPEAK";
  if (v == DISCORD_PERMISSIONS_MUTE_MEMBERS) return "MUTE_MEMBERS";
  if (v == DISCORD_PERMISSIONS_DEAFEN_MEMBERS) return "DEAFEN_MEMBERS";
  if (v == DISCORD_PERMISSIONS_MOVE_MEMBERS) return "MOVE_MEMBERS";
  if (v == DISCORD_PERMISSIONS_USE_VAD) return "USE_VAD";
  if (v == DISCORD_PERMISSIONS_CHANGE_NICKNAME) return "CHANGE_NICKNAME";
  if (v == DISCORD_PERMISSIONS_MANAGE_NICKNAMES) return "MANAGE_NICKNAMES";
  if (v == DISCORD_PERMISSIONS_MANAGE_ROLES) return "MANAGE_ROLES";
  if (v == DISCORD_PERMISSIONS_MANAGE_WEBHOOKS) return "MANAGE_WEBHOOKS";
  if (v == DISCORD_PERMISSIONS_MANAGE_EMOJIS) return "MANAGE_EMOJIS";

  return (void*)0;
}
bool discord_permissions_bitwise_flags_has(enum discord_permissions_bitwise_flags v, char *s) {
  enum discord_permissions_bitwise_flags v1 = discord_permissions_bitwise_flags_from_string(s);
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  if (v & v1) return true;
  return false;
}

void discord_permissions_role_from_json(char *json, size_t len, struct discord_permissions_role *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */
                "(name):s,"
  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                "(color):d,"
  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                "(hoist):b,"
  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                "(position):d,"
  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                "(permissions):?s,"
  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                "(managed):b,"
  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                "(mentionable):b,"
  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
                "(tags):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */
                p->name,
  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                &p->color,
  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                &p->hoist,
  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                &p->position,
  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                &p->permissions,
  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                &p->managed,
  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                &p->mentionable,
  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
                discord_permissions_role_tags_from_json, p->tags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_permissions_role_use_default_inject_settings(struct discord_permissions_role *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  p->__M.arg_switches[2] = &p->color;

  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[3] = &p->hoist;

  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  p->__M.arg_switches[4] = &p->position;

  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[5] = p->permissions;

  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[6] = &p->managed;

  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[7] = &p->mentionable;

  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
  p->__M.arg_switches[8] = p->tags;

}

size_t discord_permissions_role_to_json(char *json, size_t len, struct discord_permissions_role *p)
{
  size_t r;
  discord_permissions_role_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */
                "(name):s,"
  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                "(color):d,"
  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                "(hoist):b,"
  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                "(position):d,"
  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                "(permissions):s,"
  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                "(managed):b,"
  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                "(mentionable):b,"
  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
                "(tags):F,"
                "@arg_switches:b",
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */
                p->name,
  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                &p->color,
  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                &p->hoist,
  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                &p->position,
  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                p->permissions,
  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                &p->managed,
  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                &p->mentionable,
  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
                discord_permissions_role_tags_to_json, p->tags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_permissions_role_cleanup_v(void *p) {
  discord_permissions_role_cleanup((struct discord_permissions_role *)p);
}

void discord_permissions_role_init_v(void *p) {
  discord_permissions_role_init((struct discord_permissions_role *)p);
}

void discord_permissions_role_free_v(void *p) {
 discord_permissions_role_free((struct discord_permissions_role *)p);
};

void discord_permissions_role_from_json_v(char *json, size_t len, void *p) {
 discord_permissions_role_from_json(json, len, (struct discord_permissions_role*)p);
}

size_t discord_permissions_role_to_json_v(char *json, size_t len, void *p) {
  return discord_permissions_role_to_json(json, len, (struct discord_permissions_role*)p);
}

void discord_permissions_role_list_free_v(void **p) {
  discord_permissions_role_list_free((struct discord_permissions_role**)p);
}

void discord_permissions_role_list_from_json_v(char *str, size_t len, void *p) {
  discord_permissions_role_list_from_json(str, len, (struct discord_permissions_role ***)p);
}

size_t discord_permissions_role_list_to_json_v(char *str, size_t len, void *p){
  return discord_permissions_role_list_to_json(str, len, (struct discord_permissions_role **)p);
}


void discord_permissions_role_cleanup(struct discord_permissions_role *d) {
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */
  // p->name is a scalar
  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  // p->color is a scalar
  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  // p->hoist is a scalar
  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  // p->position is a scalar
  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  if (d->permissions)
    free(d->permissions);
  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  // p->managed is a scalar
  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  // p->mentionable is a scalar
  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
  if (d->tags)
    discord_permissions_role_tags_free(d->tags);
}

void discord_permissions_role_init(struct discord_permissions_role *p) {
  memset(p, 0, sizeof(struct discord_permissions_role));
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */

  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */

  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */

  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */

  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */

  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */

  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
  p->tags = discord_permissions_role_tags_alloc();

}
struct discord_permissions_role* discord_permissions_role_alloc() {
  struct discord_permissions_role *p= malloc(sizeof(struct discord_permissions_role));
  discord_permissions_role_init(p);
  return p;
}

void discord_permissions_role_free(struct discord_permissions_role *p) {
  discord_permissions_role_cleanup(p);
  free(p);
}

void discord_permissions_role_list_free(struct discord_permissions_role **p) {
  ntl_free((void**)p, (vfvp)discord_permissions_role_cleanup);
}

void discord_permissions_role_list_from_json(char *str, size_t len, struct discord_permissions_role ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_permissions_role);
  d.init_elem = discord_permissions_role_init_v;
  d.elem_from_buf = discord_permissions_role_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_permissions_role_list_to_json(char *str, size_t len, struct discord_permissions_role **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_permissions_role_to_json_v);
}


void discord_permissions_role_tags_from_json(char *json, size_t len, struct discord_permissions_role_tags *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(bot_id):F,"
  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(integration_id):F,"
  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                "(premium_subscriber):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->bot_id,
  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->integration_id,
  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                &p->premium_subscriber,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_permissions_role_tags_use_default_inject_settings(struct discord_permissions_role_tags *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->bot_id;

  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[1] = &p->integration_id;

  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  p->__M.arg_switches[2] = &p->premium_subscriber;

}

size_t discord_permissions_role_tags_to_json(char *json, size_t len, struct discord_permissions_role_tags *p)
{
  size_t r;
  discord_permissions_role_tags_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(bot_id):|F|,"
  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(integration_id):|F|,"
  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                "(premium_subscriber):d,"
                "@arg_switches:b",
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->bot_id,
  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->integration_id,
  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                &p->premium_subscriber,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_permissions_role_tags_cleanup_v(void *p) {
  discord_permissions_role_tags_cleanup((struct discord_permissions_role_tags *)p);
}

void discord_permissions_role_tags_init_v(void *p) {
  discord_permissions_role_tags_init((struct discord_permissions_role_tags *)p);
}

void discord_permissions_role_tags_free_v(void *p) {
 discord_permissions_role_tags_free((struct discord_permissions_role_tags *)p);
};

void discord_permissions_role_tags_from_json_v(char *json, size_t len, void *p) {
 discord_permissions_role_tags_from_json(json, len, (struct discord_permissions_role_tags*)p);
}

size_t discord_permissions_role_tags_to_json_v(char *json, size_t len, void *p) {
  return discord_permissions_role_tags_to_json(json, len, (struct discord_permissions_role_tags*)p);
}

void discord_permissions_role_tags_list_free_v(void **p) {
  discord_permissions_role_tags_list_free((struct discord_permissions_role_tags**)p);
}

void discord_permissions_role_tags_list_from_json_v(char *str, size_t len, void *p) {
  discord_permissions_role_tags_list_from_json(str, len, (struct discord_permissions_role_tags ***)p);
}

size_t discord_permissions_role_tags_list_to_json_v(char *str, size_t len, void *p){
  return discord_permissions_role_tags_list_to_json(str, len, (struct discord_permissions_role_tags **)p);
}


void discord_permissions_role_tags_cleanup(struct discord_permissions_role_tags *d) {
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->bot_id is a scalar
  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->integration_id is a scalar
  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  // p->premium_subscriber is a scalar
}

void discord_permissions_role_tags_init(struct discord_permissions_role_tags *p) {
  memset(p, 0, sizeof(struct discord_permissions_role_tags));
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */

}
struct discord_permissions_role_tags* discord_permissions_role_tags_alloc() {
  struct discord_permissions_role_tags *p= malloc(sizeof(struct discord_permissions_role_tags));
  discord_permissions_role_tags_init(p);
  return p;
}

void discord_permissions_role_tags_free(struct discord_permissions_role_tags *p) {
  discord_permissions_role_tags_cleanup(p);
  free(p);
}

void discord_permissions_role_tags_list_free(struct discord_permissions_role_tags **p) {
  ntl_free((void**)p, (vfvp)discord_permissions_role_tags_cleanup);
}

void discord_permissions_role_tags_list_from_json(char *str, size_t len, struct discord_permissions_role_tags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_permissions_role_tags);
  d.init_elem = discord_permissions_role_tags_init_v;
  d.elem_from_buf = discord_permissions_role_tags_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_permissions_role_tags_list_to_json(char *str, size_t len, struct discord_permissions_role_tags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_permissions_role_tags_to_json_v);
}

