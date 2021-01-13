#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <libdiscord.h>
#include "settings.h"

int main(int argc, char *argv[])
{
  static struct bot_settings settings;

  if (argc > 1)
    bot_settings_init(&settings, argv[1]);
  else
    bot_settings_init(&settings, "bot.config");

  discord_global_init();
  discord_t *client = discord_init(settings.discord.token);
  assert(NULL != client);

  discord_user_t *self = discord_user_init(); 
  assert(NULL != self);

  discord_get_client_user(client, self);
  printf("Greetings, %s#%s!\n", self->username, self->discriminator);

  discord_user_cleanup(self);

  discord_cleanup(client);
  discord_global_cleanup();
}
