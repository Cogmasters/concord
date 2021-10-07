/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/invite.endpoints-params.c
 * @see https://discord.com/developers/docs/resources/invite
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_get_invite_params_from_json(char *json, size_t len, struct discord_get_invite_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_get_invite_params *p = *pp;
  discord_get_invite_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/invite.endpoints-params.json:12:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */
                "(with_counts):b,"
  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */
                "(with_expiration):b,",
  /* specs/discord/invite.endpoints-params.json:12:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */
                &p->with_counts,
  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */
                &p->with_expiration);
  ret = r;
}

size_t discord_get_invite_params_to_json(char *json, size_t len, struct discord_get_invite_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* specs/discord/invite.endpoints-params.json:12:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */
  arg_switches[0] = &p->with_counts;

  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */
  arg_switches[1] = &p->with_expiration;

  r=json_inject(json, len, 
  /* specs/discord/invite.endpoints-params.json:12:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */
                "(with_counts):b,"
  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */
                "(with_expiration):b,"
                "@arg_switches:b",
  /* specs/discord/invite.endpoints-params.json:12:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */
                &p->with_counts,
  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */
                &p->with_expiration,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_get_invite_params_cleanup_v(void *p) {
  discord_get_invite_params_cleanup((struct discord_get_invite_params *)p);
}

void discord_get_invite_params_init_v(void *p) {
  discord_get_invite_params_init((struct discord_get_invite_params *)p);
}

void discord_get_invite_params_from_json_v(char *json, size_t len, void *pp) {
 discord_get_invite_params_from_json(json, len, (struct discord_get_invite_params**)pp);
}

size_t discord_get_invite_params_to_json_v(char *json, size_t len, void *p) {
  return discord_get_invite_params_to_json(json, len, (struct discord_get_invite_params*)p);
}

void discord_get_invite_params_list_free_v(void **p) {
  discord_get_invite_params_list_free((struct discord_get_invite_params**)p);
}

void discord_get_invite_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_get_invite_params_list_from_json(str, len, (struct discord_get_invite_params ***)p);
}

size_t discord_get_invite_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_get_invite_params_list_to_json(str, len, (struct discord_get_invite_params **)p);
}


void discord_get_invite_params_cleanup(struct discord_get_invite_params *d) {
  /* specs/discord/invite.endpoints-params.json:12:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */
  /* p->with_counts is a scalar */
  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */
  /* p->with_expiration is a scalar */
}

void discord_get_invite_params_init(struct discord_get_invite_params *p) {
  memset(p, 0, sizeof(struct discord_get_invite_params));
  /* specs/discord/invite.endpoints-params.json:12:20
     '{ "name": "with_counts", "type":{ "base":"bool" }, "comment":"whether the invite should contain approximate member counts"}' */

  /* specs/discord/invite.endpoints-params.json:13:20
     '{ "name": "with_expiration", "type":{ "base":"bool" }, "comment":"whether the invite should contain the expiration date"}' */

}
void discord_get_invite_params_list_free(struct discord_get_invite_params **p) {
  ntl_free((void**)p, (vfvp)discord_get_invite_params_cleanup);
}

void discord_get_invite_params_list_from_json(char *str, size_t len, struct discord_get_invite_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_get_invite_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_get_invite_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_get_invite_params_list_to_json(char *str, size_t len, struct discord_get_invite_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_get_invite_params_to_json_v);
}

