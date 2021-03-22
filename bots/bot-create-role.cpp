#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libdiscord.h"
#include "orka-utils.h" // for orka_timestamp_ms()

void on_ready(discord::client *client, const discord::user::dati *me) {
  fprintf(stderr, "\n\nCreate-Role-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_command(
    discord::client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord::guild::role::dati *role = discord::guild::role::dati_alloc();

  discord::guild::create_guild_role::params params1 = {
    .name = msg->content
  };
  discord::guild::create_guild_role::run(client, msg->guild_id, &params1, role);

  if (role->id) {
    char text[150];
    snprintf(text, sizeof(text), "Succesfully created <@&%" PRIu64 "> role", role->id);

    discord::channel::create_message::params params2 = {
      .content = text
    };
    discord::channel::create_message::run(client, msg->channel_id, &params2, NULL);
  }

  discord::guild::role::dati_free(role);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  discord::global_init();

  discord::client *client = discord::config_init(config_file);
  assert(NULL != client);

  discord::setcb_command(client, "!createRole", &on_command);

  printf("\n\nThis bot demonstrates how easy it is to create a"
         " new role.\n"
         "1. Type !createRole <name of role>"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord::run(client);

  discord::cleanup(client);

  discord::global_cleanup();
}
