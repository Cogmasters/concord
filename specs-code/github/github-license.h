/* This file is generated from specs/github/github-license.json, Please don't edit it. */
/**
 * @file specs-code/github/github-license.h
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
