#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libdiscord.h"



void on_ready(discord::client *client, const discord::user::dati *me) {
  fprintf(stderr, "\n\nCreate-Channel-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_create(
    discord::client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord::channel::dati *channel = discord::channel::dati_alloc();

  discord::guild::create_channel::params params1 = {
    .name = msg->content
  };
  discord::guild::create_channel::run(client, msg->guild_id, &params1, channel);

  if (channel->id) {
    discord::channel::create_message::params params2 = {
      .content = "Hello world!"
    };
    discord::channel::create_message::run(client, channel->id, &params2, NULL);
  }

  discord::channel::dati_free(channel);
}

void on_delete(
    discord::client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord::channel::delete_channel::run(client, msg->channel_id, NULL);
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

  discord::set_prefix(client, "!channel");
  discord::setcb_command(client, "Create", &on_create);
  discord::setcb_command(client, "DeleteHere", &on_delete);

  printf("\n\nThis bot demonstrates how easy it is to create/delete channels\n"
         "1. Type '!channelCreate <channel_name>' anywhere to create a new channel\n"
         "2. (USE WITH CAUTION) Type '!channelDeleteHere' to delete the current channel\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord::run(client);

  discord::cleanup(client);

  discord::global_cleanup();
}
