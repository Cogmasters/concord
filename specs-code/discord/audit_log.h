/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/**
 * @file specs-code/discord/audit_log.h
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
 *   - <tt>discord_audit_log_to_json(char *wbuf, size_t len, struct discord_audit_log *p)</tt>
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
extern void discord_audit_log_cleanup_v(void *p);
extern void discord_audit_log_cleanup(struct discord_audit_log *p);
extern void discord_audit_log_init_v(void *p);
extern void discord_audit_log_init(struct discord_audit_log *p);
extern void discord_audit_log_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_from_json(char *json, size_t len, struct discord_audit_log **pp);
extern size_t discord_audit_log_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_to_json(char *json, size_t len, struct discord_audit_log *p);
extern size_t discord_audit_log_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_to_query(char *json, size_t len, struct discord_audit_log *p);
extern void discord_audit_log_list_free_v(void **p);
extern void discord_audit_log_list_free(struct discord_audit_log **p);
extern void discord_audit_log_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_list_from_json(char *str, size_t len, struct discord_audit_log ***p);
extern size_t discord_audit_log_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_list_to_json(char *str, size_t len, struct discord_audit_log **p);


enum discord_audit_log_events {
  DISCORD_AUDIT_LOG_GUILD_UPDATE = 1,
  DISCORD_AUDIT_LOG_CHANNEL_CREATE = 10,
  DISCORD_AUDIT_LOG_CHANNEL_UPDATE = 11,
  DISCORD_AUDIT_LOG_CHANNEL_DELETE = 12,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_CREATE = 13,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_UPDATE = 14,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_DELETE = 15,
  DISCORD_AUDIT_LOG_MEMBER_KICK = 20,
  DISCORD_AUDIT_LOG_MEMBER_PRUNE = 21,
  DISCORD_AUDIT_LOG_MEMBER_BAN_ADD = 22,
  DISCORD_AUDIT_LOG_MEMBER_BAN_REMOVE = 23,
  DISCORD_AUDIT_LOG_MEMBER_UPDATE = 24,
  DISCORD_AUDIT_LOG_MEMBER_ROLE_UPDATE = 25,
  DISCORD_AUDIT_LOG_MEMBER_MOVE = 26,
  DISCORD_AUDIT_LOG_MEMBER_DISCONNECT = 27,
  DISCORD_AUDIT_LOG_BOT_ADD = 28,
  DISCORD_AUDIT_LOG_ROLE_CREATE = 30,
  DISCORD_AUDIT_LOG_ROLE_UPDATE = 31,
  DISCORD_AUDIT_LOG_ROLE_DELETE = 32,
  DISCORD_AUDIT_LOG_INVITE_CREATE = 40,
  DISCORD_AUDIT_LOG_INVITE_DELETE = 42,
  DISCORD_AUDIT_LOG_WEBHOOK_CREATE = 50,
  DISCORD_AUDIT_LOG_WEBHOOK_UPDATE = 51,
  DISCORD_AUDIT_LOG_WEBHOOK_DELETE = 52,
  DISCORD_AUDIT_LOG_EMOJI_CREATE = 60,
  DISCORD_AUDIT_LOG_EMOJI_UPDATE = 61,
  DISCORD_AUDIT_LOG_EMOJI_DELETE = 62,
  DISCORD_AUDIT_LOG_MESSAGE_DELETE = 72,
  DISCORD_AUDIT_LOG_MESSAGE_BULK_DELETE = 73,
  DISCORD_AUDIT_LOG_MESSAGE_PIN = 74,
  DISCORD_AUDIT_LOG_MESSAGE_UNPIN = 75,
  DISCORD_AUDIT_LOG_INTEGRATION_CREATE = 80,
  DISCORD_AUDIT_LOG_INTEGRATION_UPDATE = 81,
  DISCORD_AUDIT_LOG_INTEGRATION_DELETE = 82,
};
extern char* discord_audit_log_events_to_string(enum discord_audit_log_events);
extern enum discord_audit_log_events discord_audit_log_events_from_string(char*);
extern bool discord_audit_log_events_has(enum discord_audit_log_events, char*);

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
 *   - <tt>discord_audit_log_entry_to_json(char *wbuf, size_t len, struct discord_audit_log_entry *p)</tt>
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
extern void discord_audit_log_entry_cleanup_v(void *p);
extern void discord_audit_log_entry_cleanup(struct discord_audit_log_entry *p);
extern void discord_audit_log_entry_init_v(void *p);
extern void discord_audit_log_entry_init(struct discord_audit_log_entry *p);
extern void discord_audit_log_entry_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_entry_from_json(char *json, size_t len, struct discord_audit_log_entry **pp);
extern size_t discord_audit_log_entry_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_to_json(char *json, size_t len, struct discord_audit_log_entry *p);
extern size_t discord_audit_log_entry_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_to_query(char *json, size_t len, struct discord_audit_log_entry *p);
extern void discord_audit_log_entry_list_free_v(void **p);
extern void discord_audit_log_entry_list_free(struct discord_audit_log_entry **p);
extern void discord_audit_log_entry_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_entry_list_from_json(char *str, size_t len, struct discord_audit_log_entry ***p);
extern size_t discord_audit_log_entry_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_entry_list_to_json(char *str, size_t len, struct discord_audit_log_entry **p);

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
 *   - <tt>discord_audit_log_entry_optional_info_to_json(char *wbuf, size_t len, struct discord_audit_log_entry_optional_info *p)</tt>
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
extern void discord_audit_log_entry_optional_info_cleanup_v(void *p);
extern void discord_audit_log_entry_optional_info_cleanup(struct discord_audit_log_entry_optional_info *p);
extern void discord_audit_log_entry_optional_info_init_v(void *p);
extern void discord_audit_log_entry_optional_info_init(struct discord_audit_log_entry_optional_info *p);
extern void discord_audit_log_entry_optional_info_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_entry_optional_info_from_json(char *json, size_t len, struct discord_audit_log_entry_optional_info **pp);
extern size_t discord_audit_log_entry_optional_info_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_to_json(char *json, size_t len, struct discord_audit_log_entry_optional_info *p);
extern size_t discord_audit_log_entry_optional_info_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_to_query(char *json, size_t len, struct discord_audit_log_entry_optional_info *p);
extern void discord_audit_log_entry_optional_info_list_free_v(void **p);
extern void discord_audit_log_entry_optional_info_list_free(struct discord_audit_log_entry_optional_info **p);
extern void discord_audit_log_entry_optional_info_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_entry_optional_info_list_from_json(char *str, size_t len, struct discord_audit_log_entry_optional_info ***p);
extern size_t discord_audit_log_entry_optional_info_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_list_to_json(char *str, size_t len, struct discord_audit_log_entry_optional_info **p);

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
 *   - <tt>discord_audit_log_change_to_json(char *wbuf, size_t len, struct discord_audit_log_change *p)</tt>
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
extern void discord_audit_log_change_cleanup_v(void *p);
extern void discord_audit_log_change_cleanup(struct discord_audit_log_change *p);
extern void discord_audit_log_change_init_v(void *p);
extern void discord_audit_log_change_init(struct discord_audit_log_change *p);
extern void discord_audit_log_change_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_change_from_json(char *json, size_t len, struct discord_audit_log_change **pp);
extern size_t discord_audit_log_change_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_to_json(char *json, size_t len, struct discord_audit_log_change *p);
extern size_t discord_audit_log_change_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_to_query(char *json, size_t len, struct discord_audit_log_change *p);
extern void discord_audit_log_change_list_free_v(void **p);
extern void discord_audit_log_change_list_free(struct discord_audit_log_change **p);
extern void discord_audit_log_change_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_list_from_json(char *str, size_t len, struct discord_audit_log_change ***p);
extern size_t discord_audit_log_change_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_list_to_json(char *str, size_t len, struct discord_audit_log_change **p);

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
 *   - <tt>discord_audit_log_change_key_to_json(char *wbuf, size_t len, struct discord_audit_log_change_key *p)</tt>
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
extern void discord_audit_log_change_key_cleanup_v(void *p);
extern void discord_audit_log_change_key_cleanup(struct discord_audit_log_change_key *p);
extern void discord_audit_log_change_key_init_v(void *p);
extern void discord_audit_log_change_key_init(struct discord_audit_log_change_key *p);
extern void discord_audit_log_change_key_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_change_key_from_json(char *json, size_t len, struct discord_audit_log_change_key **pp);
extern size_t discord_audit_log_change_key_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_key_to_json(char *json, size_t len, struct discord_audit_log_change_key *p);
extern size_t discord_audit_log_change_key_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_key_to_query(char *json, size_t len, struct discord_audit_log_change_key *p);
extern void discord_audit_log_change_key_list_free_v(void **p);
extern void discord_audit_log_change_key_list_free(struct discord_audit_log_change_key **p);
extern void discord_audit_log_change_key_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_key_list_from_json(char *str, size_t len, struct discord_audit_log_change_key ***p);
extern size_t discord_audit_log_change_key_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_key_list_to_json(char *str, size_t len, struct discord_audit_log_change_key **p);
