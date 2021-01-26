#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

void on_ready(client *client, const user::data *me)
{
  fprintf(stderr, "\n\nPingPong-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_message_create(
    client *client,
    const user::data *me,
    const message::data *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;
  // make sure it doesn't echoes itme
  if (0 == strcmp(me->username, msg->author->username))
    return;

  message::create::params params = {0};
  if (0 == strcmp(msg->content, "ping"))
    params.content = "pong";
  else if (0 == strcmp(msg->content, "pong"))
    params.content = "ping";
  else
    return; //nothing to do here

  message::create::run(client, msg->channel_id, &params);

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

  setcb_ready(client, &on_ready);
  setcb_message_create(client, &on_message_create);

  run(client);

  cleanup(client);

  global_cleanup();
}
