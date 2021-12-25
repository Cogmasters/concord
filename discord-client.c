#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isgraph() */
#include <errno.h>

#include "discord.h"
#include "discord-internal.h"
#include "cee-utils.h"

static void
_discord_init(struct discord *new_client)
{
  orca_global_init();

  discord_adapter_init(&new_client->adapter, &new_client->conf,
                       &new_client->token);
  discord_gateway_init(&new_client->gw, &new_client->conf, &new_client->token);
  discord_voice_connections_init(new_client);

  /* fetch the client user structure */
  if (new_client->token.size) {
    discord_get_current_user(new_client, &new_client->self);
  }

  new_client->is_original = true;
}

struct discord *
discord_init(const char token[])
{
  struct discord *new_client;

  new_client = calloc(1, sizeof *new_client);
  logconf_setup(&new_client->conf, "DISCORD", NULL);
  /* silence terminal input by default */
  logconf_set_quiet(&new_client->conf, true);

  new_client->token.start = (char *)token;
  new_client->token.size = token ? cee_str_bounds_check(token, 128) : 0;

  _discord_init(new_client);

  return new_client;
}

struct discord *
discord_config_init(const char config_file[])
{
  struct discord *new_client;
  FILE *fp;

  fp = fopen(config_file, "rb");
  VASSERT_S(fp != NULL, "Couldn't open '%s': %s", config_file,
            strerror(errno));

  new_client = calloc(1, sizeof *new_client);
  logconf_setup(&new_client->conf, "DISCORD", fp);

  fclose(fp);

  new_client->token = logconf_get_field(&new_client->conf, "discord.token");
  if (STRNEQ("YOUR-BOT-TOKEN", new_client->token.start,
             new_client->token.size)) {
    memset(&new_client->token, 0, sizeof(new_client->token));
  }

  _discord_init(new_client);

  return new_client;
}

struct discord *
discord_clone(const struct discord *orig_client)
{
  struct discord *clone_client = malloc(sizeof(struct discord));

  memcpy(clone_client, orig_client, sizeof(struct discord));
  clone_client->is_original = false;

  return clone_client;
}

void
discord_cleanup(struct discord *client)
{
  if (client->is_original) {
    logconf_cleanup(&client->conf);
    discord_adapter_cleanup(&client->adapter);
    discord_gateway_cleanup(&client->gw);
    discord_user_cleanup(&client->self);
  }
  free(client);
}

void
discord_async_next(struct discord *client, struct discord_async_attr *attr)
{
  discord_adapter_async_next(&client->adapter, attr);
}

const char *
discord_strerror(ORCAcode code, struct discord *client)
{
  switch (code) {
  default:
    return orca_strerror(code);
  case ORCA_DISCORD_JSON_CODE:
    return client ? client->adapter.errbuf
                  : "Discord JSON Error Code: Failed request";
  case ORCA_DISCORD_BAD_AUTH:
    return "Discord Bad Authentication: Bad authentication token";
  case ORCA_DISCORD_RATELIMIT:
    return "Discord Ratelimit: You are being ratelimited";
  case ORCA_DISCORD_CONNECTION:
    return "Discord Connection: Couldn't establish a connection to discord";
  }
}

void *
discord_set_data(struct discord *client, void *data)
{
  return client->data = data;
}

void *
discord_get_data(struct discord *client)
{
  return client->data;
}

void
discord_add_intents(struct discord *client, enum discord_gateway_intents code)
{
  if (WS_CONNECTED == ws_get_status(client->gw.ws)) {
    logconf_error(&client->conf, "Can't set intents to a running client.");
    return;
  }

  client->gw.id.intents |= code;
}

void
discord_remove_intents(struct discord *client,
                       enum discord_gateway_intents code)
{
  if (WS_CONNECTED == ws_get_status(client->gw.ws)) {
    logconf_error(&client->conf,
                  "Can't remove intents from a running client.");
    return;
  }

  client->gw.id.intents &= ~code;
}

void
discord_set_prefix(struct discord *client, char *prefix)
{
  if (IS_EMPTY_STRING(prefix)) return;

  if (client->gw.cmds.prefix.start) free(client->gw.cmds.prefix.start);

  client->gw.cmds.prefix.size =
    cee_strndup(prefix, strlen(prefix), &client->gw.cmds.prefix.start);
}

const struct discord_user *
discord_get_self(struct discord *client)
{
  return &client->self;
}

void
discord_set_on_command(struct discord *client,
                       char *command,
                       discord_on_message callback)
{
  /**
   * default command callback if prefix is detected, but command isn't
   *  specified
   */
  if (client->gw.cmds.prefix.size && IS_EMPTY_STRING(command)) {
    client->gw.cmds.on_default.cb = callback;
    return; /* EARLY RETURN */
  }

  ++client->gw.cmds.amt;
  client->gw.cmds.pool = realloc(
    client->gw.cmds.pool, client->gw.cmds.amt * sizeof(*client->gw.cmds.pool));

  client->gw.cmds.pool[client->gw.cmds.amt - 1].start = command;
  client->gw.cmds.pool[client->gw.cmds.amt - 1].size = strlen(command);
  client->gw.cmds.pool[client->gw.cmds.amt - 1].cb = callback;

  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_commands(struct discord *client,
                        discord_on_message callback,
                        ...)
{
  char *command = NULL;
  va_list commands;

  va_start(commands, callback);

  command = va_arg(commands, char *);
  while (command != NULL) {
    discord_set_on_command(client, command, callback);
    command = va_arg(commands, char *);
  }

  va_end(commands);
}

void
discord_set_event_scheduler(struct discord *client,
                            discord_event_scheduler callback)
{
  client->gw.cmds.scheduler = callback;
}

void
discord_set_on_idle(struct discord *client, discord_on_idle callback)
{
  client->gw.cmds.cbs.on_idle = callback;
}

void
discord_set_on_ready(struct discord *client, discord_on_idle callback)
{
  client->gw.cmds.cbs.on_ready = callback;
}

ORCAcode
discord_run(struct discord *client)
{
  ORCAcode code;

  while (1) {
    code = discord_gateway_start(&client->gw);
    if (code != ORCA_OK) break;

    do {
      code = discord_gateway_perform(&client->gw);
      if (code != ORCA_OK) break;

      code = discord_adapter_perform(&client->adapter);
      if (code != ORCA_OK) break;
    } while (1);

    if (discord_gateway_end(&client->gw)) {
      discord_adapter_stop_all(&client->adapter);
      break;
    }
  }

  return code;
}

void
discord_shutdown(struct discord *client)
{
  return discord_gateway_shutdown(&client->gw);
}

void
discord_reconnect(struct discord *client, bool resume)
{
  return discord_gateway_reconnect(&client->gw, resume);
}

void
discord_set_on_guild_role_create(struct discord *client,
                                 discord_on_guild_role callback)
{
  client->gw.cmds.cbs.on_guild_role_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_role_update(struct discord *client,
                                 discord_on_guild_role callback)
{
  client->gw.cmds.cbs.on_guild_role_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_role_delete(struct discord *client,
                                 discord_on_guild_role_delete callback)
{
  client->gw.cmds.cbs.on_guild_role_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_member_add(struct discord *client,
                                discord_on_guild_member callback)
{
  client->gw.cmds.cbs.on_guild_member_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_member_update(struct discord *client,
                                   discord_on_guild_member callback)
{
  client->gw.cmds.cbs.on_guild_member_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_member_remove(struct discord *client,
                                   discord_on_guild_member_remove callback)
{
  client->gw.cmds.cbs.on_guild_member_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MEMBERS);
}

void
discord_set_on_guild_ban_add(struct discord *client,
                             discord_on_guild_ban callback)
{
  client->gw.cmds.cbs.on_guild_ban_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void
discord_set_on_guild_ban_remove(struct discord *client,
                                discord_on_guild_ban callback)
{
  client->gw.cmds.cbs.on_guild_ban_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_BANS);
}

void
discord_set_on_application_command_create(
  struct discord *client, discord_on_application_command callback)
{
  client->gw.cmds.cbs.on_application_command_create = callback;
}

void
discord_set_on_application_command_update(
  struct discord *client, discord_on_application_command callback)
{
  client->gw.cmds.cbs.on_application_command_update = callback;
}

void
discord_set_on_application_command_delete(
  struct discord *client, discord_on_application_command callback)
{
  client->gw.cmds.cbs.on_application_command_delete = callback;
}

void
discord_set_on_channel_create(struct discord *client,
                              discord_on_channel callback)
{
  client->gw.cmds.cbs.on_channel_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_update(struct discord *client,
                              discord_on_channel callback)
{
  client->gw.cmds.cbs.on_channel_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_delete(struct discord *client,
                              discord_on_channel callback)
{
  client->gw.cmds.cbs.on_channel_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_channel_pins_update(struct discord *client,
                                   discord_on_channel_pins_update callback)
{
  client->gw.cmds.cbs.on_channel_pins_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_create(struct discord *client,
                             discord_on_channel callback)
{
  client->gw.cmds.cbs.on_thread_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_update(struct discord *client,
                             discord_on_channel callback)
{
  client->gw.cmds.cbs.on_thread_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_thread_delete(struct discord *client,
                             discord_on_channel callback)
{
  client->gw.cmds.cbs.on_thread_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_create(struct discord *client, discord_on_guild callback)
{
  client->gw.cmds.cbs.on_guild_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_update(struct discord *client, discord_on_guild callback)
{
  client->gw.cmds.cbs.on_guild_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_guild_delete(struct discord *client,
                            discord_on_guild_delete callback)
{
  client->gw.cmds.cbs.on_guild_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILDS);
}

void
discord_set_on_message_create(struct discord *client,
                              discord_on_message callback)
{
  client->gw.cmds.cbs.on_message_create = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_update(struct discord *client,
                              discord_on_message callback)
{
  client->gw.cmds.cbs.on_message_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete(struct discord *client,
                              discord_on_message_delete callback)
{
  client->gw.cmds.cbs.on_message_delete = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_delete_bulk(struct discord *client,
                                   discord_on_message_delete_bulk callback)
{
  client->gw.cmds.cbs.on_message_delete_bulk = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGES
                                | DISCORD_GATEWAY_DIRECT_MESSAGES);
}

void
discord_set_on_message_reaction_add(struct discord *client,
                                    discord_on_message_reaction_add callback)
{
  client->gw.cmds.cbs.on_message_reaction_add = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                                | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove(
  struct discord *client, discord_on_message_reaction_remove callback)
{
  client->gw.cmds.cbs.on_message_reaction_remove = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                                | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_all(
  struct discord *client, discord_on_message_reaction_remove_all callback)
{
  client->gw.cmds.cbs.on_message_reaction_remove_all = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                                | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_message_reaction_remove_emoji(
  struct discord *client, discord_on_message_reaction_remove_emoji callback)
{
  client->gw.cmds.cbs.on_message_reaction_remove_emoji = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS
                                | DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS);
}

void
discord_set_on_interaction_create(struct discord *client,
                                  discord_on_interaction callback)
{
  client->gw.cmds.cbs.on_interaction_create = callback;
}

void
discord_set_on_voice_state_update(struct discord *client,
                                  discord_on_voice_state_update callback)
{
  client->gw.cmds.cbs.on_voice_state_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_on_voice_server_update(struct discord *client,
                                   discord_on_voice_server_update callback)
{
  client->gw.cmds.cbs.on_voice_server_update = callback;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_voice_cbs(struct discord *client,
                      struct discord_voice_cbs *callbacks)
{
  if (callbacks->on_speaking)
    client->voice_cbs.on_speaking = callbacks->on_speaking;
  if (callbacks->on_codec) client->voice_cbs.on_codec = callbacks->on_codec;
  if (callbacks->on_session_descriptor)
    client->voice_cbs.on_session_descriptor = callbacks->on_session_descriptor;
  if (callbacks->on_client_disconnect)
    client->voice_cbs.on_client_disconnect = callbacks->on_client_disconnect;
  if (callbacks->on_ready) client->voice_cbs.on_ready = callbacks->on_ready;
  if (callbacks->on_idle) client->voice_cbs.on_idle = callbacks->on_idle;
  if (callbacks->on_udp_server_connected)
    client->voice_cbs.on_udp_server_connected =
      callbacks->on_udp_server_connected;
  discord_add_intents(client, DISCORD_GATEWAY_GUILD_VOICE_STATES);
}

void
discord_set_presence(struct discord *client,
                     struct discord_presence_status *presence)
{
  memcpy(client->gw.id.presence, presence, sizeof *presence);
}

int
discord_get_ping(struct discord *client)
{
  int ping_ms;

  pthread_rwlock_rdlock(&client->gw.timer->rwlock);
  ping_ms = client->gw.timer->ping_ms;
  pthread_rwlock_unlock(&client->gw.timer->rwlock);

  return ping_ms;
}

uint64_t
discord_timestamp(struct discord *client)
{
  /* get WebSockets internal timestamp if available */
  if (ws_is_functional(client->gw.ws)) {
    return ws_timestamp(client->gw.ws);
  }
  return cee_timestamp_ms();
}

struct logconf *
discord_get_logconf(struct discord *client)
{
  return &client->conf;
}

/******************************************************************************
 * The following functions are deprecated
 ******************************************************************************/

void
discord_global_init()
{
  orca_global_init();
}

void
discord_global_cleanup()
{
  orca_global_cleanup();
}
