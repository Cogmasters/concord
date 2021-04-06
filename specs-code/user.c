/* This file is generated from specs/user.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/user#user-object
*/


enum discord_user_flags discord_user_flags_from_string(char *s){
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
  abort();
}
char* discord_user_flags_to_string(enum discord_user_flags v){
  if (v == DISCORD_USER_DISCORD_EMPLOYEE) return "DISCORD_EMPLOYEE";
  if (v == DISCORD_USER_PARTNERED_SERVER_OWNER) return "PARTNERED_SERVER_OWNER";
  if (v == DISCORD_USER_HYPESQUAD_EVENTS) return "HYPESQUAD_EVENTS";
  if (v == DISCORD_USER_BUG_HUNTER_LEVEL_1) return "BUG_HUNTER_LEVEL_1";
  if (v == DISCORD_USER_HOUSE_BRAVERY) return "HOUSE_BRAVERY";
  if (v == DISCORD_USER_HOUSE_BRILLIANCE) return "HOUSE_BRILLIANCE";
  if (v == DISCORD_USER_HOUSE_BALANCE) return "HOUSE_BALANCE";
  if (v == DISCORD_USER_EARLY_SUPPORTER) return "EARLY_SUPPORTER";
  if (v == DISCORD_USER_TEAM_USER) return "TEAM_USER";
  if (v == DISCORD_USER_SYSTEM) return "SYSTEM";
  if (v == DISCORD_USER_BUG_HUNTER_LEVEL_2) return "BUG_HUNTER_LEVEL_2";
  if (v == DISCORD_USER_VERIFIED_BOT) return "VERIFIED_BOT";
  if (v == DISCORD_USER_EARLY_VERIFIED_BOT_DEVELOPER) return "EARLY_VERIFIED_BOT_DEVELOPER";

  return (void*)0;
}
bool discord_user_flags_has(enum discord_user_flags v, char *s) {
  enum discord_user_flags v1 = discord_user_flags_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}


enum discord_user_premium_types discord_user_premium_types_from_string(char *s){
  if(strcasecmp("NITRO_CLASSIC", s) == 0) return DISCORD_USER_NITRO_CLASSIC;
  if(strcasecmp("NITRO", s) == 0) return DISCORD_USER_NITRO;
  abort();
}
char* discord_user_premium_types_to_string(enum discord_user_premium_types v){
  if (v == DISCORD_USER_NITRO_CLASSIC) return "NITRO_CLASSIC";
  if (v == DISCORD_USER_NITRO) return "NITRO";

  return (void*)0;
}
bool discord_user_premium_types_has(enum discord_user_premium_types v, char *s) {
  enum discord_user_premium_types v1 = discord_user_premium_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_user_from_json(char *json, size_t len, struct discord_user *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
                "(id):F,"
  /* specs/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
                "(username):s,"
  /* specs/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
                "(discriminator):s,"
  /* specs/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                "(avatar):s,"
  /* specs/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
                "(bot):b,"
  /* specs/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
                "(system):b,"
  /* specs/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
                "(mfa_enabled):b,"
  /* specs/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
                "(locale):s,"
  /* specs/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                "(verified):b,"
  /* specs/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
                "(email):s,"
  /* specs/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
                "(flags):d,"
  /* specs/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */
                "(premium_type):d,"
  /* specs/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
                "(public_flags):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
                orka_strtoull, &p->id,
  /* specs/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
                p->username,
  /* specs/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
                p->discriminator,
  /* specs/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                p->avatar,
  /* specs/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
                &p->bot,
  /* specs/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
                &p->System,
  /* specs/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
                &p->mfa_enabled,
  /* specs/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
                p->locale,
  /* specs/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                &p->verified,
  /* specs/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
                p->email,
  /* specs/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
                &p->flags,
  /* specs/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */
                &p->premium_type,
  /* specs/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
                &p->public_flags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_user_use_default_inject_settings(struct discord_user *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
  p->__M.arg_switches[1] = p->username;

  /* specs/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
  p->__M.arg_switches[2] = p->discriminator;

  /* specs/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  p->__M.arg_switches[3] = p->avatar;

  /* specs/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[4] = &p->bot;

  /* specs/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[5] = &p->System;

  /* specs/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[6] = &p->mfa_enabled;

  /* specs/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
  p->__M.arg_switches[7] = p->locale;

  /* specs/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[8] = &p->verified;

  /* specs/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
  p->__M.arg_switches[9] = p->email;

  /* specs/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
  p->__M.arg_switches[10] = &p->flags;

  /* specs/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */
  p->__M.arg_switches[11] = &p->premium_type;

  /* specs/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
  p->__M.arg_switches[12] = &p->public_flags;

}

size_t discord_user_to_json(char *json, size_t len, struct discord_user *p)
{
  size_t r;
  discord_user_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
                "(id):|F|,"
  /* specs/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
                "(username):s,"
  /* specs/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
                "(discriminator):s,"
  /* specs/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                "(avatar):s,"
  /* specs/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
                "(bot):b,"
  /* specs/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
                "(system):b,"
  /* specs/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
                "(mfa_enabled):b,"
  /* specs/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
                "(locale):s,"
  /* specs/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                "(verified):b,"
  /* specs/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
                "(email):s,"
  /* specs/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
                "(flags):d,"
  /* specs/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */
                "(premium_type):d,"
  /* specs/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
                "(public_flags):d,"
                "@arg_switches:b",
  /* specs/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
                orka_ulltostr, &p->id,
  /* specs/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
                p->username,
  /* specs/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
                p->discriminator,
  /* specs/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                p->avatar,
  /* specs/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
                &p->bot,
  /* specs/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
                &p->System,
  /* specs/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
                &p->mfa_enabled,
  /* specs/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
                p->locale,
  /* specs/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                &p->verified,
  /* specs/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
                p->email,
  /* specs/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
                &p->flags,
  /* specs/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */
                &p->premium_type,
  /* specs/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
                &p->public_flags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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

void discord_user_free_v(void *p) {
 discord_user_free((struct discord_user *)p);
};

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
  /* specs/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
  //p->id is a scalar
  /* specs/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
  //p->username is a scalar
  /* specs/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
  //p->discriminator is a scalar
  /* specs/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  //p->avatar is a scalar
  /* specs/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
  //p->bot is a scalar
  /* specs/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
  //p->System is a scalar
  /* specs/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
  //p->mfa_enabled is a scalar
  /* specs/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
  //p->locale is a scalar
  /* specs/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  //p->verified is a scalar
  /* specs/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
  //p->email is a scalar
  /* specs/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
  //p->flags is a scalar
  /* specs/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */
  //p->premium_type is a scalar
  /* specs/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */
  //p->public_flags is a scalar
}

void discord_user_init(struct discord_user *p) {
  memset(p, 0, sizeof(struct discord_user));
  /* specs/user.json:45:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */

  /* specs/user.json:46:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */

  /* specs/user.json:47:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */

  /* specs/user.json:48:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */

  /* specs/user.json:49:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:50:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:51:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:52:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */

  /* specs/user.json:53:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:54:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */

  /* specs/user.json:55:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */

  /* specs/user.json:56:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types" }}'
  */

  /* specs/user.json:57:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags" }}'
  */

}
struct discord_user* discord_user_alloc() {
  struct discord_user *p= (struct discord_user*)malloc(sizeof(struct discord_user));
  discord_user_init(p);
  return p;
}

void discord_user_free(struct discord_user *p) {
  discord_user_cleanup(p);
  free(p);
}

void discord_user_list_free(struct discord_user **p) {
  ntl_free((void**)p, (vfvp)discord_user_cleanup);
}

void discord_user_list_from_json(char *str, size_t len, struct discord_user ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_user);
  d.init_elem = discord_user_init_v;
  d.elem_from_buf = discord_user_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_user_list_to_json(char *str, size_t len, struct discord_user **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_user_to_json_v);
}



enum discord_user_connection_visibility_types discord_user_connection_visibility_types_from_string(char *s){
  if(strcasecmp("NONE", s) == 0) return DISCORD_USER_CONNECTION_NONE;
  if(strcasecmp("EVERYONE", s) == 0) return DISCORD_USER_CONNECTION_EVERYONE;
  abort();
}
char* discord_user_connection_visibility_types_to_string(enum discord_user_connection_visibility_types v){
  if (v == DISCORD_USER_CONNECTION_NONE) return "NONE";
  if (v == DISCORD_USER_CONNECTION_EVERYONE) return "EVERYONE";

  return (void*)0;
}
bool discord_user_connection_visibility_types_has(enum discord_user_connection_visibility_types v, char *s) {
  enum discord_user_connection_visibility_types v1 = discord_user_connection_visibility_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_connection_from_json(char *json, size_t len, struct discord_connection *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(id):?s,"
  /* specs/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                "(name):?s,"
  /* specs/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                "(type):?s,"
  /* specs/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                "(revoked):b,"
  /* specs/user.json:81:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}, "todo":true}'
  */
  /* specs/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                "(verified):b,"
  /* specs/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
                "(friend_sync):b,"
  /* specs/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
                "(show_activity):b,"
  /* specs/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */
                "(visibility):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->id,
  /* specs/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                &p->name,
  /* specs/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                &p->type,
  /* specs/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                &p->revoked,
  /* specs/user.json:81:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}, "todo":true}'
  */
  /* specs/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                &p->verified,
  /* specs/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
                &p->friend_sync,
  /* specs/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
                &p->show_activity,
  /* specs/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */
                &p->visibility,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_connection_use_default_inject_settings(struct discord_connection *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[0] = p->id;

  /* specs/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[2] = p->type;

  /* specs/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  p->__M.arg_switches[3] = &p->revoked;

  /* specs/user.json:81:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}, "todo":true}'
  */

  /* specs/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[5] = &p->verified;

  /* specs/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[6] = &p->friend_sync;

  /* specs/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[7] = &p->show_activity;

  /* specs/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */
  p->__M.arg_switches[8] = &p->visibility;

}

size_t discord_connection_to_json(char *json, size_t len, struct discord_connection *p)
{
  size_t r;
  discord_connection_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(id):s,"
  /* specs/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                "(name):s,"
  /* specs/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                "(type):s,"
  /* specs/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                "(revoked):b,"
  /* specs/user.json:81:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}, "todo":true}'
  */
  /* specs/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                "(verified):b,"
  /* specs/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
                "(friend_sync):b,"
  /* specs/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
                "(show_activity):b,"
  /* specs/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */
                "(visibility):d,"
                "@arg_switches:b",
  /* specs/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->id,
  /* specs/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                p->name,
  /* specs/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                p->type,
  /* specs/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                &p->revoked,
  /* specs/user.json:81:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}, "todo":true}'
  */
  /* specs/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                &p->verified,
  /* specs/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
                &p->friend_sync,
  /* specs/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
                &p->show_activity,
  /* specs/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */
                &p->visibility,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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

void discord_connection_free_v(void *p) {
 discord_connection_free((struct discord_connection *)p);
};

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
  /* specs/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->id)
    free(d->id);
  /* specs/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  if (d->name)
    free(d->name);
  /* specs/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  if (d->type)
    free(d->type);
  /* specs/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  //p->revoked is a scalar
  /* specs/user.json:81:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}, "todo":true}'
  */
  //@todo p->(null)
  /* specs/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  //p->verified is a scalar
  /* specs/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
  //p->friend_sync is a scalar
  /* specs/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
  //p->show_activity is a scalar
  /* specs/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */
  //p->visibility is a scalar
}

void discord_connection_init(struct discord_connection *p) {
  memset(p, 0, sizeof(struct discord_connection));
  /* specs/user.json:77:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/user.json:78:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */

  /* specs/user.json:79:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */

  /* specs/user.json:80:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */

  /* specs/user.json:81:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration", "dec":"ntl"}, "todo":true}'
  */

  /* specs/user.json:82:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:83:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:84:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:85:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types" }}'
  */

}
struct discord_connection* discord_connection_alloc() {
  struct discord_connection *p= (struct discord_connection*)malloc(sizeof(struct discord_connection));
  discord_connection_init(p);
  return p;
}

void discord_connection_free(struct discord_connection *p) {
  discord_connection_cleanup(p);
  free(p);
}

void discord_connection_list_free(struct discord_connection **p) {
  ntl_free((void**)p, (vfvp)discord_connection_cleanup);
}

void discord_connection_list_from_json(char *str, size_t len, struct discord_connection ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_connection);
  d.init_elem = discord_connection_init_v;
  d.elem_from_buf = discord_connection_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_connection_list_to_json(char *str, size_t len, struct discord_connection **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_connection_to_json_v);
}

