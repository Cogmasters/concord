#include "memhandl.h"

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(mem->memory + mem->size, contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

void sbclone_MemoHandler(struct discord *client, const struct discord_message_reaction_add *event) {
  #if SELECTIVE_CHANNEL
    // Checks if the channel of the event was the submissions channel
    int isMemChannel = sbclone_check_if_star_channel(event->channel_id);
    if(isMemChannel == 0) return;
  #endif
  // Checks if the reaction is ⭐
  if(strcmp(event->emoji->name, "⭐") != 0) return;

  // Get the post (if exists)
  sqlite3_stmt* stmt;
  char* sql = "SELECT * FROM posts WHERE messageid=?";
  sqlite3_prepare_v2(sbclone_DB, sql, strlen(sql), &stmt, NULL);
  char message_id[20];
  char* tmp = message_id;
  snowflake_to_char(tmp, event->message_id);
  sqlite3_bind_text(stmt, 1, message_id, strlen(message_id), SQLITE_STATIC);
  int rc = sqlite3_step(stmt);

  // This is set, if the submission was checked to be already sent to the board channel
  int isposted = 0;

  // Fetch the message
  struct discord_message message;
  struct discord_ret_message message_ret = { .sync = &message };
  CCORDcode code;

  // Get the message object and make check.
  code = discord_get_channel_message(client, event->channel_id, event->message_id, &message_ret);
  assert(CCORD_OK == code && "Couldn't fetch message");

  struct discord_user client_user;
  struct discord_ret_user client_user_ret = { .sync = &client_user };

  discord_get_current_user(client, &client_user_ret);
  if(message.author->id == client_user.id) return;

  char user_id[83]; // Don't even try to ask me, how 83 and up, are the only sizes that make it not crash
                // Don't even try to say to me that "it works with like 20", it does only in debug mode
                // I have NO idea why???? or how?????, you gotta trust me on that

  switch(rc) {
    case SQLITE_ROW:
      isposted = sqlite3_column_int(stmt, 4);
      break;
    case SQLITE_DONE:
      snowflake_to_char(user_id, message.author->id);

      sbclone_create_row(message_id, user_id);
      break;
    default:
      // Error
      fprintf(stderr, "Couldn't query post.\n");
      break;
  }
  sqlite3_finalize(stmt);

  // Checks if its already posted
  if(isposted == 1) return;
  // Check if it should add a star reaction
  /*if(message.reactions->size == 0) {
    // Add the star reaction
    discord_create_reaction(client, message.channel_id, message.id, 0, "⭐", NULL);
  }*/
  int i;
  while(i < message.reactions->size) {
    // Check if the emoji is a star
    if(strcmp(message.reactions->array[i].emoji->name, "⭐") == 0) {
      // Check if the message surpassed the minimum reaction count to be sent to the board
      if(message.reactions->array[0].count < 10) return; //! You can change me to whatever you want <3
      break;
    }
    i++;
  }
  // Check if the message surpassed the minimum reaction count to be sent to the board
  //if(message.reactions->array[0].count < 1) return; //! You can change me to whatever you want <3

  // Post it.
  sbclone_post_to_channel(client, &message, message_id, &event->message_id, &event->channel_id, &event->guild_id);
}

int sbclone_check_if_star_channel(u64snowflake channel_id) {
  sqlite3_stmt* stmt;
  char* sql = "SELECT * FROM channels WHERE channelid = ?";
  sqlite3_prepare_v2(sbclone_DB, sql, strlen(sql), &stmt, NULL);
  char char_channel_id[20];
  snowflake_to_char((char *)&char_channel_id, channel_id);
  sqlite3_bind_text(stmt, 1, char_channel_id, strlen(char_channel_id), SQLITE_STATIC);

  int rc = sqlite3_step(stmt);
  switch(rc) {
    case SQLITE_ROW:
      // Check if the channelid from the database is char_channel_id
      if (strcmp((const char *)sqlite3_column_text(stmt, 1), (const char *)&char_channel_id) == 0 &&
          sqlite3_column_int(stmt, 3) == 0 // Check if the channel is a board channel
      ) {
        sqlite3_finalize(stmt);
        return 1;
      }
      break;
    case SQLITE_DONE:
      // Not found
      sqlite3_finalize(stmt);
      return 0;

    default:
      // Error
      fprintf(stderr, "Couldn't query star channel.\n");
      break;
  }
  sqlite3_finalize(stmt);

  return 0;
}

void sbclone_post_to_channel(struct discord* client, struct discord_message* message, char* message_id, const u64snowflake* event_message_id, const u64snowflake* event_channel_id, const u64snowflake* event_guild_id) {
  // Set as posted
  sqlite3_stmt* isPostedStatement;
  sqlite3_prepare_v2(sbclone_DB, "UPDATE posts SET isposted=1 WHERE messageid=?;", -1, &isPostedStatement, NULL);
  sqlite3_bind_text(isPostedStatement, 1, message_id, strlen(message_id), SQLITE_STATIC);
  sqlite3_step(isPostedStatement);
  sqlite3_finalize(isPostedStatement);

  struct discord_attachments* atts = message->attachments;
  char content[60];
  snprintf(content, sizeof(content), "<@%" PRIu64 "> | <#%" PRIu64 ">", message->author->id, message->channel_id);

  // Get the user object for the embed author
  CCORDcode code;
  struct discord_user user;
  struct discord_ret_user user_ret = { .sync = &user };
  code = discord_get_user(client, message->author->id, &user_ret); // valgrind complains to this
  assert(CCORD_OK == code && "Couldn't fetch user.");

  // Get the user's avatar
  char full_avatar_string[95];
  snprintf(full_avatar_string, sizeof(full_avatar_string), "https://cdn.discordapp.com/avatars/%" PRIu64 "/%s.png", user.id, user.avatar);

  // Combine all attachments links into a string
  struct discord_attachments post_attachments;
  struct discord_attachment arrAtt[10];
  // For the downloaded attachments to be free'd at the end
  void* voidArr[10];

  post_attachments.size = atts->size;

  int i = 0;
  while(i < atts->size) {
    CURL *curl_handle;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, atts->array[i].url);

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

    /* some servers do not like requests that are made without a user-agent
      field, so we provide one */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* get it! */
    res = curl_easy_perform(curl_handle);

    /* check for errors */
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    else {
      /*
      * Now, our chunk.memory points to a memory block that is chunk.size
      * bytes big and contains the remote file.
      *
      * Do something nice with it!
      */

      struct discord_attachment singular_post_attachment = {
        .content = chunk.memory,
        .size = chunk.size,
        .filename = atts->array[i].filename,
      };

      arrAtt[i] = singular_post_attachment;
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
    voidArr[i] = chunk.memory;
    i++;
  }

  post_attachments.array = arrAtt;

  struct discord_embed postEmbed = {
    .color = 0xfcf403, // pissy yellow
    .description = message->content,
    .author = &(struct discord_embed_author) {
      .name = user.username,
      .icon_url = full_avatar_string
    },
  };

  // The message to be posted on the board
  struct discord_create_message params = {
    .content = content,

    .embeds = &(struct discord_embeds) {
      .size = 1,
      .array = &postEmbed
    },
  };

  // Checks if it should add attachments
  if(message->attachments->size > 0) {
    params.attachments = &post_attachments;
  }

  // Create message ret
  struct discord_message sent_message;
  struct discord_ret_message sent_message_ret = { .sync = &sent_message };

  // Get the board channel
  u64snowflake board_channel;
  sbclone_get_board_channel(&board_channel, *event_guild_id);

  // Send message to the board channel
  code = discord_create_message(client, board_channel, &params, &sent_message_ret);
  //assert(CCORD_OK == code && "Couldn't fetch message.");

  // Create a star reaction
  discord_create_reaction(client, sent_message.channel_id, sent_message.id, 0, "⭐", NULL);

  i = 0;
  while (i < atts->size) {
    free(voidArr[i]); // Free all the attachments

    i++;
  }
}

void sbclone_get_board_channel(u64snowflake* buf, u64snowflake guild_id) {
  sqlite3_stmt* stmt;
  char* sql = "SELECT * FROM channels WHERE guildid = ? AND isboardchannel = 1";
  sqlite3_prepare_v2(sbclone_DB, sql, strlen(sql), &stmt, NULL);
  char char_guild_id[20];
  snowflake_to_char((char *)char_guild_id, guild_id);
  sqlite3_bind_text(stmt, 1, char_guild_id, strlen(char_guild_id), SQLITE_STATIC);

  int rc = sqlite3_step(stmt);
  switch(rc) {
    case SQLITE_ROW:
      // Check if the channelid from the database is char_channel_id
      *buf = char_to_snowflake((char *)sqlite3_column_text(stmt, 1));
      break;
    case SQLITE_DONE:
      // Not found
      buf = NULL;
      break;

    default:
      // Error
      fprintf(stderr, "Couldn't query board channel.\n");
      buf = NULL;
      break;
  }
  sqlite3_finalize(stmt);
}

void sbclone_create_row(char* message_id, char* author_id) {
  sqlite3_stmt* insertStatement;
  sqlite3_prepare_v2(sbclone_DB, "INSERT INTO posts (userid, messageid, isposted) VALUES (?1, ?2, false)", -1, &insertStatement, NULL);
  sqlite3_bind_text(insertStatement, 1, author_id, strlen(author_id), SQLITE_STATIC);
  sqlite3_bind_text(insertStatement, 2, message_id, strlen(message_id), SQLITE_STATIC);
  sqlite3_step(insertStatement);
  sqlite3_finalize(insertStatement);
}

int sbclone_add_channel(char* channel_id, char* guild_id, int is_board_channel) {
  // It makes sure that you don't have duplicate board channels
  if(is_board_channel) {
    if(sbclone_check_for_multiple_board_channels(guild_id) >= 1) {
      return 1;
    }
  }

  // Checks if you're trying to add a channel, thats already in the database
  if(sbclone_check_for_multiple_channels(channel_id) >= 1) {
    return 2;
  }

  sqlite3_stmt* insertStatement;
  sqlite3_prepare_v2(sbclone_DB, "INSERT INTO channels (channelid, guildid, isboardchannel) VALUES (?1, ?2, ?3)", -1, &insertStatement, NULL);
  sqlite3_bind_text(insertStatement, 1, channel_id, strlen(channel_id), SQLITE_STATIC);
  sqlite3_bind_text(insertStatement, 2, guild_id, strlen(channel_id), SQLITE_STATIC);
  sqlite3_bind_int(insertStatement, 3, is_board_channel);
  sqlite3_step(insertStatement);
  sqlite3_finalize(insertStatement);

  return 0;
}

int sbclone_check_for_multiple_board_channels(char* guild_id) {
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(sbclone_DB, "SELECT * FROM channels WHERE guildid = ? AND isboardchannel = 1", -1, &stmt, NULL);
  sqlite3_bind_text(stmt, 1, guild_id, strlen(guild_id), SQLITE_STATIC);
  int ret_val = sbclone_multi_channel_check(stmt);
  return ret_val;
}

int sbclone_check_for_multiple_channels(char* channel_id) {
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(sbclone_DB, "SELECT * FROM channels WHERE channelid = ?", -1, &stmt, NULL);
  sqlite3_bind_text(stmt, 1, channel_id, strlen(channel_id), SQLITE_STATIC);
  int ret_val = sbclone_multi_channel_check(stmt);
  return ret_val;
}

int sbclone_multi_channel_check(sqlite3_stmt* stmt) {
  int ret_val = 0;
  while(sqlite3_step(stmt) == SQLITE_ROW) {
    ret_val++;
  }
  sqlite3_finalize(stmt);
  return ret_val;
}
