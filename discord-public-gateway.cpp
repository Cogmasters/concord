#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdiscord.h>
#include <orka-utils.h>

namespace discord {
namespace gateway {

namespace session {
static void
dati_from_json(char *str, size_t len, void *p_session)
{
  discord::gateway::session::dati *session = (discord::gateway::session::dati*)p_session;

  struct sized_buffer buf = {NULL, 0};

  json_scanf(str, len,
     "[url]%s"
     "[shards]%d"
     "[session_start_limit]%T",
     session->url,
     &session->shards,
     &buf);

  json_scanf(buf.start, buf.size,
      "[total]%d"
      "[remaining]%d"
      "[reset_after]%d"
      "[max_concurrency]%d",
      &session->total,
      &session->remaining,
      &session->reset_after,
      &session->max_concurrency);

  DS_NOTOP_PUTS("Session Start Limit object loaded with API response"); 
}
} // namespace session

namespace get_gateway {
void
run(discord::client *client, discord::gateway::session::dati *p_session)
{
  struct resp_handle resp_handle = \
    { .ok_cb = &discord::gateway::session::dati_from_json, .ok_obj = (void*)p_session };

  discord::adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway");
}
} // namespace get_gateway

namespace get_gateway_bot {
void
run(discord::client *client, discord::gateway::session::dati *p_session)
{
  struct resp_handle resp_handle = \
    { .ok_cb = &discord::gateway::session::dati_from_json, .ok_obj = (void*)p_session};

  discord::adapter::run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway/bot");
}
} // namespace get_gateway_bot

} // namespace gateway
} // namespace discord
