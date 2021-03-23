/* This file is generated from specs/user.create-group-dm.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/user#create-group-dm */
/* This is defined at specs/user.create-group-dm.json:8:22 */
struct discord_user_create_group_dm_params {
  /* specs/user.create-group-dm.json:11:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}'
  */
  ja_str **access_tokens; // access tokens of users that have granted your app the gdm.join scope

  /* specs/user.create-group-dm.json:13:19
     '{ "name":"nick", "type":{ "base":"char", "dec":"*"}, 
          "todo":true,
          "comment":"ia dictionary of user ids to their respective nicknames"}'
  */
  //@todo nick ia dictionary of user ids to their respective nicknames;

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
extern void discord_user_create_group_dm_params_cleanup_v(void *p);
extern void discord_user_create_group_dm_params_cleanup(struct discord_user_create_group_dm_params *p);
extern void discord_user_create_group_dm_params_init_v(void *p);
extern void discord_user_create_group_dm_params_init(struct discord_user_create_group_dm_params *p);
extern struct discord_user_create_group_dm_params * discord_user_create_group_dm_params_alloc();
extern void discord_user_create_group_dm_params_free_v(void *p);
extern void discord_user_create_group_dm_params_free(struct discord_user_create_group_dm_params *p);
extern void discord_user_create_group_dm_params_from_json_v(char *json, size_t len, void *p);
extern void discord_user_create_group_dm_params_from_json(char *json, size_t len, struct discord_user_create_group_dm_params *p);
extern size_t discord_user_create_group_dm_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_user_create_group_dm_params_to_json(char *json, size_t len, struct discord_user_create_group_dm_params *p);
extern size_t discord_user_create_group_dm_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_user_create_group_dm_params_to_query(char *json, size_t len, struct discord_user_create_group_dm_params *p);
extern void discord_user_create_group_dm_params_list_free_v(void **p);
extern void discord_user_create_group_dm_params_list_free(struct discord_user_create_group_dm_params **p);
extern void discord_user_create_group_dm_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_user_create_group_dm_params_list_from_json(char *str, size_t len, struct discord_user_create_group_dm_params ***p);
extern size_t discord_user_create_group_dm_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_user_create_group_dm_params_list_to_json(char *str, size_t len, struct discord_user_create_group_dm_params **p);
