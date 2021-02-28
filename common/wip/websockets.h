#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <curl/curl.h>
#include "orka-debug.h"

enum ws_status {
  WS_DISCONNECTED,  //disconnected from ws
  WS_RESUME,        //attempt to resume ws session
  WS_FRESH,         //attempt a fresh ws session (session timed out)
  WS_CONNECTED      //connected to ws
};

struct websockets_s {
  enum ws_status status;
  CURLM *mhandle;
  CURL *ehandle;

  uint64_t now_tstamp; //timestamp updated every loop iteration

  struct { /* RECONNECT STRUCT */
    int threshold; // max reconnections attempts before quitting
    int count; // current count of reconnection attempt
  } reconnect;

  char *base_url;

  struct { /* CALLBACKS STRUCT */
    void *data; /* user arbitrary data to be passed to callbacks */

    void (*on_connect)(void *data, const char *protocols);
    void (*on_text)(void *data, const char *reason, size_t len);
    void (*on_binary)(void *data, const void *mem, size_t len);
    void (*on_ping)(void *data, const char *reason, size_t len);
    void (*on_pong)(void *data, const char *reason, size_t len);
    void (*on_close)(void *data, enum cws_close_reason cwscode, const char *reason, size_t len);

    void (*on_idle)(void *data); // execs at end of every loop iteration
    int (*on_start)(void *data); // execs once, before attempting connection return 1 for proceed, 0 for abort
  } cbs;
};

void ws_init(struct websockets_s *ws, char base_url[]);
void ws_cleanup(struct websockets_s *ws);
void ws_run(struct websockets_s *ws);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WEBSOCKETS_H
