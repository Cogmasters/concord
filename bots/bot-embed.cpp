#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libdiscord.h>
#include "orka-utils.h" // for orka_timestamp_ms()

using namespace discord;

#define JSON_FILE "bot-embed.json"

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nEmbed-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_command(
    client *client,
    const user::dati *me,
    const channel::message::dati *msg)
{
  using namespace channel;

  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  message::create::params params = {
    .content = "This is an embed",
    .embed = (embed::dati*)get_data(client)
  };

  message::create::run(client, msg->channel_id, &params, NULL);
}

static channel::embed::dati*
load_embed_from_json(char filename[])
{
  using namespace channel;

  /* get contents of file to string */
  size_t len;
  char *json_payload = orka_load_whole_file(filename, &len);

  embed::dati *new_embed = embed::dati_alloc();
  embed::dati_from_json(json_payload, len, new_embed);

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

  global_init();

  client *client = config_init(config_file);
  assert(NULL != client);

  setcb_command(client, "show embed", &on_command);

  printf("\n\nThis bot demonstrates how easy it is to load embed"
         " from a json file.\n"
         "1. Edit 'bot-embed.json' to change how the embed contents"
         " are displayed.\n"
         "2. Type 'show embed' in any channel to trigger the bot\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  channel::embed::dati *embed = load_embed_from_json(JSON_FILE);
  set_data(client, embed);

  run(client);

  channel::embed::dati_free(embed);
  cleanup(client);

  global_cleanup();
}

