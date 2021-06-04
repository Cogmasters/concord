/* This file is generated from specs/discord/channel.start-thread-without-message.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
                "(name):?s,"
  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                "(auto_archive_duration):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
                &p->name,
  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                &p->auto_archive_duration,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_start_thread_without_message_params_use_default_inject_settings(struct discord_start_thread_without_message_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  if (p->auto_archive_duration != 0)
    p->__M.arg_switches[1] = &p->auto_archive_duration;

}

size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p)
{
  size_t r;
  discord_start_thread_without_message_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
                "(name):s,"
  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                "(auto_archive_duration):d,"
                "@arg_switches:b",
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
                p->name,
  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                &p->auto_archive_duration,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_start_thread_without_message_params_cleanup_v(void *p) {
  discord_start_thread_without_message_params_cleanup((struct discord_start_thread_without_message_params *)p);
}

void discord_start_thread_without_message_params_init_v(void *p) {
  discord_start_thread_without_message_params_init((struct discord_start_thread_without_message_params *)p);
}

void discord_start_thread_without_message_params_free_v(void *p) {
 discord_start_thread_without_message_params_free((struct discord_start_thread_without_message_params *)p);
};

void discord_start_thread_without_message_params_from_json_v(char *json, size_t len, void *p) {
 discord_start_thread_without_message_params_from_json(json, len, (struct discord_start_thread_without_message_params*)p);
}

size_t discord_start_thread_without_message_params_to_json_v(char *json, size_t len, void *p) {
  return discord_start_thread_without_message_params_to_json(json, len, (struct discord_start_thread_without_message_params*)p);
}

void discord_start_thread_without_message_params_list_free_v(void **p) {
  discord_start_thread_without_message_params_list_free((struct discord_start_thread_without_message_params**)p);
}

void discord_start_thread_without_message_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_start_thread_without_message_params_list_from_json(str, len, (struct discord_start_thread_without_message_params ***)p);
}

size_t discord_start_thread_without_message_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_start_thread_without_message_params_list_to_json(str, len, (struct discord_start_thread_without_message_params **)p);
}


void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *d) {
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */
  if (d->name)
    free(d->name);
  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  //p->auto_archive_duration is a scalar
}

void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *p) {
  memset(p, 0, sizeof(struct discord_start_thread_without_message_params));
  /* specs/discord/channel.start-thread-without-message.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }'
  */

  /* specs/discord/channel.start-thread-without-message.json:12:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }'
  */

}
struct discord_start_thread_without_message_params* discord_start_thread_without_message_params_alloc() {
  struct discord_start_thread_without_message_params *p= (struct discord_start_thread_without_message_params*)malloc(sizeof(struct discord_start_thread_without_message_params));
  discord_start_thread_without_message_params_init(p);
  return p;
}

void discord_start_thread_without_message_params_free(struct discord_start_thread_without_message_params *p) {
  discord_start_thread_without_message_params_cleanup(p);
  free(p);
}

void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **p) {
  ntl_free((void**)p, (vfvp)discord_start_thread_without_message_params_cleanup);
}

void discord_start_thread_without_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_without_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_start_thread_without_message_params);
  d.init_elem = discord_start_thread_without_message_params_init_v;
  d.elem_from_buf = discord_start_thread_without_message_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_start_thread_without_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_without_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_start_thread_without_message_params_to_json_v);
}

