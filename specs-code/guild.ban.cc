/* This file is generated from specs/guild.ban.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/
namespace discord {
namespace guild {

namespace ban {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                "(reason):s,"
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
                "(user):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                p->reason,
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
                discord::user::dati_from_json, p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  p->__M.arg_switches[0] = p->reason;

  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  p->__M.arg_switches[1] = p->user;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                "(reason):s,"
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
                "(user):F,"
                "@arg_switches:b",
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
                p->reason,
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
                discord::user::dati_to_json, p->user,
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
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */
  //p->reason is a scalar
  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  if (d->user)
    discord::user::dati_free(d->user);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/guild.ban.json:12:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"[MAX_REASON_LEN]" }}'
  */

  /* specs/guild.ban.json:13:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  p->user = discord::user::dati_alloc();

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

} // namespace ban
} // namespace guild
} // namespace discord
