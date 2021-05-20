#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* SCNu64 */
#include <assert.h>

#include "discord.h"


void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nDelete-Reaction-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
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

void on_delete_self(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{ 
  if (msg->author->bot || !msg->referenced_message) return;

  discord_delete_own_reaction(
      client, 
      msg->referenced_message->channel_id, 
      msg->referenced_message->id,
      0,
      msg->content);
}

void on_delete_user(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{ 
  if (msg->author->bot || !msg->referenced_message) return;

  u64_snowflake_t user_id=0;
  char emoji_name[256]="";
  sscanf(msg->content, "%"SCNu64" %s", &user_id, emoji_name);

  discord_delete_user_reaction(
      client, 
      msg->referenced_message->channel_id, 
      msg->referenced_message->id,
      user_id,
      0,
      emoji_name);
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
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_ready(client, &on_ready);
  discord_set_prefix(client, "delete.");
  discord_set_on_command(client, "emoji", &on_delete_emoji);
  discord_set_on_command(client, "all", &on_delete_all);
  discord_set_on_command(client, "self", &on_delete_self);
  discord_set_on_command(client, "user", &on_delete_user);

  printf("\n\nThis bot demonstrates how easy it is to delete reactions"
         " from a message.\n"
         "1. Reply to a message with delete.all to delete all reactions\n"
         "2. Reply to a message with delete.emoji <emoji> to delete all reactions with a particular emoji\n"
         "3. Reply to a message with delete.self <emoji> to delete your reaction with a particular emoji\n"
         "4. Reply to a message with delete.user <user_id> <emoji> to delete the user reaction with a particular emoji\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}


