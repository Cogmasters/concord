#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "slack.h"

#if 0
void on_ready(struct slack *client, const struct slack_user *me) {
  fprintf(stderr, "\n\nSuccesfully connected to Slack as %s#%s!\n\n",
      me->username, me->discriminator);
}
#endif

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";


  struct slack *client = slack_config_init(config_file);
  assert(NULL != client);
#if 0
  slack_on_ready(client, &on_ready);
#endif

  slack_run(client);

  slack_cleanup(client);
}

