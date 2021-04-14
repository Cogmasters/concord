#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* FORWARD DECLARATIONS */
struct websockets;

enum ws_status {
  WS_DISCONNECTED = 0,  //disconnected from ws
  WS_DISCONNECTING,     //disconnecting from ws
  WS_CONNECTED,         //connected to ws
  WS_RESUME,            //attempt to resume ws session
  WS_FRESH,             //attempt a fresh ws session
  WS_SHUTDOWN           //shutdown current ws session (don't reconnect)
};

/* see https://tools.ietf.org/html/rfc6455#section-7.4.1 */
enum ws_close_reason {
    WS_CLOSE_REASON_NORMAL               = 1000,
    WS_CLOSE_REASON_GOING_AWAY           = 1001,
    WS_CLOSE_REASON_PROTOCOL_ERROR       = 1002,
    WS_CLOSE_REASON_UNEXPECTED_DATA      = 1003,
    WS_CLOSE_REASON_NO_REASON            = 1005,
    WS_CLOSE_REASON_ABRUPTLY             = 1006,
    WS_CLOSE_REASON_INCONSISTENT_DATA    = 1007,
    WS_CLOSE_REASON_POLICY_VIOLATION     = 1008,
    WS_CLOSE_REASON_TOO_BIG              = 1009,
    WS_CLOSE_REASON_MISSING_EXTENSION    = 1010,
    WS_CLOSE_REASON_SERVER_ERROR         = 1011,
    WS_CLOSE_REASON_IANA_REGISTRY_START  = 3000,
    WS_CLOSE_REASON_IANA_REGISTRY_END    = 3999,
    WS_CLOSE_REASON_PRIVATE_START        = 4000,
    WS_CLOSE_REASON_PRIVATE_END          = 4999
};

struct ws_callbacks {
  void *data; // user arbitrary data received by callbacks

  void (*on_connect)(void *data, const char *protocols);
  void (*on_text)(void *data, const char *text, size_t len);
  void (*on_binary)(void *data, const void *mem, size_t len);
  void (*on_ping)(void *data, const char *reason, size_t len);
  void (*on_pong)(void *data, const char *reason, size_t len);
  void (*on_close)(void *data, enum ws_close_reason wscode, const char *reason, size_t len);
};

struct websockets* ws_init(const char base_url[], struct ws_callbacks *cbs);
struct websockets* ws_config_init(
  const char base_url[], 
  struct ws_callbacks *cbs,
  const char tag[], 
  const char config_file[]);
void ws_cleanup(struct websockets *ws);
void ws_close(
  struct websockets *ws,
  enum ws_close_reason wscode, 
  const char reason[], 
  size_t len);
void ws_send_text(struct websockets *ws, char text[], size_t len);
void ws_perform(struct websockets *ws, _Bool *is_running);
void ws_wait_activity(struct websockets *ws, uint64_t wait_ms);

void ws_redirect(struct websockets *ws, char base_url[]);
void ws_reconnect(struct websockets *ws);
uint64_t ws_timestamp(struct websockets *ws);
enum ws_status ws_get_status(struct websockets *ws);
void ws_set_status(struct websockets *ws, enum ws_status status);
void ws_set_max_reconnect(struct websockets *ws, int max_attempts);
struct sized_buffer ws_config_get_field(struct websockets *ws, char *json_field);
char* ws_close_opcode_print(enum ws_close_reason opcode);
char* ws_config_get_fname(struct websockets *ws);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WEBSOCKETS_H
