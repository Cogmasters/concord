/* This file is generated from specs/discord/stage-instance.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/stage-instance.endpoints-params.h
 * @see (null)
 */


/* Create Stage Instance */
/* defined at specs/discord/stage-instance.endpoints-params.json:8:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_create_stage_instance_params_init(struct discord_create_stage_instance_params *)`
 *   * Cleanup:

 *     * :code:`void discord_create_stage_instance_params_cleanup(struct discord_create_stage_instance_params *)`
 *     * :code:`void discord_create_stage_instance_params_list_free(struct discord_create_stage_instance_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_create_stage_instance_params_from_json(char *rbuf, size_t len, struct discord_create_stage_instance_params **)`
 *     * :code:`void discord_create_stage_instance_params_list_from_json(char *rbuf, size_t len, struct discord_create_stage_instance_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_create_stage_instance_params_to_json(char *wbuf, size_t len, struct discord_create_stage_instance_params *)`
 *     * :code:`void discord_create_stage_instance_params_list_to_json(char *wbuf, size_t len, struct discord_create_stage_instance_params **)`
 * @endverbatim
 */
struct discord_create_stage_instance_params {
  /* specs/discord/stage-instance.endpoints-params.json:11:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the Stage channel"}' */
  u64_snowflake_t channel_id; /**< The id of the Stage channel */

  /* specs/discord/stage-instance.endpoints-params.json:12:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  char *topic; /**< The topic of the Stage instance (1-120 characters) */

  /* specs/discord/stage-instance.endpoints-params.json:13:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
  enum discord_stage_instance_privacy_level privacy_level;

};
extern void discord_create_stage_instance_params_cleanup_v(void *p);
extern void discord_create_stage_instance_params_cleanup(struct discord_create_stage_instance_params *p);
extern void discord_create_stage_instance_params_init_v(void *p);
extern void discord_create_stage_instance_params_init(struct discord_create_stage_instance_params *p);
extern void discord_create_stage_instance_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_create_stage_instance_params_from_json(char *json, size_t len, struct discord_create_stage_instance_params **pp);
extern size_t discord_create_stage_instance_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_create_stage_instance_params_to_json(char *json, size_t len, struct discord_create_stage_instance_params *p);
extern void discord_create_stage_instance_params_list_free_v(void **p);
extern void discord_create_stage_instance_params_list_free(struct discord_create_stage_instance_params **p);
extern void discord_create_stage_instance_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_create_stage_instance_params_list_from_json(char *str, size_t len, struct discord_create_stage_instance_params ***p);
extern size_t discord_create_stage_instance_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_create_stage_instance_params_list_to_json(char *str, size_t len, struct discord_create_stage_instance_params **p);

/* Modify Stage Instance */
/* defined at specs/discord/stage-instance.endpoints-params.json:19:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_modify_stage_instance_params_init(struct discord_modify_stage_instance_params *)`
 *   * Cleanup:

 *     * :code:`void discord_modify_stage_instance_params_cleanup(struct discord_modify_stage_instance_params *)`
 *     * :code:`void discord_modify_stage_instance_params_list_free(struct discord_modify_stage_instance_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_modify_stage_instance_params_from_json(char *rbuf, size_t len, struct discord_modify_stage_instance_params **)`
 *     * :code:`void discord_modify_stage_instance_params_list_from_json(char *rbuf, size_t len, struct discord_modify_stage_instance_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_modify_stage_instance_params_to_json(char *wbuf, size_t len, struct discord_modify_stage_instance_params *)`
 *     * :code:`void discord_modify_stage_instance_params_list_to_json(char *wbuf, size_t len, struct discord_modify_stage_instance_params **)`
 * @endverbatim
 */
struct discord_modify_stage_instance_params {
  /* specs/discord/stage-instance.endpoints-params.json:22:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  char *topic; /**< The topic of the Stage instance (1-120 characters) */

  /* specs/discord/stage-instance.endpoints-params.json:23:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level", "comment":"The privacy level of the Stage instance (default GUILD_ONLY)"}, "inject_if_not":0}' */
  enum discord_stage_instance_privacy_level privacy_level;

};
extern void discord_modify_stage_instance_params_cleanup_v(void *p);
extern void discord_modify_stage_instance_params_cleanup(struct discord_modify_stage_instance_params *p);
extern void discord_modify_stage_instance_params_init_v(void *p);
extern void discord_modify_stage_instance_params_init(struct discord_modify_stage_instance_params *p);
extern void discord_modify_stage_instance_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_modify_stage_instance_params_from_json(char *json, size_t len, struct discord_modify_stage_instance_params **pp);
extern size_t discord_modify_stage_instance_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_modify_stage_instance_params_to_json(char *json, size_t len, struct discord_modify_stage_instance_params *p);
extern void discord_modify_stage_instance_params_list_free_v(void **p);
extern void discord_modify_stage_instance_params_list_free(struct discord_modify_stage_instance_params **p);
extern void discord_modify_stage_instance_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_modify_stage_instance_params_list_from_json(char *str, size_t len, struct discord_modify_stage_instance_params ***p);
extern size_t discord_modify_stage_instance_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_modify_stage_instance_params_list_to_json(char *str, size_t len, struct discord_modify_stage_instance_params **p);
