#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace channel {

dati*
init()
{
  dati *new_channel = (dati*)calloc(1, sizeof *new_channel);
  return new_channel;
}

void
cleanup(dati *channel) {
  free(channel);
}

void
pin_message(client *client, const uint64_t channel_id, const uint64_t message_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  struct resp_handle resp_handle = {NULL, NULL};
  struct sized_buffer body = {"", 0};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &body, //empty POSTFIELDS
    HTTP_PUT, PINNED_MESSAGE, channel_id, message_id);
}

void
unpin_message(client *client, const uint64_t channel_id, const uint64_t message_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  struct resp_handle resp_handle = {NULL, NULL};
  struct sized_buffer body = {"", 0};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &body, //empty POSTFIELDS
    HTTP_DELETE, PINNED_MESSAGE, channel_id, message_id);
}

namespace message {

void
json_load(char *str, size_t len, void *p_message)
{
  dati *message = (dati*)p_message;

  if (message->nonce) {
    free(message->nonce);
    message->nonce = NULL;
  }

  json_scanf(str, len,
     "[id]%F"
     "[channel_id]%F"
     "[guild_id]%F"
     "[author]%F"
     "[member]%F"
     "[content]%s"
     "[timestamp]%F"
     "[edited_timestamp]%F"
     "[tts]%b"
     "[mention_everyone]%b"
     //"[mentions]%F"
     "[nonce]%?s"
     "[pinned]%b"
     "[webhook_id]%F"
     "[type]%d"
     "[flags]%d",
     //"[referenced_message]%F",
      &orka_strtoull, &message->id,
      &orka_strtoull, &message->channel_id,
      &orka_strtoull, &message->guild_id,
      &user::json_load, message->author,
      &guild::member::json_load, message->member,
      message->content,
      &orka_iso8601_to_unix_ms, &message->timestamp,
      &orka_iso8601_to_unix_ms, &message->edited_timestamp,
      &message->tts,
      &message->mention_everyone,
      &message->nonce,
      &message->pinned,
      &orka_strtoull, &message->webhook_id,
      &message->type,
      &message->flags);

  D_NOTOP_PUTS("Message object loaded with API response"); 
}

static dati*
message_init()
{
  dati *new_message = (dati*)calloc(1, sizeof *new_message);
  if (NULL == new_message) return NULL;

  new_message->author = user::init();
  if (NULL == new_message->author) goto cleanupA;

  new_message->member = guild::member::init();
  if (NULL == new_message->member) goto cleanupB;

  return new_message;

cleanupB:
  user::cleanup(new_message->author);
cleanupA:
  free(new_message);

  return NULL;
}

dati*
init()
{
  dati *new_message = message_init();
  if (NULL == new_message) return NULL;

  new_message->referenced_message = message_init();
  if (NULL == new_message->referenced_message) {
    cleanup(new_message);
    return NULL;
  }

  return new_message;
}

static void
message_cleanup(dati *message)
{
  if (message->nonce)
    free(message->nonce);
  if (message->author)
    user::cleanup(message->author);
  if (message->member)
    guild::member::cleanup(message->member);

  free(message);
}

void
cleanup(dati *message)
{
  if (message->referenced_message) {
    message_cleanup(message->referenced_message);
  }
  message_cleanup(message);
}

namespace create {

void
run(client *client, const uint64_t channel_id, params *params, dati *p_message)
{
  if (!channel_id) {
    D_PUTS("Can't send message to Discord: missing 'channel_id'");
    return;
  }
  if (IS_EMPTY_STRING(params->content)) {
    D_PUTS("Can't send an empty message to Discord: missing 'content'");
    return;
  }
  if (strlen(params->content) >= MAX_MESSAGE_LEN) {
    D_PRINT("Content length exceeds 2000 characters threshold (%u)", strlen(params->content));
    return;
  }

  char payload[MAX_PAYLOAD_LEN];
  int ret = json_snprintf(payload, MAX_PAYLOAD_LEN,
      "{|content|:|%s|}", params->content);
  ASSERT_S(ret < MAX_PAYLOAD_LEN, "Out of bounds write attempt");

  struct resp_handle resp_handle = {
    .ok_cb = p_message ? json_load : NULL,
    .ok_obj = p_message,
    .err_cb = NULL, 
    .err_obj = NULL};

  struct sized_buffer body = {payload, strlen(payload)};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &body,
    HTTP_POST, CHANNEL MESSAGES, channel_id);
}

} // namespace create

void
del(client *client, const uint64_t channel_id, const uint64_t message_id)
{
  if (!channel_id) {
    D_PUTS("Can't delete message: missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Can't delete message: missing 'message_id'");
    return;
  }

  struct resp_handle resp_handle = {NULL, NULL, NULL, NULL};
  struct sized_buffer body = {NULL, 0};

  user_agent::run(
    &client->ua,
    &resp_handle,
    &body,
    HTTP_DELETE, CHANNEL MESSAGE, channel_id, message_id);
}

} // namespace message

} // namespace channel
} // namespace discord
