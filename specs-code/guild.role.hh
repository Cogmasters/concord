/* This file is generated from specs/guild.role.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/

namespace role {
namespace tags {
/* Title: Role Tags Structure */
/* This is defined at specs/guild.role.json:9:22 */
struct dati {
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t bot_id;

  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t integration_id;

  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
  int premium_subscriber;

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
} // namespace tags
} // namespace role

namespace role {
/* Title: Role Object */
/* This is defined at specs/guild.role.json:20:22 */
struct dati {
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
  char name[MAX_NAME_LEN];

  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
  int color;

  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
  bool hoist;

  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  int position;

  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
  char *permissions;

  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
  bool managed;

  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
  bool mentionable;

  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
  discord::guild::role::tags::dati *tags;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[9];
    void *record_defined[9];
    void *record_null[9];
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
} // namespace role
