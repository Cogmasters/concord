/*
 * Examples on how to use guild templates.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> /* PRIu64, SCNu64 */
#include <assert.h>

#include "discord.h"

void on_ready(struct discord *client)
{
  const struct discord_user *bot = discord_get_self(client);

  log_info("Guild-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_get_guild_template(struct discord *client,
                           const struct discord_message *msg)
{
  struct discord_guild_template template;
  char buf[DISCORD_MAX_MESSAGE_LEN];
  CCORDcode code;

  code = discord_get_guild_template(client, msg->content, &template);

  if (code == CCORD_OK) {
    snprintf(buf, sizeof(buf),
             "Here is some information about your guild template:\nName: "
             "'%s'\nDescription: '%s'\nCreator Id: %" PRIu64 "\n",
             template.name, template.description, template.creator_id);

    discord_guild_template_cleanup(&template);
  }
  else {
    snprintf(buf, sizeof(buf),
             "Could not retrieve guild template. Error: '%s'\n",
             discord_strerror(code, client));
  }

  struct discord_create_message_params params = { .content = buf };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_create_guild_template(struct discord *client,
                              const struct discord_message *msg)
{
  struct discord_guild_template template;
  char buf[DISCORD_MAX_MESSAGE_LEN];
  CCORDcode code;

  struct discord_create_guild_template_params params = {
    .name = "New server template!",
    .description = "This is a new server templated created with Orca!"
  };

  code =
    discord_create_guild_template(client, msg->guild_id, &params, &template);

  if (code == CCORD_OK) {
    snprintf(buf, sizeof(buf),
             "Successfully synced the guild template! Here is some "
             "information about its current state guild template:\nName: "
             "'%s'\nDescription: '%s'\nCode: %s\nCreator Id: %" PRIu64 "\n",
             template.name, template.description, template.code,
             template.creator_id);

    discord_guild_template_cleanup(&template);
  }
  else {
    snprintf(buf, sizeof(buf),
             "Could not create guild template. Error: '%s'\n",
             discord_strerror(code, client));
  }

  discord_create_message(
    client, msg->channel_id,
    &(struct discord_create_message_params){ .content = buf }, NULL);
}

void on_sync_guild_template(struct discord *client,
                            const struct discord_message *msg)
{
  struct discord_guild_template template;
  char buf[DISCORD_MAX_MESSAGE_LEN];
  CCORDcode code;

  code = discord_sync_guild_template(client, msg->guild_id, msg->content,
                                     &template);

  if (code == CCORD_OK) {
    snprintf(buf, sizeof(buf),
             "Successfully synced the guild template! Here is some "
             "information about its current state guild template:\nName: "
             "'%s'\nDescription: '%s'\nCode: %s\nCreator Id: %" PRIu64 "\n",
             template.name, template.description, template.code,
             template.creator_id);

    discord_guild_template_cleanup(&template);
  }
  else {
    snprintf(buf, sizeof(buf), "Could not create sync template. Error: '%s'\n",
             discord_strerror(code, client));
  }

  struct discord_create_message_params params = { .content = buf };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  ccord_global_init();
  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_ready(client, &on_ready);
  discord_set_prefix(client, "guild-template.");
  discord_set_on_command(client, "get", on_get_guild_template);
  discord_set_on_command(client, "create", on_create_guild_template);
  discord_set_on_command(client, "sync", on_sync_guild_template);

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
  ccord_global_cleanup();
}
