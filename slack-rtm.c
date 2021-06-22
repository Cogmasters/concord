#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slack.h"
#include "slack-internal.h"

#include "cee-utils.h"


static void 
rtm_connect_from_json(char str[], size_t len, void *p_url) 
{
  bool status = false;
  json_extract(str, len, 
    "(ok):b"
    "(url):s",
    &status,
    (char*)p_url);
}

void
slack_rtm_connect(struct slack *client)
{
  struct ua_resp_handle resp_handle = { .ok_cb = &rtm_connect_from_json, .ok_obj = client->rtm.base_url };

  slack_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, "/rtm.connect");
}

static void
on_hello(struct slack_rtm *rtm, struct sized_buffer *payload)
{
  struct slack *client = rtm->p_client;

  rtm->is_ready = true;
  if (client->cbs.on_hello)
    (*client->cbs.on_hello)(client, payload->start, payload->size);
}

static void
on_message(struct slack_rtm *rtm, struct sized_buffer *payload)
{
  struct slack *client = rtm->p_client;

  if (client->cbs.on_message)
    (*client->cbs.on_message)(client, payload->start, payload->size);
}

static void
on_connect_cb(void *p_rtm, const char *ws_protocols) {
  log_info("Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_text_cb(void *p_rtm, const char *text, size_t len) 
{
  struct slack_rtm *rtm = p_rtm;

  log_trace("ON_EVENT:\t%s", text);

  char event[128] = {0};
  json_extract((char*)text, len, "(type):s", event);

  struct sized_buffer payload = {(char*)text, len};
  // @todo just two events for testing purposes
  if (STREQ(event, "hello"))
    on_hello(rtm, &payload);
  if (STREQ(event, "message"))
    on_message(rtm, &payload);
}

static void
on_close_cb(void *p_rtm, enum ws_close_reason wscode, const char *reason, size_t len)
{
  struct slack_rtm *rtm = p_rtm;
  log_warn("\n\t(code: %4d) : %zd bytes\n\t"
          "REASON: '%s'", 
          wscode, len, reason);

  rtm->is_ready = false; // reset
}

void
slack_rtm_init(struct slack_rtm *rtm, struct logconf *config)
{
  ASSERT_S(NULL != rtm->p_client, "Not meant to be called standalone");
  slack_rtm_connect(rtm->p_client);

  struct ws_callbacks cbs = {
    .data = rtm,
    .on_connect = &on_connect_cb,
    .on_text = &on_text_cb,
    .on_close = &on_close_cb
  };

  rtm->ws = ws_init(&cbs, config);
  ws_set_url(rtm->ws, rtm->base_url, NULL);
  logconf_add_id(config, rtm->ws, "SLACK_RTM");
}

void
slack_rtm_cleanup(struct slack_rtm *rtm) {
  ws_cleanup(rtm->ws);
}

/* connects to the slack websockets server */
void
slack_rtm_run(struct slack *client) 
{
  struct slack_rtm *rtm = &client->rtm;

  ASSERT_S(WS_DISCONNECTED == ws_get_status(rtm->ws), "Can't run websockets recursively");

  ws_start(rtm->ws);

  bool is_running;
  do {
    ws_perform(rtm->ws, &is_running, 1);
    if (rtm->is_ready) continue;
    
    // connection established
    
  } while (is_running);
}
