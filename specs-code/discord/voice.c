/* This file is generated from specs/discord/voice.json, Please don't edit it. */
/**
 * @file specs-code/discord/voice.c
 * @see https://discord.com/developers/docs/resources/voice
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_voice_state_from_json(char *json, size_t len, struct discord_voice_state **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_voice_state *p = *pp;
  discord_voice_state_init(p);
  r=json_extract(json, len, 
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(guild_id):F,"
  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(channel_id):F,"
  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(user_id):F,"
  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
                "(member):F,"
  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
                "(session_id):?s,"
  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                "(deaf):b,"
  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                "(mute):b,"
  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
                "(self_deaf):b,"
  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
                "(self_mute):b,"
  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
                "(self_stream):b,"
  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
                "(self_video):b,"
  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
                "(supress):b,",
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->user_id,
  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
                discord_guild_member_from_json, &p->member,
  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
                &p->session_id,
  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                &p->deaf,
  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                &p->mute,
  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
                &p->self_deaf,
  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
                &p->self_mute,
  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
                &p->self_stream,
  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
                &p->self_video,
  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
                &p->supress);
  ret = r;
}

size_t discord_voice_state_to_json(char *json, size_t len, struct discord_voice_state *p)
{
  size_t r;
  void *arg_switches[12]={NULL};
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->guild_id;

  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  arg_switches[1] = &p->channel_id;

  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[2] = &p->user_id;

  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
  arg_switches[3] = p->member;

  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[4] = p->session_id;

  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  arg_switches[5] = &p->deaf;

  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->mute;

  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
  arg_switches[7] = &p->self_deaf;

  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
  arg_switches[8] = &p->self_mute;

  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
  arg_switches[9] = &p->self_stream;

  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
  arg_switches[10] = &p->self_video;

  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
  arg_switches[11] = &p->supress;

  r=json_inject(json, len, 
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(guild_id):|F|,"
  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(channel_id):|F|,"
  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(user_id):|F|,"
  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
                "(member):F,"
  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
                "(session_id):s,"
  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                "(deaf):b,"
  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                "(mute):b,"
  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
                "(self_deaf):b,"
  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
                "(self_mute):b,"
  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
                "(self_stream):b,"
  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
                "(self_video):b,"
  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
                "(supress):b,"
                "@arg_switches:b",
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->user_id,
  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
                discord_guild_member_to_json, p->member,
  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
                p->session_id,
  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                &p->deaf,
  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                &p->mute,
  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
                &p->self_deaf,
  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
                &p->self_mute,
  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
                &p->self_stream,
  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
                &p->self_video,
  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
                &p->supress,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_voice_state_cleanup_v(void *p) {
  discord_voice_state_cleanup((struct discord_voice_state *)p);
}

void discord_voice_state_init_v(void *p) {
  discord_voice_state_init((struct discord_voice_state *)p);
}

void discord_voice_state_from_json_v(char *json, size_t len, void *pp) {
 discord_voice_state_from_json(json, len, (struct discord_voice_state**)pp);
}

size_t discord_voice_state_to_json_v(char *json, size_t len, void *p) {
  return discord_voice_state_to_json(json, len, (struct discord_voice_state*)p);
}

void discord_voice_state_list_free_v(void **p) {
  discord_voice_state_list_free((struct discord_voice_state**)p);
}

void discord_voice_state_list_from_json_v(char *str, size_t len, void *p) {
  discord_voice_state_list_from_json(str, len, (struct discord_voice_state ***)p);
}

size_t discord_voice_state_list_to_json_v(char *str, size_t len, void *p){
  return discord_voice_state_list_to_json(str, len, (struct discord_voice_state **)p);
}


void discord_voice_state_cleanup(struct discord_voice_state *d) {
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  /* p->guild_id is a scalar */
  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  /* p->channel_id is a scalar */
  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  /* p->user_id is a scalar */
  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
  if (d->member) {
    discord_guild_member_cleanup(d->member);
    free(d->member);
  }
  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
  if (d->session_id)
    free(d->session_id);
  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  /* p->deaf is a scalar */
  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  /* p->mute is a scalar */
  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
  /* p->self_deaf is a scalar */
  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
  /* p->self_mute is a scalar */
  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
  /* p->self_stream is a scalar */
  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
  /* p->self_video is a scalar */
  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
  /* p->supress is a scalar */
}

void discord_voice_state_init(struct discord_voice_state *p) {
  memset(p, 0, sizeof(struct discord_voice_state));
  /* specs/discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */

  /* specs/discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */

}
void discord_voice_state_list_free(struct discord_voice_state **p) {
  ntl_free((void**)p, (vfvp)discord_voice_state_cleanup);
}

void discord_voice_state_list_from_json(char *str, size_t len, struct discord_voice_state ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_voice_state);
  d.init_elem = NULL;
  d.elem_from_buf = discord_voice_state_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_voice_state_list_to_json(char *str, size_t len, struct discord_voice_state **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_voice_state_to_json_v);
}


void discord_voice_region_from_json(char *json, size_t len, struct discord_voice_region **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_voice_region *p = *pp;
  discord_voice_region_init(p);
  r=json_extract(json, len, 
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                "(id):?s,"
  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
                "(vip):b,"
  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
                "(optimal):b,"
  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
                "(deprecated):b,"
  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
                "(custom):b,",
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                &p->id,
  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
                &p->vip,
  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
                &p->optimal,
  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
                &p->deprecated,
  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
                &p->custom);
  ret = r;
}

size_t discord_voice_region_to_json(char *json, size_t len, struct discord_voice_region *p)
{
  size_t r;
  void *arg_switches[6]={NULL};
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->id;

  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[1] = p->name;

  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
  arg_switches[2] = &p->vip;

  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
  arg_switches[3] = &p->optimal;

  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
  arg_switches[4] = &p->deprecated;

  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
  arg_switches[5] = &p->custom;

  r=json_inject(json, len, 
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                "(id):s,"
  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
                "(vip):b,"
  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
                "(optimal):b,"
  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
                "(deprecated):b,"
  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
                "(custom):b,"
                "@arg_switches:b",
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                p->id,
  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
                &p->vip,
  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
                &p->optimal,
  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
                &p->deprecated,
  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
                &p->custom,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_voice_region_cleanup_v(void *p) {
  discord_voice_region_cleanup((struct discord_voice_region *)p);
}

void discord_voice_region_init_v(void *p) {
  discord_voice_region_init((struct discord_voice_region *)p);
}

void discord_voice_region_from_json_v(char *json, size_t len, void *pp) {
 discord_voice_region_from_json(json, len, (struct discord_voice_region**)pp);
}

size_t discord_voice_region_to_json_v(char *json, size_t len, void *p) {
  return discord_voice_region_to_json(json, len, (struct discord_voice_region*)p);
}

void discord_voice_region_list_free_v(void **p) {
  discord_voice_region_list_free((struct discord_voice_region**)p);
}

void discord_voice_region_list_from_json_v(char *str, size_t len, void *p) {
  discord_voice_region_list_from_json(str, len, (struct discord_voice_region ***)p);
}

size_t discord_voice_region_list_to_json_v(char *str, size_t len, void *p){
  return discord_voice_region_list_to_json(str, len, (struct discord_voice_region **)p);
}


void discord_voice_region_cleanup(struct discord_voice_region *d) {
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  if (d->id)
    free(d->id);
  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
  /* p->vip is a scalar */
  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
  /* p->optimal is a scalar */
  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
  /* p->deprecated is a scalar */
  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
  /* p->custom is a scalar */
}

void discord_voice_region_init(struct discord_voice_region *p) {
  memset(p, 0, sizeof(struct discord_voice_region));
  /* specs/discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */

  /* specs/discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */

}
void discord_voice_region_list_free(struct discord_voice_region **p) {
  ntl_free((void**)p, (vfvp)discord_voice_region_cleanup);
}

void discord_voice_region_list_from_json(char *str, size_t len, struct discord_voice_region ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_voice_region);
  d.init_elem = NULL;
  d.elem_from_buf = discord_voice_region_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_voice_region_list_to_json(char *str, size_t len, struct discord_voice_region **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_voice_region_to_json_v);
}

