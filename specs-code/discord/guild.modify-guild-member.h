/* This file is generated from specs/discord/guild.modify-guild-member.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#modify-guild-member */
/* This is defined at specs/discord/guild.modify-guild-member.json:8:22 */
struct discord_modify_guild_member_params {
  /* specs/discord/guild.modify-guild-member.json:11:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}'
  */
  char *nick;

  /* specs/discord/guild.modify-guild-member.json:12:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}'
  */
  ja_u64 **roles;

  /* specs/discord/guild.modify-guild-member.json:13:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool mute;

  /* specs/discord/guild.modify-guild-member.json:14:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool deaf;

  /* specs/discord/guild.modify-guild-member.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
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
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
};
extern void discord_modify_guild_member_params_cleanup_v(void *p);
extern void discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_init_v(void *p);
extern void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *p);
extern struct discord_modify_guild_member_params * discord_modify_guild_member_params_alloc();
extern void discord_modify_guild_member_params_free_v(void *p);
extern void discord_modify_guild_member_params_free(struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_guild_member_params_from_json(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern size_t discord_modify_guild_member_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_member_params_to_json(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern size_t discord_modify_guild_member_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_member_params_to_query(char *json, size_t len, struct discord_modify_guild_member_params *p);
extern void discord_modify_guild_member_params_list_free_v(void **p);
extern void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **p);
extern void discord_modify_guild_member_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_member_params_list_from_json(char *str, size_t len, struct discord_modify_guild_member_params ***p);
extern size_t discord_modify_guild_member_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_member_params_list_to_json(char *str, size_t len, struct discord_modify_guild_member_params **p);
