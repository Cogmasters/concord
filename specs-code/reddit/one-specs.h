/* This file is generated from reddit/links_n_comments.json, Please don't edit it. */
/**
 * @file specs-code/reddit/one-specs.h
 * @see 
 */


/* defined at reddit/links_n_comments.json:10:22 */
/**
 * @brief Comment
 *
 * @see https://www.reddit.com/dev/api/#POST_api_comment
 */
struct reddit_comment_params;
/* This file is generated from reddit/oauth2.json, Please don't edit it. */

/* defined at reddit/oauth2.json:9:22 */
/**
 * @brief Access Token
 *
 */
struct reddit_access_token_params;
/* This file is generated from reddit/search.json, Please don't edit it. */

/* defined at reddit/search.json:10:22 */
/**
 * @brief Search
 *
 * @see https://www.reddit.com/dev/api/#GET_search
 */
struct reddit_search_params;
/* This file is generated from reddit/links_n_comments.json, Please don't edit it. */
/* This file is generated from reddit/oauth2.json, Please don't edit it. */
/* This file is generated from reddit/search.json, Please don't edit it. */
/* This file is generated from reddit/links_n_comments.json, Please don't edit it. */

/* Comment */
/* defined at reddit/links_n_comments.json:10:22 */
/**
 * @see https://www.reddit.com/dev/api/#POST_api_comment
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void reddit_comment_params_init(struct reddit_comment_params *)`
 *   * Cleanup:

 *     * :code:`void reddit_comment_params_cleanup(struct reddit_comment_params *)`
 *     * :code:`void reddit_comment_params_list_free(struct reddit_comment_params **)`
 *   * JSON Decoder:

 *     * :code:`void reddit_comment_params_from_json(char *rbuf, size_t len, struct reddit_comment_params *)`
 *     * :code:`void reddit_comment_params_list_from_json(char *rbuf, size_t len, struct reddit_comment_params ***)`
 *   * JSON Encoder:

 *     * :code:`void reddit_comment_params_to_json(char *wbuf, size_t len, struct reddit_comment_params *)`
 *     * :code:`void reddit_comment_params_list_to_json(char *wbuf, size_t len, struct reddit_comment_params **)`
 * @endverbatim
 */
struct reddit_comment_params {
  /* reddit/links_n_comments.json:13:20
     '{ "name": "api_type", "type":{ "base":"char", "dec":"*" }, "comment":"the string json" }' */
  char *api_type; /**< the string json */

  /* reddit/links_n_comments.json:14:20
     '{ "name": "return_rtjson", "type":{ "base":"bool" }, "comment":"boolean value" }' */
  bool return_rtjson; /**< boolean value */

  /* reddit/links_n_comments.json:15:20
     '{ "name": "richtext_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON data" }' */
  char *richtext_json; /**< JSON data */

  /* reddit/links_n_comments.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"raw markdown text" }' */
  char *text; /**< raw markdown text */

  /* reddit/links_n_comments.json:17:20
     '{ "name": "thing_id", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of parent thing" }' */
  char *thing_id; /**< fullname of parent thing */

  /* reddit/links_n_comments.json:18:20
     '{ "name": "uh", "type":{ "base":"char", "dec":"*" }, "comment":"a modhash" }' */
  char *uh; /**< a modhash */

};
/* This file is generated from reddit/oauth2.json, Please don't edit it. */

/* Access Token */
/* defined at reddit/oauth2.json:9:22 */
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

 *     * :code:`void reddit_access_token_params_from_json(char *rbuf, size_t len, struct reddit_access_token_params *)`
 *     * :code:`void reddit_access_token_params_list_from_json(char *rbuf, size_t len, struct reddit_access_token_params ***)`
 *   * JSON Encoder:

 *     * :code:`void reddit_access_token_params_to_json(char *wbuf, size_t len, struct reddit_access_token_params *)`
 *     * :code:`void reddit_access_token_params_list_to_json(char *wbuf, size_t len, struct reddit_access_token_params **)`
 * @endverbatim
 */
struct reddit_access_token_params {
  /* reddit/oauth2.json:12:20
     '{ "name": "grant_type", "type":{ "base":"char", "dec":"*" }, "comment":"'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps"}' */
  char *grant_type; /**< 'password' for script type apps, 'refresh_token' for renewing access token and 'authorization_code' for webapps */

  /* reddit/oauth2.json:13:20
     '{ "name": "username", "type":{ "base":"char", "dec":"*" }, "comment":"username for script app"}' */
  char *username; /**< username for script app */

  /* reddit/oauth2.json:14:20
     '{ "name": "password", "type":{ "base":"char", "dec":"*" }, "comment":"password for script app"}' */
  char *password; /**< password for script app */

  /* reddit/oauth2.json:15:20
     '{ "name": "code", "type":{ "base":"char", "dec":"*" }, "comment":"the code retrieved by the webapp"}' */
  char *code; /**< the code retrieved by the webapp */

  /* reddit/oauth2.json:16:20
     '{ "name": "redirect_uri", "type":{ "base":"char", "dec":"*" }, "comment":"redirect uri for webapp"}' */
  char *redirect_uri; /**< redirect uri for webapp */

};
/* This file is generated from reddit/search.json, Please don't edit it. */

/* Search */
/* defined at reddit/search.json:10:22 */
/**
 * @see https://www.reddit.com/dev/api/#GET_search
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void reddit_search_params_init(struct reddit_search_params *)`
 *   * Cleanup:

 *     * :code:`void reddit_search_params_cleanup(struct reddit_search_params *)`
 *     * :code:`void reddit_search_params_list_free(struct reddit_search_params **)`
 *   * JSON Decoder:

 *     * :code:`void reddit_search_params_from_json(char *rbuf, size_t len, struct reddit_search_params *)`
 *     * :code:`void reddit_search_params_list_from_json(char *rbuf, size_t len, struct reddit_search_params ***)`
 *   * JSON Encoder:

 *     * :code:`void reddit_search_params_to_json(char *wbuf, size_t len, struct reddit_search_params *)`
 *     * :code:`void reddit_search_params_list_to_json(char *wbuf, size_t len, struct reddit_search_params **)`
 * @endverbatim
 */
struct reddit_search_params {
  /* reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  char *after; /**< fullname of a thing */

  /* reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  char *before; /**< fullname of a thing */

  /* reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
  char *category; /**< a string no longer than 5 character */

  /* reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
  int count; /**< a positive integer (default: 0) */

  /* reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  bool include_facets; /**< boolean value */

  /* reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
  int limit; /**< the maximum number of items desired (default: 25, maximum: 100) */

  /* reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
  char *q; /**< a string no longer than 512 characters */

  /* reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  bool restrict_sr; /**< boolean value */

  /* reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
  char *show; /**< (optional)the string all */

  /* reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
  char *sort; /**< one of(relevance, hot, top, new, comments) */

  /* reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
  char *sr_detail; /**< expand subreddits */

  /* reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
  char *t; /**< one of(hour, day, week, month, year, all) */

  /* reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
  char *type; /**< (optional) comma-delimited list of result types (sr, link, user) */

};
/* This file is generated from reddit/links_n_comments.json, Please don't edit it. */

extern void reddit_comment_params_cleanup_v(void *p);
extern void reddit_comment_params_cleanup(struct reddit_comment_params *p);
extern void reddit_comment_params_init_v(void *p);
extern void reddit_comment_params_init(struct reddit_comment_params *p);
extern void reddit_comment_params_from_json_v(char *json, size_t len, void *p);
extern void reddit_comment_params_from_json_p(char *json, size_t len, struct reddit_comment_params **pp);
extern void reddit_comment_params_from_json(char *json, size_t len, struct reddit_comment_params *p);
extern size_t reddit_comment_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_comment_params_to_json(char *json, size_t len, struct reddit_comment_params *p);
extern void reddit_comment_params_list_free_v(void **p);
extern void reddit_comment_params_list_free(struct reddit_comment_params **p);
extern void reddit_comment_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_comment_params_list_from_json(char *str, size_t len, struct reddit_comment_params ***p);
extern size_t reddit_comment_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_comment_params_list_to_json(char *str, size_t len, struct reddit_comment_params **p);
/* This file is generated from reddit/oauth2.json, Please don't edit it. */

extern void reddit_access_token_params_cleanup_v(void *p);
extern void reddit_access_token_params_cleanup(struct reddit_access_token_params *p);
extern void reddit_access_token_params_init_v(void *p);
extern void reddit_access_token_params_init(struct reddit_access_token_params *p);
extern void reddit_access_token_params_from_json_v(char *json, size_t len, void *p);
extern void reddit_access_token_params_from_json_p(char *json, size_t len, struct reddit_access_token_params **pp);
extern void reddit_access_token_params_from_json(char *json, size_t len, struct reddit_access_token_params *p);
extern size_t reddit_access_token_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_access_token_params_to_json(char *json, size_t len, struct reddit_access_token_params *p);
extern void reddit_access_token_params_list_free_v(void **p);
extern void reddit_access_token_params_list_free(struct reddit_access_token_params **p);
extern void reddit_access_token_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_access_token_params_list_from_json(char *str, size_t len, struct reddit_access_token_params ***p);
extern size_t reddit_access_token_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_access_token_params_list_to_json(char *str, size_t len, struct reddit_access_token_params **p);
/* This file is generated from reddit/search.json, Please don't edit it. */

extern void reddit_search_params_cleanup_v(void *p);
extern void reddit_search_params_cleanup(struct reddit_search_params *p);
extern void reddit_search_params_init_v(void *p);
extern void reddit_search_params_init(struct reddit_search_params *p);
extern void reddit_search_params_from_json_v(char *json, size_t len, void *p);
extern void reddit_search_params_from_json_p(char *json, size_t len, struct reddit_search_params **pp);
extern void reddit_search_params_from_json(char *json, size_t len, struct reddit_search_params *p);
extern size_t reddit_search_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_search_params_to_json(char *json, size_t len, struct reddit_search_params *p);
extern void reddit_search_params_list_free_v(void **p);
extern void reddit_search_params_list_free(struct reddit_search_params **p);
extern void reddit_search_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_search_params_list_from_json(char *str, size_t len, struct reddit_search_params ***p);
extern size_t reddit_search_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_search_params_list_to_json(char *str, size_t len, struct reddit_search_params **p);
