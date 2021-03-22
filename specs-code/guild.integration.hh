/* This file is generated from specs/guild.integration.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/


namespace integration {
namespace expire_behaviors {
enum code {
  REMOVE_ROLE = 0,
  KICK = 1,
};
} // namespace expire_behaviors
} // namespace integration

namespace integration {
namespace account {
/* Title: Integration Account Structure */
/* https://discord.com/developers/docs/resources/guild#integration-account-object-integration-account-structure */
/* This is defined at specs/guild.integration.json:21:22 */
struct dati {
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

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
} // namespace account
} // namespace integration

namespace integration {
namespace application {
/* Title: Integration Application Object */
/* https://discord.com/developers/docs/resources/guild#integration-application-object-integration-application-structure */
/* This is defined at specs/guild.integration.json:31:22 */
struct dati {
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
  char *name;

  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  char icon[MAX_SHA256_LEN];

  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
  char *description;

  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
  char *summary;

  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"discord::user::dati", "dec":"*" }, "option":true}'
  */
  discord::user::dati *bot;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
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
} // namespace application
} // namespace integration

namespace integration {
/* Title: Integration Structure */
/* https://discord.com/developers/docs/resources/guild#integration-object-integration-structure */
/* This is defined at specs/guild.integration.json:45:22 */
struct dati {
  /* specs/guild.integration.json:48:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  u64_snowflake_t id;

  /* specs/guild.integration.json:49:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  char *name;

  /* specs/guild.integration.json:50:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  char *type;

  /* specs/guild.integration.json:51:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
  bool enabled;

  /* specs/guild.integration.json:52:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
  bool syncing;

  /* specs/guild.integration.json:53:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  u64_snowflake_t role_id;

  /* specs/guild.integration.json:54:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
  bool enable_emotions;

  /* specs/guild.integration.json:55:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"discord::guild::integration::expire_behaviors::code"}}'
  */
  discord::guild::integration::expire_behaviors::code expire_behavior;

  /* specs/guild.integration.json:56:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
  int expire_grace_period;

  /* specs/guild.integration.json:57:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "opt":true}'
  */
  discord::user::dati *user;

  /* specs/guild.integration.json:58:20
     '{ "name": "account", "type":{ "base":"discord::guild::integration::account::dati", "dec":"*"}}'
  */
  discord::guild::integration::account::dati *account;

  /* specs/guild.integration.json:59:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  u64_unix_ms_t synced_at;

  /* specs/guild.integration.json:60:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
  int subscriber_count;

  /* specs/guild.integration.json:61:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  bool revoked;

  /* specs/guild.integration.json:62:20
     '{ "name": "application", "type":{ "base":"discord::guild::integration::application::dati", "dec":"*" }}'
  */
  discord::guild::integration::application::dati *application;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[15];
    void *record_defined[15];
    void *record_null[15];
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
} // namespace integration
