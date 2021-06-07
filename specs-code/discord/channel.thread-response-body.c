/* This file is generated from specs/discord/channel.thread-response-body.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
                "(threads):F,"
  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
                "(members):F,"
  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */
                "(has_more):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
                discord_channel_list_from_json, &p->threads,
  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
                discord_thread_member_list_from_json, &p->members,
  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */
                &p->has_more,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_thread_response_body_use_default_inject_settings(struct discord_thread_response_body *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
  p->__M.arg_switches[0] = p->threads;

  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
  p->__M.arg_switches[1] = p->members;

  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */
  p->__M.arg_switches[2] = &p->has_more;

}

size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p)
{
  size_t r;
  discord_thread_response_body_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
                "(threads):F,"
  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
                "(members):F,"
  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */
                "(has_more):b,"
                "@arg_switches:b",
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
                discord_channel_list_to_json, p->threads,
  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
                discord_thread_member_list_to_json, p->members,
  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */
                &p->has_more,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_thread_response_body_cleanup_v(void *p) {
  discord_thread_response_body_cleanup((struct discord_thread_response_body *)p);
}

void discord_thread_response_body_init_v(void *p) {
  discord_thread_response_body_init((struct discord_thread_response_body *)p);
}

void discord_thread_response_body_free_v(void *p) {
 discord_thread_response_body_free((struct discord_thread_response_body *)p);
};

void discord_thread_response_body_from_json_v(char *json, size_t len, void *p) {
 discord_thread_response_body_from_json(json, len, (struct discord_thread_response_body*)p);
}

size_t discord_thread_response_body_to_json_v(char *json, size_t len, void *p) {
  return discord_thread_response_body_to_json(json, len, (struct discord_thread_response_body*)p);
}

void discord_thread_response_body_list_free_v(void **p) {
  discord_thread_response_body_list_free((struct discord_thread_response_body**)p);
}

void discord_thread_response_body_list_from_json_v(char *str, size_t len, void *p) {
  discord_thread_response_body_list_from_json(str, len, (struct discord_thread_response_body ***)p);
}

size_t discord_thread_response_body_list_to_json_v(char *str, size_t len, void *p){
  return discord_thread_response_body_list_to_json(str, len, (struct discord_thread_response_body **)p);
}


void discord_thread_response_body_cleanup(struct discord_thread_response_body *d) {
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */
  if (d->threads)
    discord_channel_list_free(d->threads);
  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */
  if (d->members)
    discord_thread_member_list_free(d->members);
  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */
  //p->has_more is a scalar
}

void discord_thread_response_body_init(struct discord_thread_response_body *p) {
  memset(p, 0, sizeof(struct discord_thread_response_body));
  /* specs/discord/channel.thread-response-body.json:11:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }'
  */

  /* specs/discord/channel.thread-response-body.json:12:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }'
  */

  /* specs/discord/channel.thread-response-body.json:13:20
     '{ "name": "has_more", "type":{ "base":"bool" } }'
  */

}
struct discord_thread_response_body* discord_thread_response_body_alloc() {
  struct discord_thread_response_body *p= (struct discord_thread_response_body*)malloc(sizeof(struct discord_thread_response_body));
  discord_thread_response_body_init(p);
  return p;
}

void discord_thread_response_body_free(struct discord_thread_response_body *p) {
  discord_thread_response_body_cleanup(p);
  free(p);
}

void discord_thread_response_body_list_free(struct discord_thread_response_body **p) {
  ntl_free((void**)p, (vfvp)discord_thread_response_body_cleanup);
}

void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_response_body);
  d.init_elem = discord_thread_response_body_init_v;
  d.elem_from_buf = discord_thread_response_body_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_thread_response_body_to_json_v);
}

