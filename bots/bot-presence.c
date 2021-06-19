#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"
#include "cee-utils.h" /* cee_load_whole_file() */

#define JSON_FILE "bot-presence.json"

void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nPresence-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void
load_presence_from_json(struct discord *client, char filename[])
{
  /* get contents of file to string */
  size_t len;
  char *json_payload = cee_load_whole_file(filename, &len);

  struct discord_gateway_status_update *presence = discord_gateway_status_update_alloc();
  discord_gateway_status_update_from_json(json_payload, len, presence);

  discord_replace_presence(client, presence);

  free(json_payload);
  discord_gateway_status_update_free(presence);
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
  assert(NULL != client && "Couldn't initialize client");

  printf("\n\nThis bot demonstrates how easy it is to change presence"
         " from a json file.\n"
         "1. Edit 'bot-presence.json' to change how presence is"
         " displayed.\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  load_presence_from_json(client, JSON_FILE);
  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}

