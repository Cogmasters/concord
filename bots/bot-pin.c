#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libdiscord.h"


void on_ready(struct discord *client, const struct discord_user *me) {
  fprintf(stderr, "\n\nPin-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_message_create(
    struct discord *client,
    const struct discord_user *me,
    const struct discord_message *msg)
{
  // make sure bot ignores msgs from other bots
  if (msg->author->bot)
    return;

  if (strstr(msg->content, "pin me")) {
    discord_add_pinned_channel_message(client, msg->channel_id, msg->id);
  }
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

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
