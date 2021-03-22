#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace emoji {

namespace list_guild_emojis {
void
run(discord::client *client, const uint64_t guild_id, NTL_T(discord::emoji::dati) *p_emojis)
{
  if (!guild_id) {
    D_PUTS("Missing 'guild_id'");
    return;
  }

  struct resp_handle resp_handle =
    { .ok_cb = &discord::emoji::dati_list_from_json_v, .ok_obj = (void*)p_emojis};

  discord::adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/guilds/%llu/emojis", guild_id);
}
} // namespace list_guild_emojis

} // namespace emoji
} // namespace discord

