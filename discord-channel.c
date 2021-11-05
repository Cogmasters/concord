#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

ORCAcode
discord_get_channel(struct discord *client,
                    const u64_snowflake_t channel_id,
                    struct discord_channel *p_channel)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_channel) {
    logconf_error(client->conf, "Missing 'p_channel'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_channel_from_json_v,
                              .ok_obj = &p_channel },
    NULL, HTTP_GET, "/channels/%" PRIu64, channel_id);
}

ORCAcode
discord_modify_channel(struct discord *client,
                       const u64_snowflake_t channel_id,
                       struct discord_modify_channel_params *params,
                       struct discord_channel *p_channel)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret =
    discord_modify_channel_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_channel ? &discord_channel_from_json_v
                                                 : NULL,
                              .ok_obj = &p_channel },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH, "/channels/%" PRIu64,
    channel_id);
}

ORCAcode
discord_delete_channel(struct discord *client,
                       const u64_snowflake_t channel_id,
                       struct discord_channel *p_channel)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_channel ? &discord_channel_from_json_v
                                                 : NULL,
                              .ok_obj = &p_channel },
    NULL, HTTP_DELETE, "/channels/%" PRIu64, channel_id);
}

ORCAcode
discord_get_channel_messages(
  struct discord *client,
  const u64_snowflake_t channel_id,
  struct discord_get_channel_messages_params *params,
  NTL_T(struct discord_message) * p_messages)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_messages) {
    logconf_error(client->conf, "Missing 'p_messages'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[1024] = "";
  if (params) {
    size_t offset = 0;
    if (params->limit) {
      offset += snprintf(query + offset, sizeof(query) - offset, "limit=%d",
                         params->limit);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->around) {
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "%saround=%" PRIu64,
                 (*query) ? "&" : "", params->around);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->before) {
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "%sbefore=%" PRIu64,
                 (*query) ? "&" : "", params->before);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
    if (params->after) {
      offset +=
        snprintf(query + offset, sizeof(query) - offset, "%safter=%" PRIu64,
                 (*query) ? "&" : "", params->after);
      ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
    }
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_message_list_from_json_v,
                              .ok_obj = p_messages },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/messages%s%s", channel_id,
    (*query) ? "?" : "", query);
}

ORCAcode
discord_get_channel_message(struct discord *client,
                            const u64_snowflake_t channel_id,
                            const u64_snowflake_t message_id,
                            struct discord_message *p_message)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_message) {
    logconf_error(client->conf, "Missing 'p_message'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_message_from_json_v,
                              .ok_obj = &p_message },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/messages/%" PRIu64, channel_id,
    message_id);
}

ORCAcode
discord_create_message(struct discord *client,
                       const u64_snowflake_t channel_id,
                       struct discord_create_message_params *params,
                       struct discord_message *p_message)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_message ? &discord_message_from_json_v : NULL,
    .ok_obj = &p_message
  };

  char payload[16384]; /**< @todo dynamic buffer */
  size_t ret =
    discord_create_message_params_to_json(payload, sizeof(payload), params);
  struct sized_buffer body = { payload, ret };

  /* content-type is application/json */
  if (!params->attachments) {
    return discord_adapter_run(&client->adapter, &resp_handle, &body,
                               HTTP_POST, "/channels/%" PRIu64 "/messages",
                               channel_id);
  }

  /* content-type is multipart/form-data */
  ua_curl_mime_setopt(client->adapter.ua,
                      (void *[2]){ params->attachments, &body },
                      &_discord_params_to_mime);

  ua_reqheader_add(client->adapter.ua, "Content-Type", "multipart/form-data");

  ORCAcode code;
  code =
    discord_adapter_run(&client->adapter, &resp_handle, NULL, HTTP_MIMEPOST,
                        "/channels/%" PRIu64 "/messages", channel_id);

  /*set back to default */
  ua_reqheader_add(client->adapter.ua, "Content-Type", "application/json");

  return code;
}

ORCAcode
discord_crosspost_message(struct discord *client,
                          const u64_snowflake_t channel_id,
                          const u64_snowflake_t message_id,
                          struct discord_message *p_message)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_message ? &discord_message_from_json_v
                                                 : NULL,
                              .ok_obj = &p_message },
    NULL, HTTP_POST, "/channels/%" PRIu64 "/messages/%" PRIu64 "/crosspost",
    channel_id, message_id);
}

ORCAcode
discord_create_reaction(struct discord *client,
                        const u64_snowflake_t channel_id,
                        const u64_snowflake_t message_id,
                        const u64_snowflake_t emoji_id,
                        const char emoji_name[])
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char *pct_emoji_name = (emoji_name) ? url_encode((char *)emoji_name) : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s/@me",
                             channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_own_reaction(struct discord *client,
                            const u64_snowflake_t channel_id,
                            const u64_snowflake_t message_id,
                            const u64_snowflake_t emoji_id,
                            const char emoji_name[])
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char *pct_emoji_name = (emoji_name) ? url_encode((char *)emoji_name) : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s/@me",
                             channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_user_reaction(struct discord *client,
                             const u64_snowflake_t channel_id,
                             const u64_snowflake_t message_id,
                             const u64_snowflake_t user_id,
                             const u64_snowflake_t emoji_id,
                             const char emoji_name[])
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char *pct_emoji_name = (emoji_name) ? url_encode((char *)emoji_name) : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s/%" PRIu64,
                             channel_id, message_id, emoji_endpoint, user_id);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_get_reactions(struct discord *client,
                      u64_snowflake_t channel_id,
                      u64_snowflake_t message_id,
                      const u64_snowflake_t emoji_id,
                      const char emoji_name[],
                      struct discord_get_reactions_params *params,
                      NTL_T(struct discord_user) * p_users)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_users) {
    logconf_error(client->conf, "Missing 'p_users'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[1024] = "";
  if (params) {
    if (params->limit <= 0 || params->limit > 100) {
      logconf_error(client->conf, "'params.limit' should be between [1-100]");
      return ORCA_BAD_PARAMETER;
    }

    size_t ret;
    if (params->after) {
      ret = query_inject(query, sizeof(query),
                         "(after):F"
                         "(limit):d",
                         &cee_ulltostr, &params->after, &params->limit);
    }
    else {
      ret = query_inject(query, sizeof(query), "(limit):d", &params->limit);
    }
    ASSERT_S(ret < sizeof(query), "Out of bounds write attempt");
  }

  char *pct_emoji_name = (emoji_name) ? url_encode((char *)emoji_name) : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_user_list_from_json_v,
                              .ok_obj = p_users },
    NULL, HTTP_GET,
    "/channels/%" PRIu64 "/messages/%" PRIu64 "/reactions/%s%s", channel_id,
    message_id, emoji_endpoint, query);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_delete_all_reactions(struct discord *client,
                             u64_snowflake_t channel_id,
                             u64_snowflake_t message_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions",
                             channel_id, message_id);
}

ORCAcode
discord_delete_all_reactions_for_emoji(struct discord *client,
                                       const u64_snowflake_t channel_id,
                                       const u64_snowflake_t message_id,
                                       const u64_snowflake_t emoji_id,
                                       const char emoji_name[])
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char *pct_emoji_name = (emoji_name) ? url_encode((char *)emoji_name) : NULL;

  char emoji_endpoint[256];
  if (emoji_id)
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s:%" PRIu64,
             pct_emoji_name, emoji_id);
  else
    snprintf(emoji_endpoint, sizeof(emoji_endpoint), "%s", pct_emoji_name);

  ORCAcode code;
  code = discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64
                             "/reactions/%s",
                             channel_id, message_id, emoji_endpoint);

  free(pct_emoji_name);

  return code;
}

ORCAcode
discord_edit_message(struct discord *client,
                     const u64_snowflake_t channel_id,
                     const u64_snowflake_t message_id,
                     struct discord_edit_message_params *params,
                     struct discord_message *p_message)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[16384]; /**< @todo dynamic buffer */
  size_t ret =
    discord_edit_message_params_to_json(payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_message ? &discord_message_from_json_v
                                                 : NULL,
                              .ok_obj = &p_message },
    &(struct sized_buffer){ payload, ret }, HTTP_PATCH,
    "/channels/%" PRIu64 "/messages/%" PRIu64, channel_id, message_id);
}

ORCAcode
discord_delete_message(struct discord *client,
                       u64_snowflake_t channel_id,
                       u64_snowflake_t message_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/messages/%" PRIu64,
                             channel_id, message_id);
}

/** @todo add duplicated ID verification */
ORCAcode
discord_bulk_delete_messages(struct discord *client,
                             u64_snowflake_t channel_id,
                             NTL_T(u64_snowflake_t) messages)
{
  if (!messages) {
    logconf_error(client->conf, "Missing 'messages'");
    return ORCA_MISSING_PARAMETER;
  }

  size_t count = ntl_length_max((ntl_t)messages, 101);
  if (count < 2 || count > 100) {
    logconf_error(client->conf, "Message count should be between 2 and 100");
    return ORCA_BAD_PARAMETER;
  }

  u64_unix_ms_t now = cee_timestamp_ms();
  int i;
  for (i = 0; messages[i]; i++) {
    u64_unix_ms_t timestamp = (*messages[i] >> 22) + 1420070400000;
    if (now > timestamp && now - timestamp > 1209600000) {
      logconf_error(client->conf,
                    "Messages should not be older than 2 weeks.");
      return ORCA_BAD_PARAMETER;
    }
  }

  char *payload = NULL;
  size_t ret = json_ainject(&payload, "(messages):F", ja_u64_list_to_json,
                            (NTL_T(ja_u64))messages);

  if (!payload) {
    logconf_error(client->conf, "Couldn't create JSON Payload");
    return ORCA_BAD_JSON;
  }

  ORCAcode code;
  code = discord_adapter_run(
    &client->adapter, NULL, &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/channels/%" PRIu64 "/messages/bulk-delete", channel_id);

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
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!overwrite_id) {
    logconf_error(client->conf, "Missing 'overwrite_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret = discord_edit_channel_permissions_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter, NULL, &(struct sized_buffer){ payload, ret }, HTTP_PUT,
    "/channels/%" PRIu64 "/permissions/%" PRIu64, channel_id, overwrite_id);
}

ORCAcode
discord_get_channel_invites(struct discord *client,
                            const u64_snowflake_t channel_id,
                            NTL_T(struct discord_invite) * p_invites)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_invites) {
    logconf_error(client->conf, "Missing 'p_invites'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_invite_list_from_json_v,
                              .ok_obj = p_invites },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/invites", channel_id);
}

ORCAcode
discord_create_channel_invite(
  struct discord *client,
  const u64_snowflake_t channel_id,
  struct discord_create_channel_invite_params *params,
  struct discord_invite *p_invite)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret;
  if (params)
    ret = discord_create_channel_invite_params_to_json(
      payload, sizeof(payload), params);
  else
    ret = sprintf(payload, "{}");

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb =
                                p_invite ? &discord_invite_from_json_v : NULL,
                              .ok_obj = &p_invite },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/channels/%" PRIu64 "/invites", channel_id);
}

ORCAcode
discord_delete_channel_permission(struct discord *client,
                                  const u64_snowflake_t channel_id,
                                  const u64_snowflake_t overwrite_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!overwrite_id) {
    logconf_error(client->conf, "Missing 'overwrite_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/permissions/%" PRIu64,
                             channel_id, overwrite_id);
}

ORCAcode
discord_follow_news_channel(struct discord *client,
                            const u64_snowflake_t channel_id,
                            struct discord_follow_news_channel_params *params,
                            struct discord_channel *p_followed_channel)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params || !params->webhook_channel_id) {
    logconf_error(client->conf, "Missing 'params.webhook_channel_id'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[256]; /* should be more than enough for this */
  size_t ret = discord_follow_news_channel_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = p_followed_channel ? &discord_channel_from_json_v : NULL,
      .ok_obj = &p_followed_channel },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/channels/%" PRIu64 "/followers", channel_id);
}

ORCAcode
discord_trigger_typing_indicator(struct discord *client,
                                 u64_snowflake_t channel_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_POST,
                             "/channels/%" PRIu64 "/typing", channel_id);
}

ORCAcode
discord_get_pinned_messages(struct discord *client,
                            const u64_snowflake_t channel_id,
                            NTL_T(struct discord_message) * p_messages)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_messages) {
    logconf_error(client->conf, "Missing 'p_messages'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_message_list_from_json_v,
                              .ok_obj = p_messages },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/pins", channel_id);
}

ORCAcode
discord_pin_message(struct discord *client,
                    const u64_snowflake_t channel_id,
                    const u64_snowflake_t message_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/channels/%" PRIu64 "/pins/%" PRIu64, channel_id,
                             message_id);
}

ORCAcode
discord_unpin_message(struct discord *client,
                      const u64_snowflake_t channel_id,
                      const u64_snowflake_t message_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/pins/%" PRIu64, channel_id,
                             message_id);
}

ORCAcode
discord_group_dm_add_recipient(
  struct discord *client,
  const u64_snowflake_t channel_id,
  const u64_snowflake_t user_id,
  struct discord_group_dm_add_recipient_params *params)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret = discord_group_dm_add_recipient_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter, NULL, &(struct sized_buffer){ payload, ret }, HTTP_PUT,
    "/channels/%" PRIu64 "/recipients/%" PRIu64, channel_id, user_id);
}

ORCAcode
discord_group_dm_remove_recipient(struct discord *client,
                                  const u64_snowflake_t channel_id,
                                  const u64_snowflake_t user_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/recipients/%" PRIu64,
                             channel_id, user_id);
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
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!message_id) {
    logconf_error(client->conf, "Missing 'message_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret = discord_start_thread_with_message_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_channel ? &discord_channel_from_json_v
                                                 : NULL,
                              .ok_obj = &p_channel },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/channels/%" PRIu64 "/messages/%" PRIu64 "/threads", channel_id,
    message_id);
}

ORCAcode
discord_start_thread_without_message(
  struct discord *client,
  const u64_snowflake_t channel_id,
  struct discord_start_thread_without_message_params *params,
  struct discord_channel *p_channel)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!params) {
    logconf_error(client->conf, "Missing 'params'");
    return ORCA_MISSING_PARAMETER;
  }

  char payload[1024];
  size_t ret = discord_start_thread_without_message_params_to_json(
    payload, sizeof(payload), params);

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = p_channel ? &discord_channel_from_json_v
                                                 : NULL,
                              .ok_obj = &p_channel },
    &(struct sized_buffer){ payload, ret }, HTTP_POST,
    "/channels/%" PRIu64 "/threads", channel_id);
}

ORCAcode
discord_join_thread(struct discord *client, const u64_snowflake_t channel_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/channels/%" PRIu64 "/thread-members/@me",
                             channel_id);
}

ORCAcode
discord_add_thread_member(struct discord *client,
                          const u64_snowflake_t channel_id,
                          const u64_snowflake_t user_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_PUT,
                             "/channels/%" PRIu64 "/thread-members/" PRIu64,
                             channel_id, user_id);
}

ORCAcode
discord_leave_thread(struct discord *client, const u64_snowflake_t channel_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/thread-members/@me",
                             channel_id);
}

ORCAcode
discord_remove_thread_member(struct discord *client,
                             const u64_snowflake_t channel_id,
                             const u64_snowflake_t user_id)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!user_id) {
    logconf_error(client->conf, "Missing 'user_id'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(&client->adapter, NULL, NULL, HTTP_DELETE,
                             "/channels/%" PRIu64 "/thread-members/" PRIu64,
                             channel_id, user_id);
}

ORCAcode
discord_list_thread_members(struct discord *client,
                            const u64_snowflake_t channel_id,
                            NTL_T(struct discord_thread_member) *
                              p_thread_members)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!p_thread_members) {
    logconf_error(client->conf, "Missing 'p_thread_members'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &discord_thread_member_list_from_json_v,
                              .ok_obj = p_thread_members },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/thread-members", channel_id);
}

ORCAcode
discord_list_active_threads(struct discord *client,
                            const u64_snowflake_t channel_id,
                            struct discord_thread_response_body *body)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!body) {
    logconf_error(client->conf, "Missing 'body'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = &discord_thread_response_body_from_json_v, .ok_obj = &body },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/threads/active", channel_id);
}

ORCAcode
discord_list_public_archived_threads(struct discord *client,
                                     const u64_snowflake_t channel_id,
                                     const u64_unix_ms_t before,
                                     const int limit,
                                     struct discord_thread_response_body *body)
{
  if (!channel_id) {
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!body) {
    logconf_error(client->conf, "Missing 'body'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[1024] = "";
  size_t offset = 0;
  if (before) {
    offset += snprintf(query + offset, sizeof(query) - offset,
                       "before=%" PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                       (*query) ? "&" : "", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = &discord_thread_response_body_from_json_v, .ok_obj = &body },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/threads/archived/public%s%s",
    channel_id, (*query) ? "?" : "", query);
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
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!body) {
    logconf_error(client->conf, "Missing 'body'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[1024] = "";
  size_t offset = 0;
  if (before) {
    offset += snprintf(query + offset, sizeof(query) - offset,
                       "before=%" PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                       (*query) ? "&" : "", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = &discord_thread_response_body_from_json_v, .ok_obj = &body },
    NULL, HTTP_GET, "/channels/%" PRIu64 "/threads/archived/private%s%s",
    channel_id, (*query) ? "?" : "", query);
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
    logconf_error(client->conf, "Missing 'channel_id'");
    return ORCA_MISSING_PARAMETER;
  }
  if (!body) {
    logconf_error(client->conf, "Missing 'body'");
    return ORCA_MISSING_PARAMETER;
  }

  char query[1024] = "";
  size_t offset = 0;
  if (before) {
    offset += snprintf(query + offset, sizeof(query) - offset,
                       "before=%" PRIu64, before);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }
  if (limit) {
    offset += snprintf(query + offset, sizeof(query) - offset, "%slimit=%d",
                       (*query) ? "&" : "", limit);
    ASSERT_S(offset < sizeof(query), "Out of bounds write attempt");
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){
      .ok_cb = &discord_thread_response_body_from_json_v, .ok_obj = &body },
    NULL, HTTP_GET,
    "/channels/%" PRIu64 "/users/@me/threads/archived/private%s%s", channel_id,
    (*query) ? "?" : "", query);
}
