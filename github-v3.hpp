#ifndef GITHUB_V3_HPP
#define GITHUB_V3_HPP
#include "github-v3-user-agent.hpp"


namespace github {
namespace v3 {
namespace git_op { // high-level function
struct dati;

struct file {
  char * path;
  char * sha;
};

dati * init (char * username, char * token, char * repo_config);
char * get_head_commit (dati * data);
char * get_tree_sha(dati * data, char * commit_sha);
void create_blobs (dati * data, struct file ** files);
char * create_tree (dati * data, char * base_tree_sha, struct file ** files);
char * create_a_commit (dati * data, char * tree_sha,
                        char * parent_commit_sha, char * message);
void create_a_branch (dati * data, char * head_commit_sha, char * branch);
void update_a_commit (dati * d, char * branch, char * commit_sha);
void create_a_pull_request (dati * d, char * branch);

} // git_op
} // v3
} // github

#endif //GITHUB_V3_HPP
