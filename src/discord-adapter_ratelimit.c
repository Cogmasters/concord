#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

#include "cog-utils.h"
#include "clock.h"

struct _discord_route {
    /** route associated with bucket */
    char route[DISCORD_ROUTE_LEN];
    /** this route's bucket */
    struct discord_bucket *bucket;
    /** makes this structure hashable */
    UT_hash_handle hh;
};

static void
_discord_route_init(struct discord_adapter *adapter,
                    const char route[DISCORD_ROUTE_LEN],
                    struct discord_bucket *b)
{
    struct _discord_route *r;
    int len;

    r = calloc(1, sizeof(struct _discord_route));

    r->bucket = b;

    len = snprintf(r->route, sizeof(r->route), "%s", route);
    ASSERT_NOT_OOB(len, sizeof(b->hash));

    pthread_mutex_lock(&adapter->global->lock);
    HASH_ADD(hh, adapter->routes, route, len, r);
    pthread_mutex_unlock(&adapter->global->lock);
}

#define ROUTE_PUSH(route, len, ...)                                           \
    do {                                                                      \
        *len += snprintf(route + *len, DISCORD_ROUTE_LEN - (size_t)*len,      \
                         ":" __VA_ARGS__);                                    \
        ASSERT_NOT_OOB(*len, DISCORD_ROUTE_LEN);                              \
    } while (0)

/* determine which ratelimit group (aka bucket) a request belongs to
 * by checking its route.
 * see:  https://discord.com/developers/docs/topics/rate-limits */
void
discord_bucket_get_route(enum http_method method,
                         char route[DISCORD_ROUTE_LEN],
                         const char endpoint_fmt[],
                         va_list args)
{
    /* generated route length */
    int routelen = 0;
    /* split endpoint sections */
    const char *curr = endpoint_fmt, *prev = "";
    size_t currlen = 0;

    ROUTE_PUSH(route, &routelen, "%d", method);
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

        /* push section to route's string, in case of a major parameter the
         * literal ID will be pushed */
        if (0 == strncmp(curr, "%" PRIu64, currlen)
            && (0 == strncmp(prev, "channels", 8)
                || 0 == strncmp(prev, "guilds", 6)))
        {
            ROUTE_PUSH(route, &routelen, "%" PRIu64, id_arg);
        }
        else {
            ROUTE_PUSH(route, &routelen, "%.*s", (int)currlen, curr);
        }

        prev = curr;

    } while (curr[currlen] != '\0');
}

#undef ROUTE_PUSH

struct discord_bucket *
discord_bucket_init(struct discord_adapter *adapter,
                    const struct sized_buffer *hash,
                    const long limit)
{
    struct discord_bucket *b;
    int len;

    b = calloc(1, sizeof(struct discord_bucket));

    b->remaining = 1;
    b->limit = limit;

    len = snprintf(b->hash, sizeof(b->hash), "%.*s", (int)hash->size,
                   hash->start);
    ASSERT_NOT_OOB(len, sizeof(b->hash));

    if (pthread_mutex_init(&b->lock, NULL))
        ERR("Couldn't initialize pthread mutex");

    QUEUE_INIT(&b->waitq);
    QUEUE_INIT(&b->busyq);

    pthread_mutex_lock(&adapter->global->lock);
    HASH_ADD(hh, adapter->buckets, hash, len, b);
    pthread_mutex_unlock(&adapter->global->lock);

    return b;
}

void
discord_buckets_cleanup(struct discord_adapter *adapter)
{
    struct _discord_route *r, *r_tmp;
    struct discord_bucket *b, *b_tmp;

    /* cleanup routes */
    HASH_ITER(hh, adapter->routes, r, r_tmp)
    {
        HASH_DEL(adapter->routes, r);
        free(r);
    }
    /* cleanup buckets */
    HASH_ITER(hh, adapter->buckets, b, b_tmp)
    {
        HASH_DEL(adapter->buckets, b);
        pthread_mutex_destroy(&b->lock);
        free(b);
    }
}

static struct discord_bucket *
_discord_bucket_find(struct discord_adapter *adapter,
                     const char route[DISCORD_ROUTE_LEN])
{
    struct _discord_route *r;

    /* attempt to find bucket from 'route' */
    pthread_mutex_lock(&adapter->global->lock);
    HASH_FIND_STR(adapter->routes, route, r);
    pthread_mutex_unlock(&adapter->global->lock);

    return r ? r->bucket : NULL;
}

static struct discord_bucket *
_discord_bucket_get_match(struct discord_adapter *adapter,
                          const char route[DISCORD_ROUTE_LEN],
                          struct ua_info *info)
{
    struct discord_bucket *b;

    /* create bucket if it doesn't exist yet */
    if (NULL == (b = _discord_bucket_find(adapter, route))) {
        struct sized_buffer hash =
            ua_info_get_header(info, "x-ratelimit-bucket");

        if (!hash.size) {
            /* no bucket given for route */
            b = adapter->b_miss;
        }
        else {
            struct sized_buffer limit =
                ua_info_get_header(info, "x-ratelimit-limit");
            long _limit =
                limit.size ? strtol(limit.start, NULL, 10) : LONG_MAX;

            b = discord_bucket_init(adapter, &hash, _limit);
        }

        _discord_route_init(adapter, route, b);
    }

    logconf_debug(&adapter->conf, "[%.4s] Match '%s' to bucket", b->hash,
                  route);

    return b;
}

u64unix_ms
discord_adapter_get_global_wait(struct discord_adapter *adapter)
{
    u64unix_ms global;

    pthread_rwlock_rdlock(&adapter->global->rwlock);
    global = adapter->global->wait_ms;
    pthread_rwlock_unlock(&adapter->global->rwlock);

    return global;
}

/* return ratelimit timeout timestamp for this bucket */
u64unix_ms
discord_bucket_get_timeout(struct discord_adapter *adapter,
                           struct discord_bucket *b)
{
    u64unix_ms global = discord_adapter_get_global_wait(adapter);
    u64unix_ms reset = (b->remaining < 1) ? b->reset_tstamp : 0ULL;

    return (global > reset) ? global : reset;
}

int64_t
discord_bucket_get_wait(struct discord_adapter *adapter,
                        struct discord_bucket *b)
{
    struct discord *client = CLIENT(adapter, adapter);
    u64unix_ms now = discord_timestamp(client);
    u64unix_ms reset = discord_bucket_get_timeout(adapter, b);

    return (int64_t)(reset - now);
}

/* attempt to find a bucket associated with this route */
struct discord_bucket *
discord_bucket_get(struct discord_adapter *adapter,
                   const char route[DISCORD_ROUTE_LEN])
{
    struct discord_bucket *b;

    if ((b = _discord_bucket_find(adapter, route)) != NULL) {
        logconf_trace(&adapter->conf, "[%.4s] Found a bucket match for '%s'!",
                      b->hash, route);

        return b;
    }

    logconf_trace(&adapter->conf,
                  "[null] Couldn't match known buckets to '%s'", route);

    return adapter->b_null;
}

/* attempt to parse rate limit's header fields to the bucket
 *  linked with the connection which was performed */
static void
_discord_bucket_populate(struct discord_adapter *adapter,
                         struct discord_bucket *b,
                         struct ua_info *info)
{
    struct sized_buffer remaining, reset, reset_after;
    struct discord *client = CLIENT(adapter, adapter);
    u64unix_ms now = discord_timestamp(client);
    long _remaining;

    remaining = ua_info_get_header(info, "x-ratelimit-remaining");
    _remaining = remaining.size ? strtol(remaining.start, NULL, 10) : 1L;

    /* skip out of order responses */
    if (_remaining > b->remaining && now < b->reset_tstamp) return;

    b->remaining = _remaining;

    reset = ua_info_get_header(info, "x-ratelimit-reset");
    reset_after = ua_info_get_header(info, "x-ratelimit-reset-after");

    /* use X-Ratelimit-Reset-After if available, X-Ratelimit-Reset otherwise */
    if (reset_after.size) {
        struct sized_buffer global =
            ua_info_get_header(info, "x-ratelimit-global");
        u64unix_ms reset_tstamp =
            now + (u64unix_ms)(1000 * strtod(reset_after.start, NULL));

        if (global.size) {
            /* lock all buckets */
            pthread_rwlock_wrlock(&adapter->global->rwlock);
            adapter->global->wait_ms = reset_tstamp;
            pthread_rwlock_unlock(&adapter->global->rwlock);
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
         *   (system time) + (diff between Discord's reset timestamp and
         * offset) */
        b->reset_tstamp =
            now + ((u64unix_ms)(1000 * strtod(reset.start, NULL)) - offset);
    }

    logconf_debug(&adapter->conf, "[%.4s] Remaining = %ld | Reset = %" PRIu64,
                  b->hash, b->remaining, b->reset_tstamp);
}

/* in case of asynchronous requests, check if successive requests with
 * null buckets can be matched to a new route */
static void
_discord_bucket_null_filter(struct discord_adapter *adapter,
                            struct discord_bucket *b,
                            const char route[DISCORD_ROUTE_LEN])
{
    struct discord_context *cxt;
    QUEUE queue;
    QUEUE *qelem;

    QUEUE_MOVE(&adapter->b_null->waitq, &queue);
    QUEUE_INIT(&adapter->b_null->waitq);

    while (!QUEUE_EMPTY(&queue)) {
        qelem = QUEUE_HEAD(&queue);
        QUEUE_REMOVE(qelem);

        cxt = QUEUE_DATA(qelem, struct discord_context, entry);
        if (0 == strcmp(cxt->route, route)) {
            QUEUE_INSERT_TAIL(&b->waitq, qelem);
            cxt->bucket = b;
        }
        else {
            QUEUE_INSERT_TAIL(&adapter->b_null->waitq, qelem);
        }
    }
}

/* attempt to create and/or update bucket's values */
void
discord_bucket_build(struct discord_adapter *adapter,
                     struct discord_bucket *b,
                     const char route[DISCORD_ROUTE_LEN],
                     struct ua_info *info)
{
    /* match new route to existing or new bucket */
    if (b == adapter->b_null) {
        b = _discord_bucket_get_match(adapter, route, info);
        _discord_bucket_null_filter(adapter, b, route);
    }
    /* update bucket's values with header values */
    _discord_bucket_populate(adapter, b, info);
}
