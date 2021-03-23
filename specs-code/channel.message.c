/* This file is generated from specs/channel.message.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_channel_message_sticker_dati_from_json(char *json, size_t len, struct discord_channel_message_sticker_dati *p)
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
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_sticker_format_type_code"}}'
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
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_sticker_format_type_code"}}'
  */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_message_sticker_dati_use_default_inject_settings(struct discord_channel_message_sticker_dati *p)
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
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_sticker_format_type_code"}}'
  */
  p->__M.arg_switches[7] = &p->type;

}

size_t discord_channel_message_sticker_dati_to_json(char *json, size_t len, struct discord_channel_message_sticker_dati *p)
{
  size_t r;
  discord_channel_message_sticker_dati_use_default_inject_settings(p);
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
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_sticker_format_type_code"}}'
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
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_sticker_format_type_code"}}'
  */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_message_sticker_dati_cleanup_v(void *p) {
  discord_channel_message_sticker_dati_cleanup((struct discord_channel_message_sticker_dati *)p);
}

void discord_channel_message_sticker_dati_init_v(void *p) {
  discord_channel_message_sticker_dati_init((struct discord_channel_message_sticker_dati *)p);
}

void discord_channel_message_sticker_dati_free_v(void *p) {
 discord_channel_message_sticker_dati_free((struct discord_channel_message_sticker_dati *)p);
};

void discord_channel_message_sticker_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_message_sticker_dati_from_json(json, len, (struct discord_channel_message_sticker_dati*)p);
}

size_t discord_channel_message_sticker_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_message_sticker_dati_to_json(json, len, (struct discord_channel_message_sticker_dati*)p);
}

void discord_channel_message_sticker_dati_list_free_v(void **p) {
  discord_channel_message_sticker_dati_list_free((struct discord_channel_message_sticker_dati**)p);
}

void discord_channel_message_sticker_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_message_sticker_dati_list_from_json(str, len, (struct discord_channel_message_sticker_dati ***)p);
}

size_t discord_channel_message_sticker_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_message_sticker_dati_list_to_json(str, len, (struct discord_channel_message_sticker_dati **)p);
}


void discord_channel_message_sticker_dati_cleanup(struct discord_channel_message_sticker_dati *d) {
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
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_sticker_format_type_code"}}'
  */
  //p->type is a scalar
}

void discord_channel_message_sticker_dati_init(struct discord_channel_message_sticker_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_message_sticker_dati));
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
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_sticker_format_type_code"}}'
  */

}
struct discord_channel_message_sticker_dati* discord_channel_message_sticker_dati_alloc() {
  struct discord_channel_message_sticker_dati *p= (struct discord_channel_message_sticker_dati*)malloc(sizeof(struct discord_channel_message_sticker_dati));
  discord_channel_message_sticker_dati_init(p);
  return p;
}

void discord_channel_message_sticker_dati_free(struct discord_channel_message_sticker_dati *p) {
  discord_channel_message_sticker_dati_cleanup(p);
  free(p);
}

void discord_channel_message_sticker_dati_list_free(struct discord_channel_message_sticker_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_message_sticker_dati_cleanup);
}

void discord_channel_message_sticker_dati_list_from_json(char *str, size_t len, struct discord_channel_message_sticker_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_message_sticker_dati);
  d.init_elem = discord_channel_message_sticker_dati_init_v;
  d.elem_from_buf = discord_channel_message_sticker_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_message_sticker_dati_list_to_json(char *str, size_t len, struct discord_channel_message_sticker_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_message_sticker_dati_to_json_v);
}


void discord_channel_message_reference_dati_from_json(char *json, size_t len, struct discord_channel_message_reference_dati *p)
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

static void discord_channel_message_reference_dati_use_default_inject_settings(struct discord_channel_message_reference_dati *p)
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

size_t discord_channel_message_reference_dati_to_json(char *json, size_t len, struct discord_channel_message_reference_dati *p)
{
  size_t r;
  discord_channel_message_reference_dati_use_default_inject_settings(p);
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
void discord_channel_message_reference_dati_cleanup_v(void *p) {
  discord_channel_message_reference_dati_cleanup((struct discord_channel_message_reference_dati *)p);
}

void discord_channel_message_reference_dati_init_v(void *p) {
  discord_channel_message_reference_dati_init((struct discord_channel_message_reference_dati *)p);
}

void discord_channel_message_reference_dati_free_v(void *p) {
 discord_channel_message_reference_dati_free((struct discord_channel_message_reference_dati *)p);
};

void discord_channel_message_reference_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_message_reference_dati_from_json(json, len, (struct discord_channel_message_reference_dati*)p);
}

size_t discord_channel_message_reference_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_message_reference_dati_to_json(json, len, (struct discord_channel_message_reference_dati*)p);
}

void discord_channel_message_reference_dati_list_free_v(void **p) {
  discord_channel_message_reference_dati_list_free((struct discord_channel_message_reference_dati**)p);
}

void discord_channel_message_reference_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_message_reference_dati_list_from_json(str, len, (struct discord_channel_message_reference_dati ***)p);
}

size_t discord_channel_message_reference_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_message_reference_dati_list_to_json(str, len, (struct discord_channel_message_reference_dati **)p);
}


void discord_channel_message_reference_dati_cleanup(struct discord_channel_message_reference_dati *d) {
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

void discord_channel_message_reference_dati_init(struct discord_channel_message_reference_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_message_reference_dati));
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
struct discord_channel_message_reference_dati* discord_channel_message_reference_dati_alloc() {
  struct discord_channel_message_reference_dati *p= (struct discord_channel_message_reference_dati*)malloc(sizeof(struct discord_channel_message_reference_dati));
  discord_channel_message_reference_dati_init(p);
  return p;
}

void discord_channel_message_reference_dati_free(struct discord_channel_message_reference_dati *p) {
  discord_channel_message_reference_dati_cleanup(p);
  free(p);
}

void discord_channel_message_reference_dati_list_free(struct discord_channel_message_reference_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_message_reference_dati_cleanup);
}

void discord_channel_message_reference_dati_list_from_json(char *str, size_t len, struct discord_channel_message_reference_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_message_reference_dati);
  d.init_elem = discord_channel_message_reference_dati_init_v;
  d.elem_from_buf = discord_channel_message_reference_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_message_reference_dati_list_to_json(char *str, size_t len, struct discord_channel_message_reference_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_message_reference_dati_to_json_v);
}


void discord_channel_message_application_dati_from_json(char *json, size_t len, struct discord_channel_message_application_dati *p)
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

static void discord_channel_message_application_dati_use_default_inject_settings(struct discord_channel_message_application_dati *p)
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

size_t discord_channel_message_application_dati_to_json(char *json, size_t len, struct discord_channel_message_application_dati *p)
{
  size_t r;
  discord_channel_message_application_dati_use_default_inject_settings(p);
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
void discord_channel_message_application_dati_cleanup_v(void *p) {
  discord_channel_message_application_dati_cleanup((struct discord_channel_message_application_dati *)p);
}

void discord_channel_message_application_dati_init_v(void *p) {
  discord_channel_message_application_dati_init((struct discord_channel_message_application_dati *)p);
}

void discord_channel_message_application_dati_free_v(void *p) {
 discord_channel_message_application_dati_free((struct discord_channel_message_application_dati *)p);
};

void discord_channel_message_application_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_message_application_dati_from_json(json, len, (struct discord_channel_message_application_dati*)p);
}

size_t discord_channel_message_application_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_message_application_dati_to_json(json, len, (struct discord_channel_message_application_dati*)p);
}

void discord_channel_message_application_dati_list_free_v(void **p) {
  discord_channel_message_application_dati_list_free((struct discord_channel_message_application_dati**)p);
}

void discord_channel_message_application_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_message_application_dati_list_from_json(str, len, (struct discord_channel_message_application_dati ***)p);
}

size_t discord_channel_message_application_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_message_application_dati_list_to_json(str, len, (struct discord_channel_message_application_dati **)p);
}


void discord_channel_message_application_dati_cleanup(struct discord_channel_message_application_dati *d) {
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

void discord_channel_message_application_dati_init(struct discord_channel_message_application_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_message_application_dati));
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
struct discord_channel_message_application_dati* discord_channel_message_application_dati_alloc() {
  struct discord_channel_message_application_dati *p= (struct discord_channel_message_application_dati*)malloc(sizeof(struct discord_channel_message_application_dati));
  discord_channel_message_application_dati_init(p);
  return p;
}

void discord_channel_message_application_dati_free(struct discord_channel_message_application_dati *p) {
  discord_channel_message_application_dati_cleanup(p);
  free(p);
}

void discord_channel_message_application_dati_list_free(struct discord_channel_message_application_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_message_application_dati_cleanup);
}

void discord_channel_message_application_dati_list_from_json(char *str, size_t len, struct discord_channel_message_application_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_message_application_dati);
  d.init_elem = discord_channel_message_application_dati_init_v;
  d.elem_from_buf = discord_channel_message_application_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_message_application_dati_list_to_json(char *str, size_t len, struct discord_channel_message_application_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_message_application_dati_to_json_v);
}


void discord_channel_message_activity_dati_from_json(char *json, size_t len, struct discord_channel_message_activity_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_activity_types_code"}}'
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
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_activity_types_code"}}'
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

static void discord_channel_message_activity_dati_use_default_inject_settings(struct discord_channel_message_activity_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_activity_types_code"}}'
  */
  p->__M.arg_switches[0] = &p->type;

  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  if (p->party_id != NULL)
    p->__M.arg_switches[1] = p->party_id;

}

size_t discord_channel_message_activity_dati_to_json(char *json, size_t len, struct discord_channel_message_activity_dati *p)
{
  size_t r;
  discord_channel_message_activity_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_activity_types_code"}}'
  */
                "(type):d,"
  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
                "(party_id):s,"
                "@arg_switches:b",
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_activity_types_code"}}'
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
void discord_channel_message_activity_dati_cleanup_v(void *p) {
  discord_channel_message_activity_dati_cleanup((struct discord_channel_message_activity_dati *)p);
}

void discord_channel_message_activity_dati_init_v(void *p) {
  discord_channel_message_activity_dati_init((struct discord_channel_message_activity_dati *)p);
}

void discord_channel_message_activity_dati_free_v(void *p) {
 discord_channel_message_activity_dati_free((struct discord_channel_message_activity_dati *)p);
};

void discord_channel_message_activity_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_message_activity_dati_from_json(json, len, (struct discord_channel_message_activity_dati*)p);
}

size_t discord_channel_message_activity_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_message_activity_dati_to_json(json, len, (struct discord_channel_message_activity_dati*)p);
}

void discord_channel_message_activity_dati_list_free_v(void **p) {
  discord_channel_message_activity_dati_list_free((struct discord_channel_message_activity_dati**)p);
}

void discord_channel_message_activity_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_message_activity_dati_list_from_json(str, len, (struct discord_channel_message_activity_dati ***)p);
}

size_t discord_channel_message_activity_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_message_activity_dati_list_to_json(str, len, (struct discord_channel_message_activity_dati **)p);
}


void discord_channel_message_activity_dati_cleanup(struct discord_channel_message_activity_dati *d) {
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_activity_types_code"}}'
  */
  //p->type is a scalar
  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */
  if (d->party_id)
    free(d->party_id);
}

void discord_channel_message_activity_dati_init(struct discord_channel_message_activity_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_message_activity_dati));
  /* specs/channel.message.json:94:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_channel_message_activity_types_code"}}'
  */

  /* specs/channel.message.json:95:18
     '{"name":"party_id", "type":{"base":"char", "dec":"*"},
         "option":true, "inject_if_not":null}'
  */

}
struct discord_channel_message_activity_dati* discord_channel_message_activity_dati_alloc() {
  struct discord_channel_message_activity_dati *p= (struct discord_channel_message_activity_dati*)malloc(sizeof(struct discord_channel_message_activity_dati));
  discord_channel_message_activity_dati_init(p);
  return p;
}

void discord_channel_message_activity_dati_free(struct discord_channel_message_activity_dati *p) {
  discord_channel_message_activity_dati_cleanup(p);
  free(p);
}

void discord_channel_message_activity_dati_list_free(struct discord_channel_message_activity_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_message_activity_dati_cleanup);
}

void discord_channel_message_activity_dati_list_from_json(char *str, size_t len, struct discord_channel_message_activity_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_message_activity_dati);
  d.init_elem = discord_channel_message_activity_dati_init_v;
  d.elem_from_buf = discord_channel_message_activity_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_message_activity_dati_list_to_json(char *str, size_t len, struct discord_channel_message_activity_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_message_activity_dati_to_json_v);
}



/* This method is disabled at specs/channel.message.json:127:31 */
void discord_channel_message_dati_from_json_disabled(char *json, size_t len, struct discord_channel_message_dati *p)
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
                discord_user_dati_from_json, p->author,
                discord_guild_member_dati_from_json, p->member,
                &p->content,
                orka_iso8601_to_unix_ms, &p->timestamp,
                orka_iso8601_to_unix_ms, &p->edited_timestamp,
                &p->tts,
                &p->mention_everyone,
                discord_user_dati_list_from_json, &p->mentions,
                ja_u64_list_from_json, &p->mention_roles,
                discord_channel_mention_dati_list_from_json, &p->mention_channels,
                discord_channel_attachment_dati_list_from_json, &p->attachments,
                discord_channel_embed_dati_list_from_json, &p->embeds,
                discord_channel_reaction_dati_list_from_json, &p->reactions,
                &p->nonce,
                &p->pinned,
                orka_strtoull, &p->webhook_id,
                &p->type,
                discord_channel_message_activity_dati_from_json, p->activity,
                discord_channel_message_application_dati_list_from_json, &p->application,
                discord_channel_message_reference_dati_from_json, p->message_reference,
                &p->flags,
                discord_channel_message_sticker_dati_list_from_json, &p->stickers,
                discord_channel_message_dati_from_json, p->referenced_message,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_message_dati_use_default_inject_settings(struct discord_channel_message_dati *p)
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

  /* specs/channel.message.json:134:74
     '{"type":{"base":"struct discord_user_dati", "dec":"*"}, "name":"author"}'
  */
  p->__M.arg_switches[3] = p->author;

  /* specs/channel.message.json:135:82
     '{"type":{"base":"struct discord_guild_member_dati", "dec":"*"}, "name":"member", 
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

  /* specs/channel.message.json:143:76
     '{"type":{"base":"struct discord_user_dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
  p->__M.arg_switches[10] = p->mentions;

  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
  p->__M.arg_switches[11] = p->mention_roles;

  /* specs/channel.message.json:146:87
     '{"type":{"base":"struct discord_channel_mention_dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
  p->__M.arg_switches[12] = p->mention_channels;

  /* specs/channel.message.json:148:90
     '{"type":{"base":"struct discord_channel_attachment_dati", "dec":"ntl"}, "name":"attachments"}'
  */
  p->__M.arg_switches[13] = p->attachments;

  /* specs/channel.message.json:149:85
     '{"type":{"base":"struct discord_channel_embed_dati", "dec":"ntl"}, "name":"embeds"}'
  */
  p->__M.arg_switches[14] = p->embeds;

  /* specs/channel.message.json:150:87
     '{"type":{"base":"struct discord_channel_reaction_dati","dec":"ntl"}, "name":"reactions", 
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

  /* specs/channel.message.json:157:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_types_code"}, "name":"type"}'
  */
  p->__M.arg_switches[19] = &p->type;

  /* specs/channel.message.json:158:94
     '{"type":{"base":"struct discord_channel_message_activity_dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  if (p->activity != NULL)
    p->__M.arg_switches[20] = p->activity;

  /* specs/channel.message.json:160:99
     '{"type":{"base":"struct discord_channel_message_application_dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
  if (p->application != NULL)
    p->__M.arg_switches[21] = p->application;

  /* specs/channel.message.json:162:95
     '{"type":{"base":"struct discord_channel_message_reference_dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  if (p->message_reference != NULL)
    p->__M.arg_switches[22] = p->message_reference;

  /* specs/channel.message.json:164:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_flags_code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
  if (p->flags != 0)
    p->__M.arg_switches[23] = &p->flags;

  /* specs/channel.message.json:166:95
     '{"type":{"base":"struct discord_channel_message_sticker_dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
  if (p->stickers != NULL)
    p->__M.arg_switches[24] = p->stickers;

  /* specs/channel.message.json:168:85
     '{"type":{"base":"struct discord_channel_message_dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
  if (p->referenced_message != NULL)
    p->__M.arg_switches[25] = p->referenced_message;

}

size_t discord_channel_message_dati_to_json(char *json, size_t len, struct discord_channel_message_dati *p)
{
  size_t r;
  discord_channel_message_dati_use_default_inject_settings(p);
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
  /* specs/channel.message.json:134:74
     '{"type":{"base":"struct discord_user_dati", "dec":"*"}, "name":"author"}'
  */
                "(author):F,"
  /* specs/channel.message.json:135:82
     '{"type":{"base":"struct discord_guild_member_dati", "dec":"*"}, "name":"member", 
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
  /* specs/channel.message.json:143:76
     '{"type":{"base":"struct discord_user_dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
                "(mentions):F,"
  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
                "(mention_roles):F,"
  /* specs/channel.message.json:146:87
     '{"type":{"base":"struct discord_channel_mention_dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
                "(mention_channels):F,"
  /* specs/channel.message.json:148:90
     '{"type":{"base":"struct discord_channel_attachment_dati", "dec":"ntl"}, "name":"attachments"}'
  */
                "(attachments):F,"
  /* specs/channel.message.json:149:85
     '{"type":{"base":"struct discord_channel_embed_dati", "dec":"ntl"}, "name":"embeds"}'
  */
                "(embeds):F,"
  /* specs/channel.message.json:150:87
     '{"type":{"base":"struct discord_channel_reaction_dati","dec":"ntl"}, "name":"reactions", 
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
  /* specs/channel.message.json:157:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_types_code"}, "name":"type"}'
  */
                "(type):d,"
  /* specs/channel.message.json:158:94
     '{"type":{"base":"struct discord_channel_message_activity_dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
                "(activity):F,"
  /* specs/channel.message.json:160:99
     '{"type":{"base":"struct discord_channel_message_application_dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
                "(application):F,"
  /* specs/channel.message.json:162:95
     '{"type":{"base":"struct discord_channel_message_reference_dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
                "(message_reference):F,"
  /* specs/channel.message.json:164:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_flags_code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
                "(flags):d,"
  /* specs/channel.message.json:166:95
     '{"type":{"base":"struct discord_channel_message_sticker_dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
                "(stickers):F,"
  /* specs/channel.message.json:168:85
     '{"type":{"base":"struct discord_channel_message_dati", "dec":"*"}, "name":"referenced_message", 
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
  /* specs/channel.message.json:134:74
     '{"type":{"base":"struct discord_user_dati", "dec":"*"}, "name":"author"}'
  */
                discord_user_dati_to_json, p->author,
  /* specs/channel.message.json:135:82
     '{"type":{"base":"struct discord_guild_member_dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
                discord_guild_member_dati_to_json, p->member,
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
  /* specs/channel.message.json:143:76
     '{"type":{"base":"struct discord_user_dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
                discord_user_dati_list_to_json, p->mentions,
  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
                ja_u64_list_to_json, p->mention_roles,
  /* specs/channel.message.json:146:87
     '{"type":{"base":"struct discord_channel_mention_dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
                discord_channel_mention_dati_list_to_json, p->mention_channels,
  /* specs/channel.message.json:148:90
     '{"type":{"base":"struct discord_channel_attachment_dati", "dec":"ntl"}, "name":"attachments"}'
  */
                discord_channel_attachment_dati_list_to_json, p->attachments,
  /* specs/channel.message.json:149:85
     '{"type":{"base":"struct discord_channel_embed_dati", "dec":"ntl"}, "name":"embeds"}'
  */
                discord_channel_embed_dati_list_to_json, p->embeds,
  /* specs/channel.message.json:150:87
     '{"type":{"base":"struct discord_channel_reaction_dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
                discord_channel_reaction_dati_list_to_json, p->reactions,
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
  /* specs/channel.message.json:157:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_types_code"}, "name":"type"}'
  */
                &p->type,
  /* specs/channel.message.json:158:94
     '{"type":{"base":"struct discord_channel_message_activity_dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
                discord_channel_message_activity_dati_to_json, p->activity,
  /* specs/channel.message.json:160:99
     '{"type":{"base":"struct discord_channel_message_application_dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
                discord_channel_message_application_dati_list_to_json, p->application,
  /* specs/channel.message.json:162:95
     '{"type":{"base":"struct discord_channel_message_reference_dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
                discord_channel_message_reference_dati_to_json, p->message_reference,
  /* specs/channel.message.json:164:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_flags_code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
                &p->flags,
  /* specs/channel.message.json:166:95
     '{"type":{"base":"struct discord_channel_message_sticker_dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
                discord_channel_message_sticker_dati_list_to_json, p->stickers,
  /* specs/channel.message.json:168:85
     '{"type":{"base":"struct discord_channel_message_dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
                discord_channel_message_dati_to_json, p->referenced_message,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_message_dati_cleanup_v(void *p) {
  discord_channel_message_dati_cleanup((struct discord_channel_message_dati *)p);
}

void discord_channel_message_dati_init_v(void *p) {
  discord_channel_message_dati_init((struct discord_channel_message_dati *)p);
}

void discord_channel_message_dati_free_v(void *p) {
 discord_channel_message_dati_free((struct discord_channel_message_dati *)p);
};

void discord_channel_message_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_message_dati_from_json(json, len, (struct discord_channel_message_dati*)p);
}

size_t discord_channel_message_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_message_dati_to_json(json, len, (struct discord_channel_message_dati*)p);
}

void discord_channel_message_dati_list_free_v(void **p) {
  discord_channel_message_dati_list_free((struct discord_channel_message_dati**)p);
}

void discord_channel_message_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_message_dati_list_from_json(str, len, (struct discord_channel_message_dati ***)p);
}

size_t discord_channel_message_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_message_dati_list_to_json(str, len, (struct discord_channel_message_dati **)p);
}


void discord_channel_message_dati_cleanup(struct discord_channel_message_dati *d) {
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
  /* specs/channel.message.json:134:74
     '{"type":{"base":"struct discord_user_dati", "dec":"*"}, "name":"author"}'
  */
  if (d->author)
    discord_user_dati_free(d->author);
  /* specs/channel.message.json:135:82
     '{"type":{"base":"struct discord_guild_member_dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  if (d->member)
    discord_guild_member_dati_free(d->member);
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
  /* specs/channel.message.json:143:76
     '{"type":{"base":"struct discord_user_dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */
  if (d->mentions)
    discord_user_dati_list_free(d->mentions);
  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */
  if (d->mention_roles)
    ja_u64_list_free(d->mention_roles);
  /* specs/channel.message.json:146:87
     '{"type":{"base":"struct discord_channel_mention_dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */
  if (d->mention_channels)
    discord_channel_mention_dati_list_free(d->mention_channels);
  /* specs/channel.message.json:148:90
     '{"type":{"base":"struct discord_channel_attachment_dati", "dec":"ntl"}, "name":"attachments"}'
  */
  if (d->attachments)
    discord_channel_attachment_dati_list_free(d->attachments);
  /* specs/channel.message.json:149:85
     '{"type":{"base":"struct discord_channel_embed_dati", "dec":"ntl"}, "name":"embeds"}'
  */
  if (d->embeds)
    discord_channel_embed_dati_list_free(d->embeds);
  /* specs/channel.message.json:150:87
     '{"type":{"base":"struct discord_channel_reaction_dati","dec":"ntl"}, "name":"reactions", 
          "option":true }'
  */
  if (d->reactions)
    discord_channel_reaction_dati_list_free(d->reactions);
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
  /* specs/channel.message.json:157:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_types_code"}, "name":"type"}'
  */
  //p->type is a scalar
  /* specs/channel.message.json:158:94
     '{"type":{"base":"struct discord_channel_message_activity_dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  if (d->activity)
    discord_channel_message_activity_dati_free(d->activity);
  /* specs/channel.message.json:160:99
     '{"type":{"base":"struct discord_channel_message_application_dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */
  if (d->application)
    discord_channel_message_application_dati_list_free(d->application);
  /* specs/channel.message.json:162:95
     '{"type":{"base":"struct discord_channel_message_reference_dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  if (d->message_reference)
    discord_channel_message_reference_dati_free(d->message_reference);
  /* specs/channel.message.json:164:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_flags_code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */
  //p->flags is a scalar
  /* specs/channel.message.json:166:95
     '{"type":{"base":"struct discord_channel_message_sticker_dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */
  if (d->stickers)
    discord_channel_message_sticker_dati_list_free(d->stickers);
  /* specs/channel.message.json:168:85
     '{"type":{"base":"struct discord_channel_message_dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */
  if (d->referenced_message)
    discord_channel_message_dati_free(d->referenced_message);
}

void discord_channel_message_dati_init(struct discord_channel_message_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_message_dati));
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

  /* specs/channel.message.json:134:74
     '{"type":{"base":"struct discord_user_dati", "dec":"*"}, "name":"author"}'
  */
  p->author = discord_user_dati_alloc();

  /* specs/channel.message.json:135:82
     '{"type":{"base":"struct discord_guild_member_dati", "dec":"*"}, "name":"member", 
          "option":true, "comment":"partial guild member object"}'
  */
  p->member = discord_guild_member_dati_alloc();

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

  /* specs/channel.message.json:143:76
     '{"type":{"base":"struct discord_user_dati", "dec":"ntl"}, "name":"mentions", 
          "comment":"array of user objects, with an additional partial member field"}'
  */

  /* specs/channel.message.json:145:58
     '{"type":{"base":"ja_u64", "dec":"ntl"}, "name":"mention_roles", "comment":"array of role object ids"}'
  */

  /* specs/channel.message.json:146:87
     '{"type":{"base":"struct discord_channel_mention_dati", "dec":"ntl"}, "name":"mention_channels",
          "option":true }'
  */

  /* specs/channel.message.json:148:90
     '{"type":{"base":"struct discord_channel_attachment_dati", "dec":"ntl"}, "name":"attachments"}'
  */

  /* specs/channel.message.json:149:85
     '{"type":{"base":"struct discord_channel_embed_dati", "dec":"ntl"}, "name":"embeds"}'
  */

  /* specs/channel.message.json:150:87
     '{"type":{"base":"struct discord_channel_reaction_dati","dec":"ntl"}, "name":"reactions", 
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

  /* specs/channel.message.json:157:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_types_code"}, "name":"type"}'
  */

  /* specs/channel.message.json:158:94
     '{"type":{"base":"struct discord_channel_message_activity_dati", "dec":"*"}, "name":"activity", 
          "option":true, "inject_if_not":null }'
  */
  p->activity = discord_channel_message_activity_dati_alloc();

  /* specs/channel.message.json:160:99
     '{"type":{"base":"struct discord_channel_message_application_dati", "dec":"ntl"}, "name":"application",
          "option":true, "inject_if_not":null }'
  */

  /* specs/channel.message.json:162:95
     '{"type":{"base":"struct discord_channel_message_reference_dati", "dec":"*"}, "name":"message_reference",
          "option":true, "inject_if_not":null }'
  */
  p->message_reference = discord_channel_message_reference_dati_alloc();

  /* specs/channel.message.json:164:97
     '{"type":{"base":"int", "int_alias":"enum discord_channel_message_flags_code"}, "name":"flags",
          "option":true, "inject_if_not":0 }'
  */

  /* specs/channel.message.json:166:95
     '{"type":{"base":"struct discord_channel_message_sticker_dati", "dec":"ntl"}, "name":"stickers",
          "option":true, "inject_if_not":null, "comment":"array of sticker objects"}'
  */

  /* specs/channel.message.json:168:85
     '{"type":{"base":"struct discord_channel_message_dati", "dec":"*"}, "name":"referenced_message", 
          "lazy_init":true, "option":true", "inject_if_not":null,
          "comment":"this will cause recursive allocation if allocating as the parent"}'
  */

}
struct discord_channel_message_dati* discord_channel_message_dati_alloc() {
  struct discord_channel_message_dati *p= (struct discord_channel_message_dati*)malloc(sizeof(struct discord_channel_message_dati));
  discord_channel_message_dati_init(p);
  return p;
}

void discord_channel_message_dati_free(struct discord_channel_message_dati *p) {
  discord_channel_message_dati_cleanup(p);
  free(p);
}

void discord_channel_message_dati_list_free(struct discord_channel_message_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_message_dati_cleanup);
}

void discord_channel_message_dati_list_from_json(char *str, size_t len, struct discord_channel_message_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_message_dati);
  d.init_elem = discord_channel_message_dati_init_v;
  d.elem_from_buf = discord_channel_message_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_message_dati_list_to_json(char *str, size_t len, struct discord_channel_message_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_message_dati_to_json_v);
}

