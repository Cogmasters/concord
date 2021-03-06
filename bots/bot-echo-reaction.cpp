#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>
#include "orka-utils.h" // for orka_timestamp_ms()

using namespace discord;

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nEcho-Reaction-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_reaction_add(
    client *client, 
    const user::dati *me,
    const uint64_t channel_id, 
    const uint64_t message_id, 
    const uint64_t guild_id, 
    const guild::member::dati *member, 
    const emoji::dati *emoji)
{
  if (member->user->bot) return;

  channel::reaction::create(client, channel_id, message_id, emoji->id, emoji->name);
}


int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  global_init();

  client *client = config_init(config_file);
  assert(NULL != client);

  setcb(client, READY, &on_ready);
  setcb(client, REACTION_ADD, &on_reaction_add);

  run(client);

  cleanup(client);

  global_cleanup();
}

