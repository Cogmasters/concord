/*
 * A bot that can create a fork of a repository.
 */

#include <stdio.h>
#include "github.h"

void print_usage()
{
  printf("bot-github-create-fork - create forks of a repository from the "
         "terminal\n");
  printf("Usage: bot-github-create-fork.exe <owner> <repo> \n\n");
  printf("Parameters:\n");
  printf("    owner           the owner of the repository\n");
  printf("    repo            the name of the repository\n");
}

int main(int argc, char *argv[])
{
  struct github *client = github_config_init("../config.json", NULL);

  if (argc == 1) {
    print_usage();
    exit(1);
  }
  else if (argc < 3) {
    printf("bot-github-create-fork expects 2 arguments. owner, and repo\n");
    exit(1);
  }

  ORCAcode success = github_create_fork(client, argv[1], argv[2]);

  if (success == 0) {
    printf("Successfully created fork!");
  }

  return 0;
}
