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
  fprintf(stderr, "\n\nBash-Bot succesfully connected to Discord as %s#%s!\n\n",
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

  message::create::params params = {0};

  if (STRNEQ(msg->content, "ls", 2) || STRNEQ(msg->content, "wc", 2)) {
    FILE *fp = popen(msg->content, "r");
    ASSERT_S(NULL != fp, "Failed to run command");

    char path[1024] = "";
    char pathtmp[1024] = "";
    while (NULL != fgets(path, sizeof(path), fp)) {
      path[strlen(path)-1] = ' '; //replace \n with space
      strncat(pathtmp, path, sizeof(pathtmp)-1);
    }

    params.content = pathtmp;

    pclose(fp);
  }
  if (STRNEQ(msg->content, "less", 4)) {
    FILE *fp = popen(msg->content, "r");
    ASSERT_S(NULL != fp, "Failed to run command");

    char path[1024] = "";
    char pathtmp[1024] = "```\n";
    while (NULL != fgets(path, sizeof(path), fp)) {
      strncat(pathtmp, path, sizeof(pathtmp)-1);
    }
    strncat(pathtmp, "\n```", sizeof(pathtmp)-1);

    params.content = pathtmp;

    pclose(fp);
  }
  else if (STRNEQ(msg->content, "cd", 2)) {
    char path[100];

    chdir(msg->content + 3);
    getcwd(path, sizeof(path));

    params.content = path;
  }

  message::create::run(client, msg->channel_id, &params, NULL); 
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

  command_prefix(client, "$");
  setcb_message_command(client, &on_command);

  run(client);

  cleanup(client);

  global_cleanup();
}
