/* This file is generated from specs/discord/guild.create-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild-channel */
/* This is defined at specs/discord/guild.create-channel.json:8:22 */
struct discord_create_guild_channel_params {
  /* specs/discord/guild.create-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/discord/guild.create-channel.json:12:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/discord/guild.create-channel.json:13:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}'
  */
  char *topic;

  /* specs/discord/guild.create-channel.json:14:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/discord/guild.create-channel.json:15:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/discord/guild.create-channel.json:16:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/discord/guild.create-channel.json:17:20
     '{ "name": "position", "type":{ "base":"int" } }'
  */
  int position;

  /* specs/discord/guild.create-channel.json:18:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
  struct discord_channel_overwrite **permission_overwrites;

  /* specs/discord/guild.create-channel.json:19:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  /* specs/discord/guild.create-channel.json:20:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}'
  */
  bool nsfw;

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
extern void discord_create_guild_channel_params_cleanup_v(void *p);
extern void discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_init_v(void *p);
extern void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *p);
extern struct discord_create_guild_channel_params * discord_create_guild_channel_params_alloc();
extern void discord_create_guild_channel_params_free_v(void *p);
extern void discord_create_guild_channel_params_free(struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_channel_params_from_json(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern size_t discord_create_guild_channel_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_channel_params_to_json(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern size_t discord_create_guild_channel_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_channel_params_to_query(char *json, size_t len, struct discord_create_guild_channel_params *p);
extern void discord_create_guild_channel_params_list_free_v(void **p);
extern void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **p);
extern void discord_create_guild_channel_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_channel_params_list_from_json(char *str, size_t len, struct discord_create_guild_channel_params ***p);
extern size_t discord_create_guild_channel_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_channel_params_list_to_json(char *str, size_t len, struct discord_create_guild_channel_params **p);
