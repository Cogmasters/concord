/* This file is generated from specs/github/gist.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/github/gist.endpoints-params.h
 * @see https://docs.github.com/en/rest/reference/gists
 */


/* Gist Create */
/* defined at specs/github/gist.endpoints-params.json:10:32 */
/**
 * @see https://docs.github.com/en/rest/reference/gists#create-a-gist--parameters
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void github_gist_create_params_init(struct github_gist_create_params *)`
 *   * Cleanup:

 *     * :code:`void github_gist_create_params_cleanup(struct github_gist_create_params *)`
 *     * :code:`void github_gist_create_params_list_free(struct github_gist_create_params **)`
 *   * JSON Decoder:

 *     * :code:`void github_gist_create_params_from_json(char *rbuf, size_t len, struct github_gist_create_params **)`
 *     * :code:`void github_gist_create_params_list_from_json(char *rbuf, size_t len, struct github_gist_create_params ***)`
 *   * JSON Encoder:

 *     * :code:`void github_gist_create_params_to_json(char *wbuf, size_t len, struct github_gist_create_params *)`
 *     * :code:`void github_gist_create_params_list_to_json(char *wbuf, size_t len, struct github_gist_create_params **)`
 * @endverbatim
 */
struct github_gist_create_params {
  /* specs/github/gist.endpoints-params.json:13:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*" }}' */
  char *description;

  /* specs/github/gist.endpoints-params.json:14:28
     '{ "name": "title", "type":{ "base":"char", "dec":"*" }}' */
  char *title;

  /* specs/github/gist.endpoints-params.json:15:28
     '{ "name": "contents", "type":{ "base":"char", "dec":"*" }}' */
  char *contents;

  /* specs/github/gist.endpoints-params.json:16:28
     '{ "name": "public", "type":{ "base":"char", "dec":"*" }}' */
  char *public;

};
extern void github_gist_create_params_cleanup_v(void *p);
extern void github_gist_create_params_cleanup(struct github_gist_create_params *p);
extern void github_gist_create_params_init_v(void *p);
extern void github_gist_create_params_init(struct github_gist_create_params *p);
extern void github_gist_create_params_from_json_v(char *json, size_t len, void *pp);
extern void github_gist_create_params_from_json(char *json, size_t len, struct github_gist_create_params **pp);
extern size_t github_gist_create_params_to_json_v(char *json, size_t len, void *p);
extern size_t github_gist_create_params_to_json(char *json, size_t len, struct github_gist_create_params *p);
extern void github_gist_create_params_list_free_v(void **p);
extern void github_gist_create_params_list_free(struct github_gist_create_params **p);
extern void github_gist_create_params_list_from_json_v(char *str, size_t len, void *p);
extern void github_gist_create_params_list_from_json(char *str, size_t len, struct github_gist_create_params ***p);
extern size_t github_gist_create_params_list_to_json_v(char *str, size_t len, void *p);
extern size_t github_gist_create_params_list_to_json(char *str, size_t len, struct github_gist_create_params **p);
