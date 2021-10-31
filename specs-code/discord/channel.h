/* This file is generated from specs/discord/channel.json, Please don't edit it. */
/**
 * @file specs-code/discord/channel.h
 * @see https://discord.com/developers/docs/resources/channel
 */



/* Channel Types */
/* defined at specs/discord/channel.json:6:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#channel-object-channel-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_channel_types_print(enum discord_channel_types code)`
 *   * :code:`enum discord_channel_types discord_channel_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_channel_types {
  DISCORD_CHANNEL_GUILD_TEXT = 0,
  DISCORD_CHANNEL_DM = 1,
  DISCORD_CHANNEL_GUILD_VOICE = 2,
  DISCORD_CHANNEL_GROUP_DM = 3,
  DISCORD_CHANNEL_GUILD_CATEGORY = 4,
  DISCORD_CHANNEL_GUILD_NEWS = 5,
  DISCORD_CHANNEL_GUILD_STORE = 6,
  DISCORD_CHANNEL_GUILD_NEWS_THREAD = 10,
  DISCORD_CHANNEL_GUILD_PUBLIC_THREAD = 11,
  DISCORD_CHANNEL_GUILD_PRIVATE_THREAD = 12,
  DISCORD_CHANNEL_GUILD_STAGE_VOICE = 13,
};
extern char* discord_channel_types_print(enum discord_channel_types);
extern enum discord_channel_types discord_channel_types_eval(char*);
extern void discord_channel_types_list_free_v(void **p);
extern void discord_channel_types_list_free(enum discord_channel_types **p);
extern void discord_channel_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_types_list_from_json(char *str, size_t len, enum discord_channel_types ***p);
extern size_t discord_channel_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_types_list_to_json(char *str, size_t len, enum discord_channel_types **p);

/* Channel Structure */
/* defined at specs/discord/channel.json:29:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#channel-object-channel-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_channel_init(struct discord_channel *)`
 *   * Cleanup:

 *     * :code:`void discord_channel_cleanup(struct discord_channel *)`
 *     * :code:`void discord_channel_list_free(struct discord_channel **)`
 *   * JSON Decoder:

 *     * :code:`void discord_channel_from_json(char *rbuf, size_t len, struct discord_channel **)`
 *     * :code:`void discord_channel_list_from_json(char *rbuf, size_t len, struct discord_channel ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_channel_to_json(char *wbuf, size_t len, struct discord_channel *)`
 *     * :code:`void discord_channel_list_to_json(char *wbuf, size_t len, struct discord_channel **)`
 * @endverbatim
 */
struct discord_channel {
  /* specs/discord/channel.json:32:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:33:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}' */
  enum discord_channel_types type;

  /* specs/discord/channel.json:34:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:36:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }' */
  int position;

  /* specs/discord/channel.json:38:75
     '{"type":{"base":"struct discord_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
  struct discord_overwrite **permission_overwrites;

  /* specs/discord/channel.json:40:53
     '{"type":{"base":"char", "dec":"*"}, "name":"name", "option":true, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:41:53
     '{"type":{"base":"char", "dec":"*"}, "name":"topic", "option":true, "inject_if_not":null }' */
  char *topic;

  /* specs/discord/channel.json:42:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
  bool nsfw;

  /* specs/discord/channel.json:43:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t last_message_id;

  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
  int bitrate;

  /* specs/discord/channel.json:46:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
  int user_limit;

  /* specs/discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
  int rate_limit_per_user;

  /* specs/discord/channel.json:49:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
  struct discord_user **recipients;

  /* specs/discord/channel.json:51:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "name":"icon",
         "option":true, "inject_if_not":""}' */
  char icon[ORCA_LIMITS_SHA256];

  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t owner_id;

  /* specs/discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t application_id;

  /* specs/discord/channel.json:57:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.json:59:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
  u64_unix_ms_t last_pin_timestamp;

  /* specs/discord/channel.json:61:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
  struct discord_message **messages;

};
extern void discord_channel_cleanup_v(void *p);
extern void discord_channel_cleanup(struct discord_channel *p);
extern void discord_channel_init_v(void *p);
extern void discord_channel_init(struct discord_channel *p);
extern void discord_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_from_json(char *json, size_t len, struct discord_channel **pp);
extern size_t discord_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_to_json(char *json, size_t len, struct discord_channel *p);
extern void discord_channel_list_free_v(void **p);
extern void discord_channel_list_free(struct discord_channel **p);
extern void discord_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_list_from_json(char *str, size_t len, struct discord_channel ***p);
extern size_t discord_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_list_to_json(char *str, size_t len, struct discord_channel **p);


/* Message Sticker Format Types */
/* defined at specs/discord/channel.json:64:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-sticker-format-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_message_sticker_format_types_print(enum discord_message_sticker_format_types code)`
 *   * :code:`enum discord_message_sticker_format_types discord_message_sticker_format_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_message_sticker_format_types {
  DISCORD_MESSAGE_STICKER_PNG = 1,
  DISCORD_MESSAGE_STICKER_APNG = 2,
  DISCORD_MESSAGE_STICKER_LOTTIE = 3,
};
extern char* discord_message_sticker_format_types_print(enum discord_message_sticker_format_types);
extern enum discord_message_sticker_format_types discord_message_sticker_format_types_eval(char*);
extern void discord_message_sticker_format_types_list_free_v(void **p);
extern void discord_message_sticker_format_types_list_free(enum discord_message_sticker_format_types **p);
extern void discord_message_sticker_format_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_sticker_format_types_list_from_json(char *str, size_t len, enum discord_message_sticker_format_types ***p);
extern size_t discord_message_sticker_format_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_sticker_format_types_list_to_json(char *str, size_t len, enum discord_message_sticker_format_types **p);

/* Message Sticker Structure */
/* defined at specs/discord/channel.json:80:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_sticker_init(struct discord_message_sticker *)`
 *   * Cleanup:

 *     * :code:`void discord_message_sticker_cleanup(struct discord_message_sticker *)`
 *     * :code:`void discord_message_sticker_list_free(struct discord_message_sticker **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_sticker_from_json(char *rbuf, size_t len, struct discord_message_sticker **)`
 *     * :code:`void discord_message_sticker_list_from_json(char *rbuf, size_t len, struct discord_message_sticker ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_sticker_to_json(char *wbuf, size_t len, struct discord_message_sticker *)`
 *     * :code:`void discord_message_sticker_list_to_json(char *wbuf, size_t len, struct discord_message_sticker **)`
 * @endverbatim
 */
struct discord_message_sticker {
  /* specs/discord/channel.json:82:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:83:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t pack_id;

  /* specs/discord/channel.json:84:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/channel.json:85:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  char *description;

  /* specs/discord/channel.json:86:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
  char *tags;

  /* specs/discord/channel.json:87:18
     '{"name":"asset","type":{"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */
  char asset[ORCA_LIMITS_SHA256];

  /* specs/discord/channel.json:88:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "option":true, "inject_if_not":""}' */
  char preview_asset[ORCA_LIMITS_SHA256];

  /* specs/discord/channel.json:90:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
  enum discord_message_sticker_format_types type;

};
extern void discord_message_sticker_cleanup_v(void *p);
extern void discord_message_sticker_cleanup(struct discord_message_sticker *p);
extern void discord_message_sticker_init_v(void *p);
extern void discord_message_sticker_init(struct discord_message_sticker *p);
extern void discord_message_sticker_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_sticker_from_json(char *json, size_t len, struct discord_message_sticker **pp);
extern size_t discord_message_sticker_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_sticker_to_json(char *json, size_t len, struct discord_message_sticker *p);
extern void discord_message_sticker_list_free_v(void **p);
extern void discord_message_sticker_list_free(struct discord_message_sticker **p);
extern void discord_message_sticker_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_sticker_list_from_json(char *str, size_t len, struct discord_message_sticker ***p);
extern size_t discord_message_sticker_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_sticker_list_to_json(char *str, size_t len, struct discord_message_sticker **p);


/* Message Flags */
/* defined at specs/discord/channel.json:93:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_message_flags_print(enum discord_message_flags code)`
 *   * :code:`enum discord_message_flags discord_message_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_message_flags {
  DISCORD_MESSAGE_CROSSPOSTED = 1, /**< 1<<0 */
  DISCORD_MESSAGE_IS_CROSSPOST = 2, /**< 1<<1 */
  DISCORD_MESSAGE_SUPRESS_EMBEDS = 4, /**< 1<<2 */
  DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED = 8, /**< 1<<3 */
  DISCORD_MESSAGE_URGENT = 16, /**< 1<<4 */
};
extern char* discord_message_flags_print(enum discord_message_flags);
extern enum discord_message_flags discord_message_flags_eval(char*);
extern void discord_message_flags_list_free_v(void **p);
extern void discord_message_flags_list_free(enum discord_message_flags **p);
extern void discord_message_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_flags_list_from_json(char *str, size_t len, enum discord_message_flags ***p);
extern size_t discord_message_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_flags_list_to_json(char *str, size_t len, enum discord_message_flags **p);

/* Message Reference Structure */
/* defined at specs/discord/channel.json:110:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-reference-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_reference_init(struct discord_message_reference *)`
 *   * Cleanup:

 *     * :code:`void discord_message_reference_cleanup(struct discord_message_reference *)`
 *     * :code:`void discord_message_reference_list_free(struct discord_message_reference **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_reference_from_json(char *rbuf, size_t len, struct discord_message_reference **)`
 *     * :code:`void discord_message_reference_list_from_json(char *rbuf, size_t len, struct discord_message_reference ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_reference_to_json(char *wbuf, size_t len, struct discord_message_reference *)`
 *     * :code:`void discord_message_reference_list_to_json(char *wbuf, size_t len, struct discord_message_reference **)`
 * @endverbatim
 */
struct discord_message_reference {
  /* specs/discord/channel.json:112:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t message_id;

  /* specs/discord/channel.json:113:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:114:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:115:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  bool fail_if_not_exists;

};
extern void discord_message_reference_cleanup_v(void *p);
extern void discord_message_reference_cleanup(struct discord_message_reference *p);
extern void discord_message_reference_init_v(void *p);
extern void discord_message_reference_init(struct discord_message_reference *p);
extern void discord_message_reference_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_reference_from_json(char *json, size_t len, struct discord_message_reference **pp);
extern size_t discord_message_reference_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_reference_to_json(char *json, size_t len, struct discord_message_reference *p);
extern void discord_message_reference_list_free_v(void **p);
extern void discord_message_reference_list_free(struct discord_message_reference **p);
extern void discord_message_reference_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_reference_list_from_json(char *str, size_t len, struct discord_message_reference ***p);
extern size_t discord_message_reference_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_reference_list_to_json(char *str, size_t len, struct discord_message_reference **p);

/* Message Application Structure */
/* defined at specs/discord/channel.json:122:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-application-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_application_init(struct discord_message_application *)`
 *   * Cleanup:

 *     * :code:`void discord_message_application_cleanup(struct discord_message_application *)`
 *     * :code:`void discord_message_application_list_free(struct discord_message_application **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_application_from_json(char *rbuf, size_t len, struct discord_message_application **)`
 *     * :code:`void discord_message_application_list_from_json(char *rbuf, size_t len, struct discord_message_application ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_application_to_json(char *wbuf, size_t len, struct discord_message_application *)`
 *     * :code:`void discord_message_application_list_to_json(char *wbuf, size_t len, struct discord_message_application **)`
 * @endverbatim
 */
struct discord_message_application {
  /* specs/discord/channel.json:124:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:125:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *cover_image;

  /* specs/discord/channel.json:126:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  char *description;

  /* specs/discord/channel.json:127:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *icon;

  /* specs/discord/channel.json:128:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  char *name;

};
extern void discord_message_application_cleanup_v(void *p);
extern void discord_message_application_cleanup(struct discord_message_application *p);
extern void discord_message_application_init_v(void *p);
extern void discord_message_application_init(struct discord_message_application *p);
extern void discord_message_application_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_application_from_json(char *json, size_t len, struct discord_message_application **pp);
extern size_t discord_message_application_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_application_to_json(char *json, size_t len, struct discord_message_application *p);
extern void discord_message_application_list_free_v(void **p);
extern void discord_message_application_list_free(struct discord_message_application **p);
extern void discord_message_application_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_application_list_from_json(char *str, size_t len, struct discord_message_application ***p);
extern size_t discord_message_application_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_application_list_to_json(char *str, size_t len, struct discord_message_application **p);


/* Message Activity Types */
/* defined at specs/discord/channel.json:131:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-activity-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_message_activity_types_print(enum discord_message_activity_types code)`
 *   * :code:`enum discord_message_activity_types discord_message_activity_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_message_activity_types {
  DISCORD_MESSAGE_ACTIVITY_JOIN = 1,
  DISCORD_MESSAGE_ACTIVITY_SPECTATE = 2,
  DISCORD_MESSAGE_ACTIVITY_LISTEN = 3,
  DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST = 5,
};
extern char* discord_message_activity_types_print(enum discord_message_activity_types);
extern enum discord_message_activity_types discord_message_activity_types_eval(char*);
extern void discord_message_activity_types_list_free_v(void **p);
extern void discord_message_activity_types_list_free(enum discord_message_activity_types **p);
extern void discord_message_activity_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_activity_types_list_from_json(char *str, size_t len, enum discord_message_activity_types ***p);
extern size_t discord_message_activity_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_activity_types_list_to_json(char *str, size_t len, enum discord_message_activity_types **p);

/* Message Activity Structure */
/* defined at specs/discord/channel.json:147:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_activity_init(struct discord_message_activity *)`
 *   * Cleanup:

 *     * :code:`void discord_message_activity_cleanup(struct discord_message_activity *)`
 *     * :code:`void discord_message_activity_list_free(struct discord_message_activity **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_activity_from_json(char *rbuf, size_t len, struct discord_message_activity **)`
 *     * :code:`void discord_message_activity_list_from_json(char *rbuf, size_t len, struct discord_message_activity ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_activity_to_json(char *wbuf, size_t len, struct discord_message_activity *)`
 *     * :code:`void discord_message_activity_list_to_json(char *wbuf, size_t len, struct discord_message_activity **)`
 * @endverbatim
 */
struct discord_message_activity {
  /* specs/discord/channel.json:149:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
  enum discord_message_activity_types type;

  /* specs/discord/channel.json:150:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
  char *party_id;

};
extern void discord_message_activity_cleanup_v(void *p);
extern void discord_message_activity_cleanup(struct discord_message_activity *p);
extern void discord_message_activity_init_v(void *p);
extern void discord_message_activity_init(struct discord_message_activity *p);
extern void discord_message_activity_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_activity_from_json(char *json, size_t len, struct discord_message_activity **pp);
extern size_t discord_message_activity_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_activity_to_json(char *json, size_t len, struct discord_message_activity *p);
extern void discord_message_activity_list_free_v(void **p);
extern void discord_message_activity_list_free(struct discord_message_activity **p);
extern void discord_message_activity_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_activity_list_from_json(char *str, size_t len, struct discord_message_activity ***p);
extern size_t discord_message_activity_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_activity_list_to_json(char *str, size_t len, struct discord_message_activity **p);


/* Message Types */
/* defined at specs/discord/channel.json:154:5 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-types
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_message_types_print(enum discord_message_types code)`
 *   * :code:`enum discord_message_types discord_message_types_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_message_types {
  DISCORD_MESSAGE_DEFAULT = 0,
  DISCORD_MESSAGE_RECIPIENT_ADD = 1,
  DISCORD_MESSAGE_RECIPIENT_REMOVE = 2,
  DISCORD_MESSAGE_CALL = 3,
  DISCORD_MESSAGE_CHANNEL_NAME_CHANGE = 4,
  DISCORD_MESSAGE_CHANNEL_ICON_CHANGE = 5,
  DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE = 6,
  DISCORD_MESSAGE_GUILD_MEMBER_JOIN = 7,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION = 8,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
  DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD = 12,
  DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED = 14,
  DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED = 15,
  DISCORD_MESSAGE_REPLY = 19,
  DISCORD_MESSAGE_APPLICATION_COMMAND = 20,
};
extern char* discord_message_types_print(enum discord_message_types);
extern enum discord_message_types discord_message_types_eval(char*);
extern void discord_message_types_list_free_v(void **p);
extern void discord_message_types_list_free(enum discord_message_types **p);
extern void discord_message_types_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_types_list_from_json(char *str, size_t len, enum discord_message_types ***p);
extern size_t discord_message_types_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_types_list_to_json(char *str, size_t len, enum discord_message_types **p);

/* Message Structure */
/* defined at specs/discord/channel.json:182:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_message_init(struct discord_message *)`
 *   * Cleanup:

 *     * :code:`void discord_message_cleanup(struct discord_message *)`
 *     * :code:`void discord_message_list_free(struct discord_message **)`
 *   * JSON Decoder:

 *     * :code:`void discord_message_from_json(char *rbuf, size_t len, struct discord_message **)`
 *     * :code:`void discord_message_list_from_json(char *rbuf, size_t len, struct discord_message ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_message_to_json(char *wbuf, size_t len, struct discord_message *)`
 *     * :code:`void discord_message_list_to_json(char *wbuf, size_t len, struct discord_message **)`
 * @endverbatim
 */
struct discord_message {
  /* specs/discord/channel.json:184:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:185:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:186:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:187:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
  struct discord_user *author;

  /* specs/discord/channel.json:188:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
  struct discord_guild_member *member; /**< partial guild member object */

  /* specs/discord/channel.json:189:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
  char *content;

  /* specs/discord/channel.json:190:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.json:191:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
  u64_unix_ms_t edited_timestamp;

  /* specs/discord/channel.json:192:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
  bool tts;

  /* specs/discord/channel.json:193:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
  bool mention_everyone;

  /* specs/discord/channel.json:194:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
  struct discord_user **mentions; /**< array of user objects, with an additional partial member field */

  /* specs/discord/channel.json:195:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
  ja_u64 **mention_roles; /**< array of role object ids */

  /* specs/discord/channel.json:196:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
  struct discord_channel_mention **mention_channels;

  /* specs/discord/channel.json:197:77
     '{"type":{"base":"struct discord_attachment", "dec":"ntl"}, "name":"attachments"}' */
  struct discord_attachment **attachments;

  /* specs/discord/channel.json:198:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
  struct discord_embed **embeds;

  /* specs/discord/channel.json:199:74
     '{"type":{"base":"struct discord_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
  struct discord_reaction **reactions;

  /* specs/discord/channel.json:200:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
  char *nonce; /**< integer or string */

  /* specs/discord/channel.json:201:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
  bool pinned;

  /* specs/discord/channel.json:202:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
  u64_snowflake_t webhook_id;

  /* specs/discord/channel.json:203:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
  enum discord_message_types type;

  /* specs/discord/channel.json:204:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
  struct discord_message_activity *activity;

  /* specs/discord/channel.json:205:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
  struct discord_message_application **application;

  /* specs/discord/channel.json:206:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
  struct discord_message_reference *message_reference;

  /* specs/discord/channel.json:207:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
  enum discord_message_flags flags;

  /* specs/discord/channel.json:208:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
  struct discord_message *referenced_message; /**< this will cause recursive allocation if allocating as the parent */

  /* specs/discord/channel.json:209:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
  struct discord_message_interaction *interaction; /**< the message associated with the message_reference */

  /* specs/discord/channel.json:210:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
  struct discord_channel *thread; /**< the channel that was started from this message, includes thread member obejct */

  /* specs/discord/channel.json:211:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
  struct discord_component **components; /**< sent if the message contains components like buttons, actions rows, or other interactive components */

  /* specs/discord/channel.json:212:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
  struct discord_message_sticker **sticker_items; /**< sent if the message contains stickets */

  /* specs/discord/channel.json:213:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
  struct discord_message_sticker **stickers; /**< [DEPRECATED] array of sticker objects */

};
extern void discord_message_cleanup_v(void *p);
extern void discord_message_cleanup(struct discord_message *p);
extern void discord_message_init_v(void *p);
extern void discord_message_init(struct discord_message *p);
extern void discord_message_from_json_v(char *json, size_t len, void *pp);
extern void discord_message_from_json(char *json, size_t len, struct discord_message **pp);
extern size_t discord_message_to_json_v(char *json, size_t len, void *p);
extern size_t discord_message_to_json(char *json, size_t len, struct discord_message *p);
extern void discord_message_list_free_v(void **p);
extern void discord_message_list_free(struct discord_message **p);
extern void discord_message_list_from_json_v(char *str, size_t len, void *p);
extern void discord_message_list_from_json(char *str, size_t len, struct discord_message ***p);
extern size_t discord_message_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_message_list_to_json(char *str, size_t len, struct discord_message **p);

/* Followed Channel Structure */
/* defined at specs/discord/channel.json:219:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_followed_channel_init(struct discord_followed_channel *)`
 *   * Cleanup:

 *     * :code:`void discord_followed_channel_cleanup(struct discord_followed_channel *)`
 *     * :code:`void discord_followed_channel_list_free(struct discord_followed_channel **)`
 *   * JSON Decoder:

 *     * :code:`void discord_followed_channel_from_json(char *rbuf, size_t len, struct discord_followed_channel **)`
 *     * :code:`void discord_followed_channel_list_from_json(char *rbuf, size_t len, struct discord_followed_channel ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_followed_channel_to_json(char *wbuf, size_t len, struct discord_followed_channel *)`
 *     * :code:`void discord_followed_channel_list_to_json(char *wbuf, size_t len, struct discord_followed_channel **)`
 * @endverbatim
 */
struct discord_followed_channel {
  /* specs/discord/channel.json:222:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:223:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t webhook_id;

};
extern void discord_followed_channel_cleanup_v(void *p);
extern void discord_followed_channel_cleanup(struct discord_followed_channel *p);
extern void discord_followed_channel_init_v(void *p);
extern void discord_followed_channel_init(struct discord_followed_channel *p);
extern void discord_followed_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_followed_channel_from_json(char *json, size_t len, struct discord_followed_channel **pp);
extern size_t discord_followed_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_followed_channel_to_json(char *json, size_t len, struct discord_followed_channel *p);
extern void discord_followed_channel_list_free_v(void **p);
extern void discord_followed_channel_list_free(struct discord_followed_channel **p);
extern void discord_followed_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_followed_channel_list_from_json(char *str, size_t len, struct discord_followed_channel ***p);
extern size_t discord_followed_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_followed_channel_list_to_json(char *str, size_t len, struct discord_followed_channel **p);

/* Reaction Structure */
/* defined at specs/discord/channel.json:229:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_reaction_init(struct discord_reaction *)`
 *   * Cleanup:

 *     * :code:`void discord_reaction_cleanup(struct discord_reaction *)`
 *     * :code:`void discord_reaction_list_free(struct discord_reaction **)`
 *   * JSON Decoder:

 *     * :code:`void discord_reaction_from_json(char *rbuf, size_t len, struct discord_reaction **)`
 *     * :code:`void discord_reaction_list_from_json(char *rbuf, size_t len, struct discord_reaction ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_reaction_to_json(char *wbuf, size_t len, struct discord_reaction *)`
 *     * :code:`void discord_reaction_list_to_json(char *wbuf, size_t len, struct discord_reaction **)`
 * @endverbatim
 */
struct discord_reaction {
  /* specs/discord/channel.json:232:20
     '{ "name": "count", "type":{ "base":"int" }}' */
  int count;

  /* specs/discord/channel.json:233:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
  bool me;

  /* specs/discord/channel.json:234:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
  struct discord_emoji *emoji; /**< partial emoji object */

};
extern void discord_reaction_cleanup_v(void *p);
extern void discord_reaction_cleanup(struct discord_reaction *p);
extern void discord_reaction_init_v(void *p);
extern void discord_reaction_init(struct discord_reaction *p);
extern void discord_reaction_from_json_v(char *json, size_t len, void *pp);
extern void discord_reaction_from_json(char *json, size_t len, struct discord_reaction **pp);
extern size_t discord_reaction_to_json_v(char *json, size_t len, void *p);
extern size_t discord_reaction_to_json(char *json, size_t len, struct discord_reaction *p);
extern void discord_reaction_list_free_v(void **p);
extern void discord_reaction_list_free(struct discord_reaction **p);
extern void discord_reaction_list_from_json_v(char *str, size_t len, void *p);
extern void discord_reaction_list_from_json(char *str, size_t len, struct discord_reaction ***p);
extern size_t discord_reaction_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_reaction_list_to_json(char *str, size_t len, struct discord_reaction **p);

/* Overwrite Structure */
/* defined at specs/discord/channel.json:239:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_overwrite_init(struct discord_overwrite *)`
 *   * Cleanup:

 *     * :code:`void discord_overwrite_cleanup(struct discord_overwrite *)`
 *     * :code:`void discord_overwrite_list_free(struct discord_overwrite **)`
 *   * JSON Decoder:

 *     * :code:`void discord_overwrite_from_json(char *rbuf, size_t len, struct discord_overwrite **)`
 *     * :code:`void discord_overwrite_list_from_json(char *rbuf, size_t len, struct discord_overwrite ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_overwrite_to_json(char *wbuf, size_t len, struct discord_overwrite *)`
 *     * :code:`void discord_overwrite_list_to_json(char *wbuf, size_t len, struct discord_overwrite **)`
 * @endverbatim
 */
struct discord_overwrite {
  /* specs/discord/channel.json:242:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:243:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/channel.json:244:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags"}, 
          "comment":"permission bit set"}' */
  enum discord_bitwise_permission_flags allow; /**< permission bit set */

  /* specs/discord/channel.json:246:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_bitwise_permission_flags"}, 
          "comment":"permission bit set"}' */
  enum discord_bitwise_permission_flags deny; /**< permission bit set */

};
extern void discord_overwrite_cleanup_v(void *p);
extern void discord_overwrite_cleanup(struct discord_overwrite *p);
extern void discord_overwrite_init_v(void *p);
extern void discord_overwrite_init(struct discord_overwrite *p);
extern void discord_overwrite_from_json_v(char *json, size_t len, void *pp);
extern void discord_overwrite_from_json(char *json, size_t len, struct discord_overwrite **pp);
extern size_t discord_overwrite_to_json_v(char *json, size_t len, void *p);
extern size_t discord_overwrite_to_json(char *json, size_t len, struct discord_overwrite *p);
extern void discord_overwrite_list_free_v(void **p);
extern void discord_overwrite_list_free(struct discord_overwrite **p);
extern void discord_overwrite_list_from_json_v(char *str, size_t len, void *p);
extern void discord_overwrite_list_from_json(char *str, size_t len, struct discord_overwrite ***p);
extern size_t discord_overwrite_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_overwrite_list_to_json(char *str, size_t len, struct discord_overwrite **p);

/* Thread Metadata Object */
/* defined at specs/discord/channel.json:254:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#thread-metadata-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_thread_metadata_init(struct discord_thread_metadata *)`
 *   * Cleanup:

 *     * :code:`void discord_thread_metadata_cleanup(struct discord_thread_metadata *)`
 *     * :code:`void discord_thread_metadata_list_free(struct discord_thread_metadata **)`
 *   * JSON Decoder:

 *     * :code:`void discord_thread_metadata_from_json(char *rbuf, size_t len, struct discord_thread_metadata **)`
 *     * :code:`void discord_thread_metadata_list_from_json(char *rbuf, size_t len, struct discord_thread_metadata ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_thread_metadata_to_json(char *wbuf, size_t len, struct discord_thread_metadata *)`
 *     * :code:`void discord_thread_metadata_list_to_json(char *wbuf, size_t len, struct discord_thread_metadata **)`
 * @endverbatim
 */
struct discord_thread_metadata {
  /* specs/discord/channel.json:257:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
  bool archived;

  /* specs/discord/channel.json:258:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t archiver_id;

  /* specs/discord/channel.json:259:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
  int auto_archive_duration;

  /* specs/discord/channel.json:260:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t archive_timestamp;

  /* specs/discord/channel.json:261:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
  bool locked;

};
extern void discord_thread_metadata_cleanup_v(void *p);
extern void discord_thread_metadata_cleanup(struct discord_thread_metadata *p);
extern void discord_thread_metadata_init_v(void *p);
extern void discord_thread_metadata_init(struct discord_thread_metadata *p);
extern void discord_thread_metadata_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_metadata_from_json(char *json, size_t len, struct discord_thread_metadata **pp);
extern size_t discord_thread_metadata_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_metadata_to_json(char *json, size_t len, struct discord_thread_metadata *p);
extern void discord_thread_metadata_list_free_v(void **p);
extern void discord_thread_metadata_list_free(struct discord_thread_metadata **p);
extern void discord_thread_metadata_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_metadata_list_from_json(char *str, size_t len, struct discord_thread_metadata ***p);
extern size_t discord_thread_metadata_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_metadata_list_to_json(char *str, size_t len, struct discord_thread_metadata **p);

/* Thread Member Object */
/* defined at specs/discord/channel.json:268:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#thread-member-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_thread_member_init(struct discord_thread_member *)`
 *   * Cleanup:

 *     * :code:`void discord_thread_member_cleanup(struct discord_thread_member *)`
 *     * :code:`void discord_thread_member_list_free(struct discord_thread_member **)`
 *   * JSON Decoder:

 *     * :code:`void discord_thread_member_from_json(char *rbuf, size_t len, struct discord_thread_member **)`
 *     * :code:`void discord_thread_member_list_from_json(char *rbuf, size_t len, struct discord_thread_member ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_thread_member_to_json(char *wbuf, size_t len, struct discord_thread_member *)`
 *     * :code:`void discord_thread_member_list_to_json(char *wbuf, size_t len, struct discord_thread_member **)`
 * @endverbatim
 */
struct discord_thread_member {
  /* specs/discord/channel.json:271:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:272:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t user_id;

  /* specs/discord/channel.json:273:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t join_timestamp;

  /* specs/discord/channel.json:274:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
  int flags;

};
extern void discord_thread_member_cleanup_v(void *p);
extern void discord_thread_member_cleanup(struct discord_thread_member *p);
extern void discord_thread_member_init_v(void *p);
extern void discord_thread_member_init(struct discord_thread_member *p);
extern void discord_thread_member_from_json_v(char *json, size_t len, void *pp);
extern void discord_thread_member_from_json(char *json, size_t len, struct discord_thread_member **pp);
extern size_t discord_thread_member_to_json_v(char *json, size_t len, void *p);
extern size_t discord_thread_member_to_json(char *json, size_t len, struct discord_thread_member *p);
extern void discord_thread_member_list_free_v(void **p);
extern void discord_thread_member_list_free(struct discord_thread_member **p);
extern void discord_thread_member_list_from_json_v(char *str, size_t len, void *p);
extern void discord_thread_member_list_from_json(char *str, size_t len, struct discord_thread_member ***p);
extern size_t discord_thread_member_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_thread_member_list_to_json(char *str, size_t len, struct discord_thread_member **p);

/* Attachment Structure */
/* defined at specs/discord/channel.json:280:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#attachment-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_attachment_init(struct discord_attachment *)`
 *   * Cleanup:

 *     * :code:`void discord_attachment_cleanup(struct discord_attachment *)`
 *     * :code:`void discord_attachment_list_free(struct discord_attachment **)`
 *   * JSON Decoder:

 *     * :code:`void discord_attachment_from_json(char *rbuf, size_t len, struct discord_attachment **)`
 *     * :code:`void discord_attachment_list_from_json(char *rbuf, size_t len, struct discord_attachment ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_attachment_to_json(char *wbuf, size_t len, struct discord_attachment *)`
 *     * :code:`void discord_attachment_list_to_json(char *wbuf, size_t len, struct discord_attachment **)`
 * @endverbatim
 */
struct discord_attachment {
  /* specs/discord/channel.json:283:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "loc":"multipart", "comment":"the file contents", "inject_if_not":null }' */
  char *content; /**< the file contents */

  /* specs/discord/channel.json:285:20
     '{ "name": "id", "type":{ "base":"int" }, "comment":"attachment id"}' */
  int id; /**< attachment id */

  /* specs/discord/channel.json:286:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of file attached"}' */
  char *filename; /**< name of file attached */

  /* specs/discord/channel.json:287:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"description for the file"}' */
  char *description; /**< description for the file */

  /* specs/discord/channel.json:288:20
     '{ "name": "content_type", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"the attachment's media type"}' */
  char *content_type; /**< the attachment's media type */

  /* specs/discord/channel.json:289:20
     '{ "name": "size", "type":{ "base":"int" }, "inject_if_not":0, "comment":"size of file in bytes"}' */
  int size; /**< size of file in bytes */

  /* specs/discord/channel.json:290:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"source url of file"}' */
  char *url; /**< source url of file */

  /* specs/discord/channel.json:291:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"a proxied url of file"}' */
  char *proxy_url; /**< a proxied url of file */

  /* specs/discord/channel.json:292:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0, "comment":"height of file (if image)" }' */
  int height; /**< height of file (if image) */

  /* specs/discord/channel.json:293:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0, "comment":"width of file (if image)"}' */
  int width; /**< width of file (if image) */

  /* specs/discord/channel.json:294:20
     '{ "name": "ephemeral", "type":{ "base":"bool" }, "inject_if_not":false, "comment":"whether this attachment is ephemeral"}' */
  bool ephemeral; /**< whether this attachment is ephemeral */

};
extern void discord_attachment_cleanup_v(void *p);
extern void discord_attachment_cleanup(struct discord_attachment *p);
extern void discord_attachment_init_v(void *p);
extern void discord_attachment_init(struct discord_attachment *p);
extern void discord_attachment_from_json_v(char *json, size_t len, void *pp);
extern void discord_attachment_from_json(char *json, size_t len, struct discord_attachment **pp);
extern size_t discord_attachment_to_json_v(char *json, size_t len, void *p);
extern size_t discord_attachment_to_json(char *json, size_t len, struct discord_attachment *p);
extern void discord_attachment_list_free_v(void **p);
extern void discord_attachment_list_free(struct discord_attachment **p);
extern void discord_attachment_list_from_json_v(char *str, size_t len, void *p);
extern void discord_attachment_list_from_json(char *str, size_t len, struct discord_attachment ***p);
extern size_t discord_attachment_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_attachment_list_to_json(char *str, size_t len, struct discord_attachment **p);

/* Channel Mention Structure */
/* defined at specs/discord/channel.json:301:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_channel_mention_init(struct discord_channel_mention *)`
 *   * Cleanup:

 *     * :code:`void discord_channel_mention_cleanup(struct discord_channel_mention *)`
 *     * :code:`void discord_channel_mention_list_free(struct discord_channel_mention **)`
 *   * JSON Decoder:

 *     * :code:`void discord_channel_mention_from_json(char *rbuf, size_t len, struct discord_channel_mention **)`
 *     * :code:`void discord_channel_mention_list_from_json(char *rbuf, size_t len, struct discord_channel_mention ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_channel_mention_to_json(char *wbuf, size_t len, struct discord_channel_mention *)`
 *     * :code:`void discord_channel_mention_list_to_json(char *wbuf, size_t len, struct discord_channel_mention **)`
 * @endverbatim
 */
struct discord_channel_mention {
  /* specs/discord/channel.json:304:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:305:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:306:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
  enum discord_channel_types type;

  /* specs/discord/channel.json:307:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

};
extern void discord_channel_mention_cleanup_v(void *p);
extern void discord_channel_mention_cleanup(struct discord_channel_mention *p);
extern void discord_channel_mention_init_v(void *p);
extern void discord_channel_mention_init(struct discord_channel_mention *p);
extern void discord_channel_mention_from_json_v(char *json, size_t len, void *pp);
extern void discord_channel_mention_from_json(char *json, size_t len, struct discord_channel_mention **pp);
extern size_t discord_channel_mention_to_json_v(char *json, size_t len, void *p);
extern size_t discord_channel_mention_to_json(char *json, size_t len, struct discord_channel_mention *p);
extern void discord_channel_mention_list_free_v(void **p);
extern void discord_channel_mention_list_free(struct discord_channel_mention **p);
extern void discord_channel_mention_list_from_json_v(char *str, size_t len, void *p);
extern void discord_channel_mention_list_from_json(char *str, size_t len, struct discord_channel_mention ***p);
extern size_t discord_channel_mention_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_channel_mention_list_to_json(char *str, size_t len, struct discord_channel_mention **p);

/* Allowed Mentions Structure */
/* defined at specs/discord/channel.json:313:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_allowed_mentions_init(struct discord_allowed_mentions *)`
 *   * Cleanup:

 *     * :code:`void discord_allowed_mentions_cleanup(struct discord_allowed_mentions *)`
 *     * :code:`void discord_allowed_mentions_list_free(struct discord_allowed_mentions **)`
 *   * JSON Decoder:

 *     * :code:`void discord_allowed_mentions_from_json(char *rbuf, size_t len, struct discord_allowed_mentions **)`
 *     * :code:`void discord_allowed_mentions_list_from_json(char *rbuf, size_t len, struct discord_allowed_mentions ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_allowed_mentions_to_json(char *wbuf, size_t len, struct discord_allowed_mentions *)`
 *     * :code:`void discord_allowed_mentions_list_to_json(char *wbuf, size_t len, struct discord_allowed_mentions **)`
 * @endverbatim
 */
struct discord_allowed_mentions {
  /* specs/discord/channel.json:316:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
  ja_str **parse;

  /* specs/discord/channel.json:317:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  ja_u64 **roles; /**< list of snowflakes */

  /* specs/discord/channel.json:318:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  ja_u64 **users; /**< list of snowflakes */

  /* specs/discord/channel.json:319:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
  bool replied_user;

};
extern void discord_allowed_mentions_cleanup_v(void *p);
extern void discord_allowed_mentions_cleanup(struct discord_allowed_mentions *p);
extern void discord_allowed_mentions_init_v(void *p);
extern void discord_allowed_mentions_init(struct discord_allowed_mentions *p);
extern void discord_allowed_mentions_from_json_v(char *json, size_t len, void *pp);
extern void discord_allowed_mentions_from_json(char *json, size_t len, struct discord_allowed_mentions **pp);
extern size_t discord_allowed_mentions_to_json_v(char *json, size_t len, void *p);
extern size_t discord_allowed_mentions_to_json(char *json, size_t len, struct discord_allowed_mentions *p);
extern void discord_allowed_mentions_list_free_v(void **p);
extern void discord_allowed_mentions_list_free(struct discord_allowed_mentions **p);
extern void discord_allowed_mentions_list_from_json_v(char *str, size_t len, void *p);
extern void discord_allowed_mentions_list_from_json(char *str, size_t len, struct discord_allowed_mentions ***p);
extern size_t discord_allowed_mentions_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_allowed_mentions_list_to_json(char *str, size_t len, struct discord_allowed_mentions **p);

/* Embed Structure */
/* defined at specs/discord/channel.json:325:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_init(struct discord_embed *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_cleanup(struct discord_embed *)`
 *     * :code:`void discord_embed_list_free(struct discord_embed **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_from_json(char *rbuf, size_t len, struct discord_embed **)`
 *     * :code:`void discord_embed_list_from_json(char *rbuf, size_t len, struct discord_embed ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_to_json(char *wbuf, size_t len, struct discord_embed *)`
 *     * :code:`void discord_embed_list_to_json(char *wbuf, size_t len, struct discord_embed **)`
 * @endverbatim
 */
struct discord_embed {
  /* specs/discord/channel.json:328:20
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  char *title;

  /* specs/discord/channel.json:329:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":""}' */
  char type[32];

  /* specs/discord/channel.json:330:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *description;

  /* specs/discord/channel.json:331:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:332:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.json:333:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
  int color;

  /* specs/discord/channel.json:334:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
  struct discord_embed_footer *footer;

  /* specs/discord/channel.json:335:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_image *image;

  /* specs/discord/channel.json:336:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_thumbnail *thumbnail;

  /* specs/discord/channel.json:337:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_video *video;

  /* specs/discord/channel.json:338:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_provider *provider;

  /* specs/discord/channel.json:339:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_author *author;

  /* specs/discord/channel.json:340:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
  struct discord_embed_field **fields;

};
extern void discord_embed_cleanup_v(void *p);
extern void discord_embed_cleanup(struct discord_embed *p);
extern void discord_embed_init_v(void *p);
extern void discord_embed_init(struct discord_embed *p);
extern void discord_embed_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_from_json(char *json, size_t len, struct discord_embed **pp);
extern size_t discord_embed_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_to_json(char *json, size_t len, struct discord_embed *p);
extern void discord_embed_list_free_v(void **p);
extern void discord_embed_list_free(struct discord_embed **p);
extern void discord_embed_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_list_from_json(char *str, size_t len, struct discord_embed ***p);
extern size_t discord_embed_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_list_to_json(char *str, size_t len, struct discord_embed **p);

/* Embed Thumbnail Structure */
/* defined at specs/discord/channel.json:347:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_thumbnail_init(struct discord_embed_thumbnail *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *)`
 *     * :code:`void discord_embed_thumbnail_list_free(struct discord_embed_thumbnail **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_thumbnail_from_json(char *rbuf, size_t len, struct discord_embed_thumbnail **)`
 *     * :code:`void discord_embed_thumbnail_list_from_json(char *rbuf, size_t len, struct discord_embed_thumbnail ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_thumbnail_to_json(char *wbuf, size_t len, struct discord_embed_thumbnail *)`
 *     * :code:`void discord_embed_thumbnail_list_to_json(char *wbuf, size_t len, struct discord_embed_thumbnail **)`
 * @endverbatim
 */
struct discord_embed_thumbnail {
  /* specs/discord/channel.json:349:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:350:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:351:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:352:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

};
extern void discord_embed_thumbnail_cleanup_v(void *p);
extern void discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_init_v(void *p);
extern void discord_embed_thumbnail_init(struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_thumbnail_from_json(char *json, size_t len, struct discord_embed_thumbnail **pp);
extern size_t discord_embed_thumbnail_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_thumbnail_to_json(char *json, size_t len, struct discord_embed_thumbnail *p);
extern void discord_embed_thumbnail_list_free_v(void **p);
extern void discord_embed_thumbnail_list_free(struct discord_embed_thumbnail **p);
extern void discord_embed_thumbnail_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_thumbnail_list_from_json(char *str, size_t len, struct discord_embed_thumbnail ***p);
extern size_t discord_embed_thumbnail_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_thumbnail_list_to_json(char *str, size_t len, struct discord_embed_thumbnail **p);

/* Embed Video Structure */
/* defined at specs/discord/channel.json:359:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_video_init(struct discord_embed_video *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_video_cleanup(struct discord_embed_video *)`
 *     * :code:`void discord_embed_video_list_free(struct discord_embed_video **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_video_from_json(char *rbuf, size_t len, struct discord_embed_video **)`
 *     * :code:`void discord_embed_video_list_from_json(char *rbuf, size_t len, struct discord_embed_video ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_video_to_json(char *wbuf, size_t len, struct discord_embed_video *)`
 *     * :code:`void discord_embed_video_list_to_json(char *wbuf, size_t len, struct discord_embed_video **)`
 * @endverbatim
 */
struct discord_embed_video {
  /* specs/discord/channel.json:361:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:362:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:363:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:364:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

};
extern void discord_embed_video_cleanup_v(void *p);
extern void discord_embed_video_cleanup(struct discord_embed_video *p);
extern void discord_embed_video_init_v(void *p);
extern void discord_embed_video_init(struct discord_embed_video *p);
extern void discord_embed_video_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_video_from_json(char *json, size_t len, struct discord_embed_video **pp);
extern size_t discord_embed_video_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_video_to_json(char *json, size_t len, struct discord_embed_video *p);
extern void discord_embed_video_list_free_v(void **p);
extern void discord_embed_video_list_free(struct discord_embed_video **p);
extern void discord_embed_video_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_video_list_from_json(char *str, size_t len, struct discord_embed_video ***p);
extern size_t discord_embed_video_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_video_list_to_json(char *str, size_t len, struct discord_embed_video **p);

/* Embed Image Structure */
/* defined at specs/discord/channel.json:371:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_image_init(struct discord_embed_image *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_image_cleanup(struct discord_embed_image *)`
 *     * :code:`void discord_embed_image_list_free(struct discord_embed_image **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_image_from_json(char *rbuf, size_t len, struct discord_embed_image **)`
 *     * :code:`void discord_embed_image_list_from_json(char *rbuf, size_t len, struct discord_embed_image ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_image_to_json(char *wbuf, size_t len, struct discord_embed_image *)`
 *     * :code:`void discord_embed_image_list_to_json(char *wbuf, size_t len, struct discord_embed_image **)`
 * @endverbatim
 */
struct discord_embed_image {
  /* specs/discord/channel.json:373:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:374:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:375:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:376:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

};
extern void discord_embed_image_cleanup_v(void *p);
extern void discord_embed_image_cleanup(struct discord_embed_image *p);
extern void discord_embed_image_init_v(void *p);
extern void discord_embed_image_init(struct discord_embed_image *p);
extern void discord_embed_image_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_image_from_json(char *json, size_t len, struct discord_embed_image **pp);
extern size_t discord_embed_image_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_image_to_json(char *json, size_t len, struct discord_embed_image *p);
extern void discord_embed_image_list_free_v(void **p);
extern void discord_embed_image_list_free(struct discord_embed_image **p);
extern void discord_embed_image_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_image_list_from_json(char *str, size_t len, struct discord_embed_image ***p);
extern size_t discord_embed_image_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_image_list_to_json(char *str, size_t len, struct discord_embed_image **p);

/* Embed Provider Structure */
/* defined at specs/discord/channel.json:383:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_provider_init(struct discord_embed_provider *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_provider_cleanup(struct discord_embed_provider *)`
 *     * :code:`void discord_embed_provider_list_free(struct discord_embed_provider **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_provider_from_json(char *rbuf, size_t len, struct discord_embed_provider **)`
 *     * :code:`void discord_embed_provider_list_from_json(char *rbuf, size_t len, struct discord_embed_provider ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_provider_to_json(char *wbuf, size_t len, struct discord_embed_provider *)`
 *     * :code:`void discord_embed_provider_list_to_json(char *wbuf, size_t len, struct discord_embed_provider **)`
 * @endverbatim
 */
struct discord_embed_provider {
  /* specs/discord/channel.json:385:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:386:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *url;

};
extern void discord_embed_provider_cleanup_v(void *p);
extern void discord_embed_provider_cleanup(struct discord_embed_provider *p);
extern void discord_embed_provider_init_v(void *p);
extern void discord_embed_provider_init(struct discord_embed_provider *p);
extern void discord_embed_provider_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_provider_from_json(char *json, size_t len, struct discord_embed_provider **pp);
extern size_t discord_embed_provider_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_provider_to_json(char *json, size_t len, struct discord_embed_provider *p);
extern void discord_embed_provider_list_free_v(void **p);
extern void discord_embed_provider_list_free(struct discord_embed_provider **p);
extern void discord_embed_provider_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_provider_list_from_json(char *str, size_t len, struct discord_embed_provider ***p);
extern size_t discord_embed_provider_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_provider_list_to_json(char *str, size_t len, struct discord_embed_provider **p);

/* Embed Author Structure */
/* defined at specs/discord/channel.json:393:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_author_init(struct discord_embed_author *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_author_cleanup(struct discord_embed_author *)`
 *     * :code:`void discord_embed_author_list_free(struct discord_embed_author **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_author_from_json(char *rbuf, size_t len, struct discord_embed_author **)`
 *     * :code:`void discord_embed_author_list_from_json(char *rbuf, size_t len, struct discord_embed_author ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_author_to_json(char *wbuf, size_t len, struct discord_embed_author *)`
 *     * :code:`void discord_embed_author_list_to_json(char *wbuf, size_t len, struct discord_embed_author **)`
 * @endverbatim
 */
struct discord_embed_author {
  /* specs/discord/channel.json:395:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:396:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:397:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *icon_url;

  /* specs/discord/channel.json:398:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_icon_url;

};
extern void discord_embed_author_cleanup_v(void *p);
extern void discord_embed_author_cleanup(struct discord_embed_author *p);
extern void discord_embed_author_init_v(void *p);
extern void discord_embed_author_init(struct discord_embed_author *p);
extern void discord_embed_author_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_author_from_json(char *json, size_t len, struct discord_embed_author **pp);
extern size_t discord_embed_author_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_author_to_json(char *json, size_t len, struct discord_embed_author *p);
extern void discord_embed_author_list_free_v(void **p);
extern void discord_embed_author_list_free(struct discord_embed_author **p);
extern void discord_embed_author_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_author_list_from_json(char *str, size_t len, struct discord_embed_author ***p);
extern size_t discord_embed_author_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_author_list_to_json(char *str, size_t len, struct discord_embed_author **p);

/* Embed Footer Structure */
/* defined at specs/discord/channel.json:405:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_footer_init(struct discord_embed_footer *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_footer_cleanup(struct discord_embed_footer *)`
 *     * :code:`void discord_embed_footer_list_free(struct discord_embed_footer **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_footer_from_json(char *rbuf, size_t len, struct discord_embed_footer **)`
 *     * :code:`void discord_embed_footer_list_from_json(char *rbuf, size_t len, struct discord_embed_footer ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_footer_to_json(char *wbuf, size_t len, struct discord_embed_footer *)`
 *     * :code:`void discord_embed_footer_list_to_json(char *wbuf, size_t len, struct discord_embed_footer **)`
 * @endverbatim
 */
struct discord_embed_footer {
  /* specs/discord/channel.json:407:20
     '{ "name": "text", "type": {"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *text;

  /* specs/discord/channel.json:408:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  char *icon_url;

  /* specs/discord/channel.json:409:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *proxy_icon_url;

};
extern void discord_embed_footer_cleanup_v(void *p);
extern void discord_embed_footer_cleanup(struct discord_embed_footer *p);
extern void discord_embed_footer_init_v(void *p);
extern void discord_embed_footer_init(struct discord_embed_footer *p);
extern void discord_embed_footer_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_footer_from_json(char *json, size_t len, struct discord_embed_footer **pp);
extern size_t discord_embed_footer_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_footer_to_json(char *json, size_t len, struct discord_embed_footer *p);
extern void discord_embed_footer_list_free_v(void **p);
extern void discord_embed_footer_list_free(struct discord_embed_footer **p);
extern void discord_embed_footer_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_footer_list_from_json(char *str, size_t len, struct discord_embed_footer ***p);
extern size_t discord_embed_footer_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_footer_list_to_json(char *str, size_t len, struct discord_embed_footer **p);

/* Embed Field Structure */
/* defined at specs/discord/channel.json:416:22 */
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_embed_field_init(struct discord_embed_field *)`
 *   * Cleanup:

 *     * :code:`void discord_embed_field_cleanup(struct discord_embed_field *)`
 *     * :code:`void discord_embed_field_list_free(struct discord_embed_field **)`
 *   * JSON Decoder:

 *     * :code:`void discord_embed_field_from_json(char *rbuf, size_t len, struct discord_embed_field **)`
 *     * :code:`void discord_embed_field_list_from_json(char *rbuf, size_t len, struct discord_embed_field ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_embed_field_to_json(char *wbuf, size_t len, struct discord_embed_field *)`
 *     * :code:`void discord_embed_field_list_to_json(char *wbuf, size_t len, struct discord_embed_field **)`
 * @endverbatim
 */
struct discord_embed_field {
  /* specs/discord/channel.json:418:20
     '{ "name": "name", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:419:20
     '{ "name": "value", "type": { "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *value;

  /* specs/discord/channel.json:420:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
  bool Inline;

};
extern void discord_embed_field_cleanup_v(void *p);
extern void discord_embed_field_cleanup(struct discord_embed_field *p);
extern void discord_embed_field_init_v(void *p);
extern void discord_embed_field_init(struct discord_embed_field *p);
extern void discord_embed_field_from_json_v(char *json, size_t len, void *pp);
extern void discord_embed_field_from_json(char *json, size_t len, struct discord_embed_field **pp);
extern size_t discord_embed_field_to_json_v(char *json, size_t len, void *p);
extern size_t discord_embed_field_to_json(char *json, size_t len, struct discord_embed_field *p);
extern void discord_embed_field_list_free_v(void **p);
extern void discord_embed_field_list_free(struct discord_embed_field **p);
extern void discord_embed_field_list_from_json_v(char *str, size_t len, void *p);
extern void discord_embed_field_list_from_json(char *str, size_t len, struct discord_embed_field ***p);
extern size_t discord_embed_field_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_embed_field_list_to_json(char *str, size_t len, struct discord_embed_field **p);
