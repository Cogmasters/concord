/* This file is generated from specs/discord/webhook.json, Please don't edit it. */
/**
 * @file specs-code/discord/webhook.c
 * @see https://discord.com/developers/docs/resources/webhook
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_webhook_from_json(char *json, size_t len, struct discord_webhook **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_webhook *p = *pp;
  discord_webhook_init(p);
  r=json_extract(json, len, 
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */
                "(id):F,"
  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */
                "(type):d,"
  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */
                "(guild_id):F,"
  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */
                "(channel_id):F,"
  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */
                "(user):F,"
  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */
                "(name):?s,"
  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */
                "(avatar):?s,"
  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */
                "(token):?s,"
  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */
                "(application_id):F,"
  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */
                "(source_guild):F,"
  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */
                "(source_channel):F,"
  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */
                "(url):?s,",
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */
                cee_strtoull, &p->id,
  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */
                &p->type,
  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */
                discord_user_from_json, &p->user,
  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */
                &p->name,
  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */
                &p->avatar,
  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */
                &p->token,
  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */
                cee_strtoull, &p->application_id,
  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */
                discord_guild_from_json, &p->source_guild,
  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */
                discord_channel_from_json, &p->source_channel,
  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */
                &p->url);
  ret = r;
}

size_t discord_webhook_to_json(char *json, size_t len, struct discord_webhook *p)
{
  size_t r;
  void *arg_switches[12]={NULL};
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */
  arg_switches[0] = &p->id;

  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */
  arg_switches[1] = &p->type;

  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */
  if (p->guild_id != 0)
    arg_switches[2] = &p->guild_id;

  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */
  if (p->channel_id != 0)
    arg_switches[3] = &p->channel_id;

  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */
  if (p->user != NULL)
    arg_switches[4] = p->user;

  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */
  arg_switches[5] = p->name;

  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */
  if (p->avatar != NULL)
    arg_switches[6] = p->avatar;

  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */
  if (p->token != NULL)
    arg_switches[7] = p->token;

  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */
  if (p->application_id != 0)
    arg_switches[8] = &p->application_id;

  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */
  if (p->source_guild != NULL)
    arg_switches[9] = p->source_guild;

  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */
  if (p->source_channel != NULL)
    arg_switches[10] = p->source_channel;

  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */
  if (p->url != NULL)
    arg_switches[11] = p->url;

  r=json_inject(json, len, 
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */
                "(id):|F|,"
  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */
                "(type):d,"
  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */
                "(guild_id):|F|,"
  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */
                "(channel_id):|F|,"
  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */
                "(user):F,"
  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */
                "(name):s,"
  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */
                "(avatar):s,"
  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */
                "(token):s,"
  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */
                "(application_id):|F|,"
  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */
                "(source_guild):F,"
  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */
                "(source_channel):F,"
  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */
                "(url):s,"
                "@arg_switches:b",
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */
                cee_ulltostr, &p->id,
  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */
                &p->type,
  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */
                discord_user_to_json, p->user,
  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */
                p->name,
  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */
                p->avatar,
  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */
                p->token,
  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */
                discord_guild_to_json, p->source_guild,
  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */
                discord_channel_to_json, p->source_channel,
  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */
                p->url,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_webhook_cleanup_v(void *p) {
  discord_webhook_cleanup((struct discord_webhook *)p);
}

void discord_webhook_init_v(void *p) {
  discord_webhook_init((struct discord_webhook *)p);
}

void discord_webhook_from_json_v(char *json, size_t len, void *pp) {
 discord_webhook_from_json(json, len, (struct discord_webhook**)pp);
}

size_t discord_webhook_to_json_v(char *json, size_t len, void *p) {
  return discord_webhook_to_json(json, len, (struct discord_webhook*)p);
}

void discord_webhook_list_free_v(void **p) {
  discord_webhook_list_free((struct discord_webhook**)p);
}

void discord_webhook_list_from_json_v(char *str, size_t len, void *p) {
  discord_webhook_list_from_json(str, len, (struct discord_webhook ***)p);
}

size_t discord_webhook_list_to_json_v(char *str, size_t len, void *p){
  return discord_webhook_list_to_json(str, len, (struct discord_webhook **)p);
}


void discord_webhook_cleanup(struct discord_webhook *d) {
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */
  /* p->id is a scalar */
  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */
  /* p->type is a scalar */
  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */
  /* p->guild_id is a scalar */
  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */
  /* p->channel_id is a scalar */
  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */
  if (d->name)
    free(d->name);
  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */
  if (d->avatar)
    free(d->avatar);
  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */
  if (d->token)
    free(d->token);
  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */
  /* p->application_id is a scalar */
  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */
  if (d->source_guild) {
    discord_guild_cleanup(d->source_guild);
    free(d->source_guild);
  }
  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */
  if (d->source_channel) {
    discord_channel_cleanup(d->source_channel);
    free(d->source_channel);
  }
  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */
  if (d->url)
    free(d->url);
}

void discord_webhook_init(struct discord_webhook *p) {
  memset(p, 0, sizeof(struct discord_webhook));
  /* specs/discord/webhook.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the id of the webhook" }' */

  /* specs/discord/webhook.json:13:20
     '{ "name": "type", "type":{ "base":"int", "int_alias":"enum discord_webhook_types" }, "comment":"the type of the webhook" }' */

  /* specs/discord/webhook.json:14:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the guild id this webhook is for, if any", "inject_if_not":0 }' */

  /* specs/discord/webhook.json:15:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the channel id this webhook is for, if any", "inject_if_not":0 }' */

  /* specs/discord/webhook.json:16:20
     '{ "name": "user", "type":{ "base":"struct discord_user", "dec":"*" }, "comment":"the user this webhook was created by (not returned when getting a webhook with its token", "inject_if_not":null }' */

  /* specs/discord/webhook.json:17:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*", "comment":"the default name of the webhook", "inject_if_not":null }}' */

  /* specs/discord/webhook.json:18:20
     '{ "name": "avatar", "type":{ "base":"char", "dec":"*" }, "comment":"the default user avatar has of the webhook", "inject_if_not":null }' */

  /* specs/discord/webhook.json:19:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"the secure token of the webhook (returned for Incoming Webhooks)", "inject_if_not":null }' */

  /* specs/discord/webhook.json:20:20
     '{ "name": "application_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"the bot/OAuth2 application that created this webhook", "inject_if_not":0 }' */

  /* specs/discord/webhook.json:21:20
     '{ "name": "source_guild", "type":{ "base":"struct discord_guild", "dec":"*" }, "comment":"the guild of the channel that this webhook is following (returned for Channel Follower Webhook)", "inject_if_not":null }' */

  /* specs/discord/webhook.json:22:20
     '{ "name": "source_channel", "type":{ "base":"struct discord_channel", "dec":"*" }, "comment":"the channel that this webhook is following (returned for Channel Follower Webhooks)", "inject_if_not":null }' */

  /* specs/discord/webhook.json:23:20
     '{ "name": "url", "type":{ "base":"char", "dec":"*" }, "comment":"the url used for executing the webhook (returned by the webhooks OAuth2 flow)", "inject_if_not":null }' */

}
void discord_webhook_list_free(struct discord_webhook **p) {
  ntl_free((void**)p, (vfvp)discord_webhook_cleanup);
}

void discord_webhook_list_from_json(char *str, size_t len, struct discord_webhook ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_webhook);
  d.init_elem = NULL;
  d.elem_from_buf = discord_webhook_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_webhook_list_to_json(char *str, size_t len, struct discord_webhook **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_webhook_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_webhook_types_list_free_v(void **p) {
  discord_webhook_types_list_free((enum discord_webhook_types**)p);
}

void discord_webhook_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_webhook_types_list_from_json(str, len, (enum discord_webhook_types ***)p);
}

size_t discord_webhook_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_webhook_types_list_to_json(str, len, (enum discord_webhook_types **)p);
}

enum discord_webhook_types discord_webhook_types_eval(char *s){
  if(strcasecmp("INCOMING", s) == 0) return DISCORD_WEBHOOK_INCOMING;
  if(strcasecmp("CHANNEL_FOLLOWER", s) == 0) return DISCORD_WEBHOOK_CHANNEL_FOLLOWER;
  if(strcasecmp("APPLICATION", s) == 0) return DISCORD_WEBHOOK_APPLICATION;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_webhook_types_print(enum discord_webhook_types v){

  switch (v) {
  case DISCORD_WEBHOOK_INCOMING: return "INCOMING";
  case DISCORD_WEBHOOK_CHANNEL_FOLLOWER: return "CHANNEL_FOLLOWER";
  case DISCORD_WEBHOOK_APPLICATION: return "APPLICATION";
  }

  return NULL;
}

void discord_webhook_types_list_free(enum discord_webhook_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_webhook_types_list_from_json(char *str, size_t len, enum discord_webhook_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_webhook_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_webhook_types_list_to_json(char *str, size_t len, enum discord_webhook_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}

