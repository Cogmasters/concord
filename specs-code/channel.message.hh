/* This file is generated from specs/channel.message.json, Please don't edit it. */
/*

*/


namespace sticker {
namespace format_type {
enum code {
  PNG = 1,
  APNG = 2,
  LOTTIE = 3,
};
} // namespace format_type
} // namespace sticker

namespace sticker {
/* https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure */
/* This is defined at specs/channel.message.json:20:22 */
struct dati {
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
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
  */
  discord::channel::message::sticker::format_type::code type;

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
} // namespace sticker


namespace flags {
enum code {
  CROSSPOSTED = 1, // 1<<0
  IS_CROSSPOST = 2, // 1<<1
  SUPRESS_EMBEDS = 4, // 1<<2
  SOURCE_MESSAGE_DELETED = 8, // 1<<3
  URGENT = 16, // 1<<4
};
} // namespace flags

namespace reference {
/* Title: Message Reference Structure */
/* https://discord.com/developers/docs/resources/channel#message-object-message-reference-structure */
/* This is defined at specs/channel.message.json:50:22 */
struct dati {
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
} // namespace reference

namespace application {
/* Title: Message Application Structure */
/* https://discord.com/developers/docs/resources/channel#message-object-message-application-structure */
/* This is defined at specs/channel.message.json:66:22 */
struct dati {
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
} // namespace application


namespace activity {
namespace types {
enum code {
  JOIN = 1,
  SPECTATE = 2,
  LISTEN = 3,
  JOIN_REQUEST = 5,
};
} // namespace types
} // namespace activity

namespace activity {
/* Title: Message Activity Structure */
/* https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure */
/* This is defined at specs/channel.message.json:92:22 */
struct dati {
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */
  discord::channel::message::activity::types::code type;

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
} // namespace activity


namespace types {
enum code {
  DEFAULT = 0,
  RECIPIENT_ADD = 1,
  RECIPIENT_REMOVE = 3,
  CALL = 5,
  CHANNEL_NAME_CHANGE = 5,
  CHANNEL_ICON_CHANGE = 5,
  CHANNEL_PINNED_MESSAGE = 5,
  GUILD_MEMBER_JOIN = 5,
  USER_PREMIUM_GUILD_SUBSCRIPTION = 5,
  USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
  USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
  USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
  CHANNEL_FOLLOW_ADD = 12,
  GUILD_DISCOVERY_DISQUALIFIED = 14,
  GUILD_DISCOVERY_REQUALIFIED = 15,
  REPLY = 19,
  APPLICATION_COMMAND = 20,
};
} // namespace types

/* Title: Message Structure */
/* https://discord.com/developers/docs/resources/channel#message-object */
/* This is defined at specs/channel.message.json:128:22 */
struct dati {
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

  /* specs/channel.message.json:134:60
     '{"type":{"base":"user::dati", "dec":"*"}, "name":"author"}'
  */
  user::dati *author;

  /* specs/channel.message.json:135:69
     '{"type":{"base":"guild::member::dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  guild::member::dati *member; // partial guild member object

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

  /* specs/channel.message.json:143:62
     '{"type":{"base":"user::dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
  user::dati **mentions; // array of user objects, with an additional partial member field

  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
  ja_u64 **mention_roles; // array of role object ids

  /* specs/channel.message.json:146:65
     '{"type":{"base":"mention::dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
  mention::dati **mention_channels;

  /* specs/channel.message.json:148:68
     '{"type":{"base":"attachment::dati", "dec":"ntl"}, "name":"attachments"}'
  */
  attachment::dati **attachments;

  /* specs/channel.message.json:149:63
     '{"type":{"base":"embed::dati", "dec":"ntl"}, "name":"embeds"}'
  */
  embed::dati **embeds;

  /* specs/channel.message.json:150:65
     '{"type":{"base":"reaction::dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
  reaction::dati **reactions;

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

  /* specs/channel.message.json:157:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::types::code"}, "name":"type"}'
  */
  discord::channel::message::types::code type;

  /* specs/channel.message.json:158:91
     '{"type":{"base":"discord::channel::message::activity::dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  discord::channel::message::activity::dati *activity;

  /* specs/channel.message.json:160:96
     '{"type":{"base":"discord::channel::message::application::dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
  discord::channel::message::application::dati **application;

  /* specs/channel.message.json:162:92
     '{"type":{"base":"discord::channel::message::reference::dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  discord::channel::message::reference::dati *message_reference;

  /* specs/channel.message.json:164:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::flags::code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
  discord::channel::message::flags::code flags;

  /* specs/channel.message.json:166:92
     '{"type":{"base":"discord::channel::message::sticker::dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
  discord::channel::message::sticker::dati **stickers; // array of sticker objects

  /* specs/channel.message.json:168:81
     '{"type":{"base":"discord::channel::message::dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
  discord::channel::message::dati *referenced_message; // this will cause recursive allocation if allocating as the parent

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
