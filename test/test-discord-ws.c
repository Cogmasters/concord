#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "discord.h"
#include "discord-internal.h"

void on_ready(struct discord *client, const struct discord_user *me) {
  fprintf(stderr, "\n\nSuccesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_reconnect(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot)
    return;

  struct discord_create_message_params params = { .content = "Reconnecting ..." };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_gateway_reconnect(&client->gw);
}

void on_disconnect(
  struct discord *client,
  const struct discord_user *bot,
  const struct discord_message *msg)
{
  if (msg->author->bot)
    return;

  struct discord_create_message_params params = { .content = "Disconnecting ..." };
  discord_create_message(client, msg->channel_id, &params, NULL);

  discord_gateway_shutdown(&client->gw);
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

  discord_set_on_ready(client, &on_ready);
  discord_set_on_command(client, "reconnect", &on_reconnect);
  discord_set_on_command(client, "disconnect", &on_disconnect);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}

