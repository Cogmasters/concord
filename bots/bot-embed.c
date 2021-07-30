#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "cee-utils.h" /* cee_timestamp_ms() */

#define JSON_FILE "bot-embed.json"


static struct discord_embed*
load_embed_from_json(char filename[])
{
  size_t len;
  char *json_payload = cee_load_whole_file(filename, &len);

  struct discord_embed *new_embed=NULL;
  discord_embed_from_json(json_payload, len, &new_embed);

  new_embed->timestamp = cee_timestamp_ms(); // get current timestamp

  free(json_payload);

  return new_embed;
}

void on_ready(struct discord *client, const struct discord_user *bot) {
  log_info("Embed-Bot succesfully connected to Discord as %s#%s!",
      bot->username, bot->discriminator);
}

void on_show(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params = {
    .content = "This is an embed",
    .embed = discord_get_data(client)
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_format(
  struct discord *client, 
  const struct discord_user *bot, 
  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_embed embed;
  discord_embed_init(&embed);

  discord_embed_set_title(&embed, "String: %s Integer: %d Scientific Notation: %E", "Test", 42, 12345678);
  discord_embed_add_field(&embed, "Field", "Value", false);

  struct discord_create_message_params params = {
    .embed = &embed
  };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_embed_cleanup(&embed);
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
  discord_set_on_command(client, "!show", &on_show);
  discord_set_on_command(client, "!format", &on_format);

  printf("\n\nThis bot demonstrates how easy it is to create a embed.\n"
         "1. Edit 'bot-embed.json' to change how the embed contents"
         " are displayed.\n"
         "2. Type '!show' in any channel to trigger the bot\n"
         "3. Type '!format' in any channel to trigger the bot\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  struct discord_embed *embed = load_embed_from_json(JSON_FILE);
  discord_set_data(client, embed);

  discord_run(client);

  discord_embed_cleanup(embed);
  free(embed);

  discord_cleanup(client);

  discord_global_cleanup();
}

