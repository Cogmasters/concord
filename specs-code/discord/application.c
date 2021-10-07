/* This file is generated from specs/discord/application.json, Please don't edit it. */
/**
 * @file specs-code/discord/application.c
 * @see https://discord.com/developers/docs/resources/application
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_application_from_json(char *json, size_t len, struct discord_application **pp)
{
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_application *p = *pp;
  discord_application_init(p);
  r=json_extract(json, len, 
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */
                "(id):F,"
  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */
                "(name):?s,"
  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */
                "(icon):?s,"
  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */
                "(description):?s,"
  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */
                "(rpc_origins):F,"
  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */
                "(bot_public):b,"
  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */
                "(bot_require_code_grant):b,"
  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */
                "(term_of_service_url):?s,"
  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */
                "(privacy_policy_url):?s,"
  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */
  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */
                "(guild_id):F,"
  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */
                "(primary_sku_id):F,"
  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */
                "(slug):?s,"
  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */
                "(flags):d,",
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */
                cee_strtoull, &p->id,
  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */
                &p->name,
  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */
                &p->icon,
  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */
                &p->description,
  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */
                ja_str_list_from_json, &p->rpc_origins,
  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */
                &p->bot_public,
  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */
                &p->bot_require_code_grant,
  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */
                &p->term_of_service_url,
  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */
                &p->privacy_policy_url,
  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */
  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */
                cee_strtoull, &p->primary_sku_id,
  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */
                &p->slug,
  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */
                &p->flags);
  ret = r;
}

size_t discord_application_to_json(char *json, size_t len, struct discord_application *p)
{
  size_t r;
  void *arg_switches[14]={NULL};
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */
  arg_switches[0] = &p->id;

  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */
  arg_switches[1] = p->name;

  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */
  if (p->icon != NULL)
    arg_switches[2] = p->icon;

  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */
  arg_switches[3] = p->description;

  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */
  if (p->rpc_origins != NULL)
    arg_switches[4] = p->rpc_origins;

  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */
  arg_switches[5] = &p->bot_public;

  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */
  arg_switches[6] = &p->bot_require_code_grant;

  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */
  if (p->term_of_service_url != NULL)
    arg_switches[7] = p->term_of_service_url;

  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */
  if (p->privacy_policy_url != NULL)
    arg_switches[8] = p->privacy_policy_url;

  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */

  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */
  if (p->guild_id != 0)
    arg_switches[10] = &p->guild_id;

  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */
  if (p->primary_sku_id != 0)
    arg_switches[11] = &p->primary_sku_id;

  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */
  if (p->slug != NULL)
    arg_switches[12] = p->slug;

  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */
  if (p->flags != 0)
    arg_switches[13] = &p->flags;

  r=json_inject(json, len, 
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */
                "(id):|F|,"
  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */
                "(name):s,"
  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */
                "(icon):s,"
  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */
                "(description):s,"
  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */
                "(rpc_origins):F,"
  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */
                "(bot_public):b,"
  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */
                "(bot_require_code_grant):b,"
  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */
                "(term_of_service_url):s,"
  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */
                "(privacy_policy_url):s,"
  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */
  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */
                "(guild_id):|F|,"
  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */
                "(primary_sku_id):|F|,"
  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */
                "(slug):s,"
  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */
                "(flags):d,"
                "@arg_switches:b",
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */
                cee_ulltostr, &p->id,
  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */
                p->name,
  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */
                p->icon,
  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */
                p->description,
  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */
                ja_str_list_to_json, p->rpc_origins,
  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */
                &p->bot_public,
  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */
                &p->bot_require_code_grant,
  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */
                p->term_of_service_url,
  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */
                p->privacy_policy_url,
  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */
  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */
                cee_ulltostr, &p->primary_sku_id,
  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */
                p->slug,
  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */
                &p->flags,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_cleanup_v(void *p) {
  discord_application_cleanup((struct discord_application *)p);
}

void discord_application_init_v(void *p) {
  discord_application_init((struct discord_application *)p);
}

void discord_application_from_json_v(char *json, size_t len, void *pp) {
 discord_application_from_json(json, len, (struct discord_application**)pp);
}

size_t discord_application_to_json_v(char *json, size_t len, void *p) {
  return discord_application_to_json(json, len, (struct discord_application*)p);
}

void discord_application_list_free_v(void **p) {
  discord_application_list_free((struct discord_application**)p);
}

void discord_application_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_list_from_json(str, len, (struct discord_application ***)p);
}

size_t discord_application_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_list_to_json(str, len, (struct discord_application **)p);
}


void discord_application_cleanup(struct discord_application *d) {
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */
  /* p->id is a scalar */
  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */
  if (d->name)
    free(d->name);
  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */
  if (d->icon)
    free(d->icon);
  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */
  if (d->description)
    free(d->description);
  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */
  if (d->rpc_origins)
    ja_str_list_free(d->rpc_origins);
  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */
  /* p->bot_public is a scalar */
  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */
  /* p->bot_require_code_grant is a scalar */
  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */
  if (d->term_of_service_url)
    free(d->term_of_service_url);
  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */
  if (d->privacy_policy_url)
    free(d->privacy_policy_url);
  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */
  /* @todo p->(null) */
  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */
  /* p->guild_id is a scalar */
  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */
  /* p->primary_sku_id is a scalar */
  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */
  if (d->slug)
    free(d->slug);
  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */
  /* p->flags is a scalar */
}

void discord_application_init(struct discord_application *p) {
  memset(p, 0, sizeof(struct discord_application));
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */

  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */

  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */

  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */

  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */

  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */

  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */

  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */

  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */

  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */

  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */

  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */

  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */

  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */

}
void discord_application_list_free(struct discord_application **p) {
  ntl_free((void**)p, (vfvp)discord_application_cleanup);
}

void discord_application_list_from_json(char *str, size_t len, struct discord_application ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_application);
  d.init_elem = NULL;
  d.elem_from_buf = discord_application_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_list_to_json(char *str, size_t len, struct discord_application **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_application_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_application_flags_list_free_v(void **p) {
  discord_application_flags_list_free((enum discord_application_flags**)p);
}

void discord_application_flags_list_from_json_v(char *str, size_t len, void *p) {
  discord_application_flags_list_from_json(str, len, (enum discord_application_flags ***)p);
}

size_t discord_application_flags_list_to_json_v(char *str, size_t len, void *p){
  return discord_application_flags_list_to_json(str, len, (enum discord_application_flags **)p);
}

enum discord_application_flags discord_application_flags_eval(char *s){
  if(strcasecmp("GATEWAY_PRESENCE", s) == 0) return DISCORD_APPLICATION_GATEWAY_PRESENCE;
  if(strcasecmp("GATEWAY_PRESENCE_LIMITED", s) == 0) return DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED;
  if(strcasecmp("GATEWAY_GUILD_MEMBERS", s) == 0) return DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS;
  if(strcasecmp("GATEWAY_GUILD_MEMBERS_LIMITED", s) == 0) return DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED;
  if(strcasecmp("VERIFICATION_PENDING_GUILD_LIMIT", s) == 0) return DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT;
  if(strcasecmp("EMBEDDED", s) == 0) return DISCORD_APPLICATION_EMBEDDED;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_application_flags_print(enum discord_application_flags v){

  switch (v) {
  case DISCORD_APPLICATION_GATEWAY_PRESENCE: return "GATEWAY_PRESENCE";
  case DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED: return "GATEWAY_PRESENCE_LIMITED";
  case DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS: return "GATEWAY_GUILD_MEMBERS";
  case DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED: return "GATEWAY_GUILD_MEMBERS_LIMITED";
  case DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT: return "VERIFICATION_PENDING_GUILD_LIMIT";
  case DISCORD_APPLICATION_EMBEDDED: return "EMBEDDED";
  }

  return NULL;
}

void discord_application_flags_list_free(enum discord_application_flags **p) {
  ntl_free((void**)p, NULL);
}

void discord_application_flags_list_from_json(char *str, size_t len, enum discord_application_flags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_application_flags);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_application_flags_list_to_json(char *str, size_t len, enum discord_application_flags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}

