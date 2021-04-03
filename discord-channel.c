#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-common.h"
#include "orka-utils.h"


void
discord_get_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
    return;
  }

  struct ua_resp_handle resp_handle =
    { .ok_cb = &discord_channel_from_json_v, .ok_obj = (void*)p_channel};

  discord_adapter_run(
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/channels/%llu", channel_id);
}

void
discord_delete_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
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
    "/channels/%llu", channel_id);
}

void
discord_add_pinned_channel_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  discord_adapter_run( 
    &client->adapter,
    NULL,
    NULL,
    HTTP_PUT, 
    "/channels/%llu/pins/%llu", channel_id, message_id);
}

void
discord_delete_pinned_channel_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }

  discord_adapter_run( 
    &client->adapter,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%llu/pins/%llu", channel_id, message_id);
}

void
discord_get_channel_messages(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  struct discord_get_channel_messages_params *params, 
  NTL_T(struct discord_message) *p_messages)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!params) {
    D_PUTS("Missing 'params'");
    return;
  }
  if (params->limit < 1 || params->limit > 100) {
    D_PUTS("'limit' value should be in an interval of (1-100)");
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
    "/channels/%llu/messages%s%s%s", 
    channel_id, limit_query, around_query, before_query, after_query);
}

void
discord_delete_message(
  struct discord *client, 
  u64_snowflake_t channel_id, 
  u64_snowflake_t message_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }
  discord_adapter_run(
    &client->adapter,
    NULL,
    NULL,
    HTTP_DELETE,
    "/channels/%llu/messages/%llu", channel_id, message_id);
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
    D_PUTS("Can't perform action unless client has an active websockets connection");
    return;
  }
  if (!channel_id) {
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!params) {
    D_PUTS("Missing 'params'");
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
        D_PUTS("Missing 'content'");
        return;
      }
      if (strlen(params->content) >= MAX_MESSAGE_LEN) {
        D_PRINT("Content length exceeds %d characters threshold (%zu)",
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

    char payload[MAX_PAYLOAD_LEN];
    json_inject(payload, sizeof(payload),
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

    struct sized_buffer req_body = {payload, strlen(payload)};

    discord_adapter_run( 
      &client->adapter,
      &resp_handle,
      &req_body,
      HTTP_POST, 
      "/channels/%llu/messages", channel_id);
  }
  else 
  { // content-type is multipart/form-data
    ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");

    ua_mime_setopt(client->adapter.ua, params, &curl_mime_cb);

    discord_adapter_run( 
      &client->adapter,
      &resp_handle,
      NULL,
      HTTP_MIMEPOST, "/channels/%llu/messages", channel_id);

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
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
    return;
  }
  if (!params) {
    D_PUTS("Missing 'params'");
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
    "/channels/%llu/messages/%llu", channel_id, message_id);
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
    D_PUTS("Missing 'channel_id'");
    return;
  }
  if (!message_id) {
    D_PUTS("Missing 'message_id'");
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
    "/channels/%llu/messages/%llu/reactions/%s/@me", 
    channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);
}

void
discord_trigger_typing_indicator(struct discord* client, u64_snowflake_t channel_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
    return;
  }

  discord_adapter_run( 
    &client->adapter,
    NULL,
    NULL,
    HTTP_POST, 
    "/channels/%llu/typing", channel_id);
}
