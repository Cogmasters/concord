#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <libdiscord.h>


using namespace discord;

void 
on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nShell-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void
on_command(client *client, const user::dati *me, const channel::message::dati *msg)
{
  using namespace channel;
  
  // make sure bot doesn't consider other bots
  if (msg->author->bot)
    return;

  // make sure user has machine control privileges
  uint64_t *user_id = (uint64_t*)get_data(client);
  if (*user_id != msg->author->id)
    return;

  message::create::params params = {0};

  if (STRNEQ(msg->content, "cd", 2)) {
    char path[100];

    chdir(msg->content + 3);
    getcwd(path, sizeof(path));

    params.content = path;
  }
  else { /* DEFAULT CASE */
    FILE *fp = popen(msg->content, "r");
    ASSERT_S(NULL != fp, "Failed to run command");

    char path[1024] = "";
    char pathtmp[1024] = "";
    if (STRNEQ(msg->content, "less", 4) || STRNEQ(msg->content, "cat", 3)) {
      strncat(pathtmp, "```\n", sizeof(pathtmp)-1);
      while (NULL != fgets(path, sizeof(path), fp)) {
        strncat(pathtmp, path, sizeof(pathtmp)-1);
      }
      strncat(pathtmp, "\n```", sizeof(pathtmp)-1);
    }
    else {
      while (NULL != fgets(path, sizeof(path), fp)) {
        path[strlen(path)-1] = ' '; //replace \n with space
        strncat(pathtmp, path, sizeof(pathtmp)-1);
      }
    }

    params.content = pathtmp;

    pclose(fp);
  }

  message::create::run(client, msg->channel_id, &params, NULL); 
}

uint64_t
select_guild(client *client)
{
  using namespace guild;

  // get guilds bot is a part of
  dati **guilds = NULL;
  guilds = user::me::get_guilds(client);
  ASSERT_S(NULL != guilds, "This bot is not part of any guilds");

  fprintf(stderr, "\n\nSelect the guild where the admin member is at.");
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
      free_list(guilds);
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

  fprintf(stderr, "\n\nSelect the admin member that may control your machine");
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
      member::free_list(members);
      return user_id;
    }
    fprintf(stderr, "\nPlease, insert a value between 1 and %d", i);
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

  setcb_message_command(client, "$", &on_command);

  printf("\n\nThis bot allows navigating its host machine like"
         " a shell terminal.\n\n"
         "DISCLAIMER: This bot is potentially dangerous if not"
         " used with care.\nOnly give admin privileges to yourself"
         " or someone trustworthy.\n\n\n");

  uint64_t guild_id = select_guild(client);
  uint64_t user_id = select_member(client, guild_id);

  set_data(client, &user_id);

  run(client);

  cleanup(client);

  global_cleanup();
}
