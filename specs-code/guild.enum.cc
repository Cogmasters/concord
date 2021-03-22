/* This file is generated from specs/guild.enum.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/
namespace discord {
namespace guild {

namespace unavailable_guild {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/guild.enum.json:103:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                "(unavailable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.enum.json:103:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                &p->unavailable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.enum.json:103:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
  p->__M.arg_switches[1] = &p->unavailable;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/guild.enum.json:103:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                "(unavailable):b,"
                "@arg_switches:b",
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.enum.json:103:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                &p->unavailable,
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
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/guild.enum.json:103:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
  //p->unavailable is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/guild.enum.json:103:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
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

} // namespace unavailable_guild

namespace preview {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.enum.json:112:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/guild.enum.json:113:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/guild.enum.json:114:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(icon):?s,"
  /* specs/guild.enum.json:115:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(splash):?s,"
  /* specs/guild.enum.json:116:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(discovery):?s,"
  /* specs/guild.enum.json:117:18
     '{"name":"emojis", "type":{"base":"discord::emoji::dati", "dec":"*"}}'
  */
                "(emojis):F,"
  /* specs/guild.enum.json:118:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/guild.enum.json:119:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                "(approximate_member_count):d,"
  /* specs/guild.enum.json:120:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                "(approximate_presence_count):d,"
  /* specs/guild.enum.json:121:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                "(description):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.enum.json:112:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.enum.json:113:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/guild.enum.json:114:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->icon,
  /* specs/guild.enum.json:115:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->splash,
  /* specs/guild.enum.json:116:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->discovery,
  /* specs/guild.enum.json:117:18
     '{"name":"emojis", "type":{"base":"discord::emoji::dati", "dec":"*"}}'
  */
                discord::emoji::dati_from_json, p->emojis,
  /* specs/guild.enum.json:118:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/guild.enum.json:119:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                &p->approximate_member_count,
  /* specs/guild.enum.json:120:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                &p->approximate_presence_count,
  /* specs/guild.enum.json:121:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.enum.json:112:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.enum.json:113:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/guild.enum.json:114:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[2] = p->icon;

  /* specs/guild.enum.json:115:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[3] = p->splash;

  /* specs/guild.enum.json:116:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[4] = p->discovery;

  /* specs/guild.enum.json:117:18
     '{"name":"emojis", "type":{"base":"discord::emoji::dati", "dec":"*"}}'
  */
  p->__M.arg_switches[5] = p->emojis;

  /* specs/guild.enum.json:118:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */

  /* specs/guild.enum.json:119:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
  p->__M.arg_switches[7] = &p->approximate_member_count;

  /* specs/guild.enum.json:120:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
  p->__M.arg_switches[8] = &p->approximate_presence_count;

  /* specs/guild.enum.json:121:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  p->__M.arg_switches[9] = p->description;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.enum.json:112:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/guild.enum.json:113:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/guild.enum.json:114:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(icon):s,"
  /* specs/guild.enum.json:115:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(splash):s,"
  /* specs/guild.enum.json:116:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(discovery):s,"
  /* specs/guild.enum.json:117:18
     '{"name":"emojis", "type":{"base":"discord::emoji::dati", "dec":"*"}}'
  */
                "(emojis):F,"
  /* specs/guild.enum.json:118:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/guild.enum.json:119:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                "(approximate_member_count):d,"
  /* specs/guild.enum.json:120:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                "(approximate_presence_count):d,"
  /* specs/guild.enum.json:121:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                "(description):s,"
                "@arg_switches:b",
  /* specs/guild.enum.json:112:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.enum.json:113:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/guild.enum.json:114:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->icon,
  /* specs/guild.enum.json:115:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->splash,
  /* specs/guild.enum.json:116:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->discovery,
  /* specs/guild.enum.json:117:18
     '{"name":"emojis", "type":{"base":"discord::emoji::dati", "dec":"*"}}'
  */
                discord::emoji::dati_to_json, p->emojis,
  /* specs/guild.enum.json:118:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/guild.enum.json:119:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                &p->approximate_member_count,
  /* specs/guild.enum.json:120:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                &p->approximate_presence_count,
  /* specs/guild.enum.json:121:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                p->description,
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
  /* specs/guild.enum.json:112:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/guild.enum.json:113:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  //p->name is a scalar
  /* specs/guild.enum.json:114:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->icon)
    free(d->icon);
  /* specs/guild.enum.json:115:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->splash)
    free(d->splash);
  /* specs/guild.enum.json:116:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->discovery)
    free(d->discovery);
  /* specs/guild.enum.json:117:18
     '{"name":"emojis", "type":{"base":"discord::emoji::dati", "dec":"*"}}'
  */
  if (d->emojis)
    discord::emoji::dati_free(d->emojis);
  /* specs/guild.enum.json:118:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  //@todo p->(null)
  /* specs/guild.enum.json:119:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
  //p->approximate_member_count is a scalar
  /* specs/guild.enum.json:120:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
  //p->approximate_presence_count is a scalar
  /* specs/guild.enum.json:121:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  //p->description is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/guild.enum.json:112:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/guild.enum.json:113:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */

  /* specs/guild.enum.json:114:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/guild.enum.json:115:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/guild.enum.json:116:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/guild.enum.json:117:18
     '{"name":"emojis", "type":{"base":"discord::emoji::dati", "dec":"*"}}'
  */
  p->emojis = discord::emoji::dati_alloc();

  /* specs/guild.enum.json:118:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */

  /* specs/guild.enum.json:119:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */

  /* specs/guild.enum.json:120:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */

  /* specs/guild.enum.json:121:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
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

} // namespace preview

namespace widget {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.enum.json:130:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                "(enabled):b,"
  /* specs/guild.enum.json:131:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                "(channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.enum.json:130:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                &p->enabled,
  /* specs/guild.enum.json:131:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                orka_strtoull, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.enum.json:130:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
  p->__M.arg_switches[0] = &p->enabled;

  /* specs/guild.enum.json:131:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
  p->__M.arg_switches[1] = &p->channel_id;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.enum.json:130:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                "(enabled):b,"
  /* specs/guild.enum.json:131:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* specs/guild.enum.json:130:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                &p->enabled,
  /* specs/guild.enum.json:131:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                orka_ulltostr, &p->channel_id,
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
  /* specs/guild.enum.json:130:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
  //p->enabled is a scalar
  /* specs/guild.enum.json:131:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
  //p->channel_id is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/guild.enum.json:130:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */

  /* specs/guild.enum.json:131:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
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

} // namespace widget
} // namespace guild
} // namespace discord
