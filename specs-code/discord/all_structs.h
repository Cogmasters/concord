/* This file is generated from specs/discord/audit_log.get-guild-audit-log.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/audit-log#get-guild-audit-log */
/* This is defined at specs/discord/audit_log.get-guild-audit-log.json:8:22 */
struct discord_get_guild_audit_log_params {
  /* specs/discord/audit_log.get-guild-audit-log.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
  u64_snowflake_t user_id;

  /* specs/discord/audit_log.get-guild-audit-log.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }'
  */
  enum discord_audit_log_events action_type;

  /* specs/discord/audit_log.get-guild-audit-log.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
  u64_snowflake_t before;

  /* specs/discord/audit_log.get-guild-audit-log.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
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
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/*
(null)
*/

/* Title: Audit Log Structure */
/* https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure */
/* This is defined at specs/discord/audit_log.json:8:22 */
struct discord_audit_log {
  /* specs/discord/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"*" } }'
  */
  struct discord_webhook *webhooks;

  /* specs/discord/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"*"}}'
  */
  struct discord_user *users;

  /* specs/discord/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"*"}}'
  */
  struct discord_audit_log_entry *audit_log_entries;

  /* specs/discord/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}'
  */
  struct discord_guild_integration **integrations;

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
/* This is defined at specs/discord/audit_log.json:64:22 */
struct discord_audit_log_entry {
  /* specs/discord/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */
  char *target_id;

  /* specs/discord/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"*"}}'
  */
  struct discord_audit_log_change *changes;

  /* specs/discord/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t user_id;

  /* specs/discord/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/discord/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}'
  */
  int action_type;

  /* specs/discord/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"*"}}'
  */
  struct discord_audit_log_entry_optional_info *options;

  /* specs/discord/audit_log.json:73:18
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
/* This is defined at specs/discord/audit_log.json:80:22 */
struct discord_audit_log_entry_optional_info {
  /* specs/discord/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *delete_member_days; // @todo find fixed size limit

  /* specs/discord/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *members_removed; // @todo find fixed size limit

  /* specs/discord/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
  u64_snowflake_t channel_id;

  /* specs/discord/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
  u64_snowflake_t message_id;

  /* specs/discord/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  char *count; // @todo find fixed size limit

  /* specs/discord/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  char *type; // @todo find fixed size limit

  /* specs/discord/audit_log.json:90:20
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
/* This is defined at specs/discord/audit_log.json:97:22 */
struct discord_audit_log_change {
  /* specs/discord/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */
  char *new_value;

  /* specs/discord/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */
  char *old_value;

  /* specs/discord/audit_log.json:102:18
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
/* This is defined at specs/discord/audit_log.json:109:22 */
struct discord_audit_log_change_key {
  /* specs/discord/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  char name[MAX_NAME_LEN];

  /* specs/discord/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  char description[MAX_DESCRIPTION_LEN];

  /* specs/discord/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */
  char icon_hash[MAX_SHA256_LEN]; // icon changed

  /* specs/discord/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */
  char splash_hash[MAX_SHA256_LEN]; // invite splash page artwork changed

  /* specs/discord/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
  char discovery_splash_hash[MAX_SHA256_LEN];

  /* specs/discord/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t banner_hash;

  /* specs/discord/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t owner_id;

  /* specs/discord/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */
  char region[MAX_REGION_LEN];

  /* specs/discord/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */
  char preferred_locale[MAX_LOCALE_LEN];

  /* specs/discord/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t afk_channel_id;

  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */
  int afk_timeout;

  /* specs/discord/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t rules_channel_id;

  /* specs/discord/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t public_updates_channel_id;

  /* specs/discord/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */
  int mfa_level;

  /* specs/discord/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */
  int verification_level;

  /* specs/discord/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */
  int explicit_content_filter;

  /* specs/discord/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */
  int default_message_notifications;

  /* specs/discord/audit_log.json:131:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}'
  */
  char *vanity_url;

  /* specs/discord/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo add (null);

  /* specs/discord/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo remove (null);

  /* specs/discord/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */
  int prune_delete_days;

  /* specs/discord/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */
  bool widget_enabled;

  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t widget_channel_id;

  /* specs/discord/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t system_channel_id;

  /* specs/discord/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */
  int position;

  /* specs/discord/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */
  char *topic;

  /* specs/discord/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */
  int bitrate;

  /* specs/discord/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo permission_overwrites (null);

  /* specs/discord/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */
  bool nsfw;

  /* specs/discord/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t application_id;

  /* specs/discord/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */
  int rate_limit_per_user;

  /* specs/discord/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */
  char *permissions;

  /* specs/discord/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */
  int color;

  /* specs/discord/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */
  bool hoist;

  /* specs/discord/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */
  bool mentionable;

  /* specs/discord/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */
  char *allow;

  /* specs/discord/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */
  char *deny;

  /* specs/discord/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */
  char *code;

  /* specs/discord/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */
  char *channel_id;

  /* specs/discord/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */
  char *inviter_id;

  /* specs/discord/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */
  char *max_uses;

  /* specs/discord/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */
  char *uses;

  /* specs/discord/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */
  char *max_age;

  /* specs/discord/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */
  char *temporary;

  /* specs/discord/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */
  char *deaf;

  /* specs/discord/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */
  char *mute;

  /* specs/discord/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */
  char *nick;

  /* specs/discord/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */
  char *avatar_hash;

  /* specs/discord/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/discord/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */
  //@todo type integer or string;

  /* specs/discord/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */
  bool enable_emotions;

  /* specs/discord/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */
  int expire_behavior;

  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */
  int expire_grace_period;

  /* specs/discord/audit_log.json:171:18
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
/* This file is generated from specs/discord/channel.create-channel-invite.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#create-channel-invite */
/* This is defined at specs/discord/channel.create-channel-invite.json:8:22 */
struct discord_create_channel_invite_params {
  /* specs/discord/channel.create-channel-invite.json:11:20
     '{ "name": "max_age", "type":{ "base":"int" } }'
  */
  int max_age;

  /* specs/discord/channel.create-channel-invite.json:12:20
     '{ "name": "max_uses", "type":{ "base":"int" } }'
  */
  int max_uses;

  /* specs/discord/channel.create-channel-invite.json:13:20
     '{ "name": "temporary", "type":{ "base":"bool"}}'
  */
  bool temporary;

  /* specs/discord/channel.create-channel-invite.json:14:20
     '{ "name": "unique", "type":{ "base":"bool"}}'
  */
  bool unique;

  /* specs/discord/channel.create-channel-invite.json:15:20
     '{ "name": "target_type", "type":{ "base":"int" },
          "option":true, "inject_if_not":0}'
  */
  int target_type;

  /* specs/discord/channel.create-channel-invite.json:17:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, 
          "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t target_user_id;

  /* specs/discord/channel.create-channel-invite.json:19:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, 
          "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t target_application_id;

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
/* This file is generated from specs/discord/channel.edit-channel-permissions.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#edit-channel-permissions */
/* This is defined at specs/discord/channel.edit-channel-permissions.json:8:22 */
struct discord_edit_channel_permissions_params {
  /* specs/discord/channel.edit-channel-permissions.json:11:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"},
          "comment":"permission bit set"}'
  */
  enum discord_permissions_bitwise_flags allow; // permission bit set

  /* specs/discord/channel.edit-channel-permissions.json:13:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"},
          "comment":"permission bit set"}'
  */
  enum discord_permissions_bitwise_flags deny; // permission bit set

  /* specs/discord/channel.edit-channel-permissions.json:15:20
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
/* This file is generated from specs/discord/channel.follow-news-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#follow-news-channel */
/* This is defined at specs/discord/channel.follow-news-channel.json:8:22 */
struct discord_follow_news_channel_params {
  /* specs/discord/channel.follow-news-channel.json:11:20
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
/* This file is generated from specs/discord/channel.get-reactions.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#get-reactions */
/* This is defined at specs/discord/channel.get-reactions.json:8:22 */
struct discord_get_reactions_params {
  /* specs/discord/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
  u64_snowflake_t before;

  /* specs/discord/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
  u64_snowflake_t after;

  /* specs/discord/channel.get-reactions.json:13:20
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
/* This file is generated from specs/discord/channel.group-dm-add-recipient.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#group-dm-add-recipient */
/* This is defined at specs/discord/channel.group-dm-add-recipient.json:8:22 */
struct discord_group_dm_add_recipient_params {
  /* specs/discord/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
  char *access_token;

  /* specs/discord/channel.group-dm-add-recipient.json:12:20
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
/* This file is generated from specs/discord/channel.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#channel-object-channel-types
*/



/* Title: Channel Structure */
/* https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
/* This is defined at specs/discord/channel.json:25:22 */
struct discord_channel {
  /* specs/discord/channel.json:28:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.json:29:83
     '{"type":{"base":"int", "int_alias":"enum discord_channel_types"}, "name":"type"}'
  */
  enum discord_channel_types type;

  /* specs/discord/channel.json:30:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
         "option":true, "inject_if_not":0 }'
  */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:32:41
     '{"type":{"base":"int"}, "name":"position",
         "option":true, "inject_if_not":0 }'
  */
  int position;

  /* specs/discord/channel.json:34:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }'
  */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/channel.json:36:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":""}'
  */
  char name[MAX_NAME_LEN];

  /* specs/discord/channel.json:38:67
     '{"type":{"base":"char", "dec":"[MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":"" }'
  */
  char topic[MAX_TOPIC_LEN];

  /* specs/discord/channel.json:40:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}'
  */
  bool nsfw;

  /* specs/discord/channel.json:41:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t last_message_id;

  /* specs/discord/channel.json:43:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/discord/channel.json:44:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/discord/channel.json:45:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/discord/channel.json:47:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}'
  */
  struct discord_user **recipients;

  /* specs/discord/channel.json:49:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":""}'
  */
  char icon[MAX_SHA256_LEN];

  /* specs/discord/channel.json:51:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t owner_id;

  /* specs/discord/channel.json:53:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t application_id;

  /* specs/discord/channel.json:55:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.json:57:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}'
  */
  u64_unix_ms_t last_pin_timestamp;

  /* specs/discord/channel.json:59:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}'
  */
  struct discord_message **messages;

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
/* This file is generated from specs/discord/channel.message.json, Please don't edit it. */
/*

*/



/* https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure */
/* This is defined at specs/discord/channel.message.json:20:22 */
struct discord_message_sticker {
  /* specs/discord/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t pack_id;

  /* specs/discord/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/discord/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
  char *description;

  /* specs/discord/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */
  char *tags;

  /* specs/discord/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
  char asset[MAX_SHA256_LEN];

  /* specs/discord/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */
  char preview_asset[MAX_SHA256_LEN];

  /* specs/discord/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}'
  */
  enum discord_message_sticker_format_types type;

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
/* This is defined at specs/discord/channel.message.json:50:22 */
struct discord_message_reference {
  /* specs/discord/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t message_id;

  /* specs/discord/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.message.json:58:18
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
/* This is defined at specs/discord/channel.message.json:66:22 */
struct discord_message_application {
  /* specs/discord/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  char *cover_image;

  /* specs/discord/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
  char *description;

  /* specs/discord/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */
  char *icon;

  /* specs/discord/channel.message.json:73:18
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
/* This is defined at specs/discord/channel.message.json:92:22 */
struct discord_message_activity {
  /* specs/discord/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}'
  */
  enum discord_message_activity_types type;

  /* specs/discord/channel.message.json:95:18
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
/* This is defined at specs/discord/channel.message.json:128:22 */
struct discord_message {
  /* specs/discord/channel.message.json:130:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.message.json:131:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}'
  */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.message.json:132:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
          "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.message.json:134:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}'
  */
  struct discord_user *author;

  /* specs/discord/channel.message.json:135:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  struct discord_guild_member *member; // partial guild member object

  /* specs/discord/channel.message.json:137:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}'
  */
  char *content;

  /* specs/discord/channel.message.json:138:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}'
  */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.message.json:139:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp",
          "inject_if_not":0}'
  */
  u64_unix_ms_t edited_timestamp;

  /* specs/discord/channel.message.json:141:43
     '{"type":{"base":"bool"}, "name":"tts"}'
  */
  bool tts;

  /* specs/discord/channel.message.json:142:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}'
  */
  bool mention_everyone;

  /* specs/discord/channel.message.json:143:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
  struct discord_user **mentions; // array of user objects, with an additional partial member field

  /* specs/discord/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
  ja_u64 **mention_roles; // array of role object ids

  /* specs/discord/channel.message.json:146:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
  struct discord_channel_mention **mention_channels;

  /* specs/discord/channel.message.json:148:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}'
  */
  struct discord_channel_attachment **attachments;

  /* specs/discord/channel.message.json:149:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}'
  */
  struct discord_embed **embeds;

  /* specs/discord/channel.message.json:150:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
  struct discord_channel_reaction **reactions;

  /* specs/discord/channel.message.json:152:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string",
          "option":true }'
  */
  char *nonce; // integer or string

  /* specs/discord/channel.message.json:154:43
     '{"type":{"base":"bool"}, "name":"pinned"}'
  */
  bool pinned;

  /* specs/discord/channel.message.json:155:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id",
          "option":true }'
  */
  u64_snowflake_t webhook_id;

  /* specs/discord/channel.message.json:157:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}'
  */
  enum discord_message_types type;

  /* specs/discord/channel.message.json:158:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  struct discord_message_activity *activity;

  /* specs/discord/channel.message.json:160:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
  struct discord_message_application **application;

  /* specs/discord/channel.message.json:162:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  struct discord_message_reference *message_reference;

  /* specs/discord/channel.message.json:164:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
  enum discord_message_flags flags;

  /* specs/discord/channel.message.json:166:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
  struct discord_message_sticker **stickers; // array of sticker objects

  /* specs/discord/channel.message.json:168:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
  struct discord_message *referenced_message; // this will cause recursive allocation if allocating as the parent

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
/* This file is generated from specs/discord/channel.modify-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#modify-channel */
/* This is defined at specs/discord/channel.modify-channel.json:8:22 */
struct discord_modify_channel_params {
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  char *name;

  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  char *icon;

  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  int position;

  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  char *topic;

  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool nsfw;

  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  char *rtc_region;

  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int video_quality_mode;

  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */
  bool archived;

  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int auto_archive_duration;

  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool locked;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[16];
    void *record_defined[16];
    void *record_null[16];
  } __M; // metadata
};
/* This file is generated from specs/discord/channel.objects.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/

/* Title: Overwrite Structure */
/* This is defined at specs/discord/channel.objects.json:10:22 */
struct discord_channel_overwrite {
  /* specs/discord/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/discord/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  enum discord_permissions_bitwise_flags allow; // permission bit set

  /* specs/discord/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  enum discord_permissions_bitwise_flags deny; // permission bit set

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

/* Title: Reaction Structure */
/* https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure */
/* This is defined at specs/discord/channel.objects.json:25:22 */
struct discord_channel_reaction {
  /* specs/discord/channel.objects.json:28:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  int count;

  /* specs/discord/channel.objects.json:29:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  bool me;

  /* specs/discord/channel.objects.json:30:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}'
  */
  struct discord_emoji *emoji; // partial emoji object

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

/* Title: Thread Metadata Object */
/* https://discord.com/developers/docs/resources/channel#thread-metadata-object */
/* This is defined at specs/discord/channel.objects.json:37:22 */
struct discord_thread_metadata {
  /* specs/discord/channel.objects.json:40:20
     '{ "name": "archived", "type":{ "base":"bool" }}'
  */
  bool archived;

  /* specs/discord/channel.objects.json:41:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t archiver_id;

  /* specs/discord/channel.objects.json:42:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}'
  */
  int auto_archive_duration;

  /* specs/discord/channel.objects.json:43:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t archive_timestamp;

  /* specs/discord/channel.objects.json:44:20
     '{ "name": "locked", "type":{ "base":"bool" }}'
  */
  bool locked;

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

/* Title: Thread Member Object */
/* https://discord.com/developers/docs/resources/channel#thread-member-object */
/* This is defined at specs/discord/channel.objects.json:51:22 */
struct discord_thread_member {
  /* specs/discord/channel.objects.json:54:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.objects.json:55:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t user_id;

  /* specs/discord/channel.objects.json:56:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t join_timestamp;

  /* specs/discord/channel.objects.json:57:20
     '{ "name": "flags", "type":{ "base":"int" }}'
  */
  int flags;

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

/* Title: Followed Channel Structure */
/* https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure */
/* This is defined at specs/discord/channel.objects.json:64:22 */
struct discord_channel_followed_channel {
  /* specs/discord/channel.objects.json:67:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.objects.json:68:20
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
/* This is defined at specs/discord/channel.objects.json:74:22 */
struct discord_channel_attachment {
  /* specs/discord/channel.objects.json:77:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.objects.json:78:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  char filename[256];

  /* specs/discord/channel.objects.json:79:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  int size;

  /* specs/discord/channel.objects.json:80:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}'
  */
  char *url;

  /* specs/discord/channel.objects.json:81:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}'
  */
  char *proxy_url;

  /* specs/discord/channel.objects.json:82:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  int height;

  /* specs/discord/channel.objects.json:83:20
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
/* This is defined at specs/discord/channel.objects.json:90:22 */
struct discord_channel_mention {
  /* specs/discord/channel.objects.json:93:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/channel.objects.json:94:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.objects.json:95:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}'
  */
  enum discord_channel_types type;

  /* specs/discord/channel.objects.json:96:20
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
/* This is defined at specs/discord/channel.objects.json:103:22 */
struct discord_channel_allowed_mentions {
  /* specs/discord/channel.objects.json:106:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  ja_str **parse;

  /* specs/discord/channel.objects.json:107:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **roles; // list of snowflakes

  /* specs/discord/channel.objects.json:108:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  ja_u64 **users; // list of snowflakes

  /* specs/discord/channel.objects.json:109:20
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
/* This is defined at specs/discord/channel.objects.json:115:22 */
struct discord_embed {
  /* specs/discord/channel.objects.json:118:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  char title[EMBED_TITLE_LEN];

  /* specs/discord/channel.objects.json:120:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  char type[32];

  /* specs/discord/channel.objects.json:122:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  char description[EMBED_DESCRIPTION_LEN];

  /* specs/discord/channel.objects.json:124:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */
  char *url;

  /* specs/discord/channel.objects.json:126:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.objects.json:128:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  int color;

  /* specs/discord/channel.objects.json:129:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  struct discord_embed_footer *footer;

  /* specs/discord/channel.objects.json:131:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_image *image;

  /* specs/discord/channel.objects.json:132:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_thumbnail *thumbnail;

  /* specs/discord/channel.objects.json:133:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_video *video;

  /* specs/discord/channel.objects.json:134:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_provider *provider;

  /* specs/discord/channel.objects.json:135:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}'
  */
  struct discord_embed_author *author;

  /* specs/discord/channel.objects.json:136:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  struct discord_embed_field **fields;

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
/* This is defined at specs/discord/channel.objects.json:144:22 */
struct discord_embed_thumbnail {
  /* specs/discord/channel.objects.json:146:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *url;

  /* specs/discord/channel.objects.json:147:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *proxy_url;

  /* specs/discord/channel.objects.json:148:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/discord/channel.objects.json:149:20
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

/* Title: Embed Video Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure */
/* This is defined at specs/discord/channel.objects.json:156:22 */
struct discord_embed_video {
  /* specs/discord/channel.objects.json:158:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *url;

  /* specs/discord/channel.objects.json:159:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *proxy_url;

  /* specs/discord/channel.objects.json:160:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/discord/channel.objects.json:161:20
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

/* Title: Embed Image Structure */
/* https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure */
/* This is defined at specs/discord/channel.objects.json:168:22 */
struct discord_embed_image {
  /* specs/discord/channel.objects.json:170:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *url;

  /* specs/discord/channel.objects.json:171:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *proxy_url;

  /* specs/discord/channel.objects.json:172:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int height;

  /* specs/discord/channel.objects.json:173:20
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
/* This is defined at specs/discord/channel.objects.json:180:22 */
struct discord_embed_provider {
  /* specs/discord/channel.objects.json:182:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/discord/channel.objects.json:183:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":""}'
  */
  char *url;

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
/* This is defined at specs/discord/channel.objects.json:190:22 */
struct discord_embed_author {
  /* specs/discord/channel.objects.json:192:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_AUTHOR_NAME_LEN];

  /* specs/discord/channel.objects.json:193:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *url;

  /* specs/discord/channel.objects.json:194:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *icon_url;

  /* specs/discord/channel.objects.json:195:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":""}'
  */
  char *proxy_icon_url;

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
/* This is defined at specs/discord/channel.objects.json:202:22 */
struct discord_embed_footer {
  /* specs/discord/channel.objects.json:204:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  char text[EMBED_FOOTER_TEXT_LEN];

  /* specs/discord/channel.objects.json:205:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":""}'
  */
  char *icon_url;

  /* specs/discord/channel.objects.json:207:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":""}'
  */
  char *proxy_icon_url;

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
/* This is defined at specs/discord/channel.objects.json:215:22 */
struct discord_embed_field {
  /* specs/discord/channel.objects.json:217:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  char name[EMBED_FIELD_NAME_LEN];

  /* specs/discord/channel.objects.json:218:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  char value[EMBED_FIELD_VALUE_LEN];

  /* specs/discord/channel.objects.json:219:20
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
/* This file is generated from specs/discord/channel.start-thread-with-message.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#start-thread-with-message-json-params */
/* This is defined at specs/discord/channel.start-thread-with-message.json:8:22 */
struct discord_start_thread_with_message_params {
  /* specs/discord/channel.start-thread-with-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
  char *name;

  /* specs/discord/channel.start-thread-with-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  int auto_archive_duration;

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
/* This file is generated from specs/discord/channel.start-thread-without-message.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#start-thread-without-message-json-params */
/* This is defined at specs/discord/channel.start-thread-without-message.json:8:22 */
struct discord_start_thread_without_message_params {
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
  char *name;

  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  int auto_archive_duration;

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
/* This file is generated from specs/discord/channel.thread-response-body.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#list-active-threads-response-body */
/* This is defined at specs/discord/channel.thread-response-body.json:8:22 */
struct discord_thread_response_body {
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
  struct discord_channel **threads;

  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
  struct discord_thread_member **members;

  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */
  bool has_more;

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
/* This file is generated from specs/discord/emoji.create-guild-emoji.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/emoji#create-guild-emoji */
/* This is defined at specs/discord/emoji.create-guild-emoji.json:8:22 */
struct discord_create_guild_emoji_params {
  /* specs/discord/emoji.create-guild-emoji.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/discord/emoji.create-guild-emoji.json:12:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}'
  */
  char *image; // Base64 Encoded Image Data

  /* specs/discord/emoji.create-guild-emoji.json:13:20
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
/* This file is generated from specs/discord/emoji.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
*/

/* Title: Emoji Structure */
/* This is defined at specs/discord/emoji.json:8:22 */
struct discord_emoji {
  /* specs/discord/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/discord/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  char name[MAX_NAME_LEN];

  /* specs/discord/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role", "dec":"ntl"}, "option":true,
          "todo":true }'
  */
  //@todo roles (null);

  /* specs/discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }'
  */
  struct discord_user *user;

  /* specs/discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
  bool require_colons;

  /* specs/discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
  bool managed;

  /* specs/discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
  bool animated;

  /* specs/discord/emoji.json:19:20
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
/* This file is generated from specs/discord/emoji.modify-guild-emoji.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/emoji#modify-guild-emoji */
/* This is defined at specs/discord/emoji.modify-guild-emoji.json:8:22 */
struct discord_modify_guild_emoji_params {
  /* specs/discord/emoji.modify-guild-emoji.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/discord/emoji.modify-guild-emoji.json:12:20
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
/* This file is generated from specs/discord/gateway.json, Please don't edit it. */
/*
(null)
*/









/* Title: Identify Structure */
/* https://discord.com/developers/docs/topics/gateway#identify-identify-structure */
/* This is defined at specs/discord/gateway.json:115:22 */
struct discord_gateway_identify {
  /* specs/discord/gateway.json:118:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  char *token;

  /* specs/discord/gateway.json:119:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
  struct discord_gateway_identify_connection *properties;

  /* specs/discord/gateway.json:120:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  bool compress;

  /* specs/discord/gateway.json:121:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
  int large_threshold;

  /* specs/discord/gateway.json:122:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  bool guild_subscriptions;

  /* specs/discord/gateway.json:123:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  //@todo shard (null);

  /* specs/discord/gateway.json:124:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}'
  */
  struct discord_gateway_status_update *presence;

  /* specs/discord/gateway.json:125:19
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
/* This is defined at specs/discord/gateway.json:131:22 */
struct discord_gateway_status_update {
  /* specs/discord/gateway.json:134:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  u64_unix_ms_t since;

  /* specs/discord/gateway.json:136:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
  struct discord_gateway_activity **activities;

  /* specs/discord/gateway.json:138:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  char status[16];

  /* specs/discord/gateway.json:139:19
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
/* This is defined at specs/discord/gateway.json:146:22 */
struct discord_gateway_identify_connection {
  /* specs/discord/gateway.json:149:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
  char *$os;

  /* specs/discord/gateway.json:150:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
  char *$browser;

  /* specs/discord/gateway.json:151:19
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
/* This is defined at specs/discord/gateway.json:157:22 */
struct discord_gateway_activity {
  /* specs/discord/gateway.json:160:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  char name[512];

  /* specs/discord/gateway.json:161:19
     '{ "name":"type","type":{"base":"int"}}'
  */
  int type;

  /* specs/discord/gateway.json:162:19
     '{ "name":"url","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}'
  */
  char *url;

  /* specs/discord/gateway.json:164:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  u64_unix_ms_t created_at;

  /* specs/discord/gateway.json:166:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
  u64_snowflake_t application_id;

  /* specs/discord/gateway.json:168:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  char *details;

  /* specs/discord/gateway.json:170:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  char *state;

  /* specs/discord/gateway.json:172:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
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


/* This file is generated from specs/discord/guild.ban.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/

/* This is defined at specs/discord/guild.ban.json:7:22 */
struct discord_guild_ban {
  /* specs/discord/guild.ban.json:10:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  char reason[MAX_REASON_LEN];

  /* specs/discord/guild.ban.json:11:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
  struct discord_user *user; // partial user object

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
/* This file is generated from specs/discord/guild.create-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild-channel */
/* This is defined at specs/discord/guild.create-channel.json:8:22 */
struct discord_create_guild_channel_params {
  /* specs/discord/guild.create-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/discord/guild.create-channel.json:12:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/discord/guild.create-channel.json:13:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}'
  */
  char *topic;

  /* specs/discord/guild.create-channel.json:14:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/discord/guild.create-channel.json:15:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/discord/guild.create-channel.json:16:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/discord/guild.create-channel.json:17:20
     '{ "name": "position", "type":{ "base":"int" } }'
  */
  int position;

  /* specs/discord/guild.create-channel.json:18:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/guild.create-channel.json:19:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  /* specs/discord/guild.create-channel.json:20:20
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
/* This file is generated from specs/discord/guild.create-guild.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild */
/* This is defined at specs/discord/guild.create-guild.json:8:22 */
struct discord_create_guild_params {
  /* specs/discord/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
  char name[200+1]; // name of the guild (2-100) characters

  /* specs/discord/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
  char *region; // voice region id

  /* specs/discord/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
  char *icon; // base64 128x1128 image for the guild icon

  /* specs/discord/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
  int verification_level; // verification level

  /* specs/discord/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
  int default_message_notifications; // default message notification level

  /* specs/discord/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
  int explicit_content_filter; // explicit content filter level

  /* specs/discord/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */
  //@todo roles new guild roles;

  /* specs/discord/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
  struct discord_channel **channels; // array of partial channel objects

  /* specs/discord/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
  u64_snowflake_t afk_channel_id; // id for afk channel

  /* specs/discord/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
  int afk_timeout; // afk timeout in seconds

  /* specs/discord/guild.create-guild.json:31:20
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
/* This file is generated from specs/discord/guild.enum.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/















/* Title: Unavailable Guild Object */
/* https://discord.com/developers/docs/resources/guild#unavailable-guild-object */
/* This is defined at specs/discord/guild.enum.json:91:23 */
struct discord_guild_unavailable {
  /* specs/discord/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/discord/guild.enum.json:94:18
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
/* This is defined at specs/discord/guild.enum.json:100:23 */
struct discord_guild_preview {
  /* specs/discord/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/discord/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  char name[MAX_NAME_LEN];

  /* specs/discord/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  char *icon;

  /* specs/discord/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  char *splash;

  /* specs/discord/guild.enum.json:106:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  char *discovery;

  /* specs/discord/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
  struct discord_emoji **emojis;

  /* specs/discord/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  //@todo features (null);

  /* specs/discord/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
  int approximate_member_count;

  /* specs/discord/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
  int approximate_presence_count;

  /* specs/discord/guild.enum.json:111:18
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
/* This is defined at specs/discord/guild.enum.json:117:23 */
struct discord_guild_widget {
  /* specs/discord/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
  bool enabled;

  /* specs/discord/guild.enum.json:120:18
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
/* This file is generated from specs/discord/guild.integration.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/



/* Title: Integration Account Structure */
/* https://discord.com/developers/docs/resources/guild#integration-account-object-integration-account-structure */
/* This is defined at specs/discord/guild.integration.json:21:22 */
struct discord_guild_integration_account {
  /* specs/discord/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/guild.integration.json:24:19
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
/* This is defined at specs/discord/guild.integration.json:31:22 */
struct discord_guild_integration_application {
  /* specs/discord/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/discord/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  char icon[MAX_SHA256_LEN];

  /* specs/discord/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
  char *description;

  /* specs/discord/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
  char *summary;

  /* specs/discord/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  struct discord_user *bot;

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
/* This is defined at specs/discord/guild.integration.json:44:22 */
struct discord_guild_integration {
  /* specs/discord/guild.integration.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/guild.integration.json:48:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/discord/guild.integration.json:49:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  char *type;

  /* specs/discord/guild.integration.json:50:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
  bool enabled;

  /* specs/discord/guild.integration.json:51:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
  bool syncing;

  /* specs/discord/guild.integration.json:52:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t role_id;

  /* specs/discord/guild.integration.json:53:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
  bool enable_emotions;

  /* specs/discord/guild.integration.json:54:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}'
  */
  enum discord_guild_integration_expire_behaviors expire_behavior;

  /* specs/discord/guild.integration.json:55:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
  int expire_grace_period;

  /* specs/discord/guild.integration.json:56:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}'
  */
  struct discord_user *user;

  /* specs/discord/guild.integration.json:57:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}'
  */
  struct discord_guild_integration_account *account;

  /* specs/discord/guild.integration.json:58:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  u64_unix_ms_t synced_at;

  /* specs/discord/guild.integration.json:59:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
  int subscriber_count;

  /* specs/discord/guild.integration.json:60:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  bool revoked;

  /* specs/discord/guild.integration.json:61:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}'
  */
  struct discord_guild_integration_application *application;

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
/* This file is generated from specs/discord/guild.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
*/

/* Title: Guild Structure */
/* This is defined at specs/discord/guild.json:8:22 */
struct discord_guild {
  /* specs/discord/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/discord/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
  char name[MAX_NAME_LEN];

  /* specs/discord/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
  char *icon;

  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
  char *icon_hash;

  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
  char *splash;

  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
  char *discovery_splash;

  /* specs/discord/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
  bool owner;

  /* specs/discord/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
  u64_snowflake_t owner_id;

  /* specs/discord/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
  int permissions;

  /* specs/discord/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
  char region[MAX_REGION_LEN];

  /* specs/discord/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
  u64_snowflake_t afk_channel_id;

  /* specs/discord/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
  int afk_timeout;

  /* specs/discord/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
  bool widget_enabled;

  /* specs/discord/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
  u64_snowflake_t widget_channel_id;

  /* specs/discord/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */
  enum discord_guild_verification_level verification_level;

  /* specs/discord/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */
  enum discord_guild_default_message_notification_level default_message_notifications;

  /* specs/discord/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */
  enum discord_guild_explicit_content_filter_level explicit_content_filter;

  /* specs/discord/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  //@todo roles array of role objects;

  /* specs/discord/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */
  struct discord_emoji **emojis;

  /* specs/discord/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  //@todo features array of guild feature strings;

  /* specs/discord/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */
  enum discord_guild_mfa_level mfa_level;

  /* specs/discord/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
  u64_snowflake_t application_id;

  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
  u64_snowflake_t system_channel_id;

  /* specs/discord/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */
  enum discord_guild_system_channel_flags system_channel_flags;

  /* specs/discord/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
  u64_snowflake_t rules_channel_id;

  /* specs/discord/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
  u64_unix_ms_t joined_at;

  /* specs/discord/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
  bool large;

  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
  bool unavailable;

  /* specs/discord/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
  int member_count;

  /* specs/discord/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  //@todo voice_states array of partial voice state objects;

  /* specs/discord/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */
  struct discord_guild_member **members;

  /* specs/discord/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
  struct discord_channel **channels; // array of channel objects

  /* specs/discord/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  //@todo presences array of partial presence update objects;

  /* specs/discord/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
  int max_presences;

  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
  int max_members;

  /* specs/discord/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */
  char *vanity_url;

  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
  char *description;

  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
  char *banner;

  /* specs/discord/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */
  enum discord_guild_premium_tier premium_tier;

  /* specs/discord/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
  int premium_subscription_count;

  /* specs/discord/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
  char preferred_locale[MAX_LOCALE_LEN];

  /* specs/discord/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
  u64_snowflake_t public_updates_channel_id;

  /* specs/discord/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
  int max_video_channel_users;

  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
  int approximate_member_count;

  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
  int approximate_presence_count;

  /* specs/discord/guild.json:64:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
  struct discord_guild_welcome_screen *welcome_screen;

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
/* This file is generated from specs/discord/guild.member.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-member-object
*/

/* This is defined at specs/discord/guild.member.json:7:22 */
struct discord_guild_member {
  /* specs/discord/guild.member.json:10:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  struct discord_user *user;

  /* specs/discord/guild.member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}, "option":true}'
  */
  char nick[MAX_NAME_LEN];

  /* specs/discord/guild.member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}'
  */
  ja_u64 **roles; // array of role object ids

  /* specs/discord/guild.member.json:13:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t joined_at;

  /* specs/discord/guild.member.json:14:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t premium_since;

  /* specs/discord/guild.member.json:15:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  bool deaf;

  /* specs/discord/guild.member.json:16:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  bool mute;

  /* specs/discord/guild.member.json:17:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}'
  */
  bool pending;

  /* specs/discord/guild.member.json:18:20
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
/* This file is generated from specs/discord/guild.membership_screening.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/



/* https://discord.com/developers/docs/resources/guild#membership-screening-object-membership-screening-field-structure */
/* This is defined at specs/discord/guild.membership_screening.json:17:22 */
struct discord_guild_membership_screening_field {
  /* specs/discord/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */
  enum discord_guild_membership_screening_field_type field_type;

  /* specs/discord/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
  char *label;

  /* specs/discord/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  //@todo values (null);

  /* specs/discord/guild.membership_screening.json:23:20
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

/* This is defined at specs/discord/guild.membership_screening.json:27:22 */
struct discord_guild_membership_screening {
  /* specs/discord/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  uint64_t version;

  /* specs/discord/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */
  struct discord_guild_membership_screening_field **fields;

  /* specs/discord/guild.membership_screening.json:32:20
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
/* This file is generated from specs/discord/guild.modify-guild-member.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#modify-guild-member */
/* This is defined at specs/discord/guild.modify-guild-member.json:8:22 */
struct discord_modify_guild_member_params {
  /* specs/discord/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
  char *nick;

  /* specs/discord/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
  ja_u64 **roles;

  /* specs/discord/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool mute;

  /* specs/discord/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool deaf;

  /* specs/discord/guild.modify-guild-member.json:15:20
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
/* This file is generated from specs/discord/guild.role.create.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild-role */
/* This is defined at specs/discord/guild.role.create.json:8:22 */
struct discord_create_guild_role_params {
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */
  enum discord_permissions_bitwise_flags permissions;

  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int color;

  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool hoist;

  /* specs/discord/guild.role.create.json:16:20
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
/* This file is generated from specs/discord/guild.role.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/

/* Title: Role Tags Structure */
/* This is defined at specs/discord/guild.role.json:9:22 */
struct discord_guild_role_tags {
  /* specs/discord/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t bot_id;

  /* specs/discord/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t integration_id;

  /* specs/discord/guild.role.json:14:20
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
/* This is defined at specs/discord/guild.role.json:19:22 */
struct discord_guild_role {
  /* specs/discord/guild.role.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/guild.role.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
  char name[MAX_NAME_LEN];

  /* specs/discord/guild.role.json:24:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
  int color;

  /* specs/discord/guild.role.json:25:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
  bool hoist;

  /* specs/discord/guild.role.json:26:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  int position;

  /* specs/discord/guild.role.json:27:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
  char *permissions;

  /* specs/discord/guild.role.json:28:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
  bool managed;

  /* specs/discord/guild.role.json:29:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
  bool mentionable;

  /* specs/discord/guild.role.json:30:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags", "dec":"*"}}'
  */
  struct discord_guild_role_tags *tags;

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
/* This file is generated from specs/discord/guild.welcome_screen.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#welcome-screen-object
*/

/* Title: Welcome Screen Channel Structure */
/* https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure */
/* This is defined at specs/discord/guild.welcome_screen.json:11:22 */
struct discord_guild_welcome_screen_channel {
  /* specs/discord/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/discord/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  char *description;

  /* specs/discord/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t emoji_id;

  /* specs/discord/guild.welcome_screen.json:17:20
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
/* This is defined at specs/discord/guild.welcome_screen.json:23:22 */
struct discord_guild_welcome_screen {
  /* specs/discord/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *description; // @todo fixed size limit

  /* specs/discord/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }'
  */
  struct discord_guild_welcome_screen_channel **welcome_channels;

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
/* This file is generated from specs/discord/invite.get-invite.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/invite#get-invite
*/

/* https://discord.com/developers/docs/resources/invite#get-invite-query-string-params */
/* This is defined at specs/discord/invite.get-invite.json:8:22 */
struct discord_get_invite_params {
  /* specs/discord/invite.get-invite.json:11:20
     '{ "name": "with_counts", "type":{ "base":"bool" },
          "comment":"whether the invite should contain approximate member counts"}'
  */
  bool with_counts; // whether the invite should contain approximate member counts

  /* specs/discord/invite.get-invite.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" },
          "comment":"whether the invite should contain the expiration date"}'
  */
  bool with_expiration; // whether the invite should contain the expiration date

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
/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/invite#invite-object
*/



/* Title: Invite Structure */
/* https://discord.com/developers/docs/resources/invite#invite-object-invite-structure */
/* This is defined at specs/discord/invite.json:19:22 */
struct discord_invite {
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *code; // @todo fixed size limit

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}'
  */
  struct discord_guild *guild; // partial guild object

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}'
  */
  struct discord_channel *channel; // partial channel object

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}'
  */
  struct discord_user *inviter;

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}'
  */
  struct discord_user *target_user; // partial user object

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}'
  */
  enum discord_invite_target_user_types target_user_type;

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
  int approximate_presence_count;

  /* specs/discord/invite.json:29:20
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
/* This is defined at specs/discord/invite.json:36:22 */
struct discord_invite_metadata {
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
  int user;

  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
  int max_uses;

  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
  int max_age;

  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
  int temporary;

  /* specs/discord/invite.json:43:20
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
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions
*/


/* This file is generated from specs/discord/template.create-guild-from-template.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/template#create-guild-from-template */
/* This is defined at specs/discord/template.create-guild-from-template.json:8:22 */
struct discord_create_guild_from_template_params {
  /* specs/discord/template.create-guild-from-template.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}'
  */
  char *name; // name of the guild

  /* specs/discord/template.create-guild-from-template.json:12:20
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
/* This file is generated from specs/discord/template.create-guild-template.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/template#create-guild-template */
/* This is defined at specs/discord/template.create-guild-template.json:8:22 */
struct discord_create_guild_template_params {
  /* specs/discord/template.create-guild-template.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[100+1]"}, "comment":"name of the guild"}'
  */
  char name[100+1]; // name of the guild

  /* specs/discord/template.create-guild-template.json:12:20
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
/* This file is generated from specs/discord/template.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/template#template-object-template-structure
*/

/* Title: Template Structure */
/* This is defined at specs/discord/template.json:8:22 */
struct discord_template {
  /* specs/discord/template.json:11:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *code; // @todo find fixed size limit

  /* specs/discord/template.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *name; // @todo find fixed size limit

  /* specs/discord/template.json:13:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
  char *description; // @todo find fixed size limit

  /* specs/discord/template.json:14:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
  int usage_count;

  /* specs/discord/template.json:15:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t creator_id;

  /* specs/discord/template.json:16:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
  struct discord_user *creator;

  /* specs/discord/template.json:17:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t created_at;

  /* specs/discord/template.json:18:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t updated_at;

  /* specs/discord/template.json:19:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t source_guild_id;

  /* specs/discord/template.json:20:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}'
  */
  struct discord_guild *serialized_source_guild;

  /* specs/discord/template.json:21:20
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
/* This file is generated from specs/discord/template.modify-guild-template.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/template#modify-guild-template */
/* This is defined at specs/discord/template.modify-guild-template.json:8:22 */
struct discord_modify_guild_template_params {
  /* specs/discord/template.modify-guild-template.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[100+1]"}, "comment":"name of the guild"}'
  */
  char name[100+1]; // name of the guild

  /* specs/discord/template.modify-guild-template.json:12:20
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
/* This file is generated from specs/discord/user.create-group-dm.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/user#create-group-dm */
/* This is defined at specs/discord/user.create-group-dm.json:8:22 */
struct discord_create_group_dm_params {
  /* specs/discord/user.create-group-dm.json:11:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}'
  */
  ja_str **access_tokens; // access tokens of users that have granted your app the gdm.join scope

  /* specs/discord/user.create-group-dm.json:13:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"ia dictionary of user ids to their respective nicknames"}'
  */
  ja_u64 **nicks; // ia dictionary of user ids to their respective nicknames

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
/* This file is generated from specs/discord/user.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/user#user-object
*/





/* Title: User Structure */
/* This is defined at specs/discord/user.json:42:18 */
struct discord_user {
  /* specs/discord/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
  u64_snowflake_t id;

  /* specs/discord/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
  char username[MAX_USERNAME_LEN];

  /* specs/discord/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
  char discriminator[MAX_DISCRIMINATOR_LEN];

  /* specs/discord/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  char avatar[MAX_SHA256_LEN];

  /* specs/discord/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
  bool bot;

  /* specs/discord/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
  bool System;

  /* specs/discord/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
  bool mfa_enabled;

  /* specs/discord/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
  char locale[MAX_LOCALE_LEN];

  /* specs/discord/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  bool verified;

  /* specs/discord/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
  char email[MAX_EMAIL_LEN];

  /* specs/discord/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
  enum discord_user_flags flags;

  /* specs/discord/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */
  enum discord_user_premium_types premium_type;

  /* specs/discord/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
  enum discord_user_flags public_flags;

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
/* This is defined at specs/discord/user.json:74:18 */
struct discord_connection {
  /* specs/discord/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *id; // @todo fixed size limit

  /* specs/discord/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/discord/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  char *type;

  /* specs/discord/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  bool revoked;

  /* specs/discord/user.json:81:16
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}}'
  */
  struct discord_guild_integration **integrations;

  /* specs/discord/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  bool verified;

  /* specs/discord/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
  bool friend_sync;

  /* specs/discord/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
  bool show_activity;

  /* specs/discord/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */
  enum discord_user_connection_visibility_types visibility;

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
/* This file is generated from specs/discord/user.modify-curent-user.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/user#modify-current-user */
/* This is defined at specs/discord/user.modify-curent-user.json:8:22 */
struct discord_modify_current_user_params {
  /* specs/discord/user.modify-curent-user.json:11:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}'
  */
  char *username;

  /* specs/discord/user.modify-curent-user.json:12:20
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
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */
/*
(null)
*/






/* This file is generated from specs/discord/voice.json, Please don't edit it. */
/*
(null)
*/

/* Title: Voice State Object */
/* https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure */
/* This is defined at specs/discord/voice.json:8:22 */
struct discord_voice_state {
  /* specs/discord/voice.json:11:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/discord/voice.json:12:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t channel_id;

  /* specs/discord/voice.json:13:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t user_id;

  /* specs/discord/voice.json:14:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}'
  */
  struct discord_guild_member *member;

  /* specs/discord/voice.json:15:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
  char *session_id;

  /* specs/discord/voice.json:16:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  bool deaf;

  /* specs/discord/voice.json:17:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  bool mute;

  /* specs/discord/voice.json:18:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
  bool self_deaf;

  /* specs/discord/voice.json:19:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
  bool self_mute;

  /* specs/discord/voice.json:20:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
  bool self_stream;

  /* specs/discord/voice.json:21:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
  bool self_video;

  /* specs/discord/voice.json:22:20
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
/* This is defined at specs/discord/voice.json:28:22 */
struct discord_voice_region {
  /* specs/discord/voice.json:31:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  char *id; // @todo fixed size limit

  /* specs/discord/voice.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  char *name; // @todo fixed size limit

  /* specs/discord/voice.json:33:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
  bool vip;

  /* specs/discord/voice.json:34:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
  bool optimal;

  /* specs/discord/voice.json:35:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
  bool deprecated;

  /* specs/discord/voice.json:36:20
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
/* This file is generated from specs/discord/webhook.create-webhook.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#create-webhook */
/* This is defined at specs/discord/webhook.create-webhook.json:8:22 */
struct discord_create_webhook_params {
  /* specs/discord/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
  char name[80+1]; // name of the webhook(1-80) chars

  /* specs/discord/webhook.create-webhook.json:13:20
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
/* This file is generated from specs/discord/webhook.edit-webhook-message.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#edit-webhook-message */
/* This is defined at specs/discord/webhook.edit-webhook-message.json:8:22 */
struct discord_edit_webhook_message_params {
  /* specs/discord/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
  char content[2000+1]; // name of the webhook(1-2000) chars

  /* specs/discord/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
  struct discord_embed **embeds; // array of up to 10 embeds objects

  /* specs/discord/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
  struct discord_channel_allowed_mentions *allowed_mentions; // allowed mentions for the message

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
/* This file is generated from specs/discord/webhook.execute-webhook.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#execute-webhook */
/* This is defined at specs/discord/webhook.execute-webhook.json:8:22 */
struct discord_execute_webhook_params {
  /* specs/discord/webhook.execute-webhook.json:12:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"name of the webhook(1-80) chars",
          "required":"one of content, file, embeds"
        }'
  */
  bool wait; // name of the webhook(1-80) chars

  /* specs/discord/webhook.execute-webhook.json:16:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"the message contents (up to 2000 characters",
          "required":false
        }'
  */
  char content[2000+1]; // the message contents (up to 2000 characters

  /* specs/discord/webhook.execute-webhook.json:20:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }'
  */
  char *username; // override the default username of the webhook

  /* specs/discord/webhook.execute-webhook.json:24:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }'
  */
  char *avatar_url; // override the default avatar of the webhook

  /* specs/discord/webhook.execute-webhook.json:26:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }'
  */
  bool tts; // true if this is a TTS message

  /* specs/discord/webhook.execute-webhook.json:30:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }'
  */
  char *file; // the contents of the file being sent

  /* specs/discord/webhook.execute-webhook.json:34:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }'
  */
  struct discord_embed *embeds; // embedded rich content

  /* specs/discord/webhook.execute-webhook.json:38:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }'
  */
  char *payload_json; // See message create

  /* specs/discord/webhook.execute-webhook.json:42:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }'
  */
  struct discord_channel_allowed_mentions *allowed_mentions; // allowed mentions for the message

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
/* This file is generated from specs/discord/webhook.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
*/



/* Title: Webhook Structure */
/* This is defined at specs/discord/webhook.json:18:22 */
struct discord_webhook {
  /* specs/discord/webhook.json:21:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/discord/webhook.json:22:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}'
  */
  enum discord_webhook_types type;

  /* specs/discord/webhook.json:23:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/discord/webhook.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/discord/webhook.json:25:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
  struct discord_user *user;

  /* specs/discord/webhook.json:26:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
  char name[WEBHOOK_NAME_LEN];

  /* specs/discord/webhook.json:27:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *avatar; // @todo fixed size limit

  /* specs/discord/webhook.json:28:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *token; // @todo fixed size limit

  /* specs/discord/webhook.json:29:20
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
/* This file is generated from specs/discord/webhook.modify-webhook.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/webhook#modify-webhook */
/* This is defined at specs/discord/webhook.modify-webhook.json:8:22 */
struct discord_modify_webhook_params {
  /* specs/discord/webhook.modify-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
  char name[80+1]; // name of the webhook(1-80) chars

  /* specs/discord/webhook.modify-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
  char *avatar; // base64 image for the default webhook avatar

  /* specs/discord/webhook.modify-webhook.json:16:20
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
