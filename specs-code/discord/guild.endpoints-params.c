/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild.endpoints-params.c
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild
 */

#include "specs.h"

void discord_create_guild_params_from_json(char *json, size_t len, struct discord_create_guild_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_create_guild_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                "(name):?s,"
  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                "(region):?s,"
  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                "(icon):?s,"
  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                "(verification_level):d,"
  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                "(default_message_notifications):d,"
  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                "(explicit_content_filter):d,"
  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */
  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
                "(channels):F,"
  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                "(afk_channel_id):F,"
  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                "(afk_timeout):d,"
  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                "(system_channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                &p->name,
  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                &p->region,
  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                &p->icon,
  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                &p->verification_level,
  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                &p->default_message_notifications,
  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                &p->explicit_content_filter,
  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */
  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
                discord_channel_list_from_json, &p->channels,
  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                cee_strtoull, &p->afk_channel_id,
  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                &p->afk_timeout,
  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                cee_strtoull, &p->system_channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_create_guild_params_use_default_inject_settings(struct discord_create_guild_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  if (p->region != NULL)
    p->__M.arg_switches[1] = p->region;

  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  if (p->icon != NULL)
    p->__M.arg_switches[2] = p->icon;

  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  if (p->verification_level != 0)
    p->__M.arg_switches[3] = &p->verification_level;

  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  if (p->default_message_notifications != 0)
    p->__M.arg_switches[4] = &p->default_message_notifications;

  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  if (p->explicit_content_filter != 0)
    p->__M.arg_switches[5] = &p->explicit_content_filter;

  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */

  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
  if (p->channels != NULL)
    p->__M.arg_switches[7] = p->channels;

  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  if (p->afk_channel_id != 0)
    p->__M.arg_switches[8] = &p->afk_channel_id;

  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  if (p->afk_timeout != 0)
    p->__M.arg_switches[9] = &p->afk_timeout;

  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  if (p->system_channel_id != 0)
    p->__M.arg_switches[10] = &p->system_channel_id;

}

size_t discord_create_guild_params_to_json(char *json, size_t len, struct discord_create_guild_params *p)
{
  size_t r;
  discord_create_guild_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                "(name):s,"
  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                "(region):s,"
  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                "(icon):s,"
  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                "(verification_level):d,"
  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                "(default_message_notifications):d,"
  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                "(explicit_content_filter):d,"
  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */
  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
                "(channels):F,"
  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                "(afk_channel_id):|F|,"
  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                "(afk_timeout):d,"
  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                "(system_channel_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                p->name,
  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                p->region,
  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                p->icon,
  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                &p->verification_level,
  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                &p->default_message_notifications,
  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                &p->explicit_content_filter,
  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */
  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
                discord_channel_list_to_json, p->channels,
  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                cee_ulltostr, &p->afk_channel_id,
  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                &p->afk_timeout,
  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                cee_ulltostr, &p->system_channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_guild_params_cleanup_v(void *p) {
  discord_create_guild_params_cleanup((struct discord_create_guild_params *)p);
}

void discord_create_guild_params_init_v(void *p) {
  discord_create_guild_params_init((struct discord_create_guild_params *)p);
}

void discord_create_guild_params_free_v(void *p) {
 discord_create_guild_params_free((struct discord_create_guild_params *)p);
};

void discord_create_guild_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_guild_params_from_json(json, len, (struct discord_create_guild_params**)pp);
}

size_t discord_create_guild_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_params_to_json(json, len, (struct discord_create_guild_params*)p);
}

void discord_create_guild_params_list_free_v(void **p) {
  discord_create_guild_params_list_free((struct discord_create_guild_params**)p);
}

void discord_create_guild_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_params_list_from_json(str, len, (struct discord_create_guild_params ***)p);
}

size_t discord_create_guild_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_params_list_to_json(str, len, (struct discord_create_guild_params **)p);
}


void discord_create_guild_params_cleanup(struct discord_create_guild_params *d) {
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  if (d->region)
    free(d->region);
  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  if (d->icon)
    free(d->icon);
  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  // p->verification_level is a scalar
  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  // p->default_message_notifications is a scalar
  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  // p->explicit_content_filter is a scalar
  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */
  // @todo p->(null)
  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
  if (d->channels)
    discord_channel_list_free(d->channels);
  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  // p->afk_channel_id is a scalar
  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  // p->afk_timeout is a scalar
  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  // p->system_channel_id is a scalar
}

void discord_create_guild_params_init(struct discord_create_guild_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_params));
  /* specs/discord/guild.endpoints-params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */

  /* specs/discord/guild.endpoints-params.json:14:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */

  /* specs/discord/guild.endpoints-params.json:15:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */

  /* specs/discord/guild.endpoints-params.json:16:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */

  /* specs/discord/guild.endpoints-params.json:17:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */

  /* specs/discord/guild.endpoints-params.json:18:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */

  /* specs/discord/guild.endpoints-params.json:19:20
     '{ "name": "roles", "type":{ "base":"int" }, "todo":true, "comment":"new guild roles" }' */

  /* specs/discord/guild.endpoints-params.json:20:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */

  /* specs/discord/guild.endpoints-params.json:21:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */

  /* specs/discord/guild.endpoints-params.json:22:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */

  /* specs/discord/guild.endpoints-params.json:23:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */

}
struct discord_create_guild_params* discord_create_guild_params_alloc() {
  struct discord_create_guild_params *p= malloc(sizeof(struct discord_create_guild_params));
  discord_create_guild_params_init(p);
  return p;
}

void discord_create_guild_params_free(struct discord_create_guild_params *p) {
  discord_create_guild_params_cleanup(p);
  free(p);
}

void discord_create_guild_params_list_free(struct discord_create_guild_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_guild_params_cleanup);
}

void discord_create_guild_params_list_from_json(char *str, size_t len, struct discord_create_guild_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_guild_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_params_list_to_json(char *str, size_t len, struct discord_create_guild_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_guild_params_to_json_v);
}


void discord_modify_guild_params_from_json(char *json, size_t len, struct discord_modify_guild_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_modify_guild_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                "(name):?s,"
  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                "(region):?s,"
  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                "(verification_level):d,"
  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                "(default_message_notifications):d,"
  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                "(explicit_content_filter):d,"
  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                "(afk_channel_id):F,"
  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                "(afk_timeout):d,"
  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                "(icon):?s,"
  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
                "(owner_id):F,"
  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
                "(splash):?s,"
  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
                "(discovery_splash):?s,"
  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
                "(banner):?s,"
  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                "(system_channel_id):F,"
  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
                "(system_channel_flags):d,"
  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
                "(rules_channel_id):F,"
  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
                "(public_updates_channel_id):F,"
  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
                "(preferred_locale):?s,"
  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */
  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
                "(description):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                &p->name,
  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                &p->region,
  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                &p->verification_level,
  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                &p->default_message_notifications,
  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                &p->explicit_content_filter,
  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                cee_strtoull, &p->afk_channel_id,
  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                &p->afk_timeout,
  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                &p->icon,
  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
                cee_strtoull, &p->owner_id,
  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
                &p->splash,
  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
                &p->discovery_splash,
  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
                &p->banner,
  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                cee_strtoull, &p->system_channel_id,
  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
                &p->system_channel_flags,
  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
                cee_strtoull, &p->rules_channel_id,
  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
                cee_strtoull, &p->public_updates_channel_id,
  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
                &p->preferred_locale,
  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */
  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
                &p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_params_use_default_inject_settings(struct discord_modify_guild_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  if (p->region != NULL)
    p->__M.arg_switches[1] = p->region;

  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  if (p->verification_level != 0)
    p->__M.arg_switches[2] = &p->verification_level;

  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  if (p->default_message_notifications != 0)
    p->__M.arg_switches[3] = &p->default_message_notifications;

  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  if (p->explicit_content_filter != 0)
    p->__M.arg_switches[4] = &p->explicit_content_filter;

  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  if (p->afk_channel_id != 0)
    p->__M.arg_switches[5] = &p->afk_channel_id;

  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  if (p->afk_timeout != 0)
    p->__M.arg_switches[6] = &p->afk_timeout;

  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  if (p->icon != NULL)
    p->__M.arg_switches[7] = p->icon;

  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
  if (p->owner_id != 0)
    p->__M.arg_switches[8] = &p->owner_id;

  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
  if (p->splash != NULL)
    p->__M.arg_switches[9] = p->splash;

  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
  if (p->discovery_splash != NULL)
    p->__M.arg_switches[10] = p->discovery_splash;

  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
  if (p->banner != NULL)
    p->__M.arg_switches[11] = p->banner;

  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  if (p->system_channel_id != 0)
    p->__M.arg_switches[12] = &p->system_channel_id;

  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
  if (p->system_channel_flags != 0)
    p->__M.arg_switches[13] = &p->system_channel_flags;

  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
  if (p->rules_channel_id != 0)
    p->__M.arg_switches[14] = &p->rules_channel_id;

  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
  if (p->public_updates_channel_id != 0)
    p->__M.arg_switches[15] = &p->public_updates_channel_id;

  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
  p->__M.arg_switches[16] = p->preferred_locale;

  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */

  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
  p->__M.arg_switches[18] = p->description;

}

size_t discord_modify_guild_params_to_json(char *json, size_t len, struct discord_modify_guild_params *p)
{
  size_t r;
  discord_modify_guild_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                "(name):s,"
  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                "(region):s,"
  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                "(verification_level):d,"
  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                "(default_message_notifications):d,"
  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                "(explicit_content_filter):d,"
  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                "(afk_channel_id):|F|,"
  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                "(afk_timeout):d,"
  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                "(icon):s,"
  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
                "(owner_id):|F|,"
  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
                "(splash):s,"
  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
                "(discovery_splash):s,"
  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
                "(banner):s,"
  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                "(system_channel_id):|F|,"
  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
                "(system_channel_flags):d,"
  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
                "(rules_channel_id):|F|,"
  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
                "(public_updates_channel_id):|F|,"
  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
                "(preferred_locale):s,"
  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */
  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
                "(description):s,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                p->name,
  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                p->region,
  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                &p->verification_level,
  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                &p->default_message_notifications,
  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                &p->explicit_content_filter,
  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                cee_ulltostr, &p->afk_channel_id,
  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                &p->afk_timeout,
  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                p->icon,
  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
                cee_ulltostr, &p->owner_id,
  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
                p->splash,
  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
                p->discovery_splash,
  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
                p->banner,
  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                cee_ulltostr, &p->system_channel_id,
  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
                &p->system_channel_flags,
  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
                cee_ulltostr, &p->rules_channel_id,
  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
                cee_ulltostr, &p->public_updates_channel_id,
  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
                p->preferred_locale,
  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */
  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
                p->description,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_params_cleanup_v(void *p) {
  discord_modify_guild_params_cleanup((struct discord_modify_guild_params *)p);
}

void discord_modify_guild_params_init_v(void *p) {
  discord_modify_guild_params_init((struct discord_modify_guild_params *)p);
}

void discord_modify_guild_params_free_v(void *p) {
 discord_modify_guild_params_free((struct discord_modify_guild_params *)p);
};

void discord_modify_guild_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_guild_params_from_json(json, len, (struct discord_modify_guild_params**)pp);
}

size_t discord_modify_guild_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_params_to_json(json, len, (struct discord_modify_guild_params*)p);
}

void discord_modify_guild_params_list_free_v(void **p) {
  discord_modify_guild_params_list_free((struct discord_modify_guild_params**)p);
}

void discord_modify_guild_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_params_list_from_json(str, len, (struct discord_modify_guild_params ***)p);
}

size_t discord_modify_guild_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_params_list_to_json(str, len, (struct discord_modify_guild_params **)p);
}


void discord_modify_guild_params_cleanup(struct discord_modify_guild_params *d) {
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  if (d->region)
    free(d->region);
  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  // p->verification_level is a scalar
  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  // p->default_message_notifications is a scalar
  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  // p->explicit_content_filter is a scalar
  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  // p->afk_channel_id is a scalar
  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  // p->afk_timeout is a scalar
  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  if (d->icon)
    free(d->icon);
  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
  // p->owner_id is a scalar
  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
  if (d->splash)
    free(d->splash);
  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
  if (d->discovery_splash)
    free(d->discovery_splash);
  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
  if (d->banner)
    free(d->banner);
  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  // p->system_channel_id is a scalar
  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
  // p->system_channel_flags is a scalar
  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
  // p->rules_channel_id is a scalar
  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
  // p->public_updates_channel_id is a scalar
  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
  if (d->preferred_locale)
    free(d->preferred_locale);
  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */
  // @todo p->(null)
  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
  if (d->description)
    free(d->description);
}

void discord_modify_guild_params_init(struct discord_modify_guild_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_params));
  /* specs/discord/guild.endpoints-params.json:33:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */

  /* specs/discord/guild.endpoints-params.json:34:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */

  /* specs/discord/guild.endpoints-params.json:35:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */

  /* specs/discord/guild.endpoints-params.json:36:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */

  /* specs/discord/guild.endpoints-params.json:37:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */

  /* specs/discord/guild.endpoints-params.json:38:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */

  /* specs/discord/guild.endpoints-params.json:39:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */

  /* specs/discord/guild.endpoints-params.json:40:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */

  /* specs/discord/guild.endpoints-params.json:41:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */

  /* specs/discord/guild.endpoints-params.json:42:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */

  /* specs/discord/guild.endpoints-params.json:43:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */

  /* specs/discord/guild.endpoints-params.json:44:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */

  /* specs/discord/guild.endpoints-params.json:45:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */

  /* specs/discord/guild.endpoints-params.json:46:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_guild_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */

  /* specs/discord/guild.endpoints-params.json:47:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */

  /* specs/discord/guild.endpoints-params.json:48:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */

  /* specs/discord/guild.endpoints-params.json:49:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */

  /* specs/discord/guild.endpoints-params.json:50:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "todo":true, "comment":"array of guild feature strings"}' */

  /* specs/discord/guild.endpoints-params.json:51:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */

}
struct discord_modify_guild_params* discord_modify_guild_params_alloc() {
  struct discord_modify_guild_params *p= malloc(sizeof(struct discord_modify_guild_params));
  discord_modify_guild_params_init(p);
  return p;
}

void discord_modify_guild_params_free(struct discord_modify_guild_params *p) {
  discord_modify_guild_params_cleanup(p);
  free(p);
}

void discord_modify_guild_params_list_free(struct discord_modify_guild_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_params_cleanup);
}

void discord_modify_guild_params_list_from_json(char *str, size_t len, struct discord_modify_guild_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_guild_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_params_list_to_json(char *str, size_t len, struct discord_modify_guild_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_params_to_json_v);
}


void discord_create_guild_channel_params_from_json(char *json, size_t len, struct discord_create_guild_channel_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_create_guild_channel_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
                "(topic):?s,"
  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(bitrate):d,"
  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(user_limit):d,"
  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(rate_limit_per_user):d,"
  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */
                "(position):d,"
  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
                "(permission_overwrites):F,"
  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                "(parent_id):F,"
  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
                "(nsfw):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
                &p->topic,
  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->bitrate,
  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->user_limit,
  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->rate_limit_per_user,
  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */
                &p->position,
  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
                discord_channel_overwrite_list_from_json, &p->permission_overwrites,
  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                cee_strtoull, &p->parent_id,
  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
                &p->nsfw,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_create_guild_channel_params_use_default_inject_settings(struct discord_create_guild_channel_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  p->__M.arg_switches[1] = &p->type;

  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[2] = p->topic;

  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->bitrate != 0)
    p->__M.arg_switches[3] = &p->bitrate;

  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->user_limit != 0)
    p->__M.arg_switches[4] = &p->user_limit;

  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->rate_limit_per_user != 0)
    p->__M.arg_switches[5] = &p->rate_limit_per_user;

  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */
  p->__M.arg_switches[6] = &p->position;

  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->permission_overwrites != NULL)
    p->__M.arg_switches[7] = p->permission_overwrites;

  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  if (p->parent_id != 0)
    p->__M.arg_switches[8] = &p->parent_id;

  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
  p->__M.arg_switches[9] = &p->nsfw;

}

size_t discord_create_guild_channel_params_to_json(char *json, size_t len, struct discord_create_guild_channel_params *p)
{
  size_t r;
  discord_create_guild_channel_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
                "(topic):s,"
  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(bitrate):d,"
  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(user_limit):d,"
  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(rate_limit_per_user):d,"
  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */
                "(position):d,"
  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
                "(permission_overwrites):F,"
  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                "(parent_id):|F|,"
  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
                "(nsfw):b,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
                p->topic,
  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->bitrate,
  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->user_limit,
  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->rate_limit_per_user,
  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */
                &p->position,
  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
                discord_channel_overwrite_list_to_json, p->permission_overwrites,
  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                cee_ulltostr, &p->parent_id,
  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
                &p->nsfw,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_guild_channel_params_cleanup_v(void *p) {
  discord_create_guild_channel_params_cleanup((struct discord_create_guild_channel_params *)p);
}

void discord_create_guild_channel_params_init_v(void *p) {
  discord_create_guild_channel_params_init((struct discord_create_guild_channel_params *)p);
}

void discord_create_guild_channel_params_free_v(void *p) {
 discord_create_guild_channel_params_free((struct discord_create_guild_channel_params *)p);
};

void discord_create_guild_channel_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_guild_channel_params_from_json(json, len, (struct discord_create_guild_channel_params**)pp);
}

size_t discord_create_guild_channel_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_channel_params_to_json(json, len, (struct discord_create_guild_channel_params*)p);
}

void discord_create_guild_channel_params_list_free_v(void **p) {
  discord_create_guild_channel_params_list_free((struct discord_create_guild_channel_params**)p);
}

void discord_create_guild_channel_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_channel_params_list_from_json(str, len, (struct discord_create_guild_channel_params ***)p);
}

size_t discord_create_guild_channel_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_channel_params_list_to_json(str, len, (struct discord_create_guild_channel_params **)p);
}


void discord_create_guild_channel_params_cleanup(struct discord_create_guild_channel_params *d) {
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  // p->type is a scalar
  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
  if (d->topic)
    free(d->topic);
  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->bitrate is a scalar
  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->user_limit is a scalar
  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->rate_limit_per_user is a scalar
  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */
  // p->position is a scalar
  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->permission_overwrites)
    discord_channel_overwrite_list_free(d->permission_overwrites);
  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  // p->parent_id is a scalar
  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
  // p->nsfw is a scalar
}

void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_channel_params));
  /* specs/discord/guild.endpoints-params.json:61:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild.endpoints-params.json:62:20
     '{ "name": "type", "type":{ "base":"int" }}' */

  /* specs/discord/guild.endpoints-params.json:63:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild.endpoints-params.json:64:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/guild.endpoints-params.json:65:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/guild.endpoints-params.json:66:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/guild.endpoints-params.json:67:20
     '{ "name": "position", "type":{ "base":"int" } }' */

  /* specs/discord/guild.endpoints-params.json:68:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_channel_overwrite", "dec":"ntl" }, "inject_if_not":null}' */

  /* specs/discord/guild.endpoints-params.json:69:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */

  /* specs/discord/guild.endpoints-params.json:70:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */

}
struct discord_create_guild_channel_params* discord_create_guild_channel_params_alloc() {
  struct discord_create_guild_channel_params *p= malloc(sizeof(struct discord_create_guild_channel_params));
  discord_create_guild_channel_params_init(p);
  return p;
}

void discord_create_guild_channel_params_free(struct discord_create_guild_channel_params *p) {
  discord_create_guild_channel_params_cleanup(p);
  free(p);
}

void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_guild_channel_params_cleanup);
}

void discord_create_guild_channel_params_list_from_json(char *str, size_t len, struct discord_create_guild_channel_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_channel_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_guild_channel_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_channel_params_list_to_json(char *str, size_t len, struct discord_create_guild_channel_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_guild_channel_params_to_json_v);
}


void discord_modify_guild_channel_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_modify_guild_channel_positions_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
                "(id):F,"
  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
                "(position):d,"
  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
                "(lock_permissions):b,"
  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
                "(parent_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
                cee_strtoull, &p->id,
  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
                &p->position,
  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
                &p->lock_permissions,
  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
                cee_strtoull, &p->parent_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_channel_positions_params_use_default_inject_settings(struct discord_modify_guild_channel_positions_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
  if (p->id != 0)
    p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
  if (p->position != 0)
    p->__M.arg_switches[1] = &p->position;

  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
  if (p->lock_permissions != false)
    p->__M.arg_switches[2] = &p->lock_permissions;

  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
  if (p->parent_id != 0)
    p->__M.arg_switches[3] = &p->parent_id;

}

size_t discord_modify_guild_channel_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p)
{
  size_t r;
  discord_modify_guild_channel_positions_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
                "(id):|F|,"
  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
                "(position):d,"
  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
                "(lock_permissions):b,"
  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
                "(parent_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
                &p->position,
  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
                &p->lock_permissions,
  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
                cee_ulltostr, &p->parent_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_channel_positions_params_cleanup_v(void *p) {
  discord_modify_guild_channel_positions_params_cleanup((struct discord_modify_guild_channel_positions_params *)p);
}

void discord_modify_guild_channel_positions_params_init_v(void *p) {
  discord_modify_guild_channel_positions_params_init((struct discord_modify_guild_channel_positions_params *)p);
}

void discord_modify_guild_channel_positions_params_free_v(void *p) {
 discord_modify_guild_channel_positions_params_free((struct discord_modify_guild_channel_positions_params *)p);
};

void discord_modify_guild_channel_positions_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_guild_channel_positions_params_from_json(json, len, (struct discord_modify_guild_channel_positions_params**)pp);
}

size_t discord_modify_guild_channel_positions_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_channel_positions_params_to_json(json, len, (struct discord_modify_guild_channel_positions_params*)p);
}

void discord_modify_guild_channel_positions_params_list_free_v(void **p) {
  discord_modify_guild_channel_positions_params_list_free((struct discord_modify_guild_channel_positions_params**)p);
}

void discord_modify_guild_channel_positions_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_channel_positions_params_list_from_json(str, len, (struct discord_modify_guild_channel_positions_params ***)p);
}

size_t discord_modify_guild_channel_positions_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_channel_positions_params_list_to_json(str, len, (struct discord_modify_guild_channel_positions_params **)p);
}


void discord_modify_guild_channel_positions_params_cleanup(struct discord_modify_guild_channel_positions_params *d) {
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
  // p->id is a scalar
  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
  // p->position is a scalar
  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
  // p->lock_permissions is a scalar
  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
  // p->parent_id is a scalar
}

void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_channel_positions_params));
  /* specs/discord/guild.endpoints-params.json:80:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */

  /* specs/discord/guild.endpoints-params.json:81:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */

  /* specs/discord/guild.endpoints-params.json:82:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */

  /* specs/discord/guild.endpoints-params.json:83:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */

}
struct discord_modify_guild_channel_positions_params* discord_modify_guild_channel_positions_params_alloc() {
  struct discord_modify_guild_channel_positions_params *p= malloc(sizeof(struct discord_modify_guild_channel_positions_params));
  discord_modify_guild_channel_positions_params_init(p);
  return p;
}

void discord_modify_guild_channel_positions_params_free(struct discord_modify_guild_channel_positions_params *p) {
  discord_modify_guild_channel_positions_params_cleanup(p);
  free(p);
}

void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_channel_positions_params_cleanup);
}

void discord_modify_guild_channel_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_channel_positions_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_guild_channel_positions_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_channel_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_channel_positions_params_to_json_v);
}


void discord_search_guild_members_params_from_json(char *json, size_t len, struct discord_search_guild_members_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_search_guild_members_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
                "(query):?s,"
  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
                "(limit):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
                &p->query,
  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_search_guild_members_params_use_default_inject_settings(struct discord_search_guild_members_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
  if (p->query != NULL)
    p->__M.arg_switches[0] = p->query;

  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
  if (p->limit != 0)
    p->__M.arg_switches[1] = &p->limit;

}

size_t discord_search_guild_members_params_to_json(char *json, size_t len, struct discord_search_guild_members_params *p)
{
  size_t r;
  discord_search_guild_members_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
                "(query):s,"
  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
                "(limit):d,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
                p->query,
  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
                &p->limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_search_guild_members_params_cleanup_v(void *p) {
  discord_search_guild_members_params_cleanup((struct discord_search_guild_members_params *)p);
}

void discord_search_guild_members_params_init_v(void *p) {
  discord_search_guild_members_params_init((struct discord_search_guild_members_params *)p);
}

void discord_search_guild_members_params_free_v(void *p) {
 discord_search_guild_members_params_free((struct discord_search_guild_members_params *)p);
};

void discord_search_guild_members_params_from_json_v(char *json, size_t len, void *pp) {
 discord_search_guild_members_params_from_json(json, len, (struct discord_search_guild_members_params**)pp);
}

size_t discord_search_guild_members_params_to_json_v(char *json, size_t len, void *p) {
  return discord_search_guild_members_params_to_json(json, len, (struct discord_search_guild_members_params*)p);
}

void discord_search_guild_members_params_list_free_v(void **p) {
  discord_search_guild_members_params_list_free((struct discord_search_guild_members_params**)p);
}

void discord_search_guild_members_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_search_guild_members_params_list_from_json(str, len, (struct discord_search_guild_members_params ***)p);
}

size_t discord_search_guild_members_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_search_guild_members_params_list_to_json(str, len, (struct discord_search_guild_members_params **)p);
}


void discord_search_guild_members_params_cleanup(struct discord_search_guild_members_params *d) {
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
  if (d->query)
    free(d->query);
  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
  // p->limit is a scalar
}

void discord_search_guild_members_params_init(struct discord_search_guild_members_params *p) {
  memset(p, 0, sizeof(struct discord_search_guild_members_params));
  /* specs/discord/guild.endpoints-params.json:93:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */

  /* specs/discord/guild.endpoints-params.json:94:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */

}
struct discord_search_guild_members_params* discord_search_guild_members_params_alloc() {
  struct discord_search_guild_members_params *p= malloc(sizeof(struct discord_search_guild_members_params));
  discord_search_guild_members_params_init(p);
  return p;
}

void discord_search_guild_members_params_free(struct discord_search_guild_members_params *p) {
  discord_search_guild_members_params_cleanup(p);
  free(p);
}

void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **p) {
  ntl_free((void**)p, (vfvp)discord_search_guild_members_params_cleanup);
}

void discord_search_guild_members_params_list_from_json(char *str, size_t len, struct discord_search_guild_members_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_search_guild_members_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_search_guild_members_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_search_guild_members_params_list_to_json(char *str, size_t len, struct discord_search_guild_members_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_search_guild_members_params_to_json_v);
}


void discord_add_guild_member_params_from_json(char *json, size_t len, struct discord_add_guild_member_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_add_guild_member_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(access_token):?s,"
  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(nick):?s,"
  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(roles):F,"
  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mute):b,"
  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(deaf):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->access_token,
  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->nick,
  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_from_json, &p->roles,
  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mute,
  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->deaf,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_add_guild_member_params_use_default_inject_settings(struct discord_add_guild_member_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->access_token != NULL)
    p->__M.arg_switches[0] = p->access_token;

  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->nick != NULL)
    p->__M.arg_switches[1] = p->nick;

  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->roles != NULL)
    p->__M.arg_switches[2] = p->roles;

  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->mute != false)
    p->__M.arg_switches[3] = &p->mute;

  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->deaf != false)
    p->__M.arg_switches[4] = &p->deaf;

}

size_t discord_add_guild_member_params_to_json(char *json, size_t len, struct discord_add_guild_member_params *p)
{
  size_t r;
  discord_add_guild_member_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(access_token):s,"
  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(nick):s,"
  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(roles):F,"
  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mute):b,"
  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(deaf):b,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->access_token,
  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->nick,
  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_to_json, p->roles,
  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mute,
  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->deaf,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_add_guild_member_params_cleanup_v(void *p) {
  discord_add_guild_member_params_cleanup((struct discord_add_guild_member_params *)p);
}

void discord_add_guild_member_params_init_v(void *p) {
  discord_add_guild_member_params_init((struct discord_add_guild_member_params *)p);
}

void discord_add_guild_member_params_free_v(void *p) {
 discord_add_guild_member_params_free((struct discord_add_guild_member_params *)p);
};

void discord_add_guild_member_params_from_json_v(char *json, size_t len, void *pp) {
 discord_add_guild_member_params_from_json(json, len, (struct discord_add_guild_member_params**)pp);
}

size_t discord_add_guild_member_params_to_json_v(char *json, size_t len, void *p) {
  return discord_add_guild_member_params_to_json(json, len, (struct discord_add_guild_member_params*)p);
}

void discord_add_guild_member_params_list_free_v(void **p) {
  discord_add_guild_member_params_list_free((struct discord_add_guild_member_params**)p);
}

void discord_add_guild_member_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_add_guild_member_params_list_from_json(str, len, (struct discord_add_guild_member_params ***)p);
}

size_t discord_add_guild_member_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_add_guild_member_params_list_to_json(str, len, (struct discord_add_guild_member_params **)p);
}


void discord_add_guild_member_params_cleanup(struct discord_add_guild_member_params *d) {
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->access_token)
    free(d->access_token);
  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->nick)
    free(d->nick);
  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  // p->mute is a scalar
  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  // p->deaf is a scalar
}

void discord_add_guild_member_params_init(struct discord_add_guild_member_params *p) {
  memset(p, 0, sizeof(struct discord_add_guild_member_params));
  /* specs/discord/guild.endpoints-params.json:104:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/guild.endpoints-params.json:105:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* specs/discord/guild.endpoints-params.json:106:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */

  /* specs/discord/guild.endpoints-params.json:107:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* specs/discord/guild.endpoints-params.json:108:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */

}
struct discord_add_guild_member_params* discord_add_guild_member_params_alloc() {
  struct discord_add_guild_member_params *p= malloc(sizeof(struct discord_add_guild_member_params));
  discord_add_guild_member_params_init(p);
  return p;
}

void discord_add_guild_member_params_free(struct discord_add_guild_member_params *p) {
  discord_add_guild_member_params_cleanup(p);
  free(p);
}

void discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **p) {
  ntl_free((void**)p, (vfvp)discord_add_guild_member_params_cleanup);
}

void discord_add_guild_member_params_list_from_json(char *str, size_t len, struct discord_add_guild_member_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_add_guild_member_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_add_guild_member_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_add_guild_member_params_list_to_json(char *str, size_t len, struct discord_add_guild_member_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_add_guild_member_params_to_json_v);
}


void discord_modify_guild_member_params_from_json(char *json, size_t len, struct discord_modify_guild_member_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_modify_guild_member_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):?s,"
  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(roles):F,"
  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mute):b,"
  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(deaf):b,"
  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                "(channel_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                &p->nick,
  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_from_json, &p->roles,
  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mute,
  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->deaf,
  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                cee_strtoull, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_member_params_use_default_inject_settings(struct discord_modify_guild_member_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[0] = p->nick;

  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->roles != NULL)
    p->__M.arg_switches[1] = p->roles;

  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->mute != false)
    p->__M.arg_switches[2] = &p->mute;

  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->deaf != false)
    p->__M.arg_switches[3] = &p->deaf;

  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  if (p->channel_id != 0)
    p->__M.arg_switches[4] = &p->channel_id;

}

size_t discord_modify_guild_member_params_to_json(char *json, size_t len, struct discord_modify_guild_member_params *p)
{
  size_t r;
  discord_modify_guild_member_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):s,"
  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(roles):F,"
  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mute):b,"
  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(deaf):b,"
  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                p->nick,
  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_to_json, p->roles,
  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mute,
  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->deaf,
  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                cee_ulltostr, &p->channel_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_member_params_cleanup_v(void *p) {
  discord_modify_guild_member_params_cleanup((struct discord_modify_guild_member_params *)p);
}

void discord_modify_guild_member_params_init_v(void *p) {
  discord_modify_guild_member_params_init((struct discord_modify_guild_member_params *)p);
}

void discord_modify_guild_member_params_free_v(void *p) {
 discord_modify_guild_member_params_free((struct discord_modify_guild_member_params *)p);
};

void discord_modify_guild_member_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_guild_member_params_from_json(json, len, (struct discord_modify_guild_member_params**)pp);
}

size_t discord_modify_guild_member_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_member_params_to_json(json, len, (struct discord_modify_guild_member_params*)p);
}

void discord_modify_guild_member_params_list_free_v(void **p) {
  discord_modify_guild_member_params_list_free((struct discord_modify_guild_member_params**)p);
}

void discord_modify_guild_member_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_member_params_list_from_json(str, len, (struct discord_modify_guild_member_params ***)p);
}

size_t discord_modify_guild_member_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_member_params_list_to_json(str, len, (struct discord_modify_guild_member_params **)p);
}


void discord_modify_guild_member_params_cleanup(struct discord_modify_guild_member_params *d) {
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  if (d->nick)
    free(d->nick);
  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  // p->mute is a scalar
  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  // p->deaf is a scalar
  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  // p->channel_id is a scalar
}

void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_member_params));
  /* specs/discord/guild.endpoints-params.json:118:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild.endpoints-params.json:119:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */

  /* specs/discord/guild.endpoints-params.json:120:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* specs/discord/guild.endpoints-params.json:121:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* specs/discord/guild.endpoints-params.json:122:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */

}
struct discord_modify_guild_member_params* discord_modify_guild_member_params_alloc() {
  struct discord_modify_guild_member_params *p= malloc(sizeof(struct discord_modify_guild_member_params));
  discord_modify_guild_member_params_init(p);
  return p;
}

void discord_modify_guild_member_params_free(struct discord_modify_guild_member_params *p) {
  discord_modify_guild_member_params_cleanup(p);
  free(p);
}

void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_member_params_cleanup);
}

void discord_modify_guild_member_params_list_from_json(char *str, size_t len, struct discord_modify_guild_member_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_member_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_guild_member_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_member_params_list_to_json(char *str, size_t len, struct discord_modify_guild_member_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_member_params_to_json_v);
}


void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_create_guild_role_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */
                "(permissions):s_as_hex_uint,"
  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(color):d,"
  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(hoist):b,"
  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mentionable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */
                &p->permissions,
  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->color,
  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->hoist,
  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mentionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_create_guild_role_params_use_default_inject_settings(struct discord_create_guild_role_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */
  if (p->permissions != 0)
    p->__M.arg_switches[1] = &p->permissions;

  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->color != 0)
    p->__M.arg_switches[2] = &p->color;

  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->hoist != false)
    p->__M.arg_switches[3] = &p->hoist;

  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->mentionable != false)
    p->__M.arg_switches[4] = &p->mentionable;

}

size_t discord_create_guild_role_params_to_json(char *json, size_t len, struct discord_create_guild_role_params *p)
{
  size_t r;
  discord_create_guild_role_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */
                "(permissions):s_as_hex_uint,"
  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(color):d,"
  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(hoist):b,"
  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mentionable):b,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */
                &p->permissions,
  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->color,
  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->hoist,
  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mentionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_guild_role_params_cleanup_v(void *p) {
  discord_create_guild_role_params_cleanup((struct discord_create_guild_role_params *)p);
}

void discord_create_guild_role_params_init_v(void *p) {
  discord_create_guild_role_params_init((struct discord_create_guild_role_params *)p);
}

void discord_create_guild_role_params_free_v(void *p) {
 discord_create_guild_role_params_free((struct discord_create_guild_role_params *)p);
};

void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *pp) {
 discord_create_guild_role_params_from_json(json, len, (struct discord_create_guild_role_params**)pp);
}

size_t discord_create_guild_role_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_role_params_to_json(json, len, (struct discord_create_guild_role_params*)p);
}

void discord_create_guild_role_params_list_free_v(void **p) {
  discord_create_guild_role_params_list_free((struct discord_create_guild_role_params**)p);
}

void discord_create_guild_role_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_role_params_list_from_json(str, len, (struct discord_create_guild_role_params ***)p);
}

size_t discord_create_guild_role_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_role_params_list_to_json(str, len, (struct discord_create_guild_role_params **)p);
}


void discord_create_guild_role_params_cleanup(struct discord_create_guild_role_params *d) {
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */
  // p->permissions is a scalar
  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->color is a scalar
  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
  // p->hoist is a scalar
  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
  // p->mentionable is a scalar
}

void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_role_params));
  /* specs/discord/guild.endpoints-params.json:132:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* specs/discord/guild.endpoints-params.json:133:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "inject_if_not":0}' */

  /* specs/discord/guild.endpoints-params.json:134:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/guild.endpoints-params.json:135:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* specs/discord/guild.endpoints-params.json:136:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */

}
struct discord_create_guild_role_params* discord_create_guild_role_params_alloc() {
  struct discord_create_guild_role_params *p= malloc(sizeof(struct discord_create_guild_role_params));
  discord_create_guild_role_params_init(p);
  return p;
}

void discord_create_guild_role_params_free(struct discord_create_guild_role_params *p) {
  discord_create_guild_role_params_cleanup(p);
  free(p);
}

void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_guild_role_params_cleanup);
}

void discord_create_guild_role_params_list_from_json(char *str, size_t len, struct discord_create_guild_role_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_role_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_create_guild_role_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_role_params_list_to_json(char *str, size_t len, struct discord_create_guild_role_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_create_guild_role_params_to_json_v);
}


void discord_modify_guild_role_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_role_positions_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_modify_guild_role_positions_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
                "(id):F,"
  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
                "(position):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
                cee_strtoull, &p->id,
  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
                &p->position,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_role_positions_params_use_default_inject_settings(struct discord_modify_guild_role_positions_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
  if (p->id != 0)
    p->__M.arg_switches[0] = &p->id;

  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
  if (p->position != 0)
    p->__M.arg_switches[1] = &p->position;

}

size_t discord_modify_guild_role_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p)
{
  size_t r;
  discord_modify_guild_role_positions_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
                "(id):|F|,"
  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
                "(position):d,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
                &p->position,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_role_positions_params_cleanup_v(void *p) {
  discord_modify_guild_role_positions_params_cleanup((struct discord_modify_guild_role_positions_params *)p);
}

void discord_modify_guild_role_positions_params_init_v(void *p) {
  discord_modify_guild_role_positions_params_init((struct discord_modify_guild_role_positions_params *)p);
}

void discord_modify_guild_role_positions_params_free_v(void *p) {
 discord_modify_guild_role_positions_params_free((struct discord_modify_guild_role_positions_params *)p);
};

void discord_modify_guild_role_positions_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_guild_role_positions_params_from_json(json, len, (struct discord_modify_guild_role_positions_params**)pp);
}

size_t discord_modify_guild_role_positions_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_role_positions_params_to_json(json, len, (struct discord_modify_guild_role_positions_params*)p);
}

void discord_modify_guild_role_positions_params_list_free_v(void **p) {
  discord_modify_guild_role_positions_params_list_free((struct discord_modify_guild_role_positions_params**)p);
}

void discord_modify_guild_role_positions_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_role_positions_params_list_from_json(str, len, (struct discord_modify_guild_role_positions_params ***)p);
}

size_t discord_modify_guild_role_positions_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_role_positions_params_list_to_json(str, len, (struct discord_modify_guild_role_positions_params **)p);
}


void discord_modify_guild_role_positions_params_cleanup(struct discord_modify_guild_role_positions_params *d) {
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
  // p->id is a scalar
  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
  // p->position is a scalar
}

void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_role_positions_params));
  /* specs/discord/guild.endpoints-params.json:146:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */

  /* specs/discord/guild.endpoints-params.json:147:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */

}
struct discord_modify_guild_role_positions_params* discord_modify_guild_role_positions_params_alloc() {
  struct discord_modify_guild_role_positions_params *p= malloc(sizeof(struct discord_modify_guild_role_positions_params));
  discord_modify_guild_role_positions_params_init(p);
  return p;
}

void discord_modify_guild_role_positions_params_free(struct discord_modify_guild_role_positions_params *p) {
  discord_modify_guild_role_positions_params_cleanup(p);
  free(p);
}

void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_role_positions_params_cleanup);
}

void discord_modify_guild_role_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_positions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_role_positions_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_guild_role_positions_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_role_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_positions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_role_positions_params_to_json_v);
}


void discord_modify_guild_role_params_from_json(char *json, size_t len, struct discord_modify_guild_role_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_modify_guild_role_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
                "(name):?s,"
  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
                "(permissions):s_as_hex_uint,"
  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
                "(color):d,"
  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
                "(hoist):b,"
  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
                "(mentionable):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
                &p->name,
  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
                &p->permissions,
  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
                &p->color,
  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
                &p->hoist,
  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
                &p->mentionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_modify_guild_role_params_use_default_inject_settings(struct discord_modify_guild_role_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
  if (p->permissions != 0)
    p->__M.arg_switches[1] = &p->permissions;

  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
  if (p->color != 0)
    p->__M.arg_switches[2] = &p->color;

  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
  if (p->hoist != false)
    p->__M.arg_switches[3] = &p->hoist;

  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
  if (p->mentionable != false)
    p->__M.arg_switches[4] = &p->mentionable;

}

size_t discord_modify_guild_role_params_to_json(char *json, size_t len, struct discord_modify_guild_role_params *p)
{
  size_t r;
  discord_modify_guild_role_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
                "(name):s,"
  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
                "(permissions):s_as_hex_uint,"
  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
                "(color):d,"
  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
                "(hoist):b,"
  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
                "(mentionable):b,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
                p->name,
  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
                &p->permissions,
  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
                &p->color,
  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
                &p->hoist,
  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
                &p->mentionable,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_role_params_cleanup_v(void *p) {
  discord_modify_guild_role_params_cleanup((struct discord_modify_guild_role_params *)p);
}

void discord_modify_guild_role_params_init_v(void *p) {
  discord_modify_guild_role_params_init((struct discord_modify_guild_role_params *)p);
}

void discord_modify_guild_role_params_free_v(void *p) {
 discord_modify_guild_role_params_free((struct discord_modify_guild_role_params *)p);
};

void discord_modify_guild_role_params_from_json_v(char *json, size_t len, void *pp) {
 discord_modify_guild_role_params_from_json(json, len, (struct discord_modify_guild_role_params**)pp);
}

size_t discord_modify_guild_role_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_role_params_to_json(json, len, (struct discord_modify_guild_role_params*)p);
}

void discord_modify_guild_role_params_list_free_v(void **p) {
  discord_modify_guild_role_params_list_free((struct discord_modify_guild_role_params**)p);
}

void discord_modify_guild_role_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_role_params_list_from_json(str, len, (struct discord_modify_guild_role_params ***)p);
}

size_t discord_modify_guild_role_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_role_params_list_to_json(str, len, (struct discord_modify_guild_role_params **)p);
}


void discord_modify_guild_role_params_cleanup(struct discord_modify_guild_role_params *d) {
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
  // p->permissions is a scalar
  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
  // p->color is a scalar
  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
  // p->hoist is a scalar
  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
  // p->mentionable is a scalar
}

void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_role_params));
  /* specs/discord/guild.endpoints-params.json:157:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */

  /* specs/discord/guild.endpoints-params.json:158:20
     '{ "name": "permissions", "type":{ "base":"s_as_hex_uint", "int_alias":"enum discord_permissions_bitwise_flags" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */

  /* specs/discord/guild.endpoints-params.json:159:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */

  /* specs/discord/guild.endpoints-params.json:160:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */

  /* specs/discord/guild.endpoints-params.json:161:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */

}
struct discord_modify_guild_role_params* discord_modify_guild_role_params_alloc() {
  struct discord_modify_guild_role_params *p= malloc(sizeof(struct discord_modify_guild_role_params));
  discord_modify_guild_role_params_init(p);
  return p;
}

void discord_modify_guild_role_params_free(struct discord_modify_guild_role_params *p) {
  discord_modify_guild_role_params_cleanup(p);
  free(p);
}

void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_role_params_cleanup);
}

void discord_modify_guild_role_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_role_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_modify_guild_role_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_role_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_modify_guild_role_params_to_json_v);
}


void discord_get_guild_prune_count_params_from_json(char *json, size_t len, struct discord_get_guild_prune_count_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_get_guild_prune_count_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(days):d,"
  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(include_roles):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->days,
  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_from_json, &p->include_roles,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_get_guild_prune_count_params_use_default_inject_settings(struct discord_get_guild_prune_count_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->days != 0)
    p->__M.arg_switches[0] = &p->days;

  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->include_roles != NULL)
    p->__M.arg_switches[1] = p->include_roles;

}

size_t discord_get_guild_prune_count_params_to_json(char *json, size_t len, struct discord_get_guild_prune_count_params *p)
{
  size_t r;
  discord_get_guild_prune_count_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(days):d,"
  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(include_roles):F,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->days,
  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_to_json, p->include_roles,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_get_guild_prune_count_params_cleanup_v(void *p) {
  discord_get_guild_prune_count_params_cleanup((struct discord_get_guild_prune_count_params *)p);
}

void discord_get_guild_prune_count_params_init_v(void *p) {
  discord_get_guild_prune_count_params_init((struct discord_get_guild_prune_count_params *)p);
}

void discord_get_guild_prune_count_params_free_v(void *p) {
 discord_get_guild_prune_count_params_free((struct discord_get_guild_prune_count_params *)p);
};

void discord_get_guild_prune_count_params_from_json_v(char *json, size_t len, void *pp) {
 discord_get_guild_prune_count_params_from_json(json, len, (struct discord_get_guild_prune_count_params**)pp);
}

size_t discord_get_guild_prune_count_params_to_json_v(char *json, size_t len, void *p) {
  return discord_get_guild_prune_count_params_to_json(json, len, (struct discord_get_guild_prune_count_params*)p);
}

void discord_get_guild_prune_count_params_list_free_v(void **p) {
  discord_get_guild_prune_count_params_list_free((struct discord_get_guild_prune_count_params**)p);
}

void discord_get_guild_prune_count_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_get_guild_prune_count_params_list_from_json(str, len, (struct discord_get_guild_prune_count_params ***)p);
}

size_t discord_get_guild_prune_count_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_get_guild_prune_count_params_list_to_json(str, len, (struct discord_get_guild_prune_count_params **)p);
}


void discord_get_guild_prune_count_params_cleanup(struct discord_get_guild_prune_count_params *d) {
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->days is a scalar
  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->include_roles)
    ja_u64_list_free(d->include_roles);
}

void discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params *p) {
  memset(p, 0, sizeof(struct discord_get_guild_prune_count_params));
  /* specs/discord/guild.endpoints-params.json:171:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/guild.endpoints-params.json:172:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */

}
struct discord_get_guild_prune_count_params* discord_get_guild_prune_count_params_alloc() {
  struct discord_get_guild_prune_count_params *p= malloc(sizeof(struct discord_get_guild_prune_count_params));
  discord_get_guild_prune_count_params_init(p);
  return p;
}

void discord_get_guild_prune_count_params_free(struct discord_get_guild_prune_count_params *p) {
  discord_get_guild_prune_count_params_cleanup(p);
  free(p);
}

void discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params **p) {
  ntl_free((void**)p, (vfvp)discord_get_guild_prune_count_params_cleanup);
}

void discord_get_guild_prune_count_params_list_from_json(char *str, size_t len, struct discord_get_guild_prune_count_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_get_guild_prune_count_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_get_guild_prune_count_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_get_guild_prune_count_params_list_to_json(char *str, size_t len, struct discord_get_guild_prune_count_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_get_guild_prune_count_params_to_json_v);
}


void discord_begin_guild_prune_params_from_json(char *json, size_t len, struct discord_begin_guild_prune_params **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_begin_guild_prune_params *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(days):d,"
  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(compute_prune_count):b,"
  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(include_roles):F,"
  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(reason):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->days,
  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->compute_prune_count,
  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_from_json, &p->include_roles,
  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->reason,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_begin_guild_prune_params_use_default_inject_settings(struct discord_begin_guild_prune_params *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->days != 0)
    p->__M.arg_switches[0] = &p->days;

  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->compute_prune_count != false)
    p->__M.arg_switches[1] = &p->compute_prune_count;

  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->include_roles != NULL)
    p->__M.arg_switches[2] = p->include_roles;

  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->reason != NULL)
    p->__M.arg_switches[3] = p->reason;

}

size_t discord_begin_guild_prune_params_to_json(char *json, size_t len, struct discord_begin_guild_prune_params *p)
{
  size_t r;
  discord_begin_guild_prune_params_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(days):d,"
  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(compute_prune_count):b,"
  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(include_roles):F,"
  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(reason):s,"
                "@arg_switches:b",
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->days,
  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->compute_prune_count,
  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_to_json, p->include_roles,
  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->reason,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_begin_guild_prune_params_cleanup_v(void *p) {
  discord_begin_guild_prune_params_cleanup((struct discord_begin_guild_prune_params *)p);
}

void discord_begin_guild_prune_params_init_v(void *p) {
  discord_begin_guild_prune_params_init((struct discord_begin_guild_prune_params *)p);
}

void discord_begin_guild_prune_params_free_v(void *p) {
 discord_begin_guild_prune_params_free((struct discord_begin_guild_prune_params *)p);
};

void discord_begin_guild_prune_params_from_json_v(char *json, size_t len, void *pp) {
 discord_begin_guild_prune_params_from_json(json, len, (struct discord_begin_guild_prune_params**)pp);
}

size_t discord_begin_guild_prune_params_to_json_v(char *json, size_t len, void *p) {
  return discord_begin_guild_prune_params_to_json(json, len, (struct discord_begin_guild_prune_params*)p);
}

void discord_begin_guild_prune_params_list_free_v(void **p) {
  discord_begin_guild_prune_params_list_free((struct discord_begin_guild_prune_params**)p);
}

void discord_begin_guild_prune_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_begin_guild_prune_params_list_from_json(str, len, (struct discord_begin_guild_prune_params ***)p);
}

size_t discord_begin_guild_prune_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_begin_guild_prune_params_list_to_json(str, len, (struct discord_begin_guild_prune_params **)p);
}


void discord_begin_guild_prune_params_cleanup(struct discord_begin_guild_prune_params *d) {
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  // p->days is a scalar
  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
  // p->compute_prune_count is a scalar
  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->include_roles)
    ja_u64_list_free(d->include_roles);
  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->reason)
    free(d->reason);
}

void discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params *p) {
  memset(p, 0, sizeof(struct discord_begin_guild_prune_params));
  /* specs/discord/guild.endpoints-params.json:182:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* specs/discord/guild.endpoints-params.json:183:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* specs/discord/guild.endpoints-params.json:184:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */

  /* specs/discord/guild.endpoints-params.json:185:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

}
struct discord_begin_guild_prune_params* discord_begin_guild_prune_params_alloc() {
  struct discord_begin_guild_prune_params *p= malloc(sizeof(struct discord_begin_guild_prune_params));
  discord_begin_guild_prune_params_init(p);
  return p;
}

void discord_begin_guild_prune_params_free(struct discord_begin_guild_prune_params *p) {
  discord_begin_guild_prune_params_cleanup(p);
  free(p);
}

void discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **p) {
  ntl_free((void**)p, (vfvp)discord_begin_guild_prune_params_cleanup);
}

void discord_begin_guild_prune_params_list_from_json(char *str, size_t len, struct discord_begin_guild_prune_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_begin_guild_prune_params);
  d.init_elem = NULL;
  d.elem_from_buf = discord_begin_guild_prune_params_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_begin_guild_prune_params_list_to_json(char *str, size_t len, struct discord_begin_guild_prune_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_begin_guild_prune_params_to_json_v);
}

