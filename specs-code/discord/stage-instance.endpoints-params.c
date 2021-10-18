/* This file is generated from specs/discord/stage-instance.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/stage-instance.endpoints-params.c
 * @see (null)
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_create_stage_instance_params_from_json(char *json, size_t len, struct discord_create_stage_instance_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_create_stage_instance_params *p = *pp;
  discord_create_stage_instance_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */
                "(channel_id):F,"
  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                "(topic):?s,"
  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
                "(privacy_level):d,",
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                &p->topic,
  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
                &p->privacy_level);
  ret = r;
}

size_t discord_create_stage_instance_params_to_json(char *json, size_t len, struct discord_create_stage_instance_params *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */
  arg_switches[0] = &p->channel_id;

  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  arg_switches[1] = p->topic;

  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
  if (p->privacy_level != 0)
    arg_switches[2] = &p->privacy_level;

  r=json_inject(json, len, 
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */
                "(channel_id):|F|,"
  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                "(topic):s,"
  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
                "(privacy_level):d,"
                "@arg_switches:b",
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                p->topic,
  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
                &p->privacy_level,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_stage_instance_params_cleanup_v(void *p) {
  discord_create_stage_instance_params_cleanup((struct discord_create_stage_instance_params *)p);
}

void discord_create_stage_instance_params_init_v(void *p) {
  discord_create_stage_instance_params_init((struct discord_create_stage_instance_params *)p);
}

void discord_create_stage_instance_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_stage_instance_params_from_json(json, len, (struct discord_create_stage_instance_params**)pp);
}

size_t discord_create_stage_instance_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_stage_instance_params_to_json(json, len, (struct discord_create_stage_instance_params*)p);
}

void discord_create_stage_instance_params_list_free_v(void **p) {
  discord_create_stage_instance_params_list_free((struct discord_create_stage_instance_params**)p);
}

void discord_create_stage_instance_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_stage_instance_params_list_from_json(str, len, (struct discord_create_stage_instance_params ***)p);
}

size_t discord_create_stage_instance_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_stage_instance_params_list_to_json(str, len, (struct discord_create_stage_instance_params **)p);
}


void discord_create_stage_instance_params_cleanup(struct discord_create_stage_instance_params *d) {
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */
  /* p->channel_id is a scalar */
  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  if (d->topic)
    free(d->topic);
  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
  /* p->privacy_level is a scalar */
}

void discord_create_stage_instance_params_init(struct discord_create_stage_instance_params *p) {
  memset(p, 0, sizeof(struct discord_create_stage_instance_params));
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */

  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */

  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */

}
void discord_create_stage_instance_params_list_free(struct discord_create_stage_instance_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_stage_instance_params_cleanup);
}

void discord_create_stage_instance_params_list_from_json(char *str, size_t len, struct discord_create_stage_instance_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_stage_instance_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_stage_instance_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_stage_instance_params_list_to_json(char *str, size_t len, struct discord_create_stage_instance_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_stage_instance_params_to_json_v);
}


void discord_modify_stage_instance_params_from_json(char *json, size_t len, struct discord_modify_stage_instance_params **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_modify_stage_instance_params *p = *pp;
  discord_modify_stage_instance_params_init(p);
  r=json_extract(json, len, 
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                "(topic):?s,"
  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
                "(privacy_level):d,",
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                &p->topic,
  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
                &p->privacy_level);
  ret = r;
}

size_t discord_modify_stage_instance_params_to_json(char *json, size_t len, struct discord_modify_stage_instance_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  arg_switches[0] = p->topic;

  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
  if (p->privacy_level != 0)
    arg_switches[1] = &p->privacy_level;

  r=json_inject(json, len, 
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                "(topic):s,"
  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
                "(privacy_level):d,"
                "@arg_switches:b",
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                p->topic,
  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
                &p->privacy_level,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_stage_instance_params_cleanup_v(void *p) {
  discord_modify_stage_instance_params_cleanup((struct discord_modify_stage_instance_params *)p);
}

void discord_modify_stage_instance_params_init_v(void *p) {
  discord_modify_stage_instance_params_init((struct discord_modify_stage_instance_params *)p);
}

void discord_modify_stage_instance_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_stage_instance_params_from_json(json, len, (struct discord_modify_stage_instance_params**)pp);
}

size_t discord_modify_stage_instance_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_stage_instance_params_to_json(json, len, (struct discord_modify_stage_instance_params*)p);
}

void discord_modify_stage_instance_params_list_free_v(void **p) {
  discord_modify_stage_instance_params_list_free((struct discord_modify_stage_instance_params**)p);
}

void discord_modify_stage_instance_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_stage_instance_params_list_from_json(str, len, (struct discord_modify_stage_instance_params ***)p);
}

size_t discord_modify_stage_instance_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_stage_instance_params_list_to_json(str, len, (struct discord_modify_stage_instance_params **)p);
}


void discord_modify_stage_instance_params_cleanup(struct discord_modify_stage_instance_params *d) {
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  if (d->topic)
    free(d->topic);
  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
  /* p->privacy_level is a scalar */
}

void discord_modify_stage_instance_params_init(struct discord_modify_stage_instance_params *p) {
  memset(p, 0, sizeof(struct discord_modify_stage_instance_params));
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */

  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */

}
void discord_modify_stage_instance_params_list_free(struct discord_modify_stage_instance_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_stage_instance_params_cleanup);
}

void discord_modify_stage_instance_params_list_from_json(char *str, size_t len, struct discord_modify_stage_instance_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_stage_instance_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_stage_instance_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_stage_instance_params_list_to_json(char *str, size_t len, struct discord_modify_stage_instance_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_stage_instance_params_to_json_v);
}

