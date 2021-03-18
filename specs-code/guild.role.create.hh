/* This file is generated from specs/guild.role.create.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/guild#create-guild-role */
/* This is defined at specs/guild.role.create.json:8:22 */
struct params {
  /* specs/guild.role.create.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/guild.role.create.json:12:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"permissions::bitwise_flags" }, "inject_if_not":0}'
  */
  permissions::bitwise_flags permissions;

  /* specs/guild.role.create.json:13:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  int color;

  /* specs/guild.role.create.json:14:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool hoist;

  /* specs/guild.role.create.json:15:20
     '{ "name": "memtionable", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  bool memtionable;

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
