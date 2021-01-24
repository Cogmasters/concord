#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

void on_ready(client *client, const user::data *self)
{
  fprintf(stderr, "\n\nPingPong-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_message_create(
    client *client,
    const user::data *self,
    const message::data *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;
  // make sure it doesn't echoes itself
  if (0 == strcmp(self->username, msg->author->username))
    return;

  if (0 == strcmp(msg->content, "ping"))
    message::create(client, msg->channel_id, "pong");
  else if (0 == strcmp(msg->content, "pong"))
    message::create(client, msg->channel_id, "ping");

  (void)self;
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  global_init();

  client *client = fast_init(config_file);
  assert(NULL != client);

  setcb_ready(client, &on_ready);
  setcb_message_create(client, &on_message_create);

  run(client);

  cleanup(client);

  global_cleanup();
}
