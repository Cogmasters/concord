/* This file is generated from specs/discord/channel.follow-news-channel.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.follow-news-channel.json:11:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(webhook_channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.follow-news-channel.json:11:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->webhook_channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_follow_news_channel_params_use_default_inject_settings(struct discord_follow_news_channel_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.follow-news-channel.json:11:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->webhook_channel_id;

}

size_t discord_follow_news_channel_params_to_json(char *json, size_t len, struct discord_follow_news_channel_params *p)
{
  size_t r;
  discord_follow_news_channel_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.follow-news-channel.json:11:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(webhook_channel_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/channel.follow-news-channel.json:11:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->webhook_channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_follow_news_channel_params_cleanup_v(void *p) {
  discord_follow_news_channel_params_cleanup((struct discord_follow_news_channel_params *)p);
}

void discord_follow_news_channel_params_init_v(void *p) {
  discord_follow_news_channel_params_init((struct discord_follow_news_channel_params *)p);
}

void discord_follow_news_channel_params_free_v(void *p) {
 discord_follow_news_channel_params_free((struct discord_follow_news_channel_params *)p);
};

void discord_follow_news_channel_params_from_json_v(char *json, size_t len, void *p) {
 discord_follow_news_channel_params_from_json(json, len, (struct discord_follow_news_channel_params*)p);
}

size_t discord_follow_news_channel_params_to_json_v(char *json, size_t len, void *p) {
  return discord_follow_news_channel_params_to_json(json, len, (struct discord_follow_news_channel_params*)p);
}

void discord_follow_news_channel_params_list_free_v(void **p) {
  discord_follow_news_channel_params_list_free((struct discord_follow_news_channel_params**)p);
}

void discord_follow_news_channel_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_follow_news_channel_params_list_from_json(str, len, (struct discord_follow_news_channel_params ***)p);
}

size_t discord_follow_news_channel_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_follow_news_channel_params_list_to_json(str, len, (struct discord_follow_news_channel_params **)p);
}


void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *d) {
  /* specs/discord/channel.follow-news-channel.json:11:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->webhook_channel_id is a scalar
}

void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p) {
  memset(p, 0, sizeof(struct discord_follow_news_channel_params));
  /* specs/discord/channel.follow-news-channel.json:11:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

}
struct discord_follow_news_channel_params* discord_follow_news_channel_params_alloc() {
  struct discord_follow_news_channel_params *p= (struct discord_follow_news_channel_params*)malloc(sizeof(struct discord_follow_news_channel_params));
  discord_follow_news_channel_params_init(p);
  return p;
}

void discord_follow_news_channel_params_free(struct discord_follow_news_channel_params *p) {
  discord_follow_news_channel_params_cleanup(p);
  free(p);
}

void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **p) {
  ntl_free((void**)p, (vfvp)discord_follow_news_channel_params_cleanup);
}

void discord_follow_news_channel_params_list_from_json(char *str, size_t len, struct discord_follow_news_channel_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_follow_news_channel_params);
  d.init_elem = discord_follow_news_channel_params_init_v;
  d.elem_from_buf = discord_follow_news_channel_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_follow_news_channel_params_list_to_json(char *str, size_t len, struct discord_follow_news_channel_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_follow_news_channel_params_to_json_v);
}

