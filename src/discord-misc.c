#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cog-utils.h"
#include "carray.h"

void
discord_overwrite_append(struct discord_overwrites *permission_overwrites,
                         u64snowflake id,
                         int type,
                         u64bitmask allow,
                         u64bitmask deny)
{
    struct discord_overwrite new_overwrite = { 0 };

    new_overwrite.id = id;
    new_overwrite.type = type;
    new_overwrite.allow = allow;
    new_overwrite.deny = deny;

    carray_append(permission_overwrites, new_overwrite);
}

void
discord_presence_add_activity(struct discord_presence_update *presence,
                              struct discord_activity *activity)
{
    if (!presence->activities)
        presence->activities = calloc(1, sizeof *presence->activities);
    carray_append(presence->activities, *activity);
}
