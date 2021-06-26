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
#if 0
  slack_rtm_init(&new_client->rtm, &new_client->config);
#endif
  slack_socketmode_init(&new_client->sm, &new_client->config);

  return new_client;
}

void 
slack_cleanup(struct slack *client)
{
  logconf_cleanup(&client->config);
  slack_adapter_cleanup(&client->adapter);
#if 0
  slack_rtm_cleanup(&client->rtm);
#endif
  slack_socketmode_cleanup(&client->sm);

  free(client);
}

void
slack_set_on_idle(struct slack *client, idle_cb callback) {
  client->cbs.on_hello = callback;
}

void
slack_set_on_hello(struct slack *client, idle_cb callback) {
  client->cbs.on_hello = callback;
}

void
slack_set_on_message(struct slack *client, idle_cb callback) {
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
  size_t ret = json_inject(payload, sizeof(payload), 
                "(channel):s"
                "(token):.*s"
                "(text):s", 
                channel, 
                (int)client->bot_token.size, client->bot_token.start, 
                text);

  ua_reqheader_add(client->adapter.ua, "Content-type", "application/json");

  struct sized_buffer req_body = { payload, ret };

  slack_adapter_run(
    &client->adapter,
    NULL,
    &req_body,
    HTTP_POST, "/chat.postMessage");

  ua_reqheader_add(client->adapter.ua, "Content-type", "application/x-www-form-urlencoded");
}

static void
auth_test_from_json(char str[], size_t len, void *p_resp) 
{
  *(struct sized_buffer*)p_resp = (struct sized_buffer){ 
                                    .start = strdup(str), 
                                    .size = len 
                                  }; 
}

// @todo move to slack-auth.c
void
slack_auth_test(struct slack *client, struct sized_buffer *p_resp)
{
  struct ua_resp_handle resp_handle = {
    .ok_cb = p_resp ? &auth_test_from_json : NULL,
    .ok_obj = p_resp
  };

  slack_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_POST, "/auth.test");
}
