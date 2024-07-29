#ifndef STAR_COMMAND_ADD_H
#define STAR_COMMAND_ADD_H

#include <concord/discord.h>

void star_command_add_register(struct discord* client, u64snowflake application_id);
void star_command_add_execute(struct discord* client, const struct discord_interaction* event);

#endif // STAR_COMMAND_ADD_H