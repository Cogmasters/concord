/* This file is generated from specs/discord/audit_log.get-guild-audit-log.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_get_guild_audit_log_params_from_json(char *json, size_t len, struct discord_get_guild_audit_log_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/audit_log.get-guild-audit-log.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
                "(user_id):F,"
  /* specs/discord/audit_log.get-guild-audit-log.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }'
  */
                "(action_type):d,"
  /* specs/discord/audit_log.get-guild-audit-log.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
                "(before):F,"
  /* specs/discord/audit_log.get-guild-audit-log.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                "(limit):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.get-guild-audit-log.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
                orka_strtoull, &p->user_id,
  /* specs/discord/audit_log.get-guild-audit-log.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }'
  */
                &p->action_type,
  /* specs/discord/audit_log.get-guild-audit-log.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
                orka_strtoull, &p->before,
  /* specs/discord/audit_log.get-guild-audit-log.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_get_guild_audit_log_params_use_default_inject_settings(struct discord_get_guild_audit_log_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.get-guild-audit-log.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
  if (p->user_id != 0)
    p->__M.arg_switches[0] = &p->user_id;

  /* specs/discord/audit_log.get-guild-audit-log.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }'
  */
  if (p->action_type != 0)
    p->__M.arg_switches[1] = &p->action_type;

  /* specs/discord/audit_log.get-guild-audit-log.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
  if (p->before != 0)
    p->__M.arg_switches[2] = &p->before;

  /* specs/discord/audit_log.get-guild-audit-log.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  if (p->limit != 0)
    p->__M.arg_switches[3] = &p->limit;

}

size_t discord_get_guild_audit_log_params_to_json(char *json, size_t len, struct discord_get_guild_audit_log_params *p)
{
  size_t r;
  discord_get_guild_audit_log_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.get-guild-audit-log.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
                "(user_id):|F|,"
  /* specs/discord/audit_log.get-guild-audit-log.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }'
  */
                "(action_type):d,"
  /* specs/discord/audit_log.get-guild-audit-log.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
                "(before):|F|,"
  /* specs/discord/audit_log.get-guild-audit-log.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                "(limit):d,"
                "@arg_switches:b",
  /* specs/discord/audit_log.get-guild-audit-log.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
                orka_ulltostr, &p->user_id,
  /* specs/discord/audit_log.get-guild-audit-log.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }'
  */
                &p->action_type,
  /* specs/discord/audit_log.get-guild-audit-log.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
                orka_ulltostr, &p->before,
  /* specs/discord/audit_log.get-guild-audit-log.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_get_guild_audit_log_params_cleanup_v(void *p) {
  discord_get_guild_audit_log_params_cleanup((struct discord_get_guild_audit_log_params *)p);
}

void discord_get_guild_audit_log_params_init_v(void *p) {
  discord_get_guild_audit_log_params_init((struct discord_get_guild_audit_log_params *)p);
}

void discord_get_guild_audit_log_params_free_v(void *p) {
 discord_get_guild_audit_log_params_free((struct discord_get_guild_audit_log_params *)p);
};

void discord_get_guild_audit_log_params_from_json_v(char *json, size_t len, void *p) {
 discord_get_guild_audit_log_params_from_json(json, len, (struct discord_get_guild_audit_log_params*)p);
}

size_t discord_get_guild_audit_log_params_to_json_v(char *json, size_t len, void *p) {
  return discord_get_guild_audit_log_params_to_json(json, len, (struct discord_get_guild_audit_log_params*)p);
}

void discord_get_guild_audit_log_params_list_free_v(void **p) {
  discord_get_guild_audit_log_params_list_free((struct discord_get_guild_audit_log_params**)p);
}

void discord_get_guild_audit_log_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_get_guild_audit_log_params_list_from_json(str, len, (struct discord_get_guild_audit_log_params ***)p);
}

size_t discord_get_guild_audit_log_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_get_guild_audit_log_params_list_to_json(str, len, (struct discord_get_guild_audit_log_params **)p);
}


void discord_get_guild_audit_log_params_cleanup(struct discord_get_guild_audit_log_params *d) {
  /* specs/discord/audit_log.get-guild-audit-log.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
  //p->user_id is a scalar
  /* specs/discord/audit_log.get-guild-audit-log.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }'
  */
  //p->action_type is a scalar
  /* specs/discord/audit_log.get-guild-audit-log.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */
  //p->before is a scalar
  /* specs/discord/audit_log.get-guild-audit-log.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  //p->limit is a scalar
}

void discord_get_guild_audit_log_params_init(struct discord_get_guild_audit_log_params *p) {
  memset(p, 0, sizeof(struct discord_get_guild_audit_log_params));
  /* specs/discord/audit_log.get-guild-audit-log.json:11:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */

  /* specs/discord/audit_log.get-guild-audit-log.json:12:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "inject_if_not":0 }'
  */

  /* specs/discord/audit_log.get-guild-audit-log.json:13:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }'
  */

  /* specs/discord/audit_log.get-guild-audit-log.json:14:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0 }'
  */

}
struct discord_get_guild_audit_log_params* discord_get_guild_audit_log_params_alloc() {
  struct discord_get_guild_audit_log_params *p= (struct discord_get_guild_audit_log_params*)malloc(sizeof(struct discord_get_guild_audit_log_params));
  discord_get_guild_audit_log_params_init(p);
  return p;
}

void discord_get_guild_audit_log_params_free(struct discord_get_guild_audit_log_params *p) {
  discord_get_guild_audit_log_params_cleanup(p);
  free(p);
}

void discord_get_guild_audit_log_params_list_free(struct discord_get_guild_audit_log_params **p) {
  ntl_free((void**)p, (vfvp)discord_get_guild_audit_log_params_cleanup);
}

void discord_get_guild_audit_log_params_list_from_json(char *str, size_t len, struct discord_get_guild_audit_log_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_get_guild_audit_log_params);
  d.init_elem = discord_get_guild_audit_log_params_init_v;
  d.elem_from_buf = discord_get_guild_audit_log_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_get_guild_audit_log_params_list_to_json(char *str, size_t len, struct discord_get_guild_audit_log_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_get_guild_audit_log_params_to_json_v);
}

