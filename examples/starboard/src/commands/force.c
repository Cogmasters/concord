#include "force.h"
#include "../config.h"
#include "../utils.h"
#include "../starboard.h"
#include <assert.h>

void star_command_force_register(struct discord* client, u64snowflake application_id) {
  discord_create_global_application_command(client, application_id,
                                            &(struct discord_create_global_application_command) {
                                              .name = "force",
                                              .description = "Force a submission onto the board",
                                              .options = &(struct discord_application_command_options) {
                                                .array = &(struct discord_application_command_option)
                                                  {
                                                    .name = "message_id",
                                                    .description = "Message ID",
                                                    .required = true,
                                                    .type = DISCORD_APPLICATION_OPTION_STRING,
                                                  },
                                                .size = 1,
                                              }
                                            }, NULL);
}
void star_command_force_execute(struct discord* client, const struct discord_interaction* event) {
  if(event->member->user->id != CONFIG_OWNER_USER_ID) return; // If the user isn't the owner, return

  star_interaction_defer_hidden(client, event->id, event->token);

  // It's set to the user-inputted message id
  char* stringified_message_id = event->data->options->array[0].value;

  // Get the message and make check to make sure it was successful.
  struct discord_message message;
  struct discord_ret_message message_ret = { .sync = &message };

  CCORDcode code = discord_get_channel_message(client, event->channel_id, star_string_to_snowflake(stringified_message_id), &message_ret);
  assert(CCORD_OK == code && "Couldn't fetch message");

  // Stringify
  char stringified_user_id[STAR_SNOWFLAKE_BUF_SIZE];
  star_snowflake_to_string(stringified_user_id, message.author->id);

  // Do the things needed to post and mark the message
  star_create_row(stringified_user_id, stringified_message_id);
  star_post_to_channel(client, &message, stringified_message_id, &message.id, &message.channel_id, &event->guild_id);

  // Post the response to the user
  discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response){
                                              .content = "Completed without errors.",
                                            }, NULL);
}