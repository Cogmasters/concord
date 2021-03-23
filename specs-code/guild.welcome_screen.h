/* This file is generated from specs/guild.welcome_screen.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#welcome-screen-object
*/

/* Title: Welcome Screen Channel Structure */
/* https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-channel-structure */
/* This is defined at specs/guild.welcome_screen.json:11:22 */
struct discord_guild_welcome_screen_screen_channel_dati {
  /* specs/guild.welcome_screen.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/guild.welcome_screen.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  char *description;

  /* specs/guild.welcome_screen.json:16:20
     '{ "name": "emoji_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t emoji_id;

  /* specs/guild.welcome_screen.json:17:20
     '{ "name": "emoji_name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *emoji_name;

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
extern void discord_guild_welcome_screen_screen_channel_dati_cleanup_v(void *p);
extern void discord_guild_welcome_screen_screen_channel_dati_cleanup(struct discord_guild_welcome_screen_screen_channel_dati *p);
extern void discord_guild_welcome_screen_screen_channel_dati_init_v(void *p);
extern void discord_guild_welcome_screen_screen_channel_dati_init(struct discord_guild_welcome_screen_screen_channel_dati *p);
extern struct discord_guild_welcome_screen_screen_channel_dati * discord_guild_welcome_screen_screen_channel_dati_alloc();
extern void discord_guild_welcome_screen_screen_channel_dati_free_v(void *p);
extern void discord_guild_welcome_screen_screen_channel_dati_free(struct discord_guild_welcome_screen_screen_channel_dati *p);
extern void discord_guild_welcome_screen_screen_channel_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_welcome_screen_screen_channel_dati_from_json(char *json, size_t len, struct discord_guild_welcome_screen_screen_channel_dati *p);
extern size_t discord_guild_welcome_screen_screen_channel_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_screen_channel_dati_to_json(char *json, size_t len, struct discord_guild_welcome_screen_screen_channel_dati *p);
extern size_t discord_guild_welcome_screen_screen_channel_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_screen_channel_dati_to_query(char *json, size_t len, struct discord_guild_welcome_screen_screen_channel_dati *p);
extern void discord_guild_welcome_screen_screen_channel_dati_list_free_v(void **p);
extern void discord_guild_welcome_screen_screen_channel_dati_list_free(struct discord_guild_welcome_screen_screen_channel_dati **p);
extern void discord_guild_welcome_screen_screen_channel_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_welcome_screen_screen_channel_dati_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen_screen_channel_dati ***p);
extern size_t discord_guild_welcome_screen_screen_channel_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_welcome_screen_screen_channel_dati_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen_screen_channel_dati **p);

/* Title: Welcome Screen Structure */
/* https://discord.com/developers/docs/resources/guild#welcome-screen-object-welcome-screen-structure */
/* This is defined at specs/guild.welcome_screen.json:23:22 */
struct discord_guild_welcome_screen_dati {
  /* specs/guild.welcome_screen.json:26:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *description; // @todo fixed size limit

  /* specs/guild.welcome_screen.json:27:20
     '{ "name": "welcome_channels", "type":{ "base":"struct discord_guild_welcome_screen_screen_channel_dati", "dec":"ntl" }, "todo":false }'
  */
  struct discord_guild_welcome_screen_screen_channel_dati **welcome_channels;

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
extern void discord_guild_welcome_screen_dati_cleanup_v(void *p);
extern void discord_guild_welcome_screen_dati_cleanup(struct discord_guild_welcome_screen_dati *p);
extern void discord_guild_welcome_screen_dati_init_v(void *p);
extern void discord_guild_welcome_screen_dati_init(struct discord_guild_welcome_screen_dati *p);
extern struct discord_guild_welcome_screen_dati * discord_guild_welcome_screen_dati_alloc();
extern void discord_guild_welcome_screen_dati_free_v(void *p);
extern void discord_guild_welcome_screen_dati_free(struct discord_guild_welcome_screen_dati *p);
extern void discord_guild_welcome_screen_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_welcome_screen_dati_from_json(char *json, size_t len, struct discord_guild_welcome_screen_dati *p);
extern size_t discord_guild_welcome_screen_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_dati_to_json(char *json, size_t len, struct discord_guild_welcome_screen_dati *p);
extern size_t discord_guild_welcome_screen_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_welcome_screen_dati_to_query(char *json, size_t len, struct discord_guild_welcome_screen_dati *p);
extern void discord_guild_welcome_screen_dati_list_free_v(void **p);
extern void discord_guild_welcome_screen_dati_list_free(struct discord_guild_welcome_screen_dati **p);
extern void discord_guild_welcome_screen_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_welcome_screen_dati_list_from_json(char *str, size_t len, struct discord_guild_welcome_screen_dati ***p);
extern size_t discord_guild_welcome_screen_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_welcome_screen_dati_list_to_json(char *str, size_t len, struct discord_guild_welcome_screen_dati **p);
