/* This file is generated from specs/discord/sticker.params.json, Please don't edit it. */
/**
 * @file specs-code/discord/sticker.params.c
 * @see (null)
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_list_nitro_sticker_packs_response_from_json_p(char *json, size_t len, struct discord_list_nitro_sticker_packs_response **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_list_nitro_sticker_packs_response_from_json(json, len, *pp);
}
void discord_list_nitro_sticker_packs_response_from_json(char *json, size_t len, struct discord_list_nitro_sticker_packs_response *p)
{
  discord_list_nitro_sticker_packs_response_init(p);
  json_extract(json, len, 
  /* specs/discord/sticker.params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */
                "(sticker_packs):F,",
  /* specs/discord/sticker.params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */
                discord_sticker_pack_list_from_json, &p->sticker_packs);
}

size_t discord_list_nitro_sticker_packs_response_to_json(char *json, size_t len, struct discord_list_nitro_sticker_packs_response *p)
{
  size_t r;
  void *arg_switches[1]={NULL};
  /* specs/discord/sticker.params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */
  arg_switches[0] = p->sticker_packs;

  r=json_inject(json, len, 
  /* specs/discord/sticker.params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */
                "(sticker_packs):F,"
                "@arg_switches:b",
  /* specs/discord/sticker.params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */
                discord_sticker_pack_list_to_json, p->sticker_packs,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_list_nitro_sticker_packs_response_cleanup_v(void *p) {
  discord_list_nitro_sticker_packs_response_cleanup((struct discord_list_nitro_sticker_packs_response *)p);
}

void discord_list_nitro_sticker_packs_response_init_v(void *p) {
  discord_list_nitro_sticker_packs_response_init((struct discord_list_nitro_sticker_packs_response *)p);
}

void discord_list_nitro_sticker_packs_response_from_json_v(char *json, size_t len, void *p) {
 discord_list_nitro_sticker_packs_response_from_json(json, len, (struct discord_list_nitro_sticker_packs_response*)p);
}

size_t discord_list_nitro_sticker_packs_response_to_json_v(char *json, size_t len, void *p) {
  return discord_list_nitro_sticker_packs_response_to_json(json, len, (struct discord_list_nitro_sticker_packs_response*)p);
}

void discord_list_nitro_sticker_packs_response_list_free_v(void **p) {
  discord_list_nitro_sticker_packs_response_list_free((struct discord_list_nitro_sticker_packs_response**)p);
}

void discord_list_nitro_sticker_packs_response_list_from_json_v(char *str, size_t len, void *p) {
  discord_list_nitro_sticker_packs_response_list_from_json(str, len, (struct discord_list_nitro_sticker_packs_response ***)p);
}

size_t discord_list_nitro_sticker_packs_response_list_to_json_v(char *str, size_t len, void *p){
  return discord_list_nitro_sticker_packs_response_list_to_json(str, len, (struct discord_list_nitro_sticker_packs_response **)p);
}


void discord_list_nitro_sticker_packs_response_cleanup(struct discord_list_nitro_sticker_packs_response *d) {
  /* specs/discord/sticker.params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */
  if (d->sticker_packs)
    discord_sticker_pack_list_free(d->sticker_packs);
}

void discord_list_nitro_sticker_packs_response_init(struct discord_list_nitro_sticker_packs_response *p) {
  memset(p, 0, sizeof(struct discord_list_nitro_sticker_packs_response));
  /* specs/discord/sticker.params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */

}
void discord_list_nitro_sticker_packs_response_list_free(struct discord_list_nitro_sticker_packs_response **p) {
  ntl_free((void**)p, (vfvp)discord_list_nitro_sticker_packs_response_cleanup);
}

void discord_list_nitro_sticker_packs_response_list_from_json(char *str, size_t len, struct discord_list_nitro_sticker_packs_response ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_list_nitro_sticker_packs_response);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_list_nitro_sticker_packs_response_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_list_nitro_sticker_packs_response_list_to_json(char *str, size_t len, struct discord_list_nitro_sticker_packs_response **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_list_nitro_sticker_packs_response_to_json);
}


void discord_create_guild_sticker_params_from_json_p(char *json, size_t len, struct discord_create_guild_sticker_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_create_guild_sticker_params_from_json(json, len, *pp);
}
void discord_create_guild_sticker_params_from_json(char *json, size_t len, struct discord_create_guild_sticker_params *p)
{
  discord_create_guild_sticker_params_init(p);
  json_extract(json, len, 
  /* specs/discord/sticker.params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
                "(name):?s,"
  /* specs/discord/sticker.params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
                "(description):?s,"
  /* specs/discord/sticker.params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                "(tags):?s,",
  /* specs/discord/sticker.params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
                &p->name,
  /* specs/discord/sticker.params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
                &p->description,
  /* specs/discord/sticker.params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                &p->tags);
}

size_t discord_create_guild_sticker_params_to_json(char *json, size_t len, struct discord_create_guild_sticker_params *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* specs/discord/sticker.params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
  arg_switches[0] = p->name;

  /* specs/discord/sticker.params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
  arg_switches[1] = p->description;

  /* specs/discord/sticker.params.json:22:18
     '{"name":"file", "type":{ "base":"struct discord_attachment", "dec":"*" }, "loc":"multipart", "comment":"the sticker file to upload, must be a PNG, APNG, or Lottie JSON file, max 500 KB"}' */
  arg_switches[2] = p->file;

  /* specs/discord/sticker.params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  arg_switches[3] = p->tags;

  r=json_inject(json, len, 
  /* specs/discord/sticker.params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
                "(name):s,"
  /* specs/discord/sticker.params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
                "(description):s,"
  /* specs/discord/sticker.params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                "(tags):s,"
                "@arg_switches:b",
  /* specs/discord/sticker.params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
                p->name,
  /* specs/discord/sticker.params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
                p->description,
  /* specs/discord/sticker.params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                p->tags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_create_guild_sticker_params_cleanup_v(void *p) {
  discord_create_guild_sticker_params_cleanup((struct discord_create_guild_sticker_params *)p);
}

void discord_create_guild_sticker_params_init_v(void *p) {
  discord_create_guild_sticker_params_init((struct discord_create_guild_sticker_params *)p);
}

void discord_create_guild_sticker_params_from_json_v(char *json, size_t len, void *p) {
 discord_create_guild_sticker_params_from_json(json, len, (struct discord_create_guild_sticker_params*)p);
}

size_t discord_create_guild_sticker_params_to_json_v(char *json, size_t len, void *p) {
  return discord_create_guild_sticker_params_to_json(json, len, (struct discord_create_guild_sticker_params*)p);
}

void discord_create_guild_sticker_params_list_free_v(void **p) {
  discord_create_guild_sticker_params_list_free((struct discord_create_guild_sticker_params**)p);
}

void discord_create_guild_sticker_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_create_guild_sticker_params_list_from_json(str, len, (struct discord_create_guild_sticker_params ***)p);
}

size_t discord_create_guild_sticker_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_create_guild_sticker_params_list_to_json(str, len, (struct discord_create_guild_sticker_params **)p);
}


void discord_create_guild_sticker_params_cleanup(struct discord_create_guild_sticker_params *d) {
  /* specs/discord/sticker.params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/sticker.params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
  if (d->description)
    free(d->description);
  /* specs/discord/sticker.params.json:22:18
     '{"name":"file", "type":{ "base":"struct discord_attachment", "dec":"*" }, "loc":"multipart", "comment":"the sticker file to upload, must be a PNG, APNG, or Lottie JSON file, max 500 KB"}' */
  if (d->file) {
    discord_attachment_cleanup(d->file);
    free(d->file);
  }
  /* specs/discord/sticker.params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  if (d->tags)
    free(d->tags);
}

void discord_create_guild_sticker_params_init(struct discord_create_guild_sticker_params *p) {
  memset(p, 0, sizeof(struct discord_create_guild_sticker_params));
  /* specs/discord/sticker.params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */

  /* specs/discord/sticker.params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */

  /* specs/discord/sticker.params.json:22:18
     '{"name":"file", "type":{ "base":"struct discord_attachment", "dec":"*" }, "loc":"multipart", "comment":"the sticker file to upload, must be a PNG, APNG, or Lottie JSON file, max 500 KB"}' */

  /* specs/discord/sticker.params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */

}
void discord_create_guild_sticker_params_list_free(struct discord_create_guild_sticker_params **p) {
  ntl_free((void**)p, (vfvp)discord_create_guild_sticker_params_cleanup);
}

void discord_create_guild_sticker_params_list_from_json(char *str, size_t len, struct discord_create_guild_sticker_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_create_guild_sticker_params);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_create_guild_sticker_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_create_guild_sticker_params_list_to_json(char *str, size_t len, struct discord_create_guild_sticker_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_create_guild_sticker_params_to_json);
}


void discord_modify_guild_sticker_params_from_json_p(char *json, size_t len, struct discord_modify_guild_sticker_params **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_modify_guild_sticker_params_from_json(json, len, *pp);
}
void discord_modify_guild_sticker_params_from_json(char *json, size_t len, struct discord_modify_guild_sticker_params *p)
{
  discord_modify_guild_sticker_params_init(p);
  json_extract(json, len, 
  /* specs/discord/sticker.params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
                "(name):?s,"
  /* specs/discord/sticker.params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
                "(description):?s,"
  /* specs/discord/sticker.params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                "(tags):?s,",
  /* specs/discord/sticker.params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
                &p->name,
  /* specs/discord/sticker.params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
                &p->description,
  /* specs/discord/sticker.params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                &p->tags);
}

size_t discord_modify_guild_sticker_params_to_json(char *json, size_t len, struct discord_modify_guild_sticker_params *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* specs/discord/sticker.params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
  arg_switches[0] = p->name;

  /* specs/discord/sticker.params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
  arg_switches[1] = p->description;

  /* specs/discord/sticker.params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  arg_switches[2] = p->tags;

  r=json_inject(json, len, 
  /* specs/discord/sticker.params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
                "(name):s,"
  /* specs/discord/sticker.params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
                "(description):s,"
  /* specs/discord/sticker.params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                "(tags):s,"
                "@arg_switches:b",
  /* specs/discord/sticker.params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
                p->name,
  /* specs/discord/sticker.params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
                p->description,
  /* specs/discord/sticker.params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                p->tags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_modify_guild_sticker_params_cleanup_v(void *p) {
  discord_modify_guild_sticker_params_cleanup((struct discord_modify_guild_sticker_params *)p);
}

void discord_modify_guild_sticker_params_init_v(void *p) {
  discord_modify_guild_sticker_params_init((struct discord_modify_guild_sticker_params *)p);
}

void discord_modify_guild_sticker_params_from_json_v(char *json, size_t len, void *p) {
 discord_modify_guild_sticker_params_from_json(json, len, (struct discord_modify_guild_sticker_params*)p);
}

size_t discord_modify_guild_sticker_params_to_json_v(char *json, size_t len, void *p) {
  return discord_modify_guild_sticker_params_to_json(json, len, (struct discord_modify_guild_sticker_params*)p);
}

void discord_modify_guild_sticker_params_list_free_v(void **p) {
  discord_modify_guild_sticker_params_list_free((struct discord_modify_guild_sticker_params**)p);
}

void discord_modify_guild_sticker_params_list_from_json_v(char *str, size_t len, void *p) {
  discord_modify_guild_sticker_params_list_from_json(str, len, (struct discord_modify_guild_sticker_params ***)p);
}

size_t discord_modify_guild_sticker_params_list_to_json_v(char *str, size_t len, void *p){
  return discord_modify_guild_sticker_params_list_to_json(str, len, (struct discord_modify_guild_sticker_params **)p);
}


void discord_modify_guild_sticker_params_cleanup(struct discord_modify_guild_sticker_params *d) {
  /* specs/discord/sticker.params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/sticker.params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
  if (d->description)
    free(d->description);
  /* specs/discord/sticker.params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  if (d->tags)
    free(d->tags);
}

void discord_modify_guild_sticker_params_init(struct discord_modify_guild_sticker_params *p) {
  memset(p, 0, sizeof(struct discord_modify_guild_sticker_params));
  /* specs/discord/sticker.params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */

  /* specs/discord/sticker.params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */

  /* specs/discord/sticker.params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */

}
void discord_modify_guild_sticker_params_list_free(struct discord_modify_guild_sticker_params **p) {
  ntl_free((void**)p, (vfvp)discord_modify_guild_sticker_params_cleanup);
}

void discord_modify_guild_sticker_params_list_from_json(char *str, size_t len, struct discord_modify_guild_sticker_params ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_modify_guild_sticker_params);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_modify_guild_sticker_params_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_modify_guild_sticker_params_list_to_json(char *str, size_t len, struct discord_modify_guild_sticker_params **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_modify_guild_sticker_params_to_json);
}

