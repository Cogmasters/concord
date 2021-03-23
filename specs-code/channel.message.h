/* This file is generated from specs/channel.message.json, Please don't edit it. */
/*

*/


enum discord_channel_message_sticker_format_type_code {
  DISCORD_CHANNEL_MESSAGE_STICKER_FORMAT_TYPE_PNG = 1,
  DISCORD_CHANNEL_MESSAGE_STICKER_FORMAT_TYPE_APNG = 2,
  DISCORD_CHANNEL_MESSAGE_STICKER_FORMAT_TYPE_LOTTIE = 3,
};

/* https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure */
/* This is defined at specs/channel.message.json:20:22 */
struct discord_channel_message_sticker_dati {
  /* specs/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t pack_id;

  /* specs/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
  char *description;

  /* specs/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */
  char *tags;

  /* specs/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
  char asset[MAX_SHA256_LEN];

  /* specs/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */
  char preview_asset[MAX_SHA256_LEN];

  /* specs/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_sticker_format_type_code"}}'
  */
  enum discord_channel_message_sticker_format_type_code type;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
};
extern void discord_channel_message_sticker_dati_cleanup_v(void *p);
extern void discord_channel_message_sticker_dati_cleanup(struct discord_channel_message_sticker_dati *p);
extern void discord_channel_message_sticker_dati_init_v(void *p);
extern void discord_channel_message_sticker_dati_init(struct discord_channel_message_sticker_dati *p);
extern struct discord_channel_message_sticker_dati * discord_channel_message_sticker_dati_alloc();
extern void discord_channel_message_sticker_dati_free_v(void *p);
extern void discord_channel_message_sticker_dati_free(struct discord_channel_message_sticker_dati *p);
extern void discord_channel_message_sticker_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_message_sticker_dati_from_json(char *json, size_t len, struct discord_channel_message_sticker_dati *p);
extern size_t discord_channel_message_sticker_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_sticker_dati_to_json(char *json, size_t len, struct discord_channel_message_sticker_dati *p);
extern size_t discord_channel_message_sticker_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_sticker_dati_to_query(char *json, size_t len, struct discord_channel_message_sticker_dati *p);
extern void discord_channel_message_sticker_dati_list_free_v(void **p);
extern void discord_channel_message_sticker_dati_list_free(struct discord_channel_message_sticker_dati **p);
extern void discord_channel_message_sticker_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_message_sticker_dati_list_from_json(char *str, size_t len, struct discord_channel_message_sticker_dati ***p);
extern size_t discord_channel_message_sticker_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_message_sticker_dati_list_to_json(char *str, size_t len, struct discord_channel_message_sticker_dati **p);


enum discord_channel_message_flags_code {
  DISCORD_CHANNEL_MESSAGE_FLAGS_CROSSPOSTED = 1, // 1<<0
  DISCORD_CHANNEL_MESSAGE_FLAGS_IS_CROSSPOST = 2, // 1<<1
  DISCORD_CHANNEL_MESSAGE_FLAGS_SUPRESS_EMBEDS = 4, // 1<<2
  DISCORD_CHANNEL_MESSAGE_FLAGS_SOURCE_MESSAGE_DELETED = 8, // 1<<3
  DISCORD_CHANNEL_MESSAGE_FLAGS_URGENT = 16, // 1<<4
};

/* Title: Message Reference Structure */
/* https://discord.com/developers/docs/resources/channel#message-object-message-reference-structure */
/* This is defined at specs/channel.message.json:50:22 */
struct discord_channel_message_reference_dati {
  /* specs/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t message_id;

  /* specs/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t channel_id;

  /* specs/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t guild_id;

  /* specs/channel.message.json:58:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, 
         "option":true, "inject_if_not":false}'
  */
  bool fail_if_not_exists;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_channel_message_reference_dati_cleanup_v(void *p);
extern void discord_channel_message_reference_dati_cleanup(struct discord_channel_message_reference_dati *p);
extern void discord_channel_message_reference_dati_init_v(void *p);
extern void discord_channel_message_reference_dati_init(struct discord_channel_message_reference_dati *p);
extern struct discord_channel_message_reference_dati * discord_channel_message_reference_dati_alloc();
extern void discord_channel_message_reference_dati_free_v(void *p);
extern void discord_channel_message_reference_dati_free(struct discord_channel_message_reference_dati *p);
extern void discord_channel_message_reference_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_message_reference_dati_from_json(char *json, size_t len, struct discord_channel_message_reference_dati *p);
extern size_t discord_channel_message_reference_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_reference_dati_to_json(char *json, size_t len, struct discord_channel_message_reference_dati *p);
extern size_t discord_channel_message_reference_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_reference_dati_to_query(char *json, size_t len, struct discord_channel_message_reference_dati *p);
extern void discord_channel_message_reference_dati_list_free_v(void **p);
extern void discord_channel_message_reference_dati_list_free(struct discord_channel_message_reference_dati **p);
extern void discord_channel_message_reference_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_message_reference_dati_list_from_json(char *str, size_t len, struct discord_channel_message_reference_dati ***p);
extern size_t discord_channel_message_reference_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_message_reference_dati_list_to_json(char *str, size_t len, struct discord_channel_message_reference_dati **p);

/* Title: Message Application Structure */
/* https://discord.com/developers/docs/resources/channel#message-object-message-application-structure */
/* This is defined at specs/channel.message.json:66:22 */
struct discord_channel_message_application_dati {
  /* specs/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  char *cover_image;

  /* specs/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
  char *description;

  /* specs/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */
  char *icon;

  /* specs/channel.message.json:73:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
  char *name;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
};
extern void discord_channel_message_application_dati_cleanup_v(void *p);
extern void discord_channel_message_application_dati_cleanup(struct discord_channel_message_application_dati *p);
extern void discord_channel_message_application_dati_init_v(void *p);
extern void discord_channel_message_application_dati_init(struct discord_channel_message_application_dati *p);
extern struct discord_channel_message_application_dati * discord_channel_message_application_dati_alloc();
extern void discord_channel_message_application_dati_free_v(void *p);
extern void discord_channel_message_application_dati_free(struct discord_channel_message_application_dati *p);
extern void discord_channel_message_application_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_message_application_dati_from_json(char *json, size_t len, struct discord_channel_message_application_dati *p);
extern size_t discord_channel_message_application_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_application_dati_to_json(char *json, size_t len, struct discord_channel_message_application_dati *p);
extern size_t discord_channel_message_application_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_application_dati_to_query(char *json, size_t len, struct discord_channel_message_application_dati *p);
extern void discord_channel_message_application_dati_list_free_v(void **p);
extern void discord_channel_message_application_dati_list_free(struct discord_channel_message_application_dati **p);
extern void discord_channel_message_application_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_message_application_dati_list_from_json(char *str, size_t len, struct discord_channel_message_application_dati ***p);
extern size_t discord_channel_message_application_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_message_application_dati_list_to_json(char *str, size_t len, struct discord_channel_message_application_dati **p);


enum discord_channel_message_activity_types_code {
  DISCORD_CHANNEL_MESSAGE_ACTIVITY_TYPES_JOIN = 1,
  DISCORD_CHANNEL_MESSAGE_ACTIVITY_TYPES_SPECTATE = 2,
  DISCORD_CHANNEL_MESSAGE_ACTIVITY_TYPES_LISTEN = 3,
  DISCORD_CHANNEL_MESSAGE_ACTIVITY_TYPES_JOIN_REQUEST = 5,
};

/* Title: Message Activity Structure */
/* https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure */
/* This is defined at specs/channel.message.json:92:22 */
struct discord_channel_message_activity_dati {
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_activity_types_code"}}'
  */
  enum discord_channel_message_activity_types_code type;

  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  char *party_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
};
extern void discord_channel_message_activity_dati_cleanup_v(void *p);
extern void discord_channel_message_activity_dati_cleanup(struct discord_channel_message_activity_dati *p);
extern void discord_channel_message_activity_dati_init_v(void *p);
extern void discord_channel_message_activity_dati_init(struct discord_channel_message_activity_dati *p);
extern struct discord_channel_message_activity_dati * discord_channel_message_activity_dati_alloc();
extern void discord_channel_message_activity_dati_free_v(void *p);
extern void discord_channel_message_activity_dati_free(struct discord_channel_message_activity_dati *p);
extern void discord_channel_message_activity_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_message_activity_dati_from_json(char *json, size_t len, struct discord_channel_message_activity_dati *p);
extern size_t discord_channel_message_activity_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_activity_dati_to_json(char *json, size_t len, struct discord_channel_message_activity_dati *p);
extern size_t discord_channel_message_activity_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_activity_dati_to_query(char *json, size_t len, struct discord_channel_message_activity_dati *p);
extern void discord_channel_message_activity_dati_list_free_v(void **p);
extern void discord_channel_message_activity_dati_list_free(struct discord_channel_message_activity_dati **p);
extern void discord_channel_message_activity_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_message_activity_dati_list_from_json(char *str, size_t len, struct discord_channel_message_activity_dati ***p);
extern size_t discord_channel_message_activity_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_message_activity_dati_list_to_json(char *str, size_t len, struct discord_channel_message_activity_dati **p);


enum discord_channel_message_types_code {
  DISCORD_CHANNEL_MESSAGE_TYPES_DEFAULT = 0,
  DISCORD_CHANNEL_MESSAGE_TYPES_RECIPIENT_ADD = 1,
  DISCORD_CHANNEL_MESSAGE_TYPES_RECIPIENT_REMOVE = 3,
  DISCORD_CHANNEL_MESSAGE_TYPES_CALL = 5,
  DISCORD_CHANNEL_MESSAGE_TYPES_CHANNEL_NAME_CHANGE = 5,
  DISCORD_CHANNEL_MESSAGE_TYPES_CHANNEL_ICON_CHANGE = 5,
  DISCORD_CHANNEL_MESSAGE_TYPES_CHANNEL_PINNED_MESSAGE = 5,
  DISCORD_CHANNEL_MESSAGE_TYPES_GUILD_MEMBER_JOIN = 5,
  DISCORD_CHANNEL_MESSAGE_TYPES_USER_PREMIUM_GUILD_SUBSCRIPTION = 5,
  DISCORD_CHANNEL_MESSAGE_TYPES_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
  DISCORD_CHANNEL_MESSAGE_TYPES_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
  DISCORD_CHANNEL_MESSAGE_TYPES_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
  DISCORD_CHANNEL_MESSAGE_TYPES_CHANNEL_FOLLOW_ADD = 12,
  DISCORD_CHANNEL_MESSAGE_TYPES_GUILD_DISCOVERY_DISQUALIFIED = 14,
  DISCORD_CHANNEL_MESSAGE_TYPES_GUILD_DISCOVERY_REQUALIFIED = 15,
  DISCORD_CHANNEL_MESSAGE_TYPES_REPLY = 19,
  DISCORD_CHANNEL_MESSAGE_TYPES_APPLICATION_COMMAND = 20,
};

/* Title: Message Structure */
/* https://discord.com/developers/docs/resources/channel#message-object */
/* This is defined at specs/channel.message.json:128:22 */
struct discord_channel_message_dati {
  /* specs/channel.message.json:130:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/channel.message.json:131:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}'
  */
  u64_snowflake_t channel_id;

  /* specs/channel.message.json:132:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
          "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t guild_id;

  /* specs/channel.message.json:134:74
     '{"type":{"base":"struct discord_user_dati", "dec":"*"}, "name":"author"}'
  */
  struct discord_user_dati *author;

  /* specs/channel.message.json:135:82
     '{"type":{"base":"struct discord_guild_member_dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  struct discord_guild_member_dati *member; // partial guild member object

  /* specs/channel.message.json:137:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}'
  */
  char *content;

  /* specs/channel.message.json:138:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}'
  */
  u64_unix_ms_t timestamp;

  /* specs/channel.message.json:139:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp",
          "inject_if_not":0}'
  */
  u64_unix_ms_t edited_timestamp;

  /* specs/channel.message.json:141:43
     '{"type":{"base":"bool"}, "name":"tts"}'
  */
  bool tts;

  /* specs/channel.message.json:142:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}'
  */
  bool mention_everyone;

  /* specs/channel.message.json:143:76
     '{"type":{"base":"struct discord_user_dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
  struct discord_user_dati **mentions; // array of user objects, with an additional partial member field

  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
  ja_u64 **mention_roles; // array of role object ids

  /* specs/channel.message.json:146:87
     '{"type":{"base":"struct discord_channel_mention_dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
  struct discord_channel_mention_dati **mention_channels;

  /* specs/channel.message.json:148:90
     '{"type":{"base":"struct discord_channel_attachment_dati", "dec":"ntl"}, "name":"attachments"}'
  */
  struct discord_channel_attachment_dati **attachments;

  /* specs/channel.message.json:149:85
     '{"type":{"base":"struct discord_channel_embed_dati", "dec":"ntl"}, "name":"embeds"}'
  */
  struct discord_channel_embed_dati **embeds;

  /* specs/channel.message.json:150:87
     '{"type":{"base":"struct discord_channel_reaction_dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
  struct discord_channel_reaction_dati **reactions;

  /* specs/channel.message.json:152:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string",
          "option":true }'
  */
  char *nonce; // integer or string

  /* specs/channel.message.json:154:43
     '{"type":{"base":"bool"}, "name":"pinned"}'
  */
  bool pinned;

  /* specs/channel.message.json:155:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id",
          "option":true }'
  */
  u64_snowflake_t webhook_id;

  /* specs/channel.message.json:157:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_types_code"}, "name":"type"}'
  */
  enum discord_channel_message_types_code type;

  /* specs/channel.message.json:158:94
     '{"type":{"base":"struct discord_channel_message_activity_dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  struct discord_channel_message_activity_dati *activity;

  /* specs/channel.message.json:160:99
     '{"type":{"base":"struct discord_channel_message_application_dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
  struct discord_channel_message_application_dati **application;

  /* specs/channel.message.json:162:95
     '{"type":{"base":"struct discord_channel_message_reference_dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  struct discord_channel_message_reference_dati *message_reference;

  /* specs/channel.message.json:164:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_flags_code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
  enum discord_channel_message_flags_code flags;

  /* specs/channel.message.json:166:95
     '{"type":{"base":"struct discord_channel_message_sticker_dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
  struct discord_channel_message_sticker_dati **stickers; // array of sticker objects

  /* specs/channel.message.json:168:85
     '{"type":{"base":"struct discord_channel_message_dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
  struct discord_channel_message_dati *referenced_message; // this will cause recursive allocation if allocating as the parent

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[26];
    void *record_defined[26];
    void *record_null[26];
  } __M; // metadata
};
extern void discord_channel_message_dati_cleanup_v(void *p);
extern void discord_channel_message_dati_cleanup(struct discord_channel_message_dati *p);
extern void discord_channel_message_dati_init_v(void *p);
extern void discord_channel_message_dati_init(struct discord_channel_message_dati *p);
extern struct discord_channel_message_dati * discord_channel_message_dati_alloc();
extern void discord_channel_message_dati_free_v(void *p);
extern void discord_channel_message_dati_free(struct discord_channel_message_dati *p);
extern void discord_channel_message_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_channel_message_dati_from_json(char *json, size_t len, struct discord_channel_message_dati *p);
extern size_t discord_channel_message_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_dati_to_json(char *json, size_t len, struct discord_channel_message_dati *p);
extern size_t discord_channel_message_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_channel_message_dati_to_query(char *json, size_t len, struct discord_channel_message_dati *p);
extern void discord_channel_message_dati_list_free_v(void **p);
extern void discord_channel_message_dati_list_free(struct discord_channel_message_dati **p);
extern void discord_channel_message_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_message_dati_list_from_json(char *str, size_t len, struct discord_channel_message_dati ***p);
extern size_t discord_channel_message_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_message_dati_list_to_json(char *str, size_t len, struct discord_channel_message_dati **p);
