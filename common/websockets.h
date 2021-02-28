#include "curl-websocket.h"
#include <inttypes.h>

enum ws_status {
  WS_DISCONNECTED,  //disconnected from ws
  WS_RESUME,        //attempt to resume ws session
  WS_FRESH,         //attempt a fresh ws session (session timed out)
  WS_CONNECTED      //connected to ws
};

typedef void (ws_callbacks)(
  struct websockets_s *ws, 
  const char *text, 
  size_t len);

struct websockets_s {
  enum ws_status status;
  CURLM *mhandle;
  CURL *ehandle;

  uint64_t now_tstamp; //timestamp updated every loop iteration

  int reconnect_attempts; //hard limit 5 reconnection attempts @todo make configurable
  char *base_url;

  ws_callbacks *on_connect_cb;
  ws_callbacks *on_text_cb;
  ws_callbacks *on_binary_cb;
  ws_callbacks *on_ping_cb;
  ws_callbacks *on_pong_cb;
  ws_callbacks *on_close_cb;
};

void ws_init(struct websockets_s *ws, char base_url[]);
void ws_cleanup(struct websockets_s *ws);
void ws_run(struct websockets_s *ws);
