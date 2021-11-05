#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>

#include "curl-websocket.h"

#include "websockets.h"
#include "cee-utils.h"

#define CURLE_CHECK(ws, ecode)                                                \
  VASSERT_S(                                                                  \
    CURLE_OK == ecode, "[%s] (CURLE code: %d) %s", ws->conf.id, ecode,        \
    IS_EMPTY_STRING(ws->errbuf) ? curl_easy_strerror(ecode) : ws->errbuf)

#define CURLM_CHECK(ws, mcode)                                                \
  VASSERT_S(CURLM_OK == mcode, "[%s] (CURLM code: %d) %s", ws->conf.id,       \
            mcode, curl_multi_strerror(mcode))

struct websockets {
  /**
   * Stores info on the latest transfer performed via websockets
   */
  struct ws_info info;
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
   * The logconf structure for logging facility
   * @see logconf.h
   */
  struct logconf conf;

  pthread_mutex_t lock;
  /*
   * This is used to check whether the running thread
   * is the same as the thread that ran ws_start.
   * Some functions can only run in the same thread
   */
  pthread_t tid;

  /**
   * The user may close the active connection via ws_close()
   * @see ws_close()
   */
  enum {
    WS_ACTION_NONE = 0,
    WS_ACTION_BEGIN_CLOSE,
    WS_ACTION_END_CLOSE
  } action;

  struct {
    enum ws_close_reason code;
    char reason[125 + 1];
  } pending_close;
};

static void
dump(const char *text, FILE *stream, unsigned char *ptr, size_t size)
{
  size_t i;
  size_t c;

  unsigned int width = 0x10;

  fprintf(stream, "%s, %10.10lu bytes (0x%8.8lx)\n", text, (unsigned long)size,
          (unsigned long)size);

  for (i = 0; i < size; i += width) {

    fprintf(stream, "%4.4lx: ", (unsigned long)i);

    for (c = 0; c < width; c++)
      if (i + c < size)
        fprintf(stream, "%02x ", ptr[i + c]);
      else
        fputs("   ", stream);

    for (c = 0; (c < width) && (i + c < size); c++) {
      /* check for 0D0A; if found, skip past and start a new line of output */
      if ((i + c + 1 < size) && ptr[i + c] == 0x0D && ptr[i + c + 1] == 0x0A) {
        i += (c + 2 - width);
        break;
      }
      fprintf(stream, "%c",
              (ptr[i + c] >= 0x20) && (ptr[i + c] < 0x80) ? ptr[i + c] : '.');
      /* check again for 0D0A, to avoid an extra \n if it's at width */
      if ((i + c + 2 < size) && ptr[i + c + 1] == 0x0D &&
          ptr[i + c + 2] == 0x0A) {
        i += (c + 3 - width);
        break;
      }
    }
    fputc('\n', stream); /* newline */
  }
  fflush(stream);
}

static int
_curl_debug_trace(
  CURL *handle, curl_infotype type, char *data, size_t size, void *userp)
{
  (void)handle;
  (void)userp;

  const char *text;
  switch (type) {
  case CURLINFO_TEXT:
    fprintf(stderr, "== Info: %s", data);
    /* FALLTHROUGH */
  default: /* in case a new one is introduced to shock us */ return 0;

  case CURLINFO_HEADER_OUT: text = "=> Send header"; break;
  case CURLINFO_DATA_OUT: text = "=> Send data"; break;
  case CURLINFO_SSL_DATA_OUT: text = "=> Send SSL data"; break;
  case CURLINFO_HEADER_IN: text = "<= Recv header"; break;
  case CURLINFO_DATA_IN: text = "<= Recv data"; break;
  case CURLINFO_SSL_DATA_IN: text = "<= Recv SSL data"; break;
  }

  dump(text, stderr, (unsigned char *)data, size);
  return 0;
}

static int
_curl_tls_check(
  CURL *handle, curl_infotype type, char *data, size_t size, void *userp)
{
  (void)handle;
  (void)data;
  (void)size;

  if (CURLINFO_TEXT == type && strstr(data, "close notify (256)")) {
    char reason[] = "TLS ended connection with a close notify (256)";
    ws_close(userp, WS_CLOSE_REASON_ABRUPTLY, reason, sizeof(reason) - 1);
  }
  return 0;
}

const char *
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

static const char *
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

static CURL *_ws_cws_new(struct websockets *ws, const char ws_protocols[]);

static void
_ws_set_status_nolock(struct websockets *ws, enum ws_status status)
{
  if ((WS_DISCONNECTING == ws->status) && (status != WS_DISCONNECTED))
    return; /* EARLY RETURN */

  switch (status) {
  case WS_DISCONNECTED:
    VASSERT_S(WS_DISCONNECTING == ws->status,
              "[%s] (Internal Error) Disconnect abruptly (Current status: %s)",
              ws->conf.id, _ws_status_print(ws->status));
    logconf_debug(&ws->conf, "Change status to WS_DISCONNECTED");
    break;
  case WS_CONNECTED:
    VASSERT_S(
      WS_CONNECTING == ws->status,
      "[%s] Missing ws_start() before the event loop (Current status: %s)",
      ws->conf.id, _ws_status_print(ws->status));
    logconf_debug(&ws->conf, "Change status to WS_CONNECTED");
    break;
  case WS_DISCONNECTING:
    logconf_debug(&ws->conf, "Change status to WS_DISCONNECTING");
    break;
  case WS_CONNECTING: /* triggered at ws_start() */
    logconf_debug(&ws->conf, "Change status to WS_CONNECTING");
    break;
  default:
    ERR("[%s] Unknown ws_status (code: %d)", ws->conf.id, status);
    break;
  }
  ws->status = status;
}

/* thread-safe */
static void
_ws_set_status(struct websockets *ws, enum ws_status status)
{
  pthread_mutex_lock(&ws->lock);
  _ws_set_status_nolock(ws, status);
  pthread_mutex_unlock(&ws->lock);
}

static void
cws_on_connect_cb(void *p_ws, CURL *ehandle, const char *ws_protocols)
{
  struct websockets *ws = p_ws;

  _ws_set_status(ws, WS_CONNECTED);

  logconf_http(
    &ws->conf, &ws->info.loginfo, ws->base_url, (struct sized_buffer){ "", 0 },
    (struct sized_buffer){ (char *)ws_protocols, strlen(ws_protocols) },
    "WS_RCV_CONNECT");

  logconf_trace(
    &ws->conf,
    ANSICOLOR("RCV",
              ANSI_FG_YELLOW) " CONNECT (WS-Protocols: '%s') [@@@_%zu_@@@]",
    ws_protocols, ws->info.loginfo.counter);

  (*ws->cbs.on_connect)(ws->cbs.data, ws, &ws->info, ws_protocols);
}

static void
cws_on_close_cb(void *p_ws,
                CURL *ehandle,
                enum cws_close_reason cwscode,
                const char *reason,
                size_t len)
{
  struct websockets *ws = p_ws;

  _ws_set_status(ws, WS_DISCONNECTING);

  logconf_http(
    &ws->conf, &ws->info.loginfo, ws->base_url, (struct sized_buffer){ "", 0 },
    (struct sized_buffer){ (char *)reason, len }, "WS_RCV_CLOSE(%d)", cwscode);

  logconf_trace(
    &ws->conf,
    ANSICOLOR("RCV", ANSI_FG_YELLOW) " CLOSE(%d) (%zu bytes) [@@@_%zu_@@@]",
    cwscode, len, ws->info.loginfo.counter);

  (*ws->cbs.on_close)(ws->cbs.data, ws, &ws->info, cwscode, reason, len);
  ws->action = WS_ACTION_END_CLOSE;

  /* will set status to WS_DISCONNECTED when is_running == false */
}

static void
cws_on_text_cb(void *p_ws, CURL *ehandle, const char *text, size_t len)
{
  struct websockets *ws = p_ws;

  logconf_http(&ws->conf, &ws->info.loginfo, ws->base_url,
               (struct sized_buffer){ "", 0 },
               (struct sized_buffer){ (char *)text, len }, "WS_RCV_TEXT");

  logconf_trace(
    &ws->conf,
    ANSICOLOR("RCV", ANSI_FG_YELLOW) " TEXT (%zu bytes) [@@@_%zu_@@@]", len,
    ws->info.loginfo.counter);

  (*ws->cbs.on_text)(ws->cbs.data, ws, &ws->info, text, len);
}

static void
cws_on_binary_cb(void *p_ws, CURL *ehandle, const void *mem, size_t len)
{
  struct websockets *ws = p_ws;

  logconf_http(&ws->conf, &ws->info.loginfo, ws->base_url,
               (struct sized_buffer){ "", 0 },
               (struct sized_buffer){ (char *)mem, len }, "WS_RCV_BINARY");

  logconf_trace(
    &ws->conf,
    ANSICOLOR("RCV", ANSI_FG_YELLOW) " BINARY (%zu bytes) [@@@_%zu_@@@]", len,
    ws->info.loginfo.counter);

  (*ws->cbs.on_binary)(ws->cbs.data, ws, &ws->info, mem, len);
}

static void
cws_on_ping_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

#if 0
  logconf_http(
    &ws->conf, 
    &ws->info.loginfo,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_PING");
#endif
  logconf_trace(
    &ws->conf,
    ANSICOLOR("RCV", ANSI_FG_YELLOW) " PING (%zu bytes) [@@@_%zu_@@@]", len,
    ws->info.loginfo.counter);

  (*ws->cbs.on_ping)(ws->cbs.data, ws, &ws->info, reason, len);
}

static void
cws_on_pong_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;

#if 0
  logconf_http(
    &ws->conf, 
    &ws->info.loginfo,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_RCV_PONG");
#endif
  logconf_trace(
    &ws->conf,
    ANSICOLOR("RCV", ANSI_FG_YELLOW) " PONG (%zu bytes) [@@@_%zu_@@@]", len,
    ws->info.loginfo.counter);

  (*ws->cbs.on_pong)(ws->cbs.data, ws, &ws->info, reason, len);
}

static bool _ws_close(struct websockets *ws,
                      enum ws_close_reason code,
                      const char reason[]);

static int
_ws_check_action_cb(void *p_userdata,
                    curl_off_t dltotal,
                    curl_off_t dlnow,
                    curl_off_t ultotal,
                    curl_off_t ulnow)
{
  struct websockets *ws = p_userdata;
  int ret;

  pthread_mutex_lock(&ws->lock);
  switch (ws->action) {
  case WS_ACTION_BEGIN_CLOSE:
    logconf_warn(&ws->conf, "Received pending %s, closing the connection ...",
                 ws_close_opcode_print(ws->pending_close.code));
    _ws_close(ws, ws->pending_close.code, ws->pending_close.reason);
  /* fall-through */
  case WS_ACTION_NONE:
  default: ret = 0; break;
  case WS_ACTION_END_CLOSE:
    ret = 1; /* END WEBSOCKETS CONNECTION */
    break;
  }
  ws->action = WS_ACTION_NONE;
  pthread_mutex_unlock(&ws->lock);

  return ret;
}

/* init easy handle with some default opt */
static CURL *
_ws_cws_new(struct websockets *ws, const char ws_protocols[])
{
  struct cws_callbacks cws_cbs = { .on_connect = &cws_on_connect_cb,
                                   .on_text = &cws_on_text_cb,
                                   .on_binary = &cws_on_binary_cb,
                                   .on_ping = &cws_on_ping_cb,
                                   .on_pong = &cws_on_pong_cb,
                                   .on_close = &cws_on_close_cb,
                                   .data = ws };

  CURL *new_ehandle = cws_new(ws->base_url, ws_protocols, &cws_cbs);

  CURLcode ecode;
  /* set error buffer for capturing CURL error descriptions */
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_ERRORBUFFER, ws->errbuf);
  CURLE_CHECK(ws, ecode);
  /* enable follow redirections */
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 1L);
  CURLE_CHECK(ws, ecode);
  /* enable progress function (a callback that executes constantly) */
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_XFERINFOFUNCTION,
                           &_ws_check_action_cb);
  CURLE_CHECK(ws, ecode);
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_XFERINFODATA, ws);
  CURLE_CHECK(ws, ecode);
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_NOPROGRESS, 0L);
  CURLE_CHECK(ws, ecode);

#ifdef _ORCA_DEBUG_WEBSOCKETS
  ecode =
    curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, _curl_debug_trace);
  CURLE_CHECK(ws, ecode);
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L);
  CURLE_CHECK(ws, ecode);
#else
  ecode =
    curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, _curl_tls_check);
  CURLE_CHECK(ws, ecode);
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L);
  CURLE_CHECK(ws, ecode);
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGDATA, ws);
  CURLE_CHECK(ws, ecode);
#endif

  return new_ehandle;
}

static bool
_ws_close(struct websockets *ws,
          enum ws_close_reason code,
          const char reason[])
{
  logconf_http(&ws->conf, &ws->info.loginfo, ws->base_url,
               (struct sized_buffer){ "", 0 },
               (struct sized_buffer){ (char *)reason, strlen(reason) },
               "WS_SEND_CLOSE(%d)", code);

  logconf_trace(&ws->conf,
                ANSICOLOR("SEND", ANSI_FG_GREEN) " CLOSE (%s) [@@@_%zu_@@@]",
                reason, ws->info.loginfo.counter);

  if (WS_DISCONNECTED == ws->status) {
    logconf_warn(
      &ws->conf,
      ANSICOLOR("Failed", ANSI_FG_RED) " at SEND CLOSE : Connection already "
                                       "closed [@@@_%zu_@@@]",
      ws->info.loginfo.counter);
    return false;
  }
  if (WS_DISCONNECTING == ws->status) {
    logconf_warn(
      &ws->conf,
      ANSICOLOR("Failed", ANSI_FG_RED) " at SEND CLOSE : Close already taking "
                                       "place [@@@_%zu_@@@]",
      ws->info.loginfo.counter);
    return false;
  }
  _ws_set_status_nolock(ws, WS_DISCONNECTING);

  if (!cws_close(ws->ehandle, (enum cws_close_reason)code, reason, SIZE_MAX)) {
    logconf_error(
      &ws->conf,
      ANSICOLOR("Failed", ANSI_FG_RED) " at SEND CLOSE(%d): %s [@@@_%zu_@@@]",
      code, reason, ws->info.loginfo.counter);
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
noop_on_connect(void *a,
                struct websockets *b,
                struct ws_info *info,
                const char *c)
{
  return;
}
static void
noop_on_text(
  void *a, struct websockets *b, struct ws_info *info, const char *c, size_t d)
{
  return;
}
static void
noop_on_binary(
  void *a, struct websockets *b, struct ws_info *info, const void *c, size_t d)
{
  return;
}
static void
noop_on_ping(void *a,
             struct websockets *ws,
             struct ws_info *info,
             const char *reason,
             size_t len)
{
  ws_pong(ws, &ws->info, reason, len);
}
static void
noop_on_pong(
  void *a, struct websockets *b, struct ws_info *info, const char *c, size_t d)
{
  return;
}
static void
noop_on_close(void *a,
              struct websockets *b,
              struct ws_info *info,
              enum ws_close_reason c,
              const char *d,
              size_t e)
{
  return;
}

struct websockets *
ws_init(struct ws_callbacks *cbs, struct logconf *conf)
{
  struct websockets *new_ws = calloc(1, sizeof *new_ws);
  new_ws->mhandle = curl_multi_init();

  logconf_branch(&new_ws->conf, conf, "WEBSOCKETS");

  new_ws->cbs = *cbs;
  /* use noop callbacks for missing callbacks */
  if (!new_ws->cbs.on_connect) new_ws->cbs.on_connect = &noop_on_connect;
  if (!new_ws->cbs.on_text) new_ws->cbs.on_text = &noop_on_text;
  if (!new_ws->cbs.on_binary) new_ws->cbs.on_binary = &noop_on_binary;
  if (!new_ws->cbs.on_ping) new_ws->cbs.on_ping = &noop_on_ping;
  if (!new_ws->cbs.on_pong) new_ws->cbs.on_pong = &noop_on_pong;
  if (!new_ws->cbs.on_close) new_ws->cbs.on_close = &noop_on_close;

  if (pthread_mutex_init(&new_ws->lock, NULL))
    ERR("[%s] Couldn't initialize pthread mutex", new_ws->conf.id);

  return new_ws;
}

void
ws_set_url(struct websockets *ws,
           const char base_url[],
           const char ws_protocols[])
{
  pthread_mutex_lock(&ws->lock);

  if (IS_EMPTY_STRING(ws->base_url))
    logconf_debug(&ws->conf, "Websockets new URL: %s", base_url);
  else
    logconf_debug(&ws->conf, "WebSockets redirecting:\n\tfrom: %s\n\tto: %s",
                  ws->base_url, base_url);

  int ret = snprintf(ws->base_url, sizeof(ws->base_url), "%s", base_url);
  VASSERT_S(ret < sizeof(ws->base_url), "[%s] Out of bounds write attempt",
            ws->conf.id);

  if (!IS_EMPTY_STRING(ws_protocols)) {
    ret = snprintf(ws->protocols, sizeof(ws->protocols), "%s", ws_protocols);
    VASSERT_S(ret < sizeof(ws->protocols), "[%s] Out of bounds write attempt",
              ws->conf.id);
  }

  pthread_mutex_unlock(&ws->lock);
}

void
ws_cleanup(struct websockets *ws)
{
  curl_multi_cleanup(ws->mhandle);
  if (ws->ehandle) cws_free(ws->ehandle);
  pthread_mutex_destroy(&ws->lock);
  free(ws);
}

bool
ws_send_binary(struct websockets *ws,
               struct ws_info *info,
               const char msg[],
               size_t msglen)
{
  ASSERT_S(ws->tid == pthread_self(), "Can only be called from main-thread");

  logconf_http(&ws->conf, NULL, ws->base_url, (struct sized_buffer){ "", 0 },
               (struct sized_buffer){ (char *)msg, msglen }, "WS_SEND_BINARY");

  logconf_trace(
    &ws->conf,
    ANSICOLOR("SEND", ANSI_FG_GREEN) " BINARY (%zu bytes) [@@@_%zu_@@@]",
    msglen, ws->info.loginfo.counter);

  if (WS_CONNECTED != ws->status) {
    logconf_error(
      &ws->conf,
      ANSICOLOR(
        "Failed",
        ANSI_FG_RED) " at SEND BINARY : No active connection [@@@_%zu_@@@]",
      ws->info.loginfo.counter);
    return false;
  }

  if (info) *info = ws->info;

  if (!cws_send(ws->ehandle, false, msg, msglen)) {
    logconf_error(
      &ws->conf,
      ANSICOLOR("Failed", ANSI_FG_RED) " at SEND BINARY [@@@_%zu_@@@]",
      ws->info.loginfo.counter);
    return false;
  }
  return true;
}

bool
ws_send_text(struct websockets *ws,
             struct ws_info *info,
             const char text[],
             size_t len)
{
  ASSERT_S(ws->tid == pthread_self(), "Can only be called from main-thread");

  logconf_http(&ws->conf, NULL, ws->base_url, (struct sized_buffer){ "", 0 },
               (struct sized_buffer){ (char *)text, len }, "WS_SEND_TEXT");

  logconf_trace(
    &ws->conf,
    ANSICOLOR("SEND", ANSI_FG_GREEN) " TEXT (%zu bytes) [@@@_%zu_@@@]", len,
    ws->info.loginfo.counter);

  if (WS_CONNECTED != ws->status) {
    logconf_error(
      &ws->conf,
      ANSICOLOR(
        "Failed",
        ANSI_FG_RED) " at SEND TEXT : No active connection [@@@_%zu_@@@]",
      ws->info.loginfo.counter);
    return false;
  }

  if (info) *info = ws->info;

  if (!cws_send(ws->ehandle, true, text, len)) {
    logconf_error(
      &ws->conf,
      ANSICOLOR("Failed", ANSI_FG_RED) " at SEND TEXT [@@@_%zu_@@@]",
      ws->info.loginfo.counter);
    return false;
  }
  return true;
}

bool
ws_ping(struct websockets *ws,
        struct ws_info *info,
        const char *reason,
        size_t len)
{
/* disabled because this creates too many entries */
#if 0
  logconf_http(
    &ws->conf, 
    &ws->info.loginfo,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_SEND_PING");
#endif
  logconf_trace(
    &ws->conf,
    ANSICOLOR("SEND", ANSI_FG_GREEN) " PING (%zu bytes) [@@@_%zu_@@@]", len,
    ws->info.loginfo.counter);

  if (WS_CONNECTED != ws->status) {
    logconf_error(
      &ws->conf,
      ANSICOLOR("Failed", ANSI_FG_RED) " at SEND PING : No active connection");
    return false;
  }

  if (!cws_ping(ws->ehandle, reason, len)) {
    logconf_error(&ws->conf,
                  ANSICOLOR("Failed", ANSI_FG_RED) " at SEND PING.");
    return false;
  }
  return true;
}

bool
ws_pong(struct websockets *ws,
        struct ws_info *info,
        const char *reason,
        size_t len)
{
/* disabled because this creates too many entries */
#if 0
  logconf_http(
    &ws->conf, 
    &ws->info.loginfo,
    ws->base_url, 
    (struct sized_buffer){"", 0},
    (struct sized_buffer){(char*)reason, len},
    "WS_SEND_PONG");
#endif
  logconf_trace(
    &ws->conf,
    ANSICOLOR("SEND", ANSI_FG_GREEN) " PONG (%zu bytes) [@@@_%zu_@@@]", len,
    ws->info.loginfo.counter);

  if (WS_CONNECTED != ws->status) {
    logconf_error(
      &ws->conf,
      ANSICOLOR("Failed", ANSI_FG_RED) " at SEND PONG : No active connection");
    return false;
  }

  if (!cws_pong(ws->ehandle, reason, len)) {
    logconf_error(&ws->conf,
                  ANSICOLOR("Failed", ANSI_FG_RED) " at SEND PONG.");
    return false;
  }
  return true;
}

void
ws_start(struct websockets *ws)
{
  ws->tid = pthread_self(); /* save the starting thread */
  memset(&ws->pending_close, 0, sizeof ws->pending_close);
  ws->action = WS_ACTION_NONE;

  VASSERT_S(false == ws_is_alive(ws),
            "[%s] Please shutdown current WebSockets connection before "
            "calling ws_start() (Current status: %s)",
            ws->conf.id, _ws_status_print(ws->status));
  VASSERT_S(NULL == ws->ehandle,
            "[%s] (Internal error) Attempt to reconnect without properly "
            "closing the connection",
            ws->conf.id);
  ws->ehandle = _ws_cws_new(ws, ws->protocols);
  curl_multi_add_handle(ws->mhandle, ws->ehandle);
  _ws_set_status(ws, WS_CONNECTING);
}

void
ws_perform(struct websockets *ws, bool *p_is_running, uint64_t wait_ms)
{
  ASSERT_S(
    ws->tid == pthread_self(),
    "ws_perform() should only be called from its initialization thread");

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
  CURLM_CHECK(ws, mcode);

  /* wait for some activity or timeout after "wait_ms" elapsed */
  mcode = curl_multi_wait(ws->mhandle, NULL, 0, wait_ms, &numfds);
  CURLM_CHECK(ws, mcode);

  if (!is_running) { /* WebSockets connection is severed */
    _ws_set_status(ws, WS_DISCONNECTING);

    /* read messages/informationals from the individual transfers */
    int msgq = 0;
    struct CURLMsg *curlmsg = curl_multi_info_read(ws->mhandle, &msgq);
    if (curlmsg) {
      CURLcode ecode = curlmsg->data.result;
      switch (ecode) {
      case CURLE_OK:
      case CURLE_ABORTED_BY_CALLBACK: /* _ws_check_action_cb() */
        logconf_info(&ws->conf, "Disconnected gracefully");
        break;
      case CURLE_READ_ERROR:
      default:
        logconf_error(&ws->conf, "(CURLE code: %d) %s", ecode,
                      IS_EMPTY_STRING(ws->errbuf) ? curl_easy_strerror(ecode)
                                                  : ws->errbuf);
        logconf_error(&ws->conf, "Disconnected abruptly");
        break;
      }
    }
    else {
      logconf_warn(&ws->conf, "Exit before establishing a connection");
    }

    curl_multi_remove_handle(ws->mhandle, ws->ehandle);

    /* reset for next iteration */
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

bool
ws_is_alive(struct websockets *ws)
{
  return WS_DISCONNECTED != ws_get_status(ws);
}

bool
ws_is_functional(struct websockets *ws)
{
  return WS_CONNECTED == ws_get_status(ws);
}

void
ws_close(struct websockets *ws,
         const enum ws_close_reason code,
         const char reason[],
         const size_t len)
{
  logconf_warn(&ws->conf,
               "Attempting to close WebSockets connection with %s : %.*s",
               ws_close_opcode_print(code), (int)len, reason);

  pthread_mutex_lock(&ws->lock);
  ws->action = WS_ACTION_BEGIN_CLOSE;
  ws->pending_close.code = code;
  snprintf(ws->pending_close.reason, sizeof(ws->pending_close.reason), "%.*s",
           (int)len, reason);
  pthread_mutex_unlock(&ws->lock);
}

bool
ws_same_thread(struct websockets *ws)
{
  return ws->tid == pthread_self();
}

int
ws_lock(struct websockets *ws)
{
  return pthread_mutex_lock(&ws->lock);
}

int
ws_unlock(struct websockets *ws)
{
  return pthread_mutex_unlock(&ws->lock);
}

void
ws_reqheader_add(struct websockets *ws, const char field[], const char value[])
{
  ASSERT_S(ws_is_alive(ws),
           "ws_start() must have been called prior to ws_reqheader_add()");
  cws_reqheader_add(ws->ehandle, field, value);
}
