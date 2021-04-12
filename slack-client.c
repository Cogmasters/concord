#include <string.h>

#include "slack.h"
#include "slack-common.h"

struct slack* 
slack_config_init(const char config_file[])
{
  struct slack *new_client = calloc(1, sizeof *new_client);

  new_client->adapter.p_client = new_client;
  new_client->rtm.p_client = new_client;
  new_client->sm.p_client = new_client;
  slack_adapter_config_init(&new_client->adapter, config_file);
  slack_rtm_config_init(&new_client->rtm, config_file);
  slack_socketmode_config_init(&new_client->sm, config_file);

  return new_client;
}

void 
slack_cleanup(struct slack *client)
{
  slack_adapter_cleanup(&client->adapter);
  slack_rtm_cleanup(&client->rtm);
  slack_socketmode_cleanup(&client->sm);

  free(client);
}

void
slack_on_idle(struct slack *client, idle_cb *callback) {
  client->cbs.on_hello = callback;
}

void
slack_on_hello(struct slack *client, idle_cb *callback) {
  client->cbs.on_hello = callback;
}

void
slack_on_message(struct slack *client, idle_cb *callback) {
  client->cbs.on_message = callback;
}

void
slack_rtm_send_message(struct slack *client, char channel[], char text[]) 
{
  if (WS_CONNECTED != ws_get_status(client->rtm.ws)) {
    PRINT("Can't send messages via RTM unless connected");
    return;
  }

  char payload[4096 + 1];
  int ret = json_inject(payload, sizeof(payload),
              "(id):1"
              "(type):\"message\""
              "(channel):s"
              "(text):s",
              channel, text);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  ws_send_text(client->rtm.ws, payload, ret);
}

// @todo move to slack-chat.c
// @todo missing response object
void
slack_chat_post_message(struct slack *client, char channel[], char text[])
{
  if (IS_EMPTY_STRING(channel)) {
    D_PRINT("Missing 'channel'");
    return;
  }

  struct sized_buffer token = ua_config_get_field(client->adapter.ua, "slack.bot-token");
  if (!token.start) {
    D_PRINT("Missing bot token");
    return;
  }

  char payload[4096+1];
  json_inject(payload, sizeof(payload), 
      "(channel):s"
      "(token):.*s"
      "(text):s", 
      channel, 
      (int)token.size, token.start, 
      text);

  ua_reqheader_add(client->adapter.ua, "Content-type", "application/json");

  struct sized_buffer req_body = {payload, strlen(payload)};

  slack_adapter_run(
    &client->adapter,
    NULL,
    &req_body,
    HTTP_POST, "/chat.postMessage");

  ua_reqheader_add(client->adapter.ua, "Content-type", "application/x-www-form-urlencoded");
}
