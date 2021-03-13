/* This file is generated from specs/gateway.json, Please don't edit it. */
#include "specs.h"
/*
(null)
*/
namespace discord {
namespace gateway {

namespace identify {

/* This method is disabled at specs/gateway.json:75:31 */
void dait_from_json_disabled(char *json, size_t len, struct dait *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
                "(token):?s,"
                "(compress):b,"
                "(large_threshod):d,"
                "(shard):?s,"
                "(presense):F,"
                "(guild_subscriptions):b,"
                "(intents):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
                &p->token,
                &p->compress,
                &p->large_threshod,
                &p->shard,
                discord::gateway::status_update::dati_from_json, p->presense,
                &p->guild_subscriptions,
                &p->intents,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}


/* This method is disabled at specs/gateway.json:75:31 */
size_t dait_to_json_disabled(char *json, size_t len, struct dait *p)
{
  size_t r;
  r=json_inject(json, len, 
                "(token):s,"
                "(compress):b,"
                "(large_threshod):d,"
                "(shard):s,"
                "(presense):F,"
                "(guild_subscriptions):b,"
                "(intents):d,"
                "@arg_switches:b",
                p->token,
                &p->compress,
                &p->large_threshod,
                p->shard,
                discord::gateway::status_update::dati_to_json, p->presense,
                &p->guild_subscriptions,
                &p->intents,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dait_use_default_inject_settings(struct dait *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:79:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->token;

  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[1] = &p->compress;

  /* specs/gateway.json:81:19
     '{ "name":"large_threshod","type":{"base":"int"}}'
  */
  p->__M.arg_switches[2] = &p->large_threshod;

  /* specs/gateway.json:82:19
     '{ "name":"shard","type":{"base":"char", "dec":"*", "todo":true}}'
  */
  p->__M.arg_switches[3] = p->shard;

  /* specs/gateway.json:83:19
     '{ "name":"presense","type":{"base":"discord::gateway::status_update::dati", "dec":"*"}}'
  */
  p->__M.arg_switches[4] = p->presense;

  /* specs/gateway.json:84:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[5] = &p->guild_subscriptions;

  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int", "int_alias":"discord::gateway::intents::code"}}'
  */
  p->__M.arg_switches[6] = &p->intents;

}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void dait_cleanup_v(void *p) {
  dait_cleanup((struct dait *)p);
}

void dait_init_v(void *p) {
  dait_init((struct dait *)p);
}

void dait_free_v(void *p) {
 dait_free((struct dait *)p);
};

void dait_from_json_v(char *json, size_t len, void *p) {
 dait_from_json(json, len, (struct dait*)p);
}

size_t dait_to_json_v(char *json, size_t len, void *p) {
  return dait_to_json(json, len, (struct dait*)p);
}

void dait_list_free_v(void **p) {
  dait_list_free((struct dait**)p);
}

void dait_list_from_json_v(char *str, size_t len, void *p) {
  dait_list_from_json(str, len, (struct dait ***)p);
}

size_t dait_list_to_json_v(char *str, size_t len, void *p){
  return dait_list_to_json(str, len, (struct dait **)p);
}


void dait_cleanup(struct dait *d) {
  /* specs/gateway.json:79:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  if (d->token)
    free(d->token);
  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  //p->compress is a scalar
  /* specs/gateway.json:81:19
     '{ "name":"large_threshod","type":{"base":"int"}}'
  */
  //p->large_threshod is a scalar
  /* specs/gateway.json:82:19
     '{ "name":"shard","type":{"base":"char", "dec":"*", "todo":true}}'
  */
  if (d->shard)
    free(d->shard);
  /* specs/gateway.json:83:19
     '{ "name":"presense","type":{"base":"discord::gateway::status_update::dati", "dec":"*"}}'
  */
  if (d->presense)
    discord::gateway::status_update::dati_free(d->presense);
  /* specs/gateway.json:84:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  //p->guild_subscriptions is a scalar
  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int", "int_alias":"discord::gateway::intents::code"}}'
  */
  //p->intents is a scalar
}

void dait_init(struct dait *p) {
  memset(p, 0, sizeof(struct dait));
  /* specs/gateway.json:79:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */

  /* specs/gateway.json:81:19
     '{ "name":"large_threshod","type":{"base":"int"}}'
  */

  /* specs/gateway.json:82:19
     '{ "name":"shard","type":{"base":"char", "dec":"*", "todo":true}}'
  */

  /* specs/gateway.json:83:19
     '{ "name":"presense","type":{"base":"discord::gateway::status_update::dati", "dec":"*"}}'
  */
  p->presense = discord::gateway::status_update::dati_alloc();

  /* specs/gateway.json:84:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */

  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int", "int_alias":"discord::gateway::intents::code"}}'
  */

}
struct dait* dait_alloc() {
  struct dait *p= (struct dait*)malloc(sizeof(struct dait));
  dait_init(p);
  return p;
}

void dait_free(struct dait *p) {
  dait_cleanup(p);
  free(p);
}

void dait_list_free(struct dait **p) {
  ntl_free((void**)p, (vfvp)dait_cleanup);
}

void dait_list_from_json(char *str, size_t len, struct dait ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct dait);
  d.init_elem = dait_init_v;
  d.elem_from_buf = dait_from_json_v;
  d.ntl_recipient_p= (void***)p;
  orka_str_to_ntl(str, len, &d);
}

size_t dait_list_to_json(char *str, size_t len, struct dait **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dait_to_json_v);
}

} // namespace identify

namespace activity {

/* This method is disabled at specs/gateway.json:106:31 */
void dati_from_json_disabled(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
                "(name):s,"
                "(code):d,"
                "(url):s,"
                "(created_at):F,"
                "(application_id):F,"
                "(details):?s,"
                "(state):?s,"
                "(instance):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
                p->name,
                &p->code,
                p->url,
                orka_iso8601_to_unix_ms, &p->created_at,
                orka_strtoull, &p->application_id,
                &p->details,
                &p->state,
                &p->instance,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}


/* This method is disabled at specs/gateway.json:106:31 */
size_t dati_to_json_disabled(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
                "(name):s,"
                "(code):d,"
                "(url):s,"
                "(created_at):|F|,"
                "(application_id):|F|,"
                "(details):s,"
                "(state):s,"
                "(instance):b,"
                "@arg_switches:b",
                p->name,
                &p->code,
                p->url,
                orka_unix_ms_to_iso8601, &p->created_at,
                orka_ulltostr, &p->application_id,
                p->details,
                p->state,
                &p->instance,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:110:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/gateway.json:111:19
     '{ "name":"code","type":{"base":"int", "int_alias":"discord::gateway::activity::types::code"}}'
  */
  p->__M.arg_switches[1] = &p->code;

  /* specs/gateway.json:112:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"}}'
  */
  p->__M.arg_switches[2] = p->url;

  /* specs/gateway.json:113:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  p->__M.arg_switches[3] = &p->created_at;

  /* specs/gateway.json:114:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[4] = &p->application_id;

  /* specs/gateway.json:115:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[5] = p->details;

  /* specs/gateway.json:116:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[6] = p->state;

  /* specs/gateway.json:117:19
     '{ "name":"instance","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[7] = &p->instance;

}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void dati_cleanup_v(void *p) {
  dati_cleanup((struct dati *)p);
}

void dati_init_v(void *p) {
  dati_init((struct dati *)p);
}

void dati_free_v(void *p) {
 dati_free((struct dati *)p);
};

void dati_from_json_v(char *json, size_t len, void *p) {
 dati_from_json(json, len, (struct dati*)p);
}

size_t dati_to_json_v(char *json, size_t len, void *p) {
  return dati_to_json(json, len, (struct dati*)p);
}

void dati_list_free_v(void **p) {
  dati_list_free((struct dati**)p);
}

void dati_list_from_json_v(char *str, size_t len, void *p) {
  dati_list_from_json(str, len, (struct dati ***)p);
}

size_t dati_list_to_json_v(char *str, size_t len, void *p){
  return dati_list_to_json(str, len, (struct dati **)p);
}


void dati_cleanup(struct dati *d) {
  /* specs/gateway.json:110:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  //p->name is a scalar
  /* specs/gateway.json:111:19
     '{ "name":"code","type":{"base":"int", "int_alias":"discord::gateway::activity::types::code"}}'
  */
  //p->code is a scalar
  /* specs/gateway.json:112:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"}}'
  */
  //p->url is a scalar
  /* specs/gateway.json:113:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  //p->created_at is a scalar
  /* specs/gateway.json:114:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->application_id is a scalar
  /* specs/gateway.json:115:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}}'
  */
  if (d->details)
    free(d->details);
  /* specs/gateway.json:116:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}}'
  */
  if (d->state)
    free(d->state);
  /* specs/gateway.json:117:19
     '{ "name":"instance","type":{"base":"bool"}}'
  */
  //p->instance is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/gateway.json:110:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */

  /* specs/gateway.json:111:19
     '{ "name":"code","type":{"base":"int", "int_alias":"discord::gateway::activity::types::code"}}'
  */

  /* specs/gateway.json:112:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"}}'
  */

  /* specs/gateway.json:113:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}}'
  */

  /* specs/gateway.json:114:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/gateway.json:115:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:116:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:117:19
     '{ "name":"instance","type":{"base":"bool"}}'
  */

}
struct dati* dati_alloc() {
  struct dati *p= (struct dati*)malloc(sizeof(struct dati));
  dati_init(p);
  return p;
}

void dati_free(struct dati *p) {
  dati_cleanup(p);
  free(p);
}

void dati_list_free(struct dati **p) {
  ntl_free((void**)p, (vfvp)dati_cleanup);
}

void dati_list_from_json(char *str, size_t len, struct dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct dati);
  d.init_elem = dati_init_v;
  d.elem_from_buf = dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  orka_str_to_ntl(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace activity

namespace status_update {

/* This method is disabled at specs/gateway.json:124:31 */
void dati_from_json_disabled(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
                "(since):?s,"
                "(activities):F,"
                "(status):s,"
                "(afk):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
                &p->since,
                discord::gateway::activity::dati_list_from_json, &p->activities,
                p->status,
                &p->afk,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}


/* This method is disabled at specs/gateway.json:124:31 */
size_t dati_to_json_disabled(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
                "(since):s,"
                "(activities):F,"
                "(status):s,"
                "(afk):b,"
                "@arg_switches:b",
                p->since,
                discord::gateway::activity::dati_list_to_json, p->activities,
                p->status,
                &p->afk,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:128:19
     '{ "name":"since","type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->since;

  /* specs/gateway.json:129:19
     '{ "name":"activities","type":{"base":"discord::gateway::activity::dati", "dec":"ntl"}}'
  */
  p->__M.arg_switches[1] = p->activities;

  /* specs/gateway.json:130:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  p->__M.arg_switches[2] = p->status;

  /* specs/gateway.json:131:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[3] = &p->afk;

}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void dati_cleanup_v(void *p) {
  dati_cleanup((struct dati *)p);
}

void dati_init_v(void *p) {
  dati_init((struct dati *)p);
}

void dati_free_v(void *p) {
 dati_free((struct dati *)p);
};

void dati_from_json_v(char *json, size_t len, void *p) {
 dati_from_json(json, len, (struct dati*)p);
}

size_t dati_to_json_v(char *json, size_t len, void *p) {
  return dati_to_json(json, len, (struct dati*)p);
}

void dati_list_free_v(void **p) {
  dati_list_free((struct dati**)p);
}

void dati_list_from_json_v(char *str, size_t len, void *p) {
  dati_list_from_json(str, len, (struct dati ***)p);
}

size_t dati_list_to_json_v(char *str, size_t len, void *p){
  return dati_list_to_json(str, len, (struct dati **)p);
}


void dati_cleanup(struct dati *d) {
  /* specs/gateway.json:128:19
     '{ "name":"since","type":{"base":"char", "dec":"*"}}'
  */
  if (d->since)
    free(d->since);
  /* specs/gateway.json:129:19
     '{ "name":"activities","type":{"base":"discord::gateway::activity::dati", "dec":"ntl"}}'
  */
  if (d->activities)
    discord::gateway::activity::dati_list_free(d->activities);
  /* specs/gateway.json:130:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  //p->status is a scalar
  /* specs/gateway.json:131:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
  //p->afk is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/gateway.json:128:19
     '{ "name":"since","type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:129:19
     '{ "name":"activities","type":{"base":"discord::gateway::activity::dati", "dec":"ntl"}}'
  */

  /* specs/gateway.json:130:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */

  /* specs/gateway.json:131:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */

}
struct dati* dati_alloc() {
  struct dati *p= (struct dati*)malloc(sizeof(struct dati));
  dati_init(p);
  return p;
}

void dati_free(struct dati *p) {
  dati_cleanup(p);
  free(p);
}

void dati_list_free(struct dati **p) {
  ntl_free((void**)p, (vfvp)dati_cleanup);
}

void dati_list_from_json(char *str, size_t len, struct dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct dati);
  d.init_elem = dati_init_v;
  d.elem_from_buf = dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  orka_str_to_ntl(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace status_update
} // namespace gateway
} // namespace discord
