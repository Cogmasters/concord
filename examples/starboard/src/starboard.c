#include "starboard.h"
#include <concord/log.h>
#include "config.h"
#include "utils.h"
#include "assert.h"
#include "db.h"
#include <string.h>
#include <stdlib.h>

struct star_memory {
  char* data;
  size_t size;
};

static size_t star_write_memory_callback(void* contents, size_t size, size_t nmemb, void* userp) {
  size_t realsize = size * nmemb;
  struct star_memory* mem = (struct star_memory*)userp;

  char *ptr = realloc(mem->data, mem->size + realsize + 1);
  if(!ptr) {
    log_fatal("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->data = ptr;
  memcpy(mem->data + mem->size, contents, realsize);
  mem->size += realsize;
  mem->data[mem->size] = 0;

  return realsize;
}

void star_main_handler(struct discord* client, const struct discord_message_reaction_add* event) {
  #if CONFIG_SELECTIVE_CHANNEL
    // Checks if the channel of the event was the submissions channel
    int is_allowed_channel = star_check_if_star_channel(event->channel_id);
    if(is_allowed_channel == 0) return;
  #endif // CONFIG_SELECTIVE_CHANNEL

  // Checks if the reaction is the emoji specified in the config (CONFIG_EMOJI)
  if(strcmp(event->emoji->name, CONFIG_EMOJI) != 0) return;
  
  // Converts a snowflake to a char[]
  char stringified_message_id[STAR_SNOWFLAKE_BUF_SIZE];
  star_snowflake_to_string(stringified_message_id, event->message_id);

  // Get the message that was reacted to
  struct discord_message message;
  struct discord_ret_message message_ret = { .sync = &message };
  CCORDcode code = discord_get_channel_message(client, event->channel_id, event->message_id, &message_ret);
  assert(CCORD_OK == code && "Couldn't fetch message");

  // Check of message wasn't sent by the bot
  struct discord_user client_user;
  struct discord_ret_user client_user_ret = { .sync = &client_user };
  discord_get_current_user(client, &client_user_ret);
  if(message.author->id == client_user.id) return;

  // Get the post (if it exists)
  const char* param_values[1] = { stringified_message_id };
  const int param_lengths[1] = { strlen(param_values[0]) };
  PGresult* res = PQexecPrepared(star_db_conn, "get_post_by_message_id", 1, param_values, param_lengths, NULL, 0);
  star_db_error_check(res, star_db_conn);
  
  bool is_posted = false;
  char stringified_user_id[STAR_SNOWFLAKE_BUF_SIZE];

  // Check if we got a result
  if(PQntuples(res) == 0) {
    star_snowflake_to_string(stringified_user_id, message.author->id);

    star_create_row(stringified_user_id, stringified_message_id);
  } else {
    is_posted = PQgetvalue(res, 0, 3); // 3 is the column for `is_posted`
  }
  
  // End it
  PQclear(res);

  // If the post was found to be already posted on the board 
  if(is_posted) return;

  // Checks for the minimal required amount of emojis
  for(int i = 0; i < message.reactions->size; i++) {
    if(strcmp(message.reactions->array[i].emoji->name, CONFIG_EMOJI) == 0) {
      if(message.reactions->array[i].count < CONFIG_EMOJI_AMOUNT) return;
      break;
    }
  }

  // Post it.
  star_post_to_channel(client, &message, stringified_message_id, &event->message_id, &event->channel_id, &event->guild_id);
}

u64snowflake star_get_board_channel(u64snowflake guild_id) {
  // Stringify it
  char stringified_guild_id[STAR_SNOWFLAKE_BUF_SIZE];
  int stringified_guild_id_length = star_snowflake_to_string(stringified_guild_id, guild_id);

  const char* param_values[2] = { stringified_guild_id };
  const int param_lengths[2] = { stringified_guild_id_length };
  PGresult* res = PQexecPrepared(star_db_conn, "get_board_channel", 1, param_values, param_lengths, NULL, 0);
  star_db_error_check(res, star_db_conn);

  // We have no board channel
  if(PQntuples(res) <= 0) return 0;
  
  // Get the value and convert
  char* stringified_board_channel_id = PQgetvalue(res, 0, 1);
  u64snowflake board_channel_id = star_string_to_snowflake(stringified_board_channel_id);

  PQclear(res);

  return board_channel_id;
}

void star_create_row(char* stringified_author_id, char* stringified_message_id) {
  const char* param_values[2] = { stringified_author_id, stringified_message_id };
  const int param_lengths[2] = { strlen(param_values[0]), strlen(param_values[1]) };
  PGresult* res = PQexecPrepared(star_db_conn, "create_post", 2, param_values, param_lengths, NULL, 0);
  star_db_error_check(res, star_db_conn);
  PQclear(res);
}

enum STAR_ADD_CHANNEL_CODE star_add_channel(char* stringified_channel_id, char* stringified_guild_id, bool is_board_channel) {
  // It makes sure that you don't have duplicate board channels
  if(is_board_channel) {
    if(star_check_for_multiple_board_channels(stringified_guild_id) >= 1) return STAR_BOARD_CHANNEL_ALREADY_SET;
  }

  // Checks if you're trying to add a channel, thats already in the database
  if(star_check_for_multiple_channels(stringified_channel_id) >= 1) return STAR_DUPLICATE_CHANNEL;

  // Add the channel to the database
  const char* param_values[3] = { stringified_channel_id, stringified_guild_id, (const char*)&is_board_channel };
  const int param_lengths[3] = { strlen(param_values[0]), strlen(param_values[1]), sizeof(bool) };
  PGresult* res = PQexecPrepared(star_db_conn, "create_channel", 3, param_values, param_lengths, (const int[3]){ 0, 0, 1 }, 0); // The `const int[3]` here is basically: 0 means text, 1 means binary (we need binary for bool, int or other stuff like that)
  star_db_error_check(res, star_db_conn);
  PQclear(res);

  // No error
  return STAR_CHANNEL_OK;
}

// Remove the channel from the database
void star_remove_channel(char* stringified_channel_id) {
  const char* param_values[1] = { stringified_channel_id };
  const int param_lengths[1] = { strlen(param_values[0]) };
  PGresult* res = PQexecPrepared(star_db_conn, "delete_channel_by_id", 1, param_values, param_lengths, NULL, 0);
  star_db_error_check(res, star_db_conn);
  PQclear(res);
}

// Checks if there's a board channel already.
int star_check_for_multiple_board_channels(char* stringified_guild_id) {
  const char* param_values[1] = { stringified_guild_id };
  const int param_lengths[1] = { strlen(param_values[0]) };
  PGresult* res = PQexecPrepared(star_db_conn, "get_board_channel", 1, param_values, param_lengths, NULL, 0);
  star_db_error_check(res, star_db_conn);
  return star_multi_channel_check(res);
}

// Get the number of channels total
int star_check_for_multiple_channels(char* stringified_channel_id) {
  const char* param_values[1] = { stringified_channel_id };
  const int param_lengths[1] = { strlen(param_values[0]) };
  PGresult* res = PQexecPrepared(star_db_conn, "get_channel_by_id", 1, param_values, param_lengths, NULL, 0);
  star_db_error_check(res, star_db_conn);
  return star_multi_channel_check(res);
}

// Returns the number of channels found
int star_multi_channel_check(PGresult* res) {
  int channel_num = PQntuples(res);
  PQclear(res);
  return channel_num;
}

bool star_check_if_star_channel(u64snowflake channel_id) {
  // Convert
  char stringified_channel_id[STAR_SNOWFLAKE_BUF_SIZE];
  int stringified_channel_id_length = star_snowflake_to_string(stringified_channel_id, channel_id);

  const char* param_values[1] = { stringified_channel_id };
  const int param_lengths[1] = { stringified_channel_id_length };
  PGresult* res = PQexecPrepared(star_db_conn, "get_channel_by_id", 1, param_values, param_lengths, NULL, 0);
  star_db_error_check(res, star_db_conn);

  // Check if we got a result
  if(PQntuples(res) == 0) {
    // We haven't
    PQclear(res);
    return false;
  }
  // We did, but is it a board channel?
  // If something breaks, debug this first
  char* stringified_is_board = PQgetvalue(res, 0, 3); // Apparently, that's how you get a bool. Why did they have to do this to me?
  bool is_board = star_string_to_bool(stringified_is_board);
  if(is_board) {
    PQclear(res);
    return false; // We don't want it
  }

  PQclear(res);
  return true; // All good
}

void star_post_to_channel(struct discord* client, struct discord_message* message, 
                          char* stringified_message_id, const u64snowflake* event_message_id, 
                          const u64snowflake* event_channel_id, const u64snowflake* event_guild_id) {
  const char* param_values[1] = { stringified_message_id };
  const int param_lengths[1] = { strlen(param_values[0]) };
  PGresult* res = PQexecPrepared(star_db_conn, "set_as_posted", 1, param_values, param_lengths, NULL, 0);
  star_db_error_check(res, star_db_conn);
  PQclear(res);
  
  struct discord_attachments* attachments = message->attachments;

  // Generate the board message content
  char content[64];
  snprintf(content, sizeof(content), "<@%" PRIu64 "> | <#%" PRIu64 ">", message->author->id, message->channel_id);

  // Get the user object for the embed author
  struct discord_user user;
  struct discord_ret_user user_ret = { .sync = &user };
  CCORDcode code = discord_get_user(client, message->author->id, &user_ret);
  assert(CCORD_OK == code && "Couldn't fetch user.");

  // Get the user's avatar url
  char full_avatar_string[128];
  snprintf(full_avatar_string, sizeof(full_avatar_string), "https://cdn.discordapp.com/avatars/%" PRIu64 "/%s.png", user.id, user.avatar);

  // Combine all attachments' links into a string
  struct discord_attachments board_post_attachments;
  struct discord_attachment array_of_attachments[STAR_DISCORD_MAX_ATTACHMENT_COUNT];

  // The pointers to the downloaded attachments, because they need to be freed at the end
  void* attachment_void_array[STAR_DISCORD_MAX_ATTACHMENT_COUNT];

  board_post_attachments.size = attachments->size;

  for(int i = 0; i < attachments->size; i++) {
    struct star_memory chunk;
    chunk.data = malloc(1);
    chunk.size = 0;

    CURL* curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, attachments->array[i].url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, star_write_memory_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    CURLcode res = curl_easy_perform(curl_handle);
    if(res != CURLE_OK) {
      log_fatal("curl_easy_perform() failed: %s", curl_easy_strerror(res));
      // Close concord nicely
      ccord_shutdown_async();
      ccord_global_cleanup();

      // Close the db nicely
      PQfinish(star_db_conn);

      exit(1); // If we don't exit now, it will most likely segfault anyway, maybe doing something unwanted in the process.
    }

    struct discord_attachment singular_post_attachment = {
      .content = chunk.data,
      .size = chunk.size,
      .filename = attachments->array[i].filename,
    };

    array_of_attachments[i] = singular_post_attachment;
    attachment_void_array[i] = chunk.data;
    curl_easy_cleanup(curl_handle);
  }

  board_post_attachments.array = array_of_attachments;

  // The embed for the board message
  struct discord_embed post_embed = {
    .color = 0xfcf403, // flashback
    .description = message->content,
    .author = &(struct discord_embed_author) {
      .name = user.username,
      .icon_url = full_avatar_string,
    },
  };

  // The message to be posted on the board
  struct discord_create_message params = {
    .content = content,

    .embeds = &(struct discord_embeds) {
      .size = 1,
      .array = &post_embed,
    },
  };

  // Check if we should add attachments
  if(message->attachments->size > 0) {
    params.attachments = &board_post_attachments;
  }

  // Get the posted message
  struct discord_message sent_message;
  struct discord_ret_message sent_message_ret = { .sync = &sent_message };

  // Get the board channel
  u64snowflake board_channel = star_get_board_channel(*event_guild_id);

  // We can reuse the already defined `code` variable from earlier
  code = discord_create_message(client, board_channel, &params, &sent_message_ret);
  assert(code == CCORD_OK && "Couldn't create message");

  // Create a star reaction on the board post
  discord_create_reaction(client, sent_message.channel_id, sent_message.id, 0, CONFIG_BOARD_EMOJI, NULL);

  // Free everything built up from later
  for(int i = 0; i < attachments->size; i++) {
    free(attachment_void_array[i]);
  }
}