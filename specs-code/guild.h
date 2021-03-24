/* This file is generated from specs/guild.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
*/

/* Title: Guild Structure */
/* This is defined at specs/guild.json:8:22 */
struct discord_guild {
  /* specs/guild.json:11:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/guild.json:12:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
  char name[MAX_NAME_LEN];

  /* specs/guild.json:13:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
  char *icon;

  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
  char *icon_hash;

  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
  char *splash;

  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
  char *discovery_splash;

  /* specs/guild.json:17:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
  bool owner;

  /* specs/guild.json:18:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
  u64_snowflake_t owner_id;

  /* specs/guild.json:19:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
  int permissions;

  /* specs/guild.json:20:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
  char region[MAX_REGION_LEN];

  /* specs/guild.json:21:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
  u64_snowflake_t afk_channel_id;

  /* specs/guild.json:22:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
  int afk_timeout;

  /* specs/guild.json:23:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
  bool widget_enabled;

  /* specs/guild.json:24:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
  u64_snowflake_t widget_channel_id;

  /* specs/guild.json:25:94
     '{"type":{"base":"int", "int_alias":"enum discord_guild_verification_level"}, "name":"verification_level"}'
  */
  enum discord_guild_verification_level verification_level;

  /* specs/guild.json:27:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_default_message_notification_level"}, 
              "name":"default_message_notifications"}'
  */
  enum discord_guild_default_message_notification_level default_message_notifications;

  /* specs/guild.json:29:32
     '{"type":{"base":"int", "int_alias":"enum discord_guild_explicit_content_filter_level"},
              "name":"explicit_content_filter"}'
  */
  enum discord_guild_explicit_content_filter_level explicit_content_filter;

  /* specs/guild.json:30:76
     '{"type":{"base":"struct discord_guild_role", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  //@todo roles array of role objects;

  /* specs/guild.json:32:71
     '{"type":{"base":"struct discord_emoji", "dec":"ntl"}, "name":"emojis"}'
  */
  struct discord_emoji **emojis;

  /* specs/guild.json:33:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  //@todo features array of guild feature strings;

  /* specs/guild.json:35:85
     '{"type":{"base":"int", "int_alias":"enum discord_guild_mfa_level"}, "name":"mfa_level"}'
  */
  enum discord_guild_mfa_level mfa_level;

  /* specs/guild.json:36:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
  u64_snowflake_t application_id;

  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
  u64_snowflake_t system_channel_id;

  /* specs/guild.json:38:96
     '{"type":{"base":"int", "int_alias":"enum discord_guild_system_channel_flags"}, "name":"system_channel_flags"}'
  */
  enum discord_guild_system_channel_flags system_channel_flags;

  /* specs/guild.json:39:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
  u64_snowflake_t rules_channel_id;

  /* specs/guild.json:40:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
  u64_unix_ms_t joined_at;

  /* specs/guild.json:41:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
  bool large;

  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
  bool unavailable;

  /* specs/guild.json:43:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
  int member_count;

  /* specs/guild.json:44:71
     '{"type":{"base":"struct discord_voice", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  //@todo voice_states array of partial voice state objects;

  /* specs/guild.json:46:78
     '{"type":{"base":"struct discord_guild_member", "dec":"ntl"}, "name":"members", "option":true}'
  */
  struct discord_guild_member **members;

  /* specs/guild.json:47:73
     '{"type":{"base":"struct discord_channel", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
  struct discord_channel **channels; // array of channel objects

  /* specs/guild.json:49:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  //@todo presences array of partial presence update objects;

  /* specs/guild.json:51:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
  int max_presences;

  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
  int max_members;

  /* specs/guild.json:53:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url"}'
  */
  char *vanity_url;

  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
  char *description;

  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
  char *banner;

  /* specs/guild.json:56:88
     '{"type":{"base":"int", "int_alias":"enum discord_guild_premium_tier"}, "name":"premium_tier"}'
  */
  enum discord_guild_premium_tier premium_tier;

  /* specs/guild.json:57:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
  int premium_subscription_count;

  /* specs/guild.json:58:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
  char preferred_locale[MAX_LOCALE_LEN];

  /* specs/guild.json:60:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
  u64_snowflake_t public_updates_channel_id;

  /* specs/guild.json:61:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
  int max_video_channel_users;

  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
  int approximate_member_count;

  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
  int approximate_presence_count;

  /* specs/guild.json:64:84
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
extern void discord_guild_cleanup_v(void *p);
extern void discord_guild_cleanup(struct discord_guild *p);
extern void discord_guild_init_v(void *p);
extern void discord_guild_init(struct discord_guild *p);
extern struct discord_guild * discord_guild_alloc();
extern void discord_guild_free_v(void *p);
extern void discord_guild_free(struct discord_guild *p);
extern void discord_guild_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_from_json(char *json, size_t len, struct discord_guild *p);
extern size_t discord_guild_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_to_json(char *json, size_t len, struct discord_guild *p);
extern size_t discord_guild_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_to_query(char *json, size_t len, struct discord_guild *p);
extern void discord_guild_list_free_v(void **p);
extern void discord_guild_list_free(struct discord_guild **p);
extern void discord_guild_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_list_from_json(char *str, size_t len, struct discord_guild ***p);
extern size_t discord_guild_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_list_to_json(char *str, size_t len, struct discord_guild **p);
