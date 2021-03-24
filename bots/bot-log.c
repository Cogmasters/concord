#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libdiscord.h"


void on_ready(struct discord *client, const struct discord_user *me) {
  fprintf(stderr, "\n\nLog-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_guild_member_add(
  struct discord *client,
  const struct discord_user *me,
  const uint64_t guild_id, 
  const struct discord_guild_member *member)
{
  printf("%s#%s joined guild %" PRIu64".\n", member->user->username, member->user->discriminator, guild_id);
}

void on_guild_member_update(
  struct discord *client,
  const struct discord_user *me,
  const uint64_t guild_id, 
  const struct discord_guild_member *member)
{
  printf("%s#%s ", member->user->username, member->user->discriminator);
  if(!IS_EMPTY_STRING(member->nick)) {
    printf("(%s) ", member->nick);
  }
  printf("updated (guild %" PRIu64")\n", guild_id);
}

void on_guild_member_remove(
  struct discord *client,
  const struct discord_user *me,
  const uint64_t guild_id, 
  const struct discord_user *user)
{
  printf("%s#%s left guild %" PRIu64".\n", user->username, user->discriminator, guild_id);
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

  discord_setcb(client, READY, &on_ready);
  discord_setcb(client, GUILD_MEMBER_ADD, &on_guild_member_add);
  discord_setcb(client, GUILD_MEMBER_UPDATE, &on_guild_member_update);
  discord_setcb(client, GUILD_MEMBER_REMOVE, &on_guild_member_remove);

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
