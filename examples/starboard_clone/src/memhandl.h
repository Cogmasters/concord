#include <concord/discord.h>
#include <sqlite3.h>
#include <string.h>
#include "utils.h"
#include <assert.h>
#include <stdlib.h>
#include "config.h"

extern sqlite3* sbclone_DB;
void sbclone_MemoHandler(struct discord *client, const struct discord_message_reaction_add *event);
void sbclone_post_to_channel(struct discord* client, struct discord_message* message, char* message_id, const u64snowflake* event_message_id, const u64snowflake* event_channel_id, const u64snowflake* event_guild_id);
void sbclone_create_row(char* message_id, char* author_id);
void sbclone_get_board_channel(u64snowflake* buf, u64snowflake guild_id);
int sbclone_check_if_star_channel(u64snowflake channel_id);
int sbclone_add_channel(char* channel_id, char* guild_id, int is_board_channel);
int sbclone_check_for_multiple_board_channels(char* guild_id);
int sbclone_check_for_multiple_channels(char* channel_id);
int sbclone_multi_channel_check(sqlite3_stmt* stmt);
