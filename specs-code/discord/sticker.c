/* This file is generated from specs/discord/sticker.json, Please don't edit it. */
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


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
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



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
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


void discord_sticker_from_json(char *json, size_t len, struct discord_sticker **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_sticker *p = *pp;
  discord_sticker_init(p);
  r=json_extract(json, len, 
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                "(id):F,"
  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
                "(pack_id):F,"
  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                "(name):?s,"
  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
                "(description):?s,"
  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                "(tags):?s,"
  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
                "(asset):?s,"
  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
                "(type):d,"
  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                "(format_type):d,"
  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
                "(available):b,"
  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
                "(guild_id):F,"
  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
                "(user):F,"
  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
                "(sort_value):d,",
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                cee_strtoull, &p->id,
  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
                cee_strtoull, &p->pack_id,
  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                &p->name,
  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
                &p->description,
  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                &p->tags,
  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
                &p->asset,
  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
                &p->type,
  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                &p->format_type,
  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
                &p->available,
  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
                discord_user_from_json, &p->user,
  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
                &p->sort_value);
  ret = r;
}

size_t discord_sticker_to_json(char *json, size_t len, struct discord_sticker *p)
{
  size_t r;
  void *arg_switches[12]={NULL};
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  arg_switches[0] = &p->id;

  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
  if (p->pack_id != 0)
    arg_switches[1] = &p->pack_id;

  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  arg_switches[2] = p->name;

  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
  arg_switches[3] = p->description;

  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  arg_switches[4] = p->tags;

  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
  arg_switches[5] = p->asset;

  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
  arg_switches[6] = &p->type;

  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  arg_switches[7] = &p->format_type;

  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
  if (p->available != false)
    arg_switches[8] = &p->available;

  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
  if (p->guild_id != 0)
    arg_switches[9] = &p->guild_id;

  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
  if (p->user != NULL)
    arg_switches[10] = p->user;

  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
  arg_switches[11] = &p->sort_value;

  r=json_inject(json, len, 
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                "(id):|F|,"
  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
                "(pack_id):|F|,"
  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                "(name):s,"
  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
                "(description):s,"
  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                "(tags):s,"
  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
                "(asset):s,"
  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
                "(type):d,"
  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                "(format_type):d,"
  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
                "(available):b,"
  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
                "(guild_id):|F|,"
  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
                "(user):F,"
  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
                "(sort_value):d,"
                "@arg_switches:b",
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
                cee_ulltostr, &p->pack_id,
  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                p->name,
  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
                p->description,
  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
                p->tags,
  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
                p->asset,
  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
                &p->type,
  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                &p->format_type,
  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
                &p->available,
  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
                discord_user_to_json, p->user,
  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
                &p->sort_value,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_sticker_cleanup_v(void *p) {
  discord_sticker_cleanup((struct discord_sticker *)p);
}

void discord_sticker_init_v(void *p) {
  discord_sticker_init((struct discord_sticker *)p);
}

void discord_sticker_from_json_v(char *json, size_t len, void *pp) {
 discord_sticker_from_json(json, len, (struct discord_sticker**)pp);
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
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  /* p->id is a scalar */
  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */
  /* p->pack_id is a scalar */
  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */
  if (d->description)
    free(d->description);
  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  if (d->tags)
    free(d->tags);
  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */
  if (d->asset)
    free(d->asset);
  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */
  /* p->type is a scalar */
  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  /* p->format_type is a scalar */
  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */
  /* p->available is a scalar */
  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */
  /* p->guild_id is a scalar */
  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */
  if (d->user) {
    discord_user_cleanup(d->user);
    free(d->user);
  }
  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */
  /* p->sort_value is a scalar */
}

void discord_sticker_init(struct discord_sticker *p) {
  memset(p, 0, sizeof(struct discord_sticker));
  /* specs/discord/sticker.json:31:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */

  /* specs/discord/sticker.json:32:18
     '{"name":"pack_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"for standard stickers, id of the pack the sticker is from"}' */

  /* specs/discord/sticker.json:33:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */

  /* specs/discord/sticker.json:34:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker"}' */

  /* specs/discord/sticker.json:35:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */

  /* specs/discord/sticker.json:36:18
     '{"name":"asset", "type":{"base":"char", "dec":"*"}, "comment":"Deprecated previously the sticker asset hash, now an empty string"}' */

  /* specs/discord/sticker.json:37:18
     '{"name":"type", "type":{"base":"int", "int_alias":"enum discord_sticker_types"}, "comment":"type of sticker"}' */

  /* specs/discord/sticker.json:38:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */

  /* specs/discord/sticker.json:39:18
     '{"name":"available", "type":{"base":"bool"}, "inject_if_not":false, "comment":"whether this guild sticker can be used, may be false due to loss of Server Boosts"}' */

  /* specs/discord/sticker.json:40:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of the guild that owns this sticker"}' */

  /* specs/discord/sticker.json:41:18
     '{"name":"user", "type":{"base":"struct discord_user", "dec":"*"}, "inject_if_not":null, "comment":"the user that uploaded the guild sticker"}' */

  /* specs/discord/sticker.json:42:18
     '{"name":"sort_value", "type":{"base":"int"}, "comment":"the standard sticker's sort order within its pack"}' */

}
void discord_sticker_list_free(struct discord_sticker **p) {
  ntl_free((void**)p, (vfvp)discord_sticker_cleanup);
}

void discord_sticker_list_from_json(char *str, size_t len, struct discord_sticker ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_sticker);
  d.init_elem = NULL;
  d.elem_from_buf = discord_sticker_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_sticker_list_to_json(char *str, size_t len, struct discord_sticker **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_sticker_to_json_v);
}


void discord_sticker_item_from_json(char *json, size_t len, struct discord_sticker_item **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_sticker_item *p = *pp;
  discord_sticker_item_init(p);
  r=json_extract(json, len, 
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                "(id):F,"
  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                "(name):?s,"
  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                "(format_type):d,",
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                cee_strtoull, &p->id,
  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                &p->name,
  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                &p->format_type);
  ret = r;
}

size_t discord_sticker_item_to_json(char *json, size_t len, struct discord_sticker_item *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  arg_switches[0] = &p->id;

  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  arg_switches[1] = p->name;

  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  arg_switches[2] = &p->format_type;

  r=json_inject(json, len, 
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                "(id):|F|,"
  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                "(name):s,"
  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                "(format_type):d,"
                "@arg_switches:b",
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
                p->name,
  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
                &p->format_type,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_sticker_item_cleanup_v(void *p) {
  discord_sticker_item_cleanup((struct discord_sticker_item *)p);
}

void discord_sticker_item_init_v(void *p) {
  discord_sticker_item_init((struct discord_sticker_item *)p);
}

void discord_sticker_item_from_json_v(char *json, size_t len, void *pp) {
 discord_sticker_item_from_json(json, len, (struct discord_sticker_item**)pp);
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
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */
  /* p->id is a scalar */
  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */
  /* p->format_type is a scalar */
}

void discord_sticker_item_init(struct discord_sticker_item *p) {
  memset(p, 0, sizeof(struct discord_sticker_item));
  /* specs/discord/sticker.json:50:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker"}' */

  /* specs/discord/sticker.json:51:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker"}' */

  /* specs/discord/sticker.json:52:18
     '{"name":"format_type", "type":{"base":"int", "int_alias":"enum discord_sticker_format_types"}, "comment":"type of sticker format"}' */

}
void discord_sticker_item_list_free(struct discord_sticker_item **p) {
  ntl_free((void**)p, (vfvp)discord_sticker_item_cleanup);
}

void discord_sticker_item_list_from_json(char *str, size_t len, struct discord_sticker_item ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_sticker_item);
  d.init_elem = NULL;
  d.elem_from_buf = discord_sticker_item_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_sticker_item_list_to_json(char *str, size_t len, struct discord_sticker_item **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_sticker_item_to_json_v);
}


void discord_sticker_pack_from_json(char *json, size_t len, struct discord_sticker_pack **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_sticker_pack *p = *pp;
  discord_sticker_pack_init(p);
  r=json_extract(json, len, 
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
                "(id):F,"
  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
                "(stickers):F,"
  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
                "(name):?s,"
  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
                "(sku_id):F,"
  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
                "(cover_sticker_id):F,"
  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
                "(description):?s,"
  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
                "(banner_asset_id):F,",
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
                cee_strtoull, &p->id,
  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
                discord_sticker_list_from_json, &p->stickers,
  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
                &p->name,
  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
                cee_strtoull, &p->sku_id,
  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
                cee_strtoull, &p->cover_sticker_id,
  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
                &p->description,
  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
                cee_strtoull, &p->banner_asset_id);
  ret = r;
}

size_t discord_sticker_pack_to_json(char *json, size_t len, struct discord_sticker_pack *p)
{
  size_t r;
  void *arg_switches[7]={NULL};
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
  arg_switches[0] = &p->id;

  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
  arg_switches[1] = p->stickers;

  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
  arg_switches[2] = p->name;

  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
  arg_switches[3] = &p->sku_id;

  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
  if (p->cover_sticker_id != 0)
    arg_switches[4] = &p->cover_sticker_id;

  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
  arg_switches[5] = p->description;

  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
  arg_switches[6] = &p->banner_asset_id;

  r=json_inject(json, len, 
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
                "(id):|F|,"
  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
                "(stickers):F,"
  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
                "(name):s,"
  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
                "(sku_id):|F|,"
  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
                "(cover_sticker_id):|F|,"
  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
                "(description):s,"
  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
                "(banner_asset_id):|F|,"
                "@arg_switches:b",
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
                cee_ulltostr, &p->id,
  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
                discord_sticker_list_to_json, p->stickers,
  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
                p->name,
  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
                cee_ulltostr, &p->sku_id,
  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
                cee_ulltostr, &p->cover_sticker_id,
  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
                p->description,
  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
                cee_ulltostr, &p->banner_asset_id,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_sticker_pack_cleanup_v(void *p) {
  discord_sticker_pack_cleanup((struct discord_sticker_pack *)p);
}

void discord_sticker_pack_init_v(void *p) {
  discord_sticker_pack_init((struct discord_sticker_pack *)p);
}

void discord_sticker_pack_from_json_v(char *json, size_t len, void *pp) {
 discord_sticker_pack_from_json(json, len, (struct discord_sticker_pack**)pp);
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
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */
  /* p->id is a scalar */
  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */
  if (d->stickers)
    discord_sticker_list_free(d->stickers);
  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */
  if (d->name)
    free(d->name);
  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */
  /* p->sku_id is a scalar */
  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */
  /* p->cover_sticker_id is a scalar */
  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */
  if (d->description)
    free(d->description);
  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */
  /* p->banner_asset_id is a scalar */
}

void discord_sticker_pack_init(struct discord_sticker_pack *p) {
  memset(p, 0, sizeof(struct discord_sticker_pack));
  /* specs/discord/sticker.json:60:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack"}' */

  /* specs/discord/sticker.json:61:18
     '{"name":"stickers", "type":{"base":"struct discord_sticker", "dec":"ntl"}, "comment":"the stickers in the pack"}' */

  /* specs/discord/sticker.json:62:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker pack"}' */

  /* specs/discord/sticker.json:63:18
     '{"name":"sku_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the pack's SKU"}' */

  /* specs/discord/sticker.json:64:18
     '{"name":"cover_sticker_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "inject_if_not":0, "comment":"id of a sticker in the pack which is shown as the pack's icon"}' */

  /* specs/discord/sticker.json:65:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker pack"}' */

  /* specs/discord/sticker.json:66:18
     '{"name":"banner_asset_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the sticker pack's banner image"}' */

}
void discord_sticker_pack_list_free(struct discord_sticker_pack **p) {
  ntl_free((void**)p, (vfvp)discord_sticker_pack_cleanup);
}

void discord_sticker_pack_list_from_json(char *str, size_t len, struct discord_sticker_pack ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_sticker_pack);
  d.init_elem = NULL;
  d.elem_from_buf = discord_sticker_pack_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_sticker_pack_list_to_json(char *str, size_t len, struct discord_sticker_pack **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_sticker_pack_to_json_v);
}

