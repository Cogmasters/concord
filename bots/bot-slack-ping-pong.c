#define _GNU_SOURCE /* strcasestr */
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
  json_extract(payload, len, "(text):?s,(channel):?s", &text, &channel);

  if (strcasestr(text, "ping"))
    slack_send_message(client, channel, "pong");
  else if (strcasestr(text, "pong"))
    slack_send_message(client, channel, "ping");

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
  assert(NULL != client);

  slack_on_hello(client, &on_hello);
  slack_on_message(client, &on_message);

  slack_rtm_run(client);

  slack_cleanup(client);
}

