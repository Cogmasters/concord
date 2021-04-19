/* This file is generated from specs/reddit/search.json, Please don't edit it. */
/*

*/

extern void reddit_search_params_cleanup_v(void *p);
extern void reddit_search_params_cleanup(struct reddit_search_params *p);
extern void reddit_search_params_init_v(void *p);
extern void reddit_search_params_init(struct reddit_search_params *p);
extern struct reddit_search_params * reddit_search_params_alloc();
extern void reddit_search_params_free_v(void *p);
extern void reddit_search_params_free(struct reddit_search_params *p);
extern void reddit_search_params_from_json_v(char *json, size_t len, void *p);
extern void reddit_search_params_from_json(char *json, size_t len, struct reddit_search_params *p);
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
