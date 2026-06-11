#ifndef TEST_CLIENT_H
#define TEST_CLIENT_H

#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cog-utils.h"

#include "fixture-server.h"

/* Boot scaffolding for hermetic integration tests: a real struct discord
 * pointed at a loopback fixture server via discord_config.base_url.
 *
 * discord_run() is never used — it unconditionally starts the gateway,
 * which dials out. Sync requests (`ret.sync`) need no loop at all: the
 * REST machinery (curl multi, io_poller, bucket timers, 429 retries) runs
 * autonomously on the REST threadpool thread. Async callbacks normally
 * fire from discord_run()'s loop, so tests pump
 * discord_requestor_dispatch_responses() directly via test_client_await();
 * callbacks therefore run on the test thread and plain int flags are safe.
 */

/* format-valid per _discord_token_is_valid() (len 50-80, exactly 2 dots,
 * part lengths 24/6/40) and free of '$' (would trigger env expansion) */
#define TEST_DUMMY_TOKEN                                                      \
    "MTAwMDAwMDAwMDAwMDAwMDAx.G4bZ9X."                                        \
    "c29tZS1mYWtlLXRva2VuLXNlY3JldC1wYWRkaW5n"

/* Construct a client against `fs`. Scripts the synchronous GET /users/@me
 * that _discord_init() performs at boot (no ratelimit headers, so the boot
 * route lands in the 'miss' bucket and stays out of bucket tests' way).
 * Returns NULL on boot failure. */
static inline struct discord *
test_client_boot(struct fixture_server *fs)
{
    static char base_url[64]; /* must outlive the client; borrowed by it */

    fixture_server_script(
        fs, &(struct fs_script){
                .method = "GET",
                .path = "/users/@me",
                .status = 200,
                .body_fixture = "user-basic.json",
                .headers =
                    (const struct fs_header[]){
                        { "Content-Type", "application/json" },
                    },
                .n_headers = 1,
            });

    snprintf(base_url, sizeof base_url, "http://127.0.0.1:%hu",
             fixture_server_port(fs));

    return discord_from_config(&(struct discord_config){
        /* discord_cleanup() frees config.token: must be heap'd */
        .token = strdup(TEST_DUMMY_TOKEN),
        .base_url = base_url,
        .log = { .quiet = true },
    });
}

/* Pump async callback dispatch until *flag is nonzero or timeout_ms
 * elapses; returns nonzero if the flag was raised in time. */
static inline int
test_client_await(struct discord *client, const int *flag, long timeout_ms)
{
    const u64unix_ms deadline = cog_timestamp_ms() + (u64unix_ms)timeout_ms;

    while (!*flag && cog_timestamp_ms() < deadline) {
        discord_requestor_dispatch_responses(&client->rest.requestor);
        cog_sleep_us(2000);
    }
    return *flag != 0;
}

#endif /* TEST_CLIENT_H */
