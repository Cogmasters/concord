#ifndef GITHUB_V3_H
#define GITHUB_V3_H

#include "github-v3-adapter.h"


struct github_v3_git_op_file {
  char *path;
  char *sha;
};

struct github_v3_git_op* 
github_v3_git_op_init(char *username, char *token, char *repo_config);

char * github_v3_git_op_update_my_fork(struct github_v3_git_op *d);
char* github_v3_git_op_get_head_commit(struct github_v3_git_op *data);
char* github_v3_git_op_get_tree_sha(struct github_v3_git_op *data, char *commit_sha);
void github_v3_git_op_create_blobs(struct github_v3_git_op *data, struct github_v3_git_op_file **files);
char* github_v3_git_op_create_tree(struct github_v3_git_op *data, char *base_tree_sha, struct github_v3_git_op_file **files);
char* github_v3_git_op_create_a_commit(struct github_v3_git_op *data, char *tree_sha, char *parent_commit_sha, char *commit_msg);
void github_v3_git_op_create_a_branch(struct github_v3_git_op *data, char *head_commit_sha, char *branch);
void github_v3_git_op_update_a_commit(struct github_v3_git_op *d, char *branch, char *commit_sha);
void github_v3_git_op_create_a_pull_request(struct github_v3_git_op *d, char *branch, char *pull_msg);

#endif // GITHUB_V3_H
