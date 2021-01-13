#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>
#include "settings.h"


void on_ready(discord_t *client, discord_user_t *self)
{
  fprintf(stderr, "\n\nEcho-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_message(
    discord_t *client,
    discord_user_t *self,
    discord_message_t *message)
{
  // make sure it doesn't echoes itself
  if (strcmp(self->username, message->author->username)){
    discord_send_message(client, message->channel_id, message->content);
  }
}

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

  if (settings.logging.dump_json.enable) {
    discord_dump_json(client, settings.logging.dump_json.filename);
  }

  discord_set_on_ready(client, &on_ready);
  discord_set_on_message(client, &on_message);

  discord_run(client);

  discord_cleanup(client);
  discord_global_cleanup();
}


