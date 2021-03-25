/* This file is generated from specs/gateway.json, Please don't edit it. */
#include "specs.h"
/*
(null)
*/

void discord_gateway_identify_from_json(char *json, size_t len, struct discord_gateway_identify *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/gateway.json:75:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
                "(token):?s,"
  /* specs/gateway.json:76:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
                "(properties):F,"
  /* specs/gateway.json:77:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
                "(compress):b,"
  /* specs/gateway.json:78:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
                "(large_threshold):d,"
  /* specs/gateway.json:79:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
                "(guild_subscriptions):b,"
  /* specs/gateway.json:80:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  /* specs/gateway.json:81:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}'
  */
                "(presence):F,"
  /* specs/gateway.json:82:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
                "(intents):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/gateway.json:75:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
                &p->token,
  /* specs/gateway.json:76:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
                discord_gateway_identify_connection_from_json, p->properties,
  /* specs/gateway.json:77:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
                &p->compress,
  /* specs/gateway.json:78:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
                &p->large_threshold,
  /* specs/gateway.json:79:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
                &p->guild_subscriptions,
  /* specs/gateway.json:80:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  /* specs/gateway.json:81:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}'
  */
                discord_gateway_status_update_from_json, p->presence,
  /* specs/gateway.json:82:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
                &p->intents,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_gateway_identify_use_default_inject_settings(struct discord_gateway_identify *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:75:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->token;

  /* specs/gateway.json:76:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->properties;

  /* specs/gateway.json:77:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[2] = &p->compress;

  /* specs/gateway.json:78:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
  p->__M.arg_switches[3] = &p->large_threshold;

  /* specs/gateway.json:79:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[4] = &p->guild_subscriptions;

  /* specs/gateway.json:80:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */

  /* specs/gateway.json:81:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}'
  */
  p->__M.arg_switches[6] = p->presence;

  /* specs/gateway.json:82:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
  p->__M.arg_switches[7] = &p->intents;

}

size_t discord_gateway_identify_to_json(char *json, size_t len, struct discord_gateway_identify *p)
{
  size_t r;
  discord_gateway_identify_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/gateway.json:75:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
                "(token):s,"
  /* specs/gateway.json:76:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
                "(properties):F,"
  /* specs/gateway.json:77:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
                "(compress):b,"
  /* specs/gateway.json:78:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
                "(large_threshold):d,"
  /* specs/gateway.json:79:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
                "(guild_subscriptions):b,"
  /* specs/gateway.json:80:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  /* specs/gateway.json:81:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}'
  */
                "(presence):F,"
  /* specs/gateway.json:82:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
                "(intents):d,"
                "@arg_switches:b",
  /* specs/gateway.json:75:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
                p->token,
  /* specs/gateway.json:76:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
                discord_gateway_identify_connection_to_json, p->properties,
  /* specs/gateway.json:77:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
                &p->compress,
  /* specs/gateway.json:78:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
                &p->large_threshold,
  /* specs/gateway.json:79:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
                &p->guild_subscriptions,
  /* specs/gateway.json:80:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  /* specs/gateway.json:81:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}'
  */
                discord_gateway_status_update_to_json, p->presence,
  /* specs/gateway.json:82:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
                &p->intents,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_gateway_identify_cleanup_v(void *p) {
  discord_gateway_identify_cleanup((struct discord_gateway_identify *)p);
}

void discord_gateway_identify_init_v(void *p) {
  discord_gateway_identify_init((struct discord_gateway_identify *)p);
}

void discord_gateway_identify_free_v(void *p) {
 discord_gateway_identify_free((struct discord_gateway_identify *)p);
};

void discord_gateway_identify_from_json_v(char *json, size_t len, void *p) {
 discord_gateway_identify_from_json(json, len, (struct discord_gateway_identify*)p);
}

size_t discord_gateway_identify_to_json_v(char *json, size_t len, void *p) {
  return discord_gateway_identify_to_json(json, len, (struct discord_gateway_identify*)p);
}

void discord_gateway_identify_list_free_v(void **p) {
  discord_gateway_identify_list_free((struct discord_gateway_identify**)p);
}

void discord_gateway_identify_list_from_json_v(char *str, size_t len, void *p) {
  discord_gateway_identify_list_from_json(str, len, (struct discord_gateway_identify ***)p);
}

size_t discord_gateway_identify_list_to_json_v(char *str, size_t len, void *p){
  return discord_gateway_identify_list_to_json(str, len, (struct discord_gateway_identify **)p);
}


void discord_gateway_identify_cleanup(struct discord_gateway_identify *d) {
  /* specs/gateway.json:75:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */
  if (d->token)
    free(d->token);
  /* specs/gateway.json:76:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
  if (d->properties)
    discord_gateway_identify_connection_free(d->properties);
  /* specs/gateway.json:77:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */
  //p->compress is a scalar
  /* specs/gateway.json:78:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */
  //p->large_threshold is a scalar
  /* specs/gateway.json:79:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */
  //p->guild_subscriptions is a scalar
  /* specs/gateway.json:80:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */
  //@todo p->(null)
  /* specs/gateway.json:81:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}'
  */
  if (d->presence)
    discord_gateway_status_update_free(d->presence);
  /* specs/gateway.json:82:19
     '{ "name":"intents","type":{"base":"int"}}'
  */
  //p->intents is a scalar
}

void discord_gateway_identify_init(struct discord_gateway_identify *p) {
  memset(p, 0, sizeof(struct discord_gateway_identify));
  /* specs/gateway.json:75:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:76:19
     '{ "name":"properties","type":{"base":"struct discord_gateway_identify_connection", "dec":"*"}}'
  */
  p->properties = discord_gateway_identify_connection_alloc();

  /* specs/gateway.json:77:19
     '{ "name":"compress","type":{"base":"bool"}}'
  */

  /* specs/gateway.json:78:19
     '{ "name":"large_threshold","type":{"base":"int"}}'
  */

  /* specs/gateway.json:79:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}'
  */

  /* specs/gateway.json:80:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}'
  */

  /* specs/gateway.json:81:19
     '{ "name":"presence","type":{"base":"struct discord_gateway_status_update", "dec":"*"}}'
  */
  p->presence = discord_gateway_status_update_alloc();

  /* specs/gateway.json:82:19
     '{ "name":"intents","type":{"base":"int"}}'
  */

}
struct discord_gateway_identify* discord_gateway_identify_alloc() {
  struct discord_gateway_identify *p= (struct discord_gateway_identify*)malloc(sizeof(struct discord_gateway_identify));
  discord_gateway_identify_init(p);
  return p;
}

void discord_gateway_identify_free(struct discord_gateway_identify *p) {
  discord_gateway_identify_cleanup(p);
  free(p);
}

void discord_gateway_identify_list_free(struct discord_gateway_identify **p) {
  ntl_free((void**)p, (vfvp)discord_gateway_identify_cleanup);
}

void discord_gateway_identify_list_from_json(char *str, size_t len, struct discord_gateway_identify ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_gateway_identify);
  d.init_elem = discord_gateway_identify_init_v;
  d.elem_from_buf = discord_gateway_identify_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_gateway_identify_list_to_json(char *str, size_t len, struct discord_gateway_identify **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_gateway_identify_to_json_v);
}


void discord_gateway_status_update_from_json(char *json, size_t len, struct discord_gateway_status_update *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/gateway.json:91:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                "(since):F,"
  /* specs/gateway.json:93:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
                "(activities):F,"
  /* specs/gateway.json:95:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
                "(status):s,"
  /* specs/gateway.json:96:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
                "(afk):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/gateway.json:91:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                orka_iso8601_to_unix_ms, &p->since,
  /* specs/gateway.json:93:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
                discord_gateway_activity_list_from_json, &p->activities,
  /* specs/gateway.json:95:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
                p->status,
  /* specs/gateway.json:96:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
                &p->afk,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_gateway_status_update_use_default_inject_settings(struct discord_gateway_status_update *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:91:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  if (p->since != 0)
    p->__M.arg_switches[0] = &p->since;

  /* specs/gateway.json:93:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
  if (p->activities != NULL)
    p->__M.arg_switches[1] = p->activities;

  /* specs/gateway.json:95:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  p->__M.arg_switches[2] = p->status;

  /* specs/gateway.json:96:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
  p->__M.arg_switches[3] = &p->afk;

}

size_t discord_gateway_status_update_to_json(char *json, size_t len, struct discord_gateway_status_update *p)
{
  size_t r;
  discord_gateway_status_update_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/gateway.json:91:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                "(since):|F|,"
  /* specs/gateway.json:93:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
                "(activities):F,"
  /* specs/gateway.json:95:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
                "(status):s,"
  /* specs/gateway.json:96:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
                "(afk):b,"
                "@arg_switches:b",
  /* specs/gateway.json:91:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                orka_unix_ms_to_iso8601, &p->since,
  /* specs/gateway.json:93:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
                discord_gateway_activity_list_to_json, p->activities,
  /* specs/gateway.json:95:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
                p->status,
  /* specs/gateway.json:96:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
                &p->afk,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_gateway_status_update_cleanup_v(void *p) {
  discord_gateway_status_update_cleanup((struct discord_gateway_status_update *)p);
}

void discord_gateway_status_update_init_v(void *p) {
  discord_gateway_status_update_init((struct discord_gateway_status_update *)p);
}

void discord_gateway_status_update_free_v(void *p) {
 discord_gateway_status_update_free((struct discord_gateway_status_update *)p);
};

void discord_gateway_status_update_from_json_v(char *json, size_t len, void *p) {
 discord_gateway_status_update_from_json(json, len, (struct discord_gateway_status_update*)p);
}

size_t discord_gateway_status_update_to_json_v(char *json, size_t len, void *p) {
  return discord_gateway_status_update_to_json(json, len, (struct discord_gateway_status_update*)p);
}

void discord_gateway_status_update_list_free_v(void **p) {
  discord_gateway_status_update_list_free((struct discord_gateway_status_update**)p);
}

void discord_gateway_status_update_list_from_json_v(char *str, size_t len, void *p) {
  discord_gateway_status_update_list_from_json(str, len, (struct discord_gateway_status_update ***)p);
}

size_t discord_gateway_status_update_list_to_json_v(char *str, size_t len, void *p){
  return discord_gateway_status_update_list_to_json(str, len, (struct discord_gateway_status_update **)p);
}


void discord_gateway_status_update_cleanup(struct discord_gateway_status_update *d) {
  /* specs/gateway.json:91:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  //p->since is a scalar
  /* specs/gateway.json:93:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */
  if (d->activities)
    discord_gateway_activity_list_free(d->activities);
  /* specs/gateway.json:95:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */
  //p->status is a scalar
  /* specs/gateway.json:96:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */
  //p->afk is a scalar
}

void discord_gateway_status_update_init(struct discord_gateway_status_update *p) {
  memset(p, 0, sizeof(struct discord_gateway_status_update));
  /* specs/gateway.json:91:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */

  /* specs/gateway.json:93:19
     '{ "name":"activities","type":{"base":"struct discord_gateway_activity", "dec":"ntl"}, 
          "option":true, "inject_if_not":null}'
  */

  /* specs/gateway.json:95:19
     '{ "name":"status","type":{"base":"char", "dec":"[16]"}}'
  */

  /* specs/gateway.json:96:19
     '{ "name":"afk","type":{"base":"bool"}}'
  */

}
struct discord_gateway_status_update* discord_gateway_status_update_alloc() {
  struct discord_gateway_status_update *p= (struct discord_gateway_status_update*)malloc(sizeof(struct discord_gateway_status_update));
  discord_gateway_status_update_init(p);
  return p;
}

void discord_gateway_status_update_free(struct discord_gateway_status_update *p) {
  discord_gateway_status_update_cleanup(p);
  free(p);
}

void discord_gateway_status_update_list_free(struct discord_gateway_status_update **p) {
  ntl_free((void**)p, (vfvp)discord_gateway_status_update_cleanup);
}

void discord_gateway_status_update_list_from_json(char *str, size_t len, struct discord_gateway_status_update ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_gateway_status_update);
  d.init_elem = discord_gateway_status_update_init_v;
  d.elem_from_buf = discord_gateway_status_update_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_gateway_status_update_list_to_json(char *str, size_t len, struct discord_gateway_status_update **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_gateway_status_update_to_json_v);
}


void discord_gateway_identify_connection_from_json(char *json, size_t len, struct discord_gateway_identify_connection *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/gateway.json:106:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
                "($os):?s,"
  /* specs/gateway.json:107:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
                "($browser):?s,"
  /* specs/gateway.json:108:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
                "($device):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/gateway.json:106:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
                &p->$os,
  /* specs/gateway.json:107:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
                &p->$browser,
  /* specs/gateway.json:108:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
                &p->$device,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_gateway_identify_connection_use_default_inject_settings(struct discord_gateway_identify_connection *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:106:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->$os;

  /* specs/gateway.json:107:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->$browser;

  /* specs/gateway.json:108:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[2] = p->$device;

}

size_t discord_gateway_identify_connection_to_json(char *json, size_t len, struct discord_gateway_identify_connection *p)
{
  size_t r;
  discord_gateway_identify_connection_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/gateway.json:106:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
                "($os):s,"
  /* specs/gateway.json:107:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
                "($browser):s,"
  /* specs/gateway.json:108:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
                "($device):s,"
                "@arg_switches:b",
  /* specs/gateway.json:106:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
                p->$os,
  /* specs/gateway.json:107:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
                p->$browser,
  /* specs/gateway.json:108:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
                p->$device,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_gateway_identify_connection_cleanup_v(void *p) {
  discord_gateway_identify_connection_cleanup((struct discord_gateway_identify_connection *)p);
}

void discord_gateway_identify_connection_init_v(void *p) {
  discord_gateway_identify_connection_init((struct discord_gateway_identify_connection *)p);
}

void discord_gateway_identify_connection_free_v(void *p) {
 discord_gateway_identify_connection_free((struct discord_gateway_identify_connection *)p);
};

void discord_gateway_identify_connection_from_json_v(char *json, size_t len, void *p) {
 discord_gateway_identify_connection_from_json(json, len, (struct discord_gateway_identify_connection*)p);
}

size_t discord_gateway_identify_connection_to_json_v(char *json, size_t len, void *p) {
  return discord_gateway_identify_connection_to_json(json, len, (struct discord_gateway_identify_connection*)p);
}

void discord_gateway_identify_connection_list_free_v(void **p) {
  discord_gateway_identify_connection_list_free((struct discord_gateway_identify_connection**)p);
}

void discord_gateway_identify_connection_list_from_json_v(char *str, size_t len, void *p) {
  discord_gateway_identify_connection_list_from_json(str, len, (struct discord_gateway_identify_connection ***)p);
}

size_t discord_gateway_identify_connection_list_to_json_v(char *str, size_t len, void *p){
  return discord_gateway_identify_connection_list_to_json(str, len, (struct discord_gateway_identify_connection **)p);
}


void discord_gateway_identify_connection_cleanup(struct discord_gateway_identify_connection *d) {
  /* specs/gateway.json:106:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->$os)
    free(d->$os);
  /* specs/gateway.json:107:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->$browser)
    free(d->$browser);
  /* specs/gateway.json:108:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->$device)
    free(d->$device);
}

void discord_gateway_identify_connection_init(struct discord_gateway_identify_connection *p) {
  memset(p, 0, sizeof(struct discord_gateway_identify_connection));
  /* specs/gateway.json:106:19
     '{ "name":"$os", "type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:107:19
     '{ "name":"$browser", "type":{"base":"char", "dec":"*"}}'
  */

  /* specs/gateway.json:108:19
     '{ "name":"$device", "type":{"base":"char", "dec":"*"}}'
  */

}
struct discord_gateway_identify_connection* discord_gateway_identify_connection_alloc() {
  struct discord_gateway_identify_connection *p= (struct discord_gateway_identify_connection*)malloc(sizeof(struct discord_gateway_identify_connection));
  discord_gateway_identify_connection_init(p);
  return p;
}

void discord_gateway_identify_connection_free(struct discord_gateway_identify_connection *p) {
  discord_gateway_identify_connection_cleanup(p);
  free(p);
}

void discord_gateway_identify_connection_list_free(struct discord_gateway_identify_connection **p) {
  ntl_free((void**)p, (vfvp)discord_gateway_identify_connection_cleanup);
}

void discord_gateway_identify_connection_list_from_json(char *str, size_t len, struct discord_gateway_identify_connection ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_gateway_identify_connection);
  d.init_elem = discord_gateway_identify_connection_init_v;
  d.elem_from_buf = discord_gateway_identify_connection_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_gateway_identify_connection_list_to_json(char *str, size_t len, struct discord_gateway_identify_connection **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_gateway_identify_connection_to_json_v);
}


void discord_gateway_activity_from_json(char *json, size_t len, struct discord_gateway_activity *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/gateway.json:117:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
                "(name):s,"
  /* specs/gateway.json:118:19
     '{ "name":"type","type":{"base":"int"}}'
  */
                "(type):d,"
  /* specs/gateway.json:119:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/gateway.json:121:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                "(created_at):F,"
  /* specs/gateway.json:123:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
                "(application_id):F,"
  /* specs/gateway.json:125:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(details):?s,"
  /* specs/gateway.json:127:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(state):?s,"
  /* specs/gateway.json:129:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
                "(instance):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/gateway.json:117:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
                p->name,
  /* specs/gateway.json:118:19
     '{ "name":"type","type":{"base":"int"}}'
  */
                &p->type,
  /* specs/gateway.json:119:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/gateway.json:121:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                orka_iso8601_to_unix_ms, &p->created_at,
  /* specs/gateway.json:123:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
                orka_strtoull, &p->application_id,
  /* specs/gateway.json:125:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                &p->details,
  /* specs/gateway.json:127:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                &p->state,
  /* specs/gateway.json:129:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
                &p->instance,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_gateway_activity_use_default_inject_settings(struct discord_gateway_activity *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/gateway.json:117:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/gateway.json:118:19
     '{ "name":"type","type":{"base":"int"}}'
  */
  p->__M.arg_switches[1] = &p->type;

  /* specs/gateway.json:119:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[2] = p->url;

  /* specs/gateway.json:121:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  if (p->created_at != 0)
    p->__M.arg_switches[3] = &p->created_at;

  /* specs/gateway.json:123:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
  if (p->application_id != 0)
    p->__M.arg_switches[4] = &p->application_id;

  /* specs/gateway.json:125:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (p->details != NULL)
    p->__M.arg_switches[5] = p->details;

  /* specs/gateway.json:127:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (p->state != NULL)
    p->__M.arg_switches[6] = p->state;

  /* specs/gateway.json:129:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
  if (p->instance != false)
    p->__M.arg_switches[7] = &p->instance;

}

size_t discord_gateway_activity_to_json(char *json, size_t len, struct discord_gateway_activity *p)
{
  size_t r;
  discord_gateway_activity_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/gateway.json:117:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
                "(name):s,"
  /* specs/gateway.json:118:19
     '{ "name":"type","type":{"base":"int"}}'
  */
                "(type):d,"
  /* specs/gateway.json:119:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/gateway.json:121:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                "(created_at):|F|,"
  /* specs/gateway.json:123:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
                "(application_id):|F|,"
  /* specs/gateway.json:125:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(details):s,"
  /* specs/gateway.json:127:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(state):s,"
  /* specs/gateway.json:129:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
                "(instance):b,"
                "@arg_switches:b",
  /* specs/gateway.json:117:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
                p->name,
  /* specs/gateway.json:118:19
     '{ "name":"type","type":{"base":"int"}}'
  */
                &p->type,
  /* specs/gateway.json:119:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/gateway.json:121:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
                orka_unix_ms_to_iso8601, &p->created_at,
  /* specs/gateway.json:123:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
                orka_ulltostr, &p->application_id,
  /* specs/gateway.json:125:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                p->details,
  /* specs/gateway.json:127:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                p->state,
  /* specs/gateway.json:129:19
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
void discord_gateway_activity_cleanup_v(void *p) {
  discord_gateway_activity_cleanup((struct discord_gateway_activity *)p);
}

void discord_gateway_activity_init_v(void *p) {
  discord_gateway_activity_init((struct discord_gateway_activity *)p);
}

void discord_gateway_activity_free_v(void *p) {
 discord_gateway_activity_free((struct discord_gateway_activity *)p);
};

void discord_gateway_activity_from_json_v(char *json, size_t len, void *p) {
 discord_gateway_activity_from_json(json, len, (struct discord_gateway_activity*)p);
}

size_t discord_gateway_activity_to_json_v(char *json, size_t len, void *p) {
  return discord_gateway_activity_to_json(json, len, (struct discord_gateway_activity*)p);
}

void discord_gateway_activity_list_free_v(void **p) {
  discord_gateway_activity_list_free((struct discord_gateway_activity**)p);
}

void discord_gateway_activity_list_from_json_v(char *str, size_t len, void *p) {
  discord_gateway_activity_list_from_json(str, len, (struct discord_gateway_activity ***)p);
}

size_t discord_gateway_activity_list_to_json_v(char *str, size_t len, void *p){
  return discord_gateway_activity_list_to_json(str, len, (struct discord_gateway_activity **)p);
}


void discord_gateway_activity_cleanup(struct discord_gateway_activity *d) {
  /* specs/gateway.json:117:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */
  //p->name is a scalar
  /* specs/gateway.json:118:19
     '{ "name":"type","type":{"base":"int"}}'
  */
  //p->type is a scalar
  /* specs/gateway.json:119:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/gateway.json:121:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */
  //p->created_at is a scalar
  /* specs/gateway.json:123:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */
  //p->application_id is a scalar
  /* specs/gateway.json:125:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (d->details)
    free(d->details);
  /* specs/gateway.json:127:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (d->state)
    free(d->state);
  /* specs/gateway.json:129:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */
  //p->instance is a scalar
}

void discord_gateway_activity_init(struct discord_gateway_activity *p) {
  memset(p, 0, sizeof(struct discord_gateway_activity));
  /* specs/gateway.json:117:19
     '{ "name":"name","type":{"base":"char", "dec":"[512]"}}'
  */

  /* specs/gateway.json:118:19
     '{ "name":"type","type":{"base":"int"}}'
  */

  /* specs/gateway.json:119:19
     '{ "name":"url","type":{"base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */

  /* specs/gateway.json:121:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"},
          "option":true, "inject_if_not":0 }'
  */

  /* specs/gateway.json:123:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" },
          "option":true, "inject_if_not":0 }'
  */

  /* specs/gateway.json:125:19
     '{ "name":"details","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */

  /* specs/gateway.json:127:19
     '{ "name":"state","type":{"base":"char", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */

  /* specs/gateway.json:129:19
     '{ "name":"instance","type":{"base":"bool"},
          "option":true, "inject_if_not":false}'
  */

}
struct discord_gateway_activity* discord_gateway_activity_alloc() {
  struct discord_gateway_activity *p= (struct discord_gateway_activity*)malloc(sizeof(struct discord_gateway_activity));
  discord_gateway_activity_init(p);
  return p;
}

void discord_gateway_activity_free(struct discord_gateway_activity *p) {
  discord_gateway_activity_cleanup(p);
  free(p);
}

void discord_gateway_activity_list_free(struct discord_gateway_activity **p) {
  ntl_free((void**)p, (vfvp)discord_gateway_activity_cleanup);
}

void discord_gateway_activity_list_from_json(char *str, size_t len, struct discord_gateway_activity ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_gateway_activity);
  d.init_elem = discord_gateway_activity_init_v;
  d.elem_from_buf = discord_gateway_activity_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_gateway_activity_list_to_json(char *str, size_t len, struct discord_gateway_activity **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_gateway_activity_to_json_v);
}

