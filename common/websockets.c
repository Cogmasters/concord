#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>

#include "curl-websocket.h"

#include "websockets.h"
#include "orka-utils.h"


#define CURLE_CHECK(ws, ecode)                             \
  VASSERT_S(CURLE_OK == ecode, "[%s] (CURLE code: %d) %s", \
      ws->tag,                                             \
      ecode,                                               \
      IS_EMPTY_STRING(ws->errbuf)                          \
        ? curl_easy_strerror(ecode)                        \
        : ws->errbuf)

struct websockets {
  enum ws_status status;
  bool is_running;

  struct {
    bool enable;
    enum ws_close_reason wscode;
    char reason[1028];
    size_t len;
  } closing;

  int numfds;

  CURLM *mhandle;
  CURL *ehandle;
  uint64_t now_tstamp; // timestamp updated every loop iteration

  char base_url[512 + 1];
  char protocols[126];
  struct ws_callbacks cbs; 

  /** 
   * capture curl error messages
   * @note should only be accessed after a error code returns
   */
  char errbuf[CURL_ERROR_SIZE]; /** @see https://curl.se/libcurl/c/CURLOPT_ERRORBUFFER.html */

  char *tag;
  struct logconf *p_config;
  pthread_mutex_t lock;
};

static CURL* cws_custom_new(struct websockets *ws, const char ws_protocols[]);

static void
_ws_set_status_nolock(struct websockets *ws, enum ws_status status)
{
  switch (status) {
  case WS_DISCONNECTED:
      VASSERT_S(WS_DISCONNECTING == ws->status, "[%s] (Internal Error) Disconnect abruptly", ws->tag);
      log_debug("[%s] Change status to WS_DISCONNECTED", ws->tag);
      break;
  case WS_CONNECTED:
      // ws_start() should have been called first
      VASSERT_S(WS_CONNECTING == ws->status, "[%s] Missing ws_start() before the event loop", ws->tag);
      log_debug("[%s] Change status to WS_CONNECTED", ws->tag);
      break;
  case WS_DISCONNECTING:
      log_debug("[%s] Change status to WS_DISCONNECTING", ws->tag);
      break;
  case WS_CONNECTING: /* triggered at ws_start() */
      log_debug("[%s] Change status to WS_CONNECTING", ws->tag);
      break;
  default:
      ERR("[%s] Unknown ws_status (code: %d)", ws->tag, status);
      break;
  }
  ws->status = status;
}

static void // multi-thread
_ws_set_status(struct websockets *ws, enum ws_status status)
{
  pthread_mutex_lock(&ws->lock);
  _ws_set_status_nolock(ws, status);
  pthread_mutex_unlock(&ws->lock);
}

static void // main thread
cws_on_connect_cb(void *p_ws, CURL *ehandle, const char *ws_protocols)
{
  struct websockets *ws = p_ws;
  _ws_set_status(ws, WS_CONNECTED);

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)ws_protocols, strlen(ws_protocols)},
    "WS_RCV_CONNECT");

  (*ws->cbs.on_connect)(ws->cbs.data, ws_protocols);
}

static void // main thread
cws_on_close_cb(void *p_ws, CURL *ehandle, enum cws_close_reason cwscode, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;
  _ws_set_status(ws, WS_DISCONNECTING);

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_CLOSE(%d)", cwscode);

  log_debug("[%s] Receive CLOSE(%d): %.*s", ws->tag, cwscode, (int)len, reason);
  (*ws->cbs.on_close)(ws->cbs.data, cwscode, reason, len);
  // will set status to WS_DISCONNECTED when ws->is_running == false
}

char* // thread-safe
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

static void // main-thread
cws_on_text_cb(void *p_ws, CURL *ehandle, const char *text, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)text, len},
    "WS_RCV_TEXT");

  (*ws->cbs.on_text)(ws->cbs.data, text, len);
}

static void // main-thread
cws_on_binary_cb(void *p_ws, CURL *ehandle, const void *mem, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)mem, len},
    "WS_RCV_BINARY");

  (*ws->cbs.on_binary)(ws->cbs.data, mem, len);
}

static void // main-thread
cws_on_ping_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_PING");

  (*ws->cbs.on_ping)(ws->cbs.data, reason, len);
}

static void // main-thread
cws_on_pong_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_PONG");

  (*ws->cbs.on_pong)(ws->cbs.data, reason, len);
}

/* init easy handle with some default opt */
static CURL* // main-thread
cws_custom_new(struct websockets *ws, const char ws_protocols[])
{
  struct cws_callbacks cws_cbs = {
    .on_connect = &cws_on_connect_cb,
    .on_text = &cws_on_text_cb,
    .on_binary = &cws_on_binary_cb,
    .on_ping = &cws_on_pong_cb,
    .on_pong = &cws_on_pong_cb,
    .on_close = &cws_on_close_cb,
    .data = ws
  };

  CURL *new_ehandle = cws_new(ws->base_url, ws_protocols, &cws_cbs);

  CURLcode ecode;
  //set error buffer for capturing CURL error descriptions
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_ERRORBUFFER, ws->errbuf);
  CURLE_CHECK(ws, ecode);
  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 2L);
  CURLE_CHECK(ws, ecode);

  return new_ehandle;
}

static bool // main-thread
_ws_close(struct websockets *ws)
{
  pthread_mutex_lock(&ws->lock);

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){ws->closing.reason, ws->closing.len},
    "WS_SEND_CLOSE");

  log_debug("[%s] Sending CLOSE(%d): %.*s", ws->tag, ws->closing.wscode, (int)ws->closing.len, ws->closing.reason);

  bool ret = cws_close(ws->ehandle, (enum cws_close_reason)ws->closing.wscode, ws->closing.reason, ws->closing.len);

  ws->closing.wscode = 0;
  ws->closing.enable = false;
  *ws->closing.reason = '\0';
  ws->closing.len = 0;

  pthread_mutex_unlock(&ws->lock);
  return ret;
}

bool // multi-thread
ws_close(
  struct websockets *ws, 
  enum ws_close_reason wscode, 
  const char reason[], 
  size_t len)
{
  pthread_mutex_lock(&ws->lock);

  bool will_close = !ws->closing.enable;
  if (will_close) {
    _ws_set_status_nolock(ws, WS_DISCONNECTING);
    ws->closing.wscode = wscode;
    snprintf(ws->closing.reason, sizeof(ws->closing.reason), "%.*s", (int)len, reason);
    ws->closing.len = len;
    ws->closing.enable = true;
  }

  pthread_mutex_unlock(&ws->lock);
  return will_close;
}

enum ws_status // MT-Safe as long _ws_set_status() is used properly
ws_get_status(struct websockets *ws) 
{
  pthread_mutex_lock(&ws->lock);
  enum ws_status status = ws->status;
  pthread_mutex_unlock(&ws->lock);
  return status;
}

static void noop_on_connect(void *a, const char *b){return;}
static void noop_on_text(void *a, const char *b, size_t c){return;}
static void noop_on_binary(void *a, const void *b, size_t c){return;}
static void noop_on_ping(void *a, const char *b, size_t c){return;}
static void noop_on_pong(void *a, const char *b, size_t c){return;}
static void noop_on_close(void *a, enum ws_close_reason b, const char *c, size_t d){return;}

struct websockets* // main-thread
ws_init(struct ws_callbacks *cbs, struct logconf *config)
{
  struct websockets *new_ws = calloc(1, sizeof *new_ws);
  new_ws->mhandle = curl_multi_init();
  logconf_add_id(config, new_ws, new_ws->tag = "WEBSOCKETS");
  new_ws->p_config = config;

  new_ws->cbs = *cbs;
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
    ERR("[%s] Couldn't initialize pthread mutex", new_ws->tag);

  return new_ws;
}

void // multi-thread / unsafe
ws_set_url(struct websockets *ws, const char base_url[], const char ws_protocols[])
{
  if (IS_EMPTY_STRING(ws->base_url))
    log_debug("[%s] Websockets new URL: %s", ws->tag, base_url);
  else
    log_debug("[%s] WebSockets redirecting:\n\tfrom: %s\n\tto: %s", ws->tag, ws->base_url, base_url);

  int ret = snprintf(ws->base_url, sizeof(ws->base_url), "%s", base_url);
  VASSERT_S(ret < sizeof(ws->base_url), "[%s] Out of bounds write attempt", ws->tag);

  if (!IS_EMPTY_STRING(ws_protocols)) {
    int ret = snprintf(ws->protocols, sizeof(ws->protocols), "%s", ws_protocols);
    VASSERT_S(ret < sizeof(ws->protocols), "[%s] Out of bounds write attempt", ws->tag);
  }
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

bool // multi-thread / unsafe
ws_send_text(struct websockets *ws, char text[], size_t len)
{
  pthread_mutex_lock(&ws->lock);
  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){text, len},
    "WS_SEND_TEXT");

  bool ret = cws_send(ws->ehandle, true, text, len);
  pthread_mutex_unlock(&ws->lock);
  return ret;
}

void // main-thread
ws_start(struct websockets *ws) 
{
  ws->tag = logconf_tag(ws->p_config, ws);
  VASSERT_S(false == ws_is_alive(ws), "[%s] Shutdown current WebSockets connection before calling ws_start()", ws->tag);
  VASSERT_S(NULL == ws->ehandle, "[%s] (Internal error) Attempt to reconnect without properly closing the connection", ws->tag);
  ws->ehandle = cws_custom_new(ws, ws->protocols);
  curl_multi_add_handle(ws->mhandle, ws->ehandle);
  _ws_set_status(ws, WS_CONNECTING);  
}

void // main-thread
ws_perform(struct websockets *ws, bool *p_is_running, uint64_t wait_ms)
{
  int is_running;
  CURLMcode mcode;

  pthread_mutex_lock(&ws->lock);
  ws->now_tstamp = orka_timestamp_ms(); //update our concept of now
  pthread_mutex_unlock(&ws->lock);

  mcode = curl_multi_perform(ws->mhandle, &is_running);
  VASSERT_S(CURLM_OK == mcode, "[%s] (CURLM code: %d) %s", ws->tag, mcode, curl_multi_strerror(mcode));

  if (!is_running) {
    _ws_set_status(ws, WS_DISCONNECTED);
  }
  else { // wait for activity or timeout
    mcode = curl_multi_wait(ws->mhandle, NULL, 0, wait_ms, &ws->numfds);
    VASSERT_S(CURLM_OK == mcode, "[%s] (CURLM code: %d) %s", ws->tag, mcode, curl_multi_strerror(mcode));
  }

  switch (ws_get_status(ws)) {
  case WS_CONNECTING:
      break;
  case WS_CONNECTED:
      break;
  case WS_DISCONNECTING:
      if (ws->closing.enable) {
        _ws_close(ws);
      }
      curl_multi_remove_handle(ws->mhandle, ws->ehandle);
      break;
  case WS_DISCONNECTED: {
      // read messages/informationals from the individual transfers
      int msgq = 0;
      struct CURLMsg *curlmsg = curl_multi_info_read(ws->mhandle, &msgq);
      if (curlmsg) {
        CURLcode ecode = curlmsg->data.result;
        if (CURLMSG_DONE == curlmsg->msg || CURLE_OK != ecode) {
          log_error("[%s] (CURLE code: %d) %s", \
              ws->tag,
              ecode, 
              IS_EMPTY_STRING(ws->errbuf) 
                  ? curl_easy_strerror(ecode) 
                  : ws->errbuf);
          log_error("[%s] Disconnected abruptly", ws->tag);
        }
        else {
          log_debug("[%s] Disconnected gracefully", ws->tag);
        }
      }
      else {
        log_debug("[%s] Disconnected gracefully", ws->tag);
      }
      
      // reset for next iteration
      *ws->errbuf = '\0';
      if (ws->ehandle) {
        cws_free(ws->ehandle);
        ws->ehandle = NULL;
      }
      break; }
  }

  *p_is_running = ws->is_running = is_running;
}

uint64_t
ws_timestamp(struct websockets *ws) 
{
  pthread_mutex_lock(&ws->lock);
  uint64_t now_tstamp = ws->now_tstamp;
  pthread_mutex_unlock(&ws->lock);
  return now_tstamp;
}

bool
ws_is_alive(struct websockets *ws) {
  return WS_DISCONNECTED != ws_get_status(ws);
}
