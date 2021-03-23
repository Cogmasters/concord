#include <stdio.h>
#include <stdlib.h>

#include "github-v3-user-agent.h"

#include "orka-utils.h"
#include "json-actor.h"
#include "github-v3.h"

struct github_config_dati {
  char *owner;
  char *username;
  char *repo;
  char *default_branch;
};

void
github_config_init(struct github_config_dati *data, char * username, char *file)
{
  size_t len = 0;
  char *json = orka_load_whole_file(file, &len);
  json_extract(json, len, "(owner):?s (repo):?s (default_branch):?s",
               &data->owner, &data->repo, &data->default_branch);
  data->username = username;
  free(json);
}

struct github_v3_git_op_dati {
  struct github_v3_user_agent_dati ua_data;
  struct github_config_dati config;
  struct sized_buffer body;
  struct resp_handle handle;
};

/*
struct github_v3_git_op_file {
  char *path;
  char *sha;
};
*/

static void
load_object_sha(char *str, size_t len, void *ptr) 
{
  fprintf(stderr, "%.*s\n", (int)len, str);
  json_extract(str, len, "(object.sha):?s", ptr);
  fprintf(stderr, "extracted sha %s\n", *(char **)ptr);
}

static void
load_sha(char *json, size_t len, void *ptr)
{
  fprintf(stderr, "%.*s\n", (int)len, json);
  json_extract(json, len, "(sha):?s", ptr);
  fprintf(stderr, "extracted sha %s\n", *(char **)ptr);
}

static void
log(char *str, size_t len, void *ptr) {
  fprintf(stderr, "%.*s\n", (int)len, str);
}

struct github_v3_git_op_dati*
github_v3_git_op_init(char *username, char *token, char *repo_config)
{
  struct github_v3_git_op_dati *d = calloc(1, sizeof(*d));

  github_v3_user_agent_init (&d->ua_data, username, token);
  github_config_init(&d->config, username, repo_config);

  d->handle.ok_cb = NULL;
  d->handle.ok_obj = NULL;
  d->handle.err_cb = log;
  d->handle.err_obj = NULL;
  d->body.start = NULL;
  d->body.size = 0;
  return d;
}

char * github_v3_git_op_update_my_fork(struct github_v3_git_op_dati *d)
{
  fprintf(stderr, "===update-my-fork===\n");
  char *sha = NULL;
  d->handle.ok_cb = load_object_sha;
  d->handle.ok_obj = &sha;
  github_v3_user_agent_run(&d->ua_data, &d->handle, NULL,
                  HTTP_GET, "/repos/%s/%s/git/refs/heads/%s",
                  d->config.owner, d->config.repo, d->config.default_branch);

  d->handle.ok_cb = log;

  d->body.size = json_ainject(&d->body.start, "(sha):s", sha);

  fprintf(stderr, "PATCH: %.*s %zu\n", (int)d->body.size, d->body.start, d->body.size);
  github_v3_user_agent_run(&d->ua_data, &d->handle, &d->body,
                  HTTP_PATCH, "/repos/%s/%s/git/refs/heads/%s",
                  d->config.username, d->config.repo, d->config.default_branch);
  free(d->body.start);
  return sha;
}


char *
github_v3_git_op_get_head_commit(struct github_v3_git_op_dati *d)
{
  char *sha = NULL;
  d->handle.ok_cb = load_object_sha;
  d->handle.ok_obj = &sha;
  github_v3_user_agent_run(&d->ua_data, &d->handle, NULL,
          HTTP_GET, "/repos/%s/%s/git/refs/heads/%s",
          d->config.username, d->config.repo, d->config.default_branch);
  return sha;
}


char *
github_v3_git_op_get_tree_sha(struct github_v3_git_op_dati *d, char *commit_sha)
{
  fprintf(stderr, "===get-tree-sha==\n");
  char *sha = NULL;
  d->handle.ok_cb = load_sha;
  d->handle.ok_obj = &sha;
  github_v3_user_agent_run(&d->ua_data, &d->handle, NULL,
          HTTP_GET, "/repos/%s/%s/git/trees/%s",
          d->config.username, d->config.repo, commit_sha);

  fprintf(stderr, "tree-sha:%s\n", sha);
  return sha;
}

void
github_v3_git_op_create_blobs(struct github_v3_git_op_dati *d, struct github_v3_git_op_file **files)
{
  char *file_sha = NULL;
  d->handle.ok_cb = load_sha;
  d->handle.ok_obj = &file_sha;

  for (int i = 0; files[i]; i++) {
    fprintf(stderr, "===creating blob for %s===\n", files[i]->path);
    size_t len;
    char *content = orka_load_whole_file(files[i]->path, &len);

    d->body.size = json_ainject(&d->body.start,
                                     "(content) : .*s, (encoding) : |utf-8|",
                                     len, content);

    fprintf(stderr, "%.*s\n", (int)d->body.size, d->body.start);
    github_v3_user_agent_run(&d->ua_data, &d->handle, &d->body,
            HTTP_POST, "/repos/%s/%s/git/blobs",
            d->config.username, d->config.repo);
    free(d->body.start);

    fprintf(stderr, "file-sha %s\n", file_sha);
    files[i]->sha = file_sha;
  }
}

static size_t
node2json(char *str, size_t size, void *p)
{
  struct github_v3_git_op_file *f = (struct github_v3_git_op_file *)p;
  return json_inject(str, size,
                     "(path) : s"
                     "(mode) : |100644|"
                     "(type) : |blob|"
                     "(sha) : s",
                     f->path,
                     f->sha);
}

static int
node_list2json(char *buf, size_t size, void *p) {
  return ntl_to_buf(buf, size, (void **)p, NULL, node2json);
}

char *
github_v3_git_op_create_tree(
  struct github_v3_git_op_dati *d, char *base_tree_sha, 
  struct github_v3_git_op_file **files)
{
  fprintf(stderr, "==create-tree==\n");

  d->body.size = json_ainject(&d->body.start,
                              "(tree):F"
                              "(base_tree):s",
                              node_list2json, files,
                              base_tree_sha);

  char *new_tree_sha = NULL;
  d->handle.ok_cb = load_sha;
  d->handle.ok_obj = &new_tree_sha;

  fprintf(stderr, "%s\n", d->body.start);
  github_v3_user_agent_run(&d->ua_data, &d->handle, &d->body,
          HTTP_POST, "/repos/%s/%s/git/trees",
          d->config.username, d->config.repo);

  free(d->body.start);
  fprintf(stderr, "new-tree-sha:%s\n", new_tree_sha);

  return new_tree_sha;
}

char *
github_v3_git_op_create_a_commit(struct github_v3_git_op_dati *d, char *tree_sha, 
                 char *parent_commit_sha, char *commit_msg)
{
  fprintf(stderr, "===create-a-commit===\n");
  char *new_commit_sha = NULL;
  d->handle.ok_cb = load_sha;
  d->handle.ok_obj = &new_commit_sha;

  d->body.size = json_ainject(&d->body.start,
                              " (message) : s"
                              " (tree) : s"
                              " (parents) : [ s ]",
                              commit_msg,
                              tree_sha,
                              parent_commit_sha);

  github_v3_user_agent_run(&d->ua_data, &d->handle, &d->body,
          HTTP_POST, "/repos/%s/%s/git/commits",
          d->config.username, d->config.repo);

  free(d->body.start);
  fprintf(stderr, "commit-sha:%s\n", new_commit_sha);
  return new_commit_sha;
}

void
github_v3_git_op_create_a_branch(struct github_v3_git_op_dati *d, char *head_commit_sha, char *branch)
{
  fprintf(stderr, "===create-a-branch===\n");
  d->body.size = json_ainject(&d->body.start,
                              "(ref): |refs/heads/%s|"
                              "(sha): s",
                              branch, head_commit_sha);

  fprintf(stderr, "%.*s\n", (int)d->body.size, d->body.start);
  d->handle.ok_cb = log;
  d->handle.ok_obj = NULL;
  github_v3_user_agent_run(&d->ua_data, &d->handle, &d->body,
          HTTP_POST, "/repos/%s/%s/git/refs",
          d->config.username, d->config.repo);
  free(d->body.start);
}

void
github_v3_git_op_update_a_commit(struct github_v3_git_op_dati *d, char *branch, char *commit_sha)
{
  fprintf(stderr, "===update-a-commit===\n");
  d->handle.ok_cb = log;
  d->body.size = json_ainject(&d->body.start, "(sha):s", commit_sha);
  fprintf(stderr, "PATCH: %s\n", d->body.start);
  github_v3_user_agent_run(&d->ua_data, &d->handle, &d->body,
          HTTP_PATCH, "/repos/%s/%s/git/refs/heads/%s",
          d->config.username, d->config.repo, branch);
  free(d->body.start);
}

void
github_v3_git_op_create_a_pull_request(struct github_v3_git_op_dati *d, char *branch, char *pull_msg) {
  // 5. create a pull request
  fprintf(stderr, "===create-a-pull-request===\n");

  d->body.size = json_ainject(&d->body.start,
                              "(title): s"
                              "(body): s"
                              "(head): |%s:%s|"
                              "(base): s",
                              branch, pull_msg, d->config.username,
                              branch, d->config.default_branch);

  d->handle.ok_cb = log;
  github_v3_user_agent_run(&d->ua_data, &d->handle, &d->body,
          HTTP_POST, "/repos/%s/%s/pulls", d->config.owner, d->config.repo);
  free(d->body.start);
}