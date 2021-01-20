#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>


void on_ready(discord_t *client, const discord_user_t *self)
{
  fprintf(stderr, "\n\nPingPong-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_message_create(
    discord_t *client,
    const discord_user_t *self,
    const discord_message_t *message)
{
  // make sure bot doesn't echoes other bots
  if (message->author->bot)
    return;
  // make sure it doesn't echoes itself
  if (0 == strcmp(self->username, message->author->username))
    return;

  if (0 == strcmp(message->content, "ping"))
    discord_send_message(client, message->channel_id, "pong");
  else if (0 == strcmp(message->content, "pong"))
    discord_send_message(client, message->channel_id, "ping");

  (void)self;
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
