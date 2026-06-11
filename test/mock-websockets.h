#ifndef MOCK_WEBSOCKETS_H
#define MOCK_WEBSOCKETS_H

#include <stddef.h>

#include "websockets.h"

/* Test-side control API for the mock `ws_*` transport
 * (mock-websockets.c).  Gateway test binaries link mock-websockets.o
 * BEFORE -ldiscord so every ws_* symbol resolves to the mock and the
 * real core/websockets.o archive member is never pulled in.
 *
 * The mock mirrors the real transport's observable semantics:
 *  - ws_send_* succeeds only while WS_CONNECTED, capturing frames into
 *    a FIFO inspectable via mockws_pop_sent()/mockws_sent_count().
 *  - ws_close() only RECORDS a close request (the real transport defers
 *    the CLOSE frame to the next perform and fires on_close only when
 *    the peer echoes); complete it with mockws_finish_close(), or tear
 *    down via ws_end() with the request still pending — both happen in
 *    production.
 *  - ws_start() fails if the handle is alive or was not ws_end()'d
 *    since the previous start, like the real ehandle guard. */

/* CONNECTING -> CONNECTED, then fires on_connect */
void mockws_connect(struct websockets *ws);

/* deliver an inbound text frame: fires on_text synchronously (the
 * gateway processes the whole payload, including user callbacks,
 * before this returns) */
void mockws_deliver_text(struct websockets *ws, const char text[], size_t len);

/* server/transport-initiated close: fires on_close with CODE/REASON,
 * leaves the handle WS_DISCONNECTED (ws_end() still required before
 * the next ws_start, as with the real transport) */
void mockws_close(struct websockets *ws,
                  enum ws_close_reason code,
                  const char reason[]);

/* complete a gateway-requested ws_close(): fires on_close with the
 * recorded code/reason (the "peer echoed our CLOSE" path) */
void mockws_finish_close(struct websockets *ws);

/* nonzero if a gateway-initiated ws_close() is pending; copies its
 * code into *CODE when non-NULL */
int mockws_close_requested(struct websockets *ws, enum ws_close_reason *code);

/* pop the oldest captured outbound frame as a malloc'd NUL-terminated
 * string (caller frees), or NULL if none */
char *mockws_pop_sent(struct websockets *ws);

/* number of captured outbound frames not yet popped */
size_t mockws_sent_count(struct websockets *ws);

/* discard all captured outbound frames */
void mockws_drain_sent(struct websockets *ws);

#endif /* MOCK_WEBSOCKETS_H */
