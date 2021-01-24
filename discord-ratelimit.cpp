#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h> //for lround
#include <search.h> //for tfind, tsearch, tdestroy

#include <libdiscord.h>
#include "discord-common.h"

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
  bucket::data *p_bucket; //bucket assigned to this route
};

/* return the expected cooldown for a connection within this bucket
 *  in milliseconds */
long long
cooldown(bucket::data *bucket, bool use_clock)
{
  if (bucket->remaining) return 0; //means we don't have any delay

  if (true == use_clock || !bucket->reset_after_ms) {
    long long delay_ms = bucket->reset_ms - timestamp_ms();
    if (delay_ms < 0) //no delay needed
      return 0;
    if (delay_ms < bucket->reset_after_ms) //don't delay longer than necessary
      return delay_ms;
  }

  return bucket->reset_after_ms; //delay for expected minimum
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
  if (strstr(route1->str, CHANNEL) && strstr(route2->str, CHANNEL)) return 0;
  if (strstr(route1->str, GUILD) && strstr(route2->str, GUILD)) return 0;
//if (strstr(route1->str, WEBHOOK) && strstr(route2->str, WEBHOOK)) return 0;

  return ret; //couldn't find any match, return strcmp diff value
}

/* attempt to find a bucket associated with this endpoint */
bucket::data*
try_get(user_agent::data *ua, char endpoint[])
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
parse_ratelimits(bucket::data *bucket, struct api_header_s *pairs)
{ 
  char *value; //fetch header value as string

  value = get_header_value(pairs, "x-ratelimit-remaining");
  if (NULL != value) {
    bucket->remaining =  strtol(value, NULL, 10);
  }

  value = get_header_value(pairs, "x-ratelimit-reset-after");
  if (NULL != value) {
    bucket->reset_after_ms = 1000 * strtoll(value, NULL, 10);
  }

  value = get_header_value(pairs, "x-ratelimit-reset");
  if (NULL != value) {
    bucket->reset_ms = 1000 * strtoll(value, NULL, 10);
  }
}

/* Attempt to create a route between endpoint and a client bucket by
 *  comparing the hash retrieved from header to hashes from existing
 *  client buckets.
 * If no match is found then we create a new client bucket */
static void
create_route(user_agent::data *ua, char endpoint[])
{
  char *bucket_hash = get_header_value(&ua->pairs, "x-ratelimit-bucket");
  if (NULL == bucket_hash) return; //no hash information in header

  // create new route that will link the endpoint with a bucket
  struct _route_s *new_route = (struct _route_s*) calloc(1, sizeof *new_route);
  ASSERT_S(NULL != new_route, "Out of memory");

  new_route->str = strdup(endpoint);
  ASSERT_S(NULL != new_route->str, "Out of memory");

  //attempt to match hash to client bucket hashes
  for (size_t i=0; i < ua->ratelimit.num_buckets; ++i) {
    if (STREQ(bucket_hash, ua->ratelimit.buckets[i]->hash)) {
      new_route->p_bucket = ua->ratelimit.buckets[i];
    }
  }

  if (!new_route->p_bucket) { //couldn't find match, create new bucket
    bucket::data *new_bucket = (bucket::data*) calloc(1, sizeof *new_bucket);
    ASSERT_S(NULL != new_bucket, "Out of memory");

    new_bucket->hash = strdup(bucket_hash);
    ASSERT_S(NULL != new_bucket->hash, "Our of memory");

    ++ua->ratelimit.num_buckets; //increments client buckets

    void *tmp = realloc(ua->ratelimit.buckets, ua->ratelimit.num_buckets * sizeof(bucket::data*));
    ASSERT_S(NULL != tmp, "Out of memory");

    ua->ratelimit.buckets = (bucket::data**)tmp;
    ua->ratelimit.buckets[ua->ratelimit.num_buckets-1] = new_bucket;

    new_route->p_bucket = new_bucket; //route points to new bucket
  }

  //add new route to tree
  struct _route_s **p_route;
  p_route = (struct _route_s**)tsearch(new_route, &ua->ratelimit.routes_root, &routecmp);
  ASSERT_S(*p_route == new_route, "Couldn't create new bucket route");

  parse_ratelimits(new_route->p_bucket, &ua->pairs);
}

/* Attempt to build and/or updates bucket's rate limiting information.
 * In case that the endpoint doesn't have a bucket for routing, no 
 *  clashing will occur */
void
build(user_agent::data *ua, bucket::data *bucket, char endpoint[])
{
  /* for the first use of an endpoint, we attempt to establish a
      route between it and a bucket (create a new bucket if needed) */
  if (!bucket) {
    create_route(ua, endpoint);
    return;
  }

  // otherwise we just update the bucket rate limit values

  parse_ratelimits(bucket, &ua->pairs);
}

static void
route_cleanup(void *p_route)
{
  struct _route_s *route = (struct _route_s*)p_route;

  free(route->str); //clean the endpoint associaited to this route
  free(route);
}

/* clean routes and buckets */
void
cleanup(user_agent::data *ua)
{
  //destroy every route encountered
  tdestroy(&ua->ratelimit.routes_root, &route_cleanup);

  //destroy every client bucket found
  for (size_t i=0; i < ua->ratelimit.num_buckets; ++i) {
    free(ua->ratelimit.buckets[i]->hash);
    free(ua->ratelimit.buckets[i]);
  }
  free(ua->ratelimit.buckets);
}

} // namespace bucket
} // namespace user_agent
} // namespace discord
