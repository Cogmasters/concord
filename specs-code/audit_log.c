/* This file is generated from specs/audit_log.json, Please don't edit it. */
#include "specs.h"
/*
(null)
*/

void discord_audit_log_dati_from_json(char *json, size_t len, struct discord_audit_log_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook_dati", "dec":"*" } }'
  */
                "(webhooks):F,"
  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user_dati", "dec":"*"}}'
  */
                "(users):F,"
  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry_dati", "dec":"*"}}'
  */
                "(audit_log_entries):F,"
  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration_dati", "dec":"ntl"}}'
  */
                "(integrations):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook_dati", "dec":"*" } }'
  */
                discord_webhook_dati_from_json, p->webhooks,
  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user_dati", "dec":"*"}}'
  */
                discord_user_dati_from_json, p->users,
  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry_dati", "dec":"*"}}'
  */
                discord_audit_log_entry_dati_from_json, p->audit_log_entries,
  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration_dati", "dec":"ntl"}}'
  */
                discord_guild_integration_dati_list_from_json, &p->integrations,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_dati_use_default_inject_settings(struct discord_audit_log_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook_dati", "dec":"*" } }'
  */
  p->__M.arg_switches[0] = p->webhooks;

  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user_dati", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->users;

  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry_dati", "dec":"*"}}'
  */
  p->__M.arg_switches[2] = p->audit_log_entries;

  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration_dati", "dec":"ntl"}}'
  */
  p->__M.arg_switches[3] = p->integrations;

}

size_t discord_audit_log_dati_to_json(char *json, size_t len, struct discord_audit_log_dati *p)
{
  size_t r;
  discord_audit_log_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook_dati", "dec":"*" } }'
  */
                "(webhooks):F,"
  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user_dati", "dec":"*"}}'
  */
                "(users):F,"
  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry_dati", "dec":"*"}}'
  */
                "(audit_log_entries):F,"
  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration_dati", "dec":"ntl"}}'
  */
                "(integrations):F,"
                "@arg_switches:b",
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook_dati", "dec":"*" } }'
  */
                discord_webhook_dati_to_json, p->webhooks,
  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user_dati", "dec":"*"}}'
  */
                discord_user_dati_to_json, p->users,
  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry_dati", "dec":"*"}}'
  */
                discord_audit_log_entry_dati_to_json, p->audit_log_entries,
  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration_dati", "dec":"ntl"}}'
  */
                discord_guild_integration_dati_list_to_json, p->integrations,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_dati_cleanup_v(void *p) {
  discord_audit_log_dati_cleanup((struct discord_audit_log_dati *)p);
}

void discord_audit_log_dati_init_v(void *p) {
  discord_audit_log_dati_init((struct discord_audit_log_dati *)p);
}

void discord_audit_log_dati_free_v(void *p) {
 discord_audit_log_dati_free((struct discord_audit_log_dati *)p);
};

void discord_audit_log_dati_from_json_v(char *json, size_t len, void *p) {
 discord_audit_log_dati_from_json(json, len, (struct discord_audit_log_dati*)p);
}

size_t discord_audit_log_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_dati_to_json(json, len, (struct discord_audit_log_dati*)p);
}

void discord_audit_log_dati_list_free_v(void **p) {
  discord_audit_log_dati_list_free((struct discord_audit_log_dati**)p);
}

void discord_audit_log_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_dati_list_from_json(str, len, (struct discord_audit_log_dati ***)p);
}

size_t discord_audit_log_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_dati_list_to_json(str, len, (struct discord_audit_log_dati **)p);
}


void discord_audit_log_dati_cleanup(struct discord_audit_log_dati *d) {
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook_dati", "dec":"*" } }'
  */
  if (d->webhooks)
    discord_webhook_dati_free(d->webhooks);
  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user_dati", "dec":"*"}}'
  */
  if (d->users)
    discord_user_dati_free(d->users);
  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry_dati", "dec":"*"}}'
  */
  if (d->audit_log_entries)
    discord_audit_log_entry_dati_free(d->audit_log_entries);
  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration_dati", "dec":"ntl"}}'
  */
  if (d->integrations)
    discord_guild_integration_dati_list_free(d->integrations);
}

void discord_audit_log_dati_init(struct discord_audit_log_dati *p) {
  memset(p, 0, sizeof(struct discord_audit_log_dati));
  /* specs/audit_log.json:11:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook_dati", "dec":"*" } }'
  */
  p->webhooks = discord_webhook_dati_alloc();

  /* specs/audit_log.json:12:18
     '{"name":"users", "type": { "base":"struct discord_user_dati", "dec":"*"}}'
  */
  p->users = discord_user_dati_alloc();

  /* specs/audit_log.json:13:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry_dati", "dec":"*"}}'
  */
  p->audit_log_entries = discord_audit_log_entry_dati_alloc();

  /* specs/audit_log.json:14:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration_dati", "dec":"ntl"}}'
  */

}
struct discord_audit_log_dati* discord_audit_log_dati_alloc() {
  struct discord_audit_log_dati *p= (struct discord_audit_log_dati*)malloc(sizeof(struct discord_audit_log_dati));
  discord_audit_log_dati_init(p);
  return p;
}

void discord_audit_log_dati_free(struct discord_audit_log_dati *p) {
  discord_audit_log_dati_cleanup(p);
  free(p);
}

void discord_audit_log_dati_list_free(struct discord_audit_log_dati **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_dati_cleanup);
}

void discord_audit_log_dati_list_from_json(char *str, size_t len, struct discord_audit_log_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_dati);
  d.init_elem = discord_audit_log_dati_init_v;
  d.elem_from_buf = discord_audit_log_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_audit_log_dati_list_to_json(char *str, size_t len, struct discord_audit_log_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_dati_to_json_v);
}


void discord_audit_log_entry_dati_from_json(char *json, size_t len, struct discord_audit_log_entry_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */
                "(target_id):?s,"
  /* specs/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change_dati", "dec":"*"}}'
  */
                "(changes):F,"
  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(user_id):F,"
  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_entry_events_code"}}'
  */
                "(action_type):d,"
  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info_dati", "dec":"*"}}'
  */
                "(options):F,"
  /* specs/audit_log.json:73:18
     '{"name":"reason", "type": {"base":"char", "dec":"[MAX_REASON_LEN]"}}'
  */
                "(reason):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */
                &p->target_id,
  /* specs/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change_dati", "dec":"*"}}'
  */
                discord_audit_log_change_dati_from_json, p->changes,
  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->user_id,
  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_entry_events_code"}}'
  */
                &p->action_type,
  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info_dati", "dec":"*"}}'
  */
                discord_audit_log_entry_optional_info_dati_from_json, p->options,
  /* specs/audit_log.json:73:18
     '{"name":"reason", "type": {"base":"char", "dec":"[MAX_REASON_LEN]"}}'
  */
                p->reason,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_entry_dati_use_default_inject_settings(struct discord_audit_log_entry_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->target_id;

  /* specs/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change_dati", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->changes;

  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[2] = &p->user_id;

  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[3] = &p->id;

  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_entry_events_code"}}'
  */
  p->__M.arg_switches[4] = &p->action_type;

  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info_dati", "dec":"*"}}'
  */
  p->__M.arg_switches[5] = p->options;

  /* specs/audit_log.json:73:18
     '{"name":"reason", "type": {"base":"char", "dec":"[MAX_REASON_LEN]"}}'
  */
  p->__M.arg_switches[6] = p->reason;

}

size_t discord_audit_log_entry_dati_to_json(char *json, size_t len, struct discord_audit_log_entry_dati *p)
{
  size_t r;
  discord_audit_log_entry_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */
                "(target_id):s,"
  /* specs/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change_dati", "dec":"*"}}'
  */
                "(changes):F,"
  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(user_id):|F|,"
  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_entry_events_code"}}'
  */
                "(action_type):d,"
  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info_dati", "dec":"*"}}'
  */
                "(options):F,"
  /* specs/audit_log.json:73:18
     '{"name":"reason", "type": {"base":"char", "dec":"[MAX_REASON_LEN]"}}'
  */
                "(reason):s,"
                "@arg_switches:b",
  /* specs/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */
                p->target_id,
  /* specs/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change_dati", "dec":"*"}}'
  */
                discord_audit_log_change_dati_to_json, p->changes,
  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->user_id,
  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_entry_events_code"}}'
  */
                &p->action_type,
  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info_dati", "dec":"*"}}'
  */
                discord_audit_log_entry_optional_info_dati_to_json, p->options,
  /* specs/audit_log.json:73:18
     '{"name":"reason", "type": {"base":"char", "dec":"[MAX_REASON_LEN]"}}'
  */
                p->reason,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_entry_dati_cleanup_v(void *p) {
  discord_audit_log_entry_dati_cleanup((struct discord_audit_log_entry_dati *)p);
}

void discord_audit_log_entry_dati_init_v(void *p) {
  discord_audit_log_entry_dati_init((struct discord_audit_log_entry_dati *)p);
}

void discord_audit_log_entry_dati_free_v(void *p) {
 discord_audit_log_entry_dati_free((struct discord_audit_log_entry_dati *)p);
};

void discord_audit_log_entry_dati_from_json_v(char *json, size_t len, void *p) {
 discord_audit_log_entry_dati_from_json(json, len, (struct discord_audit_log_entry_dati*)p);
}

size_t discord_audit_log_entry_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_entry_dati_to_json(json, len, (struct discord_audit_log_entry_dati*)p);
}

void discord_audit_log_entry_dati_list_free_v(void **p) {
  discord_audit_log_entry_dati_list_free((struct discord_audit_log_entry_dati**)p);
}

void discord_audit_log_entry_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_entry_dati_list_from_json(str, len, (struct discord_audit_log_entry_dati ***)p);
}

size_t discord_audit_log_entry_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_entry_dati_list_to_json(str, len, (struct discord_audit_log_entry_dati **)p);
}


void discord_audit_log_entry_dati_cleanup(struct discord_audit_log_entry_dati *d) {
  /* specs/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->target_id)
    free(d->target_id);
  /* specs/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change_dati", "dec":"*"}}'
  */
  if (d->changes)
    discord_audit_log_change_dati_free(d->changes);
  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->user_id is a scalar
  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_entry_events_code"}}'
  */
  //p->action_type is a scalar
  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info_dati", "dec":"*"}}'
  */
  if (d->options)
    discord_audit_log_entry_optional_info_dati_free(d->options);
  /* specs/audit_log.json:73:18
     '{"name":"reason", "type": {"base":"char", "dec":"[MAX_REASON_LEN]"}}'
  */
  //p->reason is a scalar
}

void discord_audit_log_entry_dati_init(struct discord_audit_log_entry_dati *p) {
  memset(p, 0, sizeof(struct discord_audit_log_entry_dati));
  /* specs/audit_log.json:67:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:68:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change_dati", "dec":"*"}}'
  */
  p->changes = discord_audit_log_change_dati_alloc();

  /* specs/audit_log.json:69:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:70:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:71:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_entry_events_code"}}'
  */

  /* specs/audit_log.json:72:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info_dati", "dec":"*"}}'
  */
  p->options = discord_audit_log_entry_optional_info_dati_alloc();

  /* specs/audit_log.json:73:18
     '{"name":"reason", "type": {"base":"char", "dec":"[MAX_REASON_LEN]"}}'
  */

}
struct discord_audit_log_entry_dati* discord_audit_log_entry_dati_alloc() {
  struct discord_audit_log_entry_dati *p= (struct discord_audit_log_entry_dati*)malloc(sizeof(struct discord_audit_log_entry_dati));
  discord_audit_log_entry_dati_init(p);
  return p;
}

void discord_audit_log_entry_dati_free(struct discord_audit_log_entry_dati *p) {
  discord_audit_log_entry_dati_cleanup(p);
  free(p);
}

void discord_audit_log_entry_dati_list_free(struct discord_audit_log_entry_dati **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_entry_dati_cleanup);
}

void discord_audit_log_entry_dati_list_from_json(char *str, size_t len, struct discord_audit_log_entry_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_entry_dati);
  d.init_elem = discord_audit_log_entry_dati_init_v;
  d.elem_from_buf = discord_audit_log_entry_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_audit_log_entry_dati_list_to_json(char *str, size_t len, struct discord_audit_log_entry_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_entry_dati_to_json_v);
}


void discord_audit_log_entry_optional_info_dati_from_json(char *json, size_t len, struct discord_audit_log_entry_optional_info_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(delete_member_days):?s,"
  /* specs/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(members_removed):?s,"
  /* specs/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
                "(channel_id):F,"
  /* specs/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
                "(message_id):F,"
  /* specs/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                "(count):?s,"
  /* specs/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                "(type):?s,"
  /* specs/audit_log.json:90:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                "(role):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                &p->delete_member_days,
  /* specs/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                &p->members_removed,
  /* specs/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
                orka_strtoull, &p->channel_id,
  /* specs/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
                orka_strtoull, &p->message_id,
  /* specs/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                &p->count,
  /* specs/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                &p->type,
  /* specs/audit_log.json:90:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                &p->role,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_entry_optional_info_dati_use_default_inject_settings(struct discord_audit_log_entry_optional_info_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[0] = p->delete_member_days;

  /* specs/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[1] = p->members_removed;

  /* specs/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
  p->__M.arg_switches[2] = &p->channel_id;

  /* specs/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
  p->__M.arg_switches[3] = &p->message_id;

  /* specs/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[4] = p->count;

  /* specs/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[5] = &p->id;

  /* specs/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[6] = p->type;

  /* specs/audit_log.json:90:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[7] = p->role;

}

size_t discord_audit_log_entry_optional_info_dati_to_json(char *json, size_t len, struct discord_audit_log_entry_optional_info_dati *p)
{
  size_t r;
  discord_audit_log_entry_optional_info_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(delete_member_days):s,"
  /* specs/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(members_removed):s,"
  /* specs/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
                "(channel_id):|F|,"
  /* specs/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
                "(message_id):|F|,"
  /* specs/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                "(count):s,"
  /* specs/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                "(type):s,"
  /* specs/audit_log.json:90:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                "(role):s,"
                "@arg_switches:b",
  /* specs/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                p->delete_member_days,
  /* specs/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                p->members_removed,
  /* specs/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
                orka_ulltostr, &p->message_id,
  /* specs/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                p->count,
  /* specs/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                p->type,
  /* specs/audit_log.json:90:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
                p->role,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_entry_optional_info_dati_cleanup_v(void *p) {
  discord_audit_log_entry_optional_info_dati_cleanup((struct discord_audit_log_entry_optional_info_dati *)p);
}

void discord_audit_log_entry_optional_info_dati_init_v(void *p) {
  discord_audit_log_entry_optional_info_dati_init((struct discord_audit_log_entry_optional_info_dati *)p);
}

void discord_audit_log_entry_optional_info_dati_free_v(void *p) {
 discord_audit_log_entry_optional_info_dati_free((struct discord_audit_log_entry_optional_info_dati *)p);
};

void discord_audit_log_entry_optional_info_dati_from_json_v(char *json, size_t len, void *p) {
 discord_audit_log_entry_optional_info_dati_from_json(json, len, (struct discord_audit_log_entry_optional_info_dati*)p);
}

size_t discord_audit_log_entry_optional_info_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_entry_optional_info_dati_to_json(json, len, (struct discord_audit_log_entry_optional_info_dati*)p);
}

void discord_audit_log_entry_optional_info_dati_list_free_v(void **p) {
  discord_audit_log_entry_optional_info_dati_list_free((struct discord_audit_log_entry_optional_info_dati**)p);
}

void discord_audit_log_entry_optional_info_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_entry_optional_info_dati_list_from_json(str, len, (struct discord_audit_log_entry_optional_info_dati ***)p);
}

size_t discord_audit_log_entry_optional_info_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_entry_optional_info_dati_list_to_json(str, len, (struct discord_audit_log_entry_optional_info_dati **)p);
}


void discord_audit_log_entry_optional_info_dati_cleanup(struct discord_audit_log_entry_optional_info_dati *d) {
  /* specs/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  if (d->delete_member_days)
    free(d->delete_member_days);
  /* specs/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  if (d->members_removed)
    free(d->members_removed);
  /* specs/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
  //p->channel_id is a scalar
  /* specs/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */
  //p->message_id is a scalar
  /* specs/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  if (d->count)
    free(d->count);
  /* specs/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  if (d->type)
    free(d->type);
  /* specs/audit_log.json:90:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */
  if (d->role)
    free(d->role);
}

void discord_audit_log_entry_optional_info_dati_init(struct discord_audit_log_entry_optional_info_dati *p) {
  memset(p, 0, sizeof(struct discord_audit_log_entry_optional_info_dati));
  /* specs/audit_log.json:83:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */

  /* specs/audit_log.json:84:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */

  /* specs/audit_log.json:85:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */

  /* specs/audit_log.json:86:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }'
  */

  /* specs/audit_log.json:87:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */

  /* specs/audit_log.json:88:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/audit_log.json:89:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */

  /* specs/audit_log.json:90:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}'
  */

}
struct discord_audit_log_entry_optional_info_dati* discord_audit_log_entry_optional_info_dati_alloc() {
  struct discord_audit_log_entry_optional_info_dati *p= (struct discord_audit_log_entry_optional_info_dati*)malloc(sizeof(struct discord_audit_log_entry_optional_info_dati));
  discord_audit_log_entry_optional_info_dati_init(p);
  return p;
}

void discord_audit_log_entry_optional_info_dati_free(struct discord_audit_log_entry_optional_info_dati *p) {
  discord_audit_log_entry_optional_info_dati_cleanup(p);
  free(p);
}

void discord_audit_log_entry_optional_info_dati_list_free(struct discord_audit_log_entry_optional_info_dati **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_entry_optional_info_dati_cleanup);
}

void discord_audit_log_entry_optional_info_dati_list_from_json(char *str, size_t len, struct discord_audit_log_entry_optional_info_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_entry_optional_info_dati);
  d.init_elem = discord_audit_log_entry_optional_info_dati_init_v;
  d.elem_from_buf = discord_audit_log_entry_optional_info_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_audit_log_entry_optional_info_dati_list_to_json(char *str, size_t len, struct discord_audit_log_entry_optional_info_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_entry_optional_info_dati_to_json_v);
}


void discord_audit_log_change_dati_from_json(char *json, size_t len, struct discord_audit_log_change_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */
                "(new_value):?s,"
  /* specs/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */
                "(old_value):?s,"
  /* specs/audit_log.json:102:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}'
  */
                "(key):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */
                &p->new_value,
  /* specs/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */
                &p->old_value,
  /* specs/audit_log.json:102:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}'
  */
                p->key,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_change_dati_use_default_inject_settings(struct discord_audit_log_change_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->new_value;

  /* specs/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->old_value;

  /* specs/audit_log.json:102:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}'
  */
  p->__M.arg_switches[2] = p->key;

}

size_t discord_audit_log_change_dati_to_json(char *json, size_t len, struct discord_audit_log_change_dati *p)
{
  size_t r;
  discord_audit_log_change_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */
                "(new_value):s,"
  /* specs/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */
                "(old_value):s,"
  /* specs/audit_log.json:102:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}'
  */
                "(key):s,"
                "@arg_switches:b",
  /* specs/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */
                p->new_value,
  /* specs/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */
                p->old_value,
  /* specs/audit_log.json:102:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}'
  */
                p->key,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_change_dati_cleanup_v(void *p) {
  discord_audit_log_change_dati_cleanup((struct discord_audit_log_change_dati *)p);
}

void discord_audit_log_change_dati_init_v(void *p) {
  discord_audit_log_change_dati_init((struct discord_audit_log_change_dati *)p);
}

void discord_audit_log_change_dati_free_v(void *p) {
 discord_audit_log_change_dati_free((struct discord_audit_log_change_dati *)p);
};

void discord_audit_log_change_dati_from_json_v(char *json, size_t len, void *p) {
 discord_audit_log_change_dati_from_json(json, len, (struct discord_audit_log_change_dati*)p);
}

size_t discord_audit_log_change_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_change_dati_to_json(json, len, (struct discord_audit_log_change_dati*)p);
}

void discord_audit_log_change_dati_list_free_v(void **p) {
  discord_audit_log_change_dati_list_free((struct discord_audit_log_change_dati**)p);
}

void discord_audit_log_change_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_change_dati_list_from_json(str, len, (struct discord_audit_log_change_dati ***)p);
}

size_t discord_audit_log_change_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_change_dati_list_to_json(str, len, (struct discord_audit_log_change_dati **)p);
}


void discord_audit_log_change_dati_cleanup(struct discord_audit_log_change_dati *d) {
  /* specs/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->new_value)
    free(d->new_value);
  /* specs/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->old_value)
    free(d->old_value);
  /* specs/audit_log.json:102:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}'
  */
  //p->key is a scalar
}

void discord_audit_log_change_dati_init(struct discord_audit_log_change_dati *p) {
  memset(p, 0, sizeof(struct discord_audit_log_change_dati));
  /* specs/audit_log.json:100:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:101:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:102:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}'
  */

}
struct discord_audit_log_change_dati* discord_audit_log_change_dati_alloc() {
  struct discord_audit_log_change_dati *p= (struct discord_audit_log_change_dati*)malloc(sizeof(struct discord_audit_log_change_dati));
  discord_audit_log_change_dati_init(p);
  return p;
}

void discord_audit_log_change_dati_free(struct discord_audit_log_change_dati *p) {
  discord_audit_log_change_dati_cleanup(p);
  free(p);
}

void discord_audit_log_change_dati_list_free(struct discord_audit_log_change_dati **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_change_dati_cleanup);
}

void discord_audit_log_change_dati_list_from_json(char *str, size_t len, struct discord_audit_log_change_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_change_dati);
  d.init_elem = discord_audit_log_change_dati_init_v;
  d.elem_from_buf = discord_audit_log_change_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_audit_log_change_dati_list_to_json(char *str, size_t len, struct discord_audit_log_change_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_change_dati_to_json_v);
}


void discord_audit_log_change_key_dati_from_json(char *json, size_t len, struct discord_audit_log_change_key_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                "(description):s,"
  /* specs/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */
                "(icon_hash):s,"
  /* specs/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */
                "(splash_hash):s,"
  /* specs/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
                "(discovery_splash_hash):s,"
  /* specs/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(banner_hash):F,"
  /* specs/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(owner_id):F,"
  /* specs/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */
                "(region):s,"
  /* specs/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */
                "(preferred_locale):s,"
  /* specs/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(afk_channel_id):F,"
  /* specs/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */
                "(afk_timeout):d,"
  /* specs/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(rules_channel_id):F,"
  /* specs/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(public_updates_channel_id):F,"
  /* specs/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */
                "(mfa_level):d,"
  /* specs/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */
                "(verification_level):d,"
  /* specs/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */
                "(explicit_content_filter):d,"
  /* specs/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */
                "(default_message_notifications):d,"
  /* specs/audit_log.json:131:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}}'
  */
                "(vanity_url_code):?s,"
  /* specs/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */
                "(prune_delete_days):d,"
  /* specs/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */
                "(widget_enabled):b,"
  /* specs/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(widget_channel_id):F,"
  /* specs/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(system_channel_id):F,"
  /* specs/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */
                "(position):d,"
  /* specs/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */
                "(topic):?s,"
  /* specs/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */
                "(bitrate):d,"
  /* specs/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */
                "(nsfw):b,"
  /* specs/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(application_id):F,"
  /* specs/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */
                "(rate_limit_per_user):d,"
  /* specs/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */
                "(permissions):?s,"
  /* specs/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */
                "(color):d,"
  /* specs/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */
                "(hoist):b,"
  /* specs/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */
                "(mentionable):b,"
  /* specs/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */
                "(allow):?s,"
  /* specs/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */
                "(deny):?s,"
  /* specs/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */
                "(code):?s,"
  /* specs/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */
                "(channel_id):?s,"
  /* specs/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */
                "(inviter_id):?s,"
  /* specs/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */
                "(max_uses):?s,"
  /* specs/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */
                "(uses):?s,"
  /* specs/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */
                "(max_age):?s,"
  /* specs/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */
                "(temporary):?s,"
  /* specs/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */
                "(deaf):?s,"
  /* specs/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */
                "(mute):?s,"
  /* specs/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */
                "(nick):?s,"
  /* specs/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */
                "(avatar_hash):?s,"
  /* specs/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */
  /* specs/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */
                "(enable_emotions):b,"
  /* specs/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */
                "(expire_behavior):d,"
  /* specs/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */
                "(expire_grace_period):d,"
  /* specs/audit_log.json:171:18
     '{"name":"user_limit", "type": {"base":"int" }}'
  */
                "(user_limit):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                p->description,
  /* specs/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */
                p->icon_hash,
  /* specs/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */
                p->splash_hash,
  /* specs/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
                p->discovery_splash_hash,
  /* specs/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->banner_hash,
  /* specs/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->owner_id,
  /* specs/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */
                p->region,
  /* specs/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */
                p->preferred_locale,
  /* specs/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->afk_channel_id,
  /* specs/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */
                &p->afk_timeout,
  /* specs/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->rules_channel_id,
  /* specs/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->public_updates_channel_id,
  /* specs/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */
                &p->mfa_level,
  /* specs/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */
                &p->verification_level,
  /* specs/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */
                &p->explicit_content_filter,
  /* specs/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */
                &p->default_message_notifications,
  /* specs/audit_log.json:131:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}}'
  */
                &p->vanity_url_code,
  /* specs/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */
                &p->prune_delete_days,
  /* specs/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */
                &p->widget_enabled,
  /* specs/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->widget_channel_id,
  /* specs/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->system_channel_id,
  /* specs/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */
                &p->position,
  /* specs/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */
                &p->topic,
  /* specs/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */
                &p->bitrate,
  /* specs/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */
                &p->nsfw,
  /* specs/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->application_id,
  /* specs/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */
                &p->rate_limit_per_user,
  /* specs/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */
                &p->permissions,
  /* specs/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */
                &p->color,
  /* specs/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */
                &p->hoist,
  /* specs/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */
                &p->mentionable,
  /* specs/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */
                &p->allow,
  /* specs/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */
                &p->deny,
  /* specs/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */
                &p->code,
  /* specs/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */
                &p->channel_id,
  /* specs/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */
                &p->inviter_id,
  /* specs/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */
                &p->max_uses,
  /* specs/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */
                &p->uses,
  /* specs/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */
                &p->max_age,
  /* specs/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */
                &p->temporary,
  /* specs/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */
                &p->deaf,
  /* specs/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */
                &p->mute,
  /* specs/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */
                &p->nick,
  /* specs/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */
                &p->avatar_hash,
  /* specs/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */
  /* specs/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */
                &p->enable_emotions,
  /* specs/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */
                &p->expire_behavior,
  /* specs/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */
                &p->expire_grace_period,
  /* specs/audit_log.json:171:18
     '{"name":"user_limit", "type": {"base":"int" }}'
  */
                &p->user_limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_change_key_dati_use_default_inject_settings(struct discord_audit_log_change_key_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  p->__M.arg_switches[1] = p->description;

  /* specs/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */
  p->__M.arg_switches[2] = p->icon_hash;

  /* specs/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */
  p->__M.arg_switches[3] = p->splash_hash;

  /* specs/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
  p->__M.arg_switches[4] = p->discovery_splash_hash;

  /* specs/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[5] = &p->banner_hash;

  /* specs/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[6] = &p->owner_id;

  /* specs/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */
  p->__M.arg_switches[7] = p->region;

  /* specs/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */
  p->__M.arg_switches[8] = p->preferred_locale;

  /* specs/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[9] = &p->afk_channel_id;

  /* specs/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[10] = &p->afk_timeout;

  /* specs/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[11] = &p->rules_channel_id;

  /* specs/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[12] = &p->public_updates_channel_id;

  /* specs/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[13] = &p->mfa_level;

  /* specs/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[14] = &p->verification_level;

  /* specs/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[15] = &p->explicit_content_filter;

  /* specs/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[16] = &p->default_message_notifications;

  /* specs/audit_log.json:131:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[17] = p->vanity_url_code;

  /* specs/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */

  /* specs/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */

  /* specs/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[20] = &p->prune_delete_days;

  /* specs/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */
  p->__M.arg_switches[21] = &p->widget_enabled;

  /* specs/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[22] = &p->widget_channel_id;

  /* specs/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[23] = &p->system_channel_id;

  /* specs/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[24] = &p->position;

  /* specs/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[25] = p->topic;

  /* specs/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[26] = &p->bitrate;

  /* specs/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */

  /* specs/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */
  p->__M.arg_switches[28] = &p->nsfw;

  /* specs/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[29] = &p->application_id;

  /* specs/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[30] = &p->rate_limit_per_user;

  /* specs/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[31] = p->permissions;

  /* specs/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[32] = &p->color;

  /* specs/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */
  p->__M.arg_switches[33] = &p->hoist;

  /* specs/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */
  p->__M.arg_switches[34] = &p->mentionable;

  /* specs/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[35] = p->allow;

  /* specs/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[36] = p->deny;

  /* specs/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[37] = p->code;

  /* specs/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[38] = p->channel_id;

  /* specs/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[39] = p->inviter_id;

  /* specs/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[40] = p->max_uses;

  /* specs/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[41] = p->uses;

  /* specs/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[42] = p->max_age;

  /* specs/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[43] = p->temporary;

  /* specs/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[44] = p->deaf;

  /* specs/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[45] = p->mute;

  /* specs/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[46] = p->nick;

  /* specs/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[47] = p->avatar_hash;

  /* specs/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[48] = &p->id;

  /* specs/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */

  /* specs/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */
  p->__M.arg_switches[50] = &p->enable_emotions;

  /* specs/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[51] = &p->expire_behavior;

  /* specs/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */
  p->__M.arg_switches[52] = &p->expire_grace_period;

  /* specs/audit_log.json:171:18
     '{"name":"user_limit", "type": {"base":"int" }}'
  */
  p->__M.arg_switches[53] = &p->user_limit;

}

size_t discord_audit_log_change_key_dati_to_json(char *json, size_t len, struct discord_audit_log_change_key_dati *p)
{
  size_t r;
  discord_audit_log_change_key_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                "(description):s,"
  /* specs/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */
                "(icon_hash):s,"
  /* specs/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */
                "(splash_hash):s,"
  /* specs/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
                "(discovery_splash_hash):s,"
  /* specs/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(banner_hash):|F|,"
  /* specs/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(owner_id):|F|,"
  /* specs/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */
                "(region):s,"
  /* specs/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */
                "(preferred_locale):s,"
  /* specs/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(afk_channel_id):|F|,"
  /* specs/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */
                "(afk_timeout):d,"
  /* specs/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(rules_channel_id):|F|,"
  /* specs/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(public_updates_channel_id):|F|,"
  /* specs/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */
                "(mfa_level):d,"
  /* specs/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */
                "(verification_level):d,"
  /* specs/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */
                "(explicit_content_filter):d,"
  /* specs/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */
                "(default_message_notifications):d,"
  /* specs/audit_log.json:131:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}}'
  */
                "(vanity_url_code):s,"
  /* specs/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */
                "(prune_delete_days):d,"
  /* specs/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */
                "(widget_enabled):b,"
  /* specs/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(widget_channel_id):|F|,"
  /* specs/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(system_channel_id):|F|,"
  /* specs/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */
                "(position):d,"
  /* specs/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */
                "(topic):s,"
  /* specs/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */
                "(bitrate):d,"
  /* specs/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */
                "(nsfw):b,"
  /* specs/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(application_id):|F|,"
  /* specs/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */
                "(rate_limit_per_user):d,"
  /* specs/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */
                "(permissions):s,"
  /* specs/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */
                "(color):d,"
  /* specs/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */
                "(hoist):b,"
  /* specs/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */
                "(mentionable):b,"
  /* specs/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */
                "(allow):s,"
  /* specs/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */
                "(deny):s,"
  /* specs/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */
                "(code):s,"
  /* specs/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */
                "(channel_id):s,"
  /* specs/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */
                "(inviter_id):s,"
  /* specs/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */
                "(max_uses):s,"
  /* specs/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */
                "(uses):s,"
  /* specs/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */
                "(max_age):s,"
  /* specs/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */
                "(temporary):s,"
  /* specs/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */
                "(deaf):s,"
  /* specs/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */
                "(mute):s,"
  /* specs/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */
                "(nick):s,"
  /* specs/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */
                "(avatar_hash):s,"
  /* specs/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */
  /* specs/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */
                "(enable_emotions):b,"
  /* specs/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */
                "(expire_behavior):d,"
  /* specs/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */
                "(expire_grace_period):d,"
  /* specs/audit_log.json:171:18
     '{"name":"user_limit", "type": {"base":"int" }}'
  */
                "(user_limit):d,"
                "@arg_switches:b",
  /* specs/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                p->description,
  /* specs/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */
                p->icon_hash,
  /* specs/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */
                p->splash_hash,
  /* specs/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
                p->discovery_splash_hash,
  /* specs/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->banner_hash,
  /* specs/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->owner_id,
  /* specs/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */
                p->region,
  /* specs/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */
                p->preferred_locale,
  /* specs/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->afk_channel_id,
  /* specs/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */
                &p->afk_timeout,
  /* specs/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->rules_channel_id,
  /* specs/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->public_updates_channel_id,
  /* specs/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */
                &p->mfa_level,
  /* specs/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */
                &p->verification_level,
  /* specs/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */
                &p->explicit_content_filter,
  /* specs/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */
                &p->default_message_notifications,
  /* specs/audit_log.json:131:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}}'
  */
                p->vanity_url_code,
  /* specs/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */
                &p->prune_delete_days,
  /* specs/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */
                &p->widget_enabled,
  /* specs/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->widget_channel_id,
  /* specs/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->system_channel_id,
  /* specs/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */
                &p->position,
  /* specs/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */
                p->topic,
  /* specs/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */
                &p->bitrate,
  /* specs/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  /* specs/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */
                &p->nsfw,
  /* specs/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->application_id,
  /* specs/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */
                &p->rate_limit_per_user,
  /* specs/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */
                p->permissions,
  /* specs/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */
                &p->color,
  /* specs/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */
                &p->hoist,
  /* specs/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */
                &p->mentionable,
  /* specs/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */
                p->allow,
  /* specs/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */
                p->deny,
  /* specs/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */
                p->code,
  /* specs/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */
                p->channel_id,
  /* specs/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */
                p->inviter_id,
  /* specs/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */
                p->max_uses,
  /* specs/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */
                p->uses,
  /* specs/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */
                p->max_age,
  /* specs/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */
                p->temporary,
  /* specs/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */
                p->deaf,
  /* specs/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */
                p->mute,
  /* specs/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */
                p->nick,
  /* specs/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */
                p->avatar_hash,
  /* specs/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */
  /* specs/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */
                &p->enable_emotions,
  /* specs/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */
                &p->expire_behavior,
  /* specs/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */
                &p->expire_grace_period,
  /* specs/audit_log.json:171:18
     '{"name":"user_limit", "type": {"base":"int" }}'
  */
                &p->user_limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_change_key_dati_cleanup_v(void *p) {
  discord_audit_log_change_key_dati_cleanup((struct discord_audit_log_change_key_dati *)p);
}

void discord_audit_log_change_key_dati_init_v(void *p) {
  discord_audit_log_change_key_dati_init((struct discord_audit_log_change_key_dati *)p);
}

void discord_audit_log_change_key_dati_free_v(void *p) {
 discord_audit_log_change_key_dati_free((struct discord_audit_log_change_key_dati *)p);
};

void discord_audit_log_change_key_dati_from_json_v(char *json, size_t len, void *p) {
 discord_audit_log_change_key_dati_from_json(json, len, (struct discord_audit_log_change_key_dati*)p);
}

size_t discord_audit_log_change_key_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_change_key_dati_to_json(json, len, (struct discord_audit_log_change_key_dati*)p);
}

void discord_audit_log_change_key_dati_list_free_v(void **p) {
  discord_audit_log_change_key_dati_list_free((struct discord_audit_log_change_key_dati**)p);
}

void discord_audit_log_change_key_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_change_key_dati_list_from_json(str, len, (struct discord_audit_log_change_key_dati ***)p);
}

size_t discord_audit_log_change_key_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_change_key_dati_list_to_json(str, len, (struct discord_audit_log_change_key_dati **)p);
}


void discord_audit_log_change_key_dati_cleanup(struct discord_audit_log_change_key_dati *d) {
  /* specs/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  //p->name is a scalar
  /* specs/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  //p->description is a scalar
  /* specs/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */
  //p->icon_hash is a scalar
  /* specs/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */
  //p->splash_hash is a scalar
  /* specs/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
  //p->discovery_splash_hash is a scalar
  /* specs/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->banner_hash is a scalar
  /* specs/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->owner_id is a scalar
  /* specs/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */
  //p->region is a scalar
  /* specs/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */
  //p->preferred_locale is a scalar
  /* specs/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->afk_channel_id is a scalar
  /* specs/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */
  //p->afk_timeout is a scalar
  /* specs/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->rules_channel_id is a scalar
  /* specs/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->public_updates_channel_id is a scalar
  /* specs/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */
  //p->mfa_level is a scalar
  /* specs/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */
  //p->verification_level is a scalar
  /* specs/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */
  //p->explicit_content_filter is a scalar
  /* specs/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */
  //p->default_message_notifications is a scalar
  /* specs/audit_log.json:131:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->vanity_url_code)
    free(d->vanity_url_code);
  /* specs/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo p->(null)
  /* specs/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo p->(null)
  /* specs/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */
  //p->prune_delete_days is a scalar
  /* specs/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */
  //p->widget_enabled is a scalar
  /* specs/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->widget_channel_id is a scalar
  /* specs/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->system_channel_id is a scalar
  /* specs/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */
  //p->position is a scalar
  /* specs/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->topic)
    free(d->topic);
  /* specs/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */
  //p->bitrate is a scalar
  /* specs/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */
  //@todo p->(null)
  /* specs/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */
  //p->nsfw is a scalar
  /* specs/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->application_id is a scalar
  /* specs/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */
  //p->rate_limit_per_user is a scalar
  /* specs/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->permissions)
    free(d->permissions);
  /* specs/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */
  //p->color is a scalar
  /* specs/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */
  //p->hoist is a scalar
  /* specs/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */
  //p->mentionable is a scalar
  /* specs/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->allow)
    free(d->allow);
  /* specs/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->deny)
    free(d->deny);
  /* specs/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->code)
    free(d->code);
  /* specs/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->channel_id)
    free(d->channel_id);
  /* specs/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->inviter_id)
    free(d->inviter_id);
  /* specs/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->max_uses)
    free(d->max_uses);
  /* specs/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->uses)
    free(d->uses);
  /* specs/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->max_age)
    free(d->max_age);
  /* specs/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->temporary)
    free(d->temporary);
  /* specs/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->deaf)
    free(d->deaf);
  /* specs/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->mute)
    free(d->mute);
  /* specs/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->nick)
    free(d->nick);
  /* specs/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */
  if (d->avatar_hash)
    free(d->avatar_hash);
  /* specs/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */
  //@todo p->(null)
  /* specs/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */
  //p->enable_emotions is a scalar
  /* specs/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */
  //p->expire_behavior is a scalar
  /* specs/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */
  //p->expire_grace_period is a scalar
  /* specs/audit_log.json:171:18
     '{"name":"user_limit", "type": {"base":"int" }}'
  */
  //p->user_limit is a scalar
}

void discord_audit_log_change_key_dati_init(struct discord_audit_log_change_key_dati *p) {
  memset(p, 0, sizeof(struct discord_audit_log_change_key_dati));
  /* specs/audit_log.json:112:18
     '{"name":"name", "type": {"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */

  /* specs/audit_log.json:113:18
     '{"name":"description", "type": {"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */

  /* specs/audit_log.json:114:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "comment":"icon changed" }'
  */

  /* specs/audit_log.json:116:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"},
         "comment":"invite splash page artwork changed"}'
  */

  /* specs/audit_log.json:118:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */

  /* specs/audit_log.json:119:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:120:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:121:18
     '{"name":"region", "type": {"base":"char", "dec":"[MAX_REGION_LEN]"}}'
  */

  /* specs/audit_log.json:122:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[MAX_LOCALE_LEN]"}}'
  */

  /* specs/audit_log.json:123:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:124:18
     '{"name":"afk_timeout", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:125:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:126:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:127:18
     '{"name":"mfa_level", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:128:18
     '{"name":"verification_level", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:129:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:130:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:131:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:132:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */

  /* specs/audit_log.json:134:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */

  /* specs/audit_log.json:136:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:137:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}'
  */

  /* specs/audit_log.json:138:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:139:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:140:18
     '{"name":"position", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:141:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:142:18
     '{"name":"bitrate", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:143:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }'
  */

  /* specs/audit_log.json:145:18
     '{"name":"nsfw", "type": {"base":"bool"}}'
  */

  /* specs/audit_log.json:146:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:147:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:148:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:149:18
     '{"name":"color", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:150:18
     '{"name":"hoist", "type": {"base":"bool"}}'
  */

  /* specs/audit_log.json:151:18
     '{"name":"mentionable", "type": {"base":"bool"}}'
  */

  /* specs/audit_log.json:152:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:153:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:154:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:155:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:156:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:157:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:158:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:159:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:160:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:161:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:162:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:163:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:164:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}'
  */

  /* specs/audit_log.json:165:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/audit_log.json:166:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}'
  */

  /* specs/audit_log.json:168:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}'
  */

  /* specs/audit_log.json:169:18
     '{"name":"expire_behavior", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:170:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}'
  */

  /* specs/audit_log.json:171:18
     '{"name":"user_limit", "type": {"base":"int" }}'
  */

}
struct discord_audit_log_change_key_dati* discord_audit_log_change_key_dati_alloc() {
  struct discord_audit_log_change_key_dati *p= (struct discord_audit_log_change_key_dati*)malloc(sizeof(struct discord_audit_log_change_key_dati));
  discord_audit_log_change_key_dati_init(p);
  return p;
}

void discord_audit_log_change_key_dati_free(struct discord_audit_log_change_key_dati *p) {
  discord_audit_log_change_key_dati_cleanup(p);
  free(p);
}

void discord_audit_log_change_key_dati_list_free(struct discord_audit_log_change_key_dati **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_change_key_dati_cleanup);
}

void discord_audit_log_change_key_dati_list_from_json(char *str, size_t len, struct discord_audit_log_change_key_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_change_key_dati);
  d.init_elem = discord_audit_log_change_key_dati_init_v;
  d.elem_from_buf = discord_audit_log_change_key_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_audit_log_change_key_dati_list_to_json(char *str, size_t len, struct discord_audit_log_change_key_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_change_key_dati_to_json_v);
}

