/* See:
https://discord.com/developers/docs/topics/rate-limits#rate-limits */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"

#include "cee-utils.h"
#include "clock.h"

static struct discord_bucket *
bucket_init(struct sized_buffer *hash, const char route[])
{
  struct discord_bucket *new_bucket = calloc(1, sizeof *new_bucket);
  new_bucket->remaining = 1;
  int ret = snprintf(new_bucket->hash, sizeof(new_bucket->hash), "%.*s",
                     (int)hash->size, hash->start);
  ASSERT_S(ret < sizeof(new_bucket->hash), "Out of bounds write attempt");
  ret = snprintf(new_bucket->route, sizeof(new_bucket->route), "%s", route);
  ASSERT_S(ret < sizeof(new_bucket->route), "Out of bounds write attempt");
  if (pthread_mutex_init(&new_bucket->lock, NULL))
    ERR("Couldn't initialize pthread mutex");
  return new_bucket;
}

static void
bucket_cleanup(struct discord_bucket *bucket)
{
  pthread_mutex_destroy(&bucket->lock);
  free(bucket);
}

/* clean routes and buckets */
void
discord_buckets_cleanup(struct discord_adapter *adapter)
{
  struct discord_bucket *bucket, *tmp;
  HASH_ITER(hh, adapter->ratelimit->buckets, bucket, tmp)
  {
    HASH_DEL(adapter->ratelimit->buckets, bucket);
    bucket_cleanup(bucket);
  }
}

/* return ratelimit cooldown for this bucket (in milliseconds) */
long
discord_bucket_get_cooldown(struct discord_adapter *adapter,
                            struct discord_bucket *bucket)
{
  if (!bucket) return 0L;

  u64_unix_ms_t now_tstamp = cee_timestamp_ms(), delay_ms = 0L;

  if (bucket->remaining < 1 && bucket->reset_tstamp > now_tstamp) {
    delay_ms = bucket->reset_tstamp - now_tstamp;
  }
  --bucket->remaining;
  /* @todo check for global ratelimits */
  return delay_ms;
}

/* attempt to find a bucket associated with this route */
struct discord_bucket *
discord_bucket_try_get(struct discord_adapter *adapter, const char route[])
{
  logconf_debug(&adapter->ratelimit->conf,
                "[?] Attempt to find matching bucket for route '%s'", route);

  struct discord_bucket *bucket;
  pthread_mutex_lock(&adapter->ratelimit->lock);
  HASH_FIND_STR(adapter->ratelimit->buckets, route, bucket);
  pthread_mutex_unlock(&adapter->ratelimit->lock);

  if (!bucket)
    logconf_debug(&adapter->ratelimit->conf,
                  "[?] Couldn't match bucket to route '%s', will attempt to "
                  "create a new one",
                  route);
  else
    logconf_debug(&adapter->ratelimit->conf, "[%.4s] Found a match!",
                  bucket->hash);

  return bucket;
}

/* attempt to parse rate limit's header fields to the bucket
 *  linked with the connection which was performed */
static void
parse_ratelimits(struct discord_adapter *adapter,
                 struct discord_bucket *bucket,
                 ORCAcode code,
                 struct ua_info *info)
{
  if (code != ORCA_OK) {
    logconf_debug(&adapter->ratelimit->conf, "[%.4s] Request failed",
                  bucket->hash);
  }
  else if (bucket->update_tstamp <= info->req_tstamp) {
    /* fetch header individual fields */
    struct sized_buffer reset = ua_info_header_get(info, "x-ratelimit-reset"),
                        remaining =
                          ua_info_header_get(info, "x-ratelimit-remaining"),
                        reset_after =
                          ua_info_header_get(info, "x-ratelimit-reset-after");

    bucket->remaining = remaining.size ? strtol(remaining.start, NULL, 10) : 1;

    /* use the more accurate X-Ratelimit-Reset header if available,
     * otherwise use X-Ratelimit-Reset-After */
    if (reset.size) {
      bucket->reset_tstamp = 1000 * strtod(reset.start, NULL);
    }
    else if (reset_after.size) {
      /* calculate the reset time with Discord's date header */
      struct sized_buffer date = ua_info_header_get(info, "date");
      u64_unix_ms_t now_tstamp;

      if (date.size) {
        struct PsnipClockTimespec ts;
        psnip_clock_wall_get_time(&ts);
        now_tstamp =
          1000 * curl_getdate(date.start, NULL) + ts.nanoseconds / 1000000;
      }
      else {
        /* rely on system time to fetch current timestamp */
        now_tstamp = cee_timestamp_ms();
      }
      bucket->reset_tstamp =
        now_tstamp + 1000 * strtod(reset_after.start, NULL);
    }

    logconf_info(&adapter->ratelimit->conf,
                 "[%.4s] Reset = %" PRIu64 " ; Remaining = %d", bucket->hash,
                 bucket->reset_tstamp, bucket->remaining);

    bucket->update_tstamp = info->req_tstamp;
  }
}

/* Attempt to find/link a route between route and a client bucket by
 *  comparing the hash retrieved from response header with discovered
 *  buckets hashes
 * If no match is found then a new bucket is created and linked to the
 *  route*/
static void
match_route(struct discord_adapter *adapter,
            const char route[],
            ORCAcode code,
            struct ua_info *info)
{
  struct sized_buffer hash = ua_info_header_get(info, "x-ratelimit-bucket");
  if (!hash.size) {
    logconf_debug(&adapter->ratelimit->conf,
                  "[?] Missing bucket-hash from response header,"
                  " route '%s' can't be assigned to a bucket",
                  route);
    return;
  }

  struct discord_bucket *bucket = NULL, *iter, *tmp;
  /*attempt to match hash to client bucket hashes */
  HASH_ITER(hh, adapter->ratelimit->buckets, iter, tmp)
  {
    if (STRNEQ(iter->hash, hash.start, hash.size)) {
      bucket = iter;
      break;
    }
  }
  if (!bucket) bucket = bucket_init(&hash, route);

  /*assign new route and update bucket ratelimit fields */
  logconf_debug(&adapter->ratelimit->conf,
                "[%.4s] Assign new route '%s' to bucket", bucket->hash,
                bucket->route);
  HASH_ADD_STR(adapter->ratelimit->buckets, route, bucket);
  parse_ratelimits(adapter, bucket, code, info);
}

/* Attempt to build and/or update bucket's rate limiting information. */
void
discord_bucket_build(struct discord_adapter *adapter,
                     struct discord_bucket *bucket,
                     const char route[],
                     ORCAcode code,
                     struct ua_info *info)
{
  /* no bucket means first time using this route.  attempt to
   *  establish a route between it and a bucket via its unique hash
   *  (will create a new bucket if it can't establish a route) */
  if (!bucket)
    match_route(adapter, route, code, info);
  else /* update the bucket rate limit values */
    parse_ratelimits(adapter, bucket, code, info);
}
