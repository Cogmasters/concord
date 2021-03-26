/* This file is generated from specs/guild.integration.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/


enum discord_guild_integration_expire_behaviors discord_guild_integration_expire_behaviors_from_string(char *s){
  if(strcmp("REMOVE_ROLE", s) == 0) return DISCORD_GUILD_INTEGRATION_REMOVE_ROLE;
  if(strcmp("KICK", s) == 0) return DISCORD_GUILD_INTEGRATION_KICK;
  abort();
}
char* discord_guild_integration_expire_behaviors_to_string(enum discord_guild_integration_expire_behaviors v){
  if (v == DISCORD_GUILD_INTEGRATION_REMOVE_ROLE) return "REMOVE_ROLE";
  if (v == DISCORD_GUILD_INTEGRATION_KICK) return "KICK";

  abort();
}

void discord_guild_integration_account_from_json(char *json, size_t len, struct discord_guild_integration_account *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_integration_account_use_default_inject_settings(struct discord_guild_integration_account *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[1] = p->name;

}

size_t discord_guild_integration_account_to_json(char *json, size_t len, struct discord_guild_integration_account *p)
{
  size_t r;
  discord_guild_integration_account_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):s,"
                "@arg_switches:b",
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
                p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_integration_account_cleanup_v(void *p) {
  discord_guild_integration_account_cleanup((struct discord_guild_integration_account *)p);
}

void discord_guild_integration_account_init_v(void *p) {
  discord_guild_integration_account_init((struct discord_guild_integration_account *)p);
}

void discord_guild_integration_account_free_v(void *p) {
 discord_guild_integration_account_free((struct discord_guild_integration_account *)p);
};

void discord_guild_integration_account_from_json_v(char *json, size_t len, void *p) {
 discord_guild_integration_account_from_json(json, len, (struct discord_guild_integration_account*)p);
}

size_t discord_guild_integration_account_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_integration_account_to_json(json, len, (struct discord_guild_integration_account*)p);
}

void discord_guild_integration_account_list_free_v(void **p) {
  discord_guild_integration_account_list_free((struct discord_guild_integration_account**)p);
}

void discord_guild_integration_account_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_integration_account_list_from_json(str, len, (struct discord_guild_integration_account ***)p);
}

size_t discord_guild_integration_account_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_integration_account_list_to_json(str, len, (struct discord_guild_integration_account **)p);
}


void discord_guild_integration_account_cleanup(struct discord_guild_integration_account *d) {
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->name)
    free(d->name);
}

void discord_guild_integration_account_init(struct discord_guild_integration_account *p) {
  memset(p, 0, sizeof(struct discord_guild_integration_account));
  /* specs/guild.integration.json:23:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/guild.integration.json:24:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */

}
struct discord_guild_integration_account* discord_guild_integration_account_alloc() {
  struct discord_guild_integration_account *p= (struct discord_guild_integration_account*)malloc(sizeof(struct discord_guild_integration_account));
  discord_guild_integration_account_init(p);
  return p;
}

void discord_guild_integration_account_free(struct discord_guild_integration_account *p) {
  discord_guild_integration_account_cleanup(p);
  free(p);
}

void discord_guild_integration_account_list_free(struct discord_guild_integration_account **p) {
  ntl_free((void**)p, (vfvp)discord_guild_integration_account_cleanup);
}

void discord_guild_integration_account_list_from_json(char *str, size_t len, struct discord_guild_integration_account ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_integration_account);
  d.init_elem = discord_guild_integration_account_init_v;
  d.elem_from_buf = discord_guild_integration_account_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_integration_account_list_to_json(char *str, size_t len, struct discord_guild_integration_account **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_integration_account_to_json_v);
}


void discord_guild_integration_application_from_json(char *json, size_t len, struct discord_guild_integration_application *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):?s,"
  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                "(icon):s,"
  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
                "(description):?s,"
  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
                "(summary):?s,"
  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
                "(bot):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->name,
  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                p->icon,
  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->description,
  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->summary,
  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
                discord_user_from_json, p->bot,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_integration_application_use_default_inject_settings(struct discord_guild_integration_application *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  p->__M.arg_switches[2] = p->icon;

  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[3] = p->description;

  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[4] = p->summary;

  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  p->__M.arg_switches[5] = p->bot;

}

size_t discord_guild_integration_application_to_json(char *json, size_t len, struct discord_guild_integration_application *p)
{
  size_t r;
  discord_guild_integration_application_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):s,"
  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                "(icon):s,"
  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
                "(description):s,"
  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
                "(summary):s,"
  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
                "(bot):F,"
                "@arg_switches:b",
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
                p->name,
  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                p->icon,
  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
                p->description,
  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
                p->summary,
  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
                discord_user_to_json, p->bot,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_integration_application_cleanup_v(void *p) {
  discord_guild_integration_application_cleanup((struct discord_guild_integration_application *)p);
}

void discord_guild_integration_application_init_v(void *p) {
  discord_guild_integration_application_init((struct discord_guild_integration_application *)p);
}

void discord_guild_integration_application_free_v(void *p) {
 discord_guild_integration_application_free((struct discord_guild_integration_application *)p);
};

void discord_guild_integration_application_from_json_v(char *json, size_t len, void *p) {
 discord_guild_integration_application_from_json(json, len, (struct discord_guild_integration_application*)p);
}

size_t discord_guild_integration_application_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_integration_application_to_json(json, len, (struct discord_guild_integration_application*)p);
}

void discord_guild_integration_application_list_free_v(void **p) {
  discord_guild_integration_application_list_free((struct discord_guild_integration_application**)p);
}

void discord_guild_integration_application_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_integration_application_list_from_json(str, len, (struct discord_guild_integration_application ***)p);
}

size_t discord_guild_integration_application_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_integration_application_list_to_json(str, len, (struct discord_guild_integration_application **)p);
}


void discord_guild_integration_application_cleanup(struct discord_guild_integration_application *d) {
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->name)
    free(d->name);
  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  //p->icon is a scalar
  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->description)
    free(d->description);
  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->summary)
    free(d->summary);
  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  if (d->bot)
    discord_user_free(d->bot);
}

void discord_guild_integration_application_init(struct discord_guild_integration_application *p) {
  memset(p, 0, sizeof(struct discord_guild_integration_application));
  /* specs/guild.integration.json:33:19
     '{ "name":"id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/guild.integration.json:34:19
     '{ "name":"name", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/guild.integration.json:35:19
     '{ "name":"icon", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */

  /* specs/guild.integration.json:36:19
     '{ "name":"description", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/guild.integration.json:37:19
     '{ "name":"summary", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/guild.integration.json:38:19
     '{ "name":"bot", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true}'
  */
  p->bot = discord_user_alloc();

}
struct discord_guild_integration_application* discord_guild_integration_application_alloc() {
  struct discord_guild_integration_application *p= (struct discord_guild_integration_application*)malloc(sizeof(struct discord_guild_integration_application));
  discord_guild_integration_application_init(p);
  return p;
}

void discord_guild_integration_application_free(struct discord_guild_integration_application *p) {
  discord_guild_integration_application_cleanup(p);
  free(p);
}

void discord_guild_integration_application_list_free(struct discord_guild_integration_application **p) {
  ntl_free((void**)p, (vfvp)discord_guild_integration_application_cleanup);
}

void discord_guild_integration_application_list_from_json(char *str, size_t len, struct discord_guild_integration_application ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_integration_application);
  d.init_elem = discord_guild_integration_application_init_v;
  d.elem_from_buf = discord_guild_integration_application_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_integration_application_list_to_json(char *str, size_t len, struct discord_guild_integration_application **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_integration_application_to_json_v);
}


void discord_guild_integration_from_json(char *json, size_t len, struct discord_guild_integration *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.integration.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/guild.integration.json:48:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                "(name):?s,"
  /* specs/guild.integration.json:49:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                "(type):?s,"
  /* specs/guild.integration.json:50:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
                "(enabled):b,"
  /* specs/guild.integration.json:51:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
                "(syncing):b,"
  /* specs/guild.integration.json:52:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(role_id):F,"
  /* specs/guild.integration.json:53:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
                "(enable_emotions):b,"
  /* specs/guild.integration.json:54:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}'
  */
                "(expire_behavior):d,"
  /* specs/guild.integration.json:55:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
                "(expire_grace_period):d,"
  /* specs/guild.integration.json:56:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}'
  */
                "(user):F,"
  /* specs/guild.integration.json:57:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}'
  */
                "(account):F,"
  /* specs/guild.integration.json:58:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                "(synced_at):F,"
  /* specs/guild.integration.json:59:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
                "(subscriber_count):d,"
  /* specs/guild.integration.json:60:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                "(revoked):b,"
  /* specs/guild.integration.json:61:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}'
  */
                "(application):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.integration.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.integration.json:48:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                &p->name,
  /* specs/guild.integration.json:49:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                &p->type,
  /* specs/guild.integration.json:50:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
                &p->enabled,
  /* specs/guild.integration.json:51:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
                &p->syncing,
  /* specs/guild.integration.json:52:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->role_id,
  /* specs/guild.integration.json:53:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
                &p->enable_emotions,
  /* specs/guild.integration.json:54:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}'
  */
                &p->expire_behavior,
  /* specs/guild.integration.json:55:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
                &p->expire_grace_period,
  /* specs/guild.integration.json:56:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}'
  */
                discord_user_from_json, p->user,
  /* specs/guild.integration.json:57:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}'
  */
                discord_guild_integration_account_from_json, p->account,
  /* specs/guild.integration.json:58:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                orka_iso8601_to_unix_ms, &p->synced_at,
  /* specs/guild.integration.json:59:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
                &p->subscriber_count,
  /* specs/guild.integration.json:60:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                &p->revoked,
  /* specs/guild.integration.json:61:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}'
  */
                discord_guild_integration_application_from_json, p->application,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_integration_use_default_inject_settings(struct discord_guild_integration *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.integration.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.integration.json:48:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/guild.integration.json:49:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[2] = p->type;

  /* specs/guild.integration.json:50:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
  p->__M.arg_switches[3] = &p->enabled;

  /* specs/guild.integration.json:51:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
  p->__M.arg_switches[4] = &p->syncing;

  /* specs/guild.integration.json:52:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[5] = &p->role_id;

  /* specs/guild.integration.json:53:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
  p->__M.arg_switches[6] = &p->enable_emotions;

  /* specs/guild.integration.json:54:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}'
  */
  p->__M.arg_switches[7] = &p->expire_behavior;

  /* specs/guild.integration.json:55:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
  p->__M.arg_switches[8] = &p->expire_grace_period;

  /* specs/guild.integration.json:56:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}'
  */
  p->__M.arg_switches[9] = p->user;

  /* specs/guild.integration.json:57:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}'
  */
  p->__M.arg_switches[10] = p->account;

  /* specs/guild.integration.json:58:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  p->__M.arg_switches[11] = &p->synced_at;

  /* specs/guild.integration.json:59:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
  p->__M.arg_switches[12] = &p->subscriber_count;

  /* specs/guild.integration.json:60:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  p->__M.arg_switches[13] = &p->revoked;

  /* specs/guild.integration.json:61:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}'
  */
  p->__M.arg_switches[14] = p->application;

}

size_t discord_guild_integration_to_json(char *json, size_t len, struct discord_guild_integration *p)
{
  size_t r;
  discord_guild_integration_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.integration.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/guild.integration.json:48:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                "(name):s,"
  /* specs/guild.integration.json:49:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                "(type):s,"
  /* specs/guild.integration.json:50:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
                "(enabled):b,"
  /* specs/guild.integration.json:51:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
                "(syncing):b,"
  /* specs/guild.integration.json:52:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(role_id):|F|,"
  /* specs/guild.integration.json:53:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
                "(enable_emotions):b,"
  /* specs/guild.integration.json:54:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}'
  */
                "(expire_behavior):d,"
  /* specs/guild.integration.json:55:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
                "(expire_grace_period):d,"
  /* specs/guild.integration.json:56:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}'
  */
                "(user):F,"
  /* specs/guild.integration.json:57:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}'
  */
                "(account):F,"
  /* specs/guild.integration.json:58:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                "(synced_at):|F|,"
  /* specs/guild.integration.json:59:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
                "(subscriber_count):d,"
  /* specs/guild.integration.json:60:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                "(revoked):b,"
  /* specs/guild.integration.json:61:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}'
  */
                "(application):F,"
                "@arg_switches:b",
  /* specs/guild.integration.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.integration.json:48:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                p->name,
  /* specs/guild.integration.json:49:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                p->type,
  /* specs/guild.integration.json:50:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
                &p->enabled,
  /* specs/guild.integration.json:51:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
                &p->syncing,
  /* specs/guild.integration.json:52:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->role_id,
  /* specs/guild.integration.json:53:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
                &p->enable_emotions,
  /* specs/guild.integration.json:54:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}'
  */
                &p->expire_behavior,
  /* specs/guild.integration.json:55:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
                &p->expire_grace_period,
  /* specs/guild.integration.json:56:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}'
  */
                discord_user_to_json, p->user,
  /* specs/guild.integration.json:57:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}'
  */
                discord_guild_integration_account_to_json, p->account,
  /* specs/guild.integration.json:58:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                orka_unix_ms_to_iso8601, &p->synced_at,
  /* specs/guild.integration.json:59:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
                &p->subscriber_count,
  /* specs/guild.integration.json:60:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                &p->revoked,
  /* specs/guild.integration.json:61:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}'
  */
                discord_guild_integration_application_to_json, p->application,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_integration_cleanup_v(void *p) {
  discord_guild_integration_cleanup((struct discord_guild_integration *)p);
}

void discord_guild_integration_init_v(void *p) {
  discord_guild_integration_init((struct discord_guild_integration *)p);
}

void discord_guild_integration_free_v(void *p) {
 discord_guild_integration_free((struct discord_guild_integration *)p);
};

void discord_guild_integration_from_json_v(char *json, size_t len, void *p) {
 discord_guild_integration_from_json(json, len, (struct discord_guild_integration*)p);
}

size_t discord_guild_integration_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_integration_to_json(json, len, (struct discord_guild_integration*)p);
}

void discord_guild_integration_list_free_v(void **p) {
  discord_guild_integration_list_free((struct discord_guild_integration**)p);
}

void discord_guild_integration_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_integration_list_from_json(str, len, (struct discord_guild_integration ***)p);
}

size_t discord_guild_integration_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_integration_list_to_json(str, len, (struct discord_guild_integration **)p);
}


void discord_guild_integration_cleanup(struct discord_guild_integration *d) {
  /* specs/guild.integration.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/guild.integration.json:48:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  if (d->name)
    free(d->name);
  /* specs/guild.integration.json:49:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  if (d->type)
    free(d->type);
  /* specs/guild.integration.json:50:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */
  //p->enabled is a scalar
  /* specs/guild.integration.json:51:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */
  //p->syncing is a scalar
  /* specs/guild.integration.json:52:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->role_id is a scalar
  /* specs/guild.integration.json:53:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */
  //p->enable_emotions is a scalar
  /* specs/guild.integration.json:54:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}'
  */
  //p->expire_behavior is a scalar
  /* specs/guild.integration.json:55:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */
  //p->expire_grace_period is a scalar
  /* specs/guild.integration.json:56:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}'
  */
  if (d->user)
    discord_user_free(d->user);
  /* specs/guild.integration.json:57:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}'
  */
  if (d->account)
    discord_guild_integration_account_free(d->account);
  /* specs/guild.integration.json:58:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  //p->synced_at is a scalar
  /* specs/guild.integration.json:59:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */
  //p->subscriber_count is a scalar
  /* specs/guild.integration.json:60:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  //p->revoked is a scalar
  /* specs/guild.integration.json:61:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}'
  */
  if (d->application)
    discord_guild_integration_application_free(d->application);
}

void discord_guild_integration_init(struct discord_guild_integration *p) {
  memset(p, 0, sizeof(struct discord_guild_integration));
  /* specs/guild.integration.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/guild.integration.json:48:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */

  /* specs/guild.integration.json:49:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */

  /* specs/guild.integration.json:50:20
     '{ "name": "enabled", "type":{ "base":"bool"}}'
  */

  /* specs/guild.integration.json:51:20
     '{ "name": "syncing", "type":{ "base":"bool"}}'
  */

  /* specs/guild.integration.json:52:20
     '{ "name": "role_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/guild.integration.json:53:20
     '{ "name": "enable_emotions", "type":{ "base":"bool"}}'
  */

  /* specs/guild.integration.json:54:20
     '{ "name": "expire_behavior", "type":{ "base":"int", "int_alias":"enum discord_guild_integration_expire_behaviors"}}'
  */

  /* specs/guild.integration.json:55:20
     '{ "name": "expire_grace_period", "type":{ "base":"int"}}'
  */

  /* specs/guild.integration.json:56:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*"}, "opt":true}'
  */
  p->user = discord_user_alloc();

  /* specs/guild.integration.json:57:20
     '{ "name": "account", "type":{ "base":"struct discord_guild_integration_account", "dec":"*"}}'
  */
  p->account = discord_guild_integration_account_alloc();

  /* specs/guild.integration.json:58:20
     '{ "name": "synced_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */

  /* specs/guild.integration.json:59:20
     '{ "name": "subscriber_count", "type":{ "base":"int"}}'
  */

  /* specs/guild.integration.json:60:20
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */

  /* specs/guild.integration.json:61:20
     '{ "name": "application", "type":{ "base":"struct discord_guild_integration_application", "dec":"*" }}'
  */
  p->application = discord_guild_integration_application_alloc();

}
struct discord_guild_integration* discord_guild_integration_alloc() {
  struct discord_guild_integration *p= (struct discord_guild_integration*)malloc(sizeof(struct discord_guild_integration));
  discord_guild_integration_init(p);
  return p;
}

void discord_guild_integration_free(struct discord_guild_integration *p) {
  discord_guild_integration_cleanup(p);
  free(p);
}

void discord_guild_integration_list_free(struct discord_guild_integration **p) {
  ntl_free((void**)p, (vfvp)discord_guild_integration_cleanup);
}

void discord_guild_integration_list_from_json(char *str, size_t len, struct discord_guild_integration ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_integration);
  d.init_elem = discord_guild_integration_init_v;
  d.elem_from_buf = discord_guild_integration_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_integration_list_to_json(char *str, size_t len, struct discord_guild_integration **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_integration_to_json_v);
}

