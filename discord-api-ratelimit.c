#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "discord-common.h"


/* See:
https://discord.com/developers/docs/topics/rate-limits#rate-limits */

/* get the key to be matched with a bucket */
char*
Discord_ratelimit_tryget_major(char endpoint[])
{
  if (strstr(endpoint, CHANNEL)) return "channel_major";
  if (strstr(endpoint, GUILD)) return "guild_major";
/* @todo implement WEBHOOK
  if (strstr(endpoint, WEBHOOK)) return "webhook_major"; */
  return endpoint;
}
