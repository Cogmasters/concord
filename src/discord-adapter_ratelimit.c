#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

#include "cog-utils.h"
#include "clock.h"

#define CHASH_VALUE_FIELD   bucket
#define CHASH_BUCKETS_FIELD routes
#include "chash.h"

/* chash heap-mode (auto-increase hashtable) */
#define RATELIMITER_TABLE_HEAP   1
#define RATELIMITER_TABLE_BUCKET struct _discord_route
#define RATELIMITER_TABLE_FREE_KEY(_key)
#define RATELIMITER_TABLE_HASH(_key, _hash)  chash_string_hash(_key, _hash)
#define RATELIMITER_TABLE_FREE_VALUE(_value) _discord_bucket_cleanup(_value)
#define RATELIMITER_TABLE_COMPARE(_cmp_a, _cmp_b)                             \
    chash_string_compare(_cmp_a, _cmp_b)
#define RATELIMITER_TABLE_INIT(route, _key, _value)                           \
    memcpy(route.key, _key, sizeof(route.key));                               \
    route.bucket = _value

struct _discord_route {
    /** key formed from a request's route */
    char key[DISCORD_ROUTE_LEN];
    /** this route's bucket match */
    struct discord_bucket *bucket;
    /** the route state in the hashtable (see chash.h 'State enums') */
    int state;
};

static void
_discord_bucket_cleanup(struct discord_bucket *b)
{
    pthread_mutex_destroy(&b->lock);
    free(b);
}

#define KEY_PUSH(key, len, ...)                                               \
    do {                                                                      \
        *len += snprintf(key + *len, DISCORD_ROUTE_LEN - (size_t)*len,        \
                         ":" __VA_ARGS__);                                    \
        ASSERT_NOT_OOB(*len, DISCORD_ROUTE_LEN);                              \
    } while (0)

/* determine which ratelimit group a request belongs to by generating its key.
 * see: https://discord.com/developers/docs/topics/rate-limits */
void
discord_ratelimiter_build_key(enum http_method method,
                              char key[DISCORD_ROUTE_LEN],
                              const char endpoint_fmt[],
                              va_list args)
{
    /* generated key length */
    int keylen = 0;
    /* split endpoint sections */
    const char *curr = endpoint_fmt, *prev = "";
    size_t currlen = 0;

    KEY_PUSH(key, &keylen, "%d", method);
    do {
        u64snowflake id_arg = 0ULL;
        size_t i;

        curr += 1 + currlen;
        currlen = strcspn(curr, "/");

        /* reactions and sub-routes share the same bucket */
        if (0 == strncmp(prev, "reactions", 9)) break;

        /* consume variadic arguments */
        for (i = 0; i < currlen; ++i) {
            if ('%' == curr[i]) {
                const char *type = &curr[i + 1];

                switch (*type) {
                default:
                    VASSERT_S(0 == strncmp(type, PRIu64, sizeof(PRIu64) - 1),
                              "Internal error: Missing check for '%%%s'",
                              type);

                    id_arg = va_arg(args, u64snowflake);
                    break;
                case 's':
                    (void)va_arg(args, char *);
                    break;
                case 'd':
                    (void)va_arg(args, int);
                    break;
                }
            }
        }

        /* push section to key's string, in case of a major parameter the
         * literal ID will be pushed */
        if (0 == strncmp(curr, "%" PRIu64, currlen)
            && (0 == strncmp(prev, "channels", 8)
                || 0 == strncmp(prev, "guilds", 6)))
        {
            KEY_PUSH(key, &keylen, "%" PRIu64, id_arg);
        }
        else {
            KEY_PUSH(key, &keylen, "%.*s", (int)currlen, curr);
        }

        prev = curr;

    } while (curr[currlen] != '\0');
}

#undef KEY_PUSH

/* initialize bucket and assign it to ratelimiter hashtable */
static struct discord_bucket *
_discord_bucket_init(struct discord_ratelimiter *rl,
                     const char key[],
                     const struct sized_buffer *hash,
                     const long limit)
{
    struct discord_bucket *b = calloc(1, sizeof *b);
    int len = snprintf(b->hash, sizeof(b->hash), "%.*s", (int)hash->size,
                       hash->start);

    ASSERT_NOT_OOB(len, sizeof(b->hash));

    b->remaining = 1;
    b->limit = limit;

    if (pthread_mutex_init(&b->lock, NULL))
        ERR("Couldn't initialize pthread mutex");

    QUEUE_INIT(&b->waitq);

    pthread_mutex_lock(&rl->global.lock);
    chash_assign(rl, key, b, RATELIMITER_TABLE);
    pthread_mutex_unlock(&rl->global.lock);

    return b;
}

struct discord_ratelimiter *
discord_ratelimiter_init(struct logconf *conf)
{
    const struct sized_buffer keynull = { "null", 4 }, keymiss = { "miss", 4 };
    struct discord_ratelimiter *rl = chash_init(rl, RATELIMITER_TABLE);

    logconf_branch(&rl->conf, conf, "DISCORD_RATELIMIT");

    /* global ratelimiting resources */
    rl->global.wait_ms = 0;
    if (pthread_rwlock_init(&rl->global.rwlock, NULL))
        ERR("Couldn't initialize pthread rwlock");
    if (pthread_mutex_init(&rl->global.lock, NULL))
        ERR("Couldn't initialize pthread mutex");

    /* initialize 'singleton' buckets */
    rl->null = _discord_bucket_init(rl, "null", &keynull, 1L);
    rl->miss = _discord_bucket_init(rl, "miss", &keymiss, LONG_MAX);

    return rl;
}

void
discord_ratelimiter_cleanup(struct discord_ratelimiter *rl)
{
    pthread_rwlock_destroy(&rl->global.rwlock);
    pthread_mutex_destroy(&rl->global.lock);
    chash_free(rl, RATELIMITER_TABLE);
}

void
discord_ratelimiter_foreach(struct discord_ratelimiter *rl,
                            struct discord_adapter *adapter,
                            void (*iter)(struct discord_adapter *adapter,
                                         struct discord_bucket *b))
{
    struct _discord_route *r;
    int i;

    pthread_mutex_lock(&rl->global.lock);
    for (i = 0; i < rl->capacity; ++i) {
        r = rl->routes + i;
        if (CHASH_FILLED == r->state) (*iter)(adapter, r->bucket);
    }
    pthread_mutex_unlock(&rl->global.lock);
}

static struct discord_bucket *
_discord_bucket_find(struct discord_ratelimiter *rl, const char key[])
{
    struct discord_bucket *b = NULL;
    int ret;

    pthread_mutex_lock(&rl->global.lock);
    ret = chash_contains(rl, key, ret, RATELIMITER_TABLE);
    if (ret) {
        b = chash_lookup(rl, key, b, RATELIMITER_TABLE);
    }
    pthread_mutex_unlock(&rl->global.lock);

    return b;
}

u64unix_ms
discord_ratelimiter_get_global_wait(struct discord_ratelimiter *rl)
{
    u64unix_ms global;

    pthread_rwlock_rdlock(&rl->global.rwlock);
    global = rl->global.wait_ms;
    pthread_rwlock_unlock(&rl->global.rwlock);

    return global;
}

/* return ratelimit timeout timestamp for this bucket */
u64unix_ms
discord_bucket_get_timeout(struct discord_ratelimiter *rl,
                           struct discord_bucket *b)
{
    u64unix_ms global = discord_ratelimiter_get_global_wait(rl),
               reset = (b->remaining < 1) ? b->reset_tstamp : 0ULL;

    return (global > reset) ? global : reset;
}

void
discord_bucket_try_sleep(struct discord_ratelimiter *rl,
                         struct discord_bucket *b)
{
    /* sleep_ms := reset timestamp - current timestamp */
    const int64_t sleep_ms =
        (int64_t)(discord_bucket_get_timeout(rl, b) - cog_timestamp_ms());

    if (sleep_ms > 0) {
        /* block thread's runtime for delay amount */
        logconf_info(&rl->conf, "[%.4s] RATELIMITING (wait %" PRId64 " ms)",
                     b->hash, sleep_ms);
        cog_sleep_ms(sleep_ms);
    }
}

static void
_discord_bucket_wake_cb(struct discord *client, struct discord_timer *timer)
{
    (void)client;
    struct discord_bucket *b = timer->data;

    b->busy = NULL; /* bucket is no longer busy */
    b->remaining = 1;
}

void
discord_bucket_try_timeout(struct discord *client, struct discord_bucket *b)
{
    const int64_t delay_ms = (int64_t)(b->reset_tstamp - cog_timestamp_ms());

    b->busy = DISCORD_BUCKET_TIMEOUT;

    discord_internal_timer(client, &_discord_bucket_wake_cb, b, delay_ms);

    logconf_info(&client->adapter.ratelimiter->conf,
                 "[%.4s] RATELIMITING (wait %" PRId64 " ms)", b->hash,
                 delay_ms);
}

/* attempt to find a bucket associated key */
struct discord_bucket *
discord_bucket_get(struct discord_ratelimiter *rl, const char key[])
{
    struct discord_bucket *b;

    if (NULL != (b = _discord_bucket_find(rl, key))) {
        logconf_trace(&rl->conf, "[%.4s] Found a bucket match for '%s'!",
                      b->hash, key);

        return b;
    }

    logconf_trace(&rl->conf, "[null] Couldn't match known buckets to '%s'",
                  key);

    return rl->null;
}

static struct discord_bucket *
_discord_ratelimiter_get_match(struct discord_ratelimiter *rl,
                               const char key[],
                               struct ua_info *info)
{
    struct discord_bucket *b;

    /* create bucket if it doesn't exist yet */
    if (NULL == (b = _discord_bucket_find(rl, key))) {
        struct sized_buffer hash =
            ua_info_get_header(info, "x-ratelimit-bucket");

        if (!hash.size) { /* bucket is not part of a ratelimiting group */
            b = rl->miss;
        }
        else {
            struct sized_buffer limit =
                ua_info_get_header(info, "x-ratelimit-limit");
            long _limit =
                limit.size ? strtol(limit.start, NULL, 10) : LONG_MAX;

            b = _discord_bucket_init(rl, key, &hash, _limit);
        }
    }

    logconf_debug(&rl->conf, "[%.4s] Match '%s' to bucket", b->hash, key);

    return b;
}

/* attempt to fill bucket's values with response header fields */
static void
_discord_bucket_populate(struct discord_ratelimiter *rl,
                         struct discord_bucket *b,
                         struct ua_info *info)
{
    struct sized_buffer remaining =
                            ua_info_get_header(info, "x-ratelimit-remaining"),
                        reset = ua_info_get_header(info, "x-ratelimit-reset"),
                        reset_after = ua_info_get_header(
                            info, "x-ratelimit-reset-after");
    u64unix_ms now = cog_timestamp_ms();

    b->remaining = remaining.size ? strtol(remaining.start, NULL, 10) : 1L;

    /* use X-Ratelimit-Reset-After if available, X-Ratelimit-Reset otherwise */
    if (reset_after.size) {
        struct sized_buffer global =
            ua_info_get_header(info, "x-ratelimit-global");
        u64unix_ms reset_tstamp =
            now + (u64unix_ms)(1000 * strtod(reset_after.start, NULL));

        if (global.size) {
            /* lock all buckets */
            pthread_rwlock_wrlock(&rl->global.rwlock);
            rl->global.wait_ms = reset_tstamp;
            pthread_rwlock_unlock(&rl->global.rwlock);
        }
        else {
            /* lock single bucket, timeout at discord_adapter_run() */
            b->reset_tstamp = reset_tstamp;
        }
    }
    else if (reset.size) {
        struct sized_buffer date = ua_info_get_header(info, "date");
        /* get approximate elapsed time since request */
        struct PsnipClockTimespec ts;
        /* the Discord time in milliseconds */
        u64unix_ms server;
        /* the Discord time + request's elapsed time */
        u64unix_ms offset;

        server = (u64unix_ms)(1000 * curl_getdate(date.start, NULL));
        psnip_clock_wall_get_time(&ts);
        offset = server + ts.nanoseconds / 1000000;

        /* reset timestamp =
         *   (system time)
         *      + (diff between Discord's reset timestamp and offset)
         */
        b->reset_tstamp =
            now + ((u64unix_ms)(1000 * strtod(reset.start, NULL)) - offset);
    }

    logconf_debug(&rl->conf, "[%.4s] Remaining = %ld | Reset = %" PRIu64,
                  b->hash, b->remaining, b->reset_tstamp);
}

/* in case of asynchronous requests, check if successive requests made from a
 * `null` singleton bucket can be matched to another bucket */
static void
_discord_ratelimiter_null_filter(struct discord_ratelimiter *rl,
                                 struct discord_bucket *b,
                                 const char key[])
{
    QUEUE(struct discord_context) queue, *qelem;
    struct discord_context *cxt;

    QUEUE_MOVE(&rl->null->waitq, &queue);
    QUEUE_INIT(&rl->null->waitq);

    while (!QUEUE_EMPTY(&queue)) {
        qelem = QUEUE_HEAD(&queue);
        QUEUE_REMOVE(qelem);

        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
        if (0 == strcmp(cxt->key, key)) {
            QUEUE_INSERT_TAIL(&b->waitq, qelem);
            cxt->b = b;
        }
        else {
            QUEUE_INSERT_TAIL(&rl->null->waitq, qelem);
        }
    }
}

/* attempt to create and/or update bucket's values */
void
discord_ratelimiter_build(struct discord_ratelimiter *rl,
                          struct discord_bucket *b,
                          const char key[],
                          struct ua_info *info)
{
    /* try to match to existing, or create new bucket */
    if (b == rl->null) {
        b = _discord_ratelimiter_get_match(rl, key, info);
        _discord_ratelimiter_null_filter(rl, b, key);
    }
    /* populate bucket with response header values */
    _discord_bucket_populate(rl, b, info);
}
