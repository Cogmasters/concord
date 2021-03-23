#ifndef GITHUB_V3_HPP
#define GITHUB_V3_HPP

#include "github-v3-user-agent.h"

struct github_v3_git_op_dati; // forward declaration

struct github_v3_git_op_file {
  char *path;
  char *sha;
};

struct github_v3_git_op_dati* 
github_v3_git_op_init(char *username, char *token, char *repo_config);

char * github_v3_git_op_update_my_fork(struct github_v3_git_op_dati *d);
char* github_v3_git_op_get_head_commit(struct github_v3_git_op_dati *data);
char* github_v3_git_op_get_tree_sha(struct github_v3_git_op_dati *data, char *commit_sha);
void github_v3_git_op_create_blobs(struct github_v3_git_op_dati *data, struct github_v3_git_op_file **files);
char* github_v3_git_op_create_tree(struct github_v3_git_op_dati *data, char *base_tree_sha, struct github_v3_git_op_file **files);
char* github_v3_git_op_create_a_commit(struct github_v3_git_op_dati *data, char *tree_sha, char *parent_commit_sha, char *commit_msg);
void github_v3_git_op_create_a_branch(struct github_v3_git_op_dati *data, char *head_commit_sha, char *branch);
void github_v3_git_op_update_a_commit(struct github_v3_git_op_dati *d, char *branch, char *commit_sha);
void github_v3_git_op_create_a_pull_request(struct github_v3_git_op_dati *d, char *branch, char *pull_msg);

#endif // GITHUB_V3_HPP
