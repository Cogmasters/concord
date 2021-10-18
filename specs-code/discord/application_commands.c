/* This file is generated from specs/discord/application_commands.json, Please don't edit it. */
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

void discord_application_command_from_json(char *json, size_t len, struct discord_application_command **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_application_command *p = *pp;
  discord_application_command_init(p);
  r=json_extract(json, len, 
  /* specs/discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                "(id):F,"
  /* specs/discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
                "(type):d,"
  /* specs/discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                "(application_id):F,"
  /* specs/discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
                "(guild_id):F,"
  /* specs/discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 character name"}' */
                "(name):s,"
  /* specs/discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
                "(description):s,"
  /* specs/discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* specs/discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,",
  /* specs/discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                cee_strtoull, &p->id,
  /* specs/discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
                &p->type,
  /* specs/discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 character name"}' */
                p->name,
  /* specs/discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
                p->description,
  /* specs/discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
  /* specs/discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission);
  ret = r;
}

size_t discord_application_command_to_json(char *json, size_t len, struct discord_application_command *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* specs/discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  arg_switches[0] = &p->id;

  /* specs/discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
  if (p->type != 0)
    arg_switches[1] = &p->type;

  /* specs/discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  arg_switches[2] = &p->application_id;

  /* specs/discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
  if (p->guild_id != 0)
    arg_switches[3] = &p->guild_id;

  /* specs/discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 character name"}' */
  arg_switches[4] = p->name;

  /* specs/discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
  arg_switches[5] = p->description;

  /* specs/discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[6] = p->options;

  /* specs/discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  arg_switches[7] = &p->default_permission;

  r=json_inject(json, len, 
  /* specs/discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                "(id):|F|,"
  /* specs/discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
                "(type):d,"
  /* specs/discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                "(application_id):|F|,"
  /* specs/discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
                "(guild_id):|F|,"
  /* specs/discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 character name"}' */
                "(name):s,"
  /* specs/discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
                "(description):s,"
  /* specs/discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* specs/discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
                "@arg_switches:b",
  /* specs/discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
                &p->type,
  /* specs/discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 character name"}' */
                p->name,
  /* specs/discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
                p->description,
  /* specs/discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
  /* specs/discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_command_cleanup_v(void *p) {
  discord_application_command_cleanup((struct discord_application_command *)p);
}

void discord_application_command_init_v(void *p) {
  discord_application_command_init((struct discord_application_command *)p);
}

void discord_application_command_from_json_v(char *json, size_t len, void *pp) {
 discord_application_command_from_json(json, len, (struct discord_application_command**)pp);
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
  /* specs/discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  /* p->id is a scalar */
  /* specs/discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */
  /* p->type is a scalar */
  /* specs/discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  /* p->application_id is a scalar */
  /* specs/discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */
  /* p->guild_id is a scalar */
  /* specs/discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 character name"}' */
  /* p->name is a scalar */
  /* specs/discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */
  /* p->description is a scalar */
  /* specs/discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
  /* specs/discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  /* p->default_permission is a scalar */
}

void discord_application_command_init(struct discord_application_command *p) {
  memset(p, 0, sizeof(struct discord_application_command));
  /* specs/discord/application_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */

  /* specs/discord/application_commands.json:13:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_types"}, "default_value":1, "comment":"the type of the command, defaults 1 if not set", "inject_if_not":0}' */

  /* specs/discord/application_commands.json:14:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */

  /* specs/discord/application_commands.json:15:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"guild id of the command, if not global","inject_if_not":0}' */

  /* specs/discord/application_commands.json:16:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 character name"}' */

  /* specs/discord/application_commands.json:17:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description for CHAT_INPUT commands, empty string for USER and MESSAGE commands"}' */

  /* specs/discord/application_commands.json:18:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */

  /* specs/discord/application_commands.json:19:18
     '{"name":"default_permission", "type":{"base":"bool"}, "default_value":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */

}
void discord_application_command_list_free(struct discord_application_command **p) {
  ntl_free((void**)p, (vfvp)discord_application_command_cleanup);
}

void discord_application_command_list_from_json(char *str, size_t len, struct discord_application_command ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command);
  d.init_elem = NULL;
  d.elem_from_buf = discord_application_command_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_list_to_json(char *str, size_t len, struct discord_application_command **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_application_command_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
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


void discord_application_command_option_from_json(char *json, size_t len, struct discord_application_command_option **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_application_command_option *p = *pp;
  discord_application_command_option_init(p);
  r=json_extract(json, len, 
  /* specs/discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* specs/discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                "(name):s,"
  /* specs/discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                "(description):s,"
  /* specs/discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
                "(required):b,"
  /* specs/discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                "(choices):F,"
  /* specs/discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                "(options):F,",
  /* specs/discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* specs/discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                p->name,
  /* specs/discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                p->description,
  /* specs/discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
                &p->required,
  /* specs/discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                discord_application_command_option_choice_list_from_json, &p->choices,
  /* specs/discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options);
  ret = r;
}

size_t discord_application_command_option_to_json(char *json, size_t len, struct discord_application_command_option *p)
{
  size_t r;
  void *arg_switches[6]={NULL};
  /* specs/discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  arg_switches[0] = &p->type;

  /* specs/discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  arg_switches[1] = p->name;

  /* specs/discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  arg_switches[2] = p->description;

  /* specs/discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
  arg_switches[3] = &p->required;

  /* specs/discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  if (p->choices != NULL)
    arg_switches[4] = p->choices;

  /* specs/discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[5] = p->options;

  r=json_inject(json, len, 
  /* specs/discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* specs/discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                "(name):s,"
  /* specs/discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                "(description):s,"
  /* specs/discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
                "(required):b,"
  /* specs/discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                "(choices):F,"
  /* specs/discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                "(options):F,"
                "@arg_switches:b",
  /* specs/discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* specs/discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                p->name,
  /* specs/discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                p->description,
  /* specs/discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
                &p->required,
  /* specs/discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                discord_application_command_option_choice_list_to_json, p->choices,
  /* specs/discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_command_option_cleanup_v(void *p) {
  discord_application_command_option_cleanup((struct discord_application_command_option *)p);
}

void discord_application_command_option_init_v(void *p) {
  discord_application_command_option_init((struct discord_application_command_option *)p);
}

void discord_application_command_option_from_json_v(char *json, size_t len, void *pp) {
 discord_application_command_option_from_json(json, len, (struct discord_application_command_option**)pp);
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
  /* specs/discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  /* p->type is a scalar */
  /* specs/discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  /* p->name is a scalar */
  /* specs/discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  /* p->description is a scalar */
  /* specs/discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */
  /* p->required is a scalar */
  /* specs/discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  if (d->choices)
    discord_application_command_option_choice_list_free(d->choices);
  /* specs/discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
}

void discord_application_command_option_init(struct discord_application_command_option *p) {
  memset(p, 0, sizeof(struct discord_application_command_option));
  /* specs/discord/application_commands.json:41:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */

  /* specs/discord/application_commands.json:42:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */

  /* specs/discord/application_commands.json:43:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */

  /* specs/discord/application_commands.json:44:18
     '{"name":"required", "type":{"base":"bool"}, "default_value":false, "comment":"if the parameter is required or optional -- default false"}' */

  /* specs/discord/application_commands.json:45:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */

  /* specs/discord/application_commands.json:46:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */

}
void discord_application_command_option_list_free(struct discord_application_command_option **p) {
  ntl_free((void**)p, (vfvp)discord_application_command_option_cleanup);
}

void discord_application_command_option_list_from_json(char *str, size_t len, struct discord_application_command_option ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_option);
  d.init_elem = NULL;
  d.elem_from_buf = discord_application_command_option_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_option_list_to_json(char *str, size_t len, struct discord_application_command_option **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_application_command_option_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
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


void discord_application_command_option_choice_from_json(char *json, size_t len, struct discord_application_command_option_choice **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_application_command_option_choice *p = *pp;
  discord_application_command_option_choice_init(p);
  r=json_extract(json, len, 
  /* specs/discord/application_commands.json:75:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
                "(name):s,"
  /* specs/discord/application_commands.json:76:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
                "(value):F,",
  /* specs/discord/application_commands.json:75:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
                p->name,
  /* specs/discord/application_commands.json:76:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
                cee_strndup, &p->value);
  ret = r;
}

size_t discord_application_command_option_choice_to_json(char *json, size_t len, struct discord_application_command_option_choice *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* specs/discord/application_commands.json:75:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
  arg_switches[0] = p->name;

  /* specs/discord/application_commands.json:76:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
  arg_switches[1] = p->value;

  r=json_inject(json, len, 
  /* specs/discord/application_commands.json:75:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
                "(name):s,"
  /* specs/discord/application_commands.json:76:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
                "(value):s,"
                "@arg_switches:b",
  /* specs/discord/application_commands.json:75:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
                p->name,
  /* specs/discord/application_commands.json:76:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
                p->value,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_command_option_choice_cleanup_v(void *p) {
  discord_application_command_option_choice_cleanup((struct discord_application_command_option_choice *)p);
}

void discord_application_command_option_choice_init_v(void *p) {
  discord_application_command_option_choice_init((struct discord_application_command_option_choice *)p);
}

void discord_application_command_option_choice_from_json_v(char *json, size_t len, void *pp) {
 discord_application_command_option_choice_from_json(json, len, (struct discord_application_command_option_choice**)pp);
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
  /* specs/discord/application_commands.json:75:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
  /* p->name is a scalar */
  /* specs/discord/application_commands.json:76:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */
  if (d->value)
    free(d->value);
}

void discord_application_command_option_choice_init(struct discord_application_command_option_choice *p) {
  memset(p, 0, sizeof(struct discord_application_command_option_choice));
  /* specs/discord/application_commands.json:75:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */

  /* specs/discord/application_commands.json:76:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"value of choice, up to 100 characters if string"}' */

}
void discord_application_command_option_choice_list_free(struct discord_application_command_option_choice **p) {
  ntl_free((void**)p, (vfvp)discord_application_command_option_choice_cleanup);
}

void discord_application_command_option_choice_list_from_json(char *str, size_t len, struct discord_application_command_option_choice ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_option_choice);
  d.init_elem = NULL;
  d.elem_from_buf = discord_application_command_option_choice_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_option_choice_list_to_json(char *str, size_t len, struct discord_application_command_option_choice **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_application_command_option_choice_to_json_v);
}


void discord_guild_application_command_permissions_from_json(char *json, size_t len, struct discord_guild_application_command_permissions **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_guild_application_command_permissions *p = *pp;
  discord_guild_application_command_permissions_init(p);
  r=json_extract(json, len, 
  /* specs/discord/application_commands.json:86:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):F,"
  /* specs/discord/application_commands.json:87:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                "(application_id):F,"
  /* specs/discord/application_commands.json:88:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                "(guild_id):F,"
  /* specs/discord/application_commands.json:89:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                "(permissions):F,",
  /* specs/discord/application_commands.json:86:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_strtoull, &p->id,
  /* specs/discord/application_commands.json:87:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/application_commands.json:88:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/application_commands.json:89:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                discord_application_command_permissions_list_from_json, &p->permissions);
  ret = r;
}

size_t discord_guild_application_command_permissions_to_json(char *json, size_t len, struct discord_guild_application_command_permissions *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* specs/discord/application_commands.json:86:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  arg_switches[0] = &p->id;

  /* specs/discord/application_commands.json:87:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  arg_switches[1] = &p->application_id;

  /* specs/discord/application_commands.json:88:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  arg_switches[2] = &p->guild_id;

  /* specs/discord/application_commands.json:89:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  arg_switches[3] = p->permissions;

  r=json_inject(json, len, 
  /* specs/discord/application_commands.json:86:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):|F|,"
  /* specs/discord/application_commands.json:87:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                "(application_id):|F|,"
  /* specs/discord/application_commands.json:88:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                "(guild_id):|F|,"
  /* specs/discord/application_commands.json:89:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                "(permissions):F,"
                "@arg_switches:b",
  /* specs/discord/application_commands.json:86:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/application_commands.json:87:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/application_commands.json:88:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/application_commands.json:89:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                discord_application_command_permissions_list_to_json, p->permissions,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_guild_application_command_permissions_cleanup_v(void *p) {
  discord_guild_application_command_permissions_cleanup((struct discord_guild_application_command_permissions *)p);
}

void discord_guild_application_command_permissions_init_v(void *p) {
  discord_guild_application_command_permissions_init((struct discord_guild_application_command_permissions *)p);
}

void discord_guild_application_command_permissions_from_json_v(char *json, size_t len, void *pp) {
 discord_guild_application_command_permissions_from_json(json, len, (struct discord_guild_application_command_permissions**)pp);
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
  /* specs/discord/application_commands.json:86:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  /* p->id is a scalar */
  /* specs/discord/application_commands.json:87:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  /* p->application_id is a scalar */
  /* specs/discord/application_commands.json:88:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  /* p->guild_id is a scalar */
  /* specs/discord/application_commands.json:89:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  if (d->permissions)
    discord_application_command_permissions_list_free(d->permissions);
}

void discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions *p) {
  memset(p, 0, sizeof(struct discord_guild_application_command_permissions));
  /* specs/discord/application_commands.json:86:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */

  /* specs/discord/application_commands.json:87:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */

  /* specs/discord/application_commands.json:88:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */

  /* specs/discord/application_commands.json:89:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */

}
void discord_guild_application_command_permissions_list_free(struct discord_guild_application_command_permissions **p) {
  ntl_free((void**)p, (vfvp)discord_guild_application_command_permissions_cleanup);
}

void discord_guild_application_command_permissions_list_from_json(char *str, size_t len, struct discord_guild_application_command_permissions ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_guild_application_command_permissions);
  d.init_elem = NULL;
  d.elem_from_buf = discord_guild_application_command_permissions_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_guild_application_command_permissions_list_to_json(char *str, size_t len, struct discord_guild_application_command_permissions **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_guild_application_command_permissions_to_json_v);
}


void discord_application_command_permissions_from_json(char *json, size_t len, struct discord_application_command_permissions **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_application_command_permissions *p = *pp;
  discord_application_command_permissions_init(p);
  r=json_extract(json, len, 
  /* specs/discord/application_commands.json:99:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):F,"
  /* specs/discord/application_commands.json:100:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                "(type):d,"
  /* specs/discord/application_commands.json:101:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                "(permission):b,",
  /* specs/discord/application_commands.json:99:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_strtoull, &p->id,
  /* specs/discord/application_commands.json:100:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                &p->type,
  /* specs/discord/application_commands.json:101:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                &p->permission);
  ret = r;
}

size_t discord_application_command_permissions_to_json(char *json, size_t len, struct discord_application_command_permissions *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* specs/discord/application_commands.json:99:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  arg_switches[0] = &p->id;

  /* specs/discord/application_commands.json:100:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  arg_switches[1] = &p->type;

  /* specs/discord/application_commands.json:101:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  arg_switches[2] = &p->permission;

  r=json_inject(json, len, 
  /* specs/discord/application_commands.json:99:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):|F|,"
  /* specs/discord/application_commands.json:100:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                "(type):d,"
  /* specs/discord/application_commands.json:101:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                "(permission):b,"
                "@arg_switches:b",
  /* specs/discord/application_commands.json:99:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/application_commands.json:100:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                &p->type,
  /* specs/discord/application_commands.json:101:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                &p->permission,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_command_permissions_cleanup_v(void *p) {
  discord_application_command_permissions_cleanup((struct discord_application_command_permissions *)p);
}

void discord_application_command_permissions_init_v(void *p) {
  discord_application_command_permissions_init((struct discord_application_command_permissions *)p);
}

void discord_application_command_permissions_from_json_v(char *json, size_t len, void *pp) {
 discord_application_command_permissions_from_json(json, len, (struct discord_application_command_permissions**)pp);
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
  /* specs/discord/application_commands.json:99:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  /* p->id is a scalar */
  /* specs/discord/application_commands.json:100:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  /* p->type is a scalar */
  /* specs/discord/application_commands.json:101:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  /* p->permission is a scalar */
}

void discord_application_command_permissions_init(struct discord_application_command_permissions *p) {
  memset(p, 0, sizeof(struct discord_application_command_permissions));
  /* specs/discord/application_commands.json:99:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */

  /* specs/discord/application_commands.json:100:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */

  /* specs/discord/application_commands.json:101:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */

}
void discord_application_command_permissions_list_free(struct discord_application_command_permissions **p) {
  ntl_free((void**)p, (vfvp)discord_application_command_permissions_cleanup);
}

void discord_application_command_permissions_list_from_json(char *str, size_t len, struct discord_application_command_permissions ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_permissions);
  d.init_elem = NULL;
  d.elem_from_buf = discord_application_command_permissions_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_permissions_list_to_json(char *str, size_t len, struct discord_application_command_permissions **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_application_command_permissions_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
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


void discord_application_command_interaction_data_option_from_json(char *json, size_t len, struct discord_application_command_interaction_data_option **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_application_command_interaction_data_option *p = *pp;
  discord_application_command_interaction_data_option_init(p);
  r=json_extract(json, len, 
  /* specs/discord/application_commands.json:122:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                "(name):?s,"
  /* specs/discord/application_commands.json:123:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* specs/discord/application_commands.json:124:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
                "(value):F,"
  /* specs/discord/application_commands.json:125:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                "(options):F,",
  /* specs/discord/application_commands.json:122:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                &p->name,
  /* specs/discord/application_commands.json:123:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* specs/discord/application_commands.json:124:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
                cee_strndup, &p->value,
  /* specs/discord/application_commands.json:125:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_from_json, &p->options);
  ret = r;
}

size_t discord_application_command_interaction_data_option_to_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* specs/discord/application_commands.json:122:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  arg_switches[0] = p->name;

  /* specs/discord/application_commands.json:123:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  arg_switches[1] = &p->type;

  /* specs/discord/application_commands.json:124:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
  arg_switches[2] = p->value;

  /* specs/discord/application_commands.json:125:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[3] = p->options;

  r=json_inject(json, len, 
  /* specs/discord/application_commands.json:122:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                "(name):s,"
  /* specs/discord/application_commands.json:123:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* specs/discord/application_commands.json:124:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
                "(value):s,"
  /* specs/discord/application_commands.json:125:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                "(options):F,"
                "@arg_switches:b",
  /* specs/discord/application_commands.json:122:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                p->name,
  /* specs/discord/application_commands.json:123:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* specs/discord/application_commands.json:124:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
                p->value,
  /* specs/discord/application_commands.json:125:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_to_json, p->options,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_command_interaction_data_option_cleanup_v(void *p) {
  discord_application_command_interaction_data_option_cleanup((struct discord_application_command_interaction_data_option *)p);
}

void discord_application_command_interaction_data_option_init_v(void *p) {
  discord_application_command_interaction_data_option_init((struct discord_application_command_interaction_data_option *)p);
}

void discord_application_command_interaction_data_option_from_json_v(char *json, size_t len, void *pp) {
 discord_application_command_interaction_data_option_from_json(json, len, (struct discord_application_command_interaction_data_option**)pp);
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
  /* specs/discord/application_commands.json:122:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/application_commands.json:123:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  /* p->type is a scalar */
  /* specs/discord/application_commands.json:124:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */
  if (d->value)
    free(d->value);
  /* specs/discord/application_commands.json:125:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_interaction_data_option_list_free(d->options);
}

void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *p) {
  memset(p, 0, sizeof(struct discord_application_command_interaction_data_option));
  /* specs/discord/application_commands.json:122:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */

  /* specs/discord/application_commands.json:123:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */

  /* specs/discord/application_commands.json:124:18
     '{"name":"value", "type":{"base":"char", "dec":"*", "converter":"mixed"}, "comment":"the value of the pair"}' */

  /* specs/discord/application_commands.json:125:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */

}
void discord_application_command_interaction_data_option_list_free(struct discord_application_command_interaction_data_option **p) {
  ntl_free((void**)p, (vfvp)discord_application_command_interaction_data_option_cleanup);
}

void discord_application_command_interaction_data_option_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_option ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_interaction_data_option);
  d.init_elem = NULL;
  d.elem_from_buf = discord_application_command_interaction_data_option_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_interaction_data_option_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_option **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_application_command_interaction_data_option_to_json_v);
}

