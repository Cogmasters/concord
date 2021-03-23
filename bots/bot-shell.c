#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "libdiscord.h"
#include "orka-debug.h"


struct sudo_s {
  char username[64];
  char *discriminator;
} sudo;

void 
on_ready(struct discord_client *client, const struct discord_user_dati *me) {
  fprintf(stderr, "\n\nShell-Bot succesfully connected to Discord as %s#%s!\n\n",
      me->username, me->discriminator);
}

void
on_command(struct discord_client *client,
           const struct discord_user_dati *me,
           const struct discord_channel_message_dati *msg)
{
  // make sure bot doesn't consider other bots
  if (msg->author->bot)
    return;

  if (strcmp(sudo.discriminator, msg->author->discriminator)
      || strcmp(sudo.username, msg->author->username)) {
    return; // EARLY RETURN IF NOT SUDO USER
  }

  struct discord_channel_create_message_params params = {0};

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

  discord_create_message(client, msg->channel_id, &params, NULL);
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

  struct discord_client *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_setcb_command(client, "$", &on_command);

  printf("\n\nThis bot allows navigating its host machine like"
         " a shell terminal.\n\n"
         "DISCLAIMER: This bot is potentially dangerous if not"
         " used with care.\nOnly give admin privileges to yourself"
         " or someone trustworthy.\n\n\n");

  fputs("\n\nType name of user with admin privileges (eg. user#1234)\n", stderr);
  fgets(sudo.username, sizeof(sudo.username), stdin);

  sudo.discriminator = strchr(sudo.username, '#');
  VASSERT_S(NULL != sudo.discriminator, "Wrong formatted username (%s)", sudo.username);

  sudo.discriminator[strlen(sudo.discriminator)-1] = '\0'; //remove \n
  *sudo.discriminator = '\0'; //split at #
  ++sudo.discriminator;


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
