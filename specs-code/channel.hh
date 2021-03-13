/* This file is generated from specs/channel.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#channel-object-channel-types
*/


namespace types {
enum code {
  GUILD_TEXT = 0,
  DM = 1,
  GUILD_VOICE = 2,
  GROUP_DM = 3,
  GUILD_CATEGORY = 4,
  GUILD_NEWS = 5,
  GUILD_STORE = 6,
};
} // namespace types

/* Title: Channel Structure */
/* https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
/* This is defined at specs/channel.json:25:22 */
struct dati {
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */
  discord::channel::types::code type;

  /* specs/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */
  u64_snowflake_t guild_id;

  /* specs/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */
  int position;

  /* specs/channel.json:34:84
     '{"type":{"base":"discord::channel::overwrite::dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
  discord::channel::overwrite::dati **permission_overwrites;

  /* specs/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */
  char name[MAX_NAME_LEN];

  /* specs/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */
  char topic[MAX_TOPIC_LEN];

  /* specs/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */
  bool nsfw;

  /* specs/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t last_message_id;

  /* specs/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/channel.json:47:70
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
  discord::user::dati **recipients;

  /* specs/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */
  char icon[MAX_SHA256_LEN];

  /* specs/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t owner_id;

  /* specs/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t application_id;

  /* specs/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  /* specs/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */
  u64_unix_ms_t last_pin_timestamp;

  /* specs/channel.json:59:82
     '{"type":{"base":"discord::channel::message::dati", "dec":"ntl"}, "name":"messages"}'
  */
  discord::channel::message::dati **messages;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[19];
    void *record_defined[19];
    void *record_null[19];
  } __M; // metadata
};
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
extern void dati_use_default_inject_settings(struct dati *p);
