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
  int ret = snprintf(payload, sizeof(payload), "{\"content\":\"%s\"}", content);
  ASSERT_S(ret < sizeof(payload), "out-of-bounds write of payload");

  Discord_api_request( 
    &client->api,
    NULL,
    NULL,
    payload,
    POST, CHANNEL "/messages", channel_id);
}
