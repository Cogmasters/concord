#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libdiscord.h"


void on_ready(discord::client *client, const discord::user::dati *me) {
  fprintf(stderr, "\n\nPin-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_message_create(
    discord::client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  // make sure bot ignores msgs from other bots
  if (msg->author->bot)
    return;

  if (strstr(msg->content, "pin me")) {
    discord_add_pinned_channel_message(client, msg->channel_id, msg->id);
  }
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  discord::global_init();

  discord::client *client = discord::config_init(config_file);
  assert(NULL != client);

  discord::setcb(client, discord::READY, &on_ready);
  discord::setcb(client, discord::MESSAGE_CREATE, &on_message_create);

  discord::run(client);

  discord::cleanup(client);

  discord::global_cleanup();
}
