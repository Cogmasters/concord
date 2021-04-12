#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isgraph() */

#include "discord.h"
#include "discord-common.h"
#include "orka-utils.h"


struct discord*
discord_init(const char token[])
{
  struct discord *new_client = calloc(1, sizeof *new_client);
  new_client->adapter.p_client = new_client;
  new_client->gw.p_client = new_client;
  discord_adapter_init(&new_client->adapter, token);
  discord_gateway_init(&new_client->gw, token);
  if (pthread_mutex_init(&new_client->lock, NULL))
    ERR("Couldn't initialize pthread mutex");
  return new_client;
}

struct discord*
discord_config_init(const char config_file[])
{
  struct discord *new_client = calloc(1, sizeof *new_client);
  new_client->adapter.p_client = new_client;
  new_client->gw.p_client = new_client;
  discord_adapter_config_init(&new_client->adapter, config_file);
  discord_gateway_config_init(&new_client->gw, config_file);
  if (pthread_mutex_init(&new_client->lock, NULL))
    ERR("Couldn't initialize pthread mutex");
  return new_client;
}

void
discord_cleanup(struct discord *client)
{
  discord_adapter_cleanup(&client->adapter);
  discord_gateway_cleanup(&client->gw);
  pthread_mutex_destroy(&client->lock);
  free(client);
}

void
discord_global_init() {
  if (0 != curl_global_init(CURL_GLOBAL_DEFAULT)) {
    log_warn("Couldn't start libcurl's globals");
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
discord_add_intents(struct discord *client, enum discord_gateway_intents code)
{
  if (WS_CONNECTED == ws_get_status(client->gw.ws)) {
    log_error("Can't set intents to a running client.");
    return;
  }

  client->gw.id->intents |= code;
}

void
discord_set_prefix(struct discord *client, char *prefix) 
{
  const size_t PREFIX_LEN = 32;
  if (!orka_str_bounds_check(prefix, PREFIX_LEN)) {
    log_error("Prefix length greater than threshold (%zu chars)", PREFIX_LEN);
    return;
  }

  client->gw.prefix = prefix;
}

void
discord_on_command(struct discord *client, char *command, message_cb *callback)
{
  const size_t CMD_LEN = 64;
  if (!orka_str_bounds_check(command, CMD_LEN)) {
    log_error("Command length greater than threshold (%zu chars)", CMD_LEN);
    return;
  }

  ++client->gw.num_cmd;
  client->gw.on_cmd = realloc(client->gw.on_cmd, client->gw.num_cmd * sizeof(struct cmd_cbs));

  client->gw.on_cmd[client->gw.num_cmd-1].str = command;
  client->gw.on_cmd[client->gw.num_cmd-1].cb = callback;

  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_on_idle(struct discord *client, idle_cb *callback) {
  client->gw.cbs.on_idle = callback;
}

void 
discord_on_event_raw(struct discord *client, event_raw_cb *callback) {
  client->gw.cbs.on_event_raw = callback;
}

void
discord_on_ready(struct discord *client, idle_cb *callback) {
  client->gw.cbs.on_ready = callback;
}

void
discord_run(struct discord *client) {
  ws_run(client->gw.ws);
}

void 
discord_on_guild_role_create(struct discord *client, guild_role_cb *callback) {
  client->gw.cbs.on_guild_role_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_on_guild_role_update(struct discord *client, guild_role_cb *callback) {
  client->gw.cbs.on_guild_role_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_on_guild_role_delete(struct discord *client, guild_role_delete_cb *callback) {
  client->gw.cbs.on_guild_role_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_on_guild_member_add(struct discord *client, guild_member_cb *callback) {
  client->gw.cbs.on_guild_member_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void 
discord_on_guild_member_update(struct discord *client, guild_member_cb *callback) {
  client->gw.cbs.on_guild_member_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void 
discord_on_guild_member_remove(struct discord *client, guild_member_remove_cb *callback) {
  client->gw.cbs.on_guild_member_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void 
discord_on_guild_ban_add(struct discord *client, guild_ban_cb *callback) {
  client->gw.cbs.on_guild_ban_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void 
discord_on_guild_ban_remove(struct discord *client, guild_ban_cb *callback) {
  client->gw.cbs.on_guild_ban_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void 
discord_on_channel_create(struct discord *client, channel_cb *callback) {
  client->gw.cbs.on_channel_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_on_channel_update(struct discord *client, channel_cb *callback) {
  client->gw.cbs.on_channel_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_on_channel_delete(struct discord *client, channel_cb *callback) {
  client->gw.cbs.on_channel_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_on_channel_pins_update(struct discord *client, channel_pins_update_cb *callback) {
  client->gw.cbs.on_channel_pins_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_on_message_create(struct discord *client, message_cb *callback) {
  client->gw.cbs.on_message_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void 
discord_on_sb_message_create(struct discord *client, sb_message_cb *callback)
{
  client->gw.cbs.sb_on_message_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_on_message_update(struct discord *client, message_cb *callback) {
  client->gw.cbs.on_message_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void 
discord_on_sb_message_update(struct discord *client, sb_message_cb *callback)
{
  client->gw.cbs.sb_on_message_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_on_message_delete(struct discord *client, message_delete_cb *callback) {
  client->gw.cbs.on_message_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_on_message_delete_bulk(struct discord *client, message_delete_bulk_cb *callback) {
  client->gw.cbs.on_message_delete_bulk = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_on_message_reaction_add(struct discord *client, message_reaction_add_cb *callback) {
  client->gw.cbs.on_message_reaction_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_on_message_reaction_remove(struct discord *client, message_reaction_remove_cb *callback) {
  client->gw.cbs.on_message_reaction_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_on_message_reaction_remove_all(struct discord *client, message_reaction_remove_all_cb* callback) {
  client->gw.cbs.on_message_reaction_remove_all = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_on_message_reaction_remove_emoji(struct discord *client, message_reaction_remove_emoji_cb *callback) {
  client->gw.cbs.on_message_reaction_remove_emoji = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_on_voice_state_update(struct discord *client, voice_state_update_cb *callback)
{
  client->gw.cbs.on_voice_state_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_on_voice_server_update(struct discord *client, voice_server_update_cb *callback)
{
  client->gw.cbs.on_voice_server_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_replace_presence(struct discord *client, struct discord_gateway_status_update *presence)
{
  if (NULL == presence) return;

  discord_gateway_status_update_free(client->gw.id->presence);
  client->gw.id->presence = presence;
}

void
discord_set_presence(
  struct discord *client, 
  struct discord_gateway_activity *activity, //will take ownership
  char status[], 
  bool afk)
{
  struct discord_gateway_status_update *presence = client->gw.id->presence;

  if (activity) {
    presence->activities = (void*)ntl_append((void*)presence->activities, 
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
