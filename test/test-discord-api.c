#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

#include "discord.h"

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

  struct discord_user me;
  discord_user_init(&me);

  assert(ORCA_OK == discord_get_current_user(client, &me));
  printf("Greetings, %s#%s!\n", me.username, me.discriminator);

  NTL_T(struct discord_guild) guilds = NULL;
  assert(ORCA_OK == discord_get_current_user_guilds(client, &guilds));
  for (size_t i = 0; guilds[i]; ++i)
    fprintf(stderr, "Guild[%s] id:\n\t%" PRIu64 "\n", guilds[i]->name,
            guilds[i]->id);

  // Test discord_strerror()
  ORCAcode code;
  code = discord_delete_channel(client, 123, NULL);
  fprintf(stderr, "%s\n", discord_strerror(code, client));
  code = discord_modify_channel(client, 123, NULL, NULL);
  fprintf(stderr, "%s\n", discord_strerror(code, client));

  discord_guild_list_free(guilds);
  discord_user_cleanup(&me);

  discord_cleanup(client);

  discord_global_cleanup();
}
