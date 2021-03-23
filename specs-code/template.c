/* This file is generated from specs/template.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/template#template-object-template-structure
*/

void discord_Template_dati_from_json(char *json, size_t len, struct discord_Template_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(code):?s,"
  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(name):?s,"
  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
                "(description):?s,"
  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
                "(usage_count):d,"
  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(creator_id):F,"
  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
                "(creator):F,"
  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(created_at):F,"
  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(updated_at):F,"
  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(source_guild_id):F,"
  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"discord::guild::dati", "dec":"*" }}'
  */
                "(serialized_source_guild):F,"
  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
                "(is_dirty):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                &p->code,
  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                &p->name,
  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
                &p->description,
  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
                &p->usage_count,
  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->creator_id,
  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
                discord_user_dati_from_json, p->creator,
  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_iso8601_to_unix_ms, &p->created_at,
  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_iso8601_to_unix_ms, &p->updated_at,
  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->source_guild_id,
  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"discord::guild::dati", "dec":"*" }}'
  */
                discord_guild_dati_from_json, p->serialized_source_guild,
  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
                &p->is_dirty,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_Template_dati_use_default_inject_settings(struct discord_Template_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[0] = p->code;

  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
  p->__M.arg_switches[2] = p->description;

  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
  p->__M.arg_switches[3] = &p->usage_count;

  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[4] = &p->creator_id;

  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  p->__M.arg_switches[5] = p->creator;

  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  p->__M.arg_switches[6] = &p->created_at;

  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  p->__M.arg_switches[7] = &p->updated_at;

  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[8] = &p->source_guild_id;

  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"discord::guild::dati", "dec":"*" }}'
  */
  p->__M.arg_switches[9] = p->serialized_source_guild;

  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[10] = &p->is_dirty;

}

size_t discord_Template_dati_to_json(char *json, size_t len, struct discord_Template_dati *p)
{
  size_t r;
  discord_Template_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(code):s,"
  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(name):s,"
  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
                "(description):s,"
  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
                "(usage_count):d,"
  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(creator_id):|F|,"
  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
                "(creator):F,"
  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(created_at):|F|,"
  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(updated_at):|F|,"
  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(source_guild_id):|F|,"
  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"discord::guild::dati", "dec":"*" }}'
  */
                "(serialized_source_guild):F,"
  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
                "(is_dirty):b,"
                "@arg_switches:b",
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                p->code,
  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                p->name,
  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
                p->description,
  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
                &p->usage_count,
  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->creator_id,
  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
                discord_user_dati_to_json, p->creator,
  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_unix_ms_to_iso8601, &p->created_at,
  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_unix_ms_to_iso8601, &p->updated_at,
  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->source_guild_id,
  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"discord::guild::dati", "dec":"*" }}'
  */
                discord_guild_dati_to_json, p->serialized_source_guild,
  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
                &p->is_dirty,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_Template_dati_cleanup_v(void *p) {
  discord_Template_dati_cleanup((struct discord_Template_dati *)p);
}

void discord_Template_dati_init_v(void *p) {
  discord_Template_dati_init((struct discord_Template_dati *)p);
}

void discord_Template_dati_free_v(void *p) {
 discord_Template_dati_free((struct discord_Template_dati *)p);
};

void discord_Template_dati_from_json_v(char *json, size_t len, void *p) {
 discord_Template_dati_from_json(json, len, (struct discord_Template_dati*)p);
}

size_t discord_Template_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_Template_dati_to_json(json, len, (struct discord_Template_dati*)p);
}

void discord_Template_dati_list_free_v(void **p) {
  discord_Template_dati_list_free((struct discord_Template_dati**)p);
}

void discord_Template_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_Template_dati_list_from_json(str, len, (struct discord_Template_dati ***)p);
}

size_t discord_Template_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_Template_dati_list_to_json(str, len, (struct discord_Template_dati **)p);
}


void discord_Template_dati_cleanup(struct discord_Template_dati *d) {
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  if (d->code)
    free(d->code);
  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  if (d->name)
    free(d->name);
  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
  if (d->description)
    free(d->description);
  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
  //p->usage_count is a scalar
  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->creator_id is a scalar
  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  if (d->creator)
    discord_user_dati_free(d->creator);
  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  //p->created_at is a scalar
  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  //p->updated_at is a scalar
  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->source_guild_id is a scalar
  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"discord::guild::dati", "dec":"*" }}'
  */
  if (d->serialized_source_guild)
    discord_guild_dati_free(d->serialized_source_guild);
  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
  //p->is_dirty is a scalar
}

void discord_Template_dati_init(struct discord_Template_dati *p) {
  memset(p, 0, sizeof(struct discord_Template_dati));
  /* specs/template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */

  /* specs/template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */

  /* specs/template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */

  /* specs/template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */

  /* specs/template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/template.json:17:20
     '{ "name": "creator", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  p->creator = discord_user_dati_alloc();

  /* specs/template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */

  /* specs/template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */

  /* specs/template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"discord::guild::dati", "dec":"*" }}'
  */
  p->serialized_source_guild = discord_guild_dati_alloc();

  /* specs/template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */

}
struct discord_Template_dati* discord_Template_dati_alloc() {
  struct discord_Template_dati *p= (struct discord_Template_dati*)malloc(sizeof(struct discord_Template_dati));
  discord_Template_dati_init(p);
  return p;
}

void discord_Template_dati_free(struct discord_Template_dati *p) {
  discord_Template_dati_cleanup(p);
  free(p);
}

void discord_Template_dati_list_free(struct discord_Template_dati **p) {
  ntl_free((void**)p, (vfvp)discord_Template_dati_cleanup);
}

void discord_Template_dati_list_from_json(char *str, size_t len, struct discord_Template_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_Template_dati);
  d.init_elem = discord_Template_dati_init_v;
  d.elem_from_buf = discord_Template_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_Template_dati_list_to_json(char *str, size_t len, struct discord_Template_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_Template_dati_to_json_v);
}

