#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>


void on_ready(discord_t *client, const discord_user_t *self)
{
  fprintf(stderr, "\n\nPin-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_message_create(
    discord_t *client,
    const discord_user_t *self,
    const discord_message_t *message)
{
  // make sure bot ignores msgs from other bots
  if (message->author->bot)
    return;
  // make sure it ignores itself
  if (0 == strcmp(self->username, message->author->username))
    return;

  if (strstr(message->content, "pin me")) 
    discord_pin_message(client, message->channel_id, message->id);
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
  discord_setcb_message_create(client, &on_message_create);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}



