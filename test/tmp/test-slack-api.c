#include <stdio.h>
#include <stdlib.h>

#include "slack.h"


int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct slack *client = slack_config_init(config_file);

  slack_rtm_connect(client); 

  slack_cleanup(client);
}
