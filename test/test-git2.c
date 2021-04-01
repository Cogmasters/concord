#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

#include "github.h"
#include "orka-utils.h"
#include "orka-config.h"


static
void print_usage (char * prog)
{
  fprintf(stderr, "Usage: %s [-c config] [-m <commit-message>] file file ...\n",
          prog);
  exit(EXIT_FAILURE);
}

int main (int argc, char ** argv)
{
  int opt;
  char * commit_msg = NULL, * config_file = NULL;

  while ((opt = getopt(argc, argv, "c:m:")) != -1) {
    switch (opt) {
      case 'c':
        config_file = strdup(optarg);
        break;
      case 'm':
        commit_msg = strdup(optarg);
        break;
      default: /* '?' */
        print_usage(argv[0]);
    }
  }

  if (NULL == config_file) {
    fprintf(stderr, "Using .cee-contributor as the user config\n");
    config_file = ".cee-contributor";
  }
  else if (NULL == commit_msg) {
    fprintf(stderr, "Please specify: -m \"commit message\"\n");
    exit(EXIT_FAILURE);
  }
  else if (optind >= argc) {
    fprintf(stderr, "Expected files\n");
    exit(EXIT_FAILURE);
  }


  struct github_git_op_file ** files = NULL;
  files = (struct github_git_op_file**)ntl_calloc(argc-optind, sizeof(struct github_git_op_file));
  for (int i = 0; files[i]; ++i)
    files[i]->path = argv[optind + i];

  curl_global_init(CURL_GLOBAL_ALL);

  struct orka_config config;
  memset(&config, 0, sizeof(config));
  orka_config_init(&config, NULL, config_file);
  char *username = orka_config_get_field(&config, "github.username");
  char *token = orka_config_get_field(&config, "github.token");

  struct github_git_op *data = github_git_op_init(username, token, ".cee-repo");

  github_git_op_update_my_fork(data);
  github_git_op_create_blobs(data, files);
  char * head_commit_sha = github_git_op_get_head_commit(data);
  char * base_tree_sha = github_git_op_get_tree_sha(data, head_commit_sha);
  char * tree_sha = github_git_op_create_tree(data, base_tree_sha, files);
  char * commit_sha =
    github_git_op_create_a_commit(data, tree_sha, head_commit_sha, commit_msg);

  char new_branch[256];
  snprintf(new_branch, sizeof(new_branch), "n%ld", time(NULL));
  github_git_op_create_a_branch(data, head_commit_sha, new_branch);
  github_git_op_update_a_commit(data, new_branch, commit_sha);
  github_git_op_create_a_pull_request(data, new_branch, commit_msg);
  return 0;
}
