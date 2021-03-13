/* This file is generated from specs/channel.create-channel-invite.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#create-channel-invite */
/* This is defined at specs/channel.create-channel-invite.json:8:22 */
struct params {
  /* specs/channel.create-channel-invite.json:11:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"url"}'
  */
  u64_snowflake_t channel_id;

  /* specs/channel.create-channel-invite.json:12:20
     '{ "name": "max_age", "type":{ "base":"int" } }'
  */
  int max_age;

  /* specs/channel.create-channel-invite.json:13:20
     '{ "name": "max_uses", "type":{ "base":"int" } }'
  */
  int max_uses;

  /* specs/channel.create-channel-invite.json:14:20
     '{ "name": "temporary", "type":{ "base":"bool"}}'
  */
  bool temporary;

  /* specs/channel.create-channel-invite.json:15:20
     '{ "name": "unique", "type":{ "base":"bool"}}'
  */
  bool unique;

  /* specs/channel.create-channel-invite.json:16:20
     '{ "name": "target_user", "type":{ "base":"char", "dec":"*"}, 
          "option":true, "inject_if_not":null}'
  */
  char *target_user;

  /* specs/channel.create-channel-invite.json:18:20
     '{ "name": "target_user_type", "type":{ "base":"int" },
          "option":true, "inject_if_not":0}'
  */
  int target_user_type;

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
extern void params_cleanup_v(void *p);
extern void params_cleanup(struct params *p);
extern void params_init_v(void *p);
extern void params_init(struct params *p);
extern struct params * params_alloc();
extern void params_free_v(void *p);
extern void params_free(struct params *p);
extern void params_from_json_v(char *json, size_t len, void *p);
extern void params_from_json(char *json, size_t len, struct params *p);
extern size_t params_to_json_v(char *json, size_t len, void *p);
extern size_t params_to_json(char *json, size_t len, struct params *p);
extern size_t params_to_query_v(char *json, size_t len, void *p);
extern size_t params_to_query(char *json, size_t len, struct params *p);
extern void params_list_free_v(void **p);
extern void params_list_free(struct params **p);
extern void params_list_from_json_v(char *str, size_t len, void *p);
extern void params_list_from_json(char *str, size_t len, struct params ***p);
extern size_t params_list_to_json_v(char *str, size_t len, void *p);
extern size_t params_list_to_json(char *str, size_t len, struct params **p);
extern void params_use_default_inject_settings(struct params *p);
