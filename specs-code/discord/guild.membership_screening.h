/* This file is generated from specs/discord/guild.membership_screening.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/


enum discord_guild_membership_screening_field_type {
  DISCORD_GUILD_MEMBERSHIP_SCREENING_TERMS = 0,
};
extern char* discord_guild_membership_screening_field_type_to_string(enum discord_guild_membership_screening_field_type);
extern enum discord_guild_membership_screening_field_type discord_guild_membership_screening_field_type_from_string(char*);
extern bool discord_guild_membership_screening_field_type_has(enum discord_guild_membership_screening_field_type, char*);

/* https://discord.com/developers/docs/resources/guild#membership-screening-object-membership-screening-field-structure */
/* This is defined at specs/discord/guild.membership_screening.json:17:22 */
struct discord_guild_membership_screening_field {
  /* specs/discord/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */
  enum discord_guild_membership_screening_field_type field_type;

  /* specs/discord/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
  char *label;

  /* specs/discord/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  //@todo values (null);

  /* specs/discord/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */
  bool required;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
};
extern void discord_guild_membership_screening_field_cleanup_v(void *p);
extern void discord_guild_membership_screening_field_cleanup(struct discord_guild_membership_screening_field *p);
extern void discord_guild_membership_screening_field_init_v(void *p);
extern void discord_guild_membership_screening_field_init(struct discord_guild_membership_screening_field *p);
extern struct discord_guild_membership_screening_field * discord_guild_membership_screening_field_alloc();
extern void discord_guild_membership_screening_field_free_v(void *p);
extern void discord_guild_membership_screening_field_free(struct discord_guild_membership_screening_field *p);
extern void discord_guild_membership_screening_field_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_membership_screening_field_from_json(char *json, size_t len, struct discord_guild_membership_screening_field *p);
extern size_t discord_guild_membership_screening_field_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_membership_screening_field_to_json(char *json, size_t len, struct discord_guild_membership_screening_field *p);
extern size_t discord_guild_membership_screening_field_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_membership_screening_field_to_query(char *json, size_t len, struct discord_guild_membership_screening_field *p);
extern void discord_guild_membership_screening_field_list_free_v(void **p);
extern void discord_guild_membership_screening_field_list_free(struct discord_guild_membership_screening_field **p);
extern void discord_guild_membership_screening_field_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_membership_screening_field_list_from_json(char *str, size_t len, struct discord_guild_membership_screening_field ***p);
extern size_t discord_guild_membership_screening_field_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_membership_screening_field_list_to_json(char *str, size_t len, struct discord_guild_membership_screening_field **p);

/* This is defined at specs/discord/guild.membership_screening.json:27:22 */
struct discord_guild_membership_screening {
  /* specs/discord/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  uint64_t version;

  /* specs/discord/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */
  struct discord_guild_membership_screening_field **fields;

  /* specs/discord/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  char *description;

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
extern void discord_guild_membership_screening_cleanup_v(void *p);
extern void discord_guild_membership_screening_cleanup(struct discord_guild_membership_screening *p);
extern void discord_guild_membership_screening_init_v(void *p);
extern void discord_guild_membership_screening_init(struct discord_guild_membership_screening *p);
extern struct discord_guild_membership_screening * discord_guild_membership_screening_alloc();
extern void discord_guild_membership_screening_free_v(void *p);
extern void discord_guild_membership_screening_free(struct discord_guild_membership_screening *p);
extern void discord_guild_membership_screening_from_json_v(char *json, size_t len, void *p);
extern void discord_guild_membership_screening_from_json(char *json, size_t len, struct discord_guild_membership_screening *p);
extern size_t discord_guild_membership_screening_to_json_v(char *json, size_t len, void *p);
extern size_t discord_guild_membership_screening_to_json(char *json, size_t len, struct discord_guild_membership_screening *p);
extern size_t discord_guild_membership_screening_to_query_v(char *json, size_t len, void *p);
extern size_t discord_guild_membership_screening_to_query(char *json, size_t len, struct discord_guild_membership_screening *p);
extern void discord_guild_membership_screening_list_free_v(void **p);
extern void discord_guild_membership_screening_list_free(struct discord_guild_membership_screening **p);
extern void discord_guild_membership_screening_list_from_json_v(char *str, size_t len, void *p);
extern void discord_guild_membership_screening_list_from_json(char *str, size_t len, struct discord_guild_membership_screening ***p);
extern size_t discord_guild_membership_screening_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_guild_membership_screening_list_to_json(char *str, size_t len, struct discord_guild_membership_screening **p);
