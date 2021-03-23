#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdiscord.h"
#include "discord-common.h"
#include "orka-utils.h"


static void
discord_session_dati_from_json(char *str, size_t len, void *p_session)
{
  struct discord_session *session = (struct discord_session*)p_session;

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

void
discord_get_gateway(struct discord_client *client, struct discord_session *p_session)
{
  struct resp_handle resp_handle = \
    { .ok_cb = &discord_session_dati_from_json, .ok_obj = (void*)p_session };

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway");
}

void
discord_get_gateway_bot(struct discord_client *client, struct discord_session *p_session)
{
  struct resp_handle resp_handle = \
    { .ok_cb = &discord_session_dati_from_json, .ok_obj = (void*)p_session};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway/bot");
}
