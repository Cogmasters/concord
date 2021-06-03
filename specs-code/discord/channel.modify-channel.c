/* This file is generated from specs/discord/channel.modify-channel.json, Please don't edit it. */
#include "specs.h"
/*

*/

void discord_modify_channel_params_from_json(char *json, size_t len, struct discord_modify_channel_params *p)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  r=json_extract(json, len, 
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(name):?s,"
  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(icon):?s,"
  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
                "(type):d,"
  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                "(position):d,"
  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(topic):?s,"
  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(nsfw):b,"
  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(rate_limit_per_user):d,"
  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(bitrate):d,"
  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(user_limit):d,"
  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
                "(permission_overwrites):F,"
  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
                "(parent_id):F,"
  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(rtc_region):?s,"
  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(video_quality_mode):d,"
  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */
                "(archived):b,"
  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(auto_archive_duration):d,"
  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(locked):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                &p->name,
  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                &p->icon,
  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
                &p->type,
  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                &p->position,
  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                &p->topic,
  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->nsfw,
  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->rate_limit_per_user,
  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->bitrate,
  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->user_limit,
  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
                discord_channel_overwrite_list_from_json, &p->permission_overwrites,
  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
                orka_strtoull, &p->parent_id,
  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                &p->rtc_region,
  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->video_quality_mode,
  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */
                &p->archived,
  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->auto_archive_duration,
  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->locked,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_channel_params_use_default_inject_settings(struct discord_modify_channel_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (p->icon != NULL)
    p->__M.arg_switches[1] = p->icon;

  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  p->__M.arg_switches[2] = &p->type;

  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  if (p->position != 0)
    p->__M.arg_switches[3] = &p->position;

  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (p->topic != NULL)
    p->__M.arg_switches[4] = p->topic;

  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->nsfw != false)
    p->__M.arg_switches[5] = &p->nsfw;

  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->rate_limit_per_user != 0)
    p->__M.arg_switches[6] = &p->rate_limit_per_user;

  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->bitrate != 0)
    p->__M.arg_switches[7] = &p->bitrate;

  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->user_limit != 0)
    p->__M.arg_switches[8] = &p->user_limit;

  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
  if (p->permission_overwrites != NULL)
    p->__M.arg_switches[9] = p->permission_overwrites;

  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  if (p->parent_id != 0)
    p->__M.arg_switches[10] = &p->parent_id;

  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (p->rtc_region != NULL)
    p->__M.arg_switches[11] = p->rtc_region;

  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->video_quality_mode != 0)
    p->__M.arg_switches[12] = &p->video_quality_mode;

  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */
  if (p->archived != false)
    p->__M.arg_switches[13] = &p->archived;

  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  if (p->auto_archive_duration != 0)
    p->__M.arg_switches[14] = &p->auto_archive_duration;

  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  if (p->locked != false)
    p->__M.arg_switches[15] = &p->locked;

}

size_t discord_modify_channel_params_to_json(char *json, size_t len, struct discord_modify_channel_params *p)
{
  size_t r;
  discord_modify_channel_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(name):s,"
  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(icon):s,"
  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
                "(type):d,"
  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                "(position):d,"
  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(topic):s,"
  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(nsfw):b,"
  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(rate_limit_per_user):d,"
  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(bitrate):d,"
  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(user_limit):d,"
  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
                "(permission_overwrites):F,"
  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
                "(parent_id):|F|,"
  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                "(rtc_region):s,"
  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(video_quality_mode):d,"
  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */
                "(archived):b,"
  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                "(auto_archive_duration):d,"
  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                "(locked):b,"
                "@arg_switches:b",
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                p->name,
  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                p->icon,
  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
                &p->type,
  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
                &p->position,
  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                p->topic,
  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
                &p->nsfw,
  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->rate_limit_per_user,
  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->bitrate,
  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->user_limit,
  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
                discord_channel_overwrite_list_to_json, p->permission_overwrites,
  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
                orka_ulltostr, &p->parent_id,
  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
                p->rtc_region,
  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->video_quality_mode,
  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */
                &p->archived,
  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */
                &p->auto_archive_duration,
  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
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
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (d->name)
    free(d->name);
  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (d->icon)
    free(d->icon);
  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */
  //p->type is a scalar
  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */
  //p->position is a scalar
  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (d->topic)
    free(d->topic);
  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->nsfw is a scalar
  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->rate_limit_per_user is a scalar
  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->bitrate is a scalar
  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->user_limit is a scalar
  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */
  if (d->permission_overwrites)
    discord_channel_overwrite_list_free(d->permission_overwrites);
  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */
  //p->parent_id is a scalar
  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */
  if (d->rtc_region)
    free(d->rtc_region);
  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->video_quality_mode is a scalar
  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */
  //p->archived is a scalar
  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */
  //p->auto_archive_duration is a scalar
  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */
  //p->locked is a scalar
}

void discord_modify_channel_params_init(struct discord_modify_channel_params *p) {
  memset(p, 0, sizeof(struct discord_modify_channel_params));
  /* specs/discord/channel.modify-channel.json:11:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */

  /* specs/discord/channel.modify-channel.json:12:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */

  /* specs/discord/channel.modify-channel.json:13:20
     '{ "name": "type", "type":{ "base":"int" }}'
  */

  /* specs/discord/channel.modify-channel.json:14:20
     '{ "name": "position", "type":{ "base":"int" }, "inject_if_not":0 }'
  */

  /* specs/discord/channel.modify-channel.json:15:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */

  /* specs/discord/channel.modify-channel.json:16:20
     '{ "name": "nsfw", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

  /* specs/discord/channel.modify-channel.json:17:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.modify-channel.json:18:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.modify-channel.json:19:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.modify-channel.json:20:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}'
  */

  /* specs/discord/channel.modify-channel.json:21:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.modify-channel.json:22:20
     '{ "name": "rtc_region", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}'
  */

  /* specs/discord/channel.modify-channel.json:23:20
     '{ "name": "video_quality_mode", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.modify-channel.json:24:20
     '{ "name": "archived", "type":{ "base":"bool" }, "inject_if_not":false }'
  */

  /* specs/discord/channel.modify-channel.json:25:20
     '{ "name": "auto_archive_duration", "type":{ "base":"int" }, "inject_if_not":0}'
  */

  /* specs/discord/channel.modify-channel.json:26:20
     '{ "name": "locked", "type":{ "base":"bool" }, "inject_if_not":false}'
  */

}
struct discord_modify_channel_params* discord_modify_channel_params_alloc() {
  struct discord_modify_channel_params *p= (struct discord_modify_channel_params*)malloc(sizeof(struct discord_modify_channel_params));
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

