/* This file is generated from specs/webhook.create-webhook.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_webhook_create_webhook_params_from_json(char *json, size_t len, struct discord_webhook_create_webhook_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
                "(name):s,"
  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
                "(avatar):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
                p->name,
  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
                &p->avatar,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_webhook_create_webhook_params_use_default_inject_settings(struct discord_webhook_create_webhook_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
  p->__M.arg_switches[0] = p->name;

  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
  if (p->avatar != NULL)
    p->__M.arg_switches[1] = p->avatar;

}

size_t discord_webhook_create_webhook_params_to_json(char *json, size_t len, struct discord_webhook_create_webhook_params *p)
{
  size_t r;
  discord_webhook_create_webhook_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
                "(name):s,"
  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
                "(avatar):s,"
                "@arg_switches:b",
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
                p->name,
  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
                p->avatar,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_webhook_create_webhook_params_cleanup_v(void *p) {
  discord_webhook_create_webhook_params_cleanup((struct discord_webhook_create_webhook_params *)p);
}

void discord_webhook_create_webhook_params_init_v(void *p) {
  discord_webhook_create_webhook_params_init((struct discord_webhook_create_webhook_params *)p);
}

void discord_webhook_create_webhook_params_free_v(void *p) {
 discord_webhook_create_webhook_params_free((struct discord_webhook_create_webhook_params *)p);
};

void discord_webhook_create_webhook_params_from_json_v(char *json, size_t len, void *p) {
 discord_webhook_create_webhook_params_from_json(json, len, (struct discord_webhook_create_webhook_params*)p);
}

size_t discord_webhook_create_webhook_params_to_json_v(char *json, size_t len, void *p) {
  return discord_webhook_create_webhook_params_to_json(json, len, (struct discord_webhook_create_webhook_params*)p);
}

void discord_webhook_create_webhook_params_list_free_v(void **p) {
  discord_webhook_create_webhook_params_list_free((struct discord_webhook_create_webhook_params**)p);
}

void discord_webhook_create_webhook_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_webhook_create_webhook_params_list_from_json(str, len, (struct discord_webhook_create_webhook_params ***)p);
}

size_t discord_webhook_create_webhook_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_webhook_create_webhook_params_list_to_json(str, len, (struct discord_webhook_create_webhook_params **)p);
}


void discord_webhook_create_webhook_params_cleanup(struct discord_webhook_create_webhook_params *d) {
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */
  //p->name is a scalar
  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */
  if (d->avatar)
    free(d->avatar);
}

void discord_webhook_create_webhook_params_init(struct discord_webhook_create_webhook_params *p) {
  memset(p, 0, sizeof(struct discord_webhook_create_webhook_params));
  /* specs/webhook.create-webhook.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[80+1]" }, 
          "comment":"name of the webhook(1-80) chars" }'
  */

  /* specs/webhook.create-webhook.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, 
          "inject_if_not":null, 
          "comment":"base64 image for the default webhook avatar" }'
  */

}
struct discord_webhook_create_webhook_params* discord_webhook_create_webhook_params_alloc() {
  struct discord_webhook_create_webhook_params *p= (struct discord_webhook_create_webhook_params*)malloc(sizeof(struct discord_webhook_create_webhook_params));
  discord_webhook_create_webhook_params_init(p);
  return p;
}

void discord_webhook_create_webhook_params_free(struct discord_webhook_create_webhook_params *p) {
  discord_webhook_create_webhook_params_cleanup(p);
  free(p);
}

void discord_webhook_create_webhook_params_list_free(struct discord_webhook_create_webhook_params **p) {
  ntl_free((void**)p, (vfvp)discord_webhook_create_webhook_params_cleanup);
}

void discord_webhook_create_webhook_params_list_from_json(char *str, size_t len, struct discord_webhook_create_webhook_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_webhook_create_webhook_params);
  d.init_elem = discord_webhook_create_webhook_params_init_v;
  d.elem_from_buf = discord_webhook_create_webhook_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_webhook_create_webhook_params_list_to_json(char *str, size_t len, struct discord_webhook_create_webhook_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_webhook_create_webhook_params_to_json_v);
}

