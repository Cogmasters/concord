#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

namespace discord {
namespace channel {

dati*
init()
{
  dati *new_channel = (dati*)calloc(1, sizeof *new_channel);
  return new_channel;
}

void
cleanup(dati *channel) {
  free(channel);
}

void
pin_message(client *client, const char channel_id[], const char message_id[])
{
  if (IS_EMPTY_STRING(channel_id)) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (IS_EMPTY_STRING(message_id)) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  user_agent::run( 
    &client->ua,
    NULL,
    NULL,
    "", //empty POSTFIELDS
    HTTP_PUT, PINNED_MESSAGE, channel_id, message_id);
}

void
unpin_message(client *client, const char channel_id[], const char message_id[])
{
  if (IS_EMPTY_STRING(channel_id)) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (IS_EMPTY_STRING(message_id)) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  user_agent::run( 
    &client->ua,
    NULL,
    NULL,
    "", //empty POSTFIELDS
    HTTP_DELETE, PINNED_MESSAGE, channel_id, message_id);
}

} // namespace channel
} // namespace discord
