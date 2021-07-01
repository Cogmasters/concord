/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/channel.endpoints-params.c
 * @author cee-studio
 * @date 30 Jun 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */

#include "specs.h"

void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(name):?s,"
  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(icon):?s,"
  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(position):d,"
  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(topic):?s,"
  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(nsfw):b,"
  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(rate_limit_per_user):d,"
  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(bitrate):d,"
  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(user_limit):d,"
  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
                "(permission_overwrites):F,"
  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
                "(parent_id):F,"
  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(rtc_region):?s,"
  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(video_quality_mode):d,"
  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(archived):b,"
  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(locked):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->name,
  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->icon,
  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->position,
  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->topic,
  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->nsfw,
  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->rate_limit_per_user,
  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->bitrate,
  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->user_limit,
  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
                discord_channel_overwrite_list_from_json, &p->permission_overwrites,
  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
                cee_strtoull, &p->parent_id,
  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->rtc_region,
  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->video_quality_mode,
  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->archived,
  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->locked,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_channel_params_use_default_inject_settings(struct discord_modify_channel_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->icon != NULL)
    p->__M.arg_switches[1] = p->icon;

  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  p->__M.arg_switches[2] = &p->type;

  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->position != 0)
    p->__M.arg_switches[3] = &p->position;

  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->topic != NULL)
    p->__M.arg_switches[4] = p->topic;

  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  if (p->nsfw != false)
    p->__M.arg_switches[5] = &p->nsfw;

  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->rate_limit_per_user != 0)
    p->__M.arg_switches[6] = &p->rate_limit_per_user;

  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->bitrate != 0)
    p->__M.arg_switches[7] = &p->bitrate;

  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->user_limit != 0)
    p->__M.arg_switches[8] = &p->user_limit;

  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  if (p->permission_overwrites != NULL)
    p->__M.arg_switches[9] = p->permission_overwrites;

  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  if (p->parent_id != 0)
    p->__M.arg_switches[10] = &p->parent_id;

  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->rtc_region != NULL)
    p->__M.arg_switches[11] = p->rtc_region;

  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->video_quality_mode != 0)
    p->__M.arg_switches[12] = &p->video_quality_mode;

  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  if (p->archived != false)
    p->__M.arg_switches[13] = &p->archived;

  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->auto_archive_duration != 0)
    p->__M.arg_switches[14] = &p->auto_archive_duration;

  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
  if (p->locked != false)
    p->__M.arg_switches[15] = &p->locked;

}

size_t discord_modify_channel_params_to_json(char *json, size_t len, struct discord_modify_channel_params *p)
{
  size_t r;
  discord_modify_channel_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(name):s,"
  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(icon):s,"
  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(position):d,"
  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(topic):s,"
  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(nsfw):b,"
  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(rate_limit_per_user):d,"
  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(bitrate):d,"
  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(user_limit):d,"
  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
                "(permission_overwrites):F,"
  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
                "(parent_id):|F|,"
  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(rtc_region):s,"
  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(video_quality_mode):d,"
  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(archived):b,"
  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
                "(locked):b,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->name,
  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->icon,
  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->position,
  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->topic,
  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->nsfw,
  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->rate_limit_per_user,
  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->bitrate,
  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->user_limit,
  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
                discord_channel_overwrite_list_to_json, p->permission_overwrites,
  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
                cee_ulltostr, &p->parent_id,
  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->rtc_region,
  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->video_quality_mode,
  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->archived,
  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
                &p->locked,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_channel_params_cleanup_v(void *p) {
  discord_modify_channel_params_cleanup((struct discord_modify_channel_params *)p);
}

void discord_modify_channel_params_init_v(void *p) {
  discord_modify_channel_params_init((struct discord_modify_channel_params *)p);
}

void discord_modify_channel_params_free_v(void *p) {
 discord_modify_channel_params_free((struct discord_modify_channel_params *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->name)
    free(d->name);
  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->icon)
    free(d->icon);
  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  // p->type is a scalar
  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */
  // p->position is a scalar
  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->topic)
    free(d->topic);
  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */
  // p->nsfw is a scalar
  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */
  // p->rate_limit_per_user is a scalar
  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */
  // p->bitrate is a scalar
  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */
  // p->user_limit is a scalar
  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */
  if (d->permission_overwrites)
    discord_channel_overwrite_list_free(d->permission_overwrites);
  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */
  // p->parent_id is a scalar
  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->rtc_region)
    free(d->rtc_region);
  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */
  // p->video_quality_mode is a scalar
  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */
  // p->archived is a scalar
  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  // p->auto_archive_duration is a scalar
  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */
  // p->locked is a scalar
}

void discord_modify_channel_params_init(struct discord_modify_channel_params *p) {
  memset(p, 0, sizeof(struct discord_modify_channel_params));
  /* specs/discord/channel.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* specs/discord/channel.endpoints-params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* specs/discord/channel.endpoints-params.json:15:20
     '{ "name": "type", "type":{ "base":"int" }}' */

  /* specs/discord/channel.endpoints-params.json:16:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:17:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* specs/discord/channel.endpoints-params.json:18:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false }' */

  /* specs/discord/channel.endpoints-params.json:19:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:20:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:21:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:22:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null }' */

  /* specs/discord/channel.endpoints-params.json:23:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:24:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* specs/discord/channel.endpoints-params.json:25:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:26:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }' */

  /* specs/discord/channel.endpoints-params.json:27:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:28:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false }' */

}
struct discord_modify_channel_params* discord_modify_channel_params_alloc() {
  struct discord_modify_channel_params *p= malloc(sizeof(struct discord_modify_channel_params));
  discord_modify_channel_params_init(p);
  return p;
}

void discord_modify_channel_params_free(struct discord_modify_channel_params *p) {
  discord_modify_channel_params_cleanup(p);
  free(p);
}

void discord_modify_channel_params_list_free(struct discord_modify_channel_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_channel_params_cleanup);
}

void discord_modify_channel_params_list_from_json(char *str, size_t len, struct discord_modify_channel_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_channel_params);
  d.init_elem = discord_modify_channel_params_init_v;
  d.elem_from_buf = discord_modify_channel_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_modify_channel_params_list_to_json(char *str, size_t len, struct discord_modify_channel_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_channel_params_to_json_v);
}


void discord_get_reactions_params_from_json(char *json, size_t len, struct discord_get_reactions_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
                "(after):F,"
  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
                "(limit):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
                cee_strtoull, &p->after,
  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_get_reactions_params_use_default_inject_settings(struct discord_get_reactions_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  p->__M.arg_switches[0] = &p->after;

  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  p->__M.arg_switches[1] = &p->limit;

}

size_t discord_get_reactions_params_to_json(char *json, size_t len, struct discord_get_reactions_params *p)
{
  size_t r;
  discord_get_reactions_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
                "(after):|F|,"
  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
                "(limit):d,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
                cee_ulltostr, &p->after,
  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_get_reactions_params_cleanup_v(void *p) {
  discord_get_reactions_params_cleanup((struct discord_get_reactions_params *)p);
}

void discord_get_reactions_params_init_v(void *p) {
  discord_get_reactions_params_init((struct discord_get_reactions_params *)p);
}

void discord_get_reactions_params_free_v(void *p) {
 discord_get_reactions_params_free((struct discord_get_reactions_params *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */
  // p->after is a scalar
  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */
  // p->limit is a scalar
}

void discord_get_reactions_params_init(struct discord_get_reactions_params *p) {
  memset(p, 0, sizeof(struct discord_get_reactions_params));
  /* specs/discord/channel.endpoints-params.json:38:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "loc":"query"}' */

  /* specs/discord/channel.endpoints-params.json:39:20
     '{ "name": "limit", "type":{ "base":"int" }, "loc":"query"}' */

}
struct discord_get_reactions_params* discord_get_reactions_params_alloc() {
  struct discord_get_reactions_params *p= malloc(sizeof(struct discord_get_reactions_params));
  discord_get_reactions_params_init(p);
  return p;
}

void discord_get_reactions_params_free(struct discord_get_reactions_params *p) {
  discord_get_reactions_params_cleanup(p);
  free(p);
}

void discord_get_reactions_params_list_free(struct discord_get_reactions_params **p) {
  ntl_free((void**)p, (vfvp)discord_get_reactions_params_cleanup);
}

void discord_get_reactions_params_list_from_json(char *str, size_t len, struct discord_get_reactions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_get_reactions_params);
  d.init_elem = discord_get_reactions_params_init_v;
  d.elem_from_buf = discord_get_reactions_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_get_reactions_params_list_to_json(char *str, size_t len, struct discord_get_reactions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_get_reactions_params_to_json_v);
}


void discord_edit_channel_permissions_params_from_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
                "(allow):s_as_hex_uint,"
  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
                "(deny):s_as_hex_uint,"
  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
                &p->allow,
  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
                &p->deny,
  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_edit_channel_permissions_params_use_default_inject_settings(struct discord_edit_channel_permissions_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
  p->__M.arg_switches[0] = &p->allow;

  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
  p->__M.arg_switches[1] = &p->deny;

  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  p->__M.arg_switches[2] = &p->type;

}

size_t discord_edit_channel_permissions_params_to_json(char *json, size_t len, struct discord_edit_channel_permissions_params *p)
{
  size_t r;
  discord_edit_channel_permissions_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
                "(allow):s_as_hex_uint,"
  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
                "(deny):s_as_hex_uint,"
  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
                &p->allow,
  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
                &p->deny,
  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_edit_channel_permissions_params_cleanup_v(void *p) {
  discord_edit_channel_permissions_params_cleanup((struct discord_edit_channel_permissions_params *)p);
}

void discord_edit_channel_permissions_params_init_v(void *p) {
  discord_edit_channel_permissions_params_init((struct discord_edit_channel_permissions_params *)p);
}

void discord_edit_channel_permissions_params_free_v(void *p) {
 discord_edit_channel_permissions_params_free((struct discord_edit_channel_permissions_params *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
  // p->allow is a scalar
  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */
  // p->deny is a scalar
  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  // p->type is a scalar
}

void discord_edit_channel_permissions_params_init(struct discord_edit_channel_permissions_params *p) {
  memset(p, 0, sizeof(struct discord_edit_channel_permissions_params));
  /* specs/discord/channel.endpoints-params.json:49:20
     '{ "name": "allow", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */

  /* specs/discord/channel.endpoints-params.json:50:20
     '{ "name": "deny", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags"}, "comment":"permission bit set" }' */

  /* specs/discord/channel.endpoints-params.json:51:20
     '{ "name": "type", "type":{ "base":"int" }}' */

}
struct discord_edit_channel_permissions_params* discord_edit_channel_permissions_params_alloc() {
  struct discord_edit_channel_permissions_params *p= malloc(sizeof(struct discord_edit_channel_permissions_params));
  discord_edit_channel_permissions_params_init(p);
  return p;
}

void discord_edit_channel_permissions_params_free(struct discord_edit_channel_permissions_params *p) {
  discord_edit_channel_permissions_params_cleanup(p);
  free(p);
}

void discord_edit_channel_permissions_params_list_free(struct discord_edit_channel_permissions_params **p) {
  ntl_free((void**)p, (vfvp)discord_edit_channel_permissions_params_cleanup);
}

void discord_edit_channel_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_channel_permissions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_channel_permissions_params);
  d.init_elem = discord_edit_channel_permissions_params_init_v;
  d.elem_from_buf = discord_edit_channel_permissions_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_edit_channel_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_channel_permissions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_edit_channel_permissions_params_to_json_v);
}


void discord_follow_news_channel_params_from_json(char *json, size_t len, struct discord_follow_news_channel_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                "(webhook_channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                cee_strtoull, &p->webhook_channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_follow_news_channel_params_use_default_inject_settings(struct discord_follow_news_channel_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  p->__M.arg_switches[0] = &p->webhook_channel_id;

}

size_t discord_follow_news_channel_params_to_json(char *json, size_t len, struct discord_follow_news_channel_params *p)
{
  size_t r;
  discord_follow_news_channel_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                "(webhook_channel_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
                cee_ulltostr, &p->webhook_channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_follow_news_channel_params_cleanup_v(void *p) {
  discord_follow_news_channel_params_cleanup((struct discord_follow_news_channel_params *)p);
}

void discord_follow_news_channel_params_init_v(void *p) {
  discord_follow_news_channel_params_init((struct discord_follow_news_channel_params *)p);
}

void discord_follow_news_channel_params_free_v(void *p) {
 discord_follow_news_channel_params_free((struct discord_follow_news_channel_params *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */
  // p->webhook_channel_id is a scalar
}

void discord_follow_news_channel_params_init(struct discord_follow_news_channel_params *p) {
  memset(p, 0, sizeof(struct discord_follow_news_channel_params));
  /* specs/discord/channel.endpoints-params.json:61:20
     '{ "name": "webhook_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"} }' */

}
struct discord_follow_news_channel_params* discord_follow_news_channel_params_alloc() {
  struct discord_follow_news_channel_params *p= malloc(sizeof(struct discord_follow_news_channel_params));
  discord_follow_news_channel_params_init(p);
  return p;
}

void discord_follow_news_channel_params_free(struct discord_follow_news_channel_params *p) {
  discord_follow_news_channel_params_cleanup(p);
  free(p);
}

void discord_follow_news_channel_params_list_free(struct discord_follow_news_channel_params **p) {
  ntl_free((void**)p, (vfvp)discord_follow_news_channel_params_cleanup);
}

void discord_follow_news_channel_params_list_from_json(char *str, size_t len, struct discord_follow_news_channel_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_follow_news_channel_params);
  d.init_elem = discord_follow_news_channel_params_init_v;
  d.elem_from_buf = discord_follow_news_channel_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_follow_news_channel_params_list_to_json(char *str, size_t len, struct discord_follow_news_channel_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_follow_news_channel_params_to_json_v);
}


void discord_create_channel_invite_params_from_json(char *json, size_t len, struct discord_create_channel_invite_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                "(max_age):d,"
  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                "(max_uses):d,"
  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
                "(temporary):b,"
  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
                "(unique):b,"
  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
                "(target_type):d,"
  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                "(target_user_id):F,"
  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                "(target_application_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                &p->max_age,
  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                &p->max_uses,
  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
                &p->temporary,
  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
                &p->unique,
  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
                &p->target_type,
  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                cee_strtoull, &p->target_user_id,
  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                cee_strtoull, &p->target_application_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_create_channel_invite_params_use_default_inject_settings(struct discord_create_channel_invite_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  p->__M.arg_switches[0] = &p->max_age;

  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  p->__M.arg_switches[1] = &p->max_uses;

  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[2] = &p->temporary;

  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[3] = &p->unique;

  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  if (p->target_type != 0)
    p->__M.arg_switches[4] = &p->target_type;

  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  if (p->target_user_id != 0)
    p->__M.arg_switches[5] = &p->target_user_id;

  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  if (p->target_application_id != 0)
    p->__M.arg_switches[6] = &p->target_application_id;

}

size_t discord_create_channel_invite_params_to_json(char *json, size_t len, struct discord_create_channel_invite_params *p)
{
  size_t r;
  discord_create_channel_invite_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                "(max_age):d,"
  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                "(max_uses):d,"
  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
                "(temporary):b,"
  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
                "(unique):b,"
  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
                "(target_type):d,"
  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                "(target_user_id):|F|,"
  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                "(target_application_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
                &p->max_age,
  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
                &p->max_uses,
  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
                &p->temporary,
  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
                &p->unique,
  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
                &p->target_type,
  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                cee_ulltostr, &p->target_user_id,
  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
                cee_ulltostr, &p->target_application_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_channel_invite_params_cleanup_v(void *p) {
  discord_create_channel_invite_params_cleanup((struct discord_create_channel_invite_params *)p);
}

void discord_create_channel_invite_params_init_v(void *p) {
  discord_create_channel_invite_params_init((struct discord_create_channel_invite_params *)p);
}

void discord_create_channel_invite_params_free_v(void *p) {
 discord_create_channel_invite_params_free((struct discord_create_channel_invite_params *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */
  // p->max_age is a scalar
  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */
  // p->max_uses is a scalar
  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */
  // p->temporary is a scalar
  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */
  // p->unique is a scalar
  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */
  // p->target_type is a scalar
  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  // p->target_user_id is a scalar
  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */
  // p->target_application_id is a scalar
}

void discord_create_channel_invite_params_init(struct discord_create_channel_invite_params *p) {
  memset(p, 0, sizeof(struct discord_create_channel_invite_params));
  /* specs/discord/channel.endpoints-params.json:71:20
     '{ "name": "max_age", "type":{ "base":"int" }}' */

  /* specs/discord/channel.endpoints-params.json:72:20
     '{ "name": "max_uses", "type":{ "base":"int" }}' */

  /* specs/discord/channel.endpoints-params.json:73:20
     '{ "name": "temporary", "type":{ "base":"bool" }}' */

  /* specs/discord/channel.endpoints-params.json:74:20
     '{ "name": "unique", "type":{ "base":"bool" }}' */

  /* specs/discord/channel.endpoints-params.json:75:20
     '{ "name": "target_type", "type":{ "base":"int" }, "option":true, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:76:20
     '{ "name": "target_user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */

  /* specs/discord/channel.endpoints-params.json:77:20
     '{ "name": "target_application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "inject_if_not":0 }' */

}
struct discord_create_channel_invite_params* discord_create_channel_invite_params_alloc() {
  struct discord_create_channel_invite_params *p= malloc(sizeof(struct discord_create_channel_invite_params));
  discord_create_channel_invite_params_init(p);
  return p;
}

void discord_create_channel_invite_params_free(struct discord_create_channel_invite_params *p) {
  discord_create_channel_invite_params_cleanup(p);
  free(p);
}

void discord_create_channel_invite_params_list_free(struct discord_create_channel_invite_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_channel_invite_params_cleanup);
}

void discord_create_channel_invite_params_list_from_json(char *str, size_t len, struct discord_create_channel_invite_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_channel_invite_params);
  d.init_elem = discord_create_channel_invite_params_init_v;
  d.elem_from_buf = discord_create_channel_invite_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_create_channel_invite_params_list_to_json(char *str, size_t len, struct discord_create_channel_invite_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_channel_invite_params_to_json_v);
}


void discord_group_dm_add_recipient_params_from_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
                "(access_token):?s,"
  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
                &p->access_token,
  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                &p->nick,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_group_dm_add_recipient_params_use_default_inject_settings(struct discord_group_dm_add_recipient_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[0] = p->access_token;

  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[1] = p->nick;

}

size_t discord_group_dm_add_recipient_params_to_json(char *json, size_t len, struct discord_group_dm_add_recipient_params *p)
{
  size_t r;
  discord_group_dm_add_recipient_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
                "(access_token):s,"
  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):s,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
                p->access_token,
  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                p->nick,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_group_dm_add_recipient_params_cleanup_v(void *p) {
  discord_group_dm_add_recipient_params_cleanup((struct discord_group_dm_add_recipient_params *)p);
}

void discord_group_dm_add_recipient_params_init_v(void *p) {
  discord_group_dm_add_recipient_params_init((struct discord_group_dm_add_recipient_params *)p);
}

void discord_group_dm_add_recipient_params_free_v(void *p) {
 discord_group_dm_add_recipient_params_free((struct discord_group_dm_add_recipient_params *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */
  if (d->access_token)
    free(d->access_token);
  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  if (d->nick)
    free(d->nick);
}

void discord_group_dm_add_recipient_params_init(struct discord_group_dm_add_recipient_params *p) {
  memset(p, 0, sizeof(struct discord_group_dm_add_recipient_params));
  /* specs/discord/channel.endpoints-params.json:87:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/channel.endpoints-params.json:88:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */

}
struct discord_group_dm_add_recipient_params* discord_group_dm_add_recipient_params_alloc() {
  struct discord_group_dm_add_recipient_params *p= malloc(sizeof(struct discord_group_dm_add_recipient_params));
  discord_group_dm_add_recipient_params_init(p);
  return p;
}

void discord_group_dm_add_recipient_params_free(struct discord_group_dm_add_recipient_params *p) {
  discord_group_dm_add_recipient_params_cleanup(p);
  free(p);
}

void discord_group_dm_add_recipient_params_list_free(struct discord_group_dm_add_recipient_params **p) {
  ntl_free((void**)p, (vfvp)discord_group_dm_add_recipient_params_cleanup);
}

void discord_group_dm_add_recipient_params_list_from_json(char *str, size_t len, struct discord_group_dm_add_recipient_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_group_dm_add_recipient_params);
  d.init_elem = discord_group_dm_add_recipient_params_init_v;
  d.elem_from_buf = discord_group_dm_add_recipient_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_group_dm_add_recipient_params_list_to_json(char *str, size_t len, struct discord_group_dm_add_recipient_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_group_dm_add_recipient_params_to_json_v);
}


void discord_start_thread_with_message_params_from_json(char *json, size_t len, struct discord_start_thread_with_message_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(name):?s,"
  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                &p->name,
  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_start_thread_with_message_params_use_default_inject_settings(struct discord_start_thread_with_message_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->auto_archive_duration != 0)
    p->__M.arg_switches[1] = &p->auto_archive_duration;

}

size_t discord_start_thread_with_message_params_to_json(char *json, size_t len, struct discord_start_thread_with_message_params *p)
{
  size_t r;
  discord_start_thread_with_message_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                "(name):s,"
  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
                p->name,
  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_start_thread_with_message_params_cleanup_v(void *p) {
  discord_start_thread_with_message_params_cleanup((struct discord_start_thread_with_message_params *)p);
}

void discord_start_thread_with_message_params_init_v(void *p) {
  discord_start_thread_with_message_params_init((struct discord_start_thread_with_message_params *)p);
}

void discord_start_thread_with_message_params_free_v(void *p) {
 discord_start_thread_with_message_params_free((struct discord_start_thread_with_message_params *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */
  if (d->name)
    free(d->name);
  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  // p->auto_archive_duration is a scalar
}

void discord_start_thread_with_message_params_init(struct discord_start_thread_with_message_params *p) {
  memset(p, 0, sizeof(struct discord_start_thread_with_message_params));
  /* specs/discord/channel.endpoints-params.json:98:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null }' */

  /* specs/discord/channel.endpoints-params.json:99:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */

}
struct discord_start_thread_with_message_params* discord_start_thread_with_message_params_alloc() {
  struct discord_start_thread_with_message_params *p= malloc(sizeof(struct discord_start_thread_with_message_params));
  discord_start_thread_with_message_params_init(p);
  return p;
}

void discord_start_thread_with_message_params_free(struct discord_start_thread_with_message_params *p) {
  discord_start_thread_with_message_params_cleanup(p);
  free(p);
}

void discord_start_thread_with_message_params_list_free(struct discord_start_thread_with_message_params **p) {
  ntl_free((void**)p, (vfvp)discord_start_thread_with_message_params_cleanup);
}

void discord_start_thread_with_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_with_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_start_thread_with_message_params);
  d.init_elem = discord_start_thread_with_message_params_init_v;
  d.elem_from_buf = discord_start_thread_with_message_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_start_thread_with_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_with_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_start_thread_with_message_params_to_json_v);
}


void discord_start_thread_without_message_params_from_json(char *json, size_t len, struct discord_start_thread_without_message_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
                "(name):?s,"
  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
                &p->name,
  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_start_thread_without_message_params_use_default_inject_settings(struct discord_start_thread_without_message_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  if (p->auto_archive_duration != 0)
    p->__M.arg_switches[1] = &p->auto_archive_duration;

}

size_t discord_start_thread_without_message_params_to_json(char *json, size_t len, struct discord_start_thread_without_message_params *p)
{
  size_t r;
  discord_start_thread_without_message_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
                "(name):s,"
  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                "(auto_archive_duration):d,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
                p->name,
  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
                &p->auto_archive_duration,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_start_thread_without_message_params_cleanup_v(void *p) {
  discord_start_thread_without_message_params_cleanup((struct discord_start_thread_without_message_params *)p);
}

void discord_start_thread_without_message_params_init_v(void *p) {
  discord_start_thread_without_message_params_init((struct discord_start_thread_without_message_params *)p);
}

void discord_start_thread_without_message_params_free_v(void *p) {
 discord_start_thread_without_message_params_free((struct discord_start_thread_without_message_params *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */
  if (d->name)
    free(d->name);
  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */
  // p->auto_archive_duration is a scalar
}

void discord_start_thread_without_message_params_init(struct discord_start_thread_without_message_params *p) {
  memset(p, 0, sizeof(struct discord_start_thread_without_message_params));
  /* specs/discord/channel.endpoints-params.json:109:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" } }' */

  /* specs/discord/channel.endpoints-params.json:110:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0 }' */

}
struct discord_start_thread_without_message_params* discord_start_thread_without_message_params_alloc() {
  struct discord_start_thread_without_message_params *p= malloc(sizeof(struct discord_start_thread_without_message_params));
  discord_start_thread_without_message_params_init(p);
  return p;
}

void discord_start_thread_without_message_params_free(struct discord_start_thread_without_message_params *p) {
  discord_start_thread_without_message_params_cleanup(p);
  free(p);
}

void discord_start_thread_without_message_params_list_free(struct discord_start_thread_without_message_params **p) {
  ntl_free((void**)p, (vfvp)discord_start_thread_without_message_params_cleanup);
}

void discord_start_thread_without_message_params_list_from_json(char *str, size_t len, struct discord_start_thread_without_message_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_start_thread_without_message_params);
  d.init_elem = discord_start_thread_without_message_params_init_v;
  d.elem_from_buf = discord_start_thread_without_message_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_start_thread_without_message_params_list_to_json(char *str, size_t len, struct discord_start_thread_without_message_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_start_thread_without_message_params_to_json_v);
}


void discord_thread_response_body_from_json(char *json, size_t len, struct discord_thread_response_body *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.endpoints-params.json:120:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
                "(threads):F,"
  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
                "(members):F,"
  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
                "(has_more):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.endpoints-params.json:120:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
                discord_channel_list_from_json, &p->threads,
  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
                discord_thread_member_list_from_json, &p->members,
  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
                &p->has_more,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_thread_response_body_use_default_inject_settings(struct discord_thread_response_body *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.endpoints-params.json:120:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  p->__M.arg_switches[0] = p->threads;

  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  p->__M.arg_switches[1] = p->members;

  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  p->__M.arg_switches[2] = &p->has_more;

}

size_t discord_thread_response_body_to_json(char *json, size_t len, struct discord_thread_response_body *p)
{
  size_t r;
  discord_thread_response_body_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.endpoints-params.json:120:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
                "(threads):F,"
  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
                "(members):F,"
  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
                "(has_more):b,"
                "@arg_switches:b",
  /* specs/discord/channel.endpoints-params.json:120:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
                discord_channel_list_to_json, p->threads,
  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
                discord_thread_member_list_to_json, p->members,
  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
                &p->has_more,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_thread_response_body_cleanup_v(void *p) {
  discord_thread_response_body_cleanup((struct discord_thread_response_body *)p);
}

void discord_thread_response_body_init_v(void *p) {
  discord_thread_response_body_init((struct discord_thread_response_body *)p);
}

void discord_thread_response_body_free_v(void *p) {
 discord_thread_response_body_free((struct discord_thread_response_body *)p);
};

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
  /* specs/discord/channel.endpoints-params.json:120:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */
  if (d->threads)
    discord_channel_list_free(d->threads);
  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */
  if (d->members)
    discord_thread_member_list_free(d->members);
  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */
  // p->has_more is a scalar
}

void discord_thread_response_body_init(struct discord_thread_response_body *p) {
  memset(p, 0, sizeof(struct discord_thread_response_body));
  /* specs/discord/channel.endpoints-params.json:120:20
     '{ "name": "threads", "type":{ "base":"struct discord_channel", "dec":"ntl" } }' */

  /* specs/discord/channel.endpoints-params.json:121:20
     '{ "name": "members", "type":{ "base":"struct discord_thread_member", "dec":"ntl" } }' */

  /* specs/discord/channel.endpoints-params.json:122:20
     '{ "name": "has_more", "type":{ "base":"bool" } }' */

}
struct discord_thread_response_body* discord_thread_response_body_alloc() {
  struct discord_thread_response_body *p= malloc(sizeof(struct discord_thread_response_body));
  discord_thread_response_body_init(p);
  return p;
}

void discord_thread_response_body_free(struct discord_thread_response_body *p) {
  discord_thread_response_body_cleanup(p);
  free(p);
}

void discord_thread_response_body_list_free(struct discord_thread_response_body **p) {
  ntl_free((void**)p, (vfvp)discord_thread_response_body_cleanup);
}

void discord_thread_response_body_list_from_json(char *str, size_t len, struct discord_thread_response_body ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_thread_response_body);
  d.init_elem = discord_thread_response_body_init_v;
  d.elem_from_buf = discord_thread_response_body_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json(str, len, &d);
}

size_t discord_thread_response_body_list_to_json(char *str, size_t len, struct discord_thread_response_body **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_thread_response_body_to_json_v);
}

