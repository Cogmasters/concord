/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/guild-template.endpoints-params.h
 * @see https://discord.com/developers/docs/resources/guild-template
 */


/* Create Guild From Guild Template */
/* defined at specs/discord/guild-template.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_from_guild_template_params_init(struct discord_create_guild_from_guild_template_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_from_guild_template_params_cleanup(struct discord_create_guild_from_guild_template_params *)`
 *     * :code:`void discord_create_guild_from_guild_template_params_list_free(struct discord_create_guild_from_guild_template_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_from_guild_template_params_from_json(char *rbuf, size_t len, struct discord_create_guild_from_guild_template_params **)`
 *     * :code:`void discord_create_guild_from_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_from_guild_template_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_from_guild_template_params_to_json(char *wbuf, size_t len, struct discord_create_guild_from_guild_template_params *)`
 *     * :code:`void discord_create_guild_from_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_from_guild_template_params **)`
 * @endverbatim
 */
struct discord_create_guild_from_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  char *name; /**< name of the guild */

  /* specs/discord/guild-template.endpoints-params.json:13:20
     '{ "name": "icon", "type":{ "base":"char", "dec":"*" }, "comment":"base64 128x128 image for the guild icon", "inject_if_not": null}' */
  char *icon; /**< base64 128x128 image for the guild icon */

};
extern void discord_create_guild_from_guild_template_params_cleanup_v(void *p);
extern void discord_create_guild_from_guild_template_params_cleanup(struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_init_v(void *p);
extern void discord_create_guild_from_guild_template_params_init(struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_from_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params **pp);
extern size_t discord_create_guild_from_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_from_guild_template_params *p);
extern void discord_create_guild_from_guild_template_params_list_free_v(void **p);
extern void discord_create_guild_from_guild_template_params_list_free(struct discord_create_guild_from_guild_template_params **p);
extern void discord_create_guild_from_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_from_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_from_guild_template_params ***p);
extern size_t discord_create_guild_from_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_from_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_from_guild_template_params **p);

/* Create Guild Template */
/* defined at specs/discord/guild-template.endpoints-params.json:19:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_template_params_init(struct discord_create_guild_template_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_template_params_cleanup(struct discord_create_guild_template_params *)`
 *     * :code:`void discord_create_guild_template_params_list_free(struct discord_create_guild_template_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_template_params_from_json(char *rbuf, size_t len, struct discord_create_guild_template_params **)`
 *     * :code:`void discord_create_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_template_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_template_params_to_json(char *wbuf, size_t len, struct discord_create_guild_template_params *)`
 *     * :code:`void discord_create_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_template_params **)`
 * @endverbatim
 */
struct discord_create_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:22:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild"}' */
  char *name; /**< name of the guild */

  /* specs/discord/guild-template.endpoints-params.json:23:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
  char *description; /**< description for the template (0-120) chars */

};
extern void discord_create_guild_template_params_cleanup_v(void *p);
extern void discord_create_guild_template_params_cleanup(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_init_v(void *p);
extern void discord_create_guild_template_params_init(struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_template_params_from_json(char *json, size_t len, struct discord_create_guild_template_params **pp);
extern size_t discord_create_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_template_params_to_json(char *json, size_t len, struct discord_create_guild_template_params *p);
extern void discord_create_guild_template_params_list_free_v(void **p);
extern void discord_create_guild_template_params_list_free(struct discord_create_guild_template_params **p);
extern void discord_create_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_template_params_list_from_json(char *str, size_t len, struct discord_create_guild_template_params ***p);
extern size_t discord_create_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_template_params_list_to_json(char *str, size_t len, struct discord_create_guild_template_params **p);

/* Modify Guild Template */
/* defined at specs/discord/guild-template.endpoints-params.json:29:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_template_params_init(struct discord_modify_guild_template_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params *)`
 *     * :code:`void discord_modify_guild_template_params_list_free(struct discord_modify_guild_template_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_template_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_template_params **)`
 *     * :code:`void discord_modify_guild_template_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_template_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_template_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_template_params *)`
 *     * :code:`void discord_modify_guild_template_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_template_params **)`
 * @endverbatim
 */
struct discord_modify_guild_template_params {
  /* specs/discord/guild-template.endpoints-params.json:32:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}, "comment":"name of the guild", "inject_if_not": null}' */
  char *name; /**< name of the guild */

  /* specs/discord/guild-template.endpoints-params.json:33:20
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }, "comment":"description for the template (0-120) chars", "inject_if_not": null}' */
  char *description; /**< description for the template (0-120) chars */

};
extern void discord_modify_guild_template_params_cleanup_v(void *p);
extern void discord_modify_guild_template_params_cleanup(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_init_v(void *p);
extern void discord_modify_guild_template_params_init(struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_template_params_from_json(char *json, size_t len, struct discord_modify_guild_template_params **pp);
extern size_t discord_modify_guild_template_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_template_params_to_json(char *json, size_t len, struct discord_modify_guild_template_params *p);
extern void discord_modify_guild_template_params_list_free_v(void **p);
extern void discord_modify_guild_template_params_list_free(struct discord_modify_guild_template_params **p);
extern void discord_modify_guild_template_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_template_params_list_from_json(char *str, size_t len, struct discord_modify_guild_template_params ***p);
extern size_t discord_modify_guild_template_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_template_params_list_to_json(char *str, size_t len, struct discord_modify_guild_template_params **p);
