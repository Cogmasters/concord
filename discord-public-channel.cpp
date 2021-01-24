#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

namespace discord {
namespace channel {

struct data*
init()
{
  struct data *new_channel = (struct data*)calloc(1, sizeof *new_channel);
  return new_channel;
}

void
cleanup(struct data *channel) {
  free(channel);
}

void
pin_message(discord_t *client, const char channel_id[], const char message_id[])
{
  if (IS_EMPTY_STRING(channel_id)) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (IS_EMPTY_STRING(message_id)) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  Discord_api_request( 
    &client->api,
    NULL,
    NULL,
    "", //empty POSTFIELDS
    PUT, PINNED_MESSAGE, channel_id, message_id);
}

void
unpin_message(discord_t *client, const char channel_id[], const char message_id[])
{
  if (IS_EMPTY_STRING(channel_id)) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (IS_EMPTY_STRING(message_id)) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  Discord_api_request( 
    &client->api,
    NULL,
    NULL,
    "", //empty POSTFIELDS
    DELETE, PINNED_MESSAGE, channel_id, message_id);
}

} // namespace channel
} // namespace discord
