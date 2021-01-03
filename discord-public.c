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

  return new_client;
}

void
discord_cleanup(discord_t *client) {
  Discord_api_cleanup(&client->api);
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
