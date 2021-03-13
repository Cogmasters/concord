/* This file is generated from specs/channel.objects.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/
namespace discord {
namespace channel {

namespace overwrite {

/* This method is disabled at specs/channel.objects.json:9:30 */
void dati_from_json_disabled(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
                "(id):F,"
                "(type):d,"
                "(allow):s_as_u64,"
                "(deny):s_as_u64,"
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


/* This method is disabled at specs/channel.objects.json:9:30 */
size_t dati_to_json_disabled(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
                "(id):|F|,"
                "(type):d,"
                "(allow):s_as_u64,"
                "(deny):s_as_u64,"
                "@arg_switches:b",
                orka_ulltostr, &p->id,
                &p->type,
                &p->allow,
                &p->deny,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
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
     '{ "name": "allow", "type":{ "base":"s_as_u64"}, "comment":"permission bit set"}'
  */
  p->__M.arg_switches[2] = &p->allow;

  /* specs/channel.objects.json:16:20
     '{ "name": "deny", "type":{ "base":"s_as_u64"}, "comment":"permission bit set"}'
  */
  p->__M.arg_switches[3] = &p->deny;

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
  /* specs/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  //p->type is a scalar
  /* specs/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_u64"}, "comment":"permission bit set"}'
  */
  //p->allow is a scalar
  /* specs/channel.objects.json:16:20
     '{ "name": "deny", "type":{ "base":"s_as_u64"}, "comment":"permission bit set"}'
  */
  //p->deny is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:13:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:14:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */

  /* specs/channel.objects.json:15:20
     '{ "name": "allow", "type":{ "base":"s_as_u64"}, "comment":"permission bit set"}'
  */

  /* specs/channel.objects.json:16:20
     '{ "name": "deny", "type":{ "base":"s_as_u64"}, "comment":"permission bit set"}'
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

} // namespace overwrite

namespace reaction {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                "(count):d,"
  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                "(me):b,"
  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
                "(emoji):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                &p->count,
  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                &p->me,
  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
                discord::emoji::dati_from_json, p->emoji,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                "(count):d,"
  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                "(me):b,"
  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
                "(emoji):F,"
                "@arg_switches:b",
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
                &p->count,
  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
                &p->me,
  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
                discord::emoji::dati_to_json, p->emoji,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[0] = &p->count;

  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[1] = &p->me;

  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  p->__M.arg_switches[2] = p->emoji;

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
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */
  //p->count is a scalar
  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */
  //p->me is a scalar
  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  if (d->emoji)
    discord::emoji::dati_free(d->emoji);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:25:20
     '{ "name": "count", "type":{ "base":"int" }}'
  */

  /* specs/channel.objects.json:26:20
     '{ "name": "me", "type":{ "base":"bool" }}'
  */

  /* specs/channel.objects.json:27:20
     '{ "name": "emoji", "type":{ "base":"discord::emoji::dati", "dec":"*" }, "comment":"partial emoji object"}'
  */
  p->emoji = discord::emoji::dati_alloc();

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

} // namespace reaction

namespace followed_channel {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):F,"
  /* specs/channel.objects.json:38:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(webhook_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->channel_id,
  /* specs/channel.objects.json:38:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->webhook_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):|F|,"
  /* specs/channel.objects.json:38:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(webhook_id):|F|,"
                "@arg_switches:b",
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/channel.objects.json:38:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->webhook_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->channel_id;

  /* specs/channel.objects.json:38:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->webhook_id;

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
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->channel_id is a scalar
  /* specs/channel.objects.json:38:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->webhook_id is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:37:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:38:20
     '{ "name": "webhook_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
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

} // namespace followed_channel

namespace attachment {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                "(filename):s,"
  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                "(size):d,"
  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                "(url):s,"
  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                "(height):d,"
  /* specs/channel.objects.json:53:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                p->filename,
  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                &p->size,
  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                p->url,
  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                &p->height,
  /* specs/channel.objects.json:53:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                "(filename):s,"
  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                "(size):d,"
  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                "(url):s,"
  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                "(height):d,"
  /* specs/channel.objects.json:53:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
                p->filename,
  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
                &p->size,
  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                p->url,
  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
                &p->height,
  /* specs/channel.objects.json:53:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  p->__M.arg_switches[1] = p->filename;

  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->size;

  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  p->__M.arg_switches[3] = p->url;

  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  p->__M.arg_switches[4] = p->proxy_url;

  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  p->__M.arg_switches[5] = &p->height;

  /* specs/channel.objects.json:53:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
  p->__M.arg_switches[6] = &p->width;

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
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */
  //p->filename is a scalar
  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */
  //p->size is a scalar
  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */
  //p->proxy_url is a scalar
  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */
  //p->height is a scalar
  /* specs/channel.objects.json:53:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
  */
  //p->width is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:47:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:48:20
     '{ "name": "filename", "type":{ "base":"char", "dec":"[256]" }}'
  */

  /* specs/channel.objects.json:49:20
     '{ "name": "size", "type":{ "base":"int" }}'
  */

  /* specs/channel.objects.json:50:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */

  /* specs/channel.objects.json:51:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }}'
  */

  /* specs/channel.objects.json:52:20
     '{ "name": "height", "type":{ "base":"int", "nullable":true }}'
  */

  /* specs/channel.objects.json:53:20
     '{ "name": "width", "type":{ "base":"int", "nullable":true }}'
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

} // namespace attachment

namespace mention {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):F,"
  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */
                "(type):d,"
  /* specs/channel.objects.json:66:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->guild_id,
  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */
                &p->type,
  /* specs/channel.objects.json:66:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):|F|,"
  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */
                "(type):d,"
  /* specs/channel.objects.json:66:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                "(name):s,"
                "@arg_switches:b",
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */
                &p->type,
  /* specs/channel.objects.json:66:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
                p->name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->guild_id;

  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */
  p->__M.arg_switches[2] = &p->type;

  /* specs/channel.objects.json:66:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[3] = p->name;

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
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->guild_id is a scalar
  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */
  //p->type is a scalar
  /* specs/channel.objects.json:66:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->name)
    free(d->name);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:63:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:64:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/channel.objects.json:65:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::channel::types::code" }}'
  */

  /* specs/channel.objects.json:66:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}'
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

} // namespace mention

namespace allowed_mentions {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                "(parse):F,"
  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(roles):F,"
  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(users):F,"
  /* specs/channel.objects.json:79:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                "(replied_user):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                ja_str_list_from_json, &p->parse,
  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_from_json, &p->roles,
  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_from_json, &p->users,
  /* specs/channel.objects.json:79:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                &p->replied_user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                "(parse):F,"
  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(roles):F,"
  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                "(users):F,"
  /* specs/channel.objects.json:79:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                "(replied_user):b,"
                "@arg_switches:b",
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
                ja_str_list_to_json, p->parse,
  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_to_json, p->roles,
  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
                ja_u64_list_to_json, p->users,
  /* specs/channel.objects.json:79:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
                &p->replied_user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  p->__M.arg_switches[0] = p->parse;

  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  p->__M.arg_switches[1] = p->roles;

  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  p->__M.arg_switches[2] = p->users;

  /* specs/channel.objects.json:79:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[3] = &p->replied_user;

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
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */
  if (d->parse)
    ja_str_list_free(d->parse);
  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */
  if (d->users)
    ja_u64_list_free(d->users);
  /* specs/channel.objects.json:79:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
  */
  //p->replied_user is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:76:20
     '{ "name": "parse", "type":{ "base":"ja_str", "dec":"ntl" }}'
  */

  /* specs/channel.objects.json:77:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */

  /* specs/channel.objects.json:78:20
     '{ "name": "users", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"list of snowflakes"}'
  */

  /* specs/channel.objects.json:79:20
     '{ "name": "replied_user", "type":{ "base":"bool" }}'
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

} // namespace allowed_mentions

namespace embed {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(title):s,"
  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(type):s,"
  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(description):s,"
  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                "(timestamp):F,"
  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(footer):F,"
  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(image):F,"
  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(thumbnail):F,"
  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(video):F,"
  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(provider):F,"
  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(author):F,"
  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                "(fields):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->title,
  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->type,
  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->description,
  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                orka_iso8601_to_unix_ms, &p->timestamp,
  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                &p->color,
  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                discord::channel::embed::footer::dati_from_json, p->footer,
  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::image::dati_from_json, p->image,
  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::thumbnail::dati_from_json, p->thumbnail,
  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::video::dati_from_json, p->video,
  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::provider::dati_from_json, p->provider,
  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::author::dati_from_json, p->author,
  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                discord::channel::embed::field::dati_list_from_json, &p->fields,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(title):s,"
  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(type):s,"
  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(description):s,"
  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                "(timestamp):|F|,"
  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                "(color):d,"
  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                "(footer):F,"
  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(image):F,"
  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(thumbnail):F,"
  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(video):F,"
  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(provider):F,"
  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
                "(author):F,"
  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                "(fields):F,"
                "@arg_switches:b",
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->title,
  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->type,
  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->description,
  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
                orka_unix_ms_to_iso8601, &p->timestamp,
  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
                &p->color,
  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
                discord::channel::embed::footer::dati_to_json, p->footer,
  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::image::dati_to_json, p->image,
  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::thumbnail::dati_to_json, p->thumbnail,
  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::video::dati_to_json, p->video,
  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::provider::dati_to_json, p->provider,
  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
                discord::channel::embed::author::dati_to_json, p->author,
  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
                discord::channel::embed::field::dati_list_to_json, p->fields,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->title) != 0)
    p->__M.arg_switches[0] = p->title;

  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->type) != 0)
    p->__M.arg_switches[1] = p->type;

  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->description) != 0)
    p->__M.arg_switches[2] = p->description;

  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[3] = p->url;

  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  if (p->timestamp != 0)
    p->__M.arg_switches[4] = &p->timestamp;

  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  if (p->color != 0)
    p->__M.arg_switches[5] = &p->color;

  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (p->footer != NULL)
    p->__M.arg_switches[6] = p->footer;

  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->image != NULL)
    p->__M.arg_switches[7] = p->image;

  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->thumbnail != NULL)
    p->__M.arg_switches[8] = p->thumbnail;

  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->video != NULL)
    p->__M.arg_switches[9] = p->video;

  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->provider != NULL)
    p->__M.arg_switches[10] = p->provider;

  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (p->author != NULL)
    p->__M.arg_switches[11] = p->author;

  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  if (p->fields != NULL)
    p->__M.arg_switches[12] = p->fields;

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
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  //p->title is a scalar
  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */
  //p->type is a scalar
  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  //p->description is a scalar
  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */
  //p->timestamp is a scalar
  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */
  //p->color is a scalar
  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  if (d->footer)
    discord::channel::embed::footer::dati_free(d->footer);
  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->image)
    discord::channel::embed::image::dati_free(d->image);
  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->thumbnail)
    discord::channel::embed::thumbnail::dati_free(d->thumbnail);
  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->video)
    discord::channel::embed::video::dati_free(d->video);
  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->provider)
    discord::channel::embed::provider::dati_free(d->provider);
  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
  if (d->author)
    discord::channel::embed::author::dati_free(d->author);
  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
          "option":true, "inject_if_not":null}'
  */
  if (d->fields)
    discord::channel::embed::field::dati_list_free(d->fields);
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:89:20
     '{ "name": "title", "type":{ "base":"char", "dec":"[EMBED_TITLE_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:91:20
     '{ "name": "type", "type":{ "base":"char", "dec":"[32]" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:93:20
     '{ "name": "description", "type":{ "base":"char", "dec":"[EMBED_DESCRIPTION_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:95:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]"},
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:97:20
     '{ "name": "timestamp", "type":{ "base":"char", "dec":"*", "converter":"iso8601" },
          "option":true, "inject_if_not":0}'
  */

  /* specs/channel.objects.json:99:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0}'
  */

  /* specs/channel.objects.json:100:20
     '{ "name": "footer", "type":{ "base":"discord::channel::embed::footer::dati", "dec":"*"},
          "option":true, "inject_if_not":null}'
  */
  p->footer = discord::channel::embed::footer::dati_alloc();

  /* specs/channel.objects.json:102:20
     '{ "name": "image", "type":{ "base":"discord::channel::embed::image::dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->image = discord::channel::embed::image::dati_alloc();

  /* specs/channel.objects.json:103:20
     '{ "name": "thumbnail", "type":{ "base":"discord::channel::embed::thumbnail::dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->thumbnail = discord::channel::embed::thumbnail::dati_alloc();

  /* specs/channel.objects.json:104:20
     '{ "name": "video", "type":{ "base":"discord::channel::embed::video::dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->video = discord::channel::embed::video::dati_alloc();

  /* specs/channel.objects.json:105:20
     '{ "name": "provider", "type":{ "base":"discord::channel::embed::provider::dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->provider = discord::channel::embed::provider::dati_alloc();

  /* specs/channel.objects.json:106:20
     '{ "name": "author", "type":{ "base":"discord::channel::embed::author::dati", "dec":"*"}, "inject_if_not":null}'
  */
  p->author = discord::channel::embed::author::dati_alloc();

  /* specs/channel.objects.json:107:20
     '{ "name": "fields", "type":{ "base":"discord::channel::embed::field::dati", "dec":"ntl"},
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
  orka_str_to_ntl(str, len, &d);
}

size_t dati_list_to_json(char *str, size_t len, struct dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, dati_to_json_v);
}

} // namespace embed

namespace embed {
namespace thumbnail {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/channel.objects.json:121:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/channel.objects.json:121:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_url):s,"
  /* specs/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(height):d,"
  /* specs/channel.objects.json:121:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(width):d,"
                "@arg_switches:b",
  /* specs/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_url,
  /* specs/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->height,
  /* specs/channel.objects.json:121:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->width,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[0] = p->url;

  /* specs/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->proxy_url) != 0)
    p->__M.arg_switches[1] = p->proxy_url;

  /* specs/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->height != 0)
    p->__M.arg_switches[2] = &p->height;

  /* specs/channel.objects.json:121:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->width != 0)
    p->__M.arg_switches[3] = &p->width;

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
  /* specs/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->proxy_url is a scalar
  /* specs/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->height is a scalar
  /* specs/channel.objects.json:121:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->width is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:118:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:119:20
     '{ "name": "proxy_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:120:20
     '{ "name": "height", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/channel.objects.json:121:20
     '{ "name": "width", "type":{ "base":"int" }, "inject_if_not":0}'
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

} // namespace thumbnail
} // namespace embed

namespace embed {
namespace provider {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:130:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:131:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
                "(url):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:130:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:131:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
                p->url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:130:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:131:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
                "(url):s,"
                "@arg_switches:b",
  /* specs/channel.objects.json:130:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:131:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
                p->url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:130:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/channel.objects.json:131:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[1] = p->url;

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
  /* specs/channel.objects.json:130:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/channel.objects.json:131:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
  */
  //p->url is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:130:20
     '{ "name": "name", "type":{"base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]"}, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:131:20
     '{ "name": "url", "type":{"base":"char", "dec":"[MAX_URL_LEN]"}, "inject_if_not":""}'
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

} // namespace provider
} // namespace embed

namespace embed {
namespace author {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:140:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:141:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:142:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/channel.objects.json:143:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:140:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:141:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:142:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/channel.objects.json:143:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:140:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:141:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(url):s,"
  /* specs/channel.objects.json:142:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/channel.objects.json:143:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* specs/channel.objects.json:140:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:141:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->url,
  /* specs/channel.objects.json:142:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/channel.objects.json:143:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:140:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/channel.objects.json:141:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->url) != 0)
    p->__M.arg_switches[1] = p->url;

  /* specs/channel.objects.json:142:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->icon_url) != 0)
    p->__M.arg_switches[2] = p->icon_url;

  /* specs/channel.objects.json:143:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->proxy_icon_url) != 0)
    p->__M.arg_switches[3] = p->proxy_icon_url;

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
  /* specs/channel.objects.json:140:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/channel.objects.json:141:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->url is a scalar
  /* specs/channel.objects.json:142:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->icon_url is a scalar
  /* specs/channel.objects.json:143:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */
  //p->proxy_icon_url is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:140:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[EMBED_AUTHOR_NAME_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:141:20
     '{ "name": "url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:142:20
     '{ "name": "icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:143:20
     '{ "name": "proxy_icon_url", "type":{ "base":"char", "dec":"[MAX_URL_LEN]" }, "inject_if_not":""}'
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

} // namespace author
} // namespace embed

namespace embed {
namespace footer {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:152:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                "(text):s,"
  /* specs/channel.objects.json:153:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/channel.objects.json:155:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:152:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                p->text,
  /* specs/channel.objects.json:153:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/channel.objects.json:155:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:152:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                "(text):s,"
  /* specs/channel.objects.json:153:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                "(icon_url):s,"
  /* specs/channel.objects.json:155:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                "(proxy_icon_url):s,"
                "@arg_switches:b",
  /* specs/channel.objects.json:152:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
                p->text,
  /* specs/channel.objects.json:153:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
                p->icon_url,
  /* specs/channel.objects.json:155:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
                p->proxy_icon_url,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:152:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  if (strlen(p->text) != 0)
    p->__M.arg_switches[0] = p->text;

  /* specs/channel.objects.json:153:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->icon_url) != 0)
    p->__M.arg_switches[1] = p->icon_url;

  /* specs/channel.objects.json:155:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  if (strlen(p->proxy_icon_url) != 0)
    p->__M.arg_switches[2] = p->proxy_icon_url;

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
  /* specs/channel.objects.json:152:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */
  //p->text is a scalar
  /* specs/channel.objects.json:153:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */
  //p->icon_url is a scalar
  /* specs/channel.objects.json:155:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
  */
  //p->proxy_icon_url is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:152:20
     '{ "name": "text", "type": {"base":"char", "dec":"[EMBED_FOOTER_TEXT_LEN]"}, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:153:20
     '{ "name": "icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]" }, 
          "option":true, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:155:20
     '{ "name": "proxy_icon_url", "type": {"base":"char", "dec":"[MAX_URL_LEN]"}, 
          "option":true, "inject_if_not":""}'
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

} // namespace footer
} // namespace embed

namespace embed {
namespace field {
void dati_from_json(char *json, size_t len, struct dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.objects.json:165:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:166:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                "(value):s,"
  /* specs/channel.objects.json:167:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                "(inline):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.objects.json:165:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:166:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                p->value,
  /* specs/channel.objects.json:167:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                &p->Inline,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

size_t dati_to_json(char *json, size_t len, struct dati *p)
{
  size_t r;
  r=json_inject(json, len, 
  /* specs/channel.objects.json:165:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                "(name):s,"
  /* specs/channel.objects.json:166:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                "(value):s,"
  /* specs/channel.objects.json:167:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                "(inline):b,"
                "@arg_switches:b",
  /* specs/channel.objects.json:165:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
                p->name,
  /* specs/channel.objects.json:166:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
                p->value,
  /* specs/channel.objects.json:167:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
                &p->Inline,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}

void dati_use_default_inject_settings(struct dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.objects.json:165:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->name) != 0)
    p->__M.arg_switches[0] = p->name;

  /* specs/channel.objects.json:166:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  if (strlen(p->value) != 0)
    p->__M.arg_switches[1] = p->value;

  /* specs/channel.objects.json:167:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
  p->__M.arg_switches[2] = &p->Inline;

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
  /* specs/channel.objects.json:165:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */
  //p->name is a scalar
  /* specs/channel.objects.json:166:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */
  //p->value is a scalar
  /* specs/channel.objects.json:167:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
  */
  //p->Inline is a scalar
}

void dati_init(struct dati *p) {
  memset(p, 0, sizeof(struct dati));
  /* specs/channel.objects.json:165:20
     '{ "name": "name", "type": { "base":"char", "dec":"[EMBED_FIELD_NAME_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:166:20
     '{ "name": "value", "type": { "base":"char", "dec":"[EMBED_FIELD_VALUE_LEN]" }, "inject_if_not":""}'
  */

  /* specs/channel.objects.json:167:20
     '{ "name": "Inline", "json_key":"inline", "type": { "base":"bool" }, "option":true}'
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
} // namespace embed
} // namespace channel
} // namespace discord
