/* This file is generated from specs/webhook.edit-webhook-message.json, Please don't edit it. */
#include "specs.h"
/*

*/
namespace discord {
namespace webhook {
namespace edit_webhook_message {

void params_from_json(char *json, size_t len, struct params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
                "(content):s,"
  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
                "(embeds):F,"
  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
                "(allowed_mentions):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
                p->content,
  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
                discord::channel::embed::dati_list_from_json, &p->embeds,
  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
                discord::channel::allowed_mentions::dati_from_json, p->allowed_mentions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void params_use_default_inject_settings(struct params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
  p->__M.arg_switches[0] = p->content;

  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
  p->__M.arg_switches[1] = p->embeds;

  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
  p->__M.arg_switches[2] = p->allowed_mentions;

}

size_t params_to_json(char *json, size_t len, struct params *p)
{
  size_t r;
  params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
                "(content):s,"
  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
                "(embeds):F,"
  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
                "(allowed_mentions):F,"
                "@arg_switches:b",
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
                p->content,
  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
                discord::channel::embed::dati_list_to_json, p->embeds,
  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
                discord::channel::allowed_mentions::dati_to_json, p->allowed_mentions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void params_cleanup_v(void *p) {
  params_cleanup((struct params *)p);
}

void params_init_v(void *p) {
  params_init((struct params *)p);
}

void params_free_v(void *p) {
 params_free((struct params *)p);
};

void params_from_json_v(char *json, size_t len, void *p) {
 params_from_json(json, len, (struct params*)p);
}

size_t params_to_json_v(char *json, size_t len, void *p) {
  return params_to_json(json, len, (struct params*)p);
}

void params_list_free_v(void **p) {
  params_list_free((struct params**)p);
}

void params_list_from_json_v(char *str, size_t len, void *p) {
  params_list_from_json(str, len, (struct params ***)p);
}

size_t params_list_to_json_v(char *str, size_t len, void *p){
  return params_list_to_json(str, len, (struct params **)p);
}


void params_cleanup(struct params *d) {
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */
  //p->content is a scalar
  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */
  if (d->embeds)
    discord::channel::embed::dati_list_free(d->embeds);
  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
  if (d->allowed_mentions)
    discord::channel::allowed_mentions::dati_free(d->allowed_mentions);
}

void params_init(struct params *p) {
  memset(p, 0, sizeof(struct params));
  /* specs/webhook.edit-webhook-message.json:11:20
     '{ "name": "content", "type":{ "base":"char", "dec":"[2000+1]" }, 
          "comment":"name of the webhook(1-2000) chars" }'
  */

  /* specs/webhook.edit-webhook-message.json:13:20
     '{ "name": "embeds", "type":{ "base":"discord::channel::embed::dati", "dec":"ntl" }, 
          "comment":"array of up to 10 embeds objects" }'
  */

  /* specs/webhook.edit-webhook-message.json:15:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"discord::channel::allowed_mentions::dati", "dec":"*" }, 
          "comment":"allowed mentions for the message" }'
  */
  p->allowed_mentions = discord::channel::allowed_mentions::dati_alloc();

}
struct params* params_alloc() {
  struct params *p= (struct params*)malloc(sizeof(struct params));
  params_init(p);
  return p;
}

void params_free(struct params *p) {
  params_cleanup(p);
  free(p);
}

void params_list_free(struct params **p) {
  ntl_free((void**)p, (vfvp)params_cleanup);
}

void params_list_from_json(char *str, size_t len, struct params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct params);
  d.init_elem = params_init_v;
  d.elem_from_buf = params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t params_list_to_json(char *str, size_t len, struct params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, params_to_json_v);
}

} // namespace edit_webhook_message
} // namespace webhook
} // namespace discord
