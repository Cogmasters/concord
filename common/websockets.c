#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>

#include "curl-websocket.h"

#include "websockets.h"
#include "orka-utils.h"
#include "orka-config.h"


struct event_cb {
  int code; // code that should trigger the callback
  void (*cb)(void *data, void *curr_iter_data); // see ws_set_curr_iter_data()
};

struct wthread { // worker thread
  pthread_t tid;
  bool is_busy;

  /* the following are set by ws_set_curr_iter_data() */
  void *data; //user arbitrary data that lasts for this thread cycle
  void (*cleanup)(void *data); //data cleanup method
};

#define MAX_THREADS 10 //@todo temp size just for prototyping
struct websockets {
  struct orka_config config;
  enum ws_status status;
  CURLM *mhandle;
  CURL *ehandle;
  uint64_t wait_ms; // how long to wait for sockets activity
  uint64_t now_tstamp; // timestamp updated every loop iteration

  struct { /* RECONNECT STRUCT */
    int threshold; // max reconnections attempts before quitting
    int attempt; // current count of reconnection attempt
  } reconnect;

  char *base_url;

  struct ws_callbacks cbs; 
  struct event_cb *event_pool; //events set with ws_set_event()
  size_t num_events;

  /* will last only for this current loop iteration, the data is 
   *   passed as a event_pool callback parameter, and free'd from 
   *   memory with the given cleanup function (if any is given) */
  void *curr_iter_data;
  void (*curr_iter_cleanup)(void *curr_iter_data);

  struct wthread thread_pool[MAX_THREADS];
  int num_notbusy; // num of available threads

  pthread_mutex_t lock;
  pthread_cond_t cond;
};


static void
cws_on_connect_cb(void *p_ws, CURL *ehandle, const char *ws_protocols)
{
  struct websockets *ws = p_ws;
  (*ws->cbs.on_connect)(ws->cbs.data, ws_protocols);
}

static void
cws_on_close_cb(void *p_ws, CURL *ehandle, enum cws_close_reason cwscode, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;
  (*ws->cbs.on_close)(ws->cbs.data, cwscode, reason, len);
}

struct _event_cxt {
  struct websockets *ws; // the websockets client
  struct event_cb *event; // callback associated with event
  struct wthread *thread; // thread associated with event
};

static void*
event_run(void *p_cxt)
{
  struct _event_cxt *cxt = p_cxt;

  (*cxt->event->cb)(cxt->ws->cbs.data, cxt->thread->data);

  pthread_mutex_lock(&cxt->ws->lock);
  cxt->thread->is_busy = false;
  ++cxt->ws->num_notbusy;
  if (cxt->thread->data && cxt->thread->cleanup) {
    (*cxt->thread->cleanup)(cxt->thread->data);
  }
  cxt->thread->cleanup = NULL;
  cxt->thread->data = NULL;

  pthread_cond_signal(&cxt->ws->cond);
  pthread_mutex_unlock(&cxt->ws->lock);

  free(cxt);

  return NULL;
}

static void
cws_on_text_cb(void *p_ws, CURL *ehandle, const char *text, size_t len)
{
  struct websockets *ws = p_ws;

  int event_code = (*ws->cbs.on_text_event)(ws->cbs.data, text, len);
  for (size_t i=0; i < ws->num_events; ++i) {
    if (event_code != ws->event_pool[i].code) 
      continue;

    pthread_mutex_lock(&ws->lock);

    (*ws->config.http_dump_cb)(
      true,
      event_code, "ON_EVENT",
      &ws->config, 
      ws->base_url, 
      (char*)text);

    // wait until a thread is available before proceeding
    while (!ws->num_notbusy) {
      pthread_cond_wait(&ws->cond, &ws->lock);
    }

    //@todo non-heap MT-Safe alternative ?
    struct _event_cxt *cxt = calloc(1, sizeof(struct _event_cxt));
    cxt->ws = ws;
    cxt->event = &ws->event_pool[i];

    // get a available thread
    for (size_t i=0; i < MAX_THREADS; ++i) {
      if (!ws->thread_pool[i].is_busy) {
        --ws->num_notbusy;

        cxt->thread = &ws->thread_pool[i];
        cxt->thread->is_busy = true;
        cxt->thread->data = ws->curr_iter_data;
        cxt->thread->cleanup = ws->curr_iter_cleanup;
        ws->curr_iter_data = NULL;
        ws->curr_iter_cleanup = NULL;
        break; /* EARLY BREAK */
      }
    }
    ASSERT_S(NULL != cxt->thread, "Internal thread synchronization error (couldn't fetch thread)");

    if (pthread_create(&cxt->thread->tid, NULL, &event_run, cxt))
      ERR("Couldn't create thread");
    if (pthread_detach(cxt->thread->tid))
      ERR("Couldn't detach thread");

    pthread_mutex_unlock(&ws->lock);
    return; /* EARLY RETURN */
  }

  pthread_mutex_lock(&ws->lock);

  if (ws->curr_iter_data && ws->curr_iter_cleanup) {
    (*ws->curr_iter_cleanup)(ws->curr_iter_data);
  }
  ws->curr_iter_cleanup = NULL;
  ws->curr_iter_data = NULL;

  (*ws->config.http_dump_cb)(
    false,
    0, "ON_TEXT",
    &ws->config, 
    ws->base_url, 
    (char*)text);

  pthread_mutex_unlock(&ws->lock);

  (*ws->cbs.on_text)(ws->cbs.data, text, len);
}

static void
cws_on_binary_cb(void *p_ws, CURL *ehandle, const void *mem, size_t len)
{
  struct websockets *ws = p_ws;
  (*ws->cbs.on_binary)(ws->cbs.data, mem, len);
}

static void
cws_on_ping_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;
  (*ws->cbs.on_ping)(ws->cbs.data, reason, len);
}

static void
cws_on_pong_cb(void *p_ws, CURL *ehandle, const char *reason, size_t len)
{
  struct websockets *ws = p_ws;
  (*ws->cbs.on_pong)(ws->cbs.data, reason, len);
}

/* init easy handle with some default opt */
static CURL*
custom_cws_new(struct websockets *ws)
{
  struct cws_callbacks cws_cbs = {0};
  cws_cbs.on_connect = &cws_on_connect_cb;
  cws_cbs.on_text = &cws_on_text_cb;
  cws_cbs.on_binary = &cws_on_binary_cb;
  cws_cbs.on_ping = &cws_on_pong_cb;
  cws_cbs.on_pong = &cws_on_pong_cb;
  cws_cbs.on_close = &cws_on_close_cb;
  cws_cbs.data = ws;

  CURL *new_ehandle = cws_new(ws->base_url, NULL, &cws_cbs);
  ASSERT_S(NULL != new_ehandle, "Out of memory");

  CURLcode ecode;
  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 2L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

/* @todo
  // execute user-defined curl_easy_setopts
  if (ws->setopt_cb) {
    (*ws->setopt_cb)(new_ehandle, ws->cbs.data);
  }
*/

  return new_ehandle;
}

static int noop_on_startup(void *a){return 1;}
static void noop_on_iter(void *a){return;}
static int noop_on_text_event(void *a, const char *b, size_t c)
{return INT_MIN;} // return unlikely event value as default

static void noop_on_connect(void *a, const char *b){return;}
static void noop_on_text(void *a, const char *b, size_t c){return;}
static void noop_on_binary(void *a, const void *b, size_t c){return;}
static void noop_on_ping(void *a, const char *b, size_t c){return;}
static void noop_on_pong(void *a, const char *b, size_t c){return;}
static void noop_on_close(void *a, enum ws_close_reason b, const char *c, size_t d){return;}

struct websockets*
ws_init(const char base_url[], struct ws_callbacks *cbs)
{
  struct websockets *new_ws = calloc(1, sizeof *new_ws);

  new_ws->base_url = strdup(base_url);
  new_ws->status = WS_DISCONNECTED;
  new_ws->reconnect.threshold = 5;
  new_ws->wait_ms = 100;

  new_ws->ehandle = custom_cws_new(new_ws);
  new_ws->mhandle = curl_multi_init();

  orka_config_init(&new_ws->config, NULL, NULL);

  new_ws->num_notbusy = MAX_THREADS;

  memcpy(&new_ws->cbs, cbs, sizeof(struct ws_callbacks));
  if (!new_ws->cbs.on_startup) 
    new_ws->cbs.on_startup = &noop_on_startup;
  if (!new_ws->cbs.on_iter_start) 
    new_ws->cbs.on_iter_start = &noop_on_iter;
  if (!new_ws->cbs.on_iter_end) 
    new_ws->cbs.on_iter_end = &noop_on_iter;
  if (!new_ws->cbs.on_text_event) 
    new_ws->cbs.on_text_event = &noop_on_text_event;
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
  if (pthread_cond_init(&new_ws->cond, NULL))
    ERR("Couldn't initialize pthread cond");

  return new_ws;
}

struct websockets*
ws_config_init(
  const char base_url[], 
  struct ws_callbacks *cbs,
  const char tag[], 
  const char config_file[]) 
{
  struct websockets *new_ws = ws_init(base_url, cbs);
  orka_config_init(&new_ws->config, tag, config_file);
  return new_ws;
}

void
ws_cleanup(struct websockets *ws)
{
  if (ws->event_pool)
    free(ws->event_pool);
  free(ws->base_url);
  curl_multi_cleanup(ws->mhandle);
  cws_free(ws->ehandle);
  orka_config_cleanup(&ws->config);
  pthread_mutex_destroy(&ws->lock);
  pthread_cond_destroy(&ws->cond);
  free(ws);
}

static void
event_loop(struct websockets *ws)
{
  curl_multi_add_handle(ws->mhandle, ws->ehandle);

  if ( !(*ws->cbs.on_startup)(ws->cbs.data) ) {
    ws_set_status(ws, WS_DISCONNECTED);
    return; /* EARLY RETURN */
  }

  // kickstart a connection then enter loop
  CURLMcode mcode;
  int is_running = 0;
  mcode = curl_multi_perform(ws->mhandle, &is_running);
  ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

  do {
    int numfds;

    pthread_mutex_lock(&ws->lock);
    ws->now_tstamp = orka_timestamp_ms(); //update our concept of now
    pthread_mutex_unlock(&ws->lock);

    // @todo branchless alternative ?
    if (ws_get_status(ws) == WS_CONNECTED) { // run if connection established
      (*ws->cbs.on_iter_start)(ws->cbs.data);
    }

    mcode = curl_multi_perform(ws->mhandle, &is_running);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

    // wait for activity or timeout
    mcode = curl_multi_wait(ws->mhandle, NULL, 0, ws->wait_ms, &numfds);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

    // @todo branchless alternative ?
    if (ws_get_status(ws) == WS_CONNECTED) { // run if connection established
      (*ws->cbs.on_iter_end)(ws->cbs.data);
    }
  } while(is_running);

  curl_multi_remove_handle(ws->mhandle, ws->ehandle);
}

void
ws_close(
  struct websockets *ws, 
  enum ws_close_reason wscode, 
  const char reason[], 
  size_t len)
{
  pthread_mutex_lock(&ws->lock);
  //@todo add pthread_join() here
  cws_close(ws->ehandle, (enum cws_close_reason)wscode, reason, len);
  pthread_mutex_unlock(&ws->lock);
}

void
ws_send_text(struct websockets *ws, char text[])
{
  pthread_mutex_lock(&ws->lock);
  (*ws->config.http_dump_cb)(
    false, 
    0, "SEND", 
    &ws->config, 
    ws->base_url, 
    text);

  bool ret = cws_send_text(ws->ehandle, text);
  if (false == ret) PRINT("Couldn't send websockets payload");
  pthread_mutex_unlock(&ws->lock);
}

uint64_t
ws_timestamp(struct websockets *ws) 
{
  pthread_mutex_lock(&ws->lock);
  uint64_t now_tstamp = ws->now_tstamp;
  pthread_mutex_unlock(&ws->lock);
  return now_tstamp;
}

enum ws_status
ws_get_status(struct websockets *ws) 
{
  pthread_mutex_lock(&ws->lock);
  enum ws_status status = ws->status;
  pthread_mutex_unlock(&ws->lock);
  return status;
}

void
ws_set_status(struct websockets *ws, enum ws_status status) 
{
  pthread_mutex_lock(&ws->lock);
  if (status == WS_CONNECTED) {
    ws->reconnect.attempt = 0;
  }
  ws->status = status;
  pthread_mutex_unlock(&ws->lock);
}

void
ws_set_refresh_rate(struct websockets *ws, uint64_t wait_ms) 
{
  pthread_mutex_lock(&ws->lock);
  ws->wait_ms = wait_ms;
  pthread_mutex_unlock(&ws->lock);
}

void
ws_set_max_reconnect(struct websockets *ws, int max_attempts) 
{
  pthread_mutex_lock(&ws->lock);
  ws->reconnect.threshold = max_attempts;
  pthread_mutex_unlock(&ws->lock);
}

void
ws_set_event(
  struct websockets *ws, 
  int event_code, 
  void (*user_cb)(void *data, void *event_data))
{
  ASSERT_S(WS_DISCONNECTED == ws_get_status(ws), "Can't set event on a running client");

  ++ws->num_events;
  ws->event_pool = realloc(ws->event_pool, ws->num_events * sizeof(struct event_cb));

  memset(&ws->event_pool[ws->num_events-1], 0, sizeof(struct event_cb));
  ws->event_pool[ws->num_events-1].code = event_code;
  ws->event_pool[ws->num_events-1].cb = user_cb;
}

/* set data that will be accessable on current loop iteration with 
 *  any event_pool callback.  It will be freed before the next 
 *  iteration by calling user defined cleanup() method */
void
ws_set_curr_iter_data(
  struct websockets *ws, 
  void *curr_iter_data, 
  void (*curr_iter_cleanup)(void *curr_iter_data))
{
  ws->curr_iter_data = curr_iter_data;
  ws->curr_iter_cleanup = curr_iter_cleanup;
}

static enum ws_status
attempt_reconnect(struct websockets *ws)
{
  switch (ws->status) {
  default:
      if (ws->reconnect.attempt < ws->reconnect.threshold)
        break;

      PRINT("Failed all reconnect attempts (%d)", ws->reconnect.attempt);
      ws->status = WS_DISCONNECTED;
  /* fall through */
  case WS_DISCONNECTED:
      return ws->status; /* WS_DISCONNECTED */
  }

  /* force reset */
  cws_free(ws->ehandle);
  ws->ehandle = custom_cws_new(ws);

  ++ws->reconnect.attempt;

  return ws->status; /* WS_CONNECTED || WS_RESUME || WS_FRESH */
}

/* connects to the websockets server */
void
ws_run(struct websockets *ws)
{
  ASSERT_S(WS_DISCONNECTED == ws_get_status(ws), 
      "Failed attempt to run websockets recursively");

  while (1) {
    event_loop(ws);
    if (WS_DISCONNECTED == attempt_reconnect(ws))
      break; /* EXIT LOOP */
  }
}

struct sized_buffer
ws_config_get_field(struct websockets *ws, char *json_field) {
  return orka_config_get_field(&ws->config, json_field);
}
