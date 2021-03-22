
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libdiscord.h"


void on_ready(discord::client *client, const discord::user::dati *me) {
  fprintf(stderr, "\n\nLog-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void on_guild_member_add(
  discord::client *client,
  const discord::user::dati *me,
  const uint64_t guild_id, 
  const discord::guild::member::dati *member)
{
  printf("%s#%s joined guild %" PRIu64".\n", member->user->username, member->user->discriminator, guild_id);
}

void on_guild_member_update(
  discord::client *client,
  const discord::user::dati *me,
  const uint64_t guild_id, 
  const discord::guild::member::dati *member)
{
  printf("%s#%s ", member->user->username, member->user->discriminator);
  if(!IS_EMPTY_STRING(member->nick)) {
    printf("(%s) ", member->nick);
  }
  printf("updated (guild %" PRIu64")\n", guild_id);
}

void on_guild_member_remove(
  discord::client *client,
  const discord::user::dati *me,
  const uint64_t guild_id, 
  const discord::user::dati *user)
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

  discord::global_init();

  discord::client *client = discord::config_init(config_file);
  assert(NULL != client);

  discord::setcb(client, discord::READY, &on_ready);
  discord::setcb(client, discord::GUILD_MEMBER_ADD, &on_guild_member_add);
  discord::setcb(client, discord::GUILD_MEMBER_UPDATE, &on_guild_member_update);
  discord::setcb(client, discord::GUILD_MEMBER_REMOVE, &on_guild_member_remove);

  discord::run(client);

  discord::cleanup(client);

  discord::global_cleanup();
}
