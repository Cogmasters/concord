/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/emoji.endpoints-params.h
 * @see 
 */


/* Create Guild Emoji */
/* defined at specs/discord/emoji.endpoints-params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_emoji_params_init(struct discord_create_guild_emoji_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_emoji_params_cleanup(struct discord_create_guild_emoji_params *)`
 *     * :code:`void discord_create_guild_emoji_params_list_free(struct discord_create_guild_emoji_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_emoji_params_from_json(char *rbuf, size_t len, struct discord_create_guild_emoji_params **)`
 *     * :code:`void discord_create_guild_emoji_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_emoji_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_emoji_params_to_json(char *wbuf, size_t len, struct discord_create_guild_emoji_params *)`
 *     * :code:`void discord_create_guild_emoji_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_emoji_params **)`
 * @endverbatim
 */
struct discord_create_guild_emoji_params {
  /* specs/discord/emoji.endpoints-params.json:12:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/emoji.endpoints-params.json:13:20
     '{ "name": "image", "type":{ "base":"char", "dec":"*"}, "comment":"Base64 Encoded Image Data"}' */
  char *image; /**< Base64 Encoded Image Data */

  /* specs/discord/emoji.endpoints-params.json:14:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  ja_u64 **roles; /**< roles for which this emoji will be whitelisted */

};
extern void discord_create_guild_emoji_params_cleanup_v(void *p);
extern void discord_create_guild_emoji_params_cleanup(struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_init_v(void *p);
extern void discord_create_guild_emoji_params_init(struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_emoji_params_from_json(char *json, size_t len, struct discord_create_guild_emoji_params **pp);
extern size_t discord_create_guild_emoji_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_emoji_params_to_json(char *json, size_t len, struct discord_create_guild_emoji_params *p);
extern void discord_create_guild_emoji_params_list_free_v(void **p);
extern void discord_create_guild_emoji_params_list_free(struct discord_create_guild_emoji_params **p);
extern void discord_create_guild_emoji_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_emoji_params_list_from_json(char *str, size_t len, struct discord_create_guild_emoji_params ***p);
extern size_t discord_create_guild_emoji_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_emoji_params_list_to_json(char *str, size_t len, struct discord_create_guild_emoji_params **p);

/* Modify Guild Emoji */
/* defined at specs/discord/emoji.endpoints-params.json:20:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_emoji_params_init(struct discord_modify_guild_emoji_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_emoji_params_cleanup(struct discord_modify_guild_emoji_params *)`
 *     * :code:`void discord_modify_guild_emoji_params_list_free(struct discord_modify_guild_emoji_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_emoji_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_emoji_params **)`
 *     * :code:`void discord_modify_guild_emoji_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_emoji_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_emoji_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_emoji_params *)`
 *     * :code:`void discord_modify_guild_emoji_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_emoji_params **)`
 * @endverbatim
 */
struct discord_modify_guild_emoji_params {
  /* specs/discord/emoji.endpoints-params.json:23:20
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/discord/emoji.endpoints-params.json:24:20
     '{ "name": "roles", "type":{ "base":"ja_u64", "dec":"ntl" }, "comment":"roles for which this emoji will be whitelisted"}' */
  ja_u64 **roles; /**< roles for which this emoji will be whitelisted */

};
extern void discord_modify_guild_emoji_params_cleanup_v(void *p);
extern void discord_modify_guild_emoji_params_cleanup(struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_init_v(void *p);
extern void discord_modify_guild_emoji_params_init(struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_emoji_params_from_json(char *json, size_t len, struct discord_modify_guild_emoji_params **pp);
extern size_t discord_modify_guild_emoji_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_emoji_params_to_json(char *json, size_t len, struct discord_modify_guild_emoji_params *p);
extern void discord_modify_guild_emoji_params_list_free_v(void **p);
extern void discord_modify_guild_emoji_params_list_free(struct discord_modify_guild_emoji_params **p);
extern void discord_modify_guild_emoji_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_emoji_params_list_from_json(char *str, size_t len, struct discord_modify_guild_emoji_params ***p);
extern size_t discord_modify_guild_emoji_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_emoji_params_list_to_json(char *str, size_t len, struct discord_modify_guild_emoji_params **p);
