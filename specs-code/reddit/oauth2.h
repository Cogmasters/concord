/* This file is generated from specs/reddit/oauth2.json, Please don't edit it. */
/**
 * @file specs-code/reddit/oauth2.h
 * @see https://github.com/reddit-archive/reddit/wiki/OAuth2-Quick-Start-Example
 */


// Access Token
// defined at specs/reddit/oauth2.json:9:22
/**
 * - Initializer:
 *   - <tt> void reddit_access_token_params_init(struct reddit_access_token_params *) </tt>
 * - Cleanup:
 *   - <tt> void reddit_access_token_params_cleanup(struct reddit_access_token_params *) </tt>
 *   - <tt> void reddit_access_token_params_list_free(struct reddit_access_token_params **) </tt>
 * - JSON Decoder:
 *   - <tt> void reddit_access_token_params_from_json(char *rbuf, size_t len, struct reddit_access_token_params **) </tt>
 *   - <tt> void reddit_access_token_params_list_from_json(char *rbuf, size_t len, struct reddit_access_token_params ***) </tt>
 * - JSON Encoder:
 *   - <tt> void reddit_access_token_params_to_json(char *wbuf, size_t len, struct reddit_access_token_params *) </tt>
 *   - <tt> void reddit_access_token_params_list_to_json(char *wbuf, size_t len, struct reddit_access_token_params **) </tt>
 */
struct reddit_access_token_params {
  /* specs/reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
  char *grant_type; ///< 'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps

  /* specs/reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
  char *username; ///< username for script app

  /* specs/reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
  char *password; ///< password for script app

  /* specs/reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
  char *code; ///< the code retrieved by the webapp

  /* specs/reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
  char *redirect_uri; ///< redirect uri for webapp

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[5];
    void *record_defined[5];
    void *record_null[5];
  } __M; // metadata
/// @endcond
};
extern void reddit_access_token_params_cleanup_v(void *p);
extern void reddit_access_token_params_cleanup(struct reddit_access_token_params *p);
extern void reddit_access_token_params_init_v(void *p);
extern void reddit_access_token_params_init(struct reddit_access_token_params *p);
extern void reddit_access_token_params_from_json_v(char *json, size_t len, void *pp);
extern void reddit_access_token_params_from_json(char *json, size_t len, struct reddit_access_token_params **pp);
extern size_t reddit_access_token_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_access_token_params_to_json(char *json, size_t len, struct reddit_access_token_params *p);
extern size_t reddit_access_token_params_to_query_v(char *json, size_t len, void *p);
extern size_t reddit_access_token_params_to_query(char *json, size_t len, struct reddit_access_token_params *p);
extern void reddit_access_token_params_list_free_v(void **p);
extern void reddit_access_token_params_list_free(struct reddit_access_token_params **p);
extern void reddit_access_token_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_access_token_params_list_from_json(char *str, size_t len, struct reddit_access_token_params ***p);
extern size_t reddit_access_token_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_access_token_params_list_to_json(char *str, size_t len, struct reddit_access_token_params **p);
