#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slack.h"
#include "slack-internal.h"

#include "cee-utils.h"


static void 
apps_connections_open_from_json(char str[], size_t len, void *p_url) 
{
  bool status=false;
  struct sized_buffer messages={0};
  json_extract(str, len, 
    "(ok):b"
    "(url):s"
    "(response_metadata.messages):T",
    &status, (char*)p_url, &messages);

  VASSERT_S(true == status,
      "Couldn't fetch connections for websockets:\n\t\tMessage: %.*s", 
      (int)messages.size, messages.start);
}

void
slack_apps_connections_open(struct slack *client)
{

  ASSERT_S(NULL != client->bot_token.start, "Missing bot token");
  ASSERT_S(NULL != client->app_token.start, "Missing app token");

  char auth[128]="";
  char base_url[UA_MAX_URL_LEN]="";
  size_t ret;

  ret = snprintf(auth, sizeof(auth), "Bearer %.*s", (int)client->app_token.size, client->app_token.start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");
  ua_reqheader_add(client->adapter.ua, "Authorization", auth);

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &apps_connections_open_from_json, 
    .ok_obj = base_url 
  };

  slack_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_POST, "/apps.connections.open");

  ret = snprintf(auth, sizeof(auth), "Bearer %.*s", (int)client->bot_token.size, client->bot_token.start);
  ASSERT_S(ret < sizeof(auth), "Out of bounds write attempt");
  ua_reqheader_add(client->adapter.ua, "Authorization", auth);

/// @note enable this to test reconnect
#if 0
  size_t len = strlen(base_url);
  snprintf(base_url+len, sizeof(base_url)-len, "&debug_reconnects=true");
#endif
  ws_set_url(client->sm.ws, base_url, NULL);
}

static void
send_acknowledge(struct slack_socketmode *sm, const char envelope_id[])
{
  char payload[512];
  size_t ret = json_inject(payload, sizeof(payload), 
                "(envelope_id):s", envelope_id);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  log_info("Sending ACK(%zu bytes)", ret);
  ws_send_text(sm->ws, payload, ret);
}

static void
on_hello(struct slack_socketmode *sm, const char *text, size_t len)
{
  struct slack *client = sm->p_client;

  sm->is_ready = true;
  sm->hbeat.interval_ms = 0;
  sm->hbeat.tstamp = cee_timestamp_ms();

  long interval_s=0;
  json_extract((char*)text, len, 
    "(debug_info.approximate_connection_time):ld", &interval_s);
  sm->hbeat.interval_ms = 1000*interval_s;

  if (client->cbs.on_hello)
    (*client->cbs.on_hello)(client, text, len);
}

static void
on_message(struct slack_socketmode *sm, struct sized_buffer *event)
{
  if (sm->p_client->cbs.on_message)
    (*sm->p_client->cbs.on_message)(sm->p_client, event->start, event->size);
}

static void
on_events_api(struct slack_socketmode *sm, const char *text, size_t len)
{
  char type[64]="";
  char envelope_id[64]="";
  bool accepts_response_payload=false;
  struct sized_buffer t_event={0};
  json_extract((char*)text, len, 
      "(payload.event):T"
      "(payload.event.type):s"
      "(envelope_id):s"
      "(accepts_response_payload):b", 
      &t_event, type, envelope_id, &accepts_response_payload);

  if (*envelope_id) {
    send_acknowledge(sm, envelope_id);
  }

  if (*type) {
    if (STREQ(type, "message"))
      on_message(sm, &t_event);
  }
}

static void
on_connect_cb(void *p_sm, struct websockets *ws, const char *ws_protocols) {
  log_info("Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_sm, struct websockets *ws, enum ws_close_reason wscode, const char *reason, size_t len)
{
  struct slack_socketmode *sm = p_sm;

  sm->is_ready = false; // reset

  log_warn("\n\t(code: %4d) : %zd bytes\n\t"
           "REASON: '%s'", 
           wscode, len, reason);
}

static void
on_text_cb(void *p_sm, struct websockets *ws, const char *text, size_t len) 
{
  struct slack_socketmode *sm = p_sm;

  log_trace("ON_EVENT(%zu bytes)", len);

  char type[64]="";
  json_extract((char*)text, len, "(type):s", type);

  // @todo just two events for testing purposes
  if (STREQ(type, "hello"))
    on_hello(sm, text, len);
  else if (STREQ(type, "events_api"))
    on_events_api(sm, text, len);
}

void
slack_socketmode_init(struct slack_socketmode *sm, struct logconf *config)
{
  ASSERT_S(NULL != sm->p_client, "Not meant to be called standalone");

  struct ws_callbacks cbs = {
    .data = sm,
    .on_connect = &on_connect_cb,
    .on_text = &on_text_cb,
    .on_close = &on_close_cb
  };
  sm->ws = ws_init(&cbs, config);
  logconf_add_id(config, sm->ws, "SLACK_SOCKETMODE");

  slack_apps_connections_open(sm->p_client);
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

  ws_start(sm->ws);

  bool is_running=false;
  while (1) {
    ws_perform(sm->ws, &is_running, 1);
    if (!is_running)break; // exit event loop
    if (!sm->is_ready) continue; // wait until on_hello()
    
    // connection established

    /*check if timespan since first pulse is greater than
     * minimum heartbeat interval required */
    if (sm->hbeat.interval_ms < (ws_timestamp(sm->ws) - sm->hbeat.tstamp)) 
    {
      slack_apps_connections_open(sm->p_client);
      sm->hbeat.tstamp = ws_timestamp(sm->ws); //update heartbeat timestamp
    }
  }
}
