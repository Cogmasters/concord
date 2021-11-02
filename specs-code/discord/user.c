/* This file is generated from specs/discord/user.json, Please don't edit it. */
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


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
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



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
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


void discord_user_from_json(char *json, size_t len, struct discord_user **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_user *p = *pp;
  discord_user_init(p);
  r=json_extract(json, len, 
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                "(id):F,"
  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
                "(username):?s,"
  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
                "(discriminator):?s,"
  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                "(avatar):s,"
  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
                "(bot):b,"
  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
                "(system):b,"
  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
                "(mfa_enabled):b,"
  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */
                "(locale):s,"
  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                "(verified):b,"
  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */
                "(email):s,"
  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                "(flags):d,"
  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                "(banner):s,"
  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
                "(premium_type):d,"
  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                "(public_flags):d,",
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                cee_strtoull, &p->id,
  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
                &p->username,
  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
                &p->discriminator,
  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                p->avatar,
  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
                &p->bot,
  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
                &p->System,
  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
                &p->mfa_enabled,
  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */
                p->locale,
  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                &p->verified,
  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */
                p->email,
  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                &p->flags,
  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                p->banner,
  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
                &p->premium_type,
  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                &p->public_flags);
  ret = r;
}

size_t discord_user_to_json(char *json, size_t len, struct discord_user *p)
{
  size_t r;
  void *arg_switches[14]={NULL};
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  arg_switches[0] = &p->id;

  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[1] = p->username;

  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[2] = p->discriminator;

  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  arg_switches[3] = p->avatar;

  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
  arg_switches[4] = &p->bot;

  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
  arg_switches[5] = &p->System;

  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->mfa_enabled;

  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */
  arg_switches[7] = p->locale;

  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  arg_switches[8] = &p->verified;

  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */
  arg_switches[9] = p->email;

  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  arg_switches[10] = &p->flags;

  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  arg_switches[11] = p->banner;

  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
  arg_switches[12] = &p->premium_type;

  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  arg_switches[13] = &p->public_flags;

  r=json_inject(json, len, 
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                "(id):|F|,"
  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
                "(username):s,"
  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
                "(discriminator):s,"
  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                "(avatar):s,"
  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
                "(bot):b,"
  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
                "(system):b,"
  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
                "(mfa_enabled):b,"
  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */
                "(locale):s,"
  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                "(verified):b,"
  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */
                "(email):s,"
  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                "(flags):d,"
  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                "(banner):s,"
  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
                "(premium_type):d,"
  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                "(public_flags):d,"
                "@arg_switches:b",
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                cee_ulltostr, &p->id,
  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
                p->username,
  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
                p->discriminator,
  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                p->avatar,
  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
                &p->bot,
  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
                &p->System,
  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
                &p->mfa_enabled,
  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */
                p->locale,
  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                &p->verified,
  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */
                p->email,
  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                &p->flags,
  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
                p->banner,
  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
                &p->premium_type,
  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
                &p->public_flags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_user_cleanup_v(void *p) {
  discord_user_cleanup((struct discord_user *)p);
}

void discord_user_init_v(void *p) {
  discord_user_init((struct discord_user *)p);
}

void discord_user_from_json_v(char *json, size_t len, void *pp) {
 discord_user_from_json(json, len, (struct discord_user**)pp);
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
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  /* p->id is a scalar */
  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */
  if (d->username)
    free(d->username);
  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */
  if (d->discriminator)
    free(d->discriminator);
  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  /* p->avatar is a scalar */
  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */
  /* p->bot is a scalar */
  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */
  /* p->System is a scalar */
  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */
  /* p->mfa_enabled is a scalar */
  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */
  /* p->locale is a scalar */
  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  /* p->verified is a scalar */
  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */
  /* p->email is a scalar */
  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  /* p->flags is a scalar */
  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */
  /* p->banner is a scalar */
  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */
  /* p->premium_type is a scalar */
  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */
  /* p->public_flags is a scalar */
}

void discord_user_init(struct discord_user *p) {
  memset(p, 0, sizeof(struct discord_user));
  /* specs/discord/user.json:44:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */

  /* specs/discord/user.json:45:24
     '{ "name": "username", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/user.json:46:24
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/user.json:47:24
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */

  /* specs/discord/user.json:48:24
     '{ "name": "bot", "type":{ "base":"bool" }}' */

  /* specs/discord/user.json:49:24
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}' */

  /* specs/discord/user.json:50:24
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}' */

  /* specs/discord/user.json:51:24
     '{ "name": "locale", "type":{ "base":"char", "dec":"[ORCA_LIMITS_LOCALE]" }}' */

  /* specs/discord/user.json:52:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */

  /* specs/discord/user.json:53:24
     '{ "name": "email", "type":{ "base":"char", "dec":"[ORCA_LIMITS_EMAIL]" }}' */

  /* specs/discord/user.json:54:24
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */

  /* specs/discord/user.json:55:24
     '{ "name": "banner", "type":{ "base":"char", "dec":"[ORCA_LIMITS_SHA256]" }}' */

  /* specs/discord/user.json:56:24
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}' */

  /* specs/discord/user.json:57:24
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}' */

}
void discord_user_list_free(struct discord_user **p) {
  ntl_free((void**)p, (vfvp)discord_user_cleanup);
}

void discord_user_list_from_json(char *str, size_t len, struct discord_user ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_user);
  d.init_elem = NULL;
  d.elem_from_buf = discord_user_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_user_list_to_json(char *str, size_t len, struct discord_user **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_user_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
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


void discord_connection_from_json(char *json, size_t len, struct discord_connection **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_connection *p = *pp;
  discord_connection_init(p);
  r=json_extract(json, len, 
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                "(id):?s,"
  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):?s,"
  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                "(revoked):b,"
  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
                "(integrations):F,"
  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                "(verified):b,"
  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
                "(friend_sync):b,"
  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
                "(show_activity):b,"
  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
                "(visibility):d,",
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                &p->id,
  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                &p->name,
  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                &p->type,
  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                &p->revoked,
  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
                discord_integration_list_from_json, &p->integrations,
  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                &p->verified,
  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
                &p->friend_sync,
  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
                &p->show_activity,
  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
                &p->visibility);
  ret = r;
}

size_t discord_connection_to_json(char *json, size_t len, struct discord_connection *p)
{
  size_t r;
  void *arg_switches[9]={NULL};
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->id;

  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[1] = p->name;

  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  arg_switches[2] = p->type;

  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  arg_switches[3] = &p->revoked;

  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
  arg_switches[4] = p->integrations;

  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  arg_switches[5] = &p->verified;

  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->friend_sync;

  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
  arg_switches[7] = &p->show_activity;

  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
  arg_switches[8] = &p->visibility;

  r=json_inject(json, len, 
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                "(id):s,"
  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                "(name):s,"
  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                "(type):s,"
  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                "(revoked):b,"
  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
                "(integrations):F,"
  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                "(verified):b,"
  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
                "(friend_sync):b,"
  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
                "(show_activity):b,"
  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
                "(visibility):d,"
                "@arg_switches:b",
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                p->id,
  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
                p->name,
  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
                p->type,
  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
                &p->revoked,
  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
                discord_integration_list_to_json, p->integrations,
  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
                &p->verified,
  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
                &p->friend_sync,
  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
                &p->show_activity,
  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
                &p->visibility,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_connection_cleanup_v(void *p) {
  discord_connection_cleanup((struct discord_connection *)p);
}

void discord_connection_init_v(void *p) {
  discord_connection_init((struct discord_connection *)p);
}

void discord_connection_from_json_v(char *json, size_t len, void *pp) {
 discord_connection_from_json(json, len, (struct discord_connection**)pp);
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
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  if (d->id)
    free(d->id);
  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  if (d->type)
    free(d->type);
  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */
  /* p->revoked is a scalar */
  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */
  if (d->integrations)
    discord_integration_list_free(d->integrations);
  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */
  /* p->verified is a scalar */
  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */
  /* p->friend_sync is a scalar */
  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */
  /* p->show_activity is a scalar */
  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */
  /* p->visibility is a scalar */
}

void discord_connection_init(struct discord_connection *p) {
  memset(p, 0, sizeof(struct discord_connection));
  /* specs/discord/user.json:77:24
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/user.json:78:24
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/user.json:79:24
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */

  /* specs/discord/user.json:80:24
     '{ "name": "revoked", "type":{ "base":"bool"}}' */

  /* specs/discord/user.json:81:24
     '{ "name": "integrations", "type": {"base":"struct discord_integration", "dec":"ntl"}}' */

  /* specs/discord/user.json:82:24
     '{ "name": "verified", "type":{ "base":"bool" }}' */

  /* specs/discord/user.json:83:24
     '{ "name": "friend_sync", "type":{ "base":"bool" }}' */

  /* specs/discord/user.json:84:24
     '{ "name": "show_activity", "type":{ "base":"bool" }}' */

  /* specs/discord/user.json:85:24
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_visibility_types" }}' */

}
void discord_connection_list_free(struct discord_connection **p) {
  ntl_free((void**)p, (vfvp)discord_connection_cleanup);
}

void discord_connection_list_from_json(char *str, size_t len, struct discord_connection ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_connection);
  d.init_elem = NULL;
  d.elem_from_buf = discord_connection_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_connection_list_to_json(char *str, size_t len, struct discord_connection **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_connection_to_json_v);
}

