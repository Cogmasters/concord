/* This file is generated from discord/emoji.json, Please don't edit it. */
/**
 * @file specs-code/discord/emoji.c
 * @see https://discord.com/developers/docs/resources/emoji
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_emoji_from_json_p(char *json, size_t len, struct discord_emoji **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_emoji_from_json(json, len, *pp);
}
void discord_emoji_from_json(char *json, size_t len, struct discord_emoji *p)
{
  discord_emoji_init(p);
  json_extract(json, len, 
  /* discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */
                "(id):F,"
  /* discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */
                "(name):?s,"
  /* discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */
                "(roles):F,"
  /* discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */
                "(user):F,"
  /* discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */
                "(require_colons):b,"
  /* discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */
                "(managed):b,"
  /* discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */
                "(animated):b,"
  /* discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */
                "(available):b,",
  /* discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */
                cee_strtou64, &p->id,
  /* discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */
                &p->name,
  /* discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */
                discord_role_list_from_json, &p->roles,
  /* discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */
                discord_user_from_json_p, &p->user,
  /* discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */
                &p->require_colons,
  /* discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */
                &p->managed,
  /* discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */
                &p->animated,
  /* discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */
                &p->available);
}

size_t discord_emoji_to_json(char *json, size_t len, struct discord_emoji *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */
  arg_switches[0] = &p->id;

  /* discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */
  arg_switches[1] = p->name;

  /* discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */
  arg_switches[2] = p->roles;

  /* discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */
  arg_switches[3] = p->user;

  /* discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */
  arg_switches[4] = &p->require_colons;

  /* discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */
  arg_switches[5] = &p->managed;

  /* discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */
  arg_switches[6] = &p->animated;

  /* discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */
  arg_switches[7] = &p->available;

  r=json_inject(json, len, 
  /* discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */
                "(id):|F|,"
  /* discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */
                "(name):s,"
  /* discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */
                "(roles):F,"
  /* discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */
                "(user):F,"
  /* discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */
                "(require_colons):b,"
  /* discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */
                "(managed):b,"
  /* discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */
                "(animated):b,"
  /* discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */
                "(available):b,"
                "@arg_switches:b",
  /* discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */
                cee_u64tostr, &p->id,
  /* discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */
                p->name,
  /* discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */
                discord_role_list_to_json, p->roles,
  /* discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */
                discord_user_to_json, p->user,
  /* discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */
                &p->require_colons,
  /* discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */
                &p->managed,
  /* discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */
                &p->animated,
  /* discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */
                &p->available,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_emoji_cleanup_v(void *p) {
  discord_emoji_cleanup((struct discord_emoji *)p);
}

void discord_emoji_init_v(void *p) {
  discord_emoji_init((struct discord_emoji *)p);
}

void discord_emoji_from_json_v(char *json, size_t len, void *p) {
 discord_emoji_from_json(json, len, (struct discord_emoji*)p);
}

size_t discord_emoji_to_json_v(char *json, size_t len, void *p) {
  return discord_emoji_to_json(json, len, (struct discord_emoji*)p);
}

void discord_emoji_list_free_v(void **p) {
  discord_emoji_list_free((struct discord_emoji**)p);
}

void discord_emoji_list_from_json_v(char *str, size_t len, void *p) {
  discord_emoji_list_from_json(str, len, (struct discord_emoji ***)p);
}

size_t discord_emoji_list_to_json_v(char *str, size_t len, void *p){
  return discord_emoji_list_to_json(str, len, (struct discord_emoji **)p);
}


void discord_emoji_cleanup(struct discord_emoji *d) {
  /* discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */
  /* p->id is a scalar */
  /* discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */
  if (d->name)
    free(d->name);
  /* discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */
  if (d->roles)
    discord_role_list_free(d->roles);
  /* discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
  /* discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */
  /* p->require_colons is a scalar */
  /* discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */
  /* p->managed is a scalar */
  /* discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */
  /* p->animated is a scalar */
  /* discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */
  /* p->available is a scalar */
}

void discord_emoji_init(struct discord_emoji *p) {
  memset(p, 0, sizeof(struct discord_emoji));
  /* discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"emoji id"}' */

  /* discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"emoji name"}' */

  /* discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl"}, "option":true, "comment":"roles allowed to use this emoji" }' */

  /* discord/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true, "comment":"user that created this emoji" }' */

  /* discord/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji must be wrapped in colons" }' */

  /* discord/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is managed" }' */

  /* discord/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true, "comment":"whether this emoji is animated" }' */

  /* discord/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true, "whether this emoji can be used, may be false due to loss of Server Boosts" }' */

}
void discord_emoji_list_free(struct discord_emoji **p) {
  ntl_free((void**)p, (vfvp)discord_emoji_cleanup);
}

void discord_emoji_list_from_json(char *str, size_t len, struct discord_emoji ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_emoji);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_emoji_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_emoji_list_to_json(char *str, size_t len, struct discord_emoji **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_emoji_to_json);
}

