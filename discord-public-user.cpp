#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"


void
discord_get_user(struct discord_client *client, const u64_snowflake_t user_id, discord::user::dati *p_user)
{
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  struct resp_handle resp_handle =
    { .ok_cb = &discord::user::dati_from_json_v, .ok_obj = (void*)p_user};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/%llu", user_id);
}

void 
discord_get_current_user(struct discord_client *client, discord::user::dati *p_user)
{
  struct resp_handle resp_handle =
    { .ok_cb = &discord::user::dati_from_json_v, .ok_obj = (void*)p_user};

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
sb_discord_get_current_user(struct discord_client *client, struct sized_buffer *p_sb_user)
{
  struct resp_handle resp_handle =
    {.ok_cb = &json_to_sb, .ok_obj = (void*)p_sb_user};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/@me");
}

void
discord_get_current_user_guilds(struct discord_client *client, NTL_T(discord::guild::dati) *p_guilds)
{
  struct resp_handle resp_handle =
    { .ok_cb = &discord::guild::dati_list_from_json_v, .ok_obj = (void*)p_guilds};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/users/@me/guilds");
}

void 
discord_leave_guild(struct discord_client *client, const u64_snowflake_t guild_id)
{
  struct sized_buffer req_body = {"{}", 2};

  discord_adapter_run(
    &client->adapter,
    NULL,
    &req_body,
    HTTP_DELETE,
    "/users/@me/guilds/%llu", guild_id);
}
