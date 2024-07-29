#include "remove.h"
#include "../config.h"
#include "../utils.h"
#include "../starboard.h"

void star_command_remove_register(struct discord* client, u64snowflake application_id) {
  discord_create_global_application_command(client, application_id,
                                            &(struct discord_create_global_application_command) {
                                              .name = "remove",
                                              .description = "Removes a channel",
                                              .options = &(struct discord_application_command_options) {
                                                .array = (struct discord_application_command_option *)&(struct discord_application_command_option[]) {
                                                  {
                                                    .name = "channel",
                                                    .description = "Channel",
                                                    .required = true,
                                                    .type = DISCORD_APPLICATION_OPTION_CHANNEL,
                                                  },
                                                },
                                                .size = 1,
                                              }
                                            }, NULL);
}
void star_command_remove_execute(struct discord* client, const struct discord_interaction* event) {
  if(event->member->user->id != CONFIG_OWNER_USER_ID) return; // If the user isn't the owner, return

  star_interaction_defer_hidden(client, event->id, event->token);

  // Get the channel id from the parameters
  char* stringified_channel_id = event->data->options->array[0].value;

  // Remove the channel
  star_remove_channel(stringified_channel_id);

  discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response) {
    .content = "Channel has been removed."
  }, NULL);
}