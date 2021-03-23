/* This file is generated from specs/invite.json, Please don't edit it. */
#include "specs.h"
/*
https://discord.com/developers/docs/resources/invite#invite-object
*/

void discord_invite_dati_from_json(char *json, size_t len, struct discord_invite_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(code):?s,"
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild_dati", "dec":"*"}, "comment":"partial guild object"}'
  */
                "(guild):F,"
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel_dati", "dec":"*"}, "comment":"partial channel object"}'
  */
                "(channel):F,"
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user_dati", "dec":"*"}}'
  */
                "(inviter):F,"
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
                "(target_user):F,"
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types_code" }}'
  */
                "(target_user_type):d,"
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
                "(approximate_presence_count):d,"
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
                "(approximate_member_count):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                &p->code,
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild_dati", "dec":"*"}, "comment":"partial guild object"}'
  */
                discord_guild_dati_from_json, p->guild,
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel_dati", "dec":"*"}, "comment":"partial channel object"}'
  */
                discord_channel_dati_from_json, p->channel,
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user_dati", "dec":"*"}}'
  */
                discord_user_dati_from_json, p->inviter,
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
                discord_user_dati_from_json, p->target_user,
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types_code" }}'
  */
                &p->target_user_type,
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
                &p->approximate_presence_count,
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
                &p->approximate_member_count,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_invite_dati_use_default_inject_settings(struct discord_invite_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  p->__M.arg_switches[0] = p->code;

  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild_dati", "dec":"*"}, "comment":"partial guild object"}'
  */
  p->__M.arg_switches[1] = p->guild;

  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel_dati", "dec":"*"}, "comment":"partial channel object"}'
  */
  p->__M.arg_switches[2] = p->channel;

  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user_dati", "dec":"*"}}'
  */
  p->__M.arg_switches[3] = p->inviter;

  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
  p->__M.arg_switches[4] = p->target_user;

  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types_code" }}'
  */
  p->__M.arg_switches[5] = &p->target_user_type;

  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[6] = &p->approximate_presence_count;

  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[7] = &p->approximate_member_count;

}

size_t discord_invite_dati_to_json(char *json, size_t len, struct discord_invite_dati *p)
{
  size_t r;
  discord_invite_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                "(code):s,"
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild_dati", "dec":"*"}, "comment":"partial guild object"}'
  */
                "(guild):F,"
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel_dati", "dec":"*"}, "comment":"partial channel object"}'
  */
                "(channel):F,"
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user_dati", "dec":"*"}}'
  */
                "(inviter):F,"
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
                "(target_user):F,"
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types_code" }}'
  */
                "(target_user_type):d,"
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
                "(approximate_presence_count):d,"
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
                "(approximate_member_count):d,"
                "@arg_switches:b",
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
                p->code,
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild_dati", "dec":"*"}, "comment":"partial guild object"}'
  */
                discord_guild_dati_to_json, p->guild,
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel_dati", "dec":"*"}, "comment":"partial channel object"}'
  */
                discord_channel_dati_to_json, p->channel,
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user_dati", "dec":"*"}}'
  */
                discord_user_dati_to_json, p->inviter,
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
                discord_user_dati_to_json, p->target_user,
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types_code" }}'
  */
                &p->target_user_type,
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
                &p->approximate_presence_count,
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
                &p->approximate_member_count,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_invite_dati_cleanup_v(void *p) {
  discord_invite_dati_cleanup((struct discord_invite_dati *)p);
}

void discord_invite_dati_init_v(void *p) {
  discord_invite_dati_init((struct discord_invite_dati *)p);
}

void discord_invite_dati_free_v(void *p) {
 discord_invite_dati_free((struct discord_invite_dati *)p);
};

void discord_invite_dati_from_json_v(char *json, size_t len, void *p) {
 discord_invite_dati_from_json(json, len, (struct discord_invite_dati*)p);
}

size_t discord_invite_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_invite_dati_to_json(json, len, (struct discord_invite_dati*)p);
}

void discord_invite_dati_list_free_v(void **p) {
  discord_invite_dati_list_free((struct discord_invite_dati**)p);
}

void discord_invite_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_invite_dati_list_from_json(str, len, (struct discord_invite_dati ***)p);
}

size_t discord_invite_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_invite_dati_list_to_json(str, len, (struct discord_invite_dati **)p);
}


void discord_invite_dati_cleanup(struct discord_invite_dati *d) {
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */
  if (d->code)
    free(d->code);
  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild_dati", "dec":"*"}, "comment":"partial guild object"}'
  */
  if (d->guild)
    discord_guild_dati_free(d->guild);
  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel_dati", "dec":"*"}, "comment":"partial channel object"}'
  */
  if (d->channel)
    discord_channel_dati_free(d->channel);
  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user_dati", "dec":"*"}}'
  */
  if (d->inviter)
    discord_user_dati_free(d->inviter);
  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
  if (d->target_user)
    discord_user_dati_free(d->target_user);
  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types_code" }}'
  */
  //p->target_user_type is a scalar
  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */
  //p->approximate_presence_count is a scalar
  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */
  //p->approximate_member_count is a scalar
}

void discord_invite_dati_init(struct discord_invite_dati *p) {
  memset(p, 0, sizeof(struct discord_invite_dati));
  /* specs/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}'
  */

  /* specs/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild_dati", "dec":"*"}, "comment":"partial guild object"}'
  */
  p->guild = discord_guild_dati_alloc();

  /* specs/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel_dati", "dec":"*"}, "comment":"partial channel object"}'
  */
  p->channel = discord_channel_dati_alloc();

  /* specs/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user_dati", "dec":"*"}}'
  */
  p->inviter = discord_user_dati_alloc();

  /* specs/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user_dati", "dec":"*"}, "comment":"partial user object"}'
  */
  p->target_user = discord_user_dati_alloc();

  /* specs/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types_code" }}'
  */

  /* specs/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}'
  */

}
struct discord_invite_dati* discord_invite_dati_alloc() {
  struct discord_invite_dati *p= (struct discord_invite_dati*)malloc(sizeof(struct discord_invite_dati));
  discord_invite_dati_init(p);
  return p;
}

void discord_invite_dati_free(struct discord_invite_dati *p) {
  discord_invite_dati_cleanup(p);
  free(p);
}

void discord_invite_dati_list_free(struct discord_invite_dati **p) {
  ntl_free((void**)p, (vfvp)discord_invite_dati_cleanup);
}

void discord_invite_dati_list_from_json(char *str, size_t len, struct discord_invite_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_invite_dati);
  d.init_elem = discord_invite_dati_init_v;
  d.elem_from_buf = discord_invite_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_invite_dati_list_to_json(char *str, size_t len, struct discord_invite_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_invite_dati_to_json_v);
}


void discord_invite_metadata_dati_from_json(char *json, size_t len, struct discord_invite_metadata_dati *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
                "(user):d,"
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
                "(max_uses):d,"
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
                "(max_age):d,"
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
                "(temporary):d,"
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                "(created_at):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
                &p->user,
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
                &p->max_uses,
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
                &p->max_age,
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
                &p->temporary,
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                orka_iso8601_to_unix_ms, &p->created_at,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_invite_metadata_dati_use_default_inject_settings(struct discord_invite_metadata_dati *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[0] = &p->user;

  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[1] = &p->max_uses;

  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->max_age;

  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[3] = &p->temporary;

  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  p->__M.arg_switches[4] = &p->created_at;

}

size_t discord_invite_metadata_dati_to_json(char *json, size_t len, struct discord_invite_metadata_dati *p)
{
  size_t r;
  discord_invite_metadata_dati_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
                "(user):d,"
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
                "(max_uses):d,"
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
                "(max_age):d,"
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
                "(temporary):d,"
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                "(created_at):|F|,"
                "@arg_switches:b",
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
                &p->user,
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
                &p->max_uses,
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
                &p->max_age,
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
                &p->temporary,
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
                orka_unix_ms_to_iso8601, &p->created_at,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_invite_metadata_dati_cleanup_v(void *p) {
  discord_invite_metadata_dati_cleanup((struct discord_invite_metadata_dati *)p);
}

void discord_invite_metadata_dati_init_v(void *p) {
  discord_invite_metadata_dati_init((struct discord_invite_metadata_dati *)p);
}

void discord_invite_metadata_dati_free_v(void *p) {
 discord_invite_metadata_dati_free((struct discord_invite_metadata_dati *)p);
};

void discord_invite_metadata_dati_from_json_v(char *json, size_t len, void *p) {
 discord_invite_metadata_dati_from_json(json, len, (struct discord_invite_metadata_dati*)p);
}

size_t discord_invite_metadata_dati_to_json_v(char *json, size_t len, void *p) {
  return discord_invite_metadata_dati_to_json(json, len, (struct discord_invite_metadata_dati*)p);
}

void discord_invite_metadata_dati_list_free_v(void **p) {
  discord_invite_metadata_dati_list_free((struct discord_invite_metadata_dati**)p);
}

void discord_invite_metadata_dati_list_from_json_v(char *str, size_t len, void *p) {
  discord_invite_metadata_dati_list_from_json(str, len, (struct discord_invite_metadata_dati ***)p);
}

size_t discord_invite_metadata_dati_list_to_json_v(char *str, size_t len, void *p){
  return discord_invite_metadata_dati_list_to_json(str, len, (struct discord_invite_metadata_dati **)p);
}


void discord_invite_metadata_dati_cleanup(struct discord_invite_metadata_dati *d) {
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */
  //p->user is a scalar
  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */
  //p->max_uses is a scalar
  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */
  //p->max_age is a scalar
  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */
  //p->temporary is a scalar
  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */
  //p->created_at is a scalar
}

void discord_invite_metadata_dati_init(struct discord_invite_metadata_dati *p) {
  memset(p, 0, sizeof(struct discord_invite_metadata_dati));
  /* specs/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}'
  */

  /* specs/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}'
  */

}
struct discord_invite_metadata_dati* discord_invite_metadata_dati_alloc() {
  struct discord_invite_metadata_dati *p= (struct discord_invite_metadata_dati*)malloc(sizeof(struct discord_invite_metadata_dati));
  discord_invite_metadata_dati_init(p);
  return p;
}

void discord_invite_metadata_dati_free(struct discord_invite_metadata_dati *p) {
  discord_invite_metadata_dati_cleanup(p);
  free(p);
}

void discord_invite_metadata_dati_list_free(struct discord_invite_metadata_dati **p) {
  ntl_free((void**)p, (vfvp)discord_invite_metadata_dati_cleanup);
}

void discord_invite_metadata_dati_list_from_json(char *str, size_t len, struct discord_invite_metadata_dati ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_invite_metadata_dati);
  d.init_elem = discord_invite_metadata_dati_init_v;
  d.elem_from_buf = discord_invite_metadata_dati_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_invite_metadata_dati_list_to_json(char *str, size_t len, struct discord_invite_metadata_dati **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_invite_metadata_dati_to_json_v);
}

