#include <stdio.h>
#include <stdlib.h>

#include "discord.h"

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("PingPong-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_ping(struct discord *client,
             const struct discord_user *bot,
             const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params = { .content = "pong" };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_pong(struct discord *client,
             const struct discord_user *bot,
             const struct discord_message *msg)
{
  if (msg->author->bot) return;

  struct discord_create_message_params params = { .content = "ping" };
  discord_create_message(client, msg->channel_id, &params, NULL);
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

  discord_set_on_ready(client, &on_ready);
  discord_set_on_command(client, "ping", &on_ping);
  discord_set_on_command(client, "pong", &on_pong);

  printf("\n\nThis bot demonstrates a simple ping-pong response.\n"
         "1. Type 'pong' in chat\n"
         "2. Type 'ping' in chat\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
