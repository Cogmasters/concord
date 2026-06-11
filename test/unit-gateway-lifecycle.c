/* Gateway connection lifecycle against the mock transport: HELLO →
 * IDENTIFY handshake, heartbeat/ACK cycle, zombie detection, READY
 * session bookkeeping.  Everything is synchronous and clock-free: the
 * only timing source is the internal heartbeat timer, which tests
 * force-expire explicitly. */

#include "gateway-harness.h"

#define TEST_INTENTS (DISCORD_GATEWAY_GUILDS | DISCORD_GATEWAY_GUILD_MESSAGES)

TEST
nothing_sent_before_hello(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, tg_boot(&tg));
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ((size_t)0, mockws_sent_count(tg.ws));

    tg_cleanup(&tg);
    PASS();
}

TEST
hello_triggers_identify(void)
{
    struct test_gateway tg;
    char *frame, intents[24];
    test_json out;

    snprintf(intents, sizeof(intents), "%d", TEST_INTENTS);

    ASSERT_EQ(0, tg_boot(&tg));
    /* must precede connect: discord_add_intents refuses while CONNECTED */
    discord_add_intents(tg.client, TEST_INTENTS);
    ASSERT_EQ(0, tg_connect(&tg));

    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-hello.json"));
    ASSERT_EQ((size_t)1, mockws_sent_count(tg.ws));
    frame = mockws_pop_sent(tg.ws);
    ASSERT_NEQ(NULL, frame);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "2");
    ASSERT_JSON_PATH_STR(&out, "d.token", TEST_DUMMY_TOKEN);
    ASSERT_JSON_PATH_STR(&out, "d.intents", intents);
    ASSERT_JSON_PATH_STR(&out, "d.properties.browser", "concord");
    ASSERT_JSON_PATH_STR(&out, "d.properties.device", "concord");
    ASSERT_JSON_HAS(&out, "d.properties.os");

    test_json_unload(&out);
    free(frame);
    tg_cleanup(&tg);
    PASS();
}

TEST
hello_stores_heartbeat_interval(void)
{
    struct test_gateway tg;

    ASSERT_EQ(0, tg_boot(&tg));
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-hello.json"));
    ASSERT_EQ(41250, (int)tg.gw->timer->hbeat_interval);

    tg_cleanup(&tg);
    PASS();
}

TEST
ready_stores_session_and_heartbeats(void)
{
    struct test_gateway tg;
    char *frame;
    test_json out;

    ASSERT_EQ(0, tg_boot(&tg));
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-hello.json"));
    free(mockws_pop_sent(tg.ws)); /* IDENTIFY */

    ASSERT_EQ(0, tg_deliver_fixture(&tg, "gateway-ready.json"));
    ASSERT_STR_EQ("fake_session_33ecab261d4681af", tg.gw->session->id);
    ASSERT_EQ(0, strncmp("wss://gateway.example.invalid/",
                         tg.gw->session->resume_url,
                         strlen("wss://gateway.example.invalid/")));
    ASSERT_NEQ(NULL, strstr(tg.gw->session->resume_url, "encoding=json"));
    ASSERT_EQ(true, tg.gw->session->is_ready);
    ASSERT_EQ(0, tg.gw->session->retry.attempt);

    /* READY sends the first heartbeat immediately, with READY's seq */
    ASSERT_EQ((size_t)1, mockws_sent_count(tg.ws));
    frame = mockws_pop_sent(tg.ws);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "1");
    ASSERT_JSON_PATH_STR(&out, "d", "1");
    test_json_unload(&out);
    free(frame);

    /* and registers the cadence timer */
    ASSERT(tg.gw->timer->hbeat_timer != 0);

    tg_cleanup(&tg);
    PASS();
}

TEST
heartbeat_ack_cycle(void)
{
    struct test_gateway tg;
    char *frame;
    test_json out;

    ASSERT_EQ(0, tg_boot(&tg));
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    /* READY's heartbeat is in flight: un-ACK'd */
    ASSERT_EQ(false, tg.gw->timer->hbeat_acknowledged);

    discord_gateway_perform(tg.gw); /* refresh gw->timer->now */
    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":11,\"d\":null}");
    ASSERT_EQ(true, tg.gw->timer->hbeat_acknowledged);
    ASSERT(tg.gw->timer->ping_ms >= 0);

    /* next pulse flips the flag again */
    discord_gateway_send_heartbeat(tg.gw, tg.gw->payload.seq);
    ASSERT_EQ(false, tg.gw->timer->hbeat_acknowledged);
    frame = mockws_pop_sent(tg.ws);
    ASSERT_NEQ(NULL, frame);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "1");
    ASSERT_JSON_PATH_STR(&out, "d", "1");
    test_json_unload(&out);
    free(frame);

    tg_cleanup(&tg);
    PASS();
}

/* force the internal heartbeat timer to fire now (GET to keep its
 * callback/data, reschedule with zero delay, then run the queue) */
static void
force_heartbeat_timer(struct test_gateway *tg)
{
    struct discord_timer t = { .id = tg->gw->timer->hbeat_timer,
                               .flags = DISCORD_TIMER_GET };

    if (!discord_internal_timer_ctl(tg->client, &t)) return;
    t.flags &= ~(enum discord_timer_flags)DISCORD_TIMER_GET;
    t.delay = 0;
    discord_internal_timer_ctl(tg->client, &t);
    discord_timers_run(tg->client, &tg->client->timers.internal);
}

TEST
heartbeat_cadence_refire(void)
{
    struct test_gateway tg;
    char *frame;
    test_json out;

    ASSERT_EQ(0, tg_boot(&tg));
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":11,\"d\":null}"); /* ACK */
    force_heartbeat_timer(&tg);

    ASSERT_EQ((size_t)1, mockws_sent_count(tg.ws));
    frame = mockws_pop_sent(tg.ws);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "1");
    test_json_unload(&out);
    free(frame);
    ASSERT_EQ(false, tg.gw->timer->hbeat_acknowledged);

    tg_cleanup(&tg);
    PASS();
}

TEST
zombie_connection_reconnects(void)
{
    struct test_gateway tg;
    enum ws_close_reason code = 0;

    ASSERT_EQ(0, tg_boot(&tg));
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    /* READY's heartbeat was never ACK'd; the next cadence tick must
     * treat the connection as zombie and reconnect with a fresh
     * session (close 1000, resumability not retained) */
    ASSERT_EQ(false, tg.gw->timer->hbeat_acknowledged);
    force_heartbeat_timer(&tg);

    ASSERT_EQ((size_t)0, mockws_sent_count(tg.ws));
    ASSERT_EQ(1, mockws_close_requested(tg.ws, &code));
    ASSERT_EQ(WS_CLOSE_REASON_NORMAL, code);
    ASSERT(tg.gw->session->status & DISCORD_SESSION_SHUTDOWN);
    ASSERT(!(tg.gw->session->status & DISCORD_SESSION_RESUMABLE));
    ASSERT_EQ(true, tg.gw->session->retry.enable);

    tg_cleanup(&tg);
    PASS();
}

TEST
server_heartbeat_request_gets_reply(void)
{
    struct test_gateway tg;
    char *frame;
    test_json out;

    ASSERT_EQ(0, tg_boot(&tg));
    ASSERT_EQ(0, tg_connect(&tg));
    ASSERT_EQ(0, tg_handshake(&tg));

    /* even while the READY heartbeat is un-ACK'd, a server-requested
     * beat is answered unconditionally (the request proves liveness) */
    ASSERT_EQ(false, tg.gw->timer->hbeat_acknowledged);
    tg_deliver(&tg, "{\"t\":null,\"s\":null,\"op\":1,\"d\":null}");

    ASSERT_EQ((size_t)1, mockws_sent_count(tg.ws));
    frame = mockws_pop_sent(tg.ws);
    ASSERT_EQ(0, test_json_load(&out, frame, strlen(frame)));
    ASSERT_JSON_PATH_STR(&out, "op", "1");
    ASSERT_JSON_PATH_STR(&out, "d", "1");
    test_json_unload(&out);
    free(frame);
    /* no reconnect was triggered */
    ASSERT_EQ(0, mockws_close_requested(tg.ws, NULL));

    tg_cleanup(&tg);
    PASS();
}

SUITE(gateway_lifecycle)
{
    RUN_TEST(nothing_sent_before_hello);
    RUN_TEST(hello_triggers_identify);
    RUN_TEST(hello_stores_heartbeat_interval);
    RUN_TEST(ready_stores_session_and_heartbeats);
    RUN_TEST(heartbeat_ack_cycle);
    RUN_TEST(heartbeat_cadence_refire);
    RUN_TEST(zombie_connection_reconnects);
    RUN_TEST(server_heartbeat_request_gets_reply);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(gateway_lifecycle);
    GREATEST_MAIN_END();
}
