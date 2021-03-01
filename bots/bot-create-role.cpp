#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>
#include "orka-utils.h" // for orka_timestamp_ms()

using namespace discord;

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nCreate-Role-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_command(
    client *client,
    const user::dati *me,
    const channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  role::dati *role = role::dati_alloc();

  guild::create_role::params params1 = {
    .name = msg->content
  };
  guild::create_role::run(client, msg->guild_id, &params1, role);

  if (role->id) {
    char text[150];
    snprintf(text, sizeof(text), "Succesfully created %s role", msg->content);

    channel::message::create::params params2 = {
      .content = text
    };
    channel::message::create::run(client, msg->channel_id, &params2, NULL);
  }

  role::dati_free(role);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  global_init();

  client *client = fast_init(config_file);
  assert(NULL != client);

  setcb_command(client, "!createRole", &on_command);

  printf("\n\nThis bot demonstrates how easy it is to create a"
         " new role.\n"
         "1. Type !createRole <name of role>"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  run(client);

  cleanup(client);

  global_cleanup();
}


