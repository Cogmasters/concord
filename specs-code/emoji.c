/* This file is generated from specs/emoji.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
*/

void discord_emoji_dati_from_json(char *json, size_t len, struct discord_emoji_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):F,"
  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role_dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */
  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*" }, "option":true }'
  */
                "(user):F,"
  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
                "(require_colons):b,"
  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
                "(managed):b,"
  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
                "(animated):b,"
  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */
                "(available):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_strtoull, &p->id,
  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role_dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */
  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*" }, "option":true }'
  */
                discord_user_dati_from_json, p->user,
  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
                &p->require_colons,
  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
                &p->managed,
  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
                &p->animated,
  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */
                &p->available,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_emoji_dati_use_default_inject_settings(struct discord_emoji_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role_dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */

  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*" }, "option":true }'
  */
  p->__M.arg_switches[3] = p->user;

  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
  p->__M.arg_switches[4] = &p->require_colons;

  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
  p->__M.arg_switches[5] = &p->managed;

  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
  p->__M.arg_switches[6] = &p->animated;

  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */
  p->__M.arg_switches[7] = &p->available;

}

size_t discord_emoji_dati_to_json(char *json, size_t len, struct discord_emoji_dati *p)
{
  size_t r;
  discord_emoji_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                "(id):|F|,"
  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                "(name):s,"
  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role_dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */
  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*" }, "option":true }'
  */
                "(user):F,"
  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
                "(require_colons):b,"
  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
                "(managed):b,"
  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
                "(animated):b,"
  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */
                "(available):b,"
                "@arg_switches:b",
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
                orka_ulltostr, &p->id,
  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
                p->name,
  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role_dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */
  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*" }, "option":true }'
  */
                discord_user_dati_to_json, p->user,
  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
                &p->require_colons,
  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
                &p->managed,
  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
                &p->animated,
  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */
                &p->available,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_emoji_dati_cleanup_v(void *p) {
  discord_emoji_dati_cleanup((struct discord_emoji_dati *)p);
}

void discord_emoji_dati_init_v(void *p) {
  discord_emoji_dati_init((struct discord_emoji_dati *)p);
}

void discord_emoji_dati_free_v(void *p) {
 discord_emoji_dati_free((struct discord_emoji_dati *)p);
};

void discord_emoji_dati_from_json_v(char *json, size_t len, void *p) {
 discord_emoji_dati_from_json(json, len, (struct discord_emoji_dati*)p);
}

size_t discord_emoji_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_emoji_dati_to_json(json, len, (struct discord_emoji_dati*)p);
}

void discord_emoji_dati_list_free_v(void **p) {
  discord_emoji_dati_list_free((struct discord_emoji_dati**)p);
}

void discord_emoji_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_emoji_dati_list_from_json(str, len, (struct discord_emoji_dati ***)p);
}

size_t discord_emoji_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_emoji_dati_list_to_json(str, len, (struct discord_emoji_dati **)p);
}


void discord_emoji_dati_cleanup(struct discord_emoji_dati *d) {
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */
  //p->id is a scalar
  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */
  //p->name is a scalar
  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role_dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */
  //@todo p->(null)
  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*" }, "option":true }'
  */
  if (d->user)
    discord_user_dati_free(d->user);
  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */
  //p->require_colons is a scalar
  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */
  //p->managed is a scalar
  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */
  //p->animated is a scalar
  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */
  //p->available is a scalar
}

void discord_emoji_dati_init(struct discord_emoji_dati *p) {
  memset(p, 0, sizeof(struct discord_emoji_dati));
  /* specs/emoji.json:11:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}'
  */

  /* specs/emoji.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]"}}'
  */

  /* specs/emoji.json:13:20
     '{ "name": "roles", "type":{ "base":"struct discord_guild_role_dati", "dec":"ntl"}, "option":true,
          "todo":true }'
  */

  /* specs/emoji.json:15:20
     '{ "name": "user", "type":{ "base":"struct discord_user_dati", "dec":"*" }, "option":true }'
  */
  p->user = discord_user_dati_alloc();

  /* specs/emoji.json:16:20
     '{ "name": "require_colons", "type":{ "base":"bool" }, "option":true}'
  */

  /* specs/emoji.json:17:20
     '{ "name": "managed", "type":{ "base":"bool" }, "option":true}'
  */

  /* specs/emoji.json:18:20
     '{ "name": "animated", "type":{ "base":"bool" }, "option":true}'
  */

  /* specs/emoji.json:19:20
     '{ "name": "available", "type":{ "base":"bool" }, "option":true}'
  */

}
struct discord_emoji_dati* discord_emoji_dati_alloc() {
  struct discord_emoji_dati *p= (struct discord_emoji_dati*)malloc(sizeof(struct discord_emoji_dati));
  discord_emoji_dati_init(p);
  return p;
}

void discord_emoji_dati_free(struct discord_emoji_dati *p) {
  discord_emoji_dati_cleanup(p);
  free(p);
}

void discord_emoji_dati_list_free(struct discord_emoji_dati **p) {
  ntl_free((void**)p, (vfvp)discord_emoji_dati_cleanup);
}

void discord_emoji_dati_list_from_json(char *str, size_t len, struct discord_emoji_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_emoji_dati);
  d.init_elem = discord_emoji_dati_init_v;
  d.elem_from_buf = discord_emoji_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_emoji_dati_list_to_json(char *str, size_t len, struct discord_emoji_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_emoji_dati_to_json_v);
}

