/* This file is generated from specs/discord/sticker.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/sticker.endpoints-params.h
 * @see (null)
 */


/* List Nitro Sticker Packs */
/* defined at specs/discord/sticker.endpoints-params.json:8:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_list_nitro_sticker_packs_response_init(struct discord_list_nitro_sticker_packs_response *)`
 *   * Cleanup:

 *     * :code:`void discord_list_nitro_sticker_packs_response_cleanup(struct discord_list_nitro_sticker_packs_response *)`
 *     * :code:`void discord_list_nitro_sticker_packs_response_list_free(struct discord_list_nitro_sticker_packs_response **)`
 *   * JSON Decoder:

 *     * :code:`void discord_list_nitro_sticker_packs_response_from_json(char *rbuf, size_t len, struct discord_list_nitro_sticker_packs_response **)`
 *     * :code:`void discord_list_nitro_sticker_packs_response_list_from_json(char *rbuf, size_t len, struct discord_list_nitro_sticker_packs_response ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_list_nitro_sticker_packs_response_to_json(char *wbuf, size_t len, struct discord_list_nitro_sticker_packs_response *)`
 *     * :code:`void discord_list_nitro_sticker_packs_response_list_to_json(char *wbuf, size_t len, struct discord_list_nitro_sticker_packs_response **)`
 * @endverbatim
 */
struct discord_list_nitro_sticker_packs_response {
  /* specs/discord/sticker.endpoints-params.json:11:18
     '{"name":"sticker_packs", "type":{"base":"struct discord_sticker_pack", "dec":"ntl"}, "comment":"array of sticker pack objects"}' */
  struct discord_sticker_pack **sticker_packs; /**< array of sticker pack objects */

};
extern void discord_list_nitro_sticker_packs_response_cleanup_v(void *p);
extern void discord_list_nitro_sticker_packs_response_cleanup(struct discord_list_nitro_sticker_packs_response *p);
extern void discord_list_nitro_sticker_packs_response_init_v(void *p);
extern void discord_list_nitro_sticker_packs_response_init(struct discord_list_nitro_sticker_packs_response *p);
extern void discord_list_nitro_sticker_packs_response_from_json_v(char *json, size_t len, void *pp);
extern void discord_list_nitro_sticker_packs_response_from_json(char *json, size_t len, struct discord_list_nitro_sticker_packs_response **pp);
extern size_t discord_list_nitro_sticker_packs_response_to_json_v(char *json, size_t len, void *p);
extern size_t discord_list_nitro_sticker_packs_response_to_json(char *json, size_t len, struct discord_list_nitro_sticker_packs_response *p);
extern void discord_list_nitro_sticker_packs_response_list_free_v(void **p);
extern void discord_list_nitro_sticker_packs_response_list_free(struct discord_list_nitro_sticker_packs_response **p);
extern void discord_list_nitro_sticker_packs_response_list_from_json_v(char *str, size_t len, void *p);
extern void discord_list_nitro_sticker_packs_response_list_from_json(char *str, size_t len, struct discord_list_nitro_sticker_packs_response ***p);
extern size_t discord_list_nitro_sticker_packs_response_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_list_nitro_sticker_packs_response_list_to_json(char *str, size_t len, struct discord_list_nitro_sticker_packs_response **p);

/* Create Guild Sticker */
/* defined at specs/discord/sticker.endpoints-params.json:17:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_guild_sticker_params_init(struct discord_create_guild_sticker_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_guild_sticker_params_cleanup(struct discord_create_guild_sticker_params *)`
 *     * :code:`void discord_create_guild_sticker_params_list_free(struct discord_create_guild_sticker_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_guild_sticker_params_from_json(char *rbuf, size_t len, struct discord_create_guild_sticker_params **)`
 *     * :code:`void discord_create_guild_sticker_params_list_from_json(char *rbuf, size_t len, struct discord_create_guild_sticker_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_guild_sticker_params_to_json(char *wbuf, size_t len, struct discord_create_guild_sticker_params *)`
 *     * :code:`void discord_create_guild_sticker_params_list_to_json(char *wbuf, size_t len, struct discord_create_guild_sticker_params **)`
 * @endverbatim
 */
struct discord_create_guild_sticker_params {
  /* specs/discord/sticker.endpoints-params.json:20:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
  char *name; /**< name of the sticker (2-30 characters) */

  /* specs/discord/sticker.endpoints-params.json:21:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
  char *description; /**< description of the sticker (empty or 2-100 characters) */

  /* specs/discord/sticker.endpoints-params.json:22:18
     '{"name":"file", "type":{ "base":"struct discord_attachment", "dec":"*" }, "loc":"multipart", "comment":"the sticker file to upload, must be a PNG, APNG, or Lottie JSON file, max 500 KB"}' */
  struct discord_attachment *file; /**< the sticker file to upload, must be a PNG, APNG, or Lottie JSON file, max 500 KB */

  /* specs/discord/sticker.endpoints-params.json:23:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  char *tags; /**< autocomplete/suggestion tags for the sticker (max 200 characters) */

};
extern void discord_create_guild_sticker_params_cleanup_v(void *p);
extern void discord_create_guild_sticker_params_cleanup(struct discord_create_guild_sticker_params *p);
extern void discord_create_guild_sticker_params_init_v(void *p);
extern void discord_create_guild_sticker_params_init(struct discord_create_guild_sticker_params *p);
extern void discord_create_guild_sticker_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_guild_sticker_params_from_json(char *json, size_t len, struct discord_create_guild_sticker_params **pp);
extern size_t discord_create_guild_sticker_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_guild_sticker_params_to_json(char *json, size_t len, struct discord_create_guild_sticker_params *p);
extern void discord_create_guild_sticker_params_list_free_v(void **p);
extern void discord_create_guild_sticker_params_list_free(struct discord_create_guild_sticker_params **p);
extern void discord_create_guild_sticker_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_guild_sticker_params_list_from_json(char *str, size_t len, struct discord_create_guild_sticker_params ***p);
extern size_t discord_create_guild_sticker_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_guild_sticker_params_list_to_json(char *str, size_t len, struct discord_create_guild_sticker_params **p);

/* Modify Guild Sticker */
/* defined at specs/discord/sticker.endpoints-params.json:29:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_guild_sticker_params_init(struct discord_modify_guild_sticker_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_guild_sticker_params_cleanup(struct discord_modify_guild_sticker_params *)`
 *     * :code:`void discord_modify_guild_sticker_params_list_free(struct discord_modify_guild_sticker_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_guild_sticker_params_from_json(char *rbuf, size_t len, struct discord_modify_guild_sticker_params **)`
 *     * :code:`void discord_modify_guild_sticker_params_list_from_json(char *rbuf, size_t len, struct discord_modify_guild_sticker_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_guild_sticker_params_to_json(char *wbuf, size_t len, struct discord_modify_guild_sticker_params *)`
 *     * :code:`void discord_modify_guild_sticker_params_list_to_json(char *wbuf, size_t len, struct discord_modify_guild_sticker_params **)`
 * @endverbatim
 */
struct discord_modify_guild_sticker_params {
  /* specs/discord/sticker.endpoints-params.json:32:18
     '{"name":"name", "type":{"base":"char", "dec":"*"}, "comment":"name of the sticker (2-30 characters)"}' */
  char *name; /**< name of the sticker (2-30 characters) */

  /* specs/discord/sticker.endpoints-params.json:33:18
     '{"name":"description", "type":{"base":"char", "dec":"*"}, "comment":"description of the sticker (empty or 2-100 characters)"}' */
  char *description; /**< description of the sticker (empty or 2-100 characters) */

  /* specs/discord/sticker.endpoints-params.json:34:18
     '{"name":"tags", "type":{"base":"char", "dec":"*"}, "comment":"autocomplete/suggestion tags for the sticker (max 200 characters)"}' */
  char *tags; /**< autocomplete/suggestion tags for the sticker (max 200 characters) */

};
extern void discord_modify_guild_sticker_params_cleanup_v(void *p);
extern void discord_modify_guild_sticker_params_cleanup(struct discord_modify_guild_sticker_params *p);
extern void discord_modify_guild_sticker_params_init_v(void *p);
extern void discord_modify_guild_sticker_params_init(struct discord_modify_guild_sticker_params *p);
extern void discord_modify_guild_sticker_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_guild_sticker_params_from_json(char *json, size_t len, struct discord_modify_guild_sticker_params **pp);
extern size_t discord_modify_guild_sticker_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_guild_sticker_params_to_json(char *json, size_t len, struct discord_modify_guild_sticker_params *p);
extern void discord_modify_guild_sticker_params_list_free_v(void **p);
extern void discord_modify_guild_sticker_params_list_free(struct discord_modify_guild_sticker_params **p);
extern void discord_modify_guild_sticker_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_guild_sticker_params_list_from_json(char *str, size_t len, struct discord_modify_guild_sticker_params ***p);
extern size_t discord_modify_guild_sticker_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_guild_sticker_params_list_to_json(char *str, size_t len, struct discord_modify_guild_sticker_params **p);
