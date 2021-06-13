/* This file is generated from specs/discord/guild.modify-guild-role.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#modify-guild-role-json-params */
/* This is defined at specs/discord/guild.modify-guild-role.json:8:22 */
struct discord_modify_guild_role_params {
  /* specs/discord/guild.modify-guild-role.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, 
          "option":true, "inject_if_not":null, "comment":"name of the role"}'
  */
  char *name; // name of the role

  /* specs/discord/guild.modify-guild-role.json:13:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}'
  */
  enum discord_permissions_bitwise_flags permissions; // bitwise value of the enabled/disabled permissions

  /* specs/discord/guild.modify-guild-role.json:15:20
     '{ "name": "color", "type":{ "base":"int" }, 
          "option":true, "inject_if_not":0, "comment":"RGB color value"}'
  */
  int color; // RGB color value

  /* specs/discord/guild.modify-guild-role.json:17:20
     '{ "name": "hoist", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}'
  */
  bool hoist; // whether the role should be displayed separately in the sidebar

  /* specs/discord/guild.modify-guild-role.json:19:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, 
          "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}'
  */
  bool mentionable; // whether the role should be mentionable

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
extern void discord_modify_guild_role_params_cleanup_v(void *p);
extern void discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_init_v(void *p);
extern void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *p);
extern struct discord_modify_guild_role_params * discord_modify_guild_role_params_alloc();
extern void discord_modify_guild_role_params_free_v(void *p);
extern void discord_modify_guild_role_params_free(struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_guild_role_params_from_json(char *json, size_t len, struct discord_modify_guild_role_params *p);
extern size_t discord_modify_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_params_to_json(char *json, size_t len, struct discord_modify_guild_role_params *p);
extern size_t discord_modify_guild_role_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_role_params_to_query(char *json, size_t len, struct discord_modify_guild_role_params *p);
extern void discord_modify_guild_role_params_list_free_v(void **p);
extern void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **p);
extern void discord_modify_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_role_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_params ***p);
extern size_t discord_modify_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_role_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_params **p);
