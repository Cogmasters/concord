#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

#include "github.h"
#include "cee-utils.h"

static void print_usage(char *prog)
{
  fprintf(stderr,
          "Usage: %s [-c config] [-m <commit-message>] file file ...\n", prog);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
  int opt;
  char *commit_msg = NULL, *config_file = NULL;

  while ((opt = getopt(argc, argv, "c:m:")) != -1) {
    switch (opt) {
    case 'c': config_file = strdup(optarg); break;
    case 'm': commit_msg = strdup(optarg); break;
    default: /* '?' */ print_usage(argv[0]);
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

  ORCAcode code;
  NTL_T(struct github_file)
  files = (void *)ntl_calloc(argc - optind, sizeof(struct github_file));
  for (int i = 0; files[i]; ++i)
    files[i]->path = argv[optind + i];

  curl_global_init(CURL_GLOBAL_ALL);
  struct github *client = github_config_init(config_file, ".cee-repo");

  code = github_update_my_fork(client, NULL);
  if (code != ORCA_OK) return EXIT_FAILURE;

  code = github_create_blobs(client, files);
  if (code != ORCA_OK) return EXIT_FAILURE;

  char *head_commit_sha = NULL, *base_tree_sha = NULL, *tree_sha = NULL,
       *commit_sha = NULL;
  code = github_get_head_commit(client, &head_commit_sha);
  if (code != ORCA_OK) return EXIT_FAILURE;
  code = github_get_tree_sha(client, head_commit_sha, &base_tree_sha);
  if (code != ORCA_OK) return EXIT_FAILURE;
  code = github_create_tree(client, base_tree_sha, files, &tree_sha);
  if (code != ORCA_OK) return EXIT_FAILURE;
  code = github_create_a_commit(client, tree_sha, head_commit_sha, commit_msg,
                                &commit_sha);
  if (code != ORCA_OK) return EXIT_FAILURE;

  char new_branch[256];
  snprintf(new_branch, sizeof(new_branch), "n%ld", time(NULL));
  code = github_create_a_branch(client, head_commit_sha, new_branch);
  if (code != ORCA_OK) return EXIT_FAILURE;
  code = github_update_a_commit(client, new_branch, commit_sha);
  if (code != ORCA_OK) return EXIT_FAILURE;
  code = github_create_a_pull_request(client, new_branch, commit_msg);
  if (code != ORCA_OK) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
