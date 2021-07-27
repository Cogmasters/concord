/* This file is generated from specs/discord/channel.json, Please don't edit it. */
/**
 * @file specs-code/discord/channel.c
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */

#include "specs.h"


enum discord_channel_types discord_channel_types_from_string(char *s){
  if(strcasecmp("GUILD_TEXT", s) == 0) return DISCORD_CHANNEL_GUILD_TEXT;
  if(strcasecmp("DM", s) == 0) return DISCORD_CHANNEL_DM;
  if(strcasecmp("GUILD_VOICE", s) == 0) return DISCORD_CHANNEL_GUILD_VOICE;
  if(strcasecmp("GROUP_DM", s) == 0) return DISCORD_CHANNEL_GROUP_DM;
  if(strcasecmp("GUILD_CATEGORY", s) == 0) return DISCORD_CHANNEL_GUILD_CATEGORY;
  if(strcasecmp("GUILD_NEWS", s) == 0) return DISCORD_CHANNEL_GUILD_NEWS;
  if(strcasecmp("GUILD_STORE", s) == 0) return DISCORD_CHANNEL_GUILD_STORE;
  abort();
}
char* discord_channel_types_to_string(enum discord_channel_types v){
  if (v == DISCORD_CHANNEL_GUILD_TEXT) return "GUILD_TEXT";
  if (v == DISCORD_CHANNEL_DM) return "DM";
  if (v == DISCORD_CHANNEL_GUILD_VOICE) return "GUILD_VOICE";
  if (v == DISCORD_CHANNEL_GROUP_DM) return "GROUP_DM";
  if (v == DISCORD_CHANNEL_GUILD_CATEGORY) return "GUILD_CATEGORY";
  if (v == DISCORD_CHANNEL_GUILD_NEWS) return "GUILD_NEWS";
  if (v == DISCORD_CHANNEL_GUILD_STORE) return "GUILD_STORE";

  return (void*)0;
}
bool discord_channel_types_has(enum discord_channel_types v, char *s) {
  enum discord_channel_types v1 = discord_channel_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_channel_from_json(char *json, size_t len, struct discord_channel **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_channel *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):F,"
  /* specs/discord/channel.json:29:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
                "(type):d,"
  /* specs/discord/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
                "(guild_id):F,"
  /* specs/discord/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
                "(position):d,"
  /* specs/discord/channel.json:34:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
                "(permission_overwrites):F,"
  /* specs/discord/channel.json:36:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":null}' */
                "(name):s,"
  /* specs/discord/channel.json:38:75
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":null }' */
                "(topic):s,"
  /* specs/discord/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
                "(nsfw):b,"
  /* specs/discord/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
                "(last_message_id):F,"
  /* specs/discord/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
                "(bitrate):d,"
  /* specs/discord/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
                "(user_limit):d,"
  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
                "(rate_limit_per_user):d,"
  /* specs/discord/channel.json:47:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
                "(recipients):F,"
  /* specs/discord/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
                "(icon):s,"
  /* specs/discord/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
                "(owner_id):F,"
  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
                "(application_id):F,"
  /* specs/discord/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
                "(parent_id):F,"
  /* specs/discord/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
                "(last_pin_timestamp):F,"
  /* specs/discord/channel.json:59:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
                "(messages):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_strtoull, &p->id,
  /* specs/discord/channel.json:29:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
                &p->type,
  /* specs/discord/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
                &p->position,
  /* specs/discord/channel.json:34:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
                discord_channel_overwrite_list_from_json, &p->permission_overwrites,
  /* specs/discord/channel.json:36:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":null}' */
                p->name,
  /* specs/discord/channel.json:38:75
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":null }' */
                p->topic,
  /* specs/discord/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
                &p->nsfw,
  /* specs/discord/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
                cee_strtoull, &p->last_message_id,
  /* specs/discord/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
                &p->bitrate,
  /* specs/discord/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
                &p->user_limit,
  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
                &p->rate_limit_per_user,
  /* specs/discord/channel.json:47:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
                discord_user_list_from_json, &p->recipients,
  /* specs/discord/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
                p->icon,
  /* specs/discord/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
                cee_strtoull, &p->owner_id,
  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
                cee_strtoull, &p->parent_id,
  /* specs/discord/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
                cee_iso8601_to_unix_ms, &p->last_pin_timestamp,
  /* specs/discord/channel.json:59:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
                discord_message_list_from_json, &p->messages,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_use_default_inject_settings(struct discord_channel *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.json:29:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
  p->__M.arg_switches[1] = &p->type;

  /* specs/discord/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
  if (p->guild_id != 0)
    p->__M.arg_switches[2] = &p->guild_id;

  /* specs/discord/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
  if (p->position != 0)
    p->__M.arg_switches[3] = &p->position;

  /* specs/discord/channel.json:34:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
  if (p->permission_overwrites != NULL)
    p->__M.arg_switches[4] = p->permission_overwrites;

  /* specs/discord/channel.json:36:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":null}' */
  if (p->name != NULL)
    p->__M.arg_switches[5] = p->name;

  /* specs/discord/channel.json:38:75
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":null }' */
  if (p->topic != NULL)
    p->__M.arg_switches[6] = p->topic;

  /* specs/discord/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
  if (p->nsfw != false)
    p->__M.arg_switches[7] = &p->nsfw;

  /* specs/discord/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
  if (p->last_message_id != 0)
    p->__M.arg_switches[8] = &p->last_message_id;

  /* specs/discord/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
  if (p->bitrate != 0)
    p->__M.arg_switches[9] = &p->bitrate;

  /* specs/discord/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
  if (p->user_limit != 0)
    p->__M.arg_switches[10] = &p->user_limit;

  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
  if (p->rate_limit_per_user != 0)
    p->__M.arg_switches[11] = &p->rate_limit_per_user;

  /* specs/discord/channel.json:47:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
  if (p->recipients != NULL)
    p->__M.arg_switches[12] = p->recipients;

  /* specs/discord/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
  if (p->icon != NULL)
    p->__M.arg_switches[13] = p->icon;

  /* specs/discord/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
  if (p->owner_id != 0)
    p->__M.arg_switches[14] = &p->owner_id;

  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
  if (p->application_id != 0)
    p->__M.arg_switches[15] = &p->application_id;

  /* specs/discord/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
  if (p->parent_id != 0)
    p->__M.arg_switches[16] = &p->parent_id;

  /* specs/discord/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
  if (p->last_pin_timestamp != 0)
    p->__M.arg_switches[17] = &p->last_pin_timestamp;

  /* specs/discord/channel.json:59:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
  p->__M.arg_switches[18] = p->messages;

}

size_t discord_channel_to_json(char *json, size_t len, struct discord_channel *p)
{
  size_t r;
  discord_channel_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):|F|,"
  /* specs/discord/channel.json:29:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
                "(type):d,"
  /* specs/discord/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
                "(guild_id):|F|,"
  /* specs/discord/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
                "(position):d,"
  /* specs/discord/channel.json:34:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
                "(permission_overwrites):F,"
  /* specs/discord/channel.json:36:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":null}' */
                "(name):s,"
  /* specs/discord/channel.json:38:75
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":null }' */
                "(topic):s,"
  /* specs/discord/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
                "(nsfw):b,"
  /* specs/discord/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
                "(last_message_id):|F|,"
  /* specs/discord/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
                "(bitrate):d,"
  /* specs/discord/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
                "(user_limit):d,"
  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
                "(rate_limit_per_user):d,"
  /* specs/discord/channel.json:47:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
                "(recipients):F,"
  /* specs/discord/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
                "(icon):s,"
  /* specs/discord/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
                "(owner_id):|F|,"
  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
                "(application_id):|F|,"
  /* specs/discord/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
                "(parent_id):|F|,"
  /* specs/discord/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
                "(last_pin_timestamp):|F|,"
  /* specs/discord/channel.json:59:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
                "(messages):F,"
                "@arg_switches:b",
  /* specs/discord/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/channel.json:29:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
                &p->type,
  /* specs/discord/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
                &p->position,
  /* specs/discord/channel.json:34:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
                discord_channel_overwrite_list_to_json, p->permission_overwrites,
  /* specs/discord/channel.json:36:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":null}' */
                p->name,
  /* specs/discord/channel.json:38:75
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":null }' */
                p->topic,
  /* specs/discord/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
                &p->nsfw,
  /* specs/discord/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
                cee_ulltostr, &p->last_message_id,
  /* specs/discord/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
                &p->bitrate,
  /* specs/discord/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
                &p->user_limit,
  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
                &p->rate_limit_per_user,
  /* specs/discord/channel.json:47:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
                discord_user_list_to_json, p->recipients,
  /* specs/discord/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
                p->icon,
  /* specs/discord/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
                cee_ulltostr, &p->owner_id,
  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
                cee_ulltostr, &p->parent_id,
  /* specs/discord/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
                cee_unix_ms_to_iso8601, &p->last_pin_timestamp,
  /* specs/discord/channel.json:59:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
                discord_message_list_to_json, p->messages,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_cleanup_v(void *p) {
  discord_channel_cleanup((struct discord_channel *)p);
}

void discord_channel_init_v(void *p) {
  discord_channel_init((struct discord_channel *)p);
}

void discord_channel_free_v(void *p) {
 discord_channel_free((struct discord_channel *)p);
};

void discord_channel_from_json_v(char *json, size_t len, void *pp) {
 discord_channel_from_json(json, len, (struct discord_channel**)pp);
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
  /* specs/discord/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  // p->id is a scalar
  /* specs/discord/channel.json:29:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
  // p->type is a scalar
  /* specs/discord/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
  // p->guild_id is a scalar
  /* specs/discord/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
  // p->position is a scalar
  /* specs/discord/channel.json:34:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
  if (d->permission_overwrites)
    discord_channel_overwrite_list_free(d->permission_overwrites);
  /* specs/discord/channel.json:36:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":null}' */
  // p->name is a scalar
  /* specs/discord/channel.json:38:75
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":null }' */
  // p->topic is a scalar
  /* specs/discord/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
  // p->nsfw is a scalar
  /* specs/discord/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
  // p->last_message_id is a scalar
  /* specs/discord/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
  // p->bitrate is a scalar
  /* specs/discord/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
  // p->user_limit is a scalar
  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
  // p->rate_limit_per_user is a scalar
  /* specs/discord/channel.json:47:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
  if (d->recipients)
    discord_user_list_free(d->recipients);
  /* specs/discord/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
  // p->icon is a scalar
  /* specs/discord/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
  // p->owner_id is a scalar
  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
  // p->application_id is a scalar
  /* specs/discord/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
  // p->parent_id is a scalar
  /* specs/discord/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
  // p->last_pin_timestamp is a scalar
  /* specs/discord/channel.json:59:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
  if (d->messages)
    discord_message_list_free(d->messages);
}

void discord_channel_init(struct discord_channel *p) {
  memset(p, 0, sizeof(struct discord_channel));
  /* specs/discord/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */

  /* specs/discord/channel.json:29:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */

  /* specs/discord/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */

  /* specs/discord/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */

  /* specs/discord/channel.json:34:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */

  /* specs/discord/channel.json:36:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:38:75
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":null }' */

  /* specs/discord/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */

  /* specs/discord/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:47:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:59:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */

}
struct discord_channel* discord_channel_alloc() {
  struct discord_channel *p= malloc(sizeof(struct discord_channel));
  discord_channel_init(p);
  return p;
}

void discord_channel_free(struct discord_channel *p) {
  discord_channel_cleanup(p);
  free(p);
}

void discord_channel_list_free(struct discord_channel **p) {
  ntl_free((void**)p, (vfvp)discord_channel_cleanup);
}

void discord_channel_list_from_json(char *str, size_t len, struct discord_channel ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel);
  d.init_elem = NULL;
  d.elem_from_buf = discord_channel_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_list_to_json(char *str, size_t len, struct discord_channel **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_to_json_v);
}



enum discord_message_sticker_format_types discord_message_sticker_format_types_from_string(char *s){
  if(strcasecmp("PNG", s) == 0) return DISCORD_MESSAGE_STICKER_PNG;
  if(strcasecmp("APNG", s) == 0) return DISCORD_MESSAGE_STICKER_APNG;
  if(strcasecmp("LOTTIE", s) == 0) return DISCORD_MESSAGE_STICKER_LOTTIE;
  abort();
}
char* discord_message_sticker_format_types_to_string(enum discord_message_sticker_format_types v){
  if (v == DISCORD_MESSAGE_STICKER_PNG) return "PNG";
  if (v == DISCORD_MESSAGE_STICKER_APNG) return "APNG";
  if (v == DISCORD_MESSAGE_STICKER_LOTTIE) return "LOTTIE";

  return (void*)0;
}
bool discord_message_sticker_format_types_has(enum discord_message_sticker_format_types v, char *s) {
  enum discord_message_sticker_format_types v1 = discord_message_sticker_format_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_message_sticker_from_json(char *json, size_t len, struct discord_message_sticker **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_message_sticker *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:80:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* specs/discord/channel.json:81:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(pack_id):F,"
  /* specs/discord/channel.json:82:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/discord/channel.json:83:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                "(description):?s,"
  /* specs/discord/channel.json:84:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
                "(tags):?s,"
  /* specs/discord/channel.json:85:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */
                "(asset):s,"
  /* specs/discord/channel.json:86:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":null}' */
                "(preview_asset):s,"
  /* specs/discord/channel.json:88:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
                "(type):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:80:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->id,
  /* specs/discord/channel.json:81:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->pack_id,
  /* specs/discord/channel.json:82:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/discord/channel.json:83:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                &p->description,
  /* specs/discord/channel.json:84:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
                &p->tags,
  /* specs/discord/channel.json:85:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */
                p->asset,
  /* specs/discord/channel.json:86:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":null}' */
                p->preview_asset,
  /* specs/discord/channel.json:88:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_message_sticker_use_default_inject_settings(struct discord_message_sticker *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:80:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.json:81:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[1] = &p->pack_id;

  /* specs/discord/channel.json:82:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[2] = p->name;

  /* specs/discord/channel.json:83:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[3] = p->description;

  /* specs/discord/channel.json:84:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
  p->__M.arg_switches[4] = p->tags;

  /* specs/discord/channel.json:85:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */
  p->__M.arg_switches[5] = p->asset;

  /* specs/discord/channel.json:86:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":null}' */
  if (p->preview_asset != NULL)
    p->__M.arg_switches[6] = p->preview_asset;

  /* specs/discord/channel.json:88:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
  p->__M.arg_switches[7] = &p->type;

}

size_t discord_message_sticker_to_json(char *json, size_t len, struct discord_message_sticker *p)
{
  size_t r;
  discord_message_sticker_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:80:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* specs/discord/channel.json:81:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(pack_id):|F|,"
  /* specs/discord/channel.json:82:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/discord/channel.json:83:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                "(description):s,"
  /* specs/discord/channel.json:84:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
                "(tags):s,"
  /* specs/discord/channel.json:85:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */
                "(asset):s,"
  /* specs/discord/channel.json:86:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":null}' */
                "(preview_asset):s,"
  /* specs/discord/channel.json:88:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
                "(type):d,"
                "@arg_switches:b",
  /* specs/discord/channel.json:80:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->id,
  /* specs/discord/channel.json:81:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->pack_id,
  /* specs/discord/channel.json:82:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                p->name,
  /* specs/discord/channel.json:83:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                p->description,
  /* specs/discord/channel.json:84:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
                p->tags,
  /* specs/discord/channel.json:85:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */
                p->asset,
  /* specs/discord/channel.json:86:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":null}' */
                p->preview_asset,
  /* specs/discord/channel.json:88:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_message_sticker_cleanup_v(void *p) {
  discord_message_sticker_cleanup((struct discord_message_sticker *)p);
}

void discord_message_sticker_init_v(void *p) {
  discord_message_sticker_init((struct discord_message_sticker *)p);
}

void discord_message_sticker_free_v(void *p) {
 discord_message_sticker_free((struct discord_message_sticker *)p);
};

void discord_message_sticker_from_json_v(char *json, size_t len, void *pp) {
 discord_message_sticker_from_json(json, len, (struct discord_message_sticker**)pp);
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
  /* specs/discord/channel.json:80:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->id is a scalar
  /* specs/discord/channel.json:81:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->pack_id is a scalar
  /* specs/discord/channel.json:82:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/discord/channel.json:83:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  if (d->description)
    free(d->description);
  /* specs/discord/channel.json:84:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
  if (d->tags)
    free(d->tags);
  /* specs/discord/channel.json:85:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */
  // p->asset is a scalar
  /* specs/discord/channel.json:86:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":null}' */
  // p->preview_asset is a scalar
  /* specs/discord/channel.json:88:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
  // p->type is a scalar
}

void discord_message_sticker_init(struct discord_message_sticker *p) {
  memset(p, 0, sizeof(struct discord_message_sticker));
  /* specs/discord/channel.json:80:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/channel.json:81:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/channel.json:82:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */

  /* specs/discord/channel.json:83:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */

  /* specs/discord/channel.json:84:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */

  /* specs/discord/channel.json:85:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */

  /* specs/discord/channel.json:86:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:88:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */

}
struct discord_message_sticker* discord_message_sticker_alloc() {
  struct discord_message_sticker *p= malloc(sizeof(struct discord_message_sticker));
  discord_message_sticker_init(p);
  return p;
}

void discord_message_sticker_free(struct discord_message_sticker *p) {
  discord_message_sticker_cleanup(p);
  free(p);
}

void discord_message_sticker_list_free(struct discord_message_sticker **p) {
  ntl_free((void**)p, (vfvp)discord_message_sticker_cleanup);
}

void discord_message_sticker_list_from_json(char *str, size_t len, struct discord_message_sticker ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_sticker);
  d.init_elem = NULL;
  d.elem_from_buf = discord_message_sticker_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_sticker_list_to_json(char *str, size_t len, struct discord_message_sticker **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_message_sticker_to_json_v);
}



enum discord_message_flags discord_message_flags_from_string(char *s){
  if(strcasecmp("CROSSPOSTED", s) == 0) return DISCORD_MESSAGE_CROSSPOSTED;
  if(strcasecmp("IS_CROSSPOST", s) == 0) return DISCORD_MESSAGE_IS_CROSSPOST;
  if(strcasecmp("SUPRESS_EMBEDS", s) == 0) return DISCORD_MESSAGE_SUPRESS_EMBEDS;
  if(strcasecmp("SOURCE_MESSAGE_DELETED", s) == 0) return DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED;
  if(strcasecmp("URGENT", s) == 0) return DISCORD_MESSAGE_URGENT;
  abort();
}
char* discord_message_flags_to_string(enum discord_message_flags v){
  if (v == DISCORD_MESSAGE_CROSSPOSTED) return "CROSSPOSTED";
  if (v == DISCORD_MESSAGE_IS_CROSSPOST) return "IS_CROSSPOST";
  if (v == DISCORD_MESSAGE_SUPRESS_EMBEDS) return "SUPRESS_EMBEDS";
  if (v == DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED) return "SOURCE_MESSAGE_DELETED";
  if (v == DISCORD_MESSAGE_URGENT) return "URGENT";

  return (void*)0;
}
bool discord_message_flags_has(enum discord_message_flags v, char *s) {
  enum discord_message_flags v1 = discord_message_flags_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_message_reference_from_json(char *json, size_t len, struct discord_message_reference **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_message_reference *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:110:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(message_id):F,"
  /* specs/discord/channel.json:111:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(channel_id):F,"
  /* specs/discord/channel.json:112:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(guild_id):F,"
  /* specs/discord/channel.json:113:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                "(fail_if_not_exists):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:110:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_strtoull, &p->message_id,
  /* specs/discord/channel.json:111:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/channel.json:112:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/channel.json:113:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                &p->fail_if_not_exists,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_message_reference_use_default_inject_settings(struct discord_message_reference *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:110:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  if (p->message_id != 0)
    p->__M.arg_switches[0] = &p->message_id;

  /* specs/discord/channel.json:111:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  if (p->channel_id != 0)
    p->__M.arg_switches[1] = &p->channel_id;

  /* specs/discord/channel.json:112:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  if (p->guild_id != 0)
    p->__M.arg_switches[2] = &p->guild_id;

  /* specs/discord/channel.json:113:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  if (p->fail_if_not_exists != false)
    p->__M.arg_switches[3] = &p->fail_if_not_exists;

}

size_t discord_message_reference_to_json(char *json, size_t len, struct discord_message_reference *p)
{
  size_t r;
  discord_message_reference_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:110:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(message_id):|F|,"
  /* specs/discord/channel.json:111:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(channel_id):|F|,"
  /* specs/discord/channel.json:112:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                "(guild_id):|F|,"
  /* specs/discord/channel.json:113:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                "(fail_if_not_exists):b,"
                "@arg_switches:b",
  /* specs/discord/channel.json:110:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_ulltostr, &p->message_id,
  /* specs/discord/channel.json:111:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/channel.json:112:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/channel.json:113:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                &p->fail_if_not_exists,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_message_reference_cleanup_v(void *p) {
  discord_message_reference_cleanup((struct discord_message_reference *)p);
}

void discord_message_reference_init_v(void *p) {
  discord_message_reference_init((struct discord_message_reference *)p);
}

void discord_message_reference_free_v(void *p) {
 discord_message_reference_free((struct discord_message_reference *)p);
};

void discord_message_reference_from_json_v(char *json, size_t len, void *pp) {
 discord_message_reference_from_json(json, len, (struct discord_message_reference**)pp);
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
  /* specs/discord/channel.json:110:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  // p->message_id is a scalar
  /* specs/discord/channel.json:111:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  // p->channel_id is a scalar
  /* specs/discord/channel.json:112:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  // p->guild_id is a scalar
  /* specs/discord/channel.json:113:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  // p->fail_if_not_exists is a scalar
}

void discord_message_reference_init(struct discord_message_reference *p) {
  memset(p, 0, sizeof(struct discord_message_reference));
  /* specs/discord/channel.json:110:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:111:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:112:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:113:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */

}
struct discord_message_reference* discord_message_reference_alloc() {
  struct discord_message_reference *p= malloc(sizeof(struct discord_message_reference));
  discord_message_reference_init(p);
  return p;
}

void discord_message_reference_free(struct discord_message_reference *p) {
  discord_message_reference_cleanup(p);
  free(p);
}

void discord_message_reference_list_free(struct discord_message_reference **p) {
  ntl_free((void**)p, (vfvp)discord_message_reference_cleanup);
}

void discord_message_reference_list_from_json(char *str, size_t len, struct discord_message_reference ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_reference);
  d.init_elem = NULL;
  d.elem_from_buf = discord_message_reference_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_reference_list_to_json(char *str, size_t len, struct discord_message_reference **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_message_reference_to_json_v);
}


void discord_message_application_from_json(char *json, size_t len, struct discord_message_application **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_message_application *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:122:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* specs/discord/channel.json:123:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(cover_image):?s,"
  /* specs/discord/channel.json:124:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                "(description):?s,"
  /* specs/discord/channel.json:125:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(icon):?s,"
  /* specs/discord/channel.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                "(name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:122:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->id,
  /* specs/discord/channel.json:123:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->cover_image,
  /* specs/discord/channel.json:124:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                &p->description,
  /* specs/discord/channel.json:125:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                &p->icon,
  /* specs/discord/channel.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                &p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_message_application_use_default_inject_settings(struct discord_message_application *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:122:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.json:123:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->cover_image != NULL)
    p->__M.arg_switches[1] = p->cover_image;

  /* specs/discord/channel.json:124:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[2] = p->description;

  /* specs/discord/channel.json:125:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (p->icon != NULL)
    p->__M.arg_switches[3] = p->icon;

  /* specs/discord/channel.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[4] = p->name;

}

size_t discord_message_application_to_json(char *json, size_t len, struct discord_message_application *p)
{
  size_t r;
  discord_message_application_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:122:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* specs/discord/channel.json:123:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(cover_image):s,"
  /* specs/discord/channel.json:124:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                "(description):s,"
  /* specs/discord/channel.json:125:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(icon):s,"
  /* specs/discord/channel.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                "(name):s,"
                "@arg_switches:b",
  /* specs/discord/channel.json:122:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->id,
  /* specs/discord/channel.json:123:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->cover_image,
  /* specs/discord/channel.json:124:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
                p->description,
  /* specs/discord/channel.json:125:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                p->icon,
  /* specs/discord/channel.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
                p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_message_application_cleanup_v(void *p) {
  discord_message_application_cleanup((struct discord_message_application *)p);
}

void discord_message_application_init_v(void *p) {
  discord_message_application_init((struct discord_message_application *)p);
}

void discord_message_application_free_v(void *p) {
 discord_message_application_free((struct discord_message_application *)p);
};

void discord_message_application_from_json_v(char *json, size_t len, void *pp) {
 discord_message_application_from_json(json, len, (struct discord_message_application**)pp);
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
  /* specs/discord/channel.json:122:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->id is a scalar
  /* specs/discord/channel.json:123:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->cover_image)
    free(d->cover_image);
  /* specs/discord/channel.json:124:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  if (d->description)
    free(d->description);
  /* specs/discord/channel.json:125:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (d->icon)
    free(d->icon);
  /* specs/discord/channel.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
}

void discord_message_application_init(struct discord_message_application *p) {
  memset(p, 0, sizeof(struct discord_message_application));
  /* specs/discord/channel.json:122:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/channel.json:123:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:124:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */

  /* specs/discord/channel.json:125:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */

  /* specs/discord/channel.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */

}
struct discord_message_application* discord_message_application_alloc() {
  struct discord_message_application *p= malloc(sizeof(struct discord_message_application));
  discord_message_application_init(p);
  return p;
}

void discord_message_application_free(struct discord_message_application *p) {
  discord_message_application_cleanup(p);
  free(p);
}

void discord_message_application_list_free(struct discord_message_application **p) {
  ntl_free((void**)p, (vfvp)discord_message_application_cleanup);
}

void discord_message_application_list_from_json(char *str, size_t len, struct discord_message_application ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_application);
  d.init_elem = NULL;
  d.elem_from_buf = discord_message_application_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_application_list_to_json(char *str, size_t len, struct discord_message_application **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_message_application_to_json_v);
}



enum discord_message_activity_types discord_message_activity_types_from_string(char *s){
  if(strcasecmp("JOIN", s) == 0) return DISCORD_MESSAGE_ACTIVITY_JOIN;
  if(strcasecmp("SPECTATE", s) == 0) return DISCORD_MESSAGE_ACTIVITY_SPECTATE;
  if(strcasecmp("LISTEN", s) == 0) return DISCORD_MESSAGE_ACTIVITY_LISTEN;
  if(strcasecmp("JOIN_REQUEST", s) == 0) return DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST;
  abort();
}
char* discord_message_activity_types_to_string(enum discord_message_activity_types v){
  if (v == DISCORD_MESSAGE_ACTIVITY_JOIN) return "JOIN";
  if (v == DISCORD_MESSAGE_ACTIVITY_SPECTATE) return "SPECTATE";
  if (v == DISCORD_MESSAGE_ACTIVITY_LISTEN) return "LISTEN";
  if (v == DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST) return "JOIN_REQUEST";

  return (void*)0;
}
bool discord_message_activity_types_has(enum discord_message_activity_types v, char *s) {
  enum discord_message_activity_types v1 = discord_message_activity_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_message_activity_from_json(char *json, size_t len, struct discord_message_activity **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_message_activity *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:147:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
                "(type):d,"
  /* specs/discord/channel.json:148:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
                "(party_id):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:147:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
                &p->type,
  /* specs/discord/channel.json:148:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
                &p->party_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_message_activity_use_default_inject_settings(struct discord_message_activity *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:147:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
  p->__M.arg_switches[0] = &p->type;

  /* specs/discord/channel.json:148:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
  if (p->party_id != NULL)
    p->__M.arg_switches[1] = p->party_id;

}

size_t discord_message_activity_to_json(char *json, size_t len, struct discord_message_activity *p)
{
  size_t r;
  discord_message_activity_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:147:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
                "(type):d,"
  /* specs/discord/channel.json:148:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
                "(party_id):s,"
                "@arg_switches:b",
  /* specs/discord/channel.json:147:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
                &p->type,
  /* specs/discord/channel.json:148:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
                p->party_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_message_activity_cleanup_v(void *p) {
  discord_message_activity_cleanup((struct discord_message_activity *)p);
}

void discord_message_activity_init_v(void *p) {
  discord_message_activity_init((struct discord_message_activity *)p);
}

void discord_message_activity_free_v(void *p) {
 discord_message_activity_free((struct discord_message_activity *)p);
};

void discord_message_activity_from_json_v(char *json, size_t len, void *pp) {
 discord_message_activity_from_json(json, len, (struct discord_message_activity**)pp);
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
  /* specs/discord/channel.json:147:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
  // p->type is a scalar
  /* specs/discord/channel.json:148:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
  if (d->party_id)
    free(d->party_id);
}

void discord_message_activity_init(struct discord_message_activity *p) {
  memset(p, 0, sizeof(struct discord_message_activity));
  /* specs/discord/channel.json:147:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */

  /* specs/discord/channel.json:148:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */

}
struct discord_message_activity* discord_message_activity_alloc() {
  struct discord_message_activity *p= malloc(sizeof(struct discord_message_activity));
  discord_message_activity_init(p);
  return p;
}

void discord_message_activity_free(struct discord_message_activity *p) {
  discord_message_activity_cleanup(p);
  free(p);
}

void discord_message_activity_list_free(struct discord_message_activity **p) {
  ntl_free((void**)p, (vfvp)discord_message_activity_cleanup);
}

void discord_message_activity_list_from_json(char *str, size_t len, struct discord_message_activity ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_activity);
  d.init_elem = NULL;
  d.elem_from_buf = discord_message_activity_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_activity_list_to_json(char *str, size_t len, struct discord_message_activity **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_message_activity_to_json_v);
}



enum discord_message_types discord_message_types_from_string(char *s){
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
  abort();
}
char* discord_message_types_to_string(enum discord_message_types v){
  if (v == DISCORD_MESSAGE_DEFAULT) return "DEFAULT";
  if (v == DISCORD_MESSAGE_RECIPIENT_ADD) return "RECIPIENT_ADD";
  if (v == DISCORD_MESSAGE_RECIPIENT_REMOVE) return "RECIPIENT_REMOVE";
  if (v == DISCORD_MESSAGE_CALL) return "CALL";
  if (v == DISCORD_MESSAGE_CHANNEL_NAME_CHANGE) return "CHANNEL_NAME_CHANGE";
  if (v == DISCORD_MESSAGE_CHANNEL_ICON_CHANGE) return "CHANNEL_ICON_CHANGE";
  if (v == DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE) return "CHANNEL_PINNED_MESSAGE";
  if (v == DISCORD_MESSAGE_GUILD_MEMBER_JOIN) return "GUILD_MEMBER_JOIN";
  if (v == DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION) return "USER_PREMIUM_GUILD_SUBSCRIPTION";
  if (v == DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1) return "USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1";
  if (v == DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2) return "USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2";
  if (v == DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3) return "USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3";
  if (v == DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD) return "CHANNEL_FOLLOW_ADD";
  if (v == DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED) return "GUILD_DISCOVERY_DISQUALIFIED";
  if (v == DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED) return "GUILD_DISCOVERY_REQUALIFIED";
  if (v == DISCORD_MESSAGE_REPLY) return "REPLY";
  if (v == DISCORD_MESSAGE_APPLICATION_COMMAND) return "APPLICATION_COMMAND";

  return (void*)0;
}
bool discord_message_types_has(enum discord_message_types v, char *s) {
  enum discord_message_types v1 = discord_message_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_message_from_json(char *json, size_t len, struct discord_message **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_message *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:182:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):F,"
  /* specs/discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
                "(channel_id):F,"
  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
                "(guild_id):F,"
  /* specs/discord/channel.json:185:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
                "(author):F,"
  /* specs/discord/channel.json:186:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
                "(member):F,"
  /* specs/discord/channel.json:187:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
                "(content):?s,"
  /* specs/discord/channel.json:188:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
                "(timestamp):F,"
  /* specs/discord/channel.json:189:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
                "(edited_timestamp):F,"
  /* specs/discord/channel.json:190:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
                "(tts):b,"
  /* specs/discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
                "(mention_everyone):b,"
  /* specs/discord/channel.json:192:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
                "(mentions):F,"
  /* specs/discord/channel.json:193:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
                "(mention_roles):F,"
  /* specs/discord/channel.json:194:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
                "(mention_channels):F,"
  /* specs/discord/channel.json:195:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}' */
                "(attachments):F,"
  /* specs/discord/channel.json:196:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
                "(embeds):F,"
  /* specs/discord/channel.json:197:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
                "(reactions):F,"
  /* specs/discord/channel.json:198:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
                "(nonce):?s,"
  /* specs/discord/channel.json:199:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
                "(pinned):b,"
  /* specs/discord/channel.json:200:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
                "(webhook_id):F,"
  /* specs/discord/channel.json:201:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
                "(type):d,"
  /* specs/discord/channel.json:202:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
                "(activity):F,"
  /* specs/discord/channel.json:203:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
                "(application):F,"
  /* specs/discord/channel.json:204:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
                "(message_reference):F,"
  /* specs/discord/channel.json:205:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
                "(flags):d,"
  /* specs/discord/channel.json:206:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
                "(referenced_message):F,"
  /* specs/discord/channel.json:207:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
                "(interaction):F,"
  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
                "(thread):F,"
  /* specs/discord/channel.json:209:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
                "(components):F,"
  /* specs/discord/channel.json:210:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
                "(sticker_items):F,"
  /* specs/discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
                "(stickers):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:182:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_strtoull, &p->id,
  /* specs/discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/channel.json:185:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
                discord_user_from_json, &p->author,
  /* specs/discord/channel.json:186:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
                discord_guild_member_from_json, &p->member,
  /* specs/discord/channel.json:187:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
                &p->content,
  /* specs/discord/channel.json:188:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
                cee_iso8601_to_unix_ms, &p->timestamp,
  /* specs/discord/channel.json:189:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
                cee_iso8601_to_unix_ms, &p->edited_timestamp,
  /* specs/discord/channel.json:190:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
                &p->tts,
  /* specs/discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
                &p->mention_everyone,
  /* specs/discord/channel.json:192:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
                discord_user_list_from_json, &p->mentions,
  /* specs/discord/channel.json:193:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
                ja_u64_list_from_json, &p->mention_roles,
  /* specs/discord/channel.json:194:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
                discord_channel_mention_list_from_json, &p->mention_channels,
  /* specs/discord/channel.json:195:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}' */
                discord_channel_attachment_list_from_json, &p->attachments,
  /* specs/discord/channel.json:196:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
                discord_embed_list_from_json, &p->embeds,
  /* specs/discord/channel.json:197:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
                discord_channel_reaction_list_from_json, &p->reactions,
  /* specs/discord/channel.json:198:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
                &p->nonce,
  /* specs/discord/channel.json:199:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
                &p->pinned,
  /* specs/discord/channel.json:200:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
                cee_strtoull, &p->webhook_id,
  /* specs/discord/channel.json:201:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
                &p->type,
  /* specs/discord/channel.json:202:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
                discord_message_activity_from_json, &p->activity,
  /* specs/discord/channel.json:203:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
                discord_message_application_list_from_json, &p->application,
  /* specs/discord/channel.json:204:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
                discord_message_reference_from_json, &p->message_reference,
  /* specs/discord/channel.json:205:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
                &p->flags,
  /* specs/discord/channel.json:206:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
                discord_message_from_json, &p->referenced_message,
  /* specs/discord/channel.json:207:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
                discord_message_interaction_from_json, &p->interaction,
  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
                discord_channel_from_json, &p->thread,
  /* specs/discord/channel.json:209:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
                discord_component_list_from_json, &p->components,
  /* specs/discord/channel.json:210:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
                discord_message_sticker_list_from_json, &p->sticker_items,
  /* specs/discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
                discord_message_sticker_list_from_json, &p->stickers,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_message_use_default_inject_settings(struct discord_message *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:182:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
  p->__M.arg_switches[1] = &p->channel_id;

  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
  if (p->guild_id != 0)
    p->__M.arg_switches[2] = &p->guild_id;

  /* specs/discord/channel.json:185:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
  p->__M.arg_switches[3] = p->author;

  /* specs/discord/channel.json:186:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
  p->__M.arg_switches[4] = p->member;

  /* specs/discord/channel.json:187:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
  p->__M.arg_switches[5] = p->content;

  /* specs/discord/channel.json:188:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
  p->__M.arg_switches[6] = &p->timestamp;

  /* specs/discord/channel.json:189:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
  if (p->edited_timestamp != 0)
    p->__M.arg_switches[7] = &p->edited_timestamp;

  /* specs/discord/channel.json:190:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
  p->__M.arg_switches[8] = &p->tts;

  /* specs/discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
  p->__M.arg_switches[9] = &p->mention_everyone;

  /* specs/discord/channel.json:192:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
  p->__M.arg_switches[10] = p->mentions;

  /* specs/discord/channel.json:193:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
  p->__M.arg_switches[11] = p->mention_roles;

  /* specs/discord/channel.json:194:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
  p->__M.arg_switches[12] = p->mention_channels;

  /* specs/discord/channel.json:195:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}' */
  p->__M.arg_switches[13] = p->attachments;

  /* specs/discord/channel.json:196:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
  p->__M.arg_switches[14] = p->embeds;

  /* specs/discord/channel.json:197:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
  p->__M.arg_switches[15] = p->reactions;

  /* specs/discord/channel.json:198:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
  p->__M.arg_switches[16] = p->nonce;

  /* specs/discord/channel.json:199:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
  p->__M.arg_switches[17] = &p->pinned;

  /* specs/discord/channel.json:200:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
  p->__M.arg_switches[18] = &p->webhook_id;

  /* specs/discord/channel.json:201:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
  p->__M.arg_switches[19] = &p->type;

  /* specs/discord/channel.json:202:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
  if (p->activity != NULL)
    p->__M.arg_switches[20] = p->activity;

  /* specs/discord/channel.json:203:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
  if (p->application != NULL)
    p->__M.arg_switches[21] = p->application;

  /* specs/discord/channel.json:204:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
  if (p->message_reference != NULL)
    p->__M.arg_switches[22] = p->message_reference;

  /* specs/discord/channel.json:205:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
  if (p->flags != 0)
    p->__M.arg_switches[23] = &p->flags;

  /* specs/discord/channel.json:206:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
  if (p->referenced_message != NULL)
    p->__M.arg_switches[24] = p->referenced_message;

  /* specs/discord/channel.json:207:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
  if (p->interaction != NULL)
    p->__M.arg_switches[25] = p->interaction;

  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
  if (p->thread != NULL)
    p->__M.arg_switches[26] = p->thread;

  /* specs/discord/channel.json:209:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
  if (p->components != NULL)
    p->__M.arg_switches[27] = p->components;

  /* specs/discord/channel.json:210:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
  if (p->sticker_items != NULL)
    p->__M.arg_switches[28] = p->sticker_items;

  /* specs/discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
  if (p->stickers != NULL)
    p->__M.arg_switches[29] = p->stickers;

}

size_t discord_message_to_json(char *json, size_t len, struct discord_message *p)
{
  size_t r;
  discord_message_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:182:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                "(id):|F|,"
  /* specs/discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
                "(channel_id):|F|,"
  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
                "(guild_id):|F|,"
  /* specs/discord/channel.json:185:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
                "(author):F,"
  /* specs/discord/channel.json:186:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
                "(member):F,"
  /* specs/discord/channel.json:187:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
                "(content):s,"
  /* specs/discord/channel.json:188:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
                "(timestamp):|F|,"
  /* specs/discord/channel.json:189:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
                "(edited_timestamp):|F|,"
  /* specs/discord/channel.json:190:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
                "(tts):b,"
  /* specs/discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
                "(mention_everyone):b,"
  /* specs/discord/channel.json:192:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
                "(mentions):F,"
  /* specs/discord/channel.json:193:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
                "(mention_roles):F,"
  /* specs/discord/channel.json:194:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
                "(mention_channels):F,"
  /* specs/discord/channel.json:195:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}' */
                "(attachments):F,"
  /* specs/discord/channel.json:196:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
                "(embeds):F,"
  /* specs/discord/channel.json:197:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
                "(reactions):F,"
  /* specs/discord/channel.json:198:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
                "(nonce):s,"
  /* specs/discord/channel.json:199:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
                "(pinned):b,"
  /* specs/discord/channel.json:200:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
                "(webhook_id):|F|,"
  /* specs/discord/channel.json:201:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
                "(type):d,"
  /* specs/discord/channel.json:202:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
                "(activity):F,"
  /* specs/discord/channel.json:203:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
                "(application):F,"
  /* specs/discord/channel.json:204:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
                "(message_reference):F,"
  /* specs/discord/channel.json:205:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
                "(flags):d,"
  /* specs/discord/channel.json:206:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
                "(referenced_message):F,"
  /* specs/discord/channel.json:207:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
                "(interaction):F,"
  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
                "(thread):F,"
  /* specs/discord/channel.json:209:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
                "(components):F,"
  /* specs/discord/channel.json:210:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
                "(sticker_items):F,"
  /* specs/discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
                "(stickers):F,"
                "@arg_switches:b",
  /* specs/discord/channel.json:182:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/channel.json:185:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
                discord_user_to_json, p->author,
  /* specs/discord/channel.json:186:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
                discord_guild_member_to_json, p->member,
  /* specs/discord/channel.json:187:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
                p->content,
  /* specs/discord/channel.json:188:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
                cee_unix_ms_to_iso8601, &p->timestamp,
  /* specs/discord/channel.json:189:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
                cee_unix_ms_to_iso8601, &p->edited_timestamp,
  /* specs/discord/channel.json:190:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
                &p->tts,
  /* specs/discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
                &p->mention_everyone,
  /* specs/discord/channel.json:192:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
                discord_user_list_to_json, p->mentions,
  /* specs/discord/channel.json:193:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
                ja_u64_list_to_json, p->mention_roles,
  /* specs/discord/channel.json:194:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
                discord_channel_mention_list_to_json, p->mention_channels,
  /* specs/discord/channel.json:195:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}' */
                discord_channel_attachment_list_to_json, p->attachments,
  /* specs/discord/channel.json:196:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
                discord_embed_list_to_json, p->embeds,
  /* specs/discord/channel.json:197:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
                discord_channel_reaction_list_to_json, p->reactions,
  /* specs/discord/channel.json:198:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
                p->nonce,
  /* specs/discord/channel.json:199:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
                &p->pinned,
  /* specs/discord/channel.json:200:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
                cee_ulltostr, &p->webhook_id,
  /* specs/discord/channel.json:201:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
                &p->type,
  /* specs/discord/channel.json:202:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
                discord_message_activity_to_json, p->activity,
  /* specs/discord/channel.json:203:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
                discord_message_application_list_to_json, p->application,
  /* specs/discord/channel.json:204:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
                discord_message_reference_to_json, p->message_reference,
  /* specs/discord/channel.json:205:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
                &p->flags,
  /* specs/discord/channel.json:206:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
                discord_message_to_json, p->referenced_message,
  /* specs/discord/channel.json:207:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
                discord_message_interaction_to_json, p->interaction,
  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
                discord_channel_to_json, p->thread,
  /* specs/discord/channel.json:209:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
                discord_component_list_to_json, p->components,
  /* specs/discord/channel.json:210:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
                discord_message_sticker_list_to_json, p->sticker_items,
  /* specs/discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
                discord_message_sticker_list_to_json, p->stickers,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_message_cleanup_v(void *p) {
  discord_message_cleanup((struct discord_message *)p);
}

void discord_message_init_v(void *p) {
  discord_message_init((struct discord_message *)p);
}

void discord_message_free_v(void *p) {
 discord_message_free((struct discord_message *)p);
};

void discord_message_from_json_v(char *json, size_t len, void *pp) {
 discord_message_from_json(json, len, (struct discord_message**)pp);
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
  /* specs/discord/channel.json:182:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  // p->id is a scalar
  /* specs/discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
  // p->channel_id is a scalar
  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
  // p->guild_id is a scalar
  /* specs/discord/channel.json:185:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
  if (d->author)
    discord_user_free(d->author);
  /* specs/discord/channel.json:186:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
  if (d->member)
    discord_guild_member_free(d->member);
  /* specs/discord/channel.json:187:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
  if (d->content)
    free(d->content);
  /* specs/discord/channel.json:188:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
  // p->timestamp is a scalar
  /* specs/discord/channel.json:189:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
  // p->edited_timestamp is a scalar
  /* specs/discord/channel.json:190:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
  // p->tts is a scalar
  /* specs/discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
  // p->mention_everyone is a scalar
  /* specs/discord/channel.json:192:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
  if (d->mentions)
    discord_user_list_free(d->mentions);
  /* specs/discord/channel.json:193:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
  if (d->mention_roles)
    ja_u64_list_free(d->mention_roles);
  /* specs/discord/channel.json:194:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
  if (d->mention_channels)
    discord_channel_mention_list_free(d->mention_channels);
  /* specs/discord/channel.json:195:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}' */
  if (d->attachments)
    discord_channel_attachment_list_free(d->attachments);
  /* specs/discord/channel.json:196:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* specs/discord/channel.json:197:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
  if (d->reactions)
    discord_channel_reaction_list_free(d->reactions);
  /* specs/discord/channel.json:198:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
  if (d->nonce)
    free(d->nonce);
  /* specs/discord/channel.json:199:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
  // p->pinned is a scalar
  /* specs/discord/channel.json:200:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
  // p->webhook_id is a scalar
  /* specs/discord/channel.json:201:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
  // p->type is a scalar
  /* specs/discord/channel.json:202:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
  if (d->activity)
    discord_message_activity_free(d->activity);
  /* specs/discord/channel.json:203:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
  if (d->application)
    discord_message_application_list_free(d->application);
  /* specs/discord/channel.json:204:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
  if (d->message_reference)
    discord_message_reference_free(d->message_reference);
  /* specs/discord/channel.json:205:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
  // p->flags is a scalar
  /* specs/discord/channel.json:206:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
  if (d->referenced_message)
    discord_message_free(d->referenced_message);
  /* specs/discord/channel.json:207:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
  if (d->interaction)
    discord_message_interaction_free(d->interaction);
  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
  if (d->thread)
    discord_channel_free(d->thread);
  /* specs/discord/channel.json:209:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
  if (d->components)
    discord_component_list_free(d->components);
  /* specs/discord/channel.json:210:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
  if (d->sticker_items)
    discord_message_sticker_list_free(d->sticker_items);
  /* specs/discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
  if (d->stickers)
    discord_message_sticker_list_free(d->stickers);
}

void discord_message_init(struct discord_message *p) {
  memset(p, 0, sizeof(struct discord_message));
  /* specs/discord/channel.json:182:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */

  /* specs/discord/channel.json:183:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */

  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:185:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
  p->author = discord_user_alloc();

  /* specs/discord/channel.json:186:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
  p->member = discord_guild_member_alloc();

  /* specs/discord/channel.json:187:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */

  /* specs/discord/channel.json:188:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */

  /* specs/discord/channel.json:189:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */

  /* specs/discord/channel.json:190:43
     '{"type":{"base":"bool"}, "name":"tts"}' */

  /* specs/discord/channel.json:191:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */

  /* specs/discord/channel.json:192:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */

  /* specs/discord/channel.json:193:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */

  /* specs/discord/channel.json:194:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */

  /* specs/discord/channel.json:195:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}' */

  /* specs/discord/channel.json:196:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */

  /* specs/discord/channel.json:197:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */

  /* specs/discord/channel.json:198:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */

  /* specs/discord/channel.json:199:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */

  /* specs/discord/channel.json:200:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */

  /* specs/discord/channel.json:201:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */

  /* specs/discord/channel.json:202:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
  p->activity = discord_message_activity_alloc();

  /* specs/discord/channel.json:203:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */

  /* specs/discord/channel.json:204:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
  p->message_reference = discord_message_reference_alloc();

  /* specs/discord/channel.json:205:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */

  /* specs/discord/channel.json:206:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */

  /* specs/discord/channel.json:207:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
  p->interaction = discord_message_interaction_alloc();

  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
  p->thread = discord_channel_alloc();

  /* specs/discord/channel.json:209:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */

  /* specs/discord/channel.json:210:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */

  /* specs/discord/channel.json:211:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */

}
struct discord_message* discord_message_alloc() {
  struct discord_message *p= malloc(sizeof(struct discord_message));
  discord_message_init(p);
  return p;
}

void discord_message_free(struct discord_message *p) {
  discord_message_cleanup(p);
  free(p);
}

void discord_message_list_free(struct discord_message **p) {
  ntl_free((void**)p, (vfvp)discord_message_cleanup);
}

void discord_message_list_from_json(char *str, size_t len, struct discord_message ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message);
  d.init_elem = NULL;
  d.elem_from_buf = discord_message_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_list_to_json(char *str, size_t len, struct discord_message **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_message_to_json_v);
}


void discord_channel_followed_channel_from_json(char *json, size_t len, struct discord_channel_followed_channel **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_channel_followed_channel *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(channel_id):F,"
  /* specs/discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(webhook_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->webhook_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_followed_channel_use_default_inject_settings(struct discord_channel_followed_channel *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->channel_id;

  /* specs/discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[1] = &p->webhook_id;

}

size_t discord_channel_followed_channel_to_json(char *json, size_t len, struct discord_channel_followed_channel *p)
{
  size_t r;
  discord_channel_followed_channel_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(channel_id):|F|,"
  /* specs/discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(webhook_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->webhook_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_followed_channel_cleanup_v(void *p) {
  discord_channel_followed_channel_cleanup((struct discord_channel_followed_channel *)p);
}

void discord_channel_followed_channel_init_v(void *p) {
  discord_channel_followed_channel_init((struct discord_channel_followed_channel *)p);
}

void discord_channel_followed_channel_free_v(void *p) {
 discord_channel_followed_channel_free((struct discord_channel_followed_channel *)p);
};

void discord_channel_followed_channel_from_json_v(char *json, size_t len, void *pp) {
 discord_channel_followed_channel_from_json(json, len, (struct discord_channel_followed_channel**)pp);
}

size_t discord_channel_followed_channel_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_followed_channel_to_json(json, len, (struct discord_channel_followed_channel*)p);
}

void discord_channel_followed_channel_list_free_v(void **p) {
  discord_channel_followed_channel_list_free((struct discord_channel_followed_channel**)p);
}

void discord_channel_followed_channel_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_followed_channel_list_from_json(str, len, (struct discord_channel_followed_channel ***)p);
}

size_t discord_channel_followed_channel_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_followed_channel_list_to_json(str, len, (struct discord_channel_followed_channel **)p);
}


void discord_channel_followed_channel_cleanup(struct discord_channel_followed_channel *d) {
  /* specs/discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->channel_id is a scalar
  /* specs/discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->webhook_id is a scalar
}

void discord_channel_followed_channel_init(struct discord_channel_followed_channel *p) {
  memset(p, 0, sizeof(struct discord_channel_followed_channel));
  /* specs/discord/channel.json:221:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/channel.json:222:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

}
struct discord_channel_followed_channel* discord_channel_followed_channel_alloc() {
  struct discord_channel_followed_channel *p= malloc(sizeof(struct discord_channel_followed_channel));
  discord_channel_followed_channel_init(p);
  return p;
}

void discord_channel_followed_channel_free(struct discord_channel_followed_channel *p) {
  discord_channel_followed_channel_cleanup(p);
  free(p);
}

void discord_channel_followed_channel_list_free(struct discord_channel_followed_channel **p) {
  ntl_free((void**)p, (vfvp)discord_channel_followed_channel_cleanup);
}

void discord_channel_followed_channel_list_from_json(char *str, size_t len, struct discord_channel_followed_channel ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_followed_channel);
  d.init_elem = NULL;
  d.elem_from_buf = discord_channel_followed_channel_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_followed_channel_list_to_json(char *str, size_t len, struct discord_channel_followed_channel **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_followed_channel_to_json_v);
}


void discord_channel_reaction_from_json(char *json, size_t len, struct discord_channel_reaction **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_channel_reaction *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */
                "(count):d,"
  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
                "(me):b,"
  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
                "(emoji):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */
                &p->count,
  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
                &p->me,
  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
                discord_emoji_from_json, &p->emoji,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_reaction_use_default_inject_settings(struct discord_channel_reaction *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */
  p->__M.arg_switches[0] = &p->count;

  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[1] = &p->me;

  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
  p->__M.arg_switches[2] = p->emoji;

}

size_t discord_channel_reaction_to_json(char *json, size_t len, struct discord_channel_reaction *p)
{
  size_t r;
  discord_channel_reaction_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */
                "(count):d,"
  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
                "(me):b,"
  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
                "(emoji):F,"
                "@arg_switches:b",
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */
                &p->count,
  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
                &p->me,
  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
                discord_emoji_to_json, p->emoji,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_reaction_cleanup_v(void *p) {
  discord_channel_reaction_cleanup((struct discord_channel_reaction *)p);
}

void discord_channel_reaction_init_v(void *p) {
  discord_channel_reaction_init((struct discord_channel_reaction *)p);
}

void discord_channel_reaction_free_v(void *p) {
 discord_channel_reaction_free((struct discord_channel_reaction *)p);
};

void discord_channel_reaction_from_json_v(char *json, size_t len, void *pp) {
 discord_channel_reaction_from_json(json, len, (struct discord_channel_reaction**)pp);
}

size_t discord_channel_reaction_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_reaction_to_json(json, len, (struct discord_channel_reaction*)p);
}

void discord_channel_reaction_list_free_v(void **p) {
  discord_channel_reaction_list_free((struct discord_channel_reaction**)p);
}

void discord_channel_reaction_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_reaction_list_from_json(str, len, (struct discord_channel_reaction ***)p);
}

size_t discord_channel_reaction_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_reaction_list_to_json(str, len, (struct discord_channel_reaction **)p);
}


void discord_channel_reaction_cleanup(struct discord_channel_reaction *d) {
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */
  // p->count is a scalar
  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
  // p->me is a scalar
  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
  if (d->emoji)
    discord_emoji_free(d->emoji);
}

void discord_channel_reaction_init(struct discord_channel_reaction *p) {
  memset(p, 0, sizeof(struct discord_channel_reaction));
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */

  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */

  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
  p->emoji = discord_emoji_alloc();

}
struct discord_channel_reaction* discord_channel_reaction_alloc() {
  struct discord_channel_reaction *p= malloc(sizeof(struct discord_channel_reaction));
  discord_channel_reaction_init(p);
  return p;
}

void discord_channel_reaction_free(struct discord_channel_reaction *p) {
  discord_channel_reaction_cleanup(p);
  free(p);
}

void discord_channel_reaction_list_free(struct discord_channel_reaction **p) {
  ntl_free((void**)p, (vfvp)discord_channel_reaction_cleanup);
}

void discord_channel_reaction_list_from_json(char *str, size_t len, struct discord_channel_reaction ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_reaction);
  d.init_elem = NULL;
  d.elem_from_buf = discord_channel_reaction_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_reaction_list_to_json(char *str, size_t len, struct discord_channel_reaction **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_reaction_to_json_v);
}


void discord_channel_overwrite_from_json(char *json, size_t len, struct discord_channel_overwrite **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_channel_overwrite *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:243:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/channel.json:244:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* specs/discord/channel.json:245:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
                "(allow):s_as_hex_uint,"
  /* specs/discord/channel.json:247:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
                "(deny):s_as_hex_uint,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:243:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/channel.json:244:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* specs/discord/channel.json:245:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
                &p->allow,
  /* specs/discord/channel.json:247:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
                &p->deny,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_overwrite_use_default_inject_settings(struct discord_channel_overwrite *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:243:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.json:244:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  p->__M.arg_switches[1] = &p->type;

  /* specs/discord/channel.json:245:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
  p->__M.arg_switches[2] = &p->allow;

  /* specs/discord/channel.json:247:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
  p->__M.arg_switches[3] = &p->deny;

}

size_t discord_channel_overwrite_to_json(char *json, size_t len, struct discord_channel_overwrite *p)
{
  size_t r;
  discord_channel_overwrite_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:243:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/channel.json:244:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* specs/discord/channel.json:245:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
                "(allow):s_as_hex_uint,"
  /* specs/discord/channel.json:247:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
                "(deny):s_as_hex_uint,"
                "@arg_switches:b",
  /* specs/discord/channel.json:243:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/channel.json:244:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* specs/discord/channel.json:245:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
                &p->allow,
  /* specs/discord/channel.json:247:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
                &p->deny,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_overwrite_cleanup_v(void *p) {
  discord_channel_overwrite_cleanup((struct discord_channel_overwrite *)p);
}

void discord_channel_overwrite_init_v(void *p) {
  discord_channel_overwrite_init((struct discord_channel_overwrite *)p);
}

void discord_channel_overwrite_free_v(void *p) {
 discord_channel_overwrite_free((struct discord_channel_overwrite *)p);
};

void discord_channel_overwrite_from_json_v(char *json, size_t len, void *pp) {
 discord_channel_overwrite_from_json(json, len, (struct discord_channel_overwrite**)pp);
}

size_t discord_channel_overwrite_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_overwrite_to_json(json, len, (struct discord_channel_overwrite*)p);
}

void discord_channel_overwrite_list_free_v(void **p) {
  discord_channel_overwrite_list_free((struct discord_channel_overwrite**)p);
}

void discord_channel_overwrite_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_overwrite_list_from_json(str, len, (struct discord_channel_overwrite ***)p);
}

size_t discord_channel_overwrite_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_overwrite_list_to_json(str, len, (struct discord_channel_overwrite **)p);
}


void discord_channel_overwrite_cleanup(struct discord_channel_overwrite *d) {
  /* specs/discord/channel.json:243:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/channel.json:244:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  // p->type is a scalar
  /* specs/discord/channel.json:245:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
  // p->allow is a scalar
  /* specs/discord/channel.json:247:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
  // p->deny is a scalar
}

void discord_channel_overwrite_init(struct discord_channel_overwrite *p) {
  memset(p, 0, sizeof(struct discord_channel_overwrite));
  /* specs/discord/channel.json:243:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/channel.json:244:20
     '{ "name": "type", "type":{ "base":"int" }}' */

  /* specs/discord/channel.json:245:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */

  /* specs/discord/channel.json:247:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */

}
struct discord_channel_overwrite* discord_channel_overwrite_alloc() {
  struct discord_channel_overwrite *p= malloc(sizeof(struct discord_channel_overwrite));
  discord_channel_overwrite_init(p);
  return p;
}

void discord_channel_overwrite_free(struct discord_channel_overwrite *p) {
  discord_channel_overwrite_cleanup(p);
  free(p);
}

void discord_channel_overwrite_list_free(struct discord_channel_overwrite **p) {
  ntl_free((void**)p, (vfvp)discord_channel_overwrite_cleanup);
}

void discord_channel_overwrite_list_from_json(char *str, size_t len, struct discord_channel_overwrite ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_overwrite);
  d.init_elem = NULL;
  d.elem_from_buf = discord_channel_overwrite_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_overwrite_list_to_json(char *str, size_t len, struct discord_channel_overwrite **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_overwrite_to_json_v);
}


void discord_thread_metadata_from_json(char *json, size_t len, struct discord_thread_metadata **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_thread_metadata *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:258:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
                "(archived):b,"
  /* specs/discord/channel.json:259:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(archiver_id):F,"
  /* specs/discord/channel.json:260:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
                "(auto_archive_duration):d,"
  /* specs/discord/channel.json:261:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(archive_timestamp):F,"
  /* specs/discord/channel.json:262:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
                "(locked):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:258:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
                &p->archived,
  /* specs/discord/channel.json:259:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->archiver_id,
  /* specs/discord/channel.json:260:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
                &p->auto_archive_duration,
  /* specs/discord/channel.json:261:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->archive_timestamp,
  /* specs/discord/channel.json:262:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
                &p->locked,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_thread_metadata_use_default_inject_settings(struct discord_thread_metadata *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:258:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[0] = &p->archived;

  /* specs/discord/channel.json:259:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[1] = &p->archiver_id;

  /* specs/discord/channel.json:260:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
  p->__M.arg_switches[2] = &p->auto_archive_duration;

  /* specs/discord/channel.json:261:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  p->__M.arg_switches[3] = &p->archive_timestamp;

  /* specs/discord/channel.json:262:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[4] = &p->locked;

}

size_t discord_thread_metadata_to_json(char *json, size_t len, struct discord_thread_metadata *p)
{
  size_t r;
  discord_thread_metadata_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:258:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
                "(archived):b,"
  /* specs/discord/channel.json:259:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(archiver_id):|F|,"
  /* specs/discord/channel.json:260:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
                "(auto_archive_duration):d,"
  /* specs/discord/channel.json:261:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(archive_timestamp):|F|,"
  /* specs/discord/channel.json:262:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
                "(locked):b,"
                "@arg_switches:b",
  /* specs/discord/channel.json:258:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
                &p->archived,
  /* specs/discord/channel.json:259:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->archiver_id,
  /* specs/discord/channel.json:260:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
                &p->auto_archive_duration,
  /* specs/discord/channel.json:261:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->archive_timestamp,
  /* specs/discord/channel.json:262:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
                &p->locked,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_thread_metadata_cleanup_v(void *p) {
  discord_thread_metadata_cleanup((struct discord_thread_metadata *)p);
}

void discord_thread_metadata_init_v(void *p) {
  discord_thread_metadata_init((struct discord_thread_metadata *)p);
}

void discord_thread_metadata_free_v(void *p) {
 discord_thread_metadata_free((struct discord_thread_metadata *)p);
};

void discord_thread_metadata_from_json_v(char *json, size_t len, void *pp) {
 discord_thread_metadata_from_json(json, len, (struct discord_thread_metadata**)pp);
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
  /* specs/discord/channel.json:258:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
  // p->archived is a scalar
  /* specs/discord/channel.json:259:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->archiver_id is a scalar
  /* specs/discord/channel.json:260:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
  // p->auto_archive_duration is a scalar
  /* specs/discord/channel.json:261:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  // p->archive_timestamp is a scalar
  /* specs/discord/channel.json:262:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
  // p->locked is a scalar
}

void discord_thread_metadata_init(struct discord_thread_metadata *p) {
  memset(p, 0, sizeof(struct discord_thread_metadata));
  /* specs/discord/channel.json:258:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */

  /* specs/discord/channel.json:259:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/channel.json:260:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */

  /* specs/discord/channel.json:261:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* specs/discord/channel.json:262:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */

}
struct discord_thread_metadata* discord_thread_metadata_alloc() {
  struct discord_thread_metadata *p= malloc(sizeof(struct discord_thread_metadata));
  discord_thread_metadata_init(p);
  return p;
}

void discord_thread_metadata_free(struct discord_thread_metadata *p) {
  discord_thread_metadata_cleanup(p);
  free(p);
}

void discord_thread_metadata_list_free(struct discord_thread_metadata **p) {
  ntl_free((void**)p, (vfvp)discord_thread_metadata_cleanup);
}

void discord_thread_metadata_list_from_json(char *str, size_t len, struct discord_thread_metadata ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_metadata);
  d.init_elem = NULL;
  d.elem_from_buf = discord_thread_metadata_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_thread_metadata_list_to_json(char *str, size_t len, struct discord_thread_metadata **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_thread_metadata_to_json_v);
}


void discord_thread_member_from_json(char *json, size_t len, struct discord_thread_member **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_thread_member *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:272:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/channel.json:273:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(user_id):F,"
  /* specs/discord/channel.json:274:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(join_timestamp):F,"
  /* specs/discord/channel.json:275:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
                "(flags):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:272:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/channel.json:273:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->user_id,
  /* specs/discord/channel.json:274:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->join_timestamp,
  /* specs/discord/channel.json:275:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
                &p->flags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_thread_member_use_default_inject_settings(struct discord_thread_member *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:272:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.json:273:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[1] = &p->user_id;

  /* specs/discord/channel.json:274:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  p->__M.arg_switches[2] = &p->join_timestamp;

  /* specs/discord/channel.json:275:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
  p->__M.arg_switches[3] = &p->flags;

}

size_t discord_thread_member_to_json(char *json, size_t len, struct discord_thread_member *p)
{
  size_t r;
  discord_thread_member_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:272:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/channel.json:273:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(user_id):|F|,"
  /* specs/discord/channel.json:274:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(join_timestamp):|F|,"
  /* specs/discord/channel.json:275:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
                "(flags):d,"
                "@arg_switches:b",
  /* specs/discord/channel.json:272:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/channel.json:273:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->user_id,
  /* specs/discord/channel.json:274:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->join_timestamp,
  /* specs/discord/channel.json:275:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
                &p->flags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_thread_member_cleanup_v(void *p) {
  discord_thread_member_cleanup((struct discord_thread_member *)p);
}

void discord_thread_member_init_v(void *p) {
  discord_thread_member_init((struct discord_thread_member *)p);
}

void discord_thread_member_free_v(void *p) {
 discord_thread_member_free((struct discord_thread_member *)p);
};

void discord_thread_member_from_json_v(char *json, size_t len, void *pp) {
 discord_thread_member_from_json(json, len, (struct discord_thread_member**)pp);
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
  /* specs/discord/channel.json:272:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/channel.json:273:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->user_id is a scalar
  /* specs/discord/channel.json:274:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  // p->join_timestamp is a scalar
  /* specs/discord/channel.json:275:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
  // p->flags is a scalar
}

void discord_thread_member_init(struct discord_thread_member *p) {
  memset(p, 0, sizeof(struct discord_thread_member));
  /* specs/discord/channel.json:272:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/channel.json:273:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/channel.json:274:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* specs/discord/channel.json:275:20
     '{ "name": "flags", "type":{ "base":"int" }}' */

}
struct discord_thread_member* discord_thread_member_alloc() {
  struct discord_thread_member *p= malloc(sizeof(struct discord_thread_member));
  discord_thread_member_init(p);
  return p;
}

void discord_thread_member_free(struct discord_thread_member *p) {
  discord_thread_member_cleanup(p);
  free(p);
}

void discord_thread_member_list_free(struct discord_thread_member **p) {
  ntl_free((void**)p, (vfvp)discord_thread_member_cleanup);
}

void discord_thread_member_list_from_json(char *str, size_t len, struct discord_thread_member ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_member);
  d.init_elem = NULL;
  d.elem_from_buf = discord_thread_member_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_thread_member_list_to_json(char *str, size_t len, struct discord_thread_member **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_thread_member_to_json_v);
}


void discord_channel_attachment_from_json(char *json, size_t len, struct discord_channel_attachment **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_channel_attachment *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}' */
                "(filename):s,"
  /* specs/discord/channel.json:287:20
     '{ "name": "size", "type":{ "base":"int" }}' */
                "(size):d,"
  /* specs/discord/channel.json:288:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}' */
                "(url):?s,"
  /* specs/discord/channel.json:289:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}' */
                "(proxy_url):?s,"
  /* specs/discord/channel.json:290:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}' */
                "(height):d,"
  /* specs/discord/channel.json:291:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}' */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}' */
                p->filename,
  /* specs/discord/channel.json:287:20
     '{ "name": "size", "type":{ "base":"int" }}' */
                &p->size,
  /* specs/discord/channel.json:288:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}' */
                &p->url,
  /* specs/discord/channel.json:289:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}' */
                &p->proxy_url,
  /* specs/discord/channel.json:290:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}' */
                &p->height,
  /* specs/discord/channel.json:291:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}' */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_attachment_use_default_inject_settings(struct discord_channel_attachment *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}' */
  p->__M.arg_switches[1] = p->filename;

  /* specs/discord/channel.json:287:20
     '{ "name": "size", "type":{ "base":"int" }}' */
  p->__M.arg_switches[2] = &p->size;

  /* specs/discord/channel.json:288:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[3] = p->url;

  /* specs/discord/channel.json:289:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[4] = p->proxy_url;

  /* specs/discord/channel.json:290:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}' */
  p->__M.arg_switches[5] = &p->height;

  /* specs/discord/channel.json:291:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}' */
  p->__M.arg_switches[6] = &p->width;

}

size_t discord_channel_attachment_to_json(char *json, size_t len, struct discord_channel_attachment *p)
{
  size_t r;
  discord_channel_attachment_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}' */
                "(filename):s,"
  /* specs/discord/channel.json:287:20
     '{ "name": "size", "type":{ "base":"int" }}' */
                "(size):d,"
  /* specs/discord/channel.json:288:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}' */
                "(url):s,"
  /* specs/discord/channel.json:289:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}' */
                "(proxy_url):s,"
  /* specs/discord/channel.json:290:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}' */
                "(height):d,"
  /* specs/discord/channel.json:291:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}' */
                "(width):d,"
                "@arg_switches:b",
  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}' */
                p->filename,
  /* specs/discord/channel.json:287:20
     '{ "name": "size", "type":{ "base":"int" }}' */
                &p->size,
  /* specs/discord/channel.json:288:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}' */
                p->url,
  /* specs/discord/channel.json:289:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}' */
                p->proxy_url,
  /* specs/discord/channel.json:290:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}' */
                &p->height,
  /* specs/discord/channel.json:291:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}' */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_attachment_cleanup_v(void *p) {
  discord_channel_attachment_cleanup((struct discord_channel_attachment *)p);
}

void discord_channel_attachment_init_v(void *p) {
  discord_channel_attachment_init((struct discord_channel_attachment *)p);
}

void discord_channel_attachment_free_v(void *p) {
 discord_channel_attachment_free((struct discord_channel_attachment *)p);
};

void discord_channel_attachment_from_json_v(char *json, size_t len, void *pp) {
 discord_channel_attachment_from_json(json, len, (struct discord_channel_attachment**)pp);
}

size_t discord_channel_attachment_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_attachment_to_json(json, len, (struct discord_channel_attachment*)p);
}

void discord_channel_attachment_list_free_v(void **p) {
  discord_channel_attachment_list_free((struct discord_channel_attachment**)p);
}

void discord_channel_attachment_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_attachment_list_from_json(str, len, (struct discord_channel_attachment ***)p);
}

size_t discord_channel_attachment_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_attachment_list_to_json(str, len, (struct discord_channel_attachment **)p);
}


void discord_channel_attachment_cleanup(struct discord_channel_attachment *d) {
  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}' */
  // p->filename is a scalar
  /* specs/discord/channel.json:287:20
     '{ "name": "size", "type":{ "base":"int" }}' */
  // p->size is a scalar
  /* specs/discord/channel.json:288:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}' */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.json:289:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}' */
  if (d->proxy_url)
    free(d->proxy_url);
  /* specs/discord/channel.json:290:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}' */
  // p->height is a scalar
  /* specs/discord/channel.json:291:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}' */
  // p->width is a scalar
}

void discord_channel_attachment_init(struct discord_channel_attachment *p) {
  memset(p, 0, sizeof(struct discord_channel_attachment));
  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}' */

  /* specs/discord/channel.json:287:20
     '{ "name": "size", "type":{ "base":"int" }}' */

  /* specs/discord/channel.json:288:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/channel.json:289:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/channel.json:290:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}' */

  /* specs/discord/channel.json:291:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}' */

}
struct discord_channel_attachment* discord_channel_attachment_alloc() {
  struct discord_channel_attachment *p= malloc(sizeof(struct discord_channel_attachment));
  discord_channel_attachment_init(p);
  return p;
}

void discord_channel_attachment_free(struct discord_channel_attachment *p) {
  discord_channel_attachment_cleanup(p);
  free(p);
}

void discord_channel_attachment_list_free(struct discord_channel_attachment **p) {
  ntl_free((void**)p, (vfvp)discord_channel_attachment_cleanup);
}

void discord_channel_attachment_list_from_json(char *str, size_t len, struct discord_channel_attachment ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_attachment);
  d.init_elem = NULL;
  d.elem_from_buf = discord_channel_attachment_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_attachment_list_to_json(char *str, size_t len, struct discord_channel_attachment **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_attachment_to_json_v);
}


void discord_channel_mention_from_json(char *json, size_t len, struct discord_channel_mention **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_channel_mention *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(guild_id):F,"
  /* specs/discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
                "(type):d,"
  /* specs/discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
                &p->type,
  /* specs/discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_mention_use_default_inject_settings(struct discord_channel_mention *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[1] = &p->guild_id;

  /* specs/discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
  p->__M.arg_switches[2] = &p->type;

  /* specs/discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[3] = p->name;

}

size_t discord_channel_mention_to_json(char *json, size_t len, struct discord_channel_mention *p)
{
  size_t r;
  discord_channel_mention_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(guild_id):|F|,"
  /* specs/discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
                "(type):d,"
  /* specs/discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
                "@arg_switches:b",
  /* specs/discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
                &p->type,
  /* specs/discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_mention_cleanup_v(void *p) {
  discord_channel_mention_cleanup((struct discord_channel_mention *)p);
}

void discord_channel_mention_init_v(void *p) {
  discord_channel_mention_init((struct discord_channel_mention *)p);
}

void discord_channel_mention_free_v(void *p) {
 discord_channel_mention_free((struct discord_channel_mention *)p);
};

void discord_channel_mention_from_json_v(char *json, size_t len, void *pp) {
 discord_channel_mention_from_json(json, len, (struct discord_channel_mention**)pp);
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
  /* specs/discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->guild_id is a scalar
  /* specs/discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
  // p->type is a scalar
  /* specs/discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
}

void discord_channel_mention_init(struct discord_channel_mention *p) {
  memset(p, 0, sizeof(struct discord_channel_mention));
  /* specs/discord/channel.json:301:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/channel.json:302:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/channel.json:303:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */

  /* specs/discord/channel.json:304:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

}
struct discord_channel_mention* discord_channel_mention_alloc() {
  struct discord_channel_mention *p= malloc(sizeof(struct discord_channel_mention));
  discord_channel_mention_init(p);
  return p;
}

void discord_channel_mention_free(struct discord_channel_mention *p) {
  discord_channel_mention_cleanup(p);
  free(p);
}

void discord_channel_mention_list_free(struct discord_channel_mention **p) {
  ntl_free((void**)p, (vfvp)discord_channel_mention_cleanup);
}

void discord_channel_mention_list_from_json(char *str, size_t len, struct discord_channel_mention ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_mention);
  d.init_elem = NULL;
  d.elem_from_buf = discord_channel_mention_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_mention_list_to_json(char *str, size_t len, struct discord_channel_mention **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_mention_to_json_v);
}


void discord_channel_allowed_mentions_from_json(char *json, size_t len, struct discord_channel_allowed_mentions **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_channel_allowed_mentions *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:314:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
                "(parse):F,"
  /* specs/discord/channel.json:315:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                "(roles):F,"
  /* specs/discord/channel.json:316:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                "(users):F,"
  /* specs/discord/channel.json:317:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
                "(replied_user):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:314:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
                ja_str_list_from_json, &p->parse,
  /* specs/discord/channel.json:315:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                ja_u64_list_from_json, &p->roles,
  /* specs/discord/channel.json:316:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                ja_u64_list_from_json, &p->users,
  /* specs/discord/channel.json:317:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
                &p->replied_user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_allowed_mentions_use_default_inject_settings(struct discord_channel_allowed_mentions *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:314:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
  p->__M.arg_switches[0] = p->parse;

  /* specs/discord/channel.json:315:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  p->__M.arg_switches[1] = p->roles;

  /* specs/discord/channel.json:316:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  p->__M.arg_switches[2] = p->users;

  /* specs/discord/channel.json:317:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[3] = &p->replied_user;

}

size_t discord_channel_allowed_mentions_to_json(char *json, size_t len, struct discord_channel_allowed_mentions *p)
{
  size_t r;
  discord_channel_allowed_mentions_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:314:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
                "(parse):F,"
  /* specs/discord/channel.json:315:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                "(roles):F,"
  /* specs/discord/channel.json:316:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                "(users):F,"
  /* specs/discord/channel.json:317:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
                "(replied_user):b,"
                "@arg_switches:b",
  /* specs/discord/channel.json:314:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
                ja_str_list_to_json, p->parse,
  /* specs/discord/channel.json:315:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                ja_u64_list_to_json, p->roles,
  /* specs/discord/channel.json:316:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
                ja_u64_list_to_json, p->users,
  /* specs/discord/channel.json:317:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
                &p->replied_user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_allowed_mentions_cleanup_v(void *p) {
  discord_channel_allowed_mentions_cleanup((struct discord_channel_allowed_mentions *)p);
}

void discord_channel_allowed_mentions_init_v(void *p) {
  discord_channel_allowed_mentions_init((struct discord_channel_allowed_mentions *)p);
}

void discord_channel_allowed_mentions_free_v(void *p) {
 discord_channel_allowed_mentions_free((struct discord_channel_allowed_mentions *)p);
};

void discord_channel_allowed_mentions_from_json_v(char *json, size_t len, void *pp) {
 discord_channel_allowed_mentions_from_json(json, len, (struct discord_channel_allowed_mentions**)pp);
}

size_t discord_channel_allowed_mentions_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_allowed_mentions_to_json(json, len, (struct discord_channel_allowed_mentions*)p);
}

void discord_channel_allowed_mentions_list_free_v(void **p) {
  discord_channel_allowed_mentions_list_free((struct discord_channel_allowed_mentions**)p);
}

void discord_channel_allowed_mentions_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_allowed_mentions_list_from_json(str, len, (struct discord_channel_allowed_mentions ***)p);
}

size_t discord_channel_allowed_mentions_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_allowed_mentions_list_to_json(str, len, (struct discord_channel_allowed_mentions **)p);
}


void discord_channel_allowed_mentions_cleanup(struct discord_channel_allowed_mentions *d) {
  /* specs/discord/channel.json:314:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
  if (d->parse)
    ja_str_list_free(d->parse);
  /* specs/discord/channel.json:315:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/discord/channel.json:316:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  if (d->users)
    ja_u64_list_free(d->users);
  /* specs/discord/channel.json:317:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
  // p->replied_user is a scalar
}

void discord_channel_allowed_mentions_init(struct discord_channel_allowed_mentions *p) {
  memset(p, 0, sizeof(struct discord_channel_allowed_mentions));
  /* specs/discord/channel.json:314:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */

  /* specs/discord/channel.json:315:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */

  /* specs/discord/channel.json:316:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */

  /* specs/discord/channel.json:317:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */

}
struct discord_channel_allowed_mentions* discord_channel_allowed_mentions_alloc() {
  struct discord_channel_allowed_mentions *p= malloc(sizeof(struct discord_channel_allowed_mentions));
  discord_channel_allowed_mentions_init(p);
  return p;
}

void discord_channel_allowed_mentions_free(struct discord_channel_allowed_mentions *p) {
  discord_channel_allowed_mentions_cleanup(p);
  free(p);
}

void discord_channel_allowed_mentions_list_free(struct discord_channel_allowed_mentions **p) {
  ntl_free((void**)p, (vfvp)discord_channel_allowed_mentions_cleanup);
}

void discord_channel_allowed_mentions_list_from_json(char *str, size_t len, struct discord_channel_allowed_mentions ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_allowed_mentions);
  d.init_elem = NULL;
  d.elem_from_buf = discord_channel_allowed_mentions_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_channel_allowed_mentions_list_to_json(char *str, size_t len, struct discord_channel_allowed_mentions **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_allowed_mentions_to_json_v);
}


void discord_embed_from_json(char *json, size_t len, struct discord_embed **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_embed *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:326:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[DISCORD_EMBED_TITLE_LEN]" }, "option":true, "inject_if_not":null}' */
                "(title):s,"
  /* specs/discord/channel.json:327:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":null}' */
                "(type):s,"
  /* specs/discord/channel.json:328:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[DISCORD_EMBED_DESCRIPTION_LEN]"}, "option":true, "inject_if_not":null}' */
                "(description):s,"
  /* specs/discord/channel.json:329:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(url):?s,"
  /* specs/discord/channel.json:330:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
                "(timestamp):F,"
  /* specs/discord/channel.json:331:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
                "(color):d,"
  /* specs/discord/channel.json:332:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(footer):F,"
  /* specs/discord/channel.json:333:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
                "(image):F,"
  /* specs/discord/channel.json:334:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
                "(thumbnail):F,"
  /* specs/discord/channel.json:335:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
                "(video):F,"
  /* specs/discord/channel.json:336:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
                "(provider):F,"
  /* specs/discord/channel.json:337:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
                "(author):F,"
  /* specs/discord/channel.json:338:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
                "(fields):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:326:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[DISCORD_EMBED_TITLE_LEN]" }, "option":true, "inject_if_not":null}' */
                p->title,
  /* specs/discord/channel.json:327:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":null}' */
                p->type,
  /* specs/discord/channel.json:328:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[DISCORD_EMBED_DESCRIPTION_LEN]"}, "option":true, "inject_if_not":null}' */
                p->description,
  /* specs/discord/channel.json:329:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->url,
  /* specs/discord/channel.json:330:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
                cee_iso8601_to_unix_ms, &p->timestamp,
  /* specs/discord/channel.json:331:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
                &p->color,
  /* specs/discord/channel.json:332:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
                discord_embed_footer_from_json, &p->footer,
  /* specs/discord/channel.json:333:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_image_from_json, &p->image,
  /* specs/discord/channel.json:334:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_thumbnail_from_json, &p->thumbnail,
  /* specs/discord/channel.json:335:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_video_from_json, &p->video,
  /* specs/discord/channel.json:336:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_provider_from_json, &p->provider,
  /* specs/discord/channel.json:337:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_author_from_json, &p->author,
  /* specs/discord/channel.json:338:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
                discord_embed_field_list_from_json, &p->fields,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_use_default_inject_settings(struct discord_embed *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:326:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[DISCORD_EMBED_TITLE_LEN]" }, "option":true, "inject_if_not":null}' */
  if (p->title != NULL)
    p->__M.arg_switches[0] = p->title;

  /* specs/discord/channel.json:327:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":null}' */
  if (p->type != NULL)
    p->__M.arg_switches[1] = p->type;

  /* specs/discord/channel.json:328:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[DISCORD_EMBED_DESCRIPTION_LEN]"}, "option":true, "inject_if_not":null}' */
  if (p->description != NULL)
    p->__M.arg_switches[2] = p->description;

  /* specs/discord/channel.json:329:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->url != NULL)
    p->__M.arg_switches[3] = p->url;

  /* specs/discord/channel.json:330:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
  if (p->timestamp != 0)
    p->__M.arg_switches[4] = &p->timestamp;

  /* specs/discord/channel.json:331:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
  if (p->color != 0)
    p->__M.arg_switches[5] = &p->color;

  /* specs/discord/channel.json:332:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->footer != NULL)
    p->__M.arg_switches[6] = p->footer;

  /* specs/discord/channel.json:333:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
  if (p->image != NULL)
    p->__M.arg_switches[7] = p->image;

  /* specs/discord/channel.json:334:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
  if (p->thumbnail != NULL)
    p->__M.arg_switches[8] = p->thumbnail;

  /* specs/discord/channel.json:335:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
  if (p->video != NULL)
    p->__M.arg_switches[9] = p->video;

  /* specs/discord/channel.json:336:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
  if (p->provider != NULL)
    p->__M.arg_switches[10] = p->provider;

  /* specs/discord/channel.json:337:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
  if (p->author != NULL)
    p->__M.arg_switches[11] = p->author;

  /* specs/discord/channel.json:338:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
  if (p->fields != NULL)
    p->__M.arg_switches[12] = p->fields;

}

size_t discord_embed_to_json(char *json, size_t len, struct discord_embed *p)
{
  size_t r;
  discord_embed_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:326:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[DISCORD_EMBED_TITLE_LEN]" }, "option":true, "inject_if_not":null}' */
                "(title):s,"
  /* specs/discord/channel.json:327:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":null}' */
                "(type):s,"
  /* specs/discord/channel.json:328:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[DISCORD_EMBED_DESCRIPTION_LEN]"}, "option":true, "inject_if_not":null}' */
                "(description):s,"
  /* specs/discord/channel.json:329:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(url):s,"
  /* specs/discord/channel.json:330:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
                "(timestamp):|F|,"
  /* specs/discord/channel.json:331:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
                "(color):d,"
  /* specs/discord/channel.json:332:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(footer):F,"
  /* specs/discord/channel.json:333:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
                "(image):F,"
  /* specs/discord/channel.json:334:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
                "(thumbnail):F,"
  /* specs/discord/channel.json:335:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
                "(video):F,"
  /* specs/discord/channel.json:336:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
                "(provider):F,"
  /* specs/discord/channel.json:337:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
                "(author):F,"
  /* specs/discord/channel.json:338:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
                "(fields):F,"
                "@arg_switches:b",
  /* specs/discord/channel.json:326:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[DISCORD_EMBED_TITLE_LEN]" }, "option":true, "inject_if_not":null}' */
                p->title,
  /* specs/discord/channel.json:327:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":null}' */
                p->type,
  /* specs/discord/channel.json:328:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[DISCORD_EMBED_DESCRIPTION_LEN]"}, "option":true, "inject_if_not":null}' */
                p->description,
  /* specs/discord/channel.json:329:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->url,
  /* specs/discord/channel.json:330:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
                cee_unix_ms_to_iso8601, &p->timestamp,
  /* specs/discord/channel.json:331:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
                &p->color,
  /* specs/discord/channel.json:332:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
                discord_embed_footer_to_json, p->footer,
  /* specs/discord/channel.json:333:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_image_to_json, p->image,
  /* specs/discord/channel.json:334:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_thumbnail_to_json, p->thumbnail,
  /* specs/discord/channel.json:335:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_video_to_json, p->video,
  /* specs/discord/channel.json:336:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_provider_to_json, p->provider,
  /* specs/discord/channel.json:337:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
                discord_embed_author_to_json, p->author,
  /* specs/discord/channel.json:338:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
                discord_embed_field_list_to_json, p->fields,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_cleanup_v(void *p) {
  discord_embed_cleanup((struct discord_embed *)p);
}

void discord_embed_init_v(void *p) {
  discord_embed_init((struct discord_embed *)p);
}

void discord_embed_free_v(void *p) {
 discord_embed_free((struct discord_embed *)p);
};

void discord_embed_from_json_v(char *json, size_t len, void *pp) {
 discord_embed_from_json(json, len, (struct discord_embed**)pp);
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
  /* specs/discord/channel.json:326:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[DISCORD_EMBED_TITLE_LEN]" }, "option":true, "inject_if_not":null}' */
  // p->title is a scalar
  /* specs/discord/channel.json:327:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":null}' */
  // p->type is a scalar
  /* specs/discord/channel.json:328:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[DISCORD_EMBED_DESCRIPTION_LEN]"}, "option":true, "inject_if_not":null}' */
  // p->description is a scalar
  /* specs/discord/channel.json:329:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.json:330:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
  // p->timestamp is a scalar
  /* specs/discord/channel.json:331:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
  // p->color is a scalar
  /* specs/discord/channel.json:332:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->footer)
    discord_embed_footer_free(d->footer);
  /* specs/discord/channel.json:333:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
  if (d->image)
    discord_embed_image_free(d->image);
  /* specs/discord/channel.json:334:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
  if (d->thumbnail)
    discord_embed_thumbnail_free(d->thumbnail);
  /* specs/discord/channel.json:335:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
  if (d->video)
    discord_embed_video_free(d->video);
  /* specs/discord/channel.json:336:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
  if (d->provider)
    discord_embed_provider_free(d->provider);
  /* specs/discord/channel.json:337:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
  if (d->author)
    discord_embed_author_free(d->author);
  /* specs/discord/channel.json:338:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
  if (d->fields)
    discord_embed_field_list_free(d->fields);
}

void discord_embed_init(struct discord_embed *p) {
  memset(p, 0, sizeof(struct discord_embed));
  /* specs/discord/channel.json:326:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[DISCORD_EMBED_TITLE_LEN]" }, "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:327:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:328:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[DISCORD_EMBED_DESCRIPTION_LEN]"}, "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:329:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:330:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:331:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */

  /* specs/discord/channel.json:332:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
  p->footer = discord_embed_footer_alloc();

  /* specs/discord/channel.json:333:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
  p->image = discord_embed_image_alloc();

  /* specs/discord/channel.json:334:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
  p->thumbnail = discord_embed_thumbnail_alloc();

  /* specs/discord/channel.json:335:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
  p->video = discord_embed_video_alloc();

  /* specs/discord/channel.json:336:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
  p->provider = discord_embed_provider_alloc();

  /* specs/discord/channel.json:337:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
  p->author = discord_embed_author_alloc();

  /* specs/discord/channel.json:338:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */

}
struct discord_embed* discord_embed_alloc() {
  struct discord_embed *p= malloc(sizeof(struct discord_embed));
  discord_embed_init(p);
  return p;
}

void discord_embed_free(struct discord_embed *p) {
  discord_embed_cleanup(p);
  free(p);
}

void discord_embed_list_free(struct discord_embed **p) {
  ntl_free((void**)p, (vfvp)discord_embed_cleanup);
}

void discord_embed_list_from_json(char *str, size_t len, struct discord_embed ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed);
  d.init_elem = NULL;
  d.elem_from_buf = discord_embed_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_list_to_json(char *str, size_t len, struct discord_embed **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_to_json_v);
}


void discord_embed_thumbnail_from_json(char *json, size_t len, struct discord_embed_thumbnail **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_embed_thumbnail *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:347:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):?s,"
  /* specs/discord/channel.json:348:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):?s,"
  /* specs/discord/channel.json:349:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* specs/discord/channel.json:350:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:347:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->url,
  /* specs/discord/channel.json:348:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->proxy_url,
  /* specs/discord/channel.json:349:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* specs/discord/channel.json:350:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_thumbnail_use_default_inject_settings(struct discord_embed_thumbnail *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:347:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->url != NULL)
    p->__M.arg_switches[0] = p->url;

  /* specs/discord/channel.json:348:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->proxy_url != NULL)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/discord/channel.json:349:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/discord/channel.json:350:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_embed_thumbnail_to_json(char *json, size_t len, struct discord_embed_thumbnail *p)
{
  size_t r;
  discord_embed_thumbnail_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:347:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):s,"
  /* specs/discord/channel.json:348:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):s,"
  /* specs/discord/channel.json:349:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* specs/discord/channel.json:350:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b",
  /* specs/discord/channel.json:347:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->url,
  /* specs/discord/channel.json:348:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->proxy_url,
  /* specs/discord/channel.json:349:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* specs/discord/channel.json:350:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_thumbnail_cleanup_v(void *p) {
  discord_embed_thumbnail_cleanup((struct discord_embed_thumbnail *)p);
}

void discord_embed_thumbnail_init_v(void *p) {
  discord_embed_thumbnail_init((struct discord_embed_thumbnail *)p);
}

void discord_embed_thumbnail_free_v(void *p) {
 discord_embed_thumbnail_free((struct discord_embed_thumbnail *)p);
};

void discord_embed_thumbnail_from_json_v(char *json, size_t len, void *pp) {
 discord_embed_thumbnail_from_json(json, len, (struct discord_embed_thumbnail**)pp);
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
  /* specs/discord/channel.json:347:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.json:348:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->proxy_url)
    free(d->proxy_url);
  /* specs/discord/channel.json:349:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->height is a scalar
  /* specs/discord/channel.json:350:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->width is a scalar
}

void discord_embed_thumbnail_init(struct discord_embed_thumbnail *p) {
  memset(p, 0, sizeof(struct discord_embed_thumbnail));
  /* specs/discord/channel.json:347:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:348:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:349:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/channel.json:350:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */

}
struct discord_embed_thumbnail* discord_embed_thumbnail_alloc() {
  struct discord_embed_thumbnail *p= malloc(sizeof(struct discord_embed_thumbnail));
  discord_embed_thumbnail_init(p);
  return p;
}

void discord_embed_thumbnail_free(struct discord_embed_thumbnail *p) {
  discord_embed_thumbnail_cleanup(p);
  free(p);
}

void discord_embed_thumbnail_list_free(struct discord_embed_thumbnail **p) {
  ntl_free((void**)p, (vfvp)discord_embed_thumbnail_cleanup);
}

void discord_embed_thumbnail_list_from_json(char *str, size_t len, struct discord_embed_thumbnail ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_thumbnail);
  d.init_elem = NULL;
  d.elem_from_buf = discord_embed_thumbnail_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_thumbnail_list_to_json(char *str, size_t len, struct discord_embed_thumbnail **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_thumbnail_to_json_v);
}


void discord_embed_video_from_json(char *json, size_t len, struct discord_embed_video **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_embed_video *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:359:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):?s,"
  /* specs/discord/channel.json:360:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):?s,"
  /* specs/discord/channel.json:361:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* specs/discord/channel.json:362:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:359:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->url,
  /* specs/discord/channel.json:360:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->proxy_url,
  /* specs/discord/channel.json:361:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* specs/discord/channel.json:362:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_video_use_default_inject_settings(struct discord_embed_video *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:359:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->url != NULL)
    p->__M.arg_switches[0] = p->url;

  /* specs/discord/channel.json:360:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->proxy_url != NULL)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/discord/channel.json:361:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/discord/channel.json:362:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_embed_video_to_json(char *json, size_t len, struct discord_embed_video *p)
{
  size_t r;
  discord_embed_video_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:359:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):s,"
  /* specs/discord/channel.json:360:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):s,"
  /* specs/discord/channel.json:361:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* specs/discord/channel.json:362:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b",
  /* specs/discord/channel.json:359:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->url,
  /* specs/discord/channel.json:360:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->proxy_url,
  /* specs/discord/channel.json:361:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* specs/discord/channel.json:362:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_video_cleanup_v(void *p) {
  discord_embed_video_cleanup((struct discord_embed_video *)p);
}

void discord_embed_video_init_v(void *p) {
  discord_embed_video_init((struct discord_embed_video *)p);
}

void discord_embed_video_free_v(void *p) {
 discord_embed_video_free((struct discord_embed_video *)p);
};

void discord_embed_video_from_json_v(char *json, size_t len, void *pp) {
 discord_embed_video_from_json(json, len, (struct discord_embed_video**)pp);
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
  /* specs/discord/channel.json:359:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.json:360:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->proxy_url)
    free(d->proxy_url);
  /* specs/discord/channel.json:361:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->height is a scalar
  /* specs/discord/channel.json:362:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->width is a scalar
}

void discord_embed_video_init(struct discord_embed_video *p) {
  memset(p, 0, sizeof(struct discord_embed_video));
  /* specs/discord/channel.json:359:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:360:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:361:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/channel.json:362:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */

}
struct discord_embed_video* discord_embed_video_alloc() {
  struct discord_embed_video *p= malloc(sizeof(struct discord_embed_video));
  discord_embed_video_init(p);
  return p;
}

void discord_embed_video_free(struct discord_embed_video *p) {
  discord_embed_video_cleanup(p);
  free(p);
}

void discord_embed_video_list_free(struct discord_embed_video **p) {
  ntl_free((void**)p, (vfvp)discord_embed_video_cleanup);
}

void discord_embed_video_list_from_json(char *str, size_t len, struct discord_embed_video ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_video);
  d.init_elem = NULL;
  d.elem_from_buf = discord_embed_video_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_video_list_to_json(char *str, size_t len, struct discord_embed_video **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_video_to_json_v);
}


void discord_embed_image_from_json(char *json, size_t len, struct discord_embed_image **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_embed_image *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:371:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):?s,"
  /* specs/discord/channel.json:372:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):?s,"
  /* specs/discord/channel.json:373:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* specs/discord/channel.json:374:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:371:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->url,
  /* specs/discord/channel.json:372:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->proxy_url,
  /* specs/discord/channel.json:373:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* specs/discord/channel.json:374:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_image_use_default_inject_settings(struct discord_embed_image *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:371:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->url != NULL)
    p->__M.arg_switches[0] = p->url;

  /* specs/discord/channel.json:372:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->proxy_url != NULL)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/discord/channel.json:373:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/discord/channel.json:374:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_embed_image_to_json(char *json, size_t len, struct discord_embed_image *p)
{
  size_t r;
  discord_embed_image_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:371:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):s,"
  /* specs/discord/channel.json:372:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_url):s,"
  /* specs/discord/channel.json:373:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(height):d,"
  /* specs/discord/channel.json:374:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(width):d,"
                "@arg_switches:b",
  /* specs/discord/channel.json:371:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->url,
  /* specs/discord/channel.json:372:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->proxy_url,
  /* specs/discord/channel.json:373:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->height,
  /* specs/discord/channel.json:374:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_image_cleanup_v(void *p) {
  discord_embed_image_cleanup((struct discord_embed_image *)p);
}

void discord_embed_image_init_v(void *p) {
  discord_embed_image_init((struct discord_embed_image *)p);
}

void discord_embed_image_free_v(void *p) {
 discord_embed_image_free((struct discord_embed_image *)p);
};

void discord_embed_image_from_json_v(char *json, size_t len, void *pp) {
 discord_embed_image_from_json(json, len, (struct discord_embed_image**)pp);
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
  /* specs/discord/channel.json:371:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.json:372:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->proxy_url)
    free(d->proxy_url);
  /* specs/discord/channel.json:373:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->height is a scalar
  /* specs/discord/channel.json:374:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->width is a scalar
}

void discord_embed_image_init(struct discord_embed_image *p) {
  memset(p, 0, sizeof(struct discord_embed_image));
  /* specs/discord/channel.json:371:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:372:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:373:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/channel.json:374:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */

}
struct discord_embed_image* discord_embed_image_alloc() {
  struct discord_embed_image *p= malloc(sizeof(struct discord_embed_image));
  discord_embed_image_init(p);
  return p;
}

void discord_embed_image_free(struct discord_embed_image *p) {
  discord_embed_image_cleanup(p);
  free(p);
}

void discord_embed_image_list_free(struct discord_embed_image **p) {
  ntl_free((void**)p, (vfvp)discord_embed_image_cleanup);
}

void discord_embed_image_list_from_json(char *str, size_t len, struct discord_embed_image ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_image);
  d.init_elem = NULL;
  d.elem_from_buf = discord_embed_image_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_image_list_to_json(char *str, size_t len, struct discord_embed_image **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_image_to_json_v);
}


void discord_embed_provider_from_json(char *json, size_t len, struct discord_embed_provider **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_embed_provider *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:383:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(name):?s,"
  /* specs/discord/channel.json:384:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(url):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:383:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                &p->name,
  /* specs/discord/channel.json:384:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                &p->url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_provider_use_default_inject_settings(struct discord_embed_provider *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:383:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.json:384:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (p->url != NULL)
    p->__M.arg_switches[1] = p->url;

}

size_t discord_embed_provider_to_json(char *json, size_t len, struct discord_embed_provider *p)
{
  size_t r;
  discord_embed_provider_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:383:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(name):s,"
  /* specs/discord/channel.json:384:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                "(url):s,"
                "@arg_switches:b",
  /* specs/discord/channel.json:383:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                p->name,
  /* specs/discord/channel.json:384:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
                p->url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_provider_cleanup_v(void *p) {
  discord_embed_provider_cleanup((struct discord_embed_provider *)p);
}

void discord_embed_provider_init_v(void *p) {
  discord_embed_provider_init((struct discord_embed_provider *)p);
}

void discord_embed_provider_free_v(void *p) {
 discord_embed_provider_free((struct discord_embed_provider *)p);
};

void discord_embed_provider_from_json_v(char *json, size_t len, void *pp) {
 discord_embed_provider_from_json(json, len, (struct discord_embed_provider**)pp);
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
  /* specs/discord/channel.json:383:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (d->name)
    free(d->name);
  /* specs/discord/channel.json:384:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
}

void discord_embed_provider_init(struct discord_embed_provider *p) {
  memset(p, 0, sizeof(struct discord_embed_provider));
  /* specs/discord/channel.json:383:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */

  /* specs/discord/channel.json:384:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */

}
struct discord_embed_provider* discord_embed_provider_alloc() {
  struct discord_embed_provider *p= malloc(sizeof(struct discord_embed_provider));
  discord_embed_provider_init(p);
  return p;
}

void discord_embed_provider_free(struct discord_embed_provider *p) {
  discord_embed_provider_cleanup(p);
  free(p);
}

void discord_embed_provider_list_free(struct discord_embed_provider **p) {
  ntl_free((void**)p, (vfvp)discord_embed_provider_cleanup);
}

void discord_embed_provider_list_from_json(char *str, size_t len, struct discord_embed_provider ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_provider);
  d.init_elem = NULL;
  d.elem_from_buf = discord_embed_provider_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_provider_list_to_json(char *str, size_t len, struct discord_embed_provider **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_provider_to_json_v);
}


void discord_embed_author_from_json(char *json, size_t len, struct discord_embed_author **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_embed_author *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:393:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":null}' */
                "(name):s,"
  /* specs/discord/channel.json:394:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):?s,"
  /* specs/discord/channel.json:395:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(icon_url):?s,"
  /* specs/discord/channel.json:396:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_icon_url):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:393:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":null}' */
                p->name,
  /* specs/discord/channel.json:394:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->url,
  /* specs/discord/channel.json:395:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->icon_url,
  /* specs/discord/channel.json:396:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_author_use_default_inject_settings(struct discord_embed_author *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:393:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":null}' */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.json:394:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->url != NULL)
    p->__M.arg_switches[1] = p->url;

  /* specs/discord/channel.json:395:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->icon_url != NULL)
    p->__M.arg_switches[2] = p->icon_url;

  /* specs/discord/channel.json:396:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->proxy_icon_url != NULL)
    p->__M.arg_switches[3] = p->proxy_icon_url;

}

size_t discord_embed_author_to_json(char *json, size_t len, struct discord_embed_author *p)
{
  size_t r;
  discord_embed_author_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:393:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":null}' */
                "(name):s,"
  /* specs/discord/channel.json:394:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(url):s,"
  /* specs/discord/channel.json:395:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(icon_url):s,"
  /* specs/discord/channel.json:396:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* specs/discord/channel.json:393:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":null}' */
                p->name,
  /* specs/discord/channel.json:394:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->url,
  /* specs/discord/channel.json:395:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->icon_url,
  /* specs/discord/channel.json:396:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_author_cleanup_v(void *p) {
  discord_embed_author_cleanup((struct discord_embed_author *)p);
}

void discord_embed_author_init_v(void *p) {
  discord_embed_author_init((struct discord_embed_author *)p);
}

void discord_embed_author_free_v(void *p) {
 discord_embed_author_free((struct discord_embed_author *)p);
};

void discord_embed_author_from_json_v(char *json, size_t len, void *pp) {
 discord_embed_author_from_json(json, len, (struct discord_embed_author**)pp);
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
  /* specs/discord/channel.json:393:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":null}' */
  // p->name is a scalar
  /* specs/discord/channel.json:394:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->url)
    free(d->url);
  /* specs/discord/channel.json:395:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->icon_url)
    free(d->icon_url);
  /* specs/discord/channel.json:396:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->proxy_icon_url)
    free(d->proxy_icon_url);
}

void discord_embed_author_init(struct discord_embed_author *p) {
  memset(p, 0, sizeof(struct discord_embed_author));
  /* specs/discord/channel.json:393:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:394:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:395:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:396:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

}
struct discord_embed_author* discord_embed_author_alloc() {
  struct discord_embed_author *p= malloc(sizeof(struct discord_embed_author));
  discord_embed_author_init(p);
  return p;
}

void discord_embed_author_free(struct discord_embed_author *p) {
  discord_embed_author_cleanup(p);
  free(p);
}

void discord_embed_author_list_free(struct discord_embed_author **p) {
  ntl_free((void**)p, (vfvp)discord_embed_author_cleanup);
}

void discord_embed_author_list_from_json(char *str, size_t len, struct discord_embed_author ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_author);
  d.init_elem = NULL;
  d.elem_from_buf = discord_embed_author_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_author_list_to_json(char *str, size_t len, struct discord_embed_author **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_author_to_json_v);
}


void discord_embed_footer_from_json(char *json, size_t len, struct discord_embed_footer **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_embed_footer *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:405:20
     '{ "name": "text", "type": {"base":"char", "dec":"[DISCORD_EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":null}' */
                "(text):s,"
  /* specs/discord/channel.json:406:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                "(icon_url):?s,"
  /* specs/discord/channel.json:407:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(proxy_icon_url):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:405:20
     '{ "name": "text", "type": {"base":"char", "dec":"[DISCORD_EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":null}' */
                p->text,
  /* specs/discord/channel.json:406:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                &p->icon_url,
  /* specs/discord/channel.json:407:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_footer_use_default_inject_settings(struct discord_embed_footer *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:405:20
     '{ "name": "text", "type": {"base":"char", "dec":"[DISCORD_EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":null}' */
  if (p->text != NULL)
    p->__M.arg_switches[0] = p->text;

  /* specs/discord/channel.json:406:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  if (p->icon_url != NULL)
    p->__M.arg_switches[1] = p->icon_url;

  /* specs/discord/channel.json:407:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->proxy_icon_url != NULL)
    p->__M.arg_switches[2] = p->proxy_icon_url;

}

size_t discord_embed_footer_to_json(char *json, size_t len, struct discord_embed_footer *p)
{
  size_t r;
  discord_embed_footer_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:405:20
     '{ "name": "text", "type": {"base":"char", "dec":"[DISCORD_EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":null}' */
                "(text):s,"
  /* specs/discord/channel.json:406:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                "(icon_url):s,"
  /* specs/discord/channel.json:407:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* specs/discord/channel.json:405:20
     '{ "name": "text", "type": {"base":"char", "dec":"[DISCORD_EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":null}' */
                p->text,
  /* specs/discord/channel.json:406:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
                p->icon_url,
  /* specs/discord/channel.json:407:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_footer_cleanup_v(void *p) {
  discord_embed_footer_cleanup((struct discord_embed_footer *)p);
}

void discord_embed_footer_init_v(void *p) {
  discord_embed_footer_init((struct discord_embed_footer *)p);
}

void discord_embed_footer_free_v(void *p) {
 discord_embed_footer_free((struct discord_embed_footer *)p);
};

void discord_embed_footer_from_json_v(char *json, size_t len, void *pp) {
 discord_embed_footer_from_json(json, len, (struct discord_embed_footer**)pp);
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
  /* specs/discord/channel.json:405:20
     '{ "name": "text", "type": {"base":"char", "dec":"[DISCORD_EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":null}' */
  // p->text is a scalar
  /* specs/discord/channel.json:406:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  if (d->icon_url)
    free(d->icon_url);
  /* specs/discord/channel.json:407:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->proxy_icon_url)
    free(d->proxy_icon_url);
}

void discord_embed_footer_init(struct discord_embed_footer *p) {
  memset(p, 0, sizeof(struct discord_embed_footer));
  /* specs/discord/channel.json:405:20
     '{ "name": "text", "type": {"base":"char", "dec":"[DISCORD_EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":null}' */

  /* specs/discord/channel.json:406:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */

  /* specs/discord/channel.json:407:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

}
struct discord_embed_footer* discord_embed_footer_alloc() {
  struct discord_embed_footer *p= malloc(sizeof(struct discord_embed_footer));
  discord_embed_footer_init(p);
  return p;
}

void discord_embed_footer_free(struct discord_embed_footer *p) {
  discord_embed_footer_cleanup(p);
  free(p);
}

void discord_embed_footer_list_free(struct discord_embed_footer **p) {
  ntl_free((void**)p, (vfvp)discord_embed_footer_cleanup);
}

void discord_embed_footer_list_from_json(char *str, size_t len, struct discord_embed_footer ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_footer);
  d.init_elem = NULL;
  d.elem_from_buf = discord_embed_footer_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_footer_list_to_json(char *str, size_t len, struct discord_embed_footer **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_footer_to_json_v);
}


void discord_embed_field_from_json(char *json, size_t len, struct discord_embed_field **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_embed_field *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/channel.json:416:20
     '{ "name": "name", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_NAME_LEN]" }, "inject_if_not":null}' */
                "(name):s,"
  /* specs/discord/channel.json:417:20
     '{ "name": "value", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":null}' */
                "(value):s,"
  /* specs/discord/channel.json:418:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
                "(inline):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.json:416:20
     '{ "name": "name", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_NAME_LEN]" }, "inject_if_not":null}' */
                p->name,
  /* specs/discord/channel.json:417:20
     '{ "name": "value", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":null}' */
                p->value,
  /* specs/discord/channel.json:418:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
                &p->Inline,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_embed_field_use_default_inject_settings(struct discord_embed_field *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.json:416:20
     '{ "name": "name", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_NAME_LEN]" }, "inject_if_not":null}' */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.json:417:20
     '{ "name": "value", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":null}' */
  if (p->value != NULL)
    p->__M.arg_switches[1] = p->value;

  /* specs/discord/channel.json:418:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
  p->__M.arg_switches[2] = &p->Inline;

}

size_t discord_embed_field_to_json(char *json, size_t len, struct discord_embed_field *p)
{
  size_t r;
  discord_embed_field_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.json:416:20
     '{ "name": "name", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_NAME_LEN]" }, "inject_if_not":null}' */
                "(name):s,"
  /* specs/discord/channel.json:417:20
     '{ "name": "value", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":null}' */
                "(value):s,"
  /* specs/discord/channel.json:418:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
                "(inline):b,"
                "@arg_switches:b",
  /* specs/discord/channel.json:416:20
     '{ "name": "name", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_NAME_LEN]" }, "inject_if_not":null}' */
                p->name,
  /* specs/discord/channel.json:417:20
     '{ "name": "value", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":null}' */
                p->value,
  /* specs/discord/channel.json:418:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
                &p->Inline,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_embed_field_cleanup_v(void *p) {
  discord_embed_field_cleanup((struct discord_embed_field *)p);
}

void discord_embed_field_init_v(void *p) {
  discord_embed_field_init((struct discord_embed_field *)p);
}

void discord_embed_field_free_v(void *p) {
 discord_embed_field_free((struct discord_embed_field *)p);
};

void discord_embed_field_from_json_v(char *json, size_t len, void *pp) {
 discord_embed_field_from_json(json, len, (struct discord_embed_field**)pp);
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
  /* specs/discord/channel.json:416:20
     '{ "name": "name", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_NAME_LEN]" }, "inject_if_not":null}' */
  // p->name is a scalar
  /* specs/discord/channel.json:417:20
     '{ "name": "value", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":null}' */
  // p->value is a scalar
  /* specs/discord/channel.json:418:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
  // p->Inline is a scalar
}

void discord_embed_field_init(struct discord_embed_field *p) {
  memset(p, 0, sizeof(struct discord_embed_field));
  /* specs/discord/channel.json:416:20
     '{ "name": "name", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_NAME_LEN]" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:417:20
     '{ "name": "value", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":null}' */

  /* specs/discord/channel.json:418:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */

}
struct discord_embed_field* discord_embed_field_alloc() {
  struct discord_embed_field *p= malloc(sizeof(struct discord_embed_field));
  discord_embed_field_init(p);
  return p;
}

void discord_embed_field_free(struct discord_embed_field *p) {
  discord_embed_field_cleanup(p);
  free(p);
}

void discord_embed_field_list_free(struct discord_embed_field **p) {
  ntl_free((void**)p, (vfvp)discord_embed_field_cleanup);
}

void discord_embed_field_list_from_json(char *str, size_t len, struct discord_embed_field ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_embed_field);
  d.init_elem = NULL;
  d.elem_from_buf = discord_embed_field_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_embed_field_list_to_json(char *str, size_t len, struct discord_embed_field **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_embed_field_to_json_v);
}

