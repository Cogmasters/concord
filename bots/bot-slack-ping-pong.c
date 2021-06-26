#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "slack.h"

#include "json-actor.h"
#include "log.h"

const char USER_ID[32];

void on_hello(struct slack *client, const char payload[], const size_t len) {
  log_info("Succesfully connected to Slack!");
}

void on_message(struct slack *client, const char payload[], const size_t len) 
{
  char *text=NULL, channel[256]="", user[32]="";

  log_info("%.*s", len, payload);
  json_extract((char*)payload, len, 
    "(text):?s"
    "(channel):s"
    "(user):s", 
    &text, channel, user);

  if (text && strcmp(user, USER_ID) && *channel) {
    if (strstr(text, "ping"))
      slack_chat_post_message(client, channel, "pong");
    else if (strstr(text, "pong"))
      slack_chat_post_message(client, channel, "ping");
    free(text);
  }
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

  struct sized_buffer text={0};
  slack_auth_test(client, &text);
  json_extract(text.start, text.size, "(user_id):s", (char*)USER_ID);

  slack_set_on_hello(client, &on_hello);
  slack_set_on_message(client, &on_message);

  slack_socketmode_run(client);

  slack_cleanup(client);
}

