/* This file is generated from specs/reddit/links_n_comments.json, Please don't edit it. */
/**
 * @file specs-code/reddit/links_n_comments.h
 * @see 
 */


// Comment
// defined at specs/reddit/links_n_comments.json:10:22
/**
 * @see https://www.reddit.com/dev/api/#POST_api_comment

 * - Initializer:
 *   - <tt>reddit_comment_params_init(struct reddit_comment_params*)</tt>
 * - Cleanup:
 *   - <tt>reddit_comment_params_cleanup(struct reddit_comment_params*)</tt>
 *   - <tt>reddit_comment_params_list_free(struct reddit_comment_params**)</tt>
 * - JSON Decoder:
 *   - <tt>reddit_comment_params_from_json(char *rbuf, size_t len, struct reddit_comment_params**)</tt>
 *   - <tt>reddit_comment_params_list_from_json(char *rbuf, size_t len, struct reddit_comment_params***)</tt>
 * - JSON Encoder:
 *   - <tt>reddit_comment_params_to_json(char *wbuf, size_t len, struct reddit_comment_params *p)</tt>
 *   - <tt>reddit_comment_params_list_to_json(char *wbuf, size_t len, struct reddit_comment_params**)</tt>
 */
struct reddit_comment_params {
  /* specs/reddit/links_n_comments.json:13:20
     '{ "name": "api_type", "type":{ "base":"char", "dec":"*" }, "comment":"the string json" }' */
  char *api_type; ///< the string json

  /* specs/reddit/links_n_comments.json:14:20
     '{ "name": "return_rtjson", "type":{ "base":"bool" }, "comment":"boolean value" }' */
  bool return_rtjson; ///< boolean value

  /* specs/reddit/links_n_comments.json:15:20
     '{ "name": "richtext_json", "type":{ "base":"char", "dec":"*" }, "comment":"JSON data" }' */
  char *richtext_json; ///< JSON data

  /* specs/reddit/links_n_comments.json:16:20
     '{ "name": "text", "type":{ "base":"char", "dec":"*" }, "comment":"raw markdown text" }' */
  char *text; ///< raw markdown text

  /* specs/reddit/links_n_comments.json:17:20
     '{ "name": "thing_id", "type":{ "base":"char", "dec":"*" }, "comment":"fullname of parent thing" }' */
  char *thing_id; ///< fullname of parent thing

  /* specs/reddit/links_n_comments.json:18:20
     '{ "name": "uh", "type":{ "base":"char", "dec":"*" }, "comment":"a modhash" }' */
  char *uh; ///< a modhash

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[6];
    void *record_defined[6];
    void *record_null[6];
  } __M; // metadata
/// @endcond
};
extern void reddit_comment_params_cleanup_v(void *p);
extern void reddit_comment_params_cleanup(struct reddit_comment_params *p);
extern void reddit_comment_params_init_v(void *p);
extern void reddit_comment_params_init(struct reddit_comment_params *p);
extern void reddit_comment_params_from_json_v(char *json, size_t len, void *pp);
extern void reddit_comment_params_from_json(char *json, size_t len, struct reddit_comment_params **pp);
extern size_t reddit_comment_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_comment_params_to_json(char *json, size_t len, struct reddit_comment_params *p);
extern size_t reddit_comment_params_to_query_v(char *json, size_t len, void *p);
extern size_t reddit_comment_params_to_query(char *json, size_t len, struct reddit_comment_params *p);
extern void reddit_comment_params_list_free_v(void **p);
extern void reddit_comment_params_list_free(struct reddit_comment_params **p);
extern void reddit_comment_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_comment_params_list_from_json(char *str, size_t len, struct reddit_comment_params ***p);
extern size_t reddit_comment_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_comment_params_list_to_json(char *str, size_t len, struct reddit_comment_params **p);
