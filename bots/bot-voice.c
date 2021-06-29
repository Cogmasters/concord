#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"


void on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nVoice-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void on_voice_regions(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
  if (msg->author->bot) return;
  NTL_T(struct discord_voice_region) voice_regions=NULL;
  discord_list_voice_regions(client, &voice_regions);
  if (!voice_regions) {
    fprintf(stderr, "Could not obtain voice regions\n");
    return;
  }

  struct discord_create_message_params params={};
  for (size_t i=0; voice_regions[i]; ++i) {
    params.content = voice_regions[i]->name;
    discord_create_message(client, msg->channel_id, &params, NULL);
  }

  discord_voice_region_list_free(voice_regions);
}

enum discord_event_handling_mode 
on_any_event(
  struct discord *client,
  struct discord_user *bot,
  struct sized_buffer *event_data,
  enum discord_gateway_events event) 
{
  return EVENT_WILL_BE_HANDLED_IN_CHILD_THREAD;
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

  /* trigger event callbacks in a multi-threaded fashion */
  discord_set_event_handler(client, &on_any_event);

  discord_set_prefix(client, "voice.");
  discord_set_on_command(client, "regions", &on_voice_regions);

  printf("\n\nThis bot is a work in progress, it should demonstrate some Voice related utilities\n"
         "1. Type 'voice.regions' to list regions that can be used when creating servers\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}

