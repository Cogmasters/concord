/* This file is generated from specs/channel.group-dm-add-recipient.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#group-dm-add-recipient */
/* This is defined at specs/channel.group-dm-add-recipient.json:8:22 */
struct discord_group_dm_add_recipient_params {
  /* specs/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
  char *access_token;

  /* specs/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */
  char *nick;

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
extern void discord_group_dm_add_recipient_params_cleanup_v(void *p);
extern void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_init_v(void *p);
extern void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p);
extern struct discord_group_dm_add_recipient_params * discord_group_dm_add_recipient_params_alloc();
extern void discord_group_dm_add_recipient_params_free_v(void *p);
extern void discord_group_dm_add_recipient_params_free(struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern size_t discord_group_dm_add_recipient_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern size_t discord_group_dm_add_recipient_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_to_query(char *json, size_t len, struct discord_group_dm_add_recipient_params *p);
extern void discord_group_dm_add_recipient_params_list_free_v(void **p);
extern void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p);
extern void discord_group_dm_add_recipient_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p);
extern size_t discord_group_dm_add_recipient_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p);
