#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>


using namespace discord;

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nEcho-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_message_create(
    client *client,
    const user::dati *me,
    const channel::message::dati *msg)
{
  using namespace channel;

  // make sure bot doesn't echoes other bots
  if (msg->author->bot)
    return;

  message::create::params params = {
    .content = msg->content
  };

  message::reference::dati msg_ref;
  message::reference::dati_init(&msg_ref);
  if(msg->referenced_message) {
    msg_ref.message_id = msg->referenced_message->id;
    msg_ref.channel_id = msg->channel_id;
    msg_ref.guild_id = msg->guild_id;

    params.message_reference = &msg_ref;
  }

  message::create::run(client, msg->channel_id, &params, NULL);
}

void on_message_update(
    client *client,
    const user::dati *me,
    const channel::message::dati *msg)
{
  using namespace channel;

  message::create::params params = {
    .content = "I see what you did there."
  };

  message::create::run(client, msg->channel_id, &params, NULL);
  
  (void)me;
}

void on_message_delete(
    client *client,
    const user::dati *me,
    const uint64_t id,
    const uint64_t channel_id,
    const uint64_t guild_id)
{
  using namespace channel;

  message::create::params params = {
    .content = "Did that message just disappear?"
  };

  message::create::run(client, channel_id, &params, NULL);

  (void)me;
}

void on_message_delete_bulk(
    client *client,
    const user::dati *me,
    const size_t nids,
    const uint64_t ids[],
    const uint64_t channel_id,
    const uint64_t guild_id)
{
  using namespace channel;

  char buf[128];
  snprintf(buf, sizeof(buf), "Did that %zu messages just disappear?", nids);

  message::create::params params = {
    .content = buf
  };

  message::create::run(client, channel_id, &params, NULL);

  (void)me;
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

  setcb(client, READY, &on_ready);
  setcb(client, MESSAGE_CREATE, &on_message_create);
  setcb(client, MESSAGE_UPDATE, &on_message_update);
  setcb(client, MESSAGE_DELETE, &on_message_delete);
  setcb(client, MESSAGE_DELETE_BULK, &on_message_delete_bulk);

  run(client);

  cleanup(client);

  global_cleanup();
}


