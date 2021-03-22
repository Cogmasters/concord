/* This file is generated from specs/webhook.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
*/


namespace webhook {
namespace types {
enum code {
  INCOMING = 1,
  CHANNEL_FOLLOWER = 2,
};
} // namespace types
} // namespace webhook

namespace webhook {
/* Title: Webhook Structure */
/* This is defined at specs/webhook.json:19:22 */
struct dati {
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */
  discord::webhook::types::code type;

  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t guild_id;

  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t channel_id;

  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  discord::user::dati *user;

  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
  char name[WEBHOOK_NAME_LEN];

  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *avatar; // @todo fixed size limit

  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  char *token; // @todo fixed size limit

  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t application_id;

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
} // namespace webhook
