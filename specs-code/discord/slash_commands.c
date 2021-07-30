/* This file is generated from specs/discord/slash_commands.json, Please don't edit it. */
/**
 * @file specs-code/discord/slash_commands.c
 * @author cee-studio
 * @date Jul 30 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/interactions/slash-commands#data-models-and-types
 */

#include "specs.h"

void discord_application_command_from_json(char *json, size_t len, struct discord_application_command **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_application_command *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                "(id):F,"
  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                "(application_id):F,"
  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */
                "(guild_id):F,"
  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                "(description):s,"
  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                cee_strtoull, &p->id,
  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                p->name,
  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                p->description,
  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_application_command_use_default_inject_settings(struct discord_application_command *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  p->__M.arg_switches[1] = &p->application_id;

  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */
  if (p->guild_id != 0)
    p->__M.arg_switches[2] = &p->guild_id;

  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  p->__M.arg_switches[3] = p->name;

  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  p->__M.arg_switches[4] = p->description;

  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (p->options != NULL)
    p->__M.arg_switches[5] = p->options;

  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  if (p->default_permission != true)
    p->__M.arg_switches[6] = &p->default_permission;

}

size_t discord_application_command_to_json(char *json, size_t len, struct discord_application_command *p)
{
  size_t r;
  discord_application_command_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                "(id):|F|,"
  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                "(application_id):|F|,"
  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */
                "(guild_id):|F|,"
  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                "(description):s,"
  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                p->name,
  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                p->description,
  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */
  // p->id is a scalar
  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */
  // p->application_id is a scalar
  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */
  // p->guild_id is a scalar
  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  // p->name is a scalar
  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  // p->description is a scalar
  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  // p->default_permission is a scalar
}

void discord_application_command_init(struct discord_application_command *p) {
  memset(p, 0, sizeof(struct discord_application_command));
  /* specs/discord/slash_commands.json:12:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the command"}' */

  /* specs/discord/slash_commands.json:13:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"unique id of the parent application"}' */

  /* specs/discord/slash_commands.json:14:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"unique id of the command, if not global","inject_if_not":0}' */

  /* specs/discord/slash_commands.json:15:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */

  /* specs/discord/slash_commands.json:16:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */

  /* specs/discord/slash_commands.json:17:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"the parameters for the command", "inject_if_not":null}' */

  /* specs/discord/slash_commands.json:18:18
     '{"name":"default_permission", "type":{"base":"bool"}, "option":true, "inject_if_not":true, "comment":"whether the command is enabled by default when the app is added to a guild"}' */

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


void discord_application_command_option_from_json(char *json, size_t len, struct discord_application_command_option **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_application_command_option *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                "(description):s,"
  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */
                "(required):b,"
  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                "(choices):F,"
  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                "(options):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                p->name,
  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                p->description,
  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */
                &p->required,
  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                discord_application_command_option_choice_list_from_json, &p->choices,
  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_application_command_option_use_default_inject_settings(struct discord_application_command_option *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  p->__M.arg_switches[0] = &p->type;

  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  p->__M.arg_switches[2] = p->description;

  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */
  if (p->required != false)
    p->__M.arg_switches[3] = &p->required;

  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  if (p->choices != NULL)
    p->__M.arg_switches[4] = p->choices;

  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  if (p->options != NULL)
    p->__M.arg_switches[5] = p->options;

}

size_t discord_application_command_option_to_json(char *json, size_t len, struct discord_application_command_option *p)
{
  size_t r;
  discord_application_command_option_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                "(description):s,"
  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */
                "(required):b,"
  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                "(choices):F,"
  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                "(options):F,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
                p->name,
  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
                p->description,
  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */
                &p->required,
  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
                discord_application_command_option_choice_list_to_json, p->choices,
  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  // p->type is a scalar
  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */
  // p->name is a scalar
  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */
  // p->description is a scalar
  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */
  // p->required is a scalar
  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */
  if (d->choices)
    discord_application_command_option_choice_list_free(d->choices);
  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
}

void discord_application_command_option_init(struct discord_application_command_option *p) {
  memset(p, 0, sizeof(struct discord_application_command_option));
  /* specs/discord/slash_commands.json:28:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */

  /* specs/discord/slash_commands.json:29:18
     '{"name":"name", "type":{"base":"char", "dec":"[32+1]"}, "comment":"1-32 lowercase character"}' */

  /* specs/discord/slash_commands.json:30:18
     '{"name":"description", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character description"}' */

  /* specs/discord/slash_commands.json:31:18
     '{"name":"required", "type":{"base":"bool"}, "option":true, "inject_if_not":false, "comment":"if the paramter is required or optional -- default false"}' */

  /* specs/discord/slash_commands.json:32:18
     '{"name":"choices", "type":{"base":"struct discord_application_command_option_choice", "dec":"ntl"}, "option":true, "comment":"choices for string and int types for the user to pick from", "inject_if_not":null}' */

  /* specs/discord/slash_commands.json:33:18
     '{"name":"options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "option":true, "comment":"if the option is a subcommand or subcommand group type, this nested options will be the parameters", "inject_if_not":null}' */

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



enum discord_application_command_option_types discord_application_command_option_types_from_string(char *s){
  if(strcasecmp("SUB_COMMAND", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND;
  if(strcasecmp("SUB_COMMAND_GROUP", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND_GROUP;
  if(strcasecmp("STRING", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_STRING;
  if(strcasecmp("INTEGER", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_INTEGER;
  if(strcasecmp("BOOLEAN", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_BOOLEAN;
  if(strcasecmp("USER", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_USER;
  if(strcasecmp("CHANNEL", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL;
  if(strcasecmp("ROLE", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_ROLE;
  if(strcasecmp("MENTIONABLE", s) == 0) return DISCORD_APPLICATION_COMMAND_OPTION_MENTIONABLE;
  abort();
}
char* discord_application_command_option_types_to_string(enum discord_application_command_option_types v){
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND) return "SUB_COMMAND";
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND_GROUP) return "SUB_COMMAND_GROUP";
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_STRING) return "STRING";
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_INTEGER) return "INTEGER";
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_BOOLEAN) return "BOOLEAN";
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_USER) return "USER";
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL) return "CHANNEL";
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_ROLE) return "ROLE";
  if (v == DISCORD_APPLICATION_COMMAND_OPTION_MENTIONABLE) return "MENTIONABLE";

  return (void*)0;
}
bool discord_application_command_option_types_has(enum discord_application_command_option_types v, char *s) {
  enum discord_application_command_option_types v1 = discord_application_command_option_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_application_command_option_choice_from_json(char *json, size_t len, struct discord_application_command_option_choice **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_application_command_option_choice *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */
                "(value):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
                p->name,
  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */
                p->value,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_application_command_option_choice_use_default_inject_settings(struct discord_application_command_option_choice *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */
  p->__M.arg_switches[1] = p->value;

}

size_t discord_application_command_option_choice_to_json(char *json, size_t len, struct discord_application_command_option_choice *p)
{
  size_t r;
  discord_application_command_option_choice_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */
                "(value):s,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
                p->name,
  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */
                p->value,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */
  // p->name is a scalar
  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */
  // p->value is a scalar
}

void discord_application_command_option_choice_init(struct discord_application_command_option_choice *p) {
  memset(p, 0, sizeof(struct discord_application_command_option_choice));
  /* specs/discord/slash_commands.json:61:18
     '{"name":"name", "type":{"base":"char", "dec":"[100+1]"}, "comment":"1-100 character choice name"}' */

  /* specs/discord/slash_commands.json:62:18
     '{"name":"value", "type":{"base":"char", "dec":"[100+1]"}, "comment":"value of choice, up to 100 characters"}' */

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
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_guild_application_command_permissions *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):F,"
  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                "(application_id):F,"
  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                "(guild_id):F,"
  /* specs/discord/slash_commands.json:75:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                "(permissions):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_strtoull, &p->id,
  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/slash_commands.json:75:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                discord_application_command_permissions_list_from_json, &p->permissions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_guild_application_command_permissions_use_default_inject_settings(struct discord_guild_application_command_permissions *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  p->__M.arg_switches[1] = &p->application_id;

  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  p->__M.arg_switches[2] = &p->guild_id;

  /* specs/discord/slash_commands.json:75:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  p->__M.arg_switches[3] = p->permissions;

}

size_t discord_guild_application_command_permissions_to_json(char *json, size_t len, struct discord_guild_application_command_permissions *p)
{
  size_t r;
  discord_guild_application_command_permissions_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):|F|,"
  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                "(application_id):|F|,"
  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                "(guild_id):|F|,"
  /* specs/discord/slash_commands.json:75:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                "(permissions):F,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/slash_commands.json:75:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                discord_application_command_permissions_list_to_json, p->permissions,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  // p->id is a scalar
  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */
  // p->application_id is a scalar
  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */
  // p->guild_id is a scalar
  /* specs/discord/slash_commands.json:75:18
     '{"name":"permissions", "type":{"base":"struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  if (d->permissions)
    discord_application_command_permissions_list_free(d->permissions);
}

void discord_guild_application_command_permissions_init(struct discord_guild_application_command_permissions *p) {
  memset(p, 0, sizeof(struct discord_guild_application_command_permissions));
  /* specs/discord/slash_commands.json:72:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */

  /* specs/discord/slash_commands.json:73:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the parent application the command belongs to"}' */

  /* specs/discord/slash_commands.json:74:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the guild"}' */

  /* specs/discord/slash_commands.json:75:18
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
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_application_command_permissions *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):F,"
  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:87:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                "(permission):b,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_strtoull, &p->id,
  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                &p->type,
  /* specs/discord/slash_commands.json:87:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                &p->permission,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_application_command_permissions_use_default_inject_settings(struct discord_application_command_permissions *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  p->__M.arg_switches[1] = &p->type;

  /* specs/discord/slash_commands.json:87:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  p->__M.arg_switches[2] = &p->permission;

}

size_t discord_application_command_permissions_to_json(char *json, size_t len, struct discord_application_command_permissions *p)
{
  size_t r;
  discord_application_command_permissions_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                "(id):|F|,"
  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:87:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                "(permission):b,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
                &p->type,
  /* specs/discord/slash_commands.json:87:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
                &p->permission,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */
  // p->id is a scalar
  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */
  // p->type is a scalar
  /* specs/discord/slash_commands.json:87:18
     '{"name":"permission", "type":{"base":"bool"}, "comment":"true to allow, false, to disallow"}' */
  // p->permission is a scalar
}

void discord_application_command_permissions_init(struct discord_application_command_permissions *p) {
  memset(p, 0, sizeof(struct discord_application_command_permissions));
  /* specs/discord/slash_commands.json:85:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the command"}' */

  /* specs/discord/slash_commands.json:86:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_permission_types"}, "comment":"role or user"}' */

  /* specs/discord/slash_commands.json:87:18
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



enum discord_application_command_permission_types discord_application_command_permission_types_from_string(char *s){
  if(strcasecmp("ROLE", s) == 0) return DISCORD_APPLICATION_COMMAND_PERMISSION_ROLE;
  if(strcasecmp("USER", s) == 0) return DISCORD_APPLICATION_COMMAND_PERMISSION_USER;
  abort();
}
char* discord_application_command_permission_types_to_string(enum discord_application_command_permission_types v){
  if (v == DISCORD_APPLICATION_COMMAND_PERMISSION_ROLE) return "ROLE";
  if (v == DISCORD_APPLICATION_COMMAND_PERMISSION_USER) return "USER";

  return (void*)0;
}
bool discord_application_command_permission_types_has(enum discord_application_command_permission_types v, char *s) {
  enum discord_application_command_permission_types v1 = discord_application_command_permission_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_interaction_from_json(char *json, size_t len, struct discord_interaction **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_interaction *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                "(id):F,"
  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
                "(application_id):F,"
  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
                "(data):F,"
  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
                "(guild_id):F,"
  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
                "(channel_id):F,"
  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
                "(member):F,"
  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
                "(user):F,"
  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
                "(token):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                cee_strtoull, &p->id,
  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
                &p->type,
  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
                discord_application_command_interaction_data_from_json, &p->data,
  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
                discord_guild_member_from_json, &p->member,
  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
                discord_user_from_json, &p->user,
  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
                &p->token,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_interaction_use_default_inject_settings(struct discord_interaction *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
  p->__M.arg_switches[1] = &p->application_id;

  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
  p->__M.arg_switches[2] = &p->type;

  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  if (p->data != NULL)
    p->__M.arg_switches[3] = p->data;

  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
  if (p->guild_id != 0)
    p->__M.arg_switches[4] = &p->guild_id;

  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
  if (p->channel_id != 0)
    p->__M.arg_switches[5] = &p->channel_id;

  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  if (p->member != NULL)
    p->__M.arg_switches[6] = p->member;

  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  if (p->user != NULL)
    p->__M.arg_switches[7] = p->user;

  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
  if (p->token != NULL)
    p->__M.arg_switches[8] = p->token;

}

size_t discord_interaction_to_json(char *json, size_t len, struct discord_interaction *p)
{
  size_t r;
  discord_interaction_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                "(id):|F|,"
  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
                "(application_id):|F|,"
  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
                "(data):F,"
  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
                "(guild_id):|F|,"
  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
                "(channel_id):|F|,"
  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
                "(member):F,"
  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
                "(user):F,"
  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
                "(token):s,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
                &p->type,
  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
                discord_application_command_interaction_data_to_json, p->data,
  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
                discord_guild_member_to_json, p->member,
  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
                discord_user_to_json, p->user,
  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
                p->token,
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
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  // p->id is a scalar
  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */
  // p->application_id is a scalar
  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
  // p->type is a scalar
  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  if (d->data) {
    discord_application_command_interaction_data_cleanup(d->data);
    free(d->data);
  }
  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */
  // p->guild_id is a scalar
  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */
  // p->channel_id is a scalar
  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  if (d->member) {
    discord_guild_member_cleanup(d->member);
    free(d->member);
  }
  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */
  if (d->token)
    free(d->token);
}

void discord_interaction_init(struct discord_interaction *p) {
  memset(p, 0, sizeof(struct discord_interaction));
  /* specs/discord/slash_commands.json:107:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */

  /* specs/discord/slash_commands.json:108:18
     '{"name":"application_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the application this iteraction is for"}' */

  /* specs/discord/slash_commands.json:109:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */

  /* specs/discord/slash_commands.json:110:18
     '{"name":"data", "type":{"base":"struct discord_application_command_interaction_data", "dec":"*"}, "option":true, "comment":"the command data payload", "inject_if_not":null}' */
  p->data = malloc(sizeof *p->data);
  discord_application_command_interaction_data_init(p->data);

  /* specs/discord/slash_commands.json:111:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the guild it was sent from","inject_if_not":0}' */

  /* specs/discord/slash_commands.json:112:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"the channel it was sent from","inject_if_not":0}' */

  /* specs/discord/slash_commands.json:113:18
     '{"name":"member", "type":{"base":"struct discord_guild_member", "dec":"*"}, "option":true, "comment":"guild member data for the invoking user, including permissions", "inject_if_not":null}' */
  p->member = malloc(sizeof *p->member);
  discord_guild_member_init(p->member);

  /* specs/discord/slash_commands.json:114:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "option":true, "comment":"user object for the invoking user, if invoked in a DM", "inject_if_not":null}' */
  p->user = malloc(sizeof *p->user);
  discord_user_init(p->user);

  /* specs/discord/slash_commands.json:115:18
     '{"name":"token", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"a continuation token for responding to the interaction", "inject_if_not":null}' */

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



enum discord_interaction_request_types discord_interaction_request_types_from_string(char *s){
  if(strcasecmp("PING", s) == 0) return DISCORD_INTERACTION_PING;
  if(strcasecmp("APPLICATION_COMMAND", s) == 0) return DISCORD_INTERACTION_APPLICATION_COMMAND;
  if(strcasecmp("MESSAGE_COMPONENT", s) == 0) return DISCORD_INTERACTION_MESSAGE_COMPONENT;
  abort();
}
char* discord_interaction_request_types_to_string(enum discord_interaction_request_types v){
  if (v == DISCORD_INTERACTION_PING) return "PING";
  if (v == DISCORD_INTERACTION_APPLICATION_COMMAND) return "APPLICATION_COMMAND";
  if (v == DISCORD_INTERACTION_MESSAGE_COMPONENT) return "MESSAGE_COMPONENT";

  return (void*)0;
}
bool discord_interaction_request_types_has(enum discord_interaction_request_types v, char *s) {
  enum discord_interaction_request_types v1 = discord_interaction_request_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_application_command_interaction_data_from_json(char *json, size_t len, struct discord_application_command_interaction_data **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_application_command_interaction_data *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
                "(id):F,"
  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
                "(name):?s,"
  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
                "(resolved):F,"
  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */
                "(options):F,"
  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */
                "(custom_id):s,"
  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */
                "(type):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
                cee_strtoull, &p->id,
  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
                &p->name,
  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
                discord_application_command_interaction_data_resolved_from_json, &p->resolved,
  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_from_json, &p->options,
  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */
                p->custom_id,
  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_application_command_interaction_data_use_default_inject_settings(struct discord_application_command_interaction_data *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
  p->__M.arg_switches[1] = p->name;

  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  if (p->resolved != NULL)
    p->__M.arg_switches[2] = p->resolved;

  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */
  if (p->options != NULL)
    p->__M.arg_switches[3] = p->options;

  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */
  p->__M.arg_switches[4] = p->custom_id;

  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */
  p->__M.arg_switches[5] = &p->type;

}

size_t discord_application_command_interaction_data_to_json(char *json, size_t len, struct discord_application_command_interaction_data *p)
{
  size_t r;
  discord_application_command_interaction_data_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
                "(id):|F|,"
  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
                "(resolved):F,"
  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */
                "(options):F,"
  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */
                "(custom_id):s,"
  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */
                "(type):d,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
                p->name,
  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
                discord_application_command_interaction_data_resolved_to_json, p->resolved,
  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_to_json, p->options,
  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */
                p->custom_id,
  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */
                &p->type,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_command_interaction_data_cleanup_v(void *p) {
  discord_application_command_interaction_data_cleanup((struct discord_application_command_interaction_data *)p);
}

void discord_application_command_interaction_data_init_v(void *p) {
  discord_application_command_interaction_data_init((struct discord_application_command_interaction_data *)p);
}

void discord_application_command_interaction_data_from_json_v(char *json, size_t len, void *pp) {
 discord_application_command_interaction_data_from_json(json, len, (struct discord_application_command_interaction_data**)pp);
}

size_t discord_application_command_interaction_data_to_json_v(char *json, size_t len, void *p) {
  return discord_application_command_interaction_data_to_json(json, len, (struct discord_application_command_interaction_data*)p);
}

void discord_application_command_interaction_data_list_free_v(void **p) {
  discord_application_command_interaction_data_list_free((struct discord_application_command_interaction_data**)p);
}

void discord_application_command_interaction_data_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_interaction_data_list_from_json(str, len, (struct discord_application_command_interaction_data ***)p);
}

size_t discord_application_command_interaction_data_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_interaction_data_list_to_json(str, len, (struct discord_application_command_interaction_data **)p);
}


void discord_application_command_interaction_data_cleanup(struct discord_application_command_interaction_data *d) {
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */
  // p->id is a scalar
  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  if (d->resolved) {
    discord_application_command_interaction_data_resolved_cleanup(d->resolved);
    free(d->resolved);
  }
  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_interaction_data_option_list_free(d->options);
  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */
  // p->custom_id is a scalar
  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */
  // p->type is a scalar
}

void discord_application_command_interaction_data_init(struct discord_application_command_interaction_data *p) {
  memset(p, 0, sizeof(struct discord_application_command_interaction_data));
  /* specs/discord/slash_commands.json:137:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the ID of the invoked command"}' */

  /* specs/discord/slash_commands.json:138:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the invoked command"}' */

  /* specs/discord/slash_commands.json:139:18
     '{"name":"resolved", "type":{"base":"struct discord_application_command_interaction_data_resolved", "dec":"*"}, "option":true, "comment":"converted users + roles + channels", "inject_if_not":null}' */
  p->resolved = malloc(sizeof *p->resolved);
  discord_application_command_interaction_data_resolved_init(p->resolved);

  /* specs/discord/slash_commands.json:140:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"the params + values from the user", "inject_if_not":null}' */

  /* specs/discord/slash_commands.json:141:18
     '{"name":"custom_id", "type":{"base":"char", "dec":"[100+1]"}, "comment":"a developer-defined identifier for the component, max 100 characters"}' */

  /* specs/discord/slash_commands.json:142:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_component_types"}, "comment":"component type"}' */

}
void discord_application_command_interaction_data_list_free(struct discord_application_command_interaction_data **p) {
  ntl_free((void**)p, (vfvp)discord_application_command_interaction_data_cleanup);
}

void discord_application_command_interaction_data_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_interaction_data);
  d.init_elem = NULL;
  d.elem_from_buf = discord_application_command_interaction_data_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_interaction_data_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_application_command_interaction_data_to_json_v);
}


void discord_application_command_interaction_data_resolved_from_json(char *json, size_t len, struct discord_application_command_interaction_data_resolved **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_application_command_interaction_data_resolved *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
                "(users):F,"
  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
                "(members):F,"
  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
                "(roles):F,"
  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
                "(channels):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->users,
  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->members,
  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->roles,
  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
                ja_str_list_from_json, &p->channels,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_application_command_interaction_data_resolved_use_default_inject_settings(struct discord_application_command_interaction_data_resolved *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
  if (p->users != NULL)
    p->__M.arg_switches[0] = p->users;

  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
  if (p->members != NULL)
    p->__M.arg_switches[1] = p->members;

  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
  if (p->roles != NULL)
    p->__M.arg_switches[2] = p->roles;

  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
  if (p->channels != NULL)
    p->__M.arg_switches[3] = p->channels;

}

size_t discord_application_command_interaction_data_resolved_to_json(char *json, size_t len, struct discord_application_command_interaction_data_resolved *p)
{
  size_t r;
  discord_application_command_interaction_data_resolved_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
                "(users):F,"
  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
                "(members):F,"
  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
                "(roles):F,"
  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
                "(channels):F,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->users,
  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->members,
  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->roles,
  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
                ja_str_list_to_json, p->channels,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_command_interaction_data_resolved_cleanup_v(void *p) {
  discord_application_command_interaction_data_resolved_cleanup((struct discord_application_command_interaction_data_resolved *)p);
}

void discord_application_command_interaction_data_resolved_init_v(void *p) {
  discord_application_command_interaction_data_resolved_init((struct discord_application_command_interaction_data_resolved *)p);
}

void discord_application_command_interaction_data_resolved_from_json_v(char *json, size_t len, void *pp) {
 discord_application_command_interaction_data_resolved_from_json(json, len, (struct discord_application_command_interaction_data_resolved**)pp);
}

size_t discord_application_command_interaction_data_resolved_to_json_v(char *json, size_t len, void *p) {
  return discord_application_command_interaction_data_resolved_to_json(json, len, (struct discord_application_command_interaction_data_resolved*)p);
}

void discord_application_command_interaction_data_resolved_list_free_v(void **p) {
  discord_application_command_interaction_data_resolved_list_free((struct discord_application_command_interaction_data_resolved**)p);
}

void discord_application_command_interaction_data_resolved_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_command_interaction_data_resolved_list_from_json(str, len, (struct discord_application_command_interaction_data_resolved ***)p);
}

size_t discord_application_command_interaction_data_resolved_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_command_interaction_data_resolved_list_to_json(str, len, (struct discord_application_command_interaction_data_resolved **)p);
}


void discord_application_command_interaction_data_resolved_cleanup(struct discord_application_command_interaction_data_resolved *d) {
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */
  if (d->users)
    ja_str_list_free(d->users);
  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */
  if (d->members)
    ja_str_list_free(d->members);
  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */
  if (d->roles)
    ja_str_list_free(d->roles);
  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */
  if (d->channels)
    ja_str_list_free(d->channels);
}

void discord_application_command_interaction_data_resolved_init(struct discord_application_command_interaction_data_resolved *p) {
  memset(p, 0, sizeof(struct discord_application_command_interaction_data_resolved));
  /* specs/discord/slash_commands.json:152:18
     '{"name":"users", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and User objects", "inject_if_not":null}' */

  /* specs/discord/slash_commands.json:153:18
     '{"name":"members", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Member objects", "inject_if_not":null}' */

  /* specs/discord/slash_commands.json:154:18
     '{"name":"roles", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and Role objects", "inject_if_not":null}' */

  /* specs/discord/slash_commands.json:155:18
     '{"name":"channels", "type":{"base":"ja_str", "dec":"ntl"}, "option":true, "comment":"the ids and partial Channel objects", "inject_if_not":null}' */

}
void discord_application_command_interaction_data_resolved_list_free(struct discord_application_command_interaction_data_resolved **p) {
  ntl_free((void**)p, (vfvp)discord_application_command_interaction_data_resolved_cleanup);
}

void discord_application_command_interaction_data_resolved_list_from_json(char *str, size_t len, struct discord_application_command_interaction_data_resolved ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application_command_interaction_data_resolved);
  d.init_elem = NULL;
  d.elem_from_buf = discord_application_command_interaction_data_resolved_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_command_interaction_data_resolved_list_to_json(char *str, size_t len, struct discord_application_command_interaction_data_resolved **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_application_command_interaction_data_resolved_to_json_v);
}


void discord_application_command_interaction_data_option_from_json(char *json, size_t len, struct discord_application_command_interaction_data_option **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_application_command_interaction_data_option *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                "(name):?s,"
  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */
                "(value):d,"
  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                "(options):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                &p->name,
  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */
                &p->value,
  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_from_json, &p->options,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_application_command_interaction_data_option_use_default_inject_settings(struct discord_application_command_interaction_data_option *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  p->__M.arg_switches[1] = &p->type;

  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */
  p->__M.arg_switches[2] = &p->value;

  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  if (p->options != NULL)
    p->__M.arg_switches[3] = p->options;

}

size_t discord_application_command_interaction_data_option_to_json(char *json, size_t len, struct discord_application_command_interaction_data_option *p)
{
  size_t r;
  discord_application_command_interaction_data_option_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */
                "(value):d,"
  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                "(options):F,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
                p->name,
  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
                &p->type,
  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */
                &p->value,
  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
                discord_application_command_interaction_data_option_list_to_json, p->options,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
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
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */
  // p->type is a scalar
  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */
  // p->value is a scalar
  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_interaction_data_option_list_free(d->options);
}

void discord_application_command_interaction_data_option_init(struct discord_application_command_interaction_data_option *p) {
  memset(p, 0, sizeof(struct discord_application_command_interaction_data_option));
  /* specs/discord/slash_commands.json:165:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the parameter"}' */

  /* specs/discord/slash_commands.json:166:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"value of application command option type"}' */

  /* specs/discord/slash_commands.json:167:18
     '{"name":"value", "type":{"base":"int", "int_alias":"enum discord_application_command_option_types"}, "comment":"the value of the pair"}' */

  /* specs/discord/slash_commands.json:168:18
     '{"name":"options", "type":{"base":"struct discord_application_command_interaction_data_option", "dec":"ntl"}, "option":true, "comment":"present if this option is a group or subcommand", "inject_if_not":null}' */

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


void discord_interaction_response_from_json(char *json, size_t len, struct discord_interaction_response **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_interaction_response *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
                "(data):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
                &p->type,
  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
                discord_interaction_application_command_callback_data_from_json, &p->data,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_interaction_response_use_default_inject_settings(struct discord_interaction_response *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
  p->__M.arg_switches[0] = &p->type;

  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  if (p->data != NULL)
    p->__M.arg_switches[1] = p->data;

}

size_t discord_interaction_response_to_json(char *json, size_t len, struct discord_interaction_response *p)
{
  size_t r;
  discord_interaction_response_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
                "(data):F,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
                &p->type,
  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
                discord_interaction_application_command_callback_data_to_json, p->data,
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
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */
  // p->type is a scalar
  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  if (d->data) {
    discord_interaction_application_command_callback_data_cleanup(d->data);
    free(d->data);
  }
}

void discord_interaction_response_init(struct discord_interaction_response *p) {
  memset(p, 0, sizeof(struct discord_interaction_response));
  /* specs/discord/slash_commands.json:178:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_callback_types"}, "comment":"the type of response"}' */

  /* specs/discord/slash_commands.json:179:18
     '{"name":"data", "type":{"base":"struct discord_interaction_application_command_callback_data", "dec":"*"}, "option":true, "comment":"an optional response message", "inject_if_not":null}' */
  p->data = malloc(sizeof *p->data);
  discord_interaction_application_command_callback_data_init(p->data);

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



enum discord_interaction_callback_types discord_interaction_callback_types_from_string(char *s){
  if(strcasecmp("PONG", s) == 0) return DISCORD_INTERACTION_CALLBACK_PONG;
  if(strcasecmp("CHANNEL_MESSAGE_WITH_SOURCE", s) == 0) return DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE;
  if(strcasecmp("DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE", s) == 0) return DISCORD_INTERACTION_CALLBACK_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE;
  if(strcasecmp("DEFERRED_UPDATE_MESSAGE", s) == 0) return DISCORD_INTERACTION_CALLBACK_DEFERRED_UPDATE_MESSAGE;
  if(strcasecmp("UPDATE_MESSAGE", s) == 0) return DISCORD_INTERACTION_CALLBACK_UPDATE_MESSAGE;
  abort();
}
char* discord_interaction_callback_types_to_string(enum discord_interaction_callback_types v){
  if (v == DISCORD_INTERACTION_CALLBACK_PONG) return "PONG";
  if (v == DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE) return "CHANNEL_MESSAGE_WITH_SOURCE";
  if (v == DISCORD_INTERACTION_CALLBACK_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE) return "DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE";
  if (v == DISCORD_INTERACTION_CALLBACK_DEFERRED_UPDATE_MESSAGE) return "DEFERRED_UPDATE_MESSAGE";
  if (v == DISCORD_INTERACTION_CALLBACK_UPDATE_MESSAGE) return "UPDATE_MESSAGE";

  return (void*)0;
}
bool discord_interaction_callback_types_has(enum discord_interaction_callback_types v, char *s) {
  enum discord_interaction_callback_types v1 = discord_interaction_callback_types_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}

void discord_interaction_application_command_callback_data_from_json(char *json, size_t len, struct discord_interaction_application_command_callback_data **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_interaction_application_command_callback_data *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
                "(tts):b,"
  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
                "(content):?s,"
  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
                "(embeds):F,"
  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
                "(flags):d,"
  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
                "(components):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
                &p->tts,
  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
                &p->content,
  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
                discord_embed_list_from_json, &p->embeds,
  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
                &p->flags,
  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
                discord_component_list_from_json, &p->components,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_interaction_application_command_callback_data_use_default_inject_settings(struct discord_interaction_application_command_callback_data *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
  p->__M.arg_switches[0] = &p->tts;

  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
  if (p->content != NULL)
    p->__M.arg_switches[1] = p->content;

  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
  if (p->embeds != NULL)
    p->__M.arg_switches[2] = p->embeds;

  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */

  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
  if (p->flags != 0)
    p->__M.arg_switches[4] = &p->flags;

  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
  if (p->components != NULL)
    p->__M.arg_switches[5] = p->components;

}

size_t discord_interaction_application_command_callback_data_to_json(char *json, size_t len, struct discord_interaction_application_command_callback_data *p)
{
  size_t r;
  discord_interaction_application_command_callback_data_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
                "(tts):b,"
  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
                "(content):s,"
  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
                "(embeds):F,"
  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
                "(flags):d,"
  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
                "(components):F,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
                &p->tts,
  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
                p->content,
  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
                discord_embed_list_to_json, p->embeds,
  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
                &p->flags,
  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
                discord_component_list_to_json, p->components,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_interaction_application_command_callback_data_cleanup_v(void *p) {
  discord_interaction_application_command_callback_data_cleanup((struct discord_interaction_application_command_callback_data *)p);
}

void discord_interaction_application_command_callback_data_init_v(void *p) {
  discord_interaction_application_command_callback_data_init((struct discord_interaction_application_command_callback_data *)p);
}

void discord_interaction_application_command_callback_data_from_json_v(char *json, size_t len, void *pp) {
 discord_interaction_application_command_callback_data_from_json(json, len, (struct discord_interaction_application_command_callback_data**)pp);
}

size_t discord_interaction_application_command_callback_data_to_json_v(char *json, size_t len, void *p) {
  return discord_interaction_application_command_callback_data_to_json(json, len, (struct discord_interaction_application_command_callback_data*)p);
}

void discord_interaction_application_command_callback_data_list_free_v(void **p) {
  discord_interaction_application_command_callback_data_list_free((struct discord_interaction_application_command_callback_data**)p);
}

void discord_interaction_application_command_callback_data_list_from_json_v(char *str, size_t len, void *p) {
  discord_interaction_application_command_callback_data_list_from_json(str, len, (struct discord_interaction_application_command_callback_data ***)p);
}

size_t discord_interaction_application_command_callback_data_list_to_json_v(char *str, size_t len, void *p){
  return discord_interaction_application_command_callback_data_list_to_json(str, len, (struct discord_interaction_application_command_callback_data **)p);
}


void discord_interaction_application_command_callback_data_cleanup(struct discord_interaction_application_command_callback_data *d) {
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */
  // p->tts is a scalar
  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */
  if (d->content)
    free(d->content);
  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */
  if (d->embeds)
    discord_embed_list_free(d->embeds);
  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */
  // @todo p->(null)
  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */
  // p->flags is a scalar
  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */
  if (d->components)
    discord_component_list_free(d->components);
}

void discord_interaction_application_command_callback_data_init(struct discord_interaction_application_command_callback_data *p) {
  memset(p, 0, sizeof(struct discord_interaction_application_command_callback_data));
  /* specs/discord/slash_commands.json:203:18
     '{"name":"tts", "type":{"base":"bool"}, "option":true, "comment":"is the response TTS"}' */

  /* specs/discord/slash_commands.json:204:18
     '{"name":"content", "type":{"base":"char", "dec":"*"}, "option":true, "comment":"message content", "inject_if_not":null}' */

  /* specs/discord/slash_commands.json:205:18
     '{"name":"embeds", "type":{"base":"struct discord_embed", "dec":"ntl"}, "option":true, "comment":"support up to 10 embeds", "inject_if_not":null}' */

  /* specs/discord/slash_commands.json:206:18
     '{"name":"allowed_mentions", "type":{"base":"struct discord_allowed_mentions", "dec":"*"}, "option":true, "comment":"allowed mentions object", "inject_if_not":null, "todo": true}' */

  /* specs/discord/slash_commands.json:207:18
     '{"name":"flags", "type":{"base":"int", "int_alias":"enum discord_interaction_application_command_callback_data_flags"}, "option":true, "comment":"interaction application command callback data flags", "inject_if_not":0}' */

  /* specs/discord/slash_commands.json:208:18
     '{"name":"components", "type":{ "base":"struct discord_component", "dec":"ntl" }, "option":true, "comment":"message components", "inject_if_not":null}' */

}
void discord_interaction_application_command_callback_data_list_free(struct discord_interaction_application_command_callback_data **p) {
  ntl_free((void**)p, (vfvp)discord_interaction_application_command_callback_data_cleanup);
}

void discord_interaction_application_command_callback_data_list_from_json(char *str, size_t len, struct discord_interaction_application_command_callback_data ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_interaction_application_command_callback_data);
  d.init_elem = NULL;
  d.elem_from_buf = discord_interaction_application_command_callback_data_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_interaction_application_command_callback_data_list_to_json(char *str, size_t len, struct discord_interaction_application_command_callback_data **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_interaction_application_command_callback_data_to_json_v);
}



enum discord_interaction_application_command_callback_data_flags discord_interaction_application_command_callback_data_flags_from_string(char *s){
  if(strcasecmp("EPHEMERAL", s) == 0) return DISCORD_INTERACTION_APPLICATION_COMMAND_CALLBACK_DATA_EPHEMERAL;
  abort();
}
char* discord_interaction_application_command_callback_data_flags_to_string(enum discord_interaction_application_command_callback_data_flags v){
  if (v == DISCORD_INTERACTION_APPLICATION_COMMAND_CALLBACK_DATA_EPHEMERAL) return "EPHEMERAL";

  return (void*)0;
}
bool discord_interaction_application_command_callback_data_flags_has(enum discord_interaction_application_command_callback_data_flags v, char *s) {
  enum discord_interaction_application_command_callback_data_flags v1 = discord_interaction_application_command_callback_data_flags_from_string(s);
  if (v == v1) return true;
  return false;
}

void discord_message_interaction_from_json(char *json, size_t len, struct discord_message_interaction **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = calloc(1, sizeof **pp);
  struct discord_message_interaction *p = *pp;
  r=json_extract(json, len, 
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                "(id):F,"
  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
                "(name):?s,"
  /* specs/discord/slash_commands.json:231:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
                "(user):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                cee_strtoull, &p->id,
  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
                &p->type,
  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
                &p->name,
  /* specs/discord/slash_commands.json:231:18
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
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  p->__M.arg_switches[0] = &p->id;

  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
  p->__M.arg_switches[1] = &p->type;

  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
  p->__M.arg_switches[2] = p->name;

  /* specs/discord/slash_commands.json:231:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
  p->__M.arg_switches[3] = p->user;

}

size_t discord_message_interaction_to_json(char *json, size_t len, struct discord_message_interaction *p)
{
  size_t r;
  discord_message_interaction_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                "(id):|F|,"
  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
                "(type):d,"
  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
                "(name):s,"
  /* specs/discord/slash_commands.json:231:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
                "(user):F,"
                "@arg_switches:b",
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
                &p->type,
  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
                p->name,
  /* specs/discord/slash_commands.json:231:18
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
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */
  // p->id is a scalar
  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */
  // p->type is a scalar
  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/slash_commands.json:231:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
}

void discord_message_interaction_init(struct discord_message_interaction *p) {
  memset(p, 0, sizeof(struct discord_message_interaction));
  /* specs/discord/slash_commands.json:228:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the interaction"}' */

  /* specs/discord/slash_commands.json:229:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_interaction_request_types"}, "comment":"the request type of the interaction"}' */

  /* specs/discord/slash_commands.json:230:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"the name of the application command"}' */

  /* specs/discord/slash_commands.json:231:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "comment":"the user who invoked the interaction"}' */
  p->user = malloc(sizeof *p->user);
  discord_user_init(p->user);

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

