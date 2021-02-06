#include <stdio.h>
#include <stdlib.h>

#include "github-v3-user-agent.hpp"

#include "orka-utils.h"
#include "json-scanf.h"

namespace github {
namespace config {

struct dati {
  char *owner;
  char *repo;
  char *default_branch;
};

void
init(struct dati *data, char *file)
{
  size_t len = 0;
  char *content = orka_load_whole_file(file, &len);

  json_scanf(content, len, "[owner]%?s [repo]%?s [default_branch]%?s",
             &data->owner, &data->repo, &data->default_branch);
  free(content);
}

} // namespace config

namespace v3 {

namespace git_op { // high-level function

struct dati {
  user_agent::dati ua_data;
  config::dati config;
  struct sized_buffer body;
  struct resp_handle handle;
};


struct file {
  char *path;
  char *sha;
};

static void
load_object_sha(char *str, size_t len, void *ptr) 
{
  fprintf(stderr, "%.*s\n", (int)len, str);
  json_scanf(str, len, "[object][sha]%?s", ptr);
}

static void
load_sha(char *str, size_t len, void *ptr)
{
  fprintf(stderr, "%.*s\n", (int)len, str);
  json_scanf(str, len, "[sha]%?s", ptr);
}

static void
log(char *str, size_t len, void *ptr) {
  fprintf(stderr, "%.*s\n", (int)len, str);
}

dati*
init(char *username, char *token, char *repo_config)
{
  dati *d = (dati *)calloc(1, sizeof(dati));

  user_agent::init (&d->ua_data, username, token);
  config::init(&d->config, repo_config);

  d->handle.ok_cb = NULL;
  d->handle.ok_obj = NULL;
  d->handle.err_cb = log;
  d->handle.err_obj = NULL;
  d->body.start = NULL;
  d->body.size = 0;
  return d;
}

char *
get_head_commit(dati *d)
{
  char *sha = NULL;
  d->handle.ok_cb = load_object_sha;
  d->handle.ok_obj = &sha;
  user_agent::run(&d->ua_data, &d->handle, NULL,
          HTTP_GET, "/repos/%s/%s/git/refs/heads/%s",
          d->config.owner, d->config.repo, d->config.default_branch);
  return sha;
}

char *
get_tree_sha(dati *d, char *commit_sha)
{
  fprintf(stderr, "===get-tree-sha==\n");
  char *sha = NULL;
  d->handle.ok_cb = load_sha;
  d->handle.ok_obj = &sha;
  user_agent::run(&d->ua_data, &d->handle, NULL,
          HTTP_GET, "/repos/%s/%s/git/trees/%s",
          d->config.owner, d->config.repo, commit_sha);

  fprintf(stderr, "tree-sha:%s\n", sha);
  return sha;
}

void
create_blobs(dati *d, struct file **files)
{
  char *file_sha = NULL;
  d->handle.ok_cb = load_sha;
  d->handle.ok_obj = &file_sha;

  for (int i = 0; files[i]; i++) {
    fprintf(stderr, "===creating blob for %s===\n", files[i]->path);
    size_t len;
    char *content = orka_load_whole_file(files[i]->path, &len);
    d->body.size = json_asprintf(&d->body.start,
                              "{ |content|:|%.*s|, |encoding|:|utf-8| }",
                              len, content);
    fprintf(stderr, "%.*s\n", (int)d->body.size, d->body.start);
    user_agent::run(&d->ua_data, &d->handle, &d->body,
            HTTP_POST, "/repos/%s/%s/git/blobs",
            d->config.owner, d->config.repo);

    fprintf(stderr, "file-sha %s\n", file_sha);
    files[i]->sha = file_sha;
    free(d->body.start);
  }
}

static int
node2json(char *str, size_t size, void *p)
{
  struct file *f = (struct file *)p;
  return json_snprintf(str, size,
                       "{"
                         "|path|:|%s|,"
                         "|mode|:|100644|,"
                         "|type|:|blob|,"
                         "|sha|:|%s|"
                         "}", f->path, f->sha);
}

static int
node_list2json(char *buf, size_t size, void *p) {
  return ntl_to_buf(buf, size, (void **)p, NULL, node2json);
}

char *
create_tree(dati *d, char *base_tree_sha, struct file **files)
{
  fprintf(stderr, "==create-tree==\n");
  d->body.size = json_asprintf(&d->body.start,
                            "{"
                              "|tree|:%F,"
                              "|base_tree|:|%s|"
                              "}", node_list2json, files, base_tree_sha);
  char *new_tree_sha = NULL;
  d->handle.ok_cb = load_sha;
  d->handle.ok_obj = &new_tree_sha;

  fprintf(stderr, "%s\n", d->body.start);
  user_agent::run(&d->ua_data, &d->handle, &d->body,
          HTTP_POST, "/repos/%s/%s/git/trees",
          d->config.owner, d->config.repo);

  free(d->body.start);
  fprintf(stderr, "new-tree-sha:%s\n", new_tree_sha);

  return new_tree_sha;
}

char *
create_a_commit(dati *d, char *tree_sha, 
                 char *parent_commit_sha, char *commit_msg)
{
  fprintf(stderr, "===create-a-commit===\n");
  char *new_commit_sha = NULL;
  d->handle.ok_cb = load_sha;
  d->handle.ok_obj = &new_commit_sha;
  d->body.size = json_asprintf(&d->body.start,
                            "{"
                              " |message|:|%s|,"
                              " |tree|:|%s|,"
                              " |parents|: [ |%s| ]"
                            "}",
                            commit_msg, tree_sha, parent_commit_sha);
  user_agent::run(&d->ua_data, &d->handle, &d->body,
          HTTP_POST, "/repos/%s/%s/git/commits",
          d->config.owner, d->config.repo);

  free(d->body.start);
  fprintf(stderr, "commit-sha:%s\n", new_commit_sha);
  return new_commit_sha;
}

void
create_a_branch(dati *d, char *head_commit_sha, char *branch)
{
  fprintf(stderr, "===create-a-branch===\n");
  d->body.size = json_asprintf(&d->body.start, "{ |ref|: |refs/heads/%s|, |sha|:|%s| }",
                            branch, head_commit_sha);

  fprintf(stderr, "%.*s\n", (int)d->body.size, d->body.start);
  d->handle.ok_cb = log;
  d->handle.ok_obj = NULL;
  user_agent::run(&d->ua_data, &d->handle, &d->body,
          HTTP_POST, "/repos/%s/%s/git/refs",
          d->config.owner, d->config.repo);
}

void
update_a_commit(dati *d, char *branch, char *commit_sha)
{
  fprintf(stderr, "===update-a-commit===\n");
  d->handle.ok_cb = log;
  d->body.size = json_asprintf(&d->body.start, "{|sha|:|%s|}", commit_sha);
  fprintf(stderr, "PATCH: %s\n", d->body.start);
  user_agent::run(&d->ua_data, &d->handle, &d->body,
          HTTP_PATCH, "/repos/%s/%s/git/refs/heads/%s",
          d->config.owner, d->config.repo, branch);
}

void
create_a_pull_request(dati *d, char *branch, char *pull_msg) {
  // 5. create a pull request
  fprintf(stderr, "===create-a-pull-request===\n");
  d->body.size = json_asprintf(&d->body.start,
                            "{"
                              "|title|:|%s|,"
                              "|body|:|%s|,"
                              "|head|:|%s|,"
                              "|base|:|%s|"
                              "}",
                            branch, pull_msg, branch, d->config.default_branch);
  d->handle.ok_cb = log;
  user_agent::run(&d->ua_data, &d->handle, &d->body,
          HTTP_POST, "/repos/%s/%s/pulls", d->config.owner, d->config.repo);
}

} // namespace git_op
} // namespace v3
} // namespace github
