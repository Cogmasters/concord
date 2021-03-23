/* This file is generated from specs/channel.objects.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/


/* This method is disabled at specs/channel.objects.json:9:30 */
void discord_channel_overwrite_dati_from_json_disabled(char *json, size_t len, struct discord_channel_overwrite_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
                "(id):F,"
                "(type):d,"
                "(allow):s_as_hex_uint,"
                "(deny):s_as_hex_uint,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
                orka_strtoull, &p->id,
                &p->type,
                &p->allow,
                &p->deny,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_overwrite_dati_use_default_inject_settings(struct discord_channel_overwrite_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[1] = &p->type;

  /* specs/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  p->__M.arg_switches[2] = &p->allow;

  /* specs/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  p->__M.arg_switches[3] = &p->deny;

}


/* This method is disabled at specs/channel.objects.json:9:30 */
size_t discord_channel_overwrite_dati_to_json_disabled(char *json, size_t len, struct discord_channel_overwrite_dati *p)
{
  size_t r;
  discord_channel_overwrite_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
                "(id):|F|,"
                "(type):d,"
                "(allow):s_as_hex_uint,"
                "(deny):s_as_hex_uint,"
                "@arg_switches:b",
                orka_ulltostr, &p->id,
                &p->type,
                &p->allow,
                &p->deny,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_overwrite_dati_cleanup_v(void *p) {
  discord_channel_overwrite_dati_cleanup((struct discord_channel_overwrite_dati *)p);
}

void discord_channel_overwrite_dati_init_v(void *p) {
  discord_channel_overwrite_dati_init((struct discord_channel_overwrite_dati *)p);
}

void discord_channel_overwrite_dati_free_v(void *p) {
 discord_channel_overwrite_dati_free((struct discord_channel_overwrite_dati *)p);
};

void discord_channel_overwrite_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_overwrite_dati_from_json(json, len, (struct discord_channel_overwrite_dati*)p);
}

size_t discord_channel_overwrite_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_overwrite_dati_to_json(json, len, (struct discord_channel_overwrite_dati*)p);
}

void discord_channel_overwrite_dati_list_free_v(void **p) {
  discord_channel_overwrite_dati_list_free((struct discord_channel_overwrite_dati**)p);
}

void discord_channel_overwrite_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_overwrite_dati_list_from_json(str, len, (struct discord_channel_overwrite_dati ***)p);
}

size_t discord_channel_overwrite_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_overwrite_dati_list_to_json(str, len, (struct discord_channel_overwrite_dati **)p);
}


void discord_channel_overwrite_dati_cleanup(struct discord_channel_overwrite_dati *d) {
  /* specs/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  //p->type is a scalar
  /* specs/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  //p->allow is a scalar
  /* specs/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */
  //p->deny is a scalar
}

void discord_channel_overwrite_dati_init(struct discord_channel_overwrite_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_overwrite_dati));
  /* specs/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */

  /* specs/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */

  /* specs/channel.objects.json:17:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"discord_permissions_bitwise_flags"}, 
          "comment":"permission bit set"}'
  */

}
struct discord_channel_overwrite_dati* discord_channel_overwrite_dati_alloc() {
  struct discord_channel_overwrite_dati *p= (struct discord_channel_overwrite_dati*)malloc(sizeof(struct discord_channel_overwrite_dati));
  discord_channel_overwrite_dati_init(p);
  return p;
}

void discord_channel_overwrite_dati_free(struct discord_channel_overwrite_dati *p) {
  discord_channel_overwrite_dati_cleanup(p);
  free(p);
}

void discord_channel_overwrite_dati_list_free(struct discord_channel_overwrite_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_overwrite_dati_cleanup);
}

void discord_channel_overwrite_dati_list_from_json(char *str, size_t len, struct discord_channel_overwrite_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_overwrite_dati);
  d.init_elem = discord_channel_overwrite_dati_init_v;
  d.elem_from_buf = discord_channel_overwrite_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_overwrite_dati_list_to_json(char *str, size_t len, struct discord_channel_overwrite_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_overwrite_dati_to_json_v);
}


void discord_channel_reaction_dati_from_json(char *json, size_t len, struct discord_channel_reaction_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                "(count):d,"
  /* specs/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                "(me):b,"
  /* specs/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji_dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
                "(emoji):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                &p->count,
  /* specs/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                &p->me,
  /* specs/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji_dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
                discord_emoji_dati_from_json, p->emoji,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_reaction_dati_use_default_inject_settings(struct discord_channel_reaction_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[0] = &p->count;

  /* specs/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[1] = &p->me;

  /* specs/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji_dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  p->__M.arg_switches[2] = p->emoji;

}

size_t discord_channel_reaction_dati_to_json(char *json, size_t len, struct discord_channel_reaction_dati *p)
{
  size_t r;
  discord_channel_reaction_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                "(count):d,"
  /* specs/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                "(me):b,"
  /* specs/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji_dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
                "(emoji):F,"
                "@arg_switches:b",
  /* specs/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                &p->count,
  /* specs/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                &p->me,
  /* specs/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji_dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
                discord_emoji_dati_to_json, p->emoji,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_reaction_dati_cleanup_v(void *p) {
  discord_channel_reaction_dati_cleanup((struct discord_channel_reaction_dati *)p);
}

void discord_channel_reaction_dati_init_v(void *p) {
  discord_channel_reaction_dati_init((struct discord_channel_reaction_dati *)p);
}

void discord_channel_reaction_dati_free_v(void *p) {
 discord_channel_reaction_dati_free((struct discord_channel_reaction_dati *)p);
};

void discord_channel_reaction_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_reaction_dati_from_json(json, len, (struct discord_channel_reaction_dati*)p);
}

size_t discord_channel_reaction_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_reaction_dati_to_json(json, len, (struct discord_channel_reaction_dati*)p);
}

void discord_channel_reaction_dati_list_free_v(void **p) {
  discord_channel_reaction_dati_list_free((struct discord_channel_reaction_dati**)p);
}

void discord_channel_reaction_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_reaction_dati_list_from_json(str, len, (struct discord_channel_reaction_dati ***)p);
}

size_t discord_channel_reaction_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_reaction_dati_list_to_json(str, len, (struct discord_channel_reaction_dati **)p);
}


void discord_channel_reaction_dati_cleanup(struct discord_channel_reaction_dati *d) {
  /* specs/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  //p->count is a scalar
  /* specs/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  //p->me is a scalar
  /* specs/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji_dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  if (d->emoji)
    discord_emoji_dati_free(d->emoji);
}

void discord_channel_reaction_dati_init(struct discord_channel_reaction_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_reaction_dati));
  /* specs/channel.objects.json:27:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */

  /* specs/channel.objects.json:28:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */

  /* specs/channel.objects.json:29:20
     '{ "name": "emoji", "type":{ "base":"struct discord_emoji_dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  p->emoji = discord_emoji_dati_alloc();

}
struct discord_channel_reaction_dati* discord_channel_reaction_dati_alloc() {
  struct discord_channel_reaction_dati *p= (struct discord_channel_reaction_dati*)malloc(sizeof(struct discord_channel_reaction_dati));
  discord_channel_reaction_dati_init(p);
  return p;
}

void discord_channel_reaction_dati_free(struct discord_channel_reaction_dati *p) {
  discord_channel_reaction_dati_cleanup(p);
  free(p);
}

void discord_channel_reaction_dati_list_free(struct discord_channel_reaction_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_reaction_dati_cleanup);
}

void discord_channel_reaction_dati_list_from_json(char *str, size_t len, struct discord_channel_reaction_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_reaction_dati);
  d.init_elem = discord_channel_reaction_dati_init_v;
  d.elem_from_buf = discord_channel_reaction_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_reaction_dati_list_to_json(char *str, size_t len, struct discord_channel_reaction_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_reaction_dati_to_json_v);
}


void discord_channel_followed_channel_dati_from_json(char *json, size_t len, struct discord_channel_followed_channel_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):F,"
  /* specs/channel.objects.json:40:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(webhook_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->channel_id,
  /* specs/channel.objects.json:40:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->webhook_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_followed_channel_dati_use_default_inject_settings(struct discord_channel_followed_channel_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->channel_id;

  /* specs/channel.objects.json:40:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->webhook_id;

}

size_t discord_channel_followed_channel_dati_to_json(char *json, size_t len, struct discord_channel_followed_channel_dati *p)
{
  size_t r;
  discord_channel_followed_channel_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):|F|,"
  /* specs/channel.objects.json:40:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(webhook_id):|F|,"
                "@arg_switches:b",
  /* specs/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/channel.objects.json:40:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->webhook_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_followed_channel_dati_cleanup_v(void *p) {
  discord_channel_followed_channel_dati_cleanup((struct discord_channel_followed_channel_dati *)p);
}

void discord_channel_followed_channel_dati_init_v(void *p) {
  discord_channel_followed_channel_dati_init((struct discord_channel_followed_channel_dati *)p);
}

void discord_channel_followed_channel_dati_free_v(void *p) {
 discord_channel_followed_channel_dati_free((struct discord_channel_followed_channel_dati *)p);
};

void discord_channel_followed_channel_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_followed_channel_dati_from_json(json, len, (struct discord_channel_followed_channel_dati*)p);
}

size_t discord_channel_followed_channel_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_followed_channel_dati_to_json(json, len, (struct discord_channel_followed_channel_dati*)p);
}

void discord_channel_followed_channel_dati_list_free_v(void **p) {
  discord_channel_followed_channel_dati_list_free((struct discord_channel_followed_channel_dati**)p);
}

void discord_channel_followed_channel_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_followed_channel_dati_list_from_json(str, len, (struct discord_channel_followed_channel_dati ***)p);
}

size_t discord_channel_followed_channel_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_followed_channel_dati_list_to_json(str, len, (struct discord_channel_followed_channel_dati **)p);
}


void discord_channel_followed_channel_dati_cleanup(struct discord_channel_followed_channel_dati *d) {
  /* specs/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->channel_id is a scalar
  /* specs/channel.objects.json:40:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->webhook_id is a scalar
}

void discord_channel_followed_channel_dati_init(struct discord_channel_followed_channel_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_followed_channel_dati));
  /* specs/channel.objects.json:39:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:40:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

}
struct discord_channel_followed_channel_dati* discord_channel_followed_channel_dati_alloc() {
  struct discord_channel_followed_channel_dati *p= (struct discord_channel_followed_channel_dati*)malloc(sizeof(struct discord_channel_followed_channel_dati));
  discord_channel_followed_channel_dati_init(p);
  return p;
}

void discord_channel_followed_channel_dati_free(struct discord_channel_followed_channel_dati *p) {
  discord_channel_followed_channel_dati_cleanup(p);
  free(p);
}

void discord_channel_followed_channel_dati_list_free(struct discord_channel_followed_channel_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_followed_channel_dati_cleanup);
}

void discord_channel_followed_channel_dati_list_from_json(char *str, size_t len, struct discord_channel_followed_channel_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_followed_channel_dati);
  d.init_elem = discord_channel_followed_channel_dati_init_v;
  d.elem_from_buf = discord_channel_followed_channel_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_followed_channel_dati_list_to_json(char *str, size_t len, struct discord_channel_followed_channel_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_followed_channel_dati_to_json_v);
}


void discord_channel_attachment_dati_from_json(char *json, size_t len, struct discord_channel_attachment_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                "(filename):s,"
  /* specs/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                "(size):d,"
  /* specs/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                "(url):s,"
  /* specs/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                "(height):d,"
  /* specs/channel.objects.json:55:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                p->filename,
  /* specs/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                &p->size,
  /* specs/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                p->url,
  /* specs/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                &p->height,
  /* specs/channel.objects.json:55:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_attachment_dati_use_default_inject_settings(struct discord_channel_attachment_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  p->__M.arg_switches[1] = p->filename;

  /* specs/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->size;

  /* specs/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  p->__M.arg_switches[3] = p->url;

  /* specs/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  p->__M.arg_switches[4] = p->proxy_url;

  /* specs/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  p->__M.arg_switches[5] = &p->height;

  /* specs/channel.objects.json:55:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
  p->__M.arg_switches[6] = &p->width;

}

size_t discord_channel_attachment_dati_to_json(char *json, size_t len, struct discord_channel_attachment_dati *p)
{
  size_t r;
  discord_channel_attachment_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                "(filename):s,"
  /* specs/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                "(size):d,"
  /* specs/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                "(url):s,"
  /* specs/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                "(height):d,"
  /* specs/channel.objects.json:55:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                p->filename,
  /* specs/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                &p->size,
  /* specs/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                p->url,
  /* specs/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                &p->height,
  /* specs/channel.objects.json:55:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_attachment_dati_cleanup_v(void *p) {
  discord_channel_attachment_dati_cleanup((struct discord_channel_attachment_dati *)p);
}

void discord_channel_attachment_dati_init_v(void *p) {
  discord_channel_attachment_dati_init((struct discord_channel_attachment_dati *)p);
}

void discord_channel_attachment_dati_free_v(void *p) {
 discord_channel_attachment_dati_free((struct discord_channel_attachment_dati *)p);
};

void discord_channel_attachment_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_attachment_dati_from_json(json, len, (struct discord_channel_attachment_dati*)p);
}

size_t discord_channel_attachment_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_attachment_dati_to_json(json, len, (struct discord_channel_attachment_dati*)p);
}

void discord_channel_attachment_dati_list_free_v(void **p) {
  discord_channel_attachment_dati_list_free((struct discord_channel_attachment_dati**)p);
}

void discord_channel_attachment_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_attachment_dati_list_from_json(str, len, (struct discord_channel_attachment_dati ***)p);
}

size_t discord_channel_attachment_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_attachment_dati_list_to_json(str, len, (struct discord_channel_attachment_dati **)p);
}


void discord_channel_attachment_dati_cleanup(struct discord_channel_attachment_dati *d) {
  /* specs/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  //p->filename is a scalar
  /* specs/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  //p->size is a scalar
  /* specs/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  //p->proxy_url is a scalar
  /* specs/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  //p->height is a scalar
  /* specs/channel.objects.json:55:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
  //p->width is a scalar
}

void discord_channel_attachment_dati_init(struct discord_channel_attachment_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_attachment_dati));
  /* specs/channel.objects.json:49:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:50:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */

  /* specs/channel.objects.json:51:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */

  /* specs/channel.objects.json:52:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */

  /* specs/channel.objects.json:53:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */

  /* specs/channel.objects.json:54:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */

  /* specs/channel.objects.json:55:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */

}
struct discord_channel_attachment_dati* discord_channel_attachment_dati_alloc() {
  struct discord_channel_attachment_dati *p= (struct discord_channel_attachment_dati*)malloc(sizeof(struct discord_channel_attachment_dati));
  discord_channel_attachment_dati_init(p);
  return p;
}

void discord_channel_attachment_dati_free(struct discord_channel_attachment_dati *p) {
  discord_channel_attachment_dati_cleanup(p);
  free(p);
}

void discord_channel_attachment_dati_list_free(struct discord_channel_attachment_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_attachment_dati_cleanup);
}

void discord_channel_attachment_dati_list_from_json(char *str, size_t len, struct discord_channel_attachment_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_attachment_dati);
  d.init_elem = discord_channel_attachment_dati_init_v;
  d.elem_from_buf = discord_channel_attachment_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_attachment_dati_list_to_json(char *str, size_t len, struct discord_channel_attachment_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_attachment_dati_to_json_v);
}


void discord_channel_mention_dati_from_json(char *json, size_t len, struct discord_channel_mention_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):F,"
  /* specs/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types_code" }}'
  */
                "(type):d,"
  /* specs/channel.objects.json:68:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->guild_id,
  /* specs/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types_code" }}'
  */
                &p->type,
  /* specs/channel.objects.json:68:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_mention_dati_use_default_inject_settings(struct discord_channel_mention_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->guild_id;

  /* specs/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types_code" }}'
  */
  p->__M.arg_switches[2] = &p->type;

  /* specs/channel.objects.json:68:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[3] = p->name;

}

size_t discord_channel_mention_dati_to_json(char *json, size_t len, struct discord_channel_mention_dati *p)
{
  size_t r;
  discord_channel_mention_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):|F|,"
  /* specs/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types_code" }}'
  */
                "(type):d,"
  /* specs/channel.objects.json:68:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):s,"
                "@arg_switches:b",
  /* specs/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types_code" }}'
  */
                &p->type,
  /* specs/channel.objects.json:68:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_mention_dati_cleanup_v(void *p) {
  discord_channel_mention_dati_cleanup((struct discord_channel_mention_dati *)p);
}

void discord_channel_mention_dati_init_v(void *p) {
  discord_channel_mention_dati_init((struct discord_channel_mention_dati *)p);
}

void discord_channel_mention_dati_free_v(void *p) {
 discord_channel_mention_dati_free((struct discord_channel_mention_dati *)p);
};

void discord_channel_mention_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_mention_dati_from_json(json, len, (struct discord_channel_mention_dati*)p);
}

size_t discord_channel_mention_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_mention_dati_to_json(json, len, (struct discord_channel_mention_dati*)p);
}

void discord_channel_mention_dati_list_free_v(void **p) {
  discord_channel_mention_dati_list_free((struct discord_channel_mention_dati**)p);
}

void discord_channel_mention_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_mention_dati_list_from_json(str, len, (struct discord_channel_mention_dati ***)p);
}

size_t discord_channel_mention_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_mention_dati_list_to_json(str, len, (struct discord_channel_mention_dati **)p);
}


void discord_channel_mention_dati_cleanup(struct discord_channel_mention_dati *d) {
  /* specs/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->guild_id is a scalar
  /* specs/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types_code" }}'
  */
  //p->type is a scalar
  /* specs/channel.objects.json:68:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->name)
    free(d->name);
}

void discord_channel_mention_dati_init(struct discord_channel_mention_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_mention_dati));
  /* specs/channel.objects.json:65:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:66:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:67:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types_code" }}'
  */

  /* specs/channel.objects.json:68:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */

}
struct discord_channel_mention_dati* discord_channel_mention_dati_alloc() {
  struct discord_channel_mention_dati *p= (struct discord_channel_mention_dati*)malloc(sizeof(struct discord_channel_mention_dati));
  discord_channel_mention_dati_init(p);
  return p;
}

void discord_channel_mention_dati_free(struct discord_channel_mention_dati *p) {
  discord_channel_mention_dati_cleanup(p);
  free(p);
}

void discord_channel_mention_dati_list_free(struct discord_channel_mention_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_mention_dati_cleanup);
}

void discord_channel_mention_dati_list_from_json(char *str, size_t len, struct discord_channel_mention_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_mention_dati);
  d.init_elem = discord_channel_mention_dati_init_v;
  d.elem_from_buf = discord_channel_mention_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_mention_dati_list_to_json(char *str, size_t len, struct discord_channel_mention_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_mention_dati_to_json_v);
}


void discord_channel_allowed_mentions_dati_from_json(char *json, size_t len, struct discord_channel_allowed_mentions_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                "(parse):F,"
  /* specs/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(roles):F,"
  /* specs/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(users):F,"
  /* specs/channel.objects.json:81:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                "(replied_user):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                ja_str_list_from_json, &p->parse,
  /* specs/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_from_json, &p->roles,
  /* specs/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_from_json, &p->users,
  /* specs/channel.objects.json:81:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                &p->replied_user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_allowed_mentions_dati_use_default_inject_settings(struct discord_channel_allowed_mentions_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  p->__M.arg_switches[0] = p->parse;

  /* specs/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  p->__M.arg_switches[1] = p->roles;

  /* specs/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  p->__M.arg_switches[2] = p->users;

  /* specs/channel.objects.json:81:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[3] = &p->replied_user;

}

size_t discord_channel_allowed_mentions_dati_to_json(char *json, size_t len, struct discord_channel_allowed_mentions_dati *p)
{
  size_t r;
  discord_channel_allowed_mentions_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                "(parse):F,"
  /* specs/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(roles):F,"
  /* specs/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(users):F,"
  /* specs/channel.objects.json:81:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                "(replied_user):b,"
                "@arg_switches:b",
  /* specs/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                ja_str_list_to_json, p->parse,
  /* specs/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_to_json, p->roles,
  /* specs/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_to_json, p->users,
  /* specs/channel.objects.json:81:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                &p->replied_user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_allowed_mentions_dati_cleanup_v(void *p) {
  discord_channel_allowed_mentions_dati_cleanup((struct discord_channel_allowed_mentions_dati *)p);
}

void discord_channel_allowed_mentions_dati_init_v(void *p) {
  discord_channel_allowed_mentions_dati_init((struct discord_channel_allowed_mentions_dati *)p);
}

void discord_channel_allowed_mentions_dati_free_v(void *p) {
 discord_channel_allowed_mentions_dati_free((struct discord_channel_allowed_mentions_dati *)p);
};

void discord_channel_allowed_mentions_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_allowed_mentions_dati_from_json(json, len, (struct discord_channel_allowed_mentions_dati*)p);
}

size_t discord_channel_allowed_mentions_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_allowed_mentions_dati_to_json(json, len, (struct discord_channel_allowed_mentions_dati*)p);
}

void discord_channel_allowed_mentions_dati_list_free_v(void **p) {
  discord_channel_allowed_mentions_dati_list_free((struct discord_channel_allowed_mentions_dati**)p);
}

void discord_channel_allowed_mentions_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_allowed_mentions_dati_list_from_json(str, len, (struct discord_channel_allowed_mentions_dati ***)p);
}

size_t discord_channel_allowed_mentions_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_allowed_mentions_dati_list_to_json(str, len, (struct discord_channel_allowed_mentions_dati **)p);
}


void discord_channel_allowed_mentions_dati_cleanup(struct discord_channel_allowed_mentions_dati *d) {
  /* specs/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  if (d->parse)
    ja_str_list_free(d->parse);
  /* specs/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  if (d->users)
    ja_u64_list_free(d->users);
  /* specs/channel.objects.json:81:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
  //p->replied_user is a scalar
}

void discord_channel_allowed_mentions_dati_init(struct discord_channel_allowed_mentions_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_allowed_mentions_dati));
  /* specs/channel.objects.json:78:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */

  /* specs/channel.objects.json:79:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */

  /* specs/channel.objects.json:80:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */

  /* specs/channel.objects.json:81:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */

}
struct discord_channel_allowed_mentions_dati* discord_channel_allowed_mentions_dati_alloc() {
  struct discord_channel_allowed_mentions_dati *p= (struct discord_channel_allowed_mentions_dati*)malloc(sizeof(struct discord_channel_allowed_mentions_dati));
  discord_channel_allowed_mentions_dati_init(p);
  return p;
}

void discord_channel_allowed_mentions_dati_free(struct discord_channel_allowed_mentions_dati *p) {
  discord_channel_allowed_mentions_dati_cleanup(p);
  free(p);
}

void discord_channel_allowed_mentions_dati_list_free(struct discord_channel_allowed_mentions_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_allowed_mentions_dati_cleanup);
}

void discord_channel_allowed_mentions_dati_list_from_json(char *str, size_t len, struct discord_channel_allowed_mentions_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_allowed_mentions_dati);
  d.init_elem = discord_channel_allowed_mentions_dati_init_v;
  d.elem_from_buf = discord_channel_allowed_mentions_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_allowed_mentions_dati_list_to_json(char *str, size_t len, struct discord_channel_allowed_mentions_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_allowed_mentions_dati_to_json_v);
}


void discord_channel_embed_dati_from_json(char *json, size_t len, struct discord_channel_embed_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:91:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(title):s,"
  /* specs/channel.objects.json:93:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(type):s,"
  /* specs/channel.objects.json:95:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(description):s,"
  /* specs/channel.objects.json:97:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:99:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                "(timestamp):F,"
  /* specs/channel.objects.json:101:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/channel.objects.json:102:20
     '{ "name": "footer", "type":{ "base":"struct discord_channel_embed_footer_dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(footer):F,"
  /* specs/channel.objects.json:104:20
     '{ "name": "image", "type":{ "base":"struct discord_channel_embed_image_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(image):F,"
  /* specs/channel.objects.json:105:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_channel_embed_thumbnail_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(thumbnail):F,"
  /* specs/channel.objects.json:106:20
     '{ "name": "video", "type":{ "base":"struct discord_channel_embed_video_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(video):F,"
  /* specs/channel.objects.json:107:20
     '{ "name": "provider", "type":{ "base":"struct discord_channel_embed_provider_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(provider):F,"
  /* specs/channel.objects.json:108:20
     '{ "name": "author", "type":{ "base":"struct discord_channel_embed_author_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(author):F,"
  /* specs/channel.objects.json:109:20
     '{ "name": "fields", "type":{ "base":"struct discord_channel_embed_field_dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                "(fields):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:91:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->title,
  /* specs/channel.objects.json:93:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->type,
  /* specs/channel.objects.json:95:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->description,
  /* specs/channel.objects.json:97:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:99:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                orka_iso8601_to_unix_ms, &p->timestamp,
  /* specs/channel.objects.json:101:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                &p->color,
  /* specs/channel.objects.json:102:20
     '{ "name": "footer", "type":{ "base":"struct discord_channel_embed_footer_dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                discord_channel_embed_footer_dati_from_json, p->footer,
  /* specs/channel.objects.json:104:20
     '{ "name": "image", "type":{ "base":"struct discord_channel_embed_image_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_image_dati_from_json, p->image,
  /* specs/channel.objects.json:105:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_channel_embed_thumbnail_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_thumbnail_dati_from_json, p->thumbnail,
  /* specs/channel.objects.json:106:20
     '{ "name": "video", "type":{ "base":"struct discord_channel_embed_video_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_video_dati_from_json, p->video,
  /* specs/channel.objects.json:107:20
     '{ "name": "provider", "type":{ "base":"struct discord_channel_embed_provider_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_provider_dati_from_json, p->provider,
  /* specs/channel.objects.json:108:20
     '{ "name": "author", "type":{ "base":"struct discord_channel_embed_author_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_author_dati_from_json, p->author,
  /* specs/channel.objects.json:109:20
     '{ "name": "fields", "type":{ "base":"struct discord_channel_embed_field_dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                discord_channel_embed_field_dati_list_from_json, &p->fields,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_embed_dati_use_default_inject_settings(struct discord_channel_embed_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:91:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->title) != 0)
    p->__M.arg_switches[0] = p->title;

  /* specs/channel.objects.json:93:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->type) != 0)
    p->__M.arg_switches[1] = p->type;

  /* specs/channel.objects.json:95:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->description) != 0)
    p->__M.arg_switches[2] = p->description;

  /* specs/channel.objects.json:97:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[3] = p->url;

  /* specs/channel.objects.json:99:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  if (p->timestamp != 0)
    p->__M.arg_switches[4] = &p->timestamp;

  /* specs/channel.objects.json:101:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  if (p->color != 0)
    p->__M.arg_switches[5] = &p->color;

  /* specs/channel.objects.json:102:20
     '{ "name": "footer", "type":{ "base":"struct discord_channel_embed_footer_dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (p->footer != NULL)
    p->__M.arg_switches[6] = p->footer;

  /* specs/channel.objects.json:104:20
     '{ "name": "image", "type":{ "base":"struct discord_channel_embed_image_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->image != NULL)
    p->__M.arg_switches[7] = p->image;

  /* specs/channel.objects.json:105:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_channel_embed_thumbnail_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->thumbnail != NULL)
    p->__M.arg_switches[8] = p->thumbnail;

  /* specs/channel.objects.json:106:20
     '{ "name": "video", "type":{ "base":"struct discord_channel_embed_video_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->video != NULL)
    p->__M.arg_switches[9] = p->video;

  /* specs/channel.objects.json:107:20
     '{ "name": "provider", "type":{ "base":"struct discord_channel_embed_provider_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->provider != NULL)
    p->__M.arg_switches[10] = p->provider;

  /* specs/channel.objects.json:108:20
     '{ "name": "author", "type":{ "base":"struct discord_channel_embed_author_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->author != NULL)
    p->__M.arg_switches[11] = p->author;

  /* specs/channel.objects.json:109:20
     '{ "name": "fields", "type":{ "base":"struct discord_channel_embed_field_dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  if (p->fields != NULL)
    p->__M.arg_switches[12] = p->fields;

}

size_t discord_channel_embed_dati_to_json(char *json, size_t len, struct discord_channel_embed_dati *p)
{
  size_t r;
  discord_channel_embed_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:91:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(title):s,"
  /* specs/channel.objects.json:93:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(type):s,"
  /* specs/channel.objects.json:95:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(description):s,"
  /* specs/channel.objects.json:97:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:99:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                "(timestamp):|F|,"
  /* specs/channel.objects.json:101:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/channel.objects.json:102:20
     '{ "name": "footer", "type":{ "base":"struct discord_channel_embed_footer_dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(footer):F,"
  /* specs/channel.objects.json:104:20
     '{ "name": "image", "type":{ "base":"struct discord_channel_embed_image_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(image):F,"
  /* specs/channel.objects.json:105:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_channel_embed_thumbnail_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(thumbnail):F,"
  /* specs/channel.objects.json:106:20
     '{ "name": "video", "type":{ "base":"struct discord_channel_embed_video_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(video):F,"
  /* specs/channel.objects.json:107:20
     '{ "name": "provider", "type":{ "base":"struct discord_channel_embed_provider_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(provider):F,"
  /* specs/channel.objects.json:108:20
     '{ "name": "author", "type":{ "base":"struct discord_channel_embed_author_dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(author):F,"
  /* specs/channel.objects.json:109:20
     '{ "name": "fields", "type":{ "base":"struct discord_channel_embed_field_dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                "(fields):F,"
                "@arg_switches:b",
  /* specs/channel.objects.json:91:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->title,
  /* specs/channel.objects.json:93:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->type,
  /* specs/channel.objects.json:95:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->description,
  /* specs/channel.objects.json:97:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:99:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                orka_unix_ms_to_iso8601, &p->timestamp,
  /* specs/channel.objects.json:101:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                &p->color,
  /* specs/channel.objects.json:102:20
     '{ "name": "footer", "type":{ "base":"struct discord_channel_embed_footer_dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                discord_channel_embed_footer_dati_to_json, p->footer,
  /* specs/channel.objects.json:104:20
     '{ "name": "image", "type":{ "base":"struct discord_channel_embed_image_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_image_dati_to_json, p->image,
  /* specs/channel.objects.json:105:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_channel_embed_thumbnail_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_thumbnail_dati_to_json, p->thumbnail,
  /* specs/channel.objects.json:106:20
     '{ "name": "video", "type":{ "base":"struct discord_channel_embed_video_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_video_dati_to_json, p->video,
  /* specs/channel.objects.json:107:20
     '{ "name": "provider", "type":{ "base":"struct discord_channel_embed_provider_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_provider_dati_to_json, p->provider,
  /* specs/channel.objects.json:108:20
     '{ "name": "author", "type":{ "base":"struct discord_channel_embed_author_dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord_channel_embed_author_dati_to_json, p->author,
  /* specs/channel.objects.json:109:20
     '{ "name": "fields", "type":{ "base":"struct discord_channel_embed_field_dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                discord_channel_embed_field_dati_list_to_json, p->fields,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_embed_dati_cleanup_v(void *p) {
  discord_channel_embed_dati_cleanup((struct discord_channel_embed_dati *)p);
}

void discord_channel_embed_dati_init_v(void *p) {
  discord_channel_embed_dati_init((struct discord_channel_embed_dati *)p);
}

void discord_channel_embed_dati_free_v(void *p) {
 discord_channel_embed_dati_free((struct discord_channel_embed_dati *)p);
};

void discord_channel_embed_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_embed_dati_from_json(json, len, (struct discord_channel_embed_dati*)p);
}

size_t discord_channel_embed_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_embed_dati_to_json(json, len, (struct discord_channel_embed_dati*)p);
}

void discord_channel_embed_dati_list_free_v(void **p) {
  discord_channel_embed_dati_list_free((struct discord_channel_embed_dati**)p);
}

void discord_channel_embed_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_embed_dati_list_from_json(str, len, (struct discord_channel_embed_dati ***)p);
}

size_t discord_channel_embed_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_embed_dati_list_to_json(str, len, (struct discord_channel_embed_dati **)p);
}


void discord_channel_embed_dati_cleanup(struct discord_channel_embed_dati *d) {
  /* specs/channel.objects.json:91:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  //p->title is a scalar
  /* specs/channel.objects.json:93:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  //p->type is a scalar
  /* specs/channel.objects.json:95:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  //p->description is a scalar
  /* specs/channel.objects.json:97:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:99:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  //p->timestamp is a scalar
  /* specs/channel.objects.json:101:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  //p->color is a scalar
  /* specs/channel.objects.json:102:20
     '{ "name": "footer", "type":{ "base":"struct discord_channel_embed_footer_dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (d->footer)
    discord_channel_embed_footer_dati_free(d->footer);
  /* specs/channel.objects.json:104:20
     '{ "name": "image", "type":{ "base":"struct discord_channel_embed_image_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->image)
    discord_channel_embed_image_dati_free(d->image);
  /* specs/channel.objects.json:105:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_channel_embed_thumbnail_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->thumbnail)
    discord_channel_embed_thumbnail_dati_free(d->thumbnail);
  /* specs/channel.objects.json:106:20
     '{ "name": "video", "type":{ "base":"struct discord_channel_embed_video_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->video)
    discord_channel_embed_video_dati_free(d->video);
  /* specs/channel.objects.json:107:20
     '{ "name": "provider", "type":{ "base":"struct discord_channel_embed_provider_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->provider)
    discord_channel_embed_provider_dati_free(d->provider);
  /* specs/channel.objects.json:108:20
     '{ "name": "author", "type":{ "base":"struct discord_channel_embed_author_dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->author)
    discord_channel_embed_author_dati_free(d->author);
  /* specs/channel.objects.json:109:20
     '{ "name": "fields", "type":{ "base":"struct discord_channel_embed_field_dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  if (d->fields)
    discord_channel_embed_field_dati_list_free(d->fields);
}

void discord_channel_embed_dati_init(struct discord_channel_embed_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_embed_dati));
  /* specs/channel.objects.json:91:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:93:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:95:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:97:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:99:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */

  /* specs/channel.objects.json:101:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */

  /* specs/channel.objects.json:102:20
     '{ "name": "footer", "type":{ "base":"struct discord_channel_embed_footer_dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  p->footer = discord_channel_embed_footer_dati_alloc();

  /* specs/channel.objects.json:104:20
     '{ "name": "image", "type":{ "base":"struct discord_channel_embed_image_dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->image = discord_channel_embed_image_dati_alloc();

  /* specs/channel.objects.json:105:20
     '{ "name": "thumbnail", "type":{ "base":"struct discord_channel_embed_thumbnail_dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->thumbnail = discord_channel_embed_thumbnail_dati_alloc();

  /* specs/channel.objects.json:106:20
     '{ "name": "video", "type":{ "base":"struct discord_channel_embed_video_dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->video = discord_channel_embed_video_dati_alloc();

  /* specs/channel.objects.json:107:20
     '{ "name": "provider", "type":{ "base":"struct discord_channel_embed_provider_dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->provider = discord_channel_embed_provider_dati_alloc();

  /* specs/channel.objects.json:108:20
     '{ "name": "author", "type":{ "base":"struct discord_channel_embed_author_dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->author = discord_channel_embed_author_dati_alloc();

  /* specs/channel.objects.json:109:20
     '{ "name": "fields", "type":{ "base":"struct discord_channel_embed_field_dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */

}
struct discord_channel_embed_dati* discord_channel_embed_dati_alloc() {
  struct discord_channel_embed_dati *p= (struct discord_channel_embed_dati*)malloc(sizeof(struct discord_channel_embed_dati));
  discord_channel_embed_dati_init(p);
  return p;
}

void discord_channel_embed_dati_free(struct discord_channel_embed_dati *p) {
  discord_channel_embed_dati_cleanup(p);
  free(p);
}

void discord_channel_embed_dati_list_free(struct discord_channel_embed_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_embed_dati_cleanup);
}

void discord_channel_embed_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_embed_dati);
  d.init_elem = discord_channel_embed_dati_init_v;
  d.elem_from_buf = discord_channel_embed_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_embed_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_embed_dati_to_json_v);
}


void discord_channel_embed_thumbnail_dati_from_json(char *json, size_t len, struct discord_channel_embed_thumbnail_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_embed_thumbnail_dati_use_default_inject_settings(struct discord_channel_embed_thumbnail_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[0] = p->url;

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->proxy_url) != 0)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_channel_embed_thumbnail_dati_to_json(char *json, size_t len, struct discord_channel_embed_thumbnail_dati *p)
{
  size_t r;
  discord_channel_embed_thumbnail_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_embed_thumbnail_dati_cleanup_v(void *p) {
  discord_channel_embed_thumbnail_dati_cleanup((struct discord_channel_embed_thumbnail_dati *)p);
}

void discord_channel_embed_thumbnail_dati_init_v(void *p) {
  discord_channel_embed_thumbnail_dati_init((struct discord_channel_embed_thumbnail_dati *)p);
}

void discord_channel_embed_thumbnail_dati_free_v(void *p) {
 discord_channel_embed_thumbnail_dati_free((struct discord_channel_embed_thumbnail_dati *)p);
};

void discord_channel_embed_thumbnail_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_embed_thumbnail_dati_from_json(json, len, (struct discord_channel_embed_thumbnail_dati*)p);
}

size_t discord_channel_embed_thumbnail_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_embed_thumbnail_dati_to_json(json, len, (struct discord_channel_embed_thumbnail_dati*)p);
}

void discord_channel_embed_thumbnail_dati_list_free_v(void **p) {
  discord_channel_embed_thumbnail_dati_list_free((struct discord_channel_embed_thumbnail_dati**)p);
}

void discord_channel_embed_thumbnail_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_embed_thumbnail_dati_list_from_json(str, len, (struct discord_channel_embed_thumbnail_dati ***)p);
}

size_t discord_channel_embed_thumbnail_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_embed_thumbnail_dati_list_to_json(str, len, (struct discord_channel_embed_thumbnail_dati **)p);
}


void discord_channel_embed_thumbnail_dati_cleanup(struct discord_channel_embed_thumbnail_dati *d) {
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->proxy_url is a scalar
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->height is a scalar
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->width is a scalar
}

void discord_channel_embed_thumbnail_dati_init(struct discord_channel_embed_thumbnail_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_embed_thumbnail_dati));
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */

}
struct discord_channel_embed_thumbnail_dati* discord_channel_embed_thumbnail_dati_alloc() {
  struct discord_channel_embed_thumbnail_dati *p= (struct discord_channel_embed_thumbnail_dati*)malloc(sizeof(struct discord_channel_embed_thumbnail_dati));
  discord_channel_embed_thumbnail_dati_init(p);
  return p;
}

void discord_channel_embed_thumbnail_dati_free(struct discord_channel_embed_thumbnail_dati *p) {
  discord_channel_embed_thumbnail_dati_cleanup(p);
  free(p);
}

void discord_channel_embed_thumbnail_dati_list_free(struct discord_channel_embed_thumbnail_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_embed_thumbnail_dati_cleanup);
}

void discord_channel_embed_thumbnail_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_thumbnail_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_embed_thumbnail_dati);
  d.init_elem = discord_channel_embed_thumbnail_dati_init_v;
  d.elem_from_buf = discord_channel_embed_thumbnail_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_embed_thumbnail_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_thumbnail_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_embed_thumbnail_dati_to_json_v);
}


void discord_channel_embed_video_dati_from_json(char *json, size_t len, struct discord_channel_embed_video_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_embed_video_dati_use_default_inject_settings(struct discord_channel_embed_video_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[0] = p->url;

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->proxy_url) != 0)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_channel_embed_video_dati_to_json(char *json, size_t len, struct discord_channel_embed_video_dati *p)
{
  size_t r;
  discord_channel_embed_video_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_embed_video_dati_cleanup_v(void *p) {
  discord_channel_embed_video_dati_cleanup((struct discord_channel_embed_video_dati *)p);
}

void discord_channel_embed_video_dati_init_v(void *p) {
  discord_channel_embed_video_dati_init((struct discord_channel_embed_video_dati *)p);
}

void discord_channel_embed_video_dati_free_v(void *p) {
 discord_channel_embed_video_dati_free((struct discord_channel_embed_video_dati *)p);
};

void discord_channel_embed_video_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_embed_video_dati_from_json(json, len, (struct discord_channel_embed_video_dati*)p);
}

size_t discord_channel_embed_video_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_embed_video_dati_to_json(json, len, (struct discord_channel_embed_video_dati*)p);
}

void discord_channel_embed_video_dati_list_free_v(void **p) {
  discord_channel_embed_video_dati_list_free((struct discord_channel_embed_video_dati**)p);
}

void discord_channel_embed_video_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_embed_video_dati_list_from_json(str, len, (struct discord_channel_embed_video_dati ***)p);
}

size_t discord_channel_embed_video_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_embed_video_dati_list_to_json(str, len, (struct discord_channel_embed_video_dati **)p);
}


void discord_channel_embed_video_dati_cleanup(struct discord_channel_embed_video_dati *d) {
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->proxy_url is a scalar
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->height is a scalar
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->width is a scalar
}

void discord_channel_embed_video_dati_init(struct discord_channel_embed_video_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_embed_video_dati));
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */

}
struct discord_channel_embed_video_dati* discord_channel_embed_video_dati_alloc() {
  struct discord_channel_embed_video_dati *p= (struct discord_channel_embed_video_dati*)malloc(sizeof(struct discord_channel_embed_video_dati));
  discord_channel_embed_video_dati_init(p);
  return p;
}

void discord_channel_embed_video_dati_free(struct discord_channel_embed_video_dati *p) {
  discord_channel_embed_video_dati_cleanup(p);
  free(p);
}

void discord_channel_embed_video_dati_list_free(struct discord_channel_embed_video_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_embed_video_dati_cleanup);
}

void discord_channel_embed_video_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_video_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_embed_video_dati);
  d.init_elem = discord_channel_embed_video_dati_init_v;
  d.elem_from_buf = discord_channel_embed_video_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_embed_video_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_video_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_embed_video_dati_to_json_v);
}


void discord_channel_embed_image_dati_from_json(char *json, size_t len, struct discord_channel_embed_image_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_embed_image_dati_use_default_inject_settings(struct discord_channel_embed_image_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[0] = p->url;

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->proxy_url) != 0)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

}

size_t discord_channel_embed_image_dati_to_json(char *json, size_t len, struct discord_channel_embed_image_dati *p)
{
  size_t r;
  discord_channel_embed_image_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_embed_image_dati_cleanup_v(void *p) {
  discord_channel_embed_image_dati_cleanup((struct discord_channel_embed_image_dati *)p);
}

void discord_channel_embed_image_dati_init_v(void *p) {
  discord_channel_embed_image_dati_init((struct discord_channel_embed_image_dati *)p);
}

void discord_channel_embed_image_dati_free_v(void *p) {
 discord_channel_embed_image_dati_free((struct discord_channel_embed_image_dati *)p);
};

void discord_channel_embed_image_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_embed_image_dati_from_json(json, len, (struct discord_channel_embed_image_dati*)p);
}

size_t discord_channel_embed_image_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_embed_image_dati_to_json(json, len, (struct discord_channel_embed_image_dati*)p);
}

void discord_channel_embed_image_dati_list_free_v(void **p) {
  discord_channel_embed_image_dati_list_free((struct discord_channel_embed_image_dati**)p);
}

void discord_channel_embed_image_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_embed_image_dati_list_from_json(str, len, (struct discord_channel_embed_image_dati ***)p);
}

size_t discord_channel_embed_image_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_embed_image_dati_list_to_json(str, len, (struct discord_channel_embed_image_dati **)p);
}


void discord_channel_embed_image_dati_cleanup(struct discord_channel_embed_image_dati *d) {
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->proxy_url is a scalar
  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->height is a scalar
  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->width is a scalar
}

void discord_channel_embed_image_dati_init(struct discord_channel_embed_image_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_embed_image_dati));
  /* specs/channel.objects.json:121:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:122:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:123:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/channel.objects.json:124:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */

}
struct discord_channel_embed_image_dati* discord_channel_embed_image_dati_alloc() {
  struct discord_channel_embed_image_dati *p= (struct discord_channel_embed_image_dati*)malloc(sizeof(struct discord_channel_embed_image_dati));
  discord_channel_embed_image_dati_init(p);
  return p;
}

void discord_channel_embed_image_dati_free(struct discord_channel_embed_image_dati *p) {
  discord_channel_embed_image_dati_cleanup(p);
  free(p);
}

void discord_channel_embed_image_dati_list_free(struct discord_channel_embed_image_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_embed_image_dati_cleanup);
}

void discord_channel_embed_image_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_image_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_embed_image_dati);
  d.init_elem = discord_channel_embed_image_dati_init_v;
  d.elem_from_buf = discord_channel_embed_image_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_embed_image_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_image_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_embed_image_dati_to_json_v);
}


void discord_channel_embed_provider_dati_from_json(char *json, size_t len, struct discord_channel_embed_provider_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:133:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:134:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
                "(url):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:133:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:134:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
                p->url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_embed_provider_dati_use_default_inject_settings(struct discord_channel_embed_provider_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:133:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/channel.objects.json:134:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[1] = p->url;

}

size_t discord_channel_embed_provider_dati_to_json(char *json, size_t len, struct discord_channel_embed_provider_dati *p)
{
  size_t r;
  discord_channel_embed_provider_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:133:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:134:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
                "(url):s,"
                "@arg_switches:b",
  /* specs/channel.objects.json:133:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:134:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
                p->url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_embed_provider_dati_cleanup_v(void *p) {
  discord_channel_embed_provider_dati_cleanup((struct discord_channel_embed_provider_dati *)p);
}

void discord_channel_embed_provider_dati_init_v(void *p) {
  discord_channel_embed_provider_dati_init((struct discord_channel_embed_provider_dati *)p);
}

void discord_channel_embed_provider_dati_free_v(void *p) {
 discord_channel_embed_provider_dati_free((struct discord_channel_embed_provider_dati *)p);
};

void discord_channel_embed_provider_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_embed_provider_dati_from_json(json, len, (struct discord_channel_embed_provider_dati*)p);
}

size_t discord_channel_embed_provider_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_embed_provider_dati_to_json(json, len, (struct discord_channel_embed_provider_dati*)p);
}

void discord_channel_embed_provider_dati_list_free_v(void **p) {
  discord_channel_embed_provider_dati_list_free((struct discord_channel_embed_provider_dati**)p);
}

void discord_channel_embed_provider_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_embed_provider_dati_list_from_json(str, len, (struct discord_channel_embed_provider_dati ***)p);
}

size_t discord_channel_embed_provider_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_embed_provider_dati_list_to_json(str, len, (struct discord_channel_embed_provider_dati **)p);
}


void discord_channel_embed_provider_dati_cleanup(struct discord_channel_embed_provider_dati *d) {
  /* specs/channel.objects.json:133:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/channel.objects.json:134:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
  //p->url is a scalar
}

void discord_channel_embed_provider_dati_init(struct discord_channel_embed_provider_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_embed_provider_dati));
  /* specs/channel.objects.json:133:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:134:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */

}
struct discord_channel_embed_provider_dati* discord_channel_embed_provider_dati_alloc() {
  struct discord_channel_embed_provider_dati *p= (struct discord_channel_embed_provider_dati*)malloc(sizeof(struct discord_channel_embed_provider_dati));
  discord_channel_embed_provider_dati_init(p);
  return p;
}

void discord_channel_embed_provider_dati_free(struct discord_channel_embed_provider_dati *p) {
  discord_channel_embed_provider_dati_cleanup(p);
  free(p);
}

void discord_channel_embed_provider_dati_list_free(struct discord_channel_embed_provider_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_embed_provider_dati_cleanup);
}

void discord_channel_embed_provider_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_provider_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_embed_provider_dati);
  d.init_elem = discord_channel_embed_provider_dati_init_v;
  d.elem_from_buf = discord_channel_embed_provider_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_embed_provider_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_provider_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_embed_provider_dati_to_json_v);
}


void discord_channel_embed_author_dati_from_json(char *json, size_t len, struct discord_channel_embed_author_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:143:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:144:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:145:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/channel.objects.json:146:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:143:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:144:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:145:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/channel.objects.json:146:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_embed_author_dati_use_default_inject_settings(struct discord_channel_embed_author_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:143:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/channel.objects.json:144:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[1] = p->url;

  /* specs/channel.objects.json:145:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->icon_url) != 0)
    p->__M.arg_switches[2] = p->icon_url;

  /* specs/channel.objects.json:146:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->proxy_icon_url) != 0)
    p->__M.arg_switches[3] = p->proxy_icon_url;

}

size_t discord_channel_embed_author_dati_to_json(char *json, size_t len, struct discord_channel_embed_author_dati *p)
{
  size_t r;
  discord_channel_embed_author_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:143:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:144:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:145:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/channel.objects.json:146:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* specs/channel.objects.json:143:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:144:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:145:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/channel.objects.json:146:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_embed_author_dati_cleanup_v(void *p) {
  discord_channel_embed_author_dati_cleanup((struct discord_channel_embed_author_dati *)p);
}

void discord_channel_embed_author_dati_init_v(void *p) {
  discord_channel_embed_author_dati_init((struct discord_channel_embed_author_dati *)p);
}

void discord_channel_embed_author_dati_free_v(void *p) {
 discord_channel_embed_author_dati_free((struct discord_channel_embed_author_dati *)p);
};

void discord_channel_embed_author_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_embed_author_dati_from_json(json, len, (struct discord_channel_embed_author_dati*)p);
}

size_t discord_channel_embed_author_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_embed_author_dati_to_json(json, len, (struct discord_channel_embed_author_dati*)p);
}

void discord_channel_embed_author_dati_list_free_v(void **p) {
  discord_channel_embed_author_dati_list_free((struct discord_channel_embed_author_dati**)p);
}

void discord_channel_embed_author_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_embed_author_dati_list_from_json(str, len, (struct discord_channel_embed_author_dati ***)p);
}

size_t discord_channel_embed_author_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_embed_author_dati_list_to_json(str, len, (struct discord_channel_embed_author_dati **)p);
}


void discord_channel_embed_author_dati_cleanup(struct discord_channel_embed_author_dati *d) {
  /* specs/channel.objects.json:143:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/channel.objects.json:144:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:145:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->icon_url is a scalar
  /* specs/channel.objects.json:146:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->proxy_icon_url is a scalar
}

void discord_channel_embed_author_dati_init(struct discord_channel_embed_author_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_embed_author_dati));
  /* specs/channel.objects.json:143:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:144:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:145:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:146:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

}
struct discord_channel_embed_author_dati* discord_channel_embed_author_dati_alloc() {
  struct discord_channel_embed_author_dati *p= (struct discord_channel_embed_author_dati*)malloc(sizeof(struct discord_channel_embed_author_dati));
  discord_channel_embed_author_dati_init(p);
  return p;
}

void discord_channel_embed_author_dati_free(struct discord_channel_embed_author_dati *p) {
  discord_channel_embed_author_dati_cleanup(p);
  free(p);
}

void discord_channel_embed_author_dati_list_free(struct discord_channel_embed_author_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_embed_author_dati_cleanup);
}

void discord_channel_embed_author_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_author_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_embed_author_dati);
  d.init_elem = discord_channel_embed_author_dati_init_v;
  d.elem_from_buf = discord_channel_embed_author_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_embed_author_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_author_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_embed_author_dati_to_json_v);
}


void discord_channel_embed_footer_dati_from_json(char *json, size_t len, struct discord_channel_embed_footer_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:155:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                "(text):s,"
  /* specs/channel.objects.json:156:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/channel.objects.json:158:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:155:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                p->text,
  /* specs/channel.objects.json:156:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/channel.objects.json:158:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_embed_footer_dati_use_default_inject_settings(struct discord_channel_embed_footer_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:155:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  if (strlen(p->text) != 0)
    p->__M.arg_switches[0] = p->text;

  /* specs/channel.objects.json:156:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->icon_url) != 0)
    p->__M.arg_switches[1] = p->icon_url;

  /* specs/channel.objects.json:158:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->proxy_icon_url) != 0)
    p->__M.arg_switches[2] = p->proxy_icon_url;

}

size_t discord_channel_embed_footer_dati_to_json(char *json, size_t len, struct discord_channel_embed_footer_dati *p)
{
  size_t r;
  discord_channel_embed_footer_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:155:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                "(text):s,"
  /* specs/channel.objects.json:156:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/channel.objects.json:158:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* specs/channel.objects.json:155:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                p->text,
  /* specs/channel.objects.json:156:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/channel.objects.json:158:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_embed_footer_dati_cleanup_v(void *p) {
  discord_channel_embed_footer_dati_cleanup((struct discord_channel_embed_footer_dati *)p);
}

void discord_channel_embed_footer_dati_init_v(void *p) {
  discord_channel_embed_footer_dati_init((struct discord_channel_embed_footer_dati *)p);
}

void discord_channel_embed_footer_dati_free_v(void *p) {
 discord_channel_embed_footer_dati_free((struct discord_channel_embed_footer_dati *)p);
};

void discord_channel_embed_footer_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_embed_footer_dati_from_json(json, len, (struct discord_channel_embed_footer_dati*)p);
}

size_t discord_channel_embed_footer_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_embed_footer_dati_to_json(json, len, (struct discord_channel_embed_footer_dati*)p);
}

void discord_channel_embed_footer_dati_list_free_v(void **p) {
  discord_channel_embed_footer_dati_list_free((struct discord_channel_embed_footer_dati**)p);
}

void discord_channel_embed_footer_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_embed_footer_dati_list_from_json(str, len, (struct discord_channel_embed_footer_dati ***)p);
}

size_t discord_channel_embed_footer_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_embed_footer_dati_list_to_json(str, len, (struct discord_channel_embed_footer_dati **)p);
}


void discord_channel_embed_footer_dati_cleanup(struct discord_channel_embed_footer_dati *d) {
  /* specs/channel.objects.json:155:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  //p->text is a scalar
  /* specs/channel.objects.json:156:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  //p->icon_url is a scalar
  /* specs/channel.objects.json:158:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  //p->proxy_icon_url is a scalar
}

void discord_channel_embed_footer_dati_init(struct discord_channel_embed_footer_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_embed_footer_dati));
  /* specs/channel.objects.json:155:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:156:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:158:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */

}
struct discord_channel_embed_footer_dati* discord_channel_embed_footer_dati_alloc() {
  struct discord_channel_embed_footer_dati *p= (struct discord_channel_embed_footer_dati*)malloc(sizeof(struct discord_channel_embed_footer_dati));
  discord_channel_embed_footer_dati_init(p);
  return p;
}

void discord_channel_embed_footer_dati_free(struct discord_channel_embed_footer_dati *p) {
  discord_channel_embed_footer_dati_cleanup(p);
  free(p);
}

void discord_channel_embed_footer_dati_list_free(struct discord_channel_embed_footer_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_embed_footer_dati_cleanup);
}

void discord_channel_embed_footer_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_footer_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_embed_footer_dati);
  d.init_elem = discord_channel_embed_footer_dati_init_v;
  d.elem_from_buf = discord_channel_embed_footer_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_embed_footer_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_footer_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_embed_footer_dati_to_json_v);
}


void discord_channel_embed_field_dati_from_json(char *json, size_t len, struct discord_channel_embed_field_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:168:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:169:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                "(value):s,"
  /* specs/channel.objects.json:170:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                "(inline):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:168:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:169:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                p->value,
  /* specs/channel.objects.json:170:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                &p->Inline,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_embed_field_dati_use_default_inject_settings(struct discord_channel_embed_field_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:168:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/channel.objects.json:169:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->value) != 0)
    p->__M.arg_switches[1] = p->value;

  /* specs/channel.objects.json:170:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
  p->__M.arg_switches[2] = &p->Inline;

}

size_t discord_channel_embed_field_dati_to_json(char *json, size_t len, struct discord_channel_embed_field_dati *p)
{
  size_t r;
  discord_channel_embed_field_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.objects.json:168:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:169:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                "(value):s,"
  /* specs/channel.objects.json:170:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                "(inline):b,"
                "@arg_switches:b",
  /* specs/channel.objects.json:168:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:169:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                p->value,
  /* specs/channel.objects.json:170:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                &p->Inline,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_embed_field_dati_cleanup_v(void *p) {
  discord_channel_embed_field_dati_cleanup((struct discord_channel_embed_field_dati *)p);
}

void discord_channel_embed_field_dati_init_v(void *p) {
  discord_channel_embed_field_dati_init((struct discord_channel_embed_field_dati *)p);
}

void discord_channel_embed_field_dati_free_v(void *p) {
 discord_channel_embed_field_dati_free((struct discord_channel_embed_field_dati *)p);
};

void discord_channel_embed_field_dati_from_json_v(char *json, size_t len, void *p) {
 discord_channel_embed_field_dati_from_json(json, len, (struct discord_channel_embed_field_dati*)p);
}

size_t discord_channel_embed_field_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_embed_field_dati_to_json(json, len, (struct discord_channel_embed_field_dati*)p);
}

void discord_channel_embed_field_dati_list_free_v(void **p) {
  discord_channel_embed_field_dati_list_free((struct discord_channel_embed_field_dati**)p);
}

void discord_channel_embed_field_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_embed_field_dati_list_from_json(str, len, (struct discord_channel_embed_field_dati ***)p);
}

size_t discord_channel_embed_field_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_embed_field_dati_list_to_json(str, len, (struct discord_channel_embed_field_dati **)p);
}


void discord_channel_embed_field_dati_cleanup(struct discord_channel_embed_field_dati *d) {
  /* specs/channel.objects.json:168:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/channel.objects.json:169:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  //p->value is a scalar
  /* specs/channel.objects.json:170:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
  //p->Inline is a scalar
}

void discord_channel_embed_field_dati_init(struct discord_channel_embed_field_dati *p) {
  memset(p, 0, sizeof(struct discord_channel_embed_field_dati));
  /* specs/channel.objects.json:168:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:169:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:170:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */

}
struct discord_channel_embed_field_dati* discord_channel_embed_field_dati_alloc() {
  struct discord_channel_embed_field_dati *p= (struct discord_channel_embed_field_dati*)malloc(sizeof(struct discord_channel_embed_field_dati));
  discord_channel_embed_field_dati_init(p);
  return p;
}

void discord_channel_embed_field_dati_free(struct discord_channel_embed_field_dati *p) {
  discord_channel_embed_field_dati_cleanup(p);
  free(p);
}

void discord_channel_embed_field_dati_list_free(struct discord_channel_embed_field_dati **p) {
  ntl_free((void**)p, (vfvp)discord_channel_embed_field_dati_cleanup);
}

void discord_channel_embed_field_dati_list_from_json(char *str, size_t len, struct discord_channel_embed_field_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_embed_field_dati);
  d.init_elem = discord_channel_embed_field_dati_init_v;
  d.elem_from_buf = discord_channel_embed_field_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_embed_field_dati_list_to_json(char *str, size_t len, struct discord_channel_embed_field_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_embed_field_dati_to_json_v);
}

