/* This file is generated from specs/guild.membership_screening.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/

void discord_guild_membership_screening_field_dati_from_json(char *json, size_t len, struct discord_guild_membership_screening_field_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type_code" }}'
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
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type_code" }}'
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

static void discord_guild_membership_screening_field_dati_use_default_inject_settings(struct discord_guild_membership_screening_field_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type_code" }}'
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

size_t discord_guild_membership_screening_field_dati_to_json(char *json, size_t len, struct discord_guild_membership_screening_field_dati *p)
{
  size_t r;
  discord_guild_membership_screening_field_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type_code" }}'
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
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type_code" }}'
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
void discord_guild_membership_screening_field_dati_cleanup_v(void *p) {
  discord_guild_membership_screening_field_dati_cleanup((struct discord_guild_membership_screening_field_dati *)p);
}

void discord_guild_membership_screening_field_dati_init_v(void *p) {
  discord_guild_membership_screening_field_dati_init((struct discord_guild_membership_screening_field_dati *)p);
}

void discord_guild_membership_screening_field_dati_free_v(void *p) {
 discord_guild_membership_screening_field_dati_free((struct discord_guild_membership_screening_field_dati *)p);
};

void discord_guild_membership_screening_field_dati_from_json_v(char *json, size_t len, void *p) {
 discord_guild_membership_screening_field_dati_from_json(json, len, (struct discord_guild_membership_screening_field_dati*)p);
}

size_t discord_guild_membership_screening_field_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_membership_screening_field_dati_to_json(json, len, (struct discord_guild_membership_screening_field_dati*)p);
}

void discord_guild_membership_screening_field_dati_list_free_v(void **p) {
  discord_guild_membership_screening_field_dati_list_free((struct discord_guild_membership_screening_field_dati**)p);
}

void discord_guild_membership_screening_field_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_membership_screening_field_dati_list_from_json(str, len, (struct discord_guild_membership_screening_field_dati ***)p);
}

size_t discord_guild_membership_screening_field_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_membership_screening_field_dati_list_to_json(str, len, (struct discord_guild_membership_screening_field_dati **)p);
}


void discord_guild_membership_screening_field_dati_cleanup(struct discord_guild_membership_screening_field_dati *d) {
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type_code" }}'
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

void discord_guild_membership_screening_field_dati_init(struct discord_guild_membership_screening_field_dati *p) {
  memset(p, 0, sizeof(struct discord_guild_membership_screening_field_dati));
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"enum discord_guild_membership_screening_field_type_code" }}'
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
struct discord_guild_membership_screening_field_dati* discord_guild_membership_screening_field_dati_alloc() {
  struct discord_guild_membership_screening_field_dati *p= (struct discord_guild_membership_screening_field_dati*)malloc(sizeof(struct discord_guild_membership_screening_field_dati));
  discord_guild_membership_screening_field_dati_init(p);
  return p;
}

void discord_guild_membership_screening_field_dati_free(struct discord_guild_membership_screening_field_dati *p) {
  discord_guild_membership_screening_field_dati_cleanup(p);
  free(p);
}

void discord_guild_membership_screening_field_dati_list_free(struct discord_guild_membership_screening_field_dati **p) {
  ntl_free((void**)p, (vfvp)discord_guild_membership_screening_field_dati_cleanup);
}

void discord_guild_membership_screening_field_dati_list_from_json(char *str, size_t len, struct discord_guild_membership_screening_field_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_membership_screening_field_dati);
  d.init_elem = discord_guild_membership_screening_field_dati_init_v;
  d.elem_from_buf = discord_guild_membership_screening_field_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_membership_screening_field_dati_list_to_json(char *str, size_t len, struct discord_guild_membership_screening_field_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_membership_screening_field_dati_to_json_v);
}


void discord_guild_membership_screening_dati_from_json(char *json, size_t len, struct discord_guild_membership_screening_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
                "(version):s_as_u64,"
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field_dati", "dec":"ntl" }}'
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
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field_dati", "dec":"ntl" }}'
  */
                struct discord_guild_membership_screening_field_dati_list_from_json, &p->fields,
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_membership_screening_dati_use_default_inject_settings(struct discord_guild_membership_screening_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  p->__M.arg_switches[0] = &p->version;

  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field_dati", "dec":"ntl" }}'
  */
  p->__M.arg_switches[1] = p->fields;

  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[2] = p->description;

}

size_t discord_guild_membership_screening_dati_to_json(char *json, size_t len, struct discord_guild_membership_screening_dati *p)
{
  size_t r;
  discord_guild_membership_screening_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
                "(version):s_as_u64,"
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field_dati", "dec":"ntl" }}'
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
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field_dati", "dec":"ntl" }}'
  */
                struct discord_guild_membership_screening_field_dati_list_to_json, p->fields,
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
void discord_guild_membership_screening_dati_cleanup_v(void *p) {
  discord_guild_membership_screening_dati_cleanup((struct discord_guild_membership_screening_dati *)p);
}

void discord_guild_membership_screening_dati_init_v(void *p) {
  discord_guild_membership_screening_dati_init((struct discord_guild_membership_screening_dati *)p);
}

void discord_guild_membership_screening_dati_free_v(void *p) {
 discord_guild_membership_screening_dati_free((struct discord_guild_membership_screening_dati *)p);
};

void discord_guild_membership_screening_dati_from_json_v(char *json, size_t len, void *p) {
 discord_guild_membership_screening_dati_from_json(json, len, (struct discord_guild_membership_screening_dati*)p);
}

size_t discord_guild_membership_screening_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_membership_screening_dati_to_json(json, len, (struct discord_guild_membership_screening_dati*)p);
}

void discord_guild_membership_screening_dati_list_free_v(void **p) {
  discord_guild_membership_screening_dati_list_free((struct discord_guild_membership_screening_dati**)p);
}

void discord_guild_membership_screening_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_membership_screening_dati_list_from_json(str, len, (struct discord_guild_membership_screening_dati ***)p);
}

size_t discord_guild_membership_screening_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_membership_screening_dati_list_to_json(str, len, (struct discord_guild_membership_screening_dati **)p);
}


void discord_guild_membership_screening_dati_cleanup(struct discord_guild_membership_screening_dati *d) {
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  //p->version is a scalar
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field_dati", "dec":"ntl" }}'
  */
  if (d->fields)
    struct discord_guild_membership_screening_field_dati_list_free(d->fields);
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->description)
    free(d->description);
}

void discord_guild_membership_screening_dati_init(struct discord_guild_membership_screening_dati *p) {
  memset(p, 0, sizeof(struct discord_guild_membership_screening_dati));
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */

  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"struct discord_guild_membership_screening_field_dati", "dec":"ntl" }}'
  */

  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */

}
struct discord_guild_membership_screening_dati* discord_guild_membership_screening_dati_alloc() {
  struct discord_guild_membership_screening_dati *p= (struct discord_guild_membership_screening_dati*)malloc(sizeof(struct discord_guild_membership_screening_dati));
  discord_guild_membership_screening_dati_init(p);
  return p;
}

void discord_guild_membership_screening_dati_free(struct discord_guild_membership_screening_dati *p) {
  discord_guild_membership_screening_dati_cleanup(p);
  free(p);
}

void discord_guild_membership_screening_dati_list_free(struct discord_guild_membership_screening_dati **p) {
  ntl_free((void**)p, (vfvp)discord_guild_membership_screening_dati_cleanup);
}

void discord_guild_membership_screening_dati_list_from_json(char *str, size_t len, struct discord_guild_membership_screening_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_membership_screening_dati);
  d.init_elem = discord_guild_membership_screening_dati_init_v;
  d.elem_from_buf = discord_guild_membership_screening_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_membership_screening_dati_list_to_json(char *str, size_t len, struct discord_guild_membership_screening_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_membership_screening_dati_to_json_v);
}

