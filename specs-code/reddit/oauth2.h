/* This file is generated from specs/reddit/oauth2.json, Please don't edit it. */
/**
 * @file specs-code/reddit/oauth2.h
 * @see https://github.com/reddit-archive/reddit/wiki/OAuth2-Quick-Start-Example
 */


/* Access Token */
/* defined at specs/reddit/oauth2.json:9:22 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void reddit_access_token_params_init(struct reddit_access_token_params *)`
 *   * Cleanup:

 *     * :code:`void reddit_access_token_params_cleanup(struct reddit_access_token_params *)`
 *     * :code:`void reddit_access_token_params_list_free(struct reddit_access_token_params **)`
 *   * JSON Decoder:

 *     * :code:`void reddit_access_token_params_from_json(char *rbuf, size_t len, struct reddit_access_token_params **)`
 *     * :code:`void reddit_access_token_params_list_from_json(char *rbuf, size_t len, struct reddit_access_token_params ***)`
 *   * JSON Encoder:

 *     * :code:`void reddit_access_token_params_to_json(char *wbuf, size_t len, struct reddit_access_token_params *)`
 *     * :code:`void reddit_access_token_params_list_to_json(char *wbuf, size_t len, struct reddit_access_token_params **)`
 * @endverbatim
 */
struct reddit_access_token_params {
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
  char *grant_type; /**< 'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps */

  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
  char *username; /**< username for script app */

  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
  char *password; /**< password for script app */

  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
  char *code; /**< the code retrieved by the webapp */

  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
  char *redirect_uri; /**< redirect uri for webapp */

};
extern void reddit_access_token_params_cleanup_v(void *p);
extern void reddit_access_token_params_cleanup(struct reddit_access_token_params *p);
extern void reddit_access_token_params_init_v(void *p);
extern void reddit_access_token_params_init(struct reddit_access_token_params *p);
extern void reddit_access_token_params_from_json_v(char *json, size_t len, void *pp);
extern void reddit_access_token_params_from_json(char *json, size_t len, struct reddit_access_token_params **pp);
extern size_t reddit_access_token_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_access_token_params_to_json(char *json, size_t len, struct reddit_access_token_params *p);
extern void reddit_access_token_params_list_free_v(void **p);
extern void reddit_access_token_params_list_free(struct reddit_access_token_params **p);
extern void reddit_access_token_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_access_token_params_list_from_json(char *str, size_t len, struct reddit_access_token_params ***p);
extern size_t reddit_access_token_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_access_token_params_list_to_json(char *str, size_t len, struct reddit_access_token_params **p);
