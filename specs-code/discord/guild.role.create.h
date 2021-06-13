/* This file is generated from specs/discord/guild.role.create.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild-role */
/* This is defined at specs/discord/guild.role.create.json:8:22 */
struct discord_create_guild_role_params {
  /* specs/discord/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/discord/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, 
          "inject_if_not":0}'
  */
  enum discord_permissions_bitwise_flags permissions;

  /* specs/discord/guild.role.create.json:14:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int color;

  /* specs/discord/guild.role.create.json:15:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool hoist;

  /* specs/discord/guild.role.create.json:16:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool mentionable;

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
extern void discord_create_guild_role_params_cleanup_v(void *p);
extern void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_init_v(void *p);
extern void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p);
extern struct discord_create_guild_role_params * discord_create_guild_role_params_alloc();
extern void discord_create_guild_role_params_free_v(void *p);
extern void discord_create_guild_role_params_free(struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params *p);
extern size_t discord_create_guild_role_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_role_params_to_json(char *json, size_t len, struct discord_create_guild_role_params *p);
extern size_t discord_create_guild_role_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_role_params_to_query(char *json, size_t len, struct discord_create_guild_role_params *p);
extern void discord_create_guild_role_params_list_free_v(void **p);
extern void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **p);
extern void discord_create_guild_role_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_role_params_list_from_json(char *str, size_t len, struct discord_create_guild_role_params ***p);
extern size_t discord_create_guild_role_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_role_params_list_to_json(char *str, size_t len, struct discord_create_guild_role_params **p);
