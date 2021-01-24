#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

void on_ready(discord_t *client, const user::data *self)
{
  fprintf(stderr, "\n\nPin-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_message_create(
    discord_t *client,
    const user::data *self,
    const message::data *msg)
{
  // make sure bot ignores msgs from other bots
  if (msg->author->bot)
    return;
  // make sure it ignores itself
  if (0 == strcmp(self->username, msg->author->username))
    return;

  if (strstr(msg->content, "pin me")) 
    channel::pin_message(client, msg->channel_id, msg->id);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  global_init();

  discord_t *client = fast_init(config_file);
  assert(NULL != client);

  setcb_ready(client, &on_ready);
  setcb_message_create(client, &on_message_create);

  run(client);

  cleanup(client);

  global_cleanup();
}



