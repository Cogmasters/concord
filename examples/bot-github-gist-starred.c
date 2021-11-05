/*
 * A bot to check if a gist is starred
 */

#include <stdio.h>
#include <stdlib.h>
#include "github.h"

void print_usage()
{
  printf("bot-github-gist-starred - a bot to check if a gist is starred\n");
  printf("\nPositional arguments:\n");
  printf("    gist_id     the id of the gist to check\n");
  exit(0);
}

int main(int argc, char *argv[])
{
  if (argc == 1) {
    print_usage();
  }
  else if (argc > 2) {
    printf("bot-github-gist-starred: too many parameters");
  }

  struct github *client = github_config_init("../config.json", NULL);
  int is_starred = github_gist_is_starred(client, argv[1]);

  if (is_starred == ORCA_OK) {
    printf("'%s' is starred.\n", argv[1]);
  }
  else if (is_starred == ORCA_GITHUB_NOT_STARRED) {
    printf("'%s' is not starred.\n", argv[1]);
  }
  else {
    printf("Error occured for gist '%s', with status code: %i.\n", argv[1],
           is_starred);
  }
}
