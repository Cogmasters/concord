#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdiscord.h"
#include "discord-common.h"
#include "orka-utils.h"

struct msg {
  u64_snowflake_t id;
  bool matched;
};

void msg_from_json(char *json, size_t size, void *msg)
{

}

void
discord_user_defined_bulk_delete_message(
  struct discord_client *client, 
  u64_snowflake_t channel_id, 
  u64_snowflake_t author_id)
{
  if (!channel_id) {
    D_PUTS("Missing 'channel_id");
    return;
  }

  struct discord_channel_get_channel_messages_params params = {
    .limit = 100
  };

  NTL_T(struct discord_channel_message_dati) messages = NULL;
  discord_get_channel_messages(client, channel_id, &params, &messages);

  NTL_T(ja_u64) list = NULL;
  int count = 0;
  for (int i = 0; messages[i]; i++) {
    if (messages[i]->author->id == author_id)
      count ++;
  }
  list = (NTL_T(ja_u64))ntl_calloc(count, sizeof(ja_u64));

  for (int i = 0, j = 0; messages[i] && j < count; i++) {
    if (messages[i]->author->id == author_id) {
      list[j]->value = messages[i]->id;
      j++;
    }
  }
  ntl_free((ntl_t)messages, discord_channel_message_dati_cleanup_v);

  if (count == 1)
    discord_delete_message(client, channel_id, list[0]->value);
  else {
    char *json = NULL;
    json_ainject(&json,
                 "(messages):F",
                 ja_u64_list_to_json, list);

    struct sized_buffer req_body = {
      .start = json,
      .size = strlen(json)
    };

    discord_adapter_run(
      &client->adapter,
      NULL,
      &req_body,
      HTTP_POST,
      "/channels/%llu/messages/bulk-delete", channel_id);
  }
}
