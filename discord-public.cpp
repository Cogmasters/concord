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

  new_client->adapter.p_client = new_client;
  new_client->gw.p_client = new_client;
  
  adapter::init(&new_client->adapter, token, NULL);
  gateway::init(&new_client->gw, token, NULL);

  return new_client;
}

client*
config_init(const char config_file[])
{
  client *new_client = (client*)calloc(1, sizeof(client));
  if (NULL == new_client) return NULL;

  new_client->adapter.p_client = new_client;
  new_client->gw.p_client = new_client;
  
  adapter::init(&new_client->adapter, NULL, config_file);
  gateway::init(&new_client->gw, NULL, config_file);

  return new_client;
}

void
cleanup(client *client)
{
  adapter::cleanup(&client->adapter);
  gateway::cleanup(&client->gw);

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
add_intents(client *client, int intent_code)
{
  if (WS_CONNECTED == ws_get_status(&client->gw.ws)) {
    PUTS("Can't set intents to a running client.");
    return;
  }

  client->gw.identify->intents |= intent_code;
}

void
set_prefix(client *client, char *prefix) 
{
  const size_t PREFIX_LEN = 32;
  if (!orka_str_bounds_check(prefix, PREFIX_LEN)) {
    PRINT("Prefix length greater than threshold (%zu chars)", PREFIX_LEN);
    return;
  }

  client->gw.prefix = prefix;
};

void
setcb_command(client *client, char *command, message_cb *user_cb)
{
  using namespace gateway;
  dati *gw = &client->gw;

  const size_t CMD_LEN = 64;
  if (!orka_str_bounds_check(command, CMD_LEN)) {
    PRINT("Command length greater than threshold (%zu chars)", CMD_LEN);
    return;
  }

  ++gw->num_cmd;
  gw->on_cmd = (struct cmd_cbs*)realloc(gw->on_cmd, 
                      gw->num_cmd * sizeof(struct cmd_cbs));

  gw->on_cmd[gw->num_cmd-1].str = command;
  gw->on_cmd[gw->num_cmd-1].cb = user_cb;

  add_intents(client, 
      intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES);
}

#define callback ... // varargs to avoid non-conforming function pointer error

void
setcb(client *client, enum dispatch_code opt, callback)
{
  using namespace gateway;
  dati *gw = &client->gw;

  va_list args;
  va_start(args, opt);

  int code = 0;
  switch (opt) {
  case IDLE:
      gw->cbs.on_idle = va_arg(args, idle_cb*);
      break;
  case READY:
      gw->cbs.on_ready = va_arg(args, idle_cb*);
      break;
  case MESSAGE_CREATE:
      gw->cbs.on_message.create = va_arg(args, message_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case SB_MESSAGE_CREATE: /* @todo this is temporary for wrapping JS */
      gw->cbs.on_message.sb_create = va_arg(args, sb_message_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_UPDATE:
      gw->cbs.on_message.update = va_arg(args, message_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_DELETE:
      gw->cbs.on_message.del = va_arg(args, message_delete_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_DELETE_BULK:
      gw->cbs.on_message.delete_bulk = va_arg(args, message_delete_bulk_cb*);
      code |= intents::GUILD_MESSAGES | intents::DIRECT_MESSAGES;
      break;
  case MESSAGE_REACTION_ADD:
      gw->cbs.on_reaction.add = va_arg(args, reaction_add_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case MESSAGE_REACTION_REMOVE:
      gw->cbs.on_reaction.remove = va_arg(args, reaction_remove_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case MESSAGE_REACTION_REMOVE_ALL:
      gw->cbs.on_reaction.remove_all = va_arg(args, reaction_remove_all_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case MESSAGE_REACTION_REMOVE_EMOJI:
      gw->cbs.on_reaction.remove_emoji = va_arg(args, reaction_remove_emoji_cb*);
      code |= intents::GUILD_MESSAGE_REACTIONS | intents::DIRECT_MESSAGE_REACTIONS;
      break;
  case GUILD_MEMBER_ADD:
      gw->cbs.on_guild_member.add = va_arg(args, guild_member_cb*);
      code |= intents::GUILD_MEMBERS;
      break;
  case GUILD_MEMBER_UPDATE:
      gw->cbs.on_guild_member.update = va_arg(args, guild_member_cb*);
      code |= intents::GUILD_MEMBERS;
      break;
  case GUILD_MEMBER_REMOVE:
      gw->cbs.on_guild_member.remove = va_arg(args, guild_member_remove_cb*);
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
  gateway::run(&client->gw);
}

void*
set_data(client *client, void *data) {
  return client->data = data;
}

void*
get_data(client *client) {
  return client->data;
}

void
replace_presence(client *client, presence::dati *presence)
{
  if (NULL == presence) return;

  presence::dati_free(client->gw.identify->presence);
  client->gw.identify->presence = presence;
}

void
set_presence(
  client *client, 
  presence::activity::dati *activity, //will take ownership
  char status[], 
  bool afk)
{
  using namespace presence;

  dati *presence = client->gw.identify->presence;

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
