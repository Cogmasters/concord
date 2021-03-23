#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libdiscord.h"
#include "orka-utils.h" // for orka_timestamp_ms()

//using namespace discord;

#define JSON_FILE "bot-embed.json"

void on_ready(struct discord_client *client, const struct discord_user_dati *me) {
  fprintf(stderr, "\n\nEmbed-Bot succesfully connected to Discord as %s#%s!\n\n",
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

  struct discord_channel_create_message_params params = {
    .content = "This is an embed",
    .embed = (struct discord_channel_embed_dati*)discord_get_data(client)
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

static struct discord_channel_embed_dati*
load_embed_from_json(char filename[])
{
  /* get contents of file to string */
  size_t len;
  char *json_payload = orka_load_whole_file(filename, &len);

  struct discord_channel_embed_dati *new_embed = discord_channel_embed_dati_alloc();
  discord_channel_embed_dati_from_json(json_payload, len, new_embed);

  new_embed->timestamp = orka_timestamp_ms(); // get current timestamp

  free(json_payload);

  return new_embed;
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

  discord_setcb_command(client, "show embed", &on_command);

  printf("\n\nThis bot demonstrates how easy it is to load embed"
         " from a json file.\n"
         "1. Edit 'bot-embed.json' to change how the embed contents"
         " are displayed.\n"
         "2. Type 'show embed' in any channel to trigger the bot\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  struct discord_channel_embed_dati *embed = load_embed_from_json(JSON_FILE);
  discord_set_data(client, embed);

  discord_run(client);

  discord_channel_embed_dati_free(embed);
  discord_cleanup(client);

  discord_global_cleanup();
}

