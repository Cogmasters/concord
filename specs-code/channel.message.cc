/* This file is generated from specs/channel.message.json, Please don't edit it. */
#include "specs.h"
/*

*/
namespace discord {
namespace channel {
namespace message {

namespace sticker {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(pack_id):F,"
  /* specs/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
                "(name):?s,"
  /* specs/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
                "(description):?s,"
  /* specs/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */
                "(tags):?s,"
  /* specs/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
                "(asset):s,"
  /* specs/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */
                "(preview_asset):s,"
  /* specs/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
  */
                "(type):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->pack_id,
  /* specs/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
                &p->name,
  /* specs/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
                &p->description,
  /* specs/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */
                &p->tags,
  /* specs/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
                p->asset,
  /* specs/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */
                p->preview_asset,
  /* specs/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
  */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[1] = &p->pack_id;

  /* specs/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[2] = p->name;

  /* specs/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[3] = p->description;

  /* specs/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */
  p->__M.arg_switches[4] = p->tags;

  /* specs/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
  p->__M.arg_switches[5] = p->asset;

  /* specs/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */
  if (strlen(p->preview_asset) != 0)
    p->__M.arg_switches[6] = p->preview_asset;

  /* specs/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
  */
  p->__M.arg_switches[7] = &p->type;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(pack_id):|F|,"
  /* specs/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
                "(name):s,"
  /* specs/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
                "(description):s,"
  /* specs/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */
                "(tags):s,"
  /* specs/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
                "(asset):s,"
  /* specs/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */
                "(preview_asset):s,"
  /* specs/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
  */
                "(type):d,"
                "@arg_switches:b",
  /* specs/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->pack_id,
  /* specs/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
                p->name,
  /* specs/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
                p->description,
  /* specs/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */
                p->tags,
  /* specs/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
                p->asset,
  /* specs/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */
                p->preview_asset,
  /* specs/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
  */
                &p->type,
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
  /* specs/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->pack_id is a scalar
  /* specs/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->name)
    free(d->name);
  /* specs/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->description)
    free(d->description);
  /* specs/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */
  if (d->tags)
    free(d->tags);
  /* specs/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */
  //p->asset is a scalar
  /* specs/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */
  //p->preview_asset is a scalar
  /* specs/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
  */
  //p->type is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.message.json:22:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/channel.message.json:23:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/channel.message.json:24:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */

  /* specs/channel.message.json:25:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */

  /* specs/channel.message.json:26:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "option":true, "inject_of_not":null}'
  */

  /* specs/channel.message.json:27:18
     '{"name":"asset","type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}}'
  */

  /* specs/channel.message.json:28:18
     '{"name":"preview_asset", "type":{"base":"char", "dec":"[MAX_SHA256_LEN]"}, 
         "option":true, "inject_if_not":""}'
  */

  /* specs/channel.message.json:30:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::sticker::format_type::code"}}'
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace sticker

namespace reference {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                "(message_id):F,"
  /* specs/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                "(channel_id):F,"
  /* specs/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                "(guild_id):F,"
  /* specs/channel.message.json:58:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, 
         "option":true, "inject_if_not":false}'
  */
                "(fail_if_not_exists):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                orka_strtoull, &p->message_id,
  /* specs/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                orka_strtoull, &p->channel_id,
  /* specs/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                orka_strtoull, &p->guild_id,
  /* specs/channel.message.json:58:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, 
         "option":true, "inject_if_not":false}'
  */
                &p->fail_if_not_exists,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  if (p->message_id != 0)
    p->__M.arg_switches[0] = &p->message_id;

  /* specs/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  if (p->channel_id != 0)
    p->__M.arg_switches[1] = &p->channel_id;

  /* specs/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  if (p->guild_id != 0)
    p->__M.arg_switches[2] = &p->guild_id;

  /* specs/channel.message.json:58:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, 
         "option":true, "inject_if_not":false}'
  */
  if (p->fail_if_not_exists != false)
    p->__M.arg_switches[3] = &p->fail_if_not_exists;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                "(message_id):|F|,"
  /* specs/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                "(channel_id):|F|,"
  /* specs/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                "(guild_id):|F|,"
  /* specs/channel.message.json:58:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, 
         "option":true, "inject_if_not":false}'
  */
                "(fail_if_not_exists):b,"
                "@arg_switches:b",
  /* specs/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                orka_ulltostr, &p->message_id,
  /* specs/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/channel.message.json:58:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, 
         "option":true, "inject_if_not":false}'
  */
                &p->fail_if_not_exists,
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
  /* specs/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  //p->message_id is a scalar
  /* specs/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  //p->channel_id is a scalar
  /* specs/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */
  //p->guild_id is a scalar
  /* specs/channel.message.json:58:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, 
         "option":true, "inject_if_not":false}'
  */
  //p->fail_if_not_exists is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.message.json:52:18
     '{"name":"message_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.message.json:54:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.message.json:56:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, 
         "option":true, "inject_if_not":0}'
  */

  /* specs/channel.message.json:58:18
     '{"name":"fail_if_not_exists", "type":{"base":"bool"}, 
         "option":true, "inject_if_not":false}'
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace reference

namespace application {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                "(cover_image):?s,"
  /* specs/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
                "(description):?s,"
  /* specs/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */
                "(icon):?s,"
  /* specs/channel.message.json:73:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
                "(name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                &p->cover_image,
  /* specs/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
                &p->description,
  /* specs/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */
                &p->icon,
  /* specs/channel.message.json:73:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
                &p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  if (p->cover_image != NULL)
    p->__M.arg_switches[1] = p->cover_image;

  /* specs/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[2] = p->description;

  /* specs/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->icon != NULL)
    p->__M.arg_switches[3] = p->icon;

  /* specs/channel.message.json:73:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[4] = p->name;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                "(cover_image):s,"
  /* specs/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
                "(description):s,"
  /* specs/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */
                "(icon):s,"
  /* specs/channel.message.json:73:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
                "(name):s,"
                "@arg_switches:b",
  /* specs/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                p->cover_image,
  /* specs/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
                p->description,
  /* specs/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */
                p->icon,
  /* specs/channel.message.json:73:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
                p->name,
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
  /* specs/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  if (d->cover_image)
    free(d->cover_image);
  /* specs/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->description)
    free(d->description);
  /* specs/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->icon)
    free(d->icon);
  /* specs/channel.message.json:73:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
  */
  if (d->name)
    free(d->name);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.message.json:68:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/channel.message.json:69:18
     '{"name":"cover_image", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */

  /* specs/channel.message.json:71:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}}'
  */

  /* specs/channel.message.json:72:18
     '{"name":"icon", "type":{"base":"char", "dec":"*"}, "inject_if_not":null}'
  */

  /* specs/channel.message.json:73:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}}'
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace application

namespace activity {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */
                "(type):d,"
  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                "(party_id):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */
                &p->type,
  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                &p->party_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */
  p->__M.arg_switches[0] = &p->type;

  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  if (p->party_id != NULL)
    p->__M.arg_switches[1] = p->party_id;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */
                "(type):d,"
  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                "(party_id):s,"
                "@arg_switches:b",
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */
                &p->type,
  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                p->party_id,
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
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */
  //p->type is a scalar
  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  if (d->party_id)
    free(d->party_id);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"discord::channel::message::activity::types::code"}}'
  */

  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace activity


/* This method is disabled at specs/channel.message.json:127:31 */
void dati_from_json_disabled(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
                "(id):F,"
                "(channel_id):F,"
                "(guild_id):F,"
                "(author):F,"
                "(member):F,"
                "(content):?s,"
                "(timestamp):F,"
                "(edited_timestamp):F,"
                "(tts):b,"
                "(mention_everyone):b,"
                "(mentions):F,"
                "(mention_roles):F,"
                "(mention_channels):F,"
                "(attachments):F,"
                "(embeds):F,"
                "(reactions):F,"
                "(nonce):?s,"
                "(pinned):b,"
                "(webhook_id):F,"
                "(type):d,"
                "(activity):F,"
                "(application):F,"
                "(message_reference):F,"
                "(flags):d,"
                "(stickers):F,"
                "(referenced_message):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
                orka_strtoull, &p->id,
                orka_strtoull, &p->channel_id,
                orka_strtoull, &p->guild_id,
                discord::user::dati_from_json, p->author,
                discord::guild::member::dati_from_json, p->member,
                &p->content,
                orka_iso8601_to_unix_ms, &p->timestamp,
                orka_iso8601_to_unix_ms, &p->edited_timestamp,
                &p->tts,
                &p->mention_everyone,
                discord::user::dati_list_from_json, &p->mentions,
                ja_u64_list_from_json, &p->mention_roles,
                discord::channel::mention::dati_list_from_json, &p->mention_channels,
                discord::channel::attachment::dati_list_from_json, &p->attachments,
                discord::channel::embed::dati_list_from_json, &p->embeds,
                discord::channel::reaction::dati_list_from_json, &p->reactions,
                &p->nonce,
                &p->pinned,
                orka_strtoull, &p->webhook_id,
                &p->type,
                discord::channel::message::activity::dati_from_json, p->activity,
                discord::channel::message::application::dati_list_from_json, &p->application,
                discord::channel::message::reference::dati_from_json, p->message_reference,
                &p->flags,
                discord::channel::message::sticker::dati_list_from_json, &p->stickers,
                discord::channel::message::dati_from_json, p->referenced_message,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.message.json:130:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.message.json:131:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}'
  */
  p->__M.arg_switches[1] = &p->channel_id;

  /* specs/channel.message.json:132:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
          "option":true, "inject_if_not":0}'
  */
  if (p->guild_id != 0)
    p->__M.arg_switches[2] = &p->guild_id;

  /* specs/channel.message.json:134:69
     '{"type":{"base":"discord::user::dati", "dec":"*"}, "name":"author"}'
  */
  p->__M.arg_switches[3] = p->author;

  /* specs/channel.message.json:135:78
     '{"type":{"base":"discord::guild::member::dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  p->__M.arg_switches[4] = p->member;

  /* specs/channel.message.json:137:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}'
  */
  p->__M.arg_switches[5] = p->content;

  /* specs/channel.message.json:138:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}'
  */
  p->__M.arg_switches[6] = &p->timestamp;

  /* specs/channel.message.json:139:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp",
          "inject_if_not":0}'
  */
  if (p->edited_timestamp != 0)
    p->__M.arg_switches[7] = &p->edited_timestamp;

  /* specs/channel.message.json:141:43
     '{"type":{"base":"bool"}, "name":"tts"}'
  */
  p->__M.arg_switches[8] = &p->tts;

  /* specs/channel.message.json:142:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}'
  */
  p->__M.arg_switches[9] = &p->mention_everyone;

  /* specs/channel.message.json:143:71
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
  p->__M.arg_switches[10] = p->mentions;

  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
  p->__M.arg_switches[11] = p->mention_roles;

  /* specs/channel.message.json:146:83
     '{"type":{"base":"discord::channel::mention::dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
  p->__M.arg_switches[12] = p->mention_channels;

  /* specs/channel.message.json:148:86
     '{"type":{"base":"discord::channel::attachment::dati", "dec":"ntl"}, "name":"attachments"}'
  */
  p->__M.arg_switches[13] = p->attachments;

  /* specs/channel.message.json:149:81
     '{"type":{"base":"discord::channel::embed::dati", "dec":"ntl"}, "name":"embeds"}'
  */
  p->__M.arg_switches[14] = p->embeds;

  /* specs/channel.message.json:150:83
     '{"type":{"base":"discord::channel::reaction::dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
  p->__M.arg_switches[15] = p->reactions;

  /* specs/channel.message.json:152:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string",
          "option":true }'
  */
  p->__M.arg_switches[16] = p->nonce;

  /* specs/channel.message.json:154:43
     '{"type":{"base":"bool"}, "name":"pinned"}'
  */
  p->__M.arg_switches[17] = &p->pinned;

  /* specs/channel.message.json:155:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id",
          "option":true }'
  */
  p->__M.arg_switches[18] = &p->webhook_id;

  /* specs/channel.message.json:157:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::types::code"}, "name":"type"}'
  */
  p->__M.arg_switches[19] = &p->type;

  /* specs/channel.message.json:158:91
     '{"type":{"base":"discord::channel::message::activity::dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  if (p->activity != NULL)
    p->__M.arg_switches[20] = p->activity;

  /* specs/channel.message.json:160:96
     '{"type":{"base":"discord::channel::message::application::dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
  if (p->application != NULL)
    p->__M.arg_switches[21] = p->application;

  /* specs/channel.message.json:162:92
     '{"type":{"base":"discord::channel::message::reference::dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  if (p->message_reference != NULL)
    p->__M.arg_switches[22] = p->message_reference;

  /* specs/channel.message.json:164:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::flags::code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
  if (p->flags != 0)
    p->__M.arg_switches[23] = &p->flags;

  /* specs/channel.message.json:166:92
     '{"type":{"base":"discord::channel::message::sticker::dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
  if (p->stickers != NULL)
    p->__M.arg_switches[24] = p->stickers;

  /* specs/channel.message.json:168:81
     '{"type":{"base":"discord::channel::message::dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
  if (p->referenced_message != NULL)
    p->__M.arg_switches[25] = p->referenced_message;

}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.message.json:130:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                "(id):|F|,"
  /* specs/channel.message.json:131:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}'
  */
                "(channel_id):|F|,"
  /* specs/channel.message.json:132:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
          "option":true, "inject_if_not":0}'
  */
                "(guild_id):|F|,"
  /* specs/channel.message.json:134:69
     '{"type":{"base":"discord::user::dati", "dec":"*"}, "name":"author"}'
  */
                "(author):F,"
  /* specs/channel.message.json:135:78
     '{"type":{"base":"discord::guild::member::dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
                "(member):F,"
  /* specs/channel.message.json:137:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}'
  */
                "(content):s,"
  /* specs/channel.message.json:138:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}'
  */
                "(timestamp):|F|,"
  /* specs/channel.message.json:139:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp",
          "inject_if_not":0}'
  */
                "(edited_timestamp):|F|,"
  /* specs/channel.message.json:141:43
     '{"type":{"base":"bool"}, "name":"tts"}'
  */
                "(tts):b,"
  /* specs/channel.message.json:142:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}'
  */
                "(mention_everyone):b,"
  /* specs/channel.message.json:143:71
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
                "(mentions):F,"
  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
                "(mention_roles):F,"
  /* specs/channel.message.json:146:83
     '{"type":{"base":"discord::channel::mention::dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
                "(mention_channels):F,"
  /* specs/channel.message.json:148:86
     '{"type":{"base":"discord::channel::attachment::dati", "dec":"ntl"}, "name":"attachments"}'
  */
                "(attachments):F,"
  /* specs/channel.message.json:149:81
     '{"type":{"base":"discord::channel::embed::dati", "dec":"ntl"}, "name":"embeds"}'
  */
                "(embeds):F,"
  /* specs/channel.message.json:150:83
     '{"type":{"base":"discord::channel::reaction::dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
                "(reactions):F,"
  /* specs/channel.message.json:152:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string",
          "option":true }'
  */
                "(nonce):s,"
  /* specs/channel.message.json:154:43
     '{"type":{"base":"bool"}, "name":"pinned"}'
  */
                "(pinned):b,"
  /* specs/channel.message.json:155:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id",
          "option":true }'
  */
                "(webhook_id):|F|,"
  /* specs/channel.message.json:157:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::types::code"}, "name":"type"}'
  */
                "(type):d,"
  /* specs/channel.message.json:158:91
     '{"type":{"base":"discord::channel::message::activity::dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
                "(activity):F,"
  /* specs/channel.message.json:160:96
     '{"type":{"base":"discord::channel::message::application::dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
                "(application):F,"
  /* specs/channel.message.json:162:92
     '{"type":{"base":"discord::channel::message::reference::dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
                "(message_reference):F,"
  /* specs/channel.message.json:164:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::flags::code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
                "(flags):d,"
  /* specs/channel.message.json:166:92
     '{"type":{"base":"discord::channel::message::sticker::dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
                "(stickers):F,"
  /* specs/channel.message.json:168:81
     '{"type":{"base":"discord::channel::message::dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
                "(referenced_message):F,"
                "@arg_switches:b",
  /* specs/channel.message.json:130:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
                orka_ulltostr, &p->id,
  /* specs/channel.message.json:131:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/channel.message.json:132:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
          "option":true, "inject_if_not":0}'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/channel.message.json:134:69
     '{"type":{"base":"discord::user::dati", "dec":"*"}, "name":"author"}'
  */
                discord::user::dati_to_json, p->author,
  /* specs/channel.message.json:135:78
     '{"type":{"base":"discord::guild::member::dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
                discord::guild::member::dati_to_json, p->member,
  /* specs/channel.message.json:137:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}'
  */
                p->content,
  /* specs/channel.message.json:138:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}'
  */
                orka_unix_ms_to_iso8601, &p->timestamp,
  /* specs/channel.message.json:139:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp",
          "inject_if_not":0}'
  */
                orka_unix_ms_to_iso8601, &p->edited_timestamp,
  /* specs/channel.message.json:141:43
     '{"type":{"base":"bool"}, "name":"tts"}'
  */
                &p->tts,
  /* specs/channel.message.json:142:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}'
  */
                &p->mention_everyone,
  /* specs/channel.message.json:143:71
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
                discord::user::dati_list_to_json, p->mentions,
  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
                ja_u64_list_to_json, p->mention_roles,
  /* specs/channel.message.json:146:83
     '{"type":{"base":"discord::channel::mention::dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
                discord::channel::mention::dati_list_to_json, p->mention_channels,
  /* specs/channel.message.json:148:86
     '{"type":{"base":"discord::channel::attachment::dati", "dec":"ntl"}, "name":"attachments"}'
  */
                discord::channel::attachment::dati_list_to_json, p->attachments,
  /* specs/channel.message.json:149:81
     '{"type":{"base":"discord::channel::embed::dati", "dec":"ntl"}, "name":"embeds"}'
  */
                discord::channel::embed::dati_list_to_json, p->embeds,
  /* specs/channel.message.json:150:83
     '{"type":{"base":"discord::channel::reaction::dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
                discord::channel::reaction::dati_list_to_json, p->reactions,
  /* specs/channel.message.json:152:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string",
          "option":true }'
  */
                p->nonce,
  /* specs/channel.message.json:154:43
     '{"type":{"base":"bool"}, "name":"pinned"}'
  */
                &p->pinned,
  /* specs/channel.message.json:155:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id",
          "option":true }'
  */
                orka_ulltostr, &p->webhook_id,
  /* specs/channel.message.json:157:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::types::code"}, "name":"type"}'
  */
                &p->type,
  /* specs/channel.message.json:158:91
     '{"type":{"base":"discord::channel::message::activity::dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
                discord::channel::message::activity::dati_to_json, p->activity,
  /* specs/channel.message.json:160:96
     '{"type":{"base":"discord::channel::message::application::dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
                discord::channel::message::application::dati_list_to_json, p->application,
  /* specs/channel.message.json:162:92
     '{"type":{"base":"discord::channel::message::reference::dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
                discord::channel::message::reference::dati_to_json, p->message_reference,
  /* specs/channel.message.json:164:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::flags::code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
                &p->flags,
  /* specs/channel.message.json:166:92
     '{"type":{"base":"discord::channel::message::sticker::dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
                discord::channel::message::sticker::dati_list_to_json, p->stickers,
  /* specs/channel.message.json:168:81
     '{"type":{"base":"discord::channel::message::dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
                discord::channel::message::dati_to_json, p->referenced_message,
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
  /* specs/channel.message.json:130:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */
  //p->id is a scalar
  /* specs/channel.message.json:131:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}'
  */
  //p->channel_id is a scalar
  /* specs/channel.message.json:132:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
          "option":true, "inject_if_not":0}'
  */
  //p->guild_id is a scalar
  /* specs/channel.message.json:134:69
     '{"type":{"base":"discord::user::dati", "dec":"*"}, "name":"author"}'
  */
  if (d->author)
    discord::user::dati_free(d->author);
  /* specs/channel.message.json:135:78
     '{"type":{"base":"discord::guild::member::dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  if (d->member)
    discord::guild::member::dati_free(d->member);
  /* specs/channel.message.json:137:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}'
  */
  if (d->content)
    free(d->content);
  /* specs/channel.message.json:138:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}'
  */
  //p->timestamp is a scalar
  /* specs/channel.message.json:139:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp",
          "inject_if_not":0}'
  */
  //p->edited_timestamp is a scalar
  /* specs/channel.message.json:141:43
     '{"type":{"base":"bool"}, "name":"tts"}'
  */
  //p->tts is a scalar
  /* specs/channel.message.json:142:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}'
  */
  //p->mention_everyone is a scalar
  /* specs/channel.message.json:143:71
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
  if (d->mentions)
    discord::user::dati_list_free(d->mentions);
  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
  if (d->mention_roles)
    ja_u64_list_free(d->mention_roles);
  /* specs/channel.message.json:146:83
     '{"type":{"base":"discord::channel::mention::dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
  if (d->mention_channels)
    discord::channel::mention::dati_list_free(d->mention_channels);
  /* specs/channel.message.json:148:86
     '{"type":{"base":"discord::channel::attachment::dati", "dec":"ntl"}, "name":"attachments"}'
  */
  if (d->attachments)
    discord::channel::attachment::dati_list_free(d->attachments);
  /* specs/channel.message.json:149:81
     '{"type":{"base":"discord::channel::embed::dati", "dec":"ntl"}, "name":"embeds"}'
  */
  if (d->embeds)
    discord::channel::embed::dati_list_free(d->embeds);
  /* specs/channel.message.json:150:83
     '{"type":{"base":"discord::channel::reaction::dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
  if (d->reactions)
    discord::channel::reaction::dati_list_free(d->reactions);
  /* specs/channel.message.json:152:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string",
          "option":true }'
  */
  if (d->nonce)
    free(d->nonce);
  /* specs/channel.message.json:154:43
     '{"type":{"base":"bool"}, "name":"pinned"}'
  */
  //p->pinned is a scalar
  /* specs/channel.message.json:155:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id",
          "option":true }'
  */
  //p->webhook_id is a scalar
  /* specs/channel.message.json:157:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::types::code"}, "name":"type"}'
  */
  //p->type is a scalar
  /* specs/channel.message.json:158:91
     '{"type":{"base":"discord::channel::message::activity::dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  if (d->activity)
    discord::channel::message::activity::dati_free(d->activity);
  /* specs/channel.message.json:160:96
     '{"type":{"base":"discord::channel::message::application::dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
  if (d->application)
    discord::channel::message::application::dati_list_free(d->application);
  /* specs/channel.message.json:162:92
     '{"type":{"base":"discord::channel::message::reference::dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  if (d->message_reference)
    discord::channel::message::reference::dati_free(d->message_reference);
  /* specs/channel.message.json:164:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::flags::code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
  //p->flags is a scalar
  /* specs/channel.message.json:166:92
     '{"type":{"base":"discord::channel::message::sticker::dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
  if (d->stickers)
    discord::channel::message::sticker::dati_list_free(d->stickers);
  /* specs/channel.message.json:168:81
     '{"type":{"base":"discord::channel::message::dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
  if (d->referenced_message)
    discord::channel::message::dati_free(d->referenced_message);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.message.json:130:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"id"}'
  */

  /* specs/channel.message.json:131:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"channel_id"}'
  */

  /* specs/channel.message.json:132:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"guild_id",
          "option":true, "inject_if_not":0}'
  */

  /* specs/channel.message.json:134:69
     '{"type":{"base":"discord::user::dati", "dec":"*"}, "name":"author"}'
  */
  p->author = discord::user::dati_alloc();

  /* specs/channel.message.json:135:78
     '{"type":{"base":"discord::guild::member::dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  p->member = discord::guild::member::dati_alloc();

  /* specs/channel.message.json:137:54
     '{"type":{"base":"char", "dec":"*"}, "name":"content"}'
  */

  /* specs/channel.message.json:138:76
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"},"name":"timestamp"}'
  */

  /* specs/channel.message.json:139:77
     '{"type":{"base":"char", "dec":"*", "converter":"iso8601"}, "name":"edited_timestamp",
          "inject_if_not":0}'
  */

  /* specs/channel.message.json:141:43
     '{"type":{"base":"bool"}, "name":"tts"}'
  */

  /* specs/channel.message.json:142:43
     '{"type":{"base":"bool"}, "name":"mention_everyone"}'
  */

  /* specs/channel.message.json:143:71
     '{"type":{"base":"discord::user::dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */

  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */

  /* specs/channel.message.json:146:83
     '{"type":{"base":"discord::channel::mention::dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */

  /* specs/channel.message.json:148:86
     '{"type":{"base":"discord::channel::attachment::dati", "dec":"ntl"}, "name":"attachments"}'
  */

  /* specs/channel.message.json:149:81
     '{"type":{"base":"discord::channel::embed::dati", "dec":"ntl"}, "name":"embeds"}'
  */

  /* specs/channel.message.json:150:83
     '{"type":{"base":"discord::channel::reaction::dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */

  /* specs/channel.message.json:152:54
     '{"type":{"base":"char", "dec":"*"}, "name":"nonce", "comment":"integer or string",
          "option":true }'
  */

  /* specs/channel.message.json:154:43
     '{"type":{"base":"bool"}, "name":"pinned"}'
  */

  /* specs/channel.message.json:155:79
     '{"type":{"base":"char", "dec":"*", "converter":"snowflake"}, "name":"webhook_id",
          "option":true }'
  */

  /* specs/channel.message.json:157:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::types::code"}, "name":"type"}'
  */

  /* specs/channel.message.json:158:91
     '{"type":{"base":"discord::channel::message::activity::dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  p->activity = discord::channel::message::activity::dati_alloc();

  /* specs/channel.message.json:160:96
     '{"type":{"base":"discord::channel::message::application::dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */

  /* specs/channel.message.json:162:92
     '{"type":{"base":"discord::channel::message::reference::dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  p->message_reference = discord::channel::message::reference::dati_alloc();

  /* specs/channel.message.json:164:96
     '{"type":{"base":"int", "int_alias":"discord::channel::message::flags::code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */

  /* specs/channel.message.json:166:92
     '{"type":{"base":"discord::channel::message::sticker::dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */

  /* specs/channel.message.json:168:81
     '{"type":{"base":"discord::channel::message::dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
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
  extract_ntl_from_json(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace message
} // namespace channel
} // namespace discord
