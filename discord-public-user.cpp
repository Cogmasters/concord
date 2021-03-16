#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace user {

void
get(client *client, const uint64_t user_id, dati *p_user)
{
  if (!user_id) {
    D_PUTS("Missing 'user_id'");
    return;
  }

  struct resp_handle resp_handle =
    { .ok_cb = &dati_from_json_v, .ok_obj = (void*)p_user};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/%llu", user_id);
}

namespace me {

void 
get(client *client, dati *p_user)
{
  struct resp_handle resp_handle =
    { .ok_cb = &dati_from_json_v, .ok_obj = (void*)p_user};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/@me");
}

static void /* @todo this is a temporary solution for wrapping with JS */
json_to_sb(char *json, size_t len, void *p_sb_user)
{
  struct sized_buffer *sb_user = (struct sized_buffer*)p_sb_user;
  sb_user->start = strndup(json, len);
}

void /* @todo this is a temporary solution for easily wrapping JS */
sb_get(client *client, struct sized_buffer *p_sb_user)
{
  struct resp_handle resp_handle =
    {.ok_cb = &json_to_sb, .ok_obj = (void*)p_sb_user};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET, 
    "/users/@me");
}

guild::dati**
get_guilds(client *client)
{
  guild::dati **new_guilds = NULL;

  struct resp_handle resp_handle =
    { .ok_cb = &guild::dati_list_from_json_v, .ok_obj = (void*)&new_guilds};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/users/@me/guilds");

  return new_guilds;
}

void leave_guild(client *client, const u64_snowflake_t guild_id)
{
  struct sized_buffer req_body = {"{}", 2};

  user_agent::run(
    &client->ua,
    NULL,
    &req_body,
    HTTP_DELETE,
    "/users/@me/guilds/%llu", guild_id);
}

} // namespace me

} // namespace user
} // namespace discord
