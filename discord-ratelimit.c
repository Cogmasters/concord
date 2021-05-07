#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> // for bucket synchronization

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


/* See:
https://discord.com/developers/docs/topics/rate-limits#rate-limits */


static struct discord_bucket*
bucket_init(char bucket_hash[])
{
  struct discord_bucket *new_bucket = calloc(1, sizeof *new_bucket);
  int ret = snprintf(new_bucket->hash, sizeof(new_bucket->hash), "%s", \
      bucket_hash);
  ASSERT_S(ret < sizeof(new_bucket->hash), "Out of bounds write attempt");

  if (pthread_mutex_init(&new_bucket->lock, NULL))
    ERR("Couldn't initialize pthread mutex");
  if (pthread_cond_init(&new_bucket->cond, NULL))
    ERR("Couldn't initialize pthread cond");

  return new_bucket;
}

static void
bucket_cleanup(struct discord_bucket *bucket) 
{
  pthread_mutex_destroy(&bucket->lock);
  pthread_cond_destroy(&bucket->cond);
  free(bucket);
}

static struct discord_bucket*
find_bucket(struct discord_adapter *adapter, char route[], char bucket_hash[])
{
  //attempt to match hash to client bucket hashes
  for (size_t i=0; i < adapter->ratelimit.num_buckets; ++i) {
    if (STREQ(bucket_hash, adapter->ratelimit.bucket_pool[i]->hash)) {
      return adapter->ratelimit.bucket_pool[i];
    }
  }

  //couldn't find match, create new bucket
  
  ++adapter->ratelimit.num_buckets; //increments client buckets

  adapter->ratelimit.bucket_pool = realloc(adapter->ratelimit.bucket_pool, \
                    adapter->ratelimit.num_buckets * sizeof(struct discord_bucket*));

  struct discord_bucket *new_bucket = bucket_init(bucket_hash);
  adapter->ratelimit.bucket_pool[adapter->ratelimit.num_buckets-1] = new_bucket;
  return new_bucket;
}

static void
route_free(void *route, void *noop) {
  free(route);
}

/* sleep cooldown for a connection within this bucket in milliseconds */
void
discord_bucket_try_cooldown(struct discord_bucket *bucket)
{
  if (!bucket) return; /* EARLY RETURN */

  pthread_mutex_lock(&bucket->lock);
  ++bucket->busy;

  // wait for a while if busy requests reach threshold
  /// @todo? add pthread_broadcast() to avoid zombie threads
  if (bucket->busy > bucket->remaining)
    pthread_cond_wait(&bucket->cond, &bucket->lock);
  if (bucket->remaining) {
    --bucket->remaining;
    pthread_mutex_unlock(&bucket->lock);
    return; /* EARLY RETURN */
  }

  int64_t delay_ms = (int64_t)(bucket->reset_tstamp - orka_timestamp_ms());
  if (delay_ms <= 0) { //no delay needed
    pthread_mutex_unlock(&bucket->lock);
    return; /* EARLY RETURN */
  }

  if (delay_ms > bucket->reset_after_ms) //don't delay in excess
    delay_ms = bucket->reset_after_ms;

  log_trace("\n\tRATELIMITING (reach bucket's connection threshold):\n\t"
          "\tBucket:\t\t%s\n\t"
          "\tWait for:\t %"PRId64" ms",
          bucket->hash, delay_ms);

  orka_sleep_ms(delay_ms); //sleep for delay amount (if any)

  pthread_mutex_unlock(&bucket->lock);
}

/* attempt to find a bucket associated with this route */
struct discord_bucket*
discord_bucket_try_get(struct discord_adapter *adapter, char route[]) {
  return avl_search(&adapter->ratelimit.routes, route);
}

/* attempt to parse rate limit's header fields to the bucket
 *  linked with the connection which was performed */
static void
parse_ratelimits(struct discord_bucket *bucket, struct ua_conn *conn)
{ 
  pthread_mutex_lock(&bucket->lock);
  --bucket->busy;

  if (UA_SUCCESS == ua_conn_get_status(conn)
      && bucket->update_tstamp < ua_conn_timestamp(conn)) 
  {
    bucket->update_tstamp = ua_conn_timestamp(conn);

    char *str; // fetch header value as string
    if ( (str = ua_respheader_value(conn, "x-ratelimit-reset")) )
      bucket->reset_tstamp = 1000 * strtod(str, NULL);
    if ( (str = ua_respheader_value(conn, "x-ratelimit-remaining")) )
      bucket->remaining =  strtol(str, NULL, 10);
    if ( (str = ua_respheader_value(conn, "x-ratelimit-reset-after")) )
      bucket->reset_after_ms = 1000 * strtod(str, NULL);
  }

  pthread_cond_signal(&bucket->cond);
  pthread_mutex_unlock(&bucket->lock);
}

/* Attempt to create a route between route and a client bucket by
 *  comparing the hash retrieved from header to hashes from existing
 *  client buckets.
 * If no match is found then we create a new client bucket */
static void
match_route(struct discord_adapter *adapter, char route[], struct ua_conn *conn)
{
  char *bucket_hash = ua_respheader_value(conn, "x-ratelimit-bucket");
  if (!bucket_hash) return; //no hash information in header

  // create new route that will link the route to a bucket
  struct discord_bucket *bucket = find_bucket(adapter, route, bucket_hash);
  //add new route to tree and update its bucket ratelimit fields
  avl_insert(&adapter->ratelimit.routes, strdup(route), bucket);
  parse_ratelimits(bucket, conn);
}

/* Attempt to build and/or updates bucket's rate limiting information.
 * In case that the route doesn't have a bucket for routing, no 
 *  clashing will occur */
void
discord_bucket_build(struct discord_adapter *adapter, struct discord_bucket *bucket, char route[], struct ua_conn *conn)
{
  /* no bucket means first time using this route.  attempt to 
   *  establish a route between it and a bucket via its unique hash 
   *  (will create a new bucket if it can't establish a route) */
  if (!bucket)
    match_route(adapter, route, conn);
  else // update the bucket rate limit values
    parse_ratelimits(bucket, conn);
}

/* works like strcmp, but will check if endpoing matches a major 
 *  parameters criteria too */
static int
routecmp(char route[], char node_route[])
{
  int ret = strcmp(route, node_route);
  if (0 == ret) return 0;

  /* check if fits major parameter criteria */
  if (strstr(route, "/channels/%"PRIu64)
   && strstr(node_route, "/channels/%"PRIu64))
    return 0;
  if (strstr(route, "/guilds/%"PRIu64)
   && strstr(node_route, "/guilds/%"PRIu64))
    return 0;
  if (strstr(route, "/webhook/%"PRIu64)
   && strstr(node_route, "/webhook/%"PRIu64))
    return 0;

  return ret; //couldn't find any match, return strcmp diff value
}

void
discord_buckets_init(struct discord_adapter *adapter) {
  avl_initialize(&adapter->ratelimit.routes, (avl_comparator_t)&routecmp, &free);
}

/* clean routes and buckets */
void
discord_buckets_cleanup(struct discord_adapter *adapter)
{ 
  avl_destroy(&adapter->ratelimit.routes, &route_free);
  for (size_t i=0; i < adapter->ratelimit.num_buckets; ++i) {
    bucket_cleanup(adapter->ratelimit.bucket_pool[i]);
  }
  free(adapter->ratelimit.bucket_pool);
}
