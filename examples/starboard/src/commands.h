#ifndef STAR_COMMANDS_H
#define STAR_COMMANDS_H

#include <concord/discord.h>

#include "commands/ping.h"
#include "commands/add.h"
#include "commands/force.h"
#include "commands/remove.h"

void star_commands_register(struct discord* client, u64snowflake application_id);
void star_commands_handler(struct discord* client, const struct discord_interaction* event);

#endif // STAR_COMMANDS_H
