/* This file is generated from discord/guild_template.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild_template.c
 * @see https://discord.com/developers/docs/resources/guild-template
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_guild_template_from_json_p(char *json, size_t len, struct discord_guild_template **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_guild_template_from_json(json, len, *pp);
}
void discord_guild_template_from_json(char *json, size_t len, struct discord_guild_template *p)
{
  discord_guild_template_init(p);
  json_extract(json, len, 
  /* discord/guild_template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
                "(code):?s,"
  /* discord/guild_template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* discord/guild_template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                "(description):?s,"
  /* discord/guild_template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
                "(usage_count):d,"
  /* discord/guild_template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(creator_id):F,"
  /* discord/guild_template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
                "(creator):F,"
  /* discord/guild_template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(created_at):F,"
  /* discord/guild_template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(updated_at):F,"
  /* discord/guild_template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(source_guild_id):F,"
  /* discord/guild_template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
                "(serialized_source_guild):F,"
  /* discord/guild_template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
                "(is_dirty):F,",
  /* discord/guild_template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
                &p->code,
  /* discord/guild_template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* discord/guild_template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                &p->description,
  /* discord/guild_template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
                &p->usage_count,
  /* discord/guild_template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->creator_id,
  /* discord/guild_template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
                discord_user_from_json_p, &p->creator,
  /* discord/guild_template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->created_at,
  /* discord/guild_template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->updated_at,
  /* discord/guild_template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->source_guild_id,
  /* discord/guild_template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
                discord_guild_from_json_p, &p->serialized_source_guild,
  /* discord/guild_template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
                cee_strndup, &p->is_dirty);
}

size_t discord_guild_template_to_json(char *json, size_t len, struct discord_guild_template *p)
{
  size_t r;
  void *arg_switches[11]={NULL};
  /* discord/guild_template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[0] = p->code;

  /* discord/guild_template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[1] = p->name;

  /* discord/guild_template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[2] = p->description;

  /* discord/guild_template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
  arg_switches[3] = &p->usage_count;

  /* discord/guild_template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[4] = &p->creator_id;

  /* discord/guild_template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  arg_switches[5] = p->creator;

  /* discord/guild_template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  arg_switches[6] = &p->created_at;

  /* discord/guild_template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  arg_switches[7] = &p->updated_at;

  /* discord/guild_template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[8] = &p->source_guild_id;

  /* discord/guild_template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
  arg_switches[9] = p->serialized_source_guild;

  /* discord/guild_template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
  arg_switches[10] = p->is_dirty;

  r=json_inject(json, len, 
  /* discord/guild_template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
                "(code):s,"
  /* discord/guild_template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* discord/guild_template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                "(description):s,"
  /* discord/guild_template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
                "(usage_count):d,"
  /* discord/guild_template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(creator_id):|F|,"
  /* discord/guild_template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
                "(creator):F,"
  /* discord/guild_template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(created_at):|F|,"
  /* discord/guild_template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(updated_at):|F|,"
  /* discord/guild_template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(source_guild_id):|F|,"
  /* discord/guild_template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
                "(serialized_source_guild):F,"
  /* discord/guild_template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
                "(is_dirty):s,"
                "@arg_switches:b",
  /* discord/guild_template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
                p->code,
  /* discord/guild_template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* discord/guild_template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                p->description,
  /* discord/guild_template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
                &p->usage_count,
  /* discord/guild_template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->creator_id,
  /* discord/guild_template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
                discord_user_to_json, p->creator,
  /* discord/guild_template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->created_at,
  /* discord/guild_template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->updated_at,
  /* discord/guild_template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->source_guild_id,
  /* discord/guild_template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
                discord_guild_to_json, p->serialized_source_guild,
  /* discord/guild_template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
                p->is_dirty,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_guild_template_cleanup_v(void *p) {
  discord_guild_template_cleanup((struct discord_guild_template *)p);
}

void discord_guild_template_init_v(void *p) {
  discord_guild_template_init((struct discord_guild_template *)p);
}

void discord_guild_template_from_json_v(char *json, size_t len, void *p) {
 discord_guild_template_from_json(json, len, (struct discord_guild_template*)p);
}

size_t discord_guild_template_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_template_to_json(json, len, (struct discord_guild_template*)p);
}

void discord_guild_template_list_free_v(void **p) {
  discord_guild_template_list_free((struct discord_guild_template**)p);
}

void discord_guild_template_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_template_list_from_json(str, len, (struct discord_guild_template ***)p);
}

size_t discord_guild_template_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_template_list_to_json(str, len, (struct discord_guild_template **)p);
}


void discord_guild_template_cleanup(struct discord_guild_template *d) {
  /* discord/guild_template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
  if (d->code)
    free(d->code);
  /* discord/guild_template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* discord/guild_template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  if (d->description)
    free(d->description);
  /* discord/guild_template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
  (void)d->usage_count;
  /* discord/guild_template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->creator_id;
  /* discord/guild_template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  if (d->creator) {
    discord_user_cleanup(d->creator);
    free(d->creator);
  }
  /* discord/guild_template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  (void)d->created_at;
  /* discord/guild_template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  (void)d->updated_at;
  /* discord/guild_template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->source_guild_id;
  /* discord/guild_template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
  if (d->serialized_source_guild) {
    discord_guild_cleanup(d->serialized_source_guild);
    free(d->serialized_source_guild);
  }
  /* discord/guild_template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
  if (d->is_dirty)
    free(d->is_dirty);
}

void discord_guild_template_init(struct discord_guild_template *p) {
  memset(p, 0, sizeof(struct discord_guild_template));
  /* discord/guild_template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */

  /* discord/guild_template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* discord/guild_template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/guild_template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */

  /* discord/guild_template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/guild_template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */

  /* discord/guild_template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* discord/guild_template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* discord/guild_template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/guild_template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */

  /* discord/guild_template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */

}
void discord_guild_template_list_free(struct discord_guild_template **p) {
  ntl_free((void**)p, (void(*)(void*))discord_guild_template_cleanup);
}

void discord_guild_template_list_from_json(char *str, size_t len, struct discord_guild_template ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_template);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_guild_template_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_template_list_to_json(char *str, size_t len, struct discord_guild_template **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_guild_template_to_json);
}

