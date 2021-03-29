#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libdiscord.h"



void on_ready(struct discord *client, const struct discord_user *me) {
  fprintf(stderr, "\n\nEcho-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_reaction_add(
    struct discord *client,
    const struct discord_user *me,
    const uint64_t user_id, 
    const uint64_t channel_id, 
    const uint64_t message_id, 
    const uint64_t guild_id, 
    const struct discord_guild_member *member,
    const struct discord_emoji *emoji)
{ 
  // make sure bot doesn't echoes other bots
  if (member->user->bot) 
    return;

  discord_create_reaction(client, channel_id, message_id, emoji->id, emoji->name);
}

void on_message_create(
    struct discord *client,
    const struct discord_user *me,
    const struct discord_message *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  struct discord_create_message_params params = {
    .content = msg->content
  };
  struct discord_message_reference msg_ref;
  discord_message_reference_init(&msg_ref);
  if(msg->referenced_message) {
    msg_ref.message_id = msg->referenced_message->id;
    msg_ref.channel_id = msg->channel_id;
    msg_ref.guild_id = msg->guild_id;

    params.message_reference = &msg_ref;
  }

  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_message_update(
    struct discord *client,
    const struct discord_user *me,
    const struct discord_message *msg)
{
  struct discord_create_message_params params = {
    .content = "I see what you did there."
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_message_delete(
    struct discord *client,
    const struct discord_user *me,
    const uint64_t id,
    const uint64_t channel_id,
    const uint64_t guild_id)
{
  struct discord_create_message_params params = {
    .content = "Did that message just disappear?"
  };
  discord_create_message(client, channel_id, &params, NULL);
}

void on_message_delete_bulk(
    struct discord *client,
    const struct discord_user *me,
    const NTL_T(ja_u64) ids,
    const uint64_t channel_id,
    const uint64_t guild_id)
{
  char buf[128];
  snprintf(buf, sizeof(buf), "Ouch! Where did those %zu messages go?", ntl_length((ntl_t)ids));

  struct discord_create_message_params params = {
    .content = buf
  };
  discord_create_message(client, channel_id, &params, NULL);
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

  discord_on_ready(client, &on_ready);
  discord_on_message_create(client, &on_message_create);
  discord_on_message_update(client, &on_message_update);
  discord_on_message_delete(client, &on_message_delete);
  discord_on_message_delete_bulk(client, &on_message_delete_bulk);
  discord_on_message_reaction_add(client, &on_reaction_add);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}


