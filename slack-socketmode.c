#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "work.h"

#include "slack.h"
#include "slack-internal.h"

/* TODO: specs-generated */
static enum slack_sm_types
sm_eval_type(char type[])
{
  // EVENT API PAYLOADS
  if (STREQ("message", type)) return SLACK_SOCKETMODE_TYPE_MESSAGE;

  // INTERACTION PAYLOADS
  if (STREQ("block_actions", type)) return SLACK_SOCKETMODE_TYPE_BLOCK_ACTIONS;
  if (STREQ("message_actions", type))
    return SLACK_SOCKETMODE_TYPE_MESSAGE_ACTIONS;
  if (STREQ("view_closed", type)) return SLACK_SOCKETMODE_TYPE_VIEW_CLOSED;
  if (STREQ("view_submission", type))
    return SLACK_SOCKETMODE_TYPE_VIEW_SUBMISSION;

  return SLACK_SOCKETMODE_TYPE_NONE;
}

static void
send_ack(struct slack_sm *sm, const char envelope_id[])
{
  struct ws_info info = { 0 };
  char payload[512];
  size_t ret;

  ret = json_inject(payload, sizeof(payload), "(envelope_id):s", envelope_id);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  log_info(
    ANSICOLOR("SEND", ANSI_FG_BRIGHT_GREEN) " ACK (%d bytes) [@@@_%zu_@@@]",
    ret, info.loginfo.counter);

  ws_send_text(sm->ws, &info, payload, ret);
}

static void
on_hello(struct slack_sm *sm, const char *text, size_t len)
{
  long interval_sec = 0;

  sm->is_ready = true;
  sm->hbeat.interval_ms = 0;
  sm->hbeat.tstamp = cee_timestamp_ms();

  json_extract((char *)text, len,
               "(debug_info.approximate_connection_time):ld", &interval_sec);

  sm->hbeat.interval_ms = 1000 * interval_sec;

  if (sm->cbs.on_hello) sm->cbs.on_hello(CLIENT(sm, sm), text, len);
}

static void
context_run(void *p_cxt)
{
  struct slack_event *cxt = p_cxt;

  log_info("Thread " ANSICOLOR("starts", ANSI_FG_RED) " to serve %s",
           cxt->str_type);

  cxt->on_event(CLIENT(cxt->sm, sm), cxt->data.start, cxt->data.size);

  log_info("Thread " ANSICOLOR("exits", ANSI_FG_RED) " from serving %s",
           cxt->str_type);

  free(cxt->data.start);
  free(cxt);
}

static void
on_events(struct slack_sm *sm, struct sized_buffer *data, char str_type[])
{
  struct slack *client = CLIENT(sm, sm);

  slack_on_event on_event = NULL;
  enum slack_event_scheduler mode;
  enum slack_sm_types type;

  switch (type = sm_eval_type(str_type)) {
  case SLACK_SOCKETMODE_TYPE_MESSAGE:
    on_event = sm->cbs.on_message;
    break;
  case SLACK_SOCKETMODE_TYPE_BLOCK_ACTIONS:
    on_event = sm->cbs.on_block_actions;
    break;
  case SLACK_SOCKETMODE_TYPE_MESSAGE_ACTIONS:
    on_event = sm->cbs.on_message_actions;
    break;
  case SLACK_SOCKETMODE_TYPE_VIEW_CLOSED:
    on_event = sm->cbs.on_view_closed;
    break;
  case SLACK_SOCKETMODE_TYPE_VIEW_SUBMISSION:
    on_event = sm->cbs.on_view_submission;
    break;
  default:
    log_warn("Expected unimplemented Socketmode type (code: %d)", type);
    break;
  }

  mode = sm->cbs.scheduler(client, data, type);
  if (!on_event) return;

  switch (mode) {
  case SLACK_EVENT_IGNORE:
    break;
  case SLACK_EVENT_MAIN_THREAD:
    on_event(client, data->start, data->size);
    break;
  case SLACK_EVENT_WORKER_THREAD: {
    struct slack_event *cxt = malloc(sizeof *cxt);
    int ret;

    cxt->data.size = cee_strndup(data->start, data->size, &cxt->data.start);
    cxt->sm = sm;
    cxt->type = type;
    cxt->on_event = on_event;
    snprintf(cxt->str_type, sizeof(cxt->str_type), "%s", str_type);

    ret = work_run(&context_run, cxt);
    VASSERT_S(0 == ret, "Couldn't create task (code %d)", ret);
  } break;
  default:
    ERR("Unknown event handling mode (code: %d)", mode);
  }
}

static void
on_connect_cb(void *p_sm,
              struct websockets *ws,
              struct ws_info *info,
              const char *ws_protocols)
{
  log_info("Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_sm,
            struct websockets *ws,
            struct ws_info *info,
            enum ws_close_reason wscode,
            const char *reason,
            size_t len)
{
  struct slack_sm *sm = p_sm;

  sm->is_ready = false; // reset

  log_warn(ANSICOLOR("CLOSE", ANSI_FG_RED) " (code: %4d, %zu bytes): '%.*s'",
           wscode, len, (int)len, reason);
}

static void
on_text_cb(void *p_sm,
           struct websockets *ws,
           struct ws_info *info,
           const char *text,
           size_t len)
{
  struct slack_sm *sm = p_sm;

  struct sized_buffer data = { 0 };
  char event_type[64] = "";
  bool accepts_response_payload = false;
  char type[64] = "", envelope_id[64] = "";

  json_extract((char *)text, len, "(type):s,(envelope_id):s", type,
               envelope_id);

  if (*envelope_id) send_ack(sm, envelope_id);

  if (STREQ(type, "hello")) {
    on_hello(sm, text, len);
    return;
  }

  if (STREQ(type, "events_api")) {
    json_extract((char *)text, len,
                 "(payload):T"
                 "(payload.event.type):s"
                 "(accepts_response_payload):b",
                 &data, event_type, &accepts_response_payload);
  }
  else if (STREQ(type, "interactive")) {
    json_extract((char *)text, len,
                 "(payload):T"
                 "(payload.type):s"
                 "(accepts_response_payload):b",
                 &data, event_type, &accepts_response_payload);
  }

  log_trace(
    ANSICOLOR("RCV",
              ANSI_FG_BRIGHT_YELLOW) " %s%s%s (%zu bytes) [@@@_%zu_@@@]",
    type, *event_type ? " -> " : "", event_type, len, info->loginfo.counter);

  on_events(sm, &data, event_type);
}

static slack_event_scheduler_t
default_scheduler_cb(struct slack *a,
                     struct sized_buffer *b,
                     enum slack_sm_types d)
{
  return SLACK_EVENT_MAIN_THREAD;
}

static void
refresh_connection(struct slack_sm *sm)
{

  bool status = false;
  char *base_url = NULL;
  struct sized_buffer body = { 0 };
  struct sized_buffer messages = { 0 };

  slack_apps_connections_open(CLIENT(sm, sm), &body);

  json_extract(body.start, body.size,
               "(ok):b, (url):?s, (response_metadata.messages):T", &status,
               &base_url, &messages);

  VASSERT_S(true == status,
            "Couldn't fetch connections for websockets:\n\t\tMessage: %.*s",
            (int)messages.size, messages.start);

  ws_set_url(sm->ws, base_url, NULL);

  free(base_url);
  free(body.start);
}

void
slack_sm_init(struct slack_sm *sm, struct logconf *conf)
{
  struct ws_callbacks cbs = { .data = sm,
                              .on_connect = &on_connect_cb,
                              .on_text = &on_text_cb,
                              .on_close = &on_close_cb };
  struct ws_attr attr = { .conf = conf };

  sm->mhandle = curl_multi_init();
  sm->ws = ws_init(&cbs, sm->mhandle, &attr);
  logconf_branch(&sm->conf, conf, "SLACK_SOCKETMODE");

  sm->cbs.scheduler = &default_scheduler_cb;

  refresh_connection(sm);
}

void
slack_sm_cleanup(struct slack_sm *sm)
{
  curl_multi_cleanup(sm->mhandle);
  ws_cleanup(sm->ws);
}

/* connects to the slack websockets server */
void
slack_sm_run(struct slack_sm *sm)
{
  uint64_t tstamp;

  ASSERT_S(WS_DISCONNECTED == ws_get_status(sm->ws),
           "Can't run websockets recursively");

  ws_start(sm->ws);
  while (1) {
    /* break on failure */
    if (!ws_easy_run(sm->ws, 5, &tstamp)) break;

    /* wait until client is ready */
    if (!sm->is_ready) continue;

    /* check if timespan since first pulse is greater than
     * minimum heartbeat interval required */
    if (sm->hbeat.interval_ms < (ws_timestamp(sm->ws) - sm->hbeat.tstamp)) {
      refresh_connection(sm);
      sm->hbeat.tstamp = ws_timestamp(sm->ws); /* update heartbeat timestamp */
    }
  }
  ws_end(sm->ws);
}
