/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
/**
 * @file specs-code/discord/permissions.c
 * @see https://discord.com/developers/docs/topics/permissions
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_bitwise_permission_flags_list_free_v(void **p) {
  discord_bitwise_permission_flags_list_free((enum discord_bitwise_permission_flags**)p);
}

void discord_bitwise_permission_flags_list_from_json_v(char *str, size_t len, void *p) {
  discord_bitwise_permission_flags_list_from_json(str, len, (enum discord_bitwise_permission_flags ***)p);
}

size_t discord_bitwise_permission_flags_list_to_json_v(char *str, size_t len, void *p){
  return discord_bitwise_permission_flags_list_to_json(str, len, (enum discord_bitwise_permission_flags **)p);
}

enum discord_bitwise_permission_flags discord_bitwise_permission_flags_eval(char *s){
  if(strcasecmp("ZERO", s) == 0) return DISCORD_BITWISE_PERMISSION_ZERO;
  if(strcasecmp("CREATE_INSTANT_INVITE", s) == 0) return DISCORD_BITWISE_PERMISSION_CREATE_INSTANT_INVITE;
  if(strcasecmp("KICK_MEMBERS", s) == 0) return DISCORD_BITWISE_PERMISSION_KICK_MEMBERS;
  if(strcasecmp("BAN_MEMBERS", s) == 0) return DISCORD_BITWISE_PERMISSION_BAN_MEMBERS;
  if(strcasecmp("ADMINISTRATOR", s) == 0) return DISCORD_BITWISE_PERMISSION_ADMINISTRATOR;
  if(strcasecmp("MANAGE_CHANNELS", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_CHANNELS;
  if(strcasecmp("MANAGE_GUILD", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_GUILD;
  if(strcasecmp("ADD_REACTIONS", s) == 0) return DISCORD_BITWISE_PERMISSION_ADD_REACTIONS;
  if(strcasecmp("VIEW_AUDIT_LOG", s) == 0) return DISCORD_BITWISE_PERMISSION_VIEW_AUDIT_LOG;
  if(strcasecmp("PRIORITY_SPEAKER", s) == 0) return DISCORD_BITWISE_PERMISSION_PRIORITY_SPEAKER;
  if(strcasecmp("STREAM", s) == 0) return DISCORD_BITWISE_PERMISSION_STREAM;
  if(strcasecmp("VIEW_CHANNEL", s) == 0) return DISCORD_BITWISE_PERMISSION_VIEW_CHANNEL;
  if(strcasecmp("SEND_MESSAGES", s) == 0) return DISCORD_BITWISE_PERMISSION_SEND_MESSAGES;
  if(strcasecmp("SEND_TTS_MESSAGES", s) == 0) return DISCORD_BITWISE_PERMISSION_SEND_TTS_MESSAGES;
  if(strcasecmp("MANAGE_MESSAGES", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_MESSAGES;
  if(strcasecmp("EMBED_LINKS", s) == 0) return DISCORD_BITWISE_PERMISSION_EMBED_LINKS;
  if(strcasecmp("ATTACH_FILES", s) == 0) return DISCORD_BITWISE_PERMISSION_ATTACH_FILES;
  if(strcasecmp("READ_MESSAGE_HISTORY", s) == 0) return DISCORD_BITWISE_PERMISSION_READ_MESSAGE_HISTORY;
  if(strcasecmp("MENTION_EVERYONE", s) == 0) return DISCORD_BITWISE_PERMISSION_MENTION_EVERYONE;
  if(strcasecmp("USE_EXTERNAL_EMOJIS", s) == 0) return DISCORD_BITWISE_PERMISSION_USE_EXTERNAL_EMOJIS;
  if(strcasecmp("VIEW_GUILD_INSIGHTS", s) == 0) return DISCORD_BITWISE_PERMISSION_VIEW_GUILD_INSIGHTS;
  if(strcasecmp("CONNECT", s) == 0) return DISCORD_BITWISE_PERMISSION_CONNECT;
  if(strcasecmp("SPEAK", s) == 0) return DISCORD_BITWISE_PERMISSION_SPEAK;
  if(strcasecmp("MUTE_MEMBERS", s) == 0) return DISCORD_BITWISE_PERMISSION_MUTE_MEMBERS;
  if(strcasecmp("DEAFEN_MEMBERS", s) == 0) return DISCORD_BITWISE_PERMISSION_DEAFEN_MEMBERS;
  if(strcasecmp("MOVE_MEMBERS", s) == 0) return DISCORD_BITWISE_PERMISSION_MOVE_MEMBERS;
  if(strcasecmp("USE_VAD", s) == 0) return DISCORD_BITWISE_PERMISSION_USE_VAD;
  if(strcasecmp("CHANGE_NICKNAME", s) == 0) return DISCORD_BITWISE_PERMISSION_CHANGE_NICKNAME;
  if(strcasecmp("MANAGE_NICKNAMES", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_NICKNAMES;
  if(strcasecmp("MANAGE_ROLES", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_ROLES;
  if(strcasecmp("MANAGE_WEBHOOKS", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_WEBHOOKS;
  if(strcasecmp("MANAGE_EMOJIS", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_EMOJIS;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_bitwise_permission_flags_print(enum discord_bitwise_permission_flags v){

  switch (v) {
  case DISCORD_BITWISE_PERMISSION_ZERO: return "ZERO";
  case DISCORD_BITWISE_PERMISSION_CREATE_INSTANT_INVITE: return "CREATE_INSTANT_INVITE";
  case DISCORD_BITWISE_PERMISSION_KICK_MEMBERS: return "KICK_MEMBERS";
  case DISCORD_BITWISE_PERMISSION_BAN_MEMBERS: return "BAN_MEMBERS";
  case DISCORD_BITWISE_PERMISSION_ADMINISTRATOR: return "ADMINISTRATOR";
  case DISCORD_BITWISE_PERMISSION_MANAGE_CHANNELS: return "MANAGE_CHANNELS";
  case DISCORD_BITWISE_PERMISSION_MANAGE_GUILD: return "MANAGE_GUILD";
  case DISCORD_BITWISE_PERMISSION_ADD_REACTIONS: return "ADD_REACTIONS";
  case DISCORD_BITWISE_PERMISSION_VIEW_AUDIT_LOG: return "VIEW_AUDIT_LOG";
  case DISCORD_BITWISE_PERMISSION_PRIORITY_SPEAKER: return "PRIORITY_SPEAKER";
  case DISCORD_BITWISE_PERMISSION_STREAM: return "STREAM";
  case DISCORD_BITWISE_PERMISSION_VIEW_CHANNEL: return "VIEW_CHANNEL";
  case DISCORD_BITWISE_PERMISSION_SEND_MESSAGES: return "SEND_MESSAGES";
  case DISCORD_BITWISE_PERMISSION_SEND_TTS_MESSAGES: return "SEND_TTS_MESSAGES";
  case DISCORD_BITWISE_PERMISSION_MANAGE_MESSAGES: return "MANAGE_MESSAGES";
  case DISCORD_BITWISE_PERMISSION_EMBED_LINKS: return "EMBED_LINKS";
  case DISCORD_BITWISE_PERMISSION_ATTACH_FILES: return "ATTACH_FILES";
  case DISCORD_BITWISE_PERMISSION_READ_MESSAGE_HISTORY: return "READ_MESSAGE_HISTORY";
  case DISCORD_BITWISE_PERMISSION_MENTION_EVERYONE: return "MENTION_EVERYONE";
  case DISCORD_BITWISE_PERMISSION_USE_EXTERNAL_EMOJIS: return "USE_EXTERNAL_EMOJIS";
  case DISCORD_BITWISE_PERMISSION_VIEW_GUILD_INSIGHTS: return "VIEW_GUILD_INSIGHTS";
  case DISCORD_BITWISE_PERMISSION_CONNECT: return "CONNECT";
  case DISCORD_BITWISE_PERMISSION_SPEAK: return "SPEAK";
  case DISCORD_BITWISE_PERMISSION_MUTE_MEMBERS: return "MUTE_MEMBERS";
  case DISCORD_BITWISE_PERMISSION_DEAFEN_MEMBERS: return "DEAFEN_MEMBERS";
  case DISCORD_BITWISE_PERMISSION_MOVE_MEMBERS: return "MOVE_MEMBERS";
  case DISCORD_BITWISE_PERMISSION_USE_VAD: return "USE_VAD";
  case DISCORD_BITWISE_PERMISSION_CHANGE_NICKNAME: return "CHANGE_NICKNAME";
  case DISCORD_BITWISE_PERMISSION_MANAGE_NICKNAMES: return "MANAGE_NICKNAMES";
  case DISCORD_BITWISE_PERMISSION_MANAGE_ROLES: return "MANAGE_ROLES";
  case DISCORD_BITWISE_PERMISSION_MANAGE_WEBHOOKS: return "MANAGE_WEBHOOKS";
  case DISCORD_BITWISE_PERMISSION_MANAGE_EMOJIS: return "MANAGE_EMOJIS";
  }

  return NULL;
}

void discord_bitwise_permission_flags_list_free(enum discord_bitwise_permission_flags **p) {
  ntl_free((void**)p, NULL);
}

void discord_bitwise_permission_flags_list_from_json(char *str, size_t len, enum discord_bitwise_permission_flags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_bitwise_permission_flags);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_bitwise_permission_flags_list_to_json(char *str, size_t len, enum discord_bitwise_permission_flags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_role_from_json(char *json, size_t len, struct discord_role **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_role *p = *pp;
  discord_role_init(p);
  r=json_extract(json, len, 
  /* specs/discord/permissions.json:53:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/permissions.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* specs/discord/permissions.json:55:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                "(color):d,"
  /* specs/discord/permissions.json:56:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                "(hoist):b,"
  /* specs/discord/permissions.json:57:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                "(position):d,"
  /* specs/discord/permissions.json:58:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                "(permissions):?s,"
  /* specs/discord/permissions.json:59:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                "(managed):b,"
  /* specs/discord/permissions.json:60:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                "(mentionable):b,"
  /* specs/discord/permissions.json:61:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                "(tags):F,",
  /* specs/discord/permissions.json:53:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/permissions.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* specs/discord/permissions.json:55:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                &p->color,
  /* specs/discord/permissions.json:56:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                &p->hoist,
  /* specs/discord/permissions.json:57:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                &p->position,
  /* specs/discord/permissions.json:58:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                &p->permissions,
  /* specs/discord/permissions.json:59:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                &p->managed,
  /* specs/discord/permissions.json:60:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                &p->mentionable,
  /* specs/discord/permissions.json:61:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                discord_role_tags_from_json, &p->tags);
  ret = r;
}

size_t discord_role_to_json(char *json, size_t len, struct discord_role *p)
{
  size_t r;
  void *arg_switches[9]={NULL};
  /* specs/discord/permissions.json:53:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->id;

  /* specs/discord/permissions.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[1] = p->name;

  /* specs/discord/permissions.json:55:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  arg_switches[2] = &p->color;

  /* specs/discord/permissions.json:56:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  arg_switches[3] = &p->hoist;

  /* specs/discord/permissions.json:57:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  arg_switches[4] = &p->position;

  /* specs/discord/permissions.json:58:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[5] = p->permissions;

  /* specs/discord/permissions.json:59:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->managed;

  /* specs/discord/permissions.json:60:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  arg_switches[7] = &p->mentionable;

  /* specs/discord/permissions.json:61:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
  arg_switches[8] = p->tags;

  r=json_inject(json, len, 
  /* specs/discord/permissions.json:53:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/permissions.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* specs/discord/permissions.json:55:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                "(color):d,"
  /* specs/discord/permissions.json:56:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                "(hoist):b,"
  /* specs/discord/permissions.json:57:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                "(position):d,"
  /* specs/discord/permissions.json:58:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                "(permissions):s,"
  /* specs/discord/permissions.json:59:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                "(managed):b,"
  /* specs/discord/permissions.json:60:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                "(mentionable):b,"
  /* specs/discord/permissions.json:61:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                "(tags):F,"
                "@arg_switches:b",
  /* specs/discord/permissions.json:53:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/permissions.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* specs/discord/permissions.json:55:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                &p->color,
  /* specs/discord/permissions.json:56:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                &p->hoist,
  /* specs/discord/permissions.json:57:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                &p->position,
  /* specs/discord/permissions.json:58:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                p->permissions,
  /* specs/discord/permissions.json:59:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                &p->managed,
  /* specs/discord/permissions.json:60:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                &p->mentionable,
  /* specs/discord/permissions.json:61:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                discord_role_tags_to_json, p->tags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_role_cleanup_v(void *p) {
  discord_role_cleanup((struct discord_role *)p);
}

void discord_role_init_v(void *p) {
  discord_role_init((struct discord_role *)p);
}

void discord_role_from_json_v(char *json, size_t len, void *pp) {
 discord_role_from_json(json, len, (struct discord_role**)pp);
}

size_t discord_role_to_json_v(char *json, size_t len, void *p) {
  return discord_role_to_json(json, len, (struct discord_role*)p);
}

void discord_role_list_free_v(void **p) {
  discord_role_list_free((struct discord_role**)p);
}

void discord_role_list_from_json_v(char *str, size_t len, void *p) {
  discord_role_list_from_json(str, len, (struct discord_role ***)p);
}

size_t discord_role_list_to_json_v(char *str, size_t len, void *p){
  return discord_role_list_to_json(str, len, (struct discord_role **)p);
}


void discord_role_cleanup(struct discord_role *d) {
  /* specs/discord/permissions.json:53:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  /* p->id is a scalar */
  /* specs/discord/permissions.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* specs/discord/permissions.json:55:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  /* p->color is a scalar */
  /* specs/discord/permissions.json:56:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  /* p->hoist is a scalar */
  /* specs/discord/permissions.json:57:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  /* p->position is a scalar */
  /* specs/discord/permissions.json:58:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  if (d->permissions)
    free(d->permissions);
  /* specs/discord/permissions.json:59:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  /* p->managed is a scalar */
  /* specs/discord/permissions.json:60:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  /* p->mentionable is a scalar */
  /* specs/discord/permissions.json:61:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
  if (d->tags) {
    discord_role_tags_cleanup(d->tags);
    free(d->tags);
  }
}

void discord_role_init(struct discord_role *p) {
  memset(p, 0, sizeof(struct discord_role));
  /* specs/discord/permissions.json:53:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/permissions.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/permissions.json:55:20
     '{ "name": "color", "type":{ "base":"int" }}' */

  /* specs/discord/permissions.json:56:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */

  /* specs/discord/permissions.json:57:20
     '{ "name": "position", "type":{ "base":"int" }}' */

  /* specs/discord/permissions.json:58:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/permissions.json:59:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */

  /* specs/discord/permissions.json:60:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */

  /* specs/discord/permissions.json:61:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */

}
void discord_role_list_free(struct discord_role **p) {
  ntl_free((void**)p, (vfvp)discord_role_cleanup);
}

void discord_role_list_from_json(char *str, size_t len, struct discord_role ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_role);
  d.init_elem = NULL;
  d.elem_from_buf = discord_role_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_role_list_to_json(char *str, size_t len, struct discord_role **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_role_to_json_v);
}


void discord_role_tags_from_json(char *json, size_t len, struct discord_role_tags **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_role_tags *p = *pp;
  discord_role_tags_init(p);
  r=json_extract(json, len, 
  /* specs/discord/permissions.json:71:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(bot_id):F,"
  /* specs/discord/permissions.json:72:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(integration_id):F,"
  /* specs/discord/permissions.json:73:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                "(premium_subscriber):d,",
  /* specs/discord/permissions.json:71:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->bot_id,
  /* specs/discord/permissions.json:72:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->integration_id,
  /* specs/discord/permissions.json:73:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                &p->premium_subscriber);
  ret = r;
}

size_t discord_role_tags_to_json(char *json, size_t len, struct discord_role_tags *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* specs/discord/permissions.json:71:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->bot_id;

  /* specs/discord/permissions.json:72:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[1] = &p->integration_id;

  /* specs/discord/permissions.json:73:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  arg_switches[2] = &p->premium_subscriber;

  r=json_inject(json, len, 
  /* specs/discord/permissions.json:71:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(bot_id):|F|,"
  /* specs/discord/permissions.json:72:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(integration_id):|F|,"
  /* specs/discord/permissions.json:73:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                "(premium_subscriber):d,"
                "@arg_switches:b",
  /* specs/discord/permissions.json:71:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->bot_id,
  /* specs/discord/permissions.json:72:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->integration_id,
  /* specs/discord/permissions.json:73:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                &p->premium_subscriber,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_role_tags_cleanup_v(void *p) {
  discord_role_tags_cleanup((struct discord_role_tags *)p);
}

void discord_role_tags_init_v(void *p) {
  discord_role_tags_init((struct discord_role_tags *)p);
}

void discord_role_tags_from_json_v(char *json, size_t len, void *pp) {
 discord_role_tags_from_json(json, len, (struct discord_role_tags**)pp);
}

size_t discord_role_tags_to_json_v(char *json, size_t len, void *p) {
  return discord_role_tags_to_json(json, len, (struct discord_role_tags*)p);
}

void discord_role_tags_list_free_v(void **p) {
  discord_role_tags_list_free((struct discord_role_tags**)p);
}

void discord_role_tags_list_from_json_v(char *str, size_t len, void *p) {
  discord_role_tags_list_from_json(str, len, (struct discord_role_tags ***)p);
}

size_t discord_role_tags_list_to_json_v(char *str, size_t len, void *p){
  return discord_role_tags_list_to_json(str, len, (struct discord_role_tags **)p);
}


void discord_role_tags_cleanup(struct discord_role_tags *d) {
  /* specs/discord/permissions.json:71:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  /* p->bot_id is a scalar */
  /* specs/discord/permissions.json:72:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  /* p->integration_id is a scalar */
  /* specs/discord/permissions.json:73:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  /* p->premium_subscriber is a scalar */
}

void discord_role_tags_init(struct discord_role_tags *p) {
  memset(p, 0, sizeof(struct discord_role_tags));
  /* specs/discord/permissions.json:71:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/permissions.json:72:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/permissions.json:73:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */

}
void discord_role_tags_list_free(struct discord_role_tags **p) {
  ntl_free((void**)p, (vfvp)discord_role_tags_cleanup);
}

void discord_role_tags_list_from_json(char *str, size_t len, struct discord_role_tags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_role_tags);
  d.init_elem = NULL;
  d.elem_from_buf = discord_role_tags_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_role_tags_list_to_json(char *str, size_t len, struct discord_role_tags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_role_tags_to_json_v);
}

