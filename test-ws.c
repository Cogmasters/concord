#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <libdiscord.h>
#include "settings.h"

void on_ready(struct discord_s *client)
{
  discord_user_t *self = discord_user_init();
  assert(NULL != self);

  discord_get_client_user(client, &self);
  fprintf(stderr, "\n\nSuccesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  discord_user_cleanup(self);
}

int main(void)
{
  static struct bot_settings settings;
  bot_settings_init(&settings, "bot.config");

  discord_global_init();
  discord_t *client = discord_init(settings.discord.token);
  assert(NULL != client);

  if (settings.logging.dump_json.enable) {
    discord_dump_json(client, settings.logging.dump_json.filename);
  }

  discord_set_on_ready(client, &on_ready);

  discord_run(client);

  discord_cleanup(client);
  discord_global_cleanup();
}

