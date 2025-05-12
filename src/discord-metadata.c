#include "discord-metadata.h"

#define DISCORD_METADATA(_data) MIDA(DiscordMD, _data)

void *
__discord_metadata_injection(void *data,
                             const size_t size,
                             const size_t length)
{
    DISCORD_METADATA(data)->size = size;
    DISCORD_METADATA(data)->length = length;
    return data;
}
