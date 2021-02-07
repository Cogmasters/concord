#include <stdio.h>
#include <stdlib.h>
#include <string.h> //@todo remove when settings is updated
#include <ctype.h> //for isgraph()

#include <libdiscord.h>
#include "orka-utils.h"


namespace discord {

client*
init(char token[])
{
  client *new_client = (client*)calloc(1, sizeof(client));
  if (NULL == new_client) return NULL;

  new_client->settings.token = strdup(token);
  if (NULL == new_client->settings.token) {
    free(new_client);
    return NULL;
  }

  for (int i=0; token[i] != '\0'; ++i) {
    if (!isgraph(token[i])) {
      token[i] = '\0';
      break;
    }
  }

  new_client->ua.p_client = new_client;
  new_client->ws.p_client = new_client;

  user_agent::init(&new_client->ua, token);
  websockets::init(&new_client->ws, token);

  return new_client;
}

client*
fast_init(const char config_file[])
{
  struct orka_settings settings = {0};

  orka_settings_init(&settings, config_file);

  client *client;
  if (settings.discord.token) {
    client = init(settings.discord.token);
    if (NULL == client) return NULL;
  }

  if (settings.logging.dump_json.enable)
    dump_json(client, settings.logging.dump_json.filename);
  if (settings.logging.dump_curl.enable)
    dump_curl(client, settings.logging.dump_curl.filename);

  return client;
}

void
cleanup(client *client)
{
  /* @todo this is a temporary solution */
  if (client->settings.token)
    free(client->settings.token);
  if (client->settings.f_json_dump)
    fclose(client->settings.f_json_dump);
  if (client->settings.f_curl_dump)
    fclose(client->settings.f_curl_dump);
  /* * * * * * * * * * */

  user_agent::cleanup(&client->ua);
  websockets::cleanup(&client->ws);

  free(client);
}

void
global_init() {
  ASSERT_S(0 == curl_global_init(CURL_GLOBAL_DEFAULT),
      "Couldn't start libcurl's globals configurations");
}

void
global_cleanup() {
  curl_global_cleanup();
}

void
setcb_idle(client *client, idle_cb *user_cb){
  client->ws.cbs.on_idle = user_cb;
}

void
setcb_ready(client *client, idle_cb *user_cb){
  client->ws.cbs.on_ready = user_cb;
}

void
setcb_message_create(client *client, message_cb *user_cb)
{
  using namespace websockets;
  client->ws.intents |= (intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
  client->ws.cbs.on_message.create = user_cb;
}

void
setcb_message_update(client *client, message_cb *user_cb)
{
  using namespace websockets;
  client->ws.intents |= (intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
  client->ws.cbs.on_message.update = user_cb;
}

void
setcb_message_delete(client *client, message_delete_cb *user_cb)
{
  using namespace websockets;
  client->ws.intents |= (intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
  client->ws.cbs.on_message.del = user_cb;
}

void setcb_message_delete_bulk(client *client, message_delete_bulk_cb *user_cb)
{
  using namespace websockets;
  client->ws.intents |= intents::GUILD_MESSAGES;
  client->ws.cbs.on_message.delete_bulk = user_cb;
}

void setcb_guild_member_add(client *client, guild_member_cb *user_cb)
{
  using namespace websockets;
  client->ws.intents |= intents::GUILD_MEMBERS;
  client->ws.cbs.on_guild_member.add = user_cb;
}

void setcb_guild_member_update(client *client, guild_member_cb *user_cb)
{
  using namespace websockets;
  client->ws.intents |= intents::GUILD_MEMBERS;
  client->ws.cbs.on_guild_member.update = user_cb;
}

void setcb_guild_member_remove(client *client, guild_member_remove_cb *user_cb)
{
  using namespace websockets;
  client->ws.intents |= intents::GUILD_MEMBERS;
  client->ws.cbs.on_guild_member.remove = user_cb;
}

void
run(client *client){
  websockets::run(&client->ws);
}

//@todo find a better solution using settings.h logger
void
dump_json(client *client, char file[])
{
  FILE *f_dump = fopen(file, "a+");
  ASSERT_S(NULL != f_dump, "Could not create dump file");

  client->settings.f_json_dump = f_dump;  
}

//@todo find a better solution using settings.h logger
void
dump_curl(client *client, char file[])
{
  FILE *f_dump = fopen(file, "a+");
  ASSERT_S(NULL != f_dump, "Could not create dump file");

  client->settings.f_curl_dump = f_dump;  
}

void*
set_data(client *client, void *data) {
  return client->data = data;
}

void*
get_data(client *client) {
  return client->data;
}

} // namespace discord
