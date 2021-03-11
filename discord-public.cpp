#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //for isgraph()

#include <libdiscord.h>
#include "orka-utils.h"


namespace discord {

client*
init(const char token[])
{
  client *new_client = (client*)calloc(1, sizeof(client));
  if (NULL == new_client) return NULL;

  new_client->ua.p_client = new_client;
  new_client->ws.p_client = new_client;
  
  user_agent::init(&new_client->ua, token, NULL);
  websockets::init(&new_client->ws, token, NULL);

  return new_client;
}

client*
config_init(const char config_file[])
{
  client *new_client = (client*)calloc(1, sizeof(client));
  if (NULL == new_client) return NULL;

  new_client->ua.p_client = new_client;
  new_client->ws.p_client = new_client;
  
  user_agent::init(&new_client->ua, NULL, config_file);
  websockets::init(&new_client->ws, NULL, config_file);

  return new_client;
}

void
cleanup(client *client)
{
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
  if (WS_CONNECTED == ws_get_status(&client->ws.common) {
    PUTS("Can't set intents to a running client.");
    return;
  }

  client->ws.identify->intents |= code;
}

void
set_prefix(client *client, char *prefix) 
{
  const size_t PREFIX_LEN = 32;
  if (!orka_str_bounds_check(prefix, PREFIX_LEN)) {
    PRINT("Prefix length greater than threshold (%zu chars)", PREFIX_LEN);
    return;
  }

  client->ws.prefix = prefix;
};

void
setcb_command(client *client, char *command, message_cb *user_cb)
{
  using namespace websockets;
  dati *ws = &client->ws;

  const size_t CMD_LEN = 64;
  if (!orka_str_bounds_check(command, CMD_LEN)) {
    PRINT("Command length greater than threshold (%zu chars)", CMD_LEN);
    return;
  }

  ++ws->num_cmd;
  ws->on_cmd = (struct cmd_cbs*)realloc(ws->on_cmd, 
                      ws->num_cmd * sizeof(struct cmd_cbs));

  ws->on_cmd[ws->num_cmd-1].str = command;
  ws->on_cmd[ws->num_cmd-1].cb = user_cb;

  add_intents(client, 
      intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
}

#define callback ... // varargs to avoid non-conforming function pointer error

void
setcb(client *client, enum callback_opt opt, callback)
{
  using namespace websockets;
  dati *ws = &client->ws;

  va_list args;
  va_start(args, opt);

  intents::code code = 0;
  switch (opt) {
  case IDLE:
      ws->cbs.on_idle = va_arg(args, idle_cb*);
      break;
  case READY:
      ws->cbs.on_ready = va_arg(args, idle_cb*);
      break;
  case MESSAGE_CREATE:
      ws->cbs.on_message.create = va_arg(args, message_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_UPDATE:
      ws->cbs.on_message.update = va_arg(args, message_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_DELETE:
      ws->cbs.on_message.del = va_arg(args, message_delete_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_DELETE_BULK:
      ws->cbs.on_message.delete_bulk = va_arg(args, message_delete_bulk_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case REACTION_ADD:
      ws->cbs.on_reaction.add = va_arg(args, reaction_add_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case REACTION_REMOVE:
      ws->cbs.on_reaction.remove = va_arg(args, reaction_remove_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case REACTION_REMOVE_ALL:
      ws->cbs.on_reaction.remove_all = va_arg(args, reaction_remove_all_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case REACTION_REMOVE_EMOJI:
      ws->cbs.on_reaction.remove_emoji = va_arg(args, reaction_remove_emoji_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case GUILD_MEMBER_ADD:
      ws->cbs.on_guild_member.add = va_arg(args, guild_member_cb*);
      code |= intents::GUILD_MEMBERS;
      break;
  case GUILD_MEMBER_UPDATE:
      ws->cbs.on_guild_member.update = va_arg(args, guild_member_cb*);
      code |= intents::GUILD_MEMBERS;
      break;
  case GUILD_MEMBER_REMOVE:
      ws->cbs.on_guild_member.remove = va_arg(args, guild_member_remove_cb*);
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

void*
set_data(client *client, void *data) {
  return client->data = data;
}

void*
get_data(client *client) {
  return client->data;
}

//@todo this is not thread safe
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

  presence::dati_free(client->ws.identify->presence);
  client->ws.identify->presence = presence;
}

void
set_presence(
  client *client, 
  presence::activity::dati *activity, //will take ownership
  char status[], 
  bool afk)
{
  using namespace presence;

  dati *presence = client->ws.identify->presence;

  if (activity) {
    presence->activities = (activity::dati**)ntl_append(
                              (void**)presence->activities, 
                              sizeof(activity::dati), activity);
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
