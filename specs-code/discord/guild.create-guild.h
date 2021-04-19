/* This file is generated from specs/discord/guild.create-guild.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild */
/* This is defined at specs/discord/guild.create-guild.json:8:22 */
struct discord_create_guild_params {
  /* specs/discord/guild.create-guild.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[200+1]" }, 
          "comment":"name of the guild (2-100) characters"}'
  */
  char name[200+1]; // name of the guild (2-100) characters

  /* specs/discord/guild.create-guild.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" },
          "option":true, "inject_if_not":null, "comment":"voice region id" }'
  */
  char *region; // voice region id

  /* specs/discord/guild.create-guild.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}'
  */
  char *icon; // base64 128x1128 image for the guild icon

  /* specs/discord/guild.create-guild.json:17:20
     '{ "name": "verification_level", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"verification level"}'
  */
  int verification_level; // verification level

  /* specs/discord/guild.create-guild.json:19:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"default message notification level"}'
  */
  int default_message_notifications; // default message notification level

  /* specs/discord/guild.create-guild.json:21:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"explicit content filter level"}'
  */
  int explicit_content_filter; // explicit content filter level

  /* specs/discord/guild.create-guild.json:23:20
     '{ "name": "roles", "type":{ "base":"int" }, 
          "todo":true, "comment":"new guild roles" }'
  */
  //@todo roles new guild roles;

  /* specs/discord/guild.create-guild.json:25:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, 
          "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}'
  */
  struct discord_channel **channels; // array of partial channel objects

  /* specs/discord/guild.create-guild.json:27:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"id for afk channel"}'
  */
  u64_snowflake_t afk_channel_id; // id for afk channel

  /* specs/discord/guild.create-guild.json:29:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}'
  */
  int afk_timeout; // afk timeout in seconds

  /* specs/discord/guild.create-guild.json:31:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, 
          "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}'
  */
  u64_snowflake_t system_channel_id; // the id of the channel where guild notices such as welcome messages and boost events are posted

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[11];
    void *record_defined[11];
    void *record_null[11];
  } __M; // metadata
};
extern void discord_create_guild_params_cleanup_v(void *p);
extern void discord_create_guild_params_cleanup(struct discord_create_guild_params *p);
extern void discord_create_guild_params_init_v(void *p);
extern void discord_create_guild_params_init(struct discord_create_guild_params *p);
extern struct discord_create_guild_params * discord_create_guild_params_alloc();
extern void discord_create_guild_params_free_v(void *p);
extern void discord_create_guild_params_free(struct discord_create_guild_params *p);
extern void discord_create_guild_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_params_from_json(char *json, size_t len, struct discord_create_guild_params *p);
extern size_t discord_create_guild_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_params_to_json(char *json, size_t len, struct discord_create_guild_params *p);
extern size_t discord_create_guild_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_params_to_query(char *json, size_t len, struct discord_create_guild_params *p);
extern void discord_create_guild_params_list_free_v(void **p);
extern void discord_create_guild_params_list_free(struct discord_create_guild_params **p);
extern void discord_create_guild_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_params_list_from_json(char *str, size_t len, struct discord_create_guild_params ***p);
extern size_t discord_create_guild_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_params_list_to_json(char *str, size_t len, struct discord_create_guild_params **p);
