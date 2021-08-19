/* This file is generated from specs/github/github-license.json, Please don't edit it. */
/**
 * @file specs-code/github/all_functions.h
 * @see https://docs.github.com/en/rest/reference/repos#get-a-repository
 */


extern void github_license_cleanup_v(void *p);
extern void github_license_cleanup(struct github_license *p);
extern void github_license_init_v(void *p);
extern void github_license_init(struct github_license *p);
extern void github_license_from_json_v(char *json, size_t len, void *pp);
extern void github_license_from_json(char *json, size_t len, struct github_license **pp);
extern size_t github_license_to_json_v(char *json, size_t len, void *p);
extern size_t github_license_to_json(char *json, size_t len, struct github_license *p);
extern size_t github_license_to_query_v(char *json, size_t len, void *p);
extern size_t github_license_to_query(char *json, size_t len, struct github_license *p);
extern void github_license_list_free_v(void **p);
extern void github_license_list_free(struct github_license **p);
extern void github_license_list_from_json_v(char *str, size_t len, void *p);
extern void github_license_list_from_json(char *str, size_t len, struct github_license ***p);
extern size_t github_license_list_to_json_v(char *str, size_t len, void *p);
extern size_t github_license_list_to_json(char *str, size_t len, struct github_license **p);
/* This file is generated from specs/github/github-repository.json, Please don't edit it. */
/**
 * @file specs-code/github/all_functions.h
 * @see https://docs.github.com/en/rest/reference/repos#get-a-repository
 */


extern void github_repository_cleanup_v(void *p);
extern void github_repository_cleanup(struct github_repository *p);
extern void github_repository_init_v(void *p);
extern void github_repository_init(struct github_repository *p);
extern void github_repository_from_json_v(char *json, size_t len, void *pp);
extern void github_repository_from_json(char *json, size_t len, struct github_repository **pp);
extern size_t github_repository_to_json_v(char *json, size_t len, void *p);
extern size_t github_repository_to_json(char *json, size_t len, struct github_repository *p);
extern size_t github_repository_to_query_v(char *json, size_t len, void *p);
extern size_t github_repository_to_query(char *json, size_t len, struct github_repository *p);
extern void github_repository_list_free_v(void **p);
extern void github_repository_list_free(struct github_repository **p);
extern void github_repository_list_from_json_v(char *str, size_t len, void *p);
extern void github_repository_list_from_json(char *str, size_t len, struct github_repository ***p);
extern size_t github_repository_list_to_json_v(char *str, size_t len, void *p);
extern size_t github_repository_list_to_json(char *str, size_t len, struct github_repository **p);
/* This file is generated from specs/github/github-user.json, Please don't edit it. */
/**
 * @file specs-code/github/all_functions.h
 * @see https://docs.github.com/en/rest/reference/users#get-a-user
 */


extern void github_user_cleanup_v(void *p);
extern void github_user_cleanup(struct github_user *p);
extern void github_user_init_v(void *p);
extern void github_user_init(struct github_user *p);
extern void github_user_from_json_v(char *json, size_t len, void *pp);
extern void github_user_from_json(char *json, size_t len, struct github_user **pp);
extern size_t github_user_to_json_v(char *json, size_t len, void *p);
extern size_t github_user_to_json(char *json, size_t len, struct github_user *p);
extern size_t github_user_to_query_v(char *json, size_t len, void *p);
extern size_t github_user_to_query(char *json, size_t len, struct github_user *p);
extern void github_user_list_free_v(void **p);
extern void github_user_list_free(struct github_user **p);
extern void github_user_list_from_json_v(char *str, size_t len, void *p);
extern void github_user_list_from_json(char *str, size_t len, struct github_user ***p);
extern size_t github_user_list_to_json_v(char *str, size_t len, void *p);
extern size_t github_user_list_to_json(char *str, size_t len, struct github_user **p);
