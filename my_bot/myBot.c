#include <stdio.h>
#include "discord.h"

void on_ready(struct discord* client, const struct discord_user* bot)
{
  log_info("Logged in as %s!", bot->username);
}

int main()
{
  struct discord* client = discord_config_init("./mybot_config.json");

  discord_set_on_ready(client, &on_ready);
  discord_run(client);

  discord_cleanup(client);
  return 0;
}
