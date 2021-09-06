/* This file is generated from specs/discord/guild.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild.h
 * @see https://discord.com/developers/docs/resources/guild
 */


// Guild Structure
// defined at specs/discord/guild.json:9:22
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_init(struct discord_guild *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_cleanup(struct discord_guild *)`
 *     * :code:`void discord_guild_list_free(struct discord_guild **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_from_json(char *rbuf, size_t len, struct discord_guild **)`
 *     * :code:`void discord_guild_list_from_json(char *rbuf, size_t len, struct discord_guild ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_to_json(char *wbuf, size_t len, struct discord_guild *)`
 *     * :code:`void discord_guild_list_to_json(char *wbuf, size_t len, struct discord_guild **)`
 * @endverbatim
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

  /* specs/discord/guild.json:21:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "name":"region"}' */
  char region[ORCA_LIMITS_REGION];

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

  /* specs/discord/guild.json:59:72
     '{"type":{"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "name":"preferred_locale"}' */
  char preferred_locale[ORCA_LIMITS_LOCALE];

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
extern void discord_guild_cleanup_v(void *p);
extern void discord_guild_cleanup(struct discord_guild *p);
extern void discord_guild_init_v(void *p);
extern void discord_guild_init(struct discord_guild *p);
extern void discord_guild_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_from_json(char *json, size_t len, struct discord_guild **pp);
extern size_t discord_guild_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_to_json(char *json, size_t len, struct discord_guild *p);
extern void discord_guild_list_free_v(void **p);
extern void discord_guild_list_free(struct discord_guild **p);
extern void discord_guild_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_list_from_json(char *str, size_t len, struct discord_guild ***p);
extern size_t discord_guild_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_list_to_json(char *str, size_t len, struct discord_guild **p);


// Default Message Notification Level
// defined at specs/discord/guild.json:68:5
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-default-message-notification-level
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_default_message_notification_level_print(enum discord_guild_default_message_notification_level code)`
 *   * :code:`enum discord_guild_default_message_notification_level discord_guild_default_message_notification_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_default_message_notification_level {
  DISCORD_GUILD_ALL_MESSAGES = 0,
  DISCORD_GUILD_ONLY_MENTIONS = 1,
};
extern char* discord_guild_default_message_notification_level_print(enum discord_guild_default_message_notification_level);
extern enum discord_guild_default_message_notification_level discord_guild_default_message_notification_level_eval(char*);
extern void discord_guild_default_message_notification_level_list_free_v(void **p);
extern void discord_guild_default_message_notification_level_list_free(enum discord_guild_default_message_notification_level **p);
extern void discord_guild_default_message_notification_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_default_message_notification_level_list_from_json(char *str, size_t len, enum discord_guild_default_message_notification_level ***p);
extern size_t discord_guild_default_message_notification_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_default_message_notification_level_list_to_json(char *str, size_t len, enum discord_guild_default_message_notification_level **p);


// Explicit Content Filter Level
// defined at specs/discord/guild.json:78:5
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-explicit-content-filter-level
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_explicit_content_filter_level_print(enum discord_guild_explicit_content_filter_level code)`
 *   * :code:`enum discord_guild_explicit_content_filter_level discord_guild_explicit_content_filter_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_explicit_content_filter_level {
  DISCORD_GUILD_DISABLED = 0,
  DISCORD_GUILD_MEMBERS_WITHOUT_ROLES = 1,
  DISCORD_GUILD_ALL_MEMBERS = 2,
};
extern char* discord_guild_explicit_content_filter_level_print(enum discord_guild_explicit_content_filter_level);
extern enum discord_guild_explicit_content_filter_level discord_guild_explicit_content_filter_level_eval(char*);
extern void discord_guild_explicit_content_filter_level_list_free_v(void **p);
extern void discord_guild_explicit_content_filter_level_list_free(enum discord_guild_explicit_content_filter_level **p);
extern void discord_guild_explicit_content_filter_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_explicit_content_filter_level_list_from_json(char *str, size_t len, enum discord_guild_explicit_content_filter_level ***p);
extern size_t discord_guild_explicit_content_filter_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_explicit_content_filter_level_list_to_json(char *str, size_t len, enum discord_guild_explicit_content_filter_level **p);


// MFA Level
// defined at specs/discord/guild.json:89:5
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-mfa-level
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_mfa_level_print(enum discord_guild_mfa_level code)`
 *   * :code:`enum discord_guild_mfa_level discord_guild_mfa_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_mfa_level {
  DISCORD_GUILD_DISCORD_MFA_NONE = 0,
  DISCORD_GUILD_ELEVATED = 1,
};
extern char* discord_guild_mfa_level_print(enum discord_guild_mfa_level);
extern enum discord_guild_mfa_level discord_guild_mfa_level_eval(char*);
extern void discord_guild_mfa_level_list_free_v(void **p);
extern void discord_guild_mfa_level_list_free(enum discord_guild_mfa_level **p);
extern void discord_guild_mfa_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_mfa_level_list_from_json(char *str, size_t len, enum discord_guild_mfa_level ***p);
extern size_t discord_guild_mfa_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_mfa_level_list_to_json(char *str, size_t len, enum discord_guild_mfa_level **p);


// Verification Level
// defined at specs/discord/guild.json:99:5
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-verification-level
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_verification_level_print(enum discord_guild_verification_level code)`
 *   * :code:`enum discord_guild_verification_level discord_guild_verification_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_verification_level {
  DISCORD_GUILD_DISCORD_VL_NONE = 0,
  DISCORD_GUILD_LOW = 1,
  DISCORD_GUILD_MEDIUM = 2,
  DISCORD_GUILD_HIGH = 3,
  DISCORD_GUILD_VERY_HIGH = 4,
};
extern char* discord_guild_verification_level_print(enum discord_guild_verification_level);
extern enum discord_guild_verification_level discord_guild_verification_level_eval(char*);
extern void discord_guild_verification_level_list_free_v(void **p);
extern void discord_guild_verification_level_list_free(enum discord_guild_verification_level **p);
extern void discord_guild_verification_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_verification_level_list_from_json(char *str, size_t len, enum discord_guild_verification_level ***p);
extern size_t discord_guild_verification_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_verification_level_list_to_json(char *str, size_t len, enum discord_guild_verification_level **p);


// Premium Tier
// defined at specs/discord/guild.json:112:5
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-premium-tier
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_premium_tier_print(enum discord_guild_premium_tier code)`
 *   * :code:`enum discord_guild_premium_tier discord_guild_premium_tier_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_premium_tier {
  DISCORD_GUILD_DISCORD_PREMIUM_NONE = 0,
  DISCORD_GUILD_TIER_1 = 1,
  DISCORD_GUILD_TIER_2 = 2,
  DISCORD_GUILD_TIER_3 = 3,
};
extern char* discord_guild_premium_tier_print(enum discord_guild_premium_tier);
extern enum discord_guild_premium_tier discord_guild_premium_tier_eval(char*);
extern void discord_guild_premium_tier_list_free_v(void **p);
extern void discord_guild_premium_tier_list_free(enum discord_guild_premium_tier **p);
extern void discord_guild_premium_tier_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_premium_tier_list_from_json(char *str, size_t len, enum discord_guild_premium_tier ***p);
extern size_t discord_guild_premium_tier_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_premium_tier_list_to_json(char *str, size_t len, enum discord_guild_premium_tier **p);


// System Channel Flags
// defined at specs/discord/guild.json:124:5
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-system-channel-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_system_channel_flags_print(enum discord_guild_system_channel_flags code)`
 *   * :code:`enum discord_guild_system_channel_flags discord_guild_system_channel_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_system_channel_flags {
  DISCORD_GUILD_SUPRESS_JOIN_NOTIFICATIONS = 1, ///< 1<<0
  DISCORD_GUILD_SUPRESS_PREMIUM_SUBSCRIPTIONS = 2, ///< 1<<1
};
extern char* discord_guild_system_channel_flags_print(enum discord_guild_system_channel_flags);
extern enum discord_guild_system_channel_flags discord_guild_system_channel_flags_eval(char*);
extern void discord_guild_system_channel_flags_list_free_v(void **p);
extern void discord_guild_system_channel_flags_list_free(enum discord_guild_system_channel_flags **p);
extern void discord_guild_system_channel_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_system_channel_flags_list_from_json(char *str, size_t len, enum discord_guild_system_channel_flags ***p);
extern size_t discord_guild_system_channel_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_system_channel_flags_list_to_json(char *str, size_t len, enum discord_guild_system_channel_flags **p);


// Guild Features
// defined at specs/discord/guild.json:134:5
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-object-guild-features
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_features_print(enum discord_guild_features code)`
 *   * :code:`enum discord_guild_features discord_guild_features_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_features {
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
extern char* discord_guild_features_print(enum discord_guild_features);
extern enum discord_guild_features discord_guild_features_eval(char*);
extern void discord_guild_features_list_free_v(void **p);
extern void discord_guild_features_list_free(enum discord_guild_features **p);
extern void discord_guild_features_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_features_list_from_json(char *str, size_t len, enum discord_guild_features ***p);
extern size_t discord_guild_features_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_features_list_to_json(char *str, size_t len, enum discord_guild_features **p);

// Unavailable Guild Object
// defined at specs/discord/guild.json:161:23
/**
 * @see https://discord.com/developers/docs/resources/guild#unavailable-guild-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_unavailable_init(struct discord_guild_unavailable *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_unavailable_cleanup(struct discord_guild_unavailable *)`
 *     * :code:`void discord_guild_unavailable_list_free(struct discord_guild_unavailable **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_unavailable_from_json(char *rbuf, size_t len, struct discord_guild_unavailable **)`
 *     * :code:`void discord_guild_unavailable_list_from_json(char *rbuf, size_t len, struct discord_guild_unavailable ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_unavailable_to_json(char *wbuf, size_t len, struct discord_guild_unavailable *)`
 *     * :code:`void discord_guild_unavailable_list_to_json(char *wbuf, size_t len, struct discord_guild_unavailable **)`
 * @endverbatim
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
extern void discord_guild_unavailable_cleanup_v(void *p);
extern void discord_guild_unavailable_cleanup(struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_init_v(void *p);
extern void discord_guild_unavailable_init(struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_unavailable_from_json(char *json, size_t len, struct discord_guild_unavailable **pp);
extern size_t discord_guild_unavailable_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_unavailable_to_json(char *json, size_t len, struct discord_guild_unavailable *p);
extern void discord_guild_unavailable_list_free_v(void **p);
extern void discord_guild_unavailable_list_free(struct discord_guild_unavailable **p);
extern void discord_guild_unavailable_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_unavailable_list_from_json(char *str, size_t len, struct discord_guild_unavailable ***p);
extern size_t discord_guild_unavailable_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_unavailable_list_to_json(char *str, size_t len, struct discord_guild_unavailable **p);

// Guild Preview Object
// defined at specs/discord/guild.json:171:23
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-preview-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_preview_init(struct discord_guild_preview *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_preview_cleanup(struct discord_guild_preview *)`
 *     * :code:`void discord_guild_preview_list_free(struct discord_guild_preview **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_preview_from_json(char *rbuf, size_t len, struct discord_guild_preview **)`
 *     * :code:`void discord_guild_preview_list_from_json(char *rbuf, size_t len, struct discord_guild_preview ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_preview_to_json(char *wbuf, size_t len, struct discord_guild_preview *)`
 *     * :code:`void discord_guild_preview_list_to_json(char *wbuf, size_t len, struct discord_guild_preview **)`
 * @endverbatim
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
extern void discord_guild_preview_cleanup_v(void *p);
extern void discord_guild_preview_cleanup(struct discord_guild_preview *p);
extern void discord_guild_preview_init_v(void *p);
extern void discord_guild_preview_init(struct discord_guild_preview *p);
extern void discord_guild_preview_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_preview_from_json(char *json, size_t len, struct discord_guild_preview **pp);
extern size_t discord_guild_preview_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_preview_to_json(char *json, size_t len, struct discord_guild_preview *p);
extern void discord_guild_preview_list_free_v(void **p);
extern void discord_guild_preview_list_free(struct discord_guild_preview **p);
extern void discord_guild_preview_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_preview_list_from_json(char *str, size_t len, struct discord_guild_preview ***p);
extern size_t discord_guild_preview_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_preview_list_to_json(char *str, size_t len, struct discord_guild_preview **p);

// Guild Widget Object
// defined at specs/discord/guild.json:189:23
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-widget-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_widget_init(struct discord_guild_widget *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_widget_cleanup(struct discord_guild_widget *)`
 *     * :code:`void discord_guild_widget_list_free(struct discord_guild_widget **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_widget_from_json(char *rbuf, size_t len, struct discord_guild_widget **)`
 *     * :code:`void discord_guild_widget_list_from_json(char *rbuf, size_t len, struct discord_guild_widget ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_widget_to_json(char *wbuf, size_t len, struct discord_guild_widget *)`
 *     * :code:`void discord_guild_widget_list_to_json(char *wbuf, size_t len, struct discord_guild_widget **)`
 * @endverbatim
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
extern void discord_guild_widget_cleanup_v(void *p);
extern void discord_guild_widget_cleanup(struct discord_guild_widget *p);
extern void discord_guild_widget_init_v(void *p);
extern void discord_guild_widget_init(struct discord_guild_widget *p);
extern void discord_guild_widget_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_widget_from_json(char *json, size_t len, struct discord_guild_widget **pp);
extern size_t discord_guild_widget_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_widget_to_json(char *json, size_t len, struct discord_guild_widget *p);
extern void discord_guild_widget_list_free_v(void **p);
extern void discord_guild_widget_list_free(struct discord_guild_widget **p);
extern void discord_guild_widget_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_widget_list_from_json(char *str, size_t len, struct discord_guild_widget ***p);
extern size_t discord_guild_widget_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_widget_list_to_json(char *str, size_t len, struct discord_guild_widget **p);

// Guild Member Structure
// defined at specs/discord/guild.json:199:22
/**
 * @see https://discord.com/developers/docs/resources/guild#guild-member-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_member_init(struct discord_guild_member *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_member_cleanup(struct discord_guild_member *)`
 *     * :code:`void discord_guild_member_list_free(struct discord_guild_member **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_member_from_json(char *rbuf, size_t len, struct discord_guild_member **)`
 *     * :code:`void discord_guild_member_list_from_json(char *rbuf, size_t len, struct discord_guild_member ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_member_to_json(char *wbuf, size_t len, struct discord_guild_member *)`
 *     * :code:`void discord_guild_member_list_to_json(char *wbuf, size_t len, struct discord_guild_member **)`
 * @endverbatim
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
extern void discord_guild_member_cleanup_v(void *p);
extern void discord_guild_member_cleanup(struct discord_guild_member *p);
extern void discord_guild_member_init_v(void *p);
extern void discord_guild_member_init(struct discord_guild_member *p);
extern void discord_guild_member_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_member_from_json(char *json, size_t len, struct discord_guild_member **pp);
extern size_t discord_guild_member_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_member_to_json(char *json, size_t len, struct discord_guild_member *p);
extern void discord_guild_member_list_free_v(void **p);
extern void discord_guild_member_list_free(struct discord_guild_member **p);
extern void discord_guild_member_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_member_list_from_json(char *str, size_t len, struct discord_guild_member ***p);
extern size_t discord_guild_member_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_member_list_to_json(char *str, size_t len, struct discord_guild_member **p);

// Integration Structure
// defined at specs/discord/guild.json:217:22
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_integration_init(struct discord_guild_integration *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_integration_cleanup(struct discord_guild_integration *)`
 *     * :code:`void discord_guild_integration_list_free(struct discord_guild_integration **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_integration_from_json(char *rbuf, size_t len, struct discord_guild_integration **)`
 *     * :code:`void discord_guild_integration_list_from_json(char *rbuf, size_t len, struct discord_guild_integration ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_integration_to_json(char *wbuf, size_t len, struct discord_guild_integration *)`
 *     * :code:`void discord_guild_integration_list_to_json(char *wbuf, size_t len, struct discord_guild_integration **)`
 * @endverbatim
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
extern void discord_guild_integration_cleanup_v(void *p);
extern void discord_guild_integration_cleanup(struct discord_guild_integration *p);
extern void discord_guild_integration_init_v(void *p);
extern void discord_guild_integration_init(struct discord_guild_integration *p);
extern void discord_guild_integration_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_integration_from_json(char *json, size_t len, struct discord_guild_integration **pp);
extern size_t discord_guild_integration_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_to_json(char *json, size_t len, struct discord_guild_integration *p);
extern void discord_guild_integration_list_free_v(void **p);
extern void discord_guild_integration_list_free(struct discord_guild_integration **p);
extern void discord_guild_integration_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_integration_list_from_json(char *str, size_t len, struct discord_guild_integration ***p);
extern size_t discord_guild_integration_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_integration_list_to_json(char *str, size_t len, struct discord_guild_integration **p);


// Integration Expire Behaviors
// defined at specs/discord/guild.json:237:5
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-object-integration-expire-behaviors
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_guild_integration_expire_behaviors_print(enum discord_guild_integration_expire_behaviors code)`
 *   * :code:`enum discord_guild_integration_expire_behaviors discord_guild_integration_expire_behaviors_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_guild_integration_expire_behaviors {
  DISCORD_GUILD_INTEGRATION_REMOVE_ROLE = 0,
  DISCORD_GUILD_INTEGRATION_KICK = 1,
};
extern char* discord_guild_integration_expire_behaviors_print(enum discord_guild_integration_expire_behaviors);
extern enum discord_guild_integration_expire_behaviors discord_guild_integration_expire_behaviors_eval(char*);
extern void discord_guild_integration_expire_behaviors_list_free_v(void **p);
extern void discord_guild_integration_expire_behaviors_list_free(enum discord_guild_integration_expire_behaviors **p);
extern void discord_guild_integration_expire_behaviors_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_integration_expire_behaviors_list_from_json(char *str, size_t len, enum discord_guild_integration_expire_behaviors ***p);
extern size_t discord_guild_integration_expire_behaviors_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_integration_expire_behaviors_list_to_json(char *str, size_t len, enum discord_guild_integration_expire_behaviors **p);

// Integration Account Structure
// defined at specs/discord/guild.json:251:22
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-account-object-integration-account-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_integration_account_init(struct discord_guild_integration_account *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_integration_account_cleanup(struct discord_guild_integration_account *)`
 *     * :code:`void discord_guild_integration_account_list_free(struct discord_guild_integration_account **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_integration_account_from_json(char *rbuf, size_t len, struct discord_guild_integration_account **)`
 *     * :code:`void discord_guild_integration_account_list_from_json(char *rbuf, size_t len, struct discord_guild_integration_account ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_integration_account_to_json(char *wbuf, size_t len, struct discord_guild_integration_account *)`
 *     * :code:`void discord_guild_integration_account_list_to_json(char *wbuf, size_t len, struct discord_guild_integration_account **)`
 * @endverbatim
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
extern void discord_guild_integration_account_cleanup_v(void *p);
extern void discord_guild_integration_account_cleanup(struct discord_guild_integration_account *p);
extern void discord_guild_integration_account_init_v(void *p);
extern void discord_guild_integration_account_init(struct discord_guild_integration_account *p);
extern void discord_guild_integration_account_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_integration_account_from_json(char *json, size_t len, struct discord_guild_integration_account **pp);
extern size_t discord_guild_integration_account_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_account_to_json(char *json, size_t len, struct discord_guild_integration_account *p);
extern void discord_guild_integration_account_list_free_v(void **p);
extern void discord_guild_integration_account_list_free(struct discord_guild_integration_account **p);
extern void discord_guild_integration_account_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_integration_account_list_from_json(char *str, size_t len, struct discord_guild_integration_account ***p);
extern size_t discord_guild_integration_account_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_integration_account_list_to_json(char *str, size_t len, struct discord_guild_integration_account **p);

// Integration Application Object
// defined at specs/discord/guild.json:261:22
/**
 * @see https://discord.com/developers/docs/resources/guild#integration-application-object-integration-application-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_integration_application_init(struct discord_guild_integration_application *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_integration_application_cleanup(struct discord_guild_integration_application *)`
 *     * :code:`void discord_guild_integration_application_list_free(struct discord_guild_integration_application **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_integration_application_from_json(char *rbuf, size_t len, struct discord_guild_integration_application **)`
 *     * :code:`void discord_guild_integration_application_list_from_json(char *rbuf, size_t len, struct discord_guild_integration_application ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_integration_application_to_json(char *wbuf, size_t len, struct discord_guild_integration_application *)`
 *     * :code:`void discord_guild_integration_application_list_to_json(char *wbuf, size_t len, struct discord_guild_integration_application **)`
 * @endverbatim
 */
struct discord_guild_integration_application {
  /* specs/discord/guild.json:263:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  u64_snowflake_t id;

  /* specs/discord/guild.json:264:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}' */
  char *name;

  /* specs/discord/guild.json:265:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  char icon[ORCA_LIMITS_SHA256];

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
extern void discord_guild_integration_application_cleanup_v(void *p);
extern void discord_guild_integration_application_cleanup(struct discord_guild_integration_application *p);
extern void discord_guild_integration_application_init_v(void *p);
extern void discord_guild_integration_application_init(struct discord_guild_integration_application *p);
extern void discord_guild_integration_application_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_integration_application_from_json(char *json, size_t len, struct discord_guild_integration_application **pp);
extern size_t discord_guild_integration_application_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_integration_application_to_json(char *json, size_t len, struct discord_guild_integration_application *p);
extern void discord_guild_integration_application_list_free_v(void **p);
extern void discord_guild_integration_application_list_free(struct discord_guild_integration_application **p);
extern void discord_guild_integration_application_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_integration_application_list_from_json(char *str, size_t len, struct discord_guild_integration_application ***p);
extern size_t discord_guild_integration_application_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_integration_application_list_to_json(char *str, size_t len, struct discord_guild_integration_application **p);

// Ban Structure
// defined at specs/discord/guild.json:275:22
/**
 * @see https://discord.com/developers/docs/resources/guild#ban-object
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_ban_init(struct discord_guild_ban *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_ban_cleanup(struct discord_guild_ban *)`
 *     * :code:`void discord_guild_ban_list_free(struct discord_guild_ban **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_ban_from_json(char *rbuf, size_t len, struct discord_guild_ban **)`
 *     * :code:`void discord_guild_ban_list_from_json(char *rbuf, size_t len, struct discord_guild_ban ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_ban_to_json(char *wbuf, size_t len, struct discord_guild_ban *)`
 *     * :code:`void discord_guild_ban_list_to_json(char *wbuf, size_t len, struct discord_guild_ban **)`
 * @endverbatim
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
extern void discord_guild_ban_cleanup_v(void *p);
extern void discord_guild_ban_cleanup(struct discord_guild_ban *p);
extern void discord_guild_ban_init_v(void *p);
extern void discord_guild_ban_init(struct discord_guild_ban *p);
extern void discord_guild_ban_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_ban_from_json(char *json, size_t len, struct discord_guild_ban **pp);
extern size_t discord_guild_ban_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_ban_to_json(char *json, size_t len, struct discord_guild_ban *p);
extern void discord_guild_ban_list_free_v(void **p);
extern void discord_guild_ban_list_free(struct discord_guild_ban **p);
extern void discord_guild_ban_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_ban_list_from_json(char *str, size_t len, struct discord_guild_ban ***p);
extern size_t discord_guild_ban_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_ban_list_to_json(char *str, size_t len, struct discord_guild_ban **p);

// Welcome Screen Structure
// defined at specs/discord/guild.json:286:22
/**
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_welcome_screen_init(struct discord_guild_welcome_screen *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_welcome_screen_cleanup(struct discord_guild_welcome_screen *)`
 *     * :code:`void discord_guild_welcome_screen_list_free(struct discord_guild_welcome_screen **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_welcome_screen_from_json(char *rbuf, size_t len, struct discord_guild_welcome_screen **)`
 *     * :code:`void discord_guild_welcome_screen_list_from_json(char *rbuf, size_t len, struct discord_guild_welcome_screen ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_welcome_screen_to_json(char *wbuf, size_t len, struct discord_guild_welcome_screen *)`
 *     * :code:`void discord_guild_welcome_screen_list_to_json(char *wbuf, size_t len, struct discord_guild_welcome_screen **)`
 * @endverbatim
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
extern void discord_guild_welcome_screen_cleanup_v(void *p);
extern void discord_guild_welcome_screen_cleanup(struct discord_guild_welcome_screen *p);
extern void discord_guild_welcome_screen_init_v(void *p);
extern void discord_guild_welcome_screen_init(struct discord_guild_welcome_screen *p);
extern void discord_guild_welcome_screen_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_welcome_screen_from_json(char *json, size_t len, struct discord_guild_welcome_screen **pp);
extern size_t discord_guild_welcome_screen_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_to_json(char *json, size_t len, struct discord_guild_welcome_screen *p);
extern void discord_guild_welcome_screen_list_free_v(void **p);
extern void discord_guild_welcome_screen_list_free(struct discord_guild_welcome_screen **p);
extern void discord_guild_welcome_screen_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_welcome_screen_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen ***p);
extern size_t discord_guild_welcome_screen_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_welcome_screen_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen **p);

// Welcome Screen Channel Structure
// defined at specs/discord/guild.json:297:22
/**
 * @see https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_guild_welcome_screen_channel_init(struct discord_guild_welcome_screen_channel *)`
 *   * Cleanup:

 *     * :code:`void discord_guild_welcome_screen_channel_cleanup(struct discord_guild_welcome_screen_channel *)`
 *     * :code:`void discord_guild_welcome_screen_channel_list_free(struct discord_guild_welcome_screen_channel **)`
 *   * JSON Decoder:

 *     * :code:`void discord_guild_welcome_screen_channel_from_json(char *rbuf, size_t len, struct discord_guild_welcome_screen_channel **)`
 *     * :code:`void discord_guild_welcome_screen_channel_list_from_json(char *rbuf, size_t len, struct discord_guild_welcome_screen_channel ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_guild_welcome_screen_channel_to_json(char *wbuf, size_t len, struct discord_guild_welcome_screen_channel *)`
 *     * :code:`void discord_guild_welcome_screen_channel_list_to_json(char *wbuf, size_t len, struct discord_guild_welcome_screen_channel **)`
 * @endverbatim
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
extern void discord_guild_welcome_screen_channel_cleanup_v(void *p);
extern void discord_guild_welcome_screen_channel_cleanup(struct discord_guild_welcome_screen_channel *p);
extern void discord_guild_welcome_screen_channel_init_v(void *p);
extern void discord_guild_welcome_screen_channel_init(struct discord_guild_welcome_screen_channel *p);
extern void discord_guild_welcome_screen_channel_from_json_v(char *json, size_t len, void *pp);
extern void discord_guild_welcome_screen_channel_from_json(char *json, size_t len, struct discord_guild_welcome_screen_channel **pp);
extern size_t discord_guild_welcome_screen_channel_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_channel_to_json(char *json, size_t len, struct discord_guild_welcome_screen_channel *p);
extern void discord_guild_welcome_screen_channel_list_free_v(void **p);
extern void discord_guild_welcome_screen_channel_list_free(struct discord_guild_welcome_screen_channel **p);
extern void discord_guild_welcome_screen_channel_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_welcome_screen_channel_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen_channel ***p);
extern size_t discord_guild_welcome_screen_channel_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_welcome_screen_channel_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen_channel **p);
