/* This file is generated from specs/webhook.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
*/


enum discord_webhook_types discord_webhook_types_from_string(char *s){
  if(strcasecmp("INCOMING", s) == 0) return DISCORD_WEBHOOK_INCOMING;
  if(strcasecmp("CHANNEL_FOLLOWER", s) == 0) return DISCORD_WEBHOOK_CHANNEL_FOLLOWER;
  abort();
}
char* discord_webhook_types_to_string(enum discord_webhook_types v){
  if (v == DISCORD_WEBHOOK_INCOMING) return "INCOMING";
  if (v == DISCORD_WEBHOOK_CHANNEL_FOLLOWER) return "CHANNEL_FOLLOWER";

  return (void*)0;
}
bool discord_webhook_types_has(enum discord_webhook_types v, char *s) {
  enum discord_webhook_types v1 = discord_webhook_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_webhook_from_json(char *json, size_t len, struct discord_webhook *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/webhook.json:21:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/webhook.json:22:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}'
  */
                "(type):d,"
  /* specs/webhook.json:23:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):F,"
  /* specs/webhook.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):F,"
  /* specs/webhook.json:25:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
                "(user):F,"
  /* specs/webhook.json:26:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
                "(name):s,"
  /* specs/webhook.json:27:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(avatar):?s,"
  /* specs/webhook.json:28:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(token):?s,"
  /* specs/webhook.json:29:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(application_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/webhook.json:21:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/webhook.json:22:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}'
  */
                &p->type,
  /* specs/webhook.json:23:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->guild_id,
  /* specs/webhook.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->channel_id,
  /* specs/webhook.json:25:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
                discord_user_from_json, p->user,
  /* specs/webhook.json:26:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
                p->name,
  /* specs/webhook.json:27:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->avatar,
  /* specs/webhook.json:28:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->token,
  /* specs/webhook.json:29:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->application_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_webhook_use_default_inject_settings(struct discord_webhook *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/webhook.json:21:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/webhook.json:22:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}'
  */
  p->__M.arg_switches[1] = &p->type;

  /* specs/webhook.json:23:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[2] = &p->guild_id;

  /* specs/webhook.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[3] = &p->channel_id;

  /* specs/webhook.json:25:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
  p->__M.arg_switches[4] = p->user;

  /* specs/webhook.json:26:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
  p->__M.arg_switches[5] = p->name;

  /* specs/webhook.json:27:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[6] = p->avatar;

  /* specs/webhook.json:28:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[7] = p->token;

  /* specs/webhook.json:29:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[8] = &p->application_id;

}

size_t discord_webhook_to_json(char *json, size_t len, struct discord_webhook *p)
{
  size_t r;
  discord_webhook_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/webhook.json:21:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/webhook.json:22:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}'
  */
                "(type):d,"
  /* specs/webhook.json:23:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(guild_id):|F|,"
  /* specs/webhook.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(channel_id):|F|,"
  /* specs/webhook.json:25:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
                "(user):F,"
  /* specs/webhook.json:26:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
                "(name):s,"
  /* specs/webhook.json:27:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(avatar):s,"
  /* specs/webhook.json:28:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(token):s,"
  /* specs/webhook.json:29:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(application_id):|F|,"
                "@arg_switches:b",
  /* specs/webhook.json:21:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/webhook.json:22:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}'
  */
                &p->type,
  /* specs/webhook.json:23:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->guild_id,
  /* specs/webhook.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->channel_id,
  /* specs/webhook.json:25:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
                discord_user_to_json, p->user,
  /* specs/webhook.json:26:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
                p->name,
  /* specs/webhook.json:27:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->avatar,
  /* specs/webhook.json:28:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->token,
  /* specs/webhook.json:29:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->application_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_webhook_cleanup_v(void *p) {
  discord_webhook_cleanup((struct discord_webhook *)p);
}

void discord_webhook_init_v(void *p) {
  discord_webhook_init((struct discord_webhook *)p);
}

void discord_webhook_free_v(void *p) {
 discord_webhook_free((struct discord_webhook *)p);
};

void discord_webhook_from_json_v(char *json, size_t len, void *p) {
 discord_webhook_from_json(json, len, (struct discord_webhook*)p);
}

size_t discord_webhook_to_json_v(char *json, size_t len, void *p) {
  return discord_webhook_to_json(json, len, (struct discord_webhook*)p);
}

void discord_webhook_list_free_v(void **p) {
  discord_webhook_list_free((struct discord_webhook**)p);
}

void discord_webhook_list_from_json_v(char *str, size_t len, void *p) {
  discord_webhook_list_from_json(str, len, (struct discord_webhook ***)p);
}

size_t discord_webhook_list_to_json_v(char *str, size_t len, void *p){
  return discord_webhook_list_to_json(str, len, (struct discord_webhook **)p);
}


void discord_webhook_cleanup(struct discord_webhook *d) {
  /* specs/webhook.json:21:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/webhook.json:22:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}'
  */
  //p->type is a scalar
  /* specs/webhook.json:23:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->guild_id is a scalar
  /* specs/webhook.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->channel_id is a scalar
  /* specs/webhook.json:25:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
  if (d->user)
    discord_user_free(d->user);
  /* specs/webhook.json:26:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */
  //p->name is a scalar
  /* specs/webhook.json:27:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->avatar)
    free(d->avatar);
  /* specs/webhook.json:28:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->token)
    free(d->token);
  /* specs/webhook.json:29:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->application_id is a scalar
}

void discord_webhook_init(struct discord_webhook *p) {
  memset(p, 0, sizeof(struct discord_webhook));
  /* specs/webhook.json:21:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/webhook.json:22:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }}'
  */

  /* specs/webhook.json:23:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/webhook.json:24:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/webhook.json:25:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }}'
  */
  p->user = discord_user_alloc();

  /* specs/webhook.json:26:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[WEBHOOK_NAME_LEN]" }}'
  */

  /* specs/webhook.json:27:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/webhook.json:28:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/webhook.json:29:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

}
struct discord_webhook* discord_webhook_alloc() {
  struct discord_webhook *p= (struct discord_webhook*)malloc(sizeof(struct discord_webhook));
  discord_webhook_init(p);
  return p;
}

void discord_webhook_free(struct discord_webhook *p) {
  discord_webhook_cleanup(p);
  free(p);
}

void discord_webhook_list_free(struct discord_webhook **p) {
  ntl_free((void**)p, (vfvp)discord_webhook_cleanup);
}

void discord_webhook_list_from_json(char *str, size_t len, struct discord_webhook ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_webhook);
  d.init_elem = discord_webhook_init_v;
  d.elem_from_buf = discord_webhook_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_webhook_list_to_json(char *str, size_t len, struct discord_webhook **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_webhook_to_json_v);
}

