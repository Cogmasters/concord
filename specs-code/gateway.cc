/* This file is generated from specs/gateway.json, Please don't edit it. */
#include "specs.h"
/*
(null)
*/
namespace discord {
namespace gateway {

namespace identify {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/gateway.json:78:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
                "(token):?s,"
  /* specs/gateway.json:79:19
     '{ "name":"properties","type":{"base":"discord::gateway::identify::connection::dati", "dec":"*"}}'
  */
                "(properties):F,"
  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
                "(compress):b,"
  /* specs/gateway.json:81:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
                "(large_threshold):d,"
  /* specs/gateway.json:82:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
                "(guild_subscriptions):b,"
  /* specs/gateway.json:83:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  /* specs/gateway.json:84:19
     '{ "name":"presence","type":{"base":"discord::gateway::identify::status_update::dati", "dec":"*"}}'
  */
                "(presence):F,"
  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
                "(intents):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/gateway.json:78:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
                &p->token,
  /* specs/gateway.json:79:19
     '{ "name":"properties","type":{"base":"discord::gateway::identify::connection::dati", "dec":"*"}}'
  */
                discord::gateway::identify::connection::dati_from_json, p->properties,
  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
                &p->compress,
  /* specs/gateway.json:81:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
                &p->large_threshold,
  /* specs/gateway.json:82:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
                &p->guild_subscriptions,
  /* specs/gateway.json:83:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  /* specs/gateway.json:84:19
     '{ "name":"presence","type":{"base":"discord::gateway::identify::status_update::dati", "dec":"*"}}'
  */
                discord::gateway::identify::status_update::dati_from_json, p->presence,
  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
                &p->intents,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:78:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->token;

  /* specs/gateway.json:79:19
     '{ "name":"properties","type":{"base":"discord::gateway::identify::connection::dati", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->properties;

  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[2] = &p->compress;

  /* specs/gateway.json:81:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
  p->__M.arg_switches[3] = &p->large_threshold;

  /* specs/gateway.json:82:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[4] = &p->guild_subscriptions;

  /* specs/gateway.json:83:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */

  /* specs/gateway.json:84:19
     '{ "name":"presence","type":{"base":"discord::gateway::identify::status_update::dati", "dec":"*"}}'
  */
  p->__M.arg_switches[6] = p->presence;

  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
  p->__M.arg_switches[7] = &p->intents;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/gateway.json:78:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
                "(token):s,"
  /* specs/gateway.json:79:19
     '{ "name":"properties","type":{"base":"discord::gateway::identify::connection::dati", "dec":"*"}}'
  */
                "(properties):F,"
  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
                "(compress):b,"
  /* specs/gateway.json:81:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
                "(large_threshold):d,"
  /* specs/gateway.json:82:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
                "(guild_subscriptions):b,"
  /* specs/gateway.json:83:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  /* specs/gateway.json:84:19
     '{ "name":"presence","type":{"base":"discord::gateway::identify::status_update::dati", "dec":"*"}}'
  */
                "(presence):F,"
  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
                "(intents):d,"
                "@arg_switches:b",
  /* specs/gateway.json:78:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
                p->token,
  /* specs/gateway.json:79:19
     '{ "name":"properties","type":{"base":"discord::gateway::identify::connection::dati", "dec":"*"}}'
  */
                discord::gateway::identify::connection::dati_to_json, p->properties,
  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
                &p->compress,
  /* specs/gateway.json:81:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
                &p->large_threshold,
  /* specs/gateway.json:82:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
                &p->guild_subscriptions,
  /* specs/gateway.json:83:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  /* specs/gateway.json:84:19
     '{ "name":"presence","type":{"base":"discord::gateway::identify::status_update::dati", "dec":"*"}}'
  */
                discord::gateway::identify::status_update::dati_to_json, p->presence,
  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
                &p->intents,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
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
  /* specs/gateway.json:78:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  if (d->token)
    free(d->token);
  /* specs/gateway.json:79:19
     '{ "name":"properties","type":{"base":"discord::gateway::identify::connection::dati", "dec":"*"}}'
  */
  if (d->properties)
    discord::gateway::identify::connection::dati_free(d->properties);
  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  //p->compress is a scalar
  /* specs/gateway.json:81:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
  //p->large_threshold is a scalar
  /* specs/gateway.json:82:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  //p->guild_subscriptions is a scalar
  /* specs/gateway.json:83:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  //@todo p->(null)
  /* specs/gateway.json:84:19
     '{ "name":"presence","type":{"base":"discord::gateway::identify::status_update::dati", "dec":"*"}}'
  */
  if (d->presence)
    discord::gateway::identify::status_update::dati_free(d->presence);
  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
  //p->intents is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/gateway.json:78:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:79:19
     '{ "name":"properties","type":{"base":"discord::gateway::identify::connection::dati", "dec":"*"}}'
  */
  p->properties = discord::gateway::identify::connection::dati_alloc();

  /* specs/gateway.json:80:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */

  /* specs/gateway.json:81:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */

  /* specs/gateway.json:82:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */

  /* specs/gateway.json:83:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */

  /* specs/gateway.json:84:19
     '{ "name":"presence","type":{"base":"discord::gateway::identify::status_update::dati", "dec":"*"}}'
  */
  p->presence = discord::gateway::identify::status_update::dati_alloc();

  /* specs/gateway.json:85:19
     '{ "name":"intents","type":{"base":"int"}}'
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace identify

namespace identify {
namespace status_update {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/gateway.json:95:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                "(since):F,"
  /* specs/gateway.json:97:19
     '{ "name":"activities","type":{"base":"discord::gateway::identify::status_update::activity::dati", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
                "(activities):F,"
  /* specs/gateway.json:99:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
                "(status):s,"
  /* specs/gateway.json:100:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
                "(afk):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/gateway.json:95:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                orka_iso8601_to_unix_ms, &p->since,
  /* specs/gateway.json:97:19
     '{ "name":"activities","type":{"base":"discord::gateway::identify::status_update::activity::dati", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
                discord::gateway::identify::status_update::activity::dati_list_from_json, &p->activities,
  /* specs/gateway.json:99:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
                p->status,
  /* specs/gateway.json:100:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
                &p->afk,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:95:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  if (p->since != 0)
    p->__M.arg_switches[0] = &p->since;

  /* specs/gateway.json:97:19
     '{ "name":"activities","type":{"base":"discord::gateway::identify::status_update::activity::dati", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
  if (p->activities != NULL)
    p->__M.arg_switches[1] = p->activities;

  /* specs/gateway.json:99:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  p->__M.arg_switches[2] = p->status;

  /* specs/gateway.json:100:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[3] = &p->afk;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/gateway.json:95:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                "(since):|F|,"
  /* specs/gateway.json:97:19
     '{ "name":"activities","type":{"base":"discord::gateway::identify::status_update::activity::dati", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
                "(activities):F,"
  /* specs/gateway.json:99:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
                "(status):s,"
  /* specs/gateway.json:100:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
                "(afk):b,"
                "@arg_switches:b",
  /* specs/gateway.json:95:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                orka_unix_ms_to_iso8601, &p->since,
  /* specs/gateway.json:97:19
     '{ "name":"activities","type":{"base":"discord::gateway::identify::status_update::activity::dati", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
                discord::gateway::identify::status_update::activity::dati_list_to_json, p->activities,
  /* specs/gateway.json:99:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
                p->status,
  /* specs/gateway.json:100:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
                &p->afk,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
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
  /* specs/gateway.json:95:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  //p->since is a scalar
  /* specs/gateway.json:97:19
     '{ "name":"activities","type":{"base":"discord::gateway::identify::status_update::activity::dati", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
  if (d->activities)
    discord::gateway::identify::status_update::activity::dati_list_free(d->activities);
  /* specs/gateway.json:99:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  //p->status is a scalar
  /* specs/gateway.json:100:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
  //p->afk is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/gateway.json:95:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */

  /* specs/gateway.json:97:19
     '{ "name":"activities","type":{"base":"discord::gateway::identify::status_update::activity::dati", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */

  /* specs/gateway.json:99:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */

  /* specs/gateway.json:100:19
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace status_update
} // namespace identify

namespace identify {
namespace connection {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/gateway.json:110:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
                "($os):?s,"
  /* specs/gateway.json:111:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
                "($browser):?s,"
  /* specs/gateway.json:112:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
                "($device):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/gateway.json:110:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
                &p->$os,
  /* specs/gateway.json:111:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
                &p->$browser,
  /* specs/gateway.json:112:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
                &p->$device,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:110:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->$os;

  /* specs/gateway.json:111:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->$browser;

  /* specs/gateway.json:112:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[2] = p->$device;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/gateway.json:110:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
                "($os):s,"
  /* specs/gateway.json:111:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
                "($browser):s,"
  /* specs/gateway.json:112:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
                "($device):s,"
                "@arg_switches:b",
  /* specs/gateway.json:110:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
                p->$os,
  /* specs/gateway.json:111:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
                p->$browser,
  /* specs/gateway.json:112:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
                p->$device,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
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
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->$os)
    free(d->$os);
  /* specs/gateway.json:111:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->$browser)
    free(d->$browser);
  /* specs/gateway.json:112:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->$device)
    free(d->$device);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/gateway.json:110:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:111:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:112:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace connection
} // namespace identify

namespace identify {
namespace status_update {
namespace activity {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/gateway.json:122:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
                "(name):s,"
  /* specs/gateway.json:123:19
     '{ "name":"type","type":{"base":"int"}}'
  */
                "(type):d,"
  /* specs/gateway.json:124:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/gateway.json:126:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                "(created_at):F,"
  /* specs/gateway.json:128:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
                "(application_id):F,"
  /* specs/gateway.json:130:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(details):?s,"
  /* specs/gateway.json:132:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(state):?s,"
  /* specs/gateway.json:134:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
                "(instance):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/gateway.json:122:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
                p->name,
  /* specs/gateway.json:123:19
     '{ "name":"type","type":{"base":"int"}}'
  */
                &p->type,
  /* specs/gateway.json:124:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/gateway.json:126:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                orka_iso8601_to_unix_ms, &p->created_at,
  /* specs/gateway.json:128:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
                orka_strtoull, &p->application_id,
  /* specs/gateway.json:130:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                &p->details,
  /* specs/gateway.json:132:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                &p->state,
  /* specs/gateway.json:134:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
                &p->instance,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:122:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/gateway.json:123:19
     '{ "name":"type","type":{"base":"int"}}'
  */
  p->__M.arg_switches[1] = &p->type;

  /* specs/gateway.json:124:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[2] = p->url;

  /* specs/gateway.json:126:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  if (p->created_at != 0)
    p->__M.arg_switches[3] = &p->created_at;

  /* specs/gateway.json:128:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
  if (p->application_id != 0)
    p->__M.arg_switches[4] = &p->application_id;

  /* specs/gateway.json:130:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (p->details != NULL)
    p->__M.arg_switches[5] = p->details;

  /* specs/gateway.json:132:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (p->state != NULL)
    p->__M.arg_switches[6] = p->state;

  /* specs/gateway.json:134:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
  if (p->instance != false)
    p->__M.arg_switches[7] = &p->instance;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/gateway.json:122:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
                "(name):s,"
  /* specs/gateway.json:123:19
     '{ "name":"type","type":{"base":"int"}}'
  */
                "(type):d,"
  /* specs/gateway.json:124:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/gateway.json:126:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                "(created_at):|F|,"
  /* specs/gateway.json:128:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
                "(application_id):|F|,"
  /* specs/gateway.json:130:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(details):s,"
  /* specs/gateway.json:132:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(state):s,"
  /* specs/gateway.json:134:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
                "(instance):b,"
                "@arg_switches:b",
  /* specs/gateway.json:122:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
                p->name,
  /* specs/gateway.json:123:19
     '{ "name":"type","type":{"base":"int"}}'
  */
                &p->type,
  /* specs/gateway.json:124:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/gateway.json:126:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                orka_unix_ms_to_iso8601, &p->created_at,
  /* specs/gateway.json:128:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
                orka_ulltostr, &p->application_id,
  /* specs/gateway.json:130:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                p->details,
  /* specs/gateway.json:132:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                p->state,
  /* specs/gateway.json:134:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
                &p->instance,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
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
  /* specs/gateway.json:122:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  //p->name is a scalar
  /* specs/gateway.json:123:19
     '{ "name":"type","type":{"base":"int"}}'
  */
  //p->type is a scalar
  /* specs/gateway.json:124:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/gateway.json:126:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  //p->created_at is a scalar
  /* specs/gateway.json:128:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
  //p->application_id is a scalar
  /* specs/gateway.json:130:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (d->details)
    free(d->details);
  /* specs/gateway.json:132:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (d->state)
    free(d->state);
  /* specs/gateway.json:134:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
  //p->instance is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/gateway.json:122:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */

  /* specs/gateway.json:123:19
     '{ "name":"type","type":{"base":"int"}}'
  */

  /* specs/gateway.json:124:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */

  /* specs/gateway.json:126:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */

  /* specs/gateway.json:128:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */

  /* specs/gateway.json:130:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */

  /* specs/gateway.json:132:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */

  /* specs/gateway.json:134:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace activity
} // namespace status_update
} // namespace identify
} // namespace gateway
} // namespace discord
