#include <string.h>

#include "slack.h"
#include "slack-internal.h"

struct slack* 
slack_config_init(const char config_file[])
{
  struct slack *new_client = calloc(1, sizeof *new_client);

  logconf_setup(&new_client->config, config_file);
  new_client->bot_token = logconf_get_field(&new_client->config, "slack.bot_token");
  new_client->app_token = logconf_get_field(&new_client->config, "slack.app_token");

  new_client->adapter.p_client = new_client;
  new_client->rtm.p_client = new_client;
  new_client->sm.p_client = new_client;
  slack_adapter_init(
    &new_client->adapter, 
    &new_client->config,
    &new_client->bot_token);
  slack_rtm_init(&new_client->rtm, &new_client->config);
  slack_socketmode_init(&new_client->sm, &new_client->config);

  return new_client;
}

void 
slack_cleanup(struct slack *client)
{
  logconf_cleanup(&client->config);
  slack_adapter_cleanup(&client->adapter);
  slack_rtm_cleanup(&client->rtm);
  slack_socketmode_cleanup(&client->sm);

  free(client);
}

void
slack_set_on_idle(struct slack *client, idle_cb *callback) {
  client->cbs.on_hello = callback;
}

void
slack_set_on_hello(struct slack *client, idle_cb *callback) {
  client->cbs.on_hello = callback;
}

void
slack_set_on_message(struct slack *client, idle_cb *callback) {
  client->cbs.on_message = callback;
}

void
slack_rtm_send_message(struct slack *client, char channel[], char text[]) 
{
  if (WS_CONNECTED != ws_get_status(client->rtm.ws)) {
    log_warn("Can't send messages via RTM unless connected");
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
    log_warn("Missing 'channel'");
    return;
  }

  if (!client->bot_token.start) {
    log_warn("Missing bot token");
    return;
  }

  char payload[4096+1];
  json_inject(payload, sizeof(payload), 
      "(channel):s"
      "(token):.*s"
      "(text):s", 
      channel, 
      (int)client->bot_token.size, client->bot_token.start, 
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
