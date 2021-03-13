/* This file is generated from specs/invite.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/invite#invite-object
*/
namespace discord {
namespace invite {

void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(code):?s,"
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"discord::guild::dati", "dec":"*"}, "comment":"partial guild object"}'
  */
                "(guild):F,"
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"discord::channel::dati", "dec":"*"}, "comment":"partial channel object"}'
  */
                "(channel):F,"
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"discord::user::dati", "dec":"*"}}'
  */
                "(inviter):F,"
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
                "(target_user):F,"
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"discord::invite::target_user_types::code" }}'
  */
                "(target_user_type):d,"
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
                "(approximate_presence_count):d,"
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
                "(approximate_member_count):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->code,
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"discord::guild::dati", "dec":"*"}, "comment":"partial guild object"}'
  */
                discord::guild::dati_from_json, p->guild,
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"discord::channel::dati", "dec":"*"}, "comment":"partial channel object"}'
  */
                discord::channel::dati_from_json, p->channel,
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"discord::user::dati", "dec":"*"}}'
  */
                discord::user::dati_from_json, p->inviter,
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
                discord::user::dati_from_json, p->target_user,
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"discord::invite::target_user_types::code" }}'
  */
                &p->target_user_type,
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
                &p->approximate_presence_count,
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
                &p->approximate_member_count,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(code):s,"
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"discord::guild::dati", "dec":"*"}, "comment":"partial guild object"}'
  */
                "(guild):F,"
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"discord::channel::dati", "dec":"*"}, "comment":"partial channel object"}'
  */
                "(channel):F,"
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"discord::user::dati", "dec":"*"}}'
  */
                "(inviter):F,"
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
                "(target_user):F,"
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"discord::invite::target_user_types::code" }}'
  */
                "(target_user_type):d,"
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
                "(approximate_presence_count):d,"
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
                "(approximate_member_count):d,"
                "@arg_switches:b",
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->code,
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"discord::guild::dati", "dec":"*"}, "comment":"partial guild object"}'
  */
                discord::guild::dati_to_json, p->guild,
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"discord::channel::dati", "dec":"*"}, "comment":"partial channel object"}'
  */
                discord::channel::dati_to_json, p->channel,
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"discord::user::dati", "dec":"*"}}'
  */
                discord::user::dati_to_json, p->inviter,
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
                discord::user::dati_to_json, p->target_user,
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"discord::invite::target_user_types::code" }}'
  */
                &p->target_user_type,
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
                &p->approximate_presence_count,
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
                &p->approximate_member_count,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[0] = p->code;

  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"discord::guild::dati", "dec":"*"}, "comment":"partial guild object"}'
  */
  p->__M.arg_switches[1] = p->guild;

  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"discord::channel::dati", "dec":"*"}, "comment":"partial channel object"}'
  */
  p->__M.arg_switches[2] = p->channel;

  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"discord::user::dati", "dec":"*"}}'
  */
  p->__M.arg_switches[3] = p->inviter;

  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  p->__M.arg_switches[4] = p->target_user;

  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"discord::invite::target_user_types::code" }}'
  */
  p->__M.arg_switches[5] = &p->target_user_type;

  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[6] = &p->approximate_presence_count;

  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[7] = &p->approximate_member_count;

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
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->code)
    free(d->code);
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"discord::guild::dati", "dec":"*"}, "comment":"partial guild object"}'
  */
  if (d->guild)
    discord::guild::dati_free(d->guild);
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"discord::channel::dati", "dec":"*"}, "comment":"partial channel object"}'
  */
  if (d->channel)
    discord::channel::dati_free(d->channel);
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"discord::user::dati", "dec":"*"}}'
  */
  if (d->inviter)
    discord::user::dati_free(d->inviter);
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  if (d->target_user)
    discord::user::dati_free(d->target_user);
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"discord::invite::target_user_types::code" }}'
  */
  //p->target_user_type is a scalar
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
  //p->approximate_presence_count is a scalar
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
  //p->approximate_member_count is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"discord::guild::dati", "dec":"*"}, "comment":"partial guild object"}'
  */
  p->guild = discord::guild::dati_alloc();

  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"discord::channel::dati", "dec":"*"}, "comment":"partial channel object"}'
  */
  p->channel = discord::channel::dati_alloc();

  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"discord::user::dati", "dec":"*"}}'
  */
  p->inviter = discord::user::dati_alloc();

  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"discord::user::dati", "dec":"*"}, "comment":"partial user object"}'
  */
  p->target_user = discord::user::dati_alloc();

  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"discord::invite::target_user_types::code" }}'
  */

  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
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


namespace metadata {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
                "(user):d,"
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
                "(max_uses):d,"
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
                "(max_age):d,"
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
                "(temporary):d,"
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                "(created_at):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
                &p->user,
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
                &p->max_uses,
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
                &p->max_age,
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
                &p->temporary,
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                orka_iso8601_to_unix_ms, &p->created_at,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
                "(user):d,"
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
                "(max_uses):d,"
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
                "(max_age):d,"
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
                "(temporary):d,"
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                "(created_at):|F|,"
                "@arg_switches:b",
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
                &p->user,
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
                &p->max_uses,
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
                &p->max_age,
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
                &p->temporary,
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                orka_unix_ms_to_iso8601, &p->created_at,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[0] = &p->user;

  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[1] = &p->max_uses;

  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->max_age;

  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[3] = &p->temporary;

  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  p->__M.arg_switches[4] = &p->created_at;

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
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
  //p->user is a scalar
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
  //p->max_uses is a scalar
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
  //p->max_age is a scalar
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
  //p->temporary is a scalar
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  //p->created_at is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
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

} // namespace metadata
} // namespace invite
} // namespace discord
