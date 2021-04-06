#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"



void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nCreate-Channel-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void on_channel_create(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_channel *channel)
{
  struct discord_create_message_params params = { .content = "Hello world!" };
  discord_create_message(client, channel->id, &params, NULL);
}

void on_channel_update(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_channel *channel)
{
  struct discord_create_message_params params = { .content = "Succesfully updated channel!" };
  discord_create_message(client, channel->id, &params, NULL);
}

void on_channel_delete(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_channel *channel)
{
  struct discord_channel *general = discord_channel_alloc();
  discord_get_channel_at_pos(client, channel->guild_id, DISCORD_CHANNEL_GUILD_TEXT, 0, general);

  char text[150];
  snprintf(text, sizeof(text), "Succesfully deleted `%s` channel", channel->name);
  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, general->id, &params, NULL);
  discord_channel_free(general);
}

void on_create(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  struct discord_create_guild_channel_params params = {
    .name = msg->content
  };
  discord_create_guild_channel(client, msg->guild_id, &params, NULL);
}

void on_delete(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
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

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_set_prefix(client, "!channel");
  discord_on_command(client, "Create", &on_create);
  discord_on_command(client, "DeleteHere", &on_delete);
  discord_on_channel_create(client, &on_channel_create);
  discord_on_channel_update(client, &on_channel_update);
  discord_on_channel_delete(client, &on_channel_delete);

  printf("\n\nThis bot demonstrates how easy it is to create/delete channels\n"
         "1. Type '!channelCreate <channel_name>' anywhere to create a new channel\n"
         "2. (USE WITH CAUTION) Type '!channelDeleteHere' to delete the current channel\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
