/* Disconnect recovery against scripted closes: RESUME vs re-IDENTIFY
 * selection, opcode 7/9 handling, the server-close policy table, and
 * sequence integrity across a resume. */

#include "gateway-harness.h"

static struct {
    int messages;
    u64snowflake last_id;
} rec;

static void
on_message(struct discord *client, const struct discord_message *event)
{
    (void)client;
    ++rec.messages;
    rec.last_id = event->id;
}

/* boot → connect → HELLO/READY handshake (frames drained) */
static int
establish(struct test_gateway *tg)
{
    if (0 != tg_boot(tg)) return -1;
    if (0 != tg_connect(tg)) return -1;
    return tg_handshake(tg);
}

/* reconnect after discord_gateway_end() and deliver HELLO; returns the
 * first frame the gateway answers with (malloc'd), or NULL */
static char *
reconnect_hello(struct test_gateway *tg)
{
    if (0 != tg_connect(tg)) return NULL;
    if (0 != tg_deliver_fixture(tg, "gateway-hello.json")) return NULL;
    return mockws_pop_sent(tg->ws);
}

TEST
sequence_advances_on_dispatch(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, establish(&tg));
    ASSERT_EQ(1, tg.gw->payload.seq); /* READY's s */
    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-message-create.json"));
    ASSERT_EQ(3, tg.gw->payload.seq); /* fixture's s */

    tg_cleanup(&tg);
    PASS();
}

TEST
reconnect_op7_resumes(void)
{
    struct test_gateway tg;
    enum ws_close_reason code = 0;
    char *frame;
    test_json out;

    ASSERT_EQ(0, establish(&tg));
    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-message-create.json"));

    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":7,\"d\":null}");
    ASSERT_EQ(1, mockws_close_requested(tg.ws, &code));
    ASSERT_EQ(DISCORD_GATEWAY_CLOSE_REASON_RECONNECT, (int)code);
    ASSERT(tg.gw->session->status & DISCORD_SESSION_SHUTDOWN);
    ASSERT(tg.gw->session->status & DISCORD_SESSION_RESUMABLE);

    /* peer echoes our CLOSE; resumability is preserved through the
     * SHUTDOWN early-return */
    mockws_finish_close(tg.ws);
    ASSERT(tg.gw->session->status & DISCORD_SESSION_RESUMABLE);

    ASSERT_EQ(false, discord_gateway_end(tg.gw)); /* retrying */
    ASSERT_EQ(false, tg.gw->session->is_ready);

    frame = reconnect_hello(&tg);
    ASSERT_NEQ(NULL, frame);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "6"); /* RESUME, not IDENTIFY */
    ASSERT_JSON_PATH_STR(&out, "d.token", TEST_DUMMY_TOKEN);
    ASSERT_JSON_PATH_STR(&out, "d.session_id",
                         "fake_session_33ecab261d4681af");
    ASSERT_JSON_PATH_STR(&out, "d.seq", "3");
    test_json_unload(&out);
    free(frame);

    tg_cleanup(&tg);
    PASS();
}

TEST
reconnect_via_force_teardown(void)
{
    struct test_gateway tg;
    char *frame;
    test_json out;

    ASSERT_EQ(0, establish(&tg));
    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-message-create.json"));

    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":7,\"d\":null}");
    /* production's common path: the run loop breaks on SHUTDOWN and
     * force-tears the transport down before any close echo arrives */
    ASSERT_EQ(false, discord_gateway_end(tg.gw));

    frame = reconnect_hello(&tg);
    ASSERT_NEQ(NULL, frame);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "6");
    ASSERT_JSON_PATH_STR(&out, "d.seq", "3");
    test_json_unload(&out);
    free(frame);

    tg_cleanup(&tg);
    PASS();
}

TEST
invalid_session_resumable(void)
{
    struct test_gateway tg;
    enum ws_close_reason code = 0;
    char *frame;
    test_json out;

    ASSERT_EQ(0, establish(&tg));
    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":9,\"d\":true}");
    ASSERT_EQ(1, mockws_close_requested(tg.ws, &code));
    ASSERT_EQ(DISCORD_GATEWAY_CLOSE_REASON_RECONNECT, (int)code);
    ASSERT(tg.gw->session->status & DISCORD_SESSION_RESUMABLE);

    ASSERT_EQ(false, discord_gateway_end(tg.gw));
    frame = reconnect_hello(&tg);
    ASSERT_NEQ(NULL, frame);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "6");
    test_json_unload(&out);
    free(frame);

    tg_cleanup(&tg);
    PASS();
}

TEST
invalid_session_null_treated_resumable(void)
{
    struct test_gateway tg;
    enum ws_close_reason code = 0;

    ASSERT_EQ(0, establish(&tg));
    /* the handler only special-cases the literal token `false` */
    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":9,\"d\":null}");
    ASSERT_EQ(1, mockws_close_requested(tg.ws, &code));
    ASSERT_EQ(DISCORD_GATEWAY_CLOSE_REASON_RECONNECT, (int)code);
    ASSERT(tg.gw->session->status & DISCORD_SESSION_RESUMABLE);

    tg_cleanup(&tg);
    PASS();
}

TEST
invalid_session_not_resumable(void)
{
    struct test_gateway tg;
    enum ws_close_reason code = 0;
    char *frame;
    test_json out;

    ASSERT_EQ(0, establish(&tg));
    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":9,\"d\":false}");
    ASSERT_EQ(1, mockws_close_requested(tg.ws, &code));
    ASSERT_EQ(WS_CLOSE_REASON_NORMAL, code);
    ASSERT(!(tg.gw->session->status & DISCORD_SESSION_RESUMABLE));

    ASSERT_EQ(false, discord_gateway_end(tg.gw));
    frame = reconnect_hello(&tg);
    ASSERT_NEQ(NULL, frame);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "2"); /* fresh IDENTIFY */
    test_json_unload(&out);
    free(frame);

    tg_cleanup(&tg);
    PASS();
}

/* Server-initiated close policy: per the Discord gateway docs, 1000
 * and 1001 invalidate the session while other transport-level closes
 * (e.g. 1006 abnormal closure) are resumable; 4xxx codes follow the
 * documented per-code reconnect/resume table. */
TEST
close_code_policy_sweep(void)
{
    static const struct {
        int code;
        int resumable;
        int retry;
    } sweep[] = {
        /* normal/going-away: session invalidated */
        { 1000, 0, 1 },
        { 1001, 0, 1 },
        /* abnormal transport close: resumable */
        { 1006, 1, 1 },
        /* recoverable gateway errors: resumable */
        { 4000, 1, 1 },
        { 4001, 1, 1 },
        { 4002, 1, 1 },
        { 4003, 1, 1 },
        { 4005, 1, 1 },
        { 4008, 1, 1 },
        /* invalid sequence / session timed out: fresh session */
        { 4007, 0, 1 },
        { 4009, 0, 1 },
        /* fatal misconfiguration: don't retry */
        { 4004, 0, 0 },
        { 4010, 0, 0 },
        { 4011, 0, 0 },
        { 4012, 0, 0 },
        { 4013, 0, 0 },
        { 4014, 0, 0 },
        /* unknown 4xxx: conservatively fresh session */
        { 4042, 0, 1 },
    };
    size_t i;

    for (i = 0; i < sizeof(sweep) / sizeof(*sweep); ++i) {
        struct test_gateway tg;
        char label[64];

        snprintf(label, sizeof(label), "close code %d", sweep[i].code);
        ASSERT_EQm(label, 0, establish(&tg));
        mockws_close(tg.ws, (enum ws_close_reason)sweep[i].code,
                     "scripted close");
        ASSERT(tg.gw->session->status & DISCORD_SESSION_SHUTDOWN);
        ASSERT_EQm(label, sweep[i].resumable,
                   !!(tg.gw->session->status & DISCORD_SESSION_RESUMABLE));
        ASSERT_EQm(label, sweep[i].retry, (int)tg.gw->session->retry.enable);
        tg_cleanup(&tg);
    }
    PASS();
}

TEST
resumed_replay_continues_sequence(void)
{
    struct test_gateway tg;
    char *frame;

    memset(&rec, 0, sizeof(rec));
    ASSERT_EQ(0, tg_boot(&tg));
    discord_set_on_message_create(tg.client, on_message);
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));
    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-message-create.json"));
    ASSERT_EQ(1, rec.messages);

    /* scripted disconnect + resume */
    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":7,\"d\":null}");
    ASSERT_EQ(false, discord_gateway_end(tg.gw));
    frame = reconnect_hello(&tg); /* RESUME */
    ASSERT_NEQ(NULL, frame);
    free(frame);

    tg_deliver(&tg, "{\"t\":\"RESUMED\",\"s\":4,\"op\":0,\"d\":{}}");
    ASSERT_EQ(true, tg.gw->session->is_ready);
    ASSERT_EQ(4, tg.gw->payload.seq);

    /* replayed event reaches the user callback, sequence continues */
    ASSERT_EQ(
        0, tg_deliver_event(&tg, "MESSAGE_CREATE", 5, "message-plain.json"));
    ASSERT_EQ(2, rec.messages);
    ASSERT_EQ(1000000000000000100ULL, rec.last_id);
    ASSERT_EQ(5, tg.gw->payload.seq);

    tg_cleanup(&tg);
    PASS();
}

SUITE(gateway_resume)
{
    RUN_TEST(sequence_advances_on_dispatch);
    RUN_TEST(reconnect_op7_resumes);
    RUN_TEST(reconnect_via_force_teardown);
    RUN_TEST(invalid_session_resumable);
    RUN_TEST(invalid_session_null_treated_resumable);
    RUN_TEST(invalid_session_not_resumable);
    RUN_TEST(close_code_policy_sweep);
    RUN_TEST(resumed_replay_continues_sequence);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(gateway_resume);
    GREATEST_MAIN_END();
}
