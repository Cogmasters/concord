/* This file is generated from discord/channel.params.json, Please don't edit it. */
/**
 * @file specs-code/discord/channel.params.c
 * @see https://discord.com/developers/docs/resources/channel
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_modify_channel_params_from_json_p(char *json, size_t len, struct discord_modify_channel_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_channel_params_from_json(json, len, *pp);
}
void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params *p)
{
  discord_modify_channel_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(name):?s,"
  /* discord/channel.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(icon):?s,"
  /* discord/channel.params.json:14:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
                "(type):d,"
  /* discord/channel.params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(position):d,"
  /* discord/channel.params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(topic):?s,"
  /* discord/channel.params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(nsfw):b,"
  /* discord/channel.params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(rate_limit_per_user):d,"
  /* discord/channel.params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(bitrate):d,"
  /* discord/channel.params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(user_limit):d,"
  /* discord/channel.params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
                "(permission_overwrites):F,"
  /* discord/channel.params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
                "(parent_id):F,"
  /* discord/channel.params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(rtc_region):?s,"
  /* discord/channel.params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(video_quality_mode):d,"
  /* discord/channel.params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(archived):b,"
  /* discord/channel.params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
  /* discord/channel.params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(locked):b,",
  /* discord/channel.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->name,
  /* discord/channel.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->icon,
  /* discord/channel.params.json:14:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
                &p->type,
  /* discord/channel.params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->position,
  /* discord/channel.params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->topic,
  /* discord/channel.params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->nsfw,
  /* discord/channel.params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->rate_limit_per_user,
  /* discord/channel.params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->bitrate,
  /* discord/channel.params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->user_limit,
  /* discord/channel.params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
                discord_overwrite_list_from_json, &p->permission_overwrites,
  /* discord/channel.params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
                cee_strtou64, &p->parent_id,
  /* discord/channel.params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->rtc_region,
  /* discord/channel.params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->video_quality_mode,
  /* discord/channel.params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->archived,
  /* discord/channel.params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
  /* discord/channel.params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->locked);
}

size_t discord_modify_channel_params_to_json(char *json, size_t len, struct discord_modify_channel_params *p)
{
  size_t r;
  void *arg_switches[16]={NULL};
  /* discord/channel.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/channel.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->icon != NULL)
    arg_switches[1] = p->icon;

  /* discord/channel.params.json:14:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  arg_switches[2] = &p->type;

  /* discord/channel.params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->position != 0)
    arg_switches[3] = &p->position;

  /* discord/channel.params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->topic != NULL)
    arg_switches[4] = p->topic;

  /* discord/channel.params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  if (p->nsfw != false)
    arg_switches[5] = &p->nsfw;

  /* discord/channel.params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->rate_limit_per_user != 0)
    arg_switches[6] = &p->rate_limit_per_user;

  /* discord/channel.params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->bitrate != 0)
    arg_switches[7] = &p->bitrate;

  /* discord/channel.params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->user_limit != 0)
    arg_switches[8] = &p->user_limit;

  /* discord/channel.params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  if (p->permission_overwrites != NULL)
    arg_switches[9] = p->permission_overwrites;

  /* discord/channel.params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  if (p->parent_id != 0)
    arg_switches[10] = &p->parent_id;

  /* discord/channel.params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->rtc_region != NULL)
    arg_switches[11] = p->rtc_region;

  /* discord/channel.params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->video_quality_mode != 0)
    arg_switches[12] = &p->video_quality_mode;

  /* discord/channel.params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  if (p->archived != false)
    arg_switches[13] = &p->archived;

  /* discord/channel.params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->auto_archive_duration != 0)
    arg_switches[14] = &p->auto_archive_duration;

  /* discord/channel.params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
  if (p->locked != false)
    arg_switches[15] = &p->locked;

  r=json_inject(json, len, 
  /* discord/channel.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(name):s,"
  /* discord/channel.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(icon):s,"
  /* discord/channel.params.json:14:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
                "(type):d,"
  /* discord/channel.params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(position):d,"
  /* discord/channel.params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(topic):s,"
  /* discord/channel.params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(nsfw):b,"
  /* discord/channel.params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(rate_limit_per_user):d,"
  /* discord/channel.params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(bitrate):d,"
  /* discord/channel.params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(user_limit):d,"
  /* discord/channel.params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
                "(permission_overwrites):F,"
  /* discord/channel.params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
                "(parent_id):|F|,"
  /* discord/channel.params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(rtc_region):s,"
  /* discord/channel.params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(video_quality_mode):d,"
  /* discord/channel.params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(archived):b,"
  /* discord/channel.params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
  /* discord/channel.params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(locked):b,"
                "@arg_switches:b",
  /* discord/channel.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->name,
  /* discord/channel.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->icon,
  /* discord/channel.params.json:14:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
                &p->type,
  /* discord/channel.params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->position,
  /* discord/channel.params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->topic,
  /* discord/channel.params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->nsfw,
  /* discord/channel.params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->rate_limit_per_user,
  /* discord/channel.params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->bitrate,
  /* discord/channel.params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->user_limit,
  /* discord/channel.params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
                discord_overwrite_list_to_json, p->permission_overwrites,
  /* discord/channel.params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
                cee_u64tostr, &p->parent_id,
  /* discord/channel.params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->rtc_region,
  /* discord/channel.params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->video_quality_mode,
  /* discord/channel.params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->archived,
  /* discord/channel.params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
  /* discord/channel.params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->locked,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_modify_channel_params_cleanup_v(void *p) {
  discord_modify_channel_params_cleanup((struct discord_modify_channel_params *)p);
}

void discord_modify_channel_params_init_v(void *p) {
  discord_modify_channel_params_init((struct discord_modify_channel_params *)p);
}

void discord_modify_channel_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_channel_params_from_json(json, len, (struct discord_modify_channel_params*)p);
}

size_t discord_modify_channel_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_channel_params_to_json(json, len, (struct discord_modify_channel_params*)p);
}

void discord_modify_channel_params_list_free_v(void **p) {
  discord_modify_channel_params_list_free((struct discord_modify_channel_params**)p);
}

void discord_modify_channel_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_channel_params_list_from_json(str, len, (struct discord_modify_channel_params ***)p);
}

size_t discord_modify_channel_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_channel_params_list_to_json(str, len, (struct discord_modify_channel_params **)p);
}


void discord_modify_channel_params_cleanup(struct discord_modify_channel_params *d) {
  /* discord/channel.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->name)
    free(d->name);
  /* discord/channel.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->icon)
    free(d->icon);
  /* discord/channel.params.json:14:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  (void)d->type;
  /* discord/channel.params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  (void)d->position;
  /* discord/channel.params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->topic)
    free(d->topic);
  /* discord/channel.params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  (void)d->nsfw;
  /* discord/channel.params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  (void)d->rate_limit_per_user;
  /* discord/channel.params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  (void)d->bitrate;
  /* discord/channel.params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  (void)d->user_limit;
  /* discord/channel.params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  if (d->permission_overwrites)
    discord_overwrite_list_free(d->permission_overwrites);
  /* discord/channel.params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  (void)d->parent_id;
  /* discord/channel.params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->rtc_region)
    free(d->rtc_region);
  /* discord/channel.params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  (void)d->video_quality_mode;
  /* discord/channel.params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  (void)d->archived;
  /* discord/channel.params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  (void)d->auto_archive_duration;
  /* discord/channel.params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
  (void)d->locked;
}

void discord_modify_channel_params_init(struct discord_modify_channel_params *p) {
  memset(p, 0, sizeof(struct discord_modify_channel_params));
  /* discord/channel.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* discord/channel.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* discord/channel.params.json:14:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */

  /* discord/channel.params.json:15:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* discord/channel.params.json:16:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* discord/channel.params.json:17:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */

  /* discord/channel.params.json:18:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* discord/channel.params.json:19:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* discord/channel.params.json:20:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* discord/channel.params.json:21:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null }' */

  /* discord/channel.params.json:22:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */

  /* discord/channel.params.json:23:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* discord/channel.params.json:24:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* discord/channel.params.json:25:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */

  /* discord/channel.params.json:26:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* discord/channel.params.json:27:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */

}
void discord_modify_channel_params_list_free(struct discord_modify_channel_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_modify_channel_params_cleanup);
}

void discord_modify_channel_params_list_from_json(char *str, size_t len, struct discord_modify_channel_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_channel_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_modify_channel_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_channel_params_list_to_json(char *str, size_t len, struct discord_modify_channel_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_modify_channel_params_to_json);
}


void discord_create_message_params_from_json_p(char *json, size_t len, struct discord_create_message_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_message_params_from_json(json, len, *pp);
}
void discord_create_message_params_from_json(char *json, size_t len, struct discord_create_message_params *p)
{
  discord_create_message_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
                "(content):?s,"
  /* discord/channel.params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                "(tts):b,"
  /* discord/channel.params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/channel.params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
                "(embed):F,"
  /* discord/channel.params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* discord/channel.params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
                "(message_reference):F,"
  /* discord/channel.params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,"
  /* discord/channel.params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
                "(sticker_ids):F,"
  /* discord/channel.params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
                "(attachments):F,",
  /* discord/channel.params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
                &p->content,
  /* discord/channel.params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                &p->tts,
  /* discord/channel.params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
                discord_embed_list_from_json, &p->embeds,
  /* discord/channel.params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
                discord_embed_from_json_p, &p->embed,
  /* discord/channel.params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_from_json_p, &p->allowed_mentions,
  /* discord/channel.params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
                discord_message_reference_from_json_p, &p->message_reference,
  /* discord/channel.params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_from_json, &p->components,
  /* discord/channel.params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
                ja_u64_list_from_json, &p->sticker_ids,
  /* discord/channel.params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments);
}

size_t discord_create_message_params_to_json(char *json, size_t len, struct discord_create_message_params *p)
{
  size_t r;
  void *arg_switches[9]={NULL};
  /* discord/channel.params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  if (p->content != NULL)
    arg_switches[0] = p->content;

  /* discord/channel.params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  if (p->tts != false)
    arg_switches[1] = &p->tts;

  /* discord/channel.params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[2] = p->embeds;

  /* discord/channel.params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  if (p->embed != NULL)
    arg_switches[3] = p->embed;

  /* discord/channel.params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[4] = p->allowed_mentions;

  /* discord/channel.params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
  if (p->message_reference != NULL)
    arg_switches[5] = p->message_reference;

  /* discord/channel.params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (p->components != NULL)
    arg_switches[6] = p->components;

  /* discord/channel.params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
  if (p->sticker_ids != NULL)
    arg_switches[7] = p->sticker_ids;

  /* discord/channel.params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[8] = p->attachments;

  r=json_inject(json, len, 
  /* discord/channel.params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
                "(content):s,"
  /* discord/channel.params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                "(tts):b,"
  /* discord/channel.params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/channel.params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
                "(embed):F,"
  /* discord/channel.params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* discord/channel.params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
                "(message_reference):F,"
  /* discord/channel.params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,"
  /* discord/channel.params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
                "(sticker_ids):F,"
  /* discord/channel.params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
                "(attachments):F,"
                "@arg_switches:b",
  /* discord/channel.params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
                p->content,
  /* discord/channel.params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
                &p->tts,
  /* discord/channel.params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
                discord_embed_list_to_json, p->embeds,
  /* discord/channel.params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
                discord_embed_to_json, p->embed,
  /* discord/channel.params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* discord/channel.params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
                discord_message_reference_to_json, p->message_reference,
  /* discord/channel.params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_to_json, p->components,
  /* discord/channel.params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
                ja_u64_list_to_json, p->sticker_ids,
  /* discord/channel.params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_message_params_cleanup_v(void *p) {
  discord_create_message_params_cleanup((struct discord_create_message_params *)p);
}

void discord_create_message_params_init_v(void *p) {
  discord_create_message_params_init((struct discord_create_message_params *)p);
}

void discord_create_message_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_message_params_from_json(json, len, (struct discord_create_message_params*)p);
}

size_t discord_create_message_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_message_params_to_json(json, len, (struct discord_create_message_params*)p);
}

void discord_create_message_params_list_free_v(void **p) {
  discord_create_message_params_list_free((struct discord_create_message_params**)p);
}

void discord_create_message_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_message_params_list_from_json(str, len, (struct discord_create_message_params ***)p);
}

size_t discord_create_message_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_message_params_list_to_json(str, len, (struct discord_create_message_params **)p);
}


void discord_create_message_params_cleanup(struct discord_create_message_params *d) {
  /* discord/channel.params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* discord/channel.params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */
  (void)d->tts;
  /* discord/channel.params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* discord/channel.params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  if (d->embed) {
    discord_embed_cleanup(d->embed);
    free(d->embed);
  }
  /* discord/channel.params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* discord/channel.params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */
  if (d->message_reference) {
    discord_message_reference_cleanup(d->message_reference);
    free(d->message_reference);
  }
  /* discord/channel.params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (d->components)
    discord_component_list_free(d->components);
  /* discord/channel.params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */
  if (d->sticker_ids)
    ja_u64_list_free(d->sticker_ids);
  /* discord/channel.params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
}

void discord_create_message_params_init(struct discord_create_message_params *p) {
  memset(p, 0, sizeof(struct discord_create_message_params));
  /* discord/channel.params.json:36:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */

  /* discord/channel.params.json:37:20
     '{ "name": "tts", "type":{ "base":"bool" }, "comment":"true if this is a TTS message", "inject_if_not":false }' */

  /* discord/channel.params.json:38:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */

  /* discord/channel.params.json:39:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */

  /* discord/channel.params.json:40:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */

  /* discord/channel.params.json:41:20
     '{ "name": "message_reference", "type":{ "base":"struct discord_message_reference", "dec":"*" }, "comment":"include to make your message a reply", "inject_if_not":null }' */

  /* discord/channel.params.json:42:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */

  /* discord/channel.params.json:43:20
     '{ "name": "sticker_ids", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"ids of up to 3 stickers in the server to send in the message", "inject_if_not":null }' */

  /* discord/channel.params.json:44:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attachment objects with filename and description", "inject_if_not":null }' */

}
void discord_create_message_params_list_free(struct discord_create_message_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_message_params_cleanup);
}

void discord_create_message_params_list_from_json(char *str, size_t len, struct discord_create_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_message_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_message_params_list_to_json(char *str, size_t len, struct discord_create_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_message_params_to_json);
}


void discord_get_channel_messages_params_from_json_p(char *json, size_t len, struct discord_get_channel_messages_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_get_channel_messages_params_from_json(json, len, *pp);
}
void discord_get_channel_messages_params_from_json(char *json, size_t len, struct discord_get_channel_messages_params *p)
{
  discord_get_channel_messages_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:56:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query", "default_value":50, "comment":"max number of messages to return (1-100)", "inject_if_not":0 }' */
                "(limit):d,",
  /* discord/channel.params.json:56:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query", "default_value":50, "comment":"max number of messages to return (1-100)", "inject_if_not":0 }' */
                &p->limit);
}

size_t discord_get_channel_messages_params_to_json(char *json, size_t len, struct discord_get_channel_messages_params *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/channel.params.json:53:20
     '{ "name": "around", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages around this message ID", "inject_if_not":0 }' */
  if (p->around != 0)
    arg_switches[0] = &p->around;

  /* discord/channel.params.json:54:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages before this message ID", "inject_if_not":0 }' */
  if (p->before != 0)
    arg_switches[1] = &p->before;

  /* discord/channel.params.json:55:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages after this message ID", "inject_if_not":0 }' */
  if (p->after != 0)
    arg_switches[2] = &p->after;

  /* discord/channel.params.json:56:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query", "default_value":50, "comment":"max number of messages to return (1-100)", "inject_if_not":0 }' */
  if (p->limit != 0)
    arg_switches[3] = &p->limit;

  r=json_inject(json, len, 
                "@arg_switches:b",
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_get_channel_messages_params_cleanup_v(void *p) {
  discord_get_channel_messages_params_cleanup((struct discord_get_channel_messages_params *)p);
}

void discord_get_channel_messages_params_init_v(void *p) {
  discord_get_channel_messages_params_init((struct discord_get_channel_messages_params *)p);
}

void discord_get_channel_messages_params_from_json_v(char *json, size_t len, void *p) {
 discord_get_channel_messages_params_from_json(json, len, (struct discord_get_channel_messages_params*)p);
}

size_t discord_get_channel_messages_params_to_json_v(char *json, size_t len, void *p) {
  return discord_get_channel_messages_params_to_json(json, len, (struct discord_get_channel_messages_params*)p);
}

void discord_get_channel_messages_params_list_free_v(void **p) {
  discord_get_channel_messages_params_list_free((struct discord_get_channel_messages_params**)p);
}

void discord_get_channel_messages_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_get_channel_messages_params_list_from_json(str, len, (struct discord_get_channel_messages_params ***)p);
}

size_t discord_get_channel_messages_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_get_channel_messages_params_list_to_json(str, len, (struct discord_get_channel_messages_params **)p);
}


void discord_get_channel_messages_params_cleanup(struct discord_get_channel_messages_params *d) {
  /* discord/channel.params.json:53:20
     '{ "name": "around", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages around this message ID", "inject_if_not":0 }' */
  (void)d->around;
  /* discord/channel.params.json:54:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages before this message ID", "inject_if_not":0 }' */
  (void)d->before;
  /* discord/channel.params.json:55:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages after this message ID", "inject_if_not":0 }' */
  (void)d->after;
  /* discord/channel.params.json:56:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query", "default_value":50, "comment":"max number of messages to return (1-100)", "inject_if_not":0 }' */
  (void)d->limit;
}

void discord_get_channel_messages_params_init(struct discord_get_channel_messages_params *p) {
  memset(p, 0, sizeof(struct discord_get_channel_messages_params));
  /* discord/channel.params.json:53:20
     '{ "name": "around", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages around this message ID", "inject_if_not":0 }' */

  /* discord/channel.params.json:54:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages before this message ID", "inject_if_not":0 }' */

  /* discord/channel.params.json:55:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query", "comment":"get messages after this message ID", "inject_if_not":0 }' */

  /* discord/channel.params.json:56:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query", "default_value":50, "comment":"max number of messages to return (1-100)", "inject_if_not":0 }' */

}
void discord_get_channel_messages_params_list_free(struct discord_get_channel_messages_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_get_channel_messages_params_cleanup);
}

void discord_get_channel_messages_params_list_from_json(char *str, size_t len, struct discord_get_channel_messages_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_get_channel_messages_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_get_channel_messages_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_get_channel_messages_params_list_to_json(char *str, size_t len, struct discord_get_channel_messages_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_get_channel_messages_params_to_json);
}


void discord_get_reactions_params_from_json_p(char *json, size_t len, struct discord_get_reactions_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_get_reactions_params_from_json(json, len, *pp);
}
void discord_get_reactions_params_from_json(char *json, size_t len, struct discord_get_reactions_params *p)
{
  discord_get_reactions_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:66:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
                "(limit):d,",
  /* discord/channel.params.json:66:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
                &p->limit);
}

size_t discord_get_reactions_params_to_json(char *json, size_t len, struct discord_get_reactions_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/channel.params.json:65:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  arg_switches[0] = &p->after;

  /* discord/channel.params.json:66:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  arg_switches[1] = &p->limit;

  r=json_inject(json, len, 
                "@arg_switches:b",
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_get_reactions_params_cleanup_v(void *p) {
  discord_get_reactions_params_cleanup((struct discord_get_reactions_params *)p);
}

void discord_get_reactions_params_init_v(void *p) {
  discord_get_reactions_params_init((struct discord_get_reactions_params *)p);
}

void discord_get_reactions_params_from_json_v(char *json, size_t len, void *p) {
 discord_get_reactions_params_from_json(json, len, (struct discord_get_reactions_params*)p);
}

size_t discord_get_reactions_params_to_json_v(char *json, size_t len, void *p) {
  return discord_get_reactions_params_to_json(json, len, (struct discord_get_reactions_params*)p);
}

void discord_get_reactions_params_list_free_v(void **p) {
  discord_get_reactions_params_list_free((struct discord_get_reactions_params**)p);
}

void discord_get_reactions_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_get_reactions_params_list_from_json(str, len, (struct discord_get_reactions_params ***)p);
}

size_t discord_get_reactions_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_get_reactions_params_list_to_json(str, len, (struct discord_get_reactions_params **)p);
}


void discord_get_reactions_params_cleanup(struct discord_get_reactions_params *d) {
  /* discord/channel.params.json:65:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  (void)d->after;
  /* discord/channel.params.json:66:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  (void)d->limit;
}

void discord_get_reactions_params_init(struct discord_get_reactions_params *p) {
  memset(p, 0, sizeof(struct discord_get_reactions_params));
  /* discord/channel.params.json:65:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */

  /* discord/channel.params.json:66:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */

}
void discord_get_reactions_params_list_free(struct discord_get_reactions_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_get_reactions_params_cleanup);
}

void discord_get_reactions_params_list_from_json(char *str, size_t len, struct discord_get_reactions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_get_reactions_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_get_reactions_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_get_reactions_params_list_to_json(char *str, size_t len, struct discord_get_reactions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_get_reactions_params_to_json);
}


void discord_edit_channel_permissions_params_from_json_p(char *json, size_t len, struct discord_edit_channel_permissions_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_edit_channel_permissions_params_from_json(json, len, *pp);
}
void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p)
{
  discord_edit_channel_permissions_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
                "(allow):s_as_u64,"
  /* discord/channel.params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
                "(deny):s_as_u64,"
  /* discord/channel.params.json:77:20
     '{ "name": "type", "type":{ "base":"int", "int_alias": "enum discord_channel_types" }}' */
                "(type):d,",
  /* discord/channel.params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
                &p->allow,
  /* discord/channel.params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
                &p->deny,
  /* discord/channel.params.json:77:20
     '{ "name": "type", "type":{ "base":"int", "int_alias": "enum discord_channel_types" }}' */
                &p->type);
}

size_t discord_edit_channel_permissions_params_to_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/channel.params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
  arg_switches[0] = &p->allow;

  /* discord/channel.params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
  arg_switches[1] = &p->deny;

  /* discord/channel.params.json:77:20
     '{ "name": "type", "type":{ "base":"int", "int_alias": "enum discord_channel_types" }}' */
  arg_switches[2] = &p->type;

  r=json_inject(json, len, 
  /* discord/channel.params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
                "(allow):s_as_u64,"
  /* discord/channel.params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
                "(deny):s_as_u64,"
  /* discord/channel.params.json:77:20
     '{ "name": "type", "type":{ "base":"int", "int_alias": "enum discord_channel_types" }}' */
                "(type):d,"
                "@arg_switches:b",
  /* discord/channel.params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
                &p->allow,
  /* discord/channel.params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
                &p->deny,
  /* discord/channel.params.json:77:20
     '{ "name": "type", "type":{ "base":"int", "int_alias": "enum discord_channel_types" }}' */
                &p->type,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_edit_channel_permissions_params_cleanup_v(void *p) {
  discord_edit_channel_permissions_params_cleanup((struct discord_edit_channel_permissions_params *)p);
}

void discord_edit_channel_permissions_params_init_v(void *p) {
  discord_edit_channel_permissions_params_init((struct discord_edit_channel_permissions_params *)p);
}

void discord_edit_channel_permissions_params_from_json_v(char *json, size_t len, void *p) {
 discord_edit_channel_permissions_params_from_json(json, len, (struct discord_edit_channel_permissions_params*)p);
}

size_t discord_edit_channel_permissions_params_to_json_v(char *json, size_t len, void *p) {
  return discord_edit_channel_permissions_params_to_json(json, len, (struct discord_edit_channel_permissions_params*)p);
}

void discord_edit_channel_permissions_params_list_free_v(void **p) {
  discord_edit_channel_permissions_params_list_free((struct discord_edit_channel_permissions_params**)p);
}

void discord_edit_channel_permissions_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_edit_channel_permissions_params_list_from_json(str, len, (struct discord_edit_channel_permissions_params ***)p);
}

size_t discord_edit_channel_permissions_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_edit_channel_permissions_params_list_to_json(str, len, (struct discord_edit_channel_permissions_params **)p);
}


void discord_edit_channel_permissions_params_cleanup(struct discord_edit_channel_permissions_params *d) {
  /* discord/channel.params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
  (void)d->allow;
  /* discord/channel.params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */
  (void)d->deny;
  /* discord/channel.params.json:77:20
     '{ "name": "type", "type":{ "base":"int", "int_alias": "enum discord_channel_types" }}' */
  (void)d->type;
}

void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p) {
  memset(p, 0, sizeof(struct discord_edit_channel_permissions_params));
  /* discord/channel.params.json:75:20
     '{ "name": "allow", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */

  /* discord/channel.params.json:76:20
     '{ "name": "deny", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t"}, "comment":"permission bit set" }' */

  /* discord/channel.params.json:77:20
     '{ "name": "type", "type":{ "base":"int", "int_alias": "enum discord_channel_types" }}' */

}
void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_edit_channel_permissions_params_cleanup);
}

void discord_edit_channel_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_channel_permissions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_channel_permissions_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_edit_channel_permissions_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_channel_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_channel_permissions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_edit_channel_permissions_params_to_json);
}


void discord_edit_message_params_from_json_p(char *json, size_t len, struct discord_edit_message_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_edit_message_params_from_json(json, len, *pp);
}
void discord_edit_message_params_from_json(char *json, size_t len, struct discord_edit_message_params *p)
{
  discord_edit_message_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
                "(content):?s,"
  /* discord/channel.params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/channel.params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
                "(embed):F,"
  /* discord/channel.params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
                "(flags):d,"
  /* discord/channel.params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* discord/channel.params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* discord/channel.params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,",
  /* discord/channel.params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
                &p->content,
  /* discord/channel.params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
                discord_embed_list_from_json, &p->embeds,
  /* discord/channel.params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
                discord_embed_from_json_p, &p->embed,
  /* discord/channel.params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
                &p->flags,
  /* discord/channel.params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_from_json_p, &p->allowed_mentions,
  /* discord/channel.params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_from_json, &p->attachments,
  /* discord/channel.params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_from_json, &p->components);
}

size_t discord_edit_message_params_to_json(char *json, size_t len, struct discord_edit_message_params *p)
{
  size_t r;
  void *arg_switches[7]={NULL};
  /* discord/channel.params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  if (p->content != NULL)
    arg_switches[0] = p->content;

  /* discord/channel.params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  if (p->embeds != NULL)
    arg_switches[1] = p->embeds;

  /* discord/channel.params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  if (p->embed != NULL)
    arg_switches[2] = p->embed;

  /* discord/channel.params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
  if (p->flags != 0)
    arg_switches[3] = &p->flags;

  /* discord/channel.params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (p->allowed_mentions != NULL)
    arg_switches[4] = p->allowed_mentions;

  /* discord/channel.params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (p->attachments != NULL)
    arg_switches[5] = p->attachments;

  /* discord/channel.params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (p->components != NULL)
    arg_switches[6] = p->components;

  r=json_inject(json, len, 
  /* discord/channel.params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
                "(content):s,"
  /* discord/channel.params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
                "(embeds):F,"
  /* discord/channel.params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
                "(embed):F,"
  /* discord/channel.params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
                "(flags):d,"
  /* discord/channel.params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                "(allowed_mentions):F,"
  /* discord/channel.params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                "(attachments):F,"
  /* discord/channel.params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                "(components):F,"
                "@arg_switches:b",
  /* discord/channel.params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
                p->content,
  /* discord/channel.params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
                discord_embed_list_to_json, p->embeds,
  /* discord/channel.params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
                discord_embed_to_json, p->embed,
  /* discord/channel.params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
                &p->flags,
  /* discord/channel.params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
                discord_allowed_mentions_to_json, p->allowed_mentions,
  /* discord/channel.params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
                discord_attachment_list_to_json, p->attachments,
  /* discord/channel.params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
                discord_component_list_to_json, p->components,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_edit_message_params_cleanup_v(void *p) {
  discord_edit_message_params_cleanup((struct discord_edit_message_params *)p);
}

void discord_edit_message_params_init_v(void *p) {
  discord_edit_message_params_init((struct discord_edit_message_params *)p);
}

void discord_edit_message_params_from_json_v(char *json, size_t len, void *p) {
 discord_edit_message_params_from_json(json, len, (struct discord_edit_message_params*)p);
}

size_t discord_edit_message_params_to_json_v(char *json, size_t len, void *p) {
  return discord_edit_message_params_to_json(json, len, (struct discord_edit_message_params*)p);
}

void discord_edit_message_params_list_free_v(void **p) {
  discord_edit_message_params_list_free((struct discord_edit_message_params**)p);
}

void discord_edit_message_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_edit_message_params_list_from_json(str, len, (struct discord_edit_message_params ***)p);
}

size_t discord_edit_message_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_edit_message_params_list_to_json(str, len, (struct discord_edit_message_params **)p);
}


void discord_edit_message_params_cleanup(struct discord_edit_message_params *d) {
  /* discord/channel.params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */
  if (d->content)
    free(d->content);
  /* discord/channel.params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* discord/channel.params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */
  if (d->embed) {
    discord_embed_cleanup(d->embed);
    free(d->embed);
  }
  /* discord/channel.params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */
  (void)d->flags;
  /* discord/channel.params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */
  if (d->allowed_mentions) {
    discord_allowed_mentions_cleanup(d->allowed_mentions);
    free(d->allowed_mentions);
  }
  /* discord/channel.params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */
  if (d->attachments)
    discord_attachment_list_free(d->attachments);
  /* discord/channel.params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */
  if (d->components)
    discord_component_list_free(d->components);
}

void discord_edit_message_params_init(struct discord_edit_message_params *p) {
  memset(p, 0, sizeof(struct discord_edit_message_params));
  /* discord/channel.params.json:86:20
     '{ "name": "content", "type":{ "base":"char", "dec":"*" }, "comment":"the message contents (up to 2000 characters)", "inject_if_not":null }' */

  /* discord/channel.params.json:87:20
     '{ "name": "embeds", "type":{ "base":"struct discord_embed", "dec":"ntl" }, "comment":"embedded rich content (up to 6000 characters)", "inject_if_not":null }' */

  /* discord/channel.params.json:88:20
     '{ "name": "embed", "type":{ "base":"struct discord_embed", "dec":"*" }, "comment":"embedded rich content, deprecated in favor of embeds", "inject_if_not":null }' */

  /* discord/channel.params.json:89:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_message_flags" }, "comment":"edit the flags of a message", "inject_if_not":0 }' */

  /* discord/channel.params.json:90:20
     '{ "name": "allowed_mentions", "type":{ "base":"struct discord_allowed_mentions", "dec":"*" }, "comment":"allowed mentions for the message", "inject_if_not":null }' */

  /* discord/channel.params.json:91:20
     '{ "name": "attachments", "type":{ "base":"struct discord_attachment", "dec":"ntl" }, "comment":"attached files to keep", "inject_if_not":null }' */

  /* discord/channel.params.json:92:20
     '{ "name": "components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "comment":"the components to include with the message", "inject_if_not":null }' */

}
void discord_edit_message_params_list_free(struct discord_edit_message_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_edit_message_params_cleanup);
}

void discord_edit_message_params_list_from_json(char *str, size_t len, struct discord_edit_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_edit_message_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_message_params_list_to_json(char *str, size_t len, struct discord_edit_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_edit_message_params_to_json);
}


void discord_follow_news_channel_params_from_json_p(char *json, size_t len, struct discord_follow_news_channel_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_follow_news_channel_params_from_json(json, len, *pp);
}
void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params *p)
{
  discord_follow_news_channel_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                "(webhook_channel_id):F,",
  /* discord/channel.params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                cee_strtou64, &p->webhook_channel_id);
}

size_t discord_follow_news_channel_params_to_json(char *json, size_t len, struct discord_follow_news_channel_params *p)
{
  size_t r;
  void *arg_switches[1]={NULL};
  /* discord/channel.params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  arg_switches[0] = &p->webhook_channel_id;

  r=json_inject(json, len, 
  /* discord/channel.params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                "(webhook_channel_id):|F|,"
                "@arg_switches:b",
  /* discord/channel.params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                cee_u64tostr, &p->webhook_channel_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_follow_news_channel_params_cleanup_v(void *p) {
  discord_follow_news_channel_params_cleanup((struct discord_follow_news_channel_params *)p);
}

void discord_follow_news_channel_params_init_v(void *p) {
  discord_follow_news_channel_params_init((struct discord_follow_news_channel_params *)p);
}

void discord_follow_news_channel_params_from_json_v(char *json, size_t len, void *p) {
 discord_follow_news_channel_params_from_json(json, len, (struct discord_follow_news_channel_params*)p);
}

size_t discord_follow_news_channel_params_to_json_v(char *json, size_t len, void *p) {
  return discord_follow_news_channel_params_to_json(json, len, (struct discord_follow_news_channel_params*)p);
}

void discord_follow_news_channel_params_list_free_v(void **p) {
  discord_follow_news_channel_params_list_free((struct discord_follow_news_channel_params**)p);
}

void discord_follow_news_channel_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_follow_news_channel_params_list_from_json(str, len, (struct discord_follow_news_channel_params ***)p);
}

size_t discord_follow_news_channel_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_follow_news_channel_params_list_to_json(str, len, (struct discord_follow_news_channel_params **)p);
}


void discord_follow_news_channel_params_cleanup(struct discord_follow_news_channel_params *d) {
  /* discord/channel.params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  (void)d->webhook_channel_id;
}

void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p) {
  memset(p, 0, sizeof(struct discord_follow_news_channel_params));
  /* discord/channel.params.json:101:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */

}
void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_follow_news_channel_params_cleanup);
}

void discord_follow_news_channel_params_list_from_json(char *str, size_t len, struct discord_follow_news_channel_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_follow_news_channel_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_follow_news_channel_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_follow_news_channel_params_list_to_json(char *str, size_t len, struct discord_follow_news_channel_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_follow_news_channel_params_to_json);
}


void discord_create_channel_invite_params_from_json_p(char *json, size_t len, struct discord_create_channel_invite_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_channel_invite_params_from_json(json, len, *pp);
}
void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params *p)
{
  discord_create_channel_invite_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                "(max_age):d,"
  /* discord/channel.params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                "(max_uses):d,"
  /* discord/channel.params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
                "(temporary):b,"
  /* discord/channel.params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
                "(unique):b,"
  /* discord/channel.params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
                "(target_type):d,"
  /* discord/channel.params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                "(target_user_id):F,"
  /* discord/channel.params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                "(target_application_id):F,",
  /* discord/channel.params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                &p->max_age,
  /* discord/channel.params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                &p->max_uses,
  /* discord/channel.params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
                &p->temporary,
  /* discord/channel.params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
                &p->unique,
  /* discord/channel.params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
                &p->target_type,
  /* discord/channel.params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                cee_strtou64, &p->target_user_id,
  /* discord/channel.params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                cee_strtou64, &p->target_application_id);
}

size_t discord_create_channel_invite_params_to_json(char *json, size_t len, struct discord_create_channel_invite_params *p)
{
  size_t r;
  void *arg_switches[7]={NULL};
  /* discord/channel.params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  arg_switches[0] = &p->max_age;

  /* discord/channel.params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  arg_switches[1] = &p->max_uses;

  /* discord/channel.params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  arg_switches[2] = &p->temporary;

  /* discord/channel.params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  arg_switches[3] = &p->unique;

  /* discord/channel.params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  if (p->target_type != 0)
    arg_switches[4] = &p->target_type;

  /* discord/channel.params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  if (p->target_user_id != 0)
    arg_switches[5] = &p->target_user_id;

  /* discord/channel.params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  if (p->target_application_id != 0)
    arg_switches[6] = &p->target_application_id;

  r=json_inject(json, len, 
  /* discord/channel.params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                "(max_age):d,"
  /* discord/channel.params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                "(max_uses):d,"
  /* discord/channel.params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
                "(temporary):b,"
  /* discord/channel.params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
                "(unique):b,"
  /* discord/channel.params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
                "(target_type):d,"
  /* discord/channel.params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                "(target_user_id):|F|,"
  /* discord/channel.params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                "(target_application_id):|F|,"
                "@arg_switches:b",
  /* discord/channel.params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                &p->max_age,
  /* discord/channel.params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                &p->max_uses,
  /* discord/channel.params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
                &p->temporary,
  /* discord/channel.params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
                &p->unique,
  /* discord/channel.params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
                &p->target_type,
  /* discord/channel.params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                cee_u64tostr, &p->target_user_id,
  /* discord/channel.params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                cee_u64tostr, &p->target_application_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_channel_invite_params_cleanup_v(void *p) {
  discord_create_channel_invite_params_cleanup((struct discord_create_channel_invite_params *)p);
}

void discord_create_channel_invite_params_init_v(void *p) {
  discord_create_channel_invite_params_init((struct discord_create_channel_invite_params *)p);
}

void discord_create_channel_invite_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_channel_invite_params_from_json(json, len, (struct discord_create_channel_invite_params*)p);
}

size_t discord_create_channel_invite_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_channel_invite_params_to_json(json, len, (struct discord_create_channel_invite_params*)p);
}

void discord_create_channel_invite_params_list_free_v(void **p) {
  discord_create_channel_invite_params_list_free((struct discord_create_channel_invite_params**)p);
}

void discord_create_channel_invite_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_channel_invite_params_list_from_json(str, len, (struct discord_create_channel_invite_params ***)p);
}

size_t discord_create_channel_invite_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_channel_invite_params_list_to_json(str, len, (struct discord_create_channel_invite_params **)p);
}


void discord_create_channel_invite_params_cleanup(struct discord_create_channel_invite_params *d) {
  /* discord/channel.params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  (void)d->max_age;
  /* discord/channel.params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  (void)d->max_uses;
  /* discord/channel.params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  (void)d->temporary;
  /* discord/channel.params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  (void)d->unique;
  /* discord/channel.params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  (void)d->target_type;
  /* discord/channel.params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  (void)d->target_user_id;
  /* discord/channel.params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  (void)d->target_application_id;
}

void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p) {
  memset(p, 0, sizeof(struct discord_create_channel_invite_params));
  /* discord/channel.params.json:110:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */

  /* discord/channel.params.json:111:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */

  /* discord/channel.params.json:112:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */

  /* discord/channel.params.json:113:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */

  /* discord/channel.params.json:114:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */

  /* discord/channel.params.json:115:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */

  /* discord/channel.params.json:116:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */

}
void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_channel_invite_params_cleanup);
}

void discord_create_channel_invite_params_list_from_json(char *str, size_t len, struct discord_create_channel_invite_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_channel_invite_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_channel_invite_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_channel_invite_params_list_to_json(char *str, size_t len, struct discord_create_channel_invite_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_channel_invite_params_to_json);
}


void discord_group_dm_add_recipient_params_from_json_p(char *json, size_t len, struct discord_group_dm_add_recipient_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_group_dm_add_recipient_params_from_json(json, len, *pp);
}
void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p)
{
  discord_group_dm_add_recipient_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
                "(access_token):?s,"
  /* discord/channel.params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):?s,",
  /* discord/channel.params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
                &p->access_token,
  /* discord/channel.params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                &p->nick);
}

size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/channel.params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->access_token;

  /* discord/channel.params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[1] = p->nick;

  r=json_inject(json, len, 
  /* discord/channel.params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
                "(access_token):s,"
  /* discord/channel.params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):s,"
                "@arg_switches:b",
  /* discord/channel.params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
                p->access_token,
  /* discord/channel.params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                p->nick,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_group_dm_add_recipient_params_cleanup_v(void *p) {
  discord_group_dm_add_recipient_params_cleanup((struct discord_group_dm_add_recipient_params *)p);
}

void discord_group_dm_add_recipient_params_init_v(void *p) {
  discord_group_dm_add_recipient_params_init((struct discord_group_dm_add_recipient_params *)p);
}

void discord_group_dm_add_recipient_params_from_json_v(char *json, size_t len, void *p) {
 discord_group_dm_add_recipient_params_from_json(json, len, (struct discord_group_dm_add_recipient_params*)p);
}

size_t discord_group_dm_add_recipient_params_to_json_v(char *json, size_t len, void *p) {
  return discord_group_dm_add_recipient_params_to_json(json, len, (struct discord_group_dm_add_recipient_params*)p);
}

void discord_group_dm_add_recipient_params_list_free_v(void **p) {
  discord_group_dm_add_recipient_params_list_free((struct discord_group_dm_add_recipient_params**)p);
}

void discord_group_dm_add_recipient_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_group_dm_add_recipient_params_list_from_json(str, len, (struct discord_group_dm_add_recipient_params ***)p);
}

size_t discord_group_dm_add_recipient_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_group_dm_add_recipient_params_list_to_json(str, len, (struct discord_group_dm_add_recipient_params **)p);
}


void discord_group_dm_add_recipient_params_cleanup(struct discord_group_dm_add_recipient_params *d) {
  /* discord/channel.params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  if (d->access_token)
    free(d->access_token);
  /* discord/channel.params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  if (d->nick)
    free(d->nick);
}

void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p) {
  memset(p, 0, sizeof(struct discord_group_dm_add_recipient_params));
  /* discord/channel.params.json:125:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/channel.params.json:126:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */

}
void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_group_dm_add_recipient_params_cleanup);
}

void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_group_dm_add_recipient_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_group_dm_add_recipient_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_group_dm_add_recipient_params_to_json);
}


void discord_start_thread_with_message_params_from_json_p(char *json, size_t len, struct discord_start_thread_with_message_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_start_thread_with_message_params_from_json(json, len, *pp);
}
void discord_start_thread_with_message_params_from_json(char *json, size_t len, struct discord_start_thread_with_message_params *p)
{
  discord_start_thread_with_message_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(name):?s,"
  /* discord/channel.params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,",
  /* discord/channel.params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->name,
  /* discord/channel.params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration);
}

size_t discord_start_thread_with_message_params_to_json(char *json, size_t len, struct discord_start_thread_with_message_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/channel.params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/channel.params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->auto_archive_duration != 0)
    arg_switches[1] = &p->auto_archive_duration;

  r=json_inject(json, len, 
  /* discord/channel.params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(name):s,"
  /* discord/channel.params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
                "@arg_switches:b",
  /* discord/channel.params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->name,
  /* discord/channel.params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_start_thread_with_message_params_cleanup_v(void *p) {
  discord_start_thread_with_message_params_cleanup((struct discord_start_thread_with_message_params *)p);
}

void discord_start_thread_with_message_params_init_v(void *p) {
  discord_start_thread_with_message_params_init((struct discord_start_thread_with_message_params *)p);
}

void discord_start_thread_with_message_params_from_json_v(char *json, size_t len, void *p) {
 discord_start_thread_with_message_params_from_json(json, len, (struct discord_start_thread_with_message_params*)p);
}

size_t discord_start_thread_with_message_params_to_json_v(char *json, size_t len, void *p) {
  return discord_start_thread_with_message_params_to_json(json, len, (struct discord_start_thread_with_message_params*)p);
}

void discord_start_thread_with_message_params_list_free_v(void **p) {
  discord_start_thread_with_message_params_list_free((struct discord_start_thread_with_message_params**)p);
}

void discord_start_thread_with_message_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_start_thread_with_message_params_list_from_json(str, len, (struct discord_start_thread_with_message_params ***)p);
}

size_t discord_start_thread_with_message_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_start_thread_with_message_params_list_to_json(str, len, (struct discord_start_thread_with_message_params **)p);
}


void discord_start_thread_with_message_params_cleanup(struct discord_start_thread_with_message_params *d) {
  /* discord/channel.params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->name)
    free(d->name);
  /* discord/channel.params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  (void)d->auto_archive_duration;
}

void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *p) {
  memset(p, 0, sizeof(struct discord_start_thread_with_message_params));
  /* discord/channel.params.json:135:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* discord/channel.params.json:136:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */

}
void discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_start_thread_with_message_params_cleanup);
}

void discord_start_thread_with_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_with_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_start_thread_with_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_start_thread_with_message_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_start_thread_with_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_with_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_start_thread_with_message_params_to_json);
}


void discord_start_thread_without_message_params_from_json_p(char *json, size_t len, struct discord_start_thread_without_message_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_start_thread_without_message_params_from_json(json, len, *pp);
}
void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params *p)
{
  discord_start_thread_without_message_params_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
                "(name):?s,"
  /* discord/channel.params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
  /* discord/channel.params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
                "(type):d,",
  /* discord/channel.params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
                &p->name,
  /* discord/channel.params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
  /* discord/channel.params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
                &p->type);
}

size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/channel.params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  arg_switches[0] = p->name;

  /* discord/channel.params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->auto_archive_duration != 0)
    arg_switches[1] = &p->auto_archive_duration;

  /* discord/channel.params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  arg_switches[2] = &p->type;

  r=json_inject(json, len, 
  /* discord/channel.params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
                "(name):s,"
  /* discord/channel.params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
  /* discord/channel.params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
                "(type):d,"
                "@arg_switches:b",
  /* discord/channel.params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
                p->name,
  /* discord/channel.params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
  /* discord/channel.params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
                &p->type,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_start_thread_without_message_params_cleanup_v(void *p) {
  discord_start_thread_without_message_params_cleanup((struct discord_start_thread_without_message_params *)p);
}

void discord_start_thread_without_message_params_init_v(void *p) {
  discord_start_thread_without_message_params_init((struct discord_start_thread_without_message_params *)p);
}

void discord_start_thread_without_message_params_from_json_v(char *json, size_t len, void *p) {
 discord_start_thread_without_message_params_from_json(json, len, (struct discord_start_thread_without_message_params*)p);
}

size_t discord_start_thread_without_message_params_to_json_v(char *json, size_t len, void *p) {
  return discord_start_thread_without_message_params_to_json(json, len, (struct discord_start_thread_without_message_params*)p);
}

void discord_start_thread_without_message_params_list_free_v(void **p) {
  discord_start_thread_without_message_params_list_free((struct discord_start_thread_without_message_params**)p);
}

void discord_start_thread_without_message_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_start_thread_without_message_params_list_from_json(str, len, (struct discord_start_thread_without_message_params ***)p);
}

size_t discord_start_thread_without_message_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_start_thread_without_message_params_list_to_json(str, len, (struct discord_start_thread_without_message_params **)p);
}


void discord_start_thread_without_message_params_cleanup(struct discord_start_thread_without_message_params *d) {
  /* discord/channel.params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  if (d->name)
    free(d->name);
  /* discord/channel.params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  (void)d->auto_archive_duration;
  /* discord/channel.params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */
  (void)d->type;
}

void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *p) {
  memset(p, 0, sizeof(struct discord_start_thread_without_message_params));
  /* discord/channel.params.json:145:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */

  /* discord/channel.params.json:146:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* discord/channel.params.json:147:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_channel_types" } }' */

}
void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_start_thread_without_message_params_cleanup);
}

void discord_start_thread_without_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_without_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_start_thread_without_message_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_start_thread_without_message_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_start_thread_without_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_without_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_start_thread_without_message_params_to_json);
}


void discord_thread_response_body_from_json_p(char *json, size_t len, struct discord_thread_response_body **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_thread_response_body_from_json(json, len, *pp);
}
void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body *p)
{
  discord_thread_response_body_init(p);
  json_extract(json, len, 
  /* discord/channel.params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
                "(threads):F,"
  /* discord/channel.params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
                "(members):F,"
  /* discord/channel.params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
                "(has_more):b,",
  /* discord/channel.params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
                discord_channel_list_from_json, &p->threads,
  /* discord/channel.params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
                discord_thread_member_list_from_json, &p->members,
  /* discord/channel.params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
                &p->has_more);
}

size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/channel.params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  arg_switches[0] = p->threads;

  /* discord/channel.params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  arg_switches[1] = p->members;

  /* discord/channel.params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  arg_switches[2] = &p->has_more;

  r=json_inject(json, len, 
  /* discord/channel.params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
                "(threads):F,"
  /* discord/channel.params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
                "(members):F,"
  /* discord/channel.params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
                "(has_more):b,"
                "@arg_switches:b",
  /* discord/channel.params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
                discord_channel_list_to_json, p->threads,
  /* discord/channel.params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
                discord_thread_member_list_to_json, p->members,
  /* discord/channel.params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
                &p->has_more,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_thread_response_body_cleanup_v(void *p) {
  discord_thread_response_body_cleanup((struct discord_thread_response_body *)p);
}

void discord_thread_response_body_init_v(void *p) {
  discord_thread_response_body_init((struct discord_thread_response_body *)p);
}

void discord_thread_response_body_from_json_v(char *json, size_t len, void *p) {
 discord_thread_response_body_from_json(json, len, (struct discord_thread_response_body*)p);
}

size_t discord_thread_response_body_to_json_v(char *json, size_t len, void *p) {
  return discord_thread_response_body_to_json(json, len, (struct discord_thread_response_body*)p);
}

void discord_thread_response_body_list_free_v(void **p) {
  discord_thread_response_body_list_free((struct discord_thread_response_body**)p);
}

void discord_thread_response_body_list_from_json_v(char *str, size_t len, void *p) {
  discord_thread_response_body_list_from_json(str, len, (struct discord_thread_response_body ***)p);
}

size_t discord_thread_response_body_list_to_json_v(char *str, size_t len, void *p){
  return discord_thread_response_body_list_to_json(str, len, (struct discord_thread_response_body **)p);
}


void discord_thread_response_body_cleanup(struct discord_thread_response_body *d) {
  /* discord/channel.params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  if (d->threads)
    discord_channel_list_free(d->threads);
  /* discord/channel.params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  if (d->members)
    discord_thread_member_list_free(d->members);
  /* discord/channel.params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  (void)d->has_more;
}

void discord_thread_response_body_init(struct discord_thread_response_body *p) {
  memset(p, 0, sizeof(struct discord_thread_response_body));
  /* discord/channel.params.json:156:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */

  /* discord/channel.params.json:157:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */

  /* discord/channel.params.json:158:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */

}
void discord_thread_response_body_list_free(struct discord_thread_response_body **p) {
  ntl_free((void**)p, (void(*)(void*))discord_thread_response_body_cleanup);
}

void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_response_body);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_thread_response_body_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_thread_response_body_to_json);
}

