/* This file is generated from specs/discord/stage-instance.json, Please don't edit it. */
/**
 * @file specs-code/discord/stage-instance.h
 * @see (null)
 */



/* Privacy Level */
/* defined at specs/discord/stage-instance.json:5:5 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_stage_instance_privacy_level_print(enum discord_stage_instance_privacy_level code)`
 *   * :code:`enum discord_stage_instance_privacy_level discord_stage_instance_privacy_level_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_stage_instance_privacy_level {
  DISCORD_STAGE_INSTANCE_PUBLIC = 1, /**< The Stage instance is visible publicly, such as on Stage Discovery. */
  DISCORD_STAGE_INSTANCE_GUILD_ONLY = 2, /**< The Stage instance is visible to only guild members. */
};
extern char* discord_stage_instance_privacy_level_print(enum discord_stage_instance_privacy_level);
extern enum discord_stage_instance_privacy_level discord_stage_instance_privacy_level_eval(char*);
extern void discord_stage_instance_privacy_level_list_free_v(void **p);
extern void discord_stage_instance_privacy_level_list_free(enum discord_stage_instance_privacy_level **p);
extern void discord_stage_instance_privacy_level_list_from_json_v(char *str, size_t len, void *p);
extern void discord_stage_instance_privacy_level_list_from_json(char *str, size_t len, enum discord_stage_instance_privacy_level ***p);
extern size_t discord_stage_instance_privacy_level_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_stage_instance_privacy_level_list_to_json(char *str, size_t len, enum discord_stage_instance_privacy_level **p);

/* Stage Instance Structure */
/* defined at specs/discord/stage-instance.json:17:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_stage_instance_init(struct discord_stage_instance *)`
 *   * Cleanup:

 *     * :code:`void discord_stage_instance_cleanup(struct discord_stage_instance *)`
 *     * :code:`void discord_stage_instance_list_free(struct discord_stage_instance **)`
 *   * JSON Decoder:

 *     * :code:`void discord_stage_instance_from_json(char *rbuf, size_t len, struct discord_stage_instance **)`
 *     * :code:`void discord_stage_instance_list_from_json(char *rbuf, size_t len, struct discord_stage_instance ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_stage_instance_to_json(char *wbuf, size_t len, struct discord_stage_instance *)`
 *     * :code:`void discord_stage_instance_list_to_json(char *wbuf, size_t len, struct discord_stage_instance **)`
 * @endverbatim
 */
struct discord_stage_instance {
  /* specs/discord/stage-instance.json:20:18
     '{"name":"id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of this Stage instance"}' */
  u64_snowflake_t id; /**< The id of this Stage instance */

  /* specs/discord/stage-instance.json:21:18
     '{"name":"guild_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The guild id of the associated Stage channel"}' */
  u64_snowflake_t guild_id; /**< The guild id of the associated Stage channel */

  /* specs/discord/stage-instance.json:22:18
     '{"name":"channel_id", "type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"The id of the associated Stage channel"}' */
  u64_snowflake_t channel_id; /**< The id of the associated Stage channel */

  /* specs/discord/stage-instance.json:23:18
     '{"name":"topic", "type":{"base":"char", "dec":"*"}, "comment":"The topic of the Stage instance (1-120 characters)"}' */
  char *topic; /**< The topic of the Stage instance (1-120 characters) */

  /* specs/discord/stage-instance.json:24:18
     '{"name":"privacy_level", "type":{"base":"int", "int_alias":"enum discord_stage_instance_privacy_level"}, "comment":"The privacy level of the Stage instance"}' */
  enum discord_stage_instance_privacy_level privacy_level; /**< The privacy level of the Stage instance */

  /* specs/discord/stage-instance.json:25:18
     '{"name":"discoverable_disabled", "type":{"base":"bool", "comment":"Whether or not Stage Discovery is disabled"}}' */
  bool discoverable_disabled;

};
extern void discord_stage_instance_cleanup_v(void *p);
extern void discord_stage_instance_cleanup(struct discord_stage_instance *p);
extern void discord_stage_instance_init_v(void *p);
extern void discord_stage_instance_init(struct discord_stage_instance *p);
extern void discord_stage_instance_from_json_v(char *json, size_t len, void *pp);
extern void discord_stage_instance_from_json(char *json, size_t len, struct discord_stage_instance **pp);
extern size_t discord_stage_instance_to_json_v(char *json, size_t len, void *p);
extern size_t discord_stage_instance_to_json(char *json, size_t len, struct discord_stage_instance *p);
extern void discord_stage_instance_list_free_v(void **p);
extern void discord_stage_instance_list_free(struct discord_stage_instance **p);
extern void discord_stage_instance_list_from_json_v(char *str, size_t len, void *p);
extern void discord_stage_instance_list_from_json(char *str, size_t len, struct discord_stage_instance ***p);
extern size_t discord_stage_instance_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_stage_instance_list_to_json(char *str, size_t len, struct discord_stage_instance **p);
