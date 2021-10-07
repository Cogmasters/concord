/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/audit_log.endpoints-params.h
 * @see https://discord.com/developers/docs/resources/audit-log
 */


/* defined at specs/discord/audit_log.endpoints-params.json:7:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void discord_get_guild_audit_log_params_init(struct discord_get_guild_audit_log_params *)`
 *   * Cleanup:

 *     * :code:`void discord_get_guild_audit_log_params_cleanup(struct discord_get_guild_audit_log_params *)`
 *     * :code:`void discord_get_guild_audit_log_params_list_free(struct discord_get_guild_audit_log_params **)`
 *   * JSON Decoder:

 *     * :code:`void discord_get_guild_audit_log_params_from_json(char *rbuf, size_t len, struct discord_get_guild_audit_log_params **)`
 *     * :code:`void discord_get_guild_audit_log_params_list_from_json(char *rbuf, size_t len, struct discord_get_guild_audit_log_params ***)`
 *   * JSON Encoder:

 *     * :code:`void discord_get_guild_audit_log_params_to_json(char *wbuf, size_t len, struct discord_get_guild_audit_log_params *)`
 *     * :code:`void discord_get_guild_audit_log_params_list_to_json(char *wbuf, size_t len, struct discord_get_guild_audit_log_params **)`
 * @endverbatim
 */
struct discord_get_guild_audit_log_params {
  /* specs/discord/audit_log.endpoints-params.json:10:20
     '{ "name": "user_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"filter the log for actions made by a user", "inject_if_not":0 }' */
  u64_snowflake_t user_id; /**< filter the log for actions made by a user */

  /* specs/discord/audit_log.endpoints-params.json:11:20
     '{ "name": "action_type", "type":{ "base":"int", "int_alias":"enum discord_audit_log_events" }, "comment":"the type of audit log event", "inject_if_not":0 }' */
  enum discord_audit_log_events action_type; /**< the type of audit log event */

  /* specs/discord/audit_log.endpoints-params.json:12:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"filter the log before a certain entry id", "inject_if_not":0 }' */
  u64_snowflake_t before; /**< filter the log before a certain entry id */

  /* specs/discord/audit_log.endpoints-params.json:13:20
     '{ "name": "limit", "type":{ "base":"int" }, "default_value":50, "comment":"how many entries are returned (default 50, minimum 1, maximum 100)", "inject_if_not":0 }' */
  int limit; /**< how many entries are returned (default 50, minimum 1, maximum 100) */

};
extern void discord_get_guild_audit_log_params_cleanup_v(void *p);
extern void discord_get_guild_audit_log_params_cleanup(struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_init_v(void *p);
extern void discord_get_guild_audit_log_params_init(struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_from_json_v(char *json, size_t len, void *pp);
extern void discord_get_guild_audit_log_params_from_json(char *json, size_t len, struct discord_get_guild_audit_log_params **pp);
extern size_t discord_get_guild_audit_log_params_to_json_v(char *json, size_t len, void *p);
extern size_t discord_get_guild_audit_log_params_to_json(char *json, size_t len, struct discord_get_guild_audit_log_params *p);
extern void discord_get_guild_audit_log_params_list_free_v(void **p);
extern void discord_get_guild_audit_log_params_list_free(struct discord_get_guild_audit_log_params **p);
extern void discord_get_guild_audit_log_params_list_from_json_v(char *str, size_t len, void *p);
extern void discord_get_guild_audit_log_params_list_from_json(char *str, size_t len, struct discord_get_guild_audit_log_params ***p);
extern size_t discord_get_guild_audit_log_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_get_guild_audit_log_params_list_to_json(char *str, size_t len, struct discord_get_guild_audit_log_params **p);
