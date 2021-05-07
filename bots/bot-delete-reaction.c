#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"


void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nDelete-Reaction-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void on_delete_all(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{ 
  if (msg->author->bot || !msg->referenced_message) return;

  discord_delete_all_reactions(
      client, 
      msg->referenced_message->channel_id, 
      msg->referenced_message->id);
}

void on_delete_emoji(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{ 
  if (msg->author->bot || !msg->referenced_message) return;

  discord_delete_all_reactions_for_emoji(
      client, 
      msg->referenced_message->channel_id, 
      msg->referenced_message->id, 
      0, 
      msg->content);
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

  discord_set_on_ready(client, &on_ready);
  discord_set_on_command(client, "!deleteAll", &on_delete_all);
  discord_set_on_command(client, "!deleteEmoji", &on_delete_emoji);

  printf("\n\nThis bot demonstrates how easy it is to delete reactions"
         " from a message.\n"
         "1. Reply to a message with !deleteAll to delete all reactions\n"
         "2. Reply to a message with !deleteEmoji <emoji> to delete all reactions from a particular emoji\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}


