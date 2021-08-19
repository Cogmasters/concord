/*
 * A bot that retrieves public information about a GitHub user.
*/

#include <stdio.h>
#include <orca/github.h>

void print_usage() {
  printf("bot-github-user.c - retrieve some information about a github user through their username\n\n");
  printf("parameters:\n");
  printf("  username - the username to lookup:\n");
  exit(1);
}

void print_too_many() {
  printf("bot-github-user.c only accepts one username.\n");
  exit(1);
}

int main(int argc, char *argv[]) {
  if(argc == 0) {
    print_usage();
  }
  else if(argc > 2) {
    print_too_many();
  }

  struct github *client = github_config_init("bot.config", NULL);
  struct github_user user = {0};

  github_get_user(client, &user, argv[1]);

  printf("Information for '%s'\n", argv[1]);
  printf("Login: %s\n", user.login);
  printf("Biography: %s\n", user.bio);
  printf("Followers: %i\n", user.followers);
  printf("Following: %i\n", user.following);

  return 0;
}

