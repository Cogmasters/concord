/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/emoji.endpoints-params.c
 * @see 
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_create_guild_emoji_params_from_json(char *json, size_t len, struct discord_create_guild_emoji_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_create_guild_emoji_params *p = *pp;
  discord_create_guild_emoji_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
                "(image):?s,"
  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
                "(roles):F,",
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
                &p->image,
  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
                ja_u64_list_from_json, &p->roles);
  ret = r;
}

size_t discord_create_guild_emoji_params_to_json(char *json, size_t len, struct discord_create_guild_emoji_params *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[0] = p->name;

  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
  arg_switches[1] = p->image;

  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  arg_switches[2] = p->roles;

  r=json_inject(json, len, 
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
                "(image):s,"
  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
                "(roles):F,"
                "@arg_switches:b",
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
                p->image,
  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
                ja_u64_list_to_json, p->roles,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_guild_emoji_params_cleanup_v(void *p) {
  discord_create_guild_emoji_params_cleanup((struct discord_create_guild_emoji_params *)p);
}

void discord_create_guild_emoji_params_init_v(void *p) {
  discord_create_guild_emoji_params_init((struct discord_create_guild_emoji_params *)p);
}

void discord_create_guild_emoji_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_guild_emoji_params_from_json(json, len, (struct discord_create_guild_emoji_params**)pp);
}

size_t discord_create_guild_emoji_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_emoji_params_to_json(json, len, (struct discord_create_guild_emoji_params*)p);
}

void discord_create_guild_emoji_params_list_free_v(void **p) {
  discord_create_guild_emoji_params_list_free((struct discord_create_guild_emoji_params**)p);
}

void discord_create_guild_emoji_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_emoji_params_list_from_json(str, len, (struct discord_create_guild_emoji_params ***)p);
}

size_t discord_create_guild_emoji_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_emoji_params_list_to_json(str, len, (struct discord_create_guild_emoji_params **)p);
}


void discord_create_guild_emoji_params_cleanup(struct discord_create_guild_emoji_params *d) {
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
  if (d->image)
    free(d->image);
  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
}

void discord_create_guild_emoji_params_init(struct discord_create_guild_emoji_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_emoji_params));
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */

  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */

}
void discord_create_guild_emoji_params_list_free(struct discord_create_guild_emoji_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_guild_emoji_params_cleanup);
}

void discord_create_guild_emoji_params_list_from_json(char *str, size_t len, struct discord_create_guild_emoji_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_emoji_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_guild_emoji_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_emoji_params_list_to_json(char *str, size_t len, struct discord_create_guild_emoji_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_guild_emoji_params_to_json_v);
}


void discord_modify_guild_emoji_params_from_json(char *json, size_t len, struct discord_modify_guild_emoji_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_modify_guild_emoji_params *p = *pp;
  discord_modify_guild_emoji_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
                "(roles):F,",
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
                ja_u64_list_from_json, &p->roles);
  ret = r;
}

size_t discord_modify_guild_emoji_params_to_json(char *json, size_t len, struct discord_modify_guild_emoji_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[0] = p->name;

  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  arg_switches[1] = p->roles;

  r=json_inject(json, len, 
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
                "(roles):F,"
                "@arg_switches:b",
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
                ja_u64_list_to_json, p->roles,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_emoji_params_cleanup_v(void *p) {
  discord_modify_guild_emoji_params_cleanup((struct discord_modify_guild_emoji_params *)p);
}

void discord_modify_guild_emoji_params_init_v(void *p) {
  discord_modify_guild_emoji_params_init((struct discord_modify_guild_emoji_params *)p);
}

void discord_modify_guild_emoji_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_guild_emoji_params_from_json(json, len, (struct discord_modify_guild_emoji_params**)pp);
}

size_t discord_modify_guild_emoji_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_emoji_params_to_json(json, len, (struct discord_modify_guild_emoji_params*)p);
}

void discord_modify_guild_emoji_params_list_free_v(void **p) {
  discord_modify_guild_emoji_params_list_free((struct discord_modify_guild_emoji_params**)p);
}

void discord_modify_guild_emoji_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_emoji_params_list_from_json(str, len, (struct discord_modify_guild_emoji_params ***)p);
}

size_t discord_modify_guild_emoji_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_emoji_params_list_to_json(str, len, (struct discord_modify_guild_emoji_params **)p);
}


void discord_modify_guild_emoji_params_cleanup(struct discord_modify_guild_emoji_params *d) {
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
}

void discord_modify_guild_emoji_params_init(struct discord_modify_guild_emoji_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_emoji_params));
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */

}
void discord_modify_guild_emoji_params_list_free(struct discord_modify_guild_emoji_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_emoji_params_cleanup);
}

void discord_modify_guild_emoji_params_list_from_json(char *str, size_t len, struct discord_modify_guild_emoji_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_emoji_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_guild_emoji_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_emoji_params_list_to_json(char *str, size_t len, struct discord_modify_guild_emoji_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_emoji_params_to_json_v);
}

