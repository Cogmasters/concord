#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace emoji {

dati**
get_list(client *client, const uint64_t guild_id)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return NULL;
  }

  dati **new_emojis = NULL;

  struct resp_handle resp_handle =
    { .ok_cb = &dati_list_from_json_v, .ok_obj = (void*)&new_emojis};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%llu/emojis", guild_id);

  return new_emojis;
}

} // namespace emoji
} // namespace discord

