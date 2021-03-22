/* This file is generated from specs/guild.membership_screening.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/

/* https://discord.com/developers/docs/resources/guild#membership-screening-object-membership-screening-field-structure */
/* This is defined at specs/guild.membership_screening.json:17:22 */
struct discord_guild_membership_screening_field_dati {
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"field_type::code" }}'
  */
  field_type_code field_type;

  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
  char *label;

  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  //@todo values (null);

  /* specs/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */
  bool required;

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

/* This is defined at specs/guild.membership_screening.json:27:22 */
struct discord_guild_membership_screening_dati {
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  uint64_t version;

  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
  */
  discord_guild_membership_screening_field_dati **fields;

  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  char *description;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
/* This file is generated from specs/channel.edit-channel-permissions.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#edit-channel-permissions */
/* This is defined at specs/channel.edit-channel-permissions.json:8:22 */
struct discord_channel_edit_channel_permissions_params {
  /* specs/channel.edit-channel-permissions.json:11:20
     '{ "name": "allow", "type":{ "base":"char", "dec":"*"}}'
  */
  char *allow;

  /* specs/channel.edit-channel-permissions.json:12:20
     '{ "name": "deny", "type":{ "base":"char", "dec":"*"}}'
  */
  char *deny;

  /* specs/channel.edit-channel-permissions.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
/* This file is generated from specs/channel.modify-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#modify-channel */
/* This is defined at specs/channel.modify-channel.json:8:22 */
struct discord_channel_modify_params {
  /* specs/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/channel.modify-channel.json:12:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/channel.modify-channel.json:13:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  int position;

  /* specs/channel.modify-channel.json:14:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}'
  */
  char *topic;

  /* specs/channel.modify-channel.json:15:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}'
  */
  bool nsfw;

  /* specs/channel.modify-channel.json:16:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/channel.modify-channel.json:17:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/channel.modify-channel.json:18:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/channel.modify-channel.json:19:20
     '{ "name": "permission_overwrites", "type":{ "base":"discord::channel::overwrite::dati", "dec":"ntl" }, "inject_if_not":null}'
  */
  discord_channel_overwrite_dati **permission_overwrites;

  /* specs/channel.modify-channel.json:20:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[10];
    void *record_defined[10];
    void *record_null[10];
  } __M; // metadata
};
/* This file is generated from specs/channel.message.json, Please don't edit it. */
/*

*/

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
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
  */
  discord_channel_message_sticker_format_type_code type;

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

/* Title: Message Activity Structure */
/* https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure */
/* This is defined at specs/channel.message.json:92:22 */
struct discord_channel_message_activity_dati {
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */
  discord_channel_message_activity_types_code type;

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

  /* specs/channel.message.json:134:60
     '{"type":{"base":"user::dati", "dec":"*"}, "name":"author"}'
  */
  user_dati *author;

  /* specs/channel.message.json:135:69
     '{"type":{"base":"guild::member::dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  guild_member_dati *member; // partial guild member object

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
  user_dati **mentions; // array of user objects, with an additional partial member field

  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
  ja_u64 **mention_roles; // array of role object ids

  /* specs/channel.message.json:146:65
     '{"type":{"base":"mention::dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
  mention_dati **mention_channels;

  /* specs/channel.message.json:148:68
     '{"type":{"base":"attachment::dati", "dec":"ntl"}, "name":"attachments"}'
  */
  attachment_dati **attachments;

  /* specs/channel.message.json:149:63
     '{"type":{"base":"embed::dati", "dec":"ntl"}, "name":"embeds"}'
  */
  embed_dati **embeds;

  /* specs/channel.message.json:150:65
     '{"type":{"base":"reaction::dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
  reaction_dati **reactions;

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
  discord_channel_message_types_code type;

  /* specs/channel.message.json:158:91
     '{"type":{"base":"discord::channel::message::activity::dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  discord_channel_message_activity_dati *activity;

  /* specs/channel.message.json:160:96
     '{"type":{"base":"discord::channel::message::application::dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
  discord_channel_message_application_dati **application;

  /* specs/channel.message.json:162:92
     '{"type":{"base":"discord::channel::message::reference::dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  discord_channel_message_reference_dati *message_reference;

  /* specs/channel.message.json:164:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::flags::code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
  discord_channel_message_flags_code flags;

  /* specs/channel.message.json:166:92
     '{"type":{"base":"discord::channel::message::sticker::dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
  discord_channel_message_sticker_dati **stickers; // array of sticker objects

  /* specs/channel.message.json:168:81
     '{"type":{"base":"discord::channel::message::dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
  discord_channel_message_dati *referenced_message; // this will cause recursive allocation if allocating as the parent

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
/* This file is generated from specs/template.create-guild-template.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/template#create-guild-template */
/* This is defined at specs/template.create-guild-template.json:8:22 */
struct discord_Template_create_guild_template_params {
  /* specs/template.create-guild-template.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[100+1]"}, "comment":"name of the guild"}'
  */
  char name[100+1]; // name of the guild

  /* specs/template.create-guild-template.json:12:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[120+1]" }, 
          "comment":"description for the template (0-120) chars"}'
  */
  char description[120+1]; // description for the template (0-120) chars

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
/* This file is generated from specs/channel.group-dm-add-recipient.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#group-dm-add-recipient */
/* This is defined at specs/channel.group-dm-add-recipient.json:8:22 */
struct discord_channel_group_dm_add_recipient_params {
  /* specs/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
  char *access_token;

  /* specs/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */
  char *nick;

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
/* This file is generated from specs/channel.create-channel-invite.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#create-channel-invite */
/* This is defined at specs/channel.create-channel-invite.json:8:22 */
struct discord_channel_create_channel_invite_params {
  /* specs/channel.create-channel-invite.json:11:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"url"}'
  */
  u64_snowflake_t channel_id;

  /* specs/channel.create-channel-invite.json:12:20
     '{ "name": "max_age", "type":{ "base":"int" } }'
  */
  int max_age;

  /* specs/channel.create-channel-invite.json:13:20
     '{ "name": "max_uses", "type":{ "base":"int" } }'
  */
  int max_uses;

  /* specs/channel.create-channel-invite.json:14:20
     '{ "name": "temporary", "type":{ "base":"bool"}}'
  */
  bool temporary;

  /* specs/channel.create-channel-invite.json:15:20
     '{ "name": "unique", "type":{ "base":"bool"}}'
  */
  bool unique;

  /* specs/channel.create-channel-invite.json:16:20
     '{ "name": "target_user", "type":{ "base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":null}'
  */
  char *target_user;

  /* specs/channel.create-channel-invite.json:18:20
     '{ "name": "target_user_type", "type":{ "base":"int" },
          "option":true, "inject_if_not":0}'
  */
  int target_user_type;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
};
/* This file is generated from specs/guild.ban.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/

/* This is defined at specs/guild.ban.json:9:22 */
struct discord_guild_ban_dati {
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  char reason[MAX_REASON_LEN];

  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  discord_user_dati *user; // partial user object

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
/* This file is generated from specs/voice.json, Please don't edit it. */
/*
(null)
*/

/* Title: Voice State Object */
/* https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure */
/* This is defined at specs/voice.json:9:22 */
struct discord_voice_dati {
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t channel_id;

  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t user_id;

  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"discord::guild::member::dati", "dec":"*" }}'
  */
  discord_guild_member_dati *member;

  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
  char *session_id;

  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  bool deaf;

  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  bool mute;

  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
  bool self_deaf;

  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
  bool self_mute;

  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
  bool self_stream;

  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
  bool self_video;

  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
  */
  bool supress;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[12];
    void *record_defined[12];
    void *record_null[12];
  } __M; // metadata
};

/* Title: Voice Region Object */
/* https://discord.com/developers/docs/resources/voice#voice-region-object-voice-region-structure */
/* This is defined at specs/voice.json:30:22 */
struct discord_voice_region_dati {
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  char *id; // @todo fixed size limit

  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  char *name; // @todo fixed size limit

  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
  bool vip;

  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
  bool optimal;

  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
  bool deprecated;

  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
  */
  bool custom;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
};
/* This file is generated from specs/channel.get-reactions.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#get-reactions */
/* This is defined at specs/channel.get-reactions.json:8:22 */
struct discord_channel_get_reactions_params {
  /* specs/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
  u64_snowflake_t before;

  /* specs/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
  u64_snowflake_t after;

  /* specs/channel.get-reactions.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}'
  */
  int limit;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
/* This file is generated from specs/guild.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
*/

/* Title: Guild Structure */
/* This is defined at specs/guild.json:9:22 */
struct discord_guild_dati {
  /* specs/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/guild.json:13:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
  char name[MAX_NAME_LEN];

  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
  char *icon;

  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
  char *icon_hash;

  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
  char *splash;

  /* specs/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
  char *discovery_splash;

  /* specs/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
  bool owner;

  /* specs/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
  u64_snowflake_t owner_id;

  /* specs/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
  int permissions;

  /* specs/guild.json:21:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
  char region[MAX_REGION_LEN];

  /* specs/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
  u64_snowflake_t afk_channel_id;

  /* specs/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
  int afk_timeout;

  /* specs/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
  bool widget_enabled;

  /* specs/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
  u64_snowflake_t widget_channel_id;

  /* specs/guild.json:26:97
     '{"type":{"base":"int", "int_alias":"discord::guild::verification_level::code"}, "name":"verification_level"}'
  */
  discord_guild_verification_level_code verification_level;

  /* specs/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"discord::guild::default_message_notification_level::code"}, 
              "name":"default_message_notifications"}'
  */
  discord_guild_default_message_notification_level_code default_message_notifications;

  /* specs/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"discord::guild::explicit_content_filter_level::code"},
              "name":"explicit_content_filter"}'
  */
  discord_guild_explicit_content_filter_level_code explicit_content_filter;

  /* specs/guild.json:31:77
     '{"type":{"base":"discord::guild::role::dati", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  //@todo roles array of role objects;

  /* specs/guild.json:33:71
     '{"type":{"base":"discord::emoji::dati", "dec":"ntl"}, "name":"emojis"}'
  */
  discord_emoji_dati **emojis;

  /* specs/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  //@todo features array of guild feature strings;

  /* specs/guild.json:36:88
     '{"type":{"base":"int", "int_alias":"discord::guild::mfa_level::code"}, "name":"mfa_level"}'
  */
  discord_guild_mfa_level_code mfa_level;

  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
  u64_snowflake_t application_id;

  /* specs/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
  u64_snowflake_t system_channel_id;

  /* specs/guild.json:39:99
     '{"type":{"base":"int", "int_alias":"discord::guild::system_channel_flags::code"}, "name":"system_channel_flags"}'
  */
  discord_guild_system_channel_flags_code system_channel_flags;

  /* specs/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
  u64_snowflake_t rules_channel_id;

  /* specs/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
  u64_unix_ms_t joined_at;

  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
  bool large;

  /* specs/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
  bool unavailable;

  /* specs/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
  int member_count;

  /* specs/guild.json:45:71
     '{"type":{"base":"discord::voice::dati", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  //@todo voice_states array of partial voice state objects;

  /* specs/guild.json:47:79
     '{"type":{"base":"discord::guild::member::dati", "dec":"ntl"}, "name":"members", "option":true}'
  */
  discord_guild_member_dati **members;

  /* specs/guild.json:48:73
     '{"type":{"base":"discord::channel::dati", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
  discord_channel_dati **channels; // array of channel objects

  /* specs/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  //@todo presences array of partial presence update objects;

  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
  int max_presences;

  /* specs/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
  int max_members;

  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url_code"}'
  */
  char *vanity_url_code;

  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
  char *description;

  /* specs/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
  char *banner;

  /* specs/guild.json:57:91
     '{"type":{"base":"int", "int_alias":"discord::guild::premium_tier::code"}, "name":"premium_tier"}'
  */
  discord_guild_premium_tier_code premium_tier;

  /* specs/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
  int premium_subscription_count;

  /* specs/guild.json:59:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
  char preferred_locale[MAX_LOCALE_LEN];

  /* specs/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
  u64_snowflake_t public_updates_channel_id;

  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
  int max_video_channel_users;

  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
  int approximate_member_count;

  /* specs/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
  int approximate_presence_count;

  /* specs/guild.json:65:85
     '{"type":{"base":"discord::guild::welcome_screen::dati", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
  discord_guild_welcome_screen_dati *welcome_screen;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[46];
    void *record_defined[46];
    void *record_null[46];
  } __M; // metadata
};
/* This file is generated from specs/user.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/user#user-object
*/

/* Title: User Structure */
/* This is defined at specs/user.json:44:18 */
struct discord_user_dati {
  /* specs/user.json:47:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
  u64_snowflake_t id;

  /* specs/user.json:48:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
  char username[MAX_USERNAME_LEN];

  /* specs/user.json:49:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
  char discriminator[MAX_DISCRIMINATOR_LEN];

  /* specs/user.json:50:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  char avatar[MAX_SHA256_LEN];

  /* specs/user.json:51:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
  bool bot;

  /* specs/user.json:52:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
  bool System;

  /* specs/user.json:53:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
  bool mfa_enabled;

  /* specs/user.json:54:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
  char locale[MAX_LOCALE_LEN];

  /* specs/user.json:55:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  bool verified;

  /* specs/user.json:56:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
  char email[MAX_EMAIL_LEN];

  /* specs/user.json:57:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "discord::user::flags::code" }}'
  */
  discord_user_flags_code flags;

  /* specs/user.json:58:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "discord::user::premium_types::code" }}'
  */
  discord_user_premium_types_code premium_type;

  /* specs/user.json:59:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "discord::user::flags::code" }}'
  */
  discord_user_flags_code public_flags;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[13];
    void *record_defined[13];
    void *record_null[13];
  } __M; // metadata
};

/* Title: Connection Structure */
/* https://discord.com/developers/docs/resources/user#connection-object-connection-structure */
/* This is defined at specs/user.json:77:18 */
struct discord_user_connection_dati {
  /* specs/user.json:80:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *id; // @todo fixed size limit

  /* specs/user.json:81:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/user.json:82:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  char *type;

  /* specs/user.json:83:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  bool revoked;

  /* specs/user.json:84:20
     '{ "name": "integrations", "type": {"base":"discord::guild::integration::dati", "dec":"ntl"}, "todo":true}'
  */
  //@todo integrations (null);

  /* specs/user.json:85:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  bool verified;

  /* specs/user.json:86:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
  bool friend_sync;

  /* specs/user.json:87:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
  bool show_activity;

  /* specs/user.json:88:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"discord::user::connection::visibility_types::code" }}'
  */
  discord_user_connection_visibility_types_code visibility;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
};
/* This file is generated from specs/guild.modify-guild-member.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#modify-guild-member */
/* This is defined at specs/guild.modify-guild-member.json:8:22 */
struct discord_guild_modify_guild_member_params {
  /* specs/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
  char *nick;

  /* specs/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
  ja_u64 **roles;

  /* specs/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool mute;

  /* specs/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool deaf;

  /* specs/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  u64_snowflake_t channel_id;

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
/* This file is generated from specs/guild.integration.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/

/* Title: Integration Account Structure */
/* https://discord.com/developers/docs/resources/guild#integration-account-object-integration-account-structure */
/* This is defined at specs/guild.integration.json:21:22 */
struct discord_guild_integration_account_dati {
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
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
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
};

/* Title: Integration Application Object */
/* https://discord.com/developers/docs/resources/guild#integration-application-object-integration-application-structure */
/* This is defined at specs/guild.integration.json:31:22 */
struct discord_guild_integration_application_dati {
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  char icon[MAX_SHA256_LEN];

  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
  char *description;

  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
  char *summary;

  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"discord::user::dati", "dec":"*" }, "option":true}'
  */
  discord_user_dati *bot;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
};

/* Title: Integration Structure */
/* https://discord.com/developers/docs/resources/guild#integration-object-integration-structure */
/* This is defined at specs/guild.integration.json:45:22 */
struct discord_guild_integration_dati {
  /* specs/guild.integration.json:48:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.integration.json:49:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/guild.integration.json:50:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  char *type;

  /* specs/guild.integration.json:51:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
  bool enabled;

  /* specs/guild.integration.json:52:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
  bool syncing;

  /* specs/guild.integration.json:53:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t role_id;

  /* specs/guild.integration.json:54:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
  bool enable_emotions;

  /* specs/guild.integration.json:55:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"discord::guild::integration::expire_behaviors::code"}}'
  */
  discord_guild_integration_expire_behaviors_code expire_behavior;

  /* specs/guild.integration.json:56:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
  int expire_grace_period;

  /* specs/guild.integration.json:57:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "opt":true}'
  */
  discord_user_dati *user;

  /* specs/guild.integration.json:58:20
     '{ "name": "account", "type":{ "base":"discord::guild::integration::account::dati", "dec":"*"}}'
  */
  discord_guild_integration_account_dati *account;

  /* specs/guild.integration.json:59:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  u64_unix_ms_t synced_at;

  /* specs/guild.integration.json:60:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
  int subscriber_count;

  /* specs/guild.integration.json:61:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  bool revoked;

  /* specs/guild.integration.json:62:20
     '{ "name": "application", "type":{ "base":"discord::guild::integration::application::dati", "dec":"*" }}'
  */
  discord_guild_integration_application_dati *application;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[15];
    void *record_defined[15];
    void *record_null[15];
  } __M; // metadata
};
/* This file is generated from specs/guild.enum.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/

/* Title: Unavailable Guild Object */
/* https://discord.com/developers/docs/resources/guild#unavailable-guild-object */
/* This is defined at specs/guild.enum.json:100:23 */
struct discord_guild_unavailable_guild_dati {
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/guild.enum.json:103:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
  bool unavailable;

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

/* Title: Guild Preview Object */
/* https://discord.com/developers/docs/resources/guild#guild-preview-object */
/* This is defined at specs/guild.enum.json:110:23 */
struct discord_guild_preview_dati {
  /* specs/guild.enum.json:112:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/guild.enum.json:113:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  char name[MAX_NAME_LEN];

  /* specs/guild.enum.json:114:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  char *icon;

  /* specs/guild.enum.json:115:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  char *splash;

  /* specs/guild.enum.json:116:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  char *discovery;

  /* specs/guild.enum.json:117:18
     '{"name":"emojis", "type":{"base":"discord::emoji::dati", "dec":"*"}}'
  */
  discord_emoji_dati *emojis;

  /* specs/guild.enum.json:118:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  //@todo features (null);

  /* specs/guild.enum.json:119:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
  int approximate_member_count;

  /* specs/guild.enum.json:120:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
  int approximate_presence_count;

  /* specs/guild.enum.json:121:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  char description[MAX_DESCRIPTION_LEN];

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[10];
    void *record_defined[10];
    void *record_null[10];
  } __M; // metadata
};

/* Title: Guild Widget Object */
/* https://discord.com/developers/docs/resources/guild#guild-widget-object */
/* This is defined at specs/guild.enum.json:128:23 */
struct discord_guild_widget_dati {
  /* specs/guild.enum.json:130:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
  bool enabled;

  /* specs/guild.enum.json:131:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
  u64_snowflake_t channel_id;

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
/* This file is generated from specs/invite.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/invite#invite-object
*/

/* Title: Invite Structure */
/* https://discord.com/developers/docs/resources/invite#invite-object-invite-structure */
/* This is defined at specs/invite.json:19:22 */
struct discord_invite_dati {
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *code; // @todo fixed size limit

  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"discord::guild::dati", "dec":"*"}, "comment":"partial guild object"}'
  */
  discord_guild_dati *guild; // partial guild object

  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"discord::channel::dati", "dec":"*"}, "comment":"partial channel object"}'
  */
  discord_channel_dati *channel; // partial channel object

  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"discord::user::dati", "dec":"*"}}'
  */
  discord_user_dati *inviter;

  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  discord_user_dati *target_user; // partial user object

  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"discord::invite::target_user_types::code" }}'
  */
  discord_invite_target_user_types_code target_user_type;

  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
  int approximate_presence_count;

  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
  int approximate_member_count;

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

/* Title: Invite Metadata Structure */
/* https://discord.com/developers/docs/resources/invite#invite-metadata-object */
/* This is defined at specs/invite.json:36:22 */
struct discord_invite_metadata_dati {
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
  int user;

  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
  int max_uses;

  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
  int max_age;

  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
  int temporary;

  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  u64_unix_ms_t created_at;

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
/* This file is generated from specs/webhook.modify-webhook.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#modify-webhook */
/* This is defined at specs/webhook.modify-webhook.json:8:22 */
struct discord_webhook_modify_webhook_params {
  /* specs/webhook.modify-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
  char name[80+1]; // name of the webhook(1-80) chars

  /* specs/webhook.modify-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
  char *avatar; // base64 image for the default webhook avatar

  /* specs/webhook.modify-webhook.json:16:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "comment":"the new channel id this webhook should be moved to" }'
  */
  u64_snowflake_t channel_id; // the new channel id this webhook should be moved to

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
/* This file is generated from specs/template.create-guild-from-template.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/template#create-guild-from-template */
/* This is defined at specs/template.create-guild-from-template.json:8:22 */
struct discord_Template_create_guild_from_template_params {
  /* specs/template.create-guild-from-template.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}'
  */
  char *name; // name of the guild

  /* specs/template.create-guild-from-template.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon"}'
  */
  char *icon; // base64 128x128 image for the guild icon

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
/* This file is generated from specs/channel.objects.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/

/* Title: Overwrite Structure */
/* This is defined at specs/channel.objects.json:10:22 */
struct discord_channel_overwrite_dati {
  /* specs/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"permissions::bitwise_flags"}, "comment":"permission bit set"}'
  */
  permissions::bitwise_flags allow; // permission bit set

  /* specs/channel.objects.json:16:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"permissions::bitwise_flags"}, "comment":"permission bit set"}'
  */
  permissions::bitwise_flags deny; // permission bit set

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

/* https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure */
/* This is defined at specs/channel.objects.json:22:22 */
struct discord_channel_reaction_dati {
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  int count;

  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  bool me;

  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  discord_emoji_dati *emoji; // partial emoji object

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};

/* Title: Followed Channel Structure */
/* https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure */
/* This is defined at specs/channel.objects.json:34:22 */
struct discord_channel_followed_channel_dati {
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/channel.objects.json:38:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t webhook_id;

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

/* https://discord.com/developers/docs/resources/channel#attachment-object */
/* This is defined at specs/channel.objects.json:44:22 */
struct discord_channel_attachment_dati {
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  char filename[256];

  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  int size;

  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  int height;

  /* specs/channel.objects.json:53:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
  int width;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
};

/* Title: Channel Mention Structure */
/* https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure */
/* This is defined at specs/channel.objects.json:60:22 */
struct discord_channel_mention_dati {
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */
  discord_channel_types_code type;

  /* specs/channel.objects.json:66:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
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
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};

/* Title: Allowed Mentions Structure */
/* https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure */
/* This is defined at specs/channel.objects.json:73:22 */
struct discord_channel_allowed_mentions_dati {
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  ja_str **parse;

  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **roles; // list of snowflakes

  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **users; // list of snowflakes

  /* specs/channel.objects.json:79:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
  bool replied_user;

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

/* Title: Embed Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-structure */
/* This is defined at specs/channel.objects.json:86:22 */
struct discord_channel_embed_dati {
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char title[EMBED_TITLE_LEN];

  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  char type[32];

  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  char description[EMBED_DESCRIPTION_LEN];

  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  u64_unix_ms_t timestamp;

  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  int color;

  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  discord_channel_embed_footer_dati *footer;

  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord_channel_embed_image_dati *image;

  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord_channel_embed_thumbnail_dati *thumbnail;

  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord_channel_embed_video_dati *video;

  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord_channel_embed_provider_dati *provider;

  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
  discord_channel_embed_author_dati *author;

  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  discord_channel_embed_field_dati **fields;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[13];
    void *record_defined[13];
    void *record_null[13];
  } __M; // metadata
};

/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure */
/* This is defined at specs/channel.objects.json:117:22 */
struct discord_channel_embed_thumbnail_dati {
  /* specs/channel.objects.json:119:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:120:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:121:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/channel.objects.json:122:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int width;

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

/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure */
/* This is defined at specs/channel.objects.json:117:22 */
struct discord_channel_embed_video_dati {
  /* specs/channel.objects.json:119:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:120:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:121:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/channel.objects.json:122:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int width;

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

/* Title: Embed Thumbnail Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure */
/* This is defined at specs/channel.objects.json:117:22 */
struct discord_channel_embed_image_dati {
  /* specs/channel.objects.json:119:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:120:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_url[MAX_URL_LEN];

  /* specs/channel.objects.json:121:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/channel.objects.json:122:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int width;

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

/* Title: Embed Provider Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure */
/* This is defined at specs/channel.objects.json:129:22 */
struct discord_channel_embed_provider_dati {
  /* specs/channel.objects.json:131:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/channel.objects.json:132:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

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

/* Title: Embed Author Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure */
/* This is defined at specs/channel.objects.json:139:22 */
struct discord_channel_embed_author_dati {
  /* specs/channel.objects.json:141:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/channel.objects.json:142:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char url[MAX_URL_LEN];

  /* specs/channel.objects.json:143:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char icon_url[MAX_URL_LEN];

  /* specs/channel.objects.json:144:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  char proxy_icon_url[MAX_URL_LEN];

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

/* Title: Embed Footer Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure */
/* This is defined at specs/channel.objects.json:151:22 */
struct discord_channel_embed_footer_dati {
  /* specs/channel.objects.json:153:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  char text[EMBED_FOOTER_TEXT_LEN];

  /* specs/channel.objects.json:154:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char icon_url[MAX_URL_LEN];

  /* specs/channel.objects.json:156:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  char proxy_icon_url[MAX_URL_LEN];

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};

/* Title: Embed Field Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure */
/* This is defined at specs/channel.objects.json:164:22 */
struct discord_channel_embed_field_dati {
  /* specs/channel.objects.json:166:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_FIELD_NAME_LEN];

  /* specs/channel.objects.json:167:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  char value[EMBED_FIELD_VALUE_LEN];

  /* specs/channel.objects.json:168:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
  bool Inline;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
/* This file is generated from specs/guild.create-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild-channel */
/* This is defined at specs/guild.create-channel.json:8:22 */
struct discord_guild_create_channel_params {
  /* specs/guild.create-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/guild.create-channel.json:12:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/guild.create-channel.json:13:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}'
  */
  char *topic;

  /* specs/guild.create-channel.json:14:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/guild.create-channel.json:15:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/guild.create-channel.json:16:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/guild.create-channel.json:17:20
     '{ "name": "position", "type":{ "base":"int" } }'
  */
  int position;

  /* specs/guild.create-channel.json:18:20
     '{ "name": "permission_overwrites", "type":{ "base":"discord::channel::overwrite::dati", "dec":"ntl" }, "inject_if_not":null}'
  */
  discord_channel_overwrite_dati **permission_overwrites;

  /* specs/guild.create-channel.json:19:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  /* specs/guild.create-channel.json:20:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}'
  */
  bool nsfw;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[10];
    void *record_defined[10];
    void *record_null[10];
  } __M; // metadata
};
/* This file is generated from specs/emoji.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
*/

/* Title: Emoji Structure */
/* This is defined at specs/emoji.json:8:22 */
struct discord_emoji_dati {
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  char name[MAX_NAME_LEN];

  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"discord::guild::role::dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */
  //@todo roles (null);

  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }, "option":true }'
  */
  discord_user_dati *user;

  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
  bool require_colons;

  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
  bool managed;

  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
  bool animated;

  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */
  bool available;

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
/* This file is generated from specs/webhook.create-webhook.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#create-webhook */
/* This is defined at specs/webhook.create-webhook.json:8:22 */
struct discord_webhook_create_webhook_params {
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
  char name[80+1]; // name of the webhook(1-80) chars

  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
  char *avatar; // base64 image for the default webhook avatar

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
/* This file is generated from specs/guild.welcome_screen.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#welcome-screen-object
*/

/* Title: Welcome Screen Channel Structure */
/* https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure */
/* This is defined at specs/guild.welcome_screen.json:11:22 */
struct discord_guild_welcome_screen_screen_channel_dati {
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  char *description;

  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t emoji_id;

  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *emoji_name;

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

/* Title: Welcome Screen Structure */
/* https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-structure */
/* This is defined at specs/guild.welcome_screen.json:23:22 */
struct discord_guild_welcome_screen_dati {
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *description; // @todo fixed size limit

  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"discord::guild::welcome_screen::screen_channel::dati", "dec":"ntl" }, "todo":false }'
  */
  discord_guild_welcome_screen_screen_channel_dati **welcome_channels;

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
/* This file is generated from specs/guild.create-guild.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild */
/* This is defined at specs/guild.create-guild.json:8:22 */
struct discord_guild_create_guild_params {
  /* specs/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
  char name[200+1]; // name of the guild (2-100) characters

  /* specs/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
  char *region; // voice region id

  /* specs/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
  char *icon; // base64 128x1128 image for the guild icon

  /* specs/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
  int verification_level; // verification level

  /* specs/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
  int default_message_notifications; // default message notification level

  /* specs/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
  int explicit_content_filter; // explicit content filter level

  /* specs/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */
  //@todo roles new guild roles;

  /* specs/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"discord::channel::dati", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
  discord_channel_dati **channels; // array of partial channel objects

  /* specs/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
  u64_snowflake_t afk_channel_id; // id for afk channel

  /* specs/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
  int afk_timeout; // afk timeout in seconds

  /* specs/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
  u64_snowflake_t system_channel_id; // the id of the channel where guild notices such as welcome messages and boost events are posted

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[11];
    void *record_defined[11];
    void *record_null[11];
  } __M; // metadata
};
/* This file is generated from specs/channel.bulk-delete-messages.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#bulk-delete-messages */
/* This is defined at specs/channel.bulk-delete-messages.json:8:22 */
struct discord_channel_bulk_delete_messages_params {
  /* specs/channel.bulk-delete-messages.json:11:20
     '{ "name": "messages", "type":{ "base":"ja_u64", "dec":"ntl" }}'
  */
  ja_u64 **messages;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[1];
    void *record_defined[1];
    void *record_null[1];
  } __M; // metadata
};
/* This file is generated from specs/webhook.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
*/

/* Title: Webhook Structure */
/* This is defined at specs/webhook.json:19:22 */
struct discord_webhook_dati {
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */
  discord_webhook_types_code type;

  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  discord_user_dati *user;

  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
  char name[WEBHOOK_NAME_LEN];

  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *avatar; // @todo fixed size limit

  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *token; // @todo fixed size limit

  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t application_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
};
/* This file is generated from specs/user.create-group-dm.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/user#create-group-dm */
/* This is defined at specs/user.create-group-dm.json:8:22 */
struct discord_user_create_group_dm_params {
  /* specs/user.create-group-dm.json:11:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}'
  */
  ja_str **access_tokens; // access tokens of users that have granted your app the gdm.join scope

  /* specs/user.create-group-dm.json:13:19
     '{ "name":"nick", "type":{ "base":"char", "dec":"*"}, 
          "todo":true,
          "comment":"ia dictionary of user ids to their respective nicknames"}'
  */
  //@todo nick ia dictionary of user ids to their respective nicknames;

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
/* This file is generated from specs/emoji.modify-guild-emoji.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/emoji#create-guild-emoji */
/* This is defined at specs/emoji.modify-guild-emoji.json:8:22 */
struct discord_emoji_modify_guild_emoji_params {
  /* specs/emoji.modify-guild-emoji.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/emoji.modify-guild-emoji.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}'
  */
  ja_u64 **roles; // roles for which this emoji will be whitelisted

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
/* This file is generated from specs/webhook.execute-webhook.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#execute-webhook */
/* This is defined at specs/webhook.execute-webhook.json:8:22 */
struct discord_webhook_execute_webhook_params {
  /* specs/webhook.execute-webhook.json:12:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"name of the webhook(1-80) chars",
          "required":"one of content, file, embeds"
        }'
  */
  bool wait; // name of the webhook(1-80) chars

  /* specs/webhook.execute-webhook.json:16:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"the message contents (up to 2000 characters",
          "required":false
        }'
  */
  char content[2000+1]; // the message contents (up to 2000 characters

  /* specs/webhook.execute-webhook.json:20:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }'
  */
  char *username; // override the default username of the webhook

  /* specs/webhook.execute-webhook.json:24:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }'
  */
  char *avatar_url; // override the default avatar of the webhook

  /* specs/webhook.execute-webhook.json:26:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }'
  */
  bool tts; // true if this is a TTS message

  /* specs/webhook.execute-webhook.json:30:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }'
  */
  char *file; // the contents of the file being sent

  /* specs/webhook.execute-webhook.json:34:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }'
  */
  discord_channel_embed_dati *embeds; // embedded rich content

  /* specs/webhook.execute-webhook.json:38:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }'
  */
  char *payload_json; // See message create

  /* specs/webhook.execute-webhook.json:42:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }'
  */
  discord_channel_allowed_mentions_dati *allowed_mentions; // allowed mentions for the message

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
};
/* This file is generated from specs/guild.role.create.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild-role */
/* This is defined at specs/guild.role.create.json:8:22 */
struct discord_guild_create_guild_role_params {
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"permissions::bitwise_flags" }, "inject_if_not":0}'
  */
  permissions::bitwise_flags permissions;

  /* specs/guild.role.create.json:13:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int color;

  /* specs/guild.role.create.json:14:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool hoist;

  /* specs/guild.role.create.json:15:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool memtionable;

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
/* This file is generated from specs/permissions.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions
*/
/* This file is generated from specs/audit_log.json, Please don't edit it. */
/*
(null)
*/

/* Title: Audit Log Structure */
/* https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure */
/* This is defined at specs/audit_log.json:8:22 */
struct discord_audit_log_dati {
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"discord::webhook::dati", "dec":"*" } }'
  */
  discord_webhook_dati *webhooks;

  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"user::dati", "dec":"*"}}'
  */
  user_dati *users;

  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"entry::dati", "dec":"*"}}'
  */
  entry_dati *audit_log_entries;

  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"guild::integration::dati", "dec":"ntl"}}'
  */
  guild_integration_dati **integrations;

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

/* Title: Audit Log Entry Structure */
/* https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-entry-structure */
/* This is defined at specs/audit_log.json:64:22 */
struct discord_audit_log_entry_dati {
  /* specs/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */
  char *target_id;

  /* specs/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"change::dati", "dec":"*"}}'
  */
  change_dati *changes;

  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t user_id;

  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"events::code"}}'
  */
  int action_type;

  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"optional_info::dati", "dec":"*"}}'
  */
  optional_info_dati *options;

  /* specs/audit_log.json:73:18
     '{"name":"reason", "type": {"base":"char", "dec":"[MAX_REASON_LEN]"}}'
  */
  char reason[MAX_REASON_LEN];

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
};

/* Title: Optional Audit Entry Info Structure */
/* https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-optional-audit-entry-info */
/* This is defined at specs/audit_log.json:80:22 */
struct discord_audit_log_entry_optional_info_dati {
  /* specs/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *delete_member_days; // @todo find fixed size limit

  /* specs/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *members_removed; // @todo find fixed size limit

  /* specs/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
  u64_snowflake_t channel_id;

  /* specs/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
  u64_snowflake_t message_id;

  /* specs/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  char *count; // @todo find fixed size limit

  /* specs/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  char *type; // @todo find fixed size limit

  /* specs/audit_log.json:90:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  char *role; // @todo find fixed size limit

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

/* Title: Audit Log Change Structure */
/* https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-structure */
/* This is defined at specs/audit_log.json:97:22 */
struct discord_audit_log_change_dati {
  /* specs/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */
  char *new_value;

  /* specs/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */
  char *old_value;

  /* specs/audit_log.json:102:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}'
  */
  char key[64];

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};

/* Title: Audit Log Change Key */
/* https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-key */
/* This is defined at specs/audit_log.json:109:22 */
struct discord_audit_log_change_key_dati {
  /* specs/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  char name[MAX_NAME_LEN];

  /* specs/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  char description[MAX_DESCRIPTION_LEN];

  /* specs/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */
  char icon_hash[MAX_SHA256_LEN]; // icon changed

  /* specs/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */
  char splash_hash[MAX_SHA256_LEN]; // invite splash page artwork changed

  /* specs/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
  char discovery_splash_hash[MAX_SHA256_LEN];

  /* specs/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t banner_hash;

  /* specs/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t owner_id;

  /* specs/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */
  char region[MAX_REGION_LEN];

  /* specs/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */
  char preferred_locale[MAX_LOCALE_LEN];

  /* specs/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t afk_channel_id;

  /* specs/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */
  int afk_timeout;

  /* specs/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t rules_channel_id;

  /* specs/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t public_updates_channel_id;

  /* specs/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */
  int mfa_level;

  /* specs/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */
  int verification_level;

  /* specs/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */
  int explicit_content_filter;

  /* specs/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */
  int default_message_notifications;

  /* specs/audit_log.json:131:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}}'
  */
  char *vanity_url_code;

  /* specs/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo add (null);

  /* specs/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo remove (null);

  /* specs/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */
  int prune_delete_days;

  /* specs/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */
  bool widget_enabled;

  /* specs/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t widget_channel_id;

  /* specs/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t system_channel_id;

  /* specs/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */
  int position;

  /* specs/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */
  char *topic;

  /* specs/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */
  int bitrate;

  /* specs/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo permission_overwrites (null);

  /* specs/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */
  bool nsfw;

  /* specs/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t application_id;

  /* specs/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */
  int rate_limit_per_user;

  /* specs/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */
  char *permissions;

  /* specs/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */
  int color;

  /* specs/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */
  bool hoist;

  /* specs/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */
  bool mentionable;

  /* specs/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */
  char *allow;

  /* specs/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */
  char *deny;

  /* specs/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */
  char *code;

  /* specs/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */
  char *channel_id;

  /* specs/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */
  char *inviter_id;

  /* specs/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */
  char *max_uses;

  /* specs/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */
  char *uses;

  /* specs/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */
  char *max_age;

  /* specs/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */
  char *temporary;

  /* specs/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */
  char *deaf;

  /* specs/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */
  char *mute;

  /* specs/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */
  char *nick;

  /* specs/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */
  char *avatar_hash;

  /* specs/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */
  //@todo type integer or string;

  /* specs/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */
  bool enable_emotions;

  /* specs/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */
  int expire_behavior;

  /* specs/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */
  int expire_grace_period;

  /* specs/audit_log.json:171:18
     '{"name":"user_limit", "type": {"base":"int" }}'
  */
  int user_limit;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[54];
    void *record_defined[54];
    void *record_null[54];
  } __M; // metadata
};
/* This file is generated from specs/guild.role.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/

/* Title: Role Tags Structure */
/* This is defined at specs/guild.role.json:9:22 */
struct discord_guild_role_tags_dati {
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t bot_id;

  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t integration_id;

  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
  int premium_subscriber;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};

/* Title: Role Object */
/* This is defined at specs/guild.role.json:20:22 */
struct discord_guild_role_dati {
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
  char name[MAX_NAME_LEN];

  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
  int color;

  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
  bool hoist;

  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  int position;

  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
  char *permissions;

  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
  bool managed;

  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
  bool mentionable;

  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
  discord_guild_role_tags_dati *tags;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
};
/* This file is generated from specs/emoji.create-guild-emoji.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/emoji#create-guild-emoji */
/* This is defined at specs/emoji.create-guild-emoji.json:8:22 */
struct discord_emoji_create_guild_emoji_params {
  /* specs/emoji.create-guild-emoji.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/emoji.create-guild-emoji.json:12:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}'
  */
  char *image; // Base64 Encoded Image Data

  /* specs/emoji.create-guild-emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}'
  */
  ja_u64 **roles; // roles for which this emoji will be whitelisted

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
/* This file is generated from specs/template.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/template#template-object-template-structure
*/

/* Title: Template Structure */
/* This is defined at specs/template.json:9:22 */
struct discord_Template_dati {
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *code; // @todo find fixed size limit

  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *name; // @todo find fixed size limit

  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
  char *description; // @todo find fixed size limit

  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
  int usage_count;

  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t creator_id;

  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  discord_user_dati *creator;

  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t created_at;

  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t updated_at;

  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t source_guild_id;

  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"discord::guild::dati", "dec":"*" }}'
  */
  discord_guild_dati *serialized_source_guild;

  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
  bool is_dirty;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[11];
    void *record_defined[11];
    void *record_null[11];
  } __M; // metadata
};
/* This file is generated from specs/webhook.edit-webhook-message.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#edit-webhook-message */
/* This is defined at specs/webhook.edit-webhook-message.json:8:22 */
struct discord_webhook_edit_webhook_message_params {
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
  char content[2000+1]; // name of the webhook(1-2000) chars

  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
  discord_channel_embed_dati **embeds; // array of up to 10 embeds objects

  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
  discord_channel_allowed_mentions_dati *allowed_mentions; // allowed mentions for the message

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
/* This file is generated from specs/channel.follow-news-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#follow-news-channel */
/* This is defined at specs/channel.follow-news-channel.json:8:22 */
struct discord_channel_follow_news_channel_params {
  /* specs/channel.follow-news-channel.json:11:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t webhook_channel_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[1];
    void *record_defined[1];
    void *record_null[1];
  } __M; // metadata
};
/* This file is generated from specs/gateway.json, Please don't edit it. */
/*
(null)
*/

/* Title: Identify Structure */
/* https://discord.com/developers/docs/topics/gateway#identify-identify-structure */
/* This is defined at specs/gateway.json:75:22 */
struct discord_gateway_identify_dati {
  /* specs/gateway.json:78:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  char *token;

  /* specs/gateway.json:79:19
     '{ "name":"properties","type":{"base":"discord::gateway::identify::connection::dati", "dec":"*"}}'
  */
  discord_gateway_identify_connection_dati *properties;

  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  bool compress;

  /* specs/gateway.json:81:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
  int large_threshold;

  /* specs/gateway.json:82:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  bool guild_subscriptions;

  /* specs/gateway.json:83:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  //@todo shard (null);

  /* specs/gateway.json:84:19
     '{ "name":"presence","type":{"base":"discord::gateway::identify::status_update::dati", "dec":"*"}}'
  */
  discord_gateway_identify_status_update_dati *presence;

  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
  int intents;

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

/* Title: Gateway Status Update Structure */
/* https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure */
/* This is defined at specs/gateway.json:92:22 */
struct discord_gateway_identify_status_update_dati {
  /* specs/gateway.json:95:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "inject_if_not":0 }'
  */
  u64_unix_ms_t since;

  /* specs/gateway.json:97:19
     '{ "name":"activities","type":{"base":"discord::gateway::identify::status_update::activity::dati", 
          "dec":"ntl"}, "inject_if_not":null}'
  */
  discord_gateway_identify_status_update_activity_dati **activities;

  /* specs/gateway.json:99:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  char status[16];

  /* specs/gateway.json:100:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
  bool afk;

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

/* Title: Identify Connection Properties */
/* https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties */
/* This is defined at specs/gateway.json:107:22 */
struct discord_gateway_identify_connection_dati {
  /* specs/gateway.json:110:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
  char *$os;

  /* specs/gateway.json:111:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
  char *$browser;

  /* specs/gateway.json:112:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
  char *$device;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};

/* Title: Activity Structure */
/* https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure */
/* This is defined at specs/gateway.json:119:22 */
struct discord_gateway_identify_status_update_activity_dati {
  /* specs/gateway.json:122:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  char name[512];

  /* specs/gateway.json:123:19
     '{ "name":"type","type":{"base":"int"}}'
  */
  int type;

  /* specs/gateway.json:124:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"}}'
  */
  char url[MAX_URL_LEN];

  /* specs/gateway.json:125:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "inject_if_not":0 }'
  */
  u64_unix_ms_t created_at;

  /* specs/gateway.json:127:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t application_id;

  /* specs/gateway.json:128:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}}'
  */
  char *details;

  /* specs/gateway.json:129:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}}'
  */
  char *state;

  /* specs/gateway.json:130:19
     '{ "name":"instance","type":{"base":"bool"}}'
  */
  bool instance;

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
/* This file is generated from specs/template.modify-guild-template.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/template#modify-guild-template */
/* This is defined at specs/template.modify-guild-template.json:8:22 */
struct discord_Template_modify_guild_template_params {
  /* specs/template.modify-guild-template.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[100+1]"}, "comment":"name of the guild"}'
  */
  char name[100+1]; // name of the guild

  /* specs/template.modify-guild-template.json:12:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[120+1]" }, 
          "comment":"description for the template (0-120) chars"}'
  */
  char description[120+1]; // description for the template (0-120) chars

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
/* This file is generated from specs/channel.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#channel-object-channel-types
*/

/* Title: Channel Structure */
/* https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
/* This is defined at specs/channel.json:25:22 */
struct discord_channel_dati {
  /* specs/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/channel.json:29:86
     '{"type":{"base":"int", "int_alias":"discord::channel::types::code"}, "name":"type"}'
  */
  discord_channel_types_code type;

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
  discord_channel_overwrite_dati **permission_overwrites;

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
  discord_user_dati **recipients;

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
  discord_channel_message_dati **messages;

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
/* This file is generated from specs/guild.member.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-member-object
*/

/* This is defined at specs/guild.member.json:9:22 */
struct discord_guild_member_dati {
  /* specs/guild.member.json:12:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }, "option":true}'
  */
  discord_user_dati *user;

  /* specs/guild.member.json:13:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
  char nick[MAX_NAME_LEN];

  /* specs/guild.member.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
  ja_u64 **roles; // array of role object ids

  /* specs/guild.member.json:15:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t joined_at;

  /* specs/guild.member.json:16:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t premium_since;

  /* specs/guild.member.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  bool deaf;

  /* specs/guild.member.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  bool mute;

  /* specs/guild.member.json:19:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
  bool pending;

  /* specs/guild.member.json:20:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}'
  */
  char *permissions;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
};
/* This file is generated from specs/user.modify-curent-user.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/user#modify-current-user */
/* This is defined at specs/user.modify-curent-user.json:8:22 */
struct discord_user_modify_current_user_params {
  /* specs/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */
  char *username;

  /* specs/user.modify-curent-user.json:12:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}'
  */
  char *avatar; // base64 encoded image data

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
