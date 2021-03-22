/* This file is generated from specs/guild.ban.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/

namespace ban {
/* This is defined at specs/guild.ban.json:9:22 */
struct dati {
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  char reason[MAX_REASON_LEN];

  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  discord::user::dati *user; // partial user object

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
} // namespace ban
