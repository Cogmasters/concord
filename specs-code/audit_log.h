/* This file is generated from specs/audit_log.json, Please don't edit it. */
/*
(null)
*/

/* Title: Audit Log Structure */
/* https://discord.com/developers/docs/resources/audit-log#audit-log-object-audit-log-structure */
/* This is defined at specs/audit_log.json:8:22 */
struct discord_audit_log_dati {
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook_dati", "dec":"*" } }'
  */
  struct discord_webhook_dati *webhooks;

  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user_dati", "dec":"*"}}'
  */
  struct discord_user_dati *users;

  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry_dati", "dec":"*"}}'
  */
  struct discord_audit_log_entry_dati *audit_log_entries;

  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration_dati", "dec":"ntl"}}'
  */
  struct discord_guild_integration_dati **integrations;

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
extern void discord_audit_log_dati_cleanup_v(void *p);
extern void discord_audit_log_dati_cleanup(struct discord_audit_log_dati *p);
extern void discord_audit_log_dati_init_v(void *p);
extern void discord_audit_log_dati_init(struct discord_audit_log_dati *p);
extern struct discord_audit_log_dati * discord_audit_log_dati_alloc();
extern void discord_audit_log_dati_free_v(void *p);
extern void discord_audit_log_dati_free(struct discord_audit_log_dati *p);
extern void discord_audit_log_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_dati_from_json(char *json, size_t len, struct discord_audit_log_dati *p);
extern size_t discord_audit_log_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_dati_to_json(char *json, size_t len, struct discord_audit_log_dati *p);
extern size_t discord_audit_log_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_dati_to_query(char *json, size_t len, struct discord_audit_log_dati *p);
extern void discord_audit_log_dati_list_free_v(void **p);
extern void discord_audit_log_dati_list_free(struct discord_audit_log_dati **p);
extern void discord_audit_log_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_dati_list_from_json(char *str, size_t len, struct discord_audit_log_dati ***p);
extern size_t discord_audit_log_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_dati_list_to_json(char *str, size_t len, struct discord_audit_log_dati **p);


enum discord_audit_log_entry_events_code {
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_GUILD_UPDATE = 1,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_CHANNEL_CREATE = 10,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_CHANNEL_UPDATE = 11,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_CHANNEL_DELETE = 12,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_CHANNEL_OVERWRITE_CREATE = 13,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_CHANNEL_OVERWRITE_UPDATE = 14,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_CHANNEL_OVERWRITE_DELETE = 15,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MEMBER_KICK = 20,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MEMBER_PRUNE = 21,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MEMBER_BAN_ADD = 22,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MEMBER_BAN_REMOVE = 23,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MEMBER_UPDATE = 24,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MEMBER_ROLE_UPDATE = 25,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MEMBER_MOVE = 26,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MEMBER_DISCONNECT = 27,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_BOT_ADD = 28,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_ROLE_CREATE = 30,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_ROLE_UPDATE = 31,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_ROLE_DELETE = 32,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_INVITE_CREATE = 40,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_INVITE_DELETE = 42,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_WEBHOOK_CREATE = 50,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_WEBHOOK_UPDATE = 51,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_WEBHOOK_DELETE = 52,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_EMOJI_CREATE = 60,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_EMOJI_UPDATE = 61,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_EMOJI_DELETE = 62,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MESSAGE_DELETE = 72,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MESSAGE_BULK_DELETE = 73,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MESSAGE_PIN = 74,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_MESSAGE_UNPIN = 75,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_INTEGRATION_CREATE = 80,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_INTEGRATION_UPDATE = 81,
  DISCORD_AUDIT_LOG_ENTRY_EVENTS_INTEGRATION_DELETE = 82,
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
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change_dati", "dec":"*"}}'
  */
  struct discord_audit_log_change_dati *changes;

  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t user_id;

  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t id;

  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_entry_events_code"}}'
  */
  int action_type;

  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info_dati", "dec":"*"}}'
  */
  struct discord_audit_log_entry_optional_info_dati *options;

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
extern void discord_audit_log_entry_dati_cleanup_v(void *p);
extern void discord_audit_log_entry_dati_cleanup(struct discord_audit_log_entry_dati *p);
extern void discord_audit_log_entry_dati_init_v(void *p);
extern void discord_audit_log_entry_dati_init(struct discord_audit_log_entry_dati *p);
extern struct discord_audit_log_entry_dati * discord_audit_log_entry_dati_alloc();
extern void discord_audit_log_entry_dati_free_v(void *p);
extern void discord_audit_log_entry_dati_free(struct discord_audit_log_entry_dati *p);
extern void discord_audit_log_entry_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_entry_dati_from_json(char *json, size_t len, struct discord_audit_log_entry_dati *p);
extern size_t discord_audit_log_entry_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_dati_to_json(char *json, size_t len, struct discord_audit_log_entry_dati *p);
extern size_t discord_audit_log_entry_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_dati_to_query(char *json, size_t len, struct discord_audit_log_entry_dati *p);
extern void discord_audit_log_entry_dati_list_free_v(void **p);
extern void discord_audit_log_entry_dati_list_free(struct discord_audit_log_entry_dati **p);
extern void discord_audit_log_entry_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_entry_dati_list_from_json(char *str, size_t len, struct discord_audit_log_entry_dati ***p);
extern size_t discord_audit_log_entry_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_entry_dati_list_to_json(char *str, size_t len, struct discord_audit_log_entry_dati **p);

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
extern void discord_audit_log_entry_optional_info_dati_cleanup_v(void *p);
extern void discord_audit_log_entry_optional_info_dati_cleanup(struct discord_audit_log_entry_optional_info_dati *p);
extern void discord_audit_log_entry_optional_info_dati_init_v(void *p);
extern void discord_audit_log_entry_optional_info_dati_init(struct discord_audit_log_entry_optional_info_dati *p);
extern struct discord_audit_log_entry_optional_info_dati * discord_audit_log_entry_optional_info_dati_alloc();
extern void discord_audit_log_entry_optional_info_dati_free_v(void *p);
extern void discord_audit_log_entry_optional_info_dati_free(struct discord_audit_log_entry_optional_info_dati *p);
extern void discord_audit_log_entry_optional_info_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_entry_optional_info_dati_from_json(char *json, size_t len, struct discord_audit_log_entry_optional_info_dati *p);
extern size_t discord_audit_log_entry_optional_info_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_dati_to_json(char *json, size_t len, struct discord_audit_log_entry_optional_info_dati *p);
extern size_t discord_audit_log_entry_optional_info_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_dati_to_query(char *json, size_t len, struct discord_audit_log_entry_optional_info_dati *p);
extern void discord_audit_log_entry_optional_info_dati_list_free_v(void **p);
extern void discord_audit_log_entry_optional_info_dati_list_free(struct discord_audit_log_entry_optional_info_dati **p);
extern void discord_audit_log_entry_optional_info_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_entry_optional_info_dati_list_from_json(char *str, size_t len, struct discord_audit_log_entry_optional_info_dati ***p);
extern size_t discord_audit_log_entry_optional_info_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_entry_optional_info_dati_list_to_json(char *str, size_t len, struct discord_audit_log_entry_optional_info_dati **p);

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
extern void discord_audit_log_change_dati_cleanup_v(void *p);
extern void discord_audit_log_change_dati_cleanup(struct discord_audit_log_change_dati *p);
extern void discord_audit_log_change_dati_init_v(void *p);
extern void discord_audit_log_change_dati_init(struct discord_audit_log_change_dati *p);
extern struct discord_audit_log_change_dati * discord_audit_log_change_dati_alloc();
extern void discord_audit_log_change_dati_free_v(void *p);
extern void discord_audit_log_change_dati_free(struct discord_audit_log_change_dati *p);
extern void discord_audit_log_change_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_change_dati_from_json(char *json, size_t len, struct discord_audit_log_change_dati *p);
extern size_t discord_audit_log_change_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_dati_to_json(char *json, size_t len, struct discord_audit_log_change_dati *p);
extern size_t discord_audit_log_change_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_dati_to_query(char *json, size_t len, struct discord_audit_log_change_dati *p);
extern void discord_audit_log_change_dati_list_free_v(void **p);
extern void discord_audit_log_change_dati_list_free(struct discord_audit_log_change_dati **p);
extern void discord_audit_log_change_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_dati_list_from_json(char *str, size_t len, struct discord_audit_log_change_dati ***p);
extern size_t discord_audit_log_change_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_dati_list_to_json(char *str, size_t len, struct discord_audit_log_change_dati **p);

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
extern void discord_audit_log_change_key_dati_cleanup_v(void *p);
extern void discord_audit_log_change_key_dati_cleanup(struct discord_audit_log_change_key_dati *p);
extern void discord_audit_log_change_key_dati_init_v(void *p);
extern void discord_audit_log_change_key_dati_init(struct discord_audit_log_change_key_dati *p);
extern struct discord_audit_log_change_key_dati * discord_audit_log_change_key_dati_alloc();
extern void discord_audit_log_change_key_dati_free_v(void *p);
extern void discord_audit_log_change_key_dati_free(struct discord_audit_log_change_key_dati *p);
extern void discord_audit_log_change_key_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_audit_log_change_key_dati_from_json(char *json, size_t len, struct discord_audit_log_change_key_dati *p);
extern size_t discord_audit_log_change_key_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_key_dati_to_json(char *json, size_t len, struct discord_audit_log_change_key_dati *p);
extern size_t discord_audit_log_change_key_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_audit_log_change_key_dati_to_query(char *json, size_t len, struct discord_audit_log_change_key_dati *p);
extern void discord_audit_log_change_key_dati_list_free_v(void **p);
extern void discord_audit_log_change_key_dati_list_free(struct discord_audit_log_change_key_dati **p);
extern void discord_audit_log_change_key_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_audit_log_change_key_dati_list_from_json(char *str, size_t len, struct discord_audit_log_change_key_dati ***p);
extern size_t discord_audit_log_change_key_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_audit_log_change_key_dati_list_to_json(char *str, size_t len, struct discord_audit_log_change_key_dati **p);
