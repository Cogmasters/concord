/* This file is generated from specs/channel.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#channel-object-channel-types
*/


enum discord_channel_types_code {
  DISCORD_CHANNEL_TYPES_GUILD_TEXT = 0,
  DISCORD_CHANNEL_TYPES_DM = 1,
  DISCORD_CHANNEL_TYPES_GUILD_VOICE = 2,
  DISCORD_CHANNEL_TYPES_GROUP_DM = 3,
  DISCORD_CHANNEL_TYPES_GUILD_CATEGORY = 4,
  DISCORD_CHANNEL_TYPES_GUILD_NEWS = 5,
  DISCORD_CHANNEL_TYPES_GUILD_STORE = 6,
};

/* Title: Channel Structure */
/* https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
/* This is defined at specs/channel.json:25:22 */
struct discord_channel_dati {
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/channel.json:29:88
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types_code"}, "name":"type"}'
  */
  enum discord_channel_types_code type;

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

  /* specs/channel.json:34:88
     '{"type":{"base":"struct discord_channel_overwrite_dati", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
  struct discord_channel_overwrite_dati **permission_overwrites;

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

  /* specs/channel.json:47:75
     '{"type":{"base":"struct discord_user_dati", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
  struct discord_user_dati **recipients;

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

  /* specs/channel.json:59:86
     '{"type":{"base":"struct discord_channel_message_dati", "dec":"ntl"}, "name":"messages"}'
  */
  struct discord_channel_message_dati **messages;

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
extern void discord_channel_dati_cleanup_v(void *p);
extern void discord_channel_dati_cleanup(struct discord_channel_dati *p);
extern void discord_channel_dati_init_v(void *p);
extern void discord_channel_dati_init(struct discord_channel_dati *p);
extern struct discord_channel_dati * discord_channel_dati_alloc();
extern void discord_channel_dati_free_v(void *p);
extern void discord_channel_dati_free(struct discord_channel_dati *p);
extern void discord_channel_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_dati_from_json(char *json, size_t len, struct discord_channel_dati *p);
extern size_t discord_channel_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_dati_to_json(char *json, size_t len, struct discord_channel_dati *p);
extern size_t discord_channel_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_dati_to_query(char *json, size_t len, struct discord_channel_dati *p);
extern void discord_channel_dati_list_free_v(void **p);
extern void discord_channel_dati_list_free(struct discord_channel_dati **p);
extern void discord_channel_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_dati_list_from_json(char *str, size_t len, struct discord_channel_dati ***p);
extern size_t discord_channel_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_dati_list_to_json(char *str, size_t len, struct discord_channel_dati **p);
