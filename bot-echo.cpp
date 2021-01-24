#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>


using namespace discord;

void on_ready(discord::client *client, const user::data *self)
{
  fprintf(stderr, "\n\nEcho-Bot succesfully connected to Discord as %s#%s!\n\n",
      self->username, self->discriminator);

  (void)client;
}

void on_message_create(
    discord::client *client,
    const user::data *self,
    const message::data *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;
  // make sure it doesn't echoes itself
  if (0 == strcmp(self->username, msg->author->username))
    return;

  message::create(client, msg->channel_id, msg->content);
}

void on_message_update(
    discord::client *client,
    const user::data *self,
    const message::data *msg)
{
  char text[] = "I see what you did there.";

  message::create(client, msg->channel_id, text);
  
  (void)self;
}

void on_message_delete(
    discord::client *client,
    const user::data *self,
    const message::data *msg)
{
  char text[] = "Did that message just disappear?!";

  message::create(client, msg->channel_id, text);
  
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

  discord::client *client = fast_init(config_file);
  assert(NULL != client);

  setcb_ready(client, &on_ready);
  setcb_message_create(client, &on_message_create);
  setcb_message_update(client, &on_message_update);
  setcb_message_delete(client, &on_message_delete);

  run(client);

  cleanup(client);

  global_cleanup();
}


