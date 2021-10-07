/* This file is generated from specs/reddit/links_n_comments.json, Please don't edit it. */
/**
 * @file specs-code/reddit/links_n_comments.h
 * @see 
 */


/* Comment */
/* defined at specs/reddit/links_n_comments.json:10:22 */
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

 *     * :code:`void reddit_comment_params_from_json(char *rbuf, size_t len, struct reddit_comment_params **)`
 *     * :code:`void reddit_comment_params_list_from_json(char *rbuf, size_t len, struct reddit_comment_params ***)`
 *   * JSON Encoder:

 *     * :code:`void reddit_comment_params_to_json(char *wbuf, size_t len, struct reddit_comment_params *)`
 *     * :code:`void reddit_comment_params_list_to_json(char *wbuf, size_t len, struct reddit_comment_params **)`
 * @endverbatim
 */
struct reddit_comment_params {
  /* specs/reddit/links_n_comments.json:13:20
     '{ "name": "api_type", "type":{ "base":"char", "dec":"*" }, "comment":"the string json" }' */
  char *api_type; /**< the string json */

  /* specs/reddit/links_n_comments.json:14:20
     '{ "name": "return_rtjson", "type":{ "base":"bool" }, "comment":"boolean value" }' */
  bool return_rtjson; /**< boolean value */

  /* specs/reddit/links_n_comments.json:15:20
     '{ "name": "richtext_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON data" }' */
  char *richtext_json; /**< JSON data */

  /* specs/reddit/links_n_comments.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"raw markdown text" }' */
  char *text; /**< raw markdown text */

  /* specs/reddit/links_n_comments.json:17:20
     '{ "name": "thing_id", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of parent thing" }' */
  char *thing_id; /**< fullname of parent thing */

  /* specs/reddit/links_n_comments.json:18:20
     '{ "name": "uh", "type":{ "base":"char", "dec":"*" }, "comment":"a modhash" }' */
  char *uh; /**< a modhash */

};
extern void reddit_comment_params_cleanup_v(void *p);
extern void reddit_comment_params_cleanup(struct reddit_comment_params *p);
extern void reddit_comment_params_init_v(void *p);
extern void reddit_comment_params_init(struct reddit_comment_params *p);
extern void reddit_comment_params_from_json_v(char *json, size_t len, void *pp);
extern void reddit_comment_params_from_json(char *json, size_t len, struct reddit_comment_params **pp);
extern size_t reddit_comment_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_comment_params_to_json(char *json, size_t len, struct reddit_comment_params *p);
extern void reddit_comment_params_list_free_v(void **p);
extern void reddit_comment_params_list_free(struct reddit_comment_params **p);
extern void reddit_comment_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_comment_params_list_from_json(char *str, size_t len, struct reddit_comment_params ***p);
extern size_t reddit_comment_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_comment_params_list_to_json(char *str, size_t len, struct reddit_comment_params **p);
