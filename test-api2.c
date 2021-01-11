#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <libdiscord.h>
#include "settings.h"

int main(void)
{
  printf ("main\n");
  static struct bot_settings settings;
  bot_settings_init("bot.config", &settings);

  discord_global_init();
  discord_t *client = discord_init(settings.discord.token);
  assert(NULL != client);

  discord_user_t *self = discord_user_init(); 
  assert(NULL != self);

  discord_get_client_user(client, &self);
  printf("Greetings, %s#%s!\n", self->username, self->discriminator);

  discord_user_cleanup(self);

  discord_cleanup(client);
  discord_global_cleanup();
}
