/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/user.endpoints-params.c
 * @see https://discord.com/developers/docs/resources/user
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_modify_current_user_params_from_json(char *json, size_t len, struct discord_modify_current_user_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_modify_current_user_params *p = *pp;
  discord_modify_current_user_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/user.endpoints-params.json:12:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
                "(username):?s,"
  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
                "(avatar):?s,",
  /* specs/discord/user.endpoints-params.json:12:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
                &p->username,
  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
                &p->avatar);
  ret = r;
}

size_t discord_modify_current_user_params_to_json(char *json, size_t len, struct discord_modify_current_user_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* specs/discord/user.endpoints-params.json:12:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->username;

  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
  arg_switches[1] = p->avatar;

  r=json_inject(json, len, 
  /* specs/discord/user.endpoints-params.json:12:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
                "(username):s,"
  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
                "(avatar):s,"
                "@arg_switches:b",
  /* specs/discord/user.endpoints-params.json:12:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
                p->username,
  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
                p->avatar,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_current_user_params_cleanup_v(void *p) {
  discord_modify_current_user_params_cleanup((struct discord_modify_current_user_params *)p);
}

void discord_modify_current_user_params_init_v(void *p) {
  discord_modify_current_user_params_init((struct discord_modify_current_user_params *)p);
}

void discord_modify_current_user_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_current_user_params_from_json(json, len, (struct discord_modify_current_user_params**)pp);
}

size_t discord_modify_current_user_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_current_user_params_to_json(json, len, (struct discord_modify_current_user_params*)p);
}

void discord_modify_current_user_params_list_free_v(void **p) {
  discord_modify_current_user_params_list_free((struct discord_modify_current_user_params**)p);
}

void discord_modify_current_user_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_current_user_params_list_from_json(str, len, (struct discord_modify_current_user_params ***)p);
}

size_t discord_modify_current_user_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_current_user_params_list_to_json(str, len, (struct discord_modify_current_user_params **)p);
}


void discord_modify_current_user_params_cleanup(struct discord_modify_current_user_params *d) {
  /* specs/discord/user.endpoints-params.json:12:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */
  if (d->username)
    free(d->username);
  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */
  if (d->avatar)
    free(d->avatar);
}

void discord_modify_current_user_params_init(struct discord_modify_current_user_params *p) {
  memset(p, 0, sizeof(struct discord_modify_current_user_params));
  /* specs/discord/user.endpoints-params.json:12:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/user.endpoints-params.json:13:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*"}, "comment":"base64 encoded image data"}' */

}
void discord_modify_current_user_params_list_free(struct discord_modify_current_user_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_current_user_params_cleanup);
}

void discord_modify_current_user_params_list_from_json(char *str, size_t len, struct discord_modify_current_user_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_current_user_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_current_user_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_current_user_params_list_to_json(char *str, size_t len, struct discord_modify_current_user_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_current_user_params_to_json_v);
}


void discord_create_dm_params_from_json(char *json, size_t len, struct discord_create_dm_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_create_dm_params *p = *pp;
  discord_create_dm_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/user.endpoints-params.json:22:20
     '{ "name": "recipient_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the recipient to open a DM channel with", "inject_if_not":0 }' */
                "(recipient_id):F,",
  /* specs/discord/user.endpoints-params.json:22:20
     '{ "name": "recipient_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the recipient to open a DM channel with", "inject_if_not":0 }' */
                cee_strtoull, &p->recipient_id);
  ret = r;
}

size_t discord_create_dm_params_to_json(char *json, size_t len, struct discord_create_dm_params *p)
{
  size_t r;
  void *arg_switches[1]={NULL};
  /* specs/discord/user.endpoints-params.json:22:20
     '{ "name": "recipient_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the recipient to open a DM channel with", "inject_if_not":0 }' */
  if (p->recipient_id != 0)
    arg_switches[0] = &p->recipient_id;

  r=json_inject(json, len, 
  /* specs/discord/user.endpoints-params.json:22:20
     '{ "name": "recipient_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the recipient to open a DM channel with", "inject_if_not":0 }' */
                "(recipient_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/user.endpoints-params.json:22:20
     '{ "name": "recipient_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the recipient to open a DM channel with", "inject_if_not":0 }' */
                cee_ulltostr, &p->recipient_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_dm_params_cleanup_v(void *p) {
  discord_create_dm_params_cleanup((struct discord_create_dm_params *)p);
}

void discord_create_dm_params_init_v(void *p) {
  discord_create_dm_params_init((struct discord_create_dm_params *)p);
}

void discord_create_dm_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_dm_params_from_json(json, len, (struct discord_create_dm_params**)pp);
}

size_t discord_create_dm_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_dm_params_to_json(json, len, (struct discord_create_dm_params*)p);
}

void discord_create_dm_params_list_free_v(void **p) {
  discord_create_dm_params_list_free((struct discord_create_dm_params**)p);
}

void discord_create_dm_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_dm_params_list_from_json(str, len, (struct discord_create_dm_params ***)p);
}

size_t discord_create_dm_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_dm_params_list_to_json(str, len, (struct discord_create_dm_params **)p);
}


void discord_create_dm_params_cleanup(struct discord_create_dm_params *d) {
  /* specs/discord/user.endpoints-params.json:22:20
     '{ "name": "recipient_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the recipient to open a DM channel with", "inject_if_not":0 }' */
  /* p->recipient_id is a scalar */
}

void discord_create_dm_params_init(struct discord_create_dm_params *p) {
  memset(p, 0, sizeof(struct discord_create_dm_params));
  /* specs/discord/user.endpoints-params.json:22:20
     '{ "name": "recipient_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the recipient to open a DM channel with", "inject_if_not":0 }' */

}
void discord_create_dm_params_list_free(struct discord_create_dm_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_dm_params_cleanup);
}

void discord_create_dm_params_list_from_json(char *str, size_t len, struct discord_create_dm_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_dm_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_dm_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_dm_params_list_to_json(char *str, size_t len, struct discord_create_dm_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_dm_params_to_json_v);
}


void discord_create_group_dm_params_from_json(char *json, size_t len, struct discord_create_group_dm_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_create_group_dm_params *p = *pp;
  discord_create_group_dm_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/user.endpoints-params.json:31:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
                "(access_tokens):F,"
  /* specs/discord/user.endpoints-params.json:33:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"a dictionary of user ids to their respective nicknames"}' */
                "(nicks):F,",
  /* specs/discord/user.endpoints-params.json:31:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
                ja_str_list_from_json, &p->access_tokens,
  /* specs/discord/user.endpoints-params.json:33:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"a dictionary of user ids to their respective nicknames"}' */
                ja_u64_list_from_json, &p->nicks);
  ret = r;
}

size_t discord_create_group_dm_params_to_json(char *json, size_t len, struct discord_create_group_dm_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* specs/discord/user.endpoints-params.json:31:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
  arg_switches[0] = p->access_tokens;

  /* specs/discord/user.endpoints-params.json:33:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"a dictionary of user ids to their respective nicknames"}' */
  arg_switches[1] = p->nicks;

  r=json_inject(json, len, 
  /* specs/discord/user.endpoints-params.json:31:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
                "(access_tokens):F,"
  /* specs/discord/user.endpoints-params.json:33:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"a dictionary of user ids to their respective nicknames"}' */
                "(nicks):F,"
                "@arg_switches:b",
  /* specs/discord/user.endpoints-params.json:31:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
                ja_str_list_to_json, p->access_tokens,
  /* specs/discord/user.endpoints-params.json:33:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"a dictionary of user ids to their respective nicknames"}' */
                ja_u64_list_to_json, p->nicks,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_group_dm_params_cleanup_v(void *p) {
  discord_create_group_dm_params_cleanup((struct discord_create_group_dm_params *)p);
}

void discord_create_group_dm_params_init_v(void *p) {
  discord_create_group_dm_params_init((struct discord_create_group_dm_params *)p);
}

void discord_create_group_dm_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_group_dm_params_from_json(json, len, (struct discord_create_group_dm_params**)pp);
}

size_t discord_create_group_dm_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_group_dm_params_to_json(json, len, (struct discord_create_group_dm_params*)p);
}

void discord_create_group_dm_params_list_free_v(void **p) {
  discord_create_group_dm_params_list_free((struct discord_create_group_dm_params**)p);
}

void discord_create_group_dm_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_group_dm_params_list_from_json(str, len, (struct discord_create_group_dm_params ***)p);
}

size_t discord_create_group_dm_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_group_dm_params_list_to_json(str, len, (struct discord_create_group_dm_params **)p);
}


void discord_create_group_dm_params_cleanup(struct discord_create_group_dm_params *d) {
  /* specs/discord/user.endpoints-params.json:31:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */
  if (d->access_tokens)
    ja_str_list_free(d->access_tokens);
  /* specs/discord/user.endpoints-params.json:33:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"a dictionary of user ids to their respective nicknames"}' */
  if (d->nicks)
    ja_u64_list_free(d->nicks);
}

void discord_create_group_dm_params_init(struct discord_create_group_dm_params *p) {
  memset(p, 0, sizeof(struct discord_create_group_dm_params));
  /* specs/discord/user.endpoints-params.json:31:20
     '{ "name": "access_tokens", "type":{ "base":"ja_str", "dec":"ntl" }, 
          "comment":"access tokens of users that have granted your app the gdm.join scope"}' */

  /* specs/discord/user.endpoints-params.json:33:19
     '{ "name":"nicks", "type":{ "base":"ja_u64", "dec":"ntl"}, 
          "comment":"a dictionary of user ids to their respective nicknames"}' */

}
void discord_create_group_dm_params_list_free(struct discord_create_group_dm_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_group_dm_params_cleanup);
}

void discord_create_group_dm_params_list_from_json(char *str, size_t len, struct discord_create_group_dm_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_group_dm_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_group_dm_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_group_dm_params_list_to_json(char *str, size_t len, struct discord_create_group_dm_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_group_dm_params_to_json_v);
}

