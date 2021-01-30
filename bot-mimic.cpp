#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>


using namespace discord;

void on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nMimic-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

char*
select_guild(client *client)
{
  // get guilds bot is a part of
  guild::dati **guilds = user::me::get_guilds(client);
  if (NULL == guilds[0]) ERR("This bot is not part of any guild");

  fprintf(stderr, "\n\nThe user you wish to mimic is part of which guild?");
  int i=0;
  do {
    fprintf(stderr, "\n%d. %s", i, guilds[i]->name);
    ++i;
  } while (guilds[i]);
  fputs("\n\nNUMBER >>\n", stderr);

  char strnum[10]; // 10 digits should be more than enough..
  long num;
  do {
    fgets(strnum, sizeof(strnum), stdin);
    num = strtol(strnum, NULL, 10);
    if (num >= 0 && num < i) {
      char *guild_id = strdup(guilds[num]->id);
      guild::list_cleanup(guilds);

      return guild_id;
    }
  } while (1);
}

void
select_member(client *client, char *guild_id)
{
  // get guilds bot is a part of
  guild::member::dati **members = guild::member::get_list(client, guild_id);
  if (NULL == members[0]) ERR("There are no members in this guild");

  fprintf(stderr, "\n\nWho is the member you wish to mimic?");
  int i=0;
  do {
    fprintf(stderr, "\n%d. %s", i, members[i]->user->username);
    if (*members[i]->nick) { // prints nick if available
      fprintf(stderr, " (%s)", members[i]->nick);
    }

    ++i;
  } while (members[i]);
  fputs("\n\nNUMBER >>\n", stderr);

  char strnum[10]; // 10 digits should be more than enough..
  long num;
  do {
    fgets(strnum, sizeof(strnum), stdin);
    num = strtol(strnum, NULL, 10);
    if (num >= 0 && num < i) {
      guild::member::list_cleanup(members);
      ERR("THIS IS A WORK IN PROGRESS.");
    }
  } while (1);
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

  char *guild_id = select_guild(client);
  select_member(client, guild_id);

  cleanup(client);

  global_cleanup();
}
