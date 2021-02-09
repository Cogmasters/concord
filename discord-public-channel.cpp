#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace channel {

void
json_load(char *str, size_t len, void *p_channel)
{
  dati *channel = (dati*)p_channel;

  json_scanf(str, len,
     "[id]%F"
     "[type]%d"
     "[guild_id]%F"
     "[position]%d"
     "[name]%s"
     "[topic]%s"
     "[nfsw]%b"
     "[last_message_id]%F"
     "[bitrate]%d"
     "[user_limit]%d"
     "[rate_limit_per_user]%d"
     "[recipients]%F"
     "[icon]%s"
     "[owner_id]%F"
     "[application_id]%F"
     "[parent_id]%F"
     "[last_pin_timestamp]%F"
     "[messages]%F",
     &orka_strtoull, &channel->id,
     &channel->type,
     &orka_strtoull, &channel->guild_id,
     &channel->position,
     channel->name,
     channel->topic,
     &channel->nsfw,
     &orka_strtoull, &channel->last_message_id,
     &channel->bitrate,
     &channel->user_limit,
     &channel->rate_limit_per_user,
     &user::json_list_load, &channel->recipients,
     channel->icon,
     &orka_strtoull, &channel->owner_id,
     &orka_strtoull, &channel->application_id,
     &orka_strtoull, &channel->parent_id,
     &orka_iso8601_to_unix_ms, &channel->last_pin_timestamp,
     &message::json_list_load, &channel->messages);

  D_NOTOP_PUTS("Channel object loaded with API response");
}

dati*
init()
{
  dati *new_channel = (dati*)calloc(1, sizeof(dati));
  return new_channel;
}

void
cleanup(dati *channel) {
  free(channel);
}

void
get(client *client, const uint64_t channel_id, dati *p_channel)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
    return;
  }

  struct resp_handle resp_handle = {&json_load, (void*)p_channel};

  user_agent::run(
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/channels/%llu", channel_id);
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

  struct sized_buffer req_body = {"", 0};

  user_agent::run( 
    &client->ua,
    NULL,
    &req_body, //empty POSTFIELDS
    HTTP_PUT, 
    "channels/%llu/pins/%llu", channel_id, message_id);
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

  struct sized_buffer req_body = {"", 0};

  user_agent::run( 
    &client->ua,
    NULL,
    &req_body, //empty POSTFIELDS
    HTTP_DELETE,
    "channels/%llu/pins/%llu", channel_id, message_id);
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

  message->referenced_message = init();

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
     "[flags]%d"
     "[referenced_message]%F",
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
      &message->flags,
      &json_load, message->referenced_message);

  if(!message->referenced_message->id)
  {
    cleanup(message->referenced_message);
    message->referenced_message = NULL;
  }

  D_NOTOP_PUTS("Message object loaded with API response"); 
}

void
json_list_load(char *str, size_t len, void *p_messages)
{
  struct sized_buffer **buf = NULL;
  json_scanf(str, len, "[]%A", &buf);

  size_t n = ntl_length((void**)buf);
  dati **new_messages = (dati **)ntl_calloc(n, sizeof(dati*));
  for (size_t i = 0; buf[i]; i++) {
    new_messages[i] = init();
    json_load(buf[i]->start, buf[i]->size, new_messages[i]);
  }

  free(buf);

  *(dati ***)p_messages = new_messages;
}

dati*
init()
{
  dati *new_message = (dati*)calloc(1, sizeof(dati));
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
    D_PRINT("Content length exceeds 2000 characters threshold (%zu)", strlen(params->content));
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

  struct sized_buffer req_body = {payload, strlen(payload)};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    &req_body,
    HTTP_POST, 
    "/channels/%llu/messages", channel_id);
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

  user_agent::run(
    &client->ua,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%llu/messages/%llu", channel_id, message_id);
}

} // namespace message

} // namespace channel
} // namespace discord
