/* This file is generated from discord/sticker.json, Please don't edit it. */
/**
 * @file specs-code/discord/sticker.c
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


void discord_sticker_types_list_free_v(void **p) {
  discord_sticker_types_list_free((enum discord_sticker_types**)p);
}

void discord_sticker_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_sticker_types_list_from_json(str, len, (enum discord_sticker_types ***)p);
}

size_t discord_sticker_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_sticker_types_list_to_json(str, len, (enum discord_sticker_types **)p);
}

enum discord_sticker_types discord_sticker_types_eval(char *s){
  if(strcasecmp("STANDARD", s) == 0) return DISCORD_STICKER_STANDARD;
  if(strcasecmp("GUILD", s) == 0) return DISCORD_STICKER_GUILD;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_sticker_types_print(enum discord_sticker_types v){

  switch (v) {
  case DISCORD_STICKER_STANDARD: return "STANDARD";
  case DISCORD_STICKER_GUILD: return "GUILD";
  }

  return NULL;
}

void discord_sticker_types_list_free(enum discord_sticker_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_sticker_types_list_from_json(char *str, size_t len, enum discord_sticker_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_sticker_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_sticker_types_list_to_json(char *str, size_t len, enum discord_sticker_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}



void discord_sticker_format_types_list_free_v(void **p) {
  discord_sticker_format_types_list_free((enum discord_sticker_format_types**)p);
}

void discord_sticker_format_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_sticker_format_types_list_from_json(str, len, (enum discord_sticker_format_types ***)p);
}

size_t discord_sticker_format_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_sticker_format_types_list_to_json(str, len, (enum discord_sticker_format_types **)p);
}

enum discord_sticker_format_types discord_sticker_format_types_eval(char *s){
  if(strcasecmp("PNG", s) == 0) return DISCORD_STICKER_PNG;
  if(strcasecmp("APNG", s) == 0) return DISCORD_STICKER_APNG;
  if(strcasecmp("LOTTIE", s) == 0) return DISCORD_STICKER_LOTTIE;
  ERR("'%s' doesn't match any known enumerator.", s);
  return -1;
}

char* discord_sticker_format_types_print(enum discord_sticker_format_types v){

  switch (v) {
  case DISCORD_STICKER_PNG: return "PNG";
  case DISCORD_STICKER_APNG: return "APNG";
  case DISCORD_STICKER_LOTTIE: return "LOTTIE";
  }

  return NULL;
}

void discord_sticker_format_types_list_free(enum discord_sticker_format_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_sticker_format_types_list_from_json(char *str, size_t len, enum discord_sticker_format_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_sticker_format_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_sticker_format_types_list_to_json(char *str, size_t len, enum discord_sticker_format_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_sticker_from_json_p(char *json, size_t len, struct discord_sticker **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_sticker_from_json(json, len, *pp);
}
void discord_sticker_from_json(char *json, size_t len, struct discord_sticker *p)
{
  discord_sticker_init(p);
  json_extract(json, len, 
  /* discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                "(id):F,"
  /* discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
                "(pack_id):F,"
  /* discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                "(name):?s,"
  /* discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
                "(description):?s,"
  /* discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                "(tags):?s,"
  /* discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
                "(asset):?s,"
  /* discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
                "(type):d,"
  /* discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                "(format_type):d,"
  /* discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
                "(available):b,"
  /* discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
                "(guild_id):F,"
  /* discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
                "(user):F,"
  /* discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
                "(sort_value):d,",
  /* discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                cee_strtou64, &p->id,
  /* discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
                cee_strtou64, &p->pack_id,
  /* discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                &p->name,
  /* discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
                &p->description,
  /* discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                &p->tags,
  /* discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
                &p->asset,
  /* discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
                &p->type,
  /* discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                &p->format_type,
  /* discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
                &p->available,
  /* discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
                cee_strtou64, &p->guild_id,
  /* discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
                discord_user_from_json_p, &p->user,
  /* discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
                &p->sort_value);
}

size_t discord_sticker_to_json(char *json, size_t len, struct discord_sticker *p)
{
  size_t r;
  void *arg_switches[12]={NULL};
  /* discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  arg_switches[0] = &p->id;

  /* discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
  if (p->pack_id != 0)
    arg_switches[1] = &p->pack_id;

  /* discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  arg_switches[2] = p->name;

  /* discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
  arg_switches[3] = p->description;

  /* discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  arg_switches[4] = p->tags;

  /* discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
  arg_switches[5] = p->asset;

  /* discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
  arg_switches[6] = &p->type;

  /* discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  arg_switches[7] = &p->format_type;

  /* discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
  if (p->available != false)
    arg_switches[8] = &p->available;

  /* discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
  if (p->guild_id != 0)
    arg_switches[9] = &p->guild_id;

  /* discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
  if (p->user != NULL)
    arg_switches[10] = p->user;

  /* discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
  arg_switches[11] = &p->sort_value;

  r=json_inject(json, len, 
  /* discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                "(id):|F|,"
  /* discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
                "(pack_id):|F|,"
  /* discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                "(name):s,"
  /* discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
                "(description):s,"
  /* discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                "(tags):s,"
  /* discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
                "(asset):s,"
  /* discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
                "(type):d,"
  /* discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                "(format_type):d,"
  /* discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
                "(available):b,"
  /* discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
                "(guild_id):|F|,"
  /* discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
                "(user):F,"
  /* discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
                "(sort_value):d,"
                "@arg_switches:b",
  /* discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                cee_u64tostr, &p->id,
  /* discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
                cee_u64tostr, &p->pack_id,
  /* discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                p->name,
  /* discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
                p->description,
  /* discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                p->tags,
  /* discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
                p->asset,
  /* discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
                &p->type,
  /* discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                &p->format_type,
  /* discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
                &p->available,
  /* discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
                cee_u64tostr, &p->guild_id,
  /* discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
                discord_user_to_json, p->user,
  /* discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
                &p->sort_value,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_sticker_cleanup_v(void *p) {
  discord_sticker_cleanup((struct discord_sticker *)p);
}

void discord_sticker_init_v(void *p) {
  discord_sticker_init((struct discord_sticker *)p);
}

void discord_sticker_from_json_v(char *json, size_t len, void *p) {
 discord_sticker_from_json(json, len, (struct discord_sticker*)p);
}

size_t discord_sticker_to_json_v(char *json, size_t len, void *p) {
  return discord_sticker_to_json(json, len, (struct discord_sticker*)p);
}

void discord_sticker_list_free_v(void **p) {
  discord_sticker_list_free((struct discord_sticker**)p);
}

void discord_sticker_list_from_json_v(char *str, size_t len, void *p) {
  discord_sticker_list_from_json(str, len, (struct discord_sticker ***)p);
}

size_t discord_sticker_list_to_json_v(char *str, size_t len, void *p){
  return discord_sticker_list_to_json(str, len, (struct discord_sticker **)p);
}


void discord_sticker_cleanup(struct discord_sticker *d) {
  /* discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  (void)d->id;
  /* discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
  (void)d->pack_id;
  /* discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  if (d->name)
    free(d->name);
  /* discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
  if (d->description)
    free(d->description);
  /* discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  if (d->tags)
    free(d->tags);
  /* discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
  if (d->asset)
    free(d->asset);
  /* discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
  (void)d->type;
  /* discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  (void)d->format_type;
  /* discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
  (void)d->available;
  /* discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
  (void)d->guild_id;
  /* discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
  /* discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
  (void)d->sort_value;
}

void discord_sticker_init(struct discord_sticker *p) {
  memset(p, 0, sizeof(struct discord_sticker));
  /* discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */

  /* discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */

  /* discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */

  /* discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */

  /* discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */

  /* discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */

  /* discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */

  /* discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */

  /* discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */

  /* discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */

  /* discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */

  /* discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */

}
void discord_sticker_list_free(struct discord_sticker **p) {
  ntl_free((void**)p, (void(*)(void*))discord_sticker_cleanup);
}

void discord_sticker_list_from_json(char *str, size_t len, struct discord_sticker ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_sticker);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_sticker_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_sticker_list_to_json(char *str, size_t len, struct discord_sticker **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_sticker_to_json);
}


void discord_sticker_item_from_json_p(char *json, size_t len, struct discord_sticker_item **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_sticker_item_from_json(json, len, *pp);
}
void discord_sticker_item_from_json(char *json, size_t len, struct discord_sticker_item *p)
{
  discord_sticker_item_init(p);
  json_extract(json, len, 
  /* discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                "(id):F,"
  /* discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                "(name):?s,"
  /* discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                "(format_type):d,",
  /* discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                cee_strtou64, &p->id,
  /* discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                &p->name,
  /* discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                &p->format_type);
}

size_t discord_sticker_item_to_json(char *json, size_t len, struct discord_sticker_item *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  arg_switches[0] = &p->id;

  /* discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  arg_switches[1] = p->name;

  /* discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  arg_switches[2] = &p->format_type;

  r=json_inject(json, len, 
  /* discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                "(id):|F|,"
  /* discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                "(name):s,"
  /* discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                "(format_type):d,"
                "@arg_switches:b",
  /* discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                cee_u64tostr, &p->id,
  /* discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                p->name,
  /* discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                &p->format_type,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_sticker_item_cleanup_v(void *p) {
  discord_sticker_item_cleanup((struct discord_sticker_item *)p);
}

void discord_sticker_item_init_v(void *p) {
  discord_sticker_item_init((struct discord_sticker_item *)p);
}

void discord_sticker_item_from_json_v(char *json, size_t len, void *p) {
 discord_sticker_item_from_json(json, len, (struct discord_sticker_item*)p);
}

size_t discord_sticker_item_to_json_v(char *json, size_t len, void *p) {
  return discord_sticker_item_to_json(json, len, (struct discord_sticker_item*)p);
}

void discord_sticker_item_list_free_v(void **p) {
  discord_sticker_item_list_free((struct discord_sticker_item**)p);
}

void discord_sticker_item_list_from_json_v(char *str, size_t len, void *p) {
  discord_sticker_item_list_from_json(str, len, (struct discord_sticker_item ***)p);
}

size_t discord_sticker_item_list_to_json_v(char *str, size_t len, void *p){
  return discord_sticker_item_list_to_json(str, len, (struct discord_sticker_item **)p);
}


void discord_sticker_item_cleanup(struct discord_sticker_item *d) {
  /* discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  (void)d->id;
  /* discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  if (d->name)
    free(d->name);
  /* discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  (void)d->format_type;
}

void discord_sticker_item_init(struct discord_sticker_item *p) {
  memset(p, 0, sizeof(struct discord_sticker_item));
  /* discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */

  /* discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */

  /* discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */

}
void discord_sticker_item_list_free(struct discord_sticker_item **p) {
  ntl_free((void**)p, (void(*)(void*))discord_sticker_item_cleanup);
}

void discord_sticker_item_list_from_json(char *str, size_t len, struct discord_sticker_item ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_sticker_item);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_sticker_item_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_sticker_item_list_to_json(char *str, size_t len, struct discord_sticker_item **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_sticker_item_to_json);
}


void discord_sticker_pack_from_json_p(char *json, size_t len, struct discord_sticker_pack **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_sticker_pack_from_json(json, len, *pp);
}
void discord_sticker_pack_from_json(char *json, size_t len, struct discord_sticker_pack *p)
{
  discord_sticker_pack_init(p);
  json_extract(json, len, 
  /* discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
                "(id):F,"
  /* discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
                "(stickers):F,"
  /* discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
                "(name):?s,"
  /* discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
                "(sku_id):F,"
  /* discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
                "(cover_sticker_id):F,"
  /* discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
                "(description):?s,"
  /* discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
                "(banner_asset_id):F,",
  /* discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
                cee_strtou64, &p->id,
  /* discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
                discord_sticker_list_from_json, &p->stickers,
  /* discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
                &p->name,
  /* discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
                cee_strtou64, &p->sku_id,
  /* discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
                cee_strtou64, &p->cover_sticker_id,
  /* discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
                &p->description,
  /* discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
                cee_strtou64, &p->banner_asset_id);
}

size_t discord_sticker_pack_to_json(char *json, size_t len, struct discord_sticker_pack *p)
{
  size_t r;
  void *arg_switches[7]={NULL};
  /* discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
  arg_switches[0] = &p->id;

  /* discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
  arg_switches[1] = p->stickers;

  /* discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
  arg_switches[2] = p->name;

  /* discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
  arg_switches[3] = &p->sku_id;

  /* discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
  if (p->cover_sticker_id != 0)
    arg_switches[4] = &p->cover_sticker_id;

  /* discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
  arg_switches[5] = p->description;

  /* discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
  arg_switches[6] = &p->banner_asset_id;

  r=json_inject(json, len, 
  /* discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
                "(id):|F|,"
  /* discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
                "(stickers):F,"
  /* discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
                "(name):s,"
  /* discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
                "(sku_id):|F|,"
  /* discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
                "(cover_sticker_id):|F|,"
  /* discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
                "(description):s,"
  /* discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
                "(banner_asset_id):|F|,"
                "@arg_switches:b",
  /* discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
                cee_u64tostr, &p->id,
  /* discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
                discord_sticker_list_to_json, p->stickers,
  /* discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
                p->name,
  /* discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
                cee_u64tostr, &p->sku_id,
  /* discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
                cee_u64tostr, &p->cover_sticker_id,
  /* discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
                p->description,
  /* discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
                cee_u64tostr, &p->banner_asset_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


void discord_sticker_pack_cleanup_v(void *p) {
  discord_sticker_pack_cleanup((struct discord_sticker_pack *)p);
}

void discord_sticker_pack_init_v(void *p) {
  discord_sticker_pack_init((struct discord_sticker_pack *)p);
}

void discord_sticker_pack_from_json_v(char *json, size_t len, void *p) {
 discord_sticker_pack_from_json(json, len, (struct discord_sticker_pack*)p);
}

size_t discord_sticker_pack_to_json_v(char *json, size_t len, void *p) {
  return discord_sticker_pack_to_json(json, len, (struct discord_sticker_pack*)p);
}

void discord_sticker_pack_list_free_v(void **p) {
  discord_sticker_pack_list_free((struct discord_sticker_pack**)p);
}

void discord_sticker_pack_list_from_json_v(char *str, size_t len, void *p) {
  discord_sticker_pack_list_from_json(str, len, (struct discord_sticker_pack ***)p);
}

size_t discord_sticker_pack_list_to_json_v(char *str, size_t len, void *p){
  return discord_sticker_pack_list_to_json(str, len, (struct discord_sticker_pack **)p);
}


void discord_sticker_pack_cleanup(struct discord_sticker_pack *d) {
  /* discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
  (void)d->id;
  /* discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
  if (d->stickers)
    discord_sticker_list_free(d->stickers);
  /* discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
  if (d->name)
    free(d->name);
  /* discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
  (void)d->sku_id;
  /* discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
  (void)d->cover_sticker_id;
  /* discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
  if (d->description)
    free(d->description);
  /* discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
  (void)d->banner_asset_id;
}

void discord_sticker_pack_init(struct discord_sticker_pack *p) {
  memset(p, 0, sizeof(struct discord_sticker_pack));
  /* discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */

  /* discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */

  /* discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */

  /* discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */

  /* discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */

  /* discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */

  /* discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */

}
void discord_sticker_pack_list_free(struct discord_sticker_pack **p) {
  ntl_free((void**)p, (void(*)(void*))discord_sticker_pack_cleanup);
}

void discord_sticker_pack_list_from_json(char *str, size_t len, struct discord_sticker_pack ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_sticker_pack);
  d.init_elem = NULL;
  d.elem_from_buf = (void(*)(char*,size_t,void*))discord_sticker_pack_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_sticker_pack_list_to_json(char *str, size_t len, struct discord_sticker_pack **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (size_t(*)(char*,size_t,void*))discord_sticker_pack_to_json);
}

