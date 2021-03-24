/* This file is generated from specs/guild.enum.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/

void discord_guild_unavailable_from_json(char *json, size_t len, struct discord_guild_unavailable *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                "(unavailable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                &p->unavailable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_unavailable_use_default_inject_settings(struct discord_guild_unavailable *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
  p->__M.arg_switches[1] = &p->unavailable;

}

size_t discord_guild_unavailable_to_json(char *json, size_t len, struct discord_guild_unavailable *p)
{
  size_t r;
  discord_guild_unavailable_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                "(unavailable):b,"
                "@arg_switches:b",
  /* specs/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
                &p->unavailable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_unavailable_cleanup_v(void *p) {
  discord_guild_unavailable_cleanup((struct discord_guild_unavailable *)p);
}

void discord_guild_unavailable_init_v(void *p) {
  discord_guild_unavailable_init((struct discord_guild_unavailable *)p);
}

void discord_guild_unavailable_free_v(void *p) {
 discord_guild_unavailable_free((struct discord_guild_unavailable *)p);
};

void discord_guild_unavailable_from_json_v(char *json, size_t len, void *p) {
 discord_guild_unavailable_from_json(json, len, (struct discord_guild_unavailable*)p);
}

size_t discord_guild_unavailable_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_unavailable_to_json(json, len, (struct discord_guild_unavailable*)p);
}

void discord_guild_unavailable_list_free_v(void **p) {
  discord_guild_unavailable_list_free((struct discord_guild_unavailable**)p);
}

void discord_guild_unavailable_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_unavailable_list_from_json(str, len, (struct discord_guild_unavailable ***)p);
}

size_t discord_guild_unavailable_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_unavailable_list_to_json(str, len, (struct discord_guild_unavailable **)p);
}


void discord_guild_unavailable_cleanup(struct discord_guild_unavailable *d) {
  /* specs/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */
  //p->unavailable is a scalar
}

void discord_guild_unavailable_init(struct discord_guild_unavailable *p) {
  memset(p, 0, sizeof(struct discord_guild_unavailable));
  /* specs/guild.enum.json:93:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/guild.enum.json:94:18
     '{"name":"unavailable", "type":{"base":"bool"}}'
  */

}
struct discord_guild_unavailable* discord_guild_unavailable_alloc() {
  struct discord_guild_unavailable *p= (struct discord_guild_unavailable*)malloc(sizeof(struct discord_guild_unavailable));
  discord_guild_unavailable_init(p);
  return p;
}

void discord_guild_unavailable_free(struct discord_guild_unavailable *p) {
  discord_guild_unavailable_cleanup(p);
  free(p);
}

void discord_guild_unavailable_list_free(struct discord_guild_unavailable **p) {
  ntl_free((void**)p, (vfvp)discord_guild_unavailable_cleanup);
}

void discord_guild_unavailable_list_from_json(char *str, size_t len, struct discord_guild_unavailable ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_unavailable);
  d.init_elem = discord_guild_unavailable_init_v;
  d.elem_from_buf = discord_guild_unavailable_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_unavailable_list_to_json(char *str, size_t len, struct discord_guild_unavailable **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_unavailable_to_json_v);
}


void discord_guild_preview_from_json(char *json, size_t len, struct discord_guild_preview *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(icon):?s,"
  /* specs/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(splash):?s,"
  /* specs/guild.enum.json:106:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(discovery):?s,"
  /* specs/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
                "(emojis):F,"
  /* specs/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                "(approximate_member_count):d,"
  /* specs/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                "(approximate_presence_count):d,"
  /* specs/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                "(description):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->icon,
  /* specs/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->splash,
  /* specs/guild.enum.json:106:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                &p->discovery,
  /* specs/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
                discord_emoji_list_from_json, &p->emojis,
  /* specs/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                &p->approximate_member_count,
  /* specs/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                &p->approximate_presence_count,
  /* specs/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_preview_use_default_inject_settings(struct discord_guild_preview *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[2] = p->icon;

  /* specs/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[3] = p->splash;

  /* specs/guild.enum.json:106:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  p->__M.arg_switches[4] = p->discovery;

  /* specs/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
  p->__M.arg_switches[5] = p->emojis;

  /* specs/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */

  /* specs/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
  p->__M.arg_switches[7] = &p->approximate_member_count;

  /* specs/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
  p->__M.arg_switches[8] = &p->approximate_presence_count;

  /* specs/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  p->__M.arg_switches[9] = p->description;

}

size_t discord_guild_preview_to_json(char *json, size_t len, struct discord_guild_preview *p)
{
  size_t r;
  discord_guild_preview_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(icon):s,"
  /* specs/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(splash):s,"
  /* specs/guild.enum.json:106:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                "(discovery):s,"
  /* specs/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
                "(emojis):F,"
  /* specs/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                "(approximate_member_count):d,"
  /* specs/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                "(approximate_presence_count):d,"
  /* specs/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                "(description):s,"
                "@arg_switches:b",
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->icon,
  /* specs/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->splash,
  /* specs/guild.enum.json:106:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
                p->discovery,
  /* specs/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
                discord_emoji_list_to_json, p->emojis,
  /* specs/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  /* specs/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
                &p->approximate_member_count,
  /* specs/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
                &p->approximate_presence_count,
  /* specs/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_preview_cleanup_v(void *p) {
  discord_guild_preview_cleanup((struct discord_guild_preview *)p);
}

void discord_guild_preview_init_v(void *p) {
  discord_guild_preview_init((struct discord_guild_preview *)p);
}

void discord_guild_preview_free_v(void *p) {
 discord_guild_preview_free((struct discord_guild_preview *)p);
};

void discord_guild_preview_from_json_v(char *json, size_t len, void *p) {
 discord_guild_preview_from_json(json, len, (struct discord_guild_preview*)p);
}

size_t discord_guild_preview_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_preview_to_json(json, len, (struct discord_guild_preview*)p);
}

void discord_guild_preview_list_free_v(void **p) {
  discord_guild_preview_list_free((struct discord_guild_preview**)p);
}

void discord_guild_preview_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_preview_list_from_json(str, len, (struct discord_guild_preview ***)p);
}

size_t discord_guild_preview_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_preview_list_to_json(str, len, (struct discord_guild_preview **)p);
}


void discord_guild_preview_cleanup(struct discord_guild_preview *d) {
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  //p->name is a scalar
  /* specs/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->icon)
    free(d->icon);
  /* specs/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->splash)
    free(d->splash);
  /* specs/guild.enum.json:106:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */
  if (d->discovery)
    free(d->discovery);
  /* specs/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */
  if (d->emojis)
    discord_emoji_list_free(d->emojis);
  /* specs/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */
  //@todo p->(null)
  /* specs/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */
  //p->approximate_member_count is a scalar
  /* specs/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */
  //p->approximate_presence_count is a scalar
  /* specs/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */
  //p->description is a scalar
}

void discord_guild_preview_init(struct discord_guild_preview *p) {
  memset(p, 0, sizeof(struct discord_guild_preview));
  /* specs/guild.enum.json:102:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/guild.enum.json:103:18
     '{"name":"name", "type":{"base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */

  /* specs/guild.enum.json:104:18
     '{"name":"icon", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/guild.enum.json:105:18
     '{"name":"splash", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/guild.enum.json:106:18
     '{"name":"discovery", "type":{"base":"char", "dec":"*", "nullable":true}}'
  */

  /* specs/guild.enum.json:107:18
     '{"name":"emojis", "type":{"base":"struct discord_emoji", "dec":"ntl"}}'
  */

  /* specs/guild.enum.json:108:18
     '{"name":"features", "todo":true, "type":{"base":"char", "dec":"ntl"}}'
  */

  /* specs/guild.enum.json:109:18
     '{"name":"approximate_member_count", "type":{"base":"int"}}'
  */

  /* specs/guild.enum.json:110:18
     '{"name":"approximate_presence_count", "type":{"base":"int"}}'
  */

  /* specs/guild.enum.json:111:18
     '{"name":"description", "type":{"base":"char", "dec":"[MAX_DESCRIPTION_LEN]"}}'
  */

}
struct discord_guild_preview* discord_guild_preview_alloc() {
  struct discord_guild_preview *p= (struct discord_guild_preview*)malloc(sizeof(struct discord_guild_preview));
  discord_guild_preview_init(p);
  return p;
}

void discord_guild_preview_free(struct discord_guild_preview *p) {
  discord_guild_preview_cleanup(p);
  free(p);
}

void discord_guild_preview_list_free(struct discord_guild_preview **p) {
  ntl_free((void**)p, (vfvp)discord_guild_preview_cleanup);
}

void discord_guild_preview_list_from_json(char *str, size_t len, struct discord_guild_preview ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_preview);
  d.init_elem = discord_guild_preview_init_v;
  d.elem_from_buf = discord_guild_preview_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_preview_list_to_json(char *str, size_t len, struct discord_guild_preview **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_preview_to_json_v);
}


void discord_guild_widget_from_json(char *json, size_t len, struct discord_guild_widget *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                "(enabled):b,"
  /* specs/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                "(channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                &p->enabled,
  /* specs/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                orka_strtoull, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_widget_use_default_inject_settings(struct discord_guild_widget *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
  p->__M.arg_switches[0] = &p->enabled;

  /* specs/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
  p->__M.arg_switches[1] = &p->channel_id;

}

size_t discord_guild_widget_to_json(char *json, size_t len, struct discord_guild_widget *p)
{
  size_t r;
  discord_guild_widget_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                "(enabled):b,"
  /* specs/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* specs/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
                &p->enabled,
  /* specs/guild.enum.json:120:18
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
void discord_guild_widget_cleanup_v(void *p) {
  discord_guild_widget_cleanup((struct discord_guild_widget *)p);
}

void discord_guild_widget_init_v(void *p) {
  discord_guild_widget_init((struct discord_guild_widget *)p);
}

void discord_guild_widget_free_v(void *p) {
 discord_guild_widget_free((struct discord_guild_widget *)p);
};

void discord_guild_widget_from_json_v(char *json, size_t len, void *p) {
 discord_guild_widget_from_json(json, len, (struct discord_guild_widget*)p);
}

size_t discord_guild_widget_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_widget_to_json(json, len, (struct discord_guild_widget*)p);
}

void discord_guild_widget_list_free_v(void **p) {
  discord_guild_widget_list_free((struct discord_guild_widget**)p);
}

void discord_guild_widget_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_widget_list_from_json(str, len, (struct discord_guild_widget ***)p);
}

size_t discord_guild_widget_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_widget_list_to_json(str, len, (struct discord_guild_widget **)p);
}


void discord_guild_widget_cleanup(struct discord_guild_widget *d) {
  /* specs/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */
  //p->enabled is a scalar
  /* specs/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */
  //p->channel_id is a scalar
}

void discord_guild_widget_init(struct discord_guild_widget *p) {
  memset(p, 0, sizeof(struct discord_guild_widget));
  /* specs/guild.enum.json:119:18
     '{"name":"enabled", "type":{"base":"bool"}}'
  */

  /* specs/guild.enum.json:120:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake", 
         "nullable":true}}'
  */

}
struct discord_guild_widget* discord_guild_widget_alloc() {
  struct discord_guild_widget *p= (struct discord_guild_widget*)malloc(sizeof(struct discord_guild_widget));
  discord_guild_widget_init(p);
  return p;
}

void discord_guild_widget_free(struct discord_guild_widget *p) {
  discord_guild_widget_cleanup(p);
  free(p);
}

void discord_guild_widget_list_free(struct discord_guild_widget **p) {
  ntl_free((void**)p, (vfvp)discord_guild_widget_cleanup);
}

void discord_guild_widget_list_from_json(char *str, size_t len, struct discord_guild_widget ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_widget);
  d.init_elem = discord_guild_widget_init_v;
  d.elem_from_buf = discord_guild_widget_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_widget_list_to_json(char *str, size_t len, struct discord_guild_widget **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_widget_to_json_v);
}

