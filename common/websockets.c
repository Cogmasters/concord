#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>

#include "curl-websocket.h"

#include "websockets.h"
#include "orka-utils.h"


struct websockets {
  enum ws_status status;
  enum ws_action action;
  bool is_running;

  CURLM *mhandle;
  CURL *ehandle;
  uint64_t now_tstamp; // timestamp updated every loop iteration

  char base_url[512 + 1];
  struct ws_callbacks cbs; 

  struct logconf *p_log;
  pthread_mutex_t lock;
};

static void
_ws_close_nolock(
  struct websockets *ws, 
  enum ws_close_reason wscode, 
  const char reason[], 
  size_t len)
{
  log_http(
    ws->p_log, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)reason, len},
    "WS_SEND_CLOSE");

  cws_close(ws->ehandle, (enum cws_close_reason)wscode, reason, len);
}

void
ws_close(
  struct websockets *ws, 
  enum ws_close_reason wscode, 
  const char reason[], 
  size_t len)
{
  pthread_mutex_lock(&ws->lock);
  _ws_close_nolock(ws, wscode, reason, len);
  pthread_mutex_unlock(&ws->lock);
}

static void
_ws_set_status_nolock(struct websockets *ws, enum ws_status status)
{
  switch (ws->status = status) {
  case WS_DISCONNECTED: // reset
      log_debug("Change status to WS_DISCONNECTED");
      ws->action = 0;
      ws_reset(ws);
      break;
  case WS_CONNECTED:
      log_debug("Change status to WS_CONNECTED");
      break;
  case WS_DISCONNECTING:
      log_debug("Change status to WS_DISCONNECTING");
      break;
  case WS_CONNECTING:
      log_debug("Change status to WS_CONNECTING");
      break;
  default:
      ERR("Unknown ws_status (code: %d)", ws->status);
      break;
  }
}

static void
_ws_set_status(struct websockets *ws, enum ws_status status)
{
  pthread_mutex_lock(&ws->lock);
  _ws_set_status_nolock(ws, status);
  pthread_mutex_unlock(&ws->lock);
}

enum ws_status
ws_get_status(struct websockets *ws) 
{
  pthread_mutex_lock(&ws->lock);
  enum ws_status status = ws->status;
  pthread_mutex_unlock(&ws->lock);
  return status;
}

enum ws_action
ws_get_action(struct websockets *ws) 
{
  pthread_mutex_lock(&ws->lock);
  enum ws_action action = ws->action;
  pthread_mutex_unlock(&ws->lock);
  return action;
}

void
ws_set_action(struct websockets *ws, enum ws_action action)
{
  pthread_mutex_lock(&ws->lock);
  if (WS_DISCONNECTING == ws->status) { // closing process already started
    pthread_mutex_unlock(&ws->lock);
    return;
  }

  switch (ws->action = action) {
  case WS_ACTION_DISCONNECT:
      log_info("Disconnecting WebSockets client ...");
      _ws_set_status_nolock(ws, WS_DISCONNECTING);
      if (ws->is_running) { // safely close connection
        char reason[] = "Disconnect gracefully";
        _ws_close_nolock(ws, WS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
      }
      break;
  default: 
      ERR("Unknown ws_action (code: %d)", action);
      break;
  }
  pthread_mutex_unlock(&ws->lock);
}

static bool
_ws_is_running(struct websockets *ws)
{
  bool is_running;
  pthread_mutex_lock(&ws->lock);
  is_running = ws->is_running;
  pthread_mutex_unlock(&ws->lock);
  return is_running;
}

static void
_ws_set_running(struct websockets *ws, bool status)
{
  pthread_mutex_lock(&ws->lock);
  ws->is_running = status;
  pthread_mutex_unlock(&ws->lock);
}

static void
cws_on_connect_cb(void *p_ws, CURL *ehandle, const char *ws_protocols)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_log, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)ws_protocols, strlen(ws_protocols)},
    "WS_RCV_CONNECT");

  _ws_set_status(ws, WS_CONNECTING);
  (*ws->cbs.on_connect)(ws->cbs.data, ws_protocols);
  _ws_set_status(ws, WS_CONNECTED);
}

static void
cws_on_close_cb(void *p_ws, CURL *ehandle, enum cws_close_reason cwscode, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_log, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_CLOSE(%d)", cwscode);

  _ws_set_status(ws, WS_DISCONNECTING);
  (*ws->cbs.on_close)(ws->cbs.data, cwscode, reason, len);
  // will set status to WS_DISCONNECTED when ws->is_running == false
}

char*
ws_close_opcode_print(enum ws_close_reason opcode) 
{
  switch (opcode) {
  CASE_RETURN_STR(WS_CLOSE_REASON_NORMAL);
  CASE_RETURN_STR(WS_CLOSE_REASON_GOING_AWAY);
  CASE_RETURN_STR(WS_CLOSE_REASON_PROTOCOL_ERROR);
  CASE_RETURN_STR(WS_CLOSE_REASON_UNEXPECTED_DATA);
  CASE_RETURN_STR(WS_CLOSE_REASON_NO_REASON);
  CASE_RETURN_STR(WS_CLOSE_REASON_ABRUPTLY);
  CASE_RETURN_STR(WS_CLOSE_REASON_INCONSISTENT_DATA);
  CASE_RETURN_STR(WS_CLOSE_REASON_POLICY_VIOLATION);
  CASE_RETURN_STR(WS_CLOSE_REASON_TOO_BIG);
  CASE_RETURN_STR(WS_CLOSE_REASON_MISSING_EXTENSION);
  CASE_RETURN_STR(WS_CLOSE_REASON_SERVER_ERROR);
  CASE_RETURN_STR(WS_CLOSE_REASON_IANA_REGISTRY_START);
  CASE_RETURN_STR(WS_CLOSE_REASON_IANA_REGISTRY_END);
  CASE_RETURN_STR(WS_CLOSE_REASON_PRIVATE_START);
  CASE_RETURN_STR(WS_CLOSE_REASON_PRIVATE_END);
  default: return NULL;
  }
}

static void
cws_on_text_cb(void *p_ws, CURL *ehandle, const char *text, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_log, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)text, len},
    "WS_RCV_TEXT");

  (*ws->cbs.on_text)(ws->cbs.data, text, len);
}

static void
cws_on_binary_cb(void *p_ws, CURL *ehandle, const void *mem, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_log, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)mem, len},
    "WS_RCV_BINARY");

  (*ws->cbs.on_binary)(ws->cbs.data, mem, len);
}

static void
cws_on_ping_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_log, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_PING");

  (*ws->cbs.on_ping)(ws->cbs.data, reason, len);
}

static void
cws_on_pong_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_log, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_PONG");

  (*ws->cbs.on_pong)(ws->cbs.data, reason, len);
}

/* init easy handle with some default opt */
static CURL*
cws_custom_new(struct websockets *ws, const char ws_protocols[])
{
  struct cws_callbacks cws_cbs = {0};
  cws_cbs.on_connect = &cws_on_connect_cb;
  cws_cbs.on_text = &cws_on_text_cb;
  cws_cbs.on_binary = &cws_on_binary_cb;
  cws_cbs.on_ping = &cws_on_pong_cb;
  cws_cbs.on_pong = &cws_on_pong_cb;
  cws_cbs.on_close = &cws_on_close_cb;
  cws_cbs.data = ws;

  CURL *new_ehandle = cws_new(ws->base_url, ws_protocols, &cws_cbs);
  ASSERT_S(NULL != new_ehandle, "Out of memory");

  CURLcode ecode;
  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 2L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}

static void noop_on_connect(void *a, const char *b){return;}
static void noop_on_text(void *a, const char *b, size_t c){return;}
static void noop_on_binary(void *a, const void *b, size_t c){return;}
static void noop_on_ping(void *a, const char *b, size_t c){return;}
static void noop_on_pong(void *a, const char *b, size_t c){return;}
static void noop_on_close(void *a, enum ws_close_reason b, const char *c, size_t d){return;}

struct websockets*
ws_init(struct ws_callbacks *cbs, struct logconf *config)
{
  struct websockets *new_ws = calloc(1, sizeof *new_ws);

  new_ws->mhandle = curl_multi_init();

  logconf_add_id(config, new_ws, "WEBSOCKETS");
  new_ws->p_log = config;

  memcpy(&new_ws->cbs, cbs, sizeof(struct ws_callbacks));
  if (!new_ws->cbs.on_connect) 
    new_ws->cbs.on_connect = &noop_on_connect;
  if (!new_ws->cbs.on_text) 
    new_ws->cbs.on_text = &noop_on_text;
  if (!new_ws->cbs.on_binary) 
    new_ws->cbs.on_binary = &noop_on_binary;
  if (!new_ws->cbs.on_ping) 
    new_ws->cbs.on_ping = &noop_on_ping;
  if (!new_ws->cbs.on_pong) 
    new_ws->cbs.on_pong = &noop_on_pong;
  if (!new_ws->cbs.on_close) 
    new_ws->cbs.on_close = &noop_on_close;

  if (pthread_mutex_init(&new_ws->lock, NULL))
    ERR("Couldn't initialize pthread mutex");

  return new_ws;
}

void
ws_set_url(struct websockets *ws, const char base_url[], const char ws_protocols[])
{
  ASSERT_S(WS_DISCONNECTED == ws->status, "Can only set url to a disconnected client");

  if (base_url) {
    log_debug("WebSockets redirecting:\n\tfrom: %s\n\tto: %s", ws->base_url, base_url);
    int ret = snprintf(ws->base_url, sizeof(ws->base_url), "%s", base_url);
    ASSERT_S(ret < sizeof(ws->base_url), "Out of bounds write attempt");
  }
  if (ws->ehandle) {
    curl_multi_remove_handle(ws->mhandle, ws->ehandle);
    cws_free(ws->ehandle);
  }
  ws->ehandle = cws_custom_new(ws, ws_protocols);
  curl_multi_add_handle(ws->mhandle, ws->ehandle);
}

void
ws_reset(struct websockets *ws) {
  log_debug("Resetting curl's multi and easy handles");
  ws_set_url(ws, NULL, NULL);
}


void
ws_cleanup(struct websockets *ws)
{
  curl_multi_cleanup(ws->mhandle);
  if (ws->ehandle)
    cws_free(ws->ehandle);
  pthread_mutex_destroy(&ws->lock);
  free(ws);
}

void
ws_send_text(struct websockets *ws, char text[], size_t len)
{
  log_http(
    ws->p_log, 
    ws,
    ws->base_url, 
    (struct sized_buffer){text, len},
    "WS_SEND_TEXT");

  pthread_mutex_lock(&ws->lock);
  if (false == cws_send(ws->ehandle, true, text, len)) {
    log_error("Couldn't send websockets payload");
  }
  pthread_mutex_unlock(&ws->lock);
}

static void
_ws_perform(struct websockets *ws)
{
  pthread_mutex_lock(&ws->lock);
  ws->now_tstamp = orka_timestamp_ms(); //update our concept of now
  pthread_mutex_unlock(&ws->lock);

  bool is_running;
  CURLMcode mcode = curl_multi_perform(ws->mhandle, (int*)&is_running);
  ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

  _ws_set_running(ws, is_running);
}

void
ws_perform(struct websockets *ws, bool *p_is_running)
{
  _ws_perform(ws);

  if (!_ws_is_running(ws))
    _ws_set_status(ws, WS_DISCONNECTED);
  if (p_is_running)
    *p_is_running = _ws_is_running(ws);
}

void 
ws_wait_activity(struct websockets *ws, uint64_t wait_ms) 
{
  CURLMcode mcode = curl_multi_wait(ws->mhandle, NULL, 0, wait_ms, NULL);
  ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));
}

uint64_t
ws_timestamp(struct websockets *ws) 
{
  pthread_mutex_lock(&ws->lock);
  uint64_t now_tstamp = ws->now_tstamp;
  pthread_mutex_unlock(&ws->lock);
  return now_tstamp;
}
