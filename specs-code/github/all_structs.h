/* This file is generated from specs/github/github-license.json, Please don't edit it. */
/**
 * @file specs-code/github/all_structs.h
 * @see https://docs.github.com/en/rest/reference/repos#get-a-repository
 */


// License Structure
// defined at specs/github/github-license.json:9:33
/**
 * - Initializer:
 *   - <tt> github_license_init(struct github_license *) </tt>
 * - Cleanup:
 *   - <tt> github_license_cleanup(struct github_license *) </tt>
 *   - <tt> github_license_list_free(struct github_license **) </tt>
 * - JSON Decoder:
 *   - <tt> github_license_from_json(char *rbuf, size_t len, struct github_license **) </tt>
 *   - <tt> github_license_list_from_json(char *rbuf, size_t len, struct github_license ***) </tt>
 * - JSON Encoder:
 *   - <tt> github_license_to_json(char *wbuf, size_t len, struct github_license *) </tt>
 *   - <tt> github_license_list_to_json(char *wbuf, size_t len, struct github_license **) </tt>
 */
struct github_license {
  /* specs/github/github-license.json:12:28
     '{ "name": "key", "type":{ "base":"char", "dec":"*"}}' */
  char *key;

  /* specs/github/github-license.json:13:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/github/github-license.json:14:28
     '{ "name": "spdx_id", "type":{ "base":"char", "dec":"*"}}' */
  char *spdx_id;

  /* specs/github/github-license.json:15:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  char *node_id;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[4];
    void *record_defined[4];
    void *record_null[4];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/github/github-repository.json, Please don't edit it. */
/**
 * @file specs-code/github/all_structs.h
 * @see https://docs.github.com/en/rest/reference/repos#get-a-repository
 */


// Repository Structure
// defined at specs/github/github-repository.json:9:33
/**
 * - Initializer:
 *   - <tt> github_repository_init(struct github_repository *) </tt>
 * - Cleanup:
 *   - <tt> github_repository_cleanup(struct github_repository *) </tt>
 *   - <tt> github_repository_list_free(struct github_repository **) </tt>
 * - JSON Decoder:
 *   - <tt> github_repository_from_json(char *rbuf, size_t len, struct github_repository **) </tt>
 *   - <tt> github_repository_list_from_json(char *rbuf, size_t len, struct github_repository ***) </tt>
 * - JSON Encoder:
 *   - <tt> github_repository_to_json(char *wbuf, size_t len, struct github_repository *) </tt>
 *   - <tt> github_repository_list_to_json(char *wbuf, size_t len, struct github_repository **) </tt>
 */
struct github_repository {
  /* specs/github/github-repository.json:12:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  int id;

  /* specs/github/github-repository.json:13:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  char *node_id;

  /* specs/github/github-repository.json:14:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/github/github-repository.json:15:28
     '{ "name": "full_name", "type":{ "base":"char", "dec":"*"}}' */
  char *full_name;

  /* specs/github/github-repository.json:16:28
     '{ "name": "private", "type":{ "base":"bool"}}' */
  bool private;

  /* specs/github/github-repository.json:17:77
     '{ "type": {"base":"struct github_user", "dec":"*"}, "name":"owner"}' */
  struct github_user *owner;

  /* specs/github/github-repository.json:18:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  char *html_url;

  /* specs/github/github-repository.json:19:28
     '{ "name": "description", "type":{ "base":"char", "dec":"*"}}' */
  char *description;

  /* specs/github/github-repository.json:20:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  char *created_at;

  /* specs/github/github-repository.json:21:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  char *updated_at;

  /* specs/github/github-repository.json:22:28
     '{ "name": "pushed_at", "type":{ "base":"char", "dec":"*"}}' */
  char *pushed_at;

  /* specs/github/github-repository.json:23:28
     '{ "name": "homepage", "type":{ "base":"char", "dec":"*"}}' */
  char *homepage;

  /* specs/github/github-repository.json:24:28
     '{ "name": "size", "type":{ "base": "int"}}' */
  int size;

  /* specs/github/github-repository.json:25:28
     '{ "name": "stargazers_count", "type":{ "base": "int"}}' */
  int stargazers_count;

  /* specs/github/github-repository.json:26:28
     '{ "name": "watchers_count", "type":{ "base": "int"}}' */
  int watchers_count;

  /* specs/github/github-repository.json:27:28
     '{ "name": "language", "type":{ "base":"char", "dec":"*"}}' */
  char *language;

  /* specs/github/github-repository.json:28:28
     '{ "name": "has_issues", "type":{ "base":"bool"}}' */
  bool has_issues;

  /* specs/github/github-repository.json:29:28
     '{ "name": "has_projects", "type":{ "base":"bool"}}' */
  bool has_projects;

  /* specs/github/github-repository.json:30:28
     '{ "name": "has_downloads", "type":{ "base":"bool"}}' */
  bool has_downloads;

  /* specs/github/github-repository.json:31:28
     '{ "name": "has_wiki", "type":{ "base":"bool"}}' */
  bool has_wiki;

  /* specs/github/github-repository.json:32:28
     '{ "name": "has_pages", "type":{ "base":"bool"}}' */
  bool has_pages;

  /* specs/github/github-repository.json:33:28
     '{ "name": "forks_count", "type":{ "base": "int"}}' */
  int forks_count;

  /* specs/github/github-repository.json:34:28
     '{ "name": "archived", "type":{ "base":"bool"}}' */
  bool archived;

  /* specs/github/github-repository.json:35:28
     '{ "name": "disabled", "type":{ "base":"bool"}}' */
  bool disabled;

  /* specs/github/github-repository.json:36:28
     '{ "name": "open_issues_count", "type":{ "base": "int"}}' */
  int open_issues_count;

  /* specs/github/github-repository.json:37:80
     '{ "type": {"base":"struct github_license", "dec":"*"}, "name":"license"}' */
  struct github_license *license;

  /* specs/github/github-repository.json:38:28
     '{ "name": "forks", "type":{ "base": "int"}}' */
  int forks;

  /* specs/github/github-repository.json:39:28
     '{ "name": "open_issues", "type":{ "base": "int"}}' */
  int open_issues;

  /* specs/github/github-repository.json:40:28
     '{ "name": "watchers", "type":{ "base": "int"}}' */
  int watchers;

  /* specs/github/github-repository.json:41:28
     '{ "name": "default_branch", "type":{ "base":"char", "dec":"*"}}' */
  char *default_branch;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[30];
    void *record_defined[30];
    void *record_null[30];
  } __M; // metadata
/// @endcond
};
/* This file is generated from specs/github/github-user.json, Please don't edit it. */
/**
 * @file specs-code/github/all_structs.h
 * @see https://docs.github.com/en/rest/reference/users#get-a-user
 */


// User Structure
// defined at specs/github/github-user.json:9:33
/**
 * - Initializer:
 *   - <tt> github_user_init(struct github_user *) </tt>
 * - Cleanup:
 *   - <tt> github_user_cleanup(struct github_user *) </tt>
 *   - <tt> github_user_list_free(struct github_user **) </tt>
 * - JSON Decoder:
 *   - <tt> github_user_from_json(char *rbuf, size_t len, struct github_user **) </tt>
 *   - <tt> github_user_list_from_json(char *rbuf, size_t len, struct github_user ***) </tt>
 * - JSON Encoder:
 *   - <tt> github_user_to_json(char *wbuf, size_t len, struct github_user *) </tt>
 *   - <tt> github_user_list_to_json(char *wbuf, size_t len, struct github_user **) </tt>
 */
struct github_user {
  /* specs/github/github-user.json:12:28
     '{ "name": "login", "type":{ "base":"char", "dec":"*"}}' */
  char *login;

  /* specs/github/github-user.json:13:28
     '{ "name": "id", "type":{ "base":"int"}}' */
  int id;

  /* specs/github/github-user.json:14:28
     '{ "name": "node_id", "type":{ "base":"char", "dec":"*"}}' */
  char *node_id;

  /* specs/github/github-user.json:15:28
     '{ "name": "avatar_url", "type":{ "base":"char", "dec":"*"}}' */
  char *avatar_url;

  /* specs/github/github-user.json:16:28
     '{ "name": "gravatar_id", "type":{ "base":"char", "dec":"*"}}' */
  char *gravatar_id;

  /* specs/github/github-user.json:17:28
     '{ "name": "html_url", "type":{ "base":"char", "dec":"*"}}' */
  char *html_url;

  /* specs/github/github-user.json:18:28
     '{ "name": "type", "type":{ "base":"char", "dec":"*"}}' */
  char *type;

  /* specs/github/github-user.json:19:28
     '{ "name": "site_admin", "type":{ "base":"bool"}}' */
  bool site_admin;

  /* specs/github/github-user.json:20:28
     '{ "name": "name", "type":{ "base":"char", "dec":"*"}}' */
  char *name;

  /* specs/github/github-user.json:21:28
     '{ "name": "company", "type":{ "base":"char", "dec":"*"}}' */
  char *company;

  /* specs/github/github-user.json:22:28
     '{ "name": "blog", "type":{ "base":"char", "dec":"*"}}' */
  char *blog;

  /* specs/github/github-user.json:23:28
     '{ "name": "location", "type":{ "base":"char", "dec":"*"}}' */
  char *location;

  /* specs/github/github-user.json:24:28
     '{ "name": "email", "type":{ "base":"char", "dec":"*"}}' */
  char *email;

  /* specs/github/github-user.json:25:28
     '{ "name": "hireable", "type":{ "base":"char", "dec":"*"}}' */
  char *hireable;

  /* specs/github/github-user.json:26:28
     '{ "name": "bio", "type":{ "base":"char", "dec":"*"}}' */
  char *bio;

  /* specs/github/github-user.json:27:28
     '{ "name": "public_repos", "type":{ "base":"int"}}' */
  int public_repos;

  /* specs/github/github-user.json:28:28
     '{ "name": "public_gists", "type":{ "base":"int"}}' */
  int public_gists;

  /* specs/github/github-user.json:29:28
     '{ "name": "followers", "type":{ "base":"int"}}' */
  int followers;

  /* specs/github/github-user.json:30:28
     '{ "name": "following", "type":{ "base":"int"}}' */
  int following;

  /* specs/github/github-user.json:31:28
     '{ "name": "created_at", "type":{ "base":"char", "dec":"*"}}' */
  char *created_at;

  /* specs/github/github-user.json:32:28
     '{ "name": "updated_at", "type":{ "base":"char", "dec":"*"}}' */
  char *updated_at;

  // The following is metadata used to 
  // 1. control which field should be extracted/injected
  // 2. record which field is presented(defined) in JSON
  // 3. record which field is null in JSON
/// @cond DOXYGEN_SHOULD_SKIP_THIS
  struct {
    bool enable_arg_switches;
    bool enable_record_defined;
    bool enable_record_null;
    void *arg_switches[21];
    void *record_defined[21];
    void *record_null[21];
  } __M; // metadata
/// @endcond
};
