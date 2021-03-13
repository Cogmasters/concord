/* This file is generated from specs/template.create-guild-template.json, Please don't edit it. */
/*

*/

/* https://discord.com/developers/docs/resources/template#create-guild-template */
/* This is defined at specs/template.create-guild-template.json:8:22 */
struct params {
  /* specs/template.create-guild-template.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[100+1]"}, "comment":"name of the guild"}'
  */
  char name[100+1]; // name of the guild

  /* specs/template.create-guild-template.json:12:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[120+1]" }, 
          "comment":"description for the template (0-120) chars"}'
  */
  char description[120+1]; // description for the template (0-120) chars

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
