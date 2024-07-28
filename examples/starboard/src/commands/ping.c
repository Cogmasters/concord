#include "ping.h"
#include "../utils.h"

void star_command_ping_register(struct discord* client, u64snowflake application_id) {
    discord_create_global_application_command(client, application_id,
                                              &(struct discord_create_global_application_command) {
                                                .name = "ping",
                                                .description = "Ping, pong!",
                                              }, NULL);
}

void star_command_ping_execute(struct discord* client, const struct discord_interaction* event) {
  star_interaction_defer_hidden(client, event->id, event->token);

  discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response) {
    .content = "Pong!"
  }, NULL);
}