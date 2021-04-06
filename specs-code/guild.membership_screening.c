/* This file is generated from specs/guild.membership_screening.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/


enum discord_guild_membership_screening_field_type discord_guild_membership_screening_field_type_from_string(char *s){
  if(strcasecmp("TERMS", s) == 0) return DISCORD_GUILD_MEMBERSHIP_SCREENING_TERMS;
  abort();
}
char* discord_guild_membership_screening_field_type_to_string(enum discord_guild_membership_screening_field_type v){
  if (v == DISCORD_GUILD_MEMBERSHIP_SCREENING_TERMS) return "TERMS";

  return (void*)0;
}
bool discord_guild_membership_screening_field_type_has(enum discord_guild_membership_screening_field_type v, char *s) {
  enum discord_guild_membership_screening_field_type v1 = discord_guild_membership_screening_field_type_from_string(s);
  if (v == v1) return true;
  return false;
}

void discord_guild_membership_screening_field_from_json(char *json, size_t len, struct discord_guild_membership_screening_field *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */
                "(field_type):d,"
  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
                "(label):?s,"
  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  /* specs/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */
                "(required):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */
                &p->field_type,
  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->label,
  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  /* specs/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */
                &p->required,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_membership_screening_field_use_default_inject_settings(struct discord_guild_membership_screening_field *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */
  p->__M.arg_switches[0] = &p->field_type;

  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[1] = p->label;

  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */

  /* specs/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[3] = &p->required;

}

size_t discord_guild_membership_screening_field_to_json(char *json, size_t len, struct discord_guild_membership_screening_field *p)
{
  size_t r;
  discord_guild_membership_screening_field_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */
                "(field_type):d,"
  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
                "(label):s,"
  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  /* specs/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */
                "(required):b,"
                "@arg_switches:b",
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */
                &p->field_type,
  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
                p->label,
  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  /* specs/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */
                &p->required,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_membership_screening_field_cleanup_v(void *p) {
  discord_guild_membership_screening_field_cleanup((struct discord_guild_membership_screening_field *)p);
}

void discord_guild_membership_screening_field_init_v(void *p) {
  discord_guild_membership_screening_field_init((struct discord_guild_membership_screening_field *)p);
}

void discord_guild_membership_screening_field_free_v(void *p) {
 discord_guild_membership_screening_field_free((struct discord_guild_membership_screening_field *)p);
};

void discord_guild_membership_screening_field_from_json_v(char *json, size_t len, void *p) {
 discord_guild_membership_screening_field_from_json(json, len, (struct discord_guild_membership_screening_field*)p);
}

size_t discord_guild_membership_screening_field_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_membership_screening_field_to_json(json, len, (struct discord_guild_membership_screening_field*)p);
}

void discord_guild_membership_screening_field_list_free_v(void **p) {
  discord_guild_membership_screening_field_list_free((struct discord_guild_membership_screening_field**)p);
}

void discord_guild_membership_screening_field_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_membership_screening_field_list_from_json(str, len, (struct discord_guild_membership_screening_field ***)p);
}

size_t discord_guild_membership_screening_field_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_membership_screening_field_list_to_json(str, len, (struct discord_guild_membership_screening_field **)p);
}


void discord_guild_membership_screening_field_cleanup(struct discord_guild_membership_screening_field *d) {
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */
  //p->field_type is a scalar
  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->label)
    free(d->label);
  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */
  //@todo p->(null)
  /* specs/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */
  //p->required is a scalar
}

void discord_guild_membership_screening_field_init(struct discord_guild_membership_screening_field *p) {
  memset(p, 0, sizeof(struct discord_guild_membership_screening_field));
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type" }}'
  */

  /* specs/guild.membership_screening.json:21:20
     '{ "name": "label", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/guild.membership_screening.json:22:20
     '{ "name": "values", "todo":true, "type":{ "base":"char", "dec":"ntl" }}'
  */

  /* specs/guild.membership_screening.json:23:20
     '{ "name": "required", "type":{ "base":"bool" }}'
  */

}
struct discord_guild_membership_screening_field* discord_guild_membership_screening_field_alloc() {
  struct discord_guild_membership_screening_field *p= (struct discord_guild_membership_screening_field*)malloc(sizeof(struct discord_guild_membership_screening_field));
  discord_guild_membership_screening_field_init(p);
  return p;
}

void discord_guild_membership_screening_field_free(struct discord_guild_membership_screening_field *p) {
  discord_guild_membership_screening_field_cleanup(p);
  free(p);
}

void discord_guild_membership_screening_field_list_free(struct discord_guild_membership_screening_field **p) {
  ntl_free((void**)p, (vfvp)discord_guild_membership_screening_field_cleanup);
}

void discord_guild_membership_screening_field_list_from_json(char *str, size_t len, struct discord_guild_membership_screening_field ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_membership_screening_field);
  d.init_elem = discord_guild_membership_screening_field_init_v;
  d.elem_from_buf = discord_guild_membership_screening_field_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_membership_screening_field_list_to_json(char *str, size_t len, struct discord_guild_membership_screening_field **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_membership_screening_field_to_json_v);
}


void discord_guild_membership_screening_from_json(char *json, size_t len, struct discord_guild_membership_screening *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
                "(version):s_as_u64,"
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */
                "(fields):F,"
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                "(description):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
                &p->version,
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */
                discord_guild_membership_screening_field_list_from_json, &p->fields,
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_membership_screening_use_default_inject_settings(struct discord_guild_membership_screening *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  p->__M.arg_switches[0] = &p->version;

  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */
  p->__M.arg_switches[1] = p->fields;

  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[2] = p->description;

}

size_t discord_guild_membership_screening_to_json(char *json, size_t len, struct discord_guild_membership_screening *p)
{
  size_t r;
  discord_guild_membership_screening_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
                "(version):s_as_u64,"
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */
                "(fields):F,"
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                "(description):s,"
                "@arg_switches:b",
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
                &p->version,
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */
                discord_guild_membership_screening_field_list_to_json, p->fields,
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_membership_screening_cleanup_v(void *p) {
  discord_guild_membership_screening_cleanup((struct discord_guild_membership_screening *)p);
}

void discord_guild_membership_screening_init_v(void *p) {
  discord_guild_membership_screening_init((struct discord_guild_membership_screening *)p);
}

void discord_guild_membership_screening_free_v(void *p) {
 discord_guild_membership_screening_free((struct discord_guild_membership_screening *)p);
};

void discord_guild_membership_screening_from_json_v(char *json, size_t len, void *p) {
 discord_guild_membership_screening_from_json(json, len, (struct discord_guild_membership_screening*)p);
}

size_t discord_guild_membership_screening_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_membership_screening_to_json(json, len, (struct discord_guild_membership_screening*)p);
}

void discord_guild_membership_screening_list_free_v(void **p) {
  discord_guild_membership_screening_list_free((struct discord_guild_membership_screening**)p);
}

void discord_guild_membership_screening_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_membership_screening_list_from_json(str, len, (struct discord_guild_membership_screening ***)p);
}

size_t discord_guild_membership_screening_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_membership_screening_list_to_json(str, len, (struct discord_guild_membership_screening **)p);
}


void discord_guild_membership_screening_cleanup(struct discord_guild_membership_screening *d) {
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  //p->version is a scalar
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */
  if (d->fields)
    discord_guild_membership_screening_field_list_free(d->fields);
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->description)
    free(d->description);
}

void discord_guild_membership_screening_init(struct discord_guild_membership_screening *p) {
  memset(p, 0, sizeof(struct discord_guild_membership_screening));
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */

  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field", "dec":"ntl" }}'
  */

  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */

}
struct discord_guild_membership_screening* discord_guild_membership_screening_alloc() {
  struct discord_guild_membership_screening *p= (struct discord_guild_membership_screening*)malloc(sizeof(struct discord_guild_membership_screening));
  discord_guild_membership_screening_init(p);
  return p;
}

void discord_guild_membership_screening_free(struct discord_guild_membership_screening *p) {
  discord_guild_membership_screening_cleanup(p);
  free(p);
}

void discord_guild_membership_screening_list_free(struct discord_guild_membership_screening **p) {
  ntl_free((void**)p, (vfvp)discord_guild_membership_screening_cleanup);
}

void discord_guild_membership_screening_list_from_json(char *str, size_t len, struct discord_guild_membership_screening ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_membership_screening);
  d.init_elem = discord_guild_membership_screening_init_v;
  d.elem_from_buf = discord_guild_membership_screening_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_membership_screening_list_to_json(char *str, size_t len, struct discord_guild_membership_screening **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_membership_screening_to_json_v);
}

