/* This file is generated from specs/discord/channel.create-channel-invite.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#create-channel-invite */
/* This is defined at specs/discord/channel.create-channel-invite.json:8:22 */
struct discord_create_channel_invite_params {
  /* specs/discord/channel.create-channel-invite.json:11:20
     '{ "name": "max_age", "type":{ "base":"int" } }'
  */
  int max_age;

  /* specs/discord/channel.create-channel-invite.json:12:20
     '{ "name": "max_uses", "type":{ "base":"int" } }'
  */
  int max_uses;

  /* specs/discord/channel.create-channel-invite.json:13:20
     '{ "name": "temporary", "type":{ "base":"bool"}}'
  */
  bool temporary;

  /* specs/discord/channel.create-channel-invite.json:14:20
     '{ "name": "unique", "type":{ "base":"bool"}}'
  */
  bool unique;

  /* specs/discord/channel.create-channel-invite.json:15:20
     '{ "name": "target_type", "type":{ "base":"int" },
          "option":true, "inject_if_not":0}'
  */
  int target_type;

  /* specs/discord/channel.create-channel-invite.json:17:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, 
          "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t target_user_id;

  /* specs/discord/channel.create-channel-invite.json:19:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, 
          "option":true, "inject_if_not":0}'
  */
  u64_snowflake_t target_application_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[7];
    void *record_defined[7];
    void *record_null[7];
  } __M; // metadata
};
extern void discord_create_channel_invite_params_cleanup_v(void *p);
extern void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_init_v(void *p);
extern void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p);
extern struct discord_create_channel_invite_params * discord_create_channel_invite_params_alloc();
extern void discord_create_channel_invite_params_free_v(void *p);
extern void discord_create_channel_invite_params_free(struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern size_t discord_create_channel_invite_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_json(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern size_t discord_create_channel_invite_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_channel_invite_params_to_query(char *json, size_t len, struct discord_create_channel_invite_params *p);
extern void discord_create_channel_invite_params_list_free_v(void **p);
extern void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **p);
extern void discord_create_channel_invite_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_channel_invite_params_list_from_json(char *str, size_t len, struct discord_create_channel_invite_params ***p);
extern size_t discord_create_channel_invite_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_channel_invite_params_list_to_json(char *str, size_t len, struct discord_create_channel_invite_params **p);
