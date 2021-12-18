/* See:
https://discord.com/developers/docs/topics/rate-limits#rate-limits */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

#include "cee-utils.h"
#include "clock.h"

/* in case 'endpoint' has a major param, it will be written into 'buf' */
static const char *
_discord_bucket_get_route(const char endpoint[], char buf[32])
{
  /* determine which ratelimit group (aka bucket) a request belongs to
   * by checking its route.
   * see:  https://discord.com/developers/docs/topics/rate-limits */
  if (STRNEQ(endpoint, "/channels/", sizeof("/channels/") - 1)
      || STRNEQ(endpoint, "/guilds/", sizeof("/guilds/") - 1)
      || STRNEQ(endpoint, "/webhooks/", sizeof("/webhooks/") - 1))
  {
    /* safe to assume strchr() won't return NULL */
    char *start = 1 + strchr(1 + endpoint, '/');
    size_t len;

    /* get length of major parameter */
    for (len = 0; start[len] && start[len] != '/'; ++len)
      continue;

    /* copy snowflake id over to buf */
    memcpy(buf, start, len);
    buf[len] = '\0';

    return buf;
  }

  return endpoint;
}

struct discord_bucket *
discord_bucket_init(struct discord_adapter *adapter,
                    const char route[],
                    const struct sized_buffer *hash,
                    const long limit)
{
  struct discord_bucket *b;
  int ret;

  b = calloc(1, sizeof(struct discord_bucket));

  b->remaining = 1;
  b->limit = limit;

  ret = snprintf(b->route, sizeof(b->route), "%s", route);
  ASSERT_S(ret < sizeof(b->route), "Out of bounds write attempt");

  ret =
    snprintf(b->hash, sizeof(b->hash), "%.*s", (int)hash->size, hash->start);
  ASSERT_S(ret < sizeof(b->hash), "Out of bounds write attempt");

  if (pthread_mutex_init(&b->lock, NULL))
    ERR("Couldn't initialize pthread mutex");

  QUEUE_INIT(&b->waitq);
  QUEUE_INIT(&b->busyq);

  pthread_mutex_lock(&adapter->global->lock);
  HASH_ADD_STR(adapter->buckets, route, b);
  pthread_mutex_unlock(&adapter->global->lock);

  return b;
}

void
discord_buckets_cleanup(struct discord_adapter *adapter)
{
  struct discord_bucket *b, *b_tmp;

  /* cleanup buckets */
  HASH_ITER(hh, adapter->buckets, b, b_tmp)
  {
    HASH_DEL(adapter->buckets, b);
    pthread_mutex_destroy(&b->lock);
    free(b);
  }
}

static struct discord_bucket *
_discord_bucket_find(struct discord_adapter *adapter, const char route[])
{
  struct discord_bucket *b;

  /* attempt to find bucket with key 'route' */
  pthread_mutex_lock(&adapter->global->lock);
  HASH_FIND_STR(adapter->buckets, route, b);
  pthread_mutex_unlock(&adapter->global->lock);

  return b;
}

static struct discord_bucket *
_discord_bucket_get_match(struct discord_adapter *adapter,
                          const char endpoint[],
                          struct ua_info *info)
{
  char buf[32]; /* for reentrancy, stores 'major' parameter */
  const char *route = _discord_bucket_get_route(endpoint, buf);
  struct discord_bucket *b = _discord_bucket_find(adapter, route);

  /* create bucket if it doesn't exist yet */
  if (!b) {
    struct sized_buffer hash = ua_info_get_header(info, "x-ratelimit-bucket");

    if (!hash.size) {
      /* bucket not specified */
      b = adapter->b_null;
    }
    else {
      struct sized_buffer limit =
        ua_info_get_header(info, "x-ratelimit-limit");
      long _limit = limit.size ? strtol(limit.start, NULL, 10) : LONG_MAX;

      b = discord_bucket_init(adapter, route, &hash, _limit);
    }
  }

  return b;
}

u64_unix_ms_t
discord_adapter_get_global_wait(struct discord_adapter *adapter)
{
  u64_unix_ms_t global;

  pthread_rwlock_rdlock(&adapter->global->rwlock);
  global = adapter->global->wait_ms;
  pthread_rwlock_unlock(&adapter->global->rwlock);

  return global;
}

/* return ratelimit timeout timestamp for this bucket */
u64_unix_ms_t
discord_bucket_get_timeout(struct discord_adapter *adapter,
                           struct discord_bucket *b)
{
  u64_unix_ms_t global = discord_adapter_get_global_wait(adapter);
  u64_unix_ms_t reset = (b->remaining < 1) ? b->reset_tstamp : 0ULL;

  return (global > reset) ? global : reset;
}

int64_t
discord_bucket_get_wait(struct discord_adapter *adapter,
                        struct discord_bucket *b)
{
  struct discord *client = CLIENT(adapter, adapter);
  u64_unix_ms_t now = discord_timestamp(client);
  u64_unix_ms_t reset = discord_bucket_get_timeout(adapter, b);

  return (int64_t)(reset - now);
}

/* attempt to find a bucket associated with this route */
struct discord_bucket *
discord_bucket_get(struct discord_adapter *adapter, const char endpoint[])
{
  char buf[32]; /* for reentrancy, stores 'major' parameter */
  const char *route = _discord_bucket_get_route(endpoint, buf);
  struct discord_bucket *b = _discord_bucket_find(adapter, route);

  if (b) {
    logconf_trace(&adapter->conf,
                  "[%.4s] Found a bucket match for route '%s'!", b->hash,
                  b->route);

    return b;
  }

  logconf_trace(&adapter->conf,
                "[null] Couldn't match any discovered bucket to route '%s'",
                route);

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
  u64_unix_ms_t now = discord_timestamp(client);
  long _remaining;

  remaining = ua_info_get_header(info, "x-ratelimit-remaining");
  _remaining = remaining.size ? strtol(remaining.start, NULL, 10) : 1L;

  /* skip out of order responses */
  if (_remaining > b->remaining && now < b->reset_tstamp) {
    return;
  }

  b->remaining = _remaining;

  reset = ua_info_get_header(info, "x-ratelimit-reset");
  reset_after = ua_info_get_header(info, "x-ratelimit-reset-after");

  /* use X-Ratelimit-Reset-After if available, X-Ratelimit-Reset otherwise */
  if (reset_after.size) {
    struct sized_buffer global =
      ua_info_get_header(info, "x-ratelimit-global");
    u64_unix_ms_t reset_tstamp = now + 1000 * strtod(reset_after.start, NULL);

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
    u64_unix_ms_t server;
    /* the Discord time + request's elapsed time */
    u64_unix_ms_t offset;

    server = 1000 * curl_getdate(date.start, NULL);
    psnip_clock_wall_get_time(&ts);
    offset = server + ts.nanoseconds / 1000000;

    /* reset timestamp =
     *   (system time) + (diff between Discord's reset timestamp and offset) */
    b->reset_tstamp = now + (1000 * strtod(reset.start, NULL) - offset);
  }

  logconf_debug(
    &adapter->conf,
    "[%.4s] Remaining = %ld | Reset = %" PRIu64 " (%" PRId64 " ms)", b->hash,
    b->remaining, b->reset_tstamp, (int64_t)(b->reset_tstamp - now));
}

/* in case of asynchronous requests, check if successive requests with
 * null buckets can be matched to a new route */
static void
_discord_bucket_null_filter(struct discord_adapter *adapter,
                            struct discord_bucket *b,
                            const char endpoint[])
{
  struct discord_context *cxt;
  QUEUE queue;
  QUEUE *q;

  QUEUE_MOVE(&adapter->b_null->waitq, &queue);
  QUEUE_INIT(&adapter->b_null->waitq);

  while (!QUEUE_EMPTY(&queue)) {
    q = QUEUE_HEAD(&queue);
    QUEUE_REMOVE(q);

    cxt = QUEUE_DATA(q, struct discord_context, entry);
    if (0 == strcmp(cxt->endpoint, endpoint)) {
      QUEUE_INSERT_TAIL(&b->waitq, q);
      cxt->bucket = b;
    }
    else {
      QUEUE_INSERT_TAIL(&adapter->b_null->waitq, q);
    }
  }
}

/* attempt to create and/or update bucket's values */
void
discord_bucket_build(struct discord_adapter *adapter,
                     struct discord_bucket *b,
                     const char endpoint[],
                     struct ua_info *info)
{
  /* if new route, find out its bucket */
  if (b == adapter->b_null) {
    /* match bucket with hash (from discovered or create a new one) */
    b = _discord_bucket_get_match(adapter, endpoint, info);
    if (b == adapter->b_null) {
      logconf_debug(&adapter->conf, "[null] No bucket match for route '%s'",
                    endpoint);

      return;
    }

    logconf_debug(&adapter->conf, "[%.4s] Bucket match for route '%s'",
                  b->hash, b->route);

    _discord_bucket_null_filter(adapter, b, endpoint);
  }

  /* update bucket's values */
  _discord_bucket_populate(adapter, b, info);
}
