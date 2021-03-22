/* This file is generated from specs/guild.membership_screening.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/


namespace field_type {
enum code {
  TERMS = 0,
};
} // namespace field_type

namespace field {
/* https://discord.com/developers/docs/resources/guild#membership-screening-object-membership-screening-field-structure */
/* This is defined at specs/guild.membership_screening.json:17:22 */
struct dati {
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"field_type::code" }}'
  */
  field_type::code field_type;

  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
  char *label;

  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  //@todo values (null);

  /* specs/guild.membership_screening.json:23:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
} // namespace field

/* This is defined at specs/guild.membership_screening.json:27:22 */
struct dati {
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  uint64_t version;

  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
  */
  discord::guild::membership_screening::field::dati **fields;

  /* specs/guild.membership_screening.json:32:20
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
extern void dati_cleanup_v(void *p);
extern void dati_cleanup(struct dati *p);
extern void dati_init_v(void *p);
extern void dati_init(struct dati *p);
extern struct dati * dati_alloc();
extern void dati_free_v(void *p);
extern void dati_free(struct dati *p);
extern void dati_from_json_v(char *json, size_t len, void *p);
extern void dati_from_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_json_v(char *json, size_t len, void *p);
extern size_t dati_to_json(char *json, size_t len, struct dati *p);
extern size_t dati_to_query_v(char *json, size_t len, void *p);
extern size_t dati_to_query(char *json, size_t len, struct dati *p);
extern void dati_list_free_v(void **p);
extern void dati_list_free(struct dati **p);
extern void dati_list_from_json_v(char *str, size_t len, void *p);
extern void dati_list_from_json(char *str, size_t len, struct dati ***p);
extern size_t dati_list_to_json_v(char *str, size_t len, void *p);
extern size_t dati_list_to_json(char *str, size_t len, struct dati **p);
