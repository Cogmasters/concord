#include <string.h>
#include <concord/discord.h>
#include "config.h"
#include "db.h"
#include "memhandl.h"

// TODO: Add the `/remove` command

void on_ready(struct discord *client, const struct discord_ready *event) {
  discord_create_global_application_command(client, event->application->id,
                                            &(struct discord_create_global_application_command) {
                                              .name = "force",
                                              .description = "Force a submission",
                                              .options = &(struct discord_application_command_options) {
                                                .array = &(struct discord_application_command_option)
                                                  {
                                                    .name = "messageid",
                                                    .description = "Message ID",
                                                    .required = true,
                                                    .type = DISCORD_APPLICATION_OPTION_STRING,
                                                  },
                                                .size = 1,
                                              }
                                            }, NULL);

  discord_create_global_application_command(client, event->application->id,
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
                                                    .name = "isboard",
                                                    .description = "Should the channel be a board channel",
                                                    .required = true,
                                                    .type = DISCORD_APPLICATION_OPTION_BOOLEAN,
                                                  },
                                                },
                                                .size = 2,
                                              }
                                            }, NULL);
  printf("Logged in as %s#%s (%" PRIu64 ")\n", event->user->username, event->user->discriminator, event->user->id);
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
  if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
    return; /* return if interaction isn't a slash command */

  if(strcmp(event->data->name, "force") == 0) {
    if(event->member->user->id != OWNER_USER_ID) return;
    discord_create_interaction_response(client, event->id,
                                          event->token, &(struct discord_interaction_response){
                                          .type = DISCORD_INTERACTION_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE,
                                          .data = &(struct discord_interaction_callback_data) {
                                            .flags = DISCORD_MESSAGE_EPHEMERAL
                                          }
                                        }, NULL);

    char* message_id = event->data->options->array[0].value;

    struct discord_message message;
    struct discord_ret_message message_ret = { .sync = &message };
    CCORDcode code;

    // Get the message object and make check.
    code = discord_get_channel_message(client, event->channel_id, char_to_snowflake(message_id), &message_ret);
    assert(CCORD_OK == code && "Couldn't fetch message");

    char uid[83];
    snowflake_to_char(uid, message.author->id);

    sbclone_create_row(message_id, uid);
    sbclone_post_to_channel(client, &message, message_id, &message.id, &message.channel_id, &message.guild_id);
    discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response){
                                                .content = "Completed without errors.",
                                              }, NULL);
  } else if(strcmp(event->data->name, "add") == 0) {
    if(event->member->user->id != OWNER_USER_ID) return;

    discord_create_interaction_response(client, event->id,
                                        event->token, &(struct discord_interaction_response){
                                          .type = DISCORD_INTERACTION_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE,
                                          .data = &(struct discord_interaction_callback_data) {
                                            .flags = DISCORD_MESSAGE_EPHEMERAL
                                          }
                                        }, NULL);
    char guild_id_char[23];
    snowflake_to_char(guild_id_char, event->guild_id);

    int value = sbclone_add_channel(event->data->options->array[0].value, guild_id_char, strcmp(event->data->options->array[1].value, "true") == 0 ? 1 : 0);
    if(value == 1) {
      // Multiple board channels error
      discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response) {
        .content = "You can only have 1 starboard on a guild."
      }, NULL);
      return;
    } else if(value == 2) {
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
}

int main(void) {
  sbclone_connectDB();
  sbclone_init(sbclone_DB);
  sqlite3_initialize();
  struct discord *client = discord_config_init("config.json");
  discord_set_on_ready(client, &on_ready);
  discord_set_on_message_reaction_add(client, &sbclone_MemoHandler);
  discord_set_on_interaction_create(client, &on_interaction);
  discord_run(client);

  return 0;
}
