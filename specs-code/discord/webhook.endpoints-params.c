/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/webhook.endpoints-params.c
 * @author cee-studio
 * @date 21 Jun 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/webhook
 */

#include "specs.h"

void discord_create_webhook_params_from_json(char *json, size_t len, struct discord_create_webhook_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                "(name):?s,"
  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                &p->name,
  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                &p->avatar,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_create_webhook_params_use_default_inject_settings(struct discord_create_webhook_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (p->avatar != NULL)
    p->__M.arg_switches[1] = p->avatar;

}

size_t discord_create_webhook_params_to_json(char *json, size_t len, struct discord_create_webhook_params *p)
{
  size_t r;
  discord_create_webhook_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                "(name):s,"
  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):s,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                p->name,
  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                p->avatar,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_webhook_params_cleanup_v(void *p) {
  discord_create_webhook_params_cleanup((struct discord_create_webhook_params *)p);
}

void discord_create_webhook_params_init_v(void *p) {
  discord_create_webhook_params_init((struct discord_create_webhook_params *)p);
}

void discord_create_webhook_params_free_v(void *p) {
 discord_create_webhook_params_free((struct discord_create_webhook_params *)p);
};

void discord_create_webhook_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_webhook_params_from_json(json, len, (struct discord_create_webhook_params*)p);
}

size_t discord_create_webhook_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_webhook_params_to_json(json, len, (struct discord_create_webhook_params*)p);
}

void discord_create_webhook_params_list_free_v(void **p) {
  discord_create_webhook_params_list_free((struct discord_create_webhook_params**)p);
}

void discord_create_webhook_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_webhook_params_list_from_json(str, len, (struct discord_create_webhook_params ***)p);
}

size_t discord_create_webhook_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_webhook_params_list_to_json(str, len, (struct discord_create_webhook_params **)p);
}


void discord_create_webhook_params_cleanup(struct discord_create_webhook_params *d) {
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  if (d->name)
    free(d->name);
  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (d->avatar)
    free(d->avatar);
}

void discord_create_webhook_params_init(struct discord_create_webhook_params *p) {
  memset(p, 0, sizeof(struct discord_create_webhook_params));
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */

  /* specs/discord/webhook.endpoints-params.json:14:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */

}
struct discord_create_webhook_params* discord_create_webhook_params_alloc() {
  struct discord_create_webhook_params *p= malloc(sizeof(struct discord_create_webhook_params));
  discord_create_webhook_params_init(p);
  return p;
}

void discord_create_webhook_params_free(struct discord_create_webhook_params *p) {
  discord_create_webhook_params_cleanup(p);
  free(p);
}

void discord_create_webhook_params_list_free(struct discord_create_webhook_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_webhook_params_cleanup);
}

void discord_create_webhook_params_list_from_json(char *str, size_t len, struct discord_create_webhook_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_webhook_params);
  d.init_elem = discord_create_webhook_params_init_v;
  d.elem_from_buf = discord_create_webhook_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_create_webhook_params_list_to_json(char *str, size_t len, struct discord_create_webhook_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_webhook_params_to_json_v);
}


void discord_modify_webhook_params_from_json(char *json, size_t len, struct discord_modify_webhook_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                "(name):?s,"
  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):?s,"
  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
                "(channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                &p->name,
  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                &p->avatar,
  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
                cee_strtoull, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_webhook_params_use_default_inject_settings(struct discord_modify_webhook_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (p->avatar != NULL)
    p->__M.arg_switches[1] = p->avatar;

  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
  p->__M.arg_switches[2] = &p->channel_id;

}

size_t discord_modify_webhook_params_to_json(char *json, size_t len, struct discord_modify_webhook_params *p)
{
  size_t r;
  discord_modify_webhook_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                "(name):s,"
  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):s,"
  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                p->name,
  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                p->avatar,
  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
                cee_ulltostr, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_webhook_params_cleanup_v(void *p) {
  discord_modify_webhook_params_cleanup((struct discord_modify_webhook_params *)p);
}

void discord_modify_webhook_params_init_v(void *p) {
  discord_modify_webhook_params_init((struct discord_modify_webhook_params *)p);
}

void discord_modify_webhook_params_free_v(void *p) {
 discord_modify_webhook_params_free((struct discord_modify_webhook_params *)p);
};

void discord_modify_webhook_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_webhook_params_from_json(json, len, (struct discord_modify_webhook_params*)p);
}

size_t discord_modify_webhook_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_webhook_params_to_json(json, len, (struct discord_modify_webhook_params*)p);
}

void discord_modify_webhook_params_list_free_v(void **p) {
  discord_modify_webhook_params_list_free((struct discord_modify_webhook_params**)p);
}

void discord_modify_webhook_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_webhook_params_list_from_json(str, len, (struct discord_modify_webhook_params ***)p);
}

size_t discord_modify_webhook_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_webhook_params_list_to_json(str, len, (struct discord_modify_webhook_params **)p);
}


void discord_modify_webhook_params_cleanup(struct discord_modify_webhook_params *d) {
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  if (d->name)
    free(d->name);
  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (d->avatar)
    free(d->avatar);
  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */
  // p->channel_id is a scalar
}

void discord_modify_webhook_params_init(struct discord_modify_webhook_params *p) {
  memset(p, 0, sizeof(struct discord_modify_webhook_params));
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */

  /* specs/discord/webhook.endpoints-params.json:25:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */

  /* specs/discord/webhook.endpoints-params.json:26:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the new channel id this webhook should be moved to" }' */

}
struct discord_modify_webhook_params* discord_modify_webhook_params_alloc() {
  struct discord_modify_webhook_params *p= malloc(sizeof(struct discord_modify_webhook_params));
  discord_modify_webhook_params_init(p);
  return p;
}

void discord_modify_webhook_params_free(struct discord_modify_webhook_params *p) {
  discord_modify_webhook_params_cleanup(p);
  free(p);
}

void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_webhook_params_cleanup);
}

void discord_modify_webhook_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_webhook_params);
  d.init_elem = discord_modify_webhook_params_init_v;
  d.elem_from_buf = discord_modify_webhook_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_modify_webhook_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_webhook_params_to_json_v);
}


void discord_execute_webhook_params_from_json(char *json, size_t len, struct discord_execute_webhook_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
                "(wait):b,"
  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
                "(content):?s,"
  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
                "(username):?s,"
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
                "(avatar_url):?s,"
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
                "(tts):b,"
  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
                "(file):?s,"
  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
                "(embeds):F,"
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
                "(payload_json):?s,"
  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
                "(allowed_mentions):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
                &p->wait,
  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
                &p->content,
  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
                &p->username,
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
                &p->avatar_url,
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
                &p->tts,
  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
                &p->file,
  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
                discord_embed_from_json, p->embeds,
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
                &p->payload_json,
  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
                discord_channel_allowed_mentions_from_json, p->allowed_mentions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_execute_webhook_params_use_default_inject_settings(struct discord_execute_webhook_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
  p->__M.arg_switches[0] = &p->wait;

  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
  p->__M.arg_switches[1] = p->content;

  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
  p->__M.arg_switches[2] = p->username;

  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
  p->__M.arg_switches[3] = p->avatar_url;

  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
  p->__M.arg_switches[4] = &p->tts;

  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
  p->__M.arg_switches[5] = p->file;

  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
  p->__M.arg_switches[6] = p->embeds;

  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
  p->__M.arg_switches[7] = p->payload_json;

  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
  p->__M.arg_switches[8] = p->allowed_mentions;

}

size_t discord_execute_webhook_params_to_json(char *json, size_t len, struct discord_execute_webhook_params *p)
{
  size_t r;
  discord_execute_webhook_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
                "(wait):b,"
  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
                "(content):s,"
  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
                "(username):s,"
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
                "(avatar_url):s,"
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
                "(tts):b,"
  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
                "(file):s,"
  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
                "(embeds):F,"
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
                "(payload_json):s,"
  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
                "(allowed_mentions):F,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
                &p->wait,
  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
                p->content,
  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
                p->username,
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
                p->avatar_url,
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
                &p->tts,
  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
                p->file,
  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
                discord_embed_to_json, p->embeds,
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
                p->payload_json,
  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
                discord_channel_allowed_mentions_to_json, p->allowed_mentions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_execute_webhook_params_cleanup_v(void *p) {
  discord_execute_webhook_params_cleanup((struct discord_execute_webhook_params *)p);
}

void discord_execute_webhook_params_init_v(void *p) {
  discord_execute_webhook_params_init((struct discord_execute_webhook_params *)p);
}

void discord_execute_webhook_params_free_v(void *p) {
 discord_execute_webhook_params_free((struct discord_execute_webhook_params *)p);
};

void discord_execute_webhook_params_from_json_v(char *json, size_t len, void *p) {
 discord_execute_webhook_params_from_json(json, len, (struct discord_execute_webhook_params*)p);
}

size_t discord_execute_webhook_params_to_json_v(char *json, size_t len, void *p) {
  return discord_execute_webhook_params_to_json(json, len, (struct discord_execute_webhook_params*)p);
}

void discord_execute_webhook_params_list_free_v(void **p) {
  discord_execute_webhook_params_list_free((struct discord_execute_webhook_params**)p);
}

void discord_execute_webhook_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_execute_webhook_params_list_from_json(str, len, (struct discord_execute_webhook_params ***)p);
}

size_t discord_execute_webhook_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_execute_webhook_params_list_to_json(str, len, (struct discord_execute_webhook_params **)p);
}


void discord_execute_webhook_params_cleanup(struct discord_execute_webhook_params *d) {
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */
  // p->wait is a scalar
  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */
  if (d->content)
    free(d->content);
  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */
  if (d->username)
    free(d->username);
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */
  if (d->avatar_url)
    free(d->avatar_url);
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */
  // p->tts is a scalar
  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */
  if (d->file)
    free(d->file);
  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
  if (d->embeds)
    discord_embed_free(d->embeds);
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */
  if (d->payload_json)
    free(d->payload_json);
  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
  if (d->allowed_mentions)
    discord_channel_allowed_mentions_free(d->allowed_mentions);
}

void discord_execute_webhook_params_init(struct discord_execute_webhook_params *p) {
  memset(p, 0, sizeof(struct discord_execute_webhook_params));
  /* specs/discord/webhook.endpoints-params.json:37:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query",
          "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)",
          "required":"one of content, file, embeds"
        }' */

  /* specs/discord/webhook.endpoints-params.json:41:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the message contents (up to 2000 characters)",
          "required":false
        }' */

  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default username of the webhook",
          "required":false
        }' */

  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, 
          "comment":"override the default avatar of the webhook" }' */

  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "tts", "type":{ "base":"bool" }, 
          "comment":"true if this is a TTS message",
          "required":false
        }' */

  /* specs/discord/webhook.endpoints-params.json:55:20
     '{ "name": "file", "type":{ "base":"char", "dec":"*" }, 
          "comment":"the contents of the file being sent",
          "required":"one of content, file, embeds"
        }' */

  /* specs/discord/webhook.endpoints-params.json:59:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, 
          "comment":"embedded rich content",
          "required":"one of content, file, embeds"
        }' */
  p->embeds = discord_embed_alloc();

  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "payload_json", "type":{ "base":"char", "dec":"*" }, 
          "comment":"See message create",
          "required":"multipart/form-data only"
        }' */

  /* specs/discord/webhook.endpoints-params.json:67:20
     '{ "name": "allowed_mentions", 
          "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" },
          "comment":"allowed mentions for the message",
          "required":"false"
        }' */
  p->allowed_mentions = discord_channel_allowed_mentions_alloc();

}
struct discord_execute_webhook_params* discord_execute_webhook_params_alloc() {
  struct discord_execute_webhook_params *p= malloc(sizeof(struct discord_execute_webhook_params));
  discord_execute_webhook_params_init(p);
  return p;
}

void discord_execute_webhook_params_free(struct discord_execute_webhook_params *p) {
  discord_execute_webhook_params_cleanup(p);
  free(p);
}

void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **p) {
  ntl_free((void**)p, (vfvp)discord_execute_webhook_params_cleanup);
}

void discord_execute_webhook_params_list_from_json(char *str, size_t len, struct discord_execute_webhook_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_execute_webhook_params);
  d.init_elem = discord_execute_webhook_params_init_v;
  d.elem_from_buf = discord_execute_webhook_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_execute_webhook_params_list_to_json(char *str, size_t len, struct discord_execute_webhook_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_execute_webhook_params_to_json_v);
}


void discord_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_edit_webhook_message_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
                "(content):?s,"
  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
                "(embeds):F,"
  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
                "(allowed_mentions):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
                &p->content,
  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
                discord_embed_list_from_json, &p->embeds,
  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
                discord_channel_allowed_mentions_from_json, p->allowed_mentions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_edit_webhook_message_params_use_default_inject_settings(struct discord_edit_webhook_message_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
  p->__M.arg_switches[0] = p->content;

  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
  p->__M.arg_switches[1] = p->embeds;

  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
  p->__M.arg_switches[2] = p->allowed_mentions;

}

size_t discord_edit_webhook_message_params_to_json(char *json, size_t len, struct discord_edit_webhook_message_params *p)
{
  size_t r;
  discord_edit_webhook_message_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
                "(content):s,"
  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
                "(embeds):F,"
  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
                "(allowed_mentions):F,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
                p->content,
  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
                discord_embed_list_to_json, p->embeds,
  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
                discord_channel_allowed_mentions_to_json, p->allowed_mentions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_edit_webhook_message_params_cleanup_v(void *p) {
  discord_edit_webhook_message_params_cleanup((struct discord_edit_webhook_message_params *)p);
}

void discord_edit_webhook_message_params_init_v(void *p) {
  discord_edit_webhook_message_params_init((struct discord_edit_webhook_message_params *)p);
}

void discord_edit_webhook_message_params_free_v(void *p) {
 discord_edit_webhook_message_params_free((struct discord_edit_webhook_message_params *)p);
};

void discord_edit_webhook_message_params_from_json_v(char *json, size_t len, void *p) {
 discord_edit_webhook_message_params_from_json(json, len, (struct discord_edit_webhook_message_params*)p);
}

size_t discord_edit_webhook_message_params_to_json_v(char *json, size_t len, void *p) {
  return discord_edit_webhook_message_params_to_json(json, len, (struct discord_edit_webhook_message_params*)p);
}

void discord_edit_webhook_message_params_list_free_v(void **p) {
  discord_edit_webhook_message_params_list_free((struct discord_edit_webhook_message_params**)p);
}

void discord_edit_webhook_message_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_edit_webhook_message_params_list_from_json(str, len, (struct discord_edit_webhook_message_params ***)p);
}

size_t discord_edit_webhook_message_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_edit_webhook_message_params_list_to_json(str, len, (struct discord_edit_webhook_message_params **)p);
}


void discord_edit_webhook_message_params_cleanup(struct discord_edit_webhook_message_params *d) {
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */
  if (d->content)
    free(d->content);
  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
  if (d->allowed_mentions)
    discord_channel_allowed_mentions_free(d->allowed_mentions);
}

void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *p) {
  memset(p, 0, sizeof(struct discord_edit_webhook_message_params));
  /* specs/discord/webhook.endpoints-params.json:81:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars" }' */

  /* specs/discord/webhook.endpoints-params.json:82:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects" }' */

  /* specs/discord/webhook.endpoints-params.json:83:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_channel_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message" }' */
  p->allowed_mentions = discord_channel_allowed_mentions_alloc();

}
struct discord_edit_webhook_message_params* discord_edit_webhook_message_params_alloc() {
  struct discord_edit_webhook_message_params *p= malloc(sizeof(struct discord_edit_webhook_message_params));
  discord_edit_webhook_message_params_init(p);
  return p;
}

void discord_edit_webhook_message_params_free(struct discord_edit_webhook_message_params *p) {
  discord_edit_webhook_message_params_cleanup(p);
  free(p);
}

void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **p) {
  ntl_free((void**)p, (vfvp)discord_edit_webhook_message_params_cleanup);
}

void discord_edit_webhook_message_params_list_from_json(char *str, size_t len, struct discord_edit_webhook_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_webhook_message_params);
  d.init_elem = discord_edit_webhook_message_params_init_v;
  d.elem_from_buf = discord_edit_webhook_message_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_edit_webhook_message_params_list_to_json(char *str, size_t len, struct discord_edit_webhook_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_edit_webhook_message_params_to_json_v);
}

