#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libdiscord.h"



void on_ready(struct discord_client *client, const struct discord_user_dati *me) {
  fprintf(stderr, "\n\nCreate-Channel-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_create(
    struct discord_client *client,
    const struct discord_user_dati *me,
    const struct discord_channel_message_dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  struct discord_channel_dati *channel = discord_channel_dati_alloc();

  struct discord_guild_create_channel_params params1 = {
    .name = msg->content
  };
  discord_create_channel(client, msg->guild_id, &params1, channel);

  if (channel->id) {
    struct discord_channel_create_message_params params2 = {
      .content = "Hello world!"
    };
    discord_create_message(client, channel->id, &params2, NULL);
  }

  discord_channel_dati_free(channel);
}

void on_delete(
    struct discord_client *client,
    const struct discord_user_dati *me,
    const struct discord_channel_message_dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord_delete_channel(client, msg->channel_id, NULL);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  discord_global_init();

  struct discord_client *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_set_prefix(client, "!channel");
  discord_setcb_command(client, "Create", &on_create);
  discord_setcb_command(client, "DeleteHere", &on_delete);

  printf("\n\nThis bot demonstrates how easy it is to create/delete channels\n"
         "1. Type '!channelCreate <channel_name>' anywhere to create a new channel\n"
         "2. (USE WITH CAUTION) Type '!channelDeleteHere' to delete the current channel\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
