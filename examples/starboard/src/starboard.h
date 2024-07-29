#ifndef STAR_STARBOARD_H
#define STAR_STARBOARD_H

#include <concord/discord.h>
#include <libpq-fe.h>

#define STAR_SNOWFLAKE_BUF_SIZE 32 // I'm setting it to 32, because.... I don't know? I guess you could change it to 20 or 21 to save a few bytes, but why would you?
#define STAR_DISCORD_MAX_ATTACHMENT_COUNT 10

enum STAR_ADD_CHANNEL_CODE {
  STAR_BOARD_CHANNEL_ALREADY_SET,
  STAR_DUPLICATE_CHANNEL,
  STAR_CHANNEL_OK,
};

void star_main_handler(struct discord* client, const struct discord_message_reaction_add* event);
u64snowflake star_get_board_channel(u64snowflake guild_id);
void star_create_row(char* stringified_author_id, char* stringified_message_id);
enum STAR_ADD_CHANNEL_CODE star_add_channel(char* stringified_channel_id, char* stringified_guild_id, bool is_board_channel);
void star_remove_channel(char* stringified_channel_id);
int star_check_for_multiple_board_channels(char* stringified_guild_id);
int star_check_for_multiple_channels(char* stringified_channel_id);
int star_multi_channel_check(PGresult* res);
bool star_check_if_star_channel(u64snowflake channel_id);
void star_post_to_channel(struct discord* client, struct discord_message* message, 
                          char* stringified_message_id, const u64snowflake* event_message_id, 
                          const u64snowflake* event_channel_id, const u64snowflake* event_guild_id);


#endif // STAR_STARBOARD_H