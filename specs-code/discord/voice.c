/* This file is generated from discord/voice.json, Please don't edit it. */
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

void discord_voice_state_from_json_p(char *json, size_t len, struct discord_voice_state **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_voice_state_from_json(json, len, *pp);
}
void discord_voice_state_from_json(char *json, size_t len, struct discord_voice_state *p)
{
  discord_voice_state_init(p);
  json_extract(json, len, 
  /* discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(guild_id):F,"
  /* discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(channel_id):F,"
  /* discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(user_id):F,"
  /* discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
                "(member):F,"
  /* discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
                "(session_id):?s,"
  /* discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                "(deaf):b,"
  /* discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                "(mute):b,"
  /* discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
                "(self_deaf):b,"
  /* discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
                "(self_mute):b,"
  /* discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
                "(self_stream):b,"
  /* discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
                "(self_video):b,"
  /* discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
                "(supress):b,",
  /* discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->guild_id,
  /* discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtou64, &p->channel_id,
  /* discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtou64, &p->user_id,
  /* discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
                discord_guild_member_from_json_p, &p->member,
  /* discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
                &p->session_id,
  /* discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                &p->deaf,
  /* discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                &p->mute,
  /* discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
                &p->self_deaf,
  /* discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
                &p->self_mute,
  /* discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
                &p->self_stream,
  /* discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
                &p->self_video,
  /* discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
                &p->supress);
}

size_t discord_voice_state_to_json(char *json, size_t len, struct discord_voice_state *p)
{
  size_t r;
  void *arg_switches[12]={NULL};
  /* discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[0] = &p->guild_id;

  /* discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  arg_switches[1] = &p->channel_id;

  /* discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  arg_switches[2] = &p->user_id;

  /* discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
  arg_switches[3] = p->member;

  /* discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[4] = p->session_id;

  /* discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  arg_switches[5] = &p->deaf;

  /* discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  arg_switches[6] = &p->mute;

  /* discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
  arg_switches[7] = &p->self_deaf;

  /* discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
  arg_switches[8] = &p->self_mute;

  /* discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
  arg_switches[9] = &p->self_stream;

  /* discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
  arg_switches[10] = &p->self_video;

  /* discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
  arg_switches[11] = &p->supress;

  r=json_inject(json, len, 
  /* discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(guild_id):|F|,"
  /* discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(channel_id):|F|,"
  /* discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(user_id):|F|,"
  /* discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
                "(member):F,"
  /* discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
                "(session_id):s,"
  /* discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                "(deaf):b,"
  /* discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                "(mute):b,"
  /* discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
                "(self_deaf):b,"
  /* discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
                "(self_mute):b,"
  /* discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
                "(self_stream):b,"
  /* discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
                "(self_video):b,"
  /* discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
                "(supress):b,"
                "@arg_switches:b",
  /* discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->guild_id,
  /* discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_u64tostr, &p->channel_id,
  /* discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_u64tostr, &p->user_id,
  /* discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
                discord_guild_member_to_json, p->member,
  /* discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
                p->session_id,
  /* discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
                &p->deaf,
  /* discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
                &p->mute,
  /* discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
                &p->self_deaf,
  /* discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
                &p->self_mute,
  /* discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
                &p->self_stream,
  /* discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
                &p->self_video,
  /* discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
                &p->supress,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_voice_state_cleanup_v(void *p) {
  discord_voice_state_cleanup((struct discord_voice_state *)p);
}

void discord_voice_state_init_v(void *p) {
  discord_voice_state_init((struct discord_voice_state *)p);
}

void discord_voice_state_from_json_v(char *json, size_t len, void *p) {
 discord_voice_state_from_json(json, len, (struct discord_voice_state*)p);
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
  /* discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->guild_id;
  /* discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */
  (void)d->channel_id;
  /* discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  (void)d->user_id;
  /* discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */
  if (d->member) {
    discord_guild_member_cleanup(d->member);
    free(d->member);
  }
  /* discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */
  if (d->session_id)
    free(d->session_id);
  /* discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */
  (void)d->deaf;
  /* discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */
  (void)d->mute;
  /* discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */
  (void)d->self_deaf;
  /* discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */
  (void)d->self_mute;
  /* discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */
  (void)d->self_stream;
  /* discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */
  (void)d->self_video;
  /* discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */
  (void)d->supress;
}

void discord_voice_state_init(struct discord_voice_state *p) {
  memset(p, 0, sizeof(struct discord_voice_state));
  /* discord/voice.json:13:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/voice.json:14:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* discord/voice.json:15:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* discord/voice.json:16:20
     '{ "name": "member", "type":{ "base":"struct discord_guild_member", "dec":"*" }}' */

  /* discord/voice.json:17:20
     '{ "name": "session_id", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/voice.json:18:20
     '{ "name": "deaf", "type":{ "base":"bool" }}' */

  /* discord/voice.json:19:20
     '{ "name": "mute", "type":{ "base":"bool" }}' */

  /* discord/voice.json:20:20
     '{ "name": "self_deaf", "type":{ "base":"bool" }}' */

  /* discord/voice.json:21:20
     '{ "name": "self_mute", "type":{ "base":"bool" }}' */

  /* discord/voice.json:22:20
     '{ "name": "self_stream", "type":{ "base":"bool" }}' */

  /* discord/voice.json:23:20
     '{ "name": "self_video", "type":{ "base":"bool" }}' */

  /* discord/voice.json:24:20
     '{ "name": "supress", "type":{ "base":"bool" }}' */

}
void discord_voice_state_list_free(struct discord_voice_state **p) {
  ntl_free((void**)p, (void(*)(void*))discord_voice_state_cleanup);
}

void discord_voice_state_list_from_json(char *str, size_t len, struct discord_voice_state ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_voice_state);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_voice_state_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_voice_state_list_to_json(char *str, size_t len, struct discord_voice_state **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_voice_state_to_json);
}


void discord_voice_region_from_json_p(char *json, size_t len, struct discord_voice_region **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_voice_region_from_json(json, len, *pp);
}
void discord_voice_region_from_json(char *json, size_t len, struct discord_voice_region *p)
{
  discord_voice_region_init(p);
  json_extract(json, len, 
  /* discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                "(id):?s,"
  /* discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
                "(vip):b,"
  /* discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
                "(optimal):b,"
  /* discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
                "(deprecated):b,"
  /* discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
                "(custom):b,",
  /* discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                &p->id,
  /* discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
                &p->vip,
  /* discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
                &p->optimal,
  /* discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
                &p->deprecated,
  /* discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
                &p->custom);
}

size_t discord_voice_region_to_json(char *json, size_t len, struct discord_voice_region *p)
{
  size_t r;
  void *arg_switches[6]={NULL};
  /* discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->id;

  /* discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[1] = p->name;

  /* discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
  arg_switches[2] = &p->vip;

  /* discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
  arg_switches[3] = &p->optimal;

  /* discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
  arg_switches[4] = &p->deprecated;

  /* discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
  arg_switches[5] = &p->custom;

  r=json_inject(json, len, 
  /* discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                "(id):s,"
  /* discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
                "(vip):b,"
  /* discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
                "(optimal):b,"
  /* discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
                "(deprecated):b,"
  /* discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
                "(custom):b,"
                "@arg_switches:b",
  /* discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
                p->id,
  /* discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
                &p->vip,
  /* discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
                &p->optimal,
  /* discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
                &p->deprecated,
  /* discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
                &p->custom,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_voice_region_cleanup_v(void *p) {
  discord_voice_region_cleanup((struct discord_voice_region *)p);
}

void discord_voice_region_init_v(void *p) {
  discord_voice_region_init((struct discord_voice_region *)p);
}

void discord_voice_region_from_json_v(char *json, size_t len, void *p) {
 discord_voice_region_from_json(json, len, (struct discord_voice_region*)p);
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
  /* discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */
  if (d->id)
    free(d->id);
  /* discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */
  (void)d->vip;
  /* discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */
  (void)d->optimal;
  /* discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */
  (void)d->deprecated;
  /* discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */
  (void)d->custom;
}

void discord_voice_region_init(struct discord_voice_region *p) {
  memset(p, 0, sizeof(struct discord_voice_region));
  /* discord/voice.json:34:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/voice.json:35:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/voice.json:36:20
     '{ "name": "vip", "type":{ "base":"bool" }}' */

  /* discord/voice.json:37:20
     '{ "name": "optimal", "type":{ "base":"bool" }}' */

  /* discord/voice.json:38:20
     '{ "name": "deprecated", "type":{ "base":"bool" }}' */

  /* discord/voice.json:39:20
     '{ "name": "custom", "type":{ "base":"bool" }}' */

}
void discord_voice_region_list_free(struct discord_voice_region **p) {
  ntl_free((void**)p, (void(*)(void*))discord_voice_region_cleanup);
}

void discord_voice_region_list_from_json(char *str, size_t len, struct discord_voice_region ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_voice_region);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_voice_region_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_voice_region_list_to_json(char *str, size_t len, struct discord_voice_region **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_voice_region_to_json);
}

