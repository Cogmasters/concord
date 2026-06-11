#ifndef GATEWAY_HARNESS_H
#define GATEWAY_HARNESS_H

#include "test-utils.h"
#include "test-client.h"
#include "mock-websockets.h"

/* Gateway-under-test scaffolding: a real client booted hermetically via
 * test-client.h (REST pointed at the loopback fixture server), with the
 * gateway transport substituted by mock-websockets.o at link time —
 * ws_init() inside discord_gateway_init() transparently hands the
 * gateway a mock instance.
 *
 * discord_gateway_start() is deliberately bypassed: it fetches the
 * gateway URL over REST and runs a libcurl wss capability check, both
 * meaningless against the mock. Tests call ws_start() + mockws_connect()
 * directly — everything start does past those gates. Consequence: the
 * resume-URL selection (ws_set_url(session->resume_url)) is not
 * exercised here; tests assert session->resume_url content instead.
 *
 * Everything is synchronous: the default event scheduler runs user
 * callbacks on the delivering thread, so a tg_deliver*() call returns
 * only after the gateway (and any user callback) fully processed the
 * payload. */

struct test_gateway {
    struct fixture_server *fs;
    struct discord *client;
    struct discord_gateway *gw; /* == &client->gw */
    struct websockets *ws; /* the mock; == gw->ws */
};

/* Boot the client; the gateway is initialized but not connected, so
 * intents and event callbacks can still be registered.  Returns 0 on
 * success. */
static inline int
tg_boot(struct test_gateway *tg)
{
    memset(tg, 0, sizeof *tg);
    if (!(tg->fs = fixture_server_start())) return -1;
    if (!(tg->client = test_client_boot(tg->fs))) {
        fixture_server_stop(tg->fs);
        return -1;
    }
    tg->gw = &tg->client->gw;
    tg->ws = tg->client->gw.ws;
    return 0;
}

/* ws_start() + transport-level connect (fires the gateway's
 * on_connect), then one perform so gw->timer->now is fresh — the real
 * loop performs continuously, and heartbeat bookkeeping (hbeat_last,
 * ping_ms) reads that clock.  Returns 0 on success. */
static inline int
tg_connect(struct test_gateway *tg)
{
    if (!ws_start(tg->ws)) return -1;
    mockws_connect(tg->ws);
    discord_gateway_perform(tg->gw);
    return 0;
}

static inline void
tg_cleanup(struct test_gateway *tg)
{
    if (tg->client) discord_cleanup(tg->client);
    if (tg->fs) fixture_server_stop(tg->fs);
    memset(tg, 0, sizeof *tg);
}

/* deliver a raw JSON payload string */
static inline void
tg_deliver(struct test_gateway *tg, const char *json)
{
    mockws_deliver_text(tg->ws, json, strlen(json));
}

/* deliver a fixture file verbatim (for full-envelope fixtures) */
static inline int
tg_deliver_fixture(struct test_gateway *tg, const char *name)
{
    size_t len;
    char *js = test_load_json_fixture(name, &len);

    if (!js) return -1;
    mockws_deliver_text(tg->ws, js, len);
    free(js);
    return 0;
}

/* Wrap a payload fixture in a dispatch envelope and deliver it.  The
 * "d" field is always present: the dispatch path dereferences it
 * unconditionally. */
static inline int
tg_deliver_event(struct test_gateway *tg,
                 const char *name,
                 int seq,
                 const char *payload_fixture)
{
    size_t len, n;
    char *payload, *buf;

    if (!(payload = test_load_json_fixture(payload_fixture, &len))) return -1;
    n = len + 128;
    if (!(buf = malloc(n))) {
        free(payload);
        return -1;
    }
    n = (size_t)snprintf(buf, n, "{\"t\":\"%s\",\"s\":%d,\"op\":0,\"d\":%s}",
                         name, seq, payload);
    mockws_deliver_text(tg->ws, buf, n);
    free(buf);
    free(payload);
    return 0;
}

/* HELLO + READY handshake; drains the captured IDENTIFY and the
 * heartbeat that READY triggers, leaving the frame FIFO empty. */
static inline int
tg_handshake(struct test_gateway *tg)
{
    if (0 != tg_deliver_fixture(tg, "gateway-hello.json")) return -1;
    if (0 != tg_deliver_fixture(tg, "gateway-ready.json")) return -1;
    mockws_drain_sent(tg->ws);
    return 0;
}

#endif /* GATEWAY_HARNESS_H */
