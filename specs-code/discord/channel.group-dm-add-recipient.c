/* This file is generated from specs/discord/channel.group-dm-add-recipient.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
                "(access_token):?s,"
  /* specs/discord/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */
                "(nick):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
                &p->access_token,
  /* specs/discord/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */
                &p->nick,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_group_dm_add_recipient_params_use_default_inject_settings(struct discord_group_dm_add_recipient_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[0] = p->access_token;

  /* specs/discord/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->nick;

}

size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p)
{
  size_t r;
  discord_group_dm_add_recipient_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
                "(access_token):s,"
  /* specs/discord/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */
                "(nick):s,"
                "@arg_switches:b",
  /* specs/discord/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
                p->access_token,
  /* specs/discord/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */
                p->nick,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_group_dm_add_recipient_params_cleanup_v(void *p) {
  discord_group_dm_add_recipient_params_cleanup((struct discord_group_dm_add_recipient_params *)p);
}

void discord_group_dm_add_recipient_params_init_v(void *p) {
  discord_group_dm_add_recipient_params_init((struct discord_group_dm_add_recipient_params *)p);
}

void discord_group_dm_add_recipient_params_free_v(void *p) {
 discord_group_dm_add_recipient_params_free((struct discord_group_dm_add_recipient_params *)p);
};

void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *p) {
 discord_group_dm_add_recipient_params_from_json(json, len, (struct discord_group_dm_add_recipient_params*)p);
}

size_t discord_group_dm_add_recipient_params_to_json_v(char *json, size_t len, void *p) {
  return discord_group_dm_add_recipient_params_to_json(json, len, (struct discord_group_dm_add_recipient_params*)p);
}

void discord_group_dm_add_recipient_params_list_free_v(void **p) {
  discord_group_dm_add_recipient_params_list_free((struct discord_group_dm_add_recipient_params**)p);
}

void discord_group_dm_add_recipient_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_group_dm_add_recipient_params_list_from_json(str, len, (struct discord_group_dm_add_recipient_params ***)p);
}

size_t discord_group_dm_add_recipient_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_group_dm_add_recipient_params_list_to_json(str, len, (struct discord_group_dm_add_recipient_params **)p);
}


void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *d) {
  /* specs/discord/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */
  if (d->access_token)
    free(d->access_token);
  /* specs/discord/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */
  if (d->nick)
    free(d->nick);
}

void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p) {
  memset(p, 0, sizeof(struct discord_group_dm_add_recipient_params));
  /* specs/discord/channel.group-dm-add-recipient.json:11:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*"}}'
  */

  /* specs/discord/channel.group-dm-add-recipient.json:12:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*"}}'
  */

}
struct discord_group_dm_add_recipient_params* discord_group_dm_add_recipient_params_alloc() {
  struct discord_group_dm_add_recipient_params *p= (struct discord_group_dm_add_recipient_params*)malloc(sizeof(struct discord_group_dm_add_recipient_params));
  discord_group_dm_add_recipient_params_init(p);
  return p;
}

void discord_group_dm_add_recipient_params_free(struct discord_group_dm_add_recipient_params *p) {
  discord_group_dm_add_recipient_params_cleanup(p);
  free(p);
}

void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p) {
  ntl_free((void**)p, (vfvp)discord_group_dm_add_recipient_params_cleanup);
}

void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_group_dm_add_recipient_params);
  d.init_elem = discord_group_dm_add_recipient_params_init_v;
  d.elem_from_buf = discord_group_dm_add_recipient_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_group_dm_add_recipient_params_to_json_v);
}

