/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/user.endpoints-params.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/user
 */


/**
 * @brief Modify Current User
 *
 * @see https://discord.com/developers/docs/resources/user#modify-current-user-json-params
 * @note defined at specs/discord/user.endpoints-params.json:10:22
 */
struct discord_modify_current_user_params {
  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
  char *username;

  /* specs/discord/user.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
  char *avatar; ///< base64 encoded image data

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
extern void discord_modify_current_user_params_cleanup_v(void *p);
extern void discord_modify_current_user_params_cleanup(struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_init_v(void *p);
extern void discord_modify_current_user_params_init(struct discord_modify_current_user_params *p);
extern struct discord_modify_current_user_params * discord_modify_current_user_params_alloc();
extern void discord_modify_current_user_params_free_v(void *p);
extern void discord_modify_current_user_params_free(struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_current_user_params_from_json(char *json, size_t len, struct discord_modify_current_user_params **pp);
extern size_t discord_modify_current_user_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_user_params_to_json(char *json, size_t len, struct discord_modify_current_user_params *p);
extern size_t discord_modify_current_user_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_current_user_params_to_query(char *json, size_t len, struct discord_modify_current_user_params *p);
extern void discord_modify_current_user_params_list_free_v(void **p);
extern void discord_modify_current_user_params_list_free(struct discord_modify_current_user_params **p);
extern void discord_modify_current_user_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_current_user_params_list_from_json(char *str, size_t len, struct discord_modify_current_user_params ***p);
extern size_t discord_modify_current_user_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_current_user_params_list_to_json(char *str, size_t len, struct discord_modify_current_user_params **p);

/**
 * @brief Create Group DM
 *
 * @see https://discord.com/developers/docs/resources/user#create-group-dm-json-params
 * @note defined at specs/discord/user.endpoints-params.json:21:22
 */
struct discord_create_group_dm_params {
  /* specs/discord/user.endpoints-params.json:24:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
  ja_str **access_tokens; ///< access tokens of users that have granted your app the gdm.join scope

  /* specs/discord/user.endpoints-params.json:26:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"ia dictionary of user ids to their respective nicknames"}' */
  ja_u64 **nicks; ///< ia dictionary of user ids to their respective nicknames

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[2];
    void *record_defined[2];
    void *record_null[2];
  } __M; // metadata
/// @endcond
};
extern void discord_create_group_dm_params_cleanup_v(void *p);
extern void discord_create_group_dm_params_cleanup(struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_init_v(void *p);
extern void discord_create_group_dm_params_init(struct discord_create_group_dm_params *p);
extern struct discord_create_group_dm_params * discord_create_group_dm_params_alloc();
extern void discord_create_group_dm_params_free_v(void *p);
extern void discord_create_group_dm_params_free(struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_group_dm_params_from_json(char *json, size_t len, struct discord_create_group_dm_params **pp);
extern size_t discord_create_group_dm_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_group_dm_params_to_json(char *json, size_t len, struct discord_create_group_dm_params *p);
extern size_t discord_create_group_dm_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_group_dm_params_to_query(char *json, size_t len, struct discord_create_group_dm_params *p);
extern void discord_create_group_dm_params_list_free_v(void **p);
extern void discord_create_group_dm_params_list_free(struct discord_create_group_dm_params **p);
extern void discord_create_group_dm_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_group_dm_params_list_from_json(char *str, size_t len, struct discord_create_group_dm_params ***p);
extern size_t discord_create_group_dm_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_group_dm_params_list_to_json(char *str, size_t len, struct discord_create_group_dm_params **p);
