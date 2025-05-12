#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_list_voice_regions(struct discord *client,
                           struct discord_ret_voice_region *ret)
{
    struct discord_attributes attr = { 0 };
    DISCORD_ATTR_INIT(attr, discord_voice_region, ret, NULL);
    return discord_rest_run(&client->rest, &attr, NULL, HTTP_GET,
                            "/voice/regions");
}
