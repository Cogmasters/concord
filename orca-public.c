#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <liborca.h>
#include "orca-common.h"


orca_t*
orca_init(char token[])
{
  orca_t *new_client = malloc(sizeof *new_client);
  if (NULL == new_client) return NULL;

  //trim token at non-printable character (if any)
  for (int i=0; token[i] != '\0'; ++i) {
    if (!isgraph(token[i])) {
      token[i] = '\0';
      break;
    }
  }

  Orca_api_init(&new_client->api, token);
  Orca_ws_init(&new_client->ws, token);

  return new_client;
}

void
orca_cleanup(orca_t *client) {
  Orca_api_cleanup(&client->api);
  Orca_ws_cleanup(&client->ws);
  free(client);
}

void
orca_global_init() {
  int code = curl_global_init(CURL_GLOBAL_DEFAULT);
  ASSERT_S(!code, "Couldn't start curl_global_init()");
}

void
orca_global_cleanup() {
  curl_global_cleanup();
}

void
orca_set_callback(orca_t *client, enum discord_events event, orca_ws_cb *user_callback){
  Orca_ws_set_callback(&client->ws, event, user_callback);
}

void
orca_connect(orca_t *client){
  Orca_ws_connect(&client->ws);
}
