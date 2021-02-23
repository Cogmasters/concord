#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nPingPong-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_message_create(
    client *client,
    const user::dati *me,
    const channel::message::dati *msg)
{
  using namespace channel;

  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  message::create::params params = {0};
  if (0 == strcmp(msg->content, "ping"))
    params.content = "pong";
  else if (0 == strcmp(msg->content, "pong"))
    params.content = "ping";
  else
    return; //nothing to do here

  message::create::run(client, msg->channel_id, &params, NULL);

  (void)me;
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

  setcb(client, READY, &on_ready);
  setcb(client, MESSAGE_CREATE, &on_message_create);

  run(client);

  cleanup(client);

  global_cleanup();
}
