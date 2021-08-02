/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/audit-log
 */


// defined at specs/discord/audit_log.endpoints-params.json:8:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#get-guild-audit-log

 * - Initializer:
 *   - <tt>discord_get_guild_audit_log_params_init(struct discord_get_guild_audit_log_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_get_guild_audit_log_params_cleanup(struct discord_get_guild_audit_log_params*)</tt>
 *   - <tt>discord_get_guild_audit_log_params_list_free(struct discord_get_guild_audit_log_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_get_guild_audit_log_params_from_json(char *rbuf, size_t len, struct discord_get_guild_audit_log_params**)</tt>
 *   - <tt>discord_get_guild_audit_log_params_list_from_json(char *rbuf, size_t len, struct discord_get_guild_audit_log_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_get_guild_audit_log_params_to_json(char *wbuf, size_t len, struct discord_get_guild_audit_log_params*)</tt>
 *   - <tt>discord_get_guild_audit_log_params_list_to_json(char *wbuf, size_t len, struct discord_get_guild_audit_log_params**)</tt>
 */
struct discord_get_guild_audit_log_params {
  /* specs/discord/audit_log.endpoints-params.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  u64_snowflake_t user_id;

  /* specs/discord/audit_log.endpoints-params.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }' */
  enum discord_audit_log_events action_type;

  /* specs/discord/audit_log.endpoints-params.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  u64_snowflake_t before;

  /* specs/discord/audit_log.endpoints-params.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int limit;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/audit-log
 */


// Audit Log Structure
// defined at specs/discord/audit_log.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure

 * - Initializer:
 *   - <tt>discord_audit_log_init(struct discord_audit_log*)</tt>
 * - Cleanup:
 *   - <tt>discord_audit_log_cleanup(struct discord_audit_log*)</tt>
 *   - <tt>discord_audit_log_list_free(struct discord_audit_log**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_audit_log_from_json(char *rbuf, size_t len, struct discord_audit_log**)</tt>
 *   - <tt>discord_audit_log_list_from_json(char *rbuf, size_t len, struct discord_audit_log***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_audit_log_to_json(char *wbuf, size_t len, struct discord_audit_log*)</tt>
 *   - <tt>discord_audit_log_list_to_json(char *wbuf, size_t len, struct discord_audit_log**)</tt>
 */
struct discord_audit_log {
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" } }' */
  struct discord_webhook **webhooks;

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}}' */
  struct discord_user **users;

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}}' */
  struct discord_audit_log_entry **audit_log_entries;

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}' */
  struct discord_guild_integration **integrations;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};



// Audit Log Entry Structure
// defined at specs/discord/audit_log.json:65:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-entry-structure

 * - Initializer:
 *   - <tt>discord_audit_log_entry_init(struct discord_audit_log_entry*)</tt>
 * - Cleanup:
 *   - <tt>discord_audit_log_entry_cleanup(struct discord_audit_log_entry*)</tt>
 *   - <tt>discord_audit_log_entry_list_free(struct discord_audit_log_entry**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_audit_log_entry_from_json(char *rbuf, size_t len, struct discord_audit_log_entry**)</tt>
 *   - <tt>discord_audit_log_entry_list_from_json(char *rbuf, size_t len, struct discord_audit_log_entry***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_audit_log_entry_to_json(char *wbuf, size_t len, struct discord_audit_log_entry*)</tt>
 *   - <tt>discord_audit_log_entry_list_to_json(char *wbuf, size_t len, struct discord_audit_log_entry**)</tt>
 */
struct discord_audit_log_entry {
  /* specs/discord/audit_log.json:68:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}' */
  char *target_id;

  /* specs/discord/audit_log.json:69:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}}' */
  struct discord_audit_log_change **changes;

  /* specs/discord/audit_log.json:70:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t user_id;

  /* specs/discord/audit_log.json:71:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/audit_log.json:72:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}' */
  int action_type;

  /* specs/discord/audit_log.json:73:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"ntl"}}' */
  struct discord_audit_log_entry_optional_info **options;

  /* specs/discord/audit_log.json:74:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}}' */
  char reason[DISCORD_MAX_REASON_LEN];

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};

// Optional Audit Entry Info Structure
// defined at specs/discord/audit_log.json:81:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-optional-audit-entry-info

 * - Initializer:
 *   - <tt>discord_audit_log_entry_optional_info_init(struct discord_audit_log_entry_optional_info*)</tt>
 * - Cleanup:
 *   - <tt>discord_audit_log_entry_optional_info_cleanup(struct discord_audit_log_entry_optional_info*)</tt>
 *   - <tt>discord_audit_log_entry_optional_info_list_free(struct discord_audit_log_entry_optional_info**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_audit_log_entry_optional_info_from_json(char *rbuf, size_t len, struct discord_audit_log_entry_optional_info**)</tt>
 *   - <tt>discord_audit_log_entry_optional_info_list_from_json(char *rbuf, size_t len, struct discord_audit_log_entry_optional_info***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_audit_log_entry_optional_info_to_json(char *wbuf, size_t len, struct discord_audit_log_entry_optional_info*)</tt>
 *   - <tt>discord_audit_log_entry_optional_info_list_to_json(char *wbuf, size_t len, struct discord_audit_log_entry_optional_info**)</tt>
 */
struct discord_audit_log_entry_optional_info {
  /* specs/discord/audit_log.json:84:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
  char *delete_member_days; ///< @todo find fixed size limit

  /* specs/discord/audit_log.json:85:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
  char *members_removed; ///< @todo find fixed size limit

  /* specs/discord/audit_log.json:86:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
  u64_snowflake_t channel_id;

  /* specs/discord/audit_log.json:87:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
  u64_snowflake_t message_id;

  /* specs/discord/audit_log.json:88:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  char *count; ///< @todo find fixed size limit

  /* specs/discord/audit_log.json:89:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/audit_log.json:90:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  char *type; ///< @todo find fixed size limit

  /* specs/discord/audit_log.json:91:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  char *role; ///< @todo find fixed size limit

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
/// @endcond
};

// Audit Log Change Structure
// defined at specs/discord/audit_log.json:98:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-structure

 * - Initializer:
 *   - <tt>discord_audit_log_change_init(struct discord_audit_log_change*)</tt>
 * - Cleanup:
 *   - <tt>discord_audit_log_change_cleanup(struct discord_audit_log_change*)</tt>
 *   - <tt>discord_audit_log_change_list_free(struct discord_audit_log_change**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_audit_log_change_from_json(char *rbuf, size_t len, struct discord_audit_log_change**)</tt>
 *   - <tt>discord_audit_log_change_list_from_json(char *rbuf, size_t len, struct discord_audit_log_change***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_audit_log_change_to_json(char *wbuf, size_t len, struct discord_audit_log_change*)</tt>
 *   - <tt>discord_audit_log_change_list_to_json(char *wbuf, size_t len, struct discord_audit_log_change**)</tt>
 */
struct discord_audit_log_change {
  /* specs/discord/audit_log.json:101:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}' */
  char *new_value;

  /* specs/discord/audit_log.json:102:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}' */
  char *old_value;

  /* specs/discord/audit_log.json:103:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}' */
  char key[64];

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};

// Audit Log Change Key
// defined at specs/discord/audit_log.json:110:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-key

 * - Initializer:
 *   - <tt>discord_audit_log_change_key_init(struct discord_audit_log_change_key*)</tt>
 * - Cleanup:
 *   - <tt>discord_audit_log_change_key_cleanup(struct discord_audit_log_change_key*)</tt>
 *   - <tt>discord_audit_log_change_key_list_free(struct discord_audit_log_change_key**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_audit_log_change_key_from_json(char *rbuf, size_t len, struct discord_audit_log_change_key**)</tt>
 *   - <tt>discord_audit_log_change_key_list_from_json(char *rbuf, size_t len, struct discord_audit_log_change_key***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_audit_log_change_key_to_json(char *wbuf, size_t len, struct discord_audit_log_change_key*)</tt>
 *   - <tt>discord_audit_log_change_key_list_to_json(char *wbuf, size_t len, struct discord_audit_log_change_key**)</tt>
 */
struct discord_audit_log_change_key {
  /* specs/discord/audit_log.json:113:18
     '{"name":"name", "type": {"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
  char name[DISCORD_MAX_NAME_LEN];

  /* specs/discord/audit_log.json:114:18
     '{"name":"description", "type": {"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
  char description[DISCORD_MAX_DESCRIPTION_LEN];

  /* specs/discord/audit_log.json:115:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }' */
  char icon_hash[MAX_SHA256_LEN]; ///< icon changed

  /* specs/discord/audit_log.json:117:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}' */
  char splash_hash[MAX_SHA256_LEN]; ///< invite splash page artwork changed

  /* specs/discord/audit_log.json:119:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */
  char discovery_splash_hash[MAX_SHA256_LEN];

  /* specs/discord/audit_log.json:120:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t banner_hash;

  /* specs/discord/audit_log.json:121:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t owner_id;

  /* specs/discord/audit_log.json:122:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}' */
  char region[MAX_REGION_LEN];

  /* specs/discord/audit_log.json:123:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}' */
  char preferred_locale[MAX_LOCALE_LEN];

  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t afk_channel_id;

  /* specs/discord/audit_log.json:125:18
     '{"name":"afk_timeout", "type": {"base":"int"}}' */
  int afk_timeout;

  /* specs/discord/audit_log.json:126:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t rules_channel_id;

  /* specs/discord/audit_log.json:127:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t public_updates_channel_id;

  /* specs/discord/audit_log.json:128:18
     '{"name":"mfa_level", "type": {"base":"int"}}' */
  int mfa_level;

  /* specs/discord/audit_log.json:129:18
     '{"name":"verification_level", "type": {"base":"int"}}' */
  int verification_level;

  /* specs/discord/audit_log.json:130:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}' */
  int explicit_content_filter;

  /* specs/discord/audit_log.json:131:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}' */
  int default_message_notifications;

  /* specs/discord/audit_log.json:132:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}' */
  char *vanity_url;

  /* specs/discord/audit_log.json:133:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  // @todo add (null);

  /* specs/discord/audit_log.json:135:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  // @todo remove (null);

  /* specs/discord/audit_log.json:137:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}' */
  int prune_delete_days;

  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}' */
  bool widget_enabled;

  /* specs/discord/audit_log.json:139:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t widget_channel_id;

  /* specs/discord/audit_log.json:140:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t system_channel_id;

  /* specs/discord/audit_log.json:141:18
     '{"name":"position", "type": {"base":"int"}}' */
  int position;

  /* specs/discord/audit_log.json:142:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}' */
  char *topic;

  /* specs/discord/audit_log.json:143:18
     '{"name":"bitrate", "type": {"base":"int"}}' */
  int bitrate;

  /* specs/discord/audit_log.json:144:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  // @todo permission_overwrites (null);

  /* specs/discord/audit_log.json:146:18
     '{"name":"nsfw", "type": {"base":"bool"}}' */
  bool nsfw;

  /* specs/discord/audit_log.json:147:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t application_id;

  /* specs/discord/audit_log.json:148:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}' */
  int rate_limit_per_user;

  /* specs/discord/audit_log.json:149:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}' */
  char *permissions;

  /* specs/discord/audit_log.json:150:18
     '{"name":"color", "type": {"base":"int"}}' */
  int color;

  /* specs/discord/audit_log.json:151:18
     '{"name":"hoist", "type": {"base":"bool"}}' */
  bool hoist;

  /* specs/discord/audit_log.json:152:18
     '{"name":"mentionable", "type": {"base":"bool"}}' */
  bool mentionable;

  /* specs/discord/audit_log.json:153:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}' */
  char *allow;

  /* specs/discord/audit_log.json:154:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}' */
  char *deny;

  /* specs/discord/audit_log.json:155:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}' */
  char *code;

  /* specs/discord/audit_log.json:156:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}' */
  char *channel_id;

  /* specs/discord/audit_log.json:157:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}' */
  char *inviter_id;

  /* specs/discord/audit_log.json:158:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}' */
  char *max_uses;

  /* specs/discord/audit_log.json:159:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}' */
  char *uses;

  /* specs/discord/audit_log.json:160:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}' */
  char *max_age;

  /* specs/discord/audit_log.json:161:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}' */
  char *temporary;

  /* specs/discord/audit_log.json:162:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}' */
  char *deaf;

  /* specs/discord/audit_log.json:163:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}' */
  char *mute;

  /* specs/discord/audit_log.json:164:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}' */
  char *nick;

  /* specs/discord/audit_log.json:165:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}' */
  char *avatar_hash;

  /* specs/discord/audit_log.json:166:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/audit_log.json:167:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}' */
  // @todo type integer or string;

  /* specs/discord/audit_log.json:169:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}' */
  bool enable_emotions;

  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_behavior", "type": {"base":"int"}}' */
  int expire_behavior;

  /* specs/discord/audit_log.json:171:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}' */
  int expire_grace_period;

  /* specs/discord/audit_log.json:172:18
     '{"name":"user_limit", "type": {"base":"int" }}' */
  int user_limit;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[54];
    void *record_defined[54];
    void *record_null[54];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/channel
 */


// Modify Channel
// defined at specs/discord/channel.endpoints-params.json:10:22
/**
 * @see https://discord.com/developers/docs/resources/channel#modify-channel

 * - Initializer:
 *   - <tt>discord_modify_channel_params_init(struct discord_modify_channel_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_channel_params_cleanup(struct discord_modify_channel_params*)</tt>
 *   - <tt>discord_modify_channel_params_list_free(struct discord_modify_channel_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_channel_params_from_json(char *rbuf, size_t len, struct discord_modify_channel_params**)</tt>
 *   - <tt>discord_modify_channel_params_list_from_json(char *rbuf, size_t len, struct discord_modify_channel_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_channel_params_to_json(char *wbuf, size_t len, struct discord_modify_channel_params*)</tt>
 *   - <tt>discord_modify_channel_params_list_to_json(char *wbuf, size_t len, struct discord_modify_channel_params**)</tt>
 */
struct discord_modify_channel_params {
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *icon;

  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int position;

  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *topic;

  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool nsfw;

  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int rate_limit_per_user;

  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int bitrate;

  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int user_limit;

  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *rtc_region;

  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int video_quality_mode;

  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool archived;

  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
  bool locked;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[16];
    void *record_defined[16];
    void *record_null[16];
  } __M; // metadata
/// @endcond
};

// Get Reactions
// defined at specs/discord/channel.endpoints-params.json:35:22
/**
 * @see https://discord.com/developers/docs/resources/channel#get-reactions

 * - Initializer:
 *   - <tt>discord_get_reactions_params_init(struct discord_get_reactions_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_get_reactions_params_cleanup(struct discord_get_reactions_params*)</tt>
 *   - <tt>discord_get_reactions_params_list_free(struct discord_get_reactions_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_get_reactions_params_from_json(char *rbuf, size_t len, struct discord_get_reactions_params**)</tt>
 *   - <tt>discord_get_reactions_params_list_from_json(char *rbuf, size_t len, struct discord_get_reactions_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_get_reactions_params_to_json(char *wbuf, size_t len, struct discord_get_reactions_params*)</tt>
 *   - <tt>discord_get_reactions_params_list_to_json(char *wbuf, size_t len, struct discord_get_reactions_params**)</tt>
 */
struct discord_get_reactions_params {
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  u64_snowflake_t after;

  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  int limit;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Edit Channel Permissions
// defined at specs/discord/channel.endpoints-params.json:46:22
/**
 * @see https://discord.com/developers/docs/resources/channel#edit-channel-permissions

 * - Initializer:
 *   - <tt>discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params*)</tt>
 *   - <tt>discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_edit_channel_permissions_params_from_json(char *rbuf, size_t len, struct discord_edit_channel_permissions_params**)</tt>
 *   - <tt>discord_edit_channel_permissions_params_list_from_json(char *rbuf, size_t len, struct discord_edit_channel_permissions_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_edit_channel_permissions_params_to_json(char *wbuf, size_t len, struct discord_edit_channel_permissions_params*)</tt>
 *   - <tt>discord_edit_channel_permissions_params_list_to_json(char *wbuf, size_t len, struct discord_edit_channel_permissions_params**)</tt>
 */
struct discord_edit_channel_permissions_params {
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
  enum discord_permissions_bitwise_flags allow; ///< permission bit set

  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
  enum discord_permissions_bitwise_flags deny; ///< permission bit set

  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};

// Follow News Channel
// defined at specs/discord/channel.endpoints-params.json:58:22
/**
 * @see https://discord.com/developers/docs/resources/channel#follow-news-channel

 * - Initializer:
 *   - <tt>discord_follow_news_channel_params_init(struct discord_follow_news_channel_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params*)</tt>
 *   - <tt>discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_follow_news_channel_params_from_json(char *rbuf, size_t len, struct discord_follow_news_channel_params**)</tt>
 *   - <tt>discord_follow_news_channel_params_list_from_json(char *rbuf, size_t len, struct discord_follow_news_channel_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_follow_news_channel_params_to_json(char *wbuf, size_t len, struct discord_follow_news_channel_params*)</tt>
 *   - <tt>discord_follow_news_channel_params_list_to_json(char *wbuf, size_t len, struct discord_follow_news_channel_params**)</tt>
 */
struct discord_follow_news_channel_params {
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t webhook_channel_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[1];
    void *record_defined[1];
    void *record_null[1];
  } __M; // metadata
/// @endcond
};

// Create Channel Invite
// defined at specs/discord/channel.endpoints-params.json:68:22
/**
 * @see https://discord.com/developers/docs/resources/channel#create-channel-invite

 * - Initializer:
 *   - <tt>discord_create_channel_invite_params_init(struct discord_create_channel_invite_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params*)</tt>
 *   - <tt>discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_channel_invite_params_from_json(char *rbuf, size_t len, struct discord_create_channel_invite_params**)</tt>
 *   - <tt>discord_create_channel_invite_params_list_from_json(char *rbuf, size_t len, struct discord_create_channel_invite_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_channel_invite_params_to_json(char *wbuf, size_t len, struct discord_create_channel_invite_params*)</tt>
 *   - <tt>discord_create_channel_invite_params_list_to_json(char *wbuf, size_t len, struct discord_create_channel_invite_params**)</tt>
 */
struct discord_create_channel_invite_params {
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  int max_age;

  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  int max_uses;

  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  bool temporary;

  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  bool unique;

  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  int target_type;

  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_user_id;

  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  u64_snowflake_t target_application_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};

// Group DM Add Recipient
// defined at specs/discord/channel.endpoints-params.json:84:22
/**
 * @see https://discord.com/developers/docs/resources/channel#group-dm-add-recipient

 * - Initializer:
 *   - <tt>discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params*)</tt>
 *   - <tt>discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_group_dm_add_recipient_params_from_json(char *rbuf, size_t len, struct discord_group_dm_add_recipient_params**)</tt>
 *   - <tt>discord_group_dm_add_recipient_params_list_from_json(char *rbuf, size_t len, struct discord_group_dm_add_recipient_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_group_dm_add_recipient_params_to_json(char *wbuf, size_t len, struct discord_group_dm_add_recipient_params*)</tt>
 *   - <tt>discord_group_dm_add_recipient_params_list_to_json(char *wbuf, size_t len, struct discord_group_dm_add_recipient_params**)</tt>
 */
struct discord_group_dm_add_recipient_params {
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  char *access_token;

  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Start Thread with Message
// defined at specs/discord/channel.endpoints-params.json:95:22
/**
 * @see https://discord.com/developers/docs/resources/channel#start-thread-with-message-json-params

 * - Initializer:
 *   - <tt>discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params*)</tt>
 *   - <tt>discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_start_thread_with_message_params_from_json(char *rbuf, size_t len, struct discord_start_thread_with_message_params**)</tt>
 *   - <tt>discord_start_thread_with_message_params_list_from_json(char *rbuf, size_t len, struct discord_start_thread_with_message_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_start_thread_with_message_params_to_json(char *wbuf, size_t len, struct discord_start_thread_with_message_params*)</tt>
 *   - <tt>discord_start_thread_with_message_params_list_to_json(char *wbuf, size_t len, struct discord_start_thread_with_message_params**)</tt>
 */
struct discord_start_thread_with_message_params {
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Start Thread without Message
// defined at specs/discord/channel.endpoints-params.json:106:22
/**
 * @see https://discord.com/developers/docs/resources/channel#start-thread-without-message-json-params

 * - Initializer:
 *   - <tt>discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params*)</tt>
 *   - <tt>discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_start_thread_without_message_params_from_json(char *rbuf, size_t len, struct discord_start_thread_without_message_params**)</tt>
 *   - <tt>discord_start_thread_without_message_params_list_from_json(char *rbuf, size_t len, struct discord_start_thread_without_message_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_start_thread_without_message_params_to_json(char *wbuf, size_t len, struct discord_start_thread_without_message_params*)</tt>
 *   - <tt>discord_start_thread_without_message_params_list_to_json(char *wbuf, size_t len, struct discord_start_thread_without_message_params**)</tt>
 */
struct discord_start_thread_without_message_params {
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  char *name;

  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  int auto_archive_duration;

  /* specs/discord/channel.endpoints-params.json:111:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  enum discord_channel_types type;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};

// List Active Threads
// defined at specs/discord/channel.endpoints-params.json:118:22
/**
 * @see https://discord.com/developers/docs/resources/channel#list-active-threads-response-body

 * - Initializer:
 *   - <tt>discord_thread_response_body_init(struct discord_thread_response_body*)</tt>
 * - Cleanup:
 *   - <tt>discord_thread_response_body_cleanup(struct discord_thread_response_body*)</tt>
 *   - <tt>discord_thread_response_body_list_free(struct discord_thread_response_body**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_thread_response_body_from_json(char *rbuf, size_t len, struct discord_thread_response_body**)</tt>
 *   - <tt>discord_thread_response_body_list_from_json(char *rbuf, size_t len, struct discord_thread_response_body***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_thread_response_body_to_json(char *wbuf, size_t len, struct discord_thread_response_body*)</tt>
 *   - <tt>discord_thread_response_body_list_to_json(char *wbuf, size_t len, struct discord_thread_response_body**)</tt>
 */
struct discord_thread_response_body {
  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  struct discord_channel **threads;

  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  struct discord_thread_member **members;

  /* specs/discord/channel.endpoints-params.json:123:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  bool has_more;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/channel.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/channel
 */




// Channel Structure
// defined at specs/discord/channel.json:29:22
/**
 * @see https://discord.com/developers/docs/resources/channel#channel-object-channel-structure

 * - Initializer:
 *   - <tt>discord_channel_init(struct discord_channel*)</tt>
 * - Cleanup:
 *   - <tt>discord_channel_cleanup(struct discord_channel*)</tt>
 *   - <tt>discord_channel_list_free(struct discord_channel**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_channel_from_json(char *rbuf, size_t len, struct discord_channel**)</tt>
 *   - <tt>discord_channel_list_from_json(char *rbuf, size_t len, struct discord_channel***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_channel_to_json(char *wbuf, size_t len, struct discord_channel*)</tt>
 *   - <tt>discord_channel_list_to_json(char *wbuf, size_t len, struct discord_channel**)</tt>
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

  /* specs/discord/channel.json:38:83
     '{"type":{"base":"struct discord_channel_overwrite", "dec":"ntl"}, "name":"permission_overwrites",
         "option":true, "inject_if_not":null }' */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/channel.json:40:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name", 
         "option":true, "inject_if_not":null}' */
  char name[DISCORD_MAX_NAME_LEN];

  /* specs/discord/channel.json:42:75
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_TOPIC_LEN]"}, "name":"topic",
         "option":true, "inject_if_not":null }' */
  char topic[DISCORD_MAX_TOPIC_LEN];

  /* specs/discord/channel.json:44:42
     '{"type":{"base":"bool"}, "name":"nsfw", "option":true, "inject_if_not":false}' */
  bool nsfw;

  /* specs/discord/channel.json:45:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"last_message_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t last_message_id;

  /* specs/discord/channel.json:47:41
     '{"type":{"base":"int"}, "name":"bitrate", "option":true, "inject_if_not":0}' */
  int bitrate;

  /* specs/discord/channel.json:48:41
     '{"type":{"base":"int"}, "name":"user_limit", "option":true, "inject_if_not":0}' */
  int user_limit;

  /* specs/discord/channel.json:49:41
     '{"type":{"base":"int"}, "name":"rate_limit_per_user", 
         "option":true, "inject_if_not":0}' */
  int rate_limit_per_user;

  /* specs/discord/channel.json:51:70
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"recipients",
         "option":true, "inject_if_not":null}' */
  struct discord_user **recipients;

  /* specs/discord/channel.json:53:68
     '{"type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, "name":"icon",
         "option":true, "inject_if_not":null}' */
  char icon[MAX_SHA256_LEN];

  /* specs/discord/channel.json:55:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t owner_id;

  /* specs/discord/channel.json:57:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"application_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t application_id;

  /* specs/discord/channel.json:59:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"parent_id",
         "option":true, "inject_if_not":0}' */
  u64_snowflake_t parent_id;

  /* specs/discord/channel.json:61:93
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601", "nullable":true}, "name":"last_pin_timestamp",
         "option":true, "inject_if_not":0}' */
  u64_unix_ms_t last_pin_timestamp;

  /* specs/discord/channel.json:63:73
     '{"type":{"base":"struct discord_message", "dec":"ntl"}, "name":"messages"}' */
  struct discord_message **messages;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[19];
    void *record_defined[19];
    void *record_null[19];
  } __M; // metadata
/// @endcond
};



// Message Sticker Structure
// defined at specs/discord/channel.json:82:22
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure

 * - Initializer:
 *   - <tt>discord_message_sticker_init(struct discord_message_sticker*)</tt>
 * - Cleanup:
 *   - <tt>discord_message_sticker_cleanup(struct discord_message_sticker*)</tt>
 *   - <tt>discord_message_sticker_list_free(struct discord_message_sticker**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_message_sticker_from_json(char *rbuf, size_t len, struct discord_message_sticker**)</tt>
 *   - <tt>discord_message_sticker_list_from_json(char *rbuf, size_t len, struct discord_message_sticker***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_message_sticker_to_json(char *wbuf, size_t len, struct discord_message_sticker*)</tt>
 *   - <tt>discord_message_sticker_list_to_json(char *wbuf, size_t len, struct discord_message_sticker**)</tt>
 */
struct discord_message_sticker {
  /* specs/discord/channel.json:84:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:85:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t pack_id;

  /* specs/discord/channel.json:86:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/channel.json:87:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  char *description;

  /* specs/discord/channel.json:88:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}' */
  char *tags;

  /* specs/discord/channel.json:89:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}' */
  char asset[MAX_SHA256_LEN];

  /* specs/discord/channel.json:90:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":null}' */
  char preview_asset[MAX_SHA256_LEN];

  /* specs/discord/channel.json:92:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_sticker_format_types"}}' */
  enum discord_message_sticker_format_types type;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
/// @endcond
};



// Message Reference Structure
// defined at specs/discord/channel.json:112:22
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-reference-structure

 * - Initializer:
 *   - <tt>discord_message_reference_init(struct discord_message_reference*)</tt>
 * - Cleanup:
 *   - <tt>discord_message_reference_cleanup(struct discord_message_reference*)</tt>
 *   - <tt>discord_message_reference_list_free(struct discord_message_reference**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_message_reference_from_json(char *rbuf, size_t len, struct discord_message_reference**)</tt>
 *   - <tt>discord_message_reference_list_from_json(char *rbuf, size_t len, struct discord_message_reference***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_message_reference_to_json(char *wbuf, size_t len, struct discord_message_reference*)</tt>
 *   - <tt>discord_message_reference_list_to_json(char *wbuf, size_t len, struct discord_message_reference**)</tt>
 */
struct discord_message_reference {
  /* specs/discord/channel.json:114:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t message_id;

  /* specs/discord/channel.json:115:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:116:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:117:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  bool fail_if_not_exists;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Message Application Structure
// defined at specs/discord/channel.json:124:22
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-application-structure

 * - Initializer:
 *   - <tt>discord_message_application_init(struct discord_message_application*)</tt>
 * - Cleanup:
 *   - <tt>discord_message_application_cleanup(struct discord_message_application*)</tt>
 *   - <tt>discord_message_application_list_free(struct discord_message_application**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_message_application_from_json(char *rbuf, size_t len, struct discord_message_application**)</tt>
 *   - <tt>discord_message_application_list_from_json(char *rbuf, size_t len, struct discord_message_application***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_message_application_to_json(char *wbuf, size_t len, struct discord_message_application*)</tt>
 *   - <tt>discord_message_application_list_to_json(char *wbuf, size_t len, struct discord_message_application**)</tt>
 */
struct discord_message_application {
  /* specs/discord/channel.json:126:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:127:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *cover_image;

  /* specs/discord/channel.json:128:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}' */
  char *description;

  /* specs/discord/channel.json:129:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *icon;

  /* specs/discord/channel.json:130:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}' */
  char *name;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};



// Message Activity Structure
// defined at specs/discord/channel.json:149:22
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure

 * - Initializer:
 *   - <tt>discord_message_activity_init(struct discord_message_activity*)</tt>
 * - Cleanup:
 *   - <tt>discord_message_activity_cleanup(struct discord_message_activity*)</tt>
 *   - <tt>discord_message_activity_list_free(struct discord_message_activity**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_message_activity_from_json(char *rbuf, size_t len, struct discord_message_activity**)</tt>
 *   - <tt>discord_message_activity_list_from_json(char *rbuf, size_t len, struct discord_message_activity***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_message_activity_to_json(char *wbuf, size_t len, struct discord_message_activity*)</tt>
 *   - <tt>discord_message_activity_list_to_json(char *wbuf, size_t len, struct discord_message_activity**)</tt>
 */
struct discord_message_activity {
  /* specs/discord/channel.json:151:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_message_activity_types"}}' */
  enum discord_message_activity_types type;

  /* specs/discord/channel.json:152:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}' */
  char *party_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};



// Message Structure
// defined at specs/discord/channel.json:184:22
/**
 * @see https://discord.com/developers/docs/resources/channel#message-object

 * - Initializer:
 *   - <tt>discord_message_init(struct discord_message*)</tt>
 * - Cleanup:
 *   - <tt>discord_message_cleanup(struct discord_message*)</tt>
 *   - <tt>discord_message_list_free(struct discord_message**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_message_from_json(char *rbuf, size_t len, struct discord_message**)</tt>
 *   - <tt>discord_message_list_from_json(char *rbuf, size_t len, struct discord_message***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_message_to_json(char *wbuf, size_t len, struct discord_message*)</tt>
 *   - <tt>discord_message_list_to_json(char *wbuf, size_t len, struct discord_message**)</tt>
 */
struct discord_message {
  /* specs/discord/channel.json:186:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:187:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:188:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id", "option":true, "inject_if_not":0}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:189:69
     '{"type":{"base":"struct discord_user", "dec":"*"}, "name":"author"}' */
  struct discord_user *author;

  /* specs/discord/channel.json:190:77
     '{"type":{"base":"struct discord_guild_member", "dec":"*"}, "name":"member", "option":true, "comment":"partial guild member object"}' */
  struct discord_guild_member *member; ///< partial guild member object

  /* specs/discord/channel.json:191:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}' */
  char *content;

  /* specs/discord/channel.json:192:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}' */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.json:193:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp", "inject_if_not":0}' */
  u64_unix_ms_t edited_timestamp;

  /* specs/discord/channel.json:194:43
     '{"type":{"base":"bool"}, "name":"tts"}' */
  bool tts;

  /* specs/discord/channel.json:195:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}' */
  bool mention_everyone;

  /* specs/discord/channel.json:196:71
     '{"type":{"base":"struct discord_user", "dec":"ntl"}, "name":"mentions", "comment":"array of user objects, with an additional partial member field"}' */
  struct discord_user **mentions; ///< array of user objects, with an additional partial member field

  /* specs/discord/channel.json:197:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}' */
  ja_u64 **mention_roles; ///< array of role object ids

  /* specs/discord/channel.json:198:82
     '{"type":{"base":"struct discord_channel_mention", "dec":"ntl"}, "name":"mention_channels", "option":true }' */
  struct discord_channel_mention **mention_channels;

  /* specs/discord/channel.json:199:85
     '{"type":{"base":"struct discord_channel_attachment", "dec":"ntl"}, "name":"attachments"}' */
  struct discord_channel_attachment **attachments;

  /* specs/discord/channel.json:200:72
     '{"type":{"base":"struct discord_embed", "dec":"ntl"}, "name":"embeds"}' */
  struct discord_embed **embeds;

  /* specs/discord/channel.json:201:82
     '{"type":{"base":"struct discord_channel_reaction","dec":"ntl"}, "name":"reactions", "option":true }' */
  struct discord_channel_reaction **reactions;

  /* specs/discord/channel.json:202:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string", "option":true }' */
  char *nonce; ///< integer or string

  /* specs/discord/channel.json:203:43
     '{"type":{"base":"bool"}, "name":"pinned"}' */
  bool pinned;

  /* specs/discord/channel.json:204:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id", "option":true }' */
  u64_snowflake_t webhook_id;

  /* specs/discord/channel.json:205:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_types"}, "name":"type"}' */
  enum discord_message_types type;

  /* specs/discord/channel.json:206:81
     '{"type":{"base":"struct discord_message_activity", "dec":"*"}, "name":"activity", "option":true, "inject_if_not":null }' */
  struct discord_message_activity *activity;

  /* specs/discord/channel.json:207:86
     '{"type":{"base":"struct discord_message_application", "dec":"ntl"}, "name":"application", "option":true, "inject_if_not":null }' */
  struct discord_message_application **application;

  /* specs/discord/channel.json:208:82
     '{"type":{"base":"struct discord_message_reference", "dec":"*"}, "name":"message_reference", "option":true, "inject_if_not":null }' */
  struct discord_message_reference *message_reference;

  /* specs/discord/channel.json:209:84
     '{"type":{"base":"int", "int_alias":"enum discord_message_flags"}, "name":"flags", "option":true, "inject_if_not":0 }' */
  enum discord_message_flags flags;

  /* specs/discord/channel.json:210:72
     '{"type":{"base":"struct discord_message", "dec":"*"}, "name":"referenced_message", "lazy_init":true, "option":true, "inject_if_not":null, "comment":"this will cause recursive allocation if allocating as the parent"}' */
  struct discord_message *referenced_message; ///< this will cause recursive allocation if allocating as the parent

  /* specs/discord/channel.json:211:84
     '{"type":{"base":"struct discord_message_interaction", "dec":"*"}, "name":"interaction", "option":true, "inject_if_not":null, "comment":"the message associated with the message_reference"}' */
  struct discord_message_interaction *interaction; ///< the message associated with the message_reference

  /* specs/discord/channel.json:212:72
     '{"type":{"base":"struct discord_channel", "dec":"*"}, "name":"thread", "option":true, "inject_if_not":null, "comment":"the channel that was started from this message, includes thread member obejct"}' */
  struct discord_channel *thread; ///< the channel that was started from this message, includes thread member obejct

  /* specs/discord/channel.json:213:76
     '{"type":{"base":"struct discord_component", "dec":"ntl"}, "name":"components", "option":true, "inject_if_not":null, "comment":"sent if the message contains components like buttons, actions rows, or other interactive components"}' */
  struct discord_component **components; ///< sent if the message contains components like buttons, actions rows, or other interactive components

  /* specs/discord/channel.json:214:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"sticker_items", "option":true, "inject_if_not":null, "comment":"sent if the message contains stickets"}' */
  struct discord_message_sticker **sticker_items; ///< sent if the message contains stickets

  /* specs/discord/channel.json:215:82
     '{"type":{"base":"struct discord_message_sticker", "dec":"ntl"}, "name":"stickers", "option":true, "inject_if_not":null, "comment":"[DEPRECATED] array of sticker objects"}' */
  struct discord_message_sticker **stickers; ///< [DEPRECATED] array of sticker objects

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[30];
    void *record_defined[30];
    void *record_null[30];
  } __M; // metadata
/// @endcond
};

// Followed Channel Structure
// defined at specs/discord/channel.json:222:22
/**
 * @see https://discord.com/developers/docs/resources/channel#followed-channel-object-followed-channel-structure

 * - Initializer:
 *   - <tt>discord_channel_followed_channel_init(struct discord_channel_followed_channel*)</tt>
 * - Cleanup:
 *   - <tt>discord_channel_followed_channel_cleanup(struct discord_channel_followed_channel*)</tt>
 *   - <tt>discord_channel_followed_channel_list_free(struct discord_channel_followed_channel**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_channel_followed_channel_from_json(char *rbuf, size_t len, struct discord_channel_followed_channel**)</tt>
 *   - <tt>discord_channel_followed_channel_list_from_json(char *rbuf, size_t len, struct discord_channel_followed_channel***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_channel_followed_channel_to_json(char *wbuf, size_t len, struct discord_channel_followed_channel*)</tt>
 *   - <tt>discord_channel_followed_channel_list_to_json(char *wbuf, size_t len, struct discord_channel_followed_channel**)</tt>
 */
struct discord_channel_followed_channel {
  /* specs/discord/channel.json:225:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t channel_id;

  /* specs/discord/channel.json:226:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t webhook_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Reaction Structure
// defined at specs/discord/channel.json:233:22
/**
 * @see https://discord.com/developers/docs/resources/channel#reaction-object-reaction-structure

 * - Initializer:
 *   - <tt>discord_channel_reaction_init(struct discord_channel_reaction*)</tt>
 * - Cleanup:
 *   - <tt>discord_channel_reaction_cleanup(struct discord_channel_reaction*)</tt>
 *   - <tt>discord_channel_reaction_list_free(struct discord_channel_reaction**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_channel_reaction_from_json(char *rbuf, size_t len, struct discord_channel_reaction**)</tt>
 *   - <tt>discord_channel_reaction_list_from_json(char *rbuf, size_t len, struct discord_channel_reaction***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_channel_reaction_to_json(char *wbuf, size_t len, struct discord_channel_reaction*)</tt>
 *   - <tt>discord_channel_reaction_list_to_json(char *wbuf, size_t len, struct discord_channel_reaction**)</tt>
 */
struct discord_channel_reaction {
  /* specs/discord/channel.json:236:20
     '{ "name": "count", "type":{ "base":"int" }}' */
  int count;

  /* specs/discord/channel.json:237:20
     '{ "name": "me", "type":{ "base":"bool" }}' */
  bool me;

  /* specs/discord/channel.json:238:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "comment":"partial emoji object"}' */
  struct discord_emoji *emoji; ///< partial emoji object

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};

// Overwrite Structure
// defined at specs/discord/channel.json:244:22
/**
 * - Initializer:
 *   - <tt>discord_channel_overwrite_init(struct discord_channel_overwrite*)</tt>
 * - Cleanup:
 *   - <tt>discord_channel_overwrite_cleanup(struct discord_channel_overwrite*)</tt>
 *   - <tt>discord_channel_overwrite_list_free(struct discord_channel_overwrite**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_channel_overwrite_from_json(char *rbuf, size_t len, struct discord_channel_overwrite**)</tt>
 *   - <tt>discord_channel_overwrite_list_from_json(char *rbuf, size_t len, struct discord_channel_overwrite***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_channel_overwrite_to_json(char *wbuf, size_t len, struct discord_channel_overwrite*)</tt>
 *   - <tt>discord_channel_overwrite_list_to_json(char *wbuf, size_t len, struct discord_channel_overwrite**)</tt>
 */
struct discord_channel_overwrite {
  /* specs/discord/channel.json:247:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:248:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/channel.json:249:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
  enum discord_permissions_bitwise_flags allow; ///< permission bit set

  /* specs/discord/channel.json:251:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}' */
  enum discord_permissions_bitwise_flags deny; ///< permission bit set

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Thread Metadata Object
// defined at specs/discord/channel.json:259:22
/**
 * @see https://discord.com/developers/docs/resources/channel#thread-metadata-object

 * - Initializer:
 *   - <tt>discord_thread_metadata_init(struct discord_thread_metadata*)</tt>
 * - Cleanup:
 *   - <tt>discord_thread_metadata_cleanup(struct discord_thread_metadata*)</tt>
 *   - <tt>discord_thread_metadata_list_free(struct discord_thread_metadata**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_thread_metadata_from_json(char *rbuf, size_t len, struct discord_thread_metadata**)</tt>
 *   - <tt>discord_thread_metadata_list_from_json(char *rbuf, size_t len, struct discord_thread_metadata***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_thread_metadata_to_json(char *wbuf, size_t len, struct discord_thread_metadata*)</tt>
 *   - <tt>discord_thread_metadata_list_to_json(char *wbuf, size_t len, struct discord_thread_metadata**)</tt>
 */
struct discord_thread_metadata {
  /* specs/discord/channel.json:262:20
     '{ "name": "archived", "type":{ "base":"bool" }}' */
  bool archived;

  /* specs/discord/channel.json:263:20
     '{ "name": "archiver_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t archiver_id;

  /* specs/discord/channel.json:264:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }}' */
  int auto_archive_duration;

  /* specs/discord/channel.json:265:20
     '{ "name": "archive_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t archive_timestamp;

  /* specs/discord/channel.json:266:20
     '{ "name": "locked", "type":{ "base":"bool" }}' */
  bool locked;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};

// Thread Member Object
// defined at specs/discord/channel.json:273:22
/**
 * @see https://discord.com/developers/docs/resources/channel#thread-member-object

 * - Initializer:
 *   - <tt>discord_thread_member_init(struct discord_thread_member*)</tt>
 * - Cleanup:
 *   - <tt>discord_thread_member_cleanup(struct discord_thread_member*)</tt>
 *   - <tt>discord_thread_member_list_free(struct discord_thread_member**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_thread_member_from_json(char *rbuf, size_t len, struct discord_thread_member**)</tt>
 *   - <tt>discord_thread_member_list_from_json(char *rbuf, size_t len, struct discord_thread_member***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_thread_member_to_json(char *wbuf, size_t len, struct discord_thread_member*)</tt>
 *   - <tt>discord_thread_member_list_to_json(char *wbuf, size_t len, struct discord_thread_member**)</tt>
 */
struct discord_thread_member {
  /* specs/discord/channel.json:276:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:277:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t user_id;

  /* specs/discord/channel.json:278:20
     '{ "name": "join_timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t join_timestamp;

  /* specs/discord/channel.json:279:20
     '{ "name": "flags", "type":{ "base":"int" }}' */
  int flags;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Attachment Strcture
// defined at specs/discord/channel.json:286:22
/**
 * @see https://discord.com/developers/docs/resources/channel#attachment-object

 * - Initializer:
 *   - <tt>discord_channel_attachment_init(struct discord_channel_attachment*)</tt>
 * - Cleanup:
 *   - <tt>discord_channel_attachment_cleanup(struct discord_channel_attachment*)</tt>
 *   - <tt>discord_channel_attachment_list_free(struct discord_channel_attachment**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_channel_attachment_from_json(char *rbuf, size_t len, struct discord_channel_attachment**)</tt>
 *   - <tt>discord_channel_attachment_list_from_json(char *rbuf, size_t len, struct discord_channel_attachment***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_channel_attachment_to_json(char *wbuf, size_t len, struct discord_channel_attachment*)</tt>
 *   - <tt>discord_channel_attachment_list_to_json(char *wbuf, size_t len, struct discord_channel_attachment**)</tt>
 */
struct discord_channel_attachment {
  /* specs/discord/channel.json:289:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:290:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}' */
  char filename[256];

  /* specs/discord/channel.json:291:20
     '{ "name": "size", "type":{ "base":"int" }}' */
  int size;

  /* specs/discord/channel.json:292:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }}' */
  char *url;

  /* specs/discord/channel.json:293:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }}' */
  char *proxy_url;

  /* specs/discord/channel.json:294:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}' */
  int height;

  /* specs/discord/channel.json:295:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}' */
  int width;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};

// Channel Mention Structure
// defined at specs/discord/channel.json:302:22
/**
 * @see https://discord.com/developers/docs/resources/channel#channel-mention-object-channel-mention-structure

 * - Initializer:
 *   - <tt>discord_channel_mention_init(struct discord_channel_mention*)</tt>
 * - Cleanup:
 *   - <tt>discord_channel_mention_cleanup(struct discord_channel_mention*)</tt>
 *   - <tt>discord_channel_mention_list_free(struct discord_channel_mention**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_channel_mention_from_json(char *rbuf, size_t len, struct discord_channel_mention**)</tt>
 *   - <tt>discord_channel_mention_list_from_json(char *rbuf, size_t len, struct discord_channel_mention***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_channel_mention_to_json(char *wbuf, size_t len, struct discord_channel_mention*)</tt>
 *   - <tt>discord_channel_mention_list_to_json(char *wbuf, size_t len, struct discord_channel_mention**)</tt>
 */
struct discord_channel_mention {
  /* specs/discord/channel.json:305:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/channel.json:306:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t guild_id;

  /* specs/discord/channel.json:307:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" }}' */
  enum discord_channel_types type;

  /* specs/discord/channel.json:308:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Allowed Mentions Structure
// defined at specs/discord/channel.json:315:22
/**
 * @see https://discord.com/developers/docs/resources/channel#allowed-mentions-object-allowed-mentions-structure

 * - Initializer:
 *   - <tt>discord_channel_allowed_mentions_init(struct discord_channel_allowed_mentions*)</tt>
 * - Cleanup:
 *   - <tt>discord_channel_allowed_mentions_cleanup(struct discord_channel_allowed_mentions*)</tt>
 *   - <tt>discord_channel_allowed_mentions_list_free(struct discord_channel_allowed_mentions**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_channel_allowed_mentions_from_json(char *rbuf, size_t len, struct discord_channel_allowed_mentions**)</tt>
 *   - <tt>discord_channel_allowed_mentions_list_from_json(char *rbuf, size_t len, struct discord_channel_allowed_mentions***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_channel_allowed_mentions_to_json(char *wbuf, size_t len, struct discord_channel_allowed_mentions*)</tt>
 *   - <tt>discord_channel_allowed_mentions_list_to_json(char *wbuf, size_t len, struct discord_channel_allowed_mentions**)</tt>
 */
struct discord_channel_allowed_mentions {
  /* specs/discord/channel.json:318:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}' */
  ja_str **parse;

  /* specs/discord/channel.json:319:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  ja_u64 **roles; ///< list of snowflakes

  /* specs/discord/channel.json:320:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}' */
  ja_u64 **users; ///< list of snowflakes

  /* specs/discord/channel.json:321:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}' */
  bool replied_user;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Embed Structure
// defined at specs/discord/channel.json:327:22
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-structure

 * - Initializer:
 *   - <tt>discord_embed_init(struct discord_embed*)</tt>
 * - Cleanup:
 *   - <tt>discord_embed_cleanup(struct discord_embed*)</tt>
 *   - <tt>discord_embed_list_free(struct discord_embed**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_embed_from_json(char *rbuf, size_t len, struct discord_embed**)</tt>
 *   - <tt>discord_embed_list_from_json(char *rbuf, size_t len, struct discord_embed***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_embed_to_json(char *wbuf, size_t len, struct discord_embed*)</tt>
 *   - <tt>discord_embed_list_to_json(char *wbuf, size_t len, struct discord_embed**)</tt>
 */
struct discord_embed {
  /* specs/discord/channel.json:330:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[DISCORD_EMBED_TITLE_LEN]" }, "option":true, "inject_if_not":null}' */
  char title[DISCORD_EMBED_TITLE_LEN];

  /* specs/discord/channel.json:331:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, "option":true, "inject_if_not":null}' */
  char type[32];

  /* specs/discord/channel.json:332:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[DISCORD_EMBED_DESCRIPTION_LEN]"}, "option":true, "inject_if_not":null}' */
  char description[DISCORD_EMBED_DESCRIPTION_LEN];

  /* specs/discord/channel.json:333:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:334:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }, "option":true, "inject_if_not":0}' */
  u64_unix_ms_t timestamp;

  /* specs/discord/channel.json:335:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}' */
  int color;

  /* specs/discord/channel.json:336:20
     '{ "name": "footer", "type":{ "base":"struct discord_embed_footer", "dec":"*"}, "option":true, "inject_if_not":null}' */
  struct discord_embed_footer *footer;

  /* specs/discord/channel.json:337:20
     '{ "name": "image", "type":{ "base":"struct discord_embed_image", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_image *image;

  /* specs/discord/channel.json:338:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_embed_thumbnail", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_thumbnail *thumbnail;

  /* specs/discord/channel.json:339:20
     '{ "name": "video", "type":{ "base":"struct discord_embed_video", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_video *video;

  /* specs/discord/channel.json:340:20
     '{ "name": "provider", "type":{ "base":"struct discord_embed_provider", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_provider *provider;

  /* specs/discord/channel.json:341:20
     '{ "name": "author", "type":{ "base":"struct discord_embed_author", "dec":"*"}, "inject_if_not":null}' */
  struct discord_embed_author *author;

  /* specs/discord/channel.json:342:20
     '{ "name": "fields", "type":{ "base":"struct discord_embed_field", "dec":"ntl"}, "option":true, "inject_if_not":null}' */
  struct discord_embed_field **fields;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[13];
    void *record_defined[13];
    void *record_null[13];
  } __M; // metadata
/// @endcond
};

// Embed Thumbnail Structure
// defined at specs/discord/channel.json:349:22
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure

 * - Initializer:
 *   - <tt>discord_embed_thumbnail_init(struct discord_embed_thumbnail*)</tt>
 * - Cleanup:
 *   - <tt>discord_embed_thumbnail_cleanup(struct discord_embed_thumbnail*)</tt>
 *   - <tt>discord_embed_thumbnail_list_free(struct discord_embed_thumbnail**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_embed_thumbnail_from_json(char *rbuf, size_t len, struct discord_embed_thumbnail**)</tt>
 *   - <tt>discord_embed_thumbnail_list_from_json(char *rbuf, size_t len, struct discord_embed_thumbnail***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_embed_thumbnail_to_json(char *wbuf, size_t len, struct discord_embed_thumbnail*)</tt>
 *   - <tt>discord_embed_thumbnail_list_to_json(char *wbuf, size_t len, struct discord_embed_thumbnail**)</tt>
 */
struct discord_embed_thumbnail {
  /* specs/discord/channel.json:351:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:352:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:353:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:354:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Embed Video Structure
// defined at specs/discord/channel.json:361:22
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure

 * - Initializer:
 *   - <tt>discord_embed_video_init(struct discord_embed_video*)</tt>
 * - Cleanup:
 *   - <tt>discord_embed_video_cleanup(struct discord_embed_video*)</tt>
 *   - <tt>discord_embed_video_list_free(struct discord_embed_video**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_embed_video_from_json(char *rbuf, size_t len, struct discord_embed_video**)</tt>
 *   - <tt>discord_embed_video_list_from_json(char *rbuf, size_t len, struct discord_embed_video***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_embed_video_to_json(char *wbuf, size_t len, struct discord_embed_video*)</tt>
 *   - <tt>discord_embed_video_list_to_json(char *wbuf, size_t len, struct discord_embed_video**)</tt>
 */
struct discord_embed_video {
  /* specs/discord/channel.json:363:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:364:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:365:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:366:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Embed Image Structure
// defined at specs/discord/channel.json:373:22
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure

 * - Initializer:
 *   - <tt>discord_embed_image_init(struct discord_embed_image*)</tt>
 * - Cleanup:
 *   - <tt>discord_embed_image_cleanup(struct discord_embed_image*)</tt>
 *   - <tt>discord_embed_image_list_free(struct discord_embed_image**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_embed_image_from_json(char *rbuf, size_t len, struct discord_embed_image**)</tt>
 *   - <tt>discord_embed_image_list_from_json(char *rbuf, size_t len, struct discord_embed_image***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_embed_image_to_json(char *wbuf, size_t len, struct discord_embed_image*)</tt>
 *   - <tt>discord_embed_image_list_to_json(char *wbuf, size_t len, struct discord_embed_image**)</tt>
 */
struct discord_embed_image {
  /* specs/discord/channel.json:375:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:376:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_url;

  /* specs/discord/channel.json:377:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}' */
  int height;

  /* specs/discord/channel.json:378:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}' */
  int width;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Embed Provider Structure
// defined at specs/discord/channel.json:385:22
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure

 * - Initializer:
 *   - <tt>discord_embed_provider_init(struct discord_embed_provider*)</tt>
 * - Cleanup:
 *   - <tt>discord_embed_provider_cleanup(struct discord_embed_provider*)</tt>
 *   - <tt>discord_embed_provider_list_free(struct discord_embed_provider**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_embed_provider_from_json(char *rbuf, size_t len, struct discord_embed_provider**)</tt>
 *   - <tt>discord_embed_provider_list_from_json(char *rbuf, size_t len, struct discord_embed_provider***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_embed_provider_to_json(char *wbuf, size_t len, struct discord_embed_provider*)</tt>
 *   - <tt>discord_embed_provider_list_to_json(char *wbuf, size_t len, struct discord_embed_provider**)</tt>
 */
struct discord_embed_provider {
  /* specs/discord/channel.json:387:20
     '{ "name": "name", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *name;

  /* specs/discord/channel.json:388:20
     '{ "name": "url", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}' */
  char *url;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Embed Author Structure
// defined at specs/discord/channel.json:395:22
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure

 * - Initializer:
 *   - <tt>discord_embed_author_init(struct discord_embed_author*)</tt>
 * - Cleanup:
 *   - <tt>discord_embed_author_cleanup(struct discord_embed_author*)</tt>
 *   - <tt>discord_embed_author_list_free(struct discord_embed_author**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_embed_author_from_json(char *rbuf, size_t len, struct discord_embed_author**)</tt>
 *   - <tt>discord_embed_author_list_from_json(char *rbuf, size_t len, struct discord_embed_author***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_embed_author_to_json(char *wbuf, size_t len, struct discord_embed_author*)</tt>
 *   - <tt>discord_embed_author_list_to_json(char *wbuf, size_t len, struct discord_embed_author**)</tt>
 */
struct discord_embed_author {
  /* specs/discord/channel.json:397:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":null}' */
  char name[DISCORD_EMBED_AUTHOR_NAME_LEN];

  /* specs/discord/channel.json:398:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *url;

  /* specs/discord/channel.json:399:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *icon_url;

  /* specs/discord/channel.json:400:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *proxy_icon_url;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Embed Footer Structure
// defined at specs/discord/channel.json:407:22
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure

 * - Initializer:
 *   - <tt>discord_embed_footer_init(struct discord_embed_footer*)</tt>
 * - Cleanup:
 *   - <tt>discord_embed_footer_cleanup(struct discord_embed_footer*)</tt>
 *   - <tt>discord_embed_footer_list_free(struct discord_embed_footer**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_embed_footer_from_json(char *rbuf, size_t len, struct discord_embed_footer**)</tt>
 *   - <tt>discord_embed_footer_list_from_json(char *rbuf, size_t len, struct discord_embed_footer***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_embed_footer_to_json(char *wbuf, size_t len, struct discord_embed_footer*)</tt>
 *   - <tt>discord_embed_footer_list_to_json(char *wbuf, size_t len, struct discord_embed_footer**)</tt>
 */
struct discord_embed_footer {
  /* specs/discord/channel.json:409:20
     '{ "name": "text", "type": {"base":"char", "dec":"[DISCORD_EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":null}' */
  char text[DISCORD_EMBED_FOOTER_TEXT_LEN];

  /* specs/discord/channel.json:410:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"*" }, "option":true, "inject_if_not":null}' */
  char *icon_url;

  /* specs/discord/channel.json:411:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  char *proxy_icon_url;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};

// Embed Field Structure
// defined at specs/discord/channel.json:418:22
/**
 * @see https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure

 * - Initializer:
 *   - <tt>discord_embed_field_init(struct discord_embed_field*)</tt>
 * - Cleanup:
 *   - <tt>discord_embed_field_cleanup(struct discord_embed_field*)</tt>
 *   - <tt>discord_embed_field_list_free(struct discord_embed_field**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_embed_field_from_json(char *rbuf, size_t len, struct discord_embed_field**)</tt>
 *   - <tt>discord_embed_field_list_from_json(char *rbuf, size_t len, struct discord_embed_field***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_embed_field_to_json(char *wbuf, size_t len, struct discord_embed_field*)</tt>
 *   - <tt>discord_embed_field_list_to_json(char *wbuf, size_t len, struct discord_embed_field**)</tt>
 */
struct discord_embed_field {
  /* specs/discord/channel.json:420:20
     '{ "name": "name", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_NAME_LEN]" }, "inject_if_not":null}' */
  char name[DISCORD_EMBED_FIELD_NAME_LEN];

  /* specs/discord/channel.json:421:20
     '{ "name": "value", "type": { "base":"char", "dec":"[DISCORD_EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":null}' */
  char value[DISCORD_EMBED_FIELD_VALUE_LEN];

  /* specs/discord/channel.json:422:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}' */
  bool Inline;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see 
 */


// Create Guild Emoji
// defined at specs/discord/emoji.endpoints-params.json:10:22
/**
 * @see https://discord.com/developers/docs/resources/emoji#create-guild-emoji

 * - Initializer:
 *   - <tt>discord_create_guild_emoji_params_init(struct discord_create_guild_emoji_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_guild_emoji_params_cleanup(struct discord_create_guild_emoji_params*)</tt>
 *   - <tt>discord_create_guild_emoji_params_list_free(struct discord_create_guild_emoji_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_guild_emoji_params_from_json(char *rbuf, size_t len, struct discord_create_guild_emoji_params**)</tt>
 *   - <tt>discord_create_guild_emoji_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_emoji_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_guild_emoji_params_to_json(char *wbuf, size_t len, struct discord_create_guild_emoji_params*)</tt>
 *   - <tt>discord_create_guild_emoji_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_emoji_params**)</tt>
 */
struct discord_create_guild_emoji_params {
  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
  char *image; ///< Base64 Encoded Image Data

  /* specs/discord/emoji.endpoints-params.json:15:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  ja_u64 **roles; ///< roles for which this emoji will be whitelisted

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};

// Modify Guild Emoji
// defined at specs/discord/emoji.endpoints-params.json:22:22
/**
 * @see https://discord.com/developers/docs/resources/emoji#modify-guild-emoji

 * - Initializer:
 *   - <tt>discord_modify_guild_emoji_params_init(struct discord_modify_guild_emoji_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_guild_emoji_params_cleanup(struct discord_modify_guild_emoji_params*)</tt>
 *   - <tt>discord_modify_guild_emoji_params_list_free(struct discord_modify_guild_emoji_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_guild_emoji_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_emoji_params**)</tt>
 *   - <tt>discord_modify_guild_emoji_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_emoji_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_guild_emoji_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_emoji_params*)</tt>
 *   - <tt>discord_modify_guild_emoji_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_emoji_params**)</tt>
 */
struct discord_modify_guild_emoji_params {
  /* specs/discord/emoji.endpoints-params.json:25:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/emoji.endpoints-params.json:26:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  ja_u64 **roles; ///< roles for which this emoji will be whitelisted

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/emoji.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/emoji
 */


// Emoji Structure
// defined at specs/discord/emoji.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure

 * - Initializer:
 *   - <tt>discord_emoji_init(struct discord_emoji*)</tt>
 * - Cleanup:
 *   - <tt>discord_emoji_cleanup(struct discord_emoji*)</tt>
 *   - <tt>discord_emoji_list_free(struct discord_emoji**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_emoji_from_json(char *rbuf, size_t len, struct discord_emoji**)</tt>
 *   - <tt>discord_emoji_list_from_json(char *rbuf, size_t len, struct discord_emoji***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_emoji_to_json(char *wbuf, size_t len, struct discord_emoji*)</tt>
 *   - <tt>discord_emoji_list_to_json(char *wbuf, size_t len, struct discord_emoji**)</tt>
 */
struct discord_emoji {
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_permissions_role", "dec":"ntl"}, "option":true,
          "todo":true }' */
  // @todo roles (null);

  /* specs/discord/emoji.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }' */
  struct discord_user *user;

  /* specs/discord/emoji.json:17:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}' */
  bool require_colons;

  /* specs/discord/emoji.json:18:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}' */
  bool managed;

  /* specs/discord/emoji.json:19:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}' */
  bool animated;

  /* specs/discord/emoji.json:20:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}' */
  bool available;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/gateway.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/topics/gateway
 */










// Identify Structure
// defined at specs/discord/gateway.json:116:22
/**
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-structure

 * - Initializer:
 *   - <tt>discord_gateway_identify_init(struct discord_gateway_identify*)</tt>
 * - Cleanup:
 *   - <tt>discord_gateway_identify_cleanup(struct discord_gateway_identify*)</tt>
 *   - <tt>discord_gateway_identify_list_free(struct discord_gateway_identify**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_gateway_identify_from_json(char *rbuf, size_t len, struct discord_gateway_identify**)</tt>
 *   - <tt>discord_gateway_identify_list_from_json(char *rbuf, size_t len, struct discord_gateway_identify***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_gateway_identify_to_json(char *wbuf, size_t len, struct discord_gateway_identify*)</tt>
 *   - <tt>discord_gateway_identify_list_to_json(char *wbuf, size_t len, struct discord_gateway_identify**)</tt>
 */
struct discord_gateway_identify {
  /* specs/discord/gateway.json:119:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
  char *token;

  /* specs/discord/gateway.json:120:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}' */
  struct discord_gateway_identify_connection *properties;

  /* specs/discord/gateway.json:121:19
     '{ "name":"compress","type":{"base":"bool"}}' */
  bool compress;

  /* specs/discord/gateway.json:122:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
  int large_threshold;

  /* specs/discord/gateway.json:123:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
  bool guild_subscriptions;

  /* specs/discord/gateway.json:124:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  // @todo shard (null);

  /* specs/discord/gateway.json:125:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}' */
  struct discord_gateway_status_update *presence;

  /* specs/discord/gateway.json:126:19
     '{ "name":"intents","type":{"base":"int"}}' */
  int intents;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
/// @endcond
};

// Gateway Status Update Structure
// defined at specs/discord/gateway.json:132:22
/**
 * @see https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure

 * - Initializer:
 *   - <tt>discord_gateway_status_update_init(struct discord_gateway_status_update*)</tt>
 * - Cleanup:
 *   - <tt>discord_gateway_status_update_cleanup(struct discord_gateway_status_update*)</tt>
 *   - <tt>discord_gateway_status_update_list_free(struct discord_gateway_status_update**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_gateway_status_update_from_json(char *rbuf, size_t len, struct discord_gateway_status_update**)</tt>
 *   - <tt>discord_gateway_status_update_list_from_json(char *rbuf, size_t len, struct discord_gateway_status_update***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_gateway_status_update_to_json(char *wbuf, size_t len, struct discord_gateway_status_update*)</tt>
 *   - <tt>discord_gateway_status_update_list_to_json(char *wbuf, size_t len, struct discord_gateway_status_update**)</tt>
 */
struct discord_gateway_status_update {
  /* specs/discord/gateway.json:135:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }' */
  u64_unix_ms_t since;

  /* specs/discord/gateway.json:137:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}' */
  struct discord_gateway_activity **activities;

  /* specs/discord/gateway.json:139:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}' */
  char status[16];

  /* specs/discord/gateway.json:140:19
     '{ "name":"afk","type":{"base":"bool"}}' */
  bool afk;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Identify Connection Properties
// defined at specs/discord/gateway.json:147:22
/**
 * @see https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties

 * - Initializer:
 *   - <tt>discord_gateway_identify_connection_init(struct discord_gateway_identify_connection*)</tt>
 * - Cleanup:
 *   - <tt>discord_gateway_identify_connection_cleanup(struct discord_gateway_identify_connection*)</tt>
 *   - <tt>discord_gateway_identify_connection_list_free(struct discord_gateway_identify_connection**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_gateway_identify_connection_from_json(char *rbuf, size_t len, struct discord_gateway_identify_connection**)</tt>
 *   - <tt>discord_gateway_identify_connection_list_from_json(char *rbuf, size_t len, struct discord_gateway_identify_connection***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_gateway_identify_connection_to_json(char *wbuf, size_t len, struct discord_gateway_identify_connection*)</tt>
 *   - <tt>discord_gateway_identify_connection_list_to_json(char *wbuf, size_t len, struct discord_gateway_identify_connection**)</tt>
 */
struct discord_gateway_identify_connection {
  /* specs/discord/gateway.json:150:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}}' */
  char *os;

  /* specs/discord/gateway.json:151:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}}' */
  char *browser;

  /* specs/discord/gateway.json:152:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}}' */
  char *device;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};

// Activity Structure
// defined at specs/discord/gateway.json:158:22
/**
 * @see https://discord.com/developers/docs/topics/gateway#activity-object-activity-structure

 * - Initializer:
 *   - <tt>discord_gateway_activity_init(struct discord_gateway_activity*)</tt>
 * - Cleanup:
 *   - <tt>discord_gateway_activity_cleanup(struct discord_gateway_activity*)</tt>
 *   - <tt>discord_gateway_activity_list_free(struct discord_gateway_activity**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_gateway_activity_from_json(char *rbuf, size_t len, struct discord_gateway_activity**)</tt>
 *   - <tt>discord_gateway_activity_list_from_json(char *rbuf, size_t len, struct discord_gateway_activity***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_gateway_activity_to_json(char *wbuf, size_t len, struct discord_gateway_activity*)</tt>
 *   - <tt>discord_gateway_activity_list_to_json(char *wbuf, size_t len, struct discord_gateway_activity**)</tt>
 */
struct discord_gateway_activity {
  /* specs/discord/gateway.json:161:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}' */
  char name[512];

  /* specs/discord/gateway.json:162:19
     '{ "name":"type","type":{"base":"int"}}' */
  int type;

  /* specs/discord/gateway.json:163:19
     '{ "name":"url","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":""}' */
  char *url;

  /* specs/discord/gateway.json:165:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }' */
  u64_unix_ms_t created_at;

  /* specs/discord/gateway.json:167:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }' */
  u64_snowflake_t application_id;

  /* specs/discord/gateway.json:169:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}' */
  char *details;

  /* specs/discord/gateway.json:171:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}' */
  char *state;

  /* specs/discord/gateway.json:173:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}' */
  bool instance;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
/// @endcond
};


/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/guild-template
 */


// Create Guild From Guild Template
// defined at specs/discord/guild-template.endpoints-params.json:10:22
/**
 * @see https://discord.com/developers/docs/resources/guild-template#create-guild-from-guild-template-json-params

 * - Initializer:
 *   - <tt>discord_create_guild_from_guild_template_params_init(struct discord_create_guild_from_guild_template_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_guild_from_guild_template_params_cleanup(struct discord_create_guild_from_guild_template_params*)</tt>
 *   - <tt>discord_create_guild_from_guild_template_params_list_free(struct discord_create_guild_from_guild_template_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_guild_from_guild_template_params_from_json(char *rbuf, size_t len, struct discord_create_guild_from_guild_template_params**)</tt>
 *   - <tt>discord_create_guild_from_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_from_guild_template_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_guild_from_guild_template_params_to_json(char *wbuf, size_t len, struct discord_create_guild_from_guild_template_params*)</tt>
 *   - <tt>discord_create_guild_from_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_from_guild_template_params**)</tt>
 */
struct discord_create_guild_from_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  char *name; ///< name of the guild

  /* specs/discord/guild-template.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon"}' */
  char *icon; ///< base64 128x128 image for the guild icon

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Create Guild Template
// defined at specs/discord/guild-template.endpoints-params.json:21:22
/**
 * @see https://discord.com/developers/docs/resources/guild-template#create-guild-template-json-params

 * - Initializer:
 *   - <tt>discord_create_guild_template_params_init(struct discord_create_guild_template_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_guild_template_params_cleanup(struct discord_create_guild_template_params*)</tt>
 *   - <tt>discord_create_guild_template_params_list_free(struct discord_create_guild_template_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_guild_template_params_from_json(char *rbuf, size_t len, struct discord_create_guild_template_params**)</tt>
 *   - <tt>discord_create_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_template_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_guild_template_params_to_json(char *wbuf, size_t len, struct discord_create_guild_template_params*)</tt>
 *   - <tt>discord_create_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_template_params**)</tt>
 */
struct discord_create_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  char *name; ///< name of the guild

  /* specs/discord/guild-template.endpoints-params.json:25:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars"}' */
  char *description; ///< description for the template (0-120) chars

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Modify Guild Template
// defined at specs/discord/guild-template.endpoints-params.json:32:22
/**
 * @see https://discord.com/developers/docs/resources/guild-template#modify-guild-template-json-params

 * - Initializer:
 *   - <tt>discord_modify_guild_template_params_init(struct discord_modify_guild_template_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params*)</tt>
 *   - <tt>discord_modify_guild_template_params_list_free(struct discord_modify_guild_template_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_guild_template_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_template_params**)</tt>
 *   - <tt>discord_modify_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_template_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_guild_template_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_template_params*)</tt>
 *   - <tt>discord_modify_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_template_params**)</tt>
 */
struct discord_modify_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  char *name; ///< name of the guild

  /* specs/discord/guild-template.endpoints-params.json:36:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars"}' */
  char *description; ///< description for the template (0-120) chars

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/guild-template
 */


// Guild Template Structure
// defined at specs/discord/guild-template.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/guild-template#guild-template-object-guild-template-structure

 * - Initializer:
 *   - <tt>discord_guild_template_init(struct discord_guild_template*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_template_cleanup(struct discord_guild_template*)</tt>
 *   - <tt>discord_guild_template_list_free(struct discord_guild_template**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_template_from_json(char *rbuf, size_t len, struct discord_guild_template**)</tt>
 *   - <tt>discord_guild_template_list_from_json(char *rbuf, size_t len, struct discord_guild_template***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_template_to_json(char *wbuf, size_t len, struct discord_guild_template*)</tt>
 *   - <tt>discord_guild_template_list_to_json(char *wbuf, size_t len, struct discord_guild_template**)</tt>
 */
struct discord_guild_template {
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
  char *code; ///< @todo find fixed size limit

  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
  char *name; ///< @todo find fixed size limit

  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}' */
  char *description; ///< @todo find fixed size limit

  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
  int usage_count;

  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t creator_id;

  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  struct discord_user *creator;

  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t created_at;

  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t updated_at;

  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t source_guild_id;

  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
  struct discord_guild *serialized_source_guild;

  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}' */
  bool is_dirty;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[11];
    void *record_defined[11];
    void *record_null[11];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/guild
 */


// Create Guild
// defined at specs/discord/guild.endpoints-params.json:10:22
/**
 * @see https://discord.com/developers/docs/resources/guild#create-guild

 * - Initializer:
 *   - <tt>discord_create_guild_params_init(struct discord_create_guild_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_guild_params_cleanup(struct discord_create_guild_params*)</tt>
 *   - <tt>discord_create_guild_params_list_free(struct discord_create_guild_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_guild_params_from_json(char *rbuf, size_t len, struct discord_create_guild_params**)</tt>
 *   - <tt>discord_create_guild_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_guild_params_to_json(char *wbuf, size_t len, struct discord_create_guild_params*)</tt>
 *   - <tt>discord_create_guild_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_params**)</tt>
 */
struct discord_create_guild_params {
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  char *name; ///< name of the guild (2-100) characters

  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  char *region; ///< voice region id

  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  char *icon; ///< base64 128x1128 image for the guild icon

  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  int verification_level; ///< verification level

  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  int default_message_notifications; ///< default message notification level

  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  int explicit_content_filter; ///< explicit content filter level

  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */
  // @todo roles new guild roles;

  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
  struct discord_channel **channels; ///< array of partial channel objects

  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  u64_snowflake_t afk_channel_id; ///< id for afk channel

  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  int afk_timeout; ///< afk timeout in seconds

  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  u64_snowflake_t system_channel_id; ///< the id of the channel where guild notices such as welcome messages and boost events are posted

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[11];
    void *record_defined[11];
    void *record_null[11];
  } __M; // metadata
/// @endcond
};

// Modify Guild
// defined at specs/discord/guild.endpoints-params.json:30:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-json-params

 * - Initializer:
 *   - <tt>discord_modify_guild_params_init(struct discord_modify_guild_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_guild_params_cleanup(struct discord_modify_guild_params*)</tt>
 *   - <tt>discord_modify_guild_params_list_free(struct discord_modify_guild_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_guild_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_params**)</tt>
 *   - <tt>discord_modify_guild_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_guild_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_params*)</tt>
 *   - <tt>discord_modify_guild_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_params**)</tt>
 */
struct discord_modify_guild_params {
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  char *name; ///< name of the guild (2-100) characters

  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  char *region; ///< voice region id

  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  int verification_level; ///< verification level

  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  int default_message_notifications; ///< default message notification level

  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  int explicit_content_filter; ///< explicit content filter level

  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  u64_snowflake_t afk_channel_id; ///< id for afk channel

  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  int afk_timeout; ///< afk timeout in seconds

  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  char *icon; ///< base64 128x1128 image for the guild icon

  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
  u64_snowflake_t owner_id; ///< user id to transfer guild ownership to (must be owner)

  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
  char *splash; ///< base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature

  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
  char *discovery_splash; ///< base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)

  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
  char *banner; ///< cannot unescape an ill-formed-string 	base64 16:9 png/jpeg image for the guild banner (wh

  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  u64_snowflake_t system_channel_id; ///< cannot unescape an ill-formed-string 	the id of the channel where guild notices such as welcome

  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
  enum discord_guild_system_channel_flags system_channel_flags; ///< system channel flags

  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
  u64_snowflake_t rules_channel_id; ///< the id of the channel where Community guilds display rules and/or guidelines

  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
  u64_snowflake_t public_updates_channel_id; ///< the id of the channel where admins and moderators of Community guilds receive notices from Discord

  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
  char *preferred_locale; ///< the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to "en-US"

  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */
  // @todo features array of guild feature strings;

  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
  char *description; ///< the description for the guild, if the guild is discoverable

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[19];
    void *record_defined[19];
    void *record_null[19];
  } __M; // metadata
/// @endcond
};

// Create Guild Channel
// defined at specs/discord/guild.endpoints-params.json:58:22
/**
 * @see https://discord.com/developers/docs/resources/guild#create-guild-channel

 * - Initializer:
 *   - <tt>discord_create_guild_channel_params_init(struct discord_create_guild_channel_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params*)</tt>
 *   - <tt>discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_guild_channel_params_from_json(char *rbuf, size_t len, struct discord_create_guild_channel_params**)</tt>
 *   - <tt>discord_create_guild_channel_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_channel_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_guild_channel_params_to_json(char *wbuf, size_t len, struct discord_create_guild_channel_params*)</tt>
 *   - <tt>discord_create_guild_channel_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_channel_params**)</tt>
 */
struct discord_create_guild_channel_params {
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  int type;

  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
  char *topic;

  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
  int bitrate;

  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
  int user_limit;

  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
  int rate_limit_per_user;

  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */
  int position;

  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  u64_snowflake_t parent_id;

  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
  bool nsfw;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[10];
    void *record_defined[10];
    void *record_null[10];
  } __M; // metadata
/// @endcond
};

// Modify Guild Channel Positions
// defined at specs/discord/guild.endpoints-params.json:77:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-channel-positions-json-params

 * - Initializer:
 *   - <tt>discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params*)</tt>
 *   - <tt>discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_guild_channel_positions_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_channel_positions_params**)</tt>
 *   - <tt>discord_modify_guild_channel_positions_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_channel_positions_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_guild_channel_positions_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_channel_positions_params*)</tt>
 *   - <tt>discord_modify_guild_channel_positions_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_channel_positions_params**)</tt>
 */
struct discord_modify_guild_channel_positions_params {
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
  u64_snowflake_t id; ///< channel id

  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
  int position; ///< sorting position of the channel

  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
  bool lock_permissions; ///< syncs the permission overwrites with the new parent, if moving to a new category

  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
  u64_snowflake_t parent_id; ///< the new parent ID for the channel that is moved

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Search Guild Members
// defined at specs/discord/guild.endpoints-params.json:90:22
/**
 * @see https://discord.com/developers/docs/resources/guild#search-guild-members-query-string-params

 * - Initializer:
 *   - <tt>discord_search_guild_members_params_init(struct discord_search_guild_members_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params*)</tt>
 *   - <tt>discord_search_guild_members_params_list_free(struct discord_search_guild_members_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_search_guild_members_params_from_json(char *rbuf, size_t len, struct discord_search_guild_members_params**)</tt>
 *   - <tt>discord_search_guild_members_params_list_from_json(char *rbuf, size_t len, struct discord_search_guild_members_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_search_guild_members_params_to_json(char *wbuf, size_t len, struct discord_search_guild_members_params*)</tt>
 *   - <tt>discord_search_guild_members_params_list_to_json(char *wbuf, size_t len, struct discord_search_guild_members_params**)</tt>
 */
struct discord_search_guild_members_params {
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
  char *query; ///< Query string to match username(s) and nickname(s) against.

  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
  int limit; ///< max number of members to return (1-1000)

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Add Guild Member
// defined at specs/discord/guild.endpoints-params.json:101:22
/**
 * @see https://discord.com/developers/docs/resources/guild#add-guild-member-json-params

 * - Initializer:
 *   - <tt>discord_add_guild_member_params_init(struct discord_add_guild_member_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params*)</tt>
 *   - <tt>discord_add_guild_member_params_list_free(struct discord_add_guild_member_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_add_guild_member_params_from_json(char *rbuf, size_t len, struct discord_add_guild_member_params**)</tt>
 *   - <tt>discord_add_guild_member_params_list_from_json(char *rbuf, size_t len, struct discord_add_guild_member_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_add_guild_member_params_to_json(char *wbuf, size_t len, struct discord_add_guild_member_params*)</tt>
 *   - <tt>discord_add_guild_member_params_list_to_json(char *wbuf, size_t len, struct discord_add_guild_member_params**)</tt>
 */
struct discord_add_guild_member_params {
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *access_token;

  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *nick;

  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **roles;

  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mute;

  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool deaf;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};

// Modify Guild Member
// defined at specs/discord/guild.endpoints-params.json:115:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-member

 * - Initializer:
 *   - <tt>discord_modify_guild_member_params_init(struct discord_modify_guild_member_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params*)</tt>
 *   - <tt>discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_guild_member_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_member_params**)</tt>
 *   - <tt>discord_modify_guild_member_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_member_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_guild_member_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_member_params*)</tt>
 *   - <tt>discord_modify_guild_member_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_member_params**)</tt>
 */
struct discord_modify_guild_member_params {
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  char *nick;

  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **roles;

  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mute;

  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool deaf;

  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  u64_snowflake_t channel_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};

// Create Guild Role
// defined at specs/discord/guild.endpoints-params.json:129:22
/**
 * @see https://discord.com/developers/docs/resources/guild#create-guild-role

 * - Initializer:
 *   - <tt>discord_create_guild_role_params_init(struct discord_create_guild_role_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params*)</tt>
 *   - <tt>discord_create_guild_role_params_list_free(struct discord_create_guild_role_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_guild_role_params_from_json(char *rbuf, size_t len, struct discord_create_guild_role_params**)</tt>
 *   - <tt>discord_create_guild_role_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_role_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_guild_role_params_to_json(char *wbuf, size_t len, struct discord_create_guild_role_params*)</tt>
 *   - <tt>discord_create_guild_role_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_role_params**)</tt>
 */
struct discord_create_guild_role_params {
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */
  enum discord_permissions_bitwise_flags permissions;

  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
  int color;

  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool hoist;

  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool mentionable;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};

// Modify Guild Role Positions
// defined at specs/discord/guild.endpoints-params.json:143:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-role-positions-json-params

 * - Initializer:
 *   - <tt>discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params*)</tt>
 *   - <tt>discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_guild_role_positions_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_positions_params**)</tt>
 *   - <tt>discord_modify_guild_role_positions_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_positions_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_guild_role_positions_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_positions_params*)</tt>
 *   - <tt>discord_modify_guild_role_positions_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_positions_params**)</tt>
 */
struct discord_modify_guild_role_positions_params {
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
  u64_snowflake_t id; ///< role

  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
  int position; ///< sorting position of the role

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Modify Guild Role
// defined at specs/discord/guild.endpoints-params.json:154:22
/**
 * @see https://discord.com/developers/docs/resources/guild#modify-guild-role-json-params

 * - Initializer:
 *   - <tt>discord_modify_guild_role_params_init(struct discord_modify_guild_role_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params*)</tt>
 *   - <tt>discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_guild_role_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_params**)</tt>
 *   - <tt>discord_modify_guild_role_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_role_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_guild_role_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_params*)</tt>
 *   - <tt>discord_modify_guild_role_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_role_params**)</tt>
 */
struct discord_modify_guild_role_params {
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
  char *name; ///< name of the role

  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
  enum discord_permissions_bitwise_flags permissions; ///< bitwise value of the enabled/disabled permissions

  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
  int color; ///< RGB color value

  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
  bool hoist; ///< whether the role should be displayed separately in the sidebar

  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
  bool mentionable; ///< whether the role should be mentionable

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};

// Get Guild Prune Count
// defined at specs/discord/guild.endpoints-params.json:168:22
/**
 * @see https://discord.com/developers/docs/resources/guild#get-guild-prune-count-query-string-params

 * - Initializer:
 *   - <tt>discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_get_guild_prune_count_params_cleanup(struct discord_get_guild_prune_count_params*)</tt>
 *   - <tt>discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_get_guild_prune_count_params_from_json(char *rbuf, size_t len, struct discord_get_guild_prune_count_params**)</tt>
 *   - <tt>discord_get_guild_prune_count_params_list_from_json(char *rbuf, size_t len, struct discord_get_guild_prune_count_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_get_guild_prune_count_params_to_json(char *wbuf, size_t len, struct discord_get_guild_prune_count_params*)</tt>
 *   - <tt>discord_get_guild_prune_count_params_list_to_json(char *wbuf, size_t len, struct discord_get_guild_prune_count_params**)</tt>
 */
struct discord_get_guild_prune_count_params {
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  int days;

  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **include_roles;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Begin Guild Prune
// defined at specs/discord/guild.endpoints-params.json:179:22
/**
 * @see https://discord.com/developers/docs/resources/guild#begin-guild-prune-json-params

 * - Initializer:
 *   - <tt>discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_begin_guild_prune_params_cleanup(struct discord_begin_guild_prune_params*)</tt>
 *   - <tt>discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_begin_guild_prune_params_from_json(char *rbuf, size_t len, struct discord_begin_guild_prune_params**)</tt>
 *   - <tt>discord_begin_guild_prune_params_list_from_json(char *rbuf, size_t len, struct discord_begin_guild_prune_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_begin_guild_prune_params_to_json(char *wbuf, size_t len, struct discord_begin_guild_prune_params*)</tt>
 *   - <tt>discord_begin_guild_prune_params_list_to_json(char *wbuf, size_t len, struct discord_begin_guild_prune_params**)</tt>
 */
struct discord_begin_guild_prune_params {
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  int days;

  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
  bool compute_prune_count;

  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  ja_u64 **include_roles;

  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  char *reason;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/guild.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/guild
 */


// Guild Structure
// defined at specs/discord/guild.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-guild-structure

 * - Initializer:
 *   - <tt>discord_guild_init(struct discord_guild*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_cleanup(struct discord_guild*)</tt>
 *   - <tt>discord_guild_list_free(struct discord_guild**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_from_json(char *rbuf, size_t len, struct discord_guild**)</tt>
 *   - <tt>discord_guild_list_from_json(char *rbuf, size_t len, struct discord_guild***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_to_json(char *wbuf, size_t len, struct discord_guild*)</tt>
 *   - <tt>discord_guild_list_to_json(char *wbuf, size_t len, struct discord_guild**)</tt>
 */
struct discord_guild {
  /* specs/discord/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:13:74
     '{"type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "name":"name"}' */
  char name[DISCORD_MAX_NAME_LEN];

  /* specs/discord/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}' */
  char *icon;

  /* specs/discord/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}' */
  char *icon_hash;

  /* specs/discord/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}' */
  char *splash;

  /* specs/discord/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}' */
  char *discovery_splash;

  /* specs/discord/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}' */
  bool owner;

  /* specs/discord/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}' */
  u64_snowflake_t owner_id;

  /* specs/discord/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}' */
  int permissions;

  /* specs/discord/guild.json:21:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}' */
  char region[MAX_REGION_LEN];

  /* specs/discord/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}' */
  u64_snowflake_t afk_channel_id;

  /* specs/discord/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}' */
  int afk_timeout;

  /* specs/discord/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}' */
  bool widget_enabled;

  /* specs/discord/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}' */
  u64_snowflake_t widget_channel_id;

  /* specs/discord/guild.json:26:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}' */
  enum discord_guild_verification_level verification_level;

  /* specs/discord/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}' */
  enum discord_guild_default_message_notification_level default_message_notifications;

  /* specs/discord/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}' */
  enum discord_guild_explicit_content_filter_level explicit_content_filter;

  /* specs/discord/guild.json:31:82
     '{"type":{"base":"struct discord_permissions_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}' */
  // @todo roles array of role objects;

  /* specs/discord/guild.json:33:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}' */
  struct discord_emoji **emojis;

  /* specs/discord/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true, 
              "comment":"array of guild feature strings"}' */
  // @todo features array of guild feature strings;

  /* specs/discord/guild.json:36:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}' */
  enum discord_guild_mfa_level mfa_level;

  /* specs/discord/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}' */
  u64_snowflake_t application_id;

  /* specs/discord/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}' */
  u64_snowflake_t system_channel_id;

  /* specs/discord/guild.json:39:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}' */
  enum discord_guild_system_channel_flags system_channel_flags;

  /* specs/discord/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}' */
  u64_snowflake_t rules_channel_id;

  /* specs/discord/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}' */
  u64_unix_ms_t joined_at;

  /* specs/discord/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}' */
  bool large;

  /* specs/discord/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}' */
  bool unavailable;

  /* specs/discord/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}' */
  int member_count;

  /* specs/discord/guild.json:45:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true, 
         "comment":"array of partial voice state objects"}' */
  // @todo voice_states array of partial voice state objects;

  /* specs/discord/guild.json:47:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}' */
  struct discord_guild_member **members;

  /* specs/discord/guild.json:48:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}' */
  struct discord_channel **channels; ///< array of channel objects

  /* specs/discord/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}' */
  // @todo presences array of partial presence update objects;

  /* specs/discord/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}' */
  int max_presences;

  /* specs/discord/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}' */
  int max_members;

  /* specs/discord/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}' */
  char *vanity_url;

  /* specs/discord/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}' */
  char *description;

  /* specs/discord/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}' */
  char *banner;

  /* specs/discord/guild.json:57:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}' */
  enum discord_guild_premium_tier premium_tier;

  /* specs/discord/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}' */
  int premium_subscription_count;

  /* specs/discord/guild.json:59:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}' */
  char preferred_locale[MAX_LOCALE_LEN];

  /* specs/discord/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}' */
  u64_snowflake_t public_updates_channel_id;

  /* specs/discord/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}' */
  int max_video_channel_users;

  /* specs/discord/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}' */
  int approximate_member_count;

  /* specs/discord/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}' */
  int approximate_presence_count;

  /* specs/discord/guild.json:65:84
     '{"type":{"base":"struct discord_guild_welcome_screen", "dec":"*"}, "name":"welcome_screen", "option":true}' */
  struct discord_guild_welcome_screen *welcome_screen;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[46];
    void *record_defined[46];
    void *record_null[46];
  } __M; // metadata
/// @endcond
};















// Unavailable Guild Object
// defined at specs/discord/guild.json:161:23
/**
 * @see https://discord.com/developers/docs/resources/guild#unavailable-guild-object

 * - Initializer:
 *   - <tt>discord_guild_unavailable_init(struct discord_guild_unavailable*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_unavailable_cleanup(struct discord_guild_unavailable*)</tt>
 *   - <tt>discord_guild_unavailable_list_free(struct discord_guild_unavailable**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_unavailable_from_json(char *rbuf, size_t len, struct discord_guild_unavailable**)</tt>
 *   - <tt>discord_guild_unavailable_list_from_json(char *rbuf, size_t len, struct discord_guild_unavailable***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_unavailable_to_json(char *wbuf, size_t len, struct discord_guild_unavailable*)</tt>
 *   - <tt>discord_guild_unavailable_list_to_json(char *wbuf, size_t len, struct discord_guild_unavailable**)</tt>
 */
struct discord_guild_unavailable {
  /* specs/discord/guild.json:163:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:164:18
     '{"name":"unavailable", "type":{"base":"bool"}}' */
  bool unavailable;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Guild Preview Object
// defined at specs/discord/guild.json:171:23
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-preview-object

 * - Initializer:
 *   - <tt>discord_guild_preview_init(struct discord_guild_preview*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_preview_cleanup(struct discord_guild_preview*)</tt>
 *   - <tt>discord_guild_preview_list_free(struct discord_guild_preview**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_preview_from_json(char *rbuf, size_t len, struct discord_guild_preview**)</tt>
 *   - <tt>discord_guild_preview_list_from_json(char *rbuf, size_t len, struct discord_guild_preview***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_preview_to_json(char *wbuf, size_t len, struct discord_guild_preview*)</tt>
 *   - <tt>discord_guild_preview_list_to_json(char *wbuf, size_t len, struct discord_guild_preview**)</tt>
 */
struct discord_guild_preview {
  /* specs/discord/guild.json:173:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:174:18
     '{"name":"name", "type":{"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
  char name[DISCORD_MAX_NAME_LEN];

  /* specs/discord/guild.json:175:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  char *icon;

  /* specs/discord/guild.json:176:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  char *splash;

  /* specs/discord/guild.json:177:18
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}' */
  char *discovery_splash;

  /* specs/discord/guild.json:178:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}' */
  struct discord_emoji **emojis;

  /* specs/discord/guild.json:179:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}' */
  // @todo features (null);

  /* specs/discord/guild.json:180:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}' */
  int approximate_member_count;

  /* specs/discord/guild.json:181:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}' */
  int approximate_presence_count;

  /* specs/discord/guild.json:182:18
     '{"name":"description", "type":{"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
  char description[DISCORD_MAX_DESCRIPTION_LEN];

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[10];
    void *record_defined[10];
    void *record_null[10];
  } __M; // metadata
/// @endcond
};

// Guild Widget Object
// defined at specs/discord/guild.json:189:23
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-widget-object

 * - Initializer:
 *   - <tt>discord_guild_widget_init(struct discord_guild_widget*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_widget_cleanup(struct discord_guild_widget*)</tt>
 *   - <tt>discord_guild_widget_list_free(struct discord_guild_widget**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_widget_from_json(char *rbuf, size_t len, struct discord_guild_widget**)</tt>
 *   - <tt>discord_guild_widget_list_from_json(char *rbuf, size_t len, struct discord_guild_widget***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_widget_to_json(char *wbuf, size_t len, struct discord_guild_widget*)</tt>
 *   - <tt>discord_guild_widget_list_to_json(char *wbuf, size_t len, struct discord_guild_widget**)</tt>
 */
struct discord_guild_widget {
  /* specs/discord/guild.json:191:18
     '{"name":"enabled", "type":{"base":"bool"}}' */
  bool enabled;

  /* specs/discord/guild.json:192:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}}' */
  u64_snowflake_t channel_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Guild Member Structure
// defined at specs/discord/guild.json:199:22
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-member-object

 * - Initializer:
 *   - <tt>discord_guild_member_init(struct discord_guild_member*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_member_cleanup(struct discord_guild_member*)</tt>
 *   - <tt>discord_guild_member_list_free(struct discord_guild_member**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_member_from_json(char *rbuf, size_t len, struct discord_guild_member**)</tt>
 *   - <tt>discord_guild_member_list_from_json(char *rbuf, size_t len, struct discord_guild_member***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_member_to_json(char *wbuf, size_t len, struct discord_guild_member*)</tt>
 *   - <tt>discord_guild_member_list_to_json(char *wbuf, size_t len, struct discord_guild_member**)</tt>
 */
struct discord_guild_member {
  /* specs/discord/guild.json:202:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  struct discord_user *user;

  /* specs/discord/guild.json:203:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}, "option":true}' */
  char nick[DISCORD_MAX_NAME_LEN];

  /* specs/discord/guild.json:204:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl"}, "comment":"array of role object ids"}' */
  ja_u64 **roles; ///< array of role object ids

  /* specs/discord/guild.json:205:20
     '{ "name": "joined_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t joined_at;

  /* specs/discord/guild.json:206:20
     '{ "name": "premium_since", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  u64_unix_ms_t premium_since;

  /* specs/discord/guild.json:207:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  bool deaf;

  /* specs/discord/guild.json:208:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  bool mute;

  /* specs/discord/guild.json:209:20
     '{ "name": "pending", "type":{ "base":"bool" }, "option":true}' */
  bool pending;

  /* specs/discord/guild.json:210:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*"}, "option":true}' */
  char *permissions;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};

// Integration Structure
// defined at specs/discord/guild.json:217:22
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-object-integration-structure

 * - Initializer:
 *   - <tt>discord_guild_integration_init(struct discord_guild_integration*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_integration_cleanup(struct discord_guild_integration*)</tt>
 *   - <tt>discord_guild_integration_list_free(struct discord_guild_integration**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_integration_from_json(char *rbuf, size_t len, struct discord_guild_integration**)</tt>
 *   - <tt>discord_guild_integration_list_from_json(char *rbuf, size_t len, struct discord_guild_integration***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_integration_to_json(char *wbuf, size_t len, struct discord_guild_integration*)</tt>
 *   - <tt>discord_guild_integration_list_to_json(char *wbuf, size_t len, struct discord_guild_integration**)</tt>
 */
struct discord_guild_integration {
  /* specs/discord/guild.json:220:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:221:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/guild.json:222:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  char *type;

  /* specs/discord/guild.json:223:20
     '{ "name": "enabled", "type":{ "base":"bool"}}' */
  bool enabled;

  /* specs/discord/guild.json:224:20
     '{ "name": "syncing", "type":{ "base":"bool"}}' */
  bool syncing;

  /* specs/discord/guild.json:225:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t role_id;

  /* specs/discord/guild.json:226:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}' */
  bool enable_emotions;

  /* specs/discord/guild.json:227:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}' */
  enum discord_guild_integration_expire_behaviors expire_behavior;

  /* specs/discord/guild.json:228:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}' */
  int expire_grace_period;

  /* specs/discord/guild.json:229:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}' */
  struct discord_user *user;

  /* specs/discord/guild.json:230:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}' */
  struct discord_guild_integration_account *account;

  /* specs/discord/guild.json:231:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  u64_unix_ms_t synced_at;

  /* specs/discord/guild.json:232:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}' */
  int subscriber_count;

  /* specs/discord/guild.json:233:20
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  bool revoked;

  /* specs/discord/guild.json:234:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}' */
  struct discord_guild_integration_application *application;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[15];
    void *record_defined[15];
    void *record_null[15];
  } __M; // metadata
/// @endcond
};



// Integration Account Structure
// defined at specs/discord/guild.json:251:22
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-account-object-integration-account-structure

 * - Initializer:
 *   - <tt>discord_guild_integration_account_init(struct discord_guild_integration_account*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_integration_account_cleanup(struct discord_guild_integration_account*)</tt>
 *   - <tt>discord_guild_integration_account_list_free(struct discord_guild_integration_account**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_integration_account_from_json(char *rbuf, size_t len, struct discord_guild_integration_account**)</tt>
 *   - <tt>discord_guild_integration_account_list_from_json(char *rbuf, size_t len, struct discord_guild_integration_account***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_integration_account_to_json(char *wbuf, size_t len, struct discord_guild_integration_account*)</tt>
 *   - <tt>discord_guild_integration_account_list_to_json(char *wbuf, size_t len, struct discord_guild_integration_account**)</tt>
 */
struct discord_guild_integration_account {
  /* specs/discord/guild.json:253:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:254:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Integration Application Object
// defined at specs/discord/guild.json:261:22
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-application-object-integration-application-structure

 * - Initializer:
 *   - <tt>discord_guild_integration_application_init(struct discord_guild_integration_application*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_integration_application_cleanup(struct discord_guild_integration_application*)</tt>
 *   - <tt>discord_guild_integration_application_list_free(struct discord_guild_integration_application**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_integration_application_from_json(char *rbuf, size_t len, struct discord_guild_integration_application**)</tt>
 *   - <tt>discord_guild_integration_application_list_from_json(char *rbuf, size_t len, struct discord_guild_integration_application***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_integration_application_to_json(char *wbuf, size_t len, struct discord_guild_integration_application*)</tt>
 *   - <tt>discord_guild_integration_application_list_to_json(char *wbuf, size_t len, struct discord_guild_integration_application**)</tt>
 */
struct discord_guild_integration_application {
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}' */
  char icon[MAX_SHA256_LEN];

  /* specs/discord/guild.json:266:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}' */
  char *description;

  /* specs/discord/guild.json:267:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}' */
  char *summary;

  /* specs/discord/guild.json:268:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}' */
  struct discord_user *bot;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};

// Ban Structure
// defined at specs/discord/guild.json:275:22
/**
 * @see https://discord.com/developers/docs/resources/guild#ban-object

 * - Initializer:
 *   - <tt>discord_guild_ban_init(struct discord_guild_ban*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_ban_cleanup(struct discord_guild_ban*)</tt>
 *   - <tt>discord_guild_ban_list_free(struct discord_guild_ban**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_ban_from_json(char *rbuf, size_t len, struct discord_guild_ban**)</tt>
 *   - <tt>discord_guild_ban_list_from_json(char *rbuf, size_t len, struct discord_guild_ban***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_ban_to_json(char *wbuf, size_t len, struct discord_guild_ban*)</tt>
 *   - <tt>discord_guild_ban_list_to_json(char *wbuf, size_t len, struct discord_guild_ban**)</tt>
 */
struct discord_guild_ban {
  /* specs/discord/guild.json:278:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[DISCORD_MAX_REASON_LEN]" }}' */
  char reason[DISCORD_MAX_REASON_LEN];

  /* specs/discord/guild.json:279:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  struct discord_user *user; ///< partial user object

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Welcome Screen Structure
// defined at specs/discord/guild.json:286:22
/**
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-structure

 * - Initializer:
 *   - <tt>discord_guild_welcome_screen_init(struct discord_guild_welcome_screen*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_welcome_screen_cleanup(struct discord_guild_welcome_screen*)</tt>
 *   - <tt>discord_guild_welcome_screen_list_free(struct discord_guild_welcome_screen**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_welcome_screen_from_json(char *rbuf, size_t len, struct discord_guild_welcome_screen**)</tt>
 *   - <tt>discord_guild_welcome_screen_list_from_json(char *rbuf, size_t len, struct discord_guild_welcome_screen***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_welcome_screen_to_json(char *wbuf, size_t len, struct discord_guild_welcome_screen*)</tt>
 *   - <tt>discord_guild_welcome_screen_list_to_json(char *wbuf, size_t len, struct discord_guild_welcome_screen**)</tt>
 */
struct discord_guild_welcome_screen {
  /* specs/discord/guild.json:289:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *description; ///< @todo fixed size limit

  /* specs/discord/guild.json:290:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_channel", "dec":"ntl" }, "todo":false }' */
  struct discord_guild_welcome_screen_channel **welcome_channels;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Welcome Screen Channel Structure
// defined at specs/discord/guild.json:297:22
/**
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure

 * - Initializer:
 *   - <tt>discord_guild_welcome_screen_channel_init(struct discord_guild_welcome_screen_channel*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_welcome_screen_channel_cleanup(struct discord_guild_welcome_screen_channel*)</tt>
 *   - <tt>discord_guild_welcome_screen_channel_list_free(struct discord_guild_welcome_screen_channel**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_welcome_screen_channel_from_json(char *rbuf, size_t len, struct discord_guild_welcome_screen_channel**)</tt>
 *   - <tt>discord_guild_welcome_screen_channel_list_from_json(char *rbuf, size_t len, struct discord_guild_welcome_screen_channel***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_welcome_screen_channel_to_json(char *wbuf, size_t len, struct discord_guild_welcome_screen_channel*)</tt>
 *   - <tt>discord_guild_welcome_screen_channel_list_to_json(char *wbuf, size_t len, struct discord_guild_welcome_screen_channel**)</tt>
 */
struct discord_guild_welcome_screen_channel {
  /* specs/discord/guild.json:300:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t channel_id;

  /* specs/discord/guild.json:301:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  char *description;

  /* specs/discord/guild.json:302:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t emoji_id;

  /* specs/discord/guild.json:303:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}' */
  char *emoji_name;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/invite
 */


// Get Invite
// defined at specs/discord/invite.endpoints-params.json:10:22
/**
 * @see https://discord.com/developers/docs/resources/invite#get-invite-query-string-params

 * - Initializer:
 *   - <tt>discord_get_invite_params_init(struct discord_get_invite_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_get_invite_params_cleanup(struct discord_get_invite_params*)</tt>
 *   - <tt>discord_get_invite_params_list_free(struct discord_get_invite_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_get_invite_params_from_json(char *rbuf, size_t len, struct discord_get_invite_params**)</tt>
 *   - <tt>discord_get_invite_params_list_from_json(char *rbuf, size_t len, struct discord_get_invite_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_get_invite_params_to_json(char *wbuf, size_t len, struct discord_get_invite_params*)</tt>
 *   - <tt>discord_get_invite_params_list_to_json(char *wbuf, size_t len, struct discord_get_invite_params**)</tt>
 */
struct discord_get_invite_params {
  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */
  bool with_counts; ///< whether the invite should contain approximate member counts

  /* specs/discord/invite.endpoints-params.json:14:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */
  bool with_expiration; ///< whether the invite should contain the expiration date

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/invite
 */




// Invite Structure
// defined at specs/discord/invite.json:19:22
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-object-invite-structure

 * - Initializer:
 *   - <tt>discord_invite_init(struct discord_invite*)</tt>
 * - Cleanup:
 *   - <tt>discord_invite_cleanup(struct discord_invite*)</tt>
 *   - <tt>discord_invite_list_free(struct discord_invite**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_invite_from_json(char *rbuf, size_t len, struct discord_invite**)</tt>
 *   - <tt>discord_invite_list_from_json(char *rbuf, size_t len, struct discord_invite***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_invite_to_json(char *wbuf, size_t len, struct discord_invite*)</tt>
 *   - <tt>discord_invite_list_to_json(char *wbuf, size_t len, struct discord_invite**)</tt>
 */
struct discord_invite {
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *code; ///< @todo fixed size limit

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  struct discord_guild *guild; ///< partial guild object

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  struct discord_channel *channel; ///< partial channel object

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  struct discord_user *inviter;

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  struct discord_user *target_user; ///< partial user object

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
  enum discord_invite_target_user_types target_user_type;

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
  int approximate_presence_count;

  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
  int approximate_member_count;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[8];
    void *record_defined[8];
    void *record_null[8];
  } __M; // metadata
/// @endcond
};

// Invite Metadata Structure
// defined at specs/discord/invite.json:36:22
/**
 * @see https://discord.com/developers/docs/resources/invite#invite-metadata-object

 * - Initializer:
 *   - <tt>discord_invite_metadata_init(struct discord_invite_metadata*)</tt>
 * - Cleanup:
 *   - <tt>discord_invite_metadata_cleanup(struct discord_invite_metadata*)</tt>
 *   - <tt>discord_invite_metadata_list_free(struct discord_invite_metadata**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_invite_metadata_from_json(char *rbuf, size_t len, struct discord_invite_metadata**)</tt>
 *   - <tt>discord_invite_metadata_list_from_json(char *rbuf, size_t len, struct discord_invite_metadata***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_invite_metadata_to_json(char *wbuf, size_t len, struct discord_invite_metadata*)</tt>
 *   - <tt>discord_invite_metadata_list_to_json(char *wbuf, size_t len, struct discord_invite_metadata**)</tt>
 */
struct discord_invite_metadata {
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
  int user;

  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  int max_uses;

  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  int max_age;

  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
  int temporary;

  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  u64_unix_ms_t created_at;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/message_components.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/interactions/message-components#message-components
 */


// Component Structure
// defined at specs/discord/message_components.json:9:22
/**
 * @see https://discord.com/developers/docs/interactions/message-components#component-object-component-structure

 * - Initializer:
 *   - <tt>discord_component_init(struct discord_component*)</tt>
 * - Cleanup:
 *   - <tt>discord_component_cleanup(struct discord_component*)</tt>
 *   - <tt>discord_component_list_free(struct discord_component**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_component_from_json(char *rbuf, size_t len, struct discord_component**)</tt>
 *   - <tt>discord_component_list_from_json(char *rbuf, size_t len, struct discord_component***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_component_to_json(char *wbuf, size_t len, struct discord_component*)</tt>
 *   - <tt>discord_component_list_to_json(char *wbuf, size_t len, struct discord_component**)</tt>
 */
struct discord_component {
  /* specs/discord/message_components.json:12:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment":"component type"}' */
  enum discord_component_types type; ///< component type

  /* specs/discord/message_components.json:13:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "inject_if_not":"", "comment":"a developer-defined identifier for the component, max 100 characters"}' */
  char custom_id[100+1]; ///< a developer-defined identifier for the component, max 100 characters

  /* specs/discord/message_components.json:14:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"whether the component is disabled, default false"}' */
  bool disabled; ///< whether the component is disabled, default false

  /* specs/discord/message_components.json:15:18
     '{"name":"style", "type":{"base":"int", "int_alias":"enum discord_button_styles"}, "option":true, "inject_if_not":0, "comment":"one of button styles"}' */
  enum discord_button_styles style; ///< one of button styles

  /* specs/discord/message_components.json:16:18
     '{"name":"label", "type":{"base":"char", "dec":"[80+1]"}, "option":true, "comment":"text that appears on the button, max 80 characters", "inject_if_not":""}' */
  char label[80+1]; ///< text that appears on the button, max 80 characters

  /* specs/discord/message_components.json:17:18
     '{"name":"emoji", "type":{"base":"struct discord_emoji", "dec":"*"}, "option":true, "comment":"name, id and animated", "inject_if_not":null}' */
  struct discord_emoji *emoji; ///< name, id and animated

  /* specs/discord/message_components.json:18:18
     '{"name":"url", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a url for link-style buttons", "inject_if_not":null}' */
  char *url; ///< a url for link-style buttons

  /* specs/discord/message_components.json:19:18
     '{"name":"options", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the choices in the select, max 25", "inject_if_not":null}' */
  struct discord_select_option **options; ///< the choices in the select, max 25

  /* specs/discord/message_components.json:20:18
     '{"name":"placeholder", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"custom placeholder text if nothing is selected, max 100 characters", "inject_if_not":""}' */
  char placeholder[100+1]; ///< custom placeholder text if nothing is selected, max 100 characters

  /* specs/discord/message_components.json:21:18
     '{"name":"min_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the minimum number of items that must be chosen; default 1, min 0, max 25"}' */
  int min_values; ///< the minimum number of items that must be chosen; default 1, min 0, max 25

  /* specs/discord/message_components.json:22:18
     '{"name":"max_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the maximum number of items that must be chosen; default 1, min 0, max 25"}' */
  int max_values; ///< the maximum number of items that must be chosen; default 1, min 0, max 25

  /* specs/discord/message_components.json:23:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"a list of child components", "inject_if_not":null}' */
  struct discord_component **components; ///< a list of child components

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[12];
    void *record_defined[12];
    void *record_null[12];
  } __M; // metadata
/// @endcond
};



// Button Structure
// defined at specs/discord/message_components.json:41:22
/**
 * @see https://discord.com/developers/docs/interactions/message-components#button-object-button-structure

 * - Initializer:
 *   - <tt>discord_button_init(struct discord_button*)</tt>
 * - Cleanup:
 *   - <tt>discord_button_cleanup(struct discord_button*)</tt>
 *   - <tt>discord_button_list_free(struct discord_button**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_button_from_json(char *rbuf, size_t len, struct discord_button**)</tt>
 *   - <tt>discord_button_list_from_json(char *rbuf, size_t len, struct discord_button***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_button_to_json(char *wbuf, size_t len, struct discord_button*)</tt>
 *   - <tt>discord_button_list_to_json(char *wbuf, size_t len, struct discord_button**)</tt>
 */
struct discord_button {
  /* specs/discord/message_components.json:44:18
     '{"name":"type", "type": {"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment": "2 for a button"}' */
  enum discord_component_types type; ///< 2 for a button

  /* specs/discord/message_components.json:45:18
     '{"name":"style", "type": {"base":"int", "int_alias":"enum discord_button_styles"}, "inject_if_not":0, "comment": "one of button styles"}' */
  enum discord_button_styles style; ///< one of button styles

  /* specs/discord/message_components.json:46:18
     '{"name":"label", "type":{"base":"char", "dec":"[80+1]"}, "option":true, "comment":"text that appears on the button, max 80 characters", "inject_if_not":""}' */
  char label[80+1]; ///< text that appears on the button, max 80 characters

  /* specs/discord/message_components.json:47:18
     '{"name":"emoji", "type":{ "base":"struct discord_emoji", "dec":"*" }, "option":true, "comment":"name, id and animated", "inject_if_not":null}' */
  struct discord_emoji *emoji; ///< name, id and animated

  /* specs/discord/message_components.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"a developer-defined identifier for the component, max 100 characters", "inject_if_not":""}' */
  char custom_id[100+1]; ///< a developer-defined identifier for the component, max 100 characters

  /* specs/discord/message_components.json:49:18
     '{"name":"url", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a url for link-style buttons", "inject_if_not":null}' */
  char *url; ///< a url for link-style buttons

  /* specs/discord/message_components.json:50:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"whether the component is disabled, default false"}' */
  bool disabled; ///< whether the component is disabled, default false

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};



// Select Menu Structure
// defined at specs/discord/message_components.json:70:22
/**
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-menu-structure

 * - Initializer:
 *   - <tt>discord_select_menu_init(struct discord_select_menu*)</tt>
 * - Cleanup:
 *   - <tt>discord_select_menu_cleanup(struct discord_select_menu*)</tt>
 *   - <tt>discord_select_menu_list_free(struct discord_select_menu**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_select_menu_from_json(char *rbuf, size_t len, struct discord_select_menu**)</tt>
 *   - <tt>discord_select_menu_list_from_json(char *rbuf, size_t len, struct discord_select_menu***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_select_menu_to_json(char *wbuf, size_t len, struct discord_select_menu*)</tt>
 *   - <tt>discord_select_menu_list_to_json(char *wbuf, size_t len, struct discord_select_menu**)</tt>
 */
struct discord_select_menu {
  /* specs/discord/message_components.json:73:18
     '{"name":"type", "type": {"base":"int", "int_alias":"enum discord_component_types"}, "inject_if_not":0, "comment": "3 for a select menu"}' */
  enum discord_component_types type; ///< 3 for a select menu

  /* specs/discord/message_components.json:74:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters", "inject_if_not":""}' */
  char custom_id[100+1]; ///< a developer-defined identifier for the component, max 100 characters

  /* specs/discord/message_components.json:75:18
     '{"name":"options", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "comment":"the choices in the select, max 25"}' */
  struct discord_select_option **options; ///< the choices in the select, max 25

  /* specs/discord/message_components.json:76:18
     '{"name":"placeholder", "type":{"base":"char", "dec":"[100+1]"}, "option":true, "comment":"custom placeholder text if nothing is selected, max 100 characters", "inject_if_not":""}' */
  char placeholder[100+1]; ///< custom placeholder text if nothing is selected, max 100 characters

  /* specs/discord/message_components.json:77:18
     '{"name":"min_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the minimum number of items that must be chosen; default 1, min 0, max 25"}' */
  int min_values; ///< the minimum number of items that must be chosen; default 1, min 0, max 25

  /* specs/discord/message_components.json:78:18
     '{"name":"max_values", "type":{"base":"int"}, "option":true, "inject_if_not":0, "comment":"the maximum number of items that must be chosen; default 1, min 0, max 25"}' */
  int max_values; ///< the maximum number of items that must be chosen; default 1, min 0, max 25

  /* specs/discord/message_components.json:79:18
     '{"name":"disabled", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"disable the select, default false"}' */
  bool disabled; ///< disable the select, default false

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};

// Select Option Structure
// defined at specs/discord/message_components.json:85:22
/**
 * @see https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-option-structure

 * - Initializer:
 *   - <tt>discord_select_option_init(struct discord_select_option*)</tt>
 * - Cleanup:
 *   - <tt>discord_select_option_cleanup(struct discord_select_option*)</tt>
 *   - <tt>discord_select_option_list_free(struct discord_select_option**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_select_option_from_json(char *rbuf, size_t len, struct discord_select_option**)</tt>
 *   - <tt>discord_select_option_list_from_json(char *rbuf, size_t len, struct discord_select_option***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_select_option_to_json(char *wbuf, size_t len, struct discord_select_option*)</tt>
 *   - <tt>discord_select_option_list_to_json(char *wbuf, size_t len, struct discord_select_option**)</tt>
 */
struct discord_select_option {
  /* specs/discord/message_components.json:88:18
     '{"name":"label", "type":{"base":"char", "dec":"[25+1]"}, "inject_if_not":"", "comment":"the user-facing name of the option, max 25 characters"}' */
  char label[25+1]; ///< the user-facing name of the option, max 25 characters

  /* specs/discord/message_components.json:89:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "inject_if_not":"", "comment":"the dev define value of the option, max 100 characters"}' */
  char value[100+1]; ///< the dev define value of the option, max 100 characters

  /* specs/discord/message_components.json:90:18
     '{"name":"description", "type":{"base":"char", "dec":"[50+1]"}, "inject_if_not":"", "option":true, "comment":"a additional description of the option, max 50 characters"}' */
  char description[50+1]; ///< a additional description of the option, max 50 characters

  /* specs/discord/message_components.json:91:18
     '{"name":"emoji", "type":{"base":"struct discord_emoji", "dec":"*"}, "inject_if_not":null, "option":true, "comment":"name, id and animated"}' */
  struct discord_emoji *emoji; ///< name, id and animated

  /* specs/discord/message_components.json:92:18
     '{"name":"Default", "json_key":"default", "type":{"base":"bool"}, "option":true, "comment":"will render this option as selected by default"}' */
  bool Default; ///< will render this option as selected by default

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/topics/permissions
 */




// Role Structure
// defined at specs/discord/permissions.json:49:22
/**
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-structure

 * - Initializer:
 *   - <tt>discord_permissions_role_init(struct discord_permissions_role*)</tt>
 * - Cleanup:
 *   - <tt>discord_permissions_role_cleanup(struct discord_permissions_role*)</tt>
 *   - <tt>discord_permissions_role_list_free(struct discord_permissions_role**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_permissions_role_from_json(char *rbuf, size_t len, struct discord_permissions_role**)</tt>
 *   - <tt>discord_permissions_role_list_from_json(char *rbuf, size_t len, struct discord_permissions_role***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_permissions_role_to_json(char *wbuf, size_t len, struct discord_permissions_role*)</tt>
 *   - <tt>discord_permissions_role_list_to_json(char *wbuf, size_t len, struct discord_permissions_role**)</tt>
 */
struct discord_permissions_role {
  /* specs/discord/permissions.json:52:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/permissions.json:53:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_MAX_NAME_LEN]" }}' */
  char name[DISCORD_MAX_NAME_LEN];

  /* specs/discord/permissions.json:54:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  int color;

  /* specs/discord/permissions.json:55:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  bool hoist;

  /* specs/discord/permissions.json:56:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  int position;

  /* specs/discord/permissions.json:57:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}' */
  char *permissions;

  /* specs/discord/permissions.json:58:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  bool managed;

  /* specs/discord/permissions.json:59:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  bool mentionable;

  /* specs/discord/permissions.json:60:20
     '{ "name": "tags", "type":{"base":"struct discord_permissions_role_tags", "dec":"*"}}' */
  struct discord_permissions_role_tags *tags;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};

// Role Tags Structure
// defined at specs/discord/permissions.json:67:22
/**
 * @see https://discord.com/developers/docs/topics/permissions#role-object-role-tags-structure

 * - Initializer:
 *   - <tt>discord_permissions_role_tags_init(struct discord_permissions_role_tags*)</tt>
 * - Cleanup:
 *   - <tt>discord_permissions_role_tags_cleanup(struct discord_permissions_role_tags*)</tt>
 *   - <tt>discord_permissions_role_tags_list_free(struct discord_permissions_role_tags**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_permissions_role_tags_from_json(char *rbuf, size_t len, struct discord_permissions_role_tags**)</tt>
 *   - <tt>discord_permissions_role_tags_list_from_json(char *rbuf, size_t len, struct discord_permissions_role_tags***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_permissions_role_tags_to_json(char *wbuf, size_t len, struct discord_permissions_role_tags*)</tt>
 *   - <tt>discord_permissions_role_tags_list_to_json(char *wbuf, size_t len, struct discord_permissions_role_tags**)</tt>
 */
struct discord_permissions_role_tags {
  /* specs/discord/permissions.json:70:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t bot_id;

  /* specs/discord/permissions.json:71:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t integration_id;

  /* specs/discord/permissions.json:72:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  int premium_subscriber;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/slash_commands.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/interactions/slash-commands#data-models-and-types
 */


// Application Command Structure
// defined at specs/discord/slash_commands.json:9:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-structure

 * - Initializer:
 *   - <tt>discord_application_command_init(struct discord_application_command*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_cleanup(struct discord_application_command*)</tt>
 *   - <tt>discord_application_command_list_free(struct discord_application_command**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_from_json(char *rbuf, size_t len, struct discord_application_command**)</tt>
 *   - <tt>discord_application_command_list_from_json(char *rbuf, size_t len, struct discord_application_command***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_to_json(char *wbuf, size_t len, struct discord_application_command*)</tt>
 *   - <tt>discord_application_command_list_to_json(char *wbuf, size_t len, struct discord_application_command**)</tt>
 */
struct discord_application_command {
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  u64_snowflake_t id; ///< unique id of the command

  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  u64_snowflake_t application_id; ///< unique id of the parent application

  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */
  u64_snowflake_t guild_id; ///< unique id of the command, if not global

  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  char name[32+1]; ///< 1-32 lowercase character

  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  char description[100+1]; ///< 1-100 character description

  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */
  struct discord_application_command_option **options; ///< the parameters for the command

  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  bool default_permission; ///< whether the command is enabled by default when the app is added to a guild

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
/// @endcond
};

// Application Command Option Structure
// defined at specs/discord/slash_commands.json:25:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-option-structure

 * - Initializer:
 *   - <tt>discord_application_command_option_init(struct discord_application_command_option*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_option_cleanup(struct discord_application_command_option*)</tt>
 *   - <tt>discord_application_command_option_list_free(struct discord_application_command_option**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_option_from_json(char *rbuf, size_t len, struct discord_application_command_option**)</tt>
 *   - <tt>discord_application_command_option_list_from_json(char *rbuf, size_t len, struct discord_application_command_option***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_option_to_json(char *wbuf, size_t len, struct discord_application_command_option*)</tt>
 *   - <tt>discord_application_command_option_list_to_json(char *wbuf, size_t len, struct discord_application_command_option**)</tt>
 */
struct discord_application_command_option {
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  enum discord_application_command_option_types type; ///< value of application command option type

  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  char name[32+1]; ///< 1-32 lowercase character

  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  char description[100+1]; ///< 1-100 character description

  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */
  bool required; ///< if the paramter is required or optional -- default false

  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  struct discord_application_command_option_choice **choices; ///< choices for string and int types for the user to pick from

  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  struct discord_application_command_option **options; ///< if the option is a subcommand or subcommand group type, this nested options will be the parameters

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};



// Application Command Option Choice Structure
// defined at specs/discord/slash_commands.json:58:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-object-application-command-option-choice-structure

 * - Initializer:
 *   - <tt>discord_application_command_option_choice_init(struct discord_application_command_option_choice*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_option_choice_cleanup(struct discord_application_command_option_choice*)</tt>
 *   - <tt>discord_application_command_option_choice_list_free(struct discord_application_command_option_choice**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_option_choice_from_json(char *rbuf, size_t len, struct discord_application_command_option_choice**)</tt>
 *   - <tt>discord_application_command_option_choice_list_from_json(char *rbuf, size_t len, struct discord_application_command_option_choice***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_option_choice_to_json(char *wbuf, size_t len, struct discord_application_command_option_choice*)</tt>
 *   - <tt>discord_application_command_option_choice_list_to_json(char *wbuf, size_t len, struct discord_application_command_option_choice**)</tt>
 */
struct discord_application_command_option_choice {
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
  char name[100+1]; ///< 1-100 character choice name

  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */
  char value[100+1]; ///< value of choice, up to 100 characters

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Guild Application Command Permissions Structure
// defined at specs/discord/slash_commands.json:69:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-permissions-object-guild-application-command-permissions-structure

 * - Initializer:
 *   - <tt>discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions*)</tt>
 * - Cleanup:
 *   - <tt>discord_guild_application_command_permissions_cleanup(struct discord_guild_application_command_permissions*)</tt>
 *   - <tt>discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_guild_application_command_permissions_from_json(char *rbuf, size_t len, struct discord_guild_application_command_permissions**)</tt>
 *   - <tt>discord_guild_application_command_permissions_list_from_json(char *rbuf, size_t len, struct discord_guild_application_command_permissions***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_guild_application_command_permissions_to_json(char *wbuf, size_t len, struct discord_guild_application_command_permissions*)</tt>
 *   - <tt>discord_guild_application_command_permissions_list_to_json(char *wbuf, size_t len, struct discord_guild_application_command_permissions**)</tt>
 */
struct discord_guild_application_command_permissions {
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  u64_snowflake_t id; ///< the id of the command

  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  u64_snowflake_t application_id; ///< the id of the parent application the command belongs to

  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  u64_snowflake_t guild_id; ///< the id of the guild

  /* specs/discord/slash_commands.json:75:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  struct discord_application_command_permissions **permissions; ///< the permissions for the command in the guild

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Application Command Permissions Structure
// defined at specs/discord/slash_commands.json:82:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#application-command-permissions-object-guild-application-command-permissions-structure

 * - Initializer:
 *   - <tt>discord_application_command_permissions_init(struct discord_application_command_permissions*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_permissions_cleanup(struct discord_application_command_permissions*)</tt>
 *   - <tt>discord_application_command_permissions_list_free(struct discord_application_command_permissions**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_permissions_from_json(char *rbuf, size_t len, struct discord_application_command_permissions**)</tt>
 *   - <tt>discord_application_command_permissions_list_from_json(char *rbuf, size_t len, struct discord_application_command_permissions***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_permissions_to_json(char *wbuf, size_t len, struct discord_application_command_permissions*)</tt>
 *   - <tt>discord_application_command_permissions_list_to_json(char *wbuf, size_t len, struct discord_application_command_permissions**)</tt>
 */
struct discord_application_command_permissions {
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  u64_snowflake_t id; ///< the id of the command

  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  enum discord_application_command_permission_types type; ///< role or user

  /* specs/discord/slash_commands.json:87:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  bool permission; ///< true to allow, false, to disallow

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};



// Interaction Structure
// defined at specs/discord/slash_commands.json:104:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-interaction-structure

 * - Initializer:
 *   - <tt>discord_interaction_init(struct discord_interaction*)</tt>
 * - Cleanup:
 *   - <tt>discord_interaction_cleanup(struct discord_interaction*)</tt>
 *   - <tt>discord_interaction_list_free(struct discord_interaction**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_interaction_from_json(char *rbuf, size_t len, struct discord_interaction**)</tt>
 *   - <tt>discord_interaction_list_from_json(char *rbuf, size_t len, struct discord_interaction***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_interaction_to_json(char *wbuf, size_t len, struct discord_interaction*)</tt>
 *   - <tt>discord_interaction_list_to_json(char *wbuf, size_t len, struct discord_interaction**)</tt>
 */
struct discord_interaction {
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  u64_snowflake_t id; ///< id of the interaction

  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
  u64_snowflake_t application_id; ///< id of the application this iteraction is for

  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
  enum discord_interaction_request_types type; ///< the request type of the interaction

  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  struct discord_application_command_interaction_data *data; ///< the command data payload

  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
  u64_snowflake_t guild_id; ///< the guild it was sent from

  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
  u64_snowflake_t channel_id; ///< the channel it was sent from

  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  struct discord_guild_member *member; ///< guild member data for the invoking user, including permissions

  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  struct discord_user *user; ///< user object for the invoking user, if invoked in a DM

  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
  char *token; ///< a continuation token for responding to the interaction

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};



// Application Command Interaction Data Structure
// defined at specs/discord/slash_commands.json:134:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-structure

 * - Initializer:
 *   - <tt>discord_application_command_interaction_data_init(struct discord_application_command_interaction_data*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_interaction_data_cleanup(struct discord_application_command_interaction_data*)</tt>
 *   - <tt>discord_application_command_interaction_data_list_free(struct discord_application_command_interaction_data**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_interaction_data_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data**)</tt>
 *   - <tt>discord_application_command_interaction_data_list_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_interaction_data_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data*)</tt>
 *   - <tt>discord_application_command_interaction_data_list_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data**)</tt>
 */
struct discord_application_command_interaction_data {
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
  u64_snowflake_t id; ///< the ID of the invoked command

  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
  char *name; ///< the name of the invoked command

  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_resolved *resolved; ///< converted users + roles + channels

  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_option **options; ///< the params + values from the user

  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */
  char custom_id[100+1]; ///< a developer-defined identifier for the component, max 100 characters

  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */
  enum discord_component_types type; ///< component type

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};

// Application Command Interaction Data Resolved Structure
// defined at specs/discord/slash_commands.json:149:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-resolved-structure

 * - Initializer:
 *   - <tt>discord_application_command_interaction_data_resolved_init(struct discord_application_command_interaction_data_resolved*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_interaction_data_resolved_cleanup(struct discord_application_command_interaction_data_resolved*)</tt>
 *   - <tt>discord_application_command_interaction_data_resolved_list_free(struct discord_application_command_interaction_data_resolved**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_interaction_data_resolved_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_resolved**)</tt>
 *   - <tt>discord_application_command_interaction_data_resolved_list_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_resolved***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_interaction_data_resolved_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_resolved*)</tt>
 *   - <tt>discord_application_command_interaction_data_resolved_list_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_resolved**)</tt>
 */
struct discord_application_command_interaction_data_resolved {
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
  ja_str **users; ///< the ids and User objects

  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
  ja_str **members; ///< the ids and partial Member objects

  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
  ja_str **roles; ///< the ids and Role objects

  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
  ja_str **channels; ///< the ids and partial Channel objects

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Application Command Interaction Data Option Structure
// defined at specs/discord/slash_commands.json:162:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-object-application-command-interaction-data-option-structure

 * - Initializer:
 *   - <tt>discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option*)</tt>
 * - Cleanup:
 *   - <tt>discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option*)</tt>
 *   - <tt>discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_application_command_interaction_data_option_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_option**)</tt>
 *   - <tt>discord_application_command_interaction_data_option_list_from_json(char *rbuf, size_t len, struct discord_application_command_interaction_data_option***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_application_command_interaction_data_option_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_option*)</tt>
 *   - <tt>discord_application_command_interaction_data_option_list_to_json(char *wbuf, size_t len, struct discord_application_command_interaction_data_option**)</tt>
 */
struct discord_application_command_interaction_data_option {
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  char *name; ///< the name of the parameter

  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  enum discord_application_command_option_types type; ///< value of application command option type

  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */
  enum discord_application_command_option_types value; ///< the value of the pair

  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  struct discord_application_command_interaction_data_option **options; ///< present if this option is a group or subcommand

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};

// Interaction Response Structure
// defined at specs/discord/slash_commands.json:175:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-response-object-interaction-response-structure

 * - Initializer:
 *   - <tt>discord_interaction_response_init(struct discord_interaction_response*)</tt>
 * - Cleanup:
 *   - <tt>discord_interaction_response_cleanup(struct discord_interaction_response*)</tt>
 *   - <tt>discord_interaction_response_list_free(struct discord_interaction_response**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_interaction_response_from_json(char *rbuf, size_t len, struct discord_interaction_response**)</tt>
 *   - <tt>discord_interaction_response_list_from_json(char *rbuf, size_t len, struct discord_interaction_response***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_interaction_response_to_json(char *wbuf, size_t len, struct discord_interaction_response*)</tt>
 *   - <tt>discord_interaction_response_list_to_json(char *wbuf, size_t len, struct discord_interaction_response**)</tt>
 */
struct discord_interaction_response {
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
  enum discord_interaction_callback_types type; ///< the type of response

  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  struct discord_interaction_application_command_callback_data *data; ///< an optional response message

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};



// Interaction Application Command Callback Data Structure
// defined at specs/discord/slash_commands.json:200:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#interaction-response-object-interaction-application-command-callback-data-structure

 * - Initializer:
 *   - <tt>discord_interaction_application_command_callback_data_init(struct discord_interaction_application_command_callback_data*)</tt>
 * - Cleanup:
 *   - <tt>discord_interaction_application_command_callback_data_cleanup(struct discord_interaction_application_command_callback_data*)</tt>
 *   - <tt>discord_interaction_application_command_callback_data_list_free(struct discord_interaction_application_command_callback_data**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_interaction_application_command_callback_data_from_json(char *rbuf, size_t len, struct discord_interaction_application_command_callback_data**)</tt>
 *   - <tt>discord_interaction_application_command_callback_data_list_from_json(char *rbuf, size_t len, struct discord_interaction_application_command_callback_data***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_interaction_application_command_callback_data_to_json(char *wbuf, size_t len, struct discord_interaction_application_command_callback_data*)</tt>
 *   - <tt>discord_interaction_application_command_callback_data_list_to_json(char *wbuf, size_t len, struct discord_interaction_application_command_callback_data**)</tt>
 */
struct discord_interaction_application_command_callback_data {
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
  bool tts; ///< is the response TTS

  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
  char *content; ///< message content

  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
  struct discord_embed **embeds; ///< support up to 10 embeds

  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  // @todo allowed_mentions allowed mentions object;

  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
  enum discord_interaction_application_command_callback_data_flags flags; ///< interaction application command callback data flags

  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
  struct discord_component **components; ///< message components

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};



// Message Interaction Structure
// defined at specs/discord/slash_commands.json:225:22
/**
 * @see https://discord.com/developers/docs/interactions/slash-commands#message-interaction-object-message-interaction-structure

 * - Initializer:
 *   - <tt>discord_message_interaction_init(struct discord_message_interaction*)</tt>
 * - Cleanup:
 *   - <tt>discord_message_interaction_cleanup(struct discord_message_interaction*)</tt>
 *   - <tt>discord_message_interaction_list_free(struct discord_message_interaction**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_message_interaction_from_json(char *rbuf, size_t len, struct discord_message_interaction**)</tt>
 *   - <tt>discord_message_interaction_list_from_json(char *rbuf, size_t len, struct discord_message_interaction***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_message_interaction_to_json(char *wbuf, size_t len, struct discord_message_interaction*)</tt>
 *   - <tt>discord_message_interaction_list_to_json(char *wbuf, size_t len, struct discord_message_interaction**)</tt>
 */
struct discord_message_interaction {
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  u64_snowflake_t id; ///< id of the interaction

  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
  enum discord_interaction_request_types type; ///< the request type of the interaction

  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
  char *name; ///< the name of the application command

  /* specs/discord/slash_commands.json:231:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
  struct discord_user *user; ///< the user who invoked the interaction

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/user
 */


// Modify Current User
// defined at specs/discord/user.endpoints-params.json:10:22
/**
 * @see https://discord.com/developers/docs/resources/user#modify-current-user-json-params

 * - Initializer:
 *   - <tt>discord_modify_current_user_params_init(struct discord_modify_current_user_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_current_user_params_cleanup(struct discord_modify_current_user_params*)</tt>
 *   - <tt>discord_modify_current_user_params_list_free(struct discord_modify_current_user_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_current_user_params_from_json(char *rbuf, size_t len, struct discord_modify_current_user_params**)</tt>
 *   - <tt>discord_modify_current_user_params_list_from_json(char *rbuf, size_t len, struct discord_modify_current_user_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_current_user_params_to_json(char *wbuf, size_t len, struct discord_modify_current_user_params*)</tt>
 *   - <tt>discord_modify_current_user_params_list_to_json(char *wbuf, size_t len, struct discord_modify_current_user_params**)</tt>
 */
struct discord_modify_current_user_params {
  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
  char *username;

  /* specs/discord/user.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
  char *avatar; ///< base64 encoded image data

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Create Group DM
// defined at specs/discord/user.endpoints-params.json:21:22
/**
 * @see https://discord.com/developers/docs/resources/user#create-group-dm-json-params

 * - Initializer:
 *   - <tt>discord_create_group_dm_params_init(struct discord_create_group_dm_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_group_dm_params_cleanup(struct discord_create_group_dm_params*)</tt>
 *   - <tt>discord_create_group_dm_params_list_free(struct discord_create_group_dm_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_group_dm_params_from_json(char *rbuf, size_t len, struct discord_create_group_dm_params**)</tt>
 *   - <tt>discord_create_group_dm_params_list_from_json(char *rbuf, size_t len, struct discord_create_group_dm_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_group_dm_params_to_json(char *wbuf, size_t len, struct discord_create_group_dm_params*)</tt>
 *   - <tt>discord_create_group_dm_params_list_to_json(char *wbuf, size_t len, struct discord_create_group_dm_params**)</tt>
 */
struct discord_create_group_dm_params {
  /* specs/discord/user.endpoints-params.json:24:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
  ja_str **access_tokens; ///< access tokens of users that have granted your app the gdm.join scope

  /* specs/discord/user.endpoints-params.json:26:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"ia dictionary of user ids to their respective nicknames"}' */
  ja_u64 **nicks; ///< ia dictionary of user ids to their respective nicknames

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/user.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/user
 */






// User Structure
// defined at specs/discord/user.json:42:28
/**
 * - Initializer:
 *   - <tt>discord_user_init(struct discord_user*)</tt>
 * - Cleanup:
 *   - <tt>discord_user_cleanup(struct discord_user*)</tt>
 *   - <tt>discord_user_list_free(struct discord_user**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_user_from_json(char *rbuf, size_t len, struct discord_user**)</tt>
 *   - <tt>discord_user_list_from_json(char *rbuf, size_t len, struct discord_user***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_user_to_json(char *wbuf, size_t len, struct discord_user*)</tt>
 *   - <tt>discord_user_list_to_json(char *wbuf, size_t len, struct discord_user**)</tt>
 */
struct discord_user {
  /* specs/discord/user.json:45:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  u64_snowflake_t id;

  /* specs/discord/user.json:46:24
     '{ "name": "username", "type":{ "base":"char", "dec":"[DISCORD_MAX_USERNAME_LEN]"}}' */
  char username[DISCORD_MAX_USERNAME_LEN];

  /* specs/discord/user.json:47:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[DISCORD_MAX_DISCRIMINATOR_LEN]" }}' */
  char discriminator[DISCORD_MAX_DISCRIMINATOR_LEN];

  /* specs/discord/user.json:48:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}' */
  char avatar[MAX_SHA256_LEN];

  /* specs/discord/user.json:49:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
  bool bot;

  /* specs/discord/user.json:50:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
  bool System;

  /* specs/discord/user.json:51:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
  bool mfa_enabled;

  /* specs/discord/user.json:52:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}' */
  char locale[MAX_LOCALE_LEN];

  /* specs/discord/user.json:53:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  bool verified;

  /* specs/discord/user.json:54:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}' */
  char email[MAX_EMAIL_LEN];

  /* specs/discord/user.json:55:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  enum discord_user_flags flags;

  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
  enum discord_user_premium_types premium_type;

  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  enum discord_user_flags public_flags;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[13];
    void *record_defined[13];
    void *record_null[13];
  } __M; // metadata
/// @endcond
};



// Connection Structure
// defined at specs/discord/user.json:74:28
/**
 * @see https://discord.com/developers/docs/resources/user#connection-object-connection-structure

 * - Initializer:
 *   - <tt>discord_connection_init(struct discord_connection*)</tt>
 * - Cleanup:
 *   - <tt>discord_connection_cleanup(struct discord_connection*)</tt>
 *   - <tt>discord_connection_list_free(struct discord_connection**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_connection_from_json(char *rbuf, size_t len, struct discord_connection**)</tt>
 *   - <tt>discord_connection_list_from_json(char *rbuf, size_t len, struct discord_connection***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_connection_to_json(char *wbuf, size_t len, struct discord_connection*)</tt>
 *   - <tt>discord_connection_list_to_json(char *wbuf, size_t len, struct discord_connection**)</tt>
 */
struct discord_connection {
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *id; ///< @todo fixed size limit

  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  char *type;

  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  bool revoked;

  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}}' */
  struct discord_guild_integration **integrations;

  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  bool verified;

  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
  bool friend_sync;

  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
  bool show_activity;

  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}' */
  enum discord_user_connection_visibility_types visibility;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/topics/voice-connections
 */







/* This file is generated from specs/discord/voice.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/voice
 */


// Voice State Structure
// defined at specs/discord/voice.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/voice#voice-state-object-voice-state-structure

 * - Initializer:
 *   - <tt>discord_voice_state_init(struct discord_voice_state*)</tt>
 * - Cleanup:
 *   - <tt>discord_voice_state_cleanup(struct discord_voice_state*)</tt>
 *   - <tt>discord_voice_state_list_free(struct discord_voice_state**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_voice_state_from_json(char *rbuf, size_t len, struct discord_voice_state**)</tt>
 *   - <tt>discord_voice_state_list_from_json(char *rbuf, size_t len, struct discord_voice_state***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_voice_state_to_json(char *wbuf, size_t len, struct discord_voice_state*)</tt>
 *   - <tt>discord_voice_state_list_to_json(char *wbuf, size_t len, struct discord_voice_state**)</tt>
 */
struct discord_voice_state {
  /* specs/discord/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t guild_id;

  /* specs/discord/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  u64_snowflake_t channel_id;

  /* specs/discord/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t user_id;

  /* specs/discord/voice.json:15:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
  struct discord_guild_member *member;

  /* specs/discord/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
  char *session_id;

  /* specs/discord/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  bool deaf;

  /* specs/discord/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  bool mute;

  /* specs/discord/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
  bool self_deaf;

  /* specs/discord/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
  bool self_mute;

  /* specs/discord/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
  bool self_stream;

  /* specs/discord/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
  bool self_video;

  /* specs/discord/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
  bool supress;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[12];
    void *record_defined[12];
    void *record_null[12];
  } __M; // metadata
/// @endcond
};

// Voice Region Structure
// defined at specs/discord/voice.json:29:22
/**
 * @see https://discord.com/developers/docs/resources/voice#voice-region-object-voice-region-structure

 * - Initializer:
 *   - <tt>discord_voice_region_init(struct discord_voice_region*)</tt>
 * - Cleanup:
 *   - <tt>discord_voice_region_cleanup(struct discord_voice_region*)</tt>
 *   - <tt>discord_voice_region_list_free(struct discord_voice_region**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_voice_region_from_json(char *rbuf, size_t len, struct discord_voice_region**)</tt>
 *   - <tt>discord_voice_region_list_from_json(char *rbuf, size_t len, struct discord_voice_region***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_voice_region_to_json(char *wbuf, size_t len, struct discord_voice_region*)</tt>
 *   - <tt>discord_voice_region_list_to_json(char *wbuf, size_t len, struct discord_voice_region**)</tt>
 */
struct discord_voice_region {
  /* specs/discord/voice.json:32:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }' */
  char *id; ///< @todo fixed size limit

  /* specs/discord/voice.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }' */
  char *name; ///< @todo fixed size limit

  /* specs/discord/voice.json:34:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
  bool vip;

  /* specs/discord/voice.json:35:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
  bool optimal;

  /* specs/discord/voice.json:36:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
  bool deprecated;

  /* specs/discord/voice.json:37:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
  bool custom;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/webhook
 */


// Create Webhook
// defined at specs/discord/webhook.endpoints-params.json:10:22
/**
 * @see https://discord.com/developers/docs/resources/webhook#create-webhook

 * - Initializer:
 *   - <tt>discord_create_webhook_params_init(struct discord_create_webhook_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_create_webhook_params_cleanup(struct discord_create_webhook_params*)</tt>
 *   - <tt>discord_create_webhook_params_list_free(struct discord_create_webhook_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_create_webhook_params_from_json(char *rbuf, size_t len, struct discord_create_webhook_params**)</tt>
 *   - <tt>discord_create_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_create_webhook_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_create_webhook_params_to_json(char *wbuf, size_t len, struct discord_create_webhook_params*)</tt>
 *   - <tt>discord_create_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_create_webhook_params**)</tt>
 */
struct discord_create_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  char *name; ///< name of the webhook(1-80) chars

  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; ///< base64 image for the default webhook avatar

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};

// Modify Webhook
// defined at specs/discord/webhook.endpoints-params.json:21:22
/**
 * @see https://discord.com/developers/docs/resources/webhook#modify-webhook

 * - Initializer:
 *   - <tt>discord_modify_webhook_params_init(struct discord_modify_webhook_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params*)</tt>
 *   - <tt>discord_modify_webhook_params_list_free(struct discord_modify_webhook_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_modify_webhook_params_from_json(char *rbuf, size_t len, struct discord_modify_webhook_params**)</tt>
 *   - <tt>discord_modify_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_modify_webhook_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_modify_webhook_params_to_json(char *wbuf, size_t len, struct discord_modify_webhook_params*)</tt>
 *   - <tt>discord_modify_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_modify_webhook_params**)</tt>
 */
struct discord_modify_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  char *name; ///< name of the webhook(1-80) chars

  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  char *avatar; ///< base64 image for the default webhook avatar

  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
  u64_snowflake_t channel_id; ///< the new channel id this webhook should be moved to

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};

// Execute Webhook
// defined at specs/discord/webhook.endpoints-params.json:33:22
/**
 * @see https://discord.com/developers/docs/resources/webhook#execute-webhook

 * - Initializer:
 *   - <tt>discord_execute_webhook_params_init(struct discord_execute_webhook_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params*)</tt>
 *   - <tt>discord_execute_webhook_params_list_free(struct discord_execute_webhook_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_execute_webhook_params_from_json(char *rbuf, size_t len, struct discord_execute_webhook_params**)</tt>
 *   - <tt>discord_execute_webhook_params_list_from_json(char *rbuf, size_t len, struct discord_execute_webhook_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_execute_webhook_params_to_json(char *wbuf, size_t len, struct discord_execute_webhook_params*)</tt>
 *   - <tt>discord_execute_webhook_params_list_to_json(char *wbuf, size_t len, struct discord_execute_webhook_params**)</tt>
 */
struct discord_execute_webhook_params {
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
  bool wait; ///< cannot unescape an ill-formed-string 	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that i

  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
  char *content; ///< the message contents (up to 2000 characters)

  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
  char *username; ///< override the default username of the webhook

  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
  char *avatar_url; ///< override the default avatar of the webhook

  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
  bool tts; ///< true if this is a TTS message

  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
  char *file; ///< the contents of the file being sent

  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
  struct discord_embed *embeds; ///< embedded rich content

  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
  char *payload_json; ///< See message create

  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
  struct discord_channel_allowed_mentions *allowed_mentions; ///< allowed mentions for the message

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};

// Edit Webhook Message
// defined at specs/discord/webhook.endpoints-params.json:78:22
/**
 * @see https://discord.com/developers/docs/resources/webhook#edit-webhook-message

 * - Initializer:
 *   - <tt>discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params*)</tt>
 * - Cleanup:
 *   - <tt>discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params*)</tt>
 *   - <tt>discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_edit_webhook_message_params_from_json(char *rbuf, size_t len, struct discord_edit_webhook_message_params**)</tt>
 *   - <tt>discord_edit_webhook_message_params_list_from_json(char *rbuf, size_t len, struct discord_edit_webhook_message_params***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_edit_webhook_message_params_to_json(char *wbuf, size_t len, struct discord_edit_webhook_message_params*)</tt>
 *   - <tt>discord_edit_webhook_message_params_list_to_json(char *wbuf, size_t len, struct discord_edit_webhook_message_params**)</tt>
 */
struct discord_edit_webhook_message_params {
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
  char *content; ///< name of the webhook(1-2000) chars

  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
  struct discord_embed **embeds; ///< array of up to 10 embeds objects

  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
  struct discord_channel_allowed_mentions *allowed_mentions; ///< allowed mentions for the message

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/discord/webhook.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_structs.h
 * @see https://discord.com/developers/docs/resources/webhook
 */


// Webhook Structure
// defined at specs/discord/webhook.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure

 * - Initializer:
 *   - <tt>discord_webhook_init(struct discord_webhook*)</tt>
 * - Cleanup:
 *   - <tt>discord_webhook_cleanup(struct discord_webhook*)</tt>
 *   - <tt>discord_webhook_list_free(struct discord_webhook**)</tt>
 * - JSON Decoder:
 *   - <tt>discord_webhook_from_json(char *rbuf, size_t len, struct discord_webhook**)</tt>
 *   - <tt>discord_webhook_list_from_json(char *rbuf, size_t len, struct discord_webhook***)</tt>
 * - JSON Encoder:
 *   - <tt>discord_webhook_to_json(char *wbuf, size_t len, struct discord_webhook*)</tt>
 *   - <tt>discord_webhook_list_to_json(char *wbuf, size_t len, struct discord_webhook**)</tt>
 */
struct discord_webhook {
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}' */
  enum discord_webhook_types type;

  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t guild_id;

  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t channel_id;

  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  struct discord_user *user;

  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[DISCORD_WEBHOOK_NAME_LEN]" }}' */
  char name[DISCORD_WEBHOOK_NAME_LEN];

  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *avatar; ///< @todo fixed size limit

  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  char *token; ///< @todo fixed size limit

  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t application_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
  } __M; // metadata
/// @endcond
};


