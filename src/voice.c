#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-request.h"

CCORDcode
discord_list_voice_regions(struct discord *client,
                           struct discord_ret_voice_regions *ret)
{
    struct discord_request req = { 0 };

    DISCORD_REQ_LIST_INIT(req, discord_voice_regions, ret);

    return discord_adapter_run(&client->adapter, &req, NULL, HTTP_GET,
                               "/voice/regions");
}
