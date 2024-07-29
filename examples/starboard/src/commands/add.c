#include "add.h"
#include "../utils.h"
#include "../config.h"
#include "../starboard.h"
#include "../utils.h"

void star_command_add_register(struct discord* client, u64snowflake application_id) {
  discord_create_global_application_command(client, application_id,
                                            &(struct discord_create_global_application_command) {
                                              .name = "add",
                                              .description = "Adds a new starboard submission channel",
                                              .options = &(struct discord_application_command_options) {
                                                .array = (struct discord_application_command_option *)&(struct discord_application_command_option[]) {
                                                  {
                                                    .name = "channel",
                                                    .description = "Channel",
                                                    .required = true,
                                                    .type = DISCORD_APPLICATION_OPTION_CHANNEL,
                                                  },
                                                  {
                                                    .name = "is_board",
                                                    .description = "Should the channel be a board channel",
                                                    .required = true,
                                                    .type = DISCORD_APPLICATION_OPTION_BOOLEAN,
                                                  },
                                                },
                                                .size = 2,
                                              }
                                            }, NULL);
}

void star_command_add_execute(struct discord* client, const struct discord_interaction* event) {
  if(event->member->user->id != CONFIG_OWNER_USER_ID) return; // If the user isn't the owner, return

  star_interaction_defer_hidden(client, event->id, event->token);

  // Stringify
  char stringified_guild_id[STAR_SNOWFLAKE_BUF_SIZE];
  star_snowflake_to_string(stringified_guild_id, event->guild_id);

  // `event->data->options->array[0].value` is the channel and `->array[1].value` is the is_board
  enum STAR_ADD_CHANNEL_CODE value = star_add_channel(event->data->options->array[0].value, stringified_guild_id, star_string_to_bool(event->data->options->array[1].value));
  if(value == STAR_BOARD_CHANNEL_ALREADY_SET) {
    // Multiple board channels error
    discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response) {
      .content = "You can only have 1 starboard on a guild."
    }, NULL);
    return;
  } else if(value == STAR_DUPLICATE_CHANNEL) {
    // Attempted having duplicate channels error
    discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response) {
      .content = "This channel is already added."
    }, NULL);
    return;
  }

  discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response) {
    .content = "Successfully added the channel."
  }, NULL);
}