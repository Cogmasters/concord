#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "debug.h"

char *SPAM[] = {
  "Yes I love to spam", // 1
  "Do you?", // 2
  "ROFL", // 3
  "What are you going to do about it?", // 4
  "Are you going to !clear me?", // 5
  "Good luck with that.", // 6
  "Many have tried but..", // 7
  "They all fail.", // 8
  "What makes you think", // 9
  "It should be any different with you?" // 10
};

void on_spam(struct discord *client,
             const struct discord_user *bot,
             const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params = {};
  for (size_t i = 0; i < 10; ++i) {
    params.content = SPAM[i];
    discord_create_message(client, msg->channel_id, &params, NULL);
  }
}

void on_clear(struct discord *client,
              const struct discord_user *bot,
              const struct discord_message *msg)
{
  if (msg->author->bot) return;

  discord_delete_messages_by_author_id(client, msg->channel_id, bot->id);
  struct discord_create_message_params params = {
    .content = "Deleted 100 messages or less"
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_command(client, "!spam", &on_spam);
  discord_set_on_command(client, "!clear", &on_clear);

  printf("\n\nThis bot demonstrates how easy it is to delete"
         " messages.\n"
         "1. Type !spam to spam 10 random messages in chat\n"
         "2. Type !clear to delete spam messages\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);
  discord_global_cleanup();
}
