#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "discord.h"

void on_ready(struct discord *client, const struct discord_user *me) {
  fprintf(stderr, "\n\nSuccesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_on_ready(client, &on_ready);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}

