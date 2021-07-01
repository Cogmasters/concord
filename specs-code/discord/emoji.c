/* This file is generated from specs/discord/emoji.json, Please don't edit it. */
/**
 * @file specs-code/discord/emoji.c
 * @author cee-studio
 * @date 30 Jun 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/emoji
 */

#include "specs.h"

void discord_emoji_from_json(char *json, size_t len, struct discord_emoji *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_permissions_role", "dec":"ntl"}, "option":true,
          "todo":true }' */
  /* specs/discord/emoji.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }' */
                "(user):F,"
  /* specs/discord/emoji.json:17:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}' */
                "(require_colons):b,"
  /* specs/discord/emoji.json:18:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}' */
                "(managed):b,"
  /* specs/discord/emoji.json:19:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}' */
                "(animated):b,"
  /* specs/discord/emoji.json:20:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}' */
                "(available):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->id,
  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_permissions_role", "dec":"ntl"}, "option":true,
          "todo":true }' */
  /* specs/discord/emoji.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }' */
                discord_user_from_json, p->user,
  /* specs/discord/emoji.json:17:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}' */
                &p->require_colons,
  /* specs/discord/emoji.json:18:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}' */
                &p->managed,
  /* specs/discord/emoji.json:19:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}' */
                &p->animated,
  /* specs/discord/emoji.json:20:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}' */
                &p->available,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_emoji_use_default_inject_settings(struct discord_emoji *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_permissions_role", "dec":"ntl"}, "option":true,
          "todo":true }' */

  /* specs/discord/emoji.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }' */
  p->__M.arg_switches[3] = p->user;

  /* specs/discord/emoji.json:17:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}' */
  p->__M.arg_switches[4] = &p->require_colons;

  /* specs/discord/emoji.json:18:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}' */
  p->__M.arg_switches[5] = &p->managed;

  /* specs/discord/emoji.json:19:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}' */
  p->__M.arg_switches[6] = &p->animated;

  /* specs/discord/emoji.json:20:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}' */
  p->__M.arg_switches[7] = &p->available;

}

size_t discord_emoji_to_json(char *json, size_t len, struct discord_emoji *p)
{
  size_t r;
  discord_emoji_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_permissions_role", "dec":"ntl"}, "option":true,
          "todo":true }' */
  /* specs/discord/emoji.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }' */
                "(user):F,"
  /* specs/discord/emoji.json:17:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}' */
                "(require_colons):b,"
  /* specs/discord/emoji.json:18:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}' */
                "(managed):b,"
  /* specs/discord/emoji.json:19:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}' */
                "(animated):b,"
  /* specs/discord/emoji.json:20:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}' */
                "(available):b,"
                "@arg_switches:b",
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->id,
  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_permissions_role", "dec":"ntl"}, "option":true,
          "todo":true }' */
  /* specs/discord/emoji.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }' */
                discord_user_to_json, p->user,
  /* specs/discord/emoji.json:17:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}' */
                &p->require_colons,
  /* specs/discord/emoji.json:18:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}' */
                &p->managed,
  /* specs/discord/emoji.json:19:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}' */
                &p->animated,
  /* specs/discord/emoji.json:20:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}' */
                &p->available,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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

void discord_emoji_free_v(void *p) {
 discord_emoji_free((struct discord_emoji *)p);
};

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
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->id is a scalar
  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_permissions_role", "dec":"ntl"}, "option":true,
          "todo":true }' */
  ///< @todo p->(null)
  /* specs/discord/emoji.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }' */
  if (d->user)
    discord_user_free(d->user);
  /* specs/discord/emoji.json:17:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}' */
  // p->require_colons is a scalar
  /* specs/discord/emoji.json:18:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}' */
  // p->managed is a scalar
  /* specs/discord/emoji.json:19:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}' */
  // p->animated is a scalar
  /* specs/discord/emoji.json:20:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}' */
  // p->available is a scalar
}

void discord_emoji_init(struct discord_emoji *p) {
  memset(p, 0, sizeof(struct discord_emoji));
  /* specs/discord/emoji.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/emoji.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/emoji.json:14:20
     '{ "name": "roles", "type":{ "base":"struct discord_permissions_role", "dec":"ntl"}, "option":true,
          "todo":true }' */

  /* specs/discord/emoji.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "option":true }' */
  p->user = discord_user_alloc();

  /* specs/discord/emoji.json:17:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}' */

  /* specs/discord/emoji.json:18:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}' */

  /* specs/discord/emoji.json:19:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}' */

  /* specs/discord/emoji.json:20:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}' */

}
struct discord_emoji* discord_emoji_alloc() {
  struct discord_emoji *p= malloc(sizeof(struct discord_emoji));
  discord_emoji_init(p);
  return p;
}

void discord_emoji_free(struct discord_emoji *p) {
  discord_emoji_cleanup(p);
  free(p);
}

void discord_emoji_list_free(struct discord_emoji **p) {
  ntl_free((void**)p, (vfvp)discord_emoji_cleanup);
}

void discord_emoji_list_from_json(char *str, size_t len, struct discord_emoji ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_emoji);
  d.init_elem = discord_emoji_init_v;
  d.elem_from_buf = discord_emoji_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_emoji_list_to_json(char *str, size_t len, struct discord_emoji **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_emoji_to_json_v);
}

