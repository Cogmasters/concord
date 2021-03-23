/* This file is generated from specs/guild.role.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/

void discord_guild_role_tags_dati_from_json(char *json, size_t len, struct discord_guild_role_tags_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(bot_id):F,"
  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(integration_id):F,"
  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
                "(premium_subscriber):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->bot_id,
  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->integration_id,
  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
                &p->premium_subscriber,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_role_tags_dati_use_default_inject_settings(struct discord_guild_role_tags_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->bot_id;

  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->integration_id;

  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->premium_subscriber;

}

size_t discord_guild_role_tags_dati_to_json(char *json, size_t len, struct discord_guild_role_tags_dati *p)
{
  size_t r;
  discord_guild_role_tags_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(bot_id):|F|,"
  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(integration_id):|F|,"
  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
                "(premium_subscriber):d,"
                "@arg_switches:b",
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->bot_id,
  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->integration_id,
  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
                &p->premium_subscriber,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_role_tags_dati_cleanup_v(void *p) {
  discord_guild_role_tags_dati_cleanup((struct discord_guild_role_tags_dati *)p);
}

void discord_guild_role_tags_dati_init_v(void *p) {
  discord_guild_role_tags_dati_init((struct discord_guild_role_tags_dati *)p);
}

void discord_guild_role_tags_dati_free_v(void *p) {
 discord_guild_role_tags_dati_free((struct discord_guild_role_tags_dati *)p);
};

void discord_guild_role_tags_dati_from_json_v(char *json, size_t len, void *p) {
 discord_guild_role_tags_dati_from_json(json, len, (struct discord_guild_role_tags_dati*)p);
}

size_t discord_guild_role_tags_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_role_tags_dati_to_json(json, len, (struct discord_guild_role_tags_dati*)p);
}

void discord_guild_role_tags_dati_list_free_v(void **p) {
  discord_guild_role_tags_dati_list_free((struct discord_guild_role_tags_dati**)p);
}

void discord_guild_role_tags_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_role_tags_dati_list_from_json(str, len, (struct discord_guild_role_tags_dati ***)p);
}

size_t discord_guild_role_tags_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_role_tags_dati_list_to_json(str, len, (struct discord_guild_role_tags_dati **)p);
}


void discord_guild_role_tags_dati_cleanup(struct discord_guild_role_tags_dati *d) {
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->bot_id is a scalar
  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->integration_id is a scalar
  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
  //p->premium_subscriber is a scalar
}

void discord_guild_role_tags_dati_init(struct discord_guild_role_tags_dati *p) {
  memset(p, 0, sizeof(struct discord_guild_role_tags_dati));
  /* specs/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */

}
struct discord_guild_role_tags_dati* discord_guild_role_tags_dati_alloc() {
  struct discord_guild_role_tags_dati *p= (struct discord_guild_role_tags_dati*)malloc(sizeof(struct discord_guild_role_tags_dati));
  discord_guild_role_tags_dati_init(p);
  return p;
}

void discord_guild_role_tags_dati_free(struct discord_guild_role_tags_dati *p) {
  discord_guild_role_tags_dati_cleanup(p);
  free(p);
}

void discord_guild_role_tags_dati_list_free(struct discord_guild_role_tags_dati **p) {
  ntl_free((void**)p, (vfvp)discord_guild_role_tags_dati_cleanup);
}

void discord_guild_role_tags_dati_list_from_json(char *str, size_t len, struct discord_guild_role_tags_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_role_tags_dati);
  d.init_elem = discord_guild_role_tags_dati_init_v;
  d.elem_from_buf = discord_guild_role_tags_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_role_tags_dati_list_to_json(char *str, size_t len, struct discord_guild_role_tags_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_role_tags_dati_to_json_v);
}


void discord_guild_role_dati_from_json(char *json, size_t len, struct discord_guild_role_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
                "(name):s,"
  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
                "(color):d,"
  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
                "(hoist):b,"
  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
                "(position):d,"
  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
                "(permissions):?s,"
  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
                "(managed):b,"
  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
                "(mentionable):b,"
  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
                "(tags):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
                p->name,
  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
                &p->color,
  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
                &p->hoist,
  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
                &p->position,
  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->permissions,
  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
                &p->managed,
  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
                &p->mentionable,
  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
                discord_guild_role_tags_dati_from_json, p->tags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_role_dati_use_default_inject_settings(struct discord_guild_role_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->color;

  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[3] = &p->hoist;

  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[4] = &p->position;

  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[5] = p->permissions;

  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[6] = &p->managed;

  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[7] = &p->mentionable;

  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
  p->__M.arg_switches[8] = p->tags;

}

size_t discord_guild_role_dati_to_json(char *json, size_t len, struct discord_guild_role_dati *p)
{
  size_t r;
  discord_guild_role_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
                "(name):s,"
  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
                "(color):d,"
  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
                "(hoist):b,"
  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
                "(position):d,"
  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
                "(permissions):s,"
  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
                "(managed):b,"
  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
                "(mentionable):b,"
  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
                "(tags):F,"
                "@arg_switches:b",
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
                p->name,
  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
                &p->color,
  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
                &p->hoist,
  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
                &p->position,
  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
                p->permissions,
  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
                &p->managed,
  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
                &p->mentionable,
  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
                discord_guild_role_tags_dati_to_json, p->tags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_role_dati_cleanup_v(void *p) {
  discord_guild_role_dati_cleanup((struct discord_guild_role_dati *)p);
}

void discord_guild_role_dati_init_v(void *p) {
  discord_guild_role_dati_init((struct discord_guild_role_dati *)p);
}

void discord_guild_role_dati_free_v(void *p) {
 discord_guild_role_dati_free((struct discord_guild_role_dati *)p);
};

void discord_guild_role_dati_from_json_v(char *json, size_t len, void *p) {
 discord_guild_role_dati_from_json(json, len, (struct discord_guild_role_dati*)p);
}

size_t discord_guild_role_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_role_dati_to_json(json, len, (struct discord_guild_role_dati*)p);
}

void discord_guild_role_dati_list_free_v(void **p) {
  discord_guild_role_dati_list_free((struct discord_guild_role_dati**)p);
}

void discord_guild_role_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_role_dati_list_from_json(str, len, (struct discord_guild_role_dati ***)p);
}

size_t discord_guild_role_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_role_dati_list_to_json(str, len, (struct discord_guild_role_dati **)p);
}


void discord_guild_role_dati_cleanup(struct discord_guild_role_dati *d) {
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
  //p->name is a scalar
  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
  //p->color is a scalar
  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
  //p->hoist is a scalar
  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  //p->position is a scalar
  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->permissions)
    free(d->permissions);
  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
  //p->managed is a scalar
  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
  //p->mentionable is a scalar
  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
  if (d->tags)
    discord_guild_role_tags_dati_free(d->tags);
}

void discord_guild_role_dati_init(struct discord_guild_role_dati *p) {
  memset(p, 0, sizeof(struct discord_guild_role_dati));
  /* specs/guild.role.json:23:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/guild.role.json:24:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */

  /* specs/guild.role.json:25:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */

  /* specs/guild.role.json:26:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */

  /* specs/guild.role.json:27:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */

  /* specs/guild.role.json:28:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/guild.role.json:29:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */

  /* specs/guild.role.json:30:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */

  /* specs/guild.role.json:31:20
     '{ "name": "tags", "type":{"base":"discord::guild::role::tags::dati", "dec":"*"}}'
  */
  p->tags = discord_guild_role_tags_dati_alloc();

}
struct discord_guild_role_dati* discord_guild_role_dati_alloc() {
  struct discord_guild_role_dati *p= (struct discord_guild_role_dati*)malloc(sizeof(struct discord_guild_role_dati));
  discord_guild_role_dati_init(p);
  return p;
}

void discord_guild_role_dati_free(struct discord_guild_role_dati *p) {
  discord_guild_role_dati_cleanup(p);
  free(p);
}

void discord_guild_role_dati_list_free(struct discord_guild_role_dati **p) {
  ntl_free((void**)p, (vfvp)discord_guild_role_dati_cleanup);
}

void discord_guild_role_dati_list_from_json(char *str, size_t len, struct discord_guild_role_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_role_dati);
  d.init_elem = discord_guild_role_dati_init_v;
  d.elem_from_buf = discord_guild_role_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_role_dati_list_to_json(char *str, size_t len, struct discord_guild_role_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_role_dati_to_json_v);
}

