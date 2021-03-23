/* This file is generated from specs/guild.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
*/

/* Title: Guild Structure */
/* This is defined at specs/guild.json:9:22 */
struct discord_guild_dati {
  /* specs/guild.json:12:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  u64_snowflake_t id;

  /* specs/guild.json:13:66
     '{"type":{"base":"char", "dec":"[MAX_NAME_LEN]"}, "name":"name"}'
  */
  char name[MAX_NAME_LEN];

  /* specs/guild.json:14:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon"}'
  */
  char *icon;

  /* specs/guild.json:15:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"icon_hash"}'
  */
  char *icon_hash;

  /* specs/guild.json:16:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"splash"}'
  */
  char *splash;

  /* specs/guild.json:17:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"discovery_splash"}'
  */
  char *discovery_splash;

  /* specs/guild.json:18:42
     '{"type":{"base":"bool"}, "name":"owner", "option":true}'
  */
  bool owner;

  /* specs/guild.json:19:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"owner_id"}'
  */
  u64_snowflake_t owner_id;

  /* specs/guild.json:20:41
     '{"type":{"base":"int"}, "name":"permissions", "option":true}'
  */
  int permissions;

  /* specs/guild.json:21:68
     '{"type":{"base":"char", "dec":"[MAX_REGION_LEN]"}, "name":"region"}'
  */
  char region[MAX_REGION_LEN];

  /* specs/guild.json:22:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"afk_channel_id"}'
  */
  u64_snowflake_t afk_channel_id;

  /* specs/guild.json:23:41
     '{"type":{"base":"int"}, "name":"afk_timeout"}'
  */
  int afk_timeout;

  /* specs/guild.json:24:42
     '{"type":{"base":"bool"}, "name":"widget_enabled", "option":true}'
  */
  bool widget_enabled;

  /* specs/guild.json:25:78
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"widget_channel_id", "option":true}'
  */
  u64_snowflake_t widget_channel_id;

  /* specs/guild.json:26:97
     '{"type":{"base":"int", "int_alias":"discord::guild::verification_level::code"}, "name":"verification_level"}'
  */
  discord_guild_verification_level_code verification_level;

  /* specs/guild.json:28:32
     '{"type":{"base":"int", "int_alias":"discord::guild::default_message_notification_level::code"}, 
              "name":"default_message_notifications"}'
  */
  discord_guild_default_message_notification_level_code default_message_notifications;

  /* specs/guild.json:30:32
     '{"type":{"base":"int", "int_alias":"discord::guild::explicit_content_filter_level::code"},
              "name":"explicit_content_filter"}'
  */
  discord_guild_explicit_content_filter_level_code explicit_content_filter;

  /* specs/guild.json:31:77
     '{"type":{"base":"discord::guild::role::dati", "dec":"ntl"}, "name":"roles", "todo":true, 
              "comment":"array of role objects"}'
  */
  //@todo roles array of role objects;

  /* specs/guild.json:33:71
     '{"type":{"base":"discord::emoji::dati", "dec":"ntl"}, "name":"emojis"}'
  */
  discord_emoji_dati **emojis;

  /* specs/guild.json:34:57
     '{"type":{"base":"ja_str", "dec":"ntl"}, "name":"features", "todo":true", 
              "comment":"array of guild feature strings"}'
  */
  //@todo features array of guild feature strings;

  /* specs/guild.json:36:88
     '{"type":{"base":"int", "int_alias":"discord::guild::mfa_level::code"}, "name":"mfa_level"}'
  */
  discord_guild_mfa_level_code mfa_level;

  /* specs/guild.json:37:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"application_id"}'
  */
  u64_snowflake_t application_id;

  /* specs/guild.json:38:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"system_channel_id"}'
  */
  u64_snowflake_t system_channel_id;

  /* specs/guild.json:39:99
     '{"type":{"base":"int", "int_alias":"discord::guild::system_channel_flags::code"}, "name":"system_channel_flags"}'
  */
  discord_guild_system_channel_flags_code system_channel_flags;

  /* specs/guild.json:40:95
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, "name":"rules_channel_id"}'
  */
  u64_snowflake_t rules_channel_id;

  /* specs/guild.json:41:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"joined_at", "option":true}'
  */
  u64_unix_ms_t joined_at;

  /* specs/guild.json:42:42
     '{"type":{"base":"bool"}, "name":"large", "option":true}'
  */
  bool large;

  /* specs/guild.json:43:42
     '{"type":{"base":"bool"}, "name":"unavailable", "option":true}'
  */
  bool unavailable;

  /* specs/guild.json:44:41
     '{"type":{"base":"int"}, "name":"member_count", "option":true}'
  */
  int member_count;

  /* specs/guild.json:45:71
     '{"type":{"base":"discord::voice::dati", "dec":"ntl"}, "name":"voice_states", "todo":true", 
         "comment":"array of partial voice state objects"}'
  */
  //@todo voice_states array of partial voice state objects;

  /* specs/guild.json:47:79
     '{"type":{"base":"discord::guild::member::dati", "dec":"ntl"}, "name":"members", "option":true}'
  */
  discord_guild_member_dati **members;

  /* specs/guild.json:48:73
     '{"type":{"base":"discord::channel::dati", "dec":"ntl"}, "name":"channels", "option":true,
         "comment":"array of channel objects"}'
  */
  discord_channel_dati **channels; // array of channel objects

  /* specs/guild.json:50:41
     '{"type":{"base":"int"}, "name":"presences", "todo":true, "option":true,
         "comment":"array of partial presence update objects"}'
  */
  //@todo presences array of partial presence update objects;

  /* specs/guild.json:52:41
     '{"type":{"base":"int"}, "name":"max_presences", "option":true}'
  */
  int max_presences;

  /* specs/guild.json:53:41
     '{"type":{"base":"int"}, "name":"max_members", "option":true}'
  */
  int max_members;

  /* specs/guild.json:54:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"vanity_url_code"}'
  */
  char *vanity_url_code;

  /* specs/guild.json:55:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"description"}'
  */
  char *description;

  /* specs/guild.json:56:70
     '{"type":{"base":"char", "dec":"*", "nullable":true}, "name":"banner"}'
  */
  char *banner;

  /* specs/guild.json:57:91
     '{"type":{"base":"int", "int_alias":"discord::guild::premium_tier::code"}, "name":"premium_tier"}'
  */
  discord_guild_premium_tier_code premium_tier;

  /* specs/guild.json:58:41
     '{"type":{"base":"int"}, "name":"premium_subscription_count", "option":true}'
  */
  int premium_subscription_count;

  /* specs/guild.json:59:68
     '{"type":{"base":"char", "dec":"[MAX_LOCALE_LEN]"}, "name":"preferred_locale"}'
  */
  char preferred_locale[MAX_LOCALE_LEN];

  /* specs/guild.json:61:27
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake", "nullable":true}, 
         "name":"public_updates_channel_id"}'
  */
  u64_snowflake_t public_updates_channel_id;

  /* specs/guild.json:62:41
     '{"type":{"base":"int"}, "name":"max_video_channel_users", "option":true}'
  */
  int max_video_channel_users;

  /* specs/guild.json:63:41
     '{"type":{"base":"int"}, "name":"approximate_member_count", "option":true}'
  */
  int approximate_member_count;

  /* specs/guild.json:64:41
     '{"type":{"base":"int"}, "name":"approximate_presence_count", "option":true}'
  */
  int approximate_presence_count;

  /* specs/guild.json:65:85
     '{"type":{"base":"discord::guild::welcome_screen::dati", "dec":"*"}, "name":"welcome_screen", "option":true}'
  */
  discord_guild_welcome_screen_dati *welcome_screen;

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
extern void discord_guild_dati_cleanup_v(void *p);
extern void discord_guild_dati_cleanup(struct discord_guild_dati *p);
extern void discord_guild_dati_init_v(void *p);
extern void discord_guild_dati_init(struct discord_guild_dati *p);
extern struct discord_guild_dati * discord_guild_dati_alloc();
extern void discord_guild_dati_free_v(void *p);
extern void discord_guild_dati_free(struct discord_guild_dati *p);
extern void discord_guild_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_dati_from_json(char *json, size_t len, struct discord_guild_dati *p);
extern size_t discord_guild_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_dati_to_json(char *json, size_t len, struct discord_guild_dati *p);
extern size_t discord_guild_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_dati_to_query(char *json, size_t len, struct discord_guild_dati *p);
extern void discord_guild_dati_list_free_v(void **p);
extern void discord_guild_dati_list_free(struct discord_guild_dati **p);
extern void discord_guild_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_dati_list_from_json(char *str, size_t len, struct discord_guild_dati ***p);
extern size_t discord_guild_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_dati_list_to_json(char *str, size_t len, struct discord_guild_dati **p);
