#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <libdiscord.h>


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

  discord_user_t *self = discord_user_init(); 
  assert(NULL != self);

  discord_get_client_user(client, self);
  printf("Greetings, %s#%s!\n", self->username, self->discriminator);

  discord_user_cleanup(self);

  discord_cleanup(client);

  discord_global_cleanup();
}
