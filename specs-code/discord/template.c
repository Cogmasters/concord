/* This file is generated from specs/discord/template.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/template#template-object-template-structure
*/

void discord_template_from_json(char *json, size_t len, struct discord_template *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/template.json:11:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(code):?s,"
  /* specs/discord/template.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(name):?s,"
  /* specs/discord/template.json:13:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
                "(description):?s,"
  /* specs/discord/template.json:14:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
                "(usage_count):d,"
  /* specs/discord/template.json:15:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(creator_id):F,"
  /* specs/discord/template.json:16:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
                "(creator):F,"
  /* specs/discord/template.json:17:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(created_at):F,"
  /* specs/discord/template.json:18:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(updated_at):F,"
  /* specs/discord/template.json:19:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(source_guild_id):F,"
  /* specs/discord/template.json:20:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}'
  */
                "(serialized_source_guild):F,"
  /* specs/discord/template.json:21:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
                "(is_dirty):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/template.json:11:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                &p->code,
  /* specs/discord/template.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                &p->name,
  /* specs/discord/template.json:13:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
                &p->description,
  /* specs/discord/template.json:14:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
                &p->usage_count,
  /* specs/discord/template.json:15:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->creator_id,
  /* specs/discord/template.json:16:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
                discord_user_from_json, p->creator,
  /* specs/discord/template.json:17:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_iso8601_to_unix_ms, &p->created_at,
  /* specs/discord/template.json:18:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_iso8601_to_unix_ms, &p->updated_at,
  /* specs/discord/template.json:19:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->source_guild_id,
  /* specs/discord/template.json:20:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}'
  */
                discord_guild_from_json, p->serialized_source_guild,
  /* specs/discord/template.json:21:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
                &p->is_dirty,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_template_use_default_inject_settings(struct discord_template *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/template.json:11:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[0] = p->code;

  /* specs/discord/template.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/template.json:13:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
  p->__M.arg_switches[2] = p->description;

  /* specs/discord/template.json:14:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
  p->__M.arg_switches[3] = &p->usage_count;

  /* specs/discord/template.json:15:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[4] = &p->creator_id;

  /* specs/discord/template.json:16:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
  p->__M.arg_switches[5] = p->creator;

  /* specs/discord/template.json:17:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  p->__M.arg_switches[6] = &p->created_at;

  /* specs/discord/template.json:18:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  p->__M.arg_switches[7] = &p->updated_at;

  /* specs/discord/template.json:19:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[8] = &p->source_guild_id;

  /* specs/discord/template.json:20:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}'
  */
  p->__M.arg_switches[9] = p->serialized_source_guild;

  /* specs/discord/template.json:21:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[10] = &p->is_dirty;

}

size_t discord_template_to_json(char *json, size_t len, struct discord_template *p)
{
  size_t r;
  discord_template_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/template.json:11:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(code):s,"
  /* specs/discord/template.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                "(name):s,"
  /* specs/discord/template.json:13:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
                "(description):s,"
  /* specs/discord/template.json:14:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
                "(usage_count):d,"
  /* specs/discord/template.json:15:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(creator_id):|F|,"
  /* specs/discord/template.json:16:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
                "(creator):F,"
  /* specs/discord/template.json:17:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(created_at):|F|,"
  /* specs/discord/template.json:18:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                "(updated_at):|F|,"
  /* specs/discord/template.json:19:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(source_guild_id):|F|,"
  /* specs/discord/template.json:20:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}'
  */
                "(serialized_source_guild):F,"
  /* specs/discord/template.json:21:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
                "(is_dirty):b,"
                "@arg_switches:b",
  /* specs/discord/template.json:11:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                p->code,
  /* specs/discord/template.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
                p->name,
  /* specs/discord/template.json:13:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
                p->description,
  /* specs/discord/template.json:14:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
                &p->usage_count,
  /* specs/discord/template.json:15:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->creator_id,
  /* specs/discord/template.json:16:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
                discord_user_to_json, p->creator,
  /* specs/discord/template.json:17:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_unix_ms_to_iso8601, &p->created_at,
  /* specs/discord/template.json:18:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
                orka_unix_ms_to_iso8601, &p->updated_at,
  /* specs/discord/template.json:19:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->source_guild_id,
  /* specs/discord/template.json:20:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}'
  */
                discord_guild_to_json, p->serialized_source_guild,
  /* specs/discord/template.json:21:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
                &p->is_dirty,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_template_cleanup_v(void *p) {
  discord_template_cleanup((struct discord_template *)p);
}

void discord_template_init_v(void *p) {
  discord_template_init((struct discord_template *)p);
}

void discord_template_free_v(void *p) {
 discord_template_free((struct discord_template *)p);
};

void discord_template_from_json_v(char *json, size_t len, void *p) {
 discord_template_from_json(json, len, (struct discord_template*)p);
}

size_t discord_template_to_json_v(char *json, size_t len, void *p) {
  return discord_template_to_json(json, len, (struct discord_template*)p);
}

void discord_template_list_free_v(void **p) {
  discord_template_list_free((struct discord_template**)p);
}

void discord_template_list_from_json_v(char *str, size_t len, void *p) {
  discord_template_list_from_json(str, len, (struct discord_template ***)p);
}

size_t discord_template_list_to_json_v(char *str, size_t len, void *p){
  return discord_template_list_to_json(str, len, (struct discord_template **)p);
}


void discord_template_cleanup(struct discord_template *d) {
  /* specs/discord/template.json:11:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  if (d->code)
    free(d->code);
  /* specs/discord/template.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */
  if (d->name)
    free(d->name);
  /* specs/discord/template.json:13:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */
  if (d->description)
    free(d->description);
  /* specs/discord/template.json:14:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */
  //p->usage_count is a scalar
  /* specs/discord/template.json:15:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->creator_id is a scalar
  /* specs/discord/template.json:16:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
  if (d->creator)
    discord_user_free(d->creator);
  /* specs/discord/template.json:17:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  //p->created_at is a scalar
  /* specs/discord/template.json:18:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */
  //p->updated_at is a scalar
  /* specs/discord/template.json:19:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->source_guild_id is a scalar
  /* specs/discord/template.json:20:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}'
  */
  if (d->serialized_source_guild)
    discord_guild_free(d->serialized_source_guild);
  /* specs/discord/template.json:21:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */
  //p->is_dirty is a scalar
}

void discord_template_init(struct discord_template *p) {
  memset(p, 0, sizeof(struct discord_template));
  /* specs/discord/template.json:11:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */

  /* specs/discord/template.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}'
  */

  /* specs/discord/template.json:13:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment": "@todo find fixed size limit"}'
  */

  /* specs/discord/template.json:14:20
     '{ "name": "usage_count", "type":{ "base":"int"}}'
  */

  /* specs/discord/template.json:15:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/template.json:16:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
  p->creator = discord_user_alloc();

  /* specs/discord/template.json:17:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */

  /* specs/discord/template.json:18:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}'
  */

  /* specs/discord/template.json:19:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/template.json:20:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}'
  */
  p->serialized_source_guild = discord_guild_alloc();

  /* specs/discord/template.json:21:20
     '{ "name": "is_dirty", "type":{ "base":"bool" }}'
  */

}
struct discord_template* discord_template_alloc() {
  struct discord_template *p= (struct discord_template*)malloc(sizeof(struct discord_template));
  discord_template_init(p);
  return p;
}

void discord_template_free(struct discord_template *p) {
  discord_template_cleanup(p);
  free(p);
}

void discord_template_list_free(struct discord_template **p) {
  ntl_free((void**)p, (vfvp)discord_template_cleanup);
}

void discord_template_list_from_json(char *str, size_t len, struct discord_template ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_template);
  d.init_elem = discord_template_init_v;
  d.elem_from_buf = discord_template_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_template_list_to_json(char *str, size_t len, struct discord_template **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_template_to_json_v);
}

