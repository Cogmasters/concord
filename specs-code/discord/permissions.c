/* This file is generated from discord/permissions.json, Please don't edit it. */
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
  if(strcasecmp("MANAGE_EMOJIS_AND_STICKERS", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_EMOJIS_AND_STICKERS;
  if(strcasecmp("USE_APPLICATION_COMMANDS", s) == 0) return DISCORD_BITWISE_PERMISSION_USE_APPLICATION_COMMANDS;
  if(strcasecmp("REQUEST_TO_SPEAK", s) == 0) return DISCORD_BITWISE_PERMISSION_REQUEST_TO_SPEAK;
  if(strcasecmp("MANAGE_EVENTS", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_EVENTS;
  if(strcasecmp("MANAGE_THREADS", s) == 0) return DISCORD_BITWISE_PERMISSION_MANAGE_THREADS;
  if(strcasecmp("CREATE_PUBLIC_THREADS", s) == 0) return DISCORD_BITWISE_PERMISSION_CREATE_PUBLIC_THREADS;
  if(strcasecmp("CREATE_PRIVATE_THREADS", s) == 0) return DISCORD_BITWISE_PERMISSION_CREATE_PRIVATE_THREADS;
  if(strcasecmp("USE_EXTERNAL_STICKERS", s) == 0) return DISCORD_BITWISE_PERMISSION_USE_EXTERNAL_STICKERS;
  if(strcasecmp("SEND_MESSAGES_IN_THREADS", s) == 0) return DISCORD_BITWISE_PERMISSION_SEND_MESSAGES_IN_THREADS;
  if(strcasecmp("START_EMBEDDED_ACTIVITIES", s) == 0) return DISCORD_BITWISE_PERMISSION_START_EMBEDDED_ACTIVITIES;
  if(strcasecmp("MODERATE_MEMBERS", s) == 0) return DISCORD_BITWISE_PERMISSION_MODERATE_MEMBERS;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
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
  case DISCORD_BITWISE_PERMISSION_MANAGE_EMOJIS_AND_STICKERS: return "MANAGE_EMOJIS_AND_STICKERS";
  case DISCORD_BITWISE_PERMISSION_USE_APPLICATION_COMMANDS: return "USE_APPLICATION_COMMANDS";
  case DISCORD_BITWISE_PERMISSION_REQUEST_TO_SPEAK: return "REQUEST_TO_SPEAK";
  case DISCORD_BITWISE_PERMISSION_MANAGE_EVENTS: return "MANAGE_EVENTS";
  case DISCORD_BITWISE_PERMISSION_MANAGE_THREADS: return "MANAGE_THREADS";
  case DISCORD_BITWISE_PERMISSION_CREATE_PUBLIC_THREADS: return "CREATE_PUBLIC_THREADS";
  case DISCORD_BITWISE_PERMISSION_CREATE_PRIVATE_THREADS: return "CREATE_PRIVATE_THREADS";
  case DISCORD_BITWISE_PERMISSION_USE_EXTERNAL_STICKERS: return "USE_EXTERNAL_STICKERS";
  case DISCORD_BITWISE_PERMISSION_SEND_MESSAGES_IN_THREADS: return "SEND_MESSAGES_IN_THREADS";
  case DISCORD_BITWISE_PERMISSION_START_EMBEDDED_ACTIVITIES: return "START_EMBEDDED_ACTIVITIES";
  case DISCORD_BITWISE_PERMISSION_MODERATE_MEMBERS: return "MODERATE_MEMBERS";
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


void discord_role_from_json_p(char *json, size_t len, struct discord_role **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_role_from_json(json, len, *pp);
}
void discord_role_from_json(char *json, size_t len, struct discord_role *p)
{
  discord_role_init(p);
  json_extract(json, len, 
  /* discord/permissions.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* discord/permissions.json:64:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* discord/permissions.json:65:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                "(color):d,"
  /* discord/permissions.json:66:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                "(hoist):b,"
  /* discord/permissions.json:67:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                "(position):d,"
  /* discord/permissions.json:68:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                "(permissions):?s,"
  /* discord/permissions.json:69:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                "(managed):b,"
  /* discord/permissions.json:70:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                "(mentionable):b,"
  /* discord/permissions.json:71:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                "(tags):F,",
  /* discord/permissions.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->id,
  /* discord/permissions.json:64:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* discord/permissions.json:65:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                &p->color,
  /* discord/permissions.json:66:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                &p->hoist,
  /* discord/permissions.json:67:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                &p->position,
  /* discord/permissions.json:68:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                &p->permissions,
  /* discord/permissions.json:69:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                &p->managed,
  /* discord/permissions.json:70:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                &p->mentionable,
  /* discord/permissions.json:71:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                discord_role_tags_from_json_p, &p->tags);
}

size_t discord_role_to_json(char *json, size_t len, struct discord_role *p)
{
  size_t r;
  void *arg_switches[9]={NULL};
  /* discord/permissions.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->id;

  /* discord/permissions.json:64:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[1] = p->name;

  /* discord/permissions.json:65:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  arg_switches[2] = &p->color;

  /* discord/permissions.json:66:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  arg_switches[3] = &p->hoist;

  /* discord/permissions.json:67:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  arg_switches[4] = &p->position;

  /* discord/permissions.json:68:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[5] = p->permissions;

  /* discord/permissions.json:69:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->managed;

  /* discord/permissions.json:70:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  arg_switches[7] = &p->mentionable;

  /* discord/permissions.json:71:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
  arg_switches[8] = p->tags;

  r=json_inject(json, len, 
  /* discord/permissions.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* discord/permissions.json:64:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* discord/permissions.json:65:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                "(color):d,"
  /* discord/permissions.json:66:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                "(hoist):b,"
  /* discord/permissions.json:67:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                "(position):d,"
  /* discord/permissions.json:68:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                "(permissions):s,"
  /* discord/permissions.json:69:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                "(managed):b,"
  /* discord/permissions.json:70:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                "(mentionable):b,"
  /* discord/permissions.json:71:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                "(tags):F,"
                "@arg_switches:b",
  /* discord/permissions.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->id,
  /* discord/permissions.json:64:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* discord/permissions.json:65:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                &p->color,
  /* discord/permissions.json:66:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                &p->hoist,
  /* discord/permissions.json:67:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                &p->position,
  /* discord/permissions.json:68:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
                p->permissions,
  /* discord/permissions.json:69:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                &p->managed,
  /* discord/permissions.json:70:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                &p->mentionable,
  /* discord/permissions.json:71:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                discord_role_tags_to_json, p->tags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_role_cleanup_v(void *p) {
  discord_role_cleanup((struct discord_role *)p);
}

void discord_role_init_v(void *p) {
  discord_role_init((struct discord_role *)p);
}

void discord_role_from_json_v(char *json, size_t len, void *p) {
 discord_role_from_json(json, len, (struct discord_role*)p);
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
  /* discord/permissions.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->id;
  /* discord/permissions.json:64:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* discord/permissions.json:65:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  (void)d->color;
  /* discord/permissions.json:66:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  (void)d->hoist;
  /* discord/permissions.json:67:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  (void)d->position;
  /* discord/permissions.json:68:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  if (d->permissions)
    free(d->permissions);
  /* discord/permissions.json:69:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  (void)d->managed;
  /* discord/permissions.json:70:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  (void)d->mentionable;
  /* discord/permissions.json:71:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
  if (d->tags) {
    discord_role_tags_cleanup(d->tags);
    free(d->tags);
  }
}

void discord_role_init(struct discord_role *p) {
  memset(p, 0, sizeof(struct discord_role));
  /* discord/permissions.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/permissions.json:64:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/permissions.json:65:20
     '{ "name": "color", "type":{ "base":"int" }}' */

  /* discord/permissions.json:66:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */

  /* discord/permissions.json:67:20
     '{ "name": "position", "type":{ "base":"int" }}' */

  /* discord/permissions.json:68:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/permissions.json:69:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */

  /* discord/permissions.json:70:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */

  /* discord/permissions.json:71:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */

}
void discord_role_list_free(struct discord_role **p) {
  ntl_free((void**)p, (void(*)(void*))discord_role_cleanup);
}

void discord_role_list_from_json(char *str, size_t len, struct discord_role ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_role);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_role_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_role_list_to_json(char *str, size_t len, struct discord_role **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_role_to_json);
}


void discord_role_tags_from_json_p(char *json, size_t len, struct discord_role_tags **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_role_tags_from_json(json, len, *pp);
}
void discord_role_tags_from_json(char *json, size_t len, struct discord_role_tags *p)
{
  discord_role_tags_init(p);
  json_extract(json, len, 
  /* discord/permissions.json:81:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(bot_id):F,"
  /* discord/permissions.json:82:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(integration_id):F,"
  /* discord/permissions.json:83:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                "(premium_subscriber):d,",
  /* discord/permissions.json:81:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->bot_id,
  /* discord/permissions.json:82:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->integration_id,
  /* discord/permissions.json:83:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                &p->premium_subscriber);
}

size_t discord_role_tags_to_json(char *json, size_t len, struct discord_role_tags *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/permissions.json:81:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->bot_id;

  /* discord/permissions.json:82:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[1] = &p->integration_id;

  /* discord/permissions.json:83:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  arg_switches[2] = &p->premium_subscriber;

  r=json_inject(json, len, 
  /* discord/permissions.json:81:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(bot_id):|F|,"
  /* discord/permissions.json:82:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(integration_id):|F|,"
  /* discord/permissions.json:83:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                "(premium_subscriber):d,"
                "@arg_switches:b",
  /* discord/permissions.json:81:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->bot_id,
  /* discord/permissions.json:82:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->integration_id,
  /* discord/permissions.json:83:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                &p->premium_subscriber,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_role_tags_cleanup_v(void *p) {
  discord_role_tags_cleanup((struct discord_role_tags *)p);
}

void discord_role_tags_init_v(void *p) {
  discord_role_tags_init((struct discord_role_tags *)p);
}

void discord_role_tags_from_json_v(char *json, size_t len, void *p) {
 discord_role_tags_from_json(json, len, (struct discord_role_tags*)p);
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
  /* discord/permissions.json:81:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->bot_id;
  /* discord/permissions.json:82:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->integration_id;
  /* discord/permissions.json:83:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  (void)d->premium_subscriber;
}

void discord_role_tags_init(struct discord_role_tags *p) {
  memset(p, 0, sizeof(struct discord_role_tags));
  /* discord/permissions.json:81:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/permissions.json:82:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/permissions.json:83:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */

}
void discord_role_tags_list_free(struct discord_role_tags **p) {
  ntl_free((void**)p, (void(*)(void*))discord_role_tags_cleanup);
}

void discord_role_tags_list_from_json(char *str, size_t len, struct discord_role_tags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_role_tags);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_role_tags_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_role_tags_list_to_json(char *str, size_t len, struct discord_role_tags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_role_tags_to_json);
}

