#include <stdio.h>
#include <stdlib.h>
#include <string.h> //@todo remove when settings is updated
#include <ctype.h>

#include <libdiscord.h>
#include "discord-common.h"


discord_t*
discord_init(char token[])
{
  discord_t *new_client = calloc(1, sizeof *new_client);
  if (NULL == new_client) return NULL;

  /* @todo this is a temporary solution */
  new_client->settings.token = strdup(token);
  if (NULL == new_client->settings.token) goto cleanup;

  new_client->settings.f_json_dump = NULL;
  new_client->settings.f_curl_dump = NULL;
  /* * * * * * * * * * */

  //trim token at non-printable character (if any)
  for (int i=0; token[i] != '\0'; ++i) {
    if (!isgraph(token[i])) {
      token[i] = '\0';
      break;
    }
  }

  new_client->api.p_client = new_client;
  new_client->ws.p_client = new_client;

  Discord_api_init(&new_client->api, token);
  Discord_ws_init(&new_client->ws, token);

  return new_client;

cleanup:
  free(new_client);

  return NULL;
}

void
discord_cleanup(discord_t *client)
{
  /* @todo this is a temporary solution */
  if (client->settings.token)
    free(client->settings.token);
  if (client->settings.f_json_dump)
    fclose(client->settings.f_json_dump);
  if (client->settings.f_curl_dump)
    fclose(client->settings.f_curl_dump);
  /* * * * * * * * * * */

  Discord_api_cleanup(&client->api);
  Discord_ws_cleanup(&client->ws);

  free(client);
}

void
discord_global_init() {
  ASSERT_S(0 == curl_global_init(CURL_GLOBAL_DEFAULT),
      "Couldn't start libcurl's globals configurations");
}

void
discord_global_cleanup() {
  curl_global_cleanup();
}

void
discord_setcb_idle(discord_t *client, discord_idle_cb *user_cb){
  Discord_ws_setcb_idle(&client->ws, user_cb);
}

void
discord_setcb_ready(discord_t *client, discord_idle_cb *user_cb){
  Discord_ws_setcb_ready(&client->ws, user_cb);
}

void
discord_setcb_message_create(discord_t *client, discord_message_cb *user_cb){
  Discord_ws_setcb_message_create(&client->ws, user_cb);
}

void
discord_setcb_message_update(discord_t *client, discord_message_cb *user_cb){
  Discord_ws_setcb_message_update(&client->ws, user_cb);
}

void
discord_setcb_message_delete(discord_t *client, discord_message_cb *user_cb){
  Discord_ws_setcb_message_delete(&client->ws, user_cb);
}

void
discord_run(discord_t *client){
  Discord_ws_run(&client->ws);
}

//@todo find a better solution using settings.h logger
void
discord_dump_json(discord_t *client, char file[])
{
  FILE *f_dump = fopen(file, "a+");
  ASSERT_S(NULL != f_dump, "Could not create dump file");

  client->settings.f_json_dump = f_dump;  
}

//@todo find a better solution using settings.h logger
void
discord_dump_curl(discord_t *client, char file[])
{
  FILE *f_dump = fopen(file, "a+");
  ASSERT_S(NULL != f_dump, "Could not create dump file");

  client->settings.f_curl_dump = f_dump;  
}

void*
discord_set_data(discord_t *client, void *data) {
  return Discord_utils_set_data(client, data);
}

void*
discord_get_data(discord_t *client) {
  return Discord_utils_get_data(client);
}
