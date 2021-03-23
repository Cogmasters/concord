#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libdiscord.h"



void on_ready(struct discord_client *client, const discord::user::dati *me) {
  fprintf(stderr, "\n\nEcho-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_reaction_add(
    struct discord_client *client,
    const discord::user::dati *me,
    const uint64_t channel_id, 
    const uint64_t message_id, 
    const uint64_t guild_id, 
    const discord::guild::member::dati *member,
    const discord::emoji::dati *emoji)
{ 
  // make sure bot doesn't echoes other bots
  if (member->user->bot) 
    return;

  discord_create_reaction(client, channel_id, message_id, emoji->id, emoji->name);
}

void on_message_create(
    struct discord_client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  discord::channel::create_message::params params = {
    .content = msg->content
  };
  discord::channel::message::reference::dati msg_ref;
  discord::channel::message::reference::dati_init(&msg_ref);
  if(msg->referenced_message) {
    msg_ref.message_id = msg->referenced_message->id;
    msg_ref.channel_id = msg->channel_id;
    msg_ref.guild_id = msg->guild_id;

    params.message_reference = &msg_ref;
  }

  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_message_update(
    struct discord_client *client,
    const discord::user::dati *me,
    const discord::channel::message::dati *msg)
{
  discord::channel::create_message::params params = {
    .content = "I see what you did there."
  };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_message_delete(
    struct discord_client *client,
    const discord::user::dati *me,
    const uint64_t id,
    const uint64_t channel_id,
    const uint64_t guild_id)
{
  discord::channel::create_message::params params = {
    .content = "Did that message just disappear?"
  };
  discord_create_message(client, channel_id, &params, NULL);
}

void on_message_delete_bulk(
    struct discord_client *client,
    const discord::user::dati *me,
    const size_t nids,
    const uint64_t ids[],
    const uint64_t channel_id,
    const uint64_t guild_id)
{
  char buf[128];
  snprintf(buf, sizeof(buf), "Ouch! Where did those %zu messages go?", nids);

  discord::channel::create_message::params params = {
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

  struct discord_client *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_setcb(client, READY, &on_ready);
  discord_setcb(client, MESSAGE_CREATE, &on_message_create);
  discord_setcb(client, MESSAGE_UPDATE, &on_message_update);
  discord_setcb(client, MESSAGE_DELETE, &on_message_delete);
  discord_setcb(client, MESSAGE_DELETE_BULK, &on_message_delete_bulk);
  discord_setcb(client, MESSAGE_REACTION_ADD, &on_reaction_add);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}


