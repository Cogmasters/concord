#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <libdiscord.h>


void on_ready(discord_t *client, const discord_user_t *self)
{
  fprintf(stderr, "\n\nSuccesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  discord_global_init();

  discord_t *client = discord_fast_init(config_file);
  assert(NULL != client);

  discord_setcb_ready(client, &on_ready);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}

