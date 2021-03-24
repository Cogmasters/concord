/* This file is generated from specs/channel.edit-channel-permissions.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#edit-channel-permissions */
/* This is defined at specs/channel.edit-channel-permissions.json:8:22 */
struct discord_edit_channel_permissions_params {
  /* specs/channel.edit-channel-permissions.json:11:20
     '{ "name": "allow", "type":{ "base":"char", "dec":"*"}}'
  */
  char *allow;

  /* specs/channel.edit-channel-permissions.json:12:20
     '{ "name": "deny", "type":{ "base":"char", "dec":"*"}}'
  */
  char *deny;

  /* specs/channel.edit-channel-permissions.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[3];
    void *record_defined[3];
    void *record_null[3];
  } __M; // metadata
};
extern void discord_edit_channel_permissions_params_cleanup_v(void *p);
extern void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_init_v(void *p);
extern void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p);
extern struct discord_edit_channel_permissions_params * discord_edit_channel_permissions_params_alloc();
extern void discord_edit_channel_permissions_params_free_v(void *p);
extern void discord_edit_channel_permissions_params_free(struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_from_json_v(char *json, size_t len, void *p);
extern void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern size_t discord_edit_channel_permissions_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern size_t discord_edit_channel_permissions_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_to_query(char *json, size_t len, struct discord_edit_channel_permissions_params *p);
extern void discord_edit_channel_permissions_params_list_free_v(void **p);
extern void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **p);
extern void discord_edit_channel_permissions_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_edit_channel_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_channel_permissions_params ***p);
extern size_t discord_edit_channel_permissions_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_edit_channel_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_channel_permissions_params **p);
