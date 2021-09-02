/* This file is generated from specs/discord/receiving_and_responding.json, Please don't edit it. */
/**
 * @file specs-code/discord/receiving_and_responding.c
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-data-structure
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_interaction_from_json(char *json, size_t len, struct discord_interaction **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_interaction *p = *pp;
  discord_interaction_init(p);
  r=json_extract(json, len, 
  /* specs/discord/receiving_and_responding.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                "(id):F,"
  /* specs/discord/receiving_and_responding.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
                "(application_id):F,"
  /* specs/discord/receiving_and_responding.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
                "(type):d,"
  /* specs/discord/receiving_and_responding.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
                "(data):F,"
  /* specs/discord/receiving_and_responding.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
                "(guild_id):F,"
  /* specs/discord/receiving_and_responding.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
                "(channel_id):F,"
  /* specs/discord/receiving_and_responding.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
                "(member):F,"
  /* specs/discord/receiving_and_responding.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
                "(user):F,"
  /* specs/discord/receiving_and_responding.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
                "(token):?s,"
  /* specs/discord/receiving_and_responding.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */
                "(message):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/receiving_and_responding.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                cee_strtoull, &p->id,
  /* specs/discord/receiving_and_responding.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/receiving_and_responding.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
                &p->type,
  /* specs/discord/receiving_and_responding.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
                discord_interaction_data_from_json, &p->data,
  /* specs/discord/receiving_and_responding.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/receiving_and_responding.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/receiving_and_responding.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
                discord_guild_member_from_json, &p->member,
  /* specs/discord/receiving_and_responding.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
                discord_user_from_json, &p->user,
  /* specs/discord/receiving_and_responding.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
                &p->token,
  /* specs/discord/receiving_and_responding.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */
                discord_message_from_json, &p->message,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_interaction_use_default_inject_settings(struct discord_interaction *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/receiving_and_responding.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/receiving_and_responding.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
  p->__M.arg_switches[1] = &p->application_id;

  /* specs/discord/receiving_and_responding.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
  p->__M.arg_switches[2] = &p->type;

  /* specs/discord/receiving_and_responding.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  if (p->data != NULL)
    p->__M.arg_switches[3] = p->data;

  /* specs/discord/receiving_and_responding.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
  if (p->guild_id != 0)
    p->__M.arg_switches[4] = &p->guild_id;

  /* specs/discord/receiving_and_responding.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
  if (p->channel_id != 0)
    p->__M.arg_switches[5] = &p->channel_id;

  /* specs/discord/receiving_and_responding.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  if (p->member != NULL)
    p->__M.arg_switches[6] = p->member;

  /* specs/discord/receiving_and_responding.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  if (p->user != NULL)
    p->__M.arg_switches[7] = p->user;

  /* specs/discord/receiving_and_responding.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
  if (p->token != NULL)
    p->__M.arg_switches[8] = p->token;

  /* specs/discord/receiving_and_responding.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */
  if (p->message != NULL)
    p->__M.arg_switches[9] = p->message;

}

size_t discord_interaction_to_json(char *json, size_t len, struct discord_interaction *p)
{
  size_t r;
  discord_interaction_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/receiving_and_responding.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                "(id):|F|,"
  /* specs/discord/receiving_and_responding.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
                "(application_id):|F|,"
  /* specs/discord/receiving_and_responding.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
                "(type):d,"
  /* specs/discord/receiving_and_responding.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
                "(data):F,"
  /* specs/discord/receiving_and_responding.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
                "(guild_id):|F|,"
  /* specs/discord/receiving_and_responding.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
                "(channel_id):|F|,"
  /* specs/discord/receiving_and_responding.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
                "(member):F,"
  /* specs/discord/receiving_and_responding.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
                "(user):F,"
  /* specs/discord/receiving_and_responding.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
                "(token):s,"
  /* specs/discord/receiving_and_responding.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */
                "(message):F,"
                "@arg_switches:b",
  /* specs/discord/receiving_and_responding.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/receiving_and_responding.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/receiving_and_responding.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
                &p->type,
  /* specs/discord/receiving_and_responding.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
                discord_interaction_data_to_json, p->data,
  /* specs/discord/receiving_and_responding.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/receiving_and_responding.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/receiving_and_responding.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
                discord_guild_member_to_json, p->member,
  /* specs/discord/receiving_and_responding.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
                discord_user_to_json, p->user,
  /* specs/discord/receiving_and_responding.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
                p->token,
  /* specs/discord/receiving_and_responding.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */
                discord_message_to_json, p->message,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_interaction_cleanup_v(void *p) {
  discord_interaction_cleanup((struct discord_interaction *)p);
}

void discord_interaction_init_v(void *p) {
  discord_interaction_init((struct discord_interaction *)p);
}

void discord_interaction_from_json_v(char *json, size_t len, void *pp) {
 discord_interaction_from_json(json, len, (struct discord_interaction**)pp);
}

size_t discord_interaction_to_json_v(char *json, size_t len, void *p) {
  return discord_interaction_to_json(json, len, (struct discord_interaction*)p);
}

void discord_interaction_list_free_v(void **p) {
  discord_interaction_list_free((struct discord_interaction**)p);
}

void discord_interaction_list_from_json_v(char *str, size_t len, void *p) {
  discord_interaction_list_from_json(str, len, (struct discord_interaction ***)p);
}

size_t discord_interaction_list_to_json_v(char *str, size_t len, void *p){
  return discord_interaction_list_to_json(str, len, (struct discord_interaction **)p);
}


void discord_interaction_cleanup(struct discord_interaction *d) {
  /* specs/discord/receiving_and_responding.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  // p->id is a scalar
  /* specs/discord/receiving_and_responding.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
  // p->application_id is a scalar
  /* specs/discord/receiving_and_responding.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
  // p->type is a scalar
  /* specs/discord/receiving_and_responding.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  if (d->data) {
    discord_interaction_data_cleanup(d->data);
    free(d->data);
  }
  /* specs/discord/receiving_and_responding.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
  // p->guild_id is a scalar
  /* specs/discord/receiving_and_responding.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
  // p->channel_id is a scalar
  /* specs/discord/receiving_and_responding.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  if (d->member) {
    discord_guild_member_cleanup(d->member);
    free(d->member);
  }
  /* specs/discord/receiving_and_responding.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
  /* specs/discord/receiving_and_responding.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
  if (d->token)
    free(d->token);
  /* specs/discord/receiving_and_responding.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */
  if (d->message) {
    discord_message_cleanup(d->message);
    free(d->message);
  }
}

void discord_interaction_init(struct discord_interaction *p) {
  memset(p, 0, sizeof(struct discord_interaction));
  /* specs/discord/receiving_and_responding.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */

  /* specs/discord/receiving_and_responding.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */

  /* specs/discord/receiving_and_responding.json:14:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */

  /* specs/discord/receiving_and_responding.json:15:18
     '{"name":"data", "type":{"base":"struct discord_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:16:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */

  /* specs/discord/receiving_and_responding.json:17:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */

  /* specs/discord/receiving_and_responding.json:18:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:19:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:20:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:21:18
     '{"name":"message", "type":{"base":"struct discord_message", "dec":"*"}, "option":true, "comment":"for components, the message they were attached to", "inject_if_not":null}' */

}
void discord_interaction_list_free(struct discord_interaction **p) {
  ntl_free((void**)p, (vfvp)discord_interaction_cleanup);
}

void discord_interaction_list_from_json(char *str, size_t len, struct discord_interaction ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_interaction);
  d.init_elem = NULL;
  d.elem_from_buf = discord_interaction_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_interaction_list_to_json(char *str, size_t len, struct discord_interaction **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_interaction_to_json_v);
}



enum discord_interaction_types discord_interaction_types_eval(char *s){
  if(strcasecmp("PING", s) == 0) return DISCORD_INTERACTION_PING;
  if(strcasecmp("APPLICATION_COMMAND", s) == 0) return DISCORD_INTERACTION_APPLICATION_COMMAND;
  if(strcasecmp("MESSAGE_COMPONENT", s) == 0) return DISCORD_INTERACTION_MESSAGE_COMPONENT;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_interaction_types_print(enum discord_interaction_types v){

  switch (v) {
  case DISCORD_INTERACTION_PING: return "PING";
  case DISCORD_INTERACTION_APPLICATION_COMMAND: return "APPLICATION_COMMAND";
  case DISCORD_INTERACTION_MESSAGE_COMPONENT: return "MESSAGE_COMPONENT";
  }

  return NULL;
}

void discord_interaction_data_from_json(char *json, size_t len, struct discord_interaction_data **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_interaction_data *p = *pp;
  discord_interaction_data_init(p);
  r=json_extract(json, len, 
  /* specs/discord/receiving_and_responding.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
                "(id):F,"
  /* specs/discord/receiving_and_responding.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
                "(name):?s,"
  /* specs/discord/receiving_and_responding.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */
                "(type):d,"
  /* specs/discord/receiving_and_responding.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
                "(resolved):F,"
  /* specs/discord/receiving_and_responding.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */
                "(options):F,"
  /* specs/discord/receiving_and_responding.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */
                "(custom_id):?s,"
  /* specs/discord/receiving_and_responding.json:49:18
     '{"name":"values", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */
                "(values):F,"
  /* specs/discord/receiving_and_responding.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */
                "(target_id):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/receiving_and_responding.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
                cee_strtoull, &p->id,
  /* specs/discord/receiving_and_responding.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
                &p->name,
  /* specs/discord/receiving_and_responding.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */
                &p->type,
  /* specs/discord/receiving_and_responding.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
                discord_resolved_data_from_json, &p->resolved,
  /* specs/discord/receiving_and_responding.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_from_json, &p->options,
  /* specs/discord/receiving_and_responding.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */
                &p->custom_id,
  /* specs/discord/receiving_and_responding.json:49:18
     '{"name":"values", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */
                discord_select_option_list_from_json, &p->values,
  /* specs/discord/receiving_and_responding.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */
                cee_strtoull, &p->target_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_interaction_data_use_default_inject_settings(struct discord_interaction_data *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/receiving_and_responding.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/receiving_and_responding.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/receiving_and_responding.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */
  p->__M.arg_switches[2] = &p->type;

  /* specs/discord/receiving_and_responding.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  if (p->resolved != NULL)
    p->__M.arg_switches[3] = p->resolved;

  /* specs/discord/receiving_and_responding.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */
  if (p->options != NULL)
    p->__M.arg_switches[4] = p->options;

  /* specs/discord/receiving_and_responding.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */
  if (p->custom_id != NULL)
    p->__M.arg_switches[5] = p->custom_id;

  /* specs/discord/receiving_and_responding.json:49:18
     '{"name":"values", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */
  if (p->values != NULL)
    p->__M.arg_switches[6] = p->values;

  /* specs/discord/receiving_and_responding.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */
  if (p->target_id != 0)
    p->__M.arg_switches[7] = &p->target_id;

}

size_t discord_interaction_data_to_json(char *json, size_t len, struct discord_interaction_data *p)
{
  size_t r;
  discord_interaction_data_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/receiving_and_responding.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
                "(id):|F|,"
  /* specs/discord/receiving_and_responding.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
                "(name):s,"
  /* specs/discord/receiving_and_responding.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */
                "(type):d,"
  /* specs/discord/receiving_and_responding.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
                "(resolved):F,"
  /* specs/discord/receiving_and_responding.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */
                "(options):F,"
  /* specs/discord/receiving_and_responding.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */
                "(custom_id):s,"
  /* specs/discord/receiving_and_responding.json:49:18
     '{"name":"values", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */
                "(values):F,"
  /* specs/discord/receiving_and_responding.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */
                "(target_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/receiving_and_responding.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/receiving_and_responding.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
                p->name,
  /* specs/discord/receiving_and_responding.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */
                &p->type,
  /* specs/discord/receiving_and_responding.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
                discord_resolved_data_to_json, p->resolved,
  /* specs/discord/receiving_and_responding.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_to_json, p->options,
  /* specs/discord/receiving_and_responding.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */
                p->custom_id,
  /* specs/discord/receiving_and_responding.json:49:18
     '{"name":"values", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */
                discord_select_option_list_to_json, p->values,
  /* specs/discord/receiving_and_responding.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */
                cee_ulltostr, &p->target_id,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_interaction_data_cleanup_v(void *p) {
  discord_interaction_data_cleanup((struct discord_interaction_data *)p);
}

void discord_interaction_data_init_v(void *p) {
  discord_interaction_data_init((struct discord_interaction_data *)p);
}

void discord_interaction_data_from_json_v(char *json, size_t len, void *pp) {
 discord_interaction_data_from_json(json, len, (struct discord_interaction_data**)pp);
}

size_t discord_interaction_data_to_json_v(char *json, size_t len, void *p) {
  return discord_interaction_data_to_json(json, len, (struct discord_interaction_data*)p);
}

void discord_interaction_data_list_free_v(void **p) {
  discord_interaction_data_list_free((struct discord_interaction_data**)p);
}

void discord_interaction_data_list_from_json_v(char *str, size_t len, void *p) {
  discord_interaction_data_list_from_json(str, len, (struct discord_interaction_data ***)p);
}

size_t discord_interaction_data_list_to_json_v(char *str, size_t len, void *p){
  return discord_interaction_data_list_to_json(str, len, (struct discord_interaction_data **)p);
}


void discord_interaction_data_cleanup(struct discord_interaction_data *d) {
  /* specs/discord/receiving_and_responding.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
  // p->id is a scalar
  /* specs/discord/receiving_and_responding.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/receiving_and_responding.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */
  // p->type is a scalar
  /* specs/discord/receiving_and_responding.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  if (d->resolved) {
    discord_resolved_data_cleanup(d->resolved);
    free(d->resolved);
  }
  /* specs/discord/receiving_and_responding.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_interaction_data_option_list_free(d->options);
  /* specs/discord/receiving_and_responding.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */
  if (d->custom_id)
    free(d->custom_id);
  /* specs/discord/receiving_and_responding.json:49:18
     '{"name":"values", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */
  if (d->values)
    discord_select_option_list_free(d->values);
  /* specs/discord/receiving_and_responding.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */
  // p->target_id is a scalar
}

void discord_interaction_data_init(struct discord_interaction_data *p) {
  memset(p, 0, sizeof(struct discord_interaction_data));
  /* specs/discord/receiving_and_responding.json:43:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */

  /* specs/discord/receiving_and_responding.json:44:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */

  /* specs/discord/receiving_and_responding.json:45:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "comment":"the type of the invoked command"}' */

  /* specs/discord/receiving_and_responding.json:46:18
     '{"name":"resolved", "type":{"base":"struct discord_resolved_data", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:47:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command, max 25", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:48:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"*"}, "comment":"the custom id of the component", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:49:18
     '{"name":"values", "type":{"base":"struct discord_select_option", "dec":"ntl"}, "option":true, "comment":"the values the user selected", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:50:18
     '{"name":"target_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of a user or message targetted by a user or message command", "inject_if_not":0}' */

}
void discord_interaction_data_list_free(struct discord_interaction_data **p) {
  ntl_free((void**)p, (vfvp)discord_interaction_data_cleanup);
}

void discord_interaction_data_list_from_json(char *str, size_t len, struct discord_interaction_data ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_interaction_data);
  d.init_elem = NULL;
  d.elem_from_buf = discord_interaction_data_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_interaction_data_list_to_json(char *str, size_t len, struct discord_interaction_data **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_interaction_data_to_json_v);
}


void discord_resolved_data_from_json(char *json, size_t len, struct discord_resolved_data **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_resolved_data *p = *pp;
  discord_resolved_data_init(p);
  r=json_extract(json, len, 
  /* specs/discord/receiving_and_responding.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
                "(users):F,"
  /* specs/discord/receiving_and_responding.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
                "(members):F,"
  /* specs/discord/receiving_and_responding.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
                "(roles):F,"
  /* specs/discord/receiving_and_responding.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
                "(channels):F,"
  /* specs/discord/receiving_and_responding.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */
                "(messages):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/receiving_and_responding.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->users,
  /* specs/discord/receiving_and_responding.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->members,
  /* specs/discord/receiving_and_responding.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->roles,
  /* specs/discord/receiving_and_responding.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->channels,
  /* specs/discord/receiving_and_responding.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->messages,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_resolved_data_use_default_inject_settings(struct discord_resolved_data *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/receiving_and_responding.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
  if (p->users != NULL)
    p->__M.arg_switches[0] = p->users;

  /* specs/discord/receiving_and_responding.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
  if (p->members != NULL)
    p->__M.arg_switches[1] = p->members;

  /* specs/discord/receiving_and_responding.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
  if (p->roles != NULL)
    p->__M.arg_switches[2] = p->roles;

  /* specs/discord/receiving_and_responding.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
  if (p->channels != NULL)
    p->__M.arg_switches[3] = p->channels;

  /* specs/discord/receiving_and_responding.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */
  if (p->messages != NULL)
    p->__M.arg_switches[4] = p->messages;

}

size_t discord_resolved_data_to_json(char *json, size_t len, struct discord_resolved_data *p)
{
  size_t r;
  discord_resolved_data_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/receiving_and_responding.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
                "(users):F,"
  /* specs/discord/receiving_and_responding.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
                "(members):F,"
  /* specs/discord/receiving_and_responding.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
                "(roles):F,"
  /* specs/discord/receiving_and_responding.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
                "(channels):F,"
  /* specs/discord/receiving_and_responding.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */
                "(messages):F,"
                "@arg_switches:b",
  /* specs/discord/receiving_and_responding.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->users,
  /* specs/discord/receiving_and_responding.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->members,
  /* specs/discord/receiving_and_responding.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->roles,
  /* specs/discord/receiving_and_responding.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->channels,
  /* specs/discord/receiving_and_responding.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->messages,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_resolved_data_cleanup_v(void *p) {
  discord_resolved_data_cleanup((struct discord_resolved_data *)p);
}

void discord_resolved_data_init_v(void *p) {
  discord_resolved_data_init((struct discord_resolved_data *)p);
}

void discord_resolved_data_from_json_v(char *json, size_t len, void *pp) {
 discord_resolved_data_from_json(json, len, (struct discord_resolved_data**)pp);
}

size_t discord_resolved_data_to_json_v(char *json, size_t len, void *p) {
  return discord_resolved_data_to_json(json, len, (struct discord_resolved_data*)p);
}

void discord_resolved_data_list_free_v(void **p) {
  discord_resolved_data_list_free((struct discord_resolved_data**)p);
}

void discord_resolved_data_list_from_json_v(char *str, size_t len, void *p) {
  discord_resolved_data_list_from_json(str, len, (struct discord_resolved_data ***)p);
}

size_t discord_resolved_data_list_to_json_v(char *str, size_t len, void *p){
  return discord_resolved_data_list_to_json(str, len, (struct discord_resolved_data **)p);
}


void discord_resolved_data_cleanup(struct discord_resolved_data *d) {
  /* specs/discord/receiving_and_responding.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
  if (d->users)
    ja_str_list_free(d->users);
  /* specs/discord/receiving_and_responding.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
  if (d->members)
    ja_str_list_free(d->members);
  /* specs/discord/receiving_and_responding.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
  if (d->roles)
    ja_str_list_free(d->roles);
  /* specs/discord/receiving_and_responding.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
  if (d->channels)
    ja_str_list_free(d->channels);
  /* specs/discord/receiving_and_responding.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */
  if (d->messages)
    ja_str_list_free(d->messages);
}

void discord_resolved_data_init(struct discord_resolved_data *p) {
  memset(p, 0, sizeof(struct discord_resolved_data));
  /* specs/discord/receiving_and_responding.json:60:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:61:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:62:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:63:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:64:18
     '{"name":"messages", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Message objects", "inject_if_not":null}' */

}
void discord_resolved_data_list_free(struct discord_resolved_data **p) {
  ntl_free((void**)p, (vfvp)discord_resolved_data_cleanup);
}

void discord_resolved_data_list_from_json(char *str, size_t len, struct discord_resolved_data ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_resolved_data);
  d.init_elem = NULL;
  d.elem_from_buf = discord_resolved_data_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_resolved_data_list_to_json(char *str, size_t len, struct discord_resolved_data **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_resolved_data_to_json_v);
}


void discord_message_interaction_from_json(char *json, size_t len, struct discord_message_interaction **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_message_interaction *p = *pp;
  discord_message_interaction_init(p);
  r=json_extract(json, len, 
  /* specs/discord/receiving_and_responding.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                "(id):F,"
  /* specs/discord/receiving_and_responding.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
                "(type):d,"
  /* specs/discord/receiving_and_responding.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
                "(name):?s,"
  /* specs/discord/receiving_and_responding.json:77:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
                "(user):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/receiving_and_responding.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                cee_strtoull, &p->id,
  /* specs/discord/receiving_and_responding.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
                &p->type,
  /* specs/discord/receiving_and_responding.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
                &p->name,
  /* specs/discord/receiving_and_responding.json:77:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
                discord_user_from_json, &p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_message_interaction_use_default_inject_settings(struct discord_message_interaction *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/receiving_and_responding.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/receiving_and_responding.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
  p->__M.arg_switches[1] = &p->type;

  /* specs/discord/receiving_and_responding.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
  p->__M.arg_switches[2] = p->name;

  /* specs/discord/receiving_and_responding.json:77:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
  p->__M.arg_switches[3] = p->user;

}

size_t discord_message_interaction_to_json(char *json, size_t len, struct discord_message_interaction *p)
{
  size_t r;
  discord_message_interaction_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/receiving_and_responding.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                "(id):|F|,"
  /* specs/discord/receiving_and_responding.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
                "(type):d,"
  /* specs/discord/receiving_and_responding.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
                "(name):s,"
  /* specs/discord/receiving_and_responding.json:77:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
                "(user):F,"
                "@arg_switches:b",
  /* specs/discord/receiving_and_responding.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/receiving_and_responding.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
                &p->type,
  /* specs/discord/receiving_and_responding.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
                p->name,
  /* specs/discord/receiving_and_responding.json:77:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
                discord_user_to_json, p->user,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_message_interaction_cleanup_v(void *p) {
  discord_message_interaction_cleanup((struct discord_message_interaction *)p);
}

void discord_message_interaction_init_v(void *p) {
  discord_message_interaction_init((struct discord_message_interaction *)p);
}

void discord_message_interaction_from_json_v(char *json, size_t len, void *pp) {
 discord_message_interaction_from_json(json, len, (struct discord_message_interaction**)pp);
}

size_t discord_message_interaction_to_json_v(char *json, size_t len, void *p) {
  return discord_message_interaction_to_json(json, len, (struct discord_message_interaction*)p);
}

void discord_message_interaction_list_free_v(void **p) {
  discord_message_interaction_list_free((struct discord_message_interaction**)p);
}

void discord_message_interaction_list_from_json_v(char *str, size_t len, void *p) {
  discord_message_interaction_list_from_json(str, len, (struct discord_message_interaction ***)p);
}

size_t discord_message_interaction_list_to_json_v(char *str, size_t len, void *p){
  return discord_message_interaction_list_to_json(str, len, (struct discord_message_interaction **)p);
}


void discord_message_interaction_cleanup(struct discord_message_interaction *d) {
  /* specs/discord/receiving_and_responding.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  // p->id is a scalar
  /* specs/discord/receiving_and_responding.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */
  // p->type is a scalar
  /* specs/discord/receiving_and_responding.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/receiving_and_responding.json:77:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
}

void discord_message_interaction_init(struct discord_message_interaction *p) {
  memset(p, 0, sizeof(struct discord_message_interaction));
  /* specs/discord/receiving_and_responding.json:74:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */

  /* specs/discord/receiving_and_responding.json:75:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_types"}, "comment":"the request type of the interaction"}' */

  /* specs/discord/receiving_and_responding.json:76:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */

  /* specs/discord/receiving_and_responding.json:77:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */

}
void discord_message_interaction_list_free(struct discord_message_interaction **p) {
  ntl_free((void**)p, (vfvp)discord_message_interaction_cleanup);
}

void discord_message_interaction_list_from_json(char *str, size_t len, struct discord_message_interaction ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_message_interaction);
  d.init_elem = NULL;
  d.elem_from_buf = discord_message_interaction_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_message_interaction_list_to_json(char *str, size_t len, struct discord_message_interaction **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_message_interaction_to_json_v);
}


void discord_interaction_response_from_json(char *json, size_t len, struct discord_interaction_response **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_interaction_response *p = *pp;
  discord_interaction_response_init(p);
  r=json_extract(json, len, 
  /* specs/discord/receiving_and_responding.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
                "(type):d,"
  /* specs/discord/receiving_and_responding.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
                "(data):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/receiving_and_responding.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
                &p->type,
  /* specs/discord/receiving_and_responding.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
                discord_interaction_callback_data_from_json, &p->data,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_interaction_response_use_default_inject_settings(struct discord_interaction_response *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/receiving_and_responding.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
  p->__M.arg_switches[0] = &p->type;

  /* specs/discord/receiving_and_responding.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  if (p->data != NULL)
    p->__M.arg_switches[1] = p->data;

}

size_t discord_interaction_response_to_json(char *json, size_t len, struct discord_interaction_response *p)
{
  size_t r;
  discord_interaction_response_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/receiving_and_responding.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
                "(type):d,"
  /* specs/discord/receiving_and_responding.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
                "(data):F,"
                "@arg_switches:b",
  /* specs/discord/receiving_and_responding.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
                &p->type,
  /* specs/discord/receiving_and_responding.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
                discord_interaction_callback_data_to_json, p->data,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_interaction_response_cleanup_v(void *p) {
  discord_interaction_response_cleanup((struct discord_interaction_response *)p);
}

void discord_interaction_response_init_v(void *p) {
  discord_interaction_response_init((struct discord_interaction_response *)p);
}

void discord_interaction_response_from_json_v(char *json, size_t len, void *pp) {
 discord_interaction_response_from_json(json, len, (struct discord_interaction_response**)pp);
}

size_t discord_interaction_response_to_json_v(char *json, size_t len, void *p) {
  return discord_interaction_response_to_json(json, len, (struct discord_interaction_response*)p);
}

void discord_interaction_response_list_free_v(void **p) {
  discord_interaction_response_list_free((struct discord_interaction_response**)p);
}

void discord_interaction_response_list_from_json_v(char *str, size_t len, void *p) {
  discord_interaction_response_list_from_json(str, len, (struct discord_interaction_response ***)p);
}

size_t discord_interaction_response_list_to_json_v(char *str, size_t len, void *p){
  return discord_interaction_response_list_to_json(str, len, (struct discord_interaction_response **)p);
}


void discord_interaction_response_cleanup(struct discord_interaction_response *d) {
  /* specs/discord/receiving_and_responding.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
  // p->type is a scalar
  /* specs/discord/receiving_and_responding.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  if (d->data) {
    discord_interaction_callback_data_cleanup(d->data);
    free(d->data);
  }
}

void discord_interaction_response_init(struct discord_interaction_response *p) {
  memset(p, 0, sizeof(struct discord_interaction_response));
  /* specs/discord/receiving_and_responding.json:87:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */

  /* specs/discord/receiving_and_responding.json:88:18
     '{"name":"data", "type":{"base":"struct discord_interaction_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */

}
void discord_interaction_response_list_free(struct discord_interaction_response **p) {
  ntl_free((void**)p, (vfvp)discord_interaction_response_cleanup);
}

void discord_interaction_response_list_from_json(char *str, size_t len, struct discord_interaction_response ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_interaction_response);
  d.init_elem = NULL;
  d.elem_from_buf = discord_interaction_response_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_interaction_response_list_to_json(char *str, size_t len, struct discord_interaction_response **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_interaction_response_to_json_v);
}



enum discord_interaction_callback_types discord_interaction_callback_types_eval(char *s){
  if(strcasecmp("PONG", s) == 0) return DISCORD_INTERACTION_CALLBACK_PONG;
  if(strcasecmp("CHANNEL_MESSAGE_WITH_SOURCE", s) == 0) return DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE;
  if(strcasecmp("DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE", s) == 0) return DISCORD_INTERACTION_CALLBACK_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE;
  if(strcasecmp("DEFERRED_UPDATE_MESSAGE", s) == 0) return DISCORD_INTERACTION_CALLBACK_DEFERRED_UPDATE_MESSAGE;
  if(strcasecmp("UPDATE_MESSAGE", s) == 0) return DISCORD_INTERACTION_CALLBACK_UPDATE_MESSAGE;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_interaction_callback_types_print(enum discord_interaction_callback_types v){

  switch (v) {
  case DISCORD_INTERACTION_CALLBACK_PONG: return "PONG";
  case DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE: return "CHANNEL_MESSAGE_WITH_SOURCE";
  case DISCORD_INTERACTION_CALLBACK_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE: return "DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE";
  case DISCORD_INTERACTION_CALLBACK_DEFERRED_UPDATE_MESSAGE: return "DEFERRED_UPDATE_MESSAGE";
  case DISCORD_INTERACTION_CALLBACK_UPDATE_MESSAGE: return "UPDATE_MESSAGE";
  }

  return NULL;
}

void discord_interaction_callback_data_from_json(char *json, size_t len, struct discord_interaction_callback_data **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_interaction_callback_data *p = *pp;
  discord_interaction_callback_data_init(p);
  r=json_extract(json, len, 
  /* specs/discord/receiving_and_responding.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
                "(tts):b,"
  /* specs/discord/receiving_and_responding.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
                "(content):?s,"
  /* specs/discord/receiving_and_responding.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
                "(embeds):F,"
  /* specs/discord/receiving_and_responding.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  /* specs/discord/receiving_and_responding.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
                "(flags):d,"
  /* specs/discord/receiving_and_responding.json:117:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
                "(components):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/receiving_and_responding.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
                &p->tts,
  /* specs/discord/receiving_and_responding.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
                &p->content,
  /* specs/discord/receiving_and_responding.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
                discord_embed_list_from_json, &p->embeds,
  /* specs/discord/receiving_and_responding.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  /* specs/discord/receiving_and_responding.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
                &p->flags,
  /* specs/discord/receiving_and_responding.json:117:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
                discord_component_list_from_json, &p->components,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_interaction_callback_data_use_default_inject_settings(struct discord_interaction_callback_data *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/receiving_and_responding.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
  p->__M.arg_switches[0] = &p->tts;

  /* specs/discord/receiving_and_responding.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
  if (p->content != NULL)
    p->__M.arg_switches[1] = p->content;

  /* specs/discord/receiving_and_responding.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
  if (p->embeds != NULL)
    p->__M.arg_switches[2] = p->embeds;

  /* specs/discord/receiving_and_responding.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */

  /* specs/discord/receiving_and_responding.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
  if (p->flags != 0)
    p->__M.arg_switches[4] = &p->flags;

  /* specs/discord/receiving_and_responding.json:117:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
  if (p->components != NULL)
    p->__M.arg_switches[5] = p->components;

}

size_t discord_interaction_callback_data_to_json(char *json, size_t len, struct discord_interaction_callback_data *p)
{
  size_t r;
  discord_interaction_callback_data_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/receiving_and_responding.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
                "(tts):b,"
  /* specs/discord/receiving_and_responding.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
                "(content):s,"
  /* specs/discord/receiving_and_responding.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
                "(embeds):F,"
  /* specs/discord/receiving_and_responding.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  /* specs/discord/receiving_and_responding.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
                "(flags):d,"
  /* specs/discord/receiving_and_responding.json:117:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
                "(components):F,"
                "@arg_switches:b",
  /* specs/discord/receiving_and_responding.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
                &p->tts,
  /* specs/discord/receiving_and_responding.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
                p->content,
  /* specs/discord/receiving_and_responding.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
                discord_embed_list_to_json, p->embeds,
  /* specs/discord/receiving_and_responding.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  /* specs/discord/receiving_and_responding.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
                &p->flags,
  /* specs/discord/receiving_and_responding.json:117:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
                discord_component_list_to_json, p->components,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_interaction_callback_data_cleanup_v(void *p) {
  discord_interaction_callback_data_cleanup((struct discord_interaction_callback_data *)p);
}

void discord_interaction_callback_data_init_v(void *p) {
  discord_interaction_callback_data_init((struct discord_interaction_callback_data *)p);
}

void discord_interaction_callback_data_from_json_v(char *json, size_t len, void *pp) {
 discord_interaction_callback_data_from_json(json, len, (struct discord_interaction_callback_data**)pp);
}

size_t discord_interaction_callback_data_to_json_v(char *json, size_t len, void *p) {
  return discord_interaction_callback_data_to_json(json, len, (struct discord_interaction_callback_data*)p);
}

void discord_interaction_callback_data_list_free_v(void **p) {
  discord_interaction_callback_data_list_free((struct discord_interaction_callback_data**)p);
}

void discord_interaction_callback_data_list_from_json_v(char *str, size_t len, void *p) {
  discord_interaction_callback_data_list_from_json(str, len, (struct discord_interaction_callback_data ***)p);
}

size_t discord_interaction_callback_data_list_to_json_v(char *str, size_t len, void *p){
  return discord_interaction_callback_data_list_to_json(str, len, (struct discord_interaction_callback_data **)p);
}


void discord_interaction_callback_data_cleanup(struct discord_interaction_callback_data *d) {
  /* specs/discord/receiving_and_responding.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
  // p->tts is a scalar
  /* specs/discord/receiving_and_responding.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
  if (d->content)
    free(d->content);
  /* specs/discord/receiving_and_responding.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* specs/discord/receiving_and_responding.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  // @todo p->(null)
  /* specs/discord/receiving_and_responding.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
  // p->flags is a scalar
  /* specs/discord/receiving_and_responding.json:117:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
  if (d->components)
    discord_component_list_free(d->components);
}

void discord_interaction_callback_data_init(struct discord_interaction_callback_data *p) {
  memset(p, 0, sizeof(struct discord_interaction_callback_data));
  /* specs/discord/receiving_and_responding.json:112:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */

  /* specs/discord/receiving_and_responding.json:113:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:114:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */

  /* specs/discord/receiving_and_responding.json:115:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */

  /* specs/discord/receiving_and_responding.json:116:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */

  /* specs/discord/receiving_and_responding.json:117:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */

}
void discord_interaction_callback_data_list_free(struct discord_interaction_callback_data **p) {
  ntl_free((void**)p, (vfvp)discord_interaction_callback_data_cleanup);
}

void discord_interaction_callback_data_list_from_json(char *str, size_t len, struct discord_interaction_callback_data ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_interaction_callback_data);
  d.init_elem = NULL;
  d.elem_from_buf = discord_interaction_callback_data_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_interaction_callback_data_list_to_json(char *str, size_t len, struct discord_interaction_callback_data **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_interaction_callback_data_to_json_v);
}



enum discord_interaction_callback_data_flags discord_interaction_callback_data_flags_eval(char *s){
  if(strcasecmp("EPHEMERAL", s) == 0) return DISCORD_INTERACTION_CALLBACK_DATA_EPHEMERAL;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_interaction_callback_data_flags_print(enum discord_interaction_callback_data_flags v){

  switch (v) {
  case DISCORD_INTERACTION_CALLBACK_DATA_EPHEMERAL: return "EPHEMERAL";
  }

  return NULL;
}
