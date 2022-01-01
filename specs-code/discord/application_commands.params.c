/* This file is generated from discord/application_commands.params.json, Please don't edit it. */
/**
 * @file specs-code/discord/application_commands.params.c
 * @see https://discord.com/developers/docs/interactions/application-commands
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_create_global_application_command_params_from_json_p(char *json, size_t len, struct discord_create_global_application_command_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_global_application_command_params_from_json(json, len, *pp);
}
void discord_create_global_application_command_params_from_json(char *json, size_t len, struct discord_create_global_application_command_params *p)
{
  discord_create_global_application_command_params_init(p);
  json_extract(json, len, 
  /* discord/application_commands.params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
                "(name):?s,"
  /* discord/application_commands.params.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
                "(description):?s,"
  /* discord/application_commands.params.json:15:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.params.json:16:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
  /* discord/application_commands.params.json:17:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
                "(type):d,",
  /* discord/application_commands.params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
                &p->name,
  /* discord/application_commands.params.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
                &p->description,
  /* discord/application_commands.params.json:15:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
  /* discord/application_commands.params.json:16:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
  /* discord/application_commands.params.json:17:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
                &p->type);
}

size_t discord_create_global_application_command_params_to_json(char *json, size_t len, struct discord_create_global_application_command_params *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* discord/application_commands.params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
  arg_switches[0] = p->name;

  /* discord/application_commands.params.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
  arg_switches[1] = p->description;

  /* discord/application_commands.params.json:15:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[2] = p->options;

  /* discord/application_commands.params.json:16:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  arg_switches[3] = &p->default_permission;

  /* discord/application_commands.params.json:17:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
  arg_switches[4] = &p->type;

  r=json_inject(json, len, 
  /* discord/application_commands.params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
                "(name):s,"
  /* discord/application_commands.params.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
                "(description):s,"
  /* discord/application_commands.params.json:15:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.params.json:16:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
  /* discord/application_commands.params.json:17:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
                "(type):d,"
                "@arg_switches:b",
  /* discord/application_commands.params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
                p->name,
  /* discord/application_commands.params.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
                p->description,
  /* discord/application_commands.params.json:15:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
  /* discord/application_commands.params.json:16:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
  /* discord/application_commands.params.json:17:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
                &p->type,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_global_application_command_params_cleanup_v(void *p) {
  discord_create_global_application_command_params_cleanup((struct discord_create_global_application_command_params *)p);
}

void discord_create_global_application_command_params_init_v(void *p) {
  discord_create_global_application_command_params_init((struct discord_create_global_application_command_params *)p);
}

void discord_create_global_application_command_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_global_application_command_params_from_json(json, len, (struct discord_create_global_application_command_params*)p);
}

size_t discord_create_global_application_command_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_global_application_command_params_to_json(json, len, (struct discord_create_global_application_command_params*)p);
}

void discord_create_global_application_command_params_list_free_v(void **p) {
  discord_create_global_application_command_params_list_free((struct discord_create_global_application_command_params**)p);
}

void discord_create_global_application_command_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_global_application_command_params_list_from_json(str, len, (struct discord_create_global_application_command_params ***)p);
}

size_t discord_create_global_application_command_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_global_application_command_params_list_to_json(str, len, (struct discord_create_global_application_command_params **)p);
}


void discord_create_global_application_command_params_cleanup(struct discord_create_global_application_command_params *d) {
  /* discord/application_commands.params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
  if (d->name)
    free(d->name);
  /* discord/application_commands.params.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
  if (d->description)
    free(d->description);
  /* discord/application_commands.params.json:15:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
  /* discord/application_commands.params.json:16:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  (void)d->default_permission;
  /* discord/application_commands.params.json:17:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
  (void)d->type;
}

void discord_create_global_application_command_params_init(struct discord_create_global_application_command_params *p) {
  memset(p, 0, sizeof(struct discord_create_global_application_command_params));
  /* discord/application_commands.params.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */

  /* discord/application_commands.params.json:14:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */

  /* discord/application_commands.params.json:15:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */

  /* discord/application_commands.params.json:16:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  p->default_permission = true;

  /* discord/application_commands.params.json:17:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */

}
void discord_create_global_application_command_params_list_free(struct discord_create_global_application_command_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_global_application_command_params_cleanup);
}

void discord_create_global_application_command_params_list_from_json(char *str, size_t len, struct discord_create_global_application_command_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_global_application_command_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_global_application_command_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_global_application_command_params_list_to_json(char *str, size_t len, struct discord_create_global_application_command_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_global_application_command_params_to_json);
}


void discord_edit_global_application_command_params_from_json_p(char *json, size_t len, struct discord_edit_global_application_command_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_edit_global_application_command_params_from_json(json, len, *pp);
}
void discord_edit_global_application_command_params_from_json(char *json, size_t len, struct discord_edit_global_application_command_params *p)
{
  discord_edit_global_application_command_params_init(p);
  json_extract(json, len, 
  /* discord/application_commands.params.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
                "(name):?s,"
  /* discord/application_commands.params.json:28:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
                "(description):?s,"
  /* discord/application_commands.params.json:29:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.params.json:30:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,",
  /* discord/application_commands.params.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
                &p->name,
  /* discord/application_commands.params.json:28:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
                &p->description,
  /* discord/application_commands.params.json:29:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
  /* discord/application_commands.params.json:30:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission);
}

size_t discord_edit_global_application_command_params_to_json(char *json, size_t len, struct discord_edit_global_application_command_params *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/application_commands.params.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/application_commands.params.json:28:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
  if (p->description != NULL)
    arg_switches[1] = p->description;

  /* discord/application_commands.params.json:29:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[2] = p->options;

  /* discord/application_commands.params.json:30:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  arg_switches[3] = &p->default_permission;

  r=json_inject(json, len, 
  /* discord/application_commands.params.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
                "(name):s,"
  /* discord/application_commands.params.json:28:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
                "(description):s,"
  /* discord/application_commands.params.json:29:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.params.json:30:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
                "@arg_switches:b",
  /* discord/application_commands.params.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
                p->name,
  /* discord/application_commands.params.json:28:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
                p->description,
  /* discord/application_commands.params.json:29:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
  /* discord/application_commands.params.json:30:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_edit_global_application_command_params_cleanup_v(void *p) {
  discord_edit_global_application_command_params_cleanup((struct discord_edit_global_application_command_params *)p);
}

void discord_edit_global_application_command_params_init_v(void *p) {
  discord_edit_global_application_command_params_init((struct discord_edit_global_application_command_params *)p);
}

void discord_edit_global_application_command_params_from_json_v(char *json, size_t len, void *p) {
 discord_edit_global_application_command_params_from_json(json, len, (struct discord_edit_global_application_command_params*)p);
}

size_t discord_edit_global_application_command_params_to_json_v(char *json, size_t len, void *p) {
  return discord_edit_global_application_command_params_to_json(json, len, (struct discord_edit_global_application_command_params*)p);
}

void discord_edit_global_application_command_params_list_free_v(void **p) {
  discord_edit_global_application_command_params_list_free((struct discord_edit_global_application_command_params**)p);
}

void discord_edit_global_application_command_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_edit_global_application_command_params_list_from_json(str, len, (struct discord_edit_global_application_command_params ***)p);
}

size_t discord_edit_global_application_command_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_edit_global_application_command_params_list_to_json(str, len, (struct discord_edit_global_application_command_params **)p);
}


void discord_edit_global_application_command_params_cleanup(struct discord_edit_global_application_command_params *d) {
  /* discord/application_commands.params.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
  if (d->name)
    free(d->name);
  /* discord/application_commands.params.json:28:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
  if (d->description)
    free(d->description);
  /* discord/application_commands.params.json:29:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
  /* discord/application_commands.params.json:30:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  (void)d->default_permission;
}

void discord_edit_global_application_command_params_init(struct discord_edit_global_application_command_params *p) {
  memset(p, 0, sizeof(struct discord_edit_global_application_command_params));
  /* discord/application_commands.params.json:27:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */

  /* discord/application_commands.params.json:28:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */

  /* discord/application_commands.params.json:29:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */

  /* discord/application_commands.params.json:30:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  p->default_permission = true;

}
void discord_edit_global_application_command_params_list_free(struct discord_edit_global_application_command_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_edit_global_application_command_params_cleanup);
}

void discord_edit_global_application_command_params_list_from_json(char *str, size_t len, struct discord_edit_global_application_command_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_global_application_command_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_edit_global_application_command_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_global_application_command_params_list_to_json(char *str, size_t len, struct discord_edit_global_application_command_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_edit_global_application_command_params_to_json);
}


void discord_create_guild_application_command_params_from_json_p(char *json, size_t len, struct discord_create_guild_application_command_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_guild_application_command_params_from_json(json, len, *pp);
}
void discord_create_guild_application_command_params_from_json(char *json, size_t len, struct discord_create_guild_application_command_params *p)
{
  discord_create_guild_application_command_params_init(p);
  json_extract(json, len, 
  /* discord/application_commands.params.json:40:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
                "(name):?s,"
  /* discord/application_commands.params.json:41:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
                "(description):?s,"
  /* discord/application_commands.params.json:42:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.params.json:43:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
  /* discord/application_commands.params.json:44:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
                "(type):d,",
  /* discord/application_commands.params.json:40:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
                &p->name,
  /* discord/application_commands.params.json:41:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
                &p->description,
  /* discord/application_commands.params.json:42:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
  /* discord/application_commands.params.json:43:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
  /* discord/application_commands.params.json:44:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
                &p->type);
}

size_t discord_create_guild_application_command_params_to_json(char *json, size_t len, struct discord_create_guild_application_command_params *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* discord/application_commands.params.json:40:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
  arg_switches[0] = p->name;

  /* discord/application_commands.params.json:41:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
  arg_switches[1] = p->description;

  /* discord/application_commands.params.json:42:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[2] = p->options;

  /* discord/application_commands.params.json:43:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  arg_switches[3] = &p->default_permission;

  /* discord/application_commands.params.json:44:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
  arg_switches[4] = &p->type;

  r=json_inject(json, len, 
  /* discord/application_commands.params.json:40:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
                "(name):s,"
  /* discord/application_commands.params.json:41:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
                "(description):s,"
  /* discord/application_commands.params.json:42:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.params.json:43:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
  /* discord/application_commands.params.json:44:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
                "(type):d,"
                "@arg_switches:b",
  /* discord/application_commands.params.json:40:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
                p->name,
  /* discord/application_commands.params.json:41:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
                p->description,
  /* discord/application_commands.params.json:42:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
  /* discord/application_commands.params.json:43:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
  /* discord/application_commands.params.json:44:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
                &p->type,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_create_guild_application_command_params_cleanup_v(void *p) {
  discord_create_guild_application_command_params_cleanup((struct discord_create_guild_application_command_params *)p);
}

void discord_create_guild_application_command_params_init_v(void *p) {
  discord_create_guild_application_command_params_init((struct discord_create_guild_application_command_params *)p);
}

void discord_create_guild_application_command_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_application_command_params_from_json(json, len, (struct discord_create_guild_application_command_params*)p);
}

size_t discord_create_guild_application_command_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_application_command_params_to_json(json, len, (struct discord_create_guild_application_command_params*)p);
}

void discord_create_guild_application_command_params_list_free_v(void **p) {
  discord_create_guild_application_command_params_list_free((struct discord_create_guild_application_command_params**)p);
}

void discord_create_guild_application_command_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_application_command_params_list_from_json(str, len, (struct discord_create_guild_application_command_params ***)p);
}

size_t discord_create_guild_application_command_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_application_command_params_list_to_json(str, len, (struct discord_create_guild_application_command_params **)p);
}


void discord_create_guild_application_command_params_cleanup(struct discord_create_guild_application_command_params *d) {
  /* discord/application_commands.params.json:40:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */
  if (d->name)
    free(d->name);
  /* discord/application_commands.params.json:41:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */
  if (d->description)
    free(d->description);
  /* discord/application_commands.params.json:42:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
  /* discord/application_commands.params.json:43:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  (void)d->default_permission;
  /* discord/application_commands.params.json:44:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */
  (void)d->type;
}

void discord_create_guild_application_command_params_init(struct discord_create_guild_application_command_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_application_command_params));
  /* discord/application_commands.params.json:40:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name"}' */

  /* discord/application_commands.params.json:41:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description"}' */

  /* discord/application_commands.params.json:42:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */

  /* discord/application_commands.params.json:43:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  p->default_permission = true;

  /* discord/application_commands.params.json:44:20
     '{ "name": "type", "type":{"base":"int", "int_alias":"enum discord_application_command_types", "inject_if_not":0}}' */

}
void discord_create_guild_application_command_params_list_free(struct discord_create_guild_application_command_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_create_guild_application_command_params_cleanup);
}

void discord_create_guild_application_command_params_list_from_json(char *str, size_t len, struct discord_create_guild_application_command_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_application_command_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_create_guild_application_command_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_application_command_params_list_to_json(char *str, size_t len, struct discord_create_guild_application_command_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_create_guild_application_command_params_to_json);
}


void discord_edit_guild_application_command_params_from_json_p(char *json, size_t len, struct discord_edit_guild_application_command_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_edit_guild_application_command_params_from_json(json, len, *pp);
}
void discord_edit_guild_application_command_params_from_json(char *json, size_t len, struct discord_edit_guild_application_command_params *p)
{
  discord_edit_guild_application_command_params_init(p);
  json_extract(json, len, 
  /* discord/application_commands.params.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
                "(name):?s,"
  /* discord/application_commands.params.json:55:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
                "(description):?s,"
  /* discord/application_commands.params.json:56:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.params.json:57:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,",
  /* discord/application_commands.params.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
                &p->name,
  /* discord/application_commands.params.json:55:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
                &p->description,
  /* discord/application_commands.params.json:56:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_from_json, &p->options,
  /* discord/application_commands.params.json:57:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission);
}

size_t discord_edit_guild_application_command_params_to_json(char *json, size_t len, struct discord_edit_guild_application_command_params *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/application_commands.params.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/application_commands.params.json:55:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
  if (p->description != NULL)
    arg_switches[1] = p->description;

  /* discord/application_commands.params.json:56:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (p->options != NULL)
    arg_switches[2] = p->options;

  /* discord/application_commands.params.json:57:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  arg_switches[3] = &p->default_permission;

  r=json_inject(json, len, 
  /* discord/application_commands.params.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
                "(name):s,"
  /* discord/application_commands.params.json:55:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
                "(description):s,"
  /* discord/application_commands.params.json:56:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                "(options):F,"
  /* discord/application_commands.params.json:57:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                "(default_permission):b,"
                "@arg_switches:b",
  /* discord/application_commands.params.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
                p->name,
  /* discord/application_commands.params.json:55:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
                p->description,
  /* discord/application_commands.params.json:56:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
                discord_application_command_option_list_to_json, p->options,
  /* discord/application_commands.params.json:57:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
                &p->default_permission,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_edit_guild_application_command_params_cleanup_v(void *p) {
  discord_edit_guild_application_command_params_cleanup((struct discord_edit_guild_application_command_params *)p);
}

void discord_edit_guild_application_command_params_init_v(void *p) {
  discord_edit_guild_application_command_params_init((struct discord_edit_guild_application_command_params *)p);
}

void discord_edit_guild_application_command_params_from_json_v(char *json, size_t len, void *p) {
 discord_edit_guild_application_command_params_from_json(json, len, (struct discord_edit_guild_application_command_params*)p);
}

size_t discord_edit_guild_application_command_params_to_json_v(char *json, size_t len, void *p) {
  return discord_edit_guild_application_command_params_to_json(json, len, (struct discord_edit_guild_application_command_params*)p);
}

void discord_edit_guild_application_command_params_list_free_v(void **p) {
  discord_edit_guild_application_command_params_list_free((struct discord_edit_guild_application_command_params**)p);
}

void discord_edit_guild_application_command_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_edit_guild_application_command_params_list_from_json(str, len, (struct discord_edit_guild_application_command_params ***)p);
}

size_t discord_edit_guild_application_command_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_edit_guild_application_command_params_list_to_json(str, len, (struct discord_edit_guild_application_command_params **)p);
}


void discord_edit_guild_application_command_params_cleanup(struct discord_edit_guild_application_command_params *d) {
  /* discord/application_commands.params.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */
  if (d->name)
    free(d->name);
  /* discord/application_commands.params.json:55:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */
  if (d->description)
    free(d->description);
  /* discord/application_commands.params.json:56:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */
  if (d->options)
    discord_application_command_option_list_free(d->options);
  /* discord/application_commands.params.json:57:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  (void)d->default_permission;
}

void discord_edit_guild_application_command_params_init(struct discord_edit_guild_application_command_params *p) {
  memset(p, 0, sizeof(struct discord_edit_guild_application_command_params));
  /* discord/application_commands.params.json:54:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*" }, "comment":"1-32 lowercase character name", "inject_if_not":null}' */

  /* discord/application_commands.params.json:55:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"1-100 character description", "inject_if_not":null}' */

  /* discord/application_commands.params.json:56:20
     '{ "name": "options", "type":{"base":"struct discord_application_command_option", "dec":"ntl"}, "comment":"the parameters for the command", "inject_if_not":null}' */

  /* discord/application_commands.params.json:57:20
     '{ "name": "default_permission", "type":{"base":"bool", "default_value":true}, "comment":"whether the command is enabled by default when the app is added to a guild"}' */
  p->default_permission = true;

}
void discord_edit_guild_application_command_params_list_free(struct discord_edit_guild_application_command_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_edit_guild_application_command_params_cleanup);
}

void discord_edit_guild_application_command_params_list_from_json(char *str, size_t len, struct discord_edit_guild_application_command_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_guild_application_command_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_edit_guild_application_command_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_guild_application_command_params_list_to_json(char *str, size_t len, struct discord_edit_guild_application_command_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_edit_guild_application_command_params_to_json);
}


void discord_edit_application_command_permissions_params_from_json_p(char *json, size_t len, struct discord_edit_application_command_permissions_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_edit_application_command_permissions_params_from_json(json, len, *pp);
}
void discord_edit_application_command_permissions_params_from_json(char *json, size_t len, struct discord_edit_application_command_permissions_params *p)
{
  discord_edit_application_command_permissions_params_init(p);
  json_extract(json, len, 
  /* discord/application_commands.params.json:67:20
     '{ "name": "permissions", "type":{"base": "struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                "(permissions):F,",
  /* discord/application_commands.params.json:67:20
     '{ "name": "permissions", "type":{"base": "struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                discord_application_command_permissions_list_from_json, &p->permissions);
}

size_t discord_edit_application_command_permissions_params_to_json(char *json, size_t len, struct discord_edit_application_command_permissions_params *p)
{
  size_t r;
  void *arg_switches[1]={NULL};
  /* discord/application_commands.params.json:67:20
     '{ "name": "permissions", "type":{"base": "struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  arg_switches[0] = p->permissions;

  r=json_inject(json, len, 
  /* discord/application_commands.params.json:67:20
     '{ "name": "permissions", "type":{"base": "struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                "(permissions):F,"
                "@arg_switches:b",
  /* discord/application_commands.params.json:67:20
     '{ "name": "permissions", "type":{"base": "struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
                discord_application_command_permissions_list_to_json, p->permissions,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_edit_application_command_permissions_params_cleanup_v(void *p) {
  discord_edit_application_command_permissions_params_cleanup((struct discord_edit_application_command_permissions_params *)p);
}

void discord_edit_application_command_permissions_params_init_v(void *p) {
  discord_edit_application_command_permissions_params_init((struct discord_edit_application_command_permissions_params *)p);
}

void discord_edit_application_command_permissions_params_from_json_v(char *json, size_t len, void *p) {
 discord_edit_application_command_permissions_params_from_json(json, len, (struct discord_edit_application_command_permissions_params*)p);
}

size_t discord_edit_application_command_permissions_params_to_json_v(char *json, size_t len, void *p) {
  return discord_edit_application_command_permissions_params_to_json(json, len, (struct discord_edit_application_command_permissions_params*)p);
}

void discord_edit_application_command_permissions_params_list_free_v(void **p) {
  discord_edit_application_command_permissions_params_list_free((struct discord_edit_application_command_permissions_params**)p);
}

void discord_edit_application_command_permissions_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_edit_application_command_permissions_params_list_from_json(str, len, (struct discord_edit_application_command_permissions_params ***)p);
}

size_t discord_edit_application_command_permissions_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_edit_application_command_permissions_params_list_to_json(str, len, (struct discord_edit_application_command_permissions_params **)p);
}


void discord_edit_application_command_permissions_params_cleanup(struct discord_edit_application_command_permissions_params *d) {
  /* discord/application_commands.params.json:67:20
     '{ "name": "permissions", "type":{"base": "struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */
  if (d->permissions)
    discord_application_command_permissions_list_free(d->permissions);
}

void discord_edit_application_command_permissions_params_init(struct discord_edit_application_command_permissions_params *p) {
  memset(p, 0, sizeof(struct discord_edit_application_command_permissions_params));
  /* discord/application_commands.params.json:67:20
     '{ "name": "permissions", "type":{"base": "struct discord_application_command_permissions", "dec":"ntl"}, "comment":"the permissions for the command in the guild"}' */

}
void discord_edit_application_command_permissions_params_list_free(struct discord_edit_application_command_permissions_params **p) {
  ntl_free((void**)p, (void(*)(void*))discord_edit_application_command_permissions_params_cleanup);
}

void discord_edit_application_command_permissions_params_list_from_json(char *str, size_t len, struct discord_edit_application_command_permissions_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_edit_application_command_permissions_params);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_edit_application_command_permissions_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_edit_application_command_permissions_params_list_to_json(char *str, size_t len, struct discord_edit_application_command_permissions_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_edit_application_command_permissions_params_to_json);
}

