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

  new_client->webapi.p_client = new_client;
  new_client->sm.p_client = new_client;
  slack_webapi_init(&new_client->webapi, &new_client->config, &new_client->bot_token);
  slack_sm_init(&new_client->sm, &new_client->config);

  return new_client;
}

void 
slack_cleanup(struct slack *client)
{
  logconf_cleanup(&client->config);
  slack_webapi_cleanup(&client->webapi);
  slack_sm_cleanup(&client->sm);

  free(client);
}

void 
slack_sm_set_event_handler(struct slack *client, slack_event_mode_cb fn) {
  client->sm.event_handler = fn;
}

void
slack_sm_set_on_idle(struct slack *client, slack_idle_cb callback) {
  client->sm.cbs.on_hello = callback;
}

void
slack_sm_set_on_hello(struct slack *client, slack_idle_cb callback) {
  client->sm.cbs.on_hello = callback;
}

void
slack_sm_set_on_message(struct slack *client, slack_idle_cb callback) {
  client->sm.cbs.on_message = callback;
}

void
slack_sm_set_on_block_actions(struct slack *client, slack_idle_cb callback) {
  client->sm.cbs.on_block_actions = callback;
}

void
slack_sm_set_on_message_actions(struct slack *client, slack_idle_cb callback) {
  client->sm.cbs.on_message_actions = callback;
}

void
slack_sm_set_on_view_closed(struct slack *client, slack_idle_cb callback) {
  client->sm.cbs.on_view_closed = callback;
}

void
slack_sm_set_on_view_submission(struct slack *client, slack_idle_cb callback) {
  client->sm.cbs.on_view_submission = callback;
}
