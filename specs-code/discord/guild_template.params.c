/* This file is generated from discord/guild_template.params.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild_template.params.c
 * @see https://discord.com/developers/docs/resources/guild-template
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_create_guild_from_guild_template_params_from_json_p(char *json, size_t len, struct discord_create_guild_from_guild_template_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_guild_from_guild_template_params_from_json(json, len, *pp);
}
void discord_create_guild_from_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p)
{
  discord_create_guild_from_guild_template_params_init(p);
  json_extract(json, len, 
  /* discord/guild_template.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
                "(name):?s,"
  /* discord/guild_template.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */
                "(icon):?s,",
  /* discord/guild_template.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
                &p->name,
  /* discord/guild_template.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */
                &p->icon);
}

size_t discord_create_guild_from_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/guild_template.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  arg_switches[0] = p->name;

  /* discord/guild_template.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */
  if (p->icon != NULL)
    arg_switches[1] = p->icon;

  r=json_inject(json, len, 
  /* discord/guild_template.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
                "(name):s,"
  /* discord/guild_template.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */
                "(icon):s,"
                "@arg_switches:b",
  /* discord/guild_template.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
                p->name,
  /* discord/guild_template.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */
                p->icon,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_guild_from_guild_template_params_cleanup_v(void *p) {
  discord_create_guild_from_guild_template_params_cleanup((struct discord_create_guild_from_guild_template_params *)p);
}

void discord_create_guild_from_guild_template_params_init_v(void *p) {
  discord_create_guild_from_guild_template_params_init((struct discord_create_guild_from_guild_template_params *)p);
}

void discord_create_guild_from_guild_template_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_from_guild_template_params_from_json(json, len, (struct discord_create_guild_from_guild_template_params*)p);
}

size_t discord_create_guild_from_guild_template_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_from_guild_template_params_to_json(json, len, (struct discord_create_guild_from_guild_template_params*)p);
}

void discord_create_guild_from_guild_template_params_list_free_v(void **p) {
  discord_create_guild_from_guild_template_params_list_free((struct discord_create_guild_from_guild_template_params**)p);
}

void discord_create_guild_from_guild_template_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_from_guild_template_params_list_from_json(str, len, (struct discord_create_guild_from_guild_template_params ***)p);
}

size_t discord_create_guild_from_guild_template_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_from_guild_template_params_list_to_json(str, len, (struct discord_create_guild_from_guild_template_params **)p);
}


void discord_create_guild_from_guild_template_params_cleanup(struct discord_create_guild_from_guild_template_params *d) {
  /* discord/guild_template.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  if (d->name)
    free(d->name);
  /* discord/guild_template.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */
  if (d->icon)
    free(d->icon);
}

void discord_create_guild_from_guild_template_params_init(struct discord_create_guild_from_guild_template_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_from_guild_template_params));
  /* discord/guild_template.params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */

  /* discord/guild_template.params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */

}
void discord_create_guild_from_guild_template_params_list_free(struct discord_create_guild_from_guild_template_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_guild_from_guild_template_params_cleanup);
}

void discord_create_guild_from_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_from_guild_template_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_from_guild_template_params);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_create_guild_from_guild_template_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_from_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_from_guild_template_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_create_guild_from_guild_template_params_to_json);
}


void discord_create_guild_template_params_from_json_p(char *json, size_t len, struct discord_create_guild_template_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_guild_template_params_from_json(json, len, *pp);
}
void discord_create_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_template_params *p)
{
  discord_create_guild_template_params_init(p);
  json_extract(json, len, 
  /* discord/guild_template.params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
                "(name):?s,"
  /* discord/guild_template.params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
                "(description):?s,",
  /* discord/guild_template.params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
                &p->name,
  /* discord/guild_template.params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
                &p->description);
}

size_t discord_create_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_template_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/guild_template.params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  arg_switches[0] = p->name;

  /* discord/guild_template.params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
  if (p->description != NULL)
    arg_switches[1] = p->description;

  r=json_inject(json, len, 
  /* discord/guild_template.params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
                "(name):s,"
  /* discord/guild_template.params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
                "(description):s,"
                "@arg_switches:b",
  /* discord/guild_template.params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
                p->name,
  /* discord/guild_template.params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
                p->description,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_guild_template_params_cleanup_v(void *p) {
  discord_create_guild_template_params_cleanup((struct discord_create_guild_template_params *)p);
}

void discord_create_guild_template_params_init_v(void *p) {
  discord_create_guild_template_params_init((struct discord_create_guild_template_params *)p);
}

void discord_create_guild_template_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_template_params_from_json(json, len, (struct discord_create_guild_template_params*)p);
}

size_t discord_create_guild_template_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_template_params_to_json(json, len, (struct discord_create_guild_template_params*)p);
}

void discord_create_guild_template_params_list_free_v(void **p) {
  discord_create_guild_template_params_list_free((struct discord_create_guild_template_params**)p);
}

void discord_create_guild_template_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_template_params_list_from_json(str, len, (struct discord_create_guild_template_params ***)p);
}

size_t discord_create_guild_template_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_template_params_list_to_json(str, len, (struct discord_create_guild_template_params **)p);
}


void discord_create_guild_template_params_cleanup(struct discord_create_guild_template_params *d) {
  /* discord/guild_template.params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  if (d->name)
    free(d->name);
  /* discord/guild_template.params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
  if (d->description)
    free(d->description);
}

void discord_create_guild_template_params_init(struct discord_create_guild_template_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_template_params));
  /* discord/guild_template.params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */

  /* discord/guild_template.params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */

}
void discord_create_guild_template_params_list_free(struct discord_create_guild_template_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_guild_template_params_cleanup);
}

void discord_create_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_template_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_template_params);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_create_guild_template_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_template_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_create_guild_template_params_to_json);
}


void discord_modify_guild_template_params_from_json_p(char *json, size_t len, struct discord_modify_guild_template_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_guild_template_params_from_json(json, len, *pp);
}
void discord_modify_guild_template_params_from_json(char *json, size_t len, struct discord_modify_guild_template_params *p)
{
  discord_modify_guild_template_params_init(p);
  json_extract(json, len, 
  /* discord/guild_template.params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */
                "(name):?s,"
  /* discord/guild_template.params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
                "(description):?s,",
  /* discord/guild_template.params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */
                &p->name,
  /* discord/guild_template.params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
                &p->description);
}

size_t discord_modify_guild_template_params_to_json(char *json, size_t len, struct discord_modify_guild_template_params *p)
{
  size_t r;
  void *arg_switches[2]={NULL};
  /* discord/guild_template.params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */
  if (p->name != NULL)
    arg_switches[0] = p->name;

  /* discord/guild_template.params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
  if (p->description != NULL)
    arg_switches[1] = p->description;

  r=json_inject(json, len, 
  /* discord/guild_template.params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */
                "(name):s,"
  /* discord/guild_template.params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
                "(description):s,"
                "@arg_switches:b",
  /* discord/guild_template.params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */
                p->name,
  /* discord/guild_template.params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
                p->description,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_template_params_cleanup_v(void *p) {
  discord_modify_guild_template_params_cleanup((struct discord_modify_guild_template_params *)p);
}

void discord_modify_guild_template_params_init_v(void *p) {
  discord_modify_guild_template_params_init((struct discord_modify_guild_template_params *)p);
}

void discord_modify_guild_template_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_template_params_from_json(json, len, (struct discord_modify_guild_template_params*)p);
}

size_t discord_modify_guild_template_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_template_params_to_json(json, len, (struct discord_modify_guild_template_params*)p);
}

void discord_modify_guild_template_params_list_free_v(void **p) {
  discord_modify_guild_template_params_list_free((struct discord_modify_guild_template_params**)p);
}

void discord_modify_guild_template_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_template_params_list_from_json(str, len, (struct discord_modify_guild_template_params ***)p);
}

size_t discord_modify_guild_template_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_template_params_list_to_json(str, len, (struct discord_modify_guild_template_params **)p);
}


void discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params *d) {
  /* discord/guild_template.params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */
  if (d->name)
    free(d->name);
  /* discord/guild_template.params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
  if (d->description)
    free(d->description);
}

void discord_modify_guild_template_params_init(struct discord_modify_guild_template_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_template_params));
  /* discord/guild_template.params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */

  /* discord/guild_template.params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */

}
void discord_modify_guild_template_params_list_free(struct discord_modify_guild_template_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_template_params_cleanup);
}

void discord_modify_guild_template_params_list_from_json(char *str, size_t len, struct discord_modify_guild_template_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_template_params);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_modify_guild_template_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_template_params_list_to_json(char *str, size_t len, struct discord_modify_guild_template_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_modify_guild_template_params_to_json);
}

