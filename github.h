#ifndef GITHUB_H
#define GITHUB_H

#include <stdbool.h>
#include "json-actor-boxed.h"
#include "types.h"
#include "logconf.h"

#include "specs-code/github/one-specs.h"

/* This limit is fairly arbitrary, find the maximum at a later time. */
#define GITHUB_MAXIMUM_REPO_TOPICS 30

struct github_file {
  char *path;
  char *sha;
};

struct github *github_init(const char username[],
                           const char token[],
                           const char repo_config[]);
struct github *github_config_init(const char config_file[],
                                  const char repo_config[]);
void github_write_json(char *json, size_t len, void *user_obj);

ORCAcode github_create_fork(struct github *client, char *owner, char *repo);
ORCAcode github_update_my_fork(struct github *client, char **p_sha);
ORCAcode github_get_head_commit(struct github *client, char **p_sha);
ORCAcode github_get_tree_sha(struct github *client,
                             char *commit_sha,
                             char **p_sha);
ORCAcode github_create_blobs(struct github *client,
                             NTL_T(struct github_file) files);
ORCAcode github_create_tree(struct github *client,
                            char *base_tree_sha,
                            NTL_T(struct github_file) files,
                            char **p_tree_sha);
ORCAcode github_create_a_commit(struct github *client,
                                char *tree_sha,
                                char *parent_commit_sha,
                                char *commit_msg,
                                char **p_commit_sha);
ORCAcode github_create_a_branch(struct github *client,
                                char *head_commit_sha,
                                char *branch);
ORCAcode github_update_a_commit(struct github *client,
                                char *branch,
                                char *commit_sha);
ORCAcode github_create_a_pull_request(struct github *client,
                                      char *branch,
                                      char *pull_msg);
ORCAcode github_get_user(struct github *client,
                         char *username,
                         struct github_user *user);
ORCAcode github_fill_repo_config(struct github *client, char *repo_config);
ORCAcode github_get_repository(struct github *client,
                               char *owner,
                               char *repo,
                               struct sized_buffer *output);

ORCAcode github_get_gist(struct github *client,
                         char *id,
                         struct github_gist *gist);
ORCAcode github_create_gist(struct github *client,
                            struct github_gist_create_params *params,
                            struct github_gist *gist);
ORCAcode github_gist_is_starred(struct github *client, char *id);

ORCAcode github_get_repository_topics(struct github *client,
                                      char *owner,
                                      char *repository);

/* GITHUB_H */
#endif
