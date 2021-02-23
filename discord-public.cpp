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
  /* 
   * settings will be returned from this function,
   * it has to be static. It also means we can
   * only have one settings per bot.
   */
  static struct orka_settings settings;
  memset(&settings, 0, sizeof(orka_settings));

  /*
   * set a flag to make sure this function is called only once.
   */
  static int called = 0;
  if (0 == called)
    called = 1;
  else
    ERR("fast_init has been called, it can only be called once in each bot\n");


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
setcb(client *client, enum callback_opt opt, ...)
{
  va_list args;
  va_start(args, opt);

  using namespace websockets;

  intents::code code = 0;
  switch (opt) {
  case IDLE:
      client->ws.cbs.on_idle = va_arg(args, idle_cb*);
      break;
  case READY:
      client->ws.cbs.on_ready = va_arg(args, idle_cb*);
      break;
  case COMMAND: {
      client->ws.cbs.on_message.command = va_arg(args, message_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;

      const int PREFIX_LEN = sizeof(client->ws.prefix);

      const char *prefix = va_arg(args, char*);
      int ret = snprintf(client->ws.prefix, PREFIX_LEN, "%s", prefix);
      VASSERT_S(ret < PREFIX_LEN, "Prefix '%s' exceeds length of %d (%zu characters)", prefix, PREFIX_LEN, strlen(prefix));
      break;
   }
  case MESSAGE_CREATE:
      client->ws.cbs.on_message.create = va_arg(args, message_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_UPDATE:
      client->ws.cbs.on_message.update = va_arg(args, message_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_DELETE:
      client->ws.cbs.on_message.del = va_arg(args, message_delete_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_DELETE_BULK:
      client->ws.cbs.on_message.delete_bulk = va_arg(args, message_delete_bulk_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case REACTION_ADD:
      client->ws.cbs.on_reaction.add = va_arg(args, reaction_add_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case REACTION_REMOVE:
      client->ws.cbs.on_reaction.remove = va_arg(args, reaction_remove_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case REACTION_REMOVE_ALL:
      client->ws.cbs.on_reaction.remove_all = va_arg(args, reaction_remove_all_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case REACTION_REMOVE_EMOJI:
      client->ws.cbs.on_reaction.remove_emoji = va_arg(args, reaction_remove_emoji_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case GUILD_MEMBER_ADD:
      client->ws.cbs.on_guild_member.add = va_arg(args, guild_member_cb*);
      code |= intents::GUILD_MEMBERS;
      break;
  case GUILD_MEMBER_UPDATE:
      client->ws.cbs.on_guild_member.update = va_arg(args, guild_member_cb*);
      code |= intents::GUILD_MEMBERS;
      break;
  case GUILD_MEMBER_REMOVE:
      client->ws.cbs.on_guild_member.remove = va_arg(args, guild_member_remove_cb*);
      code |= intents::GUILD_MEMBERS;
      break;
  default:
      ERR("Invalid callback_opt (code: %d)", opt);
  }

  add_intents(client, code);

  va_end(args);
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
