/* This file is generated from specs/github/gist.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/github/one-specs.h
 * @see https://docs.github.com/en/rest/reference/gists
 */


/* defined at specs/github/gist.endpoints-params.json:10:32 */
/**
 * @brief Gist Create
 *
 * @see https://docs.github.com/en/rest/reference/gists#create-a-gist--parameters
 */
struct github_gist_create_params;
/* This file is generated from specs/github/gist.json, Please don't edit it. */

/* defined at specs/github/gist.json:9:33 */
/**
 * @brief Gist Structure
 *
 */
struct github_gist;
/* This file is generated from specs/github/repository.json, Please don't edit it. */

/* defined at specs/github/repository.json:9:33 */
/**
 * @brief Topic Structure
 *
 */
struct github_topic;
/* This file is generated from specs/github/user.json, Please don't edit it. */

/* defined at specs/github/user.json:9:33 */
/**
 * @brief User Structure
 *
 */
struct github_user;
/* This file is generated from specs/github/gist.endpoints-params.json, Please don't edit it. */
/* This file is generated from specs/github/gist.json, Please don't edit it. */
/* This file is generated from specs/github/repository.json, Please don't edit it. */
/* This file is generated from specs/github/user.json, Please don't edit it. */
/* This file is generated from specs/github/gist.endpoints-params.json, Please don't edit it. */

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
/* This file is generated from specs/github/gist.json, Please don't edit it. */

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
/* This file is generated from specs/github/repository.json, Please don't edit it. */

/* Topic Structure */
/* defined at specs/github/repository.json:9:33 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void github_topic_init(struct github_topic *)`
 *   * Cleanup:

 *     * :code:`void github_topic_cleanup(struct github_topic *)`
 *     * :code:`void github_topic_list_free(struct github_topic **)`
 *   * JSON Decoder:

 *     * :code:`void github_topic_from_json(char *rbuf, size_t len, struct github_topic **)`
 *     * :code:`void github_topic_list_from_json(char *rbuf, size_t len, struct github_topic ***)`
 *   * JSON Encoder:

 *     * :code:`void github_topic_to_json(char *wbuf, size_t len, struct github_topic *)`
 *     * :code:`void github_topic_list_to_json(char *wbuf, size_t len, struct github_topic **)`
 * @endverbatim
 */
struct github_topic {
  /* specs/github/repository.json:12:28
     '{ "name": "names", "type":{ "base":"ja_str", "dec":"ntl"}}' */
  ja_str **names;

};
/* This file is generated from specs/github/user.json, Please don't edit it. */

/* User Structure */
/* defined at specs/github/user.json:9:33 */
/**
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * Initializer:

 *     * :code:`void github_user_init(struct github_user *)`
 *   * Cleanup:

 *     * :code:`void github_user_cleanup(struct github_user *)`
 *     * :code:`void github_user_list_free(struct github_user **)`
 *   * JSON Decoder:

 *     * :code:`void github_user_from_json(char *rbuf, size_t len, struct github_user **)`
 *     * :code:`void github_user_list_from_json(char *rbuf, size_t len, struct github_user ***)`
 *   * JSON Encoder:

 *     * :code:`void github_user_to_json(char *wbuf, size_t len, struct github_user *)`
 *     * :code:`void github_user_list_to_json(char *wbuf, size_t len, struct github_user **)`
 * @endverbatim
 */
struct github_user {
  /* specs/github/user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
  char *login;

  /* specs/github/user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  int id;

  /* specs/github/user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  char *node_id;

  /* specs/github/user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
  char *avatar_url;

  /* specs/github/user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
  char *gravatar_id;

  /* specs/github/user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  char *html_url;

  /* specs/github/user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  char *type;

  /* specs/github/user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
  bool site_admin;

  /* specs/github/user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/github/user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
  char *company;

  /* specs/github/user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
  char *blog;

  /* specs/github/user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
  char *location;

  /* specs/github/user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
  char *email;

  /* specs/github/user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
  char *hireable;

  /* specs/github/user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
  char *bio;

  /* specs/github/user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
  int public_repos;

  /* specs/github/user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
  int public_gists;

  /* specs/github/user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
  int followers;

  /* specs/github/user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
  int following;

  /* specs/github/user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  char *created_at;

  /* specs/github/user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  char *updated_at;

};
/* This file is generated from specs/github/gist.endpoints-params.json, Please don't edit it. */

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
/* This file is generated from specs/github/gist.json, Please don't edit it. */

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
/* This file is generated from specs/github/repository.json, Please don't edit it. */

extern void github_topic_cleanup_v(void *p);
extern void github_topic_cleanup(struct github_topic *p);
extern void github_topic_init_v(void *p);
extern void github_topic_init(struct github_topic *p);
extern void github_topic_from_json_v(char *json, size_t len, void *pp);
extern void github_topic_from_json(char *json, size_t len, struct github_topic **pp);
extern size_t github_topic_to_json_v(char *json, size_t len, void *p);
extern size_t github_topic_to_json(char *json, size_t len, struct github_topic *p);
extern void github_topic_list_free_v(void **p);
extern void github_topic_list_free(struct github_topic **p);
extern void github_topic_list_from_json_v(char *str, size_t len, void *p);
extern void github_topic_list_from_json(char *str, size_t len, struct github_topic ***p);
extern size_t github_topic_list_to_json_v(char *str, size_t len, void *p);
extern size_t github_topic_list_to_json(char *str, size_t len, struct github_topic **p);
/* This file is generated from specs/github/user.json, Please don't edit it. */

extern void github_user_cleanup_v(void *p);
extern void github_user_cleanup(struct github_user *p);
extern void github_user_init_v(void *p);
extern void github_user_init(struct github_user *p);
extern void github_user_from_json_v(char *json, size_t len, void *pp);
extern void github_user_from_json(char *json, size_t len, struct github_user **pp);
extern size_t github_user_to_json_v(char *json, size_t len, void *p);
extern size_t github_user_to_json(char *json, size_t len, struct github_user *p);
extern void github_user_list_free_v(void **p);
extern void github_user_list_free(struct github_user **p);
extern void github_user_list_from_json_v(char *str, size_t len, void *p);
extern void github_user_list_from_json(char *str, size_t len, struct github_user ***p);
extern size_t github_user_list_to_json_v(char *str, size_t len, void *p);
extern size_t github_user_list_to_json(char *str, size_t len, struct github_user **p);
