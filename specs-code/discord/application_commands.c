/* This file is generated from discord/application_commands.json, Please don't edit it. */
/**
 * @file specs-code/discord/application_commands.c
 * @see https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-structure
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_application_command_from_json_p(char *json, size_t len, struct discord_application_command **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_application_command_from_json(json, len, *pp);
}
void discord_application_command_from_json(char *json, size_t len, struct discord_application_command *p)
{
  discord_application_command_init(p);
  json_extract(json, len, 
  /* discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                "(id):F,"
  /* discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
                "(type):d,"
  /* discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                "(application_id):F,"
  /* discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
                "(guild_id):F,"
  /* discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 character name"}' */
                "(name):?s,"
  /* discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
                "(description):?s,"
  /* discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,",
  /* discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                cee_strtou64, &p->id,
  /* discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
                &p->type,
  /* discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                cee_strtou64, &p->application_id,
  /* discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
                cee_strtou64, &p->guild_id,
  /* discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 character name"}' */
                &p->name,
  /* discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
                &p->description,
  /* discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
  /* discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission);
}

size_t discord_application_command_to_json(char *json, size_t len, struct discord_application_command *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  arg_switches[0] = &p->id;

  /* discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
  if (p->type != 0)
    arg_switches[1] = &p->type;

  /* discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  arg_switches[2] = &p->application_id;

  /* discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
  if (p->guild_id != 0)
    arg_switches[3] = &p->guild_id;

  /* discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 character name"}' */
  arg_switches[4] = p->name;

  /* discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
  arg_switches[5] = p->description;

  /* discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[6] = p->options;

  /* discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  arg_switches[7] = &p->default_permission;

  r=json_inject(json, len, 
  /* discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                "(id):|F|,"
  /* discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
                "(type):d,"
  /* discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                "(application_id):|F|,"
  /* discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
                "(guild_id):|F|,"
  /* discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 character name"}' */
                "(name):s,"
  /* discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
                "(description):s,"
  /* discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
                "@arg_switches:b",
  /* discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                cee_u64tostr, &p->id,
  /* discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
                &p->type,
  /* discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                cee_u64tostr, &p->application_id,
  /* discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
                cee_u64tostr, &p->guild_id,
  /* discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 character name"}' */
                p->name,
  /* discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
                p->description,
  /* discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
  /* discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_application_command_cleanup_v(void *p) {
  discord_application_command_cleanup((struct discord_application_command *)p);
}

void discord_application_command_init_v(void *p) {
  discord_application_command_init((struct discord_application_command *)p);
}

void discord_application_command_from_json_v(char *json, size_t len, void *p) {
 discord_application_command_from_json(json, len, (struct discord_application_command*)p);
}

size_t discord_application_command_to_json_v(char *json, size_t len, void *p) {
  return discord_application_command_to_json(json, len, (struct discord_application_command*)p);
}

void discord_application_command_list_free_v(void **p) {
  discord_application_command_list_free((struct discord_application_command**)p);
}

void discord_application_command_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_list_from_json(str, len, (struct discord_application_command ***)p);
}

size_t discord_application_command_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_list_to_json(str, len, (struct discord_application_command **)p);
}


void discord_application_command_cleanup(struct discord_application_command *d) {
  /* discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  (void)d->id;
  /* discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
  (void)d->type;
  /* discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  (void)d->application_id;
  /* discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
  (void)d->guild_id;
  /* discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 character name"}' */
  if (d->name)
    free(d->name);
  /* discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
  if (d->description)
    free(d->description);
  /* discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
  /* discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  (void)d->default_permission;
}

void discord_application_command_init(struct discord_application_command *p) {
  memset(p, 0, sizeof(struct discord_application_command));
  /* discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */

  /* discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */

  /* discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */

  /* discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */

  /* discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 character name"}' */

  /* discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */

  /* discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */

  /* discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */

}
void discord_application_command_list_free(struct discord_application_command **p) {
  ntl_free((void**)p, (void(*)(void*))discord_application_command_cleanup);
}

void discord_application_command_list_from_json(char *str, size_t len, struct discord_application_command ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_application_command_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_list_to_json(char *str, size_t len, struct discord_application_command **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_application_command_to_json);
}



void discord_application_command_types_list_free_v(void **p) {
  discord_application_command_types_list_free((enum discord_application_command_types**)p);
}

void discord_application_command_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_types_list_from_json(str, len, (enum discord_application_command_types ***)p);
}

size_t discord_application_command_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_types_list_to_json(str, len, (enum discord_application_command_types **)p);
}

enum discord_application_command_types discord_application_command_types_eval(char *s){
  if(strcasecmp("CHAT_INPUT", s) == 0) return DISCORD_APPLICATION_COMMAND_CHAT_INPUT;
  if(strcasecmp("USER", s) == 0) return DISCORD_APPLICATION_COMMAND_USER;
  if(strcasecmp("MESSAGE", s) == 0) return DISCORD_APPLICATION_COMMAND_MESSAGE;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_application_command_types_print(enum discord_application_command_types v){

  switch (v) {
  case DISCORD_APPLICATION_COMMAND_CHAT_INPUT: return "CHAT_INPUT";
  case DISCORD_APPLICATION_COMMAND_USER: return "USER";
  case DISCORD_APPLICATION_COMMAND_MESSAGE: return "MESSAGE";
  }

  return NULL;
}

void discord_application_command_types_list_free(enum discord_application_command_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_application_command_types_list_from_json(char *str, size_t len, enum discord_application_command_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_application_command_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_types_list_to_json(char *str, size_t len, enum discord_application_command_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_application_command_option_from_json_p(char *json, size_t len, struct discord_application_command_option **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_application_command_option_from_json(json, len, *pp);
}
void discord_application_command_option_from_json(char *json, size_t len, struct discord_application_command_option *p)
{
  discord_application_command_option_init(p);
  json_extract(json, len, 
  /* discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 lowercase character"}' */
                "(name):?s,"
  /* discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description"}' */
                "(description):?s,"
  /* discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
                "(required):b,"
  /* discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                "(choices):F,"
  /* discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.json:47:18
     '{"name":"channel_types", "type":{"base":"ja_u64", "dec":"ntl"}, "comment":"if the option is a channel type, the channels shown will be restricted to these types", "inject_if_not":null}' */
                "(channel_types):F,"
  /* discord/application_commands.json:48:18
     '{"name":"min_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the minimum value permitted", "inject_if_not":null}' */
                "(min_value):F,"
  /* discord/application_commands.json:49:18
     '{"name":"max_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the maximum value permitted", "inject_if_not":null}' */
                "(max_value):F,"
  /* discord/application_commands.json:50:18
     '{"name":"autocomplete", "type":{"base":"bool"}, "comment":"enable autocomplete interactions for this option", "inject_if_not":false}' */
                "(autocomplete):b,",
  /* discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 lowercase character"}' */
                &p->name,
  /* discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description"}' */
                &p->description,
  /* discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
                &p->required,
  /* discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                discord_application_command_option_choice_list_from_json, &p->choices,
  /* discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
  /* discord/application_commands.json:47:18
     '{"name":"channel_types", "type":{"base":"ja_u64", "dec":"ntl"}, "comment":"if the option is a channel type, the channels shown will be restricted to these types", "inject_if_not":null}' */
                ja_u64_list_from_json, &p->channel_types,
  /* discord/application_commands.json:48:18
     '{"name":"min_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the minimum value permitted", "inject_if_not":null}' */
                cee_strndup, &p->min_value,
  /* discord/application_commands.json:49:18
     '{"name":"max_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the maximum value permitted", "inject_if_not":null}' */
                cee_strndup, &p->max_value,
  /* discord/application_commands.json:50:18
     '{"name":"autocomplete", "type":{"base":"bool"}, "comment":"enable autocomplete interactions for this option", "inject_if_not":false}' */
                &p->autocomplete);
}

size_t discord_application_command_option_to_json(char *json, size_t len, struct discord_application_command_option *p)
{
  size_t r;
  void *arg_switches[10]={NULL};
  /* discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  arg_switches[0] = &p->type;

  /* discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 lowercase character"}' */
  arg_switches[1] = p->name;

  /* discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description"}' */
  arg_switches[2] = p->description;

  /* discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
  arg_switches[3] = &p->required;

  /* discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  if (p->choices != NULL)
    arg_switches[4] = p->choices;

  /* discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[5] = p->options;

  /* discord/application_commands.json:47:18
     '{"name":"channel_types", "type":{"base":"ja_u64", "dec":"ntl"}, "comment":"if the option is a channel type, the channels shown will be restricted to these types", "inject_if_not":null}' */
  if (p->channel_types != NULL)
    arg_switches[6] = p->channel_types;

  /* discord/application_commands.json:48:18
     '{"name":"min_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the minimum value permitted", "inject_if_not":null}' */
  if (p->min_value != NULL)
    arg_switches[7] = p->min_value;

  /* discord/application_commands.json:49:18
     '{"name":"max_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the maximum value permitted", "inject_if_not":null}' */
  if (p->max_value != NULL)
    arg_switches[8] = p->max_value;

  /* discord/application_commands.json:50:18
     '{"name":"autocomplete", "type":{"base":"bool"}, "comment":"enable autocomplete interactions for this option", "inject_if_not":false}' */
  if (p->autocomplete != false)
    arg_switches[9] = &p->autocomplete;

  r=json_inject(json, len, 
  /* discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 lowercase character"}' */
                "(name):s,"
  /* discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description"}' */
                "(description):s,"
  /* discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
                "(required):b,"
  /* discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                "(choices):F,"
  /* discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.json:47:18
     '{"name":"channel_types", "type":{"base":"ja_u64", "dec":"ntl"}, "comment":"if the option is a channel type, the channels shown will be restricted to these types", "inject_if_not":null}' */
                "(channel_types):F,"
  /* discord/application_commands.json:48:18
     '{"name":"min_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the minimum value permitted", "inject_if_not":null}' */
                "(min_value):s,"
  /* discord/application_commands.json:49:18
     '{"name":"max_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the maximum value permitted", "inject_if_not":null}' */
                "(max_value):s,"
  /* discord/application_commands.json:50:18
     '{"name":"autocomplete", "type":{"base":"bool"}, "comment":"enable autocomplete interactions for this option", "inject_if_not":false}' */
                "(autocomplete):b,"
                "@arg_switches:b",
  /* discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 lowercase character"}' */
                p->name,
  /* discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description"}' */
                p->description,
  /* discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
                &p->required,
  /* discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                discord_application_command_option_choice_list_to_json, p->choices,
  /* discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
  /* discord/application_commands.json:47:18
     '{"name":"channel_types", "type":{"base":"ja_u64", "dec":"ntl"}, "comment":"if the option is a channel type, the channels shown will be restricted to these types", "inject_if_not":null}' */
                ja_u64_list_to_json, p->channel_types,
  /* discord/application_commands.json:48:18
     '{"name":"min_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the minimum value permitted", "inject_if_not":null}' */
                p->min_value,
  /* discord/application_commands.json:49:18
     '{"name":"max_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the maximum value permitted", "inject_if_not":null}' */
                p->max_value,
  /* discord/application_commands.json:50:18
     '{"name":"autocomplete", "type":{"base":"bool"}, "comment":"enable autocomplete interactions for this option", "inject_if_not":false}' */
                &p->autocomplete,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_application_command_option_cleanup_v(void *p) {
  discord_application_command_option_cleanup((struct discord_application_command_option *)p);
}

void discord_application_command_option_init_v(void *p) {
  discord_application_command_option_init((struct discord_application_command_option *)p);
}

void discord_application_command_option_from_json_v(char *json, size_t len, void *p) {
 discord_application_command_option_from_json(json, len, (struct discord_application_command_option*)p);
}

size_t discord_application_command_option_to_json_v(char *json, size_t len, void *p) {
  return discord_application_command_option_to_json(json, len, (struct discord_application_command_option*)p);
}

void discord_application_command_option_list_free_v(void **p) {
  discord_application_command_option_list_free((struct discord_application_command_option**)p);
}

void discord_application_command_option_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_option_list_from_json(str, len, (struct discord_application_command_option ***)p);
}

size_t discord_application_command_option_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_option_list_to_json(str, len, (struct discord_application_command_option **)p);
}


void discord_application_command_option_cleanup(struct discord_application_command_option *d) {
  /* discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  (void)d->type;
  /* discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 lowercase character"}' */
  if (d->name)
    free(d->name);
  /* discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description"}' */
  if (d->description)
    free(d->description);
  /* discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
  (void)d->required;
  /* discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  if (d->choices)
    discord_application_command_option_choice_list_free(d->choices);
  /* discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
  /* discord/application_commands.json:47:18
     '{"name":"channel_types", "type":{"base":"ja_u64", "dec":"ntl"}, "comment":"if the option is a channel type, the channels shown will be restricted to these types", "inject_if_not":null}' */
  if (d->channel_types)
    ja_u64_list_free(d->channel_types);
  /* discord/application_commands.json:48:18
     '{"name":"min_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the minimum value permitted", "inject_if_not":null}' */
  if (d->min_value)
    free(d->min_value);
  /* discord/application_commands.json:49:18
     '{"name":"max_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the maximum value permitted", "inject_if_not":null}' */
  if (d->max_value)
    free(d->max_value);
  /* discord/application_commands.json:50:18
     '{"name":"autocomplete", "type":{"base":"bool"}, "comment":"enable autocomplete interactions for this option", "inject_if_not":false}' */
  (void)d->autocomplete;
}

void discord_application_command_option_init(struct discord_application_command_option *p) {
  memset(p, 0, sizeof(struct discord_application_command_option));
  /* discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */

  /* discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-32 lowercase character"}' */

  /* discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character description"}' */

  /* discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */

  /* discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */

  /* discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */

  /* discord/application_commands.json:47:18
     '{"name":"channel_types", "type":{"base":"ja_u64", "dec":"ntl"}, "comment":"if the option is a channel type, the channels shown will be restricted to these types", "inject_if_not":null}' */

  /* discord/application_commands.json:48:18
     '{"name":"min_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the minimum value permitted", "inject_if_not":null}' */

  /* discord/application_commands.json:49:18
     '{"name":"max_value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"if the option is an INTEGER or NUMBER type, the maximum value permitted", "inject_if_not":null}' */

  /* discord/application_commands.json:50:18
     '{"name":"autocomplete", "type":{"base":"bool"}, "comment":"enable autocomplete interactions for this option", "inject_if_not":false}' */

}
void discord_application_command_option_list_free(struct discord_application_command_option **p) {
  ntl_free((void**)p, (void(*)(void*))discord_application_command_option_cleanup);
}

void discord_application_command_option_list_from_json(char *str, size_t len, struct discord_application_command_option ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_option);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_application_command_option_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_option_list_to_json(char *str, size_t len, struct discord_application_command_option **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_application_command_option_to_json);
}



void discord_application_command_option_types_list_free_v(void **p) {
  discord_application_command_option_types_list_free((enum discord_application_command_option_types**)p);
}

void discord_application_command_option_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_option_types_list_from_json(str, len, (enum discord_application_command_option_types ***)p);
}

size_t discord_application_command_option_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_option_types_list_to_json(str, len, (enum discord_application_command_option_types **)p);
}

enum discord_application_command_option_types discord_application_command_option_types_eval(char *s){
  if(strcasecmp("SUB_COMMAND", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND;
  if(strcasecmp("SUB_COMMAND_GROUP", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND_GROUP;
  if(strcasecmp("STRING", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_STRING;
  if(strcasecmp("INTEGER", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_INTEGER;
  if(strcasecmp("BOOLEAN", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_BOOLEAN;
  if(strcasecmp("USER", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_USER;
  if(strcasecmp("CHANNEL", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL;
  if(strcasecmp("ROLE", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_ROLE;
  if(strcasecmp("MENTIONABLE", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_MENTIONABLE;
  if(strcasecmp("NUMBER", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_NUMBER;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_application_command_option_types_print(enum discord_application_command_option_types v){

  switch (v) {
  case DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND: return "SUB_COMMAND";
  case DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND_GROUP: return "SUB_COMMAND_GROUP";
  case DISCORD_APPLICATION_COMMAND_OPTION_STRING: return "STRING";
  case DISCORD_APPLICATION_COMMAND_OPTION_INTEGER: return "INTEGER";
  case DISCORD_APPLICATION_COMMAND_OPTION_BOOLEAN: return "BOOLEAN";
  case DISCORD_APPLICATION_COMMAND_OPTION_USER: return "USER";
  case DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL: return "CHANNEL";
  case DISCORD_APPLICATION_COMMAND_OPTION_ROLE: return "ROLE";
  case DISCORD_APPLICATION_COMMAND_OPTION_MENTIONABLE: return "MENTIONABLE";
  case DISCORD_APPLICATION_COMMAND_OPTION_NUMBER: return "NUMBER";
  }

  return NULL;
}

void discord_application_command_option_types_list_free(enum discord_application_command_option_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_application_command_option_types_list_from_json(char *str, size_t len, enum discord_application_command_option_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_application_command_option_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_option_types_list_to_json(char *str, size_t len, enum discord_application_command_option_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_application_command_option_choice_from_json_p(char *json, size_t len, struct discord_application_command_option_choice **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_application_command_option_choice_from_json(json, len, *pp);
}
void discord_application_command_option_choice_from_json(char *json, size_t len, struct discord_application_command_option_choice *p)
{
  discord_application_command_option_choice_init(p);
  json_extract(json, len, 
  /* discord/application_commands.json:79:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character choice name"}' */
                "(name):?s,"
  /* discord/application_commands.json:80:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
                "(value):F,",
  /* discord/application_commands.json:79:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character choice name"}' */
                &p->name,
  /* discord/application_commands.json:80:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
                cee_strndup, &p->value);
}

size_t discord_application_command_option_choice_to_json(char *json, size_t len, struct discord_application_command_option_choice *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/application_commands.json:79:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character choice name"}' */
  arg_switches[0] = p->name;

  /* discord/application_commands.json:80:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
  arg_switches[1] = p->value;

  r=json_inject(json, len, 
  /* discord/application_commands.json:79:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character choice name"}' */
                "(name):s,"
  /* discord/application_commands.json:80:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
                "(value):s,"
                "@arg_switches:b",
  /* discord/application_commands.json:79:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character choice name"}' */
                p->name,
  /* discord/application_commands.json:80:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
                p->value,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_application_command_option_choice_cleanup_v(void *p) {
  discord_application_command_option_choice_cleanup((struct discord_application_command_option_choice *)p);
}

void discord_application_command_option_choice_init_v(void *p) {
  discord_application_command_option_choice_init((struct discord_application_command_option_choice *)p);
}

void discord_application_command_option_choice_from_json_v(char *json, size_t len, void *p) {
 discord_application_command_option_choice_from_json(json, len, (struct discord_application_command_option_choice*)p);
}

size_t discord_application_command_option_choice_to_json_v(char *json, size_t len, void *p) {
  return discord_application_command_option_choice_to_json(json, len, (struct discord_application_command_option_choice*)p);
}

void discord_application_command_option_choice_list_free_v(void **p) {
  discord_application_command_option_choice_list_free((struct discord_application_command_option_choice**)p);
}

void discord_application_command_option_choice_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_option_choice_list_from_json(str, len, (struct discord_application_command_option_choice ***)p);
}

size_t discord_application_command_option_choice_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_option_choice_list_to_json(str, len, (struct discord_application_command_option_choice **)p);
}


void discord_application_command_option_choice_cleanup(struct discord_application_command_option_choice *d) {
  /* discord/application_commands.json:79:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character choice name"}' */
  if (d->name)
    free(d->name);
  /* discord/application_commands.json:80:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
  if (d->value)
    free(d->value);
}

void discord_application_command_option_choice_init(struct discord_application_command_option_choice *p) {
  memset(p, 0, sizeof(struct discord_application_command_option_choice));
  /* discord/application_commands.json:79:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"1-100 character choice name"}' */

  /* discord/application_commands.json:80:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */

}
void discord_application_command_option_choice_list_free(struct discord_application_command_option_choice **p) {
  ntl_free((void**)p, (void(*)(void*))discord_application_command_option_choice_cleanup);
}

void discord_application_command_option_choice_list_from_json(char *str, size_t len, struct discord_application_command_option_choice ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_option_choice);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_application_command_option_choice_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_option_choice_list_to_json(char *str, size_t len, struct discord_application_command_option_choice **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_application_command_option_choice_to_json);
}


void discord_guild_application_command_permissions_from_json_p(char *json, size_t len, struct discord_guild_application_command_permissions **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_guild_application_command_permissions_from_json(json, len, *pp);
}
void discord_guild_application_command_permissions_from_json(char *json, size_t len, struct discord_guild_application_command_permissions *p)
{
  discord_guild_application_command_permissions_init(p);
  json_extract(json, len, 
  /* discord/application_commands.json:90:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):F,"
  /* discord/application_commands.json:91:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                "(application_id):F,"
  /* discord/application_commands.json:92:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                "(guild_id):F,"
  /* discord/application_commands.json:93:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                "(permissions):F,",
  /* discord/application_commands.json:90:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_strtou64, &p->id,
  /* discord/application_commands.json:91:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                cee_strtou64, &p->application_id,
  /* discord/application_commands.json:92:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                cee_strtou64, &p->guild_id,
  /* discord/application_commands.json:93:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                discord_application_command_permissions_list_from_json, &p->permissions);
}

size_t discord_guild_application_command_permissions_to_json(char *json, size_t len, struct discord_guild_application_command_permissions *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/application_commands.json:90:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  arg_switches[0] = &p->id;

  /* discord/application_commands.json:91:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  arg_switches[1] = &p->application_id;

  /* discord/application_commands.json:92:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  arg_switches[2] = &p->guild_id;

  /* discord/application_commands.json:93:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  arg_switches[3] = p->permissions;

  r=json_inject(json, len, 
  /* discord/application_commands.json:90:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):|F|,"
  /* discord/application_commands.json:91:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                "(application_id):|F|,"
  /* discord/application_commands.json:92:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                "(guild_id):|F|,"
  /* discord/application_commands.json:93:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                "(permissions):F,"
                "@arg_switches:b",
  /* discord/application_commands.json:90:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_u64tostr, &p->id,
  /* discord/application_commands.json:91:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                cee_u64tostr, &p->application_id,
  /* discord/application_commands.json:92:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                cee_u64tostr, &p->guild_id,
  /* discord/application_commands.json:93:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                discord_application_command_permissions_list_to_json, p->permissions,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_guild_application_command_permissions_cleanup_v(void *p) {
  discord_guild_application_command_permissions_cleanup((struct discord_guild_application_command_permissions *)p);
}

void discord_guild_application_command_permissions_init_v(void *p) {
  discord_guild_application_command_permissions_init((struct discord_guild_application_command_permissions *)p);
}

void discord_guild_application_command_permissions_from_json_v(char *json, size_t len, void *p) {
 discord_guild_application_command_permissions_from_json(json, len, (struct discord_guild_application_command_permissions*)p);
}

size_t discord_guild_application_command_permissions_to_json_v(char *json, size_t len, void *p) {
  return discord_guild_application_command_permissions_to_json(json, len, (struct discord_guild_application_command_permissions*)p);
}

void discord_guild_application_command_permissions_list_free_v(void **p) {
  discord_guild_application_command_permissions_list_free((struct discord_guild_application_command_permissions**)p);
}

void discord_guild_application_command_permissions_list_from_json_v(char *str, size_t len, void *p) {
  discord_guild_application_command_permissions_list_from_json(str, len, (struct discord_guild_application_command_permissions ***)p);
}

size_t discord_guild_application_command_permissions_list_to_json_v(char *str, size_t len, void *p){
  return discord_guild_application_command_permissions_list_to_json(str, len, (struct discord_guild_application_command_permissions **)p);
}


void discord_guild_application_command_permissions_cleanup(struct discord_guild_application_command_permissions *d) {
  /* discord/application_commands.json:90:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  (void)d->id;
  /* discord/application_commands.json:91:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  (void)d->application_id;
  /* discord/application_commands.json:92:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  (void)d->guild_id;
  /* discord/application_commands.json:93:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  if (d->permissions)
    discord_application_command_permissions_list_free(d->permissions);
}

void discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions *p) {
  memset(p, 0, sizeof(struct discord_guild_application_command_permissions));
  /* discord/application_commands.json:90:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */

  /* discord/application_commands.json:91:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */

  /* discord/application_commands.json:92:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */

  /* discord/application_commands.json:93:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */

}
void discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions **p) {
  ntl_free((void**)p, (void(*)(void*))discord_guild_application_command_permissions_cleanup);
}

void discord_guild_application_command_permissions_list_from_json(char *str, size_t len, struct discord_guild_application_command_permissions ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_application_command_permissions);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_guild_application_command_permissions_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_application_command_permissions_list_to_json(char *str, size_t len, struct discord_guild_application_command_permissions **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_guild_application_command_permissions_to_json);
}


void discord_application_command_permissions_from_json_p(char *json, size_t len, struct discord_application_command_permissions **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_application_command_permissions_from_json(json, len, *pp);
}
void discord_application_command_permissions_from_json(char *json, size_t len, struct discord_application_command_permissions *p)
{
  discord_application_command_permissions_init(p);
  json_extract(json, len, 
  /* discord/application_commands.json:103:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):F,"
  /* discord/application_commands.json:104:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                "(type):d,"
  /* discord/application_commands.json:105:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                "(permission):b,",
  /* discord/application_commands.json:103:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_strtou64, &p->id,
  /* discord/application_commands.json:104:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                &p->type,
  /* discord/application_commands.json:105:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                &p->permission);
}

size_t discord_application_command_permissions_to_json(char *json, size_t len, struct discord_application_command_permissions *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/application_commands.json:103:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  arg_switches[0] = &p->id;

  /* discord/application_commands.json:104:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  arg_switches[1] = &p->type;

  /* discord/application_commands.json:105:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  arg_switches[2] = &p->permission;

  r=json_inject(json, len, 
  /* discord/application_commands.json:103:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):|F|,"
  /* discord/application_commands.json:104:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                "(type):d,"
  /* discord/application_commands.json:105:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                "(permission):b,"
                "@arg_switches:b",
  /* discord/application_commands.json:103:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_u64tostr, &p->id,
  /* discord/application_commands.json:104:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                &p->type,
  /* discord/application_commands.json:105:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                &p->permission,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_application_command_permissions_cleanup_v(void *p) {
  discord_application_command_permissions_cleanup((struct discord_application_command_permissions *)p);
}

void discord_application_command_permissions_init_v(void *p) {
  discord_application_command_permissions_init((struct discord_application_command_permissions *)p);
}

void discord_application_command_permissions_from_json_v(char *json, size_t len, void *p) {
 discord_application_command_permissions_from_json(json, len, (struct discord_application_command_permissions*)p);
}

size_t discord_application_command_permissions_to_json_v(char *json, size_t len, void *p) {
  return discord_application_command_permissions_to_json(json, len, (struct discord_application_command_permissions*)p);
}

void discord_application_command_permissions_list_free_v(void **p) {
  discord_application_command_permissions_list_free((struct discord_application_command_permissions**)p);
}

void discord_application_command_permissions_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_permissions_list_from_json(str, len, (struct discord_application_command_permissions ***)p);
}

size_t discord_application_command_permissions_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_permissions_list_to_json(str, len, (struct discord_application_command_permissions **)p);
}


void discord_application_command_permissions_cleanup(struct discord_application_command_permissions *d) {
  /* discord/application_commands.json:103:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  (void)d->id;
  /* discord/application_commands.json:104:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  (void)d->type;
  /* discord/application_commands.json:105:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  (void)d->permission;
}

void discord_application_command_permissions_init(struct discord_application_command_permissions *p) {
  memset(p, 0, sizeof(struct discord_application_command_permissions));
  /* discord/application_commands.json:103:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */

  /* discord/application_commands.json:104:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */

  /* discord/application_commands.json:105:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */

}
void discord_application_command_permissions_list_free(struct discord_application_command_permissions **p) {
  ntl_free((void**)p, (void(*)(void*))discord_application_command_permissions_cleanup);
}

void discord_application_command_permissions_list_from_json(char *str, size_t len, struct discord_application_command_permissions ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_permissions);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_application_command_permissions_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_permissions_list_to_json(char *str, size_t len, struct discord_application_command_permissions **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_application_command_permissions_to_json);
}



void discord_application_command_permission_types_list_free_v(void **p) {
  discord_application_command_permission_types_list_free((enum discord_application_command_permission_types**)p);
}

void discord_application_command_permission_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_permission_types_list_from_json(str, len, (enum discord_application_command_permission_types ***)p);
}

size_t discord_application_command_permission_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_permission_types_list_to_json(str, len, (enum discord_application_command_permission_types **)p);
}

enum discord_application_command_permission_types discord_application_command_permission_types_eval(char *s){
  if(strcasecmp("ROLE", s) == 0) return DISCORD_APPLICATION_COMMAND_PERMISSION_ROLE;
  if(strcasecmp("USER", s) == 0) return DISCORD_APPLICATION_COMMAND_PERMISSION_USER;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_application_command_permission_types_print(enum discord_application_command_permission_types v){

  switch (v) {
  case DISCORD_APPLICATION_COMMAND_PERMISSION_ROLE: return "ROLE";
  case DISCORD_APPLICATION_COMMAND_PERMISSION_USER: return "USER";
  }

  return NULL;
}

void discord_application_command_permission_types_list_free(enum discord_application_command_permission_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_application_command_permission_types_list_from_json(char *str, size_t len, enum discord_application_command_permission_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_application_command_permission_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_permission_types_list_to_json(char *str, size_t len, enum discord_application_command_permission_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_application_command_interaction_data_option_from_json_p(char *json, size_t len, struct discord_application_command_interaction_data_option **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_application_command_interaction_data_option_from_json(json, len, *pp);
}
void discord_application_command_interaction_data_option_from_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p)
{
  discord_application_command_interaction_data_option_init(p);
  json_extract(json, len, 
  /* discord/application_commands.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                "(name):?s,"
  /* discord/application_commands.json:127:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* discord/application_commands.json:128:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
                "(value):F,"
  /* discord/application_commands.json:129:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                "(options):F,",
  /* discord/application_commands.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                &p->name,
  /* discord/application_commands.json:127:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* discord/application_commands.json:128:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
                cee_strndup, &p->value,
  /* discord/application_commands.json:129:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_from_json, &p->options);
}

size_t discord_application_command_interaction_data_option_to_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/application_commands.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  arg_switches[0] = p->name;

  /* discord/application_commands.json:127:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  arg_switches[1] = &p->type;

  /* discord/application_commands.json:128:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
  arg_switches[2] = p->value;

  /* discord/application_commands.json:129:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[3] = p->options;

  r=json_inject(json, len, 
  /* discord/application_commands.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                "(name):s,"
  /* discord/application_commands.json:127:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* discord/application_commands.json:128:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
                "(value):s,"
  /* discord/application_commands.json:129:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                "(options):F,"
                "@arg_switches:b",
  /* discord/application_commands.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                p->name,
  /* discord/application_commands.json:127:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* discord/application_commands.json:128:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
                p->value,
  /* discord/application_commands.json:129:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_to_json, p->options,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_application_command_interaction_data_option_cleanup_v(void *p) {
  discord_application_command_interaction_data_option_cleanup((struct discord_application_command_interaction_data_option *)p);
}

void discord_application_command_interaction_data_option_init_v(void *p) {
  discord_application_command_interaction_data_option_init((struct discord_application_command_interaction_data_option *)p);
}

void discord_application_command_interaction_data_option_from_json_v(char *json, size_t len, void *p) {
 discord_application_command_interaction_data_option_from_json(json, len, (struct discord_application_command_interaction_data_option*)p);
}

size_t discord_application_command_interaction_data_option_to_json_v(char *json, size_t len, void *p) {
  return discord_application_command_interaction_data_option_to_json(json, len, (struct discord_application_command_interaction_data_option*)p);
}

void discord_application_command_interaction_data_option_list_free_v(void **p) {
  discord_application_command_interaction_data_option_list_free((struct discord_application_command_interaction_data_option**)p);
}

void discord_application_command_interaction_data_option_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_interaction_data_option_list_from_json(str, len, (struct discord_application_command_interaction_data_option ***)p);
}

size_t discord_application_command_interaction_data_option_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_interaction_data_option_list_to_json(str, len, (struct discord_application_command_interaction_data_option **)p);
}


void discord_application_command_interaction_data_option_cleanup(struct discord_application_command_interaction_data_option *d) {
  /* discord/application_commands.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  if (d->name)
    free(d->name);
  /* discord/application_commands.json:127:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  (void)d->type;
  /* discord/application_commands.json:128:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
  if (d->value)
    free(d->value);
  /* discord/application_commands.json:129:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_interaction_data_option_list_free(d->options);
}

void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *p) {
  memset(p, 0, sizeof(struct discord_application_command_interaction_data_option));
  /* discord/application_commands.json:126:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */

  /* discord/application_commands.json:127:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */

  /* discord/application_commands.json:128:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */

  /* discord/application_commands.json:129:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */

}
void discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option **p) {
  ntl_free((void**)p, (void(*)(void*))discord_application_command_interaction_data_option_cleanup);
}

void discord_application_command_interaction_data_option_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_option ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_interaction_data_option);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_application_command_interaction_data_option_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_interaction_data_option_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_option **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_application_command_interaction_data_option_to_json);
}

