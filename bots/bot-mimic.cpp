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

uint64_t
select_guild(client *client)
{
  // get guilds bot is a part of
  guild::dati **guilds = NULL;
  guilds = user::me::get_guilds(client);
  ASSERT_S(NULL != guilds, "This bot is not part of any guilds");

  fprintf(stderr, "\n\nSelect the guild that the user to be mimicked is part of");
  int i=0;
  do {
    fprintf(stderr, "\n%d. %s", i+1, guilds[i]->name);
    ++i;
  } while (guilds[i]);

  do {
    fputs("\n\nNUMBER >>\n", stderr);
    char strnum[10]; // 10 digits should be more than enough..
    fgets(strnum, sizeof(strnum), stdin);
    int num = strtol(strnum, NULL, 10);
    if (num > 0 && num <= i) {
      uint64_t guild_id = guilds[num-1]->id;
      guild::dati_list_free(guilds);
      return guild_id;
    }
    fprintf(stderr, "\nPlease, insert a value between 1 and %d", i);
  } while (1);
}

uint64_t
select_member(client *client, uint64_t guild_id)
{
  using namespace guild;

  // get guilds bot is a part of
  member::dati **members = NULL;
  member::get_list::params params = {
    .limit = 1000,
    .after = 0
  };

  members = member::get_list::run(client, guild_id, &params);
  ASSERT_S(NULL != members, "There are no members in this guild");

  fprintf(stderr, "\n\nSelect the member to be mimicked");
  int i=0;
  do {
    fprintf(stderr, "\n%d. %s", i+1, members[i]->user->username);
    if (*members[i]->nick) { // prints nick if available
      fprintf(stderr, " (%s)", members[i]->nick);
    }
    ++i;
  } while (members[i]);

  do {
    fputs("\n\nNUMBER >>\n", stderr);
    char strnum[10]; // 10 digits should be more than enough..
    fgets(strnum, sizeof(strnum), stdin);
    int num = strtol(strnum, NULL, 10);
    if (num > 0 && num <= i) {
      uint64_t user_id = members[num-1]->user->id;
      member::dati_list_free(members);
      return user_id;
    }
    fprintf(stderr, "\nPlease, insert a value between 1 and %d", i);
  } while (1);
}

void
fetch_member_msgs(client *client, uint64_t guild_id, uint64_t user_id)
{
  using namespace channel;

  dati **channels = guild::get_channels(client, guild_id);
  ASSERT_S(NULL != channels, "Couldn't fetch channels from guild");
  
  message::get_list::params params = {
    .limit = 100
  };

  message::dati **messages;
  for (int i=0; channels[i]; ++i)
  {
    params.before = 0;

    int n_msg;
    do {
      messages = message::get_list::run(client, channels[i]->id, &params);
      ASSERT_S(NULL != messages, "Couldn't fetch messages from channel");

      for (n_msg = 0; messages[n_msg]; ++n_msg) {
        if (user_id == messages[n_msg]->author->id 
            && *messages[n_msg]->content) {
          fprintf(stdout, "%s\n", messages[n_msg]->content);
        }
      }

      if (n_msg) {
        params.before = messages[n_msg-1]->id;
      }

      message::dati_list_free(messages);

    } while (n_msg == params.limit);
  }

  dati_list_free(channels);
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

  uint64_t guild_id = select_guild(client);
  uint64_t user_id = select_member(client, guild_id);

  fetch_member_msgs(client, guild_id, user_id);

  cleanup(client);

  global_cleanup();
}
