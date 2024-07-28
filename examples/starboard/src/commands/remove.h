#ifndef STAR_COMMAND_REMOVE_H
#define STAR_COMMAND_REMOVE_H

#include <concord/discord.h>

void star_command_remove_register(struct discord* client, u64snowflake application_id);
void star_command_remove_execute(struct discord* client, const struct discord_interaction* event);

#endif // STAR_COMMAND_REMOVE_H