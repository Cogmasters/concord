/* This file is generated from discord/user.json, Please don't edit it. */
/**
 * @file specs-code/discord/user.c
 * @see https://discord.com/developers/docs/resources/user
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"


void discord_user_flags_list_free_v(void **p) {
  discord_user_flags_list_free((enum discord_user_flags**)p);
}

void discord_user_flags_list_from_json_v(char *str, size_t len, void *p) {
  discord_user_flags_list_from_json(str, len, (enum discord_user_flags ***)p);
}

size_t discord_user_flags_list_to_json_v(char *str, size_t len, void *p){
  return discord_user_flags_list_to_json(str, len, (enum discord_user_flags **)p);
}

enum discord_user_flags discord_user_flags_eval(char *s){
  if(strcasecmp("DISCORD_EMPLOYEE", s) == 0) return DISCORD_USER_DISCORD_EMPLOYEE;
  if(strcasecmp("PARTNERED_SERVER_OWNER", s) == 0) return DISCORD_USER_PARTNERED_SERVER_OWNER;
  if(strcasecmp("HYPESQUAD_EVENTS", s) == 0) return DISCORD_USER_HYPESQUAD_EVENTS;
  if(strcasecmp("BUG_HUNTER_LEVEL_1", s) == 0) return DISCORD_USER_BUG_HUNTER_LEVEL_1;
  if(strcasecmp("HOUSE_BRAVERY", s) == 0) return DISCORD_USER_HOUSE_BRAVERY;
  if(strcasecmp("HOUSE_BRILLIANCE", s) == 0) return DISCORD_USER_HOUSE_BRILLIANCE;
  if(strcasecmp("HOUSE_BALANCE", s) == 0) return DISCORD_USER_HOUSE_BALANCE;
  if(strcasecmp("EARLY_SUPPORTER", s) == 0) return DISCORD_USER_EARLY_SUPPORTER;
  if(strcasecmp("TEAM_USER", s) == 0) return DISCORD_USER_TEAM_USER;
  if(strcasecmp("SYSTEM", s) == 0) return DISCORD_USER_SYSTEM;
  if(strcasecmp("BUG_HUNTER_LEVEL_2", s) == 0) return DISCORD_USER_BUG_HUNTER_LEVEL_2;
  if(strcasecmp("VERIFIED_BOT", s) == 0) return DISCORD_USER_VERIFIED_BOT;
  if(strcasecmp("EARLY_VERIFIED_BOT_DEVELOPER", s) == 0) return DISCORD_USER_EARLY_VERIFIED_BOT_DEVELOPER;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_user_flags_print(enum discord_user_flags v){

  switch (v) {
  case DISCORD_USER_DISCORD_EMPLOYEE: return "DISCORD_EMPLOYEE";
  case DISCORD_USER_PARTNERED_SERVER_OWNER: return "PARTNERED_SERVER_OWNER";
  case DISCORD_USER_HYPESQUAD_EVENTS: return "HYPESQUAD_EVENTS";
  case DISCORD_USER_BUG_HUNTER_LEVEL_1: return "BUG_HUNTER_LEVEL_1";
  case DISCORD_USER_HOUSE_BRAVERY: return "HOUSE_BRAVERY";
  case DISCORD_USER_HOUSE_BRILLIANCE: return "HOUSE_BRILLIANCE";
  case DISCORD_USER_HOUSE_BALANCE: return "HOUSE_BALANCE";
  case DISCORD_USER_EARLY_SUPPORTER: return "EARLY_SUPPORTER";
  case DISCORD_USER_TEAM_USER: return "TEAM_USER";
  case DISCORD_USER_SYSTEM: return "SYSTEM";
  case DISCORD_USER_BUG_HUNTER_LEVEL_2: return "BUG_HUNTER_LEVEL_2";
  case DISCORD_USER_VERIFIED_BOT: return "VERIFIED_BOT";
  case DISCORD_USER_EARLY_VERIFIED_BOT_DEVELOPER: return "EARLY_VERIFIED_BOT_DEVELOPER";
  }

  return NULL;
}

void discord_user_flags_list_free(enum discord_user_flags **p) {
  ntl_free((void**)p, NULL);
}

void discord_user_flags_list_from_json(char *str, size_t len, enum discord_user_flags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_user_flags);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_user_flags_list_to_json(char *str, size_t len, enum discord_user_flags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}



void discord_user_premium_types_list_free_v(void **p) {
  discord_user_premium_types_list_free((enum discord_user_premium_types**)p);
}

void discord_user_premium_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_user_premium_types_list_from_json(str, len, (enum discord_user_premium_types ***)p);
}

size_t discord_user_premium_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_user_premium_types_list_to_json(str, len, (enum discord_user_premium_types **)p);
}

enum discord_user_premium_types discord_user_premium_types_eval(char *s){
  if(strcasecmp("NITRO_CLASSIC", s) == 0) return DISCORD_USER_NITRO_CLASSIC;
  if(strcasecmp("NITRO", s) == 0) return DISCORD_USER_NITRO;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_user_premium_types_print(enum discord_user_premium_types v){

  switch (v) {
  case DISCORD_USER_NITRO_CLASSIC: return "NITRO_CLASSIC";
  case DISCORD_USER_NITRO: return "NITRO";
  }

  return NULL;
}

void discord_user_premium_types_list_free(enum discord_user_premium_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_user_premium_types_list_from_json(char *str, size_t len, enum discord_user_premium_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_user_premium_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_user_premium_types_list_to_json(char *str, size_t len, enum discord_user_premium_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_user_from_json_p(char *json, size_t len, struct discord_user **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_user_from_json(json, len, *pp);
}
void discord_user_from_json(char *json, size_t len, struct discord_user *p)
{
  discord_user_init(p);
  json_extract(json, len, 
  /* discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                "(id):F,"
  /* discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
                "(username):?s,"
  /* discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
                "(discriminator):?s,"
  /* discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }}' */
                "(avatar):?s,"
  /* discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
                "(bot):b,"
  /* discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
                "(system):b,"
  /* discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
                "(mfa_enabled):b,"
  /* discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"*" }}' */
                "(locale):?s,"
  /* discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                "(verified):b,"
  /* discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"*" }}' */
                "(email):?s,"
  /* discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                "(flags):d,"
  /* discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }}' */
                "(banner):?s,"
  /* discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
                "(premium_type):d,"
  /* discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                "(public_flags):d,",
  /* discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                cee_strtou64, &p->id,
  /* discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
                &p->username,
  /* discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
                &p->discriminator,
  /* discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }}' */
                &p->avatar,
  /* discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
                &p->bot,
  /* discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
                &p->System,
  /* discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
                &p->mfa_enabled,
  /* discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"*" }}' */
                &p->locale,
  /* discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                &p->verified,
  /* discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"*" }}' */
                &p->email,
  /* discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                &p->flags,
  /* discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }}' */
                &p->banner,
  /* discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
                &p->premium_type,
  /* discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                &p->public_flags);
}

size_t discord_user_to_json(char *json, size_t len, struct discord_user *p)
{
  size_t r;
  void *arg_switches[14]={NULL};
  /* discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  arg_switches[0] = &p->id;

  /* discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[1] = p->username;

  /* discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[2] = p->discriminator;

  /* discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[3] = p->avatar;

  /* discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
  arg_switches[4] = &p->bot;

  /* discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
  arg_switches[5] = &p->System;

  /* discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->mfa_enabled;

  /* discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[7] = p->locale;

  /* discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  arg_switches[8] = &p->verified;

  /* discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[9] = p->email;

  /* discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  arg_switches[10] = &p->flags;

  /* discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[11] = p->banner;

  /* discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
  arg_switches[12] = &p->premium_type;

  /* discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  arg_switches[13] = &p->public_flags;

  r=json_inject(json, len, 
  /* discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                "(id):|F|,"
  /* discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
                "(username):s,"
  /* discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
                "(discriminator):s,"
  /* discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }}' */
                "(avatar):s,"
  /* discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
                "(bot):b,"
  /* discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
                "(system):b,"
  /* discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
                "(mfa_enabled):b,"
  /* discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"*" }}' */
                "(locale):s,"
  /* discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                "(verified):b,"
  /* discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"*" }}' */
                "(email):s,"
  /* discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                "(flags):d,"
  /* discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }}' */
                "(banner):s,"
  /* discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
                "(premium_type):d,"
  /* discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                "(public_flags):d,"
                "@arg_switches:b",
  /* discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                cee_u64tostr, &p->id,
  /* discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
                p->username,
  /* discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
                p->discriminator,
  /* discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }}' */
                p->avatar,
  /* discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
                &p->bot,
  /* discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
                &p->System,
  /* discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
                &p->mfa_enabled,
  /* discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"*" }}' */
                p->locale,
  /* discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                &p->verified,
  /* discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"*" }}' */
                p->email,
  /* discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                &p->flags,
  /* discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }}' */
                p->banner,
  /* discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
                &p->premium_type,
  /* discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                &p->public_flags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_user_cleanup_v(void *p) {
  discord_user_cleanup((struct discord_user *)p);
}

void discord_user_init_v(void *p) {
  discord_user_init((struct discord_user *)p);
}

void discord_user_from_json_v(char *json, size_t len, void *p) {
 discord_user_from_json(json, len, (struct discord_user*)p);
}

size_t discord_user_to_json_v(char *json, size_t len, void *p) {
  return discord_user_to_json(json, len, (struct discord_user*)p);
}

void discord_user_list_free_v(void **p) {
  discord_user_list_free((struct discord_user**)p);
}

void discord_user_list_from_json_v(char *str, size_t len, void *p) {
  discord_user_list_from_json(str, len, (struct discord_user ***)p);
}

size_t discord_user_list_to_json_v(char *str, size_t len, void *p){
  return discord_user_list_to_json(str, len, (struct discord_user **)p);
}


void discord_user_cleanup(struct discord_user *d) {
  /* discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  (void)d->id;
  /* discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
  if (d->username)
    free(d->username);
  /* discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
  if (d->discriminator)
    free(d->discriminator);
  /* discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }}' */
  if (d->avatar)
    free(d->avatar);
  /* discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
  (void)d->bot;
  /* discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
  (void)d->System;
  /* discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
  (void)d->mfa_enabled;
  /* discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"*" }}' */
  if (d->locale)
    free(d->locale);
  /* discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  (void)d->verified;
  /* discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"*" }}' */
  if (d->email)
    free(d->email);
  /* discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  (void)d->flags;
  /* discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }}' */
  if (d->banner)
    free(d->banner);
  /* discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
  (void)d->premium_type;
  /* discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  (void)d->public_flags;
}

void discord_user_init(struct discord_user *p) {
  memset(p, 0, sizeof(struct discord_user));
  /* discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */

  /* discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */

  /* discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */

  /* discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */

  /* discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */

  /* discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */

  /* discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */

  /* discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */

  /* discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */

}
void discord_user_list_free(struct discord_user **p) {
  ntl_free((void**)p, (void(*)(void*))discord_user_cleanup);
}

void discord_user_list_from_json(char *str, size_t len, struct discord_user ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_user);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_user_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_user_list_to_json(char *str, size_t len, struct discord_user **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_user_to_json);
}



void discord_visibility_types_list_free_v(void **p) {
  discord_visibility_types_list_free((enum discord_visibility_types**)p);
}

void discord_visibility_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_visibility_types_list_from_json(str, len, (enum discord_visibility_types ***)p);
}

size_t discord_visibility_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_visibility_types_list_to_json(str, len, (enum discord_visibility_types **)p);
}

enum discord_visibility_types discord_visibility_types_eval(char *s){
  if(strcasecmp("NONE", s) == 0) return DISCORD_VISIBILITY_NONE;
  if(strcasecmp("EVERYONE", s) == 0) return DISCORD_VISIBILITY_EVERYONE;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_visibility_types_print(enum discord_visibility_types v){

  switch (v) {
  case DISCORD_VISIBILITY_NONE: return "NONE";
  case DISCORD_VISIBILITY_EVERYONE: return "EVERYONE";
  }

  return NULL;
}

void discord_visibility_types_list_free(enum discord_visibility_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_visibility_types_list_from_json(char *str, size_t len, enum discord_visibility_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_visibility_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_visibility_types_list_to_json(char *str, size_t len, enum discord_visibility_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_connection_from_json_p(char *json, size_t len, struct discord_connection **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_connection_from_json(json, len, *pp);
}
void discord_connection_from_json(char *json, size_t len, struct discord_connection *p)
{
  discord_connection_init(p);
  json_extract(json, len, 
  /* discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                "(id):?s,"
  /* discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):?s,"
  /* discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                "(revoked):b,"
  /* discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
                "(integrations):F,"
  /* discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                "(verified):b,"
  /* discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
                "(friend_sync):b,"
  /* discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
                "(show_activity):b,"
  /* discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
                "(visibility):d,",
  /* discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                &p->id,
  /* discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                &p->type,
  /* discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                &p->revoked,
  /* discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
                discord_integration_list_from_json, &p->integrations,
  /* discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                &p->verified,
  /* discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
                &p->friend_sync,
  /* discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
                &p->show_activity,
  /* discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
                &p->visibility);
}

size_t discord_connection_to_json(char *json, size_t len, struct discord_connection *p)
{
  size_t r;
  void *arg_switches[9]={NULL};
  /* discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->id;

  /* discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[1] = p->name;

  /* discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[2] = p->type;

  /* discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  arg_switches[3] = &p->revoked;

  /* discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
  arg_switches[4] = p->integrations;

  /* discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  arg_switches[5] = &p->verified;

  /* discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->friend_sync;

  /* discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
  arg_switches[7] = &p->show_activity;

  /* discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
  arg_switches[8] = &p->visibility;

  r=json_inject(json, len, 
  /* discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                "(id):s,"
  /* discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):s,"
  /* discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                "(revoked):b,"
  /* discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
                "(integrations):F,"
  /* discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                "(verified):b,"
  /* discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
                "(friend_sync):b,"
  /* discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
                "(show_activity):b,"
  /* discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
                "(visibility):d,"
                "@arg_switches:b",
  /* discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                p->id,
  /* discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                p->type,
  /* discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                &p->revoked,
  /* discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
                discord_integration_list_to_json, p->integrations,
  /* discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                &p->verified,
  /* discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
                &p->friend_sync,
  /* discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
                &p->show_activity,
  /* discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
                &p->visibility,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_connection_cleanup_v(void *p) {
  discord_connection_cleanup((struct discord_connection *)p);
}

void discord_connection_init_v(void *p) {
  discord_connection_init((struct discord_connection *)p);
}

void discord_connection_from_json_v(char *json, size_t len, void *p) {
 discord_connection_from_json(json, len, (struct discord_connection*)p);
}

size_t discord_connection_to_json_v(char *json, size_t len, void *p) {
  return discord_connection_to_json(json, len, (struct discord_connection*)p);
}

void discord_connection_list_free_v(void **p) {
  discord_connection_list_free((struct discord_connection**)p);
}

void discord_connection_list_from_json_v(char *str, size_t len, void *p) {
  discord_connection_list_from_json(str, len, (struct discord_connection ***)p);
}

size_t discord_connection_list_to_json_v(char *str, size_t len, void *p){
  return discord_connection_list_to_json(str, len, (struct discord_connection **)p);
}


void discord_connection_cleanup(struct discord_connection *d) {
  /* discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  if (d->id)
    free(d->id);
  /* discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  if (d->type)
    free(d->type);
  /* discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  (void)d->revoked;
  /* discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
  if (d->integrations)
    discord_integration_list_free(d->integrations);
  /* discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  (void)d->verified;
  /* discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
  (void)d->friend_sync;
  /* discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
  (void)d->show_activity;
  /* discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
  (void)d->visibility;
}

void discord_connection_init(struct discord_connection *p) {
  memset(p, 0, sizeof(struct discord_connection));
  /* discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */

  /* discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */

  /* discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */

  /* discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */

  /* discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */

  /* discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */

  /* discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */

}
void discord_connection_list_free(struct discord_connection **p) {
  ntl_free((void**)p, (void(*)(void*))discord_connection_cleanup);
}

void discord_connection_list_from_json(char *str, size_t len, struct discord_connection ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_connection);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_connection_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_connection_list_to_json(char *str, size_t len, struct discord_connection **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_connection_to_json);
}

