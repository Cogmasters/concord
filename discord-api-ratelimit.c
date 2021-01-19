#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h> //for lround
#include <search.h> //for tsearch, tfind, etc

#include <libdiscord.h>
#include "discord-common.h"

/* See:
https://discord.com/developers/docs/topics/rate-limits#rate-limits */


/* returns current timestamp in milliseconds */
//@todo move to discord-utils.c
static long long
timestamp_ms()
{
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);

  return t.tv_sec*1000 + lround(t.tv_nsec/1.0e6);
}

long long
Discord_ratelimit_delay(struct api_bucket_s *bucket, bool use_clock)
{
  if (bucket->remaining) return 0; //means we don't have any delay

  if (true == use_clock || !bucket->reset_after_ms) {
    long long delay_ms = bucket->reset_ms - timestamp_ms();
    if (delay_ms < 0) return 0;
    if (delay_ms < bucket->reset_after_ms) return delay_ms;
  }

  return bucket->reset_after_ms;
}

static int
routecmp(const void *p_route1, const void *p_route2)
{
  struct api_route_s *route1 = (struct api_route_s*)p_route1;
  struct api_route_s *route2 = (struct api_route_s*)p_route2;

  return strcmp(route1->str, route2->str);
}

/* get the route to be matched with a bucket */
char*
Discord_ratelimit_route(char endpoint[])
{
  if (strstr(endpoint, CHANNEL)) return "channel_major";
  if (strstr(endpoint, GUILD)) return "guild_major";
/* @todo implement WEBHOOK
  if (strstr(endpoint, WEBHOOK)) return "webhook_major"; */
  return endpoint;
}

struct api_bucket_s*
Discord_ratelimit_tryget_bucket(struct discord_api_s *api, char *bucket_route)
{
  struct api_route_s search_route = {.str = bucket_route};
  void *ret = tfind(&search_route, &api->ratelimit.root_routes, &routecmp);

  return (ret) ? (*(struct api_route_s**)ret)->p_bucket : NULL;
}

static char*
get_header_value(struct api_header_s *pairs, char header_field[])
{
  for (int i=0; i < pairs->size; ++i) {
    if (STREQ(header_field, pairs->field[i])) {
      return pairs->value[i];
    }
  }

  return NULL;
}

//assign route to exiting / new bucket
struct api_bucket_s*
Discord_ratelimit_assign_bucket(struct discord_api_s *api, char *bucket_route)
{
  char *bucket_hash = get_header_value(&api->pairs, "x-ratelimit-bucket");
  if (NULL == bucket_hash) return NULL;

  struct api_route_s *new_route = calloc(1, sizeof *new_route);
  ASSERT_S(NULL != new_route, "Out of memory");

  new_route->str = strdup(bucket_route);
  ASSERT_S(NULL != new_route->str, "Out of memory");

  for (size_t i=0; i < api->ratelimit.num_buckets; ++i) {
    if (STREQ(bucket_hash, api->ratelimit.buckets[i]->hash)) {
      new_route->p_bucket = api->ratelimit.buckets[i];
    }
  }

  if (!new_route->p_bucket) { //couldn't match with existing bucket
    struct api_bucket_s *new_bucket = calloc(1, sizeof *new_bucket);
    ASSERT_S(NULL != new_bucket, "Out of memory");

    new_bucket->hash = strdup(bucket_hash);
    ASSERT_S(NULL != new_bucket->hash, "Our of memory");

    ++api->ratelimit.num_buckets; //increase num of active buckets

    void *ret = realloc(api->ratelimit.buckets, api->ratelimit.num_buckets * sizeof(struct api_bucket_s*));
    ASSERT_S(NULL != ret, "Out of memory");

    api->ratelimit.buckets = ret;
    api->ratelimit.buckets[api->ratelimit.num_buckets-1] = new_bucket;

    new_route->p_bucket = new_bucket;
  }

  // add new route to tree
  void *ret = tsearch(new_route, &api->ratelimit.root_routes, &routecmp);
  ASSERT_S((*(struct api_route_s**)ret) == new_route, "Couldn't create new bucket route");

  return new_route->p_bucket;
}

void
Discord_ratelimit_parse_header(struct api_bucket_s *bucket, struct api_header_s *pairs)
{ 
  char *value = get_header_value(pairs, "x-ratelimit-remaining");
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
