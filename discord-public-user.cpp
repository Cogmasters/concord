#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include "orka-utils.h"

namespace discord {
namespace user {

namespace get_user {
void
run(client *client, const u64_snowflake_t user_id, dati *p_user)
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
} // namespace get_user

namespace get_current_user {
void 
run(client *client, dati *p_user)
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

/* @todo this is a temporary solution for wrapping with JS */
static void 
json_to_sb(char *json, size_t len, void *p_sb_user)
{
  struct sized_buffer *sb_user = (struct sized_buffer*)p_sb_user;
  sb_user->start = strndup(json, len);
}

void /* @todo this is a temporary solution for easily wrapping JS */
sb_run(client *client, struct sized_buffer *p_sb_user)
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

} // namespace get_current_user

namespace get_current_user_guilds {
void
run(client *client, NTL_T(guild::dati) *p_guilds)
{
  struct resp_handle resp_handle =
    { .ok_cb = &guild::dati_list_from_json_v, .ok_obj = (void*)p_guilds};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/users/@me/guilds");
}
} // namespace get_current_user_guilds

namespace leave_guild {
void run(client *client, const u64_snowflake_t guild_id)
{
  struct sized_buffer req_body = {"{}", 2};

  user_agent::run(
    &client->ua,
    NULL,
    &req_body,
    HTTP_DELETE,
    "/users/@me/guilds/%llu", guild_id);
}
} // namespace leave_guild

} // namespace user
} // namespace discord
