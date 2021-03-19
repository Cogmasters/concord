#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <inttypes.h>
#include "curl-websocket.h"
#include "orka-config.h"

enum ws_status {
  WS_DISCONNECTED,  //disconnected from ws
  WS_RESUME,        //attempt to resume ws session
  WS_FRESH,         //attempt a fresh ws session (session timed out)
  WS_CONNECTED      //connected to ws
};

struct event_cbs {
  int code; // code that should trigger the callback
  void (*cb)(void *data, void *curr_iter_data); // see ws_set_curr_iter_data()
};

struct ws_callbacks {
  void *data; // user arbitrary data to be passed to callbacks

  struct event_cbs *on_event;
  size_t num_events;

  int (*on_startup)(void *data); // exec before loop starts (return 1 for proceed, 0 for abort)
  void (*on_iter_start)(void *data); // execs at end of every loop iteration
  void (*on_iter_end)(void *data); // execs at end of every loop iteration
  /* on_text_event should return a valid event code by parsing the text,
   *  if code is invalid then on_text will be executed instead */
  int (*on_text_event)(void *data, const char *text, size_t len);

  /* common websockets callbacks */
  void (*on_connect)(void *data, const char *protocols);
  void (*on_text)(void *data, const char *text, size_t len);
  void (*on_binary)(void *data, const void *mem, size_t len);
  void (*on_ping)(void *data, const char *reason, size_t len);
  void (*on_pong)(void *data, const char *reason, size_t len);
  void (*on_close)(void *data, enum cws_close_reason cwscode, const char *reason, size_t len);
};

struct thread_pool {
  pthread_t tid;
  bool is_busy;

  /* the following are set by ws_set_curr_iter_data() */
  void *data; //user arbitrary data that lasts for this thread cycle
  void (*cleanup)(void *data); //data cleanup method
};

#define MAX_THREADS 10 //@todo temp size just for prototyping
struct websockets_s {
  struct orka_config config;
  enum ws_status status;
  CURLM *mhandle;
  CURL *ehandle;
  uint64_t wait_ms; // how long to wait for sockets activity

  uint64_t now_tstamp; //timestamp updated every loop iteration

  struct { /* RECONNECT STRUCT */
    int threshold; // max reconnections attempts before quitting
    int attempt; // current count of reconnection attempt
  } reconnect;

  char *base_url;

  struct ws_callbacks cbs;

  /* will last only for this current loop iteration, the data is 
   *   passed as a on_event callback parameter, and free'd from 
   *   memory with the given cleanup function (if any is given) */
  void *curr_iter_data;
  void (*curr_iter_cleanup)(void *curr_iter_data);

  struct thread_pool threads[MAX_THREADS];
  int num_notbusy; // num of available threads

  pthread_mutex_t lock;
  pthread_cond_t cond;
};

void ws_init(struct websockets_s *ws, const char base_url[], struct ws_callbacks *cbs);
void ws_config_init(
  struct websockets_s *ws, 
  const char base_url[], 
  struct ws_callbacks *cbs,
  const char tag[], 
  const char config_file[]);
void ws_cleanup(struct websockets_s *ws);
void ws_close(
  struct websockets_s *ws,
  enum cws_close_reason cwscode, 
  const char reason[], 
  size_t len);
void ws_send_text(struct websockets_s *ws, char text[]);
void ws_run(struct websockets_s *ws);
uint64_t ws_timestamp(struct websockets_s *ws);
enum ws_status ws_get_status(struct websockets_s *ws);
void ws_set_status(struct websockets_s *ws, enum ws_status status);
void ws_set_refresh_rate(struct websockets_s *ws, uint64_t wait_ms);
void ws_set_max_reconnect(struct websockets_s *ws, int max_attempts);
void ws_set_event(
  struct websockets_s *ws, 
  int event_code, 
  void (*user_cb)(void *data, void *curr_iter_data));
/* this should be used at on_text_event callbacks, it is the data that
 *  can be accessed within the on_event callbacks parameter */
void ws_set_curr_iter_data(
  struct websockets_s *ws, 
  void *curr_iter_data, 
  void (*curr_iter_cleanup)(void *curr_iter_data));

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WEBSOCKETS_H
