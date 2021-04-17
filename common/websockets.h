#ifndef WEBSOCKETS_H
#define WEBSOCKETS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "logconf.h" /* struct logconf */

/* FORWARD DECLARATIONS */
struct websockets;

/**
 * The WebSockets client possible status 
 * @see ws_get_status()
 * @see _ws_set_status()
 */
enum ws_status {
  WS_DISCONNECTED = 0, // client disconnected from ws
  WS_CONNECTED,        // client connected to ws
  WS_DISCONNECTING,    // client in the process of disconnecting to ws
  WS_CONNECTING,       // client in the process of connecting from ws
};

/**
 * Action that will trigger a reaction response from the client
 * @see ws_set_action()
 * @see ws_get_action()
 */
enum ws_action {
  WS_ACTION_DISCONNECT = 1, // trigger disconnect response
};

/* @see https://tools.ietf.org/html/rfc6455#section-7.4.1 */
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
  /**
   * called upon connection, websocket_protocols contains what
   * server reported as 'Sec-WebSocket-Protocol:'.
   *
   * @note It is not validated if matches the proposed protocols.
   */
  void (*on_connect)(void *data, const char *protocols);
  /**
   * reports UTF-8 text messages.
   *
   * @note it's guaranteed to be NULL (\0) terminated, but the UTF-8 is
   * not validated. If it's invalid, consider closing the connection
   * with #WS_CLOSE_REASON_INCONSISTENT_DATA.
   */
  void (*on_text)(void *data, const char *text, size_t len);
  /**
   * reports binary data.
   */
  void (*on_binary)(void *data, const void *mem, size_t len);
  /**
   * reports PING.
   *
   * @note if provided you should reply with ws_pong(). If not
   * provided, pong is sent with the same message payload.
   */
  void (*on_ping)(void *data, const char *reason, size_t len);
  /**
   * reports PONG.
   */
  void (*on_pong)(void *data, const char *reason, size_t len);
  /**
   * reports server closed the connection with the given reason.
   *
   * Clients should not transmit any more data after the server is
   * closed
   * @see ws_cleanup() if you don't want reconnect
   * @see ws_reset() if you wish to reconnect
   */
  void (*on_close)(void *data, enum ws_close_reason wscode, const char *reason, size_t len);
  /**
   * user arbitrary data to be passed around callbacks
   */
  void *data;
};

/**
 * Create a new (CURL-based) WebSockets handle
 *
 * @param cbs set of functions to call back when server report events.
 * @param config optional pointer to a pre-initialized logconf 
 *        @see logconf.h
 * @return newly created WebSockets handle, free with ws_cleanup
 */
struct websockets* ws_init(struct ws_callbacks *cbs, struct logconf *config);

/**
 * Free a WebSockets handle created with ws_init()
 */
void ws_cleanup(struct websockets *ws);

/**
 * Set the URL for the WebSockets handle to connect
 * 
 * @param ws the handle to connect to the URL
 * @param url the URL to connect, such as ws://echo.websockets.org
 * @param ws_protocols #NULL or something like "chat", "superchat",...
 */
void ws_set_url(struct websockets *ws, const char base_url[], const char ws_protocols[]);

/**
 * Reset a WebSockets handle for reuse
 *
 * @param ws the handle to be reset
 */
void ws_reset(struct websockets *ws);

/**
 * Send a CLOSE (opcode 0x8) frame with @a reason as payload.
 *
 * @param ws the WebSockets handle created with ws_init()
 * @param wscode the reason why it was closed, see the well-known numbers.
 * @param reason #NULL or some UTF-8 string null ('\0') terminated.
 * @param len the length of @a reason in bytes. If
 *        #SIZE_MAX, uses strlen() on @a reason if it's not
 *        #NULL.
 * @return #true if sent, #false on errors.
 */
bool ws_close(
  struct websockets *ws,
  enum ws_close_reason wscode, 
  const char reason[], 
  size_t len);

/**
 * Send a text message of given size.
 *
 * Text messages do not need to include the null terminator (\0), they
 * will be read up to @a len.
 *
 * @param ws the WebSockets handle created with ws_init()
 * @param text the pointer to memory (linear) to send.
 * @param len the length in bytes of @a text.
 *
 * @return #true if sent, #false on errors.
 */
bool ws_send_text(struct websockets *ws, char text[], size_t len);

/**
 * Reads/Write available data from WebSockets
 *
 * Helper over curl_multi_perform()
 * @see https://curl.se/libcurl/c/curl_multi_perform.html
 *
 * @param ws the WebSockets handle created with ws_init()
 * @param is_running receives #true if the client is running and #false otherwise
 */
void ws_perform(struct websockets *ws, _Bool *is_running);

/**
 * Block until activity is detected on internal file descriptors, or
 * until wait_ms has passed
 *
 * Helper over curl_multi_wait()
 * @see https://curl.se/libcurl/c/curl_multi_wait.html
 *
 * @param ws the WebSockets handle created with ws_init()
 * @param wait_ms limit amount in milliseconds to wait for until activity
 */
void ws_wait_activity(struct websockets *ws, uint64_t wait_ms);

/**
 * The WebSockets handle concept of "now", the timestamp is updated
 * at every ws_perform() call
 *
 * @param ws the WebSockets handle created with ws_init()
 * @return the timestamp in milliseconds from when ws_perform() was last called
 */
uint64_t ws_timestamp(struct websockets *ws);

/**
 * Returns the WebSockets handle connection status
 *
 * @param ws the WebSockets handle created with ws_init()
 * @return a ws_status opcode
 */
enum ws_status ws_get_status(struct websockets *ws);

/**
 * Returns the WebSockets handle triggered action
 *
 * @note This can only be checked before status being changed to WS_DISCONNECTED
 *
 * @param ws the WebSockets handle created with ws_init()
 * @return a enum ws_action opcode
 */
enum ws_action ws_get_action(struct websockets *ws);

/**
 * Trigger a action to take place for the WebSockets handle
 * Example: #WS_ACTION_DISCONNECTED will force a connection shutdown
 *
 * @param ws the WebSockets handle created with ws_init()
 * @param action the action to trigger a response
 */
void ws_set_action(struct websockets *ws, enum ws_action action);

/**
 * Returns a enum ws_close_reason opcode in a string format
 *
 * @param opcode the opcode to be converted to string
 * @return a read-only string literal of the opcode
 */
char* ws_close_opcode_print(enum ws_close_reason opcode);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // WEBSOCKETS_H
