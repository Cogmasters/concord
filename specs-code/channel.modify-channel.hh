/* This file is generated from specs/channel.modify-channel.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/channel#modify-channel */
/* This is defined at specs/channel.modify-channel.json:8:22 */
struct params {
  /* specs/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/channel.modify-channel.json:12:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  int type;

  /* specs/channel.modify-channel.json:13:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  int position;

  /* specs/channel.modify-channel.json:14:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}'
  */
  char *topic;

  /* specs/channel.modify-channel.json:15:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}'
  */
  bool nsfw;

  /* specs/channel.modify-channel.json:16:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int rate_limit_per_user;

  /* specs/channel.modify-channel.json:17:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int bitrate;

  /* specs/channel.modify-channel.json:18:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int user_limit;

  /* specs/channel.modify-channel.json:19:20
     '{ "name": "permission_overwrites", "type":{ "base":"discord::channel::overwrite::dati", "dec":"ntl" }, "inject_if_not":null}'
  */
  discord::channel::overwrite::dati **permission_overwrites;

  /* specs/channel.modify-channel.json:20:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  u64_snowflake_t parent_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[10];
    void *record_defined[10];
    void *record_null[10];
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
