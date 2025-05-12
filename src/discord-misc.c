#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cog-utils.h"

#include "mida.h"

void
discord_overwrite_append(struct discord_overwrite permission_overwrites[],
                         u64snowflake id,
                         int type,
                         u64bitmask allow,
                         u64bitmask deny)
{
    void *tmp = discord_realloc(permission_overwrites,
                                sizeof(struct discord_overwrite),
                                discord_length(permission_overwrites) + 1);
    if (!tmp) {
        logmod_log(ERROR, NULL,
                   "Failed to allocate memory for permission overwrites");
        return;
    }
    permission_overwrites = tmp;
    permission_overwrites[discord_length(permission_overwrites) - 1] =
        (struct discord_overwrite){
            .id = id, .type = type, .allow = allow, .deny = deny
        };
}

void
discord_presence_add_activity(struct discord_presence_update *presence,
                              struct discord_activity *activity)
{
    void *tmp =
        discord_realloc(presence->activities, sizeof(struct discord_activity),
                        discord_length(presence->activities) + 1);
    if (!tmp) {
        logmod_log(ERROR, NULL,
                   "Failed to allocate memory for permission overwrites");
        return;
    }
    presence->activities = tmp;
    presence->activities[discord_length(presence->activities) - 1] = *activity;
}
