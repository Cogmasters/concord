/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/**
 * @file specs-code/discord/invite.c
 * @see https://discord.com/developers/docs/resources/invite
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
void discord_invite_target_user_types_list_free_v(void **p) {
  discord_invite_target_user_types_list_free((enum discord_invite_target_user_types**)p);
}

void discord_invite_target_user_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_invite_target_user_types_list_from_json(str, len, (enum discord_invite_target_user_types ***)p);
}

size_t discord_invite_target_user_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_invite_target_user_types_list_to_json(str, len, (enum discord_invite_target_user_types **)p);
}

enum discord_invite_target_user_types discord_invite_target_user_types_eval(char *s){
  if(strcasecmp("STREAM", s) == 0) return DISCORD_INVITE_STREAM;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_invite_target_user_types_print(enum discord_invite_target_user_types v){

  switch (v) {
  case DISCORD_INVITE_STREAM: return "STREAM";
  }

  return NULL;
}

void discord_invite_target_user_types_list_free(enum discord_invite_target_user_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_invite_target_user_types_list_from_json(char *str, size_t len, enum discord_invite_target_user_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_invite_target_user_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_invite_target_user_types_list_to_json(char *str, size_t len, enum discord_invite_target_user_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_invite_from_json(char *json, size_t len, struct discord_invite **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_invite *p = *pp;
  discord_invite_init(p);
  r=json_extract(json, len, 
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */
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
                "(approximate_member_count):d,",
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */
                &p->code,
  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
                discord_guild_from_json, &p->guild,
  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
                discord_channel_from_json, &p->channel,
  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
                discord_user_from_json, &p->inviter,
  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
                discord_user_from_json, &p->target_user,
  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
                &p->target_user_type,
  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
                &p->approximate_presence_count,
  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
                &p->approximate_member_count);
  ret = r;
}

size_t discord_invite_to_json(char *json, size_t len, struct discord_invite *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->code;

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  arg_switches[1] = p->guild;

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  arg_switches[2] = p->channel;

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  arg_switches[3] = p->inviter;

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  arg_switches[4] = p->target_user;

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
  arg_switches[5] = &p->target_user_type;

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
  arg_switches[6] = &p->approximate_presence_count;

  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
  arg_switches[7] = &p->approximate_member_count;

  r=json_inject(json, len, 
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */
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
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */
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
                arg_switches, sizeof(arg_switches), true);
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

void discord_invite_from_json_v(char *json, size_t len, void *pp) {
 discord_invite_from_json(json, len, (struct discord_invite**)pp);
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
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */
  if (d->code)
    free(d->code);
  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */
  if (d->guild) {
    discord_guild_cleanup(d->guild);
    free(d->guild);
  }
  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */
  if (d->channel) {
    discord_channel_cleanup(d->channel);
    free(d->channel);
  }
  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */
  if (d->inviter) {
    discord_user_cleanup(d->inviter);
    free(d->inviter);
  }
  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */
  if (d->target_user) {
    discord_user_cleanup(d->target_user);
    free(d->target_user);
  }
  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */
  /* p->target_user_type is a scalar */
  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */
  /* p->approximate_presence_count is a scalar */
  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */
  /* p->approximate_member_count is a scalar */
}

void discord_invite_init(struct discord_invite *p) {
  memset(p, 0, sizeof(struct discord_invite));
  /* specs/discord/invite.json:22:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/invite.json:23:20
     '{ "name": "guild", "type":{ "base":"struct discord_guild", "dec":"*"}, "comment":"partial guild object"}' */

  /* specs/discord/invite.json:24:20
     '{ "name": "channel", "type":{ "base":"struct discord_channel", "dec":"*"}, "comment":"partial channel object"}' */

  /* specs/discord/invite.json:25:20
     '{ "name": "inviter", "type":{ "base":"struct discord_user", "dec":"*"}}' */

  /* specs/discord/invite.json:26:20
     '{ "name": "target_user", "type":{ "base":"struct discord_user", "dec":"*"}, "comment":"partial user object"}' */

  /* specs/discord/invite.json:27:20
     '{ "name": "target_user_type", "type":{ "base":"int", "int_alias":"enum discord_invite_target_user_types" }}' */

  /* specs/discord/invite.json:28:20
     '{ "name": "approximate_presence_count", "type":{ "base":"int" }}' */

  /* specs/discord/invite.json:29:20
     '{ "name": "approximate_member_count", "type":{ "base":"int" }}' */

}
void discord_invite_list_free(struct discord_invite **p) {
  ntl_free((void**)p, (vfvp)discord_invite_cleanup);
}

void discord_invite_list_from_json(char *str, size_t len, struct discord_invite ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_invite);
  d.init_elem = NULL;
  d.elem_from_buf = discord_invite_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_invite_list_to_json(char *str, size_t len, struct discord_invite **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_invite_to_json_v);
}


void discord_invite_metadata_from_json(char *json, size_t len, struct discord_invite_metadata **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_invite_metadata *p = *pp;
  discord_invite_metadata_init(p);
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
                "(created_at):F,",
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
                cee_iso8601_to_unix_ms, &p->created_at);
  ret = r;
}

size_t discord_invite_metadata_to_json(char *json, size_t len, struct discord_invite_metadata *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* specs/discord/invite.json:39:20
     '{ "name": "user", "type":{ "base":"int" }}' */
  arg_switches[0] = &p->user;

  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  arg_switches[1] = &p->max_uses;

  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  arg_switches[2] = &p->max_age;

  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
  arg_switches[3] = &p->temporary;

  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  arg_switches[4] = &p->created_at;

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
                arg_switches, sizeof(arg_switches), true);
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

void discord_invite_metadata_from_json_v(char *json, size_t len, void *pp) {
 discord_invite_metadata_from_json(json, len, (struct discord_invite_metadata**)pp);
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
  /* p->user is a scalar */
  /* specs/discord/invite.json:40:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  /* p->max_uses is a scalar */
  /* specs/discord/invite.json:41:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  /* p->max_age is a scalar */
  /* specs/discord/invite.json:42:20
     '{ "name": "temporary", "type":{ "base":"int" }}' */
  /* p->temporary is a scalar */
  /* specs/discord/invite.json:43:20
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*", "converter":"iso8601"}}' */
  /* p->created_at is a scalar */
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
void discord_invite_metadata_list_free(struct discord_invite_metadata **p) {
  ntl_free((void**)p, (vfvp)discord_invite_metadata_cleanup);
}

void discord_invite_metadata_list_from_json(char *str, size_t len, struct discord_invite_metadata ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_invite_metadata);
  d.init_elem = NULL;
  d.elem_from_buf = discord_invite_metadata_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_invite_metadata_list_to_json(char *str, size_t len, struct discord_invite_metadata **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_invite_metadata_to_json_v);
}

