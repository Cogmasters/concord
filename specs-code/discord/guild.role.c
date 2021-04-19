/* This file is generated from specs/discord/guild.role.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/

void discord_guild_role_tags_from_json(char *json, size_t len, struct discord_guild_role_tags *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(bot_id):F,"
  /* specs/discord/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(integration_id):F,"
  /* specs/discord/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
                "(premium_subscriber):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->bot_id,
  /* specs/discord/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->integration_id,
  /* specs/discord/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
                &p->premium_subscriber,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_role_tags_use_default_inject_settings(struct discord_guild_role_tags *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->bot_id;

  /* specs/discord/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[1] = &p->integration_id;

  /* specs/discord/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->premium_subscriber;

}

size_t discord_guild_role_tags_to_json(char *json, size_t len, struct discord_guild_role_tags *p)
{
  size_t r;
  discord_guild_role_tags_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(bot_id):|F|,"
  /* specs/discord/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(integration_id):|F|,"
  /* specs/discord/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
                "(premium_subscriber):d,"
                "@arg_switches:b",
  /* specs/discord/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->bot_id,
  /* specs/discord/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->integration_id,
  /* specs/discord/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
                &p->premium_subscriber,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_role_tags_cleanup_v(void *p) {
  discord_guild_role_tags_cleanup((struct discord_guild_role_tags *)p);
}

void discord_guild_role_tags_init_v(void *p) {
  discord_guild_role_tags_init((struct discord_guild_role_tags *)p);
}

void discord_guild_role_tags_free_v(void *p) {
 discord_guild_role_tags_free((struct discord_guild_role_tags *)p);
};

void discord_guild_role_tags_from_json_v(char *json, size_t len, void *p) {
 discord_guild_role_tags_from_json(json, len, (struct discord_guild_role_tags*)p);
}

size_t discord_guild_role_tags_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_role_tags_to_json(json, len, (struct discord_guild_role_tags*)p);
}

void discord_guild_role_tags_list_free_v(void **p) {
  discord_guild_role_tags_list_free((struct discord_guild_role_tags**)p);
}

void discord_guild_role_tags_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_role_tags_list_from_json(str, len, (struct discord_guild_role_tags ***)p);
}

size_t discord_guild_role_tags_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_role_tags_list_to_json(str, len, (struct discord_guild_role_tags **)p);
}


void discord_guild_role_tags_cleanup(struct discord_guild_role_tags *d) {
  /* specs/discord/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->bot_id is a scalar
  /* specs/discord/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->integration_id is a scalar
  /* specs/discord/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */
  //p->premium_subscriber is a scalar
}

void discord_guild_role_tags_init(struct discord_guild_role_tags *p) {
  memset(p, 0, sizeof(struct discord_guild_role_tags));
  /* specs/discord/guild.role.json:12:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/guild.role.json:13:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/guild.role.json:14:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}'
  */

}
struct discord_guild_role_tags* discord_guild_role_tags_alloc() {
  struct discord_guild_role_tags *p= (struct discord_guild_role_tags*)malloc(sizeof(struct discord_guild_role_tags));
  discord_guild_role_tags_init(p);
  return p;
}

void discord_guild_role_tags_free(struct discord_guild_role_tags *p) {
  discord_guild_role_tags_cleanup(p);
  free(p);
}

void discord_guild_role_tags_list_free(struct discord_guild_role_tags **p) {
  ntl_free((void**)p, (vfvp)discord_guild_role_tags_cleanup);
}

void discord_guild_role_tags_list_from_json(char *str, size_t len, struct discord_guild_role_tags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_role_tags);
  d.init_elem = discord_guild_role_tags_init_v;
  d.elem_from_buf = discord_guild_role_tags_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_role_tags_list_to_json(char *str, size_t len, struct discord_guild_role_tags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_role_tags_to_json_v);
}


void discord_guild_role_from_json(char *json, size_t len, struct discord_guild_role *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/guild.role.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):F,"
  /* specs/discord/guild.role.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
                "(name):s,"
  /* specs/discord/guild.role.json:24:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
                "(color):d,"
  /* specs/discord/guild.role.json:25:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
                "(hoist):b,"
  /* specs/discord/guild.role.json:26:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
                "(position):d,"
  /* specs/discord/guild.role.json:27:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
                "(permissions):?s,"
  /* specs/discord/guild.role.json:28:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
                "(managed):b,"
  /* specs/discord/guild.role.json:29:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
                "(mentionable):b,"
  /* specs/discord/guild.role.json:30:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags", "dec":"*"}}'
  */
                "(tags):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.role.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_strtoull, &p->id,
  /* specs/discord/guild.role.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
                p->name,
  /* specs/discord/guild.role.json:24:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
                &p->color,
  /* specs/discord/guild.role.json:25:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
                &p->hoist,
  /* specs/discord/guild.role.json:26:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
                &p->position,
  /* specs/discord/guild.role.json:27:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
                &p->permissions,
  /* specs/discord/guild.role.json:28:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
                &p->managed,
  /* specs/discord/guild.role.json:29:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
                &p->mentionable,
  /* specs/discord/guild.role.json:30:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags", "dec":"*"}}'
  */
                discord_guild_role_tags_from_json, p->tags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_role_use_default_inject_settings(struct discord_guild_role *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.role.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.role.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/guild.role.json:24:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->color;

  /* specs/discord/guild.role.json:25:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[3] = &p->hoist;

  /* specs/discord/guild.role.json:26:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[4] = &p->position;

  /* specs/discord/guild.role.json:27:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
  p->__M.arg_switches[5] = p->permissions;

  /* specs/discord/guild.role.json:28:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[6] = &p->managed;

  /* specs/discord/guild.role.json:29:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[7] = &p->mentionable;

  /* specs/discord/guild.role.json:30:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags", "dec":"*"}}'
  */
  p->__M.arg_switches[8] = p->tags;

}

size_t discord_guild_role_to_json(char *json, size_t len, struct discord_guild_role *p)
{
  size_t r;
  discord_guild_role_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.role.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                "(id):|F|,"
  /* specs/discord/guild.role.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
                "(name):s,"
  /* specs/discord/guild.role.json:24:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
                "(color):d,"
  /* specs/discord/guild.role.json:25:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
                "(hoist):b,"
  /* specs/discord/guild.role.json:26:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
                "(position):d,"
  /* specs/discord/guild.role.json:27:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
                "(permissions):s,"
  /* specs/discord/guild.role.json:28:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
                "(managed):b,"
  /* specs/discord/guild.role.json:29:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
                "(mentionable):b,"
  /* specs/discord/guild.role.json:30:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags", "dec":"*"}}'
  */
                "(tags):F,"
                "@arg_switches:b",
  /* specs/discord/guild.role.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
                orka_ulltostr, &p->id,
  /* specs/discord/guild.role.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
                p->name,
  /* specs/discord/guild.role.json:24:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
                &p->color,
  /* specs/discord/guild.role.json:25:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
                &p->hoist,
  /* specs/discord/guild.role.json:26:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
                &p->position,
  /* specs/discord/guild.role.json:27:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
                p->permissions,
  /* specs/discord/guild.role.json:28:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
                &p->managed,
  /* specs/discord/guild.role.json:29:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
                &p->mentionable,
  /* specs/discord/guild.role.json:30:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags", "dec":"*"}}'
  */
                discord_guild_role_tags_to_json, p->tags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_role_cleanup_v(void *p) {
  discord_guild_role_cleanup((struct discord_guild_role *)p);
}

void discord_guild_role_init_v(void *p) {
  discord_guild_role_init((struct discord_guild_role *)p);
}

void discord_guild_role_free_v(void *p) {
 discord_guild_role_free((struct discord_guild_role *)p);
};

void discord_guild_role_from_json_v(char *json, size_t len, void *p) {
 discord_guild_role_from_json(json, len, (struct discord_guild_role*)p);
}

size_t discord_guild_role_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_role_to_json(json, len, (struct discord_guild_role*)p);
}

void discord_guild_role_list_free_v(void **p) {
  discord_guild_role_list_free((struct discord_guild_role**)p);
}

void discord_guild_role_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_role_list_from_json(str, len, (struct discord_guild_role ***)p);
}

size_t discord_guild_role_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_role_list_to_json(str, len, (struct discord_guild_role **)p);
}


void discord_guild_role_cleanup(struct discord_guild_role *d) {
  /* specs/discord/guild.role.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */
  //p->id is a scalar
  /* specs/discord/guild.role.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */
  //p->name is a scalar
  /* specs/discord/guild.role.json:24:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */
  //p->color is a scalar
  /* specs/discord/guild.role.json:25:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */
  //p->hoist is a scalar
  /* specs/discord/guild.role.json:26:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */
  //p->position is a scalar
  /* specs/discord/guild.role.json:27:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */
  if (d->permissions)
    free(d->permissions);
  /* specs/discord/guild.role.json:28:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */
  //p->managed is a scalar
  /* specs/discord/guild.role.json:29:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */
  //p->mentionable is a scalar
  /* specs/discord/guild.role.json:30:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags", "dec":"*"}}'
  */
  if (d->tags)
    discord_guild_role_tags_free(d->tags);
}

void discord_guild_role_init(struct discord_guild_role *p) {
  memset(p, 0, sizeof(struct discord_guild_role));
  /* specs/discord/guild.role.json:22:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}'
  */

  /* specs/discord/guild.role.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"[MAX_NAME_LEN]" }}'
  */

  /* specs/discord/guild.role.json:24:20
     '{ "name": "color", "type":{ "base":"int" }}'
  */

  /* specs/discord/guild.role.json:25:20
     '{ "name": "hoist", "type":{ "base":"bool" }}'
  */

  /* specs/discord/guild.role.json:26:20
     '{ "name": "position", "type":{ "base":"int" }}'
  */

  /* specs/discord/guild.role.json:27:20
     '{ "name": "permissions", "type":{ "base":"char", "dec":"*" }}'
  */

  /* specs/discord/guild.role.json:28:20
     '{ "name": "managed", "type":{ "base":"bool" }}'
  */

  /* specs/discord/guild.role.json:29:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}'
  */

  /* specs/discord/guild.role.json:30:20
     '{ "name": "tags", "type":{"base":"struct discord_guild_role_tags", "dec":"*"}}'
  */
  p->tags = discord_guild_role_tags_alloc();

}
struct discord_guild_role* discord_guild_role_alloc() {
  struct discord_guild_role *p= (struct discord_guild_role*)malloc(sizeof(struct discord_guild_role));
  discord_guild_role_init(p);
  return p;
}

void discord_guild_role_free(struct discord_guild_role *p) {
  discord_guild_role_cleanup(p);
  free(p);
}

void discord_guild_role_list_free(struct discord_guild_role **p) {
  ntl_free((void**)p, (vfvp)discord_guild_role_cleanup);
}

void discord_guild_role_list_from_json(char *str, size_t len, struct discord_guild_role ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_role);
  d.init_elem = discord_guild_role_init_v;
  d.elem_from_buf = discord_guild_role_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_guild_role_list_to_json(char *str, size_t len, struct discord_guild_role **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_role_to_json_v);
}

