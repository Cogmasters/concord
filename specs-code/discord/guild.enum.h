/* This file is generated from specs/discord/guild.enum.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/


enum discord_guild_default_message_notification_level {
  DISCORD_GUILD_ALL_MESSAGES = 0,
  DISCORD_GUILD_ONLY_MENTIONS = 1,
};
extern char* discord_guild_default_message_notification_level_to_string(enum discord_guild_default_message_notification_level);
extern enum discord_guild_default_message_notification_level discord_guild_default_message_notification_level_from_string(char*);
extern bool discord_guild_default_message_notification_level_has(enum discord_guild_default_message_notification_level, char*);


enum discord_guild_explicit_content_filter_level {
  DISCORD_GUILD_DISABLED = 0,
  DISCORD_GUILD_MEMBERS_WITHOUT_ROLES = 1,
  DISCORD_GUILD_ALL_MEMBERS = 2,
};
extern char* discord_guild_explicit_content_filter_level_to_string(enum discord_guild_explicit_content_filter_level);
extern enum discord_guild_explicit_content_filter_level discord_guild_explicit_content_filter_level_from_string(char*);
extern bool discord_guild_explicit_content_filter_level_has(enum discord_guild_explicit_content_filter_level, char*);


enum discord_guild_mfa_level {
  DISCORD_GUILD_DISCORD_MFA_NONE = 0,
  DISCORD_GUILD_ELEVATED = 1,
};
extern char* discord_guild_mfa_level_to_string(enum discord_guild_mfa_level);
extern enum discord_guild_mfa_level discord_guild_mfa_level_from_string(char*);
extern bool discord_guild_mfa_level_has(enum discord_guild_mfa_level, char*);


enum discord_guild_verification_level {
  DISCORD_GUILD_DISCORD_VL_NONE = 0,
  DISCORD_GUILD_LOW = 1,
  DISCORD_GUILD_MEDIUM = 2,
  DISCORD_GUILD_HIGH = 3,
  DISCORD_GUILD_VERY_HIGH = 4,
};
extern char* discord_guild_verification_level_to_string(enum discord_guild_verification_level);
extern enum discord_guild_verification_level discord_guild_verification_level_from_string(char*);
extern bool discord_guild_verification_level_has(enum discord_guild_verification_level, char*);


enum discord_guild_premium_tier {
  DISCORD_GUILD_DISCORD_PREMIUM_NONE = 0,
  DISCORD_GUILD_TIER_1 = 1,
  DISCORD_GUILD_TIER_2 = 2,
  DISCORD_GUILD_TIER_3 = 3,
};
extern char* discord_guild_premium_tier_to_string(enum discord_guild_premium_tier);
extern enum discord_guild_premium_tier discord_guild_premium_tier_from_string(char*);
extern bool discord_guild_premium_tier_has(enum discord_guild_premium_tier, char*);


enum discord_guild_system_channel_flags {
  DISCORD_GUILD_SUPRESS_JOIN_NOTIFICATIONS = 1, // 1<<0
  DISCORD_GUILD_SUPRESS_PREMIUM_SUBSCRIPTIONS = 2, // 1<<1
};
extern char* discord_guild_system_channel_flags_to_string(enum discord_guild_system_channel_flags);
extern enum discord_guild_system_channel_flags discord_guild_system_channel_flags_from_string(char*);
extern bool discord_guild_system_channel_flags_has(enum discord_guild_system_channel_flags, char*);


enum discord_guild_guild_features {
  DISCORD_GUILD_INVITE_SPLASH = 0,
  DISCORD_GUILD_VIP_REGIONS = 1,
  DISCORD_GUILD_VANITY_URL = 2,
  DISCORD_GUILD_VERIFIED = 3,
  DISCORD_GUILD_PARTNERED = 4,
  DISCORD_GUILD_COMMUNITY = 5,
  DISCORD_GUILD_COMMERCE = 6,
  DISCORD_GUILD_NEWS = 7,
  DISCORD_GUILD_DISCOVERABLE = 8,
  DISCORD_GUILD_FEATURABLE = 9,
  DISCORD_GUILD_ANIMATED_ICON = 10,
  DISCORD_GUILD_BANNER = 11,
  DISCORD_GUILD_WELCOME_SCREEN_ENABLED = 12,
  DISCORD_GUILD_MEMBER_VERIFICATION_GATE_ENABLED = 13,
  DISCORD_GUILD_PREVIEW_ENABLED = 14,
};
extern char* discord_guild_guild_features_to_string(enum discord_guild_guild_features);
extern enum discord_guild_guild_features discord_guild_guild_features_from_string(char*);
extern bool discord_guild_guild_features_has(enum discord_guild_guild_features, char*);

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
extern void discord_guild_unavailable_cleanup_v(void *p);
extern void discord_guild_unavailable_cleanup(struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_init_v(void *p);
extern void discord_guild_unavailable_init(struct discord_guild_unavailable *p);
extern struct discord_guild_unavailable * discord_guild_unavailable_alloc();
extern void discord_guild_unavailable_free_v(void *p);
extern void discord_guild_unavailable_free(struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_unavailable_from_json(char *json, size_t len, struct discord_guild_unavailable *p);
extern size_t discord_guild_unavailable_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_unavailable_to_json(char *json, size_t len, struct discord_guild_unavailable *p);
extern size_t discord_guild_unavailable_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_unavailable_to_query(char *json, size_t len, struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_list_free_v(void **p);
extern void discord_guild_unavailable_list_free(struct discord_guild_unavailable **p);
extern void discord_guild_unavailable_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_unavailable_list_from_json(char *str, size_t len, struct discord_guild_unavailable ***p);
extern size_t discord_guild_unavailable_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_unavailable_list_to_json(char *str, size_t len, struct discord_guild_unavailable **p);

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
     '{"name":"discovery_splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  char *discovery_splash;

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
extern void discord_guild_preview_cleanup_v(void *p);
extern void discord_guild_preview_cleanup(struct discord_guild_preview *p);
extern void discord_guild_preview_init_v(void *p);
extern void discord_guild_preview_init(struct discord_guild_preview *p);
extern struct discord_guild_preview * discord_guild_preview_alloc();
extern void discord_guild_preview_free_v(void *p);
extern void discord_guild_preview_free(struct discord_guild_preview *p);
extern void discord_guild_preview_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_preview_from_json(char *json, size_t len, struct discord_guild_preview *p);
extern size_t discord_guild_preview_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_preview_to_json(char *json, size_t len, struct discord_guild_preview *p);
extern size_t discord_guild_preview_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_preview_to_query(char *json, size_t len, struct discord_guild_preview *p);
extern void discord_guild_preview_list_free_v(void **p);
extern void discord_guild_preview_list_free(struct discord_guild_preview **p);
extern void discord_guild_preview_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_preview_list_from_json(char *str, size_t len, struct discord_guild_preview ***p);
extern size_t discord_guild_preview_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_preview_list_to_json(char *str, size_t len, struct discord_guild_preview **p);

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
extern void discord_guild_widget_cleanup_v(void *p);
extern void discord_guild_widget_cleanup(struct discord_guild_widget *p);
extern void discord_guild_widget_init_v(void *p);
extern void discord_guild_widget_init(struct discord_guild_widget *p);
extern struct discord_guild_widget * discord_guild_widget_alloc();
extern void discord_guild_widget_free_v(void *p);
extern void discord_guild_widget_free(struct discord_guild_widget *p);
extern void discord_guild_widget_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_widget_from_json(char *json, size_t len, struct discord_guild_widget *p);
extern size_t discord_guild_widget_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_widget_to_json(char *json, size_t len, struct discord_guild_widget *p);
extern size_t discord_guild_widget_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_widget_to_query(char *json, size_t len, struct discord_guild_widget *p);
extern void discord_guild_widget_list_free_v(void **p);
extern void discord_guild_widget_list_free(struct discord_guild_widget **p);
extern void discord_guild_widget_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_widget_list_from_json(char *str, size_t len, struct discord_guild_widget ***p);
extern size_t discord_guild_widget_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_widget_list_to_json(char *str, size_t len, struct discord_guild_widget **p);
