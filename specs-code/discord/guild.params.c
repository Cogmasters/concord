/* This file is generated from discord/guild.params.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild.params.c
 * @see https://discord.com/developers/docs/resources/guild
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_create_guild_params_from_json_p(char *json, size_t len, struct discord_create_guild_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_guild_params_from_json(json, len, *pp);
}
void discord_create_guild_params_from_json(char *json, size_t len, struct discord_create_guild_params *p)
{
  discord_create_guild_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                "(name):?s,"
  /* discord/guild.params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                "(region):?s,"
  /* discord/guild.params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                "(icon):?s,"
  /* discord/guild.params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                "(verification_level):d,"
  /* discord/guild.params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                "(default_message_notifications):d,"
  /* discord/guild.params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                "(explicit_content_filter):d,"
  /* discord/guild.params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */
                "(roles):F,"
  /* discord/guild.params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
                "(channels):F,"
  /* discord/guild.params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                "(afk_channel_id):F,"
  /* discord/guild.params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                "(afk_timeout):d,"
  /* discord/guild.params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                "(system_channel_id):F,",
  /* discord/guild.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                &p->name,
  /* discord/guild.params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                &p->region,
  /* discord/guild.params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                &p->icon,
  /* discord/guild.params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                &p->verification_level,
  /* discord/guild.params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                &p->default_message_notifications,
  /* discord/guild.params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                &p->explicit_content_filter,
  /* discord/guild.params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */
                discord_role_list_from_json, &p->roles,
  /* discord/guild.params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
                discord_channel_list_from_json, &p->channels,
  /* discord/guild.params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                cee_strtou64, &p->afk_channel_id,
  /* discord/guild.params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                &p->afk_timeout,
  /* discord/guild.params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                cee_strtou64, &p->system_channel_id);
}

size_t discord_create_guild_params_to_json(char *json, size_t len, struct discord_create_guild_params *p)
{
  size_t r;
  void *arg_switches[11]={NULL};
  /* discord/guild.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  arg_switches[0] = p->name;

  /* discord/guild.params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  if (p->region != NULL)
    arg_switches[1] = p->region;

  /* discord/guild.params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  if (p->icon != NULL)
    arg_switches[2] = p->icon;

  /* discord/guild.params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  if (p->verification_level != 0)
    arg_switches[3] = &p->verification_level;

  /* discord/guild.params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  if (p->default_message_notifications != 0)
    arg_switches[4] = &p->default_message_notifications;

  /* discord/guild.params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  if (p->explicit_content_filter != 0)
    arg_switches[5] = &p->explicit_content_filter;

  /* discord/guild.params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */
  if (p->roles != NULL)
    arg_switches[6] = p->roles;

  /* discord/guild.params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
  if (p->channels != NULL)
    arg_switches[7] = p->channels;

  /* discord/guild.params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  if (p->afk_channel_id != 0)
    arg_switches[8] = &p->afk_channel_id;

  /* discord/guild.params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  if (p->afk_timeout != 0)
    arg_switches[9] = &p->afk_timeout;

  /* discord/guild.params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  if (p->system_channel_id != 0)
    arg_switches[10] = &p->system_channel_id;

  r=json_inject(json, len, 
  /* discord/guild.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                "(name):s,"
  /* discord/guild.params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                "(region):s,"
  /* discord/guild.params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                "(icon):s,"
  /* discord/guild.params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                "(verification_level):d,"
  /* discord/guild.params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                "(default_message_notifications):d,"
  /* discord/guild.params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                "(explicit_content_filter):d,"
  /* discord/guild.params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */
                "(roles):F,"
  /* discord/guild.params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
                "(channels):F,"
  /* discord/guild.params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                "(afk_channel_id):|F|,"
  /* discord/guild.params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                "(afk_timeout):d,"
  /* discord/guild.params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                "(system_channel_id):|F|,"
                "@arg_switches:b",
  /* discord/guild.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                p->name,
  /* discord/guild.params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                p->region,
  /* discord/guild.params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                p->icon,
  /* discord/guild.params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                &p->verification_level,
  /* discord/guild.params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                &p->default_message_notifications,
  /* discord/guild.params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                &p->explicit_content_filter,
  /* discord/guild.params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */
                discord_role_list_to_json, p->roles,
  /* discord/guild.params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
                discord_channel_list_to_json, p->channels,
  /* discord/guild.params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                cee_u64tostr, &p->afk_channel_id,
  /* discord/guild.params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                &p->afk_timeout,
  /* discord/guild.params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                cee_u64tostr, &p->system_channel_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_guild_params_cleanup_v(void *p) {
  discord_create_guild_params_cleanup((struct discord_create_guild_params *)p);
}

void discord_create_guild_params_init_v(void *p) {
  discord_create_guild_params_init((struct discord_create_guild_params *)p);
}

void discord_create_guild_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_params_from_json(json, len, (struct discord_create_guild_params*)p);
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
  /* discord/guild.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  if (d->name)
    free(d->name);
  /* discord/guild.params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  if (d->region)
    free(d->region);
  /* discord/guild.params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  if (d->icon)
    free(d->icon);
  /* discord/guild.params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  (void)d->verification_level;
  /* discord/guild.params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  (void)d->default_message_notifications;
  /* discord/guild.params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  (void)d->explicit_content_filter;
  /* discord/guild.params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */
  if (d->roles)
    discord_role_list_free(d->roles);
  /* discord/guild.params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */
  if (d->channels)
    discord_channel_list_free(d->channels);
  /* discord/guild.params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  (void)d->afk_channel_id;
  /* discord/guild.params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  (void)d->afk_timeout;
  /* discord/guild.params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  (void)d->system_channel_id;
}

void discord_create_guild_params_init(struct discord_create_guild_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_params));
  /* discord/guild.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */

  /* discord/guild.params.json:13:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */

  /* discord/guild.params.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */

  /* discord/guild.params.json:15:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */

  /* discord/guild.params.json:16:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */

  /* discord/guild.params.json:17:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */

  /* discord/guild.params.json:18:20
     '{ "name": "roles", "type":{ "base":"struct discord_role", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"new guild roles" }' */

  /* discord/guild.params.json:19:20
     '{ "name": "channels", "type":{ "base":"struct discord_channel", "dec":"ntl" }, "option":true, "inject_if_not":null, "comment":"array of partial channel objects"}' */

  /* discord/guild.params.json:20:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */

  /* discord/guild.params.json:21:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */

  /* discord/guild.params.json:22:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where guild notices such as welcome messages and boost events are posted"}' */

}
void discord_create_guild_params_list_free(struct discord_create_guild_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_guild_params_cleanup);
}

void discord_create_guild_params_list_from_json(char *str, size_t len, struct discord_create_guild_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_guild_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_params_list_to_json(char *str, size_t len, struct discord_create_guild_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_guild_params_to_json);
}


void discord_modify_guild_params_from_json_p(char *json, size_t len, struct discord_modify_guild_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_guild_params_from_json(json, len, *pp);
}
void discord_modify_guild_params_from_json(char *json, size_t len, struct discord_modify_guild_params *p)
{
  discord_modify_guild_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                "(name):?s,"
  /* discord/guild.params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                "(region):?s,"
  /* discord/guild.params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                "(verification_level):d,"
  /* discord/guild.params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                "(default_message_notifications):d,"
  /* discord/guild.params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                "(explicit_content_filter):d,"
  /* discord/guild.params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                "(afk_channel_id):F,"
  /* discord/guild.params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                "(afk_timeout):d,"
  /* discord/guild.params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                "(icon):?s,"
  /* discord/guild.params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
                "(owner_id):F,"
  /* discord/guild.params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
                "(splash):?s,"
  /* discord/guild.params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
                "(discovery_splash):?s,"
  /* discord/guild.params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
                "(banner):?s,"
  /* discord/guild.params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                "(system_channel_id):F,"
  /* discord/guild.params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
                "(system_channel_flags):d,"
  /* discord/guild.params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
                "(rules_channel_id):F,"
  /* discord/guild.params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
                "(public_updates_channel_id):F,"
  /* discord/guild.params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
                "(preferred_locale):?s,"
  /* discord/guild.params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */
                "(features):F,"
  /* discord/guild.params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
                "(description):?s,",
  /* discord/guild.params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                &p->name,
  /* discord/guild.params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                &p->region,
  /* discord/guild.params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                &p->verification_level,
  /* discord/guild.params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                &p->default_message_notifications,
  /* discord/guild.params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                &p->explicit_content_filter,
  /* discord/guild.params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                cee_strtou64, &p->afk_channel_id,
  /* discord/guild.params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                &p->afk_timeout,
  /* discord/guild.params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                &p->icon,
  /* discord/guild.params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
                cee_strtou64, &p->owner_id,
  /* discord/guild.params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
                &p->splash,
  /* discord/guild.params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
                &p->discovery_splash,
  /* discord/guild.params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
                &p->banner,
  /* discord/guild.params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                cee_strtou64, &p->system_channel_id,
  /* discord/guild.params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
                &p->system_channel_flags,
  /* discord/guild.params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
                cee_strtou64, &p->rules_channel_id,
  /* discord/guild.params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
                cee_strtou64, &p->public_updates_channel_id,
  /* discord/guild.params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
                &p->preferred_locale,
  /* discord/guild.params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */
                ja_str_list_from_json, &p->features,
  /* discord/guild.params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
                &p->description);
}

size_t discord_modify_guild_params_to_json(char *json, size_t len, struct discord_modify_guild_params *p)
{
  size_t r;
  void *arg_switches[19]={NULL};
  /* discord/guild.params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  arg_switches[0] = p->name;

  /* discord/guild.params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  if (p->region != NULL)
    arg_switches[1] = p->region;

  /* discord/guild.params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  if (p->verification_level != 0)
    arg_switches[2] = &p->verification_level;

  /* discord/guild.params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  if (p->default_message_notifications != 0)
    arg_switches[3] = &p->default_message_notifications;

  /* discord/guild.params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  if (p->explicit_content_filter != 0)
    arg_switches[4] = &p->explicit_content_filter;

  /* discord/guild.params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  if (p->afk_channel_id != 0)
    arg_switches[5] = &p->afk_channel_id;

  /* discord/guild.params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  if (p->afk_timeout != 0)
    arg_switches[6] = &p->afk_timeout;

  /* discord/guild.params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  if (p->icon != NULL)
    arg_switches[7] = p->icon;

  /* discord/guild.params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
  if (p->owner_id != 0)
    arg_switches[8] = &p->owner_id;

  /* discord/guild.params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
  if (p->splash != NULL)
    arg_switches[9] = p->splash;

  /* discord/guild.params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
  if (p->discovery_splash != NULL)
    arg_switches[10] = p->discovery_splash;

  /* discord/guild.params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
  if (p->banner != NULL)
    arg_switches[11] = p->banner;

  /* discord/guild.params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  if (p->system_channel_id != 0)
    arg_switches[12] = &p->system_channel_id;

  /* discord/guild.params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
  if (p->system_channel_flags != 0)
    arg_switches[13] = &p->system_channel_flags;

  /* discord/guild.params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
  if (p->rules_channel_id != 0)
    arg_switches[14] = &p->rules_channel_id;

  /* discord/guild.params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
  if (p->public_updates_channel_id != 0)
    arg_switches[15] = &p->public_updates_channel_id;

  /* discord/guild.params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
  arg_switches[16] = p->preferred_locale;

  /* discord/guild.params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */
  arg_switches[17] = p->features;

  /* discord/guild.params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
  arg_switches[18] = p->description;

  r=json_inject(json, len, 
  /* discord/guild.params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                "(name):s,"
  /* discord/guild.params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                "(region):s,"
  /* discord/guild.params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                "(verification_level):d,"
  /* discord/guild.params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                "(default_message_notifications):d,"
  /* discord/guild.params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                "(explicit_content_filter):d,"
  /* discord/guild.params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                "(afk_channel_id):|F|,"
  /* discord/guild.params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                "(afk_timeout):d,"
  /* discord/guild.params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                "(icon):s,"
  /* discord/guild.params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
                "(owner_id):|F|,"
  /* discord/guild.params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
                "(splash):s,"
  /* discord/guild.params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
                "(discovery_splash):s,"
  /* discord/guild.params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
                "(banner):s,"
  /* discord/guild.params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                "(system_channel_id):|F|,"
  /* discord/guild.params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
                "(system_channel_flags):d,"
  /* discord/guild.params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
                "(rules_channel_id):|F|,"
  /* discord/guild.params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
                "(public_updates_channel_id):|F|,"
  /* discord/guild.params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
                "(preferred_locale):s,"
  /* discord/guild.params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */
                "(features):F,"
  /* discord/guild.params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
                "(description):s,"
                "@arg_switches:b",
  /* discord/guild.params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
                p->name,
  /* discord/guild.params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
                p->region,
  /* discord/guild.params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
                &p->verification_level,
  /* discord/guild.params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
                &p->default_message_notifications,
  /* discord/guild.params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
                &p->explicit_content_filter,
  /* discord/guild.params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
                cee_u64tostr, &p->afk_channel_id,
  /* discord/guild.params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
                &p->afk_timeout,
  /* discord/guild.params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
                p->icon,
  /* discord/guild.params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
                cee_u64tostr, &p->owner_id,
  /* discord/guild.params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
                p->splash,
  /* discord/guild.params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
                p->discovery_splash,
  /* discord/guild.params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
                p->banner,
  /* discord/guild.params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
                cee_u64tostr, &p->system_channel_id,
  /* discord/guild.params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
                &p->system_channel_flags,
  /* discord/guild.params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
                cee_u64tostr, &p->rules_channel_id,
  /* discord/guild.params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
                cee_u64tostr, &p->public_updates_channel_id,
  /* discord/guild.params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
                p->preferred_locale,
  /* discord/guild.params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */
                ja_str_list_to_json, p->features,
  /* discord/guild.params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
                p->description,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_modify_guild_params_cleanup_v(void *p) {
  discord_modify_guild_params_cleanup((struct discord_modify_guild_params *)p);
}

void discord_modify_guild_params_init_v(void *p) {
  discord_modify_guild_params_init((struct discord_modify_guild_params *)p);
}

void discord_modify_guild_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_params_from_json(json, len, (struct discord_modify_guild_params*)p);
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
  /* discord/guild.params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */
  if (d->name)
    free(d->name);
  /* discord/guild.params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */
  if (d->region)
    free(d->region);
  /* discord/guild.params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */
  (void)d->verification_level;
  /* discord/guild.params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */
  (void)d->default_message_notifications;
  /* discord/guild.params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */
  (void)d->explicit_content_filter;
  /* discord/guild.params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */
  (void)d->afk_channel_id;
  /* discord/guild.params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */
  (void)d->afk_timeout;
  /* discord/guild.params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */
  if (d->icon)
    free(d->icon);
  /* discord/guild.params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */
  (void)d->owner_id;
  /* discord/guild.params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */
  if (d->splash)
    free(d->splash);
  /* discord/guild.params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */
  if (d->discovery_splash)
    free(d->discovery_splash);
  /* discord/guild.params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */
  if (d->banner)
    free(d->banner);
  /* discord/guild.params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */
  (void)d->system_channel_id;
  /* discord/guild.params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */
  (void)d->system_channel_flags;
  /* discord/guild.params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */
  (void)d->rules_channel_id;
  /* discord/guild.params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */
  (void)d->public_updates_channel_id;
  /* discord/guild.params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */
  if (d->preferred_locale)
    free(d->preferred_locale);
  /* discord/guild.params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */
  if (d->features)
    ja_str_list_free(d->features);
  /* discord/guild.params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */
  if (d->description)
    free(d->description);
}

void discord_modify_guild_params_init(struct discord_modify_guild_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_params));
  /* discord/guild.params.json:31:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the guild (2-100) characters"}' */

  /* discord/guild.params.json:32:20
     '{ "name": "region", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"voice region id" }' */

  /* discord/guild.params.json:33:20
     '{ "name": "verification_level", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"verification level"}' */

  /* discord/guild.params.json:34:20
     '{ "name": "default_message_notifications", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"default message notification level"}' */

  /* discord/guild.params.json:35:20
     '{ "name": "explicit_content_filter", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"explicit content filter level"}' */

  /* discord/guild.params.json:36:20
     '{ "name": "afk_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"id for afk channel"}' */

  /* discord/guild.params.json:37:20
     '{ "name": "afk_timeout", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"afk timeout in seconds"}' */

  /* discord/guild.params.json:38:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 128x1128 image for the guild icon"}' */

  /* discord/guild.params.json:39:20
     '{ "name": "owner_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"user id to transfer guild ownership to (must be owner)"}' */

  /* discord/guild.params.json:40:20
     '{ "name": "splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild splash (when the server has the INVITE_SPLASH feature"}' */

  /* discord/guild.params.json:41:20
     '{ "name": "discovery_splash", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"base64 16:9 png/jpeg image for the guild discovery splash (when the server has the DISCOVERABLE feature)"}' */

  /* discord/guild.params.json:42:20
     '{ "name": "banner", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"	base64 16:9 png/jpeg image for the guild banner (when the server has the BANNER feature)"}' */

  /* discord/guild.params.json:43:20
     '{ "name": "system_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"	the id of the channel where guild notices such as welcome messages and boost events are posted"}' */

  /* discord/guild.params.json:44:20
     '{ "name": "system_channel_flags", "type":{ "base":"int", "int_alias":"enum discord_system_channel_flags" }, "option":true, "inject_if_not":0, "comment":"system channel flags"}' */

  /* discord/guild.params.json:45:20
     '{ "name": "rules_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where Community guilds display rules and/or guidelines"}' */

  /* discord/guild.params.json:46:20
     '{ "name": "public_updates_channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the id of the channel where admins and moderators of Community guilds receive notices from Discord"}' */

  /* discord/guild.params.json:47:20
     '{ "name": "preferred_locale", "type":{ "base":"char", "dec":"*" }, "comment":"the preferred locale of a Community guild used in server discovery and notices from Discord; defaults to \"en-US\""}' */

  /* discord/guild.params.json:48:18
     '{"name":"features", "type": { "base":"ja_str", "dec":"ntl" }, "comment":"array of guild feature strings"}' */

  /* discord/guild.params.json:49:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"the description for the guild, if the guild is discoverable"}' */

}
void discord_modify_guild_params_list_free(struct discord_modify_guild_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_modify_guild_params_cleanup);
}

void discord_modify_guild_params_list_from_json(char *str, size_t len, struct discord_modify_guild_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_modify_guild_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_params_list_to_json(char *str, size_t len, struct discord_modify_guild_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_modify_guild_params_to_json);
}


void discord_create_guild_channel_params_from_json_p(char *json, size_t len, struct discord_create_guild_channel_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_guild_channel_params_from_json(json, len, *pp);
}
void discord_create_guild_channel_params_from_json(char *json, size_t len, struct discord_create_guild_channel_params *p)
{
  discord_create_guild_channel_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* discord/guild.params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* discord/guild.params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
                "(topic):?s,"
  /* discord/guild.params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(bitrate):d,"
  /* discord/guild.params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(user_limit):d,"
  /* discord/guild.params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(rate_limit_per_user):d,"
  /* discord/guild.params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */
                "(position):d,"
  /* discord/guild.params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
                "(permission_overwrites):F,"
  /* discord/guild.params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                "(parent_id):F,"
  /* discord/guild.params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
                "(nsfw):b,",
  /* discord/guild.params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* discord/guild.params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* discord/guild.params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
                &p->topic,
  /* discord/guild.params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->bitrate,
  /* discord/guild.params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->user_limit,
  /* discord/guild.params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->rate_limit_per_user,
  /* discord/guild.params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */
                &p->position,
  /* discord/guild.params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
                discord_overwrite_list_from_json, &p->permission_overwrites,
  /* discord/guild.params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                cee_strtou64, &p->parent_id,
  /* discord/guild.params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
                &p->nsfw);
}

size_t discord_create_guild_channel_params_to_json(char *json, size_t len, struct discord_create_guild_channel_params *p)
{
  size_t r;
  void *arg_switches[10]={NULL};
  /* discord/guild.params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->name;

  /* discord/guild.params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  arg_switches[1] = &p->type;

  /* discord/guild.params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[2] = p->topic;

  /* discord/guild.params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->bitrate != 0)
    arg_switches[3] = &p->bitrate;

  /* discord/guild.params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->user_limit != 0)
    arg_switches[4] = &p->user_limit;

  /* discord/guild.params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->rate_limit_per_user != 0)
    arg_switches[5] = &p->rate_limit_per_user;

  /* discord/guild.params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */
  arg_switches[6] = &p->position;

  /* discord/guild.params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->permission_overwrites != NULL)
    arg_switches[7] = p->permission_overwrites;

  /* discord/guild.params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  if (p->parent_id != 0)
    arg_switches[8] = &p->parent_id;

  /* discord/guild.params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
  arg_switches[9] = &p->nsfw;

  r=json_inject(json, len, 
  /* discord/guild.params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* discord/guild.params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                "(type):d,"
  /* discord/guild.params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
                "(topic):s,"
  /* discord/guild.params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(bitrate):d,"
  /* discord/guild.params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(user_limit):d,"
  /* discord/guild.params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(rate_limit_per_user):d,"
  /* discord/guild.params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */
                "(position):d,"
  /* discord/guild.params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
                "(permission_overwrites):F,"
  /* discord/guild.params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                "(parent_id):|F|,"
  /* discord/guild.params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
                "(nsfw):b,"
                "@arg_switches:b",
  /* discord/guild.params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* discord/guild.params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */
                &p->type,
  /* discord/guild.params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
                p->topic,
  /* discord/guild.params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->bitrate,
  /* discord/guild.params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->user_limit,
  /* discord/guild.params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->rate_limit_per_user,
  /* discord/guild.params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */
                &p->position,
  /* discord/guild.params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
                discord_overwrite_list_to_json, p->permission_overwrites,
  /* discord/guild.params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                cee_u64tostr, &p->parent_id,
  /* discord/guild.params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
                &p->nsfw,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_guild_channel_params_cleanup_v(void *p) {
  discord_create_guild_channel_params_cleanup((struct discord_create_guild_channel_params *)p);
}

void discord_create_guild_channel_params_init_v(void *p) {
  discord_create_guild_channel_params_init((struct discord_create_guild_channel_params *)p);
}

void discord_create_guild_channel_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_channel_params_from_json(json, len, (struct discord_create_guild_channel_params*)p);
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
  /* discord/guild.params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* discord/guild.params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */
  (void)d->type;
  /* discord/guild.params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */
  if (d->topic)
    free(d->topic);
  /* discord/guild.params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->bitrate;
  /* discord/guild.params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->user_limit;
  /* discord/guild.params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->rate_limit_per_user;
  /* discord/guild.params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */
  (void)d->position;
  /* discord/guild.params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->permission_overwrites)
    discord_overwrite_list_free(d->permission_overwrites);
  /* discord/guild.params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  (void)d->parent_id;
  /* discord/guild.params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */
  (void)d->nsfw;
}

void discord_create_guild_channel_params_init(struct discord_create_guild_channel_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_channel_params));
  /* discord/guild.params.json:58:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/guild.params.json:59:20
     '{ "name": "type", "type":{ "base":"int" }}' */

  /* discord/guild.params.json:60:20
     '{ "name": "topic", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/guild.params.json:61:20
     '{ "name": "bitrate", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/guild.params.json:62:20
     '{ "name": "user_limit", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/guild.params.json:63:20
     '{ "name": "rate_limit_per_user", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/guild.params.json:64:20
     '{ "name": "position", "type":{ "base":"int" } }' */

  /* discord/guild.params.json:65:20
     '{ "name": "permission_overwrites", "type":{ "base":"struct discord_overwrite", "dec":"ntl" }, "inject_if_not":null}' */

  /* discord/guild.params.json:66:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */

  /* discord/guild.params.json:67:20
     '{ "name": "nsfw", "type":{ "base":"bool" }}' */

}
void discord_create_guild_channel_params_list_free(struct discord_create_guild_channel_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_guild_channel_params_cleanup);
}

void discord_create_guild_channel_params_list_from_json(char *str, size_t len, struct discord_create_guild_channel_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_channel_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_guild_channel_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_channel_params_list_to_json(char *str, size_t len, struct discord_create_guild_channel_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_guild_channel_params_to_json);
}


void discord_modify_guild_channel_positions_params_from_json_p(char *json, size_t len, struct discord_modify_guild_channel_positions_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_guild_channel_positions_params_from_json(json, len, *pp);
}
void discord_modify_guild_channel_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p)
{
  discord_modify_guild_channel_positions_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
                "(id):F,"
  /* discord/guild.params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
                "(position):d,"
  /* discord/guild.params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
                "(lock_permissions):b,"
  /* discord/guild.params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
                "(parent_id):F,",
  /* discord/guild.params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
                cee_strtou64, &p->id,
  /* discord/guild.params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
                &p->position,
  /* discord/guild.params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
                &p->lock_permissions,
  /* discord/guild.params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
                cee_strtou64, &p->parent_id);
}

size_t discord_modify_guild_channel_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_channel_positions_params *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/guild.params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
  if (p->id != 0)
    arg_switches[0] = &p->id;

  /* discord/guild.params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
  if (p->position != 0)
    arg_switches[1] = &p->position;

  /* discord/guild.params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
  if (p->lock_permissions != false)
    arg_switches[2] = &p->lock_permissions;

  /* discord/guild.params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
  if (p->parent_id != 0)
    arg_switches[3] = &p->parent_id;

  r=json_inject(json, len, 
  /* discord/guild.params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
                "(id):|F|,"
  /* discord/guild.params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
                "(position):d,"
  /* discord/guild.params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
                "(lock_permissions):b,"
  /* discord/guild.params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
                "(parent_id):|F|,"
                "@arg_switches:b",
  /* discord/guild.params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
                cee_u64tostr, &p->id,
  /* discord/guild.params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
                &p->position,
  /* discord/guild.params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
                &p->lock_permissions,
  /* discord/guild.params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
                cee_u64tostr, &p->parent_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_modify_guild_channel_positions_params_cleanup_v(void *p) {
  discord_modify_guild_channel_positions_params_cleanup((struct discord_modify_guild_channel_positions_params *)p);
}

void discord_modify_guild_channel_positions_params_init_v(void *p) {
  discord_modify_guild_channel_positions_params_init((struct discord_modify_guild_channel_positions_params *)p);
}

void discord_modify_guild_channel_positions_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_channel_positions_params_from_json(json, len, (struct discord_modify_guild_channel_positions_params*)p);
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
  /* discord/guild.params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */
  (void)d->id;
  /* discord/guild.params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */
  (void)d->position;
  /* discord/guild.params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */
  (void)d->lock_permissions;
  /* discord/guild.params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */
  (void)d->parent_id;
}

void discord_modify_guild_channel_positions_params_init(struct discord_modify_guild_channel_positions_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_channel_positions_params));
  /* discord/guild.params.json:76:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"channel id"}' */

  /* discord/guild.params.json:77:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the channel"}' */

  /* discord/guild.params.json:78:20
     '{ "name": "lock_permissions", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"syncs the permission overwrites with the new parent, if moving to a new category"}' */

  /* discord/guild.params.json:79:20
     '{ "name": "parent_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"the new parent ID for the channel that is moved"}' */

}
void discord_modify_guild_channel_positions_params_list_free(struct discord_modify_guild_channel_positions_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_modify_guild_channel_positions_params_cleanup);
}

void discord_modify_guild_channel_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_channel_positions_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_modify_guild_channel_positions_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_channel_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_channel_positions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_modify_guild_channel_positions_params_to_json);
}


void discord_list_guild_members_params_from_json_p(char *json, size_t len, struct discord_list_guild_members_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_list_guild_members_params_from_json(json, len, *pp);
}
void discord_list_guild_members_params_from_json(char *json, size_t len, struct discord_list_guild_members_params *p)
{
  discord_list_guild_members_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */
                "(limit):d,"
  /* discord/guild.params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */
                "(after):F,",
  /* discord/guild.params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */
                &p->limit,
  /* discord/guild.params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */
                cee_strtou64, &p->after);
}

size_t discord_list_guild_members_params_to_json(char *json, size_t len, struct discord_list_guild_members_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/guild.params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */
  if (p->limit != 0)
    arg_switches[0] = &p->limit;

  /* discord/guild.params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */
  if (p->after != 0)
    arg_switches[1] = &p->after;

  r=json_inject(json, len, 
  /* discord/guild.params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */
                "(limit):d,"
  /* discord/guild.params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */
                "(after):|F|,"
                "@arg_switches:b",
  /* discord/guild.params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */
                &p->limit,
  /* discord/guild.params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */
                cee_u64tostr, &p->after,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_list_guild_members_params_cleanup_v(void *p) {
  discord_list_guild_members_params_cleanup((struct discord_list_guild_members_params *)p);
}

void discord_list_guild_members_params_init_v(void *p) {
  discord_list_guild_members_params_init((struct discord_list_guild_members_params *)p);
}

void discord_list_guild_members_params_from_json_v(char *json, size_t len, void *p) {
 discord_list_guild_members_params_from_json(json, len, (struct discord_list_guild_members_params*)p);
}

size_t discord_list_guild_members_params_to_json_v(char *json, size_t len, void *p) {
  return discord_list_guild_members_params_to_json(json, len, (struct discord_list_guild_members_params*)p);
}

void discord_list_guild_members_params_list_free_v(void **p) {
  discord_list_guild_members_params_list_free((struct discord_list_guild_members_params**)p);
}

void discord_list_guild_members_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_list_guild_members_params_list_from_json(str, len, (struct discord_list_guild_members_params ***)p);
}

size_t discord_list_guild_members_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_list_guild_members_params_list_to_json(str, len, (struct discord_list_guild_members_params **)p);
}


void discord_list_guild_members_params_cleanup(struct discord_list_guild_members_params *d) {
  /* discord/guild.params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */
  (void)d->limit;
  /* discord/guild.params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */
  (void)d->after;
}

void discord_list_guild_members_params_init(struct discord_list_guild_members_params *p) {
  memset(p, 0, sizeof(struct discord_list_guild_members_params));
  /* discord/guild.params.json:88:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max numbers of members to return (1-1000)", "default_value":1 }' */

  /* discord/guild.params.json:89:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0, "comment": "the highest user id in the previous page"}' */

}
void discord_list_guild_members_params_list_free(struct discord_list_guild_members_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_list_guild_members_params_cleanup);
}

void discord_list_guild_members_params_list_from_json(char *str, size_t len, struct discord_list_guild_members_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_list_guild_members_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_list_guild_members_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_list_guild_members_params_list_to_json(char *str, size_t len, struct discord_list_guild_members_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_list_guild_members_params_to_json);
}


void discord_search_guild_members_params_from_json_p(char *json, size_t len, struct discord_search_guild_members_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_search_guild_members_params_from_json(json, len, *pp);
}
void discord_search_guild_members_params_from_json(char *json, size_t len, struct discord_search_guild_members_params *p)
{
  discord_search_guild_members_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
                "(query):?s,"
  /* discord/guild.params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
                "(limit):d,",
  /* discord/guild.params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
                &p->query,
  /* discord/guild.params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
                &p->limit);
}

size_t discord_search_guild_members_params_to_json(char *json, size_t len, struct discord_search_guild_members_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/guild.params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
  if (p->query != NULL)
    arg_switches[0] = p->query;

  /* discord/guild.params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
  if (p->limit != 0)
    arg_switches[1] = &p->limit;

  r=json_inject(json, len, 
  /* discord/guild.params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
                "(query):s,"
  /* discord/guild.params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
                "(limit):d,"
                "@arg_switches:b",
  /* discord/guild.params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
                p->query,
  /* discord/guild.params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
                &p->limit,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_search_guild_members_params_cleanup_v(void *p) {
  discord_search_guild_members_params_cleanup((struct discord_search_guild_members_params *)p);
}

void discord_search_guild_members_params_init_v(void *p) {
  discord_search_guild_members_params_init((struct discord_search_guild_members_params *)p);
}

void discord_search_guild_members_params_from_json_v(char *json, size_t len, void *p) {
 discord_search_guild_members_params_from_json(json, len, (struct discord_search_guild_members_params*)p);
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
  /* discord/guild.params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */
  if (d->query)
    free(d->query);
  /* discord/guild.params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */
  (void)d->limit;
}

void discord_search_guild_members_params_init(struct discord_search_guild_members_params *p) {
  memset(p, 0, sizeof(struct discord_search_guild_members_params));
  /* discord/guild.params.json:98:20
     '{ "name": "query", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null, "comment": "Query string to match username(s) and nickname(s) against." }' */

  /* discord/guild.params.json:99:20
     '{ "name": "limit", "type":{ "base":"int" }, "inject_if_not":0, "comment": "max number of members to return (1-1000)"}' */

}
void discord_search_guild_members_params_list_free(struct discord_search_guild_members_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_search_guild_members_params_cleanup);
}

void discord_search_guild_members_params_list_from_json(char *str, size_t len, struct discord_search_guild_members_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_search_guild_members_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_search_guild_members_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_search_guild_members_params_list_to_json(char *str, size_t len, struct discord_search_guild_members_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_search_guild_members_params_to_json);
}


void discord_add_guild_member_params_from_json_p(char *json, size_t len, struct discord_add_guild_member_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_add_guild_member_params_from_json(json, len, *pp);
}
void discord_add_guild_member_params_from_json(char *json, size_t len, struct discord_add_guild_member_params *p)
{
  discord_add_guild_member_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(access_token):?s,"
  /* discord/guild.params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(nick):?s,"
  /* discord/guild.params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(roles):F,"
  /* discord/guild.params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mute):b,"
  /* discord/guild.params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(deaf):b,",
  /* discord/guild.params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->access_token,
  /* discord/guild.params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->nick,
  /* discord/guild.params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_from_json, &p->roles,
  /* discord/guild.params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mute,
  /* discord/guild.params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->deaf);
}

size_t discord_add_guild_member_params_to_json(char *json, size_t len, struct discord_add_guild_member_params *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* discord/guild.params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->access_token != NULL)
    arg_switches[0] = p->access_token;

  /* discord/guild.params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->nick != NULL)
    arg_switches[1] = p->nick;

  /* discord/guild.params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->roles != NULL)
    arg_switches[2] = p->roles;

  /* discord/guild.params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->mute != false)
    arg_switches[3] = &p->mute;

  /* discord/guild.params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->deaf != false)
    arg_switches[4] = &p->deaf;

  r=json_inject(json, len, 
  /* discord/guild.params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(access_token):s,"
  /* discord/guild.params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(nick):s,"
  /* discord/guild.params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(roles):F,"
  /* discord/guild.params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mute):b,"
  /* discord/guild.params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(deaf):b,"
                "@arg_switches:b",
  /* discord/guild.params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->access_token,
  /* discord/guild.params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->nick,
  /* discord/guild.params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_to_json, p->roles,
  /* discord/guild.params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mute,
  /* discord/guild.params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->deaf,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_add_guild_member_params_cleanup_v(void *p) {
  discord_add_guild_member_params_cleanup((struct discord_add_guild_member_params *)p);
}

void discord_add_guild_member_params_init_v(void *p) {
  discord_add_guild_member_params_init((struct discord_add_guild_member_params *)p);
}

void discord_add_guild_member_params_from_json_v(char *json, size_t len, void *p) {
 discord_add_guild_member_params_from_json(json, len, (struct discord_add_guild_member_params*)p);
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
  /* discord/guild.params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->access_token)
    free(d->access_token);
  /* discord/guild.params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->nick)
    free(d->nick);
  /* discord/guild.params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* discord/guild.params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  (void)d->mute;
  /* discord/guild.params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  (void)d->deaf;
}

void discord_add_guild_member_params_init(struct discord_add_guild_member_params *p) {
  memset(p, 0, sizeof(struct discord_add_guild_member_params));
  /* discord/guild.params.json:108:20
     '{ "name": "access_token", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/guild.params.json:109:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

  /* discord/guild.params.json:110:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */

  /* discord/guild.params.json:111:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* discord/guild.params.json:112:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */

}
void discord_add_guild_member_params_list_free(struct discord_add_guild_member_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_add_guild_member_params_cleanup);
}

void discord_add_guild_member_params_list_from_json(char *str, size_t len, struct discord_add_guild_member_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_add_guild_member_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_add_guild_member_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_add_guild_member_params_list_to_json(char *str, size_t len, struct discord_add_guild_member_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_add_guild_member_params_to_json);
}


void discord_modify_guild_member_params_from_json_p(char *json, size_t len, struct discord_modify_guild_member_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_guild_member_params_from_json(json, len, *pp);
}
void discord_modify_guild_member_params_from_json(char *json, size_t len, struct discord_modify_guild_member_params *p)
{
  discord_modify_guild_member_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):?s,"
  /* discord/guild.params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(roles):F,"
  /* discord/guild.params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mute):b,"
  /* discord/guild.params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(deaf):b,"
  /* discord/guild.params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                "(channel_id):F,",
  /* discord/guild.params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                &p->nick,
  /* discord/guild.params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_from_json, &p->roles,
  /* discord/guild.params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mute,
  /* discord/guild.params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->deaf,
  /* discord/guild.params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                cee_strtou64, &p->channel_id);
}

size_t discord_modify_guild_member_params_to_json(char *json, size_t len, struct discord_modify_guild_member_params *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* discord/guild.params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->nick;

  /* discord/guild.params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->roles != NULL)
    arg_switches[1] = p->roles;

  /* discord/guild.params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->mute != false)
    arg_switches[2] = &p->mute;

  /* discord/guild.params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->deaf != false)
    arg_switches[3] = &p->deaf;

  /* discord/guild.params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  if (p->channel_id != 0)
    arg_switches[4] = &p->channel_id;

  r=json_inject(json, len, 
  /* discord/guild.params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):s,"
  /* discord/guild.params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(roles):F,"
  /* discord/guild.params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mute):b,"
  /* discord/guild.params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(deaf):b,"
  /* discord/guild.params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                "(channel_id):|F|,"
                "@arg_switches:b",
  /* discord/guild.params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                p->nick,
  /* discord/guild.params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_to_json, p->roles,
  /* discord/guild.params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mute,
  /* discord/guild.params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->deaf,
  /* discord/guild.params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
                cee_u64tostr, &p->channel_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_modify_guild_member_params_cleanup_v(void *p) {
  discord_modify_guild_member_params_cleanup((struct discord_modify_guild_member_params *)p);
}

void discord_modify_guild_member_params_init_v(void *p) {
  discord_modify_guild_member_params_init((struct discord_modify_guild_member_params *)p);
}

void discord_modify_guild_member_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_member_params_from_json(json, len, (struct discord_modify_guild_member_params*)p);
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
  /* discord/guild.params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  if (d->nick)
    free(d->nick);
  /* discord/guild.params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->roles)
    ja_u64_list_free(d->roles);
  /* discord/guild.params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */
  (void)d->mute;
  /* discord/guild.params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */
  (void)d->deaf;
  /* discord/guild.params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */
  (void)d->channel_id;
}

void discord_modify_guild_member_params_init(struct discord_modify_guild_member_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_member_params));
  /* discord/guild.params.json:121:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/guild.params.json:122:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */

  /* discord/guild.params.json:123:20
     '{ "name": "mute", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* discord/guild.params.json:124:20
     '{ "name": "deaf", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* discord/guild.params.json:125:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "inject_if_not":0}' */

}
void discord_modify_guild_member_params_list_free(struct discord_modify_guild_member_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_modify_guild_member_params_cleanup);
}

void discord_modify_guild_member_params_list_from_json(char *str, size_t len, struct discord_modify_guild_member_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_member_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_modify_guild_member_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_member_params_list_to_json(char *str, size_t len, struct discord_modify_guild_member_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_modify_guild_member_params_to_json);
}


void discord_modify_current_member_params_from_json_p(char *json, size_t len, struct discord_modify_current_member_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_current_member_params_from_json(json, len, *pp);
}
void discord_modify_current_member_params_from_json(char *json, size_t len, struct discord_modify_current_member_params *p)
{
  discord_modify_current_member_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):?s,",
  /* discord/guild.params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                &p->nick);
}

size_t discord_modify_current_member_params_to_json(char *json, size_t len, struct discord_modify_current_member_params *p)
{
  size_t r;
  void *arg_switches[1]={NULL};
  /* discord/guild.params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->nick;

  r=json_inject(json, len, 
  /* discord/guild.params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):s,"
                "@arg_switches:b",
  /* discord/guild.params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                p->nick,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_modify_current_member_params_cleanup_v(void *p) {
  discord_modify_current_member_params_cleanup((struct discord_modify_current_member_params *)p);
}

void discord_modify_current_member_params_init_v(void *p) {
  discord_modify_current_member_params_init((struct discord_modify_current_member_params *)p);
}

void discord_modify_current_member_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_current_member_params_from_json(json, len, (struct discord_modify_current_member_params*)p);
}

size_t discord_modify_current_member_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_current_member_params_to_json(json, len, (struct discord_modify_current_member_params*)p);
}

void discord_modify_current_member_params_list_free_v(void **p) {
  discord_modify_current_member_params_list_free((struct discord_modify_current_member_params**)p);
}

void discord_modify_current_member_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_current_member_params_list_from_json(str, len, (struct discord_modify_current_member_params ***)p);
}

size_t discord_modify_current_member_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_current_member_params_list_to_json(str, len, (struct discord_modify_current_member_params **)p);
}


void discord_modify_current_member_params_cleanup(struct discord_modify_current_member_params *d) {
  /* discord/guild.params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  if (d->nick)
    free(d->nick);
}

void discord_modify_current_member_params_init(struct discord_modify_current_member_params *p) {
  memset(p, 0, sizeof(struct discord_modify_current_member_params));
  /* discord/guild.params.json:134:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */

}
void discord_modify_current_member_params_list_free(struct discord_modify_current_member_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_modify_current_member_params_cleanup);
}

void discord_modify_current_member_params_list_from_json(char *str, size_t len, struct discord_modify_current_member_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_current_member_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_modify_current_member_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_current_member_params_list_to_json(char *str, size_t len, struct discord_modify_current_member_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_modify_current_member_params_to_json);
}


void discord_modify_current_user_nick_params_from_json_p(char *json, size_t len, struct discord_modify_current_user_nick_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_current_user_nick_params_from_json(json, len, *pp);
}
void discord_modify_current_user_nick_params_from_json(char *json, size_t len, struct discord_modify_current_user_nick_params *p)
{
  discord_modify_current_user_nick_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):?s,",
  /* discord/guild.params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                &p->nick);
}

size_t discord_modify_current_user_nick_params_to_json(char *json, size_t len, struct discord_modify_current_user_nick_params *p)
{
  size_t r;
  void *arg_switches[1]={NULL};
  /* discord/guild.params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->nick;

  r=json_inject(json, len, 
  /* discord/guild.params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                "(nick):s,"
                "@arg_switches:b",
  /* discord/guild.params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
                p->nick,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_modify_current_user_nick_params_cleanup_v(void *p) {
  discord_modify_current_user_nick_params_cleanup((struct discord_modify_current_user_nick_params *)p);
}

void discord_modify_current_user_nick_params_init_v(void *p) {
  discord_modify_current_user_nick_params_init((struct discord_modify_current_user_nick_params *)p);
}

void discord_modify_current_user_nick_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_current_user_nick_params_from_json(json, len, (struct discord_modify_current_user_nick_params*)p);
}

size_t discord_modify_current_user_nick_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_current_user_nick_params_to_json(json, len, (struct discord_modify_current_user_nick_params*)p);
}

void discord_modify_current_user_nick_params_list_free_v(void **p) {
  discord_modify_current_user_nick_params_list_free((struct discord_modify_current_user_nick_params**)p);
}

void discord_modify_current_user_nick_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_current_user_nick_params_list_from_json(str, len, (struct discord_modify_current_user_nick_params ***)p);
}

size_t discord_modify_current_user_nick_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_current_user_nick_params_list_to_json(str, len, (struct discord_modify_current_user_nick_params **)p);
}


void discord_modify_current_user_nick_params_cleanup(struct discord_modify_current_user_nick_params *d) {
  /* discord/guild.params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */
  if (d->nick)
    free(d->nick);
}

void discord_modify_current_user_nick_params_init(struct discord_modify_current_user_nick_params *p) {
  memset(p, 0, sizeof(struct discord_modify_current_user_nick_params));
  /* discord/guild.params.json:143:20
     '{ "name": "nick", "type":{ "base":"char", "dec":"*" }}' */

}
void discord_modify_current_user_nick_params_list_free(struct discord_modify_current_user_nick_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_modify_current_user_nick_params_cleanup);
}

void discord_modify_current_user_nick_params_list_from_json(char *str, size_t len, struct discord_modify_current_user_nick_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_current_user_nick_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_modify_current_user_nick_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_current_user_nick_params_list_to_json(char *str, size_t len, struct discord_modify_current_user_nick_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_modify_current_user_nick_params_to_json);
}


void discord_create_guild_ban_params_from_json_p(char *json, size_t len, struct discord_create_guild_ban_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_guild_ban_params_from_json(json, len, *pp);
}
void discord_create_guild_ban_params_from_json(char *json, size_t len, struct discord_create_guild_ban_params *p)
{
  discord_create_guild_ban_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */
                "(delete_message_days):d,"
  /* discord/guild.params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */
                "(reason):?s,",
  /* discord/guild.params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */
                &p->delete_message_days,
  /* discord/guild.params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */
                &p->reason);
}

size_t discord_create_guild_ban_params_to_json(char *json, size_t len, struct discord_create_guild_ban_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/guild.params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */
  arg_switches[0] = &p->delete_message_days;

  /* discord/guild.params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */
  if (p->reason != NULL)
    arg_switches[1] = p->reason;

  r=json_inject(json, len, 
  /* discord/guild.params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */
                "(delete_message_days):d,"
  /* discord/guild.params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */
                "(reason):s,"
                "@arg_switches:b",
  /* discord/guild.params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */
                &p->delete_message_days,
  /* discord/guild.params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */
                p->reason,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_guild_ban_params_cleanup_v(void *p) {
  discord_create_guild_ban_params_cleanup((struct discord_create_guild_ban_params *)p);
}

void discord_create_guild_ban_params_init_v(void *p) {
  discord_create_guild_ban_params_init((struct discord_create_guild_ban_params *)p);
}

void discord_create_guild_ban_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_ban_params_from_json(json, len, (struct discord_create_guild_ban_params*)p);
}

size_t discord_create_guild_ban_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_ban_params_to_json(json, len, (struct discord_create_guild_ban_params*)p);
}

void discord_create_guild_ban_params_list_free_v(void **p) {
  discord_create_guild_ban_params_list_free((struct discord_create_guild_ban_params**)p);
}

void discord_create_guild_ban_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_ban_params_list_from_json(str, len, (struct discord_create_guild_ban_params ***)p);
}

size_t discord_create_guild_ban_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_ban_params_list_to_json(str, len, (struct discord_create_guild_ban_params **)p);
}


void discord_create_guild_ban_params_cleanup(struct discord_create_guild_ban_params *d) {
  /* discord/guild.params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */
  (void)d->delete_message_days;
  /* discord/guild.params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */
  if (d->reason)
    free(d->reason);
}

void discord_create_guild_ban_params_init(struct discord_create_guild_ban_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_ban_params));
  /* discord/guild.params.json:152:20
     '{ "name": "delete_message_days", "type":{ "base":"int" }, "comment":"number of days to delete messages for(0-7)"}' */

  /* discord/guild.params.json:153:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "comment":"reason for the ban (deprecated)", "inject_if_not":null }' */

}
void discord_create_guild_ban_params_list_free(struct discord_create_guild_ban_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_guild_ban_params_cleanup);
}

void discord_create_guild_ban_params_list_from_json(char *str, size_t len, struct discord_create_guild_ban_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_ban_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_guild_ban_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_ban_params_list_to_json(char *str, size_t len, struct discord_create_guild_ban_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_guild_ban_params_to_json);
}


void discord_create_guild_role_params_from_json_p(char *json, size_t len, struct discord_create_guild_role_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_guild_role_params_from_json(json, len, *pp);
}
void discord_create_guild_role_params_from_json(char *json, size_t len, struct discord_create_guild_role_params *p)
{
  discord_create_guild_role_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):?s,"
  /* discord/guild.params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "inject_if_not":0}' */
                "(permissions):s_as_u64,"
  /* discord/guild.params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(color):d,"
  /* discord/guild.params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(hoist):b,"
  /* discord/guild.params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mentionable):b,",
  /* discord/guild.params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                &p->name,
  /* discord/guild.params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "inject_if_not":0}' */
                &p->permissions,
  /* discord/guild.params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->color,
  /* discord/guild.params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->hoist,
  /* discord/guild.params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mentionable);
}

size_t discord_create_guild_role_params_to_json(char *json, size_t len, struct discord_create_guild_role_params *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* discord/guild.params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  arg_switches[0] = p->name;

  /* discord/guild.params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "inject_if_not":0}' */
  if (p->permissions != 0)
    arg_switches[1] = &p->permissions;

  /* discord/guild.params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->color != 0)
    arg_switches[2] = &p->color;

  /* discord/guild.params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->hoist != false)
    arg_switches[3] = &p->hoist;

  /* discord/guild.params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->mentionable != false)
    arg_switches[4] = &p->mentionable;

  r=json_inject(json, len, 
  /* discord/guild.params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                "(name):s,"
  /* discord/guild.params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "inject_if_not":0}' */
                "(permissions):s_as_u64,"
  /* discord/guild.params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(color):d,"
  /* discord/guild.params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(hoist):b,"
  /* discord/guild.params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(mentionable):b,"
                "@arg_switches:b",
  /* discord/guild.params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
                p->name,
  /* discord/guild.params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "inject_if_not":0}' */
                &p->permissions,
  /* discord/guild.params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->color,
  /* discord/guild.params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->hoist,
  /* discord/guild.params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->mentionable,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_guild_role_params_cleanup_v(void *p) {
  discord_create_guild_role_params_cleanup((struct discord_create_guild_role_params *)p);
}

void discord_create_guild_role_params_init_v(void *p) {
  discord_create_guild_role_params_init((struct discord_create_guild_role_params *)p);
}

void discord_create_guild_role_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_role_params_from_json(json, len, (struct discord_create_guild_role_params*)p);
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
  /* discord/guild.params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */
  if (d->name)
    free(d->name);
  /* discord/guild.params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "inject_if_not":0}' */
  (void)d->permissions;
  /* discord/guild.params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->color;
  /* discord/guild.params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */
  (void)d->hoist;
  /* discord/guild.params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */
  (void)d->mentionable;
}

void discord_create_guild_role_params_init(struct discord_create_guild_role_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_role_params));
  /* discord/guild.params.json:162:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }}' */

  /* discord/guild.params.json:163:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "inject_if_not":0}' */

  /* discord/guild.params.json:164:20
     '{ "name": "color", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/guild.params.json:165:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* discord/guild.params.json:166:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "inject_if_not":false}' */

}
void discord_create_guild_role_params_list_free(struct discord_create_guild_role_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_guild_role_params_cleanup);
}

void discord_create_guild_role_params_list_from_json(char *str, size_t len, struct discord_create_guild_role_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_role_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_guild_role_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_role_params_list_to_json(char *str, size_t len, struct discord_create_guild_role_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_guild_role_params_to_json);
}


void discord_modify_guild_role_positions_params_from_json_p(char *json, size_t len, struct discord_modify_guild_role_positions_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_guild_role_positions_params_from_json(json, len, *pp);
}
void discord_modify_guild_role_positions_params_from_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p)
{
  discord_modify_guild_role_positions_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
                "(id):F,"
  /* discord/guild.params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
                "(position):d,",
  /* discord/guild.params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
                cee_strtou64, &p->id,
  /* discord/guild.params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
                &p->position);
}

size_t discord_modify_guild_role_positions_params_to_json(char *json, size_t len, struct discord_modify_guild_role_positions_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/guild.params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
  if (p->id != 0)
    arg_switches[0] = &p->id;

  /* discord/guild.params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
  if (p->position != 0)
    arg_switches[1] = &p->position;

  r=json_inject(json, len, 
  /* discord/guild.params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
                "(id):|F|,"
  /* discord/guild.params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
                "(position):d,"
                "@arg_switches:b",
  /* discord/guild.params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
                cee_u64tostr, &p->id,
  /* discord/guild.params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
                &p->position,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_modify_guild_role_positions_params_cleanup_v(void *p) {
  discord_modify_guild_role_positions_params_cleanup((struct discord_modify_guild_role_positions_params *)p);
}

void discord_modify_guild_role_positions_params_init_v(void *p) {
  discord_modify_guild_role_positions_params_init((struct discord_modify_guild_role_positions_params *)p);
}

void discord_modify_guild_role_positions_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_role_positions_params_from_json(json, len, (struct discord_modify_guild_role_positions_params*)p);
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
  /* discord/guild.params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */
  (void)d->id;
  /* discord/guild.params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */
  (void)d->position;
}

void discord_modify_guild_role_positions_params_init(struct discord_modify_guild_role_positions_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_role_positions_params));
  /* discord/guild.params.json:175:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0, "comment":"role"}' */

  /* discord/guild.params.json:176:20
     '{ "name": "position", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"sorting position of the role"}' */

}
void discord_modify_guild_role_positions_params_list_free(struct discord_modify_guild_role_positions_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_modify_guild_role_positions_params_cleanup);
}

void discord_modify_guild_role_positions_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_positions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_role_positions_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_modify_guild_role_positions_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_role_positions_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_positions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_modify_guild_role_positions_params_to_json);
}


void discord_modify_guild_role_params_from_json_p(char *json, size_t len, struct discord_modify_guild_role_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_guild_role_params_from_json(json, len, *pp);
}
void discord_modify_guild_role_params_from_json(char *json, size_t len, struct discord_modify_guild_role_params *p)
{
  discord_modify_guild_role_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
                "(name):?s,"
  /* discord/guild.params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
                "(permissions):s_as_u64,"
  /* discord/guild.params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
                "(color):d,"
  /* discord/guild.params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
                "(hoist):b,"
  /* discord/guild.params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
                "(mentionable):b,",
  /* discord/guild.params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
                &p->name,
  /* discord/guild.params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
                &p->permissions,
  /* discord/guild.params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
                &p->color,
  /* discord/guild.params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
                &p->hoist,
  /* discord/guild.params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
                &p->mentionable);
}

size_t discord_modify_guild_role_params_to_json(char *json, size_t len, struct discord_modify_guild_role_params *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* discord/guild.params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/guild.params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
  if (p->permissions != 0)
    arg_switches[1] = &p->permissions;

  /* discord/guild.params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
  if (p->color != 0)
    arg_switches[2] = &p->color;

  /* discord/guild.params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
  if (p->hoist != false)
    arg_switches[3] = &p->hoist;

  /* discord/guild.params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
  if (p->mentionable != false)
    arg_switches[4] = &p->mentionable;

  r=json_inject(json, len, 
  /* discord/guild.params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
                "(name):s,"
  /* discord/guild.params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
                "(permissions):s_as_u64,"
  /* discord/guild.params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
                "(color):d,"
  /* discord/guild.params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
                "(hoist):b,"
  /* discord/guild.params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
                "(mentionable):b,"
                "@arg_switches:b",
  /* discord/guild.params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
                p->name,
  /* discord/guild.params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
                &p->permissions,
  /* discord/guild.params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
                &p->color,
  /* discord/guild.params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
                &p->hoist,
  /* discord/guild.params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
                &p->mentionable,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_modify_guild_role_params_cleanup_v(void *p) {
  discord_modify_guild_role_params_cleanup((struct discord_modify_guild_role_params *)p);
}

void discord_modify_guild_role_params_init_v(void *p) {
  discord_modify_guild_role_params_init((struct discord_modify_guild_role_params *)p);
}

void discord_modify_guild_role_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_role_params_from_json(json, len, (struct discord_modify_guild_role_params*)p);
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
  /* discord/guild.params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */
  if (d->name)
    free(d->name);
  /* discord/guild.params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */
  (void)d->permissions;
  /* discord/guild.params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */
  (void)d->color;
  /* discord/guild.params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */
  (void)d->hoist;
  /* discord/guild.params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */
  (void)d->mentionable;
}

void discord_modify_guild_role_params_init(struct discord_modify_guild_role_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_role_params));
  /* discord/guild.params.json:185:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "option":true, "inject_if_not":null, "comment":"name of the role"}' */

  /* discord/guild.params.json:186:20
     '{ "name": "permissions", "type":{ "base":"s_as_u64", "int_alias":"u64_bitmask_t" }, "option":true, "inject_if_not":0, "comment":"bitwise value of the enabled/disabled permissions"}' */

  /* discord/guild.params.json:187:20
     '{ "name": "color", "type":{ "base":"int" }, "option":true, "inject_if_not":0, "comment":"RGB color value"}' */

  /* discord/guild.params.json:188:20
     '{ "name": "hoist", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be displayed separately in the sidebar"}' */

  /* discord/guild.params.json:189:20
     '{ "name": "mentionable", "type":{ "base":"bool" }, "option":true, "inject_if_not":false, "comment":"whether the role should be mentionable"}' */

}
void discord_modify_guild_role_params_list_free(struct discord_modify_guild_role_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_modify_guild_role_params_cleanup);
}

void discord_modify_guild_role_params_list_from_json(char *str, size_t len, struct discord_modify_guild_role_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_role_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_modify_guild_role_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_role_params_list_to_json(char *str, size_t len, struct discord_modify_guild_role_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_modify_guild_role_params_to_json);
}


void discord_get_guild_prune_count_params_from_json_p(char *json, size_t len, struct discord_get_guild_prune_count_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_get_guild_prune_count_params_from_json(json, len, *pp);
}
void discord_get_guild_prune_count_params_from_json(char *json, size_t len, struct discord_get_guild_prune_count_params *p)
{
  discord_get_guild_prune_count_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(days):d,"
  /* discord/guild.params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(include_roles):F,",
  /* discord/guild.params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->days,
  /* discord/guild.params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_from_json, &p->include_roles);
}

size_t discord_get_guild_prune_count_params_to_json(char *json, size_t len, struct discord_get_guild_prune_count_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/guild.params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->days != 0)
    arg_switches[0] = &p->days;

  /* discord/guild.params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->include_roles != NULL)
    arg_switches[1] = p->include_roles;

  r=json_inject(json, len, 
  /* discord/guild.params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(days):d,"
  /* discord/guild.params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(include_roles):F,"
                "@arg_switches:b",
  /* discord/guild.params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->days,
  /* discord/guild.params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_to_json, p->include_roles,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_get_guild_prune_count_params_cleanup_v(void *p) {
  discord_get_guild_prune_count_params_cleanup((struct discord_get_guild_prune_count_params *)p);
}

void discord_get_guild_prune_count_params_init_v(void *p) {
  discord_get_guild_prune_count_params_init((struct discord_get_guild_prune_count_params *)p);
}

void discord_get_guild_prune_count_params_from_json_v(char *json, size_t len, void *p) {
 discord_get_guild_prune_count_params_from_json(json, len, (struct discord_get_guild_prune_count_params*)p);
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
  /* discord/guild.params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->days;
  /* discord/guild.params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->include_roles)
    ja_u64_list_free(d->include_roles);
}

void discord_get_guild_prune_count_params_init(struct discord_get_guild_prune_count_params *p) {
  memset(p, 0, sizeof(struct discord_get_guild_prune_count_params));
  /* discord/guild.params.json:198:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/guild.params.json:199:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */

}
void discord_get_guild_prune_count_params_list_free(struct discord_get_guild_prune_count_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_get_guild_prune_count_params_cleanup);
}

void discord_get_guild_prune_count_params_list_from_json(char *str, size_t len, struct discord_get_guild_prune_count_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_get_guild_prune_count_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_get_guild_prune_count_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_get_guild_prune_count_params_list_to_json(char *str, size_t len, struct discord_get_guild_prune_count_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_get_guild_prune_count_params_to_json);
}


void discord_begin_guild_prune_params_from_json_p(char *json, size_t len, struct discord_begin_guild_prune_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_begin_guild_prune_params_from_json(json, len, *pp);
}
void discord_begin_guild_prune_params_from_json(char *json, size_t len, struct discord_begin_guild_prune_params *p)
{
  discord_begin_guild_prune_params_init(p);
  json_extract(json, len, 
  /* discord/guild.params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(days):d,"
  /* discord/guild.params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(compute_prune_count):b,"
  /* discord/guild.params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(include_roles):F,"
  /* discord/guild.params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(reason):?s,",
  /* discord/guild.params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->days,
  /* discord/guild.params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->compute_prune_count,
  /* discord/guild.params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_from_json, &p->include_roles,
  /* discord/guild.params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                &p->reason);
}

size_t discord_begin_guild_prune_params_to_json(char *json, size_t len, struct discord_begin_guild_prune_params *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/guild.params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  if (p->days != 0)
    arg_switches[0] = &p->days;

  /* discord/guild.params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
  if (p->compute_prune_count != false)
    arg_switches[1] = &p->compute_prune_count;

  /* discord/guild.params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (p->include_roles != NULL)
    arg_switches[2] = p->include_roles;

  /* discord/guild.params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (p->reason != NULL)
    arg_switches[3] = p->reason;

  r=json_inject(json, len, 
  /* discord/guild.params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                "(days):d,"
  /* discord/guild.params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
                "(compute_prune_count):b,"
  /* discord/guild.params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                "(include_roles):F,"
  /* discord/guild.params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                "(reason):s,"
                "@arg_switches:b",
  /* discord/guild.params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
                &p->days,
  /* discord/guild.params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
                &p->compute_prune_count,
  /* discord/guild.params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
                ja_u64_list_to_json, p->include_roles,
  /* discord/guild.params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
                p->reason,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_begin_guild_prune_params_cleanup_v(void *p) {
  discord_begin_guild_prune_params_cleanup((struct discord_begin_guild_prune_params *)p);
}

void discord_begin_guild_prune_params_init_v(void *p) {
  discord_begin_guild_prune_params_init((struct discord_begin_guild_prune_params *)p);
}

void discord_begin_guild_prune_params_from_json_v(char *json, size_t len, void *p) {
 discord_begin_guild_prune_params_from_json(json, len, (struct discord_begin_guild_prune_params*)p);
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
  /* discord/guild.params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */
  (void)d->days;
  /* discord/guild.params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */
  (void)d->compute_prune_count;
  /* discord/guild.params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */
  if (d->include_roles)
    ja_u64_list_free(d->include_roles);
  /* discord/guild.params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */
  if (d->reason)
    free(d->reason);
}

void discord_begin_guild_prune_params_init(struct discord_begin_guild_prune_params *p) {
  memset(p, 0, sizeof(struct discord_begin_guild_prune_params));
  /* discord/guild.params.json:208:20
     '{ "name": "days", "type":{ "base":"int" }, "inject_if_not":0}' */

  /* discord/guild.params.json:209:20
     '{ "name": "compute_prune_count", "type":{ "base":"bool" }, "inject_if_not":false}' */

  /* discord/guild.params.json:210:20
     '{ "name": "include_roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "inject_if_not":null}' */

  /* discord/guild.params.json:211:20
     '{ "name": "reason", "type":{ "base":"char", "dec":"*" }, "inject_if_not":null}' */

}
void discord_begin_guild_prune_params_list_free(struct discord_begin_guild_prune_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_begin_guild_prune_params_cleanup);
}

void discord_begin_guild_prune_params_list_from_json(char *str, size_t len, struct discord_begin_guild_prune_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_begin_guild_prune_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_begin_guild_prune_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_begin_guild_prune_params_list_to_json(char *str, size_t len, struct discord_begin_guild_prune_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_begin_guild_prune_params_to_json);
}

