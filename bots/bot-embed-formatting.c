#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "discord.h"
#include "cee-utils.h"

void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nEmbed-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void on_command(struct discord *client, const struct discord_user *bot, const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_embed *embed = discord_embed_alloc();
  discord_embed_set_title(embed, "String: %s Integer: %d Scientific Notation: %E", "Test", 42, 12345678);
  discord_embed_add_field(embed, "Field", "Value", false);

  struct discord_create_message_params params = {
    .embed = embed
  };

  discord_create_message(client, msg->channel_id, &params, NULL);
  discord_embed_free(embed);
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
  discord_set_on_command(client, "format embed", &on_command);

  printf("\n\nThis bot demonstrates how easy it is to format the title text for embeds.\n"
         "Type 'format embed' in any channel to trigger the bot\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin);

  discord_run(client);
  discord_cleanup(client);
  discord_global_cleanup();
}

