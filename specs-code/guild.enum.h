/* This file is generated from specs/guild.enum.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/


enum discord_guild_default_message_notification_level_code {
  DISCORD_GUILD_DEFAULT_MESSAGE_NOTIFICATION_LEVEL_ALL_MESSAGES = 0,
  DISCORD_GUILD_DEFAULT_MESSAGE_NOTIFICATION_LEVEL_ONLY_MENTIONS = 1,
};


enum discord_guild_explicit_content_filter_level_code {
  DISCORD_GUILD_EXPLICIT_CONTENT_FILTER_LEVEL_DISABLED = 0,
  DISCORD_GUILD_EXPLICIT_CONTENT_FILTER_LEVEL_MEMBERS_WITHOUT_ROLES = 1,
  DISCORD_GUILD_EXPLICIT_CONTENT_FILTER_LEVEL_ALL_MEMBERS = 2,
};


enum discord_guild_mfa_level_code {
  DISCORD_GUILD_MFA_LEVEL_NONE = 0,
  DISCORD_GUILD_MFA_LEVEL_ELEVATED = 1,
};


enum discord_guild_verification_level_code {
  DISCORD_GUILD_VERIFICATION_LEVEL_NONE = 0,
  DISCORD_GUILD_VERIFICATION_LEVEL_LOW = 1,
  DISCORD_GUILD_VERIFICATION_LEVEL_MEDIUM = 2,
  DISCORD_GUILD_VERIFICATION_LEVEL_HIGH = 3,
  DISCORD_GUILD_VERIFICATION_LEVEL_VERY_HIGH = 4,
};


enum discord_guild_premium_tier_code {
  DISCORD_GUILD_PREMIUM_TIER_NONE = 0,
  DISCORD_GUILD_PREMIUM_TIER_TIER_1 = 1,
  DISCORD_GUILD_PREMIUM_TIER_TIER_2 = 2,
  DISCORD_GUILD_PREMIUM_TIER_TIER_3 = 3,
};


enum discord_guild_system_channel_flags_code {
  DISCORD_GUILD_SYSTEM_CHANNEL_FLAGS_SUPRESS_JOIN_NOTIFICATIONS = 1, // 1<<0
  DISCORD_GUILD_SYSTEM_CHANNEL_FLAGS_SUPRESS_PREMIUM_SUBSCRIPTIONS = 2, // 1<<1
};


enum discord_guild_guild_features_code {
  DISCORD_GUILD_GUILD_FEATURES_INVITE_SPLASH = 0,
  DISCORD_GUILD_GUILD_FEATURES_VIP_REGIONS = 1,
  DISCORD_GUILD_GUILD_FEATURES_VANITY_URL = 2,
  DISCORD_GUILD_GUILD_FEATURES_VERIFIED = 3,
  DISCORD_GUILD_GUILD_FEATURES_PARTNERED = 4,
  DISCORD_GUILD_GUILD_FEATURES_COMMUNITY = 5,
  DISCORD_GUILD_GUILD_FEATURES_COMMERCE = 6,
  DISCORD_GUILD_GUILD_FEATURES_NEWS = 7,
  DISCORD_GUILD_GUILD_FEATURES_DISCOVERABLE = 8,
  DISCORD_GUILD_GUILD_FEATURES_FEATURABLE = 9,
  DISCORD_GUILD_GUILD_FEATURES_ANIMATED_ICON = 10,
  DISCORD_GUILD_GUILD_FEATURES_BANNER = 11,
  DISCORD_GUILD_GUILD_FEATURES_WELCOME_SCREEN_ENABLED = 12,
  DISCORD_GUILD_GUILD_FEATURES_MEMBER_VERIFICATION_GATE_ENABLED = 13,
  DISCORD_GUILD_GUILD_FEATURES_PREVIEW_ENABLED = 14,
};

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
extern void discord_guild_unavailable_guild_dati_cleanup_v(void *p);
extern void discord_guild_unavailable_guild_dati_cleanup(struct discord_guild_unavailable_guild_dati *p);
extern void discord_guild_unavailable_guild_dati_init_v(void *p);
extern void discord_guild_unavailable_guild_dati_init(struct discord_guild_unavailable_guild_dati *p);
extern struct discord_guild_unavailable_guild_dati * discord_guild_unavailable_guild_dati_alloc();
extern void discord_guild_unavailable_guild_dati_free_v(void *p);
extern void discord_guild_unavailable_guild_dati_free(struct discord_guild_unavailable_guild_dati *p);
extern void discord_guild_unavailable_guild_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_unavailable_guild_dati_from_json(char *json, size_t len, struct discord_guild_unavailable_guild_dati *p);
extern size_t discord_guild_unavailable_guild_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_unavailable_guild_dati_to_json(char *json, size_t len, struct discord_guild_unavailable_guild_dati *p);
extern size_t discord_guild_unavailable_guild_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_unavailable_guild_dati_to_query(char *json, size_t len, struct discord_guild_unavailable_guild_dati *p);
extern void discord_guild_unavailable_guild_dati_list_free_v(void **p);
extern void discord_guild_unavailable_guild_dati_list_free(struct discord_guild_unavailable_guild_dati **p);
extern void discord_guild_unavailable_guild_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_unavailable_guild_dati_list_from_json(char *str, size_t len, struct discord_guild_unavailable_guild_dati ***p);
extern size_t discord_guild_unavailable_guild_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_unavailable_guild_dati_list_to_json(char *str, size_t len, struct discord_guild_unavailable_guild_dati **p);

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
     '{"name":"emojis", "type":{"base":"struct discord_emoji_dati", "dec":"*"}}'
  */
  struct discord_emoji_dati *emojis;

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
extern void discord_guild_preview_dati_cleanup_v(void *p);
extern void discord_guild_preview_dati_cleanup(struct discord_guild_preview_dati *p);
extern void discord_guild_preview_dati_init_v(void *p);
extern void discord_guild_preview_dati_init(struct discord_guild_preview_dati *p);
extern struct discord_guild_preview_dati * discord_guild_preview_dati_alloc();
extern void discord_guild_preview_dati_free_v(void *p);
extern void discord_guild_preview_dati_free(struct discord_guild_preview_dati *p);
extern void discord_guild_preview_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_preview_dati_from_json(char *json, size_t len, struct discord_guild_preview_dati *p);
extern size_t discord_guild_preview_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_preview_dati_to_json(char *json, size_t len, struct discord_guild_preview_dati *p);
extern size_t discord_guild_preview_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_preview_dati_to_query(char *json, size_t len, struct discord_guild_preview_dati *p);
extern void discord_guild_preview_dati_list_free_v(void **p);
extern void discord_guild_preview_dati_list_free(struct discord_guild_preview_dati **p);
extern void discord_guild_preview_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_preview_dati_list_from_json(char *str, size_t len, struct discord_guild_preview_dati ***p);
extern size_t discord_guild_preview_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_preview_dati_list_to_json(char *str, size_t len, struct discord_guild_preview_dati **p);

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
extern void discord_guild_widget_dati_cleanup_v(void *p);
extern void discord_guild_widget_dati_cleanup(struct discord_guild_widget_dati *p);
extern void discord_guild_widget_dati_init_v(void *p);
extern void discord_guild_widget_dati_init(struct discord_guild_widget_dati *p);
extern struct discord_guild_widget_dati * discord_guild_widget_dati_alloc();
extern void discord_guild_widget_dati_free_v(void *p);
extern void discord_guild_widget_dati_free(struct discord_guild_widget_dati *p);
extern void discord_guild_widget_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_widget_dati_from_json(char *json, size_t len, struct discord_guild_widget_dati *p);
extern size_t discord_guild_widget_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_widget_dati_to_json(char *json, size_t len, struct discord_guild_widget_dati *p);
extern size_t discord_guild_widget_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_widget_dati_to_query(char *json, size_t len, struct discord_guild_widget_dati *p);
extern void discord_guild_widget_dati_list_free_v(void **p);
extern void discord_guild_widget_dati_list_free(struct discord_guild_widget_dati **p);
extern void discord_guild_widget_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_widget_dati_list_from_json(char *str, size_t len, struct discord_guild_widget_dati ***p);
extern size_t discord_guild_widget_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_widget_dati_list_to_json(char *str, size_t len, struct discord_guild_widget_dati **p);
