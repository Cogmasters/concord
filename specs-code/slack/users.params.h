/* This file is generated from slack/users.params.json, Please don't edit it. */
/**
 * @file specs-code/slack/users.params.h
 * @see https://api.slack.com/methods?filter=users
 */


/* Users Info */
/* defined at slack/users.params.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void slack_users_info_params_init(struct slack_users_info_params *)`
 *   * Cleanup:

 *     * :code:`void slack_users_info_params_cleanup(struct slack_users_info_params *)`
 *     * :code:`void slack_users_info_params_list_free(struct slack_users_info_params **)`
 *   * JSON Decoder:

 *     * :code:`void slack_users_info_params_from_json(char *rbuf, size_t len, struct slack_users_info_params *)`
 *     * :code:`void slack_users_info_params_list_from_json(char *rbuf, size_t len, struct slack_users_info_params ***)`
 *   * JSON Encoder:

 *     * :code:`void slack_users_info_params_to_json(char *wbuf, size_t len, struct slack_users_info_params *)`
 *     * :code:`void slack_users_info_params_list_to_json(char *wbuf, size_t len, struct slack_users_info_params **)`
 * @endverbatim
 */
struct slack_users_info_params {
  /* slack/users.params.json:12:20
     '{ "name": "token", "type":{ "base":"char", "dec":"*" }, "comment":"Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter.", "inject_if_not":null }' */
  char *token; /**< Authentication token bearing required scopes. Tokens should be passed as an HTTP Authorization header or alternatively, as a POST parameter. */

  /* slack/users.params.json:13:20
     '{ "name": "user", "type":{ "base":"char", "dec":"*" }, "comment":"User to get info onUser to get info on", "inject_if_not":null }' */
  char *user; /**< User to get info onUser to get info on */

  /* slack/users.params.json:14:20
     '{ "name": "include_locale", "type":{ "base":"bool" }, "comment":"Set this to true to receive the locale for this user. Defaults to false", "inject_if_not":false }' */
  bool include_locale; /**< Set this to true to receive the locale for this user. Defaults to false */

};
extern void slack_users_info_params_cleanup_v(void *p);
extern void slack_users_info_params_cleanup(struct slack_users_info_params *p);
extern void slack_users_info_params_init_v(void *p);
extern void slack_users_info_params_init(struct slack_users_info_params *p);
extern void slack_users_info_params_from_json_v(char *json, size_t len, void *p);
extern void slack_users_info_params_from_json_p(char *json, size_t len, struct slack_users_info_params **pp);
extern void slack_users_info_params_from_json(char *json, size_t len, struct slack_users_info_params *p);
extern size_t slack_users_info_params_to_json_v(char *json, size_t len, void *p);
extern size_t slack_users_info_params_to_json(char *json, size_t len, struct slack_users_info_params *p);
extern void slack_users_info_params_list_free_v(void **p);
extern void slack_users_info_params_list_free(struct slack_users_info_params **p);
extern void slack_users_info_params_list_from_json_v(char *str, size_t len, void *p);
extern void slack_users_info_params_list_from_json(char *str, size_t len, struct slack_users_info_params ***p);
extern size_t slack_users_info_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t slack_users_info_params_list_to_json(char *str, size_t len, struct slack_users_info_params **p);
