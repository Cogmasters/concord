#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slack.h"
#include "slack-internal.h"

#include "orka-utils.h"


static void 
apps_connections_open_from_json(char str[], size_t len, void *p_url) 
{
  bool status = false;
  struct sized_buffer metadata = {0}, messages = {0};
  json_extract(str, len, 
    "(ok):b"
    "(url):s"
    "(response_metadata):T",
    &status,
    (char*)p_url,
    &metadata);

  if (metadata.start) {
    json_extract(metadata.start, metadata.size, "(messages):T", &messages);
  }

  VASSERT_S(true == status, "Couldn't fetch connections for websockets:\n\t\tMessage: %.*s", (int)messages.size, messages.start);
}

void
slack_apps_connections_open(struct slack *client)
{
  struct sized_buffer app_token = ua_config_get_field(client->adapter.ua, "slack.app_token");
  if (!app_token.start) {
    log_warn("Missing app token");
    return;
  }

  char auth[128];
  int ret = snprintf(auth, sizeof(auth), "Bearer %.*s", (int)app_token.size, app_token.start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");
  ua_reqheader_add(client->adapter.ua, "Authorization", auth);

  struct ua_resp_handle resp_handle = { .ok_cb = &apps_connections_open_from_json, .ok_obj = client->sm.base_url };

  slack_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_POST, "/apps.connections.open");

  struct sized_buffer bot_token = ua_config_get_field(client->adapter.ua, "slack.bot_token");
  if (!bot_token.start) ERR("Missing bot token");

  ret = snprintf(auth, sizeof(auth), "Bearer %.*s", (int)bot_token.size, bot_token.start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");
  ua_reqheader_add(client->adapter.ua, "Authorization", auth);
}

static void
on_hello(struct slack_socketmode *sm)
{
  struct slack *client = sm->p_client;

  ws_set_status(sm->ws, WS_CONNECTED);
  if (!client->cbs.on_hello) return;

  (*client->cbs.on_hello)(client, sm->text.payload.start, sm->text.payload.size);
}

static void
on_message(struct slack_socketmode *sm, struct sized_buffer *event)
{
  if (!sm->p_client->cbs.on_message) return;

  (*sm->p_client->cbs.on_message)(sm->p_client, event->start, event->size);
}

static void
on_events_api(struct slack_socketmode *sm)
{
  struct sized_buffer t_event = {0}, t_type = {0};
  json_extract(sm->text.payload.start, sm->text.payload.size, 
      "(event):T", &t_event);
  if (t_event.start) {
    json_extract(t_event.start, t_event.size, "(type):T", &t_type);
  }

  if (STRNEQ("message", t_type.start, sizeof("message")-1))
    on_message(sm, &t_event);
}

static void
on_connect_cb(void *p_sm, const char *ws_protocols) {
  log_info("Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_text_cb(void *p_sm, const char *text, size_t len) 
{
  struct slack_socketmode *sm = p_sm;

  log_trace("ON_EVENT:\t%s", text);

  json_extract((char*)text, len, 
      "(payload):T"
      "(envelope_id):s"
      "(type):s"
      "(accepts_response_payload):b",
      &sm->text.payload,
      sm->text.envelope_id,
      sm->text.type,
      &sm->text.accepts_response_payload);

  // @todo just two events for testing purposes
  if (STREQ(sm->text.type, "hello"))
    on_hello(sm);
  if (STREQ(sm->text.type, "events_api"))
    on_events_api(sm);
}

static void
on_close_cb(void *p_sm, enum ws_close_reason wscode, const char *reason, size_t len)
{
  struct slack_socketmode *sm = p_sm;
  ws_set_status(sm->ws, WS_DISCONNECTED);

  log_warn("\n\t(code: %4d) : %zd bytes\n\t"
           "REASON: '%s'", 
           wscode, len, reason);
}

void
slack_socketmode_config_init(struct slack_socketmode *sm, const char config_file[])
{
  ASSERT_S(NULL != sm->p_client, "Not meant to be called standalone");
  slack_apps_connections_open(sm->p_client);

  if (!config_file) ERR("Missing config file");
  struct ws_callbacks cbs = {
    .data = sm,
    .on_connect = &on_connect_cb,
    .on_text = &on_text_cb,
    .on_close = &on_close_cb
  };

  // @todo temporary debug_reconnect while development phase
  strncat(sm->base_url, "&debug_reconnects=true", sizeof(sm->base_url));

  sm->ws = ws_config_init(sm->base_url, &cbs, "SLACK SOCKET MODE", config_file);

  ws_set_max_reconnect(sm->ws, 15);
}

void
slack_socketmode_cleanup(struct slack_socketmode *sm) {
  ws_cleanup(sm->ws);
}

/* connects to the slack websockets server */
void
slack_socketmode_run(struct slack *client) 
{
  struct slack_socketmode *sm = &client->sm;

  ASSERT_S(WS_DISCONNECTED == ws_get_status(sm->ws), "Can't run websockets recursively");

  bool is_running;
  do {
    ws_perform(sm->ws, &is_running);

    // wait for activity or timeout
    ws_wait_activity(sm->ws, 1);

    if (WS_CONNECTED != ws_get_status(sm->ws))
      continue;
    
    // connection established
    
  } while (is_running);
}

void
slack_socketmode_shutdown(struct slack *client) {
  ws_set_status(client->sm.ws, WS_SHUTDOWN);
}
