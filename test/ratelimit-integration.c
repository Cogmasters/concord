#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "discord.h"
#include "discord-internal.h"

#include "fixture-server.h"
#include "test-client.h"
#include "test-utils.h"

/* Hermetic tests for the client's observable throttling behavior — 429
 * backoff, per-bucket pacing, global-limit handling — against scripted
 * rate-limit responses. C01 proves the bucket arithmetic; this suite
 * proves the client acts on it. These behaviors are untestable against
 * live Discord (limits must be violated to observe them).
 *
 * Timing assertions are interval-based on the fixture server's journal
 * timestamps: lower bounds allow 50ms timer slack, upper bounds allow
 * generous CI margins. No sub-second precision.
 *
 * Every scripted 429 (and every "exhausted" 200) carries an explicit
 * X-RateLimit-Remaining: 0 — _discord_bucket_populate() runs after the
 * 429 handler and would otherwise default remaining back to 1,
 * unlocking the bucket immediately. Real Discord 429s always carry the
 * header, so this is faithful scripting.
 *
 * Each test uses fresh routes/channel ids so buckets don't interfere;
 * the boot route /users/@me carries no ratelimit headers and stays in
 * the 'miss' bucket. */

static struct fixture_server *FS;
static struct discord *CLIENT;

struct async_result {
    int done_count;
    int fail_count;
    int settled;
    CCORDcode code;
};

static void
on_fail(struct discord *client, struct discord_response *resp)
{
    struct async_result *res = resp->data;
    (void)client;

    res->fail_count++;
    res->settled = 1;
    res->code = resp->code;
}

static void
on_channel_done(struct discord *client,
                struct discord_response *resp,
                const struct discord_channel *channel)
{
    struct async_result *res = resp->data;
    (void)client;
    (void)channel;

    res->done_count++;
    res->settled = 1;
    res->code = resp->code;
}

TEST
retry_429_then_succeed(void)
{
    struct discord_ret_channel ret = { .sync = DISCORD_SYNC_FLAG };
    uint64_t t1, t2;

    /* prime: discover bucket bktA with budget left */
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/111",
                .status = 200,
                .body = "{}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktA" },
                        { "X-RateLimit-Limit", "5" },
                        { "X-RateLimit-Remaining", "4" },
                        { "X-RateLimit-Reset-After", "60" },
                    },
                .n_headers = 4,
                .times = 1,
            });
    /* then: one 429 instructing a 0.6s wait, then success */
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/111",
                .status = 429,
                .body = "{\"message\": \"You are being rate limited.\", "
                        "\"retry_after\": 0.6, \"global\": false}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktA" },
                        { "X-RateLimit-Remaining", "0" },
                        { "X-RateLimit-Reset-After", "0.6" },
                    },
                .n_headers = 3,
                .times = 1,
            });
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/111",
                .status = 200,
                .body = "{}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktA" },
                        { "X-RateLimit-Remaining", "4" },
                        { "X-RateLimit-Reset-After", "60" },
                    },
                .n_headers = 3,
            });

    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 111ULL, &ret));
    /* the 429'd request is retried transparently: same sync call, three
     * requests on the wire, and the retry waited out retry_after */
    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 111ULL, &ret));
    ASSERT_EQ((size_t)3, fixture_server_count_path(FS, "/channels/111"));
    t1 = fixture_server_nth_recv_ms(FS, "/channels/111", 1); /* the 429 */
    t2 = fixture_server_nth_recv_ms(FS, "/channels/111", 2); /* the retry */
    ASSERT(t2 - t1 >= 550);
    ASSERT(t2 - t1 <= 2600);
    PASS();
}

TEST
per_bucket_pacing(void)
{
    struct discord_ret_channel sync_ret = { .sync = DISCORD_SYNC_FLAG };
    struct async_result res = { 0 };
    struct discord_ret_channel async_ret = {
        .done = on_channel_done,
        .fail = on_fail,
        .data = &res,
    };
    uint64_t t_222_first, t_222_second, t_333;

    /* route /222: budget exhausted for 0.8s, then replenished */
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/222",
                .status = 200,
                .body = "{}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktB" },
                        { "X-RateLimit-Remaining", "0" },
                        { "X-RateLimit-Reset-After", "0.8" },
                    },
                .n_headers = 3,
                .times = 1,
            });
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/222",
                .status = 200,
                .body = "{}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktB" },
                        { "X-RateLimit-Remaining", "4" },
                        { "X-RateLimit-Reset-After", "60" },
                    },
                .n_headers = 3,
            });
    /* route /333: independent bucket with budget left */
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/333",
                .status = 200,
                .body = "{}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktC" },
                        { "X-RateLimit-Remaining", "4" },
                        { "X-RateLimit-Reset-After", "60" },
                    },
                .n_headers = 3,
            });

    /* exhaust /222's bucket */
    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 222ULL, &sync_ret));
    /* queue a follow-up on the exhausted bucket: must be deferred */
    ASSERT_EQ(CCORD_PENDING, discord_get_channel(CLIENT, 222ULL, &async_ret));
    /* a different bucket proceeds immediately despite /222 waiting */
    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 333ULL, &sync_ret));

    ASSERT(test_client_await(CLIENT, &res.settled, 5000));
    ASSERT_EQ(1, res.done_count);
    ASSERT_EQ(0, res.fail_count);

    t_222_first = fixture_server_nth_recv_ms(FS, "/channels/222", 0);
    t_222_second = fixture_server_nth_recv_ms(FS, "/channels/222", 1);
    t_333 = fixture_server_nth_recv_ms(FS, "/channels/333", 0);
    ASSERT(t_333 - t_222_first < 500);
    ASSERT(t_222_second - t_222_first >= 750);
    ASSERT(t_222_second - t_222_first <= 2800);
    PASS();
}

TEST
global_limit_pauses_buckets(void)
{
    struct discord_ret_channel sync_ret = { .sync = DISCORD_SYNC_FLAG };
    struct async_result res = { 0 };
    struct discord_ret_channel async_ret = {
        .done = on_channel_done,
        .fail = on_fail,
        .data = &res,
    };
    uint64_t t_444_first, t_444_second, t_555_first, t_555_retry;

    /* /444: bucket locked for a short 0.3s */
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/444",
                .status = 200,
                .body = "{}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktG1" },
                        { "X-RateLimit-Remaining", "0" },
                        { "X-RateLimit-Reset-After", "0.3" },
                    },
                .n_headers = 3,
                .times = 1,
            });
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/444",
                .status = 200,
                .body = "{}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktG1" },
                        { "X-RateLimit-Remaining", "4" },
                        { "X-RateLimit-Reset-After", "60" },
                    },
                .n_headers = 3,
            });
    /* /555: a global 429 demanding a 1.5s full stop, then success */
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/555",
                .status = 429,
                .body = "{\"message\": \"You are being rate limited.\", "
                        "\"retry_after\": 1.5, \"global\": true}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Remaining", "0" },
                        { "X-RateLimit-Reset-After", "1.5" },
                        { "X-RateLimit-Global", "true" },
                    },
                .n_headers = 3,
                .times = 1,
            });
    fixture_server_script(FS, &(struct fs_script){
                                  .method = "GET",
                                  .path = "/channels/555",
                                  .status = 200,
                                  .body = "{}",
                              });

    /* lock /444's bucket (0.3s) */
    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 444ULL, &sync_ret));
    /* trip the global limit (1.5s) on another route */
    ASSERT_EQ(CCORD_PENDING, discord_get_channel(CLIENT, 555ULL, &async_ret));
    /* let the 429 round-trip so the global timestamp is set before the
     * next /444 attempt is scheduled */
    cog_sleep_us(250 * 1000);

    /* /444's own 0.3s lock has nearly expired, but the global limit
     * dominates: this waits ~1.5s, not ~0.05s */
    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 444ULL, &sync_ret));

    ASSERT(test_client_await(CLIENT, &res.settled, 6000));
    ASSERT_EQ(1, res.done_count);

    t_444_first = fixture_server_nth_recv_ms(FS, "/channels/444", 0);
    t_444_second = fixture_server_nth_recv_ms(FS, "/channels/444", 1);
    t_555_first = fixture_server_nth_recv_ms(FS, "/channels/555", 0);
    t_555_retry = fixture_server_nth_recv_ms(FS, "/channels/555", 1);
    /* both the locked bucket and the 429'd route waited out the global
     * window (>= 1.5s from the 429, minus margins) */
    ASSERT(t_444_second - t_444_first >= 1350);
    ASSERT(t_444_second - t_444_first <= 3700);
    ASSERT(t_555_retry - t_555_first >= 1350);
    ASSERT(t_555_retry - t_555_first <= 3700);
    PASS();
}

TEST
shared_bucket_hash_current_behavior(void)
{
    struct discord_ret_channel chan_ret = { .sync = DISCORD_SYNC_FLAG };
    struct discord_ret_messages msgs_ret = { .sync = DISCORD_SYNC_FLAG };
    uint64_t t_chan, t_pins;

    /* two distinct routes announcing the same X-RateLimit-Bucket hash;
     * /777 reports its budget exhausted for a full second */
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/777",
                .status = 200,
                .body = "{}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktSHARED" },
                        { "X-RateLimit-Remaining", "0" },
                        { "X-RateLimit-Reset-After", "1.0" },
                    },
                .n_headers = 3,
            });
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/777/pins",
                .status = 200,
                .body = "[]",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktSHARED" },
                        { "X-RateLimit-Remaining", "4" },
                        { "X-RateLimit-Reset-After", "60" },
                    },
                .n_headers = 3,
            });

    ASSERT_EQ(CCORD_OK, discord_get_channel(CLIENT, 777ULL, &chan_ret));
    ASSERT_EQ(CCORD_OK, discord_get_pinned_messages(CLIENT, 777ULL,
                                                    &msgs_ret));

    /* CURRENT behavior: buckets are keyed by route key only — the shared
     * hash is not used for matching, so /pins gets an independent bucket
     * and is NOT throttled together with /777 */
    t_chan = fixture_server_nth_recv_ms(FS, "/channels/777", 0);
    t_pins = fixture_server_nth_recv_ms(FS, "/channels/777/pins", 0);
    ASSERT(t_pins - t_chan < 500);
    PASS();
}

TEST
shared_bucket_hash_throttles_together(void)
{
    /* Discord's documented semantics: routes sharing an
     * X-RateLimit-Bucket id form one bucket and throttle together.
     * The ratelimiter's hashtable is keyed by route key only
     * (discord-rest_ratelimit.c), so this is not implemented; the test
     * above pins the current behavior. */
    SKIPm("x-ratelimit-bucket dedup not implemented - routes sharing a "
          "hash are throttled independently");
}

TEST
exhausted_429_retries_give_up(void)
{
    struct discord_ret_channel ret = { .sync = DISCORD_SYNC_FLAG };

    /* persistent 429s: the requestor abandons the request after the
     * original attempt plus retry_limit (3) retries */
    fixture_server_script(
        FS, &(struct fs_script){
                .method = "GET",
                .path = "/channels/888",
                .status = 429,
                .body = "{\"message\": \"You are being rate limited.\", "
                        "\"retry_after\": 0.05, \"global\": false}",
                .headers =
                    (const struct fs_header[]){
                        { "X-RateLimit-Bucket", "bktE" },
                        { "X-RateLimit-Remaining", "0" },
                        { "X-RateLimit-Reset-After", "0.05" },
                    },
                .n_headers = 3,
            });

    ASSERT_EQ(CCORD_DISCORD_RATELIMIT,
              discord_get_channel(CLIENT, 888ULL, &ret));
    ASSERT_EQ((size_t)4, fixture_server_count_path(FS, "/channels/888"));
    PASS();
}

SUITE(ratelimit_behavior)
{
    RUN_TEST(retry_429_then_succeed);
    RUN_TEST(per_bucket_pacing);
    RUN_TEST(global_limit_pauses_buckets);
    RUN_TEST(shared_bucket_hash_current_behavior);
    RUN_TEST(shared_bucket_hash_throttles_together);
    RUN_TEST(exhausted_429_retries_give_up);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();

    alarm(60); /* a scheduling regression must fail, not wedge make check */

    FS = fixture_server_start();
    assert(FS != NULL && "couldn't start fixture server");
    CLIENT = test_client_boot(FS);
    assert(CLIENT != NULL && "couldn't boot client against loopback");

    RUN_SUITE(ratelimit_behavior);

    discord_cleanup(CLIENT);
    fixture_server_stop(FS);
    GREATEST_MAIN_END();
}
