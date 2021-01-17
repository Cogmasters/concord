#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h> //for lround
#include <search.h> //for tsearch, tfind, etc

#include <libdiscord.h>
#include "discord-common.h"


/* returns current timestamp in milliseconds */
//@todo move to discord-utils.c
static long long
timestamp_ms()
{
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);

  return t.tv_sec*1000 + lround(t.tv_nsec/1.0e6);
}

static char*
get_header_value(struct api_header_s *pairs, char header_field[])
{
  int i=0;
  for ( ; i < pairs->size; ++i) {
    if (STREQ(pairs->field[i], header_field)) {
      return pairs->value[i];
    }
  }
  return NULL;
}

/* See:
https://discord.com/developers/docs/topics/rate-limits#rate-limits */

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

int
Discord_ratelimit_remaining(struct api_header_s *pairs)
{
  char *value = get_header_value(pairs, "x-ratelimit-remaining");
  ASSERT_S(NULL != value, "Couldn't fetch field from header");

  return strtol(value, NULL, 10);
}

long long
Discord_ratelimit_delay(int remaining, struct api_header_s *pairs, bool use_clock)
{
  if (remaining) return 0; //means we don't have any delay

  char *value = get_header_value(pairs, "x-ratelimit-reset-after");
  ASSERT_S(NULL != value, "Couldn't fetch field from header");

  long long reset_after = strtoll(value, NULL, 10);

  long long delay_ms;
  if (true == use_clock || !reset_after) {
    long long utc = timestamp_ms();
    value = get_header_value(pairs, "x-ratelimit-reset");
    ASSERT_S(NULL != value, "Couldn't fetch field from header");

    long long reset = 1000 * strtoll(value, NULL, 10);

    delay_ms = ((reset - utc) >= 0) ? (reset - utc) : 0;
  }
  else {
    delay_ms = 1000 * reset_after;
  }

  return delay_ms;
}

char*
Discord_ratelimit_bucket(struct api_header_s *pairs) {
  return get_header_value(pairs, "x-ratelimit-bucket");
}

