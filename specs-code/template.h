/* This file is generated from specs/template.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/template#template-object-template-structure
*/

/* Title: Template Structure */
/* This is defined at specs/template.json:9:22 */
struct discord_Template_dati {
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *code; // @todo find fixed size limit

  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  char *name; // @todo find fixed size limit

  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
  char *description; // @todo find fixed size limit

  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
  int usage_count;

  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t creator_id;

  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user_dati", "dec":"*" }}'
  */
  struct discord_user_dati *creator;

  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t created_at;

  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  u64_unix_ms_t updated_at;

  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t source_guild_id;

  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild_dati", "dec":"*" }}'
  */
  struct discord_guild_dati *serialized_source_guild;

  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
  bool is_dirty;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[11];
    void *record_defined[11];
    void *record_null[11];
  } __M; // metadata
};
extern void discord_Template_dati_cleanup_v(void *p);
extern void discord_Template_dati_cleanup(struct discord_Template_dati *p);
extern void discord_Template_dati_init_v(void *p);
extern void discord_Template_dati_init(struct discord_Template_dati *p);
extern struct discord_Template_dati * discord_Template_dati_alloc();
extern void discord_Template_dati_free_v(void *p);
extern void discord_Template_dati_free(struct discord_Template_dati *p);
extern void discord_Template_dati_from_json_v(char *json, size_t len, void *p);
extern void discord_Template_dati_from_json(char *json, size_t len, struct discord_Template_dati *p);
extern size_t discord_Template_dati_to_json_v(char *json, size_t len, void *p);
extern size_t discord_Template_dati_to_json(char *json, size_t len, struct discord_Template_dati *p);
extern size_t discord_Template_dati_to_query_v(char *json, size_t len, void *p);
extern size_t discord_Template_dati_to_query(char *json, size_t len, struct discord_Template_dati *p);
extern void discord_Template_dati_list_free_v(void **p);
extern void discord_Template_dati_list_free(struct discord_Template_dati **p);
extern void discord_Template_dati_list_from_json_v(char *str, size_t len, void *p);
extern void discord_Template_dati_list_from_json(char *str, size_t len, struct discord_Template_dati ***p);
extern size_t discord_Template_dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_Template_dati_list_to_json(char *str, size_t len, struct discord_Template_dati **p);
