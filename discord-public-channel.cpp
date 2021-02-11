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

void
init_dati(void *p_channel) {
  memset(p_channel, 0, sizeof(dati));
}

dati*
alloc_dati()
{
  dati *new_channel = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_channel);
  return new_channel;
}

void
cleanup_dati(void *p_channel) {
}

void
free_dati(dati *channel)
{
  cleanup_dati((void*)channel);
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

  message->referenced_message = alloc_dati();

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

  if(!message->referenced_message->id) {
    free_dati(message->referenced_message);
    message->referenced_message = NULL;
  }

  D_NOTOP_PUTS("Message object loaded with API response"); 
}

void
json_list_load(char *str, size_t len, void *p_messages)
{
  struct ntl_deserializer deserializer = {
    .elem_size = sizeof(dati),
    .init_elem = &init_dati,
    .elem_from_buf = &json_load,
    .ntl_recipient_p = (void***)p_messages
  };
  orka_str_to_ntl(str, len, &deserializer);
}

void
init_dati(void *p_message)
{
  dati *message = (dati*)p_message;

  memset(message, 0, sizeof(dati));
  message->author = user::alloc_dati();
  message->member = guild::member::alloc_dati();
}

dati*
alloc_dati()
{
  dati *new_message = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_message);
  return new_message;
}

void
cleanup_dati(void *p_message)
{
  dati *message = (dati*)p_message;

  if (message->nonce)
    free(message->nonce);
  if (message->author)
    user::free_dati(message->author);
  if (message->member)
    guild::member::free_dati(message->member);
  if (message->referenced_message) {
    cleanup_dati(message->referenced_message);
    free(message->referenced_message);
  }
}

void
free_dati(dati *message)
{
  cleanup_dati((void*)message);
  free(message);
}

void
free_list(dati **messages) {
  ntl_free((void**)messages, &cleanup_dati);
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

namespace reference {

void
init_dati(void *p_reference) {
  memset(p_reference, 0, sizeof(dati));
}

dati*
alloc_dati()
{
  dati *new_reference = (dati*)malloc(sizeof(dati));
  init_dati((void*)new_reference);
  return new_reference;
}

void
free_dati(dati *reference) {
  free(reference);
}

void
json_load(char *str, size_t len, void *p_reference)
{
  dati *reference = (dati*)p_reference;

  json_scanf(str, len,
     "[message_id]%F"
     "[channel_id]%F"
     "[guild_id]%F",
      &orka_strtoull, &reference->message_id,
      &orka_strtoull, &reference->channel_id,
      &orka_strtoull, &reference->guild_id);
}

}

} // namespace message

} // namespace channel
} // namespace discord
