#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>

#include "curl-websocket.h"

#include "websockets.h"
#include "cee-utils.h"


#define CURLE_CHECK(ws, ecode)                             \
  VASSERT_S(CURLE_OK == ecode, "[%s] (CURLE code: %d) %s", \
      ws->tag,                                             \
      ecode,                                               \
      IS_EMPTY_STRING(ws->errbuf)                          \
        ? curl_easy_strerror(ecode)                        \
        : ws->errbuf)

struct websockets {
  /**
   * The client connections status
   *
   * @note #WS_CONNECTED triggered after ws_on_connect()
   * @note #WS_DISCONNECTED triggered after complete shutdown at ws_perform()
   * @note #WS_CONNECTING triggered at ws_start()
   * @note #WS_DISCONNECTING triggered when closing connection
   *        @see ws_on_close()
   * @see ws_get_status()
   * @see _ws_set_status()
   */
  enum ws_status status;

  /**
   * CURL multi_handle used in conjuction with easy_handle
   *        to perform non-blocking requests to a WebSockets server.
   * @see ws_perform()
   */
  CURLM *mhandle;
  CURL *ehandle;

  /**
   * Timestamp updated every ws_perform() call
   */
  uint64_t now_tstamp;

  /**
   * WebSockets server URL and Protocols
   * @see ws_set_url()
   */
  char base_url[512 + 1];
  char protocols[126];

  /**
   * WebSockets callbacks
   * @see websockets.h for definition
   */
  struct ws_callbacks cbs; 

  /** 
   * Capture curl error messages
   * @note should only be accessed after a error code returns
   * @see https://curl.se/libcurl/c/CURLOPT_ERRORBUFFER.html
   */
  char errbuf[CURL_ERROR_SIZE];

  /**
   * A unique tag to identify this WebSockets client
   *        for logging purposes
   */
  char *tag;

  /**
   * The logconf structure containing logging instructions
   * @see logconf.h
   */
  struct logconf *p_config;

  /**
   * Synchronization directives
   * @param wthread_action will trigger #TRUE when _ws_close() or
   *        ws_send_text() are being called outside the main-thread.
   *        Being #TRUE means the called function will be locked until
   *        the main-thread is not performing any socket read/write
   *        operations. The main-thread will then block itself until
   *        the worker-thread complete its operations.
   *        @see _ws_close()
   *        @see ws_send_text()
   * @param tid the main-thread id, to decide whether synchronization
   *        is necessary.
   */
  //bool wthread_action;
  //pthread_cond_t cond;
  pthread_mutex_t lock;
  /*
   * This is used to check whether the running thread
   * is the same as the thread that ran ws_start.
   * Some functions can only run in the same thread
   */
  pthread_t tid;

  /*
   * the user of ws can send two commands:
   * exit, reconnect
   */
  enum ws_user_cmd user_cmd;

  /*
   * This is used to debug ws close event
   */
  bool logging_after_exit;
};


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

static char* // thread-safe
_ws_status_print(enum ws_status status) 
{
  switch (status) {
  CASE_RETURN_STR(WS_DISCONNECTED);
  CASE_RETURN_STR(WS_CONNECTED);
  CASE_RETURN_STR(WS_DISCONNECTING);
  CASE_RETURN_STR(WS_CONNECTING);
  default: return NULL;
  }
}

static CURL* cws_custom_new(struct websockets *ws, const char ws_protocols[]);

static void
_ws_set_status_nolock(struct websockets *ws, enum ws_status status)
{
  if ((WS_DISCONNECTING == ws->status) && (status != WS_DISCONNECTED)) 
    return; /* EARLY RETURN */

  switch (status) {
  case WS_DISCONNECTED:
      VASSERT_S(WS_DISCONNECTING == ws->status, \
          "[%s] (Internal Error) Disconnect abruptly (Current status: %s)", ws->tag, _ws_status_print(ws->status));
      log_debug("[%s] Change status to WS_DISCONNECTED", ws->tag);
      break;
  case WS_CONNECTED:
      VASSERT_S(WS_CONNECTING == ws->status, \
          "[%s] Missing ws_start() before the event loop (Current status: %s)", ws->tag, _ws_status_print(ws->status));
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

static void // thread-safe
_ws_set_status(struct websockets *ws, enum ws_status status)
{
  pthread_mutex_lock(&ws->lock);
  _ws_set_status_nolock(ws, status);
  pthread_mutex_unlock(&ws->lock);
}

static void // main-thread
cws_on_connect_cb(void *p_ws, CURL *ehandle, const char *ws_protocols)
{
  log_trace("cws_on_connect_cb() is called");
  struct websockets *ws = p_ws;
  _ws_set_status(ws, WS_CONNECTED);

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)ws_protocols, strlen(ws_protocols)},
    "WS_RCV_CONNECT");

  (*ws->cbs.on_connect)(ws->cbs.data, ws, ws_protocols);
}

static void // main-thread
cws_on_close_cb(void *p_ws, CURL *ehandle, enum cws_close_reason cwscode, const char *reason, size_t len)
{
  log_info("cws_on_close_cb() is called");
  struct websockets *ws = p_ws;
  _ws_set_status(ws, WS_DISCONNECTING);

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_CLOSE(%d)", cwscode);

  log_debug("[%s] Receive CLOSE(%d): %.*s", ws->tag, cwscode, (int)len, reason);
  (*ws->cbs.on_close)(ws->cbs.data, ws, cwscode, reason, len);
  // will set status to WS_DISCONNECTED when is_running == false
}

static void // main-thread
cws_on_text_cb(void *p_ws, CURL *ehandle, const char *text, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)text, len},
    "WS_RCV_TEXT");

  (*ws->cbs.on_text)(ws->cbs.data, ws, text, len);
}

static void // main-thread
cws_on_binary_cb(void *p_ws, CURL *ehandle, const void *mem, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)mem, len},
    "WS_RCV_BINARY");

  (*ws->cbs.on_binary)(ws->cbs.data, ws, mem, len);
}

static void // main-thread
cws_on_ping_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_PING");

  (*ws->cbs.on_ping)(ws->cbs.data, ws, reason, len);
}

static void // main-thread
cws_on_pong_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_PONG");

  (*ws->cbs.on_pong)(ws->cbs.data, ws, reason, len);
}

/* init easy handle with some default opt */
static CURL* // main-thread
cws_custom_new(struct websockets *ws, const char ws_protocols[])
{
  struct cws_callbacks cws_cbs = {
    .on_connect = &cws_on_connect_cb,
    .on_text = &cws_on_text_cb,
    .on_binary = &cws_on_binary_cb,
    .on_ping = &cws_on_ping_cb,
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
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  CURLE_CHECK(ws, ecode);

#if defined(BEARSSL)
  curl_easy_setopt(new_ehandle, CURLOPT_TIMEOUT, 0L); // never timeout
  CURLE_CHECK(ws, ecode);
#endif

  return new_ehandle;
}

static bool 
_ws_close(struct websockets *ws)
{
  static const char reason[] = "Client initializes close";
  static const enum cws_close_reason code = CWS_CLOSE_REASON_NO_REASON;

  log_debug("_ws_close is called");
  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, sizeof(reason)},
    "WS_SEND_CLOSE(%d)", code);

  if (WS_DISCONNECTED == ws->status) {
    log_warn("[%s] Connection already closed", ws->tag);
    return false;
  }
  if (WS_DISCONNECTING == ws->status) {
    log_warn("[%s] Close already taking place", ws->tag);
    return false;
  }
  _ws_set_status_nolock(ws, WS_DISCONNECTING);

  log_debug("[%s] Sending CLOSE(%d): %s", ws->tag, code, reason);
  if (!cws_close(ws->ehandle, code, reason, sizeof(reason))) {
    log_error("[%s] Couldn't send CLOSE(%d): %s", ws->tag, code, reason);
    return false;
  }
  return true;
}

enum ws_status 
ws_get_status(struct websockets *ws)
{
  pthread_mutex_lock(&ws->lock);
  enum ws_status status = ws->status;
  pthread_mutex_unlock(&ws->lock);
  return status;
}

static void 
noop_on_connect(void *a, struct websockets *b, const char *c)
{return;}
static void 
noop_on_text(void *a, struct websockets *b, const char *c, size_t d)
{return;}
static void 
noop_on_binary(void *a, struct websockets *b, const void *c, size_t d)
{return;}
static void 
noop_on_ping(void *a, struct websockets *ws, const char *b, size_t c) 
{ ws_pong(ws, "Default PONG", sizeof("Default PONG")); }
static void 
noop_on_pong(void *a, struct websockets *b, const char *c, size_t d)
{return;}
static void 
noop_on_close(void *a, struct websockets *b, enum ws_close_reason c, const char *d, size_t e)
{return;}

struct websockets* // main-thread
ws_init(struct ws_callbacks *cbs, struct logconf *config)
{
  struct websockets *new_ws = calloc(1, sizeof *new_ws);
  new_ws->mhandle = curl_multi_init();
  logconf_add_id(config, new_ws, new_ws->tag = "WEBSOCKETS");
  new_ws->p_config = config;

  new_ws->cbs = *cbs;
  // use noop callbacks for missing callbacks
  if (!new_ws->cbs.on_connect) new_ws->cbs.on_connect = &noop_on_connect;
  if (!new_ws->cbs.on_text) new_ws->cbs.on_text = &noop_on_text;
  if (!new_ws->cbs.on_binary) new_ws->cbs.on_binary = &noop_on_binary;
  if (!new_ws->cbs.on_ping) new_ws->cbs.on_ping = &noop_on_ping;
  if (!new_ws->cbs.on_pong) new_ws->cbs.on_pong = &noop_on_pong;
  if (!new_ws->cbs.on_close) new_ws->cbs.on_close = &noop_on_close;

  if (pthread_mutex_init(&new_ws->lock, NULL))
    ERR("[%s] Couldn't initialize pthread mutex", new_ws->tag);

  new_ws->logging_after_exit = false;
  return new_ws;
}

void // thread-safe
ws_set_url(struct websockets *ws, const char base_url[], const char ws_protocols[])
{
  pthread_mutex_lock(&ws->lock);

  if (IS_EMPTY_STRING(ws->base_url))
    log_debug("[%s] Websockets new URL: %s", ws->tag, base_url);
  else
    log_debug("[%s] \n\tWebSockets redirecting:\n\tfrom: %s\n\tto: %s", ws->tag, ws->base_url, base_url);

  int ret = snprintf(ws->base_url, sizeof(ws->base_url), "%s", base_url);
  VASSERT_S(ret < sizeof(ws->base_url), "[%s] Out of bounds write attempt", ws->tag);

  if (!IS_EMPTY_STRING(ws_protocols)) {
    ret = snprintf(ws->protocols, sizeof(ws->protocols), "%s", ws_protocols);
    VASSERT_S(ret < sizeof(ws->protocols), "[%s] Out of bounds write attempt", ws->tag);
  }

  pthread_mutex_unlock(&ws->lock);
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

bool
ws_send_binary(struct websockets *ws, const char msg[], size_t msglen)
{
  VASSERT_S(ws->tid == pthread_self(), "Can only be called from thread %u", ws->tid);

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)msg, msglen},
    "WS_SEND_BINARY");

  if (WS_CONNECTED != ws->status) {
    log_error("[%s] Failed to send '%.*s'", ws->tag, (int)msglen, msg);
    return false;
  }

  log_trace("[%s] Sending BINARY(%zu bytes)", ws->tag, msglen);
  if (!cws_send(ws->ehandle, false, msg, msglen)) {
    log_error("[%s] Couldn't send BINARY(%zu bytes)", ws->tag, msglen);
    return false;
  }
  return true;
}

bool
ws_send_text(struct websockets *ws, const char text[], size_t len)
{
  VASSERT_S(ws->tid == pthread_self(), "Can only be called from thread %u", ws->tid);

  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)text, len},
    "WS_SEND_TEXT");

  if (WS_CONNECTED != ws->status) {
    log_error("[%s] Failed to send '%.*s'", ws->tag, (int)len, text);
    return false;
  }

  log_trace("[%s] Sending TEXT(%zu bytes)", ws->tag, len);
  if (!cws_send(ws->ehandle, true, text, len)) {
    log_error("[%s] Couldn't send TEXT(%zu bytes)", ws->tag, len);
    return false;
  }
  return true;
}

bool ws_ping(struct websockets *ws, const char *reason, size_t len)
{
  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_SEND_PING");

  if (WS_CONNECTED != ws->status) {
    log_error("[%s] Failed to send '%.*s'", ws->tag, (int)len, reason);
    return false;
  }

  log_debug("[%s] Sending PING: %.*s", ws->tag, (int)len, reason);
  if (!cws_ping(ws->ehandle, reason, len)) {
    log_error("[%s] Couldn't send PING: %.*s", ws->tag, (int)len, reason);
    return false;
  }
  return true;
}

bool ws_pong(struct websockets *ws, const char *reason, size_t len)
{
  log_http(
    ws->p_config, 
    ws,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_SEND_PONG");

  if (WS_CONNECTED != ws->status) {
    log_error("[%s] Failed to send '%.*s'", ws->tag, (int)len, reason);
    return false;
  }

  log_debug("[%s] Sending PONG: %.*s", ws->tag, (int)len, reason);
  if (!cws_ping(ws->ehandle, reason, len)) {
    log_error("[%s] Couldn't send PONG: %.*s", ws->tag, (int)len, reason);
    return false;
  }
  return true;
}

/*
 * start a ws connection, and on_hello will be triggered
 * if the connection is established.
 */
void // main-thread
ws_start(struct websockets *ws) 
{
  log_debug("ws_start");
  ws->tid = pthread_self(); // save the starting thread
  ws->tag = logconf_tag(ws->p_config, ws);
  ws->user_cmd = WS_USER_CMD_NONE;
  VASSERT_S(false == ws_is_alive(ws), \
      "[%s] Please shutdown current WebSockets connection before calling ws_start() (Current status: %s)", ws->tag, _ws_status_print(ws->status));
  VASSERT_S(NULL == ws->ehandle, \
      "[%s] (Internal error) Attempt to reconnect without properly closing the connection", ws->tag);
  ws->ehandle = cws_custom_new(ws, ws->protocols);
  curl_multi_add_handle(ws->mhandle, ws->ehandle);
  _ws_set_status(ws, WS_CONNECTING);  
}

void // main-thread
ws_perform(struct websockets *ws, bool *p_is_running, uint64_t wait_ms)
{
  /*
  if (ws->logging_after_exit)
    log_info("ws_perform after ws_exit_event_loop");
  */
  if (ws->tid != pthread_self())
    ERR("ws_perform can only be called from the starting thread %u", ws->tid);

  int is_running = 0;
  CURLMcode mcode;
  int numfds = 0;

  /**
   * Update WebSockets concept of "now"
   * @see ws_timestamp()
   */
  pthread_mutex_lock(&ws->lock);
  ws->now_tstamp = cee_timestamp_ms();
  pthread_mutex_unlock(&ws->lock);

  /**
   * Perform Read/Write pending sockets activity (if any)
   * @note ws_close() and ws_send_text() are example of pending
   *        write activities
   * @note Callbacks such as ws_on_text(), ws_on_ping(), etc are
   *        example of pending read activities
   * @note Its worth noting that all websockets.c callbacks are
   *        inherently single-threaded. websockets.c doesn't create
   *        new threads.
   */
  mcode = curl_multi_perform(ws->mhandle, &is_running);
  VASSERT_S(CURLM_OK == mcode, "[%s] (CURLM code: %d) %s", ws->tag, mcode, curl_multi_strerror(mcode));

  if (is_running) { // WebSockets connection is active
    // wait for some activity or timeout after "wait_ms" elapsed
    mcode = curl_multi_wait(ws->mhandle, NULL, 0, wait_ms, &numfds);
    VASSERT_S(CURLM_OK == mcode, "[%s] (CURLM code: %d) %s", ws->tag, mcode, curl_multi_strerror(mcode));

    pthread_mutex_lock(&ws->lock);
    if (ws->user_cmd == WS_USER_CMD_EXIT) {
      log_warn("user_cmd WS_USER_CMD_EXIT");
      if (numfds) {
        log_debug("curl_multi_wait returns %d pending file descriptors.",
                  numfds);
        cee_sleep_ms(5);
      }
      _ws_close(ws);
      ws->user_cmd = WS_USER_CMD_NONE;
      ws->logging_after_exit = true;
    }
    pthread_mutex_unlock(&ws->lock);
  }
  else { // WebSockets connection is severed
    ws->logging_after_exit = false;
    log_warn("ws connection is severed: is_running %d", is_running);
    _ws_set_status(ws, WS_DISCONNECTING);
    // read messages/informationals from the individual transfers
    int msgq = 0;
    struct CURLMsg *curlmsg = curl_multi_info_read(ws->mhandle, &msgq);
    if (curlmsg) {
      CURLcode ecode = curlmsg->data.result;
      switch (ecode) {
      case CURLE_OK:
          log_info("[%s] Disconnected gracefully", ws->tag);
          break;
      case CURLE_READ_ERROR:
          log_error("[%s] (CURLE code: %d) %s", \
              ws->tag,
                    ecode,
                    IS_EMPTY_STRING(ws->errbuf)
                    ? curl_easy_strerror(ecode)
                    : ws->errbuf);
          log_error("[%s] Disconnected abruptly", ws->tag);
          break;
      default:
          log_error("[%s] (CURLE code: %d) %s", \
              ws->tag,
              ecode, 
              IS_EMPTY_STRING(ws->errbuf) 
                  ? curl_easy_strerror(ecode) 
                  : ws->errbuf);
          log_error("[%s] Disconnected abruptly", ws->tag);
          break;
      }
    }
    else {
      log_warn("[%s] Exit before establishing a connection", ws->tag);
    }
    
    curl_multi_remove_handle(ws->mhandle, ws->ehandle);

    // reset for next iteration
    *ws->errbuf = '\0';
    if (ws->ehandle) {
      cws_free(ws->ehandle);
      ws->ehandle = NULL;
    }

    _ws_set_status(ws, WS_DISCONNECTED);
  }

  *p_is_running = is_running;
}

uint64_t
ws_timestamp(struct websockets *ws) 
{
  pthread_mutex_lock(&ws->lock);
  uint64_t now_tstamp = ws->now_tstamp;
  pthread_mutex_unlock(&ws->lock);
  return now_tstamp;
}

bool ws_is_alive(struct websockets *ws)
{
  return WS_DISCONNECTED != ws_get_status(ws);
}

bool ws_is_functional(struct websockets *ws)
{
  return WS_CONNECTED == ws_get_status(ws);
}

/*
 * It can be called from any thread to exit
 * the ws event loop. Depending on the values of
 * reconnect and is_resumable, the outer loop will
 * do one of the followings:
 *
 *   1. reconnect: send out new identifier
 *   2. resume
 *   3. exit
 *
 */
void ws_exit_event_loop(struct websockets *ws)
{
  pthread_mutex_lock(&ws->lock);
  log_warn("ws_exit_event_loop is called");
  ws->user_cmd = WS_USER_CMD_EXIT;
  pthread_mutex_unlock(&ws->lock);
}

bool ws_same_thread(struct websockets *ws)
{
  return (ws->tid == pthread_self());
}
