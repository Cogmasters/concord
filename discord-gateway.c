#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> /* offsetof() */
#include <ctype.h> /* isspace() */

#include "discord.h"
#include "discord-internal.h"

/* get client from gw pointer */
#define CLIENT(p_gw)                                                          \
  (struct discord *)((int8_t *)(p_gw)-offsetof(struct discord, gw))

/* shorten event callback for maintainability purposes */
#define ON(event, ...)                                                        \
  (*gw->user_cmd->cbs.on_##event)(CLIENT(gw), &gw->bot, ##__VA_ARGS__)

static void
sized_buffer_from_json(char *json, size_t len, void *data)
{
  struct sized_buffer *p = data;
  p->size = asprintf(&p->start, "%.*s", (int)len, json);
}

ORCAcode
discord_get_gateway(struct discord *client, struct sized_buffer *p_json)
{
  if (!p_json) {
    logconf_error(client->conf, "Missing 'p_json'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &sized_buffer_from_json,
                              .ok_obj = p_json },
    NULL, HTTP_GET, "/gateway");
}

ORCAcode
discord_get_gateway_bot(struct discord *client, struct sized_buffer *p_json)
{
  if (!p_json) {
    logconf_error(client->conf, "Missing 'p_json'");
    return ORCA_MISSING_PARAMETER;
  }

  return discord_adapter_run(
    &client->adapter,
    &(struct ua_resp_handle){ .ok_cb = &sized_buffer_from_json,
                              .ok_obj = p_json },
    NULL, HTTP_GET, "/gateway/bot");
}

static const char *
opcode_print(enum discord_gateway_opcodes opcode)
{
  const char *str = discord_gateway_opcodes_print(opcode);
  if (NULL == str) {
    log_warn("Invalid Gateway opcode (client->conf, code: %d)", opcode);
    str = "Invalid Gateway opcode";
  }
  return str;
}

static const char *
close_opcode_print(enum discord_gateway_close_opcodes opcode)
{
  const char *str = discord_gateway_close_opcodes_print(opcode);
  if (str) return str;
  str = ws_close_opcode_print((enum ws_close_reason)opcode);
  if (str) return str;
  log_warn("Unknown WebSockets close opcode (client->conf, code: %d)", opcode);
  return "Unknown WebSockets close opcode";
}

static void
send_resume(struct discord_gateway *gw)
{
  gw->status->is_resumable = false; /* reset */

  char payload[1024];
  size_t ret = json_inject(payload, sizeof(payload),
                           "(op):6" /* RESUME OPCODE */
                           "(d):{"
                           "(token):s"
                           "(session_id):s"
                           "(seq):d"
                           "}",
                           gw->id.token, gw->session_id, &gw->payload->seq);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  struct ws_info info = { 0 };
  ws_send_text(gw->ws, &info, payload, ret);

  logconf_info(
    &gw->conf,
    ANSICOLOR("SEND", ANSI_FG_BRIGHT_GREEN) " RESUME (%d bytes) [@@@_%zu_@@@]",
    ret, info.loginfo.counter + 1);
}

static void
send_identify(struct discord_gateway *gw)
{
  /* Ratelimit check */
  if ((ws_timestamp(gw->ws) - gw->session.identify_tstamp) < 5) {
    ++gw->session.concurrent;
    VASSERT_S(gw->session.concurrent < gw->session.start_limit.max_concurrency,
              "Reach identify request threshold (%d every 5 seconds)",
              gw->session.start_limit.max_concurrency);
  }
  else {
    gw->session.concurrent = 0;
  }

  char payload[1024];
  size_t ret = json_inject(payload, sizeof(payload),
                           "(op):2" /* IDENTIFY OPCODE */
                           "(d):F",
                           &discord_identify_to_json_v, &gw->id);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  struct ws_info info = { 0 };
  ws_send_text(gw->ws, &info, payload, ret);

  logconf_info(
    &gw->conf,
    ANSICOLOR("SEND",
              ANSI_FG_BRIGHT_GREEN) " IDENTIFY (%d bytes) [@@@_%zu_@@@]",
    ret, info.loginfo.counter + 1);

  /*get timestamp for this identify */
  gw->session.identify_tstamp = ws_timestamp(gw->ws);
}

/* send heartbeat pulse to websockets server in order
 *  to maintain connection alive */
static void
send_heartbeat(struct discord_gateway *gw)
{
  char payload[64];
  int ret =
    json_inject(payload, sizeof(payload), "(op):1,(d):d", &gw->payload->seq);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  struct ws_info info = { 0 };
  ws_send_text(gw->ws, &info, payload, ret);

  logconf_info(
    &gw->conf,
    ANSICOLOR("SEND",
              ANSI_FG_BRIGHT_GREEN) " HEARTBEAT (%d bytes) [@@@_%zu_@@@]",
    ret, info.loginfo.counter + 1);

  gw->hbeat->tstamp = ws_timestamp(gw->ws); /*update heartbeat timestamp */
}

static void
on_hello(struct discord_gateway *gw)
{
  gw->hbeat->interval_ms = 0;
  gw->hbeat->tstamp = cee_timestamp_ms();

  json_extract(gw->payload->event_data.start, gw->payload->event_data.size,
               "(heartbeat_interval):ld", &gw->hbeat->interval_ms);

  if (gw->status->is_resumable)
    send_resume(gw);
  else
    send_identify(gw);
}

static enum discord_gateway_events
get_dispatch_event(char event_name[])
{
#define RETURN_IF_MATCH(event, str)                                           \
  if (STREQ(#event, str)) return DISCORD_GATEWAY_EVENTS_##event
  RETURN_IF_MATCH(READY, event_name);
  RETURN_IF_MATCH(RESUMED, event_name);
  RETURN_IF_MATCH(APPLICATION_COMMAND_CREATE, event_name);
  RETURN_IF_MATCH(APPLICATION_COMMAND_UPDATE, event_name);
  RETURN_IF_MATCH(APPLICATION_COMMAND_DELETE, event_name);
  RETURN_IF_MATCH(CHANNEL_CREATE, event_name);
  RETURN_IF_MATCH(CHANNEL_UPDATE, event_name);
  RETURN_IF_MATCH(CHANNEL_DELETE, event_name);
  RETURN_IF_MATCH(CHANNEL_PINS_UPDATE, event_name);
  RETURN_IF_MATCH(THREAD_CREATE, event_name);
  RETURN_IF_MATCH(THREAD_UPDATE, event_name);
  RETURN_IF_MATCH(THREAD_DELETE, event_name);
  RETURN_IF_MATCH(THREAD_LIST_SYNC, event_name);
  RETURN_IF_MATCH(THREAD_MEMBER_UPDATE, event_name);
  RETURN_IF_MATCH(THREAD_MEMBERS_UPDATE, event_name);
  RETURN_IF_MATCH(GUILD_CREATE, event_name);
  RETURN_IF_MATCH(GUILD_UPDATE, event_name);
  RETURN_IF_MATCH(GUILD_DELETE, event_name);
  RETURN_IF_MATCH(GUILD_BAN_ADD, event_name);
  RETURN_IF_MATCH(GUILD_BAN_REMOVE, event_name);
  RETURN_IF_MATCH(GUILD_EMOJIS_UPDATE, event_name);
  RETURN_IF_MATCH(GUILD_STICKERS_UPDATE, event_name);
  RETURN_IF_MATCH(GUILD_INTEGRATIONS_UPDATE, event_name);
  RETURN_IF_MATCH(GUILD_MEMBER_ADD, event_name);
  RETURN_IF_MATCH(GUILD_MEMBER_UPDATE, event_name);
  RETURN_IF_MATCH(GUILD_MEMBER_REMOVE, event_name);
  RETURN_IF_MATCH(GUILD_MEMBERS_CHUNK, event_name);
  RETURN_IF_MATCH(GUILD_ROLE_CREATE, event_name);
  RETURN_IF_MATCH(GUILD_ROLE_UPDATE, event_name);
  RETURN_IF_MATCH(GUILD_ROLE_DELETE, event_name);
  RETURN_IF_MATCH(INTEGRATION_CREATE, event_name);
  RETURN_IF_MATCH(INTEGRATION_UPDATE, event_name);
  RETURN_IF_MATCH(INTEGRATION_DELETE, event_name);
  RETURN_IF_MATCH(INTERACTION_CREATE, event_name);
  RETURN_IF_MATCH(INVITE_CREATE, event_name);
  RETURN_IF_MATCH(INVITE_DELETE, event_name);
  RETURN_IF_MATCH(MESSAGE_CREATE, event_name);
  RETURN_IF_MATCH(MESSAGE_UPDATE, event_name);
  RETURN_IF_MATCH(MESSAGE_DELETE, event_name);
  RETURN_IF_MATCH(MESSAGE_DELETE_BULK, event_name);
  RETURN_IF_MATCH(MESSAGE_REACTION_ADD, event_name);
  RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE, event_name);
  RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE_ALL, event_name);
  RETURN_IF_MATCH(MESSAGE_REACTION_REMOVE_EMOJI, event_name);
  RETURN_IF_MATCH(PRESENCE_UPDATE, event_name);
  RETURN_IF_MATCH(STAGE_INSTANCE_CREATE, event_name);
  RETURN_IF_MATCH(STAGE_INSTANCE_DELETE, event_name);
  RETURN_IF_MATCH(STAGE_INSTANCE_UPDATE, event_name);
  RETURN_IF_MATCH(TYPING_START, event_name);
  RETURN_IF_MATCH(USER_UPDATE, event_name);
  RETURN_IF_MATCH(VOICE_STATE_UPDATE, event_name);
  RETURN_IF_MATCH(VOICE_SERVER_UPDATE, event_name);
  RETURN_IF_MATCH(WEBHOOKS_UPDATE, event_name);
  return DISCORD_GATEWAY_EVENTS_NONE;
#undef RETURN_IF_MATCH
}

static void
on_guild_role_create(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_role *role = NULL;

  u64_snowflake_t guild_id = 0;
  json_extract(data->start, data->size,
               "(guild_id):s_as_u64"
               "(role):F",
               &guild_id, &discord_role_from_json, &role);

  ON(guild_role_create, guild_id, role);

  discord_role_cleanup(role);
  free(role);
}

static void
on_guild_role_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_role *role = NULL;

  u64_snowflake_t guild_id = 0;
  json_extract(data->start, data->size,
               "(guild_id):s_as_u64"
               "(role):F",
               &guild_id, &discord_role_from_json, &role);

  ON(guild_role_update, guild_id, role);

  discord_role_cleanup(role);
  free(role);
}

static void
on_guild_role_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0, role_id = 0;
  json_extract(data->start, data->size,
               "(guild_id):s_as_u64"
               "(role_id):s_as_u64",
               &guild_id, &role_id);

  ON(guild_role_delete, guild_id, role_id);
}

static void
on_guild_member_add(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_guild_member *member = NULL;
  discord_guild_member_from_json(data->start, data->size, &member);

  u64_snowflake_t guild_id = 0;
  json_extract(data->start, data->size, "(guild_id):s_as_u64", &guild_id);

  ON(guild_member_add, guild_id, member);

  discord_guild_member_cleanup(member);
  free(member);
}

static void
on_guild_member_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_guild_member *member = NULL;
  discord_guild_member_from_json(data->start, data->size, &member);

  u64_snowflake_t guild_id = 0;
  json_extract(data->start, data->size, "(guild_id):s_as_u64", &guild_id);

  ON(guild_member_update, guild_id, member);

  discord_guild_member_cleanup(member);
  free(member);
}

static void
on_guild_member_remove(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0;
  struct discord_user *user = NULL;
  json_extract(data->start, data->size,
               "(guild_id):s_as_u64"
               "(user):F",
               &guild_id, &discord_user_from_json, &user);

  ON(guild_member_remove, guild_id, user);

  discord_user_cleanup(user);
  free(user);
}

static void
on_guild_ban_add(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0;
  struct discord_user *user = NULL;
  json_extract(data->start, data->size,
               "(guild_id):s_as_u64"
               "(user):F",
               &guild_id, &discord_user_from_json, &user);

  ON(guild_ban_add, guild_id, user);

  discord_user_cleanup(user);
  free(user);
}

static void
on_guild_ban_remove(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0;
  struct discord_user *user = NULL;
  json_extract(data->start, data->size,
               "(guild_id):s_as_u64"
               "(user):F",
               &guild_id, &discord_user_from_json, &user);

  ON(guild_ban_remove, guild_id, user);

  discord_user_cleanup(user);
  free(user);
}

static void
on_application_command_create(struct discord_gateway *gw,
                              struct sized_buffer *data)
{
  struct discord_application_command *cmd = NULL;
  discord_application_command_from_json(data->start, data->size, &cmd);

  ON(application_command_create, cmd);

  discord_application_command_cleanup(cmd);
  free(cmd);
}

static void
on_application_command_update(struct discord_gateway *gw,
                              struct sized_buffer *data)
{
  struct discord_application_command *cmd = NULL;
  discord_application_command_from_json(data->start, data->size, &cmd);

  ON(application_command_update, cmd);

  discord_application_command_cleanup(cmd);
  free(cmd);
}

static void
on_application_command_delete(struct discord_gateway *gw,
                              struct sized_buffer *data)
{
  struct discord_application_command *cmd = NULL;
  discord_application_command_from_json(data->start, data->size, &cmd);

  ON(application_command_delete, cmd);

  discord_application_command_cleanup(cmd);
  free(cmd);
}

static void
on_channel_create(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *channel = NULL;
  discord_channel_from_json(data->start, data->size, &channel);

  ON(channel_create, channel);

  discord_channel_cleanup(channel);
  free(channel);
}

static void
on_channel_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *channel = NULL;
  discord_channel_from_json(data->start, data->size, &channel);

  ON(channel_update, channel);

  discord_channel_cleanup(channel);
  free(channel);
}

static void
on_channel_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *channel = NULL;
  discord_channel_from_json(data->start, data->size, &channel);

  ON(channel_delete, channel);

  discord_channel_cleanup(channel);
  free(channel);
}

static void
on_channel_pins_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0, channel_id = 0;
  u64_unix_ms_t last_pin_timestamp = 0;
  json_extract(data->start, data->size,
               "(guild_id):s_as_u64"
               "(channel_id):s_as_u64"
               "(last_pin_timestamp):F",
               &guild_id, &channel_id, &cee_iso8601_to_unix_ms,
               &last_pin_timestamp);

  ON(channel_pins_update, guild_id, channel_id, last_pin_timestamp);
}

static void
on_thread_create(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *thread = NULL;
  discord_channel_from_json(data->start, data->size, &thread);

  ON(thread_create, thread);

  discord_channel_cleanup(thread);
  free(thread);
}

static void
on_thread_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *thread = NULL;
  discord_channel_from_json(data->start, data->size, &thread);

  ON(thread_update, thread);

  discord_channel_cleanup(thread);
  free(thread);
}

static void
on_thread_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *thread = NULL;
  discord_channel_from_json(data->start, data->size, &thread);

  ON(thread_delete, thread);

  discord_channel_cleanup(thread);
  free(thread);
}

static void
on_interaction_create(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_interaction *interaction = NULL;
  discord_interaction_from_json(data->start, data->size, &interaction);

  ON(interaction_create, interaction);

  discord_interaction_cleanup(interaction);
  free(interaction);
}

static void
on_message_create(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_message *msg = NULL;
  discord_message_from_json(data->start, data->size, &msg);

  if (gw->user_cmd->pool && STRNEQ(gw->user_cmd->prefix.start, msg->content,
                                   gw->user_cmd->prefix.size))
  {
    struct discord_gateway_cmd_cbs *cmd = NULL;
    size_t i;

    for (i = 0; i < gw->user_cmd->amt; ++i) {
      /* check if command from channel matches set command */
      if (STRNEQ(gw->user_cmd->pool[i].start,
                 msg->content + gw->user_cmd->prefix.size,
                 gw->user_cmd->pool[i].size))
      {
        cmd = &gw->user_cmd->pool[i];
      }
    }
    if (!cmd && gw->user_cmd->prefix.size) {
      cmd = &gw->user_cmd->on_default;
    }

    if (cmd && cmd->cb) {
      char *tmp = msg->content; /* hold original ptr */
      msg->content = msg->content + gw->user_cmd->prefix.size + cmd->size;
      while (isspace(*msg->content)) { /* skip blank chars */
        ++msg->content;
      }

      (*cmd->cb)(CLIENT(gw), &gw->bot, msg);

      msg->content = tmp; /* retrieve original ptr */
    }

    discord_message_cleanup(msg);
    free(msg);
    return; /* EARLY RETURN */
  }

  if (gw->user_cmd->cbs.sb_on_message_create) /* @todo temporary */
    (*gw->user_cmd->cbs.sb_on_message_create)(CLIENT(gw), &gw->bot,
                                              &gw->sb_bot, msg, data);
  else if (gw->user_cmd->cbs.on_message_create)
    ON(message_create, msg);

  discord_message_cleanup(msg);
  free(msg);
}

static void
on_message_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_message *msg = NULL;
  discord_message_from_json(data->start, data->size, &msg);

  if (gw->user_cmd->cbs.sb_on_message_update)
    (*gw->user_cmd->cbs.sb_on_message_update)(CLIENT(gw), &gw->bot,
                                              &gw->sb_bot, msg, data);
  else if (gw->user_cmd->cbs.on_message_update)
    ON(message_update, msg);

  discord_message_cleanup(msg);
  free(msg);
}

static void
on_message_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t message_id = 0, channel_id = 0, guild_id = 0;
  json_extract(data->start, data->size,
               "(id):s_as_u64"
               "(channel_id):s_as_u64"
               "(guild_id):s_as_u64",
               &message_id, &channel_id, &guild_id);

  ON(message_delete, message_id, channel_id, guild_id);
}

static void
on_message_delete_bulk(struct discord_gateway *gw, struct sized_buffer *data)
{
  const NTL_T(ja_u64) ids = NULL;
  u64_snowflake_t channel_id = 0, guild_id = 0;
  json_extract(data->start, data->size,
               "(ids):F"
               "(channel_id):s_as_u64"
               "(guild_id):s_as_u64",
               &ja_u64_list_from_json, &ids, &channel_id, &guild_id);

  ON(message_delete_bulk, ids, channel_id, guild_id);

  free(ids);
}

static void
on_message_reaction_add(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t user_id = 0, message_id = 0, channel_id = 0, guild_id = 0;
  struct discord_guild_member *member = NULL;
  struct discord_emoji *emoji = NULL;

  json_extract(data->start, data->size,
               "(user_id):s_as_u64"
               "(message_id):s_as_u64"
               "(member):F"
               "(emoji):F"
               "(channel_id):s_as_u64"
               "(guild_id):s_as_u64",
               &user_id, &message_id, &discord_guild_member_from_json, &member,
               &discord_emoji_from_json, &emoji, &channel_id, &guild_id);

  ON(message_reaction_add, user_id, channel_id, message_id, guild_id, member,
     emoji);

  discord_guild_member_cleanup(member);
  free(member);
  discord_emoji_cleanup(emoji);
  free(emoji);
}

static void
on_message_reaction_remove(struct discord_gateway *gw,
                           struct sized_buffer *data)
{
  u64_snowflake_t user_id = 0, message_id = 0, channel_id = 0, guild_id = 0;
  struct discord_emoji *emoji = NULL;

  json_extract(data->start, data->size,
               "(user_id):s_as_u64"
               "(message_id):s_as_u64"
               "(emoji):F"
               "(channel_id):s_as_u64"
               "(guild_id):s_as_u64",
               &user_id, &message_id, &discord_emoji_from_json, &emoji,
               &channel_id, &guild_id);

  ON(message_reaction_remove, user_id, channel_id, message_id, guild_id,
     emoji);

  discord_emoji_cleanup(emoji);
  free(emoji);
}

static void
on_message_reaction_remove_all(struct discord_gateway *gw,
                               struct sized_buffer *data)
{
  u64_snowflake_t channel_id = 0, message_id = 0, guild_id = 0;
  json_extract(data->start, data->size,
               "(channel_id):s_as_u64"
               "(message_id):s_as_u64"
               "(channel_id):s_as_u64",
               &channel_id, &message_id, &guild_id);

  ON(message_reaction_remove_all, channel_id, message_id, guild_id);
}

static void
on_message_reaction_remove_emoji(struct discord_gateway *gw,
                                 struct sized_buffer *data)
{
  u64_snowflake_t channel_id = 0, guild_id = 0, message_id = 0;
  struct discord_emoji *emoji = NULL;
  json_extract(data->start, data->size,
               "(channel_id):s_as_u64"
               "(guild_id):s_as_u64"
               "(message_id):s_as_u64"
               "(emoji):F",
               &channel_id, &guild_id, &message_id, &discord_emoji_from_json,
               &emoji);

  ON(message_reaction_remove_emoji, channel_id, guild_id, message_id, emoji);
}

static void
on_voice_state_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_voice_state *vs = NULL;
  discord_voice_state_from_json(data->start, data->size, &vs);

  if (vs->user_id == gw->bot.id) {
    /* we only care about the voice_state_update of bot */
    _discord_on_voice_state_update(CLIENT(gw), vs);
  }

  if (gw->user_cmd->cbs.on_voice_state_update) ON(voice_state_update, vs);

  discord_voice_state_cleanup(vs);
  free(vs);
}

static void
on_voice_server_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0;
  char token[512], endpoint[1024];
  json_extract(data->start, data->size,
               "(token):s"
               "(guild_id):s_as_u64"
               "(endpoint):s",
               &token, &guild_id, &endpoint);

  /* this happens for everyone */
  _discord_on_voice_server_update(CLIENT(gw), guild_id, token, endpoint);

  if (gw->user_cmd->cbs.on_voice_server_update)
    ON(voice_server_update, token, guild_id, endpoint);
}

static void
on_ready(struct discord_gateway *gw, struct sized_buffer *data)
{
  ON(ready);
}

static void
dispatch_run(void *p_cxt)
{
  struct discord_event_cxt *cxt = p_cxt;
  cxt->tid = pthread_self();

  if (cxt->is_main_thread) {
    (*cxt->on_event)(cxt->p_gw, &cxt->data);

    (*cxt->p_gw->user_cmd->cbs.on_event_raw)(CLIENT(cxt->p_gw), cxt->event,
                                             &cxt->p_gw->sb_bot, &cxt->data);
    return;
  }

  logconf_info(&cxt->p_gw->conf,
               "Thread " ANSICOLOR("starts", ANSI_FG_RED) " to serve %s",
               cxt->event_name);

  (*cxt->on_event)(cxt->p_gw, &cxt->data);

  (*cxt->p_gw->user_cmd->cbs.on_event_raw)(CLIENT(cxt->p_gw), cxt->event,
                                           &cxt->p_gw->sb_bot, &cxt->data);

  logconf_info(&cxt->p_gw->conf,
               "Thread " ANSICOLOR("exits", ANSI_FG_RED) " from serving %s",
               cxt->event_name);

  free(cxt->event_name);
  free(cxt->data.start);
  discord_cleanup(CLIENT(cxt->p_gw));
  free(cxt);
}

static void
on_dispatch(struct discord_gateway *gw)
{
  /* Ratelimit check */
  if ((ws_timestamp(gw->ws) - gw->session.event_tstamp) < 60) {
    ++gw->session.event_count;
    ASSERT_S(gw->session.event_count < 120,
             "Reach event dispatch threshold (120 every 60 seconds)");
  }
  else {
    gw->session.event_tstamp = ws_timestamp(gw->ws);
    gw->session.event_count = 0;
  }

  /**
   * Filter through user event's subscriptions. If there are user-defined
   *      callbacks assigned to the detected event, a new thread will be
   *      created to run it, otherwise we just return.
   */
  void (*on_event)(struct discord_gateway *, struct sized_buffer *) = NULL;
  enum discord_gateway_events event =
    get_dispatch_event(gw->payload->event_name);
  switch (event) {
  case DISCORD_GATEWAY_EVENTS_READY:
    logconf_info(&gw->conf, "Succesfully started a Discord session!");
    json_extract(gw->payload->event_data.start, gw->payload->event_data.size,
                 "(session_id):s", gw->session_id);
    ASSERT_S(!IS_EMPTY_STRING(gw->session_id),
             "Missing session_id from READY event");

    gw->status->is_ready = true;
    gw->reconnect->attempt = 0;
    if (gw->user_cmd->cbs.on_ready) on_event = &on_ready;
    send_heartbeat(gw);
    break;
  case DISCORD_GATEWAY_EVENTS_RESUMED:
    logconf_info(&gw->conf, "Succesfully resumed a Discord session!");
    gw->status->is_ready = true;
    gw->reconnect->attempt = 0;
    /* @todo add callback */
    send_heartbeat(gw);
    break;
  case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_CREATE:
    if (gw->user_cmd->cbs.on_application_command_create)
      on_event = &on_application_command_create;
    break;
  case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_UPDATE:
    if (gw->user_cmd->cbs.on_application_command_update)
      on_event = &on_application_command_update;
    break;
  case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_DELETE:
    if (gw->user_cmd->cbs.on_application_command_delete)
      on_event = &on_application_command_delete;
    break;
  case DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE:
    if (gw->user_cmd->cbs.on_channel_create) on_event = &on_channel_create;
    break;
  case DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE:
    if (gw->user_cmd->cbs.on_channel_update) on_event = &on_channel_update;
    break;
  case DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE:
    if (gw->user_cmd->cbs.on_channel_delete) on_event = &on_channel_delete;
    break;
  case DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE:
    if (gw->user_cmd->cbs.on_channel_pins_update)
      on_event = &on_channel_pins_update;
    break;
  case DISCORD_GATEWAY_EVENTS_THREAD_CREATE:
    if (gw->user_cmd->cbs.on_thread_create) on_event = &on_thread_create;
    break;
  case DISCORD_GATEWAY_EVENTS_THREAD_UPDATE:
    if (gw->user_cmd->cbs.on_thread_update) on_event = &on_thread_update;
    break;
  case DISCORD_GATEWAY_EVENTS_THREAD_DELETE:
    if (gw->user_cmd->cbs.on_thread_delete) on_event = &on_thread_delete;
    break;
  case DISCORD_GATEWAY_EVENTS_THREAD_LIST_SYNC:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_THREAD_MEMBER_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_THREAD_MEMBERS_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_CREATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_DELETE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD:
    if (gw->user_cmd->cbs.on_guild_ban_add) on_event = &on_guild_ban_add;
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE:
    if (gw->user_cmd->cbs.on_guild_ban_remove) on_event = &on_guild_ban_remove;
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_STICKERS_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD:
    if (gw->user_cmd->cbs.on_guild_member_add) on_event = &on_guild_member_add;
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE:
    if (gw->user_cmd->cbs.on_guild_member_update)
      on_event = &on_guild_member_update;
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE:
    if (gw->user_cmd->cbs.on_guild_member_remove)
      on_event = &on_guild_member_remove;
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE:
    if (gw->user_cmd->cbs.on_guild_role_create)
      on_event = &on_guild_role_create;
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE:
    if (gw->user_cmd->cbs.on_guild_role_update)
      on_event = &on_guild_role_update;
    break;
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE:
    if (gw->user_cmd->cbs.on_guild_role_delete)
      on_event = &on_guild_role_delete;
    break;
  case DISCORD_GATEWAY_EVENTS_INTEGRATION_CREATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_INTEGRATION_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_INTEGRATION_DELETE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_INTERACTION_CREATE:
    if (gw->user_cmd->cbs.on_interaction_create)
      on_event = &on_interaction_create;
    break;
  case DISCORD_GATEWAY_EVENTS_INVITE_CREATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_INVITE_DELETE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE:
    if (gw->user_cmd->pool || gw->user_cmd->cbs.sb_on_message_create ||
        gw->user_cmd->cbs.on_message_create)
      on_event = &on_message_create;
    break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE:
    if (gw->user_cmd->cbs.sb_on_message_update ||
        gw->user_cmd->cbs.on_message_update)
      on_event = &on_message_update;
    break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE:
    if (gw->user_cmd->cbs.on_message_delete) on_event = &on_message_delete;
    break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK:
    if (gw->user_cmd->cbs.on_message_delete_bulk)
      on_event = &on_message_delete_bulk;
    break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD:
    if (gw->user_cmd->cbs.on_message_reaction_add)
      on_event = &on_message_reaction_add;
    break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE:
    if (gw->user_cmd->cbs.on_message_reaction_remove)
      on_event = &on_message_reaction_remove;
    break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL:
    if (gw->user_cmd->cbs.on_message_reaction_remove_all)
      on_event = &on_message_reaction_remove_all;
    break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI:
    if (gw->user_cmd->cbs.on_message_reaction_remove_emoji)
      on_event = &on_message_reaction_remove_emoji;
    break;
  case DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_CREATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_DELETE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_TYPING_START:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_USER_UPDATE:
    /** @todo implement */
    break;
  case DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE:
    if (gw->user_cmd->cbs.on_voice_state_update)
      on_event = &on_voice_state_update;
    break;
  case DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE:
    if (gw->user_cmd->cbs.on_voice_server_update)
      on_event = &on_voice_server_update;
    break;
  case DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE:
    /** @todo implement */
    break;
  default:
    logconf_warn(&gw->conf,
                 "Expected unimplemented GATEWAY_DISPATCH event (code: %d)",
                 event);
    break;
  }

  if (!on_event) return; /* user not subscribed to the event */

  enum discord_event_scheduler mode;
  mode = gw->user_cmd->scheduler(CLIENT(gw), &gw->bot,
                                 &gw->payload->event_data, event);
  switch (mode) {
  case DISCORD_EVENT_IGNORE: return;
  case DISCORD_EVENT_MAIN_THREAD: {
    struct discord_event_cxt cxt = { .event_name = gw->payload->event_name,
                                     .p_gw = gw,
                                     .data = gw->payload->event_data,
                                     .event = event,
                                     .on_event = on_event,
                                     .is_main_thread = true };
    dispatch_run(&cxt);
    return;
  }
  case DISCORD_EVENT_WORKER_THREAD: {
    struct discord *client_cpy = discord_clone(CLIENT(gw));
    struct discord_event_cxt *p_cxt = malloc(sizeof *p_cxt);
    *p_cxt = (struct discord_event_cxt){
      .event_name = strdup(gw->payload->event_name),
      .p_gw = &client_cpy->gw,
      .data = { .start = strndup(gw->payload->event_data.start,
                                 gw->payload->event_data.size),
                .size = gw->payload->event_data.size },
      .event = event,
      .on_event = on_event,
      .is_main_thread = false
    };
    /** @todo in case all worker threads are stuck on a infinite loop, this
     *    function will essentially lock the program forever while waiting
     *    on a queue, how can we get around this? Should we? */
    int ret = threadpool_add(gw->tpool, &dispatch_run, p_cxt, 0);
    VASSERT_S(0 == ret, "Couldn't create task (code %d)", ret);
    return;
  }
  default: ERR("Unknown event handling mode (code: %d)", mode);
  }
}

static void
on_invalid_session(struct discord_gateway *gw)
{
  gw->status->is_resumable = strncmp(gw->payload->event_data.start, "false",
                                     gw->payload->event_data.size);
  gw->reconnect->enable = true;

  if (gw->status->is_resumable)
    logconf_info(&gw->conf, "Session is resumable");
  else
    logconf_info(&gw->conf, "Session is not resumable");

  ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, "", 0);
}

static void
on_reconnect(struct discord_gateway *gw)
{
  gw->status->is_resumable = true;
#if 0
  gw->reconnect->enable = true;
#endif
  ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, "", 0);
}

static void
on_heartbeat_ack(struct discord_gateway *gw)
{
  /* get request / response interval in milliseconds */
  ws_lock(gw->ws);
  gw->hbeat->ping_ms = cee_timestamp_ms() - gw->hbeat->tstamp;
  ws_unlock(gw->ws);
  logconf_trace(&gw->conf, "PING: %d ms", gw->hbeat->ping_ms);
}

static void
on_connect_cb(void *p_gw,
              struct websockets *ws,
              struct ws_info *info,
              const char *ws_protocols)
{
  struct discord_gateway *gw = p_gw;
  logconf_info(&gw->conf, "Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_gw,
            struct websockets *ws,
            struct ws_info *info,
            enum ws_close_reason wscode,
            const char *reason,
            size_t len)
{
  struct discord_gateway *gw = p_gw;
  enum discord_gateway_close_opcodes opcode =
    (enum discord_gateway_close_opcodes)wscode;

  logconf_warn(
    &gw->conf,
    ANSICOLOR("CLOSE %s", ANSI_FG_RED) " (code: %4d, %zu bytes): '%.*s'",
    close_opcode_print(opcode), opcode, len, (int)len, reason);

  if (gw->status->shutdown) {
    logconf_warn(&gw->conf, "Gateway was shutdown");
    gw->reconnect->enable = false;
    gw->status->is_resumable = false;
    return;
  }

  switch (opcode) {
  case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR:
  case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE:
  case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE:
  case DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR:
  case DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED:
  case DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED:
  case DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED:
  case DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED:
  case DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED:
  case DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION:
  case DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS:
  case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD:
  case DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS:
    logconf_warn(&gw->conf, "Gateway was shutdown");
    gw->status->is_resumable = false;
    gw->reconnect->enable = false;
    break;
  default: /*websocket/clouflare opcodes */
    if (WS_CLOSE_REASON_NORMAL == (enum ws_close_reason)opcode) {
#if 0
        gw->status->is_resumable = true;
        gw->reconnect->enable = true;
#endif
    }
    else {
      logconf_warn(
        &gw->conf,
        "Gateway will attempt to reconnect and start a new session");
      gw->status->is_resumable = false;
      gw->reconnect->enable = true;
    }
    break;
  case DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT:
    logconf_warn(
      &gw->conf,
      "Gateway will attempt to reconnect and resume current session");
    gw->reconnect->enable = true;
    gw->status->is_resumable = false;
    break;
  }
}

static void
on_text_cb(void *p_gw,
           struct websockets *ws,
           struct ws_info *info,
           const char *text,
           size_t len)
{
  struct discord_gateway *gw = p_gw;

  int seq = 0; /*check value first, then assign */
  json_extract((char *)text, len, "(t):s (s):d (op):d (d):T",
               gw->payload->event_name, &seq, &gw->payload->opcode,
               &gw->payload->event_data);

  if (seq) {
    gw->payload->seq = seq;
  }

  logconf_trace(
    &gw->conf,
    ANSICOLOR("RCV",
              ANSI_FG_BRIGHT_YELLOW) " %s%s%s (%zu bytes) [@@@_%zu_@@@]",
    opcode_print(gw->payload->opcode),
    (*gw->payload->event_name) ? " -> " : "", gw->payload->event_name, len,
    info->loginfo.counter);

  switch (gw->payload->opcode) {
  case DISCORD_GATEWAY_DISPATCH: on_dispatch(gw); break;
  case DISCORD_GATEWAY_INVALID_SESSION: on_invalid_session(gw); break;
  case DISCORD_GATEWAY_RECONNECT: on_reconnect(gw); break;
  case DISCORD_GATEWAY_HELLO: on_hello(gw); break;
  case DISCORD_GATEWAY_HEARTBEAT_ACK: on_heartbeat_ack(gw); break;
  default:
    logconf_error(&gw->conf, "Not yet implemented Gateway Event (code: %d)",
                  gw->payload->opcode);
    break;
  }
}

static void
noop_idle_cb(struct discord *a, const struct discord_user *b)
{
  return;
}
static void
noop_event_raw_cb(struct discord *a,
                  enum discord_gateway_events b,
                  struct sized_buffer *c,
                  struct sized_buffer *d)
{
  return;
}
static enum discord_event_scheduler
noop_scheduler(struct discord *a,
               struct discord_user *b,
               struct sized_buffer *c,
               enum discord_gateway_events d)
{
  return DISCORD_EVENT_MAIN_THREAD;
}

void
discord_gateway_init(struct discord_gateway *gw,
                     struct logconf *conf,
                     struct sized_buffer *token)
{
  struct ws_callbacks cbs;
  struct sized_buffer buf;
  /* pre-initialize worker threads */
  static int nthreads;
  static int queue_size;
  const char *val;

  val = getenv("DISCORD_THREADPOOL_SIZE");
  if (val != NULL) nthreads = atoi(val);
  if (0 == nthreads) nthreads = 1;
  val = getenv("DISCORD_THREADPOOL_QUEUE_SIZE");
  if (val != NULL) queue_size = atoi(val);
  if (0 == queue_size) queue_size = 8;
  gw->tpool = threadpool_create(nthreads, queue_size, 0);

  cbs = (struct ws_callbacks){ .data = gw,
                               .on_connect = &on_connect_cb,
                               .on_text = &on_text_cb,
                               .on_close = &on_close_cb };

  gw->ws = ws_init(&cbs, conf);
  logconf_branch(&gw->conf, conf, "DISCORD_GATEWAY");

  gw->reconnect = malloc(sizeof *gw->reconnect);
  gw->reconnect->enable = true;
  gw->reconnect->threshold = 5; /**< hard limit for now */
  gw->reconnect->attempt = 0;

  gw->status = calloc(1, sizeof *gw->status);

  gw->id = (struct discord_identify){
    .token = strndup(token->start, token->size),
    .properties = malloc(sizeof(struct discord_identify_connection)),
    .presence = calloc(1, sizeof(struct discord_presence_status))
  };
  *gw->id.properties = (struct discord_identify_connection){
    .os = "POSIX", .browser = "orca", .device = "orca"
  };

  /* the bot initial presence */
  discord_set_presence(CLIENT(gw), &(struct discord_presence_status){
                                     .activities = NULL,
                                     .status = "online",
                                     .afk = false,
                                     .since = cee_timestamp_ms() });

  gw->payload = calloc(1, sizeof *gw->payload);
  gw->hbeat = calloc(1, sizeof *gw->hbeat);
  gw->user_cmd = calloc(1, sizeof *gw->user_cmd);

  gw->user_cmd->cbs.on_idle = &noop_idle_cb;
  gw->user_cmd->cbs.on_event_raw = &noop_event_raw_cb;
  gw->user_cmd->scheduler = &noop_scheduler;

  /* fetch and store the bot info */
  if (token->size) {
    discord_get_current_user(CLIENT(gw), &gw->bot);
    sb_discord_get_current_user(CLIENT(gw), &gw->sb_bot);
  }

  /* check for default prefix in config file */
  buf = logconf_get_field(conf, "discord.default_prefix");
  if (buf.size) {
    bool enable_prefix = false;
    json_extract(buf.start, buf.size, "(enable):b", &enable_prefix);

    if (enable_prefix) {
      char *prefix = NULL;
      json_extract(buf.start, buf.size, "(prefix):?s", &prefix);

      gw->user_cmd->prefix =
        (struct sized_buffer){ .start = prefix,
                               .size = prefix ? strlen(prefix) : 0 };
    }
  }
}

void
discord_gateway_cleanup(struct discord_gateway *gw)
{
  /* cleanup WebSockets handle */
  ws_cleanup(gw->ws);
  /* cleanup thread-pool manager */
  threadpool_destroy(gw->tpool, threadpool_graceful);
  /* cleanup bot identification */
  if (gw->id.token) free(gw->id.token);
  free(gw->id.properties);
  free(gw->id.presence);
  /* cleanup connection url */
  if (gw->session.url) free(gw->session.url);
  /* cleanup user bot */
  discord_user_cleanup(&gw->bot);
  if (gw->sb_bot.start) free(gw->sb_bot.start);
  /* cleanup response payload buffer */
  free(gw->payload);
  /* cleanup misc fields */
  free(gw->reconnect);
  free(gw->status);
  free(gw->hbeat);
  /* cleanup user commands */
  if (gw->user_cmd->pool) free(gw->user_cmd->pool);
  if (gw->user_cmd->prefix.start) free(gw->user_cmd->prefix.start);
  free(gw->user_cmd);
}

/*
 * the event loop to serve the events sent by Discord
 */
static ORCAcode
event_loop(struct discord_gateway *gw)
{
  /* get gateway bot info */
  struct sized_buffer json = { 0 };
  if (discord_get_gateway_bot(CLIENT(gw), &json)) {
    logconf_fatal(&gw->conf, "Couldn't retrieve Gateway Bot information");
    return ORCA_DISCORD_BAD_AUTH;
  }

  json_extract(
    json.start, json.size, "(url):?s,(shards):d,(session_start_limit):F",
    &gw->session.url, &gw->session.shards,
    &discord_session_start_limit_from_json,
    &(struct discord_session_start_limit *){ &gw->session.start_limit });
  free(json.start);

  /* build URL that will be used to connect to Discord */
  char url[1024];
  size_t ret = snprintf(
    url, sizeof(url), "%s%s" DISCORD_GATEWAY_URL_SUFFIX, gw->session.url,
    ('/' == gw->session.url[strlen(gw->session.url) - 1]) ? "" : "/");
  ASSERT_S(ret < sizeof(url), "Out of bounds write attempt");

  ws_set_url(gw->ws, url, NULL);

  ws_start(gw->ws);

  if (!gw->session.start_limit.remaining) {
    logconf_fatal(&gw->conf,
                  "Reach sessions threshold (%d),"
                  "Please wait %d seconds and try again",
                  gw->session.start_limit.total,
                  gw->session.start_limit.reset_after / 1000);
    return ORCA_DISCORD_RATELIMIT;
  }

  bool is_running = false;
  while (1) {
    ws_perform(gw->ws, &is_running, 5);
    if (!is_running) break; /* exit event loop */
    if (!gw->status->is_ready) continue; /* wait until on_ready() */

    /* connection is established */

    /*check if timespan since first pulse is greater than
     * minimum heartbeat interval required*/
    if (gw->hbeat->interval_ms < (ws_timestamp(gw->ws) - gw->hbeat->tstamp)) {
      send_heartbeat(gw);
    }
    (*gw->user_cmd->cbs.on_idle)(CLIENT(gw), &gw->bot);
  }
  gw->status->is_ready = false;

  return ORCA_OK;
}

/*
 * Discord's ws is not reliable. This function is responsible for
 * reconnection/resume/exit
 */
ORCAcode
discord_gateway_run(struct discord_gateway *gw)
{
  while (gw->reconnect->attempt < gw->reconnect->threshold) {
    ORCAcode code;

    code = event_loop(gw);

    if (code != ORCA_OK) return code;

    if (!gw->reconnect->enable) {
      logconf_warn(&gw->conf, "Discord Gateway Shutdown");
      return code; /* EARLY RETURN */
    }
    ++gw->reconnect->attempt;
    logconf_info(&gw->conf, "Reconnect attempt #%d", gw->reconnect->attempt);
  }
  /* reset if set */
  gw->status->is_resumable = false;
  gw->reconnect->enable = false;
  gw->reconnect->attempt = 0;
  logconf_fatal(&gw->conf,
                "Could not reconnect to Discord Gateway after %d tries",
                gw->reconnect->threshold);
  return ORCA_DISCORD_CONNECTION;
}

void
discord_gateway_shutdown(struct discord_gateway *gw)
{
  ws_lock(gw->ws);
  gw->reconnect->enable = false;
  gw->status->is_resumable = false;
  gw->status->shutdown = true;
  ws_unlock(gw->ws);
  ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, "", 0);
}

void
discord_gateway_reconnect(struct discord_gateway *gw, bool resume)
{
  ws_lock(gw->ws);
  gw->reconnect->enable = true;
  gw->status->is_resumable = resume;
  ws_unlock(gw->ws);
  ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, "", 0);
}
