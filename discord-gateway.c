#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* isspace() */

#include "discord.h"
#include "discord-internal.h"

#include "orka-utils.h"


#define BASE_GATEWAY_URL "wss://gateway.discord.gg/?v=6&encoding=json"

struct _event_cxt {
  pthread_t tid; // the thread id
  struct sized_buffer data; // a copy of payload data
  struct discord_gateway *p_gw; // the gateway client
  enum discord_gateway_events event;
  void (*on_event)(
    struct discord_gateway *gw, 
    struct sized_buffer *data);
};


static void
discord_session_from_json(char *str, size_t len, void *p_session)
{
  struct discord_session *session = p_session;
  json_extract(str, len,
      "(url):s"
      "(shards):d"
      "(session_start_limit.total):d"
      "(session_start_limit.remaining):d"
      "(session_start_limit.reset_after):d"
      "(session_start_limit.max_concurrency):d",
      session->url,
      &session->shards,
      &session->total,
      &session->remaining,
      &session->reset_after,
      &session->max_concurrency);
}

void
discord_get_gateway(struct discord *client, struct discord_session *p_session)
{
  struct ua_resp_handle resp_handle = \
    { .ok_cb = &discord_session_from_json, .ok_obj = (void*)p_session };

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway");
}

void
discord_get_gateway_bot(struct discord *client, struct discord_session *p_session)
{
  struct ua_resp_handle resp_handle = \
    { .ok_cb = &discord_session_from_json, .ok_obj = (void*)p_session};

  discord_adapter_run( 
    &client->adapter,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway/bot");
}

static char*
opcode_print(enum discord_gateway_opcodes opcode)
{
  char *str = discord_gateway_opcodes_to_string(opcode);
  if (NULL == str) {
    log_warn("Invalid Gateway opcode (code: %d)", opcode);
    str = "Invalid Gateway opcode";
  }
  return str;
}

static char*
close_opcode_print(enum discord_gateway_close_opcodes opcode)
{
  char *str = discord_gateway_close_opcodes_to_string(opcode);
  if (str) return str;
  str = ws_close_opcode_print((enum ws_close_reason)opcode);
  if (str) return str;
  log_warn("Unknown WebSockets close opcode (code: %d)", opcode);
  return "Unknown WebSockets close opcode";
}

static void
send_resume(struct discord_gateway *gw)
{
  char payload[MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):6" // RESUME OPCODE
              "(d):{"
                "(token):s"
                "(session_id):s"
                "(seq):d"
              "}",
              gw->id->token,
              gw->session_id, 
              &gw->payload.seq_number);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  log_info("sending RESUME(%d bytes)", ret);
  ws_send_text(gw->ws, payload, ret);

  gw->is_resumable = false; // reset
}

static void
send_identify(struct discord_gateway *gw)
{
  /* Ratelimit check */
  if ((ws_timestamp(gw->ws) - gw->session.identify_tstamp) < 5) {
    ++gw->session.concurrent;
    VASSERT_S(gw->session.concurrent < gw->session.max_concurrency,
        "Reach identify request threshold (%d every 5 seconds)", gw->session.max_concurrency);
  }
  else {
    gw->session.concurrent = 0;
  }

  char payload[MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):2" // IDENTIFY OPCODE
              "(d):F",
              &discord_gateway_identify_to_json_v, gw->id);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  // contain token (sensitive data), enable _ORKA_DEBUG_STRICT to print it
  log_info("sending IDENTIFY(%d bytes)", ret);
  ws_send_text(gw->ws, payload, ret);

  //get timestamp for this identify
  gw->session.identify_tstamp = ws_timestamp(gw->ws);
}

static void
on_hello(struct discord_gateway *gw)
{
  gw->hbeat.interval_ms = 0;
  gw->hbeat.tstamp = orka_timestamp_ms();

  json_extract(gw->payload.event_data.start, gw->payload.event_data.size,
             "(heartbeat_interval):ld", &gw->hbeat.interval_ms);

  if (gw->is_resumable)
    send_resume(gw);
  else
    send_identify(gw);
}

static enum discord_gateway_events
get_dispatch_event(char event_name[])
{
  if (STREQ("GUILD_CREATE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_CREATE;
  if (STREQ("GUILD_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_UPDATE;
  if (STREQ("GUILD_DELETE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_DELETE;
  if (STREQ("GUILD_ROLE_CREATE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE;
  if (STREQ("GUILD_ROLE_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE;
  if (STREQ("GUILD_ROLE_DELETE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE;
  if (STREQ("GUILD_MEMBER_ADD", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD;
  if (STREQ("GUILD_MEMBER_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE;
  if (STREQ("GUILD_MEMBER_REMOVE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE;
  if (STREQ("GUILD_BAN_ADD", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD;
  if (STREQ("GUILD_BAN_REMOVE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE;
  if (STREQ("GUILD_EMOJIS_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE;
  if (STREQ("GUILD_INTEGRATIONS_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE;
  if (STREQ("CHANNEL_CREATE", event_name)) return DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE;
  if (STREQ("CHANNEL_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE;
  if (STREQ("CHANNEL_DELETE", event_name)) return DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE;
  if (STREQ("CHANNEL_PINS_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE;
  if (STREQ("INVITE_CREATE", event_name)) return DISCORD_GATEWAY_EVENTS_INVITE_CREATE;
  if (STREQ("INVITE_DELETE", event_name)) return DISCORD_GATEWAY_EVENTS_INVITE_DELETE;
  if (STREQ("MESSAGE_CREATE", event_name)) return DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE;
  if (STREQ("MESSAGE_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE;
  if (STREQ("MESSAGE_DELETE", event_name)) return DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE;
  if (STREQ("MESSAGE_DELETE_BULK", event_name)) return DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK;
  if (STREQ("MESSAGE_REACTION_ADD", event_name)) return DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD;
  if (STREQ("MESSAGE_REACTION_REMOVE", event_name)) return DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE;
  if (STREQ("MESSAGE_REACTION_REMOVE_ALL", event_name)) return DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL;
  if (STREQ("MESSAGE_REACTION_REMOVE_EMOJI", event_name)) return DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI;
  if (STREQ("WEBHOOKS_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE;
  if (STREQ("VOICE_STATE_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE;
  if (STREQ("VOICE_SERVER_UPDATE", event_name)) return DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE;
  if (STREQ("TYPING_START", event_name)) return DISCORD_GATEWAY_EVENTS_TYPING_START;
  if (STREQ("READY", event_name)) return DISCORD_GATEWAY_EVENTS_READY;
  if (STREQ("RESUMED", event_name)) return DISCORD_GATEWAY_EVENTS_RESUMED;
  return DISCORD_GATEWAY_EVENTS_NONE;
}

static void
on_guild_role_create(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_guild_role *role = discord_guild_role_alloc();

  u64_snowflake_t guild_id = 0;
  json_extract(data->start, data->size,
    "(guild_id):s_as_u64"
    "(role):F", 
    &guild_id,
    &discord_guild_role_from_json, role);

  (*gw->cbs.on_guild_role_create)(
      gw->p_client, 
      gw->bot, 
      guild_id, 
      role);

  discord_guild_role_free(role);
}

static void
on_guild_role_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_guild_role *role = discord_guild_role_alloc();

  u64_snowflake_t guild_id = 0;
  json_extract(data->start, data->size,
    "(guild_id):s_as_u64"
    "(role):F", 
    &guild_id,
    &discord_guild_role_from_json, role);

  (*gw->cbs.on_guild_role_update)(
      gw->p_client, 
      gw->bot, 
      guild_id, 
      role);

  discord_guild_role_free(role);
}

static void
on_guild_role_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id=0, role_id=0;
  json_extract(data->start, data->size,
    "(guild_id):s_as_u64"
    "(role_id):s_as_u64", 
    &guild_id, &role_id);

  (*gw->cbs.on_guild_role_delete)(
      gw->p_client, 
      gw->bot, 
      guild_id, 
      role_id);
}


static void
on_guild_member_add(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_guild_member *member = discord_guild_member_alloc();
  discord_guild_member_from_json(data->start, data->size, member);

  u64_snowflake_t guild_id = 0;
  json_extract(data->start, data->size, "(guild_id):s_as_u64", &guild_id);

  (*gw->cbs.on_guild_member_add)(
      gw->p_client, 
      gw->bot, 
      guild_id,
      member);

  discord_guild_member_free(member);
}

static void
on_guild_member_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_guild_member *member = discord_guild_member_alloc();
  discord_guild_member_from_json(data->start, data->size, member);

  u64_snowflake_t guild_id = 0;
  json_extract(data->start, data->size, "(guild_id):s_as_u64", &guild_id);

  (*gw->cbs.on_guild_member_update)(
      gw->p_client, 
      gw->bot, 
      guild_id, 
      member);

  discord_guild_member_free(member);
}

static void
on_guild_member_remove(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0;
  struct discord_user *user = discord_user_alloc();
  json_extract(data->start, data->size,
    "(guild_id):s_as_u64"
    "(user):F", 
    &guild_id,
    &discord_user_from_json, user);

  (*gw->cbs.on_guild_member_remove)(
        gw->p_client, 
        gw->bot, 
        guild_id, 
        user);

  discord_user_free(user);
}

static void
on_guild_ban_add(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0;
  struct discord_user *user = discord_user_alloc();
  json_extract(data->start, data->size,
    "(guild_id):s_as_u64"
    "(user):F", 
    &guild_id,
    &discord_user_from_json, user);

  (*gw->cbs.on_guild_ban_add)(
        gw->p_client, 
        gw->bot, 
        guild_id, 
        user);

  discord_user_free(user);
}

static void
on_guild_ban_remove(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id = 0;
  struct discord_user *user = discord_user_alloc();
  json_extract(data->start, data->size,
    "(guild_id):s_as_u64"
    "(user):F", 
    &guild_id,
    &discord_user_from_json, user);

  (*gw->cbs.on_guild_ban_remove)(
        gw->p_client, 
        gw->bot, 
        guild_id, 
        user);

  discord_user_free(user);
}

static void
on_channel_create(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *channel = discord_channel_alloc();
  discord_channel_from_json(data->start, data->size, channel);

  (*gw->cbs.on_channel_create)(
        gw->p_client, 
        gw->bot, 
        channel);

  discord_channel_free(channel);
}

static void
on_channel_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *channel = discord_channel_alloc();
  discord_channel_from_json(data->start, data->size, channel);

  (*gw->cbs.on_channel_update)(
        gw->p_client, 
        gw->bot, 
        channel);

  discord_channel_free(channel);
}

static void
on_channel_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_channel *channel = discord_channel_alloc();
  discord_channel_from_json(data->start, data->size, channel);

  (*gw->cbs.on_channel_delete)(
        gw->p_client, 
        gw->bot, 
        channel);

  discord_channel_free(channel);
}

static void
on_channel_pins_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id=0, channel_id=0;
  u64_unix_ms_t last_pin_timestamp=0;
  json_extract(data->start, data->size,
    "(guild_id):s_as_u64"
    "(channel_id):s_as_u64"
    "(last_pin_timestamp):F",
    &guild_id, 
    &channel_id,
    &orka_iso8601_to_unix_ms, &last_pin_timestamp);

  (*gw->cbs.on_channel_pins_update)(
        gw->p_client, 
        gw->bot, 
        guild_id,
        channel_id,
        last_pin_timestamp);
}

static void
on_message_create(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_message *msg = discord_message_alloc();
  discord_message_from_json(data->start, data->size, msg);

  if (gw->on_cmd) {
    // get prefix offset
    size_t offset = strlen(gw->prefix);

    for (size_t i=0; i < gw->num_cmd; ++i) 
    {
      if (!STRNEQ(gw->prefix, msg->content, offset))
          continue; //prefix doesn't match msg->content

      // check if command from channel matches set command
      if (STRNEQ(gw->on_cmd[i].str, \
            msg->content + offset,  \
            strlen(gw->on_cmd[i].str)))
      {
        char *tmp = msg->content; // hold original ptr
        msg->content = msg->content + offset + strlen(gw->on_cmd[i].str);
        while (isspace(*msg->content)) { // offset blank chars
          ++msg->content;
        }
        (*gw->on_cmd[i].cb)(gw->p_client, gw->bot, msg);

        msg->content = tmp; // retrieve original ptr

        discord_message_free(msg);
        return; /* EARLY RETURN */
      }
    }
  }

  if (gw->cbs.sb_on_message_create) /* @todo temporary */
    (*gw->cbs.sb_on_message_create)(
      gw->p_client, 
      gw->bot, &gw->sb_bot,
      msg, data);
  else if (gw->cbs.on_message_create)
    (*gw->cbs.on_message_create)(gw->p_client, gw->bot, msg);

  discord_message_free(msg);
}

static void
on_message_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_message *msg = discord_message_alloc();
  discord_message_from_json(data->start, data->size, msg);

  if (gw->cbs.sb_on_message_update)
    (*gw->cbs.sb_on_message_update)(
      gw->p_client, 
      gw->bot, &gw->sb_bot,
      msg, data);
  else if (gw->cbs.on_message_update)
    (*gw->cbs.on_message_update)(gw->p_client, gw->bot, msg);

  discord_message_free(msg);
}

static void
on_message_delete(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t message_id=0, channel_id=0, guild_id=0;
  json_extract(data->start, data->size,
    "(id):s_as_u64"
    "(channel_id):s_as_u64"
    "(guild_id):s_as_u64",
    &message_id, 
    &channel_id, 
    &guild_id);

  (*gw->cbs.on_message_delete)(gw->p_client, gw->bot, 
      message_id, 
      channel_id, 
      guild_id);
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
      &ja_u64_list_from_json, &ids,
      &channel_id,
      &guild_id);

  (*gw->cbs.on_message_delete_bulk)(gw->p_client, gw->bot, ids, channel_id, guild_id);

  free(ids);
}

static void
on_message_reaction_add(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t user_id=0, message_id=0, channel_id=0, guild_id=0;
  struct discord_guild_member *member = discord_guild_member_alloc();
  struct discord_emoji *emoji = discord_emoji_alloc();

  json_extract(data->start, data->size,
      "(user_id):s_as_u64"
      "(message_id):s_as_u64"
      "(member):F"
      "(emoji):F"
      "(channel_id):s_as_u64"
      "(guild_id):s_as_u64",
      &user_id,
      &message_id,
      &discord_guild_member_from_json, member,
      &discord_emoji_from_json, emoji,
      &channel_id,
      &guild_id);

  (*gw->cbs.on_message_reaction_add)(gw->p_client, gw->bot, 
      user_id,
      channel_id, 
      message_id, 
      guild_id, 
      member, 
      emoji);

  discord_guild_member_free(member);
  discord_emoji_free(emoji);
}

static void
on_message_reaction_remove(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t user_id=0, message_id=0, channel_id=0, guild_id=0;
  struct discord_emoji *emoji = discord_emoji_alloc();

  json_extract(data->start, data->size,
      "(user_id):s_as_u64"
      "(message_id):s_as_u64"
      "(emoji):F"
      "(channel_id):s_as_u64"
      "(guild_id):s_as_u64",
      &user_id,
      &message_id,
      &discord_emoji_from_json, emoji,
      &channel_id,
      &guild_id);

  (*gw->cbs.on_message_reaction_remove)(gw->p_client, gw->bot, 
      user_id,
      channel_id, 
      message_id, 
      guild_id, 
      emoji);

  discord_emoji_free(emoji);
}

static void
on_message_reaction_remove_all(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t channel_id=0, message_id=0, guild_id=0;
  json_extract(data->start, data->size,
      "(channel_id):s_as_u64"
      "(message_id):s_as_u64"
      "(channel_id):s_as_u64",
      &channel_id,
      &message_id,
      &guild_id);

  (*gw->cbs.on_message_reaction_remove_all)(gw->p_client, gw->bot, 
      channel_id, 
      message_id, 
      guild_id);
}

static void
on_message_reaction_remove_emoji(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t channel_id=0, guild_id=0, message_id=0;
  struct discord_emoji *emoji = discord_emoji_alloc();
  json_extract(data->start, data->size,
      "(channel_id):s_as_u64"
      "(guild_id):s_as_u64"
      "(message_id):s_as_u64"
      "(emoji):F",
      &channel_id,
      &guild_id,
      &message_id,
      &discord_emoji_from_json, emoji);

    (*gw->cbs.on_message_reaction_remove_emoji)(gw->p_client, gw->bot, 
        channel_id, 
        guild_id, 
        message_id,
        emoji);
}

static void
on_voice_state_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  struct discord_voice_state *vs = discord_voice_state_alloc();
  discord_voice_state_from_json(data->start, data->size, vs);

#ifdef DISCORD_VOICE_CONNECTIONS_H
  _discord_on_voice_state_update(gw->p_client, vs);
#endif // DISCORD_VOICE_CONNECTIONS_H

  if (gw->cbs.on_voice_state_update)
    (*gw->cbs.on_voice_state_update)(gw->p_client, gw->bot, vs);

  discord_voice_state_free(vs);
}

static void
on_voice_server_update(struct discord_gateway *gw, struct sized_buffer *data)
{
  u64_snowflake_t guild_id=0;
  char token[512], endpoint[MAX_URL_LEN];
  json_extract(data->start, data->size,
               "(token):s"
               "(guild_id):s_as_u64"
               "(endpoint):s",
               &token, &guild_id, &endpoint);

#ifdef DISCORD_VOICE_CONNECTIONS_H
  _discord_on_voice_server_update(gw->p_client, guild_id, token, endpoint);
#endif // DISCORD_VOICE_CONNECTIONS_H

  if (gw->cbs.on_voice_server_update)
    (*gw->cbs.on_voice_server_update)(gw->p_client, gw->bot,
                                     token,
                                     guild_id,
                                     endpoint);
}

static void
on_ready(struct discord_gateway *gw, struct sized_buffer *data)
{
  json_extract(data->start, data->size, "(session_id):s", gw->session_id);
  ASSERT_S(gw->session_id, "Missing session_id from READY event");

  (*gw->cbs.on_ready)(gw->p_client, gw->bot);
}

static void*
dispatch_run(void *p_cxt)
{
  struct _event_cxt *cxt = p_cxt;
  log_info(ANSICOLOR("pthread_run %u", 31), cxt->tid);

  (*cxt->on_event)(cxt->p_gw, &cxt->data);

  (*cxt->p_gw->cbs.on_event_raw)(
      cxt->p_gw->p_client, 
      cxt->event, 
      &cxt->p_gw->sb_bot, 
      &cxt->data);

  log_info(ANSICOLOR("pthread_exit %u", 31), cxt->tid);
  free(cxt->data.start);
  free(cxt);

  pthread_exit(NULL);
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
  void (*on_event)(struct discord_gateway*, struct sized_buffer*) = NULL;
  enum discord_gateway_events event = get_dispatch_event(gw->payload.event_name);
  switch(event) {
  case DISCORD_GATEWAY_EVENTS_GUILD_CREATE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_UPDATE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_DELETE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE:
      if (gw->cbs.on_guild_role_create)
        on_event = &on_guild_role_create;
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE:
      if (gw->cbs.on_guild_role_update)
        on_event = &on_guild_role_update;
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE:
      if (gw->cbs.on_guild_role_delete)
        on_event = &on_guild_role_delete;
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD:
      if (gw->cbs.on_guild_member_add)
        on_event = &on_guild_member_add;
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE: 
      if (gw->cbs.on_guild_member_update)
        on_event = &on_guild_member_update;
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE:
      if (gw->cbs.on_guild_member_remove)
        on_event = &on_guild_member_remove;
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD:
      if (gw->cbs.on_guild_ban_add)
        on_event = &on_guild_ban_add;
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE:
      if (gw->cbs.on_guild_ban_remove)
        on_event = &on_guild_ban_remove;
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE:
      if (gw->cbs.on_channel_create)
        on_event = &on_channel_create;
      break;
  case DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE:
      if (gw->cbs.on_channel_update)
        on_event = &on_channel_update;
      break;
  case DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE:
      if (gw->cbs.on_channel_delete)
        on_event = &on_channel_delete;
      break;
  case DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE:
      if (gw->cbs.on_channel_pins_update)
        on_event = &on_channel_pins_update;
      break;
  case DISCORD_GATEWAY_EVENTS_INVITE_CREATE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_INVITE_DELETE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE:
      if (gw->on_cmd || gw->cbs.sb_on_message_create || gw->cbs.on_message_create)
        on_event = &on_message_create;
      break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE:
      if (gw->cbs.on_message_update)
        on_event = &on_message_update;
      break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE:
      if (gw->cbs.on_message_delete)
        on_event = &on_message_delete;
      break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK:
      if (gw->cbs.on_message_delete_bulk)
        on_event = &on_message_delete_bulk;
      break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD:
      if (gw->cbs.on_message_reaction_add)
        on_event = &on_message_reaction_add;
      break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE:
      if (gw->cbs.on_message_reaction_remove)
        on_event = &on_message_reaction_remove;
      break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL:
      if (gw->cbs.on_message_reaction_remove_all)
        on_event = &on_message_reaction_remove_all;
      break;
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI:
      if (gw->cbs.on_message_reaction_remove_emoji)
        on_event = &on_message_reaction_remove_emoji;
      break;
  case DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE:
      if (gw->cbs.on_voice_state_update)
        on_event = &on_voice_state_update;
      break;
  case DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE:
      if (gw->cbs.on_voice_server_update)
        on_event = &on_voice_server_update;
      break;
  case DISCORD_GATEWAY_EVENTS_TYPING_START:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE:
      /// @todo implement
      break;
  case DISCORD_GATEWAY_EVENTS_READY:
      log_info("Succesfully started a Discord session!");
      gw->is_ready = true;
      gw->reconnect.attempt = 0;
      if (gw->cbs.on_ready)
        on_event = &on_ready;
      break;
  case DISCORD_GATEWAY_EVENTS_RESUMED:
      log_info("Succesfully resumed a Discord session!");
      gw->is_ready = true;
      gw->reconnect.attempt = 0;
      /// @todo implement
      break;
  default:
      log_warn("Expected unimplemented GATEWAY_DISPATCH event (code: %d)", event);
      break;
  }

  if (!on_event) return; /* user not subscribed to the event */

  // create a new thread to execute callback
  
  struct _event_cxt *cxt = malloc(sizeof(struct _event_cxt));
  asprintf(&cxt->data.start, "%.*s", \
      (int)gw->payload.event_data.size, gw->payload.event_data.start);
  cxt->data.size = gw->payload.event_data.size;
  cxt->p_gw = gw;
  cxt->event = event;
  cxt->on_event = on_event;

  if (pthread_create(&cxt->tid, NULL, &dispatch_run, cxt))
    ERR("Couldn't create thread");
  if (pthread_detach(cxt->tid))
    ERR("Couldn't detach thread");
}

static void
on_invalid_session(struct discord_gateway *gw)
{
  gw->reconnect.enable = true;
  if (true == (gw->is_resumable = strcmp(gw->payload.event_data.start, "false"))) {
    char reason[] = "Attempting to resume session";
    log_warn("%.*s", sizeof(reason), reason);
    ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
  }
  else {
    char reason[] = "Attempting to restart session";
    log_warn("%.*s", sizeof(reason), reason);
    ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
  }
}

static void
on_reconnect(struct discord_gateway *gw)
{
  gw->is_resumable = true;
  gw->reconnect.enable = true;

  const char reason[] = "Attempting to session resume";
  log_warn("%.*s", sizeof(reason), reason);
  ws_close(gw->ws, WS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

static void
on_heartbeat_ack(struct discord_gateway *gw)
{
  // get request / response interval in milliseconds
  pthread_mutex_lock(&gw->lock);
  gw->ping_ms = orka_timestamp_ms() - gw->hbeat.tstamp;
  log_trace("PING: %d ms", gw->ping_ms);
  pthread_mutex_unlock(&gw->lock);
}

static void
on_connect_cb(void *p_gw, const char *ws_protocols) {
  log_info("Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_gw, enum ws_close_reason wscode, const char *reason, size_t len)
{
  struct discord_gateway *gw = p_gw;
  enum discord_gateway_close_opcodes opcode = \
    (enum discord_gateway_close_opcodes)wscode;

  log_warn(ANSICOLOR("%s",31)" (code: %4d) : %zd bytes,"
          "REASON: '%s'", 
          close_opcode_print(opcode), opcode, len,
          reason);
  
  // reset in case its set
  gw->is_ready = false;
  gw->is_resumable = false;
 
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
      gw->reconnect.enable = true;
      break;
  case DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT:
  default: //websocket/clouflare opcodes
      gw->reconnect.enable = false;
      break;
  }

  ws_set_action(gw->ws, WS_ACTION_DISCONNECT);
}

static void
on_text_cb(void *p_gw, const char *text, size_t len) 
{
  struct discord_gateway *gw = p_gw;

  int seq_number; //check value first, then assign
  json_extract((char*)text, len,
              "(t):s (s):d (op):d (d):T",
               gw->payload.event_name,
               &seq_number,
               &gw->payload.opcode,
               &gw->payload.event_data);

  if (seq_number) {
    gw->payload.seq_number = seq_number;
  }

  log_trace(ANSICOLOR("%s", 93)", EVENT:%s, SEQ:%d, DATA:%s%.*s", 
            opcode_print(gw->payload.opcode), 
            *gw->payload.event_name ? gw->payload.event_name : "NULL",
            gw->payload.seq_number,
            gw->payload.event_data.size < 100 ? "" : "\n\t",
            (int)gw->payload.event_data.size, gw->payload.event_data.start);

  switch (gw->payload.opcode) {
  case DISCORD_GATEWAY_DISPATCH:
      on_dispatch(gw);
      break;
  case DISCORD_GATEWAY_INVALID_SESSION:
      on_invalid_session(gw);
      break;
  case DISCORD_GATEWAY_RECONNECT:
      on_reconnect(gw);
      break;
  case DISCORD_GATEWAY_HELLO:
      on_hello(gw);
      break;
  case DISCORD_GATEWAY_HEARTBEAT_ACK:
      on_heartbeat_ack(gw);
      break;
  default:
      log_error("Not yet implemented Gateway Event(code: %d)", gw->payload.opcode);
      break;
  }
}

/* send heartbeat pulse to websockets server in order
 *  to maintain connection alive */
static void
send_heartbeat(struct discord_gateway *gw)
{
  char payload[64];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):1, (d):d", &gw->payload.seq_number);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  log_trace("sending HEARTBEAT(%d bytes)", ret);
  ws_send_text(gw->ws, payload, ret);
}

static void noop_idle_cb(struct discord *a, const struct discord_user *b)
{ return; }
static void noop_event_raw_cb(struct discord *a, enum discord_gateway_events b, struct sized_buffer *c, struct sized_buffer *d)
{ return; }

void
discord_gateway_init(struct discord_gateway *gw, struct logconf *config, struct sized_buffer *token)
{
  struct ws_callbacks cbs = {
    .data = gw,
    .on_connect = &on_connect_cb,
    .on_text = &on_text_cb,
    .on_close = &on_close_cb
  };

  gw->ws = ws_init(&cbs, config);
  ws_set_url(gw->ws, BASE_GATEWAY_URL, NULL);
  logconf_add_id(config, gw->ws, "DISCORD_GATEWAY");

  gw->reconnect.threshold = 5; /** hard limit for now */

  if (STRNEQ("YOUR-BOT-TOKEN", token->start, token->size)) {
    token->start = NULL;
  }
  ASSERT_S(NULL != token->start, "Missing bot token");

  gw->id = discord_gateway_identify_alloc();
  asprintf(&gw->id->token, "%.*s", (int)token->size, token->start);

  gw->id->properties->$os = strdup("POSIX");
  gw->id->properties->$browser = strdup("orca");
  gw->id->properties->$device = strdup("orca");
  gw->id->presence->since = orka_timestamp_ms();

  gw->cbs.on_idle = &noop_idle_cb;
  gw->cbs.on_event_raw = &noop_event_raw_cb;

  gw->bot = discord_user_alloc();

  if (gw->p_client) {
    discord_set_presence(gw->p_client, NULL, "online", false);
    discord_get_current_user(gw->p_client, gw->bot);
    sb_discord_get_current_user(gw->p_client, &gw->sb_bot);
  }

  if (pthread_mutex_init(&gw->lock, NULL))
    ERR("Couldn't initialize pthread mutex");

  struct sized_buffer default_prefix = logconf_get_field(config, "discord.default_prefix");
  if (default_prefix.start) {
    bool enable_prefix=false;
    char prefix[64]={0};
    json_extract(default_prefix.start, default_prefix.size, \
        "(enable):b,(prefix):.*s", &enable_prefix, sizeof(prefix), prefix);
    if (true == enable_prefix) {
      int ret = snprintf(gw->prefix, sizeof(gw->prefix), "%s", prefix);
      ASSERT_S(ret < sizeof(gw->prefix), "Out of bounds write attempt");
    }
  }
}

void
discord_gateway_cleanup(struct discord_gateway *gw)
{
  discord_user_free(gw->bot);
  free(gw->sb_bot.start);
  discord_gateway_identify_free(gw->id);
  ws_cleanup(gw->ws);
  if (gw->on_cmd) {
    free(gw->on_cmd);
  }
  pthread_mutex_destroy(&gw->lock);
}

/* connects to the discord websockets server */
static void
event_loop(struct discord_gateway *gw) 
{
  ws_start(gw->ws);

  //get session info before starting it
  discord_get_gateway_bot(gw->p_client, &gw->session);
  if (!gw->session.remaining) {
    log_fatal("Reach session starts threshold (%d),"
          "Please wait %d seconds and try again", 
          gw->session.total, gw->session.reset_after/1000);
    return; /* EARLY RETURN */
  }

  bool is_running=false;
  while (1) {
    ws_perform(gw->ws, &is_running);

    // wait for activity or timeout
    ws_wait_activity(gw->ws, 1);

    if (!is_running) // exit event loop
      break;
    if (!gw->is_ready) // wait until on_ready()
      continue;
    
    // connection is established

    /*check if timespan since first pulse is greater than
     * minimum heartbeat interval required*/
    if (gw->hbeat.interval_ms < (ws_timestamp(gw->ws) - gw->hbeat.tstamp)) {
      send_heartbeat(gw);

      gw->hbeat.tstamp = ws_timestamp(gw->ws); //update heartbeat timestamp
    }

    (*gw->cbs.on_idle)(gw->p_client, gw->bot);
  }
}

void
discord_gateway_run(struct discord_gateway *gw)
{
  while (gw->reconnect.attempt < gw->reconnect.threshold) {
    event_loop(gw);
    if (!gw->reconnect.enable) {
      log_warn("Discord Gateway Shutdown");
      return; /* EARLY RETURN */
    }
    ++gw->reconnect.attempt;
    log_info("Reconnect attempt #%d", gw->reconnect.attempt);
  }
  log_error("Could not reconnect to Discord Gateway after %d tries", gw->reconnect.threshold);
}

void
discord_gateway_shutdown(struct discord_gateway *gw) {
  gw->reconnect.enable = false;
  ws_set_action(gw->ws, WS_ACTION_DISCONNECT);
}

void
discord_gateway_reconnect(struct discord_gateway *gw) {
  gw->reconnect.enable = true;
  ws_set_action(gw->ws, WS_ACTION_DISCONNECT);
}
