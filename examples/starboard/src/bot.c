#include "bot.h"
#include <concord/log.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "commands.h"
#include "starboard.h"

static void star_bot_on_ready(struct discord* client, const struct discord_ready* event) {
  char* discriminator = event->user->discriminator;
  char* username = event->user->username;

  if(strncmp(discriminator, "0", strlen(discriminator)) == 0) { // This is for the time, when Discord bots will lose their discriminators
    log_info("Logged in as %s (%"PRIu64")", username, event->user->id);
  } else { // If they still have a discriminator
    log_info("Logged in as %s#%s (%"PRIu64")", username, discriminator, event->user->id);
  }

  // Register all commands
  star_commands_register(client, event->user->id); // event->user->id should be our application's ID (so the bot's ID)
}

void star_bot_start() {
  struct discord* client = discord_config_init("config.json");

  // I think we need this, but I'm not sure.
  discord_add_intents(client, DISCORD_EV_MESSAGE_REACTION_ADD);

  // This is here because we have to get the url from the config right after we initialise the client 
  star_db_connect(client);

  discord_set_on_ready(client, &star_bot_on_ready);
  discord_set_on_message_reaction_add(client, &star_main_handler);
  discord_set_on_interaction_create(client, &star_commands_handler);
  discord_run(client);
}