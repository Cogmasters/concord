#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <libdiscord.h>
#include "discord-common.h"

void*
Discord_utils_set_data(discord_t *client, void *data) {
  return client->data = data;
}

void*
Discord_utils_get_data(discord_t *client) {
  return client->data;
}
