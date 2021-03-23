/* This file is generated from specs/user.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/user#user-object
*/

void discord_user_dati_from_json(char *json, size_t len, struct discord_user_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/user.json:47:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
                "(id):F,"
  /* specs/user.json:48:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
                "(username):s,"
  /* specs/user.json:49:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
                "(discriminator):s,"
  /* specs/user.json:50:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                "(avatar):s,"
  /* specs/user.json:51:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
                "(bot):b,"
  /* specs/user.json:52:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
                "(system):b,"
  /* specs/user.json:53:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
                "(mfa_enabled):b,"
  /* specs/user.json:54:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
                "(locale):s,"
  /* specs/user.json:55:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                "(verified):b,"
  /* specs/user.json:56:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
                "(email):s,"
  /* specs/user.json:57:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
                "(flags):d,"
  /* specs/user.json:58:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types_code" }}'
  */
                "(premium_type):d,"
  /* specs/user.json:59:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
                "(public_flags):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/user.json:47:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
                orka_strtoull, &p->id,
  /* specs/user.json:48:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
                p->username,
  /* specs/user.json:49:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
                p->discriminator,
  /* specs/user.json:50:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                p->avatar,
  /* specs/user.json:51:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
                &p->bot,
  /* specs/user.json:52:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
                &p->System,
  /* specs/user.json:53:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
                &p->mfa_enabled,
  /* specs/user.json:54:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
                p->locale,
  /* specs/user.json:55:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                &p->verified,
  /* specs/user.json:56:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
                p->email,
  /* specs/user.json:57:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
                &p->flags,
  /* specs/user.json:58:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types_code" }}'
  */
                &p->premium_type,
  /* specs/user.json:59:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
                &p->public_flags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_user_dati_use_default_inject_settings(struct discord_user_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/user.json:47:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
  p->__M.arg_switches[0] = &p->id;

  /* specs/user.json:48:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
  p->__M.arg_switches[1] = p->username;

  /* specs/user.json:49:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
  p->__M.arg_switches[2] = p->discriminator;

  /* specs/user.json:50:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  p->__M.arg_switches[3] = p->avatar;

  /* specs/user.json:51:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[4] = &p->bot;

  /* specs/user.json:52:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[5] = &p->System;

  /* specs/user.json:53:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[6] = &p->mfa_enabled;

  /* specs/user.json:54:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
  p->__M.arg_switches[7] = p->locale;

  /* specs/user.json:55:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[8] = &p->verified;

  /* specs/user.json:56:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
  p->__M.arg_switches[9] = p->email;

  /* specs/user.json:57:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
  p->__M.arg_switches[10] = &p->flags;

  /* specs/user.json:58:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types_code" }}'
  */
  p->__M.arg_switches[11] = &p->premium_type;

  /* specs/user.json:59:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
  p->__M.arg_switches[12] = &p->public_flags;

}

size_t discord_user_dati_to_json(char *json, size_t len, struct discord_user_dati *p)
{
  size_t r;
  discord_user_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/user.json:47:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
                "(id):|F|,"
  /* specs/user.json:48:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
                "(username):s,"
  /* specs/user.json:49:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
                "(discriminator):s,"
  /* specs/user.json:50:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                "(avatar):s,"
  /* specs/user.json:51:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
                "(bot):b,"
  /* specs/user.json:52:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
                "(system):b,"
  /* specs/user.json:53:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
                "(mfa_enabled):b,"
  /* specs/user.json:54:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
                "(locale):s,"
  /* specs/user.json:55:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                "(verified):b,"
  /* specs/user.json:56:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
                "(email):s,"
  /* specs/user.json:57:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
                "(flags):d,"
  /* specs/user.json:58:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types_code" }}'
  */
                "(premium_type):d,"
  /* specs/user.json:59:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
                "(public_flags):d,"
                "@arg_switches:b",
  /* specs/user.json:47:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
                orka_ulltostr, &p->id,
  /* specs/user.json:48:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
                p->username,
  /* specs/user.json:49:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
                p->discriminator,
  /* specs/user.json:50:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
                p->avatar,
  /* specs/user.json:51:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
                &p->bot,
  /* specs/user.json:52:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
                &p->System,
  /* specs/user.json:53:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
                &p->mfa_enabled,
  /* specs/user.json:54:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
                p->locale,
  /* specs/user.json:55:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                &p->verified,
  /* specs/user.json:56:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
                p->email,
  /* specs/user.json:57:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
                &p->flags,
  /* specs/user.json:58:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types_code" }}'
  */
                &p->premium_type,
  /* specs/user.json:59:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
                &p->public_flags,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_user_dati_cleanup_v(void *p) {
  discord_user_dati_cleanup((struct discord_user_dati *)p);
}

void discord_user_dati_init_v(void *p) {
  discord_user_dati_init((struct discord_user_dati *)p);
}

void discord_user_dati_free_v(void *p) {
 discord_user_dati_free((struct discord_user_dati *)p);
};

void discord_user_dati_from_json_v(char *json, size_t len, void *p) {
 discord_user_dati_from_json(json, len, (struct discord_user_dati*)p);
}

size_t discord_user_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_user_dati_to_json(json, len, (struct discord_user_dati*)p);
}

void discord_user_dati_list_free_v(void **p) {
  discord_user_dati_list_free((struct discord_user_dati**)p);
}

void discord_user_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_user_dati_list_from_json(str, len, (struct discord_user_dati ***)p);
}

size_t discord_user_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_user_dati_list_to_json(str, len, (struct discord_user_dati **)p);
}


void discord_user_dati_cleanup(struct discord_user_dati *d) {
  /* specs/user.json:47:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */
  //p->id is a scalar
  /* specs/user.json:48:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */
  //p->username is a scalar
  /* specs/user.json:49:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */
  //p->discriminator is a scalar
  /* specs/user.json:50:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */
  //p->avatar is a scalar
  /* specs/user.json:51:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */
  //p->bot is a scalar
  /* specs/user.json:52:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */
  //p->System is a scalar
  /* specs/user.json:53:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */
  //p->mfa_enabled is a scalar
  /* specs/user.json:54:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */
  //p->locale is a scalar
  /* specs/user.json:55:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  //p->verified is a scalar
  /* specs/user.json:56:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */
  //p->email is a scalar
  /* specs/user.json:57:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
  //p->flags is a scalar
  /* specs/user.json:58:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types_code" }}'
  */
  //p->premium_type is a scalar
  /* specs/user.json:59:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */
  //p->public_flags is a scalar
}

void discord_user_dati_init(struct discord_user_dati *p) {
  memset(p, 0, sizeof(struct discord_user_dati));
  /* specs/user.json:47:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }'
  */

  /* specs/user.json:48:14
     '{ "name": "username", "type":{ "base":"char", "dec":"[MAX_USERNAME_LEN]"}}'
  */

  /* specs/user.json:49:14
     '{ "name": "discriminator", "type":{ "base":"char", "dec":"[MAX_DISCRIMINATOR_LEN]" }}'
  */

  /* specs/user.json:50:14
     '{ "name": "avatar", "type":{ "base":"char", "dec":"[MAX_SHA256_LEN]" }}'
  */

  /* specs/user.json:51:14
     '{ "name": "bot", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:52:14
     '{ "name": "System", "json_key": "system", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:53:14
     '{ "name": "mfa_enabled", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:54:14
     '{ "name": "locale", "type":{ "base":"char", "dec":"[MAX_LOCALE_LEN]" }}'
  */

  /* specs/user.json:55:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:56:14
     '{ "name": "email", "type":{ "base":"char", "dec":"[MAX_EMAIL_LEN]" }}'
  */

  /* specs/user.json:57:14
     '{ "name": "flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */

  /* specs/user.json:58:14
     '{ "name": "premium_type", "type":{ "base":"int", "int_alias": "enum discord_user_premium_types_code" }}'
  */

  /* specs/user.json:59:14
     '{ "name": "public_flags", "type":{ "base":"int", "int_alias": "enum discord_user_flags_code" }}'
  */

}
struct discord_user_dati* discord_user_dati_alloc() {
  struct discord_user_dati *p= (struct discord_user_dati*)malloc(sizeof(struct discord_user_dati));
  discord_user_dati_init(p);
  return p;
}

void discord_user_dati_free(struct discord_user_dati *p) {
  discord_user_dati_cleanup(p);
  free(p);
}

void discord_user_dati_list_free(struct discord_user_dati **p) {
  ntl_free((void**)p, (vfvp)discord_user_dati_cleanup);
}

void discord_user_dati_list_from_json(char *str, size_t len, struct discord_user_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_user_dati);
  d.init_elem = discord_user_dati_init_v;
  d.elem_from_buf = discord_user_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_user_dati_list_to_json(char *str, size_t len, struct discord_user_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_user_dati_to_json_v);
}


void discord_user_connection_dati_from_json(char *json, size_t len, struct discord_user_connection_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/user.json:80:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(id):?s,"
  /* specs/user.json:81:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                "(name):?s,"
  /* specs/user.json:82:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                "(type):?s,"
  /* specs/user.json:83:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                "(revoked):b,"
  /* specs/user.json:84:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration_dati", "dec":"ntl"}, "todo":true}'
  */
  /* specs/user.json:85:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                "(verified):b,"
  /* specs/user.json:86:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
                "(friend_sync):b,"
  /* specs/user.json:87:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
                "(show_activity):b,"
  /* specs/user.json:88:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types_code" }}'
  */
                "(visibility):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/user.json:80:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->id,
  /* specs/user.json:81:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                &p->name,
  /* specs/user.json:82:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                &p->type,
  /* specs/user.json:83:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                &p->revoked,
  /* specs/user.json:84:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration_dati", "dec":"ntl"}, "todo":true}'
  */
  /* specs/user.json:85:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                &p->verified,
  /* specs/user.json:86:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
                &p->friend_sync,
  /* specs/user.json:87:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
                &p->show_activity,
  /* specs/user.json:88:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types_code" }}'
  */
                &p->visibility,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_user_connection_dati_use_default_inject_settings(struct discord_user_connection_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/user.json:80:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[0] = p->id;

  /* specs/user.json:81:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[1] = p->name;

  /* specs/user.json:82:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  p->__M.arg_switches[2] = p->type;

  /* specs/user.json:83:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  p->__M.arg_switches[3] = &p->revoked;

  /* specs/user.json:84:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration_dati", "dec":"ntl"}, "todo":true}'
  */

  /* specs/user.json:85:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[5] = &p->verified;

  /* specs/user.json:86:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[6] = &p->friend_sync;

  /* specs/user.json:87:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
  p->__M.arg_switches[7] = &p->show_activity;

  /* specs/user.json:88:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types_code" }}'
  */
  p->__M.arg_switches[8] = &p->visibility;

}

size_t discord_user_connection_dati_to_json(char *json, size_t len, struct discord_user_connection_dati *p)
{
  size_t r;
  discord_user_connection_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/user.json:80:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(id):s,"
  /* specs/user.json:81:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                "(name):s,"
  /* specs/user.json:82:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                "(type):s,"
  /* specs/user.json:83:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                "(revoked):b,"
  /* specs/user.json:84:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration_dati", "dec":"ntl"}, "todo":true}'
  */
  /* specs/user.json:85:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                "(verified):b,"
  /* specs/user.json:86:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
                "(friend_sync):b,"
  /* specs/user.json:87:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
                "(show_activity):b,"
  /* specs/user.json:88:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types_code" }}'
  */
                "(visibility):d,"
                "@arg_switches:b",
  /* specs/user.json:80:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->id,
  /* specs/user.json:81:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
                p->name,
  /* specs/user.json:82:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
                p->type,
  /* specs/user.json:83:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
                &p->revoked,
  /* specs/user.json:84:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration_dati", "dec":"ntl"}, "todo":true}'
  */
  /* specs/user.json:85:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
                &p->verified,
  /* specs/user.json:86:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
                &p->friend_sync,
  /* specs/user.json:87:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
                &p->show_activity,
  /* specs/user.json:88:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types_code" }}'
  */
                &p->visibility,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_user_connection_dati_cleanup_v(void *p) {
  discord_user_connection_dati_cleanup((struct discord_user_connection_dati *)p);
}

void discord_user_connection_dati_init_v(void *p) {
  discord_user_connection_dati_init((struct discord_user_connection_dati *)p);
}

void discord_user_connection_dati_free_v(void *p) {
 discord_user_connection_dati_free((struct discord_user_connection_dati *)p);
};

void discord_user_connection_dati_from_json_v(char *json, size_t len, void *p) {
 discord_user_connection_dati_from_json(json, len, (struct discord_user_connection_dati*)p);
}

size_t discord_user_connection_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_user_connection_dati_to_json(json, len, (struct discord_user_connection_dati*)p);
}

void discord_user_connection_dati_list_free_v(void **p) {
  discord_user_connection_dati_list_free((struct discord_user_connection_dati**)p);
}

void discord_user_connection_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_user_connection_dati_list_from_json(str, len, (struct discord_user_connection_dati ***)p);
}

size_t discord_user_connection_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_user_connection_dati_list_to_json(str, len, (struct discord_user_connection_dati **)p);
}


void discord_user_connection_dati_cleanup(struct discord_user_connection_dati *d) {
  /* specs/user.json:80:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->id)
    free(d->id);
  /* specs/user.json:81:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */
  if (d->name)
    free(d->name);
  /* specs/user.json:82:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */
  if (d->type)
    free(d->type);
  /* specs/user.json:83:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */
  //p->revoked is a scalar
  /* specs/user.json:84:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration_dati", "dec":"ntl"}, "todo":true}'
  */
  //@todo p->(null)
  /* specs/user.json:85:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */
  //p->verified is a scalar
  /* specs/user.json:86:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */
  //p->friend_sync is a scalar
  /* specs/user.json:87:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */
  //p->show_activity is a scalar
  /* specs/user.json:88:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types_code" }}'
  */
  //p->visibility is a scalar
}

void discord_user_connection_dati_init(struct discord_user_connection_dati *p) {
  memset(p, 0, sizeof(struct discord_user_connection_dati));
  /* specs/user.json:80:14
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/user.json:81:14
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}'
  */

  /* specs/user.json:82:14
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}'
  */

  /* specs/user.json:83:14
     '{ "name": "revoked", "type":{ "base":"bool"}}'
  */

  /* specs/user.json:84:20
     '{ "name": "integrations", "type": {"base":"struct discord_guild_integration_dati", "dec":"ntl"}, "todo":true}'
  */

  /* specs/user.json:85:14
     '{ "name": "verified", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:86:14
     '{ "name": "friend_sync", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:87:14
     '{ "name": "show_activity", "type":{ "base":"bool" }}'
  */

  /* specs/user.json:88:14
     '{ "name": "visibility", "type":{ "base":"int", "int_alias":"enum discord_user_connection_visibility_types_code" }}'
  */

}
struct discord_user_connection_dati* discord_user_connection_dati_alloc() {
  struct discord_user_connection_dati *p= (struct discord_user_connection_dati*)malloc(sizeof(struct discord_user_connection_dati));
  discord_user_connection_dati_init(p);
  return p;
}

void discord_user_connection_dati_free(struct discord_user_connection_dati *p) {
  discord_user_connection_dati_cleanup(p);
  free(p);
}

void discord_user_connection_dati_list_free(struct discord_user_connection_dati **p) {
  ntl_free((void**)p, (vfvp)discord_user_connection_dati_cleanup);
}

void discord_user_connection_dati_list_from_json(char *str, size_t len, struct discord_user_connection_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_user_connection_dati);
  d.init_elem = discord_user_connection_dati_init_v;
  d.elem_from_buf = discord_user_connection_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_user_connection_dati_list_to_json(char *str, size_t len, struct discord_user_connection_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_user_connection_dati_to_json_v);
}

