#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "discord.h"
#include "discord-voice-connections.h"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Voice-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_list_voice_regions(struct discord *client,
                           const struct discord_user *bot,
                           const struct discord_message *msg)
{
  if (msg->author->bot) return;
  NTL_T(struct discord_voice_region) voice_regions = NULL;
  discord_list_voice_regions(client, &voice_regions);
  if (!voice_regions) {
    log_error("Could not obtain voice regions");
    return;
  }

  struct discord_create_message_params params = {};
  for (size_t i = 0; voice_regions[i]; ++i) {
    params.content = voice_regions[i]->name;
    discord_create_message(client, msg->channel_id, &params, NULL);
  }

  discord_voice_region_list_free(voice_regions);
}

void on_voice_join(struct discord *client,
                   const struct discord_user *bot,
                   const struct discord_message *msg)
{
  if (msg->author->bot) return;

  int position = -1;
  sscanf(msg->content, "%d", &position);

  struct discord_channel vchannel;
  discord_channel_init(&vchannel);

  discord_get_channel_at_pos(client, msg->guild_id,
                             DISCORD_CHANNEL_GUILD_VOICE, position - 1,
                             &vchannel);

  if (vchannel.id != 0) { // founds voice channel at pos
    discord_voice_join(client, msg->guild_id, vchannel.id, false, false);
  }
  else { // couldn't find a voice channel at pos
    struct discord_create_message_params params = {
      .content = "Invalid channel position"
    };
    discord_create_message(client, msg->channel_id, &params, NULL);
  }
  discord_channel_cleanup(&vchannel);
}

void on_voice_kick(struct discord *client,
                   const struct discord_user *bot,
                   const struct discord_message *msg)
{
  if (msg->author->bot) return;

  u64_snowflake_t user_id = 0;
  sscanf(msg->content, "%" SCNu64, &user_id);

  char text[DISCORD_MAX_MESSAGE_LEN];
  if (!user_id) {
    sprintf(text, "Couldn't find user");
  }
  else {
    discord_disconnect_guild_member(client, msg->guild_id, user_id, NULL);
    snprintf(text, sizeof(text), "<@!%" PRIu64 "> has been kicked from VC",
             user_id);
  }

  struct discord_create_message_params params = { .content = text };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void log_on_voice_state_update(struct discord *client,
                               const struct discord_user *bot,
                               const struct discord_voice_state *vs)
{
  log_info("User <@!%" PRIu64 "> has joined <#%" PRIu64 ">!", vs->user_id,
           vs->channel_id);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_set_on_voice_state_update(client, &log_on_voice_state_update);
  discord_set_prefix(client, "voice.");
  discord_set_on_command(client, "list_regions", &on_list_voice_regions);
  discord_set_on_command(client, "join", &on_voice_join);
  discord_set_on_command(client, "kick", &on_voice_kick);

  printf("\n\nThis bot is a work in progress, it should demonstrate some "
         "Voice related utilities\n"
         "1. Type 'voice.list_regions' to list regions that can be used when "
         "creating servers\n"
         "2. Type 'voice.join <channel position>' to join a particular voice "
         "channel by its position\n"
         "3. Type 'voice.kick <user id>' to kick a particular user from the "
         "voice channel he's at\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
