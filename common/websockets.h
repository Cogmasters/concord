#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* FORWARD DECLARATIONS */
struct websockets;

enum ws_status {
  WS_DISCONNECTED,  //disconnected from ws
  WS_RESUME,        //attempt to resume ws session
  WS_FRESH,         //attempt a fresh ws session (session timed out)
  WS_CONNECTED      //connected to ws
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
void ws_send_text(struct websockets *ws, char text[]);
void ws_run(struct websockets *ws);
void ws_shutdown(struct websockets *ws);
void ws_redirect(struct websockets *ws, char base_url[]);
void ws_reconnect(struct websockets *ws);
uint64_t ws_timestamp(struct websockets *ws);
enum ws_status ws_get_status(struct websockets *ws);
void ws_set_status(struct websockets *ws, enum ws_status status);
void ws_set_refresh_rate(struct websockets *ws, uint64_t wait_ms);
void ws_set_max_reconnect(struct websockets *ws, int max_attempts);
void ws_set_event(
  struct websockets *ws, 
  int event_code, 
  void (*user_cb)(void *data, void *curr_iter_data));
/* this should be used at on_text_event callbacks, it is the data that
 *  can be accessed within the on_event callbacks parameter */
void ws_set_curr_iter_data(
  struct websockets *ws, 
  void *curr_iter_data, 
  void (*curr_iter_cleanup)(void *curr_iter_data));
struct sized_buffer ws_config_get_field(struct websockets *ws, char *json_field);
char* ws_close_opcode_print(enum ws_close_reason opcode);
char* ws_config_get_fname(struct websockets *ws);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WEBSOCKETS_H
