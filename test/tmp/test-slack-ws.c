#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "slack.h"

void on_hello(struct slack *client, char *text, size_t len) {
  fputs("\n\nSuccesfully connected to Slack!\n\n", stderr);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";


  struct slack *client = slack_config_init(config_file);
  assert(NULL != client);

  slack_set_on_hello(client, &on_hello);

  slack_rtm_run(client);

  slack_cleanup(client);
}

