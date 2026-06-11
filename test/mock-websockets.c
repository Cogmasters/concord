/* In-memory test double for the `ws_*` interface (core/websockets.h).
 * Defines every public ws_* symbol so that linking this object before
 * -ldiscord fully substitutes core/websockets.o.  See mock-websockets.h
 * for the semantics contract and the test-side control API. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cog-utils.h"
#include "mock-websockets.h"

struct mockws_frame {
    char *text;
    struct mockws_frame *next;
};

/* the mock's definition of the opaque handle */
struct websockets {
    enum ws_status status;
    struct ws_callbacks cbs;
    char url[512];
    /* captured outbound frames, FIFO */
    struct mockws_frame *sent_head, *sent_tail;
    size_t sent_count;
    /* ws_start() was called without a matching ws_end() */
    int started;
    /* gateway-initiated close request (ws_close) */
    int close_pending;
    enum ws_close_reason close_code;
    char close_reason[128];
    uint64_t now;
};

/* ── ws_* interface ───────────────────────────────────────────────── */

struct websockets *
ws_init(struct ws_callbacks *cbs,
        CURLM *mhandle,
        struct logmod *logmod,
        FILE *fp)
{
    struct websockets *ws = calloc(1, sizeof *ws);

    (void)mhandle;
    (void)logmod;
    (void)fp;
    if (!ws) return NULL;
    if (cbs) ws->cbs = *cbs;
    ws->status = WS_DISCONNECTED;
    return ws;
}

void
ws_cleanup(struct websockets *ws)
{
    if (!ws) return;
    mockws_drain_sent(ws);
    free(ws);
}

void
ws_set_url(struct websockets *ws, const char base_url[])
{
    snprintf(ws->url, sizeof(ws->url), "%s", base_url ? base_url : "");
}

_Bool
ws_send_text(struct websockets *ws, const char text[], size_t len)
{
    struct mockws_frame *frame;

    if (ws->status != WS_CONNECTED) return 0;
    if (!(frame = calloc(1, sizeof *frame))) return 0;
    if (!(frame->text = malloc(len + 1))) return free(frame), 0;
    memcpy(frame->text, text, len);
    frame->text[len] = '\0';

    if (ws->sent_tail)
        ws->sent_tail->next = frame;
    else
        ws->sent_head = frame;
    ws->sent_tail = frame;
    ++ws->sent_count;
    return 1;
}

_Bool
ws_send_binary(struct websockets *ws, const char msg[], size_t msglen)
{
    return ws_send_text(ws, msg, msglen);
}

_Bool
ws_ping(struct websockets *ws, const char reason[], size_t len)
{
    (void)ws;
    (void)reason;
    (void)len;
    return 1;
}

_Bool
ws_pong(struct websockets *ws, const char reason[], size_t len)
{
    (void)ws;
    (void)reason;
    (void)len;
    return 1;
}

CURL *
ws_start(struct websockets *ws)
{
    if (ws->status != WS_DISCONNECTED || ws->started) {
        fprintf(stderr,
                "mockws: ws_start() while alive or without ws_end()\n");
        return NULL;
    }
    ws->started = 1;
    ws->close_pending = 0;
    ws->status = WS_CONNECTING;
    /* gateway only dereferences this under CCORD_DEBUG_WEBSOCKETS */
    return (CURL *)ws;
}

void
ws_end(struct websockets *ws)
{
    ws->started = 0;
    ws->close_pending = 0;
    ws->status = WS_DISCONNECTED;
    /* captured frames are kept for post-teardown assertions; freed at
     * ws_cleanup() or mockws_drain_sent() */
}

_Bool
ws_easy_run(struct websockets *ws, uint64_t wait_ms, uint64_t *tstamp)
{
    (void)ws;
    (void)wait_ms;
    (void)tstamp;
    return 0; /* unused by the gateway */
}

_Bool
ws_multi_socket_run(struct websockets *ws, uint64_t *tstamp)
{
    *tstamp = ws->now = cog_timestamp_ms();
    return ws->status == WS_CONNECTING || ws->status == WS_CONNECTED;
}

enum ws_status
ws_get_status(struct websockets *ws)
{
    return ws->status;
}

const char *
ws_close_opcode_print(enum ws_close_reason opcode)
{
    switch (opcode) {
    case WS_CLOSE_REASON_NORMAL:
        return "WS_CLOSE_REASON_NORMAL";
    case WS_CLOSE_REASON_GOING_AWAY:
        return "WS_CLOSE_REASON_GOING_AWAY";
    case WS_CLOSE_REASON_PROTOCOL_ERROR:
        return "WS_CLOSE_REASON_PROTOCOL_ERROR";
    case WS_CLOSE_REASON_ABRUPTLY:
        return "WS_CLOSE_REASON_ABRUPTLY";
    default:
        return "WS_CLOSE_REASON_UNKNOWN";
    }
}

uint64_t
ws_timestamp(struct websockets *ws)
{
    return ws->now;
}

uint64_t
ws_timestamp_update(struct websockets *ws)
{
    return ws->now = cog_timestamp_ms();
}

void
ws_close(struct websockets *ws,
         const enum ws_close_reason code,
         const char reason[],
         const size_t len)
{
    if (ws->status == WS_DISCONNECTED) return;
    ws->close_pending = 1;
    ws->close_code = code;
    /* the real transport snprintf's with "%.*s": (int)SIZE_MAX == -1 is
     * a negative precision meaning "whole string" — callers rely on it
     * (e.g. _discord_on_invalid_session passes SIZE_MAX) */
    snprintf(ws->close_reason, sizeof(ws->close_reason), "%.*s", (int)len,
             reason ? reason : "");
    /* status unchanged: the real ws_close only records the request */
}

void
ws_add_header(struct websockets *ws, const char field[], const char value[])
{
    (void)ws;
    (void)field;
    (void)value;
}

/* ── test-side control API ────────────────────────────────────────── */

void
mockws_connect(struct websockets *ws)
{
    if (ws->status != WS_CONNECTING) {
        fprintf(stderr, "mockws: mockws_connect() before ws_start()\n");
        return;
    }
    ws->status = WS_CONNECTED;
    if (ws->cbs.on_connect) ws->cbs.on_connect(ws->cbs.data, ws);
}

void
mockws_deliver_text(struct websockets *ws, const char text[], size_t len)
{
    if (ws->status != WS_CONNECTED) {
        fprintf(stderr, "mockws: deliver_text() while not connected\n");
        return;
    }
    if (ws->cbs.on_text) ws->cbs.on_text(ws->cbs.data, ws, text, len);
}

void
mockws_close(struct websockets *ws,
             enum ws_close_reason code,
             const char reason[])
{
    ws->status = WS_DISCONNECTING;
    if (ws->cbs.on_close)
        ws->cbs.on_close(ws->cbs.data, ws, code, reason,
                         reason ? strlen(reason) : 0);
    ws->status = WS_DISCONNECTED;
}

void
mockws_finish_close(struct websockets *ws)
{
    if (!ws->close_pending) {
        fprintf(stderr, "mockws: finish_close() without pending close\n");
        return;
    }
    ws->close_pending = 0;
    ws->status = WS_DISCONNECTING;
    if (ws->cbs.on_close)
        ws->cbs.on_close(ws->cbs.data, ws, ws->close_code, ws->close_reason,
                         strlen(ws->close_reason));
    ws->status = WS_DISCONNECTED;
}

int
mockws_close_requested(struct websockets *ws, enum ws_close_reason *code)
{
    if (ws->close_pending && code) *code = ws->close_code;
    return ws->close_pending;
}

char *
mockws_pop_sent(struct websockets *ws)
{
    struct mockws_frame *frame = ws->sent_head;
    char *text;

    if (!frame) return NULL;
    ws->sent_head = frame->next;
    if (!ws->sent_head) ws->sent_tail = NULL;
    --ws->sent_count;
    text = frame->text;
    free(frame);
    return text;
}

size_t
mockws_sent_count(struct websockets *ws)
{
    return ws->sent_count;
}

void
mockws_drain_sent(struct websockets *ws)
{
    char *text;

    while ((text = mockws_pop_sent(ws)))
        free(text);
}
