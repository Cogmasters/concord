/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/**
 * @file specs-code/discord/invite.c
 * @author cee-studio
 * @date 21 Jun 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/invite
 */

#include "specs.h"


enum discord_invite_target_user_types discord_invite_target_user_types_from_string(char *s){
  if(strcasecmp("STREAM", s) == 0) return DISCORD_INVITE_STREAM;
  abort();
}
char* discord_invite_target_user_types_to_string(enum discord_invite_target_user_types v){
  if (v == DISCORD_INVITE_STREAM) return "STREAM";

  return (void*)0;
}
bool discord_invite_target_user_types_has(enum discord_invite_target_user_types v, char *s) {
  enum discord_invite_target_user_types v1 = discord_invite_target_user_types_from_string(s);
  if (v == v1) return true;
  return false;
}

void discord_invite_from_json(char *json, size_t len, struct discord_invite *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
                "(code):?s,"
  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
                "(guild):F,"
  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
                "(channel):F,"
  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
                "(inviter):F,"
  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                "(target_user):F,"
  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
                "(target_user_type):d,"
  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
                "(approximate_presence_count):d,"
  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
                "(approximate_member_count):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
                &p->code,
  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
                discord_guild_from_json, p->guild,
  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
                discord_channel_from_json, p->channel,
  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
                discord_user_from_json, p->inviter,
  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                discord_user_from_json, p->target_user,
  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
                &p->target_user_type,
  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
                &p->approximate_presence_count,
  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
                &p->approximate_member_count,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_invite_use_default_inject_settings(struct discord_invite *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  p->__M.arg_switches[0] = p->code;

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  p->__M.arg_switches[1] = p->guild;

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  p->__M.arg_switches[2] = p->channel;

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  p->__M.arg_switches[3] = p->inviter;

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  p->__M.arg_switches[4] = p->target_user;

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
  p->__M.arg_switches[5] = &p->target_user_type;

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
  p->__M.arg_switches[6] = &p->approximate_presence_count;

  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
  p->__M.arg_switches[7] = &p->approximate_member_count;

}

size_t discord_invite_to_json(char *json, size_t len, struct discord_invite *p)
{
  size_t r;
  discord_invite_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
                "(code):s,"
  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
                "(guild):F,"
  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
                "(channel):F,"
  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
                "(inviter):F,"
  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                "(target_user):F,"
  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
                "(target_user_type):d,"
  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
                "(approximate_presence_count):d,"
  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
                "(approximate_member_count):d,"
                "@arg_switches:b",
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
                p->code,
  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
                discord_guild_to_json, p->guild,
  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
                discord_channel_to_json, p->channel,
  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
                discord_user_to_json, p->inviter,
  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                discord_user_to_json, p->target_user,
  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
                &p->target_user_type,
  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
                &p->approximate_presence_count,
  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
                &p->approximate_member_count,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_invite_cleanup_v(void *p) {
  discord_invite_cleanup((struct discord_invite *)p);
}

void discord_invite_init_v(void *p) {
  discord_invite_init((struct discord_invite *)p);
}

void discord_invite_free_v(void *p) {
 discord_invite_free((struct discord_invite *)p);
};

void discord_invite_from_json_v(char *json, size_t len, void *p) {
 discord_invite_from_json(json, len, (struct discord_invite*)p);
}

size_t discord_invite_to_json_v(char *json, size_t len, void *p) {
  return discord_invite_to_json(json, len, (struct discord_invite*)p);
}

void discord_invite_list_free_v(void **p) {
  discord_invite_list_free((struct discord_invite**)p);
}

void discord_invite_list_from_json_v(char *str, size_t len, void *p) {
  discord_invite_list_from_json(str, len, (struct discord_invite ***)p);
}

size_t discord_invite_list_to_json_v(char *str, size_t len, void *p){
  return discord_invite_list_to_json(str, len, (struct discord_invite **)p);
}


void discord_invite_cleanup(struct discord_invite *d) {
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */
  if (d->code)
    free(d->code);
  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  if (d->guild)
    discord_guild_free(d->guild);
  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  if (d->channel)
    discord_channel_free(d->channel);
  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  if (d->inviter)
    discord_user_free(d->inviter);
  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  if (d->target_user)
    discord_user_free(d->target_user);
  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
  // p->target_user_type is a scalar
  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
  // p->approximate_presence_count is a scalar
  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
  // p->approximate_member_count is a scalar
}

void discord_invite_init(struct discord_invite *p) {
  memset(p, 0, sizeof(struct discord_invite));
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"@todo fixed size limit"}' */

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  p->guild = discord_guild_alloc();

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  p->channel = discord_channel_alloc();

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  p->inviter = discord_user_alloc();

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  p->target_user = discord_user_alloc();

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */

  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */

}
struct discord_invite* discord_invite_alloc() {
  struct discord_invite *p= malloc(sizeof(struct discord_invite));
  discord_invite_init(p);
  return p;
}

void discord_invite_free(struct discord_invite *p) {
  discord_invite_cleanup(p);
  free(p);
}

void discord_invite_list_free(struct discord_invite **p) {
  ntl_free((void**)p, (vfvp)discord_invite_cleanup);
}

void discord_invite_list_from_json(char *str, size_t len, struct discord_invite ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_invite);
  d.init_elem = discord_invite_init_v;
  d.elem_from_buf = discord_invite_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_invite_list_to_json(char *str, size_t len, struct discord_invite **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_invite_to_json_v);
}


void discord_invite_metadata_from_json(char *json, size_t len, struct discord_invite_metadata *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
                "(user):d,"
  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                "(max_uses):d,"
  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                "(max_age):d,"
  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
                "(temporary):d,"
  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
                "(created_at):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
                &p->user,
  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                &p->max_uses,
  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                &p->max_age,
  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
                &p->temporary,
  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
                cee_iso8601_to_unix_ms, &p->created_at,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_invite_metadata_use_default_inject_settings(struct discord_invite_metadata *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
  p->__M.arg_switches[0] = &p->user;

  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  p->__M.arg_switches[1] = &p->max_uses;

  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  p->__M.arg_switches[2] = &p->max_age;

  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
  p->__M.arg_switches[3] = &p->temporary;

  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  p->__M.arg_switches[4] = &p->created_at;

}

size_t discord_invite_metadata_to_json(char *json, size_t len, struct discord_invite_metadata *p)
{
  size_t r;
  discord_invite_metadata_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
                "(user):d,"
  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                "(max_uses):d,"
  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                "(max_age):d,"
  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
                "(temporary):d,"
  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
                "(created_at):|F|,"
                "@arg_switches:b",
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
                &p->user,
  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                &p->max_uses,
  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                &p->max_age,
  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
                &p->temporary,
  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
                cee_unix_ms_to_iso8601, &p->created_at,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_invite_metadata_cleanup_v(void *p) {
  discord_invite_metadata_cleanup((struct discord_invite_metadata *)p);
}

void discord_invite_metadata_init_v(void *p) {
  discord_invite_metadata_init((struct discord_invite_metadata *)p);
}

void discord_invite_metadata_free_v(void *p) {
 discord_invite_metadata_free((struct discord_invite_metadata *)p);
};

void discord_invite_metadata_from_json_v(char *json, size_t len, void *p) {
 discord_invite_metadata_from_json(json, len, (struct discord_invite_metadata*)p);
}

size_t discord_invite_metadata_to_json_v(char *json, size_t len, void *p) {
  return discord_invite_metadata_to_json(json, len, (struct discord_invite_metadata*)p);
}

void discord_invite_metadata_list_free_v(void **p) {
  discord_invite_metadata_list_free((struct discord_invite_metadata**)p);
}

void discord_invite_metadata_list_from_json_v(char *str, size_t len, void *p) {
  discord_invite_metadata_list_from_json(str, len, (struct discord_invite_metadata ***)p);
}

size_t discord_invite_metadata_list_to_json_v(char *str, size_t len, void *p){
  return discord_invite_metadata_list_to_json(str, len, (struct discord_invite_metadata **)p);
}


void discord_invite_metadata_cleanup(struct discord_invite_metadata *d) {
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
  // p->user is a scalar
  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  // p->max_uses is a scalar
  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  // p->max_age is a scalar
  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
  // p->temporary is a scalar
  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  // p->created_at is a scalar
}

void discord_invite_metadata_init(struct discord_invite_metadata *p) {
  memset(p, 0, sizeof(struct discord_invite_metadata));
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */

  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */

  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */

  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */

  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */

}
struct discord_invite_metadata* discord_invite_metadata_alloc() {
  struct discord_invite_metadata *p= malloc(sizeof(struct discord_invite_metadata));
  discord_invite_metadata_init(p);
  return p;
}

void discord_invite_metadata_free(struct discord_invite_metadata *p) {
  discord_invite_metadata_cleanup(p);
  free(p);
}

void discord_invite_metadata_list_free(struct discord_invite_metadata **p) {
  ntl_free((void**)p, (vfvp)discord_invite_metadata_cleanup);
}

void discord_invite_metadata_list_from_json(char *str, size_t len, struct discord_invite_metadata ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_invite_metadata);
  d.init_elem = discord_invite_metadata_init_v;
  d.elem_from_buf = discord_invite_metadata_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_invite_metadata_list_to_json(char *str, size_t len, struct discord_invite_metadata **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_invite_metadata_to_json_v);
}

