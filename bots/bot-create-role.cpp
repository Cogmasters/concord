#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libdiscord.h"
#include "orka-utils.h" // for orka_timestamp_ms()

void on_ready(struct discord_client *client, const struct discord_user_dati *me) {
  fprintf(stderr, "\n\nCreate-Role-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_command(
    struct discord_client *client,
    const struct discord_user_dati *me,
    const struct discord_channel_message_dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  struct discord_guild_role_dati *role = discord_guild_role_dati_alloc();

  struct discord_guild_create_guild_role_params params1 = {
    .name = msg->content
  };
  discord_create_guild_role(client, msg->guild_id, &params1, role);

  if (role->id) {
    char text[150];
    snprintf(text, sizeof(text), "Succesfully created <@&%" PRIu64 "> role", role->id);

    struct discord_channel_create_message_params params2 = {
      .content = text
    };
    discord_create_message(client, msg->channel_id, &params2, NULL);
  }

  discord_guild_role_dati_free(role);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  discord_global_init();

  struct discord_client *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_setcb_command(client, "!createRole", &on_command);

  printf("\n\nThis bot demonstrates how easy it is to create a"
         " new role.\n"
         "1. Type !createRole <name of role>"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
