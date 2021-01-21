#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>


void on_ready(discord_t *client, const discord_user_t *self)
{
  fprintf(stderr, "\n\nEcho-Bot succesfully connected to Discord as %s#%s!\n\n",
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

  discord_send_message(client, message->channel_id, message->content);
}

void on_message_update(
    discord_t *client,
    const discord_user_t *self,
    const discord_message_t *message)
{
  char text[] = "I see what you did there.";

  discord_send_message(client, message->channel_id, text);
  
  (void)self;
}

void on_message_delete(
    discord_t *client,
    const discord_user_t *self,
    const discord_message_t *message)
{
  char text[] = "Did that message just disappear?!";

  discord_send_message(client, message->channel_id, text);
  
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
  discord_setcb_message_update(client, &on_message_update);
  discord_setcb_message_delete(client, &on_message_delete);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}


