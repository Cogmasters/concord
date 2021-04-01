#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "discord.h"
#include "orka-utils.h" // for orka_timestamp_ms()

void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nCreate-Role-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void on_role_create(
    struct discord *client,
    const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const struct discord_guild_role *role)
{
  NTL_T(struct discord_channel) channels = NULL;
  discord_get_guild_channels(client, guild_id, &channels);
  if (NULL == channels) return;

  struct discord_channel *general = NULL; // get general chat
  for (size_t i=0; channels[i]; ++i) {
    if (DISCORD_CHANNEL_GUILD_TEXT == channels[i]->type) {
      general = channels[i];
      break; /* EARLY BREAK */
    }
  }
  if (NULL == general) return;

  char text[150];
  snprintf(text, sizeof(text), "Succesfully created <@&%" PRIu64 "> role", role->id);
  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, general->id, &params, NULL);

  discord_channel_list_free(channels);
}

void on_role_update(
    struct discord *client,
    const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const struct discord_guild_role *role)
{
  NTL_T(struct discord_channel) channels = NULL;
  discord_get_guild_channels(client, guild_id, &channels);
  if (NULL == channels) return;

  struct discord_channel *general = NULL; // get general chat
  for (size_t i=0; channels[i]; ++i) {
    if (DISCORD_CHANNEL_GUILD_TEXT == channels[i]->type) {
      general = channels[i];
      break; /* EARLY BREAK */
    }
  }
  if (NULL == general) return;

  char text[150];
  snprintf(text, sizeof(text), "Succesfully updated <@&%" PRIu64 "> role", role->id);
  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, general->id, &params, NULL);

  discord_channel_list_free(channels);
}

void on_role_delete(
    struct discord *client,
    const struct discord_user *bot,
    const u64_snowflake_t guild_id,
    const u64_snowflake_t role_id)
{
  NTL_T(struct discord_channel) channels = NULL;
  discord_get_guild_channels(client, guild_id, &channels);
  if (NULL == channels) return;

  struct discord_channel *general = NULL; // get general chat
  for (size_t i=0; channels[i]; ++i) {
    if (DISCORD_CHANNEL_GUILD_TEXT == channels[i]->type) {
      general = channels[i];
      break; /* EARLY BREAK */
    }
  }
  if (NULL == general) return;

  struct discord_create_message_params params = { 
    .content = "Succesfully deleted role" 
  };
  discord_create_message(client, general->id, &params, NULL);

  discord_channel_list_free(channels);
}

void on_command(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  struct discord_create_guild_role_params params1 = { .name = msg->content };
  discord_create_guild_role(client, msg->guild_id, &params1, NULL);
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

  discord_on_command(client, "!createRole", &on_command);
  discord_on_guild_role_create(client, &on_role_create);
  discord_on_guild_role_update(client, &on_role_update);
  discord_on_guild_role_delete(client, &on_role_delete);

  printf("\n\nThis bot demonstrates how easy it is to create a"
         " new role.\n"
         "1. Type !createRole <name of role>"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
