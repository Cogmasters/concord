#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //for isgraph()

#include "libdiscord.h"
#include "discord-common.h"
#include "orka-utils.h"


struct discord*
discord_init(const char token[])
{
  struct discord *new_client = calloc(1, sizeof *new_client);
  new_client->adapter.p_client = new_client;
  new_client->gw.p_client = new_client;
  discord_adapter_init(&new_client->adapter, token, NULL);
  discord_gateway_init(&new_client->gw, token, NULL);
  return new_client;
}

struct discord*
discord_config_init(const char config_file[])
{
  struct discord *new_client = calloc(1, sizeof *new_client);
  new_client->adapter.p_client = new_client;
  new_client->gw.p_client = new_client;
  discord_adapter_init(&new_client->adapter, NULL, config_file);
  discord_gateway_init(&new_client->gw, NULL, config_file);
  return new_client;
}

void
discord_cleanup(struct discord *client)
{
  discord_adapter_cleanup(&client->adapter);
  discord_gateway_cleanup(&client->gw);
  free(client);
}

void
discord_global_init() {
  if (0 != curl_global_init(CURL_GLOBAL_DEFAULT)) {
    PUTS("Couldn't start libcurl's globals");
  }
}

void
discord_global_cleanup() {
  curl_global_cleanup();
}

//@todo make this thread safe
void*
discord_set_data(struct discord *client, void *data) {
  return client->data = data;
}

//@todo make this thread safe
void*
discord_get_data(struct discord *client) {
  return client->data;
}

void
discord_add_intents(struct discord *client, int intent_code)
{
  if (WS_CONNECTED == ws_get_status(client->gw.ws)) {
    PUTS("Can't set intents to a running client.");
    return;
  }

  client->gw.identify->intents |= intent_code;
}

void
discord_set_prefix(struct discord *client, char *prefix) 
{
  const size_t PREFIX_LEN = 32;
  if (!orka_str_bounds_check(prefix, PREFIX_LEN)) {
    PRINT("Prefix length greater than threshold (%zu chars)", PREFIX_LEN);
    return;
  }

  client->gw.prefix = prefix;
}

void
discord_setcb_command(struct discord *client, char *command, message_cb *user_cb)
{
  struct discord_gateway *gw = &client->gw;

  const size_t CMD_LEN = 64;
  if (!orka_str_bounds_check(command, CMD_LEN)) {
    PRINT("Command length greater than threshold (%zu chars)", CMD_LEN);
    return;
  }

  ++gw->num_cmd;
  gw->on_cmd = realloc(gw->on_cmd, gw->num_cmd * sizeof(struct cmd_cbs));

  gw->on_cmd[gw->num_cmd-1].str = command;
  gw->on_cmd[gw->num_cmd-1].cb = user_cb;

  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

#define callback ... // varargs to avoid non-conforming function pointer error

void
discord_setcb(struct discord *client, enum dispatch_code opt, callback)
{
  struct discord_gateway *gw = &client->gw;

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
      code |= DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES;
      break;
  case SB_MESSAGE_CREATE: /* @todo this is temporary for wrapping JS */
      gw->cbs.on_message.sb_create = va_arg(args, sb_message_cb*);
      code |= DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES;
      break;
  case MESSAGE_UPDATE:
      gw->cbs.on_message.update = va_arg(args, message_cb*);
      code |= DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES;
      break;
  case MESSAGE_DELETE:
      gw->cbs.on_message.del = va_arg(args, message_delete_cb*);
      code |= DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES;
      break;
  case MESSAGE_DELETE_BULK:
      gw->cbs.on_message.delete_bulk = va_arg(args, message_delete_bulk_cb*);
      code |= DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES;
      break;
  case MESSAGE_REACTION_ADD:
      gw->cbs.on_reaction.add = va_arg(args, reaction_add_cb*);
      code |= DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS;
      break;
  case MESSAGE_REACTION_REMOVE:
      gw->cbs.on_reaction.remove = va_arg(args, reaction_remove_cb*);
      code |= DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS;
      break;
  case MESSAGE_REACTION_REMOVE_ALL:
      gw->cbs.on_reaction.remove_all = va_arg(args, reaction_remove_all_cb*);
      code |= DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS;
      break;
  case MESSAGE_REACTION_REMOVE_EMOJI:
      gw->cbs.on_reaction.remove_emoji = va_arg(args, reaction_remove_emoji_cb*);
      code |= DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS;
      break;
  case GUILD_MEMBER_ADD:
      gw->cbs.on_guild_member.add = va_arg(args, guild_member_cb*);
      code |= DISCORD_GATEWAY_GUILD_MEMBERS;
      break;
  case GUILD_MEMBER_UPDATE:
      gw->cbs.on_guild_member.update = va_arg(args, guild_member_cb*);
      code |= DISCORD_GATEWAY_GUILD_MEMBERS;
      break;
  case GUILD_MEMBER_REMOVE:
      gw->cbs.on_guild_member.remove = va_arg(args, guild_member_remove_cb*);
      code |= DISCORD_GATEWAY_GUILD_MEMBERS;
      break;
  default:
      ERR("Invalid callback_opt (code: %d)", opt);
  }

  discord_add_intents(client, code);

  va_end(args);
}

void
discord_replace_presence(struct discord *client, struct discord_gateway_identify_status_update *presence)
{
  if (NULL == presence) return;

  discord_gateway_identify_status_update_free(client->gw.identify->presence);
  client->gw.identify->presence = presence;
}

void
discord_set_presence(
  struct discord *client, 
  struct discord_gateway_identify_status_update_activity *activity, //will take ownership
  char status[], 
  bool afk)
{
  struct discord_gateway_identify_status_update *presence = client->gw.identify->presence;

  if (activity) {
    presence->activities = ntl_append(presence->activities, 
                              sizeof **presence->activities, activity);
  }
  if (status) {
    int ret = snprintf(presence->status, 
                sizeof(presence->status), "%s", status);

    ASSERT_S(ret < (int)sizeof(presence->status),
        "Out of bounds write attempt");
  }

  presence->afk = afk;
}
