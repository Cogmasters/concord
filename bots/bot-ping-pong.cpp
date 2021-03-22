#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "libdiscord.h"


void on_ready(discord::client *client, const discord::user::dati *me) {
  fprintf(stderr, "\n\nPingPong-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_ping(
  discord::client *client,
  const discord::user::dati *me,
  const discord::channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord::channel::create_message::params params = {.content = "pong"};
  discord::channel::create_message::run(client, msg->channel_id, &params, NULL);
}

void on_pong(
    discord::client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord::channel::create_message::params params = {.content = "ping"};
  discord::channel::create_message::run(client, msg->channel_id, &params, NULL);
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
  discord::setcb_command(client, "ping", &on_ping);
  discord::setcb_command(client, "pong", &on_pong);

  discord::run(client);

  discord::cleanup(client);

  discord::global_cleanup();
}
