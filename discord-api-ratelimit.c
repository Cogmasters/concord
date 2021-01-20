#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h> //for lround
#include <search.h> //for tfind, tsearch, tdestroy

#include <libdiscord.h>
#include "discord-common.h"

/* See:
https://discord.com/developers/docs/topics/rate-limits#rate-limits */


/* this struct contains the bucket's route string and a pointer 
 *  to the bucket assigned to this route. it will be stored and 
 *  retrieved by search.h tree functions */
struct _route_s {
  char *str; //bucket route (endpoint, major parameter)
  struct api_bucket_s *p_bucket; //bucket assigned to this route
};

/* returns current timestamp in milliseconds */
//@todo move to discord-utils.c
static long long
timestamp_ms()
{
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);

  return t.tv_sec*1000 + lround(t.tv_nsec/1.0e6);
}

/* return the expected delay for a connection within this bucket
 *  in milliseconds */
long long
Discord_ratelimit_delay(struct api_bucket_s *bucket, bool use_clock)
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
struct api_bucket_s*
Discord_ratelimit_tryget_bucket(struct discord_api_s *api, char endpoint[])
{
  struct _route_s search_route = {
    .str = endpoint
  };

  struct _route_s **p_route;
  p_route = tfind(&search_route, &api->ratelimit.routes_root, &routecmp);
  //if found matching route, return its bucket, otherwise NULL
  return (p_route) ? (*p_route)->p_bucket : NULL;
}

/* attempt to get value from matching header field */
static char*
get_header_value(struct api_header_s *pairs, char header_field[])
{
  for (int i=0; i < pairs->size; ++i) {
    if (STREQ(header_field, pairs->field[i])) {
      return pairs->value[i]; //found header field, return its value
    }
  }

  return NULL; //couldn't find header field
}

/* attempt to parse rate limit's header fields to the bucket
 *  linked with the connection which was performed */
static void
parse_ratelimits(struct api_bucket_s *bucket, struct api_header_s *pairs)
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
create_route(struct discord_api_s *api, char endpoint[])
{
  char *bucket_hash = get_header_value(&api->pairs, "x-ratelimit-bucket");
  if (NULL == bucket_hash) return; //no hash information in header

  // create new route that will link the endpoint with a bucket
  struct _route_s *new_route = calloc(1, sizeof *new_route);
  ASSERT_S(NULL != new_route, "Out of memory");

  new_route->str = strdup(endpoint);
  ASSERT_S(NULL != new_route->str, "Out of memory");

  //attempt to match hash to client bucket hashes
  for (size_t i=0; i < api->ratelimit.num_buckets; ++i) {
    if (STREQ(bucket_hash, api->ratelimit.buckets[i]->hash)) {
      new_route->p_bucket = api->ratelimit.buckets[i];
    }
  }

  if (!new_route->p_bucket) { //couldn't find match, create new bucket
    struct api_bucket_s *new_bucket = calloc(1, sizeof *new_bucket);
    ASSERT_S(NULL != new_bucket, "Out of memory");

    new_bucket->hash = strdup(bucket_hash);
    ASSERT_S(NULL != new_bucket->hash, "Our of memory");

    ++api->ratelimit.num_buckets; //increments client buckets

    void *tmp = realloc(api->ratelimit.buckets, api->ratelimit.num_buckets * sizeof(struct api_bucket_s*));
    ASSERT_S(NULL != tmp, "Out of memory");

    api->ratelimit.buckets = tmp;
    api->ratelimit.buckets[api->ratelimit.num_buckets-1] = new_bucket;

    new_route->p_bucket = new_bucket; //route points to new bucket
  }

  //add new route to tree
  struct _route_s **p_route;
  p_route = tsearch(new_route, &api->ratelimit.routes_root, &routecmp);
  ASSERT_S(*p_route == new_route, "Couldn't create new bucket route");

  parse_ratelimits(new_route->p_bucket, &api->pairs);
}

/* Attempt to build and/or updates bucket's rate limiting information.
 * In case that the endpoint doesn't have a bucket for routing, no 
 *  clashing will occur */
void
Discord_ratelimit_build_bucket(struct discord_api_s *api, struct api_bucket_s *bucket, char endpoint[])
{
  /* for the first use of an endpoint, we attempt to establish a
      route between it and a bucket (create a new bucket if needed) */
  if (!bucket) {
    create_route(api, endpoint);
    return;
  }

  // otherwise we just update the bucket rate limit values

  parse_ratelimits(bucket, &api->pairs);
}

static void
route_cleanup(void *p_route)
{
  struct _route_s *route = p_route;

  free(route->str); //clean the endpoint associaited to this route
  free(route);
}

/* clean routes and buckets */
void
Discord_ratelimit_buckets_cleanup(struct discord_api_s *api)
{
  //destroy every route encountered
  tdestroy(&api->ratelimit.routes_root, &route_cleanup);

  //destroy every client bucket found
  for (size_t i=0; i < api->ratelimit.num_buckets; ++i) {
    free(api->ratelimit.buckets[i]->hash);
    free(api->ratelimit.buckets[i]);
  }
  free(api->ratelimit.buckets);
}
