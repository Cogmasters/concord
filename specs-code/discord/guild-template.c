/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild-template.c
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

void discord_guild_template_from_json(char *json, size_t len, struct discord_guild_template **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_guild_template *p = *pp;
  discord_guild_template_init(p);
  r=json_extract(json, len, 
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
                "(code):?s,"
  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                "(description):?s,"
  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
                "(usage_count):d,"
  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(creator_id):F,"
  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
                "(creator):F,"
  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(created_at):F,"
  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(updated_at):F,"
  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(source_guild_id):F,"
  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
                "(serialized_source_guild):F,"
  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
                "(is_dirty):F,",
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
                &p->code,
  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                &p->description,
  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
                &p->usage_count,
  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->creator_id,
  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
                discord_user_from_json, &p->creator,
  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->created_at,
  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_iso8601_to_unix_ms, &p->updated_at,
  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->source_guild_id,
  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
                discord_guild_from_json, &p->serialized_source_guild,
  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
                cee_strndup, &p->is_dirty);
  ret = r;
}

size_t discord_guild_template_to_json(char *json, size_t len, struct discord_guild_template *p)
{
  size_t r;
  void *arg_switches[11]={NULL};
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[0] = p->code;

  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[1] = p->name;

  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[2] = p->description;

  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
  arg_switches[3] = &p->usage_count;

  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[4] = &p->creator_id;

  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  arg_switches[5] = p->creator;

  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  arg_switches[6] = &p->created_at;

  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  arg_switches[7] = &p->updated_at;

  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[8] = &p->source_guild_id;

  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
  arg_switches[9] = p->serialized_source_guild;

  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
  arg_switches[10] = p->is_dirty;

  r=json_inject(json, len, 
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
                "(code):s,"
  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                "(description):s,"
  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
                "(usage_count):d,"
  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(creator_id):|F|,"
  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
                "(creator):F,"
  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(created_at):|F|,"
  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                "(updated_at):|F|,"
  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(source_guild_id):|F|,"
  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
                "(serialized_source_guild):F,"
  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
                "(is_dirty):s,"
                "@arg_switches:b",
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
                p->code,
  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
                p->description,
  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
                &p->usage_count,
  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->creator_id,
  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
                discord_user_to_json, p->creator,
  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->created_at,
  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
                cee_unix_ms_to_iso8601, &p->updated_at,
  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->source_guild_id,
  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
                discord_guild_to_json, p->serialized_source_guild,
  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
                p->is_dirty,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_template_cleanup_v(void *p) {
  discord_guild_template_cleanup((struct discord_guild_template *)p);
}

void discord_guild_template_init_v(void *p) {
  discord_guild_template_init((struct discord_guild_template *)p);
}

void discord_guild_template_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_template_from_json(json, len, (struct discord_guild_template**)pp);
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
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */
  if (d->code)
    free(d->code);
  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  if (d->description)
    free(d->description);
  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */
  /* p->usage_count is a scalar */
  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  /* p->creator_id is a scalar */
  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */
  if (d->creator) {
    discord_user_cleanup(d->creator);
    free(d->creator);
  }
  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  /* p->created_at is a scalar */
  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */
  /* p->updated_at is a scalar */
  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  /* p->source_guild_id is a scalar */
  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */
  if (d->serialized_source_guild) {
    discord_guild_cleanup(d->serialized_source_guild);
    free(d->serialized_source_guild);
  }
  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */
  if (d->is_dirty)
    free(d->is_dirty);
}

void discord_guild_template_init(struct discord_guild_template *p) {
  memset(p, 0, sizeof(struct discord_guild_template));
  /* specs/discord/guild-template.json:12:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/guild-template.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/guild-template.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild-template.json:15:20
     '{ "name": "usage_count", "type":{ "base":"int"}}' */

  /* specs/discord/guild-template.json:16:20
     '{ "name": "creator_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/guild-template.json:17:20
     '{ "name": "creator", "type":{ "base":"struct discord_user", "dec":"*" }}' */

  /* specs/discord/guild-template.json:18:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* specs/discord/guild-template.json:19:20
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601" }}' */

  /* specs/discord/guild-template.json:20:20
     '{ "name": "source_guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/guild-template.json:21:20
     '{ "name": "serialized_source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }}' */

  /* specs/discord/guild-template.json:22:20
     '{ "name": "is_dirty", "type":{ "base":"char", "dec":"*", "converter":"mixed"}}' */

}
void discord_guild_template_list_free(struct discord_guild_template **p) {
  ntl_free((void**)p, (vfvp)discord_guild_template_cleanup);
}

void discord_guild_template_list_from_json(char *str, size_t len, struct discord_guild_template ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_template);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_template_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_template_list_to_json(char *str, size_t len, struct discord_guild_template **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_template_to_json_v);
}

