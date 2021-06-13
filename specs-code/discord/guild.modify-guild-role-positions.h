/* This file is generated from specs/discord/guild.modify-guild-role-positions.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#modify-guild-role-positions-json-params */
/* This is defined at specs/discord/guild.modify-guild-role-positions.json:8:22 */
struct discord_modify_guild_role_positions_params {
  /* specs/discord/guild.modify-guild-role-positions.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, 
          "option":true, "inject_if_not":0, "comment":"role"}'
  */
  u64_snowflake_t id; // role

  /* specs/discord/guild.modify-guild-role-positions.json:13:20
     '{ "name": "position", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"sorting position of the role"}'
  */
  int position; // sorting position of the role

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
extern void discord_modify_guild_role_positions_params_cleanup_v(void *p);
extern void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_init_v(void *p);
extern void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *p);
extern struct discord_modify_guild_role_positions_params * discord_modify_guild_role_positions_params_alloc();
extern void discord_modify_guild_role_positions_params_free_v(void *p);
extern void discord_modify_guild_role_positions_params_free(struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_guild_role_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
extern size_t discord_modify_guild_role_positions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
extern size_t discord_modify_guild_role_positions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_to_query(char *json, size_t len, struct discord_modify_guild_role_positions_params *p);
extern void discord_modify_guild_role_positions_params_list_free_v(void **p);
extern void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **p);
extern void discord_modify_guild_role_positions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_role_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_positions_params ***p);
extern size_t discord_modify_guild_role_positions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_role_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_positions_params **p);
