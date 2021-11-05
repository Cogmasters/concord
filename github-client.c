#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "cee-utils.h"
#include "cee-utils/ntl.h"
#include "json-actor.h"

#include "github.h"
#include "github-internal.h"

static void
_github_presets_init(struct github_presets *presets,
                     char *username,
                     char *token,
                     const char *repo_config)
{

  presets->owner = NULL;
  presets->repo = NULL;
  presets->default_branch = NULL;

  /* Optionally fill in the repo_config. Can be
   * done later with github_fill_repo_config. */
  if (repo_config) {
    size_t len = 0;
    char *json = cee_load_whole_file(repo_config, &len);

    json_extract(json, len, "(owner):?s,(repo):?s,(default_branch):?s",
                 &presets->owner, &presets->repo, &presets->default_branch);

    free(json);
  }

  presets->username = username;
  presets->token = token;
}

void
github_write_json(char *json, size_t len, void *user_obj)
{
  struct sized_buffer *new_user_obj = user_obj;
  new_user_obj->size = asprintf(&new_user_obj->start, "%.*s", (int)len, json);
}

ORCAcode
github_fill_repo_config(struct github *client, char *repo_config)
{
  log_info("===github-fill-repo-config===");

  if (!repo_config) {
    log_error("repo_config is NULL.");
    return ORCA_MISSING_PARAMETER;
  }

  size_t len = 0;
  char *json = cee_load_whole_file(repo_config, &len);

  json_extract(json, len, "(owner):?s,(repo):?s,(default_branch):?s",
               &client->presets.owner, &client->presets.repo,
               &client->presets.default_branch);

  free(json);

  return ORCA_OK;
}

static void
load_object_sha(char *str, size_t len, void *pp)
{
  json_extract(str, len, "(object.sha):?s", (char **)pp);
}

static void
load_sha(char *json, size_t len, void *pp)
{
  json_extract(json, len, "(sha):?s", (char **)pp);
}

static void
__log_trace(char *str, size_t len, void *p)
{
  log_trace("%.*s", (int)len, str);
}

struct github *
github_init(const char username[],
            const char token[],
            const char repo_config[])
{
  struct github *new_client = calloc(1, sizeof *new_client);

  logconf_setup(&new_client->conf, "GITHUB", NULL);

  _github_presets_init(&new_client->presets, strdup(username), strdup(token),
                       repo_config);

  github_adapter_init(&new_client->adapter, &new_client->conf,
                      &new_client->presets);

  return new_client;
}

struct github *
github_config_init(const char config_file[], const char repo_config[])
{
  struct github *new_client = calloc(1, sizeof *new_client);

  FILE *fp = fopen(config_file, "rb");
  VASSERT_S(fp != NULL, "Couldn't open '%s': %s", config_file,
            strerror(errno));

  logconf_setup(&new_client->conf, "GITHUB", fp);

  fclose(fp);

  struct sized_buffer t_username, t_token;
  t_username = logconf_get_field(&new_client->conf, "github.username");
  t_token = logconf_get_field(&new_client->conf, "github.token");

  char *username, *token;
  asprintf(&username, "%.*s", (int)t_username.size, t_username.start);
  asprintf(&token, "%.*s", (int)t_token.size, t_token.start);

  _github_presets_init(&new_client->presets, username, token, repo_config);

  github_adapter_init(&new_client->adapter, &new_client->conf,
                      &new_client->presets);

  return new_client;
}

ORCAcode
github_update_my_fork(struct github *client, char **p_sha)
{
  log_info("===update-my-fork===");

  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.default_branch) {
    log_error("Missing 'default_branch'");
    return ORCA_MISSING_PARAMETER;
  }

  char *sha = NULL;
  ORCAcode code;
  code = github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &load_object_sha, .ok_obj = &sha },
    NULL, HTTP_GET, "/repos/%s/%s/git/refs/heads/%s", client->presets.owner,
    client->presets.repo, client->presets.default_branch);

  if (ORCA_OK != code) {
    log_error("Couldn't fetch sha");
    return code;
  }

  char payload[2048];
  size_t ret = json_inject(payload, sizeof(payload), "(sha):s", sha);

  if (p_sha)
    *p_sha = sha;
  else
    free(sha);

  return github_adapter_run(
    &client->adapter, &(struct ua_resp_handle){ .ok_cb = &__log_trace },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/repos/%s/%s/git/refs/heads/%s", client->presets.username,
    client->presets.repo, client->presets.default_branch);
}

ORCAcode
github_get_head_commit(struct github *client, char **p_sha)
{
  if (!p_sha) {
    log_error("Missing 'p_sha'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.default_branch) {
    log_error("Missing 'default_branch'");
    return ORCA_MISSING_PARAMETER;
  }

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &load_object_sha, .ok_obj = p_sha },
    NULL, HTTP_GET, "/repos/%s/%s/git/refs/heads/%s", client->presets.username,
    client->presets.repo, client->presets.default_branch);
}

ORCAcode
github_get_tree_sha(struct github *client, char *commit_sha, char **p_sha)
{
  log_info("===get-tree-sha==");

  if (!commit_sha) {
    log_error("Missing 'commit_sha'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_sha) {
    log_error("Missing 'p_sha'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.repo) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &load_sha, .ok_obj = p_sha }, NULL,
    HTTP_GET, "/repos/%s/%s/git/trees/%s", client->presets.username,
    client->presets.repo, commit_sha);
}

ORCAcode
github_create_blobs(struct github *client, NTL_T(struct github_file) files)
{
  if (!files) {
    log_error("Missing 'files'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.repo) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  int i;
  char *f_content;
  size_t f_len;
  ORCAcode code;

  for (i = 0; files[i]; ++i) {
    log_info("===creating blob for %s===", files[i]->path);

    f_content = cee_load_whole_file(files[i]->path, &f_len);
    if (!f_content) {
      log_error("Path doesn't exist: '%s'", files[i]->path);
      return ORCA_BAD_PARAMETER;
    }

    char *payload = NULL;
    size_t ret;
    ret = json_ainject(&payload,
                       "(content):.*s"
                       "(encoding):|utf-8|",
                       f_len, f_content);

    if (!payload) {
      log_error("Couldn't create JSON Payload");
      free(f_content);
      return ORCA_BAD_JSON;
    }

    code = github_adapter_run(
      &client->adapter,
      &(struct ua_resp_handle){ .ok_cb = &load_sha, .ok_obj = &files[i]->sha },
      &(struct sized_buffer){ payload, ret }, HTTP_POST,
      "/repos/%s/%s/git/blobs", client->presets.username,
      client->presets.repo);

    free(payload);
    free(f_content);
  }

  return code;
}

static size_t
node2json(char *str, size_t size, void *p)
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
node_list2json(char *buf, size_t size, void *p)
{
  return ntl_to_buf(buf, size, (void **)p, NULL, node2json);
}

ORCAcode
github_create_tree(struct github *client,
                   char *base_tree_sha,
                   NTL_T(struct github_file) files,
                   char **p_tree_sha)
{
  log_info("==create-tree==");

  if (!base_tree_sha) {
    log_error("Missing 'base_tree_sha'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!files) {
    log_error("Missing 'files'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.repo) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[2048];
  size_t ret;
  ret = json_inject(payload, sizeof(payload),
                    "(tree):F"
                    "(base_tree):s",
                    &node_list2json, files, base_tree_sha);

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_tree_sha ? &load_sha : NULL,
                              .ok_obj = p_tree_sha },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/repos/%s/%s/git/trees", client->presets.username, client->presets.repo);
}

ORCAcode
github_create_a_commit(struct github *client,
                       char *tree_sha,
                       char *parent_commit_sha,
                       char *commit_msg,
                       char **p_commit_sha)
{
  log_info("===create-a-commit===");

  if (!tree_sha) {
    log_error("Missing 'tree_sha'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!parent_commit_sha) {
    log_error("Missing 'parent_commit_sha'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!commit_msg) {
    log_error("Missing 'commit_msg'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.repo) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret;
  ret = json_inject(payload, sizeof(payload),
                    "(message):s"
                    "(tree):s"
                    "(parents):[s]",
                    commit_msg, tree_sha, parent_commit_sha);

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_commit_sha ? &load_sha : NULL,
                              .ok_obj = p_commit_sha },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/repos/%s/%s/git/commits", client->presets.username,
    client->presets.repo);
}

ORCAcode
github_create_a_branch(struct github *client,
                       char *head_commit_sha,
                       char *branch)
{
  log_info("===create-a-branch===");

  if (!head_commit_sha) {
    log_error("Missing 'head_commit_sha'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!branch) {
    log_error("Missing 'branch'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.repo) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret;
  ret = json_inject(payload, sizeof(payload),
                    "(ref):|refs/heads/%s|"
                    "(sha):s",
                    branch, head_commit_sha);

  return github_adapter_run(
    &client->adapter, &(struct ua_resp_handle){ .ok_cb = &__log_trace },
    &(struct sized_buffer){ payload, ret }, HTTP_POST, "/repos/%s/%s/git/refs",
    client->presets.username, client->presets.repo);
}

ORCAcode
github_update_a_commit(struct github *client, char *branch, char *commit_sha)
{
  log_info("===update-a-commit===");

  if (!branch) {
    log_error("Missing 'branch'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!commit_sha) {
    log_error("Missing 'commit_sha'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.repo) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[512];
  size_t ret;
  ret = json_inject(payload, sizeof(payload), "(sha):s", commit_sha);

  return github_adapter_run(
    &client->adapter, &(struct ua_resp_handle){ .ok_cb = &__log_trace },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/repos/%s/%s/git/refs/heads/%s", client->presets.username,
    client->presets.repo, branch);
}

ORCAcode
github_create_a_pull_request(struct github *client,
                             char *branch,
                             char *pull_msg)
{
  log_info("===create-a-pull-request===");

  if (!branch) {
    log_error("Missing 'branch'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!pull_msg) {
    log_error("Missing 'pull_msg'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!client->presets.default_branch) {
    log_error("Missing 'default_branch'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[4096];
  size_t ret;
  ret = json_inject(payload, sizeof(payload),
                    "(title):s"
                    "(body):s"
                    "(head):|%s:%s|"
                    "(base):s",
                    branch, pull_msg, client->presets.username, branch,
                    client->presets.default_branch);

  return github_adapter_run(
    &client->adapter, &(struct ua_resp_handle){ .ok_cb = &__log_trace },
    &(struct sized_buffer){ payload, ret }, HTTP_POST, "/repos/%s/%s/pulls",
    client->presets.owner, client->presets.repo);
}

ORCAcode
github_get_user(struct github *client,
                char *username,
                struct github_user *user)
{
  log_info("===get-user===");

  if (!username) {
    log_error("Missing 'username'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user) {
    log_error("Missing 'user'");
    return ORCA_MISSING_PARAMETER;
  }

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &github_user_from_json_v,
                              .ok_obj = &user },
    NULL, HTTP_GET, "/users/%s", username);
}

ORCAcode
github_get_repository(struct github *client,
                      char *owner,
                      char *repo,
                      struct sized_buffer *output)
{
  log_info("===get-repository===");

  if (!repo) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  if (!output) {
    log_error("Missing 'repo'");
    return ORCA_MISSING_PARAMETER;
  }

  return github_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &github_write_json, .ok_obj = output },
    NULL, HTTP_GET, "/repos/%s/%s", owner, repo);
}
