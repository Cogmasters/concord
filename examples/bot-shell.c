#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <locale.h>
#include <limits.h>

#include "discord.h"

struct {
  char username[64];
  char *discriminator;
} SUDO;

void on_ready(struct discord *client, const struct discord_user *bot)
{
  log_info("Shell-Bot succesfully connected to Discord as %s#%s!",
           bot->username, bot->discriminator);
}

void on_cd(struct discord *client,
           const struct discord_user *bot,
           const struct discord_message *msg)
{
  if (msg->author->bot) return;

  if (strcmp(SUDO.discriminator, msg->author->discriminator) ||
      strcmp(SUDO.username, msg->author->username))
  {
    return; // EARLY RETURN IF NOT SUDO USER
  }

  chdir(*msg->content ? msg->content : ".");
  char path[PATH_MAX];
  struct discord_create_message_params params = { .content = getcwd(
                                                    path, sizeof(path)) };
  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_less_like(struct discord *client,
                  const struct discord_user *bot,
                  const struct discord_message *msg)
{
  if (msg->author->bot) return;

  if (strcmp(SUDO.discriminator, msg->author->discriminator) ||
      strcmp(SUDO.username, msg->author->username))
  {
    return; // EARLY RETURN IF NOT SUDO USER
  }

  struct discord_create_message_params params = { 0 };
  if (*msg->content) {
    char attachment_url[512];
    snprintf(attachment_url, sizeof(attachment_url), "attachment://%s",
             msg->content);

    params.embeds = (struct discord_embed *[]){
      &(struct discord_embed){
        .title = msg->content,
        .thumbnail =
          &(struct discord_embed_thumbnail){ .url = attachment_url } },
      (void *){ NULL } // end of array
    };
    params.attachments = (struct discord_attachment *[]){
      &(struct discord_attachment){ .filename = msg->content },
      (void *){ NULL } // end of array
    };
  }
  else {
    params.content = "No file specified";
  }

  discord_create_message(client, msg->channel_id, &params, NULL);
}

void on_default(struct discord *client,
                const struct discord_user *bot,
                const struct discord_message *msg)
{
  if (msg->author->bot) return;

  if (strcmp(SUDO.discriminator, msg->author->discriminator) ||
      strcmp(SUDO.username, msg->author->username))
  {
    return; // EARLY RETURN IF NOT SUDO USER
  }

  char *cmd = strchr(msg->content, ' '); // get first occurence of space
  size_t len;
  if (cmd) {
    len = cmd - msg->content;
    ++cmd; // skip space
  }
  else {
    len = strlen(msg->content);
  }

  FILE *fp = popen(msg->content, "r");
  if (NULL == fp) {
    printf("Failed to run command");
    return;
  }

  const size_t MAX_FSIZE = 5e6; // 5 mb
  char *path = calloc(1, MAX_FSIZE);
  char *pathtmp = calloc(1, MAX_FSIZE);

  while (NULL != fgets(path, MAX_FSIZE, fp)) {
    strncat(pathtmp, path, MAX_FSIZE - 1);
  }

  const size_t fsize = strlen(pathtmp);
  struct discord_create_message_params params;
  if (fsize > DISCORD_MAX_MESSAGE_LEN)
    params = (struct discord_create_message_params){
      .attachments =
        (struct discord_attachment *[]){
          &(struct discord_attachment){ .content = pathtmp, .size = fsize },
          (void *){ NULL } // end of array
        }
    };
  else
    params = (struct discord_create_message_params){ .content = pathtmp };
  discord_create_message(client, msg->channel_id, &params, NULL);

  pclose(fp);
  free(path);
  free(pathtmp);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "../config.json";

  setlocale(LC_ALL, "");

  discord_global_init();

  struct discord *client = discord_config_init(config_file);
  assert(NULL != client);

  discord_set_prefix(client, "$");
  discord_set_on_command(client, NULL, &on_default);
  discord_set_on_command(client, "cd", &on_cd);
  discord_set_on_command(client, "less", &on_less_like);
  discord_set_on_command(client, "cat", &on_less_like);
  discord_set_on_command(client, "hexdump", &on_less_like);

  printf("\n\nThis bot allows navigating its host machine like"
         " a shell terminal.\n\n"
         "DISCLAIMER: This bot is potentially dangerous if not"
         " used with care.\nOnly give admin privileges to yourself"
         " or someone trustworthy.\n\n\n");

  fputs("\n\nType name of user with admin privileges (eg. user#1234)\n",
        stderr);
  fgets(SUDO.username, sizeof(SUDO.username), stdin);

  SUDO.discriminator = strchr(SUDO.username, '#');
  assert(NULL != SUDO.discriminator &&
         "Missing '#' delimiter (eg. user#1234)");

  SUDO.discriminator[strlen(SUDO.discriminator) - 1] = '\0'; // remove \n
  *SUDO.discriminator = '\0'; // split at #
  ++SUDO.discriminator;

  discord_run(client);

  discord_cleanup(client);

  discord_global_cleanup();
}
