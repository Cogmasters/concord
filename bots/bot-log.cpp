
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>

using namespace discord;

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nLog-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void on_guild_member_add(client *client, const user::dati *me, const uint64_t guild_id, const guild::member::dati *member)
{
  printf("%s#%s joined guild %" PRIu64".\n", member->user->username, member->user->discriminator, guild_id);
}

void on_guild_member_update(client *client, const user::dati *me, const uint64_t guild_id, const guild::member::dati *member)
{
  printf("%s#%s ", member->user->username, member->user->discriminator);
  if(!IS_EMPTY_STRING(member->nick))
  {
    printf("(%s) ", member->nick);
  }
  printf("updated (guild %" PRIu64")\n", guild_id);
}

void on_guild_member_remove(client *client, const user::dati *me, const uint64_t guild_id, const user::dati *user)
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

  global_init();

  client *client = fast_init(config_file);
  assert(NULL != client);

  setcb_ready(client, &on_ready);
  setcb_guild_member_add(client, &on_guild_member_add);
  setcb_guild_member_update(client, &on_guild_member_update);
  setcb_guild_member_remove(client, &on_guild_member_remove);

  run(client);

  cleanup(client);

  global_cleanup();
}