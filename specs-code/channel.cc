/* This file is generated from specs/channel.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/channel#channel-object-channel-types
*/
namespace discord {
namespace channel {

void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                "(id):F,"
  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */
                "(type):d,"
  /* specs/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */
                "(guild_id):F,"
  /* specs/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */
                "(position):d,"
  /* specs/channel.json:34:84
     '{"type":{"base":"discord::channel::overwrite::dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
                "(permission_overwrites):F,"
  /* specs/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */
                "(topic):s,"
  /* specs/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */
                "(nsfw):b,"
  /* specs/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */
                "(last_message_id):F,"
  /* specs/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */
                "(bitrate):d,"
  /* specs/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */
                "(user_limit):d,"
  /* specs/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */
                "(rate_limit_per_user):d,"
  /* specs/channel.json:47:70
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
                "(recipients):F,"
  /* specs/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */
                "(icon):s,"
  /* specs/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */
                "(owner_id):F,"
  /* specs/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */
                "(application_id):F,"
  /* specs/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */
                "(parent_id):F,"
  /* specs/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */
                "(last_pin_timestamp):F,"
  /* specs/channel.json:59:82
     '{"type":{"base":"discord::channel::message::dati", "dec":"ntl"}, "name":"messages"}'
  */
                "(messages):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                orka_strtoull, &p->id,
  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */
                &p->type,
  /* specs/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */
                orka_strtoull, &p->guild_id,
  /* specs/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */
                &p->position,
  /* specs/channel.json:34:84
     '{"type":{"base":"discord::channel::overwrite::dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
                discord::channel::overwrite::dati_list_from_json, &p->permission_overwrites,
  /* specs/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */
                p->topic,
  /* specs/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */
                &p->nsfw,
  /* specs/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */
                orka_strtoull, &p->last_message_id,
  /* specs/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */
                &p->bitrate,
  /* specs/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */
                &p->user_limit,
  /* specs/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */
                &p->rate_limit_per_user,
  /* specs/channel.json:47:70
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
                discord::user::dati_list_from_json, &p->recipients,
  /* specs/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */
                p->icon,
  /* specs/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */
                orka_strtoull, &p->owner_id,
  /* specs/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */
                orka_strtoull, &p->application_id,
  /* specs/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */
                orka_strtoull, &p->parent_id,
  /* specs/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */
                orka_iso8601_to_unix_ms, &p->last_pin_timestamp,
  /* specs/channel.json:59:82
     '{"type":{"base":"discord::channel::message::dati", "dec":"ntl"}, "name":"messages"}'
  */
                discord::channel::message::dati_list_from_json, &p->messages,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                "(id):|F|,"
  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */
                "(type):d,"
  /* specs/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */
                "(guild_id):|F|,"
  /* specs/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */
                "(position):d,"
  /* specs/channel.json:34:84
     '{"type":{"base":"discord::channel::overwrite::dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
                "(permission_overwrites):F,"
  /* specs/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */
                "(topic):s,"
  /* specs/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */
                "(nsfw):b,"
  /* specs/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */
                "(last_message_id):|F|,"
  /* specs/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */
                "(bitrate):d,"
  /* specs/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */
                "(user_limit):d,"
  /* specs/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */
                "(rate_limit_per_user):d,"
  /* specs/channel.json:47:70
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
                "(recipients):F,"
  /* specs/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */
                "(icon):s,"
  /* specs/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */
                "(owner_id):|F|,"
  /* specs/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */
                "(application_id):|F|,"
  /* specs/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */
                "(parent_id):|F|,"
  /* specs/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */
                "(last_pin_timestamp):|F|,"
  /* specs/channel.json:59:82
     '{"type":{"base":"discord::channel::message::dati", "dec":"ntl"}, "name":"messages"}'
  */
                "(messages):F,"
                "@arg_switches:b",
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                orka_ulltostr, &p->id,
  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */
                &p->type,
  /* specs/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */
                &p->position,
  /* specs/channel.json:34:84
     '{"type":{"base":"discord::channel::overwrite::dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
                discord::channel::overwrite::dati_list_to_json, p->permission_overwrites,
  /* specs/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */
                p->topic,
  /* specs/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */
                &p->nsfw,
  /* specs/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */
                orka_ulltostr, &p->last_message_id,
  /* specs/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */
                &p->bitrate,
  /* specs/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */
                &p->user_limit,
  /* specs/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */
                &p->rate_limit_per_user,
  /* specs/channel.json:47:70
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
                discord::user::dati_list_to_json, p->recipients,
  /* specs/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */
                p->icon,
  /* specs/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */
                orka_ulltostr, &p->owner_id,
  /* specs/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */
                orka_ulltostr, &p->application_id,
  /* specs/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */
                orka_ulltostr, &p->parent_id,
  /* specs/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */
                orka_unix_ms_to_iso8601, &p->last_pin_timestamp,
  /* specs/channel.json:59:82
     '{"type":{"base":"discord::channel::message::dati", "dec":"ntl"}, "name":"messages"}'
  */
                discord::channel::message::dati_list_to_json, p->messages,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */
  p->__M.arg_switches[1] = &p->type;

  /* specs/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */
  if (p->guild_id != 0)
    p->__M.arg_switches[2] = &p->guild_id;

  /* specs/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */
  if (p->position != 0)
    p->__M.arg_switches[3] = &p->position;

  /* specs/channel.json:34:84
     '{"type":{"base":"discord::channel::overwrite::dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
  if (p->permission_overwrites != NULL)
    p->__M.arg_switches[4] = p->permission_overwrites;

  /* specs/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[5] = p->name;

  /* specs/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */
  if (strlen(p->topic) != 0)
    p->__M.arg_switches[6] = p->topic;

  /* specs/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */
  if (p->nsfw != false)
    p->__M.arg_switches[7] = &p->nsfw;

  /* specs/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */
  if (p->last_message_id != 0)
    p->__M.arg_switches[8] = &p->last_message_id;

  /* specs/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */
  if (p->bitrate != 0)
    p->__M.arg_switches[9] = &p->bitrate;

  /* specs/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */
  if (p->user_limit != 0)
    p->__M.arg_switches[10] = &p->user_limit;

  /* specs/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */
  if (p->rate_limit_per_user != 0)
    p->__M.arg_switches[11] = &p->rate_limit_per_user;

  /* specs/channel.json:47:70
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
  if (p->recipients != NULL)
    p->__M.arg_switches[12] = p->recipients;

  /* specs/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */
  if (strlen(p->icon) != 0)
    p->__M.arg_switches[13] = p->icon;

  /* specs/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */
  if (p->owner_id != 0)
    p->__M.arg_switches[14] = &p->owner_id;

  /* specs/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */
  if (p->application_id != 0)
    p->__M.arg_switches[15] = &p->application_id;

  /* specs/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */
  if (p->parent_id != 0)
    p->__M.arg_switches[16] = &p->parent_id;

  /* specs/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */
  if (p->last_pin_timestamp != 0)
    p->__M.arg_switches[17] = &p->last_pin_timestamp;

  /* specs/channel.json:59:82
     '{"type":{"base":"discord::channel::message::dati", "dec":"ntl"}, "name":"messages"}'
  */
  p->__M.arg_switches[18] = p->messages;

}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void dati_cleanup_v(void *p) {
  dati_cleanup((struct dati *)p);
}

void dati_init_v(void *p) {
  dati_init((struct dati *)p);
}

void dati_free_v(void *p) {
 dati_free((struct dati *)p);
};

void dati_from_json_v(char *json, size_t len, void *p) {
 dati_from_json(json, len, (struct dati*)p);
}

size_t dati_to_json_v(char *json, size_t len, void *p) {
  return dati_to_json(json, len, (struct dati*)p);
}

void dati_list_free_v(void **p) {
  dati_list_free((struct dati**)p);
}

void dati_list_from_json_v(char *str, size_t len, void *p) {
  dati_list_from_json(str, len, (struct dati ***)p);
}

size_t dati_list_to_json_v(char *str, size_t len, void *p){
  return dati_list_to_json(str, len, (struct dati **)p);
}


void dati_cleanup(struct dati *d) {
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  //p->id is a scalar
  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */
  //p->type is a scalar
  /* specs/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */
  //p->guild_id is a scalar
  /* specs/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */
  //p->position is a scalar
  /* specs/channel.json:34:84
     '{"type":{"base":"discord::channel::overwrite::dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
  if (d->permission_overwrites)
    discord::channel::overwrite::dati_list_free(d->permission_overwrites);
  /* specs/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */
  //p->topic is a scalar
  /* specs/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */
  //p->nsfw is a scalar
  /* specs/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */
  //p->last_message_id is a scalar
  /* specs/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */
  //p->bitrate is a scalar
  /* specs/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */
  //p->user_limit is a scalar
  /* specs/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */
  //p->rate_limit_per_user is a scalar
  /* specs/channel.json:47:70
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
  if (d->recipients)
    discord::user::dati_list_free(d->recipients);
  /* specs/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */
  //p->icon is a scalar
  /* specs/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */
  //p->owner_id is a scalar
  /* specs/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */
  //p->application_id is a scalar
  /* specs/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */
  //p->parent_id is a scalar
  /* specs/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */
  //p->last_pin_timestamp is a scalar
  /* specs/channel.json:59:82
     '{"type":{"base":"discord::channel::message::dati", "dec":"ntl"}, "name":"messages"}'
  */
  if (d->messages)
    discord::channel::message::dati_list_free(d->messages);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */

  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */

  /* specs/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */

  /* specs/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */

  /* specs/channel.json:34:84
     '{"type":{"base":"discord::channel::overwrite::dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */

  /* specs/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */

  /* specs/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */

  /* specs/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */

  /* specs/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */

  /* specs/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */

  /* specs/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.json:47:70
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */

  /* specs/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */

  /* specs/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.json:59:82
     '{"type":{"base":"discord::channel::message::dati", "dec":"ntl"}, "name":"messages"}'
  */

}
struct dati* dati_alloc() {
  struct dati *p= (struct dati*)malloc(sizeof(struct dati));
  dati_init(p);
  return p;
}

void dati_free(struct dati *p) {
  dati_cleanup(p);
  free(p);
}

void dati_list_free(struct dati **p) {
  ntl_free((void**)p, (vfvp)dati_cleanup);
}

void dati_list_from_json(char *str, size_t len, struct dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct dati);
  d.init_elem = dati_init_v;
  d.elem_from_buf = dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  orka_str_to_ntl(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace channel
} // namespace discord
