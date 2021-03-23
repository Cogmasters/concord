/* This file is generated from specs/channel.get-reactions.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_channel_get_reactions_params_from_json(char *json, size_t len, struct discord_channel_get_reactions_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
                "(before):F,"
  /* specs/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
                "(after):F,"
  /* specs/channel.get-reactions.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}'
  */
                "(limit):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
                orka_strtoull, &p->before,
  /* specs/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
                orka_strtoull, &p->after,
  /* specs/channel.get-reactions.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}'
  */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_channel_get_reactions_params_use_default_inject_settings(struct discord_channel_get_reactions_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
  p->__M.arg_switches[0] = &p->before;

  /* specs/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
  p->__M.arg_switches[1] = &p->after;

  /* specs/channel.get-reactions.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}'
  */
  p->__M.arg_switches[2] = &p->limit;

}

size_t discord_channel_get_reactions_params_to_json(char *json, size_t len, struct discord_channel_get_reactions_params *p)
{
  size_t r;
  discord_channel_get_reactions_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
                "(before):|F|,"
  /* specs/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
                "(after):|F|,"
  /* specs/channel.get-reactions.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}'
  */
                "(limit):d,"
                "@arg_switches:b",
  /* specs/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
                orka_ulltostr, &p->before,
  /* specs/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
                orka_ulltostr, &p->after,
  /* specs/channel.get-reactions.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}'
  */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_channel_get_reactions_params_cleanup_v(void *p) {
  discord_channel_get_reactions_params_cleanup((struct discord_channel_get_reactions_params *)p);
}

void discord_channel_get_reactions_params_init_v(void *p) {
  discord_channel_get_reactions_params_init((struct discord_channel_get_reactions_params *)p);
}

void discord_channel_get_reactions_params_free_v(void *p) {
 discord_channel_get_reactions_params_free((struct discord_channel_get_reactions_params *)p);
};

void discord_channel_get_reactions_params_from_json_v(char *json, size_t len, void *p) {
 discord_channel_get_reactions_params_from_json(json, len, (struct discord_channel_get_reactions_params*)p);
}

size_t discord_channel_get_reactions_params_to_json_v(char *json, size_t len, void *p) {
  return discord_channel_get_reactions_params_to_json(json, len, (struct discord_channel_get_reactions_params*)p);
}

void discord_channel_get_reactions_params_list_free_v(void **p) {
  discord_channel_get_reactions_params_list_free((struct discord_channel_get_reactions_params**)p);
}

void discord_channel_get_reactions_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_channel_get_reactions_params_list_from_json(str, len, (struct discord_channel_get_reactions_params ***)p);
}

size_t discord_channel_get_reactions_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_channel_get_reactions_params_list_to_json(str, len, (struct discord_channel_get_reactions_params **)p);
}


void discord_channel_get_reactions_params_cleanup(struct discord_channel_get_reactions_params *d) {
  /* specs/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
  //p->before is a scalar
  /* specs/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */
  //p->after is a scalar
  /* specs/channel.get-reactions.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}'
  */
  //p->limit is a scalar
}

void discord_channel_get_reactions_params_init(struct discord_channel_get_reactions_params *p) {
  memset(p, 0, sizeof(struct discord_channel_get_reactions_params));
  /* specs/channel.get-reactions.json:11:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */

  /* specs/channel.get-reactions.json:12:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}'
  */

  /* specs/channel.get-reactions.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}'
  */

}
struct discord_channel_get_reactions_params* discord_channel_get_reactions_params_alloc() {
  struct discord_channel_get_reactions_params *p= (struct discord_channel_get_reactions_params*)malloc(sizeof(struct discord_channel_get_reactions_params));
  discord_channel_get_reactions_params_init(p);
  return p;
}

void discord_channel_get_reactions_params_free(struct discord_channel_get_reactions_params *p) {
  discord_channel_get_reactions_params_cleanup(p);
  free(p);
}

void discord_channel_get_reactions_params_list_free(struct discord_channel_get_reactions_params **p) {
  ntl_free((void**)p, (vfvp)discord_channel_get_reactions_params_cleanup);
}

void discord_channel_get_reactions_params_list_from_json(char *str, size_t len, struct discord_channel_get_reactions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_channel_get_reactions_params);
  d.init_elem = discord_channel_get_reactions_params_init_v;
  d.elem_from_buf = discord_channel_get_reactions_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_channel_get_reactions_params_list_to_json(char *str, size_t len, struct discord_channel_get_reactions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_channel_get_reactions_params_to_json_v);
}

