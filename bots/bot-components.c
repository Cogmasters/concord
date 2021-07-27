#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "cee-utils.h"

#define JSON_FILE "bot-components.json"


void on_ready(struct discord *client, const struct discord_user *bot) {
  log_info("Components-Bot succesfully connected to Discord as %s#%s!",
      bot->username, bot->discriminator);
}

void on_command(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_message *loaded_msg = discord_get_data(client);

  struct discord_create_message_params params = {
    .content = loaded_msg->content,
    .components = loaded_msg->components
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

static struct discord_message*
load_message_from_json(char filename[])
{
  size_t len;
  char *json_payload = cee_load_whole_file(filename, &len);

  struct discord_message *new_msg=NULL;
  discord_message_from_json(json_payload, len, &new_msg);

  free(json_payload);

  return new_msg;
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
  discord_set_on_command(client, "!show", &on_command);

  printf("\n\nThis bot demonstrates how easy it is to load components"
         " to your messages.\n"
         "1. Edit 'bot-components.json' to change how the message components"
         " are displayed.\n"
         "2. Type '!show' in any channel to trigger the bot\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  struct discord_message *loaded_msg = load_message_from_json(JSON_FILE);

  discord_set_data(client, loaded_msg);

  discord_run(client);

  discord_message_free(loaded_msg);
  discord_cleanup(client);

  discord_global_cleanup();
}

