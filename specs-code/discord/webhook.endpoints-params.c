/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/webhook.endpoints-params.c
 * @see https://discord.com/developers/docs/resources/webhook
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_create_webhook_params_from_json(char *json, size_t len, struct discord_create_webhook_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_create_webhook_params *p = *pp;
  discord_create_webhook_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                "(name):?s,"
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):?s,",
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                &p->name,
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                &p->avatar);
  ret = r;
}

size_t discord_create_webhook_params_to_json(char *json, size_t len, struct discord_create_webhook_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  arg_switches[0] = p->name;

  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (p->avatar != NULL)
    arg_switches[1] = p->avatar;

  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                "(name):s,"
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):s,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
                p->name,
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                p->avatar,
                arg_switches, sizeof(arg_switches), true);
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

void discord_create_webhook_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_webhook_params_from_json(json, len, (struct discord_create_webhook_params**)pp);
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
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */
  if (d->name)
    free(d->name);
  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (d->avatar)
    free(d->avatar);
}

void discord_create_webhook_params_init(struct discord_create_webhook_params *p) {
  memset(p, 0, sizeof(struct discord_create_webhook_params));
  /* specs/discord/webhook.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-80) chars" }' */

  /* specs/discord/webhook.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */

}
void discord_create_webhook_params_list_free(struct discord_create_webhook_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_webhook_params_cleanup);
}

void discord_create_webhook_params_list_from_json(char *str, size_t len, struct discord_create_webhook_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_webhook_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_webhook_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_webhook_params_list_to_json(char *str, size_t len, struct discord_create_webhook_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_webhook_params_to_json_v);
}


void discord_modify_webhook_params_from_json(char *json, size_t len, struct discord_modify_webhook_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_modify_webhook_params *p = *pp;
  discord_modify_webhook_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
                "(name):?s,"
  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):?s,"
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */
                "(channel_id):F,",
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
                &p->name,
  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                &p->avatar,
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */
                cee_strtoull, &p->channel_id);
  ret = r;
}

size_t discord_modify_webhook_params_to_json(char *json, size_t len, struct discord_modify_webhook_params *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (p->avatar != NULL)
    arg_switches[1] = p->avatar;

  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */
  if (p->channel_id != 0)
    arg_switches[2] = &p->channel_id;

  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
                "(name):s,"
  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):s,"
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
                p->name,
  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                p->avatar,
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */
                cee_ulltostr, &p->channel_id,
                arg_switches, sizeof(arg_switches), true);
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

void discord_modify_webhook_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_webhook_params_from_json(json, len, (struct discord_modify_webhook_params**)pp);
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
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
  if (d->name)
    free(d->name);
  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (d->avatar)
    free(d->avatar);
  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */
  /* p->channel_id is a scalar */
}

void discord_modify_webhook_params_init(struct discord_modify_webhook_params *p) {
  memset(p, 0, sizeof(struct discord_modify_webhook_params));
  /* specs/discord/webhook.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */

  /* specs/discord/webhook.endpoints-params.json:23:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */

  /* specs/discord/webhook.endpoints-params.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment":"the new channel id this webhook should be moved to" }' */

}
void discord_modify_webhook_params_list_free(struct discord_modify_webhook_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_webhook_params_cleanup);
}

void discord_modify_webhook_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_webhook_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_webhook_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_webhook_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_webhook_params_to_json_v);
}


void discord_modify_webhook_with_token_params_from_json(char *json, size_t len, struct discord_modify_webhook_with_token_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_modify_webhook_with_token_params *p = *pp;
  discord_modify_webhook_with_token_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
                "(name):?s,"
  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):?s,",
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
                &p->name,
  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                &p->avatar);
  ret = r;
}

size_t discord_modify_webhook_with_token_params_to_json(char *json, size_t len, struct discord_modify_webhook_with_token_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (p->avatar != NULL)
    arg_switches[1] = p->avatar;

  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
                "(name):s,"
  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                "(avatar):s,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
                p->name,
  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
                p->avatar,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_webhook_with_token_params_cleanup_v(void *p) {
  discord_modify_webhook_with_token_params_cleanup((struct discord_modify_webhook_with_token_params *)p);
}

void discord_modify_webhook_with_token_params_init_v(void *p) {
  discord_modify_webhook_with_token_params_init((struct discord_modify_webhook_with_token_params *)p);
}

void discord_modify_webhook_with_token_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_webhook_with_token_params_from_json(json, len, (struct discord_modify_webhook_with_token_params**)pp);
}

size_t discord_modify_webhook_with_token_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_webhook_with_token_params_to_json(json, len, (struct discord_modify_webhook_with_token_params*)p);
}

void discord_modify_webhook_with_token_params_list_free_v(void **p) {
  discord_modify_webhook_with_token_params_list_free((struct discord_modify_webhook_with_token_params**)p);
}

void discord_modify_webhook_with_token_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_webhook_with_token_params_list_from_json(str, len, (struct discord_modify_webhook_with_token_params ***)p);
}

size_t discord_modify_webhook_with_token_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_webhook_with_token_params_list_to_json(str, len, (struct discord_modify_webhook_with_token_params **)p);
}


void discord_modify_webhook_with_token_params_cleanup(struct discord_modify_webhook_with_token_params *d) {
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */
  if (d->name)
    free(d->name);
  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */
  if (d->avatar)
    free(d->avatar);
}

void discord_modify_webhook_with_token_params_init(struct discord_modify_webhook_with_token_params *p) {
  memset(p, 0, sizeof(struct discord_modify_webhook_with_token_params));
  /* specs/discord/webhook.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"name of the webhook(1-80) chars" }' */

  /* specs/discord/webhook.endpoints-params.json:34:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment":"base64 image for the default webhook avatar" }' */

}
void discord_modify_webhook_with_token_params_list_free(struct discord_modify_webhook_with_token_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_webhook_with_token_params_cleanup);
}

void discord_modify_webhook_with_token_params_list_from_json(char *str, size_t len, struct discord_modify_webhook_with_token_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_webhook_with_token_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_webhook_with_token_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_webhook_with_token_params_list_to_json(char *str, size_t len, struct discord_modify_webhook_with_token_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_webhook_with_token_params_to_json_v);
}


void discord_execute_webhook_params_from_json(char *json, size_t len, struct discord_execute_webhook_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_execute_webhook_params *p = *pp;
  discord_execute_webhook_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                "(content):?s,"
  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                "(username):?s,"
  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                "(avatar_url):?s,"
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                "(tts):b,"
  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                "(allowed_mentions):F,"
  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                "(components):F,"
  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,",
  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                &p->content,
  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                &p->username,
  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                &p->avatar_url,
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                &p->tts,
  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                discord_embed_from_json, &p->embeds,
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                discord_allowed_mentions_from_json, &p->allowed_mentions,
  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                discord_component_list_from_json, &p->components,
  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments);
  ret = r;
}

size_t discord_execute_webhook_params_to_json(char *json, size_t len, struct discord_execute_webhook_params *p)
{
  size_t r;
  void *arg_switches[10]={NULL};
  /* specs/discord/webhook.endpoints-params.json:44:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)" }' */
  arg_switches[0] = &p->wait;

  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  if (p->thread_id != 0)
    arg_switches[1] = &p->thread_id;

  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  if (p->content != NULL)
    arg_switches[2] = p->content;

  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  if (p->username != NULL)
    arg_switches[3] = p->username;

  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  if (p->avatar_url != NULL)
    arg_switches[4] = p->avatar_url;

  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  if (p->tts != false)
    arg_switches[5] = &p->tts;

  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[6] = p->embeds;

  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[7] = p->allowed_mentions;

  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  if (p->components != NULL)
    arg_switches[8] = p->components;

  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[9] = p->attachments;

  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                "(content):s,"
  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                "(username):s,"
  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                "(avatar_url):s,"
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                "(tts):b,"
  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                "(allowed_mentions):F,"
  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                "(components):F,"
  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
                p->content,
  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
                p->username,
  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
                p->avatar_url,
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                &p->tts,
  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
                discord_embed_to_json, p->embeds,
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
                discord_component_list_to_json, p->components,
  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
                arg_switches, sizeof(arg_switches), true);
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

void discord_execute_webhook_params_from_json_v(char *json, size_t len, void *pp) {
 discord_execute_webhook_params_from_json(json, len, (struct discord_execute_webhook_params**)pp);
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
  /* specs/discord/webhook.endpoints-params.json:44:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)" }' */
  /* p->wait is a scalar */
  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */
  /* p->thread_id is a scalar */
  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */
  if (d->content)
    free(d->content);
  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */
  if (d->username)
    free(d->username);
  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */
  if (d->avatar_url)
    free(d->avatar_url);
  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  /* p->tts is a scalar */
  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */
  if (d->embeds) {
    discord_embed_cleanup(d->embeds);
    free(d->embeds);
  }
  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */
  if (d->components)
    discord_component_list_free(d->components);
  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
}

void discord_execute_webhook_params_init(struct discord_execute_webhook_params *p) {
  memset(p, 0, sizeof(struct discord_execute_webhook_params));
  /* specs/discord/webhook.endpoints-params.json:44:20
     '{ "name": "wait", "type":{ "base":"bool"}, "loc":"query", "comment":"	waits for server confirmation of message send before response, and returns the created message body (defaults to false; when false a message that is not saved does not return an error)" }' */

  /* specs/discord/webhook.endpoints-params.json:45:20
     '{ "name": "thread_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "loc":"query", "comment":"Send a message to the specified thread withing a webhook's channel. The thread will automatically be unarchived", "inject_if_not":0 }' */

  /* specs/discord/webhook.endpoints-params.json:46:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not": null }' */

  /* specs/discord/webhook.endpoints-params.json:47:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"override the default username of the webhook", "inject_if_not": null }' */

  /* specs/discord/webhook.endpoints-params.json:48:20
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*" }, "comment":"override the default avatar of the webhook", "inject_if_not": null }' */

  /* specs/discord/webhook.endpoints-params.json:49:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */

  /* specs/discord/webhook.endpoints-params.json:50:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content", "inject_if_not":null }' */

  /* specs/discord/webhook.endpoints-params.json:51:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not": null }' */

  /* specs/discord/webhook.endpoints-params.json:52:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not": null }' */

  /* specs/discord/webhook.endpoints-params.json:53:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

}
void discord_execute_webhook_params_list_free(struct discord_execute_webhook_params **p) {
  ntl_free((void**)p, (vfvp)discord_execute_webhook_params_cleanup);
}

void discord_execute_webhook_params_list_from_json(char *str, size_t len, struct discord_execute_webhook_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_execute_webhook_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_execute_webhook_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_execute_webhook_params_list_to_json(char *str, size_t len, struct discord_execute_webhook_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_execute_webhook_params_to_json_v);
}


void discord_edit_webhook_message_params_from_json(char *json, size_t len, struct discord_edit_webhook_message_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_edit_webhook_message_params *p = *pp;
  discord_edit_webhook_message_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):?s,"
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,",
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                &p->content,
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_from_json, &p->embeds,
  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_from_json, &p->allowed_mentions,
  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments,
  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_from_json, &p->components);
  ret = r;
}

size_t discord_edit_webhook_message_params_to_json(char *json, size_t len, struct discord_edit_webhook_message_params *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (p->content != NULL)
    arg_switches[0] = p->content;

  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[1] = p->embeds;

  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[2] = p->allowed_mentions;

  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[3] = p->attachments;

  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (p->components != NULL)
    arg_switches[4] = p->components;

  r=json_inject(json, len, 
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                "(content):s,"
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                "(embeds):F,"
  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,"
                "@arg_switches:b",
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
                p->content,
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
                discord_embed_list_to_json, p->embeds,
  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_to_json, p->components,
                arg_switches, sizeof(arg_switches), true);
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

void discord_edit_webhook_message_params_from_json_v(char *json, size_t len, void *pp) {
 discord_edit_webhook_message_params_from_json(json, len, (struct discord_edit_webhook_message_params**)pp);
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
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (d->components)
    discord_component_list_free(d->components);
}

void discord_edit_webhook_message_params_init(struct discord_edit_webhook_message_params *p) {
  memset(p, 0, sizeof(struct discord_edit_webhook_message_params));
  /* specs/discord/webhook.endpoints-params.json:62:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"name of the webhook(1-2000) chars", "inject_if_not":null }' */

  /* specs/discord/webhook.endpoints-params.json:63:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"array of up to 10 embeds objects", "inject_if_not":null }' */

  /* specs/discord/webhook.endpoints-params.json:64:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */

  /* specs/discord/webhook.endpoints-params.json:65:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

  /* specs/discord/webhook.endpoints-params.json:66:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */

}
void discord_edit_webhook_message_params_list_free(struct discord_edit_webhook_message_params **p) {
  ntl_free((void**)p, (vfvp)discord_edit_webhook_message_params_cleanup);
}

void discord_edit_webhook_message_params_list_from_json(char *str, size_t len, struct discord_edit_webhook_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_webhook_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_edit_webhook_message_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_webhook_message_params_list_to_json(char *str, size_t len, struct discord_edit_webhook_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_edit_webhook_message_params_to_json_v);
}

