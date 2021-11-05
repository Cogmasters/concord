#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slack.h"
#include "slack-internal.h"

#include "cee-utils.h"

static enum slack_sm_types
eval_sm_type(char type[])
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
send_acknowledge(struct slack_sm *sm, const char envelope_id[])
{
  char payload[512];
  size_t ret =
    json_inject(payload, sizeof(payload), "(envelope_id):s", envelope_id);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  struct ws_info info = { 0 };
  ws_send_text(sm->ws, &info, payload, ret);

  log_info(
    ANSICOLOR("SEND",
              ANSI_FG_BRIGHT_GREEN) " ACKNOWLEDGE (%d bytes) [@@@_%zu_@@@]",
    ret, info.loginfo.counter);
}

static void
on_hello(struct slack_sm *sm, const char *text, size_t len)
{
  sm->is_ready = true;
  sm->hbeat.interval_ms = 0;
  sm->hbeat.tstamp = cee_timestamp_ms();

  long interval_s = 0;
  json_extract((char *)text, len,
               "(debug_info.approximate_connection_time):ld", &interval_s);
  sm->hbeat.interval_ms = 1000 * interval_s;

  if (sm->cbs.on_hello) (*sm->cbs.on_hello)(sm->p_client, text, len);
}

static void
on_message(struct slack_sm *sm, struct sized_buffer *data)
{
  if (sm->cbs.on_message)
    (*sm->cbs.on_message)(sm->p_client, data->start, data->size);
}

static void
on_block_actions(struct slack_sm *sm, struct sized_buffer *data)
{
  if (sm->cbs.on_block_actions)
    (*sm->cbs.on_block_actions)(sm->p_client, data->start, data->size);
}

static void
on_message_actions(struct slack_sm *sm, struct sized_buffer *data)
{
  if (sm->cbs.on_message_actions)
    (*sm->cbs.on_message_actions)(sm->p_client, data->start, data->size);
}

static void
on_view_closed(struct slack_sm *sm, struct sized_buffer *data)
{
  if (sm->cbs.on_view_closed)
    (*sm->cbs.on_view_closed)(sm->p_client, data->start, data->size);
}

static void
on_view_submission(struct slack_sm *sm, struct sized_buffer *data)
{
  if (sm->cbs.on_view_submission)
    (*sm->cbs.on_view_submission)(sm->p_client, data->start, data->size);
}

static void *
context_run(void *p_cxt)
{
  struct slack_event_cxt *cxt = p_cxt;
  bool is_main_thread = cxt->is_main_thread;
  cxt->tid = pthread_self();

  if (!is_main_thread)
    log_info("Thread " ANSICOLOR("starts", ANSI_FG_RED) " to serve %s",
             cxt->str_type);

  if (cxt->on_event) (*cxt->on_event)(cxt->p_sm, &cxt->data);

  if (!is_main_thread) {
    log_info("Thread " ANSICOLOR("exits", ANSI_FG_RED) " from serving %s",
             cxt->str_type);

    free(cxt->data.start);
    free(cxt);
    pthread_exit(NULL);
  }
  return NULL;
}

static void
on_events(struct slack_sm *sm, struct sized_buffer *data, char str_type[])
{
  void (*on_event)(struct slack_sm *, struct sized_buffer *) = NULL;
  enum slack_sm_types type = eval_sm_type(str_type);
  switch (type) {
  case SLACK_SOCKETMODE_TYPE_MESSAGE:
    if (sm->cbs.on_message) on_event = &on_message;
    break;
  case SLACK_SOCKETMODE_TYPE_BLOCK_ACTIONS:
    if (sm->cbs.on_block_actions) on_event = &on_block_actions;
    break;
  case SLACK_SOCKETMODE_TYPE_MESSAGE_ACTIONS:
    if (sm->cbs.on_message_actions) on_event = &on_message_actions;
    break;
  case SLACK_SOCKETMODE_TYPE_VIEW_CLOSED:
    if (sm->cbs.on_view_closed) on_event = &on_view_closed;
    break;
  case SLACK_SOCKETMODE_TYPE_VIEW_SUBMISSION:
    if (sm->cbs.on_view_submission) on_event = &on_view_submission;
    break;
  default:
    log_warn("Expected unimplemented Socketmode type (code: %d)", type);
    break;
  }

  if (!on_event) return;

  struct slack_event_cxt cxt;
  asprintf(&cxt.data.start, "%.*s", (int)data->size, data->start);
  cxt.data.size = data->size;
  cxt.p_sm = sm;
  cxt.type = type;
  cxt.on_event = on_event;
  snprintf(cxt.str_type, sizeof(cxt.str_type), "%s", str_type);

  enum slack_event_handling_mode mode =
    sm->event_handler(sm->p_client, &cxt.data, cxt.type);
  switch (mode) {
  case SLACK_EVENT_IGNORE: return;
  case SLACK_EVENT_MAIN_THREAD:
    cxt.is_main_thread = true;
    context_run(&cxt);
    return;
  case SLACK_EVENT_CHILD_THREAD: {
    cxt.is_main_thread = false;
    struct slack_event_cxt *p_cxt = malloc(sizeof *p_cxt);
    memcpy(p_cxt, &cxt, sizeof(cxt));
    pthread_t tid;
    if (pthread_create(&tid, NULL, &context_run, p_cxt))
      ERR("Couldn't create thread");
    if (pthread_detach(tid)) ERR("Couldn't detach thread");
    return;
  }
  default: ERR("Unknown event handling mode (code: %d)", mode);
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

  char type[64] = "", envelope_id[64] = "";
  json_extract((char *)text, len, "(type):s,(envelope_id):s", type,
               envelope_id);

  if (*envelope_id) send_acknowledge(sm, envelope_id);

  if (STREQ(type, "hello")) {
    on_hello(sm, text, len);
    return;
  }

  struct sized_buffer data = { 0 };
  char event_type[64] = "";
  bool accepts_response_payload = false;
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
    type, (*event_type) ? " -> " : "", event_type, len, info->loginfo.counter);

  on_events(sm, &data, event_type);
}

static enum slack_event_handling_mode
noop_event_handler(struct slack *a,
                   struct sized_buffer *b,
                   enum slack_sm_types d)
{
  return SLACK_EVENT_MAIN_THREAD;
}

static void
refresh_connection(struct slack_sm *sm)
{
  struct sized_buffer resp_body = { 0 };
  slack_apps_connections_open(sm->p_client, &resp_body);

  bool status = false;
  char *base_url = NULL;
  struct sized_buffer messages = { 0 };
  json_extract(resp_body.start, resp_body.size,
               "(ok):b, (url):?s, (response_metadata.messages):T", &status,
               &base_url, &messages);

  VASSERT_S(true == status,
            "Couldn't fetch connections for websockets:\n\t\tMessage: %.*s",
            (int)messages.size, messages.start);

  ws_set_url(sm->p_client->sm.ws, base_url, NULL);

  free(base_url);
  free(resp_body.start);
}

void
slack_sm_init(struct slack_sm *sm, struct logconf *conf)
{
  ASSERT_S(NULL != sm->p_client, "Not meant to be called standalone");

  struct ws_callbacks cbs = { .data = sm,
                              .on_connect = &on_connect_cb,
                              .on_text = &on_text_cb,
                              .on_close = &on_close_cb };
  sm->ws = ws_init(&cbs, conf);
  logconf_branch(&sm->conf, conf, "SLACK_SOCKETMODE");

  sm->event_handler = &noop_event_handler;

  refresh_connection(sm);
}

void
slack_sm_cleanup(struct slack_sm *sm)
{
  ws_cleanup(sm->ws);
}

/* connects to the slack websockets server */
void
slack_sm_run(struct slack *client)
{
  struct slack_sm *sm = &client->sm;
  ASSERT_S(WS_DISCONNECTED == ws_get_status(sm->ws),
           "Can't run websockets recursively");

  ws_start(sm->ws);

  bool is_running = false;
  while (1) {
    ws_perform(sm->ws, &is_running, 1);
    if (!is_running) break; // exit event loop
    if (!sm->is_ready) continue; // wait until on_hello()

    // connection established

    /*check if timespan since first pulse is greater than
     * minimum heartbeat interval required */
    if (sm->hbeat.interval_ms < (ws_timestamp(sm->ws) - sm->hbeat.tstamp)) {
      refresh_connection(sm);
      sm->hbeat.tstamp = ws_timestamp(sm->ws); // update heartbeat timestamp
    }
  }
}
