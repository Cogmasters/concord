/* This file is generated from specs/reddit/links_n_comments.json, Please don't edit it. */
/**
 * @file specs-code/reddit/all_functions.h
 * @see 
 */


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
/* This file is generated from specs/reddit/oauth2.json, Please don't edit it. */
/**
 * @file specs-code/reddit/all_functions.h
 * @see https://github.com/reddit-archive/reddit/wiki/OAuth2-Quick-Start-Example
 */


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
/* This file is generated from specs/reddit/search.json, Please don't edit it. */
/**
 * @file specs-code/reddit/all_functions.h
 * @see 
 */


extern void reddit_search_params_cleanup_v(void *p);
extern void reddit_search_params_cleanup(struct reddit_search_params *p);
extern void reddit_search_params_init_v(void *p);
extern void reddit_search_params_init(struct reddit_search_params *p);
extern void reddit_search_params_from_json_v(char *json, size_t len, void *pp);
extern void reddit_search_params_from_json(char *json, size_t len, struct reddit_search_params **pp);
extern size_t reddit_search_params_to_json_v(char *json, size_t len, void *p);
extern size_t reddit_search_params_to_json(char *json, size_t len, struct reddit_search_params *p);
extern size_t reddit_search_params_to_query_v(char *json, size_t len, void *p);
extern size_t reddit_search_params_to_query(char *json, size_t len, struct reddit_search_params *p);
extern void reddit_search_params_list_free_v(void **p);
extern void reddit_search_params_list_free(struct reddit_search_params **p);
extern void reddit_search_params_list_from_json_v(char *str, size_t len, void *p);
extern void reddit_search_params_list_from_json(char *str, size_t len, struct reddit_search_params ***p);
extern size_t reddit_search_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t reddit_search_params_list_to_json(char *str, size_t len, struct reddit_search_params **p);
