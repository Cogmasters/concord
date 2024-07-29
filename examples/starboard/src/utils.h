#ifndef STAR_UTILS_H
#define STAR_UTILS_H

#include <concord/discord.h>

// This makes the `Bot is thinking...` message, which is useful, because it gives us like 5 minutes
// to process stuff, instead of a few seconds.
// I can't spell empremmemral, so im calling it hidden, which is probably more self-explanatory
#define star_interaction_defer_hidden(client, id, token)        discord_create_interaction_response(client, id, \
                                                                  token, &(struct discord_interaction_response){ \
                                                                  .type = DISCORD_INTERACTION_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE, \
                                                                  .data = &(struct discord_interaction_callback_data) { \
                                                                    .flags = DISCORD_MESSAGE_EPHEMERAL \
                                                                  } \
                                                                }, NULL); 

// Same as before, but displays for everyone (the one without dismiss message)
#define star_interaction_defer(client, id, token)     discord_create_interaction_response(client, id, \
                                                        token, &(struct discord_interaction_response){ \
                                                        .type = DISCORD_INTERACTION_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE, \
                                                      }, NULL); 

int star_snowflake_to_string(char* buffer, u64snowflake snowflake);
u64snowflake star_string_to_snowflake(char* string);
bool star_string_to_bool(char* string);

#endif // STAR_UTILS_H