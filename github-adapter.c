#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "github.h"
#include "github-internal.h"

/**
 * @brief Shortcut for setting attributes for a specs-generated struct
 *
 * @param type datatype of the struct
 * @param obj pointer to specs-generated struct
 */
#define REQUEST_ATTR_INIT(type, obj)                                          \
  {                                                                           \
    obj, sizeof *obj, type##_init_v, type##_from_json_v, type##_cleanup_v     \
  }

static void
setopt_cb(struct ua_conn *conn, void *p_presets)
{
  struct github_presets *presets = p_presets;
  CURL *ehandle = ua_conn_get_easy_handle(conn);

  ua_conn_add_header(conn, "Accept", "application/vnd.github.v3+json");

  curl_easy_setopt(ehandle, CURLOPT_USERNAME, presets->username);
  curl_easy_setopt(ehandle, CURLOPT_USERPWD, presets->token);
}

void
github_adapter_init(struct github_adapter *adapter,
                    struct logconf *conf,
                    struct github_presets *presets)
{
  struct ua_attr attr = { 0 };

  attr.conf = conf;
  adapter->ua = ua_init(&attr);
  ua_set_url(adapter->ua, GITHUB_BASE_API_URL);

  logconf_branch(&adapter->conf, conf, "GITHUB_HTTP");

  ua_set_opt(adapter->ua, presets, &setopt_cb);
}

void
github_adapter_cleanup(struct github_adapter *adapter)
{
  ua_cleanup(adapter->ua);
}

static ORCAcode
_github_adapter_perform(struct github_adapter *adapter,
                        struct github_request_attr *attr,
                        struct sized_buffer *body,
                        enum http_method method,
                        char endpoint[])
{
  struct ua_conn_attr conn_attr = { method, body, endpoint };
  struct ua_conn *conn = ua_conn_start(adapter->ua);
  ORCAcode code;
  bool retry;

  /* populate conn with parameters */
  ua_conn_setup(conn, &conn_attr);

  do {
    /* perform blocking request, and check results */
    switch (code = ua_conn_easy_perform(conn)) {
    case ORCA_OK: {
      struct ua_info info = { 0 };
      struct sized_buffer body;

      ua_info_extract(conn, &info);

      body = ua_info_get_body(&info);
      if (ORCA_OK == info.code && attr->obj) {
        if (attr->init) attr->init(attr->obj);

        attr->from_json(body.start, body.size, attr->obj);
      }

      ua_info_cleanup(&info);

      retry = false;
    } break;
    case ORCA_CURLE_INTERNAL:
      logconf_error(&adapter->conf, "Curl internal error, will retry again");
      retry = true;
      break;
    default:
      logconf_error(&adapter->conf, "ORCA code: %d", code);
      retry = false;
      break;
    }

    ua_conn_reset(conn);
  } while (retry);

  ua_conn_stop(conn);

  return code;
}

/* template function for performing requests */
ORCAcode
github_adapter_run(struct github_adapter *adapter,
                   struct github_request_attr *attr,
                   struct sized_buffer *body,
                   enum http_method method,
                   char endpoint_fmt[],
                   ...)
{
  static struct github_request_attr blank_attr = { 0 };
  char endpoint[2048];
  va_list args;
  int ret;

  /* have it point somewhere */
  if (!attr) attr = &blank_attr;

  /* build the endpoint string */
  va_start(args, endpoint_fmt);

  ret = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
  ASSERT_S(ret < sizeof(endpoint), "Out of bounds write attempt");

  va_end(args);

  return _github_adapter_perform(adapter, attr, body, method, endpoint);
}

static void
object_sha_from_json(char *str, size_t len, void *pp)
{
  json_extract(str, len, "(object.sha):?s", (char **)pp);
}

static void
sha_from_json(char *json, size_t len, void *pp)
{
  json_extract(json, len, "(sha):?s", (char **)pp);
}

ORCAcode
github_get_repository(struct github *client,
                      char *owner,
                      char *repo,
                      struct sized_buffer *ret)
{
  struct github_request_attr attr = { ret, 0, NULL, &github_write_json };

  ORCA_EXPECT(client, !IS_EMPTY_STRING(repo), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return github_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                            "/repos/%s/%s", owner, repo);
}

ORCAcode
github_create_fork(struct github *client, char *owner, char *repo)
{
  ORCA_EXPECT(client, !IS_EMPTY_STRING(owner), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(repo), ORCA_BAD_PARAMETER);

  return github_adapter_run(&client->adapter, NULL, NULL, HTTP_POST,
                            "/repos/%s/%s/forks", owner, repo);
}

ORCAcode
github_update_my_fork(struct github *client, char **ret)
{
  struct github_request_attr attr = { ret, 0, NULL, &object_sha_from_json };
  struct sized_buffer body;
  char *sha = NULL;
  char buf[2048];
  ORCAcode code;

  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.default_branch),
              ORCA_BAD_PARAMETER);

  code =
    github_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                       "/repos/%s/%s/git/refs/heads/%s", client->presets.owner,
                       client->presets.repo, client->presets.default_branch);

  ORCA_EXPECT(client, ORCA_OK == code, code, "Couldn't fetch sha");

  body.size = json_inject(buf, sizeof(buf), "(sha):s", sha);
  body.start = buf;

  if (ret)
    *ret = sha;
  else
    free(sha);

  return github_adapter_run(&client->adapter, NULL, &body, HTTP_PATCH,
                            "/repos/%s/%s/git/refs/heads/%s",
                            client->presets.username, client->presets.repo,
                            client->presets.default_branch);
}

ORCAcode
github_get_head_commit(struct github *client, char **ret)
{
  struct github_request_attr attr = { ret, 0, NULL, &object_sha_from_json };

  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.default_branch),
              ORCA_BAD_PARAMETER);

  return github_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                            "/repos/%s/%s/git/refs/heads/%s",
                            client->presets.username, client->presets.repo,
                            client->presets.default_branch);
}

ORCAcode
github_get_tree_sha(struct github *client, char *commit_sha, char **ret)
{
  struct github_request_attr attr = { ret, 0, NULL, &sha_from_json };

  ORCA_EXPECT(client, !IS_EMPTY_STRING(commit_sha), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.repo),
              ORCA_BAD_PARAMETER);

  return github_adapter_run(
    &client->adapter, &attr, NULL, HTTP_GET, "/repos/%s/%s/git/trees/%s",
    client->presets.username, client->presets.repo, commit_sha);
}

ORCAcode
github_create_blobs(struct github *client, struct github_file **files)
{
  struct github_request_attr attr = { NULL, 0, NULL, &sha_from_json };
  struct sized_buffer body;
  ORCAcode code;
  char *buf;
  int i;

  ORCA_EXPECT(client, files != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.repo),
              ORCA_BAD_PARAMETER);

  for (i = 0; files[i]; ++i) {
    char *f_content;
    size_t f_len;

    f_content = cee_load_whole_file(files[i]->path, &f_len);
    ORCA_EXPECT(client, f_content != NULL, ORCA_BAD_PARAMETER,
                "File path doesn't exist");

    buf = NULL;

    body.size = json_ainject(&buf,
                             "(content):.*s"
                             "(encoding):|utf-8|",
                             f_len, f_content);
    body.start = buf;
    free(f_content);

    ORCA_EXPECT(client, buf != NULL, ORCA_BAD_JSON);

    attr.obj = &files[i]->sha;

    code = github_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                              "/repos/%s/%s/git/blobs",
                              client->presets.username, client->presets.repo);

    free(buf);
  }

  return code;
}

static size_t
node_to_json(char *str, size_t size, void *p)
{
  struct github_file *f = p;

  return json_inject(str, size,
                     "(path):s"
                     "(mode):|100644|"
                     "(type):|blob|"
                     "(sha):s",
                     f->path, f->sha);
}

static int
node_list_to_json(char *buf, size_t size, void *p)
{
  return ntl_to_buf(buf, size, (void **)p, NULL, &node_to_json);
}

ORCAcode
github_create_tree(struct github *client,
                   char *base_tree_sha,
                   struct github_file **files,
                   char **ret)
{
  struct github_request_attr attr = { ret, 0, NULL, &sha_from_json };
  struct sized_buffer body;
  char buf[2048];

  ORCA_EXPECT(client, !IS_EMPTY_STRING(base_tree_sha), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, files != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.repo),
              ORCA_BAD_PARAMETER);

  body.size = json_inject(buf, sizeof(buf),
                          "(tree):F"
                          "(base_tree):s",
                          &node_list_to_json, files, base_tree_sha);
  body.start = buf;

  return github_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                            "/repos/%s/%s/git/trees", client->presets.username,
                            client->presets.repo);
}

ORCAcode
github_create_a_commit(struct github *client,
                       char *tree_sha,
                       char *parent_commit_sha,
                       char *commit_msg,
                       char **ret)
{
  struct github_request_attr attr = { ret, 0, NULL, &sha_from_json };
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, !IS_EMPTY_STRING(tree_sha), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(parent_commit_sha), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(commit_msg), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.repo),
              ORCA_BAD_PARAMETER);

  body.size = json_inject(buf, sizeof(buf),
                          "(message):s"
                          "(tree):s"
                          "(parents):[s]",
                          commit_msg, tree_sha, parent_commit_sha);
  body.start = buf;

  return github_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                            "/repos/%s/%s/git/commits",
                            client->presets.username, client->presets.repo);
}

ORCAcode
github_create_a_branch(struct github *client,
                       char *head_commit_sha,
                       char *branch)
{
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, !IS_EMPTY_STRING(head_commit_sha), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(branch), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.repo),
              ORCA_BAD_PARAMETER);

  body.size = json_inject(buf, sizeof(buf),
                          "(ref):|refs/heads/%s|"
                          "(sha):s",
                          branch, head_commit_sha);
  body.start = buf;

  return github_adapter_run(&client->adapter, NULL, &body, HTTP_POST,
                            "/repos/%s/%s/git/refs", client->presets.username,
                            client->presets.repo);
}

ORCAcode
github_update_a_commit(struct github *client, char *branch, char *commit_sha)
{
  struct sized_buffer body;
  char buf[512];

  ORCA_EXPECT(client, !IS_EMPTY_STRING(branch), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(commit_sha), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.repo),
              ORCA_BAD_PARAMETER);

  body.size = json_inject(buf, sizeof(buf), "(sha):s", commit_sha);
  body.start = buf;

  return github_adapter_run(
    &client->adapter, NULL, &body, HTTP_PATCH, "/repos/%s/%s/git/refs/heads/%s",
    client->presets.username, client->presets.repo, branch);
}

ORCAcode
github_create_a_pull_request(struct github *client,
                             char *branch,
                             char *pull_msg)
{
  struct sized_buffer body;
  char buf[4096];

  ORCA_EXPECT(client, !IS_EMPTY_STRING(branch), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(pull_msg), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.username),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(client->presets.default_branch),
              ORCA_BAD_PARAMETER);

  body.size = json_inject(buf, sizeof(buf),
                          "(title):s"
                          "(body):s"
                          "(head):|%s:%s|"
                          "(base):s",
                          branch, pull_msg, client->presets.username, branch,
                          client->presets.default_branch);
  body.start = buf;

  return github_adapter_run(&client->adapter, NULL, &body, HTTP_POST,
                            "/repos/%s/%s/pulls", client->presets.owner,
                            client->presets.repo);
}

/******************************************************************************
 * Functions specific to Github Users
 ******************************************************************************/

ORCAcode
github_get_user(struct github *client, char *username, struct github_user *ret)
{
  struct github_request_attr attr = REQUEST_ATTR_INIT(github_user, ret);

  ORCA_EXPECT(client, !IS_EMPTY_STRING(username), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return github_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                            "/users/%s", username);
}

ORCAcode
github_get_gist(struct github *client, char *id, struct github_gist *ret)
{
  struct github_request_attr attr = REQUEST_ATTR_INIT(github_gist, ret);

  ORCA_EXPECT(client, !IS_EMPTY_STRING(id), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, ret != NULL, ORCA_BAD_PARAMETER);

  return github_adapter_run(&client->adapter, &attr, NULL, HTTP_GET,
                            "/gists/%s", id);
}

ORCAcode
github_create_gist(struct github *client,
                   struct github_gist_create_params *params,
                   struct github_gist *ret)
{
  struct github_request_attr attr = REQUEST_ATTR_INIT(github_gist, ret);
  struct sized_buffer body;
  char buf[4096];
  char fmt[2048];

  ORCA_EXPECT(client, params != NULL, ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->description),
              ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->title), ORCA_BAD_PARAMETER);
  ORCA_EXPECT(client, !IS_EMPTY_STRING(params->contents), ORCA_BAD_PARAMETER);

  /* Create the format string for the buf
   * TODO: Allocate buffer big enough, then free it after the request is made
   */
  snprintf(fmt, sizeof(fmt),
           "(public): \"%s\", (description): \"%s\", (files): { (%s): { "
           "(content): \"%s\" }}",
           params->public, params->description, params->title,
           params->contents);

  body.size = json_inject(buf, sizeof(buf), fmt);
  body.start = buf;

  return github_adapter_run(&client->adapter, &attr, &body, HTTP_POST,
                            "/gists");
}

ORCAcode
github_gist_is_starred(struct github *client, char *id)
{
  ORCA_EXPECT(client, !IS_EMPTY_STRING(id), ORCA_BAD_PARAMETER);

  return github_adapter_run(&client->adapter, NULL, NULL, HTTP_GET,
                            "/gists/%s/star", id);
}
