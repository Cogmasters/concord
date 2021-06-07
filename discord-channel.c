#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


ORCAcode
discord_get_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel)
{
  if (!channel_id) {
    log_error("Missing 'channel_id");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_channel) {
    log_error("Missing 'p_channel'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_channel_from_json_v, 
    .ok_obj = p_channel
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64, channel_id);
}

ORCAcode
discord_modify_channel(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  struct discord_modify_channel_params *params, 
  struct discord_channel *p_channel)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_channel ? &discord_channel_from_json_v : NULL,
    .ok_obj = p_channel
  };

  char payload[MAX_PAYLOAD_LEN];
  size_t ret = discord_modify_channel_params_to_json(payload, sizeof(payload), params);

  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_PATCH,
           "/channels/%"PRIu64, channel_id);
}

ORCAcode
discord_delete_channel(struct discord *client, const u64_snowflake_t channel_id, struct discord_channel *p_channel)
{
  if (!channel_id) {
    log_error("Missing 'channel_id");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_channel ? discord_channel_from_json_v : NULL,
    .ok_obj = p_channel,
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64, channel_id);
}

ORCAcode
discord_get_channel_messages(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  struct discord_get_channel_messages_params *params, 
  NTL_T(struct discord_message) *p_messages)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }
  if (params->limit < 1 || params->limit > 100) {
    log_error("'limit' value should be in an interval of (1-100)");
    return ORCA_BAD_PARAMETER;
  }
  if (!p_messages) {
    log_error("Missing 'p_messages'");
    return ORCA_MISSING_PARAMETER;
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

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_message_list_from_json_v, 
    .ok_obj = p_messages 
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/channels/%"PRIu64"/messages%s%s%s", 
           channel_id, limit_query, around_query, before_query, after_query);
}

ORCAcode
discord_get_channel_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id,
  struct discord_message *p_message)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_message) {
    log_error("Missing 'p_message'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_message_from_json_v, 
    .ok_obj = p_message 
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64"/messages/%"PRIu64, channel_id, message_id);
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

ORCAcode
discord_create_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  struct discord_create_message_params *params, 
  struct discord_message *p_message)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_message ? &discord_message_from_json_v : NULL,
    .ok_obj = p_message
  };

  ORCAcode code;
  if (!params->file.name && !params->file.content)
  {  // content-type is application/json
    if (!params->embed) {
      if (IS_EMPTY_STRING(params->content)) {
        log_error("Missing 'content'");
        return ORCA_BAD_PARAMETER;
      }
      if (!orka_str_bounds_check(params->content, MAX_MESSAGE_LEN)) {
        log_error("Content length exceeds %d characters threshold (%zu)",
            MAX_MESSAGE_LEN, strlen(params->content));
        return ORCA_BAD_PARAMETER;
      }
    }

    void *A[6]={}; // pointer availability array
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
      return ORCA_BAD_JSON;
    }

    struct sized_buffer req_body = { payload, ret };

    code = discord_adapter_run( 
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

    code = discord_adapter_run( 
             &client->adapter,
             &resp_handle,
             NULL,
             HTTP_MIMEPOST, 
             "/channels/%"PRIu64"/messages", channel_id);

    //set back to default
    ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");
  }
  return code;
}

ORCAcode
discord_crosspost_message(
  struct discord *client,
  const u64_snowflake_t channel_id,
  const u64_snowflake_t message_id,
  struct discord_message *p_message)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_message ? &discord_message_from_json_v : NULL,
    .ok_obj = p_message
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_POST,
           "/channels/%"PRIu64"/messages/%"PRIu64"/crosspost", 
           channel_id, message_id);
}

ORCAcode 
discord_create_reaction(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id, 
  const u64_snowflake_t emoji_id, 
  const char emoji_name[])
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char *pct_emoji_name = (emoji_name) 
                  ? url_encode((char*)emoji_name)
                  : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64, pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_PUT,
           "/channels/%"PRIu64"/messages/%"PRIu64"/reactions/%s/@me", 
           channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_own_reaction(
  struct discord *client,
  const u64_snowflake_t channel_id,
  const u64_snowflake_t message_id,
  const u64_snowflake_t emoji_id,
  const char emoji_name[])
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char *pct_emoji_name = (emoji_name) 
                  ? url_encode((char*)emoji_name)
                  : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%"PRIu64, pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/messages/%"PRIu64"/reactions/%s/@me", 
           channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_user_reaction(
  struct discord *client,
  const u64_snowflake_t channel_id,
  const u64_snowflake_t message_id,
  const u64_snowflake_t user_id,
  const u64_snowflake_t emoji_id,
  const char emoji_name[])
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char *pct_emoji_name = (emoji_name) 
                  ? url_encode((char*)emoji_name)
                  : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%"PRIu64, pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/messages/%"PRIu64"/reactions/%s/%"PRIu64, 
           channel_id, message_id, emoji_endpoint, user_id);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_get_reactions(
  struct discord *client,
  u64_snowflake_t channel_id,
  u64_snowflake_t message_id,
  const u64_snowflake_t emoji_id,
  const char emoji_name[],
  struct discord_get_reactions_params *params,
  NTL_T(struct discord_user) *p_users)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_users) {
    log_error("Missing 'p_users'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_user_list_from_json_v, 
    .ok_obj = p_users 
  };

  char query[1024]="";
  if (params) {
    if (params->limit <= 0 || params->limit > 100) {
      log_error("'params.limit' should be between [1-100]");
      return ORCA_BAD_PARAMETER;
    }

    int ret;
    if (params->after) {
      ret = query_inject(query, sizeof(query),
              "(after):F"
              "(limit):d",
              &orka_ulltostr, &params->after,
              &params->limit);
    }
    else {
      ret = query_inject(query, sizeof(query),
              "(limit):d",
              &params->limit);
    }
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }

  char *pct_emoji_name = (emoji_name) 
                  ? url_encode((char*)emoji_name)
                  : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%"PRIu64, pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64"/messages/%"PRIu64"/reactions/%s%s", 
           channel_id, message_id, emoji_endpoint, query);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_all_reactions(
  struct discord *client, 
  u64_snowflake_t channel_id, 
  u64_snowflake_t message_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/messages/%"PRIu64"/reactions", 
           channel_id, message_id);
}

ORCAcode 
discord_delete_all_reactions_for_emoji(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id, 
  const u64_snowflake_t emoji_id, 
  const char emoji_name[])
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char *pct_emoji_name = (emoji_name) 
                  ? url_encode((char*)emoji_name)
                  : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64, pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/messages/%"PRIu64"/reactions/%s", 
           channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_edit_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id, 
  struct discord_edit_message_params *params, 
  struct discord_message *p_message)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_message ? &discord_message_from_json_v : NULL,
    .ok_obj = p_message
  };

  void *A[4]={}; // pointer availability array
  A[0] = params->content;
  A[1] = params->embed;
  A[2] = params->flags;
//A[3] = params->allowed_mentions;

  char *payload=NULL;
  size_t ret = json_ainject(&payload, 
                "(content):s"
                "(embed):F"
                "(flags):d"
              //"(allowed_mentions):F"
                "@arg_switches",
                params->content,
                &discord_embed_to_json, params->embed,
                params->flags,
              //&allowed_mentions_to_json, params->allowed_mentions,
                A, sizeof(A));

  if (!payload) {
    log_error("Couldn't create JSON Payload");
    return ORCA_BAD_JSON;
  }

  struct sized_buffer req_body = { payload, ret };

  ORCAcode code;
  code = discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_PATCH,
           "/channels/%"PRIu64"/messages/%"PRIu64, 
           channel_id, message_id);

  free(payload);

  return code;
}

ORCAcode
discord_delete_message(
  struct discord *client, 
  u64_snowflake_t channel_id, 
  u64_snowflake_t message_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/messages/%"PRIu64, channel_id, message_id);
}

/// @todo add duplicated ID verification
ORCAcode 
discord_bulk_delete_messages(struct discord *client, u64_snowflake_t channel_id, NTL_T(u64_snowflake_t) messages)
{
  if(!messages) {
    log_error("Missing 'messages'");
    return ORCA_MISSING_PARAMETER;
  }

  size_t count = ntl_length_max((ntl_t)messages, 101);
  if(count < 2 || count > 100) {
    log_error("Message count should be between 2 and 100");
    return ORCA_BAD_PARAMETER;
  }

  u64_unix_ms_t now = orka_timestamp_ms();
  for(size_t i = 0; messages[i]; i++) {
    u64_unix_ms_t timestamp = (*messages[i] >> 22) + 1420070400000;
    if(now > timestamp && now - timestamp > 1209600000) {
      log_error("Messages should not be older than 2 weeks.");
      return ORCA_BAD_PARAMETER;
    }
  }

  char *payload=NULL;
  size_t ret = json_ainject(&payload, "(messages):F", \
                  ja_u64_list_to_json, (NTL_T(ja_u64))messages);

  if (!payload) {
    log_error("Couldn't create JSON Payload");
    return ORCA_BAD_JSON;
  }

  struct sized_buffer req_body = { payload, ret };

  ORCAcode code;
  code = discord_adapter_run(
           &client->adapter,
           NULL,
           &req_body,
           HTTP_POST,
           "/channels/%"PRIu64"/messages/bulk-delete", channel_id);

  free(payload);

  return code;
}

ORCAcode
discord_edit_channel_permissions(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t overwrite_id,
  struct discord_edit_channel_permissions_params *params)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!overwrite_id) {
    log_error("Missing 'overwrite_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[MAX_PAYLOAD_LEN];
  size_t ret = discord_edit_channel_permissions_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run(
           &client->adapter,
           NULL,
           &req_body,
           HTTP_PUT,
           "/channels/%"PRIu64"/permissions/%"PRIu64, 
           channel_id, overwrite_id);
}

ORCAcode
discord_get_channel_invites(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  NTL_T(struct discord_invite) *p_invites)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_invites) {
    log_error("Missing 'p_invites'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = &discord_invite_list_from_json_v,
    .ok_obj = p_invites
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64"/invites", channel_id);
}

ORCAcode
discord_create_channel_invite(
  struct discord *client, 
  const u64_snowflake_t channel_id,
  struct discord_create_channel_invite_params *params,
  struct discord_invite *p_invite)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_invite ? &discord_invite_from_json_v : NULL,
    .ok_obj = p_invite
  };

  char payload[MAX_PAYLOAD_LEN];
  size_t ret;
  if (params)
    ret = discord_create_channel_invite_params_to_json(payload, sizeof(payload), params);
  else
    ret = sprintf(payload, "{}");
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST,
           "/channels/%"PRIu64"/invites", channel_id);
}

ORCAcode
discord_delete_channel_permission(
  struct discord *client, 
  const u64_snowflake_t channel_id,
  const u64_snowflake_t overwrite_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!overwrite_id) {
    log_error("Missing 'overwrite_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run( 
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/permissions/%"PRIu64, channel_id, overwrite_id);
}

ORCAcode
discord_follow_news_channel(
  struct discord *client,
  const u64_snowflake_t channel_id,
  struct discord_follow_news_channel_params *params,
  struct discord_channel *p_followed_channel)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params || !params->webhook_channel_id) {
    log_error("Missing 'params.webhook_channel_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[256]; // should be more than enough for this
  size_t ret = discord_follow_news_channel_params_to_json(payload, sizeof(payload), params);

  struct sized_buffer req_body = { payload, ret };

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_followed_channel ? &discord_channel_from_json_v : NULL,
    .ok_obj = p_followed_channel
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST,
           "/channels/%"PRIu64"/followers", channel_id);
}

ORCAcode
discord_trigger_typing_indicator(struct discord* client, u64_snowflake_t channel_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run( 
           &client->adapter,
           NULL,
           NULL,
           HTTP_POST, 
           "/channels/%"PRIu64"/typing", channel_id);
}

ORCAcode
discord_get_pinned_messages(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  NTL_T(struct discord_message) *p_messages)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_messages) {
    log_error("Missing 'p_messages'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = { 
    .ok_cb = &discord_message_list_from_json_v, 
    .ok_obj = p_messages 
  };

  return discord_adapter_run( 
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET, 
           "/channels/%"PRIu64"/pins", channel_id);
}

ORCAcode
discord_pin_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run( 
           &client->adapter,
           NULL,
           NULL,
           HTTP_PUT, 
           "/channels/%"PRIu64"/pins/%"PRIu64, channel_id, message_id);
}

ORCAcode
discord_unpin_message(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t message_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run( 
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/pins/%"PRIu64, channel_id, message_id);
}

ORCAcode
discord_start_thread_with_message(
  struct discord *client,
  const u64_snowflake_t channel_id,
  const u64_snowflake_t message_id,
  struct discord_start_thread_with_message_params *params,
  struct discord_channel *p_channel)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    log_error("Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_channel ? &discord_channel_from_json_v : NULL,
    .ok_obj = p_channel
  };

  char payload[MAX_PAYLOAD_LEN];
  size_t ret = discord_start_thread_with_message_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST,
           "/channels/%"PRIu64"/messages/%"PRIu64"/threads", 
           channel_id, message_id);
}

ORCAcode
discord_start_thread_without_message(
  struct discord *client,
  const u64_snowflake_t channel_id,
  struct discord_start_thread_without_message_params *params,
  struct discord_channel *p_channel)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    log_error("Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_channel ? &discord_channel_from_json_v : NULL,
    .ok_obj = p_channel
  };

  char payload[MAX_PAYLOAD_LEN];
  size_t ret = discord_start_thread_without_message_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer req_body = { payload, ret };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           &req_body,
           HTTP_POST,
           "/channels/%"PRIu64"/threads", channel_id);
}

ORCAcode
discord_join_thread(struct discord *client, const u64_snowflake_t channel_id) 
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_PUT,
           "/channels/%"PRIu64"/thread-members/@me", channel_id);
}

ORCAcode
discord_add_thread_member(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t user_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_PUT,
           "/channels/%"PRIu64"/thread-members/"PRIu64, 
           channel_id, user_id);
}

ORCAcode
discord_leave_thread(struct discord *client, const u64_snowflake_t channel_id) 
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/thread-members/@me", channel_id);
}

ORCAcode
discord_remove_thread_member(
  struct discord *client, 
  const u64_snowflake_t channel_id, 
  const u64_snowflake_t user_id)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    log_error("Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
           &client->adapter,
           NULL,
           NULL,
           HTTP_DELETE,
           "/channels/%"PRIu64"/thread-members/"PRIu64, 
           channel_id, user_id);
}

ORCAcode
discord_list_thread_members(
  struct discord *client,
  const u64_snowflake_t channel_id,
  NTL_T(struct discord_thread_member) *p_thread_members)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_thread_members) {
    log_error("Missing 'p_thread_members'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = &discord_thread_member_list_from_json_v,
    .ok_obj = p_thread_members
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64"/thread-members", channel_id);
}

ORCAcode
discord_list_active_threads(
  struct discord *client,
  const u64_snowflake_t channel_id,
  struct discord_thread_response_body *body)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!body) {
    log_error("Missing 'body'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = &discord_thread_response_body_from_json_v,
    .ok_obj = body
  };

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64"/threads/active", channel_id);
}

ORCAcode
discord_list_public_archived_threads(
  struct discord *client,
  const u64_snowflake_t channel_id,
  const u64_unix_ms_t before,
  const int limit,
  struct discord_thread_response_body *body)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!body) {
    log_error("Missing 'body'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = &discord_thread_response_body_from_json_v,
    .ok_obj = body
  };

  char query[1024]="";
  size_t offset=0;
  if (before) {
    offset += snprintf(query+offset, sizeof(query)-offset, \
        "?%"PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query+offset, sizeof(query)-offset, \
        "%s%d", (*query)?"&":"?", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64"/threads/archived/public%s", 
           channel_id, query);
}

ORCAcode
discord_list_private_archived_threads(
  struct discord *client,
  const u64_snowflake_t channel_id,
  const u64_unix_ms_t before,
  const int limit,
  struct discord_thread_response_body *body)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!body) {
    log_error("Missing 'body'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = &discord_thread_response_body_from_json_v,
    .ok_obj = body
  };

  char query[1024]="";
  size_t offset=0;
  if (before) {
    offset += snprintf(query+offset, sizeof(query)-offset, \
        "?%"PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query+offset, sizeof(query)-offset, \
        "%s%d", (*query)?"&":"?", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64"/threads/archived/private%s", 
           channel_id, query);
}

ORCAcode
discord_list_joined_private_archived_threads(
  struct discord *client,
  const u64_snowflake_t channel_id,
  const u64_unix_ms_t before,
  const int limit,
  struct discord_thread_response_body *body)
{
  if (!channel_id) {
    log_error("Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!body) {
    log_error("Missing 'body'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = &discord_thread_response_body_from_json_v,
    .ok_obj = body
  };

  char query[1024]="";
  size_t offset=0;
  if (before) {
    offset += snprintf(query+offset, sizeof(query)-offset, \
        "?%"PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query+offset, sizeof(query)-offset, \
        "%s%d", (*query)?"&":"?", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(
           &client->adapter,
           &resp_handle,
           NULL,
           HTTP_GET,
           "/channels/%"PRIu64"/users/@me/threads/archived/private%s", 
           channel_id, query);
}
