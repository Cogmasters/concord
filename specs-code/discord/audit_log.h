/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/**
 * @file specs-code/discord/audit_log.h
 * @see https://discord.com/developers/docs/resources/audit-log
 */


/* Audit Log Structure */
/* defined at specs/discord/audit_log.json:9:22 */
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
  struct discord_webhook **webhooks; /**< list of webhooks found in the audit log */

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
  struct discord_user **users; /**< list of users found in the audit log */

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
  struct discord_audit_log_entry **audit_log_entries; /**< list of audit log entries */

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
  struct discord_integration **integrations; /**< list of partial integration objects */

  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
  struct discord_channel **threads; /**< list of threads found in the audit log */

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

/* Audit Log Entry Structure */
/* defined at specs/discord/audit_log.json:23:22 */
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
  char *target_id; /**< id of the affected entity (webhook,user,role,etc.) */

  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
  struct discord_audit_log_change **changes; /**< changes made to the target_id */

  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
  u64_snowflake_t user_id; /**< the user who made the changes */

  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
  u64_snowflake_t id; /**< id of the entry */

  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
  int action_type; /**< type of action that occured */

  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
  struct discord_optional_audit_entry_info **options; /**< additional info for certain action types */

  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */
  char *reason; /**< the reason for the change */

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


/* Audit Log Events */
/* defined at specs/discord/audit_log.json:35:5 */
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

/* Optional Audit Entry Info Structure */
/* defined at specs/discord/audit_log.json:91:22 */
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
  char *delete_member_days; /**< number of days after which inactive members were kicked */

  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
  char *members_removed; /**< number of members removed by the prune */

  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
  u64_snowflake_t channel_id; /**< channel in which the entities were targeted */

  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
  u64_snowflake_t message_id; /**< id of the message that was targeted */

  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
  char *count; /**< number of entities that were targeted */

  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
  u64_snowflake_t id; /**< id of the ovewritten entity */

  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
  char *type; /**< type of overwritten entity - '0' for role or '1' for member */

  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
  char *role_name; /**< name of the role if type is '0' (not present if type is '1') */

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

/* Audit Log Change Structure */
/* defined at specs/discord/audit_log.json:108:22 */
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
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */
  json_char_t* new_value; /**< new value of the key */

  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */
  json_char_t* old_value; /**< old value of the key */

  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
  char *key; /**< name of audit log change key */

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
