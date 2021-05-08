#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isgraph() */

#include "discord.h"
#include "discord-internal.h"
#include "orka-utils.h"


static void
_discord_init(struct discord *new_client)
{
  new_client->adapter.p_client = new_client;
  new_client->gw.p_client = new_client;
  discord_adapter_init(
    &new_client->adapter, 
    &new_client->config, 
    &new_client->token);
  discord_gateway_init(
    &new_client->gw, 
    &new_client->config,
    &new_client->token);

  discord_init_voice_cbs(&new_client->voice_cbs);
}

struct discord*
discord_init(const char token[])
{
  struct discord *new_client = calloc(1, sizeof *new_client);

  logconf_setup(&new_client->config, NULL);
  new_client->token = (struct sized_buffer){
    .start = (char*)token,
    .size = orka_str_bounds_check(token, 128) // avoid overflow
  };

  _discord_init(new_client);

  return new_client;
}

struct discord*
discord_config_init(const char config_file[])
{
  struct discord *new_client = calloc(1, sizeof *new_client);

  logconf_setup(&new_client->config, config_file);
  new_client->token = logconf_get_field(&new_client->config, "discord.token");

  _discord_init(new_client);

  return new_client;
}

void
discord_cleanup(struct discord *client)
{
  logconf_cleanup(&client->config);
  discord_adapter_cleanup(&client->adapter);
  discord_gateway_cleanup(&client->gw);
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
  if (!prefix) return;

  const size_t PREFIX_LEN = sizeof(client->gw.prefix);
  ssize_t len;
  if (!(len = orka_str_bounds_check(prefix, PREFIX_LEN))) {
    log_error("Prefix length greater than threshold (%zu chars)", PREFIX_LEN);
    return;
  }

  client->gw.prefix = (struct sized_buffer){
    .start = prefix,
    .size = (size_t)len
  };
}

void
discord_set_on_command(struct discord *client, char *command, message_cb *callback)
{
  /** 
   * default command callback if prefix is detected, but command isn't
   *  specified
   */
  if (client->gw.prefix.size && IS_EMPTY_STRING(command)) 
  {
    client->gw.on_default_cmd = (struct cmd_cbs){ .cb = callback };
    return; /* EARLY RETURN */
  }

  const size_t CMD_LEN = 64;
  ssize_t len;
  if (!(len = orka_str_bounds_check(command, CMD_LEN))) 
  {
    log_error("Command length greater than threshold (%zu chars)", CMD_LEN);
    return;
  }

  ++client->gw.num_cmd;
  client->gw.on_cmd = realloc(client->gw.on_cmd, client->gw.num_cmd * sizeof(struct cmd_cbs));

  client->gw.on_cmd[client->gw.num_cmd-1] = (struct cmd_cbs){
    .start = command,
    .size = (size_t)len,
    .cb = callback
  };

  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_idle(struct discord *client, idle_cb *callback) {
  client->gw.cbs.on_idle = callback;
}

void 
discord_set_on_event_raw(struct discord *client, event_raw_cb *callback) {
  client->gw.cbs.on_event_raw = callback;
}

void
discord_set_on_ready(struct discord *client, idle_cb *callback) {
  client->gw.cbs.on_ready = callback;
}

void
discord_run(struct discord *client) {
  discord_gateway_run(&client->gw);
}

void 
discord_set_on_guild_role_create(struct discord *client, guild_role_cb *callback) {
  client->gw.cbs.on_guild_role_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_set_on_guild_role_update(struct discord *client, guild_role_cb *callback) {
  client->gw.cbs.on_guild_role_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_set_on_guild_role_delete(struct discord *client, guild_role_delete_cb *callback) {
  client->gw.cbs.on_guild_role_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_set_on_guild_member_add(struct discord *client, guild_member_cb *callback) {
  client->gw.cbs.on_guild_member_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void 
discord_set_on_guild_member_update(struct discord *client, guild_member_cb *callback) {
  client->gw.cbs.on_guild_member_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void 
discord_set_on_guild_member_remove(struct discord *client, guild_member_remove_cb *callback) {
  client->gw.cbs.on_guild_member_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void 
discord_set_on_guild_ban_add(struct discord *client, guild_ban_cb *callback) {
  client->gw.cbs.on_guild_ban_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void 
discord_set_on_guild_ban_remove(struct discord *client, guild_ban_cb *callback) {
  client->gw.cbs.on_guild_ban_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void 
discord_set_on_channel_create(struct discord *client, channel_cb *callback) {
  client->gw.cbs.on_channel_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_set_on_channel_update(struct discord *client, channel_cb *callback) {
  client->gw.cbs.on_channel_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_set_on_channel_delete(struct discord *client, channel_cb *callback) {
  client->gw.cbs.on_channel_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void 
discord_set_on_channel_pins_update(struct discord *client, channel_pins_update_cb *callback) {
  client->gw.cbs.on_channel_pins_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_message_create(struct discord *client, message_cb *callback) {
  client->gw.cbs.on_message_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void 
discord_set_on_sb_message_create(struct discord *client, sb_message_cb *callback)
{
  client->gw.cbs.sb_on_message_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_update(struct discord *client, message_cb *callback) {
  client->gw.cbs.on_message_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void 
discord_set_on_sb_message_update(struct discord *client, sb_message_cb *callback)
{
  client->gw.cbs.sb_on_message_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete(struct discord *client, message_delete_cb *callback) {
  client->gw.cbs.on_message_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete_bulk(struct discord *client, message_delete_bulk_cb *callback) {
  client->gw.cbs.on_message_delete_bulk = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_reaction_add(struct discord *client, message_reaction_add_cb *callback) {
  client->gw.cbs.on_message_reaction_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove(struct discord *client, message_reaction_remove_cb *callback) {
  client->gw.cbs.on_message_reaction_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_all(struct discord *client, message_reaction_remove_all_cb* callback) {
  client->gw.cbs.on_message_reaction_remove_all = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_emoji(struct discord *client, message_reaction_remove_emoji_cb *callback) {
  client->gw.cbs.on_message_reaction_remove_emoji = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_voice_state_update(struct discord *client, voice_state_update_cb *callback)
{
  client->gw.cbs.on_voice_state_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_on_voice_server_update(struct discord *client, voice_server_update_cb *callback)
{
  client->gw.cbs.on_voice_server_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_voice_cbs(struct discord *client, struct discord_voice_cbs *callbacks)
{
  if (callbacks->on_speaking)
    client->voice_cbs.on_speaking = callbacks->on_speaking;
  if (callbacks->on_codec)
    client->voice_cbs.on_codec = callbacks->on_codec;
  if (callbacks->on_session_descriptor)
    client->voice_cbs.on_session_descriptor = callbacks->on_session_descriptor;
  if (callbacks->on_client_disconnect)
    client->voice_cbs.on_client_disconnect = callbacks->on_client_disconnect;
  if (callbacks->on_ready)
    client->voice_cbs.on_ready = callbacks->on_ready;
  if (callbacks->on_idle)
    client->voice_cbs.on_idle = callbacks->on_idle;
}

void
discord_set_blocking_event_handler(struct discord *client, enum discord_event_handling_mode (*f)(void *cxt))
{
  client->gw.blocking_event_handler = f;
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
  struct discord_gateway_activity *activity, // can be safely free'd
  char status[], 
  bool afk)
{
  struct discord_gateway_status_update *presence = client->gw.id->presence;

  if (activity) {
    ntl_append2((ntl_t*)&presence->activities, sizeof(struct discord_gateway_activity), activity);
  }
  if (status) {
    int ret = snprintf(presence->status, sizeof(presence->status), "%s", status);
    ASSERT_S(ret < sizeof(presence->status), "Out of bounds write attempt");
  }

  presence->afk = afk;
}
