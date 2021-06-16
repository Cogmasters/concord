/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild-template
*/

/* Title: Create Guild From Guild Template */
/* https://discord.com/developers/docs/resources/guild-template#create-guild-from-guild-template-json-params */
/* This is defined at specs/discord/guild-template.endpoints-params.json:10:22 */
struct discord_create_guild_from_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}'
  */
  char *name; // name of the guild

  /* specs/discord/guild-template.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon"}'
  */
  char *icon; // base64 128x128 image for the guild icon

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
extern void discord_create_guild_from_guild_template_params_cleanup_v(void *p);
extern void discord_create_guild_from_guild_template_params_cleanup(struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_init_v(void *p);
extern void discord_create_guild_from_guild_template_params_init(struct discord_create_guild_from_guild_template_params *p);
extern struct discord_create_guild_from_guild_template_params * discord_create_guild_from_guild_template_params_alloc();
extern void discord_create_guild_from_guild_template_params_free_v(void *p);
extern void discord_create_guild_from_guild_template_params_free(struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_from_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p);
extern size_t discord_create_guild_from_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p);
extern size_t discord_create_guild_from_guild_template_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_to_query(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_list_free_v(void **p);
extern void discord_create_guild_from_guild_template_params_list_free(struct discord_create_guild_from_guild_template_params **p);
extern void discord_create_guild_from_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_from_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_from_guild_template_params ***p);
extern size_t discord_create_guild_from_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_from_guild_template_params **p);

/* Title: Create Guild Template */
/* https://discord.com/developers/docs/resources/guild-template#create-guild-template-json-params */
/* This is defined at specs/discord/guild-template.endpoints-params.json:21:22 */
struct discord_create_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}'
  */
  char *name; // name of the guild

  /* specs/discord/guild-template.endpoints-params.json:25:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars"}'
  */
  char *description; // description for the template (0-120) chars

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
extern void discord_create_guild_template_params_cleanup_v(void *p);
extern void discord_create_guild_template_params_cleanup(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_init_v(void *p);
extern void discord_create_guild_template_params_init(struct discord_create_guild_template_params *p);
extern struct discord_create_guild_template_params * discord_create_guild_template_params_alloc();
extern void discord_create_guild_template_params_free_v(void *p);
extern void discord_create_guild_template_params_free(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_from_json_v(char *json, size_t len, void *p);
extern void discord_create_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_template_params *p);
extern size_t discord_create_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_template_params *p);
extern size_t discord_create_guild_template_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_template_params_to_query(char *json, size_t len, struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_list_free_v(void **p);
extern void discord_create_guild_template_params_list_free(struct discord_create_guild_template_params **p);
extern void discord_create_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_template_params ***p);
extern size_t discord_create_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_template_params **p);

/* Title: Modify Guild Template */
/* https://discord.com/developers/docs/resources/guild-template#modify-guild-template-json-params */
/* This is defined at specs/discord/guild-template.endpoints-params.json:32:22 */
struct discord_modify_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}'
  */
  char *name; // name of the guild

  /* specs/discord/guild-template.endpoints-params.json:36:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars"}'
  */
  char *description; // description for the template (0-120) chars

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
extern void discord_modify_guild_template_params_cleanup_v(void *p);
extern void discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_init_v(void *p);
extern void discord_modify_guild_template_params_init(struct discord_modify_guild_template_params *p);
extern struct discord_modify_guild_template_params * discord_modify_guild_template_params_alloc();
extern void discord_modify_guild_template_params_free_v(void *p);
extern void discord_modify_guild_template_params_free(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_from_json_v(char *json, size_t len, void *p);
extern void discord_modify_guild_template_params_from_json(char *json, size_t len, struct discord_modify_guild_template_params *p);
extern size_t discord_modify_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_template_params_to_json(char *json, size_t len, struct discord_modify_guild_template_params *p);
extern size_t discord_modify_guild_template_params_to_query_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_template_params_to_query(char *json, size_t len, struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_list_free_v(void **p);
extern void discord_modify_guild_template_params_list_free(struct discord_modify_guild_template_params **p);
extern void discord_modify_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_template_params_list_from_json(char *str, size_t len, struct discord_modify_guild_template_params ***p);
extern size_t discord_modify_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_template_params_list_to_json(char *str, size_t len, struct discord_modify_guild_template_params **p);
