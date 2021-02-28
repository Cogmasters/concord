#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>

using namespace discord;

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nCreate-Channel-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_command(
    client *client,
    const user::dati *me,
    const channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  channel::dati *channel = channel::dati_alloc();

  guild::create_channel::params params1 = {
    .name = msg->content
  };
  guild::create_channel::run(client, msg->guild_id, &params1, channel);

  if (channel->id) {
    channel::message::create::params params2 = {
      .content = "Hello world!"
    };
    channel::message::create::run(client, channel->id, &params2, NULL);
  }

  channel::dati_free(channel);
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

  setcb(client, COMMAND, &on_command, "!createChannel ");

  printf("\n\nThis bot demonstrates how easy it is to create/delete channels\n"
         "1. Type '!createChannel <channel_name>' anywhere to create a new channel\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  run(client);

  cleanup(client);

  global_cleanup();
}


