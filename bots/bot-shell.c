#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "discord.h"


struct {
  char username[64];
  char *discriminator;
} SUDO;

void 
on_ready(struct discord *client, const struct discord_user *bot) {
  fprintf(stderr, "\n\nShell-Bot succesfully connected to Discord as %s#%s!\n\n",
      bot->username, bot->discriminator);
}

void
on_command(struct discord *client,
           const struct discord_user *bot,
           const struct discord_message *msg)
{
  if (msg->author->bot) return;

  if (strcmp(SUDO.discriminator, msg->author->discriminator)
      || strcmp(SUDO.username, msg->author->username)) 
  {
    return; // EARLY RETURN IF NOT SUDO USER
  }

  char *cmd = strchr(msg->content, ' '); //get first occurence of space
  size_t len;
  if (cmd) {
    len = cmd - msg->content;
    ++cmd; //skip space
  }
  else {
    len = strlen(msg->content);
  }

  struct discord_create_message_params params = {};
  if (0 == strncmp(msg->content, "cd", len)) {
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

    if (0 == strncmp(msg->content, "less", len) 
        || 0 == strncmp(msg->content, "cat", len)
        || 0 == strncmp(msg->content, "hexdump", len)) 
    {
      strncat(pathtmp, "```\n", MAX_FSIZE-1);
      while (NULL != fgets(path, MAX_FSIZE, fp)) {
        strncat(pathtmp, path, MAX_FSIZE-1);
      }
      strncat(pathtmp, "\n```", MAX_FSIZE-1);

      if (strlen(pathtmp) > MAX_MESSAGE_LEN)
        params.file.name = 1 + msg->content + len;
      else
        params.content = pathtmp;
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

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_set_on_command(client, "$", &on_command);

  printf("\n\nThis bot allows navigating its host machine like"
         " a shell terminal.\n\n"
         "DISCLAIMER: This bot is potentially dangerous if not"
         " used with care.\nOnly give admin privileges to yourself"
         " or someone trustworthy.\n\n\n");

  fputs("\n\nType name of user with admin privileges (eg. user#1234)\n", stderr);
  fgets(SUDO.username, sizeof(SUDO.username), stdin);

  SUDO.discriminator = strchr(SUDO.username, '#');
  assert(NULL != SUDO.discriminator && "Wrong formatted username");

  SUDO.discriminator[strlen(SUDO.discriminator)-1] = '\0'; //remove \n
  *SUDO.discriminator = '\0'; //split at #
  ++SUDO.discriminator;


  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
