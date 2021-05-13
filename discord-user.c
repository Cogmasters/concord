#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


void
discord_get_user(struct discord *client, const u64_snowflake_t user_id, struct discord_user *p_user)
{
  if (!user_id) {
    log_error("Missing 'user_id'");
    return;
  }

  struct ua_resp_handle resp_handle =
    { .ok_cb = &discord_user_from_json_v, .ok_obj = (void*)p_user};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/%"PRIu64, user_id);
}

void 
discord_get_current_user(struct discord *client, struct discord_user *p_user)
{
  struct ua_resp_handle resp_handle =
    { .ok_cb = &discord_user_from_json_v, .ok_obj = (void*)p_user};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/@me");
}

/* @todo this is a temporary solution for wrapping with JS */
static void 
json_to_sb(char *json, size_t len, void *p_sb_user)
{
  struct sized_buffer *sb_user = (struct sized_buffer*)p_sb_user;
  sb_user->start = strndup(json, len);
}

void /* @todo this is a temporary solution for easily wrapping JS */
sb_discord_get_current_user(struct discord *client, struct sized_buffer *p_sb_user)
{
  struct ua_resp_handle resp_handle =
    {.ok_cb = &json_to_sb, .ok_obj = (void*)p_sb_user};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/@me");
}

void
discord_get_current_user_guilds(struct discord *client, NTL_T(struct discord_guild) *p_guilds)
{
  struct ua_resp_handle resp_handle =
    { .ok_cb = &discord_guild_list_from_json_v, .ok_obj = (void*)p_guilds};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/users/@me/guilds");
}

void 
discord_leave_guild(struct discord *client, const u64_snowflake_t guild_id)
{
  struct sized_buffer req_body = {"{}", 2};

  discord_adapter_run(
    &client->adapter,
    NULL,
    &req_body,
    HTTP_DELETE,
    "/users/@me/guilds/%"PRIu64, guild_id);
}

void 
discord_create_dm(struct discord *client, const u64_snowflake_t recipient_id, struct discord_channel *p_dm_channel)
{
  if (!recipient_id) {
    log_error("Missing 'recipient_id'");
    return;
  }

  char payload[256]; // can safely assume the payload size to be small
  size_t ret = json_inject(payload, sizeof(payload), \
      "(recipient_id):s_as_u64", &recipient_id);

  struct ua_resp_handle resp_handle = {
    .ok_cb = p_dm_channel ? &discord_channel_from_json_v : NULL,
    .ok_obj = p_dm_channel
  };
  struct sized_buffer req_body = {payload, ret};

  discord_adapter_run(
    &client->adapter,
    &resp_handle,
    &req_body,
    HTTP_POST,
    "/users/@me/channels");
}
