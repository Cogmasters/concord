/* This file is generated from specs/voice.json, Please don't edit it. */
#include "specs.h"
/*
(null)
*/
namespace discord {

namespace voice {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):F,"
  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(channel_id):F,"
  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(user_id):F,"
  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"discord::guild::member::dati", "dec":"*" }}'
  */
                "(member):F,"
  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
                "(session_id):?s,"
  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
                "(deaf):b,"
  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
                "(mute):b,"
  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
                "(self_deaf):b,"
  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
                "(self_mute):b,"
  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
                "(self_stream):b,"
  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
                "(self_video):b,"
  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
  */
                "(supress):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->guild_id,
  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->channel_id,
  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->user_id,
  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"discord::guild::member::dati", "dec":"*" }}'
  */
                discord::guild::member::dati_from_json, p->member,
  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->session_id,
  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
                &p->deaf,
  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
                &p->mute,
  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
                &p->self_deaf,
  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
                &p->self_mute,
  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
                &p->self_stream,
  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
                &p->self_video,
  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
  */
                &p->supress,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):|F|,"
  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(channel_id):|F|,"
  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(user_id):|F|,"
  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"discord::guild::member::dati", "dec":"*" }}'
  */
                "(member):F,"
  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
                "(session_id):s,"
  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
                "(deaf):b,"
  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
                "(mute):b,"
  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
                "(self_deaf):b,"
  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
                "(self_mute):b,"
  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
                "(self_stream):b,"
  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
                "(self_video):b,"
  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
  */
                "(supress):b,"
                "@arg_switches:b",
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->user_id,
  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"discord::guild::member::dati", "dec":"*" }}'
  */
                discord::guild::member::dati_to_json, p->member,
  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
                p->session_id,
  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
                &p->deaf,
  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
                &p->mute,
  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
                &p->self_deaf,
  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
                &p->self_mute,
  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
                &p->self_stream,
  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
                &p->self_video,
  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
  */
                &p->supress,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->guild_id;

  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[1] = &p->channel_id;

  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[2] = &p->user_id;

  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"discord::guild::member::dati", "dec":"*" }}'
  */
  p->__M.arg_switches[3] = p->member;

  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[4] = p->session_id;

  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[5] = &p->deaf;

  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[6] = &p->mute;

  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[7] = &p->self_deaf;

  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[8] = &p->self_mute;

  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[9] = &p->self_stream;

  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[10] = &p->self_video;

  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[11] = &p->supress;

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
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->guild_id is a scalar
  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->channel_id is a scalar
  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->user_id is a scalar
  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"discord::guild::member::dati", "dec":"*" }}'
  */
  if (d->member)
    discord::guild::member::dati_free(d->member);
  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->session_id)
    free(d->session_id);
  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */
  //p->deaf is a scalar
  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */
  //p->mute is a scalar
  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */
  //p->self_deaf is a scalar
  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */
  //p->self_mute is a scalar
  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */
  //p->self_stream is a scalar
  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */
  //p->self_video is a scalar
  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
  */
  //p->supress is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/voice.json:12:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/voice.json:13:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/voice.json:14:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/voice.json:15:20
     '{ "name": "member", "type":{ "base":"discord::guild::member::dati", "dec":"*" }}'
  */
  p->member = discord::guild::member::dati_alloc();

  /* specs/voice.json:16:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/voice.json:17:20
     '{ "name": "deaf", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:18:20
     '{ "name": "mute", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:19:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:20:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:21:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:22:20
     '{ "name": "self_video", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:23:20
     '{ "name": "supress", "type":{ "base":"bool" }}'
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

} // namespace voice

namespace voice {
namespace region {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
                "(id):?s,"
  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
                "(name):?s,"
  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
                "(vip):b,"
  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
                "(optimal):b,"
  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
                "(deprecated):b,"
  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
  */
                "(custom):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
                &p->id,
  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
                &p->name,
  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
                &p->vip,
  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
                &p->optimal,
  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
                &p->deprecated,
  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
  */
                &p->custom,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
                "(id):s,"
  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
                "(name):s,"
  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
                "(vip):b,"
  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
                "(optimal):b,"
  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
                "(deprecated):b,"
  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
  */
                "(custom):b,"
                "@arg_switches:b",
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
                p->id,
  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
                p->name,
  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
                &p->vip,
  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
                &p->optimal,
  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
                &p->deprecated,
  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
  */
                &p->custom,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  p->__M.arg_switches[0] = p->id;

  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[2] = &p->vip;

  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[3] = &p->optimal;

  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[4] = &p->deprecated;

  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[5] = &p->custom;

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
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  if (d->id)
    free(d->id);
  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */
  if (d->name)
    free(d->name);
  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */
  //p->vip is a scalar
  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */
  //p->optimal is a scalar
  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */
  //p->deprecated is a scalar
  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
  */
  //p->custom is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/voice.json:33:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */

  /* specs/voice.json:34:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit" }'
  */

  /* specs/voice.json:35:20
     '{ "name": "vip", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:36:20
     '{ "name": "optimal", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:37:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}'
  */

  /* specs/voice.json:38:20
     '{ "name": "custom", "type":{ "base":"bool" }}'
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

} // namespace region
} // namespace voice
} // namespace discord
