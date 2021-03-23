/* This file is generated from specs/webhook.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
*/

void discord_webhook_dati_from_json(char *json, size_t len, struct discord_webhook_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */
                "(type):d,"
  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):F,"
  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):F,"
  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
                "(user):F,"
  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
                "(name):s,"
  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(avatar):?s,"
  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(token):?s,"
  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(application_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */
                &p->type,
  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->guild_id,
  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->channel_id,
  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
                discord_user_dati_from_json, p->user,
  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
                p->name,
  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->avatar,
  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->token,
  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->application_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_webhook_dati_use_default_inject_settings(struct discord_webhook_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */
  p->__M.arg_switches[1] = &p->type;

  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[2] = &p->guild_id;

  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[3] = &p->channel_id;

  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  p->__M.arg_switches[4] = p->user;

  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
  p->__M.arg_switches[5] = p->name;

  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[6] = p->avatar;

  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[7] = p->token;

  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[8] = &p->application_id;

}

size_t discord_webhook_dati_to_json(char *json, size_t len, struct discord_webhook_dati *p)
{
  size_t r;
  discord_webhook_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */
                "(type):d,"
  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):|F|,"
  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):|F|,"
  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
                "(user):F,"
  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
                "(name):s,"
  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(avatar):s,"
  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(token):s,"
  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(application_id):|F|,"
                "@arg_switches:b",
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */
                &p->type,
  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
                discord_user_dati_to_json, p->user,
  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
                p->name,
  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->avatar,
  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->token,
  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->application_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_webhook_dati_cleanup_v(void *p) {
  discord_webhook_dati_cleanup((struct discord_webhook_dati *)p);
}

void discord_webhook_dati_init_v(void *p) {
  discord_webhook_dati_init((struct discord_webhook_dati *)p);
}

void discord_webhook_dati_free_v(void *p) {
 discord_webhook_dati_free((struct discord_webhook_dati *)p);
};

void discord_webhook_dati_from_json_v(char *json, size_t len, void *p) {
 discord_webhook_dati_from_json(json, len, (struct discord_webhook_dati*)p);
}

size_t discord_webhook_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_webhook_dati_to_json(json, len, (struct discord_webhook_dati*)p);
}

void discord_webhook_dati_list_free_v(void **p) {
  discord_webhook_dati_list_free((struct discord_webhook_dati**)p);
}

void discord_webhook_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_webhook_dati_list_from_json(str, len, (struct discord_webhook_dati ***)p);
}

size_t discord_webhook_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_webhook_dati_list_to_json(str, len, (struct discord_webhook_dati **)p);
}


void discord_webhook_dati_cleanup(struct discord_webhook_dati *d) {
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */
  //p->type is a scalar
  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->guild_id is a scalar
  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->channel_id is a scalar
  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  if (d->user)
    discord_user_dati_free(d->user);
  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
  //p->name is a scalar
  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->avatar)
    free(d->avatar);
  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->token)
    free(d->token);
  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->application_id is a scalar
}

void discord_webhook_dati_init(struct discord_webhook_dati *p) {
  memset(p, 0, sizeof(struct discord_webhook_dati));
  /* specs/webhook.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/webhook.json:23:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"discord::webhook::types::code" }}'
  */

  /* specs/webhook.json:24:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/webhook.json:25:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/webhook.json:26:20
     '{ "name": "user", "type":{ "base":"discord::user::dati", "dec":"*" }}'
  */
  p->user = discord_user_dati_alloc();

  /* specs/webhook.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */

  /* specs/webhook.json:28:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/webhook.json:29:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/webhook.json:30:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

}
struct discord_webhook_dati* discord_webhook_dati_alloc() {
  struct discord_webhook_dati *p= (struct discord_webhook_dati*)malloc(sizeof(struct discord_webhook_dati));
  discord_webhook_dati_init(p);
  return p;
}

void discord_webhook_dati_free(struct discord_webhook_dati *p) {
  discord_webhook_dati_cleanup(p);
  free(p);
}

void discord_webhook_dati_list_free(struct discord_webhook_dati **p) {
  ntl_free((void**)p, (vfvp)discord_webhook_dati_cleanup);
}

void discord_webhook_dati_list_from_json(char *str, size_t len, struct discord_webhook_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_webhook_dati);
  d.init_elem = discord_webhook_dati_init_v;
  d.elem_from_buf = discord_webhook_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_webhook_dati_list_to_json(char *str, size_t len, struct discord_webhook_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_webhook_dati_to_json_v);
}

