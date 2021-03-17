#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libdiscord.h"

using namespace discord;

void on_ready(client *client, const user::dati *me) {
  fprintf(stderr, "\n\nPin-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_message_create(
    client *client,
    const user::dati *me,
    const channel::message::dati *msg)
{
  // make sure bot ignores msgs from other bots
  if (msg->author->bot)
    return;

  if (strstr(msg->content, "pin me")) {
    channel::add_pinned_channel_message::run(client, msg->channel_id, msg->id);
  }
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  global_init();

  client *client = config_init(config_file);
  assert(NULL != client);

  setcb(client, READY, &on_ready);
  setcb(client, MESSAGE_CREATE, &on_message_create);

  run(client);

  cleanup(client);

  global_cleanup();
}
