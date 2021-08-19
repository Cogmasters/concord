#ifndef GITHUB_V3_H
#define GITHUB_V3_H

#include <stdbool.h>
#include "json-actor-boxed.h"
#include "types.h"
#include "logconf.h"

#include "specs-code/github/all_opaque_struct.h"
#include "specs-code/github/all_enums.h"
#include "specs-code/github/all_structs.h"
#include "specs-code/github/all_functions.h"

struct github_file {
  char *path;
  char *sha;
};

struct github* github_init(const char username[], const char token[], const char repo_config[]);
struct github* github_config_init(const char config_file[], const char repo_config[]);

ORCAcode github_update_my_fork(struct github *client, char **p_sha);
ORCAcode github_get_head_commit(struct github *client, char **p_sha);
ORCAcode github_get_tree_sha(struct github *client, char *commit_sha, char **p_sha);
ORCAcode github_create_blobs(struct github *client, NTL_T(struct github_file) files);
ORCAcode github_create_tree(struct github *client, char *base_tree_sha, NTL_T(struct github_file) files, char **p_tree_sha);
ORCAcode github_create_a_commit(struct github *client, char *tree_sha, char *parent_commit_sha, char *commit_msg, char **p_commit_sha);
ORCAcode github_create_a_branch(struct github *client, char *head_commit_sha, char *branch);
ORCAcode github_update_a_commit(struct github *client, char *branch, char *commit_sha);
ORCAcode github_create_a_pull_request(struct github *client, char *branch, char *pull_msg);
ORCAcode github_get_user(struct github *client, struct github_user* user, char *username);
ORCAcode github_fill_repo_config(struct github *client, char *repo_config);

#endif // GITHUB_V3_H
