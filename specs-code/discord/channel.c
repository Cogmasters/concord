/* This file is generated from discord/channel.json, Please don't edit it. */
/**
 * @file specs-code/discord/channel.c
 * @see https://discord.com/developers/docs/resources/channel
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"


void discord_channel_types_list_free_v(void **p) {
  discord_channel_types_list_free((enum discord_channel_types**)p);
}

void discord_channel_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_types_list_from_json(str, len, (enum discord_channel_types ***)p);
}

size_t discord_channel_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_types_list_to_json(str, len, (enum discord_channel_types **)p);
}

enum discord_channel_types discord_channel_types_eval(char *s){
  if(strcasecmp("GUILD_TEXT", s) == 0) return DISCORD_CHANNEL_GUILD_TEXT;
  if(strcasecmp("DM", s) == 0) return DISCORD_CHANNEL_DM;
  if(strcasecmp("GUILD_VOICE", s) == 0) return DISCORD_CHANNEL_GUILD_VOICE;
  if(strcasecmp("GROUP_DM", s) == 0) return DISCORD_CHANNEL_GROUP_DM;
  if(strcasecmp("GUILD_CATEGORY", s) == 0) return DISCORD_CHANNEL_GUILD_CATEGORY;
  if(strcasecmp("GUILD_NEWS", s) == 0) return DISCORD_CHANNEL_GUILD_NEWS;
  if(strcasecmp("GUILD_STORE", s) == 0) return DISCORD_CHANNEL_GUILD_STORE;
  if(strcasecmp("GUILD_NEWS_THREAD", s) == 0) return DISCORD_CHANNEL_GUILD_NEWS_THREAD;
  if(strcasecmp("GUILD_PUBLIC_THREAD", s) == 0) return DISCORD_CHANNEL_GUILD_PUBLIC_THREAD;
  if(strcasecmp("GUILD_PRIVATE_THREAD", s) == 0) return DISCORD_CHANNEL_GUILD_PRIVATE_THREAD;
  if(strcasecmp("GUILD_STAGE_VOICE", s) == 0) return DISCORD_CHANNEL_GUILD_STAGE_VOICE;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_channel_types_print(enum discord_channel_types v){

  switch (v) {
  case DISCORD_CHANNEL_GUILD_TEXT: return "GUILD_TEXT";
  case DISCORD_CHANNEL_DM: return "DM";
  case DISCORD_CHANNEL_GUILD_VOICE: return "GUILD_VOICE";
  case DISCORD_CHANNEL_GROUP_DM: return "GROUP_DM";
  case DISCORD_CHANNEL_GUILD_CATEGORY: return "GUILD_CATEGORY";
  case DISCORD_CHANNEL_GUILD_NEWS: return "GUILD_NEWS";
  case DISCORD_CHANNEL_GUILD_STORE: return "GUILD_STORE";
  case DISCORD_CHANNEL_GUILD_NEWS_THREAD: return "GUILD_NEWS_THREAD";
  case DISCORD_CHANNEL_GUILD_PUBLIC_THREAD: return "GUILD_PUBLIC_THREAD";
  case DISCORD_CHANNEL_GUILD_PRIVATE_THREAD: return "GUILD_PRIVATE_THREAD";
  case DISCORD_CHANNEL_GUILD_STAGE_VOICE: return "GUILD_STAGE_VOICE";
  }

  return NULL;
}

void discord_channel_types_list_free(enum discord_channel_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_channel_types_list_from_json(char *str, size_t len, enum discord_channel_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_channel_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_types_list_to_json(char *str, size_t len, enum discord_channel_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_channel_from_json_p(char *json, size_t len, struct discord_channel **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_channel_from_json(json, len, *pp);
}
void discord_channel_from_json(char *json, size_t len, struct discord_channel *p)
{
  discord_channel_init(p);
  json_extract(json, len, 
  /* discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):F,"
  /* discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
                "(type):d,"
  /* discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
                "(guild_id):F,"
  /* discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
                "(position):d,"
  /* discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
                "(permission_overwrites):F,"
  /* discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */
                "(name):?s,"
  /* discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */
                "(topic):?s,"
  /* discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
                "(nsfw):b,"
  /* discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
                "(last_message_id):F,"
  /* discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
                "(bitrate):d,"
  /* discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
                "(user_limit):d,"
  /* discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
                "(rate_limit_per_user):d,"
  /* discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
                "(recipients):F,"
  /* discord/channel.json:51:53
     '{"type":{"base":"char", "dec":"*"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
                "(icon):?s,"
  /* discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
                "(owner_id):F,"
  /* discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
                "(application_id):F,"
  /* discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
                "(parent_id):F,"
  /* discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
                "(last_pin_timestamp):F,"
  /* discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
                "(messages):F,",
  /* discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_strtou64, &p->id,
  /* discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
                &p->type,
  /* discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
                cee_strtou64, &p->guild_id,
  /* discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
                &p->position,
  /* discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
                discord_overwrite_list_from_json, &p->permission_overwrites,
  /* discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */
                &p->name,
  /* discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */
                &p->topic,
  /* discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
                &p->nsfw,
  /* discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
                cee_strtou64, &p->last_message_id,
  /* discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
                &p->bitrate,
  /* discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
                &p->user_limit,
  /* discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
                &p->rate_limit_per_user,
  /* discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
                discord_user_list_from_json, &p->recipients,
  /* discord/channel.json:51:53
     '{"type":{"base":"char", "dec":"*"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
                &p->icon,
  /* discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
                cee_strtou64, &p->owner_id,
  /* discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
                cee_strtou64, &p->application_id,
  /* discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
                cee_strtou64, &p->parent_id,
  /* discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
                cee_iso8601_to_unix_ms, &p->last_pin_timestamp,
  /* discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
                discord_message_list_from_json, &p->messages);
}

size_t discord_channel_to_json(char *json, size_t len, struct discord_channel *p)
{
  size_t r;
  void *arg_switches[19]={NULL};
  /* discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  arg_switches[0] = &p->id;

  /* discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
  arg_switches[1] = &p->type;

  /* discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
  if (p->guild_id != 0)
    arg_switches[2] = &p->guild_id;

  /* discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
  if (p->position != 0)
    arg_switches[3] = &p->position;

  /* discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
  if (p->permission_overwrites != NULL)
    arg_switches[4] = p->permission_overwrites;

  /* discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */
  if (p->name != NULL)
    arg_switches[5] = p->name;

  /* discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */
  if (p->topic != NULL)
    arg_switches[6] = p->topic;

  /* discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
  if (p->nsfw != false)
    arg_switches[7] = &p->nsfw;

  /* discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
  if (p->last_message_id != 0)
    arg_switches[8] = &p->last_message_id;

  /* discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
  if (p->bitrate != 0)
    arg_switches[9] = &p->bitrate;

  /* discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
  if (p->user_limit != 0)
    arg_switches[10] = &p->user_limit;

  /* discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
  if (p->rate_limit_per_user != 0)
    arg_switches[11] = &p->rate_limit_per_user;

  /* discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
  if (p->recipients != NULL)
    arg_switches[12] = p->recipients;

  /* discord/channel.json:51:53
     '{"type":{"base":"char", "dec":"*"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
  if (p->icon != NULL)
    arg_switches[13] = p->icon;

  /* discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
  if (p->owner_id != 0)
    arg_switches[14] = &p->owner_id;

  /* discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
  if (p->application_id != 0)
    arg_switches[15] = &p->application_id;

  /* discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
  if (p->parent_id != 0)
    arg_switches[16] = &p->parent_id;

  /* discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
  if (p->last_pin_timestamp != 0)
    arg_switches[17] = &p->last_pin_timestamp;

  /* discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
  arg_switches[18] = p->messages;

  r=json_inject(json, len, 
  /* discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):|F|,"
  /* discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
                "(type):d,"
  /* discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
                "(guild_id):|F|,"
  /* discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
                "(position):d,"
  /* discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
                "(permission_overwrites):F,"
  /* discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */
                "(name):s,"
  /* discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */
                "(topic):s,"
  /* discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
                "(nsfw):b,"
  /* discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
                "(last_message_id):|F|,"
  /* discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
                "(bitrate):d,"
  /* discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
                "(user_limit):d,"
  /* discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
                "(rate_limit_per_user):d,"
  /* discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
                "(recipients):F,"
  /* discord/channel.json:51:53
     '{"type":{"base":"char", "dec":"*"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
                "(icon):s,"
  /* discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
                "(owner_id):|F|,"
  /* discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
                "(application_id):|F|,"
  /* discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
                "(parent_id):|F|,"
  /* discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
                "(last_pin_timestamp):|F|,"
  /* discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
                "(messages):F,"
                "@arg_switches:b",
  /* discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_u64tostr, &p->id,
  /* discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
                &p->type,
  /* discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
                cee_u64tostr, &p->guild_id,
  /* discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
                &p->position,
  /* discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
                discord_overwrite_list_to_json, p->permission_overwrites,
  /* discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */
                p->name,
  /* discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */
                p->topic,
  /* discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
                &p->nsfw,
  /* discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
                cee_u64tostr, &p->last_message_id,
  /* discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
                &p->bitrate,
  /* discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
                &p->user_limit,
  /* discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
                &p->rate_limit_per_user,
  /* discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
                discord_user_list_to_json, p->recipients,
  /* discord/channel.json:51:53
     '{"type":{"base":"char", "dec":"*"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
                p->icon,
  /* discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
                cee_u64tostr, &p->owner_id,
  /* discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
                cee_u64tostr, &p->application_id,
  /* discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
                cee_u64tostr, &p->parent_id,
  /* discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
                cee_unix_ms_to_iso8601, &p->last_pin_timestamp,
  /* discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
                discord_message_list_to_json, p->messages,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_channel_cleanup_v(void *p) {
  discord_channel_cleanup((struct discord_channel *)p);
}

void discord_channel_init_v(void *p) {
  discord_channel_init((struct discord_channel *)p);
}

void discord_channel_from_json_v(char *json, size_t len, void *p) {
 discord_channel_from_json(json, len, (struct discord_channel*)p);
}

size_t discord_channel_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_to_json(json, len, (struct discord_channel*)p);
}

void discord_channel_list_free_v(void **p) {
  discord_channel_list_free((struct discord_channel**)p);
}

void discord_channel_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_list_from_json(str, len, (struct discord_channel ***)p);
}

size_t discord_channel_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_list_to_json(str, len, (struct discord_channel **)p);
}


void discord_channel_cleanup(struct discord_channel *d) {
  /* discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  (void)d->id;
  /* discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
  (void)d->type;
  /* discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
  (void)d->guild_id;
  /* discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
  (void)d->position;
  /* discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
  if (d->permission_overwrites)
    discord_overwrite_list_free(d->permission_overwrites);
  /* discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */
  if (d->name)
    free(d->name);
  /* discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */
  if (d->topic)
    free(d->topic);
  /* discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
  (void)d->nsfw;
  /* discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
  (void)d->last_message_id;
  /* discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
  (void)d->bitrate;
  /* discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
  (void)d->user_limit;
  /* discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
  (void)d->rate_limit_per_user;
  /* discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
  if (d->recipients)
    discord_user_list_free(d->recipients);
  /* discord/channel.json:51:53
     '{"type":{"base":"char", "dec":"*"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
  if (d->icon)
    free(d->icon);
  /* discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
  (void)d->owner_id;
  /* discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
  (void)d->application_id;
  /* discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
  (void)d->parent_id;
  /* discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
  (void)d->last_pin_timestamp;
  /* discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
  if (d->messages)
    discord_message_list_free(d->messages);
}

void discord_channel_init(struct discord_channel *p) {
  memset(p, 0, sizeof(struct discord_channel));
  /* discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */

  /* discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */

  /* discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */

  /* discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */

  /* discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */

  /* discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */

  /* discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */

  /* discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */

  /* discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */

  /* discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */

  /* discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */

  /* discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */

  /* discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */

  /* discord/channel.json:51:53
     '{"type":{"base":"char", "dec":"*"}, "name":"icon",
         "option":true, "inject_if_not":null}' */

  /* discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */

  /* discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */

  /* discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */

  /* discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */

  /* discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */

}
void discord_channel_list_free(struct discord_channel **p) {
  ntl_free((void**)p, (void(*)(void*))discord_channel_cleanup);
}

void discord_channel_list_from_json(char *str, size_t len, struct discord_channel ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_channel_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_list_to_json(char *str, size_t len, struct discord_channel **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_channel_to_json);
}



void discord_message_sticker_format_types_list_free_v(void **p) {
  discord_message_sticker_format_types_list_free((enum discord_message_sticker_format_types**)p);
}

void discord_message_sticker_format_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_sticker_format_types_list_from_json(str, len, (enum discord_message_sticker_format_types ***)p);
}

size_t discord_message_sticker_format_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_sticker_format_types_list_to_json(str, len, (enum discord_message_sticker_format_types **)p);
}

enum discord_message_sticker_format_types discord_message_sticker_format_types_eval(char *s){
  if(strcasecmp("PNG", s) == 0) return DISCORD_MESSAGE_STICKER_PNG;
  if(strcasecmp("APNG", s) == 0) return DISCORD_MESSAGE_STICKER_APNG;
  if(strcasecmp("LOTTIE", s) == 0) return DISCORD_MESSAGE_STICKER_LOTTIE;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_message_sticker_format_types_print(enum discord_message_sticker_format_types v){

  switch (v) {
  case DISCORD_MESSAGE_STICKER_PNG: return "PNG";
  case DISCORD_MESSAGE_STICKER_APNG: return "APNG";
  case DISCORD_MESSAGE_STICKER_LOTTIE: return "LOTTIE";
  }

  return NULL;
}

void discord_message_sticker_format_types_list_free(enum discord_message_sticker_format_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_message_sticker_format_types_list_from_json(char *str, size_t len, enum discord_message_sticker_format_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_message_sticker_format_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_sticker_format_types_list_to_json(char *str, size_t len, enum discord_message_sticker_format_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_message_sticker_from_json_p(char *json, size_t len, struct discord_message_sticker **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_message_sticker_from_json(json, len, *pp);
}
void discord_message_sticker_from_json(char *json, size_t len, struct discord_message_sticker *p)
{
  discord_message_sticker_init(p);
  json_extract(json, len, 
  /* discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(pack_id):F,"
  /* discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                "(description):?s,"
  /* discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
                "(tags):?s,"
  /* discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"*"}}' */
                "(asset):?s,"
  /* discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(preview_asset):?s,"
  /* discord/channel.json:89:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
                "(type):d,",
  /* discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtou64, &p->id,
  /* discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtou64, &p->pack_id,
  /* discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                &p->name,
  /* discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                &p->description,
  /* discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
                &p->tags,
  /* discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"*"}}' */
                &p->asset,
  /* discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->preview_asset,
  /* discord/channel.json:89:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
                &p->type);
}

size_t discord_message_sticker_to_json(char *json, size_t len, struct discord_message_sticker *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  arg_switches[0] = &p->id;

  /* discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  arg_switches[1] = &p->pack_id;

  /* discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  arg_switches[2] = p->name;

  /* discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  arg_switches[3] = p->description;

  /* discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
  arg_switches[4] = p->tags;

  /* discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"*"}}' */
  arg_switches[5] = p->asset;

  /* discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->preview_asset != NULL)
    arg_switches[6] = p->preview_asset;

  /* discord/channel.json:89:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
  arg_switches[7] = &p->type;

  r=json_inject(json, len, 
  /* discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(pack_id):|F|,"
  /* discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                "(name):s,"
  /* discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                "(description):s,"
  /* discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
                "(tags):s,"
  /* discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"*"}}' */
                "(asset):s,"
  /* discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(preview_asset):s,"
  /* discord/channel.json:89:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
                "(type):d,"
                "@arg_switches:b",
  /* discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_u64tostr, &p->id,
  /* discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_u64tostr, &p->pack_id,
  /* discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                p->name,
  /* discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                p->description,
  /* discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
                p->tags,
  /* discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"*"}}' */
                p->asset,
  /* discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->preview_asset,
  /* discord/channel.json:89:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
                &p->type,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_message_sticker_cleanup_v(void *p) {
  discord_message_sticker_cleanup((struct discord_message_sticker *)p);
}

void discord_message_sticker_init_v(void *p) {
  discord_message_sticker_init((struct discord_message_sticker *)p);
}

void discord_message_sticker_from_json_v(char *json, size_t len, void *p) {
 discord_message_sticker_from_json(json, len, (struct discord_message_sticker*)p);
}

size_t discord_message_sticker_to_json_v(char *json, size_t len, void *p) {
  return discord_message_sticker_to_json(json, len, (struct discord_message_sticker*)p);
}

void discord_message_sticker_list_free_v(void **p) {
  discord_message_sticker_list_free((struct discord_message_sticker**)p);
}

void discord_message_sticker_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_sticker_list_from_json(str, len, (struct discord_message_sticker ***)p);
}

size_t discord_message_sticker_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_sticker_list_to_json(str, len, (struct discord_message_sticker **)p);
}


void discord_message_sticker_cleanup(struct discord_message_sticker *d) {
  /* discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  (void)d->id;
  /* discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  (void)d->pack_id;
  /* discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  if (d->description)
    free(d->description);
  /* discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
  if (d->tags)
    free(d->tags);
  /* discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"*"}}' */
  if (d->asset)
    free(d->asset);
  /* discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->preview_asset)
    free(d->preview_asset);
  /* discord/channel.json:89:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
  (void)d->type;
}

void discord_message_sticker_init(struct discord_message_sticker *p) {
  memset(p, 0, sizeof(struct discord_message_sticker));
  /* discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */

  /* discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */

  /* discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */

  /* discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"*"}}' */

  /* discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* discord/channel.json:89:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */

}
void discord_message_sticker_list_free(struct discord_message_sticker **p) {
  ntl_free((void**)p, (void(*)(void*))discord_message_sticker_cleanup);
}

void discord_message_sticker_list_from_json(char *str, size_t len, struct discord_message_sticker ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_sticker);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_message_sticker_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_sticker_list_to_json(char *str, size_t len, struct discord_message_sticker **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_message_sticker_to_json);
}



void discord_message_flags_list_free_v(void **p) {
  discord_message_flags_list_free((enum discord_message_flags**)p);
}

void discord_message_flags_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_flags_list_from_json(str, len, (enum discord_message_flags ***)p);
}

size_t discord_message_flags_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_flags_list_to_json(str, len, (enum discord_message_flags **)p);
}

enum discord_message_flags discord_message_flags_eval(char *s){
  if(strcasecmp("CROSSPOSTED", s) == 0) return DISCORD_MESSAGE_CROSSPOSTED;
  if(strcasecmp("IS_CROSSPOST", s) == 0) return DISCORD_MESSAGE_IS_CROSSPOST;
  if(strcasecmp("SUPRESS_EMBEDS", s) == 0) return DISCORD_MESSAGE_SUPRESS_EMBEDS;
  if(strcasecmp("SOURCE_MESSAGE_DELETED", s) == 0) return DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED;
  if(strcasecmp("URGENT", s) == 0) return DISCORD_MESSAGE_URGENT;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_message_flags_print(enum discord_message_flags v){

  switch (v) {
  case DISCORD_MESSAGE_CROSSPOSTED: return "CROSSPOSTED";
  case DISCORD_MESSAGE_IS_CROSSPOST: return "IS_CROSSPOST";
  case DISCORD_MESSAGE_SUPRESS_EMBEDS: return "SUPRESS_EMBEDS";
  case DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED: return "SOURCE_MESSAGE_DELETED";
  case DISCORD_MESSAGE_URGENT: return "URGENT";
  }

  return NULL;
}

void discord_message_flags_list_free(enum discord_message_flags **p) {
  ntl_free((void**)p, NULL);
}

void discord_message_flags_list_from_json(char *str, size_t len, enum discord_message_flags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_message_flags);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_flags_list_to_json(char *str, size_t len, enum discord_message_flags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_message_reference_from_json_p(char *json, size_t len, struct discord_message_reference **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_message_reference_from_json(json, len, *pp);
}
void discord_message_reference_from_json(char *json, size_t len, struct discord_message_reference *p)
{
  discord_message_reference_init(p);
  json_extract(json, len, 
  /* discord/channel.json:111:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(message_id):F,"
  /* discord/channel.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(channel_id):F,"
  /* discord/channel.json:113:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(guild_id):F,"
  /* discord/channel.json:114:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                "(fail_if_not_exists):b,",
  /* discord/channel.json:111:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_strtou64, &p->message_id,
  /* discord/channel.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_strtou64, &p->channel_id,
  /* discord/channel.json:113:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_strtou64, &p->guild_id,
  /* discord/channel.json:114:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                &p->fail_if_not_exists);
}

size_t discord_message_reference_to_json(char *json, size_t len, struct discord_message_reference *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:111:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  if (p->message_id != 0)
    arg_switches[0] = &p->message_id;

  /* discord/channel.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  if (p->channel_id != 0)
    arg_switches[1] = &p->channel_id;

  /* discord/channel.json:113:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  if (p->guild_id != 0)
    arg_switches[2] = &p->guild_id;

  /* discord/channel.json:114:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  if (p->fail_if_not_exists != false)
    arg_switches[3] = &p->fail_if_not_exists;

  r=json_inject(json, len, 
  /* discord/channel.json:111:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(message_id):|F|,"
  /* discord/channel.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(channel_id):|F|,"
  /* discord/channel.json:113:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(guild_id):|F|,"
  /* discord/channel.json:114:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                "(fail_if_not_exists):b,"
                "@arg_switches:b",
  /* discord/channel.json:111:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_u64tostr, &p->message_id,
  /* discord/channel.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_u64tostr, &p->channel_id,
  /* discord/channel.json:113:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_u64tostr, &p->guild_id,
  /* discord/channel.json:114:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                &p->fail_if_not_exists,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_message_reference_cleanup_v(void *p) {
  discord_message_reference_cleanup((struct discord_message_reference *)p);
}

void discord_message_reference_init_v(void *p) {
  discord_message_reference_init((struct discord_message_reference *)p);
}

void discord_message_reference_from_json_v(char *json, size_t len, void *p) {
 discord_message_reference_from_json(json, len, (struct discord_message_reference*)p);
}

size_t discord_message_reference_to_json_v(char *json, size_t len, void *p) {
  return discord_message_reference_to_json(json, len, (struct discord_message_reference*)p);
}

void discord_message_reference_list_free_v(void **p) {
  discord_message_reference_list_free((struct discord_message_reference**)p);
}

void discord_message_reference_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_reference_list_from_json(str, len, (struct discord_message_reference ***)p);
}

size_t discord_message_reference_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_reference_list_to_json(str, len, (struct discord_message_reference **)p);
}


void discord_message_reference_cleanup(struct discord_message_reference *d) {
  /* discord/channel.json:111:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  (void)d->message_id;
  /* discord/channel.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  (void)d->channel_id;
  /* discord/channel.json:113:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  (void)d->guild_id;
  /* discord/channel.json:114:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  (void)d->fail_if_not_exists;
}

void discord_message_reference_init(struct discord_message_reference *p) {
  memset(p, 0, sizeof(struct discord_message_reference));
  /* discord/channel.json:111:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */

  /* discord/channel.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */

  /* discord/channel.json:113:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */

  /* discord/channel.json:114:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */

}
void discord_message_reference_list_free(struct discord_message_reference **p) {
  ntl_free((void**)p, (void(*)(void*))discord_message_reference_cleanup);
}

void discord_message_reference_list_from_json(char *str, size_t len, struct discord_message_reference ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_reference);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_message_reference_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_reference_list_to_json(char *str, size_t len, struct discord_message_reference **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_message_reference_to_json);
}


void discord_message_application_from_json_p(char *json, size_t len, struct discord_message_application **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_message_application_from_json(json, len, *pp);
}
void discord_message_application_from_json(char *json, size_t len, struct discord_message_application *p)
{
  discord_message_application_init(p);
  json_extract(json, len, 
  /* discord/channel.json:123:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* discord/channel.json:124:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(cover_image):?s,"
  /* discord/channel.json:125:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                "(description):?s,"
  /* discord/channel.json:126:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(icon):?s,"
  /* discord/channel.json:127:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                "(name):?s,",
  /* discord/channel.json:123:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtou64, &p->id,
  /* discord/channel.json:124:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->cover_image,
  /* discord/channel.json:125:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                &p->description,
  /* discord/channel.json:126:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                &p->icon,
  /* discord/channel.json:127:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                &p->name);
}

size_t discord_message_application_to_json(char *json, size_t len, struct discord_message_application *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* discord/channel.json:123:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  arg_switches[0] = &p->id;

  /* discord/channel.json:124:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->cover_image != NULL)
    arg_switches[1] = p->cover_image;

  /* discord/channel.json:125:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  arg_switches[2] = p->description;

  /* discord/channel.json:126:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (p->icon != NULL)
    arg_switches[3] = p->icon;

  /* discord/channel.json:127:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  arg_switches[4] = p->name;

  r=json_inject(json, len, 
  /* discord/channel.json:123:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* discord/channel.json:124:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(cover_image):s,"
  /* discord/channel.json:125:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                "(description):s,"
  /* discord/channel.json:126:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(icon):s,"
  /* discord/channel.json:127:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                "(name):s,"
                "@arg_switches:b",
  /* discord/channel.json:123:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_u64tostr, &p->id,
  /* discord/channel.json:124:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->cover_image,
  /* discord/channel.json:125:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                p->description,
  /* discord/channel.json:126:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                p->icon,
  /* discord/channel.json:127:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                p->name,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_message_application_cleanup_v(void *p) {
  discord_message_application_cleanup((struct discord_message_application *)p);
}

void discord_message_application_init_v(void *p) {
  discord_message_application_init((struct discord_message_application *)p);
}

void discord_message_application_from_json_v(char *json, size_t len, void *p) {
 discord_message_application_from_json(json, len, (struct discord_message_application*)p);
}

size_t discord_message_application_to_json_v(char *json, size_t len, void *p) {
  return discord_message_application_to_json(json, len, (struct discord_message_application*)p);
}

void discord_message_application_list_free_v(void **p) {
  discord_message_application_list_free((struct discord_message_application**)p);
}

void discord_message_application_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_application_list_from_json(str, len, (struct discord_message_application ***)p);
}

size_t discord_message_application_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_application_list_to_json(str, len, (struct discord_message_application **)p);
}


void discord_message_application_cleanup(struct discord_message_application *d) {
  /* discord/channel.json:123:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  (void)d->id;
  /* discord/channel.json:124:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->cover_image)
    free(d->cover_image);
  /* discord/channel.json:125:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  if (d->description)
    free(d->description);
  /* discord/channel.json:126:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (d->icon)
    free(d->icon);
  /* discord/channel.json:127:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
}

void discord_message_application_init(struct discord_message_application *p) {
  memset(p, 0, sizeof(struct discord_message_application));
  /* discord/channel.json:123:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* discord/channel.json:124:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* discord/channel.json:125:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */

  /* discord/channel.json:126:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */

  /* discord/channel.json:127:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */

}
void discord_message_application_list_free(struct discord_message_application **p) {
  ntl_free((void**)p, (void(*)(void*))discord_message_application_cleanup);
}

void discord_message_application_list_from_json(char *str, size_t len, struct discord_message_application ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_application);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_message_application_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_application_list_to_json(char *str, size_t len, struct discord_message_application **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_message_application_to_json);
}



void discord_message_activity_types_list_free_v(void **p) {
  discord_message_activity_types_list_free((enum discord_message_activity_types**)p);
}

void discord_message_activity_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_activity_types_list_from_json(str, len, (enum discord_message_activity_types ***)p);
}

size_t discord_message_activity_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_activity_types_list_to_json(str, len, (enum discord_message_activity_types **)p);
}

enum discord_message_activity_types discord_message_activity_types_eval(char *s){
  if(strcasecmp("JOIN", s) == 0) return DISCORD_MESSAGE_ACTIVITY_JOIN;
  if(strcasecmp("SPECTATE", s) == 0) return DISCORD_MESSAGE_ACTIVITY_SPECTATE;
  if(strcasecmp("LISTEN", s) == 0) return DISCORD_MESSAGE_ACTIVITY_LISTEN;
  if(strcasecmp("JOIN_REQUEST", s) == 0) return DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_message_activity_types_print(enum discord_message_activity_types v){

  switch (v) {
  case DISCORD_MESSAGE_ACTIVITY_JOIN: return "JOIN";
  case DISCORD_MESSAGE_ACTIVITY_SPECTATE: return "SPECTATE";
  case DISCORD_MESSAGE_ACTIVITY_LISTEN: return "LISTEN";
  case DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST: return "JOIN_REQUEST";
  }

  return NULL;
}

void discord_message_activity_types_list_free(enum discord_message_activity_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_message_activity_types_list_from_json(char *str, size_t len, enum discord_message_activity_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_message_activity_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_activity_types_list_to_json(char *str, size_t len, enum discord_message_activity_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_message_activity_from_json_p(char *json, size_t len, struct discord_message_activity **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_message_activity_from_json(json, len, *pp);
}
void discord_message_activity_from_json(char *json, size_t len, struct discord_message_activity *p)
{
  discord_message_activity_init(p);
  json_extract(json, len, 
  /* discord/channel.json:148:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
                "(type):d,"
  /* discord/channel.json:149:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
                "(party_id):?s,",
  /* discord/channel.json:148:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
                &p->type,
  /* discord/channel.json:149:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
                &p->party_id);
}

size_t discord_message_activity_to_json(char *json, size_t len, struct discord_message_activity *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/channel.json:148:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
  arg_switches[0] = &p->type;

  /* discord/channel.json:149:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
  if (p->party_id != NULL)
    arg_switches[1] = p->party_id;

  r=json_inject(json, len, 
  /* discord/channel.json:148:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
                "(type):d,"
  /* discord/channel.json:149:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
                "(party_id):s,"
                "@arg_switches:b",
  /* discord/channel.json:148:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
                &p->type,
  /* discord/channel.json:149:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
                p->party_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_message_activity_cleanup_v(void *p) {
  discord_message_activity_cleanup((struct discord_message_activity *)p);
}

void discord_message_activity_init_v(void *p) {
  discord_message_activity_init((struct discord_message_activity *)p);
}

void discord_message_activity_from_json_v(char *json, size_t len, void *p) {
 discord_message_activity_from_json(json, len, (struct discord_message_activity*)p);
}

size_t discord_message_activity_to_json_v(char *json, size_t len, void *p) {
  return discord_message_activity_to_json(json, len, (struct discord_message_activity*)p);
}

void discord_message_activity_list_free_v(void **p) {
  discord_message_activity_list_free((struct discord_message_activity**)p);
}

void discord_message_activity_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_activity_list_from_json(str, len, (struct discord_message_activity ***)p);
}

size_t discord_message_activity_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_activity_list_to_json(str, len, (struct discord_message_activity **)p);
}


void discord_message_activity_cleanup(struct discord_message_activity *d) {
  /* discord/channel.json:148:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
  (void)d->type;
  /* discord/channel.json:149:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
  if (d->party_id)
    free(d->party_id);
}

void discord_message_activity_init(struct discord_message_activity *p) {
  memset(p, 0, sizeof(struct discord_message_activity));
  /* discord/channel.json:148:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */

  /* discord/channel.json:149:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */

}
void discord_message_activity_list_free(struct discord_message_activity **p) {
  ntl_free((void**)p, (void(*)(void*))discord_message_activity_cleanup);
}

void discord_message_activity_list_from_json(char *str, size_t len, struct discord_message_activity ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_activity);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_message_activity_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_activity_list_to_json(char *str, size_t len, struct discord_message_activity **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_message_activity_to_json);
}



void discord_message_types_list_free_v(void **p) {
  discord_message_types_list_free((enum discord_message_types**)p);
}

void discord_message_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_types_list_from_json(str, len, (enum discord_message_types ***)p);
}

size_t discord_message_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_types_list_to_json(str, len, (enum discord_message_types **)p);
}

enum discord_message_types discord_message_types_eval(char *s){
  if(strcasecmp("DEFAULT", s) == 0) return DISCORD_MESSAGE_DEFAULT;
  if(strcasecmp("RECIPIENT_ADD", s) == 0) return DISCORD_MESSAGE_RECIPIENT_ADD;
  if(strcasecmp("RECIPIENT_REMOVE", s) == 0) return DISCORD_MESSAGE_RECIPIENT_REMOVE;
  if(strcasecmp("CALL", s) == 0) return DISCORD_MESSAGE_CALL;
  if(strcasecmp("CHANNEL_NAME_CHANGE", s) == 0) return DISCORD_MESSAGE_CHANNEL_NAME_CHANGE;
  if(strcasecmp("CHANNEL_ICON_CHANGE", s) == 0) return DISCORD_MESSAGE_CHANNEL_ICON_CHANGE;
  if(strcasecmp("CHANNEL_PINNED_MESSAGE", s) == 0) return DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE;
  if(strcasecmp("GUILD_MEMBER_JOIN", s) == 0) return DISCORD_MESSAGE_GUILD_MEMBER_JOIN;
  if(strcasecmp("USER_PREMIUM_GUILD_SUBSCRIPTION", s) == 0) return DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION;
  if(strcasecmp("USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1", s) == 0) return DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1;
  if(strcasecmp("USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2", s) == 0) return DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2;
  if(strcasecmp("USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3", s) == 0) return DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3;
  if(strcasecmp("CHANNEL_FOLLOW_ADD", s) == 0) return DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD;
  if(strcasecmp("GUILD_DISCOVERY_DISQUALIFIED", s) == 0) return DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED;
  if(strcasecmp("GUILD_DISCOVERY_REQUALIFIED", s) == 0) return DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED;
  if(strcasecmp("REPLY", s) == 0) return DISCORD_MESSAGE_REPLY;
  if(strcasecmp("APPLICATION_COMMAND", s) == 0) return DISCORD_MESSAGE_APPLICATION_COMMAND;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_message_types_print(enum discord_message_types v){

  switch (v) {
  case DISCORD_MESSAGE_DEFAULT: return "DEFAULT";
  case DISCORD_MESSAGE_RECIPIENT_ADD: return "RECIPIENT_ADD";
  case DISCORD_MESSAGE_RECIPIENT_REMOVE: return "RECIPIENT_REMOVE";
  case DISCORD_MESSAGE_CALL: return "CALL";
  case DISCORD_MESSAGE_CHANNEL_NAME_CHANGE: return "CHANNEL_NAME_CHANGE";
  case DISCORD_MESSAGE_CHANNEL_ICON_CHANGE: return "CHANNEL_ICON_CHANGE";
  case DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE: return "CHANNEL_PINNED_MESSAGE";
  case DISCORD_MESSAGE_GUILD_MEMBER_JOIN: return "GUILD_MEMBER_JOIN";
  case DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION: return "USER_PREMIUM_GUILD_SUBSCRIPTION";
  case DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1: return "USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1";
  case DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2: return "USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2";
  case DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3: return "USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3";
  case DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD: return "CHANNEL_FOLLOW_ADD";
  case DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED: return "GUILD_DISCOVERY_DISQUALIFIED";
  case DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED: return "GUILD_DISCOVERY_REQUALIFIED";
  case DISCORD_MESSAGE_REPLY: return "REPLY";
  case DISCORD_MESSAGE_APPLICATION_COMMAND: return "APPLICATION_COMMAND";
  }

  return NULL;
}

void discord_message_types_list_free(enum discord_message_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_message_types_list_from_json(char *str, size_t len, enum discord_message_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_message_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_types_list_to_json(char *str, size_t len, enum discord_message_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_message_from_json_p(char *json, size_t len, struct discord_message **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_message_from_json(json, len, *pp);
}
void discord_message_from_json(char *json, size_t len, struct discord_message *p)
{
  discord_message_init(p);
  json_extract(json, len, 
  /* discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):F,"
  /* discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
                "(channel_id):F,"
  /* discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
                "(guild_id):F,"
  /* discord/channel.json:186:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
                "(author):F,"
  /* discord/channel.json:187:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
                "(member):F,"
  /* discord/channel.json:188:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
                "(content):?s,"
  /* discord/channel.json:189:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
                "(timestamp):F,"
  /* discord/channel.json:190:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
                "(edited_timestamp):F,"
  /* discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
                "(tts):b,"
  /* discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
                "(mention_everyone):b,"
  /* discord/channel.json:193:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
                "(mentions):F,"
  /* discord/channel.json:194:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
                "(mention_roles):F,"
  /* discord/channel.json:195:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
                "(mention_channels):F,"
  /* discord/channel.json:196:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */
                "(attachments):F,"
  /* discord/channel.json:197:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
                "(embeds):F,"
  /* discord/channel.json:198:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
                "(reactions):F,"
  /* discord/channel.json:199:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
                "(nonce):?s,"
  /* discord/channel.json:200:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
                "(pinned):b,"
  /* discord/channel.json:201:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
                "(webhook_id):F,"
  /* discord/channel.json:202:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
                "(type):d,"
  /* discord/channel.json:203:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
                "(activity):F,"
  /* discord/channel.json:204:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
                "(application):F,"
  /* discord/channel.json:205:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
                "(message_reference):F,"
  /* discord/channel.json:206:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
                "(flags):d,"
  /* discord/channel.json:207:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
                "(referenced_message):F,"
  /* discord/channel.json:208:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
                "(interaction):F,"
  /* discord/channel.json:209:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
                "(thread):F,"
  /* discord/channel.json:210:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
                "(components):F,"
  /* discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
                "(sticker_items):F,"
  /* discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
                "(stickers):F,",
  /* discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_strtou64, &p->id,
  /* discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
                cee_strtou64, &p->channel_id,
  /* discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
                cee_strtou64, &p->guild_id,
  /* discord/channel.json:186:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
                discord_user_from_json_p, &p->author,
  /* discord/channel.json:187:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
                discord_guild_member_from_json_p, &p->member,
  /* discord/channel.json:188:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
                &p->content,
  /* discord/channel.json:189:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
                cee_iso8601_to_unix_ms, &p->timestamp,
  /* discord/channel.json:190:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
                cee_iso8601_to_unix_ms, &p->edited_timestamp,
  /* discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
                &p->tts,
  /* discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
                &p->mention_everyone,
  /* discord/channel.json:193:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
                discord_user_list_from_json, &p->mentions,
  /* discord/channel.json:194:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
                ja_u64_list_from_json, &p->mention_roles,
  /* discord/channel.json:195:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
                discord_channel_mention_list_from_json, &p->mention_channels,
  /* discord/channel.json:196:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */
                discord_attachment_list_from_json, &p->attachments,
  /* discord/channel.json:197:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
                discord_embed_list_from_json, &p->embeds,
  /* discord/channel.json:198:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
                discord_reaction_list_from_json, &p->reactions,
  /* discord/channel.json:199:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
                &p->nonce,
  /* discord/channel.json:200:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
                &p->pinned,
  /* discord/channel.json:201:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
                cee_strtou64, &p->webhook_id,
  /* discord/channel.json:202:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
                &p->type,
  /* discord/channel.json:203:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
                discord_message_activity_from_json_p, &p->activity,
  /* discord/channel.json:204:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
                discord_message_application_list_from_json, &p->application,
  /* discord/channel.json:205:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
                discord_message_reference_from_json_p, &p->message_reference,
  /* discord/channel.json:206:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
                &p->flags,
  /* discord/channel.json:207:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
                discord_message_from_json_p, &p->referenced_message,
  /* discord/channel.json:208:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
                discord_message_interaction_from_json_p, &p->interaction,
  /* discord/channel.json:209:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
                discord_channel_from_json_p, &p->thread,
  /* discord/channel.json:210:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
                discord_component_list_from_json, &p->components,
  /* discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
                discord_message_sticker_list_from_json, &p->sticker_items,
  /* discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
                discord_message_sticker_list_from_json, &p->stickers);
}

size_t discord_message_to_json(char *json, size_t len, struct discord_message *p)
{
  size_t r;
  void *arg_switches[30]={NULL};
  /* discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  arg_switches[0] = &p->id;

  /* discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
  arg_switches[1] = &p->channel_id;

  /* discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
  if (p->guild_id != 0)
    arg_switches[2] = &p->guild_id;

  /* discord/channel.json:186:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
  arg_switches[3] = p->author;

  /* discord/channel.json:187:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
  arg_switches[4] = p->member;

  /* discord/channel.json:188:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
  arg_switches[5] = p->content;

  /* discord/channel.json:189:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
  arg_switches[6] = &p->timestamp;

  /* discord/channel.json:190:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
  if (p->edited_timestamp != 0)
    arg_switches[7] = &p->edited_timestamp;

  /* discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
  arg_switches[8] = &p->tts;

  /* discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
  arg_switches[9] = &p->mention_everyone;

  /* discord/channel.json:193:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
  arg_switches[10] = p->mentions;

  /* discord/channel.json:194:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
  arg_switches[11] = p->mention_roles;

  /* discord/channel.json:195:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
  arg_switches[12] = p->mention_channels;

  /* discord/channel.json:196:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */
  arg_switches[13] = p->attachments;

  /* discord/channel.json:197:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
  arg_switches[14] = p->embeds;

  /* discord/channel.json:198:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
  arg_switches[15] = p->reactions;

  /* discord/channel.json:199:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
  arg_switches[16] = p->nonce;

  /* discord/channel.json:200:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
  arg_switches[17] = &p->pinned;

  /* discord/channel.json:201:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
  arg_switches[18] = &p->webhook_id;

  /* discord/channel.json:202:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
  arg_switches[19] = &p->type;

  /* discord/channel.json:203:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
  if (p->activity != NULL)
    arg_switches[20] = p->activity;

  /* discord/channel.json:204:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
  if (p->application != NULL)
    arg_switches[21] = p->application;

  /* discord/channel.json:205:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
  if (p->message_reference != NULL)
    arg_switches[22] = p->message_reference;

  /* discord/channel.json:206:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
  if (p->flags != 0)
    arg_switches[23] = &p->flags;

  /* discord/channel.json:207:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
  if (p->referenced_message != NULL)
    arg_switches[24] = p->referenced_message;

  /* discord/channel.json:208:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
  if (p->interaction != NULL)
    arg_switches[25] = p->interaction;

  /* discord/channel.json:209:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
  if (p->thread != NULL)
    arg_switches[26] = p->thread;

  /* discord/channel.json:210:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
  if (p->components != NULL)
    arg_switches[27] = p->components;

  /* discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
  if (p->sticker_items != NULL)
    arg_switches[28] = p->sticker_items;

  /* discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
  if (p->stickers != NULL)
    arg_switches[29] = p->stickers;

  r=json_inject(json, len, 
  /* discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):|F|,"
  /* discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
                "(channel_id):|F|,"
  /* discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
                "(guild_id):|F|,"
  /* discord/channel.json:186:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
                "(author):F,"
  /* discord/channel.json:187:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
                "(member):F,"
  /* discord/channel.json:188:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
                "(content):s,"
  /* discord/channel.json:189:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
                "(timestamp):|F|,"
  /* discord/channel.json:190:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
                "(edited_timestamp):|F|,"
  /* discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
                "(tts):b,"
  /* discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
                "(mention_everyone):b,"
  /* discord/channel.json:193:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
                "(mentions):F,"
  /* discord/channel.json:194:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
                "(mention_roles):F,"
  /* discord/channel.json:195:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
                "(mention_channels):F,"
  /* discord/channel.json:196:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */
                "(attachments):F,"
  /* discord/channel.json:197:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
                "(embeds):F,"
  /* discord/channel.json:198:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
                "(reactions):F,"
  /* discord/channel.json:199:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
                "(nonce):s,"
  /* discord/channel.json:200:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
                "(pinned):b,"
  /* discord/channel.json:201:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
                "(webhook_id):|F|,"
  /* discord/channel.json:202:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
                "(type):d,"
  /* discord/channel.json:203:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
                "(activity):F,"
  /* discord/channel.json:204:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
                "(application):F,"
  /* discord/channel.json:205:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
                "(message_reference):F,"
  /* discord/channel.json:206:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
                "(flags):d,"
  /* discord/channel.json:207:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
                "(referenced_message):F,"
  /* discord/channel.json:208:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
                "(interaction):F,"
  /* discord/channel.json:209:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
                "(thread):F,"
  /* discord/channel.json:210:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
                "(components):F,"
  /* discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
                "(sticker_items):F,"
  /* discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
                "(stickers):F,"
                "@arg_switches:b",
  /* discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_u64tostr, &p->id,
  /* discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
                cee_u64tostr, &p->channel_id,
  /* discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
                cee_u64tostr, &p->guild_id,
  /* discord/channel.json:186:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
                discord_user_to_json, p->author,
  /* discord/channel.json:187:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
                discord_guild_member_to_json, p->member,
  /* discord/channel.json:188:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
                p->content,
  /* discord/channel.json:189:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
                cee_unix_ms_to_iso8601, &p->timestamp,
  /* discord/channel.json:190:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
                cee_unix_ms_to_iso8601, &p->edited_timestamp,
  /* discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
                &p->tts,
  /* discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
                &p->mention_everyone,
  /* discord/channel.json:193:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
                discord_user_list_to_json, p->mentions,
  /* discord/channel.json:194:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
                ja_u64_list_to_json, p->mention_roles,
  /* discord/channel.json:195:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
                discord_channel_mention_list_to_json, p->mention_channels,
  /* discord/channel.json:196:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */
                discord_attachment_list_to_json, p->attachments,
  /* discord/channel.json:197:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
                discord_embed_list_to_json, p->embeds,
  /* discord/channel.json:198:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
                discord_reaction_list_to_json, p->reactions,
  /* discord/channel.json:199:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
                p->nonce,
  /* discord/channel.json:200:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
                &p->pinned,
  /* discord/channel.json:201:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
                cee_u64tostr, &p->webhook_id,
  /* discord/channel.json:202:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
                &p->type,
  /* discord/channel.json:203:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
                discord_message_activity_to_json, p->activity,
  /* discord/channel.json:204:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
                discord_message_application_list_to_json, p->application,
  /* discord/channel.json:205:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
                discord_message_reference_to_json, p->message_reference,
  /* discord/channel.json:206:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
                &p->flags,
  /* discord/channel.json:207:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
                discord_message_to_json, p->referenced_message,
  /* discord/channel.json:208:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
                discord_message_interaction_to_json, p->interaction,
  /* discord/channel.json:209:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
                discord_channel_to_json, p->thread,
  /* discord/channel.json:210:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
                discord_component_list_to_json, p->components,
  /* discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
                discord_message_sticker_list_to_json, p->sticker_items,
  /* discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
                discord_message_sticker_list_to_json, p->stickers,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_message_cleanup_v(void *p) {
  discord_message_cleanup((struct discord_message *)p);
}

void discord_message_init_v(void *p) {
  discord_message_init((struct discord_message *)p);
}

void discord_message_from_json_v(char *json, size_t len, void *p) {
 discord_message_from_json(json, len, (struct discord_message*)p);
}

size_t discord_message_to_json_v(char *json, size_t len, void *p) {
  return discord_message_to_json(json, len, (struct discord_message*)p);
}

void discord_message_list_free_v(void **p) {
  discord_message_list_free((struct discord_message**)p);
}

void discord_message_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_list_from_json(str, len, (struct discord_message ***)p);
}

size_t discord_message_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_list_to_json(str, len, (struct discord_message **)p);
}


void discord_message_cleanup(struct discord_message *d) {
  /* discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  (void)d->id;
  /* discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
  (void)d->channel_id;
  /* discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
  (void)d->guild_id;
  /* discord/channel.json:186:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
  if (d->author) {
    discord_user_cleanup(d->author);
    free(d->author);
  }
  /* discord/channel.json:187:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
  if (d->member) {
    discord_guild_member_cleanup(d->member);
    free(d->member);
  }
  /* discord/channel.json:188:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
  if (d->content)
    free(d->content);
  /* discord/channel.json:189:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
  (void)d->timestamp;
  /* discord/channel.json:190:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
  (void)d->edited_timestamp;
  /* discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
  (void)d->tts;
  /* discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
  (void)d->mention_everyone;
  /* discord/channel.json:193:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
  if (d->mentions)
    discord_user_list_free(d->mentions);
  /* discord/channel.json:194:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
  if (d->mention_roles)
    ja_u64_list_free(d->mention_roles);
  /* discord/channel.json:195:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
  if (d->mention_channels)
    discord_channel_mention_list_free(d->mention_channels);
  /* discord/channel.json:196:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* discord/channel.json:197:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* discord/channel.json:198:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
  if (d->reactions)
    discord_reaction_list_free(d->reactions);
  /* discord/channel.json:199:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
  if (d->nonce)
    free(d->nonce);
  /* discord/channel.json:200:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
  (void)d->pinned;
  /* discord/channel.json:201:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
  (void)d->webhook_id;
  /* discord/channel.json:202:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
  (void)d->type;
  /* discord/channel.json:203:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
  if (d->activity) {
    discord_message_activity_cleanup(d->activity);
    free(d->activity);
  }
  /* discord/channel.json:204:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
  if (d->application)
    discord_message_application_list_free(d->application);
  /* discord/channel.json:205:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
  if (d->message_reference) {
    discord_message_reference_cleanup(d->message_reference);
    free(d->message_reference);
  }
  /* discord/channel.json:206:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
  (void)d->flags;
  /* discord/channel.json:207:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
  if (d->referenced_message) {
    discord_message_cleanup(d->referenced_message);
    free(d->referenced_message);
  }
  /* discord/channel.json:208:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
  if (d->interaction) {
    discord_message_interaction_cleanup(d->interaction);
    free(d->interaction);
  }
  /* discord/channel.json:209:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
  if (d->thread) {
    discord_channel_cleanup(d->thread);
    free(d->thread);
  }
  /* discord/channel.json:210:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
  if (d->components)
    discord_component_list_free(d->components);
  /* discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
  if (d->sticker_items)
    discord_message_sticker_list_free(d->sticker_items);
  /* discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
  if (d->stickers)
    discord_message_sticker_list_free(d->stickers);
}

void discord_message_init(struct discord_message *p) {
  memset(p, 0, sizeof(struct discord_message));
  /* discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */

  /* discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */

  /* discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */

  /* discord/channel.json:186:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */

  /* discord/channel.json:187:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */

  /* discord/channel.json:188:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */

  /* discord/channel.json:189:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */

  /* discord/channel.json:190:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */

  /* discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"tts"}' */

  /* discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */

  /* discord/channel.json:193:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */

  /* discord/channel.json:194:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */

  /* discord/channel.json:195:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */

  /* discord/channel.json:196:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */

  /* discord/channel.json:197:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */

  /* discord/channel.json:198:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */

  /* discord/channel.json:199:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */

  /* discord/channel.json:200:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */

  /* discord/channel.json:201:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */

  /* discord/channel.json:202:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */

  /* discord/channel.json:203:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */

  /* discord/channel.json:204:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */

  /* discord/channel.json:205:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */

  /* discord/channel.json:206:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */

  /* discord/channel.json:207:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */

  /* discord/channel.json:208:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */

  /* discord/channel.json:209:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */

  /* discord/channel.json:210:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */

  /* discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */

  /* discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */

}
void discord_message_list_free(struct discord_message **p) {
  ntl_free((void**)p, (void(*)(void*))discord_message_cleanup);
}

void discord_message_list_from_json(char *str, size_t len, struct discord_message ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_message_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_list_to_json(char *str, size_t len, struct discord_message **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_message_to_json);
}


void discord_followed_channel_from_json_p(char *json, size_t len, struct discord_followed_channel **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_followed_channel_from_json(json, len, *pp);
}
void discord_followed_channel_from_json(char *json, size_t len, struct discord_followed_channel *p)
{
  discord_followed_channel_init(p);
  json_extract(json, len, 
  /* discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(channel_id):F,"
  /* discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(webhook_id):F,",
  /* discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->channel_id,
  /* discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->webhook_id);
}

size_t discord_followed_channel_to_json(char *json, size_t len, struct discord_followed_channel *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->channel_id;

  /* discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[1] = &p->webhook_id;

  r=json_inject(json, len, 
  /* discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(channel_id):|F|,"
  /* discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(webhook_id):|F|,"
                "@arg_switches:b",
  /* discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->channel_id,
  /* discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->webhook_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_followed_channel_cleanup_v(void *p) {
  discord_followed_channel_cleanup((struct discord_followed_channel *)p);
}

void discord_followed_channel_init_v(void *p) {
  discord_followed_channel_init((struct discord_followed_channel *)p);
}

void discord_followed_channel_from_json_v(char *json, size_t len, void *p) {
 discord_followed_channel_from_json(json, len, (struct discord_followed_channel*)p);
}

size_t discord_followed_channel_to_json_v(char *json, size_t len, void *p) {
  return discord_followed_channel_to_json(json, len, (struct discord_followed_channel*)p);
}

void discord_followed_channel_list_free_v(void **p) {
  discord_followed_channel_list_free((struct discord_followed_channel**)p);
}

void discord_followed_channel_list_from_json_v(char *str, size_t len, void *p) {
  discord_followed_channel_list_from_json(str, len, (struct discord_followed_channel ***)p);
}

size_t discord_followed_channel_list_to_json_v(char *str, size_t len, void *p){
  return discord_followed_channel_list_to_json(str, len, (struct discord_followed_channel **)p);
}


void discord_followed_channel_cleanup(struct discord_followed_channel *d) {
  /* discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->channel_id;
  /* discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->webhook_id;
}

void discord_followed_channel_init(struct discord_followed_channel *p) {
  memset(p, 0, sizeof(struct discord_followed_channel));
  /* discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

}
void discord_followed_channel_list_free(struct discord_followed_channel **p) {
  ntl_free((void**)p, (void(*)(void*))discord_followed_channel_cleanup);
}

void discord_followed_channel_list_from_json(char *str, size_t len, struct discord_followed_channel ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_followed_channel);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_followed_channel_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_followed_channel_list_to_json(char *str, size_t len, struct discord_followed_channel **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_followed_channel_to_json);
}


void discord_reaction_from_json_p(char *json, size_t len, struct discord_reaction **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_reaction_from_json(json, len, *pp);
}
void discord_reaction_from_json(char *json, size_t len, struct discord_reaction *p)
{
  discord_reaction_init(p);
  json_extract(json, len, 
  /* discord/channel.json:231:20
     '{ "name": "count", "type":{ "base":"int" }}' */
                "(count):d,"
  /* discord/channel.json:232:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
                "(me):b,"
  /* discord/channel.json:233:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
                "(emoji):F,",
  /* discord/channel.json:231:20
     '{ "name": "count", "type":{ "base":"int" }}' */
                &p->count,
  /* discord/channel.json:232:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
                &p->me,
  /* discord/channel.json:233:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
                discord_emoji_from_json_p, &p->emoji);
}

size_t discord_reaction_to_json(char *json, size_t len, struct discord_reaction *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/channel.json:231:20
     '{ "name": "count", "type":{ "base":"int" }}' */
  arg_switches[0] = &p->count;

  /* discord/channel.json:232:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
  arg_switches[1] = &p->me;

  /* discord/channel.json:233:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
  arg_switches[2] = p->emoji;

  r=json_inject(json, len, 
  /* discord/channel.json:231:20
     '{ "name": "count", "type":{ "base":"int" }}' */
                "(count):d,"
  /* discord/channel.json:232:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
                "(me):b,"
  /* discord/channel.json:233:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
                "(emoji):F,"
                "@arg_switches:b",
  /* discord/channel.json:231:20
     '{ "name": "count", "type":{ "base":"int" }}' */
                &p->count,
  /* discord/channel.json:232:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
                &p->me,
  /* discord/channel.json:233:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
                discord_emoji_to_json, p->emoji,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_reaction_cleanup_v(void *p) {
  discord_reaction_cleanup((struct discord_reaction *)p);
}

void discord_reaction_init_v(void *p) {
  discord_reaction_init((struct discord_reaction *)p);
}

void discord_reaction_from_json_v(char *json, size_t len, void *p) {
 discord_reaction_from_json(json, len, (struct discord_reaction*)p);
}

size_t discord_reaction_to_json_v(char *json, size_t len, void *p) {
  return discord_reaction_to_json(json, len, (struct discord_reaction*)p);
}

void discord_reaction_list_free_v(void **p) {
  discord_reaction_list_free((struct discord_reaction**)p);
}

void discord_reaction_list_from_json_v(char *str, size_t len, void *p) {
  discord_reaction_list_from_json(str, len, (struct discord_reaction ***)p);
}

size_t discord_reaction_list_to_json_v(char *str, size_t len, void *p){
  return discord_reaction_list_to_json(str, len, (struct discord_reaction **)p);
}


void discord_reaction_cleanup(struct discord_reaction *d) {
  /* discord/channel.json:231:20
     '{ "name": "count", "type":{ "base":"int" }}' */
  (void)d->count;
  /* discord/channel.json:232:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
  (void)d->me;
  /* discord/channel.json:233:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
  if (d->emoji) {
    discord_emoji_cleanup(d->emoji);
    free(d->emoji);
  }
}

void discord_reaction_init(struct discord_reaction *p) {
  memset(p, 0, sizeof(struct discord_reaction));
  /* discord/channel.json:231:20
     '{ "name": "count", "type":{ "base":"int" }}' */

  /* discord/channel.json:232:20
     '{ "name": "me", "type":{ "base":"bool" }}' */

  /* discord/channel.json:233:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */

}
void discord_reaction_list_free(struct discord_reaction **p) {
  ntl_free((void**)p, (void(*)(void*))discord_reaction_cleanup);
}

void discord_reaction_list_from_json(char *str, size_t len, struct discord_reaction ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_reaction);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_reaction_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_reaction_list_to_json(char *str, size_t len, struct discord_reaction **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_reaction_to_json);
}


void discord_overwrite_from_json_p(char *json, size_t len, struct discord_overwrite **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_overwrite_from_json(json, len, *pp);
}
void discord_overwrite_from_json(char *json, size_t len, struct discord_overwrite *p)
{
  discord_overwrite_init(p);
  json_extract(json, len, 
  /* discord/channel.json:241:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* discord/channel.json:242:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* discord/channel.json:243:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
                "(allow):s_as_u64,"
  /* discord/channel.json:244:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
                "(deny):s_as_u64,",
  /* discord/channel.json:241:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->id,
  /* discord/channel.json:242:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* discord/channel.json:243:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
                &p->allow,
  /* discord/channel.json:244:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
                &p->deny);
}

size_t discord_overwrite_to_json(char *json, size_t len, struct discord_overwrite *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:241:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->id;

  /* discord/channel.json:242:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  arg_switches[1] = &p->type;

  /* discord/channel.json:243:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
  arg_switches[2] = &p->allow;

  /* discord/channel.json:244:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
  arg_switches[3] = &p->deny;

  r=json_inject(json, len, 
  /* discord/channel.json:241:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* discord/channel.json:242:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* discord/channel.json:243:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
                "(allow):s_as_u64,"
  /* discord/channel.json:244:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
                "(deny):s_as_u64,"
                "@arg_switches:b",
  /* discord/channel.json:241:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->id,
  /* discord/channel.json:242:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* discord/channel.json:243:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
                &p->allow,
  /* discord/channel.json:244:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
                &p->deny,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_overwrite_cleanup_v(void *p) {
  discord_overwrite_cleanup((struct discord_overwrite *)p);
}

void discord_overwrite_init_v(void *p) {
  discord_overwrite_init((struct discord_overwrite *)p);
}

void discord_overwrite_from_json_v(char *json, size_t len, void *p) {
 discord_overwrite_from_json(json, len, (struct discord_overwrite*)p);
}

size_t discord_overwrite_to_json_v(char *json, size_t len, void *p) {
  return discord_overwrite_to_json(json, len, (struct discord_overwrite*)p);
}

void discord_overwrite_list_free_v(void **p) {
  discord_overwrite_list_free((struct discord_overwrite**)p);
}

void discord_overwrite_list_from_json_v(char *str, size_t len, void *p) {
  discord_overwrite_list_from_json(str, len, (struct discord_overwrite ***)p);
}

size_t discord_overwrite_list_to_json_v(char *str, size_t len, void *p){
  return discord_overwrite_list_to_json(str, len, (struct discord_overwrite **)p);
}


void discord_overwrite_cleanup(struct discord_overwrite *d) {
  /* discord/channel.json:241:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->id;
  /* discord/channel.json:242:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  (void)d->type;
  /* discord/channel.json:243:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
  (void)d->allow;
  /* discord/channel.json:244:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */
  (void)d->deny;
}

void discord_overwrite_init(struct discord_overwrite *p) {
  memset(p, 0, sizeof(struct discord_overwrite));
  /* discord/channel.json:241:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/channel.json:242:20
     '{ "name": "type", "type":{ "base":"int" }}' */

  /* discord/channel.json:243:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */

  /* discord/channel.json:244:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set"}' */

}
void discord_overwrite_list_free(struct discord_overwrite **p) {
  ntl_free((void**)p, (void(*)(void*))discord_overwrite_cleanup);
}

void discord_overwrite_list_from_json(char *str, size_t len, struct discord_overwrite ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_overwrite);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_overwrite_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_overwrite_list_to_json(char *str, size_t len, struct discord_overwrite **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_overwrite_to_json);
}


void discord_thread_metadata_from_json_p(char *json, size_t len, struct discord_thread_metadata **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_thread_metadata_from_json(json, len, *pp);
}
void discord_thread_metadata_from_json(char *json, size_t len, struct discord_thread_metadata *p)
{
  discord_thread_metadata_init(p);
  json_extract(json, len, 
  /* discord/channel.json:254:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
                "(archived):b,"
  /* discord/channel.json:255:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(archiver_id):F,"
  /* discord/channel.json:256:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
                "(auto_archive_duration):d,"
  /* discord/channel.json:257:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(archive_timestamp):F,"
  /* discord/channel.json:258:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
                "(locked):b,",
  /* discord/channel.json:254:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
                &p->archived,
  /* discord/channel.json:255:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->archiver_id,
  /* discord/channel.json:256:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
                &p->auto_archive_duration,
  /* discord/channel.json:257:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->archive_timestamp,
  /* discord/channel.json:258:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
                &p->locked);
}

size_t discord_thread_metadata_to_json(char *json, size_t len, struct discord_thread_metadata *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* discord/channel.json:254:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
  arg_switches[0] = &p->archived;

  /* discord/channel.json:255:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[1] = &p->archiver_id;

  /* discord/channel.json:256:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
  arg_switches[2] = &p->auto_archive_duration;

  /* discord/channel.json:257:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  arg_switches[3] = &p->archive_timestamp;

  /* discord/channel.json:258:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
  arg_switches[4] = &p->locked;

  r=json_inject(json, len, 
  /* discord/channel.json:254:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
                "(archived):b,"
  /* discord/channel.json:255:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(archiver_id):|F|,"
  /* discord/channel.json:256:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
                "(auto_archive_duration):d,"
  /* discord/channel.json:257:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(archive_timestamp):|F|,"
  /* discord/channel.json:258:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
                "(locked):b,"
                "@arg_switches:b",
  /* discord/channel.json:254:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
                &p->archived,
  /* discord/channel.json:255:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->archiver_id,
  /* discord/channel.json:256:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
                &p->auto_archive_duration,
  /* discord/channel.json:257:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->archive_timestamp,
  /* discord/channel.json:258:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
                &p->locked,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_thread_metadata_cleanup_v(void *p) {
  discord_thread_metadata_cleanup((struct discord_thread_metadata *)p);
}

void discord_thread_metadata_init_v(void *p) {
  discord_thread_metadata_init((struct discord_thread_metadata *)p);
}

void discord_thread_metadata_from_json_v(char *json, size_t len, void *p) {
 discord_thread_metadata_from_json(json, len, (struct discord_thread_metadata*)p);
}

size_t discord_thread_metadata_to_json_v(char *json, size_t len, void *p) {
  return discord_thread_metadata_to_json(json, len, (struct discord_thread_metadata*)p);
}

void discord_thread_metadata_list_free_v(void **p) {
  discord_thread_metadata_list_free((struct discord_thread_metadata**)p);
}

void discord_thread_metadata_list_from_json_v(char *str, size_t len, void *p) {
  discord_thread_metadata_list_from_json(str, len, (struct discord_thread_metadata ***)p);
}

size_t discord_thread_metadata_list_to_json_v(char *str, size_t len, void *p){
  return discord_thread_metadata_list_to_json(str, len, (struct discord_thread_metadata **)p);
}


void discord_thread_metadata_cleanup(struct discord_thread_metadata *d) {
  /* discord/channel.json:254:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
  (void)d->archived;
  /* discord/channel.json:255:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->archiver_id;
  /* discord/channel.json:256:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
  (void)d->auto_archive_duration;
  /* discord/channel.json:257:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  (void)d->archive_timestamp;
  /* discord/channel.json:258:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
  (void)d->locked;
}

void discord_thread_metadata_init(struct discord_thread_metadata *p) {
  memset(p, 0, sizeof(struct discord_thread_metadata));
  /* discord/channel.json:254:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */

  /* discord/channel.json:255:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/channel.json:256:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */

  /* discord/channel.json:257:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* discord/channel.json:258:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */

}
void discord_thread_metadata_list_free(struct discord_thread_metadata **p) {
  ntl_free((void**)p, (void(*)(void*))discord_thread_metadata_cleanup);
}

void discord_thread_metadata_list_from_json(char *str, size_t len, struct discord_thread_metadata ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_metadata);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_thread_metadata_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_thread_metadata_list_to_json(char *str, size_t len, struct discord_thread_metadata **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_thread_metadata_to_json);
}


void discord_thread_member_from_json_p(char *json, size_t len, struct discord_thread_member **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_thread_member_from_json(json, len, *pp);
}
void discord_thread_member_from_json(char *json, size_t len, struct discord_thread_member *p)
{
  discord_thread_member_init(p);
  json_extract(json, len, 
  /* discord/channel.json:268:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* discord/channel.json:269:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(user_id):F,"
  /* discord/channel.json:270:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(join_timestamp):F,"
  /* discord/channel.json:271:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
                "(flags):d,",
  /* discord/channel.json:268:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->id,
  /* discord/channel.json:269:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->user_id,
  /* discord/channel.json:270:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->join_timestamp,
  /* discord/channel.json:271:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
                &p->flags);
}

size_t discord_thread_member_to_json(char *json, size_t len, struct discord_thread_member *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:268:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->id;

  /* discord/channel.json:269:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[1] = &p->user_id;

  /* discord/channel.json:270:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  arg_switches[2] = &p->join_timestamp;

  /* discord/channel.json:271:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
  arg_switches[3] = &p->flags;

  r=json_inject(json, len, 
  /* discord/channel.json:268:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* discord/channel.json:269:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(user_id):|F|,"
  /* discord/channel.json:270:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(join_timestamp):|F|,"
  /* discord/channel.json:271:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
                "(flags):d,"
                "@arg_switches:b",
  /* discord/channel.json:268:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->id,
  /* discord/channel.json:269:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->user_id,
  /* discord/channel.json:270:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->join_timestamp,
  /* discord/channel.json:271:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
                &p->flags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_thread_member_cleanup_v(void *p) {
  discord_thread_member_cleanup((struct discord_thread_member *)p);
}

void discord_thread_member_init_v(void *p) {
  discord_thread_member_init((struct discord_thread_member *)p);
}

void discord_thread_member_from_json_v(char *json, size_t len, void *p) {
 discord_thread_member_from_json(json, len, (struct discord_thread_member*)p);
}

size_t discord_thread_member_to_json_v(char *json, size_t len, void *p) {
  return discord_thread_member_to_json(json, len, (struct discord_thread_member*)p);
}

void discord_thread_member_list_free_v(void **p) {
  discord_thread_member_list_free((struct discord_thread_member**)p);
}

void discord_thread_member_list_from_json_v(char *str, size_t len, void *p) {
  discord_thread_member_list_from_json(str, len, (struct discord_thread_member ***)p);
}

size_t discord_thread_member_list_to_json_v(char *str, size_t len, void *p){
  return discord_thread_member_list_to_json(str, len, (struct discord_thread_member **)p);
}


void discord_thread_member_cleanup(struct discord_thread_member *d) {
  /* discord/channel.json:268:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->id;
  /* discord/channel.json:269:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->user_id;
  /* discord/channel.json:270:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  (void)d->join_timestamp;
  /* discord/channel.json:271:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
  (void)d->flags;
}

void discord_thread_member_init(struct discord_thread_member *p) {
  memset(p, 0, sizeof(struct discord_thread_member));
  /* discord/channel.json:268:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/channel.json:269:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/channel.json:270:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* discord/channel.json:271:20
     '{ "name": "flags", "type":{ "base":"int" }}' */

}
void discord_thread_member_list_free(struct discord_thread_member **p) {
  ntl_free((void**)p, (void(*)(void*))discord_thread_member_cleanup);
}

void discord_thread_member_list_from_json(char *str, size_t len, struct discord_thread_member ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_member);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_thread_member_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_thread_member_list_to_json(char *str, size_t len, struct discord_thread_member **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_thread_member_to_json);
}


void discord_attachment_from_json_p(char *json, size_t len, struct discord_attachment **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_attachment_from_json(json, len, *pp);
}
void discord_attachment_from_json(char *json, size_t len, struct discord_attachment *p)
{
  discord_attachment_init(p);
  json_extract(json, len, 
  /* discord/channel.json:282:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */
                "(id):d,"
  /* discord/channel.json:283:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */
                "(filename):?s,"
  /* discord/channel.json:284:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */
                "(description):?s,"
  /* discord/channel.json:285:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */
                "(content_type):?s,"
  /* discord/channel.json:286:20
     '{ "name": "size", "type":{ "base":"size_t" }, "inject_if_not":0, "comment":"size of file in bytes"}' */
                "(size):zu,"
  /* discord/channel.json:287:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */
                "(url):?s,"
  /* discord/channel.json:288:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */
                "(proxy_url):?s,"
  /* discord/channel.json:289:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */
                "(height):d,"
  /* discord/channel.json:290:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */
                "(width):d,"
  /* discord/channel.json:291:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */
                "(ephemeral):b,",
  /* discord/channel.json:282:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */
                &p->id,
  /* discord/channel.json:283:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */
                &p->filename,
  /* discord/channel.json:284:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */
                &p->description,
  /* discord/channel.json:285:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */
                &p->content_type,
  /* discord/channel.json:286:20
     '{ "name": "size", "type":{ "base":"size_t" }, "inject_if_not":0, "comment":"size of file in bytes"}' */
                &p->size,
  /* discord/channel.json:287:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */
                &p->url,
  /* discord/channel.json:288:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */
                &p->proxy_url,
  /* discord/channel.json:289:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */
                &p->height,
  /* discord/channel.json:290:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */
                &p->width,
  /* discord/channel.json:291:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */
                &p->ephemeral);
}

size_t discord_attachment_to_json(char *json, size_t len, struct discord_attachment *p)
{
  size_t r;
  void *arg_switches[11]={NULL};
  /* discord/channel.json:280:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "loc":"multipart", "comment":"the file contents", "inject_if_not":null }' */
  if (p->content != NULL)
    arg_switches[0] = p->content;

  /* discord/channel.json:282:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */
  arg_switches[1] = &p->id;

  /* discord/channel.json:283:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */
  if (p->filename != NULL)
    arg_switches[2] = p->filename;

  /* discord/channel.json:284:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */
  if (p->description != NULL)
    arg_switches[3] = p->description;

  /* discord/channel.json:285:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */
  if (p->content_type != NULL)
    arg_switches[4] = p->content_type;

  /* discord/channel.json:286:20
     '{ "name": "size", "type":{ "base":"size_t" }, "inject_if_not":0, "comment":"size of file in bytes"}' */
  if (p->size != 0)
    arg_switches[5] = &p->size;

  /* discord/channel.json:287:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */
  if (p->url != NULL)
    arg_switches[6] = p->url;

  /* discord/channel.json:288:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */
  if (p->proxy_url != NULL)
    arg_switches[7] = p->proxy_url;

  /* discord/channel.json:289:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */
  if (p->height != 0)
    arg_switches[8] = &p->height;

  /* discord/channel.json:290:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */
  if (p->width != 0)
    arg_switches[9] = &p->width;

  /* discord/channel.json:291:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */
  if (p->ephemeral != false)
    arg_switches[10] = &p->ephemeral;

  r=json_inject(json, len, 
  /* discord/channel.json:282:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */
                "(id):d,"
  /* discord/channel.json:283:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */
                "(filename):s,"
  /* discord/channel.json:284:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */
                "(description):s,"
  /* discord/channel.json:285:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */
                "(content_type):s,"
  /* discord/channel.json:286:20
     '{ "name": "size", "type":{ "base":"size_t" }, "inject_if_not":0, "comment":"size of file in bytes"}' */
                "(size):zu,"
  /* discord/channel.json:287:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */
                "(url):s,"
  /* discord/channel.json:288:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */
                "(proxy_url):s,"
  /* discord/channel.json:289:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */
                "(height):d,"
  /* discord/channel.json:290:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */
                "(width):d,"
  /* discord/channel.json:291:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */
                "(ephemeral):b,"
                "@arg_switches:b",
  /* discord/channel.json:282:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */
                &p->id,
  /* discord/channel.json:283:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */
                p->filename,
  /* discord/channel.json:284:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */
                p->description,
  /* discord/channel.json:285:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */
                p->content_type,
  /* discord/channel.json:286:20
     '{ "name": "size", "type":{ "base":"size_t" }, "inject_if_not":0, "comment":"size of file in bytes"}' */
                &p->size,
  /* discord/channel.json:287:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */
                p->url,
  /* discord/channel.json:288:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */
                p->proxy_url,
  /* discord/channel.json:289:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */
                &p->height,
  /* discord/channel.json:290:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */
                &p->width,
  /* discord/channel.json:291:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */
                &p->ephemeral,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_attachment_cleanup_v(void *p) {
  discord_attachment_cleanup((struct discord_attachment *)p);
}

void discord_attachment_init_v(void *p) {
  discord_attachment_init((struct discord_attachment *)p);
}

void discord_attachment_from_json_v(char *json, size_t len, void *p) {
 discord_attachment_from_json(json, len, (struct discord_attachment*)p);
}

size_t discord_attachment_to_json_v(char *json, size_t len, void *p) {
  return discord_attachment_to_json(json, len, (struct discord_attachment*)p);
}

void discord_attachment_list_free_v(void **p) {
  discord_attachment_list_free((struct discord_attachment**)p);
}

void discord_attachment_list_from_json_v(char *str, size_t len, void *p) {
  discord_attachment_list_from_json(str, len, (struct discord_attachment ***)p);
}

size_t discord_attachment_list_to_json_v(char *str, size_t len, void *p){
  return discord_attachment_list_to_json(str, len, (struct discord_attachment **)p);
}


void discord_attachment_cleanup(struct discord_attachment *d) {
  /* discord/channel.json:280:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "loc":"multipart", "comment":"the file contents", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* discord/channel.json:282:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */
  (void)d->id;
  /* discord/channel.json:283:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */
  if (d->filename)
    free(d->filename);
  /* discord/channel.json:284:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */
  if (d->description)
    free(d->description);
  /* discord/channel.json:285:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */
  if (d->content_type)
    free(d->content_type);
  /* discord/channel.json:286:20
     '{ "name": "size", "type":{ "base":"size_t" }, "inject_if_not":0, "comment":"size of file in bytes"}' */
  (void)d->size;
  /* discord/channel.json:287:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */
  if (d->url)
    free(d->url);
  /* discord/channel.json:288:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */
  if (d->proxy_url)
    free(d->proxy_url);
  /* discord/channel.json:289:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */
  (void)d->height;
  /* discord/channel.json:290:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */
  (void)d->width;
  /* discord/channel.json:291:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */
  (void)d->ephemeral;
}

void discord_attachment_init(struct discord_attachment *p) {
  memset(p, 0, sizeof(struct discord_attachment));
  /* discord/channel.json:280:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "loc":"multipart", "comment":"the file contents", "inject_if_not":null }' */

  /* discord/channel.json:282:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */

  /* discord/channel.json:283:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */

  /* discord/channel.json:284:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */

  /* discord/channel.json:285:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */

  /* discord/channel.json:286:20
     '{ "name": "size", "type":{ "base":"size_t" }, "inject_if_not":0, "comment":"size of file in bytes"}' */

  /* discord/channel.json:287:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */

  /* discord/channel.json:288:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */

  /* discord/channel.json:289:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */

  /* discord/channel.json:290:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */

  /* discord/channel.json:291:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */

}
void discord_attachment_list_free(struct discord_attachment **p) {
  ntl_free((void**)p, (void(*)(void*))discord_attachment_cleanup);
}

void discord_attachment_list_from_json(char *str, size_t len, struct discord_attachment ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_attachment);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_attachment_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_attachment_list_to_json(char *str, size_t len, struct discord_attachment **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_attachment_to_json);
}


void discord_channel_mention_from_json_p(char *json, size_t len, struct discord_channel_mention **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_channel_mention_from_json(json, len, *pp);
}
void discord_channel_mention_from_json(char *json, size_t len, struct discord_channel_mention *p)
{
  discord_channel_mention_init(p);
  json_extract(json, len, 
  /* discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(guild_id):F,"
  /* discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
                "(type):d,"
  /* discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,",
  /* discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->id,
  /* discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->guild_id,
  /* discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
                &p->type,
  /* discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name);
}

size_t discord_channel_mention_to_json(char *json, size_t len, struct discord_channel_mention *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->id;

  /* discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[1] = &p->guild_id;

  /* discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
  arg_switches[2] = &p->type;

  /* discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[3] = p->name;

  r=json_inject(json, len, 
  /* discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(guild_id):|F|,"
  /* discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
                "(type):d,"
  /* discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
                "@arg_switches:b",
  /* discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->id,
  /* discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->guild_id,
  /* discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
                &p->type,
  /* discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_channel_mention_cleanup_v(void *p) {
  discord_channel_mention_cleanup((struct discord_channel_mention *)p);
}

void discord_channel_mention_init_v(void *p) {
  discord_channel_mention_init((struct discord_channel_mention *)p);
}

void discord_channel_mention_from_json_v(char *json, size_t len, void *p) {
 discord_channel_mention_from_json(json, len, (struct discord_channel_mention*)p);
}

size_t discord_channel_mention_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_mention_to_json(json, len, (struct discord_channel_mention*)p);
}

void discord_channel_mention_list_free_v(void **p) {
  discord_channel_mention_list_free((struct discord_channel_mention**)p);
}

void discord_channel_mention_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_mention_list_from_json(str, len, (struct discord_channel_mention ***)p);
}

size_t discord_channel_mention_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_mention_list_to_json(str, len, (struct discord_channel_mention **)p);
}


void discord_channel_mention_cleanup(struct discord_channel_mention *d) {
  /* discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->id;
  /* discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->guild_id;
  /* discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
  (void)d->type;
  /* discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
}

void discord_channel_mention_init(struct discord_channel_mention *p) {
  memset(p, 0, sizeof(struct discord_channel_mention));
  /* discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */

  /* discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

}
void discord_channel_mention_list_free(struct discord_channel_mention **p) {
  ntl_free((void**)p, (void(*)(void*))discord_channel_mention_cleanup);
}

void discord_channel_mention_list_from_json(char *str, size_t len, struct discord_channel_mention ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_mention);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_channel_mention_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_mention_list_to_json(char *str, size_t len, struct discord_channel_mention **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_channel_mention_to_json);
}


void discord_allowed_mentions_from_json_p(char *json, size_t len, struct discord_allowed_mentions **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_allowed_mentions_from_json(json, len, *pp);
}
void discord_allowed_mentions_from_json(char *json, size_t len, struct discord_allowed_mentions *p)
{
  discord_allowed_mentions_init(p);
  json_extract(json, len, 
  /* discord/channel.json:313:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
                "(parse):F,"
  /* discord/channel.json:314:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                "(roles):F,"
  /* discord/channel.json:315:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                "(users):F,"
  /* discord/channel.json:316:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
                "(replied_user):b,",
  /* discord/channel.json:313:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
                ja_str_list_from_json, &p->parse,
  /* discord/channel.json:314:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                ja_u64_list_from_json, &p->roles,
  /* discord/channel.json:315:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                ja_u64_list_from_json, &p->users,
  /* discord/channel.json:316:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
                &p->replied_user);
}

size_t discord_allowed_mentions_to_json(char *json, size_t len, struct discord_allowed_mentions *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:313:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
  arg_switches[0] = p->parse;

  /* discord/channel.json:314:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  arg_switches[1] = p->roles;

  /* discord/channel.json:315:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  arg_switches[2] = p->users;

  /* discord/channel.json:316:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
  arg_switches[3] = &p->replied_user;

  r=json_inject(json, len, 
  /* discord/channel.json:313:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
                "(parse):F,"
  /* discord/channel.json:314:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                "(roles):F,"
  /* discord/channel.json:315:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                "(users):F,"
  /* discord/channel.json:316:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
                "(replied_user):b,"
                "@arg_switches:b",
  /* discord/channel.json:313:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
                ja_str_list_to_json, p->parse,
  /* discord/channel.json:314:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                ja_u64_list_to_json, p->roles,
  /* discord/channel.json:315:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                ja_u64_list_to_json, p->users,
  /* discord/channel.json:316:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
                &p->replied_user,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_allowed_mentions_cleanup_v(void *p) {
  discord_allowed_mentions_cleanup((struct discord_allowed_mentions *)p);
}

void discord_allowed_mentions_init_v(void *p) {
  discord_allowed_mentions_init((struct discord_allowed_mentions *)p);
}

void discord_allowed_mentions_from_json_v(char *json, size_t len, void *p) {
 discord_allowed_mentions_from_json(json, len, (struct discord_allowed_mentions*)p);
}

size_t discord_allowed_mentions_to_json_v(char *json, size_t len, void *p) {
  return discord_allowed_mentions_to_json(json, len, (struct discord_allowed_mentions*)p);
}

void discord_allowed_mentions_list_free_v(void **p) {
  discord_allowed_mentions_list_free((struct discord_allowed_mentions**)p);
}

void discord_allowed_mentions_list_from_json_v(char *str, size_t len, void *p) {
  discord_allowed_mentions_list_from_json(str, len, (struct discord_allowed_mentions ***)p);
}

size_t discord_allowed_mentions_list_to_json_v(char *str, size_t len, void *p){
  return discord_allowed_mentions_list_to_json(str, len, (struct discord_allowed_mentions **)p);
}


void discord_allowed_mentions_cleanup(struct discord_allowed_mentions *d) {
  /* discord/channel.json:313:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
  if (d->parse)
    ja_str_list_free(d->parse);
  /* discord/channel.json:314:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* discord/channel.json:315:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  if (d->users)
    ja_u64_list_free(d->users);
  /* discord/channel.json:316:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
  (void)d->replied_user;
}

void discord_allowed_mentions_init(struct discord_allowed_mentions *p) {
  memset(p, 0, sizeof(struct discord_allowed_mentions));
  /* discord/channel.json:313:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */

  /* discord/channel.json:314:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */

  /* discord/channel.json:315:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */

  /* discord/channel.json:316:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */

}
void discord_allowed_mentions_list_free(struct discord_allowed_mentions **p) {
  ntl_free((void**)p, (void(*)(void*))discord_allowed_mentions_cleanup);
}

void discord_allowed_mentions_list_from_json(char *str, size_t len, struct discord_allowed_mentions ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_allowed_mentions);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_allowed_mentions_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_allowed_mentions_list_to_json(char *str, size_t len, struct discord_allowed_mentions **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_allowed_mentions_to_json);
}


void discord_embed_from_json_p(char *json, size_t len, struct discord_embed **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_embed_from_json(json, len, *pp);
}
void discord_embed_from_json(char *json, size_t len, struct discord_embed *p)
{
  discord_embed_init(p);
  json_extract(json, len, 
  /* discord/channel.json:325:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                "(title):?s,"
  /* discord/channel.json:326:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                "(type):?s,"
  /* discord/channel.json:327:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(description):?s,"
  /* discord/channel.json:328:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(url):?s,"
  /* discord/channel.json:329:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
                "(timestamp):F,"
  /* discord/channel.json:330:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
                "(color):d,"
  /* discord/channel.json:331:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(footer):F,"
  /* discord/channel.json:332:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
                "(image):F,"
  /* discord/channel.json:333:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
                "(thumbnail):F,"
  /* discord/channel.json:334:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
                "(video):F,"
  /* discord/channel.json:335:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
                "(provider):F,"
  /* discord/channel.json:336:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
                "(author):F,"
  /* discord/channel.json:337:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
                "(fields):F,",
  /* discord/channel.json:325:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                &p->title,
  /* discord/channel.json:326:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                &p->type,
  /* discord/channel.json:327:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->description,
  /* discord/channel.json:328:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->url,
  /* discord/channel.json:329:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
                cee_iso8601_to_unix_ms, &p->timestamp,
  /* discord/channel.json:330:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
                &p->color,
  /* discord/channel.json:331:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
                discord_embed_footer_from_json_p, &p->footer,
  /* discord/channel.json:332:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_image_from_json_p, &p->image,
  /* discord/channel.json:333:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_thumbnail_from_json_p, &p->thumbnail,
  /* discord/channel.json:334:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_video_from_json_p, &p->video,
  /* discord/channel.json:335:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_provider_from_json_p, &p->provider,
  /* discord/channel.json:336:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_author_from_json_p, &p->author,
  /* discord/channel.json:337:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
                discord_embed_field_list_from_json, &p->fields);
}

size_t discord_embed_to_json(char *json, size_t len, struct discord_embed *p)
{
  size_t r;
  void *arg_switches[13]={NULL};
  /* discord/channel.json:325:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  if (p->title != NULL)
    arg_switches[0] = p->title;

  /* discord/channel.json:326:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  if (p->type != NULL)
    arg_switches[1] = p->type;

  /* discord/channel.json:327:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->description != NULL)
    arg_switches[2] = p->description;

  /* discord/channel.json:328:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->url != NULL)
    arg_switches[3] = p->url;

  /* discord/channel.json:329:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
  if (p->timestamp != 0)
    arg_switches[4] = &p->timestamp;

  /* discord/channel.json:330:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
  if (p->color != 0)
    arg_switches[5] = &p->color;

  /* discord/channel.json:331:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->footer != NULL)
    arg_switches[6] = p->footer;

  /* discord/channel.json:332:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
  if (p->image != NULL)
    arg_switches[7] = p->image;

  /* discord/channel.json:333:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
  if (p->thumbnail != NULL)
    arg_switches[8] = p->thumbnail;

  /* discord/channel.json:334:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
  if (p->video != NULL)
    arg_switches[9] = p->video;

  /* discord/channel.json:335:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
  if (p->provider != NULL)
    arg_switches[10] = p->provider;

  /* discord/channel.json:336:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
  if (p->author != NULL)
    arg_switches[11] = p->author;

  /* discord/channel.json:337:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
  if (p->fields != NULL)
    arg_switches[12] = p->fields;

  r=json_inject(json, len, 
  /* discord/channel.json:325:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                "(title):s,"
  /* discord/channel.json:326:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                "(type):s,"
  /* discord/channel.json:327:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(description):s,"
  /* discord/channel.json:328:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(url):s,"
  /* discord/channel.json:329:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
                "(timestamp):|F|,"
  /* discord/channel.json:330:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
                "(color):d,"
  /* discord/channel.json:331:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(footer):F,"
  /* discord/channel.json:332:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
                "(image):F,"
  /* discord/channel.json:333:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
                "(thumbnail):F,"
  /* discord/channel.json:334:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
                "(video):F,"
  /* discord/channel.json:335:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
                "(provider):F,"
  /* discord/channel.json:336:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
                "(author):F,"
  /* discord/channel.json:337:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
                "(fields):F,"
                "@arg_switches:b",
  /* discord/channel.json:325:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                p->title,
  /* discord/channel.json:326:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                p->type,
  /* discord/channel.json:327:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->description,
  /* discord/channel.json:328:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->url,
  /* discord/channel.json:329:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
                cee_unix_ms_to_iso8601, &p->timestamp,
  /* discord/channel.json:330:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
                &p->color,
  /* discord/channel.json:331:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
                discord_embed_footer_to_json, p->footer,
  /* discord/channel.json:332:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_image_to_json, p->image,
  /* discord/channel.json:333:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_thumbnail_to_json, p->thumbnail,
  /* discord/channel.json:334:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_video_to_json, p->video,
  /* discord/channel.json:335:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_provider_to_json, p->provider,
  /* discord/channel.json:336:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_author_to_json, p->author,
  /* discord/channel.json:337:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
                discord_embed_field_list_to_json, p->fields,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_embed_cleanup_v(void *p) {
  discord_embed_cleanup((struct discord_embed *)p);
}

void discord_embed_init_v(void *p) {
  discord_embed_init((struct discord_embed *)p);
}

void discord_embed_from_json_v(char *json, size_t len, void *p) {
 discord_embed_from_json(json, len, (struct discord_embed*)p);
}

size_t discord_embed_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_to_json(json, len, (struct discord_embed*)p);
}

void discord_embed_list_free_v(void **p) {
  discord_embed_list_free((struct discord_embed**)p);
}

void discord_embed_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_list_from_json(str, len, (struct discord_embed ***)p);
}

size_t discord_embed_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_list_to_json(str, len, (struct discord_embed **)p);
}


void discord_embed_cleanup(struct discord_embed *d) {
  /* discord/channel.json:325:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  if (d->title)
    free(d->title);
  /* discord/channel.json:326:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  if (d->type)
    free(d->type);
  /* discord/channel.json:327:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->description)
    free(d->description);
  /* discord/channel.json:328:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* discord/channel.json:329:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
  (void)d->timestamp;
  /* discord/channel.json:330:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
  (void)d->color;
  /* discord/channel.json:331:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->footer) {
    discord_embed_footer_cleanup(d->footer);
    free(d->footer);
  }
  /* discord/channel.json:332:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
  if (d->image) {
    discord_embed_image_cleanup(d->image);
    free(d->image);
  }
  /* discord/channel.json:333:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
  if (d->thumbnail) {
    discord_embed_thumbnail_cleanup(d->thumbnail);
    free(d->thumbnail);
  }
  /* discord/channel.json:334:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
  if (d->video) {
    discord_embed_video_cleanup(d->video);
    free(d->video);
  }
  /* discord/channel.json:335:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
  if (d->provider) {
    discord_embed_provider_cleanup(d->provider);
    free(d->provider);
  }
  /* discord/channel.json:336:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
  if (d->author) {
    discord_embed_author_cleanup(d->author);
    free(d->author);
  }
  /* discord/channel.json:337:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
  if (d->fields)
    discord_embed_field_list_free(d->fields);
}

void discord_embed_init(struct discord_embed *p) {
  memset(p, 0, sizeof(struct discord_embed));
  /* discord/channel.json:325:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */

  /* discord/channel.json:326:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */

  /* discord/channel.json:327:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* discord/channel.json:328:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* discord/channel.json:329:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */

  /* discord/channel.json:330:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */

  /* discord/channel.json:331:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* discord/channel.json:332:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */

  /* discord/channel.json:333:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */

  /* discord/channel.json:334:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */

  /* discord/channel.json:335:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */

  /* discord/channel.json:336:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */

  /* discord/channel.json:337:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */

}
void discord_embed_list_free(struct discord_embed **p) {
  ntl_free((void**)p, (void(*)(void*))discord_embed_cleanup);
}

void discord_embed_list_from_json(char *str, size_t len, struct discord_embed ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_embed_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_list_to_json(char *str, size_t len, struct discord_embed **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_embed_to_json);
}


void discord_embed_thumbnail_from_json_p(char *json, size_t len, struct discord_embed_thumbnail **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_embed_thumbnail_from_json(json, len, *pp);
}
void discord_embed_thumbnail_from_json(char *json, size_t len, struct discord_embed_thumbnail *p)
{
  discord_embed_thumbnail_init(p);
  json_extract(json, len, 
  /* discord/channel.json:346:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):?s,"
  /* discord/channel.json:347:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):?s,"
  /* discord/channel.json:348:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* discord/channel.json:349:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,",
  /* discord/channel.json:346:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->url,
  /* discord/channel.json:347:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->proxy_url,
  /* discord/channel.json:348:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* discord/channel.json:349:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width);
}

size_t discord_embed_thumbnail_to_json(char *json, size_t len, struct discord_embed_thumbnail *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:346:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->url != NULL)
    arg_switches[0] = p->url;

  /* discord/channel.json:347:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->proxy_url != NULL)
    arg_switches[1] = p->proxy_url;

  /* discord/channel.json:348:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->height != 0)
    arg_switches[2] = &p->height;

  /* discord/channel.json:349:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->width != 0)
    arg_switches[3] = &p->width;

  r=json_inject(json, len, 
  /* discord/channel.json:346:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):s,"
  /* discord/channel.json:347:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):s,"
  /* discord/channel.json:348:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* discord/channel.json:349:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b",
  /* discord/channel.json:346:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->url,
  /* discord/channel.json:347:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->proxy_url,
  /* discord/channel.json:348:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* discord/channel.json:349:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_embed_thumbnail_cleanup_v(void *p) {
  discord_embed_thumbnail_cleanup((struct discord_embed_thumbnail *)p);
}

void discord_embed_thumbnail_init_v(void *p) {
  discord_embed_thumbnail_init((struct discord_embed_thumbnail *)p);
}

void discord_embed_thumbnail_from_json_v(char *json, size_t len, void *p) {
 discord_embed_thumbnail_from_json(json, len, (struct discord_embed_thumbnail*)p);
}

size_t discord_embed_thumbnail_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_thumbnail_to_json(json, len, (struct discord_embed_thumbnail*)p);
}

void discord_embed_thumbnail_list_free_v(void **p) {
  discord_embed_thumbnail_list_free((struct discord_embed_thumbnail**)p);
}

void discord_embed_thumbnail_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_thumbnail_list_from_json(str, len, (struct discord_embed_thumbnail ***)p);
}

size_t discord_embed_thumbnail_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_thumbnail_list_to_json(str, len, (struct discord_embed_thumbnail **)p);
}


void discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *d) {
  /* discord/channel.json:346:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* discord/channel.json:347:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->proxy_url)
    free(d->proxy_url);
  /* discord/channel.json:348:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->height;
  /* discord/channel.json:349:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->width;
}

void discord_embed_thumbnail_init(struct discord_embed_thumbnail *p) {
  memset(p, 0, sizeof(struct discord_embed_thumbnail));
  /* discord/channel.json:346:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:347:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:348:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/channel.json:349:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */

}
void discord_embed_thumbnail_list_free(struct discord_embed_thumbnail **p) {
  ntl_free((void**)p, (void(*)(void*))discord_embed_thumbnail_cleanup);
}

void discord_embed_thumbnail_list_from_json(char *str, size_t len, struct discord_embed_thumbnail ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_thumbnail);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_embed_thumbnail_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_thumbnail_list_to_json(char *str, size_t len, struct discord_embed_thumbnail **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_embed_thumbnail_to_json);
}


void discord_embed_video_from_json_p(char *json, size_t len, struct discord_embed_video **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_embed_video_from_json(json, len, *pp);
}
void discord_embed_video_from_json(char *json, size_t len, struct discord_embed_video *p)
{
  discord_embed_video_init(p);
  json_extract(json, len, 
  /* discord/channel.json:358:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):?s,"
  /* discord/channel.json:359:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):?s,"
  /* discord/channel.json:360:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* discord/channel.json:361:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,",
  /* discord/channel.json:358:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->url,
  /* discord/channel.json:359:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->proxy_url,
  /* discord/channel.json:360:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* discord/channel.json:361:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width);
}

size_t discord_embed_video_to_json(char *json, size_t len, struct discord_embed_video *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:358:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->url != NULL)
    arg_switches[0] = p->url;

  /* discord/channel.json:359:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->proxy_url != NULL)
    arg_switches[1] = p->proxy_url;

  /* discord/channel.json:360:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->height != 0)
    arg_switches[2] = &p->height;

  /* discord/channel.json:361:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->width != 0)
    arg_switches[3] = &p->width;

  r=json_inject(json, len, 
  /* discord/channel.json:358:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):s,"
  /* discord/channel.json:359:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):s,"
  /* discord/channel.json:360:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* discord/channel.json:361:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b",
  /* discord/channel.json:358:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->url,
  /* discord/channel.json:359:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->proxy_url,
  /* discord/channel.json:360:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* discord/channel.json:361:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_embed_video_cleanup_v(void *p) {
  discord_embed_video_cleanup((struct discord_embed_video *)p);
}

void discord_embed_video_init_v(void *p) {
  discord_embed_video_init((struct discord_embed_video *)p);
}

void discord_embed_video_from_json_v(char *json, size_t len, void *p) {
 discord_embed_video_from_json(json, len, (struct discord_embed_video*)p);
}

size_t discord_embed_video_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_video_to_json(json, len, (struct discord_embed_video*)p);
}

void discord_embed_video_list_free_v(void **p) {
  discord_embed_video_list_free((struct discord_embed_video**)p);
}

void discord_embed_video_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_video_list_from_json(str, len, (struct discord_embed_video ***)p);
}

size_t discord_embed_video_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_video_list_to_json(str, len, (struct discord_embed_video **)p);
}


void discord_embed_video_cleanup(struct discord_embed_video *d) {
  /* discord/channel.json:358:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* discord/channel.json:359:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->proxy_url)
    free(d->proxy_url);
  /* discord/channel.json:360:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->height;
  /* discord/channel.json:361:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->width;
}

void discord_embed_video_init(struct discord_embed_video *p) {
  memset(p, 0, sizeof(struct discord_embed_video));
  /* discord/channel.json:358:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:359:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:360:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/channel.json:361:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */

}
void discord_embed_video_list_free(struct discord_embed_video **p) {
  ntl_free((void**)p, (void(*)(void*))discord_embed_video_cleanup);
}

void discord_embed_video_list_from_json(char *str, size_t len, struct discord_embed_video ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_video);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_embed_video_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_video_list_to_json(char *str, size_t len, struct discord_embed_video **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_embed_video_to_json);
}


void discord_embed_image_from_json_p(char *json, size_t len, struct discord_embed_image **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_embed_image_from_json(json, len, *pp);
}
void discord_embed_image_from_json(char *json, size_t len, struct discord_embed_image *p)
{
  discord_embed_image_init(p);
  json_extract(json, len, 
  /* discord/channel.json:370:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):?s,"
  /* discord/channel.json:371:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):?s,"
  /* discord/channel.json:372:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* discord/channel.json:373:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,",
  /* discord/channel.json:370:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->url,
  /* discord/channel.json:371:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->proxy_url,
  /* discord/channel.json:372:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* discord/channel.json:373:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width);
}

size_t discord_embed_image_to_json(char *json, size_t len, struct discord_embed_image *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:370:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->url != NULL)
    arg_switches[0] = p->url;

  /* discord/channel.json:371:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->proxy_url != NULL)
    arg_switches[1] = p->proxy_url;

  /* discord/channel.json:372:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->height != 0)
    arg_switches[2] = &p->height;

  /* discord/channel.json:373:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->width != 0)
    arg_switches[3] = &p->width;

  r=json_inject(json, len, 
  /* discord/channel.json:370:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):s,"
  /* discord/channel.json:371:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):s,"
  /* discord/channel.json:372:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* discord/channel.json:373:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b",
  /* discord/channel.json:370:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->url,
  /* discord/channel.json:371:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->proxy_url,
  /* discord/channel.json:372:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* discord/channel.json:373:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_embed_image_cleanup_v(void *p) {
  discord_embed_image_cleanup((struct discord_embed_image *)p);
}

void discord_embed_image_init_v(void *p) {
  discord_embed_image_init((struct discord_embed_image *)p);
}

void discord_embed_image_from_json_v(char *json, size_t len, void *p) {
 discord_embed_image_from_json(json, len, (struct discord_embed_image*)p);
}

size_t discord_embed_image_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_image_to_json(json, len, (struct discord_embed_image*)p);
}

void discord_embed_image_list_free_v(void **p) {
  discord_embed_image_list_free((struct discord_embed_image**)p);
}

void discord_embed_image_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_image_list_from_json(str, len, (struct discord_embed_image ***)p);
}

size_t discord_embed_image_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_image_list_to_json(str, len, (struct discord_embed_image **)p);
}


void discord_embed_image_cleanup(struct discord_embed_image *d) {
  /* discord/channel.json:370:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* discord/channel.json:371:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->proxy_url)
    free(d->proxy_url);
  /* discord/channel.json:372:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->height;
  /* discord/channel.json:373:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->width;
}

void discord_embed_image_init(struct discord_embed_image *p) {
  memset(p, 0, sizeof(struct discord_embed_image));
  /* discord/channel.json:370:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:371:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:372:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/channel.json:373:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */

}
void discord_embed_image_list_free(struct discord_embed_image **p) {
  ntl_free((void**)p, (void(*)(void*))discord_embed_image_cleanup);
}

void discord_embed_image_list_from_json(char *str, size_t len, struct discord_embed_image ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_image);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_embed_image_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_image_list_to_json(char *str, size_t len, struct discord_embed_image **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_embed_image_to_json);
}


void discord_embed_provider_from_json_p(char *json, size_t len, struct discord_embed_provider **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_embed_provider_from_json(json, len, *pp);
}
void discord_embed_provider_from_json(char *json, size_t len, struct discord_embed_provider *p)
{
  discord_embed_provider_init(p);
  json_extract(json, len, 
  /* discord/channel.json:382:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(name):?s,"
  /* discord/channel.json:383:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(url):?s,",
  /* discord/channel.json:382:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                &p->name,
  /* discord/channel.json:383:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                &p->url);
}

size_t discord_embed_provider_to_json(char *json, size_t len, struct discord_embed_provider *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/channel.json:382:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/channel.json:383:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (p->url != NULL)
    arg_switches[1] = p->url;

  r=json_inject(json, len, 
  /* discord/channel.json:382:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(name):s,"
  /* discord/channel.json:383:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(url):s,"
                "@arg_switches:b",
  /* discord/channel.json:382:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                p->name,
  /* discord/channel.json:383:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                p->url,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_embed_provider_cleanup_v(void *p) {
  discord_embed_provider_cleanup((struct discord_embed_provider *)p);
}

void discord_embed_provider_init_v(void *p) {
  discord_embed_provider_init((struct discord_embed_provider *)p);
}

void discord_embed_provider_from_json_v(char *json, size_t len, void *p) {
 discord_embed_provider_from_json(json, len, (struct discord_embed_provider*)p);
}

size_t discord_embed_provider_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_provider_to_json(json, len, (struct discord_embed_provider*)p);
}

void discord_embed_provider_list_free_v(void **p) {
  discord_embed_provider_list_free((struct discord_embed_provider**)p);
}

void discord_embed_provider_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_provider_list_from_json(str, len, (struct discord_embed_provider ***)p);
}

size_t discord_embed_provider_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_provider_list_to_json(str, len, (struct discord_embed_provider **)p);
}


void discord_embed_provider_cleanup(struct discord_embed_provider *d) {
  /* discord/channel.json:382:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (d->name)
    free(d->name);
  /* discord/channel.json:383:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
}

void discord_embed_provider_init(struct discord_embed_provider *p) {
  memset(p, 0, sizeof(struct discord_embed_provider));
  /* discord/channel.json:382:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */

  /* discord/channel.json:383:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */

}
void discord_embed_provider_list_free(struct discord_embed_provider **p) {
  ntl_free((void**)p, (void(*)(void*))discord_embed_provider_cleanup);
}

void discord_embed_provider_list_from_json(char *str, size_t len, struct discord_embed_provider ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_provider);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_embed_provider_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_provider_list_to_json(char *str, size_t len, struct discord_embed_provider **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_embed_provider_to_json);
}


void discord_embed_author_from_json_p(char *json, size_t len, struct discord_embed_author **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_embed_author_from_json(json, len, *pp);
}
void discord_embed_author_from_json(char *json, size_t len, struct discord_embed_author *p)
{
  discord_embed_author_init(p);
  json_extract(json, len, 
  /* discord/channel.json:392:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(name):?s,"
  /* discord/channel.json:393:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):?s,"
  /* discord/channel.json:394:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(icon_url):?s,"
  /* discord/channel.json:395:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_icon_url):?s,",
  /* discord/channel.json:392:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->name,
  /* discord/channel.json:393:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->url,
  /* discord/channel.json:394:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->icon_url,
  /* discord/channel.json:395:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->proxy_icon_url);
}

size_t discord_embed_author_to_json(char *json, size_t len, struct discord_embed_author *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.json:392:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/channel.json:393:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->url != NULL)
    arg_switches[1] = p->url;

  /* discord/channel.json:394:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->icon_url != NULL)
    arg_switches[2] = p->icon_url;

  /* discord/channel.json:395:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->proxy_icon_url != NULL)
    arg_switches[3] = p->proxy_icon_url;

  r=json_inject(json, len, 
  /* discord/channel.json:392:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(name):s,"
  /* discord/channel.json:393:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):s,"
  /* discord/channel.json:394:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(icon_url):s,"
  /* discord/channel.json:395:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* discord/channel.json:392:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->name,
  /* discord/channel.json:393:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->url,
  /* discord/channel.json:394:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->icon_url,
  /* discord/channel.json:395:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->proxy_icon_url,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_embed_author_cleanup_v(void *p) {
  discord_embed_author_cleanup((struct discord_embed_author *)p);
}

void discord_embed_author_init_v(void *p) {
  discord_embed_author_init((struct discord_embed_author *)p);
}

void discord_embed_author_from_json_v(char *json, size_t len, void *p) {
 discord_embed_author_from_json(json, len, (struct discord_embed_author*)p);
}

size_t discord_embed_author_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_author_to_json(json, len, (struct discord_embed_author*)p);
}

void discord_embed_author_list_free_v(void **p) {
  discord_embed_author_list_free((struct discord_embed_author**)p);
}

void discord_embed_author_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_author_list_from_json(str, len, (struct discord_embed_author ***)p);
}

size_t discord_embed_author_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_author_list_to_json(str, len, (struct discord_embed_author **)p);
}


void discord_embed_author_cleanup(struct discord_embed_author *d) {
  /* discord/channel.json:392:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->name)
    free(d->name);
  /* discord/channel.json:393:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* discord/channel.json:394:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->icon_url)
    free(d->icon_url);
  /* discord/channel.json:395:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->proxy_icon_url)
    free(d->proxy_icon_url);
}

void discord_embed_author_init(struct discord_embed_author *p) {
  memset(p, 0, sizeof(struct discord_embed_author));
  /* discord/channel.json:392:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:393:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:394:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:395:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

}
void discord_embed_author_list_free(struct discord_embed_author **p) {
  ntl_free((void**)p, (void(*)(void*))discord_embed_author_cleanup);
}

void discord_embed_author_list_from_json(char *str, size_t len, struct discord_embed_author ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_author);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_embed_author_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_author_list_to_json(char *str, size_t len, struct discord_embed_author **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_embed_author_to_json);
}


void discord_embed_footer_from_json_p(char *json, size_t len, struct discord_embed_footer **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_embed_footer_from_json(json, len, *pp);
}
void discord_embed_footer_from_json(char *json, size_t len, struct discord_embed_footer *p)
{
  discord_embed_footer_init(p);
  json_extract(json, len, 
  /* discord/channel.json:404:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(text):?s,"
  /* discord/channel.json:405:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                "(icon_url):?s,"
  /* discord/channel.json:406:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(proxy_icon_url):?s,",
  /* discord/channel.json:404:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */
                &p->text,
  /* discord/channel.json:405:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                &p->icon_url,
  /* discord/channel.json:406:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->proxy_icon_url);
}

size_t discord_embed_footer_to_json(char *json, size_t len, struct discord_embed_footer *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/channel.json:404:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (p->text != NULL)
    arg_switches[0] = p->text;

  /* discord/channel.json:405:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  if (p->icon_url != NULL)
    arg_switches[1] = p->icon_url;

  /* discord/channel.json:406:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->proxy_icon_url != NULL)
    arg_switches[2] = p->proxy_icon_url;

  r=json_inject(json, len, 
  /* discord/channel.json:404:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(text):s,"
  /* discord/channel.json:405:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                "(icon_url):s,"
  /* discord/channel.json:406:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* discord/channel.json:404:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */
                p->text,
  /* discord/channel.json:405:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                p->icon_url,
  /* discord/channel.json:406:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->proxy_icon_url,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_embed_footer_cleanup_v(void *p) {
  discord_embed_footer_cleanup((struct discord_embed_footer *)p);
}

void discord_embed_footer_init_v(void *p) {
  discord_embed_footer_init((struct discord_embed_footer *)p);
}

void discord_embed_footer_from_json_v(char *json, size_t len, void *p) {
 discord_embed_footer_from_json(json, len, (struct discord_embed_footer*)p);
}

size_t discord_embed_footer_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_footer_to_json(json, len, (struct discord_embed_footer*)p);
}

void discord_embed_footer_list_free_v(void **p) {
  discord_embed_footer_list_free((struct discord_embed_footer**)p);
}

void discord_embed_footer_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_footer_list_from_json(str, len, (struct discord_embed_footer ***)p);
}

size_t discord_embed_footer_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_footer_list_to_json(str, len, (struct discord_embed_footer **)p);
}


void discord_embed_footer_cleanup(struct discord_embed_footer *d) {
  /* discord/channel.json:404:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (d->text)
    free(d->text);
  /* discord/channel.json:405:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  if (d->icon_url)
    free(d->icon_url);
  /* discord/channel.json:406:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->proxy_icon_url)
    free(d->proxy_icon_url);
}

void discord_embed_footer_init(struct discord_embed_footer *p) {
  memset(p, 0, sizeof(struct discord_embed_footer));
  /* discord/channel.json:404:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */

  /* discord/channel.json:405:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */

  /* discord/channel.json:406:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

}
void discord_embed_footer_list_free(struct discord_embed_footer **p) {
  ntl_free((void**)p, (void(*)(void*))discord_embed_footer_cleanup);
}

void discord_embed_footer_list_from_json(char *str, size_t len, struct discord_embed_footer ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_footer);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_embed_footer_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_footer_list_to_json(char *str, size_t len, struct discord_embed_footer **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_embed_footer_to_json);
}


void discord_embed_field_from_json_p(char *json, size_t len, struct discord_embed_field **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_embed_field_from_json(json, len, *pp);
}
void discord_embed_field_from_json(char *json, size_t len, struct discord_embed_field *p)
{
  discord_embed_field_init(p);
  json_extract(json, len, 
  /* discord/channel.json:415:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(name):?s,"
  /* discord/channel.json:416:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(value):?s,"
  /* discord/channel.json:417:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
                "(inline):b,",
  /* discord/channel.json:415:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->name,
  /* discord/channel.json:416:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->value,
  /* discord/channel.json:417:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
                &p->Inline);
}

size_t discord_embed_field_to_json(char *json, size_t len, struct discord_embed_field *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/channel.json:415:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/channel.json:416:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->value != NULL)
    arg_switches[1] = p->value;

  /* discord/channel.json:417:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
  arg_switches[2] = &p->Inline;

  r=json_inject(json, len, 
  /* discord/channel.json:415:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(name):s,"
  /* discord/channel.json:416:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(value):s,"
  /* discord/channel.json:417:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
                "(inline):b,"
                "@arg_switches:b",
  /* discord/channel.json:415:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->name,
  /* discord/channel.json:416:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->value,
  /* discord/channel.json:417:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
                &p->Inline,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_embed_field_cleanup_v(void *p) {
  discord_embed_field_cleanup((struct discord_embed_field *)p);
}

void discord_embed_field_init_v(void *p) {
  discord_embed_field_init((struct discord_embed_field *)p);
}

void discord_embed_field_from_json_v(char *json, size_t len, void *p) {
 discord_embed_field_from_json(json, len, (struct discord_embed_field*)p);
}

size_t discord_embed_field_to_json_v(char *json, size_t len, void *p) {
  return discord_embed_field_to_json(json, len, (struct discord_embed_field*)p);
}

void discord_embed_field_list_free_v(void **p) {
  discord_embed_field_list_free((struct discord_embed_field**)p);
}

void discord_embed_field_list_from_json_v(char *str, size_t len, void *p) {
  discord_embed_field_list_from_json(str, len, (struct discord_embed_field ***)p);
}

size_t discord_embed_field_list_to_json_v(char *str, size_t len, void *p){
  return discord_embed_field_list_to_json(str, len, (struct discord_embed_field **)p);
}


void discord_embed_field_cleanup(struct discord_embed_field *d) {
  /* discord/channel.json:415:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->name)
    free(d->name);
  /* discord/channel.json:416:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->value)
    free(d->value);
  /* discord/channel.json:417:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
  (void)d->Inline;
}

void discord_embed_field_init(struct discord_embed_field *p) {
  memset(p, 0, sizeof(struct discord_embed_field));
  /* discord/channel.json:415:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:416:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/channel.json:417:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */

}
void discord_embed_field_list_free(struct discord_embed_field **p) {
  ntl_free((void**)p, (void(*)(void*))discord_embed_field_cleanup);
}

void discord_embed_field_list_from_json(char *str, size_t len, struct discord_embed_field ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_field);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_embed_field_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_field_list_to_json(char *str, size_t len, struct discord_embed_field **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_embed_field_to_json);
}

