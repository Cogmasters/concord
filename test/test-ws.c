#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <libdiscord.h>

void on_ready(struct discord_client *client, const struct discord_user_dati *me) {
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

  struct discord_client *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_setcb(client, READY, &on_ready);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}

