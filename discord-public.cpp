#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  struct orka_settings settings;
  memset(&settings, 0, sizeof(orka_settings));

  orka_settings_init(&settings, config_file);

  client *client;
  if (settings.discord.token) {
    client = init(settings.discord.token);
    if (NULL == client) return NULL;
  }

  if (true == settings.logging.dump_json.enable)
    dump_json(client, settings.logging.dump_json.filename);
  if (true == settings.logging.dump_curl.enable)
    dump_curl(client, settings.logging.dump_curl.filename);

  return client;
}

void
cleanup(client *client)
{
  free(client->settings.token);

  if (client->settings.f_json_dump)
    fclose(client->settings.f_json_dump);
  if (client->settings.f_curl_dump)
    fclose(client->settings.f_curl_dump);

  user_agent::cleanup(&client->ua);
  websockets::cleanup(&client->ws);

  free(client);
}

void
global_init() {
  if (0 != curl_global_init(CURL_GLOBAL_DEFAULT)) {
    PUTS("Couldn't start libcurl's globals");
  }
}

void
global_cleanup() {
  curl_global_cleanup();
}

void
add_intents(client *client, websockets::intents::code code)
{
  using namespace websockets;
  if (status::CONNECTED == client->ws.status) {
    PUTS("Can't set intents to a running client.");
    return;
  }

  client->ws.identify->intents |= code;
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
setcb_message_command(client *client, char prefix[], message_cb *user_cb)
{
  using namespace websockets;
  add_intents(client, intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
  client->ws.cbs.on_message.command = user_cb;

  const int PREFIX_LEN = sizeof(client->ws.prefix);

  int ret = snprintf(client->ws.prefix, PREFIX_LEN, "%s", prefix);
  VASSERT_S(ret < PREFIX_LEN, "Prefix '%s' exceeds length of %d (%zu characters)", prefix, PREFIX_LEN, strlen(prefix));
}

void
setcb_message_create(client *client, message_cb *user_cb)
{
  using namespace websockets;
  add_intents(client, intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
  client->ws.cbs.on_message.create = user_cb;
}

void
setcb_message_update(client *client, message_cb *user_cb)
{
  using namespace websockets;
  add_intents(client, intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
  client->ws.cbs.on_message.update = user_cb;
}

void
setcb_message_delete(client *client, message_delete_cb *user_cb)
{
  using namespace websockets;
  add_intents(client, intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
  client->ws.cbs.on_message.del = user_cb;
}

void setcb_message_delete_bulk(client *client, message_delete_bulk_cb *user_cb)
{
  using namespace websockets;
  add_intents(client, intents::GUILD_MESSAGES);
  client->ws.cbs.on_message.delete_bulk = user_cb;
}

void setcb_guild_member_add(client *client, guild_member_cb *user_cb)
{
  using namespace websockets;
  add_intents(client, intents::GUILD_MEMBERS);
  client->ws.cbs.on_guild_member.add = user_cb;
}

void setcb_guild_member_update(client *client, guild_member_cb *user_cb)
{
  using namespace websockets;
  add_intents(client, intents::GUILD_MEMBERS);
  client->ws.cbs.on_guild_member.update = user_cb;
}

void setcb_guild_member_remove(client *client, guild_member_remove_cb *user_cb)
{
  using namespace websockets;
  add_intents(client, intents::GUILD_MEMBERS);
  client->ws.cbs.on_guild_member.remove = user_cb;
}

void
run(client *client){
  websockets::run(&client->ws);
}

void
dump_json(client *client, char file[])
{
  FILE *f_dump = fopen(file, "a+");
  ASSERT_S(NULL != f_dump, "Could not create dump file");

  client->settings.f_json_dump = f_dump;  
}

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

user_agent::error
get_json_error(client *client)
{
  user_agent::error get_err = client->ua.json_err;
  
  // resets json_err fields to avoid misleading repetition
  memset(&client->ua.json_err, 0, sizeof(user_agent::error));

  return get_err;
}

void
replace_presence(client *client, presence::dati *presence)
{
  if (NULL == presence) return;

  presence::free_dati(client->ws.identify->presence);
  client->ws.identify->presence = presence;
}

void
change_presence(
  client *client, 
  presence::activity::dati *activity, 
  char status[], 
  bool afk)
{
  presence::dati *presence = client->ws.identify->presence;

  if (activity) { //@todo
  }

  if (status) {
    int ret = snprintf(presence->status, 
                sizeof(presence->status), "%s", status);

    ASSERT_S(ret < (int)sizeof(presence->status),
        "Out of bounds write attempt");
  }

  presence->afk = afk;
}

} // namespace discord
