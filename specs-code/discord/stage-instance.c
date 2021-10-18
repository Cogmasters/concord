/* This file is generated from specs/discord/stage-instance.json, Please don't edit it. */
/**
 * @file specs-code/discord/stage-instance.c
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


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_stage_instance_privacy_level_list_free_v(void **p) {
  discord_stage_instance_privacy_level_list_free((enum discord_stage_instance_privacy_level**)p);
}

void discord_stage_instance_privacy_level_list_from_json_v(char *str, size_t len, void *p) {
  discord_stage_instance_privacy_level_list_from_json(str, len, (enum discord_stage_instance_privacy_level ***)p);
}

size_t discord_stage_instance_privacy_level_list_to_json_v(char *str, size_t len, void *p){
  return discord_stage_instance_privacy_level_list_to_json(str, len, (enum discord_stage_instance_privacy_level **)p);
}

enum discord_stage_instance_privacy_level discord_stage_instance_privacy_level_eval(char *s){
  if(strcasecmp("PUBLIC", s) == 0) return DISCORD_STAGE_INSTANCE_PUBLIC;
  if(strcasecmp("GUILD_ONLY", s) == 0) return DISCORD_STAGE_INSTANCE_GUILD_ONLY;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_stage_instance_privacy_level_print(enum discord_stage_instance_privacy_level v){

  switch (v) {
  case DISCORD_STAGE_INSTANCE_PUBLIC: return "PUBLIC";
  case DISCORD_STAGE_INSTANCE_GUILD_ONLY: return "GUILD_ONLY";
  }

  return NULL;
}

void discord_stage_instance_privacy_level_list_free(enum discord_stage_instance_privacy_level **p) {
  ntl_free((void**)p, NULL);
}

void discord_stage_instance_privacy_level_list_from_json(char *str, size_t len, enum discord_stage_instance_privacy_level ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_stage_instance_privacy_level);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_stage_instance_privacy_level_list_to_json(char *str, size_t len, enum discord_stage_instance_privacy_level **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_stage_instance_from_json(char *json, size_t len, struct discord_stage_instance **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_stage_instance *p = *pp;
  discord_stage_instance_init(p);
  r=json_extract(json, len, 
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */
                "(id):F,"
  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */
                "(guild_id):F,"
  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */
                "(channel_id):F,"
  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                "(topic):?s,"
  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */
                "(privacy_level):d,"
  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */
                "(discoverable_disabled):b,",
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */
                cee_strtoull, &p->id,
  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                &p->topic,
  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */
                &p->privacy_level,
  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */
                &p->discoverable_disabled);
  ret = r;
}

size_t discord_stage_instance_to_json(char *json, size_t len, struct discord_stage_instance *p)
{
  size_t r;
  void *arg_switches[6]={NULL};
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */
  arg_switches[0] = &p->id;

  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */
  arg_switches[1] = &p->guild_id;

  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */
  arg_switches[2] = &p->channel_id;

  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  arg_switches[3] = p->topic;

  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */
  arg_switches[4] = &p->privacy_level;

  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */
  arg_switches[5] = &p->discoverable_disabled;

  r=json_inject(json, len, 
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */
                "(id):|F|,"
  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */
                "(guild_id):|F|,"
  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */
                "(channel_id):|F|,"
  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                "(topic):s,"
  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */
                "(privacy_level):d,"
  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */
                "(discoverable_disabled):b,"
                "@arg_switches:b",
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
                p->topic,
  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */
                &p->privacy_level,
  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */
                &p->discoverable_disabled,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_stage_instance_cleanup_v(void *p) {
  discord_stage_instance_cleanup((struct discord_stage_instance *)p);
}

void discord_stage_instance_init_v(void *p) {
  discord_stage_instance_init((struct discord_stage_instance *)p);
}

void discord_stage_instance_from_json_v(char *json, size_t len, void *pp) {
 discord_stage_instance_from_json(json, len, (struct discord_stage_instance**)pp);
}

size_t discord_stage_instance_to_json_v(char *json, size_t len, void *p) {
  return discord_stage_instance_to_json(json, len, (struct discord_stage_instance*)p);
}

void discord_stage_instance_list_free_v(void **p) {
  discord_stage_instance_list_free((struct discord_stage_instance**)p);
}

void discord_stage_instance_list_from_json_v(char *str, size_t len, void *p) {
  discord_stage_instance_list_from_json(str, len, (struct discord_stage_instance ***)p);
}

size_t discord_stage_instance_list_to_json_v(char *str, size_t len, void *p){
  return discord_stage_instance_list_to_json(str, len, (struct discord_stage_instance **)p);
}


void discord_stage_instance_cleanup(struct discord_stage_instance *d) {
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */
  /* p->id is a scalar */
  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */
  /* p->guild_id is a scalar */
  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */
  /* p->channel_id is a scalar */
  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  if (d->topic)
    free(d->topic);
  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */
  /* p->privacy_level is a scalar */
  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */
  /* p->discoverable_disabled is a scalar */
}

void discord_stage_instance_init(struct discord_stage_instance *p) {
  memset(p, 0, sizeof(struct discord_stage_instance));
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */

  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */

  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */

  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */

  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */

  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */

}
void discord_stage_instance_list_free(struct discord_stage_instance **p) {
  ntl_free((void**)p, (vfvp)discord_stage_instance_cleanup);
}

void discord_stage_instance_list_from_json(char *str, size_t len, struct discord_stage_instance ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_stage_instance);
  d.init_elem = NULL;
  d.elem_from_buf = discord_stage_instance_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_stage_instance_list_to_json(char *str, size_t len, struct discord_stage_instance **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_stage_instance_to_json_v);
}

