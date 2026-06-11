/* Self-test for the mock ws_* transport: a bare ws_callbacks consumer
 * (no gateway) proving deliver/capture/close scripting works.  Also
 * proves at link time that the mock satisfies every ws_* symbol
 * without pulling core/websockets.o from libdiscord.a. */

#include <stdint.h>

#include "mock-websockets.h"
#include "test-utils.h"

static struct {
    int connects;
    int texts;
    char last_text[256];
    int closes;
    enum ws_close_reason last_close_code;
    char last_close_reason[256];
} rec;

static void
on_connect(void *data, struct websockets *ws)
{
    (void)data;
    (void)ws;
    ++rec.connects;
}

static void
on_text(void *data, struct websockets *ws, const char *text, size_t len)
{
    (void)data;
    (void)ws;
    ++rec.texts;
    snprintf(rec.last_text, sizeof(rec.last_text), "%.*s", (int)len, text);
}

static void
on_close(void *data,
         struct websockets *ws,
         enum ws_close_reason wscode,
         const char *reason,
         size_t len)
{
    (void)data;
    (void)ws;
    ++rec.closes;
    rec.last_close_code = wscode;
    snprintf(rec.last_close_reason, sizeof(rec.last_close_reason), "%.*s",
             (int)len, reason);
}

static struct websockets *
make_ws(void)
{
    struct ws_callbacks cbs = { .on_connect = on_connect,
                                .on_text = on_text,
                                .on_close = on_close };

    memset(&rec, 0, sizeof(rec));
    return ws_init(&cbs, NULL, NULL, NULL);
}

TEST
connect_fires_callback(void)
{
    struct websockets *ws = make_ws();

    ASSERT_NEQ(NULL, ws);
    ASSERT_EQ(WS_DISCONNECTED, ws_get_status(ws));
    ASSERT_NEQ(NULL, ws_start(ws));
    ASSERT_EQ(WS_CONNECTING, ws_get_status(ws));
    ASSERT_EQ(0, rec.connects);
    mockws_connect(ws);
    ASSERT_EQ(WS_CONNECTED, ws_get_status(ws));
    ASSERT_EQ(1, rec.connects);

    ws_cleanup(ws);
    PASS();
}

TEST
send_gated_and_captured_fifo(void)
{
    struct websockets *ws = make_ws();
    char *frame;

    ASSERT_EQ(0, ws_send_text(ws, "early", 5)); /* DISCONNECTED */
    ws_start(ws);
    ASSERT_EQ(0, ws_send_text(ws, "early", 5)); /* CONNECTING */
    ASSERT_EQ((size_t)0, mockws_sent_count(ws));

    mockws_connect(ws);
    ASSERT_EQ(1, ws_send_text(ws, "first", 5));
    ASSERT_EQ(1, ws_send_binary(ws, "second", 6));
    ASSERT_EQ((size_t)2, mockws_sent_count(ws));

    frame = mockws_pop_sent(ws);
    ASSERT_STR_EQ("first", frame);
    free(frame);
    frame = mockws_pop_sent(ws);
    ASSERT_STR_EQ("second", frame);
    free(frame);
    ASSERT_EQ(NULL, mockws_pop_sent(ws));

    ws_cleanup(ws);
    PASS();
}

TEST
deliver_text_exact_bytes(void)
{
    struct websockets *ws = make_ws();
    const char payload[] = "{\"op\":10}";

    ws_start(ws);
    mockws_connect(ws);
    mockws_deliver_text(ws, payload, sizeof(payload) - 1);
    ASSERT_EQ(1, rec.texts);
    ASSERT_STR_EQ(payload, rec.last_text);

    ws_cleanup(ws);
    PASS();
}

TEST
close_request_then_finish(void)
{
    struct websockets *ws = make_ws();
    enum ws_close_reason code = 0;

    ws_start(ws);
    mockws_connect(ws);

    ASSERT_EQ(0, mockws_close_requested(ws, &code));
    ws_close(ws, WS_CLOSE_REASON_NORMAL, "bye", 3);
    /* request only recorded: status unchanged, no callback yet */
    ASSERT_EQ(WS_CONNECTED, ws_get_status(ws));
    ASSERT_EQ(0, rec.closes);
    ASSERT_EQ(1, mockws_close_requested(ws, &code));
    ASSERT_EQ(WS_CLOSE_REASON_NORMAL, code);

    mockws_finish_close(ws);
    ASSERT_EQ(1, rec.closes);
    ASSERT_EQ(WS_CLOSE_REASON_NORMAL, rec.last_close_code);
    ASSERT_STR_EQ("bye", rec.last_close_reason);
    ASSERT_EQ(WS_DISCONNECTED, ws_get_status(ws));

    ws_cleanup(ws);
    PASS();
}

TEST
close_reason_size_max(void)
{
    struct websockets *ws = make_ws();
    enum ws_close_reason code = 0;

    ws_start(ws);
    mockws_connect(ws);
    /* _discord_on_invalid_session passes len = SIZE_MAX, relying on the
     * snprintf "%.*s" negative-precision idiom */
    ws_close(ws, WS_CLOSE_REASON_NORMAL, "whole string", SIZE_MAX);
    ASSERT_EQ(1, mockws_close_requested(ws, &code));
    mockws_finish_close(ws);
    ASSERT_STR_EQ("whole string", rec.last_close_reason);

    ws_cleanup(ws);
    PASS();
}

TEST
server_initiated_close(void)
{
    struct websockets *ws = make_ws();

    ws_start(ws);
    mockws_connect(ws);
    mockws_close(ws, (enum ws_close_reason)4000, "server says bye");
    ASSERT_EQ(1, rec.closes);
    ASSERT_EQ(4000, (int)rec.last_close_code);
    ASSERT_STR_EQ("server says bye", rec.last_close_reason);
    ASSERT_EQ(WS_DISCONNECTED, ws_get_status(ws));

    ws_cleanup(ws);
    PASS();
}

TEST
start_requires_end_between_sessions(void)
{
    struct websockets *ws = make_ws();

    ASSERT_NEQ(NULL, ws_start(ws));
    ASSERT_EQ(NULL, ws_start(ws)); /* already alive */
    mockws_connect(ws);
    mockws_close(ws, WS_CLOSE_REASON_NORMAL, "bye");
    ASSERT_EQ(NULL, ws_start(ws)); /* closed but not ws_end()'d */
    ws_end(ws);
    ASSERT_NEQ(NULL, ws_start(ws)); /* fresh session */

    ws_cleanup(ws);
    PASS();
}

TEST
frames_survive_ws_end(void)
{
    struct websockets *ws = make_ws();
    char *frame;

    ws_start(ws);
    mockws_connect(ws);
    ws_send_text(ws, "kept", 4);
    ws_end(ws);
    ASSERT_EQ((size_t)1, mockws_sent_count(ws));
    frame = mockws_pop_sent(ws);
    ASSERT_STR_EQ("kept", frame);
    free(frame);

    ws_cleanup(ws);
    PASS();
}

SUITE(mockws)
{
    RUN_TEST(connect_fires_callback);
    RUN_TEST(send_gated_and_captured_fifo);
    RUN_TEST(deliver_text_exact_bytes);
    RUN_TEST(close_request_then_finish);
    RUN_TEST(close_reason_size_max);
    RUN_TEST(server_initiated_close);
    RUN_TEST(start_requires_end_between_sessions);
    RUN_TEST(frames_survive_ws_end);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(mockws);
    GREATEST_MAIN_END();
}
