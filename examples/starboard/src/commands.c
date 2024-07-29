#include "commands.h"
#include <string.h>

// Registers all commands
void star_commands_register(struct discord* client, u64snowflake application_id) {
  star_command_ping_register(client, application_id);
  star_command_add_register(client, application_id);
  star_command_force_register(client, application_id);
  star_command_remove_register(client, application_id);
}

void star_commands_handler(struct discord* client, const struct discord_interaction* event) {
  if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
    return; // Return if interaction isn't a slash command

  if(strcmp(event->data->name, "ping") == 0) return star_command_ping_execute(client, event);
  else if(strcmp(event->data->name, "add") == 0) return star_command_add_execute(client, event);
  else if(strcmp(event->data->name, "force") == 0) return star_command_force_execute(client, event);
  else if(strcmp(event->data->name, "remove") == 0) return star_command_remove_execute(client, event);
}