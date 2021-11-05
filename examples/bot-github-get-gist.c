/*
 * A bot to get information about a gist
 */

#include <stdio.h>
#include <stdlib.h>
#include "github.h"

void print_usage()
{
  printf("bot-github-get-gist - a bot to get information about a gist\n");
  printf("\nPositional arguments:\n");
  printf("    gist_id     the id of the gist to retrieve\n");
  exit(0);
}

int main(int argc, char *argv[])
{
  if (argc == 1) {
    print_usage();
  }
  else if (argc > 2) {
    printf("bot-github-get-gist: too many parameters");
  }

  struct github *client = github_config_init("../config.json", NULL);
  struct github_gist gist;

  github_get_gist(client, argv[1], &gist);

  printf("Gist Id: %s\n", gist.id);
  printf("Gist Description: %s\n", gist.description);
  printf("Gist Comments: %i\n", gist.comments);
}
