#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "discord.h"
#include "discord-internal.h"
#include "cog-utils.h"
#include "test-utils.h"

/* Hermetic unit tests for the ratelimit bucket bookkeeping in
 * src/discord-rest_ratelimit.c, driven by synthetic X-RateLimit-* header
 * sets (no network, no threads).
 *
 * Time determinism: no injection seam is needed. Every time-dependent path
 * under test reads cog_timestamp_ms() exactly once, so assertions bracket
 * the call with before/after timestamps and check the result lands in
 * [before + delta, after + delta].
 *
 * Behavioral contract worth noting: there is no client-side `remaining--`.
 * b->remaining is authoritative from response headers (populate defaults it
 * to 1 when the header is absent) and gates the request selector when it
 * reaches 0. */

/* the ratelimiter reaches its client through CLIENT() (container_of) and
 * needs logmod + requestor queues/qlocks (for cleanup) + rest timers and
 * io_poller (for the selector's ratelimited path, which arms a timer) */
static struct discord *
bare_client_init(void)
{
    struct discord *client = calloc(1, sizeof *client);

    if (logmod_init(&client->logmod, "CONCORD", client->table,
                    sizeof(client->table) / sizeof *client->table)
        != LOGMOD_OK)
    {
        return free(client), NULL;
    }
    logmod_set_options(&client->logmod, (struct logmod_options){ .quiet = 1 });

    client->rest.requestor.queues =
        calloc(1, sizeof *client->rest.requestor.queues);
    QUEUE_INIT(&client->rest.requestor.queues->recycling);
    QUEUE_INIT(&client->rest.requestor.queues->pending);
    QUEUE_INIT(&client->rest.requestor.queues->finished);

    client->rest.requestor.qlocks =
        calloc(1, sizeof *client->rest.requestor.qlocks);
    pthread_mutex_init(&client->rest.requestor.qlocks->recycling, NULL);
    pthread_mutex_init(&client->rest.requestor.qlocks->pending, NULL);
    pthread_mutex_init(&client->rest.requestor.qlocks->finished, NULL);

    client->rest.io_poller = io_poller_create();
    discord_timers_init(&client->rest.timers, client->rest.io_poller);

    if (discord_ratelimiter_init(&client->rest.requestor.ratelimiter)
        != CCORD_OK)
    {
        return NULL;
    }
    return client;
}

/* PRECONDITION: no bucket may hold busy_req == DISCORD_BUCKET_TIMEOUT here;
 * cleanup would pass the sentinel to discord_request_cancel() which
 * dereferences it. Tests that arm the timeout path reset busy_req first.
 *
 * Fake requests queued into buckets are only *moved* to the recycling queue
 * by discord_ratelimiter_cleanup(); they stay owned by the test and must be
 * freed after this returns. */
static void
bare_client_cleanup(struct discord *client)
{
    discord_timers_cleanup(client, &client->rest.timers);
    discord_ratelimiter_cleanup(&client->rest.requestor.ratelimiter);
    io_poller_destroy(client->rest.io_poller);

    pthread_mutex_destroy(&client->rest.requestor.qlocks->recycling);
    pthread_mutex_destroy(&client->rest.requestor.qlocks->pending);
    pthread_mutex_destroy(&client->rest.requestor.qlocks->finished);
    free(client->rest.requestor.qlocks);
    free(client->rest.requestor.queues);

    logmod_cleanup(&client->logmod);
    free(client);
}

/* test-owned stand-in for a scheduled request; freed by the caller after
 * bare_client_cleanup() */
static struct discord_request *
fake_req(const char *key)
{
    struct discord_request *req = calloc(1, sizeof *req);

    snprintf(req->key, sizeof req->key, "%s", key);
    QUEUE_INIT(&req->entry);
    return req;
}

/* Build a synthetic ua_info from a raw header block such as
 * "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 4\r\n".
 * 'raw' must outlive the returned info; ua_info_get_header() only scans
 * header.{buf,pairs,n_pairs}, and strtol/strtod parsing in the ratelimiter
 * stops at '\r', so values need no per-value NUL terminator. */
static struct ua_info
make_info(const char *raw)
{
    struct ua_info info = { 0 };
    const size_t len = strlen(raw);
    size_t i = 0;

    info.httpcode = 200;
    info.header.buf = (char *)raw;
    info.header.len = len;
    while (i < len && info.header.n_pairs < UA_MAX_HEADER_PAIRS) {
        const size_t field_idx = i;
        size_t colon, value_idx, end;

        for (colon = i; colon < len && raw[colon] != ':'; ++colon)
            continue;
        if (colon == len) break;

        value_idx = colon + 1;
        while (value_idx < len && raw[value_idx] == ' ')
            ++value_idx;
        for (end = value_idx; end < len && raw[end] != '\r'; ++end)
            continue;

        info.header.pairs[info.header.n_pairs].field.idx = field_idx;
        info.header.pairs[info.header.n_pairs].field.size = colon - field_idx;
        info.header.pairs[info.header.n_pairs].value.idx = value_idx;
        info.header.pairs[info.header.n_pairs].value.size = end - value_idx;
        ++info.header.n_pairs;

        i = (end + 2 < len) ? end + 2 : len;
    }
    return info;
}

/* run the discovery path: unknown route + response headers -> new bucket */
static struct discord_bucket *
discover(struct discord_ratelimiter *rl, const char *key, const char *raw)
{
    struct ua_info info = make_info(raw);

    discord_ratelimiter_build(rl, rl->null, key, &info);
    return discord_bucket_get(rl, key);
}

/* va_list shim over discord_ratelimiter_build_key() */
static void
build_key(enum http_method method,
          char key[DISCORD_ROUTE_LEN],
          const char endpoint_fmt[],
          ...)
{
    va_list args;

    va_start(args, endpoint_fmt);
    discord_ratelimiter_build_key(method, key, endpoint_fmt, args);
    va_end(args);
}

TEST
key_major_param_channel(void)
{
    char k1[DISCORD_ROUTE_LEN], k2[DISCORD_ROUTE_LEN],
        expect[DISCORD_ROUTE_LEN];

    build_key(HTTP_GET, k1, "/channels/%" PRIu64, (u64snowflake)123ULL);
    build_key(HTTP_GET, k2, "/channels/%" PRIu64, (u64snowflake)456ULL);

    /* major parameters (channel/guild ids) are pushed literally */
    snprintf(expect, sizeof expect, ":%d:channels:123", HTTP_GET);
    ASSERT_STR_EQ(expect, k1);
    snprintf(expect, sizeof expect, ":%d:channels:456", HTTP_GET);
    ASSERT_STR_EQ(expect, k2);
    PASS();
}

TEST
key_non_major_param_shared(void)
{
    char k1[DISCORD_ROUTE_LEN], k2[DISCORD_ROUTE_LEN],
        expect[DISCORD_ROUTE_LEN];

    build_key(HTTP_GET, k1, "/users/%" PRIu64, (u64snowflake)1ULL);
    build_key(HTTP_GET, k2, "/users/%" PRIu64, (u64snowflake)2ULL);

    /* non-major ids are generalized: the format token is pushed verbatim */
    ASSERT_STR_EQ(k1, k2);
    snprintf(expect, sizeof expect, ":%d:users:%s", HTTP_GET, "%" PRIu64);
    ASSERT_STR_EQ(expect, k1);
    PASS();
}

TEST
key_reactions_collapse(void)
{
    char k1[DISCORD_ROUTE_LEN], k2[DISCORD_ROUTE_LEN];

    build_key(HTTP_PUT, k1,
              "/channels/%" PRIu64 "/messages/%" PRIu64 "/reactions/%s/@me",
              (u64snowflake)7ULL, (u64snowflake)8ULL, "emoji-one");
    build_key(HTTP_PUT, k2,
              "/channels/%" PRIu64 "/messages/%" PRIu64 "/reactions/%s/@me",
              (u64snowflake)7ULL, (u64snowflake)8ULL, "emoji-two");

    /* reactions and sub-routes share the same bucket */
    ASSERT_STR_EQ(k1, k2);
    PASS();
}

TEST
key_mimepost_normalized(void)
{
    char k1[DISCORD_ROUTE_LEN], k2[DISCORD_ROUTE_LEN];

    build_key(HTTP_MIMEPOST, k1, "/channels/%" PRIu64 "/messages",
              (u64snowflake)9ULL);
    build_key(HTTP_POST, k2, "/channels/%" PRIu64 "/messages",
              (u64snowflake)9ULL);

    ASSERT_STR_EQ(k2, k1);
    PASS();
}

SUITE(build_key_suite)
{
    RUN_TEST(key_major_param_channel);
    RUN_TEST(key_non_major_param_shared);
    RUN_TEST(key_reactions_collapse);
    RUN_TEST(key_mimepost_normalized);
}

TEST
init_singletons(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;

    ASSERT_NEQ(NULL, client);
    ASSERT_NEQ(NULL, rl->null);
    ASSERT_NEQ(NULL, rl->miss);
    ASSERT_EQ(rl->null, discord_bucket_get(rl, "null"));
    ASSERT_EQ(rl->miss, discord_bucket_get(rl, "miss"));
    ASSERT_STR_EQ("null", rl->null->hash);
    ASSERT_STR_EQ("miss", rl->miss->hash);
    ASSERT_EQ(1L, rl->null->limit);
    ASSERT_EQ(1L, rl->null->remaining);
    ASSERT_EQ(LONG_MAX, rl->miss->limit);

    bare_client_cleanup(client);
    PASS();
}

TEST
get_unknown_returns_null_bucket(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;

    ASSERT_EQ(rl->null, discord_bucket_get(rl, ":1:channels:42"));

    bare_client_cleanup(client);
    PASS();
}

TEST
build_discovers_bucket(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct ua_info info = make_info("x-ratelimit-bucket: abcd\r\n"
                                    "x-ratelimit-limit: 5\r\n"
                                    "x-ratelimit-remaining: 4\r\n"
                                    "x-ratelimit-reset-after: 1.5\r\n");
    const u64unix_ms before = cog_timestamp_ms();
    struct discord_bucket *b;
    u64unix_ms after;

    discord_ratelimiter_build(rl, rl->null, ":1:channels:42", &info);
    after = cog_timestamp_ms();

    b = discord_bucket_get(rl, ":1:channels:42");
    ASSERT(b != rl->null);
    ASSERT(b != rl->miss);
    ASSERT_STR_EQ("abcd", b->hash);
    ASSERT_EQ(5L, b->limit);
    ASSERT_EQ(4L, b->remaining);
    ASSERT(b->reset_tstamp >= before + 1500);
    ASSERT(b->reset_tstamp <= after + 1500);

    bare_client_cleanup(client);
    PASS();
}

TEST
build_miss_when_no_bucket_header(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct ua_info info = make_info("x-ratelimit-remaining: 3\r\n");

    discord_ratelimiter_build(rl, rl->null, ":1:gateway:bot", &info);

    /* not part of a ratelimiting group: no route is assigned ... */
    ASSERT_EQ(rl->null, discord_bucket_get(rl, ":1:gateway:bot"));
    /* ... and the headers populate the shared miss singleton */
    ASSERT_EQ(3L, rl->miss->remaining);

    bare_client_cleanup(client);
    PASS();
}

TEST
build_existing_bucket_skips_match(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b =
        discover(rl, ":1:channels:42",
                 "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 4\r\n");
    /* a different hash on a known bucket only re-populates values */
    struct ua_info info = make_info("x-ratelimit-bucket: wxyz\r\n"
                                    "x-ratelimit-remaining: 2\r\n");

    discord_ratelimiter_build(rl, b, ":1:channels:42", &info);

    ASSERT_EQ(b, discord_bucket_get(rl, ":1:channels:42"));
    ASSERT_STR_EQ("abcd", b->hash);
    ASSERT_EQ(2L, b->remaining);

    bare_client_cleanup(client);
    PASS();
}

TEST
null_filter_requeues_by_key(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_request *req_a = fake_req(":1:channels:1");
    struct discord_request *req_b = fake_req(":1:channels:2");
    struct ua_info info = make_info("x-ratelimit-bucket: abcd\r\n"
                                    "x-ratelimit-remaining: 4\r\n");
    struct discord_bucket *b;

    discord_bucket_insert(rl, rl->null, req_a, false);
    discord_bucket_insert(rl, rl->null, req_b, false);

    /* response for req_a's route arrives: only matching keys move over */
    discord_ratelimiter_build(rl, rl->null, ":1:channels:1", &info);

    b = discord_bucket_get(rl, ":1:channels:1");
    ASSERT(b != rl->null);
    ASSERT_EQ(b, req_a->b);
    ASSERT_EQ(rl->null, req_b->b);

    bare_client_cleanup(client);
    free(req_a);
    free(req_b);
    PASS();
}

SUITE(buckets)
{
    RUN_TEST(init_singletons);
    RUN_TEST(get_unknown_returns_null_bucket);
    RUN_TEST(build_discovers_bucket);
    RUN_TEST(build_miss_when_no_bucket_header);
    RUN_TEST(build_existing_bucket_skips_match);
    RUN_TEST(null_filter_requeues_by_key);
}

TEST
populate_remaining_zero(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b =
        discover(rl, ":1:channels:42",
                 "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 0\r\n");

    ASSERT_EQ(0L, b->remaining);

    bare_client_cleanup(client);
    PASS();
}

TEST
populate_remaining_default_is_one(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b = discover(
        rl, ":1:channels:42",
        "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 0\r\n");
    /* header absent: remaining falls back to 1 (the populate default that
     * C05's scripted 429s must override with an explicit 0) */
    struct ua_info info = make_info("x-ratelimit-bucket: abcd\r\n");

    discord_ratelimiter_build(rl, b, ":1:channels:42", &info);
    ASSERT_EQ(1L, b->remaining);

    bare_client_cleanup(client);
    PASS();
}

TEST
set_timeout_locks_bucket(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b =
        discover(rl, ":1:channels:42",
                 "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 4\r\n");
    const u64unix_ms before = cog_timestamp_ms();
    u64unix_ms after;

    discord_bucket_set_timeout(b, 250);
    after = cog_timestamp_ms();

    ASSERT_EQ(0L, b->remaining);
    ASSERT_EQ(NULL, b->busy_req);
    ASSERT(b->reset_tstamp >= before + 250);
    ASSERT(b->reset_tstamp <= after + 250);

    bare_client_cleanup(client);
    PASS();
}

TEST
global_header_sets_global_tstamp(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b =
        discover(rl, ":1:channels:42",
                 "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 4\r\n");
    struct ua_info info = make_info("x-ratelimit-bucket: abcd\r\n"
                                    "x-ratelimit-remaining: 0\r\n"
                                    "x-ratelimit-reset-after: 2.0\r\n"
                                    "x-ratelimit-global: true\r\n");
    const u64unix_ms reset_before = b->reset_tstamp;
    const u64unix_ms before = cog_timestamp_ms();
    u64unix_ms after;

    discord_ratelimiter_build(rl, b, ":1:channels:42", &info);
    after = cog_timestamp_ms();

    /* global flag locks all buckets, not this bucket's reset */
    ASSERT(*rl->global_wait_tstamp >= before + 2000);
    ASSERT(*rl->global_wait_tstamp <= after + 2000);
    ASSERT_EQ(reset_before, b->reset_tstamp);

    bare_client_cleanup(client);
    PASS();
}

TEST
set_global_timeout(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b =
        discover(rl, ":1:channels:42",
                 "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 4\r\n");
    const u64unix_ms before = cog_timestamp_ms();
    u64unix_ms after;

    discord_ratelimiter_set_global_timeout(rl, b, 300);
    after = cog_timestamp_ms();

    ASSERT(*rl->global_wait_tstamp >= before + 300);
    ASSERT(*rl->global_wait_tstamp <= after + 300);
    /* the offending bucket is also locked via discord_bucket_set_timeout */
    ASSERT_EQ(0L, b->remaining);
    ASSERT_EQ(NULL, b->busy_req);
    ASSERT(b->reset_tstamp >= before + 300);
    ASSERT(b->reset_tstamp <= after + 300);

    bare_client_cleanup(client);
    PASS();
}

TEST
populate_reset_date_branch(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    const time_t now_s = time(NULL);
    char raw[256], date[64];
    struct ua_info info;
    struct discord_bucket *b;
    u64unix_ms before, after;

    /* 'date' must be the last header: curl_getdate() reads from the value
     * offset to the end of the raw block */
    strftime(date, sizeof date, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&now_s));
    snprintf(raw, sizeof raw,
             "x-ratelimit-bucket: abcd\r\n"
             "x-ratelimit-remaining: 2\r\n"
             "x-ratelimit-reset: %lld.000\r\n"
             "date: %s\r\n",
             (long long)now_s + 2, date);
    info = make_info(raw);

    before = cog_timestamp_ms();
    discord_ratelimiter_build(rl, rl->null, ":1:channels:42", &info);
    after = cog_timestamp_ms();

    b = discord_bucket_get(rl, ":1:channels:42");
    ASSERT(b != rl->null);
    /* reset = now + (reset_epoch*1000 - (date_epoch*1000 + subsecond_ms));
     * with date == current second the delta is 2000ms minus up to a full
     * second of sub-second offset */
    ASSERT(b->reset_tstamp >= before + 1000);
    ASSERT(b->reset_tstamp <= after + 2000);

    bare_client_cleanup(client);
    PASS();
}

SUITE(remaining_and_reset)
{
    RUN_TEST(populate_remaining_zero);
    RUN_TEST(populate_remaining_default_is_one);
    RUN_TEST(set_timeout_locks_bucket);
    RUN_TEST(global_header_sets_global_tstamp);
    RUN_TEST(set_global_timeout);
    RUN_TEST(populate_reset_date_branch);
}

struct selector_record {
    struct discord_request *reqs[8];
    int count;
};

static void
selector_iter(void *data, struct discord_request *req)
{
    struct selector_record *rec = data;

    if (rec->count < (int)(sizeof(rec->reqs) / sizeof *rec->reqs))
        rec->reqs[rec->count] = req;
    rec->count++;
}

TEST
selector_dispatches_and_unselects(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b =
        discover(rl, ":1:channels:42",
                 "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 4\r\n");
    struct discord_request *req = fake_req(":1:channels:42");
    struct selector_record rec = { 0 };

    discord_bucket_insert(rl, b, req, false);
    discord_bucket_request_selector(rl, &rec, selector_iter);

    ASSERT_EQ(1, rec.count);
    ASSERT_EQ(req, rec.reqs[0]);
    ASSERT_EQ(req, b->busy_req);
    ASSERT(QUEUE_EMPTY(&b->queues.next));

    discord_bucket_request_unselect(rl, b, req);
    ASSERT_EQ(NULL, b->busy_req);
    ASSERT_EQ(NULL, req->b);
    ASSERT(QUEUE_EMPTY(&rl->queues.pending));

    bare_client_cleanup(client);
    free(req);
    PASS();
}

TEST
selector_skips_busy_bucket(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b =
        discover(rl, ":1:channels:42",
                 "x-ratelimit-bucket: abcd\r\nx-ratelimit-remaining: 4\r\n");
    struct discord_request *busy = fake_req(":1:channels:42");
    struct discord_request *queued = fake_req(":1:channels:42");
    struct selector_record rec = { 0 };

    b->busy_req = busy;
    discord_bucket_insert(rl, b, queued, false);
    discord_bucket_request_selector(rl, &rec, selector_iter);

    ASSERT_EQ(0, rec.count);
    ASSERT_EQ(busy, b->busy_req);
    /* bucket is re-queued for a later pass */
    ASSERT(!QUEUE_EMPTY(&rl->queues.pending));

    bare_client_cleanup(client);
    free(busy);
    free(queued);
    PASS();
}

TEST
selector_ratelimits_exhausted_bucket(void)
{
    struct discord *client = bare_client_init();
    struct discord_ratelimiter *rl = &client->rest.requestor.ratelimiter;
    struct discord_bucket *b =
        discover(rl, ":1:channels:42",
                 "x-ratelimit-bucket: abcd\r\n"
                 "x-ratelimit-remaining: 0\r\n"
                 "x-ratelimit-reset-after: 60\r\n");
    struct discord_request *req = fake_req(":1:channels:42");
    struct selector_record rec = { 0 };

    discord_bucket_insert(rl, b, req, false);
    discord_bucket_request_selector(rl, &rec, selector_iter);

    /* exhausted: nothing dispatched, bucket marked as waiting on a timer */
    ASSERT_EQ(0, rec.count);
    ASSERT_EQ(DISCORD_BUCKET_TIMEOUT, b->busy_req);
    ASSERT(!QUEUE_EMPTY(&rl->queues.pending));

    /* timer-driven wake is integration territory (C05); disarm the sentinel
     * so teardown doesn't dereference it */
    b->busy_req = NULL;

    bare_client_cleanup(client);
    free(req);
    PASS();
}

SUITE(selector)
{
    RUN_TEST(selector_dispatches_and_unselects);
    RUN_TEST(selector_skips_busy_bucket);
    RUN_TEST(selector_ratelimits_exhausted_bucket);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(build_key_suite);
    RUN_SUITE(buckets);
    RUN_SUITE(remaining_and_reset);
    RUN_SUITE(selector);
    GREATEST_MAIN_END();
}
