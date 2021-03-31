#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // for isspace()

#include "slack.h"
#include "slack-common.h"

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
  char *app_token = ua_config_get_field(client->adapter.ua, "slack.app-token");
  if (!app_token) ERR("Missing app token");

  char auth[128];
  int ret = snprintf(auth, sizeof(auth), "Bearer %s", app_token);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");
  ua_reqheader_add(client->adapter.ua, "Authorization", auth);

  struct resp_handle resp_handle = { .ok_cb = &apps_connections_open_from_json, .ok_obj = client->sm.base_url };

  slack_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_POST, "/apps.connections.open");

  char *bot_token = ua_config_get_field(client->adapter.ua, "slack.bot-token");
  if (!bot_token) ERR("Missing bot token");

  ret = snprintf(auth, sizeof(auth), "Bearer %s", bot_token);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");
  ua_reqheader_add(client->adapter.ua, "Authorization", auth);

  free(app_token);
  free(bot_token);
}

static int
on_startup_cb(void *p_sm) {
  return 1;
}

static void
on_connect_cb(void *p_sm, const char *ws_protocols) {
  D_PRINT("Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_text_cb(void *p_sm, const char *text, size_t len) {
  PRINT("%.*s", (int)len, text);
}

static void
on_close_cb(void *p_sm, enum ws_close_reason wscode, const char *reason, size_t len)
{
  struct slack_socketmode *sm = p_sm;
  ws_set_status(sm->ws, WS_DISCONNECTED);

  PRINT("(code: %4d) : %zd bytes\n\t"
          "REASON: '%s'", 
          wscode, len, reason);
}

void
slack_socketmode_init(struct slack_socketmode *sm, const char config_file[])
{
  if (!config_file) ERR("Missing config file");
  struct ws_callbacks cbs = {
    .data = sm,
    .on_startup = &on_startup_cb,
    .on_iter_end = NULL,
    .on_text_event = NULL,
    .on_connect = &on_connect_cb,
    .on_text = &on_text_cb,
    .on_close = &on_close_cb
  };

  // @todo temporary debug_reconnect while development phase
  strncat(sm->base_url, "&debug_reconnects=true", sizeof(sm->base_url));

  sm->ws = ws_config_init(sm->base_url, &cbs, "SLACK SOCKET MODE", config_file);

  ws_set_refresh_rate(sm->ws, 1);
  ws_set_max_reconnect(sm->ws, 15);

  if (pthread_mutex_init(&sm->lock, NULL))
    ERR("Couldn't initialize pthread mutex");
}

void
slack_socketmode_cleanup(struct slack_socketmode *sm)
{
  ws_cleanup(sm->ws);
  pthread_mutex_destroy(&sm->lock);
}

/* connects to the slack websockets server */
void
slack_socketmode_run(struct slack_socketmode *sm) {
  ws_run(sm->ws);
}

void
slack_socketmode_shutdown(struct slack_socketmode *sm) 
{
  ws_set_status(sm->ws, WS_DISCONNECTED);
  char reason[] = "Shutdown gracefully";
  ws_close(sm->ws, WS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}
