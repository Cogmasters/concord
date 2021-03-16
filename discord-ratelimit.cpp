#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h> // for POSIX tree (tfind, tsearch, tdestroy)
#include <pthread.h> // for bucket synchronization

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace user_agent {
namespace bucket {

/* See:
https://discord.com/developers/docs/topics/rate-limits#rate-limits */


/* this struct contains the bucket's route string and a pointer 
 *  to the bucket assigned to this route. it will be stored and 
 *  retrieved by search.h tree functions */
struct _route_s {
  char *str; //bucket route (endpoint, major parameter)
  dati *p_bucket; //bucket assigned to this route
};

/* sleep cooldown for a connection within this bucket in milliseconds */
void
try_cooldown(dati *bucket)
{
  if (NULL == bucket) return; /* EARLY RETURN */

  pthread_mutex_lock(&bucket->lock);

  if (bucket->remaining) { // no cooldown needed
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

  D_PRINT("RATELIMITING (reach bucket's connection threshold):\n\t"
          "\tBucket:\t\t%s\n\t"
          "\tWait for:\t %" PRId64 " ms",
          bucket->hash, delay_ms);

  orka_sleep_ms(delay_ms); //sleep for delay amount (if any)

  pthread_mutex_unlock(&bucket->lock);
}

/* works like strcmp, but will check if endpoing matches a major 
 *  parameters criteria too */
static int
routecmp(const void *p_route1, const void *p_route2)
{
  struct _route_s *route1 = (struct _route_s*)p_route1;
  struct _route_s *route2 = (struct _route_s*)p_route2;

  int ret = strcmp(route1->str, route2->str);
  if (0 == ret) return 0;

  /* check if fits major parameter criteria */
  if (strstr(route1->str, "/channels/%llu")
   && strstr(route2->str, "/channels/%llu"))
  {
    return 0;
  }
  if (strstr(route1->str, "/guilds/%llu")
   && strstr(route2->str, "/guilds/%llu"))
  {
    return 0;
  }
  if (strstr(route1->str, "/webhook/%llu")
   && strstr(route2->str, "/webhook/%llu"))
  {
    return 0;
  }

  return ret; //couldn't find any match, return strcmp diff value
}

/* attempt to find a bucket associated with this endpoint */
dati*
try_get(user_agent::dati *ua, char endpoint[])
{
  struct _route_s search_route = {
    .str = endpoint
  };
  struct _route_s **p_route;
  p_route = (struct _route_s**)tfind(&search_route, &ua->ratelimit.routes_root, &routecmp);

  //if found matching route, return its bucket, otherwise NULL
  return (p_route) ? (*p_route)->p_bucket : NULL;
}

/* attempt to parse rate limit's header fields to the bucket
 *  linked with the connection which was performed */
static void
parse_ratelimits(dati *bucket, struct ua_conn_s *conn)
{ 
  if (bucket->update_tstamp > conn->perform_tstamp)
    return; /* EARLY RETURN */
  bucket->update_tstamp = conn->perform_tstamp;

  char *str; // fetch header value as string
  if ( (str = ua_respheader_value(conn, "x-ratelimit-reset")) )
    bucket->reset_tstamp = 1000 * strtod(str, NULL);
  if ( (str = ua_respheader_value(conn, "x-ratelimit-remaining")) )
    bucket->remaining =  strtol(str, NULL, 10);
  if ( (str = ua_respheader_value(conn, "x-ratelimit-reset-after")) )
    bucket->reset_after_ms = 1000 * strtod(str, NULL);
}

static dati*
bucket_init(char bucket_hash[])
{
  dati *new_bucket = (dati*) calloc(1, sizeof *new_bucket);
  new_bucket->hash = strdup(bucket_hash);
  if (pthread_mutex_init(&new_bucket->lock, NULL))
    ERR("Couldn't initialize pthread mutex");
  return new_bucket;
}

static void
bucket_cleanup(dati *bucket) 
{
  free(bucket->hash);
  pthread_mutex_destroy(&bucket->lock);
  free(bucket);
}

/* Attempt to create a route between endpoint and a client bucket by
 *  comparing the hash retrieved from header to hashes from existing
 *  client buckets.
 * If no match is found then we create a new client bucket */
static void
match_route(user_agent::dati *ua, char endpoint[], struct ua_conn_s *conn)
{
  char *bucket_hash = ua_respheader_value(conn, "x-ratelimit-bucket");
  if (!bucket_hash) return; //no hash information in header

  // create new route that will link the endpoint with a bucket
  struct _route_s *new_route = (struct _route_s*) calloc(1, sizeof *new_route);

  new_route->str = strdup(endpoint);

  //attempt to match hash to client bucket hashes
  for (size_t i=0; i < ua->ratelimit.num_buckets; ++i) {
    if (STREQ(bucket_hash, ua->ratelimit.buckets[i]->hash)) {
      new_route->p_bucket = ua->ratelimit.buckets[i];
      break; /* EARLY BREAK */
    }
  }

  if (!new_route->p_bucket) { //couldn't find match, create new bucket
    ++ua->ratelimit.num_buckets; //increments client buckets

    ua->ratelimit.buckets = (dati**)realloc(ua->ratelimit.buckets, \
                              ua->ratelimit.num_buckets * sizeof(dati*));

    dati *new_bucket = bucket_init(bucket_hash);
    ua->ratelimit.buckets[ua->ratelimit.num_buckets-1] = new_bucket;
    new_route->p_bucket = new_bucket; //route points to new bucket
  }

  //add new route to tree and update its bucket ratelimit fields
  struct _route_s *ret_route;
  ret_route = *(struct _route_s **)tsearch(new_route, &ua->ratelimit.routes_root, &routecmp);

  parse_ratelimits(ret_route->p_bucket, conn);
}

/* Attempt to build and/or updates bucket's rate limiting information.
 * In case that the endpoint doesn't have a bucket for routing, no 
 *  clashing will occur */
void
build(user_agent::dati *ua, dati *bucket, char endpoint[], struct ua_conn_s *conn)
{
  /* no bucket means first time using this endpoint.  attempt to 
   *  establish a route between it and a bucket via its unique hash 
   *  (will create a new bucket if it can't establish a route) */
  if (!bucket)
    match_route(ua, endpoint, conn);
  else // update the bucket rate limit values
    parse_ratelimits(bucket, conn);
}

/* This comparison routines can be used with tdestroy()
 * when explicity deleting a root node, as no comparison
 * is necessary. */
static void
route_cleanup(void *p_route) 
{
  struct _route_s *route = (struct _route_s*)p_route;
  free(route->str);
  free(route);
}

/* clean routes and buckets */
void
cleanup(user_agent::dati *ua)
{
  //destroy every route encountered
  tdestroy(ua->ratelimit.routes_root, &route_cleanup);

  //destroy every client bucket found
  for (size_t i=0; i < ua->ratelimit.num_buckets; ++i) {
    bucket_cleanup(ua->ratelimit.buckets[i]);
  }
  free(ua->ratelimit.buckets);
}

} // namespace bucket
} // namespace user_agent
} // namespace discord
