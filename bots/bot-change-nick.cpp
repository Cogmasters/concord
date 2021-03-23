#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libdiscord.h"



struct context_s {
  char username[64];
  char nick[64];
  char *discriminator;
} cxt;

void 
on_ready(discord::client *client, const discord::user::dati *me) {
  fprintf(stderr, "\n\nChange-Nick-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void
on_command(discord::client *client,
           const discord::user::dati *me,
           const discord::channel::message::dati *msg)
{
  sscanf(msg->content, "%s %s", cxt.username, cxt.nick);
  cxt.discriminator = strchr(cxt.username, '#');
  if (!*cxt.nick) {
    printf("Missing nickname or bad format string\n");
    return;
  }
  if (NULL == cxt.discriminator) {
    printf("Wrong formatted username (%s)\n", cxt.username);
    return;
  }

  *cxt.discriminator = '\0'; //split at #
  ++cxt.discriminator;

  NTL_T(discord::guild::member::dati) members = NULL;
  discord::guild::list_guild_members::params params1 = {
    .limit = 1000
  };
  discord_list_guild_members(client, msg->guild_id, &params1, &members);
  if (NULL == members) {
    printf("Missing members list\n");
    return;
  }

  for (size_t i=0; members[i]; ++i) {
    if (0 == strcmp(members[i]->user->username, cxt.username)
        && 0 == strcmp(members[i]->user->discriminator, cxt.discriminator))
    {
      discord::guild::modify_guild_member::params params2 = {
        .nick = cxt.nick
      };
      discord_modify_guild_member(client, msg->guild_id, members[i]->user->id, &params2, NULL);
    }
  }

  discord::guild::member::dati_list_free(members);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  setlocale(LC_ALL, "");

  discord::global_init();

  discord::client *client = discord::config_init(config_file);
  assert(NULL != client);

  discord::setcb_command(client, "!nickChange", &on_command);

  printf("\n\nThis demonstrates how easy it is to modify the"
         " nickname of some guild member.\n\n"
         "1. Type !nickChange <user#1234> <nick>\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  discord::run(client);

  discord::cleanup(client);

  discord::global_cleanup();
}
