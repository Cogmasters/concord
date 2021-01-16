#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

static discord_message_t*
referenced_message_init()
{
  discord_message_t *new_message = calloc(1, sizeof *new_message);
  if (NULL == new_message) return NULL;

  new_message->author = discord_user_init();
  if (NULL == new_message->author) goto cleanup;

  return new_message;

cleanup:
  free(new_message);

  return NULL;
}

discord_message_t*
discord_message_init()
{
  discord_message_t *new_message = calloc(1, sizeof *new_message);
  if (NULL == new_message) return NULL;

  new_message->author = discord_user_init();
  if (NULL == new_message->author) goto cleanupA;
  
  new_message->referenced_message = referenced_message_init();
  if (NULL == new_message->referenced_message) goto cleanupB;

  return new_message;

cleanupB:
  free(new_message->author);
cleanupA:
  free(new_message);

  return NULL;
}

void
Discord_public_load_message(void *p_message, char *str, size_t len)
{
  discord_message_t *message = p_message;

  struct json_token token_author;
  struct json_token token_mentions;
  struct json_token token_referenced_message;

  json_scanf(str, len,
     "[id]%s"
     "[channel_id]%s"
     "[guild_id]%s"
     "[author]%T"
     "[content]%s"
     "[timestamp]%s"
     "[edited_timestamp]%s"
     "[tts]%b"
     "[mention_everyone]%b"
     "[mentions]%T"
     "[nonce]%s"
     "[pinned]%b"
     "[webhook_id]%s"
     "[type]%d"
     "[flags]%d"
     "[referenced_message]%T",
      message->id,
      message->channel_id,
      message->guild_id,
      &token_author,
      message->content,
      message->timestamp,
      message->edited_timestamp,
      &message->tts,
      &message->mention_everyone,
      &token_mentions,
      message->nonce,
      &message->pinned,
      message->webhook_id,
      &message->type,
      &message->flags,
      &token_referenced_message);

  Discord_public_load_user(message->author, token_author.start, token_author.length);

  D_PUTS("Message loaded with API response"); 
}

static void
referenced_message_cleanup(discord_message_t *message)
{
  discord_user_cleanup(message->author);

  free(message);
}

void
discord_message_cleanup(discord_message_t *message)
{
  discord_user_cleanup(message->author);
  referenced_message_cleanup(message->referenced_message);

  free(message);
}

/* See: https://discord.com/developers/docs/resources/channel#create-message */
void
discord_send_message(discord_t *client, const char channel_id[], const char content[])
{
  if (IS_EMPTY_STRING(channel_id)) {
    D_PUTS("Can't send message to Discord: missing 'channel_id'");
    return;
  }
  if (IS_EMPTY_STRING(content)) {
    D_PUTS("Can't send an empty message to Discord: missing 'content'");
    return;
  }

  char payload[MAX_PAYLOAD_LEN];
  int ret = snprintf(payload, sizeof(payload)-1, "{\"content\":\"%s\"}", content);
  ASSERT_S(ret < (int)sizeof(payload)-1, "out-of-bounds write of payload");

  Discord_api_request( 
    &client->api,
    NULL,
    NULL,
    payload,
    POST, CHANNEL_MESSAGES, channel_id);
}
