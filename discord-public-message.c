#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>

#include "discord-common.h"

discord_message_t*
discord_message_init()
{
  discord_message_t *new_message = calloc(1, sizeof *new_message);
  if (NULL == new_message) return NULL;

  new_message->id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_message->id) goto cleanupA;

  new_message->channel_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_message->channel_id) goto cleanupB;

  new_message->guild_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_message->guild_id) goto cleanupC;

  new_message->content = malloc(MAX_MESSAGE_LEN);
  if (NULL == new_message->content) goto cleanupD;

  new_message->timestamp = malloc(SNOWFLAKE_TIMESTAMP);
  if (NULL == new_message->timestamp) goto cleanupE;

  new_message->edited_timestamp = malloc(SNOWFLAKE_TIMESTAMP);
  if (NULL == new_message->edited_timestamp) goto cleanupF;

  new_message->nonce = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_message->nonce) goto cleanupG;

  new_message->webhook_id = malloc(SNOWFLAKE_INTERNAL_WORKER_ID);
  if (NULL == new_message->webhook_id) goto cleanupH;

  return new_message;

cleanupH:
  free(new_message->nonce);
cleanupG:
  free(new_message->edited_timestamp);
cleanupF:
  free(new_message->timestamp);
cleanupE:
  free(new_message->content);
cleanupD:
  free(new_message->guild_id);
cleanupC:
  free(new_message->channel_id);
cleanupB:
  free(new_message->id);
cleanupA:
  free(new_message);

  return NULL;
}

void
discord_message_cleanup(discord_message_t *message)
{
  free(message->id);
  free(message->channel_id);
  free(message->guild_id);
  free(message->content);
  free(message->timestamp);
  free(message->edited_timestamp);
  free(message->nonce);
  free(message->webhook_id);
  free(message);
}

/* See: https://discord.com/developers/docs/resources/channel#create-message */
void
discord_send_message(discord_t *client, char channel_id[], char content[])
{
  char fmt_json[] = "{\"content\":\"%s\"}";
  char json[MAX_MESSAGE_LEN];
  
  snprintf(json, MAX_MESSAGE_LEN-1, fmt_json, content);

  //set ptr to data data that will be read by callback
  CURLcode ecode = curl_easy_setopt(client->api.ehandle, CURLOPT_POSTFIELDS, json);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  Discord_api_request( 
    &client->api,
    NULL,
    NULL,
    POST, CHANNEL_MESSAGES, channel_id);
}
