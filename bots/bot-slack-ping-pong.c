#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "slack.h"

#include "json-actor.h"


void on_hello(struct slack *client, char payload[], size_t len) {
  fputs("\n\nSuccesfully connected to Slack!\n\n", stderr);
}

void on_message(struct slack *client, char payload[], size_t len) 
{
  char *text=NULL, *channel=NULL;
  struct sized_buffer check_bot={0};
  json_extract(payload, len, "(text):?s,(channel):?s,(bot_id):T", &text, &channel, &check_bot);
  if (check_bot.start) return; // means message belongs to a bot

  if (strstr(text, "ping"))
    slack_chat_post_message(client, channel, "pong");
  else if (strstr(text, "pong"))
    slack_chat_post_message(client, channel, "ping");

  if (text) free(text);
  if (channel) free(channel);
}

int main(int argc, char *argv[])
{
  const char *config_file;
  if (argc > 1)
    config_file = argv[1];
  else
    config_file = "bot.config";


  struct slack *client = slack_config_init(config_file);
  assert(NULL != client && "Couldn't initialize client");

  slack_set_on_hello(client, &on_hello);
  slack_set_on_message(client, &on_message);

  slack_socketmode_run(client);

  slack_cleanup(client);
}

