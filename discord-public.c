#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <libdiscord.h>
#include "discord-common.h"


discord_t*
discord_init(char token[])
{
  discord_t *new_client = malloc(sizeof *new_client);
  if (NULL == new_client) return NULL;

  //trim token at non-printable character (if any)
  for (int i=0; token[i] != '\0'; ++i) {
    if (!isgraph(token[i])) {
      token[i] = '\0';
      break;
    }
  }

  Discord_api_init(&new_client->api, token);
  Discord_ws_init(&new_client->ws, token);

  return new_client;
}

void
discord_cleanup(discord_t *client) {
  Discord_api_cleanup(&client->api);
  Discord_ws_cleanup(&client->ws);
  free(client);
}

void
discord_global_init() {
  int code = curl_global_init(CURL_GLOBAL_DEFAULT);
  ASSERT_S(!code, "Couldn't start curl_global_init()");
}

void
discord_global_cleanup() {
  curl_global_cleanup();
}

void
discord_set_callback(discord_t *client, enum discord_events event, discord_ws_cb *user_callback){
  Discord_ws_set_callback(&client->ws, event, user_callback);
}

void
discord_connect(discord_t *client){
  Discord_ws_connect(&client->ws);
}
