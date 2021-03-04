#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <libdiscord.h>


using namespace discord;

struct sudo_s {
  char username[64];
  char nick[64];
  char *discriminator;
} sudo;

void 
on_ready(client *client, const user::dati *me)
{
  fprintf(stderr, "\n\nChange-Nick-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);

  (void)client;
}

void
on_command(client *client, const user::dati *me, const channel::message::dati *msg)
{
  sscanf(msg->content, "%s %s", sudo.username, sudo.nick);
  sudo.discriminator = strchr(sudo.username, '#');
  if (!*sudo.nick) {
    printf("Missing nickname or bad format string\n");
    return;
  }
  if (NULL == sudo.discriminator) {
    printf("Wrong formatted username (%s)\n", sudo.username);
    return;
  }

  *sudo.discriminator = '\0'; //split at #
  ++sudo.discriminator;

  guild::member::dati **members = NULL;
  guild::member::get_list::params params1 = {
    .limit = 1000
  };
  members = guild::member::get_list::run(client, msg->guild_id, &params1);
  if (NULL == members) {
    printf("Missing members list\n");
    return;
  }

  for (size_t i=0; members[i]; ++i) {
    if (0 == strcmp(members[i]->user->username, sudo.username)
        && 0 == strcmp(members[i]->user->discriminator, sudo.discriminator))
    {
      guild::modify_member::params params2 = {
        .nick = sudo.nick
      };
      guild::modify_member::run(client, msg->guild_id, members[i]->user->id, &params2, NULL);
    }
  }

  guild::member::dati_list_free(members);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";

  setlocale(LC_ALL, "");

  global_init();

  client *client = config_init(config_file);
  assert(NULL != client);

  setcb_command(client, "!nickChange", &on_command);

  printf("\n\nThis demonstrates how easy it is to modify the"
         " nickname of some guild member.\n\n"
         "1. Type !nickChange <user#1234> <nick>\n"
         "\nTYPE ANY KEY TO START BOT\n");
  fgetc(stdin); // wait for input

  run(client);

  cleanup(client);

  global_cleanup();
}
