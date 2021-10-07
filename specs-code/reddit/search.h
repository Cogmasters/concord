/* This file is generated from specs/reddit/search.json, Please don't edit it. */
/**
 * @file specs-code/reddit/search.h
 * @see 
 */


/* Search */
/* defined at specs/reddit/search.json:10:22 */
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

 *     * :code:`void reddit_search_params_from_json(char *rbuf, size_t len, struct reddit_search_params **)`
 *     * :code:`void reddit_search_params_list_from_json(char *rbuf, size_t len, struct reddit_search_params ***)`
 *   * JSON Encoder:

 *     * :code:`void reddit_search_params_to_json(char *wbuf, size_t len, struct reddit_search_params *)`
 *     * :code:`void reddit_search_params_list_to_json(char *wbuf, size_t len, struct reddit_search_params **)`
 * @endverbatim
 */
struct reddit_search_params {
  /* specs/reddit/search.json:13:20
     '{ "name": "after", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  char *after; /**< fullname of a thing */

  /* specs/reddit/search.json:14:20
     '{ "name": "before", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of a thing"}' */
  char *before; /**< fullname of a thing */

  /* specs/reddit/search.json:15:20
     '{ "name": "category", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 5 character"}' */
  char *category; /**< a string no longer than 5 character */

  /* specs/reddit/search.json:16:20
     '{ "name": "count", "type":{ "base":"int" }, "comment":"a positive integer (default: 0)"}' */
  int count; /**< a positive integer (default: 0) */

  /* specs/reddit/search.json:17:20
     '{ "name": "include_facets", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  bool include_facets; /**< boolean value */

  /* specs/reddit/search.json:18:20
     '{ "name": "limit", "type":{ "base":"int" }, "comment":"the maximum number of items desired (default: 25, maximum: 100)"}' */
  int limit; /**< the maximum number of items desired (default: 25, maximum: 100) */

  /* specs/reddit/search.json:19:20
     '{ "name": "q", "type":{ "base":"char", "dec":"*" }, "comment":"a string no longer than 512 characters"}' */
  char *q; /**< a string no longer than 512 characters */

  /* specs/reddit/search.json:20:20
     '{ "name": "restrict_sr", "type":{ "base":"bool" }, "comment":"boolean value"}' */
  bool restrict_sr; /**< boolean value */

  /* specs/reddit/search.json:21:20
     '{ "name": "show", "type":{ "base":"char", "dec":"*" }, "comment":"(optional)the string all"}' */
  char *show; /**< (optional)the string all */

  /* specs/reddit/search.json:22:20
     '{ "name": "sort", "type":{ "base":"char", "dec":"*" }, "comment":"one of(relevance, hot, top, new, comments)"}' */
  char *sort; /**< one of(relevance, hot, top, new, comments) */

  /* specs/reddit/search.json:23:20
     '{ "name": "sr_detail", "type":{ "base":"char", "dec":"*" }, "comment":"expand subreddits"}' */
  char *sr_detail; /**< expand subreddits */

  /* specs/reddit/search.json:24:20
     '{ "name": "t", "type":{ "base":"char", "dec":"*" }, "comment":"one of(hour, day, week, month, year, all)"}' */
  char *t; /**< one of(hour, day, week, month, year, all) */

  /* specs/reddit/search.json:25:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"(optional) comma-delimited list of result types (sr, link, user)"}' */
  char *type; /**< (optional) comma-delimited list of result types (sr, link, user) */

};
extern void reddit_search_params_cleanup_v(void *p);
extern void reddit_search_params_cleanup(struct reddit_search_params *p);
extern void reddit_search_params_init_v(void *p);
extern void reddit_search_params_init(struct reddit_search_params *p);
extern void reddit_search_params_from_json_v(char *json, size_t len, void *pp);
extern void reddit_search_params_from_json(char *json, size_t len, struct reddit_search_params **pp);
extern size_t reddit_search_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_search_params_to_json(char *json, size_t len, struct reddit_search_params *p);
extern void reddit_search_params_list_free_v(void **p);
extern void reddit_search_params_list_free(struct reddit_search_params **p);
extern void reddit_search_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_search_params_list_from_json(char *str, size_t len, struct reddit_search_params ***p);
extern size_t reddit_search_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_search_params_list_to_json(char *str, size_t len, struct reddit_search_params **p);
