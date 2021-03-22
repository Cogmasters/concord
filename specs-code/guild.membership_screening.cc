/* This file is generated from specs/guild.membership_screening.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/
namespace discord {
namespace guild {
namespace membership_screening {

namespace field {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"discord::guild::membership_screening::field_type::code" }}'
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
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"discord::guild::membership_screening::field_type::code" }}'
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

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"discord::guild::membership_screening::field_type::code" }}'
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

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"discord::guild::membership_screening::field_type::code" }}'
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
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"discord::guild::membership_screening::field_type::code" }}'
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
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"discord::guild::membership_screening::field_type::code" }}'
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

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/guild.membership_screening.json:20:20
     '{ "name": "field_type", "type":{ "base":"int", "int_alias":"discord::guild::membership_screening::field_type::code" }}'
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

} // namespace field

void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
                "(version):s_as_u64,"
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
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
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
  */
                discord::guild::membership_screening::field::dati_list_from_json, &p->fields,
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  p->__M.arg_switches[0] = &p->version;

  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
  */
  p->__M.arg_switches[1] = p->fields;

  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[2] = p->description;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
                "(version):s_as_u64,"
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
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
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
  */
                discord::guild::membership_screening::field::dati_list_to_json, p->fields,
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
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */
  //p->version is a scalar
  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
  */
  if (d->fields)
    discord::guild::membership_screening::field::dati_list_free(d->fields);
  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->description)
    free(d->description);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/guild.membership_screening.json:30:20
     '{ "name": "version", "type":{ "base":"s_as_u64" }}'
  */

  /* specs/guild.membership_screening.json:31:20
     '{ "name": "fields", "type":{ "base":"discord::guild::membership_screening::field::dati", "dec":"ntl" }}'
  */

  /* specs/guild.membership_screening.json:32:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}'
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

} // namespace membership_screening
} // namespace guild
} // namespace discord
