/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/**
 * @file specs-code/discord/audit_log.h
 * @see https://discord.com/developers/docs/resources/audit-log
 */


// Audit Log Structure
// defined at specs/discord/audit_log.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_audit_log_init(struct discord_audit_log *)`
 *   * Cleanup:

 *     * :code:`void discord_audit_log_cleanup(struct discord_audit_log *)`
 *     * :code:`void discord_audit_log_list_free(struct discord_audit_log **)`
 *   * JSON Decoder:

 *     * :code:`void discord_audit_log_from_json(char *rbuf, size_t len, struct discord_audit_log **)`
 *     * :code:`void discord_audit_log_list_from_json(char *rbuf, size_t len, struct discord_audit_log ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_audit_log_to_json(char *wbuf, size_t len, struct discord_audit_log *)`
 *     * :code:`void discord_audit_log_list_to_json(char *wbuf, size_t len, struct discord_audit_log **)`
 * @endverbatim
 */
struct discord_audit_log {
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
  struct discord_webhook **webhooks; ///< list of webhooks found in the audit log

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
  struct discord_user **users; ///< list of users found in the audit log

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
  struct discord_audit_log_entry **audit_log_entries; ///< list of audit log entries

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
  struct discord_guild_integration **integrations; ///< list of partial integration objects

  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
  struct discord_channel **threads; ///< list of threads found in the audit log

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
extern void discord_audit_log_cleanup_v(void *p);
extern void discord_audit_log_cleanup(struct discord_audit_log *p);
extern void discord_audit_log_init_v(void *p);
extern void discord_audit_log_init(struct discord_audit_log *p);
extern void discord_audit_log_from_json_v(char *json, size_t len, void *pp);
extern void discord_audit_log_from_json(char *json, size_t len, struct discord_audit_log **pp);
extern size_t discord_audit_log_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_to_json(char *json, size_t len, struct discord_audit_log *p);
extern void discord_audit_log_list_free_v(void **p);
extern void discord_audit_log_list_free(struct discord_audit_log **p);
extern void discord_audit_log_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_list_from_json(char *str, size_t len, struct discord_audit_log ***p);
extern size_t discord_audit_log_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_list_to_json(char *str, size_t len, struct discord_audit_log **p);

// Audit Log Entry Structure
// defined at specs/discord/audit_log.json:23:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-entry-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_audit_log_entry_init(struct discord_audit_log_entry *)`
 *   * Cleanup:

 *     * :code:`void discord_audit_log_entry_cleanup(struct discord_audit_log_entry *)`
 *     * :code:`void discord_audit_log_entry_list_free(struct discord_audit_log_entry **)`
 *   * JSON Decoder:

 *     * :code:`void discord_audit_log_entry_from_json(char *rbuf, size_t len, struct discord_audit_log_entry **)`
 *     * :code:`void discord_audit_log_entry_list_from_json(char *rbuf, size_t len, struct discord_audit_log_entry ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_audit_log_entry_to_json(char *wbuf, size_t len, struct discord_audit_log_entry *)`
 *     * :code:`void discord_audit_log_entry_list_to_json(char *wbuf, size_t len, struct discord_audit_log_entry **)`
 * @endverbatim
 */
struct discord_audit_log_entry {
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
  char *target_id; ///< id of the affected entity (webhook,user,role,etc.)

  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
  struct discord_audit_log_change **changes; ///< changes made to the target_id

  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
  u64_snowflake_t user_id; ///< the user who made the changes

  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
  u64_snowflake_t id; ///< id of the entry

  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
  int action_type; ///< type of action that occured

  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
  struct discord_optional_audit_entry_info **options; ///< additional info for certain action types

  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}, "comment":"the reason for the change", "inject_if_not":"" }' */
  char reason[DISCORD_MAX_REASON_LEN]; ///< the reason for the change

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
extern void discord_audit_log_entry_list_free_v(void **p);
extern void discord_audit_log_entry_list_free(struct discord_audit_log_entry **p);
extern void discord_audit_log_entry_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_entry_list_from_json(char *str, size_t len, struct discord_audit_log_entry ***p);
extern size_t discord_audit_log_entry_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_entry_list_to_json(char *str, size_t len, struct discord_audit_log_entry **p);


// Audit Log Events
// defined at specs/discord/audit_log.json:35:5
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-events
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_audit_log_events_print(enum discord_audit_log_events code)`
 *   * :code:`enum discord_audit_log_events discord_audit_log_events_eval(char *code_as_str)`
 * @endverbatim
 */
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
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_CREATE = 83,
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_UPDATE = 84,
  DISCORD_AUDIT_LOG_STAGE_INSTANCE_DELETE = 85,
  DISCORD_AUDIT_LOG_STICKER_CREATE = 90,
  DISCORD_AUDIT_LOG_STICKER_UPDATE = 91,
  DISCORD_AUDIT_LOG_STICKER_DELETE = 92,
  DISCORD_AUDIT_LOG_THREAD_CREATE = 110,
  DISCORD_AUDIT_LOG_THREAD_UPDATE = 111,
  DISCORD_AUDIT_LOG_THREAD_DELETE = 112,
};
extern char* discord_audit_log_events_print(enum discord_audit_log_events);
extern enum discord_audit_log_events discord_audit_log_events_eval(char*);
extern void discord_audit_log_events_list_free_v(void **p);
extern void discord_audit_log_events_list_free(enum discord_audit_log_events **p);
extern void discord_audit_log_events_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_events_list_from_json(char *str, size_t len, enum discord_audit_log_events ***p);
extern size_t discord_audit_log_events_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_events_list_to_json(char *str, size_t len, enum discord_audit_log_events **p);

// Optional Audit Entry Info Structure
// defined at specs/discord/audit_log.json:91:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-optional-audit-entry-info
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_optional_audit_entry_info_init(struct discord_optional_audit_entry_info *)`
 *   * Cleanup:

 *     * :code:`void discord_optional_audit_entry_info_cleanup(struct discord_optional_audit_entry_info *)`
 *     * :code:`void discord_optional_audit_entry_info_list_free(struct discord_optional_audit_entry_info **)`
 *   * JSON Decoder:

 *     * :code:`void discord_optional_audit_entry_info_from_json(char *rbuf, size_t len, struct discord_optional_audit_entry_info **)`
 *     * :code:`void discord_optional_audit_entry_info_list_from_json(char *rbuf, size_t len, struct discord_optional_audit_entry_info ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_optional_audit_entry_info_to_json(char *wbuf, size_t len, struct discord_optional_audit_entry_info *)`
 *     * :code:`void discord_optional_audit_entry_info_list_to_json(char *wbuf, size_t len, struct discord_optional_audit_entry_info **)`
 * @endverbatim
 */
struct discord_optional_audit_entry_info {
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
  char *delete_member_days; ///< number of days after which inactive members were kicked

  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
  char *members_removed; ///< number of members removed by the prune

  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
  u64_snowflake_t channel_id; ///< channel in which the entities were targeted

  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
  u64_snowflake_t message_id; ///< id of the message that was targeted

  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
  char *count; ///< number of entities that were targeted

  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
  u64_snowflake_t id; ///< id of the ovewritten entity

  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
  char *type; ///< type of overwritten entity - '0' for role or '1' for member

  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
  char *role_name; ///< name of the role if type is '0' (not present if type is '1')

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
extern void discord_optional_audit_entry_info_cleanup_v(void *p);
extern void discord_optional_audit_entry_info_cleanup(struct discord_optional_audit_entry_info *p);
extern void discord_optional_audit_entry_info_init_v(void *p);
extern void discord_optional_audit_entry_info_init(struct discord_optional_audit_entry_info *p);
extern void discord_optional_audit_entry_info_from_json_v(char *json, size_t len, void *pp);
extern void discord_optional_audit_entry_info_from_json(char *json, size_t len, struct discord_optional_audit_entry_info **pp);
extern size_t discord_optional_audit_entry_info_to_json_v(char *json, size_t len, void *p);
extern size_t discord_optional_audit_entry_info_to_json(char *json, size_t len, struct discord_optional_audit_entry_info *p);
extern void discord_optional_audit_entry_info_list_free_v(void **p);
extern void discord_optional_audit_entry_info_list_free(struct discord_optional_audit_entry_info **p);
extern void discord_optional_audit_entry_info_list_from_json_v(char *str, size_t len, void *p);
extern void discord_optional_audit_entry_info_list_from_json(char *str, size_t len, struct discord_optional_audit_entry_info ***p);
extern size_t discord_optional_audit_entry_info_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_optional_audit_entry_info_list_to_json(char *str, size_t len, struct discord_optional_audit_entry_info **p);

// Audit Log Change Structure
// defined at specs/discord/audit_log.json:108:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_audit_log_change_init(struct discord_audit_log_change *)`
 *   * Cleanup:

 *     * :code:`void discord_audit_log_change_cleanup(struct discord_audit_log_change *)`
 *     * :code:`void discord_audit_log_change_list_free(struct discord_audit_log_change **)`
 *   * JSON Decoder:

 *     * :code:`void discord_audit_log_change_from_json(char *rbuf, size_t len, struct discord_audit_log_change **)`
 *     * :code:`void discord_audit_log_change_list_from_json(char *rbuf, size_t len, struct discord_audit_log_change ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_audit_log_change_to_json(char *wbuf, size_t len, struct discord_audit_log_change *)`
 *     * :code:`void discord_audit_log_change_list_to_json(char *wbuf, size_t len, struct discord_audit_log_change **)`
 * @endverbatim
 */
struct discord_audit_log_change {
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}, "comment":"new value of the key", "inject_if_not":null }' */
  char *new_value; ///< new value of the key

  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}, "comment":"old value of the key", "inject_if_not":null }' */
  char *old_value; ///< old value of the key

  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
  char *key; ///< name of audit log change key

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
extern void discord_audit_log_change_list_free_v(void **p);
extern void discord_audit_log_change_list_free(struct discord_audit_log_change **p);
extern void discord_audit_log_change_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_list_from_json(char *str, size_t len, struct discord_audit_log_change ***p);
extern size_t discord_audit_log_change_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_list_to_json(char *str, size_t len, struct discord_audit_log_change **p);

// Audit Log Change Key
// defined at specs/discord/audit_log.json:120:22
/**
 * @see https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-key
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_audit_log_change_key_init(struct discord_audit_log_change_key *)`
 *   * Cleanup:

 *     * :code:`void discord_audit_log_change_key_cleanup(struct discord_audit_log_change_key *)`
 *     * :code:`void discord_audit_log_change_key_list_free(struct discord_audit_log_change_key **)`
 *   * JSON Decoder:

 *     * :code:`void discord_audit_log_change_key_from_json(char *rbuf, size_t len, struct discord_audit_log_change_key **)`
 *     * :code:`void discord_audit_log_change_key_list_from_json(char *rbuf, size_t len, struct discord_audit_log_change_key ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_audit_log_change_key_to_json(char *wbuf, size_t len, struct discord_audit_log_change_key *)`
 *     * :code:`void discord_audit_log_change_key_list_to_json(char *wbuf, size_t len, struct discord_audit_log_change_key **)`
 * @endverbatim
 */
struct discord_audit_log_change_key {
  /* specs/discord/audit_log.json:123:18
     '{"name":"name", "type": {"base":"char", "dec":"*"}, "comment":"name changed", "inject_if_not":null }' */
  char *name; ///< name changed

  /* specs/discord/audit_log.json:124:18
     '{"name":"description", "type": {"base":"char", "dec":"*"}, "comment":"description changed", "inject_if_not":null }' */
  char *description; ///< description changed

  /* specs/discord/audit_log.json:125:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"icon changed", "inject_if_not":"" }' */
  char icon_hash[ORCA_LIMITS_SHA256]; ///< icon changed

  /* specs/discord/audit_log.json:126:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"invite splash page artwork changed", "inject_if_not":"" }' */
  char splash_hash[ORCA_LIMITS_SHA256]; ///< invite splash page artwork changed

  /* specs/discord/audit_log.json:127:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"discovery splash changed", "inject_if_not":"" }' */
  char discovery_splash_hash[ORCA_LIMITS_SHA256]; ///< discovery splash changed

  /* specs/discord/audit_log.json:128:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"guild banned changed", "inject_if_not":"" }' */
  char banner_hash[ORCA_LIMITS_SHA256]; ///< guild banned changed

  /* specs/discord/audit_log.json:129:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"owner changed", "inject_if_not":0 }' */
  u64_snowflake_t owner_id; ///< owner changed

  /* specs/discord/audit_log.json:130:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "comment":"region changed", "inject_if_not":"" }' */
  char region[ORCA_LIMITS_REGION]; ///< region changed

  /* specs/discord/audit_log.json:131:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "comment":"preferred locale changed", "inject_if_not":"" }' */
  char preferred_locale[ORCA_LIMITS_LOCALE]; ///< preferred locale changed

  /* specs/discord/audit_log.json:132:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"afk channel changed", "inject_if_not":0 }' */
  u64_snowflake_t afk_channel_id; ///< afk channel changed

  /* specs/discord/audit_log.json:133:18
     '{"name":"afk_timeout", "type": {"base":"int"}, "comment":"afk timeout duration changed", "inject_if_not":0 }' */
  int afk_timeout; ///< afk timeout duration changed

  /* specs/discord/audit_log.json:134:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the rules channel changed", "inject_if_not":0 }' */
  u64_snowflake_t rules_channel_id; ///< id of the rules channel changed

  /* specs/discord/audit_log.json:135:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the public updates channel changed", "inject_if_not":0 }' */
  u64_snowflake_t public_updates_channel_id; ///< id of the public updates channel changed

  /* specs/discord/audit_log.json:136:18
     '{"name":"mfa_level", "type": {"base":"int"}, "comment":"two-factor auth requirement changed", "inject_if_not":0 }' */
  int mfa_level; ///< two-factor auth requirement changed

  /* specs/discord/audit_log.json:137:18
     '{"name":"verification_level", "type": {"base":"int"}, "comment":"required verification level changed", "inject_if_not":0 }' */
  int verification_level; ///< required verification level changed

  /* specs/discord/audit_log.json:138:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}, "comment":"change in whose messages are scanned and deleted for explicit content in the server", "inject_if_not":0 }' */
  int explicit_content_filter; ///< change in whose messages are scanned and deleted for explicit content in the server

  /* specs/discord/audit_log.json:139:18
     '{"name":"default_message_notifications", "type": {"base":"int"}, "comment":"default message notification level changed", "inject_if_not":0 }' */
  int default_message_notifications; ///< default message notification level changed

  /* specs/discord/audit_log.json:140:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}, "comment":"guild invite vanity url changed", "inject_if_not":null }' */
  char *vanity_url_code; ///< guild invite vanity url changed

  /* specs/discord/audit_log.json:141:18
     '{"name":"add", "json_key":"$add", "type": {"base":"struct discord_permissions_role", "dec":"ntl" }, "comment":"new role added", "inject_if_not":null }' */
  struct discord_permissions_role **add; ///< new role added

  /* specs/discord/audit_log.json:142:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"struct discord_permissions_role", "dec":"ntl"}, "comment":"role removed", "inject_if_not":null }' */
  struct discord_permissions_role **remove; ///< role removed

  /* specs/discord/audit_log.json:143:18
     '{"name":"prune_delete_days", "type": {"base":"int"}, "comment":"change in number of days after which inactive and role-unassigned members are kicked", "inject_if_not":0 }' */
  int prune_delete_days; ///< change in number of days after which inactive and role-unassigned members are kicked

  /* specs/discord/audit_log.json:144:18
     '{"name":"widget_enabled", "type": {"base":"bool"}, "comment":"server widget enabled/disable"}' */
  bool widget_enabled; ///< server widget enabled/disable

  /* specs/discord/audit_log.json:145:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel id of the server widget changed", "inject_if_not":0 }' */
  u64_snowflake_t widget_channel_id; ///< channel id of the server widget changed

  /* specs/discord/audit_log.json:146:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the system channel changed", "inject_if_not":0 }' */
  u64_snowflake_t system_channel_id; ///< id of the system channel changed

  /* specs/discord/audit_log.json:147:18
     '{"name":"position", "type": {"base":"int"}, "comment":"text or voice channel position changed"}' */
  int position; ///< text or voice channel position changed

  /* specs/discord/audit_log.json:148:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}, "comment":"text or voice chanenl position changed", "inject_if_not":null }' */
  char *topic; ///< text or voice chanenl position changed

  /* specs/discord/audit_log.json:149:18
     '{"name":"bitrate", "type": {"base":"int"}, "comment":"voice channel bitrate changed" }' */
  int bitrate; ///< voice channel bitrate changed

  /* specs/discord/audit_log.json:150:18
     '{"name":"permission_overwrites", "type": {"base":"struct discord_channel_overwrite", "dec":"ntl"}, "comment":"permissions on a channel changed" }' */
  struct discord_channel_overwrite **permission_overwrites; ///< permissions on a channel changed

  /* specs/discord/audit_log.json:151:18
     '{"name":"nsfw", "type": {"base":"bool"}, "comment":"channel nsfw restriction changed" }' */
  bool nsfw; ///< channel nsfw restriction changed

  /* specs/discord/audit_log.json:152:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"application id of the added or removed webhook or bot", "inject_if_not":0 }' */
  u64_snowflake_t application_id; ///< application id of the added or removed webhook or bot

  /* specs/discord/audit_log.json:153:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}, "comment":"amount of seconds a user has to wait before sending another message changed" }' */
  int rate_limit_per_user; ///< amount of seconds a user has to wait before sending another message changed

  /* specs/discord/audit_log.json:154:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}, "comment":"permissions for a role changed" }' */
  char *permissions; ///< permissions for a role changed

  /* specs/discord/audit_log.json:155:18
     '{"name":"color", "type": {"base":"int"}, "comment":"role color changed" }' */
  int color; ///< role color changed

  /* specs/discord/audit_log.json:156:18
     '{"name":"hoist", "type": {"base":"bool"}, "comment":"role is now diplayed/no longer displayed separate from online users" }' */
  bool hoist; ///< role is now diplayed/no longer displayed separate from online users

  /* specs/discord/audit_log.json:157:18
     '{"name":"mentionable", "type": {"base":"bool"}, "comment":"role is now mentionable/unmentionable" }' */
  bool mentionable; ///< role is now mentionable/unmentionable

  /* specs/discord/audit_log.json:158:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was allowed for a role" }' */
  char *allow; ///< a permission on a text or voice channel was allowed for a role

  /* specs/discord/audit_log.json:159:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was denied for a role" }' */
  char *deny; ///< a permission on a text or voice channel was denied for a role

  /* specs/discord/audit_log.json:160:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}, "comment":"invite code changed" }' */
  char *code; ///< invite code changed

  /* specs/discord/audit_log.json:161:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel for invite code changed", "inject_if_not":0 }' */
  u64_snowflake_t channel_id; ///< channel for invite code changed

  /* specs/discord/audit_log.json:162:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"person who created invite code changed", "inject_if_not":0 }' */
  u64_snowflake_t inviter_id; ///< person who created invite code changed

  /* specs/discord/audit_log.json:163:18
     '{"name":"max_uses", "type": {"base":"int"}, "comment":"change to max number of times invite codes can be used" }' */
  int max_uses; ///< change to max number of times invite codes can be used

  /* specs/discord/audit_log.json:164:18
     '{"name":"uses", "type": {"base":"int"}, "comment":"number of times invite code used changed" }' */
  int uses; ///< number of times invite code used changed

  /* specs/discord/audit_log.json:165:18
     '{"name":"max_age", "type": {"base":"int"}, "comment":"how long invite code lasts changed" }' */
  int max_age; ///< how long invite code lasts changed

  /* specs/discord/audit_log.json:166:18
     '{"name":"temporary", "type": {"base":"bool"}, "comment":"invite code is temporary/never expires" }' */
  bool temporary; ///< invite code is temporary/never expires

  /* specs/discord/audit_log.json:167:18
     '{"name":"deaf", "type": {"base":"bool"}, "comment":"user server deafened/undefeaned" }' */
  bool deaf; ///< user server deafened/undefeaned

  /* specs/discord/audit_log.json:168:18
     '{"name":"mute", "type": {"base":"bool"}, "comment":"user server muted/unmuted" }' */
  bool mute; ///< user server muted/unmuted

  /* specs/discord/audit_log.json:169:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}, "comment":"user nickname/changed" }' */
  char *nick; ///< user nickname/changed

  /* specs/discord/audit_log.json:170:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"user avatar changed", "inject_if_not":"" }' */
  char avatar_hash[ORCA_LIMITS_SHA256]; ///< user avatar changed

  /* specs/discord/audit_log.json:171:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the changed entity - sometimes used in conjunction with other keys", "inject_if_not":0 }' */
  u64_snowflake_t id; ///< the id of the changed entity - sometimes used in conjunction with other keys

  /* specs/discord/audit_log.json:172:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, "todo":true, "comment":"type of entity created" }' */
  // @todo type type of entity created;

  /* specs/discord/audit_log.json:173:18
     '{"name":"enable_emotions", "type": {"base":"bool"}, "comment":"integration emoticons enabled/disabled" }' */
  bool enable_emotions; ///< integration emoticons enabled/disabled

  /* specs/discord/audit_log.json:174:18
     '{"name":"expire_behavior", "type": {"base":"int"}, "comment":"integration expiring subscriber behavior changed" }' */
  int expire_behavior; ///< integration expiring subscriber behavior changed

  /* specs/discord/audit_log.json:175:18
     '{"name":"expire_grace_period", "type": {"base":"int"}, "comment":"integration expire grace period changed" }' */
  int expire_grace_period; ///< integration expire grace period changed

  /* specs/discord/audit_log.json:176:18
     '{"name":"user_limit", "type": {"base":"int" }, "comment":"new user limit in a voice channel" }' */
  int user_limit; ///< new user limit in a voice channel

  /* specs/discord/audit_log.json:177:18
     '{"name":"privacy_level", "type": {"base":"int" }, "comment":"privacy level of stage instance changed" }' */
  int privacy_level; ///< privacy level of stage instance changed

  /* specs/discord/audit_log.json:178:18
     '{"name":"tags", "type": {"base":"char", "dec":"*" }, "comment":"related emoji of sticker changed", "inject_if_not":null }' */
  char *tags; ///< related emoji of sticker changed

  /* specs/discord/audit_log.json:179:18
     '{"name":"format_type", "type": {"base":"int" }, "comment":"format type of sticker changed" }' */
  int format_type; ///< format type of sticker changed

  /* specs/discord/audit_log.json:180:18
     '{"name":"asset", "type": {"base":"char", "dec":"*" }, "comment":"empty string", "inject_if_not":null }' */
  char *asset; ///< empty string

  /* specs/discord/audit_log.json:181:18
     '{"name":"available", "type": {"base":"bool" }, "comment":"availability of sticker changed" }' */
  bool available; ///< availability of sticker changed

  /* specs/discord/audit_log.json:182:18
     '{"name":"guild_id", "type": {"base":"char", "dec":"*", "converter":"snowflake" }, "comment":"guild sticker is in changed", "inject_if_not":0 }' */
  u64_snowflake_t guild_id; ///< guild sticker is in changed

  /* specs/discord/audit_log.json:183:18
     '{"name":"archived", "type": {"base":"bool" }, "comment":"thread is now archived/unarchived" }' */
  bool archived; ///< thread is now archived/unarchived

  /* specs/discord/audit_log.json:184:18
     '{"name":"locked", "type": {"base":"bool" }, "comment":"thread is now locked/unlocked" }' */
  bool locked; ///< thread is now locked/unlocked

  /* specs/discord/audit_log.json:185:18
     '{"name":"auto_archive_duration", "type": {"base":"int" }, "comment":"auto archive duration changed" }' */
  int auto_archive_duration; ///< auto archive duration changed

  /* specs/discord/audit_log.json:186:18
     '{"name":"default_auto_archive_duration", "type": {"base":"int" }, "comment":"default auto archive duration for newly created threads changed" }' */
  int default_auto_archive_duration; ///< default auto archive duration for newly created threads changed

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[64];
    void *record_defined[64];
    void *record_null[64];
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
extern void discord_audit_log_change_key_list_free_v(void **p);
extern void discord_audit_log_change_key_list_free(struct discord_audit_log_change_key **p);
extern void discord_audit_log_change_key_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_key_list_from_json(char *str, size_t len, struct discord_audit_log_change_key ***p);
extern size_t discord_audit_log_change_key_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_key_list_to_json(char *str, size_t len, struct discord_audit_log_change_key **p);
