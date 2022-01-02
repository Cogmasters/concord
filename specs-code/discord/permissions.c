/* This file is generated from discord/permissions.json, Please don't edit it. */
/**
 * @file specs-code/discord/permissions.c
 * @see https://discord.com/developers/docs/topics/permissions
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"



void discord_role_from_json_p(char *json, size_t len, struct discord_role **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_role_from_json(json, len, *pp);
}
void discord_role_from_json(char *json, size_t len, struct discord_role *p)
{
  discord_role_init(p);
  json_extract(json, len, 
  /* discord/permissions.json:62:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* discord/permissions.json:63:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* discord/permissions.json:64:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                "(color):d,"
  /* discord/permissions.json:65:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                "(hoist):b,"
  /* discord/permissions.json:66:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                "(position):d,"
  /* discord/permissions.json:67:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }}' */
                "(permissions):s_as_u64,"
  /* discord/permissions.json:68:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                "(managed):b,"
  /* discord/permissions.json:69:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                "(mentionable):b,"
  /* discord/permissions.json:70:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                "(tags):F,",
  /* discord/permissions.json:62:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->id,
  /* discord/permissions.json:63:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* discord/permissions.json:64:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                &p->color,
  /* discord/permissions.json:65:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                &p->hoist,
  /* discord/permissions.json:66:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                &p->position,
  /* discord/permissions.json:67:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }}' */
                &p->permissions,
  /* discord/permissions.json:68:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                &p->managed,
  /* discord/permissions.json:69:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                &p->mentionable,
  /* discord/permissions.json:70:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                discord_role_tags_from_json_p, &p->tags);
}

size_t discord_role_to_json(char *json, size_t len, struct discord_role *p)
{
  size_t r;
  void *arg_switches[9]={NULL};
  /* discord/permissions.json:62:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->id;

  /* discord/permissions.json:63:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[1] = p->name;

  /* discord/permissions.json:64:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  arg_switches[2] = &p->color;

  /* discord/permissions.json:65:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  arg_switches[3] = &p->hoist;

  /* discord/permissions.json:66:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  arg_switches[4] = &p->position;

  /* discord/permissions.json:67:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }}' */
  arg_switches[5] = &p->permissions;

  /* discord/permissions.json:68:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->managed;

  /* discord/permissions.json:69:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  arg_switches[7] = &p->mentionable;

  /* discord/permissions.json:70:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
  arg_switches[8] = p->tags;

  r=json_inject(json, len, 
  /* discord/permissions.json:62:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* discord/permissions.json:63:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* discord/permissions.json:64:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                "(color):d,"
  /* discord/permissions.json:65:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                "(hoist):b,"
  /* discord/permissions.json:66:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                "(position):d,"
  /* discord/permissions.json:67:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }}' */
                "(permissions):s_as_u64,"
  /* discord/permissions.json:68:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                "(managed):b,"
  /* discord/permissions.json:69:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                "(mentionable):b,"
  /* discord/permissions.json:70:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                "(tags):F,"
                "@arg_switches:b",
  /* discord/permissions.json:62:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->id,
  /* discord/permissions.json:63:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* discord/permissions.json:64:20
     '{ "name": "color", "type":{ "base":"int" }}' */
                &p->color,
  /* discord/permissions.json:65:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
                &p->hoist,
  /* discord/permissions.json:66:20
     '{ "name": "position", "type":{ "base":"int" }}' */
                &p->position,
  /* discord/permissions.json:67:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }}' */
                &p->permissions,
  /* discord/permissions.json:68:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
                &p->managed,
  /* discord/permissions.json:69:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
                &p->mentionable,
  /* discord/permissions.json:70:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
                discord_role_tags_to_json, p->tags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_role_cleanup_v(void *p) {
  discord_role_cleanup((struct discord_role *)p);
}

void discord_role_init_v(void *p) {
  discord_role_init((struct discord_role *)p);
}

void discord_role_from_json_v(char *json, size_t len, void *p) {
 discord_role_from_json(json, len, (struct discord_role*)p);
}

size_t discord_role_to_json_v(char *json, size_t len, void *p) {
  return discord_role_to_json(json, len, (struct discord_role*)p);
}

void discord_role_list_free_v(void **p) {
  discord_role_list_free((struct discord_role**)p);
}

void discord_role_list_from_json_v(char *str, size_t len, void *p) {
  discord_role_list_from_json(str, len, (struct discord_role ***)p);
}

size_t discord_role_list_to_json_v(char *str, size_t len, void *p){
  return discord_role_list_to_json(str, len, (struct discord_role **)p);
}


void discord_role_cleanup(struct discord_role *d) {
  /* discord/permissions.json:62:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->id;
  /* discord/permissions.json:63:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* discord/permissions.json:64:20
     '{ "name": "color", "type":{ "base":"int" }}' */
  (void)d->color;
  /* discord/permissions.json:65:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */
  (void)d->hoist;
  /* discord/permissions.json:66:20
     '{ "name": "position", "type":{ "base":"int" }}' */
  (void)d->position;
  /* discord/permissions.json:67:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }}' */
  (void)d->permissions;
  /* discord/permissions.json:68:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */
  (void)d->managed;
  /* discord/permissions.json:69:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */
  (void)d->mentionable;
  /* discord/permissions.json:70:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */
  if (d->tags) {
    discord_role_tags_cleanup(d->tags);
    free(d->tags);
  }
}

void discord_role_init(struct discord_role *p) {
  memset(p, 0, sizeof(struct discord_role));
  /* discord/permissions.json:62:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/permissions.json:63:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/permissions.json:64:20
     '{ "name": "color", "type":{ "base":"int" }}' */

  /* discord/permissions.json:65:20
     '{ "name": "hoist", "type":{ "base":"bool" }}' */

  /* discord/permissions.json:66:20
     '{ "name": "position", "type":{ "base":"int" }}' */

  /* discord/permissions.json:67:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }}' */

  /* discord/permissions.json:68:20
     '{ "name": "managed", "type":{ "base":"bool" }}' */

  /* discord/permissions.json:69:20
     '{ "name": "mentionable", "type":{ "base":"bool" }}' */

  /* discord/permissions.json:70:20
     '{ "name": "tags", "type":{"base":"struct discord_role_tags", "dec":"*"}}' */

}
void discord_role_list_free(struct discord_role **p) {
  ntl_free((void**)p, (void(*)(void*))discord_role_cleanup);
}

void discord_role_list_from_json(char *str, size_t len, struct discord_role ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_role);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_role_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_role_list_to_json(char *str, size_t len, struct discord_role **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_role_to_json);
}


void discord_role_tags_from_json_p(char *json, size_t len, struct discord_role_tags **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_role_tags_from_json(json, len, *pp);
}
void discord_role_tags_from_json(char *json, size_t len, struct discord_role_tags *p)
{
  discord_role_tags_init(p);
  json_extract(json, len, 
  /* discord/permissions.json:80:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(bot_id):F,"
  /* discord/permissions.json:81:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(integration_id):F,"
  /* discord/permissions.json:82:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                "(premium_subscriber):d,",
  /* discord/permissions.json:80:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->bot_id,
  /* discord/permissions.json:81:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->integration_id,
  /* discord/permissions.json:82:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                &p->premium_subscriber);
}

size_t discord_role_tags_to_json(char *json, size_t len, struct discord_role_tags *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/permissions.json:80:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->bot_id;

  /* discord/permissions.json:81:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[1] = &p->integration_id;

  /* discord/permissions.json:82:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  arg_switches[2] = &p->premium_subscriber;

  r=json_inject(json, len, 
  /* discord/permissions.json:80:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(bot_id):|F|,"
  /* discord/permissions.json:81:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(integration_id):|F|,"
  /* discord/permissions.json:82:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                "(premium_subscriber):d,"
                "@arg_switches:b",
  /* discord/permissions.json:80:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->bot_id,
  /* discord/permissions.json:81:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->integration_id,
  /* discord/permissions.json:82:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
                &p->premium_subscriber,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_role_tags_cleanup_v(void *p) {
  discord_role_tags_cleanup((struct discord_role_tags *)p);
}

void discord_role_tags_init_v(void *p) {
  discord_role_tags_init((struct discord_role_tags *)p);
}

void discord_role_tags_from_json_v(char *json, size_t len, void *p) {
 discord_role_tags_from_json(json, len, (struct discord_role_tags*)p);
}

size_t discord_role_tags_to_json_v(char *json, size_t len, void *p) {
  return discord_role_tags_to_json(json, len, (struct discord_role_tags*)p);
}

void discord_role_tags_list_free_v(void **p) {
  discord_role_tags_list_free((struct discord_role_tags**)p);
}

void discord_role_tags_list_from_json_v(char *str, size_t len, void *p) {
  discord_role_tags_list_from_json(str, len, (struct discord_role_tags ***)p);
}

size_t discord_role_tags_list_to_json_v(char *str, size_t len, void *p){
  return discord_role_tags_list_to_json(str, len, (struct discord_role_tags **)p);
}


void discord_role_tags_cleanup(struct discord_role_tags *d) {
  /* discord/permissions.json:80:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->bot_id;
  /* discord/permissions.json:81:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->integration_id;
  /* discord/permissions.json:82:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */
  (void)d->premium_subscriber;
}

void discord_role_tags_init(struct discord_role_tags *p) {
  memset(p, 0, sizeof(struct discord_role_tags));
  /* discord/permissions.json:80:20
     '{ "name": "bot_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/permissions.json:81:20
     '{ "name": "integration_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/permissions.json:82:20
     '{ "name": "premium_subscriber", "type":{ "base":"int" }}' */

}
void discord_role_tags_list_free(struct discord_role_tags **p) {
  ntl_free((void**)p, (void(*)(void*))discord_role_tags_cleanup);
}

void discord_role_tags_list_from_json(char *str, size_t len, struct discord_role_tags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_role_tags);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_role_tags_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_role_tags_list_to_json(char *str, size_t len, struct discord_role_tags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_role_tags_to_json);
}

