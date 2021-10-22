/*
 * Examples on how to use guild templates.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"
#include "cee-utils.h" // for cee_timestamp_ms()


void on_ready(struct discord *client, const struct discord_user *bot) {
  log_info("Guild-Bot succesfully connected to Discord as %s#%s!",
      bot->username, bot->discriminator);
}

void on_bot_get_guild_template(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *message)
{
    char message_buffer[8001];

    struct discord_message p_message;
    struct discord_guild_template template;
    ORCAcode response = discord_get_guild_template(client, message->content, &template);

    if(response == ORCA_OK) {
        snprintf(message_buffer, 8001, "Here is some information about your guild template:\nName: '%s'\nDescription: '%s'\nCreator Id: %"PRIu64"\n",
                 template.name, template.description, template.creator_id);
    } else {
        snprintf(message_buffer, 8001, "Could not retrieve guild template. Error: '%s'\n", discord_strerror(response, client));
    }

    struct discord_create_message_params params = {0};
    params.content = message_buffer;

    discord_create_message(client, message->channel_id, &params, &p_message);
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

  discord_set_on_ready(client, &on_ready);
  discord_set_prefix(client, "guild-template.");
  discord_set_on_command(client, "get", on_bot_get_guild_template);

  printf("\n\nThis bot demonstrates how easy it is to manipulate guild"
         " template endpoints.\n"
         "1. Type 'guild-template.get <code>' to get a guild template's information\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
