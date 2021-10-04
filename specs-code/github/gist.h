/* This file is generated from specs/github/gist.json, Please don't edit it. */
/**
 * @file specs-code/github/gist.h
 * @see https://docs.github.com/en/rest/reference/gists#create-a-gist
 */


/* Gist Structure */
/* defined at specs/github/gist.json:9:33 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void github_gist_init(struct github_gist *)`
 *   * Cleanup:

 *     * :code:`void github_gist_cleanup(struct github_gist *)`
 *     * :code:`void github_gist_list_free(struct github_gist **)`
 *   * JSON Decoder:

 *     * :code:`void github_gist_from_json(char *rbuf, size_t len, struct github_gist **)`
 *     * :code:`void github_gist_list_from_json(char *rbuf, size_t len, struct github_gist ***)`
 *   * JSON Encoder:

 *     * :code:`void github_gist_to_json(char *wbuf, size_t len, struct github_gist *)`
 *     * :code:`void github_gist_list_to_json(char *wbuf, size_t len, struct github_gist **)`
 * @endverbatim
 */
struct github_gist {
  /* specs/github/gist.json:12:28
     '{ "name": "url", "type":{ "base":"char", "dec":"*"}}' */
  char *url;

  /* specs/github/gist.json:13:28
     '{ "name": "id", "type":{ "base":"char", "dec":"*"}}' */
  char *id;

  /* specs/github/gist.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  char *node_id;

  /* specs/github/gist.json:15:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  char *html_url;

  /* specs/github/gist.json:16:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  char *created_at;

  /* specs/github/gist.json:17:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  char *updated_at;

  /* specs/github/gist.json:18:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
  char *description;

  /* specs/github/gist.json:19:28
     '{ "name": "comments", "type":{ "base":"int"}}' */
  int comments;

};
extern void github_gist_cleanup_v(void *p);
extern void github_gist_cleanup(struct github_gist *p);
extern void github_gist_init_v(void *p);
extern void github_gist_init(struct github_gist *p);
extern void github_gist_from_json_v(char *json, size_t len, void *pp);
extern void github_gist_from_json(char *json, size_t len, struct github_gist **pp);
extern size_t github_gist_to_json_v(char *json, size_t len, void *p);
extern size_t github_gist_to_json(char *json, size_t len, struct github_gist *p);
extern void github_gist_list_free_v(void **p);
extern void github_gist_list_free(struct github_gist **p);
extern void github_gist_list_from_json_v(char *str, size_t len, void *p);
extern void github_gist_list_from_json(char *str, size_t len, struct github_gist ***p);
extern size_t github_gist_list_to_json_v(char *str, size_t len, void *p);
extern size_t github_gist_list_to_json(char *str, size_t len, struct github_gist **p);
