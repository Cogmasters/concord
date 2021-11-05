/*
 * A bot that creates gists with a title, description, and body.
 */

#include <stdio.h>
#include "github.h"

void print_usage()
{
  printf("bot-github-gist - create gists from the terminal\n");
  printf("Usage: bot-github-gist.exe <title> <description> <body>\n\n");
  printf("Parameters:\n");
  printf("    title           the title of the gist\n");
  printf("    description     the description of the gist\n");
  printf("    body            the body of the gist\n");
}

int main(int argc, char *argv[])
{
  struct github *client = github_config_init("../config.json", NULL);

  if (argc == 1) {
    print_usage();
    exit(1);
  }
  else if (argc < 4) {
    printf(
      "bot-github-gist expects 3 arguments. title, description, and body\n");
    exit(1);
  }

  struct github_gist gist_info;
  struct github_gist_create_params params = { .title = argv[1],
                                              .description = argv[2],
                                              .contents = argv[3],
                                              .public = "false" };

  github_create_gist(client, &params, &gist_info);
  printf("Created gist \"%s\" at URL: %s\n", argv[1], gist_info.html_url);

  return 0;
}
