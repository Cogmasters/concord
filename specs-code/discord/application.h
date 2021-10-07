/* This file is generated from specs/discord/application.json, Please don't edit it. */
/**
 * @file specs-code/discord/application.h
 * @see https://discord.com/developers/docs/resources/application
 */


/* Application Structure */
/* defined at specs/discord/application.json:9:22 */
/**
 * @see https://discord.com/developers/docs/resources/application#application-object-application-structure
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_application_init(struct discord_application *)`
 *   * Cleanup:

 *     * :code:`void discord_application_cleanup(struct discord_application *)`
 *     * :code:`void discord_application_list_free(struct discord_application **)`
 *   * JSON Decoder:

 *     * :code:`void discord_application_from_json(char *rbuf, size_t len, struct discord_application **)`
 *     * :code:`void discord_application_list_from_json(char *rbuf, size_t len, struct discord_application ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_application_to_json(char *wbuf, size_t len, struct discord_application *)`
 *     * :code:`void discord_application_list_to_json(char *wbuf, size_t len, struct discord_application **)`
 * @endverbatim
 */
struct discord_application {
  /* specs/discord/application.json:12:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the app" }' */
  u64_snowflake_t id; /**< the id of the app */

  /* specs/discord/application.json:13:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"the name of the app" }' */
  char *name; /**< the name of the app */

  /* specs/discord/application.json:14:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*"}, "comment":"the icon hash of the app", "inject_if_not":null }' */
  char *icon; /**< the icon hash of the app */

  /* specs/discord/application.json:15:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}, "comment":"the description of the app" }' */
  char *description; /**< the description of the app */

  /* specs/discord/application.json:16:20
     '{ "name": "rpc_origins", "type":{ "base":"ja_str", "dec":"ntl"}, "comment":"an array of rpc origin urls, if rpc is enabled", "inject_if_not":null }' */
  ja_str **rpc_origins; /**< an array of rpc origin urls, if rpc is enabled */

  /* specs/discord/application.json:17:19
     '{ "name":"bot_public","type":{"base":"bool"}, "comment":"when false only app owner can join the app's bot to guilds"}' */
  bool bot_public; /**< when false only app owner can join the app's bot to guilds */

  /* specs/discord/application.json:18:19
     '{ "name":"bot_require_code_grant","type":{"base":"bool"}, "comment":"when true the app's bot will only join upon completion of the full oauth2 code grant flow"}' */
  bool bot_require_code_grant; /**< when true the app's bot will only join upon completion of the full oauth2 code grant flow */

  /* specs/discord/application.json:19:20
     '{ "name": "term_of_service_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's terms of service", "inject_if_not":null }' */
  char *term_of_service_url; /**< the url of the app's terms of service */

  /* specs/discord/application.json:20:20
     '{ "name": "privacy_policy_url", "type":{ "base":"char", "dec":"*"}, "comment":"the url of the app's privacy policy", "inject_if_not":null }' */
  char *privacy_policy_url; /**< the url of the app's privacy policy */

  /* specs/discord/application.json:21:19
     '{ "name":"team","type":{"base":"struct discord_team", "dec":"*"}, "comment":"if the application belongs to a team, this will be a list of the members of that team", "inject_if_not":null, "todo":true }' */
  /* @todo team if the application belongs to a team, this will be a list of the members of that team; */

  /* specs/discord/application.json:22:20
     '{ "name": "guild_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the guild on which it has been linked", "inject_if_not":0 }' */
  u64_snowflake_t guild_id; /**< if this application is a game sold on Discord, this field will be the guild on which it has been linked */

  /* specs/discord/application.json:23:20
     '{ "name": "primary_sku_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake"}, "comment":"if this application is a game sold on Discord, this field will be the id of the \"Game SKU\" that is created, if exists", "inject_if_not":0 }' */
  u64_snowflake_t primary_sku_id; /**< if this application is a game sold on Discord, this field will be the id of the "Game SKU" that is created, if exists */

  /* specs/discord/application.json:24:20
     '{ "name": "slug", "type":{ "base":"char", "dec":"*"}, "comment":"if this application is a game sold on Discord, this field will be the URL slug that links to the store page", "inject_if_not":null }' */
  char *slug; /**< if this application is a game sold on Discord, this field will be the URL slug that links to the store page */

  /* specs/discord/application.json:25:20
     '{ "name": "flags", "type":{ "base":"int", "int_alias":"enum discord_application_flags" }, "comment":"the application's public flags", "inject_if_not":0 }' */
  enum discord_application_flags flags; /**< the application's public flags */

};
extern void discord_application_cleanup_v(void *p);
extern void discord_application_cleanup(struct discord_application *p);
extern void discord_application_init_v(void *p);
extern void discord_application_init(struct discord_application *p);
extern void discord_application_from_json_v(char *json, size_t len, void *pp);
extern void discord_application_from_json(char *json, size_t len, struct discord_application **pp);
extern size_t discord_application_to_json_v(char *json, size_t len, void *p);
extern size_t discord_application_to_json(char *json, size_t len, struct discord_application *p);
extern void discord_application_list_free_v(void **p);
extern void discord_application_list_free(struct discord_application **p);
extern void discord_application_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_list_from_json(char *str, size_t len, struct discord_application ***p);
extern size_t discord_application_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_list_to_json(char *str, size_t len, struct discord_application **p);


/* Application Flags */
/* defined at specs/discord/application.json:28:5 */
/**
 * @see https://discord.com/developers/docs/resources/application#application-object-application-flags
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_application_flags_print(enum discord_application_flags code)`
 *   * :code:`enum discord_application_flags discord_application_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_application_flags {
  DISCORD_APPLICATION_GATEWAY_PRESENCE = 4096, /**< 1 << 12 */
  DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED = 8192, /**< 1 << 13 */
  DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS = 16384, /**< 1 << 14 */
  DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED = 32768, /**< 1 << 15 */
  DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT = 65536, /**< 1 << 16 */
  DISCORD_APPLICATION_EMBEDDED = 131072, /**< 1 << 17 */
};
extern char* discord_application_flags_print(enum discord_application_flags);
extern enum discord_application_flags discord_application_flags_eval(char*);
extern void discord_application_flags_list_free_v(void **p);
extern void discord_application_flags_list_free(enum discord_application_flags **p);
extern void discord_application_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_application_flags_list_from_json(char *str, size_t len, enum discord_application_flags ***p);
extern size_t discord_application_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_application_flags_list_to_json(char *str, size_t len, enum discord_application_flags **p);
