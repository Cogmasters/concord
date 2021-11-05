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

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Guild-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_bot_get_guild_template(struct discord *client,
                               const struct discord_user *bot,
                               const struct discord_message *message)
{
  char message_buffer[8001];

  struct discord_message p_message;
  struct discord_guild_template template;
  ORCAcode response =
    discord_get_guild_template(client, message->content, &template);

  if (response == ORCA_OK) {
    snprintf(message_buffer, 8001,
             "Here is some information about your guild template:\nName: "
             "'%s'\nDescription: '%s'\nCreator Id: %" PRIu64 "\n",
             template.name, template.description, template.creator_id);
  }
  else {
    snprintf(message_buffer, 8001,
             "Could not retrieve guild template. Error: '%s'\n",
             discord_strerror(response, client));
  }

  struct discord_create_message_params params = { 0 };
  params.content = message_buffer;

  discord_create_message(client, message->channel_id, &params, &p_message);

  if (response == ORCA_OK) {
    discord_guild_template_cleanup(&template);
  }
}

void on_bot_create_guild_template(struct discord *client,
                                  const struct discord_user *bot,
                                  const struct discord_message *message)
{
  char message_buffer[8001];
  struct discord_message p_message;
  struct discord_guild_template template;
  struct discord_create_guild_template_params params;

  params.name = "New server template!";
  params.description = "This is a new server template created with Orca!";

  ORCAcode response = discord_create_guild_template(client, message->guild_id,
                                                    &params, &template);

  if (response == ORCA_OK) {
    snprintf(message_buffer, 8001,
             "Successfully synced the guild template! Here is some "
             "information about its current state guild template:\nName: "
             "'%s'\nDescription: '%s'\nCode: %s\nCreator Id: %" PRIu64 "\n",
             template.name, template.description, template.code,
             template.creator_id);
  }
  else {
    snprintf(message_buffer, 8001,
             "Could not create guild template. Error: '%s'\n",
             discord_strerror(response, client));
  }

  struct discord_create_message_params message_params = { 0 };
  message_params.content = message_buffer;

  discord_create_message(client, message->channel_id, &message_params,
                         &p_message);

  if (response == ORCA_OK) {
    discord_guild_template_cleanup(&template);
  }
}

void on_bot_sync_guild_template(struct discord *client,
                                const struct discord_user *bot,
                                const struct discord_message *message)
{
  char message_buffer[8001];
  struct discord_message p_message;
  struct discord_guild_template template;

  ORCAcode response = discord_sync_guild_template(client, message->guild_id,
                                                  message->content, &template);

  if (response == ORCA_OK) {
    snprintf(message_buffer, 8001,
             "Successfully synced the guild template! Here is some "
             "information about its current state guild template:\nName: "
             "'%s'\nDescription: '%s'\nCode: %s\nCreator Id: %" PRIu64 "\n",
             template.name, template.description, template.code,
             template.creator_id);
  }
  else {
    snprintf(message_buffer, 8001,
             "Could not create sync template. Error: '%s'\n",
             discord_strerror(response, client));
  }

  struct discord_create_message_params message_params = { 0 };
  message_params.content = message_buffer;

  discord_create_message(client, message->channel_id, &message_params,
                         &p_message);

  if (response == ORCA_OK) {
    discord_guild_template_cleanup(&template);
  }
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
  discord_set_on_command(client, "create", on_bot_create_guild_template);
  discord_set_on_command(client, "sync", on_bot_sync_guild_template);

  printf("\n\nThis bot demonstrates how easy it is to manipulate guild"
         " template endpoints.\n"
         "1. Type 'guild-template.get <code>' to get a guild template's "
         "information\n"
         "2. Type 'guild-template.create' to create a new guild template\n"
         "3. Type 'guild-template.sync' to sync the guild template\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
