#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


void
discord_get_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel)
{
  if (!channel_id) {
    log_error("Missing 'channel_id");
    return;
  }

  struct ua_resp_handle resp_handle =
    { .ok_cb = &discord_channel_from_json_v, .ok_obj = (void*)p_channel};

  discord_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/channels/%"PRIu64, channel_id);
}

void
discord_delete_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel)
{
  if (!channel_id) {
    log_error("Missing 'channel_id");
    return;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_channel ? discord_channel_from_json_v : NULL,
    .ok_obj = p_channel,
  };

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_DELETE,
    "/channels/%"PRIu64, channel_id);
}

void
discord_add_pinned_channel_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return;
  }

  discord_adapter_run( 
    &client->adapter,
    NULL,
    NULL,
    HTTP_PUT, 
    "/channels/%"PRIu64"/pins/%"PRIu64, channel_id, message_id);
}

void
discord_delete_pinned_channel_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return;
  }

  discord_adapter_run( 
    &client->adapter,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%"PRIu64"/pins/%"PRIu64, channel_id, message_id);
}

void
discord_get_channel_messages(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  struct discord_get_channel_messages_params *params, 
  NTL_T(struct discord_message) *p_messages)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!params) {
    log_error("Missing 'params'");
    return;
  }
  if (params->limit < 1 || params->limit > 100) {
    log_error("'limit' value should be in an interval of (1-100)");
    return;
  }

  char limit_query[64];
  snprintf(limit_query, sizeof(limit_query),
      "?limit=%d", params->limit);

  char around_query[64] = "";
  if (params->around) {
    snprintf(around_query, sizeof(around_query),
        "&around=%" PRIu64 , params->around);
  }

  char before_query[64] = "";
  if (params->before) {
    snprintf(before_query, sizeof(before_query),
        "&before=%" PRIu64 , params->before);
  }

  char after_query[64] = "";
  if (params->after) {
    snprintf(after_query, sizeof(after_query),
        "&after=%" PRIu64 , params->after);
  }

  struct ua_resp_handle resp_handle = 
    { .ok_cb = &discord_message_list_from_json_v, .ok_obj = (void*)p_messages};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/channels/%"PRIu64"/messages%s%s%s", 
    channel_id, limit_query, around_query, before_query, after_query);
}

void
discord_get_channel_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id,
  struct discord_message *p_message)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return;
  }
  if (!p_message) {
    log_error("Missing 'p_message'");
    return;
  }

  struct ua_resp_handle resp_handle = 
    { .ok_cb = &discord_message_from_json_v, .ok_obj = p_message };

  discord_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/channels/%"PRIu64"/messages/%"PRIu64, channel_id, message_id);
}

void
discord_delete_message(
  struct discord *client, 
  u64_snowflake_t channel_id, 
  u64_snowflake_t message_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return;
  }
  discord_adapter_run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%"PRIu64"/messages/%"PRIu64, channel_id, message_id);
}

// @todo add duplicated ID verification

void discord_bulk_delete_messages(struct discord *client, u64_snowflake_t channel_id, NTL_T(u64_snowflake_t) messages)
{
  char *json = NULL;

  if(!messages) {
    log_error("Missing 'messages'");
    return;
  }

  size_t count = ntl_length_max((ntl_t)messages, 101);
  if(count < 2 || count > 100)
  {
    log_error("Message count should be between 2 and 100");
    return;
  }

  u64_unix_ms_t now = orka_timestamp_ms();
  for(size_t i = 0; messages[i]; i++)
  {
    u64_unix_ms_t timestamp = (*messages[i] >> 22) + 1420070400000;
    if(now > timestamp && now - timestamp > 1209600000)
    {
      log_error("Messages should not be older than 2 weeks.");
      return;
    }
  }

  size_t len = json_ainject(&json,
    "(messages):F",
    ja_u64_list_to_json, (NTL_T(ja_u64))messages);

  struct sized_buffer req_body = {
    .start = json,
    .size = len
  };

  discord_adapter_run(
    &client->adapter,
    NULL,
    &req_body,
    HTTP_POST,
    "/channels/%"PRIu64"/messages/bulk-delete", channel_id);

  free(json);
}

//@todo this is a temporary solution
static curl_mime*
curl_mime_cb(CURL *ehandle, void *data) 
{
  struct discord_create_message_params *params = data;

  curl_mime *mime = curl_mime_init(ehandle);
  curl_mimepart *part = curl_mime_addpart(mime);

  if (params->file.content) {
    if (!params->file.name) { // set a default name
      params->file.name = "a.out";
    }
    curl_mime_data(part, params->file.content, params->file.size);
    curl_mime_filename(part, params->file.name);
    curl_mime_type(part, "application/octet-stream");
  }
  else { //params->filename exists 
    curl_mime_filedata(part, params->file.name);
  }

  curl_mime_name(part, "file");

  return mime;
}

void
discord_create_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  struct discord_create_message_params *params, 
  struct discord_message *p_message)
{
  if (ws_get_status(client->gw.ws) != WS_CONNECTED) {
    log_warn("Can't perform action unless client has an active websockets connection");
    return;
  }
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!params) {
    log_error("Missing 'params'");
    return;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_message ? &discord_message_from_json_v : NULL,
    .ok_obj = p_message,
  };

  if (!params->file.name && !params->file.content)
  {  // content-type is application/json
    if (!params->embed) {
      if (IS_EMPTY_STRING(params->content)) {
        log_error("Missing 'content'");
        return;
      }
      if (strlen(params->content) >= MAX_MESSAGE_LEN) {
        log_error("Content length exceeds %d characters threshold (%zu)",
            MAX_MESSAGE_LEN, strlen(params->content));
        return;
      }
    }

    void *A[6] = {0}; // pointer availability array
    if (params->content)
      A[0] = (void *)params->content;
    if (params->nonce)
      A[1] = (void *)params->nonce;
    if (true == params->tts)
      A[2] = (void *)&params->tts;
    if (params->embed)
      A[3] = (void *)params->embed;
    /* @todo change current A[4] to A[5]
    if (params->allowed_mentions)
      A[4] = (void *)params->allowed_mentions;
    */
    if (params->message_reference)
      A[4] = (void *)params->message_reference;

    char *payload=NULL;
    size_t ret = json_ainject(&payload,
                  "(content):s"
                  "(nonce):s"
                  "(tts):b"
                  "(embed):F"
                  /* @todo
                  "(allowed_mentions):F"
                  */
                  "(message_reference):F"
                  "@arg_switches",
                  params->content,
                  params->nonce,
                  &params->tts,
                  &discord_embed_to_json, params->embed,
                  /* @todo
                  params->allowed_mentions,
                  */
                  &discord_message_reference_to_json, params->message_reference,
                  A, sizeof(A));

    if (!payload) {
      log_error("Couldn't create JSON Payload");
      return;
    }

    struct sized_buffer req_body = {payload, ret};

    discord_adapter_run( 
      &client->adapter,
      &resp_handle,
      &req_body,
      HTTP_POST, 
      "/channels/%"PRIu64"/messages", channel_id);

    free(payload);
  }
  else 
  { // content-type is multipart/form-data
    ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");

    ua_mime_setopt(client->adapter.ua, params, &curl_mime_cb);

    discord_adapter_run( 
      &client->adapter,
      &resp_handle,
      NULL,
      HTTP_MIMEPOST, "/channels/%"PRIu64"/messages", channel_id);

    //set back to default
    ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");
  }
}

void
discord_edit_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id, 
  struct discord_edit_message_params *params, 
  struct discord_message *p_message)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return;
  }
  if (!params) {
    log_error("Missing 'params'");
    return;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_message ? &discord_message_from_json_v : NULL,
    .ok_obj = p_message,
  };

  char payload[MAX_PAYLOAD_LEN];

  void *A[4] = {0}; // pointer availability array

  A[0] = params->content;
  A[1] = params->embed;
  A[2] = params->flags;
  // A[3] = params->allowed_mentions;

  json_inject(payload, sizeof(payload),
    "(content):s"
    "(embed):F"
    "(flags):d"
    //"(allowed_mentions):F"
    "@arg_switches",
    params->content,
    &discord_embed_to_json, params->embed,
    params->flags,
    A, sizeof(A));
    //&allowed_mentions_to_json, params->allowed_mentions);

  struct sized_buffer req_body = { payload, strlen(payload) };

  discord_adapter_run(&client->adapter,
    &resp_handle,
    &req_body,
    HTTP_PATCH,
    "/channels/%"PRIu64"/messages/%"PRIu64, channel_id, message_id);
}

void 
discord_create_reaction(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id, 
  const u64_snowflake_t emoji_id, 
  const char emoji_name[])
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return;
  }

  char *pct_emoji_name = (emoji_name) 
                  ? url_encode((char*)emoji_name)
                  : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64, pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  discord_adapter_run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_PUT,
    "/channels/%"PRIu64"/messages/%"PRIu64"/reactions/%s/@me", 
    channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);
}

void
discord_delete_all_reactions(
  struct discord *client, 
  u64_snowflake_t channel_id, 
  u64_snowflake_t message_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return;
  }

  discord_adapter_run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%"PRIu64"/messages/%"PRIu64"/reactions", 
    channel_id, message_id);
}

void 
discord_delete_all_reactions_for_emoji(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id, 
  const u64_snowflake_t emoji_id, 
  const char emoji_name[])
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return;
  }

  char *pct_emoji_name = (emoji_name) 
                  ? url_encode((char*)emoji_name)
                  : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64, pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  discord_adapter_run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%"PRIu64"/messages/%"PRIu64"/reactions/%s", 
    channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);
}

void
discord_trigger_typing_indicator(struct discord* client, u64_snowflake_t channel_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id");
    return;
  }

  discord_adapter_run( 
    &client->adapter,
    NULL,
    NULL,
    HTTP_POST, 
    "/channels/%"PRIu64"/typing", channel_id);
}
