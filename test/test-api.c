#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <libdiscord.h>

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

  struct discord_user *me = discord_user_alloc(); 
  assert(NULL != me);

  discord_get_current_user(client, me);
  printf("Greetings, %s#%s!\n", me->username, me->discriminator);

  NTL_T(struct discord_guild) guilds = NULL;
  discord_get_current_user_guilds(client, &guilds);
  for (size_t i=0; guilds[i]; ++i) {
    fprintf(stderr, "Guild[%s] id:\n\t%" PRIu64 "\n", guilds[i]->name, guilds[i]->id);
  }

  discord_guild_list_free(guilds);
  discord_user_free(me);

  discord_cleanup(client);

  discord_global_cleanup();
}
