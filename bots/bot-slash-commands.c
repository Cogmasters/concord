#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> /* PRIu64 */
#include <assert.h>

#include "discord.h"


void on_ready(struct discord *client, const struct discord_user *bot) {
  log_info("Slash-Commands-Bot succesfully connected to Discord as %s#%s!",
      bot->username, bot->discriminator);
}

void log_on_application_command_create(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_application_command *cmd)
{
  log_info("Application Command %s created", cmd->name);
}

void log_on_application_command_update(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_application_command *cmd)
{
  log_info("Application Command %s updated", cmd->name);
}

void log_on_application_command_delete(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_application_command *cmd)
{
  log_info("Application Command %s deleted", cmd->name);
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
  assert(NULL != client && "Could not initialize client");

  discord_set_on_ready(client, &on_ready);
  discord_set_on_application_command_create(client, &log_on_application_command_create);
  discord_set_on_application_command_update(client, &log_on_application_command_update);
  discord_set_on_application_command_delete(client, &log_on_application_command_delete);

  printf("\n\n(USE WITH CAUTION) This bot demonstrates how easy it is to create/update/delete application commands\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
