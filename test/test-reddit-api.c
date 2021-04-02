#include <stdio.h>
#include <stdlib.h>

#include "reddit.h"


int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  struct reddit *client = reddit_config_init(config_file);

  reddit_access_token(client); 

  reddit_cleanup(client);
}
