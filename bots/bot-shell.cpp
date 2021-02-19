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

  char *cmd = strchr(msg->content, ' '); //get first occurence of space
  size_t len;
  if (cmd) {
    len = cmd - msg->content;
    ++cmd; //skip space
  }
  else {
    len = strlen(msg->content);
  }

  if (STRNEQ(msg->content, "cd", len)) {
    char path[100];

    chdir(cmd);
    getcwd(path, sizeof(path));

    params.content = path;
  }
  else { /* DEFAULT CASE */
    FILE *fp = popen(msg->content, "r");
    if (NULL == fp) {
      printf("Failed to run command");
      return;
    }

    const size_t MAX_FSIZE = 5e6; // 5 mb
    char *path = (char*)malloc(MAX_FSIZE);
    char *pathtmp = (char*)malloc(MAX_FSIZE);

    if (STRNEQ(msg->content, "less", len) 
        || STRNEQ(msg->content, "cat", len)
        || STRNEQ(msg->content, "hexdump", len)) 
    {
      strncat(pathtmp, "```\n", MAX_FSIZE-1);
      while (NULL != fgets(path, MAX_FSIZE, fp)) {
        strncat(pathtmp, path, MAX_FSIZE-1);
      }
      strncat(pathtmp, "\n```", MAX_FSIZE-1);

      if (strlen(pathtmp) > 2000) { // MAX MESSAGE LEN is 2000 bytes
        //@todo need some checks to make sure its a valid filename
        params.file.name = 1 + msg->content + len;
      }
      else {
        params.content = pathtmp;
      }
    }
    else { /* DEFAULT CASE */
      while (NULL != fgets(path, MAX_FSIZE, fp)) {
        strncat(pathtmp, path, MAX_FSIZE-1);
      }

      size_t fsize = strlen(pathtmp);
      if (fsize > 2000) { // MAX MESSAGE LEN is 2000 bytes
        params.file.content = pathtmp;
        params.file.size = fsize;
      }
      else {
        params.content = pathtmp;
      }
    }

    pclose(fp);
  }

  message::create::run(client, msg->channel_id, &params, NULL); 
}

uint64_t
select_guild(client *client)
{
  // get guilds bot is a part of
  guild::dati **guilds = NULL;
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
      guild::free_list(guilds);
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
