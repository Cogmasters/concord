#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "discord.h"


void 
on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nChange-Nick-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void
on_command(struct discord *client,
           const struct discord_user *bot,
           const struct discord_message *msg)
{
  char username[64]="", nick[64]="";
  sscanf(msg->content, "%s %s", username, nick);
  if (!*nick) {
    printf("Missing nickname or bad format string\n");
    return;
  }

  char *discriminator = strchr(username, '#');
  if (!discriminator) {
    printf("Wrong formatted username (%s)\n", username);
    return;
  }
  *discriminator = '\0'; // split username/discriminator at #
  ++discriminator; // eat-up '#'

  NTL_T(struct discord_guild_member) members=NULL;
  {
    struct discord_list_guild_members_params params = { .limit = 1000 };
    discord_list_guild_members(client, msg->guild_id, &params, &members);
  }
  if (!members) {
    printf("Missing members list\n");
    return;
  }

  for (size_t i=0; members[i]; ++i) 
  {
    if (0 == strcmp(members[i]->user->username, username)
        && 0 == strcmp(members[i]->user->discriminator, discriminator))
    {
      struct discord_modify_guild_member_params params = { .nick = nick };
      discord_modify_guild_member(client, msg->guild_id, members[i]->user->id, &params, NULL);
      break; /* EARLY BREAK */
    }
  }

  discord_guild_member_list_free(members);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  setlocale(LC_ALL, "");

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  discord_set_on_command(client, "!nickChange", &on_command);

  printf("\n\nThis demonstrates how easy it is to modify the"
         " nickname of some guild member.\n\n"
         "1. Type !nickChange <user#1234> <nick>\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
