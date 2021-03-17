#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for isspace()
#include <pthread.h>

#include <libdiscord.h>

#include "orka-utils.h"
#include "discord-common.h"


#define BASE_WEBSOCKETS_URL "wss://gateway.discord.gg/?v=6&encoding=json"

namespace discord {
namespace websockets {

namespace identify {

void
dati_init(void *p_identify) 
{
  dati *identify = (dati*)p_identify;
  memset(identify, 0, sizeof(dati));
  identify->presence = status_update::dati_alloc();
}

dati*
dati_alloc()
{
  dati *identify = (dati*)malloc(sizeof(dati));
  dati_init((void*)identify);
  return identify;
}

void
dati_cleanup(void *p_identify) 
{
  dati *identify = (dati*)p_identify;
  status_update::dati_free(identify->presence);

  DS_NOTOP_PUTS("Identify object fields cleared"); 
}

void
dati_free(dati *identify) 
{
  dati_cleanup((void*)identify);
  free(identify);
}

void
dati_from_json(char *str, size_t len, void *p_identify)
{
  dati *identify = (dati*)p_identify;

  json_scanf(str, len,
     "[token]%s"
     "[compress]%b"
     "[large_threshold]%d"
     //"[shard]%F" @todo
     //"[presence]%F" @todo
     "[guild_subscriptions]%b"
     "[intents]%d",
     identify->token,
     &identify->compress,
     &identify->large_threshold,
     &identify->guild_subscriptions,
     &identify->intents);

  DS_NOTOP_PUTS("Identify object loaded with API response");
}

int
dati_to_json(char *str, size_t len, void *p_identify)
{
  dati *identify = (dati*)p_identify;

  void *A[7] = {0};
  A[0] = (void*)identify->token;
  A[1] = (void*)&identify->intents;
  A[2] = (void*)identify->presence;

  int ret = json_inject(str, len,
              "(token):s"
              "(intents):d"
              "(properties):{"
                "($os):|POSIX|"
                "($browser):|orca|"
                "($device):|orca|"
              "}"
              "(presence):F"
              "@arg_switches",
              identify->token, 
              &identify->intents,
              &status_update::dati_to_json, identify->presence,
              A, sizeof(A));

  return ret;
}

namespace status_update {

void
dati_init(void *p_status_update) 
{
  dati *status_update = (dati*)p_status_update;
  memset(status_update, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *status_update = (dati*)malloc(sizeof(dati));
  dati_init((void*)status_update);
  return status_update;
}

void
dati_cleanup(void *p_status_update) 
{
  dati *status_update = (dati*)p_status_update;
  if (status_update->activities)
    ntl_free((NTL_T(void))status_update->activities, &activity::dati_cleanup);

  DS_NOTOP_PUTS("Status Update (Presence) object fields cleared"); 
}

void
dati_free(dati *status_update) 
{
  dati_cleanup((void*)status_update);
  free(status_update);
}

void
dati_from_json(char *str, size_t len, void *p_status_update)
{
  dati *status_update = (dati*)p_status_update;

  json_scanf(str, len,
     "[since]%F"
     "[activities]%F"
     "[status]%s"
     "[afk]%b",
     &orka_iso8601_to_unix_ms, &status_update->since,
     &activity::dati_list_from_json, &status_update->activities,
     status_update->status,
     &status_update->afk);

  DS_NOTOP_PUTS("Status Update (Presence) object loaded with API response");
}

int
dati_to_json(char *str, size_t len, void *p_status_update)
{
  dati *status_update = (dati*)p_status_update;

  void *A[4] = {0};
  if (status_update->since)
    A[0] = (void*)status_update->since;
  if (status_update->activities)
    A[1] = (void*)&status_update->activities;
  if (*status_update->status)
    A[2] = (void*)status_update->status;
  A[3] = (void*)&status_update->afk;

  int ret = json_inject(str, len,
              "(since):F"
              "(activities):F"
              "(status):s"
              "(afk):b"
              "@arg_switches",
              &orka_unix_ms_to_iso8601, &status_update->since,
              &activity::dati_list_to_json, &status_update->activities,
              status_update->status,
              &status_update->afk,
              A, sizeof(A));

  return ret;
}

namespace activity {

void
dati_init(void *p_activity) 
{
  dati *activity = (dati*)p_activity;
  memset(activity, 0, sizeof(dati));
}

dati*
dati_alloc()
{
  dati *activity = (dati*)malloc(sizeof(dati));
  dati_init((void*)activity);
  return activity;
}

void
dati_cleanup(void *p_activity) 
{
  dati *activity = (dati*)p_activity;
  if (activity->details)
    free(activity->details);
  if (activity->state)
    free(activity->state);

  DS_NOTOP_PUTS("Activity object fields cleared"); 
}

void
dati_free(dati *activity) 
{
  dati_cleanup((void*)activity);
  free(activity);
}

void
dati_from_json(char *str, size_t len, void *p_activity)
{
  dati *activity = (dati*)p_activity;

  if (activity->details)
    free(activity->details);
  if (activity->state)
    free(activity->state);

  json_scanf(str, len,
     "[name]%s"
     "[type]%d"
     "[url]%s"
     "[created_at]%F"
     "[application_id]%F"
     "[details]%?s"
     "[state]%?s"
     "[instance]%b",
     activity->name,
     &activity->type,
     activity->url,
     &orka_iso8601_to_unix_ms, &activity->created_at,
     &orka_strtoull, &activity->application_id,
     &activity->details,
     &activity->state,
     &activity->instance);

  DS_NOTOP_PUTS("Activity object loaded with API response");
}

void
dati_list_from_json(char *str, size_t len, void *p_activities)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(dati);
  d.init_elem = &dati_init;
  d.elem_from_buf = &dati_from_json;
  d.ntl_recipient_p = (void***)p_activities;
  orka_str_to_ntl(str, len, &d);
}

size_t
dati_to_json(char *str, size_t len, void *p_activity)
{
  dati *activity = (dati*)p_activity;

  void *A[14] = {0};
  if (*activity->name)
    A[0] = (void*)activity->name;
  A[1] = (void*)&activity->type;
  if (activity->type == types::STREAMING && *activity->url)
    A[2] = (void*)activity->url;
  if (activity->created_at)
    A[3] = (void*)&activity->created_at;
  if (activity->application_id)
    A[4] = (void*)&activity->application_id;
  if (activity->details)
    A[5] = (void*)activity->details;
  if (activity->state)
    A[6] = (void*)activity->state;
  A[7] = (void*)activity->instance;

  size_t ret = json_inject(str, len,
              "(name):s"
              "(type):d"
              "(url):s"
              "(created_at):F"
              "(application_id):F"
              "(details):s"
              "(state):s"
              "(instance):b"
              "@arg_switches",
              activity->name,
              &activity->type,
              activity->url,
              &orka_unix_ms_to_iso8601, &activity->created_at,
              &orka_strtoull, &activity->application_id,
              activity->details,
              activity->state,
              &activity->instance,
              A, sizeof(A));

  return ret;
}

int
dati_list_to_json(char *str, size_t len, void *p_activities)
{
  dati **activities = *(dati ***)p_activities;
  return ntl_to_buf(str, len, (void**)activities, NULL, &dati_to_json);
}

} // namespace activity

} // namespace status_update

} // namespace identify


static char*
opcode_print(int opcode)
{
  using namespace opcodes;
  switch (opcode) {
      CASE_RETURN_STR(DISPATCH);
      CASE_RETURN_STR(HEARTBEAT);
      CASE_RETURN_STR(IDENTIFY);
      CASE_RETURN_STR(PRESENCE_UPDATE);
      CASE_RETURN_STR(VOICE_STATE_UPDATE);
      CASE_RETURN_STR(RESUME);
      CASE_RETURN_STR(RECONNECT);
      CASE_RETURN_STR(REQUEST_GUILD_MEMBERS);
      CASE_RETURN_STR(INVALID_SESSION);
      CASE_RETURN_STR(HELLO);
      CASE_RETURN_STR(HEARTBEAT_ACK);
  default:
      ERR("Invalid Gateway opcode (code: %d)", opcode);
  }

  return NULL;
}

static char*
close_opcode_print(enum close_opcodes gateway_opcode)
{
  switch (gateway_opcode) {
      CASE_RETURN_STR(CLOSE_REASON_UNKNOWN_ERROR);
      CASE_RETURN_STR(CLOSE_REASON_UNKNOWN_OPCODE);
      CASE_RETURN_STR(CLOSE_REASON_DECODE_ERROR);
      CASE_RETURN_STR(CLOSE_REASON_NOT_AUTHENTICATED);
      CASE_RETURN_STR(CLOSE_REASON_AUTHENTICATION_FAILED);
      CASE_RETURN_STR(CLOSE_REASON_ALREADY_AUTHENTICATED);
      CASE_RETURN_STR(CLOSE_REASON_INVALID_SEQUENCE);
      CASE_RETURN_STR(CLOSE_REASON_RATE_LIMITED);
      CASE_RETURN_STR(CLOSE_REASON_SESSION_TIMED_OUT);
      CASE_RETURN_STR(CLOSE_REASON_INVALID_SHARD);
      CASE_RETURN_STR(CLOSE_REASON_SHARDING_REQUIRED);
      CASE_RETURN_STR(CLOSE_REASON_INVALID_API_VERSION);
      CASE_RETURN_STR(CLOSE_REASON_INVALID_INTENTS);
      CASE_RETURN_STR(CLOSE_REASON_DISALLOWED_INTENTS);
  default: {
      enum cws_close_reason cws_opcode = \
            (enum cws_close_reason)gateway_opcode;
      switch (cws_opcode) {
          CASE_RETURN_STR(CWS_CLOSE_REASON_NORMAL);
          CASE_RETURN_STR(CWS_CLOSE_REASON_GOING_AWAY);
          CASE_RETURN_STR(CWS_CLOSE_REASON_PROTOCOL_ERROR);
          CASE_RETURN_STR(CWS_CLOSE_REASON_UNEXPECTED_DATA);
          CASE_RETURN_STR(CWS_CLOSE_REASON_NO_REASON);
          CASE_RETURN_STR(CWS_CLOSE_REASON_ABRUPTLY);
          CASE_RETURN_STR(CWS_CLOSE_REASON_INCONSISTENT_DATA);
          CASE_RETURN_STR(CWS_CLOSE_REASON_POLICY_VIOLATION);
          CASE_RETURN_STR(CWS_CLOSE_REASON_TOO_BIG);
          CASE_RETURN_STR(CWS_CLOSE_REASON_MISSING_EXTENSION);
          CASE_RETURN_STR(CWS_CLOSE_REASON_SERVER_ERROR);
          CASE_RETURN_STR(CWS_CLOSE_REASON_IANA_REGISTRY_START);
          CASE_RETURN_STR(CWS_CLOSE_REASON_IANA_REGISTRY_END);
          CASE_RETURN_STR(CWS_CLOSE_REASON_PRIVATE_START);
          CASE_RETURN_STR(CWS_CLOSE_REASON_PRIVATE_END);
      default:
          ERR("Unknown WebSockets close opcode (code: %d)", cws_opcode);
      }
   }
  }

  return NULL;
}

static void
send_payload(dati *ws, char payload[])
{
  ws_send_text(&ws->common, payload);
}

static void
ws_send_resume(dati *ws)
{
  char payload[MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):6" // RESUME OPCODE
              "(d):{"
                "(token):s"
                "(session_id):s"
                "(seq):d"
              "}",
              ws->identify->token,
              ws->session_id, 
              &ws->payload.seq_number);

  ASSERT_S(ret < (int)sizeof(payload), "Out of bounds write attempt");

  D_NOTOP_PRINT("RESUME PAYLOAD:\n\t%s", payload);
  send_payload(ws, payload);
}

static void
ws_send_identify(dati *ws)
{
  /* Ratelimit check */
  pthread_mutex_lock(&ws->lock);
  if ((ws_timestamp(&ws->common) - ws->session.identify_tstamp) < 5) {
    ++ws->session.concurrent;
    VASSERT_S(ws->session.concurrent < ws->session.max_concurrency,
        "Reach identify request threshold (%d every 5 seconds)", ws->session.max_concurrency);
  }
  else {
    ws->session.concurrent = 0;
  }
  pthread_mutex_unlock(&ws->lock);

  char payload[MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):2" // IDENTIFY OPCODE
              "(d):F",
              &identify::dati_to_json, ws->identify);

  ASSERT_S(ret < (int)sizeof(payload), "Out of bounds write attempt");

  // contain token (sensitive data), enable _ORKA_DEBUG_STRICT to print it
  DS_PRINT("IDENTIFY PAYLOAD:\n\t%s", payload);
  send_payload(ws, payload);

  //get timestamp for this identify
  pthread_mutex_lock(&ws->lock);
  ws->session.identify_tstamp = ws_timestamp(&ws->common);
  pthread_mutex_unlock(&ws->lock);
}

static void
on_hello(void *p_ws, void *curr_iter_data)
{
  dati *ws = (dati*)p_ws;
  struct payload_s *payload = (struct payload_s*)curr_iter_data;

  pthread_mutex_lock(&ws->lock);
  ws->hbeat.interval_ms = 0;
  ws->hbeat.tstamp = orka_timestamp_ms();
  pthread_mutex_unlock(&ws->lock);

  json_scanf(payload->event_data, sizeof(payload->event_data),
             "[heartbeat_interval]%ld", &ws->hbeat.interval_ms);
  ASSERT_S(ws->hbeat.interval_ms > 0, "Invalid heartbeat_ms");

  if (WS_RESUME == ws_get_status(&ws->common))
    ws_send_resume(ws);
  else // WS_FRESH || WS_DISCONNECTED
    ws_send_identify(ws);
}

static void
on_dispatch_message_reaction(
  dati *ws, 
  enum dispatch_code code,
  struct payload_s *payload)
{
  u64_snowflake_t user_id=0, message_id=0, channel_id=0, guild_id=0;
  guild::member::dati *member = guild::member::dati_alloc();
  emoji::dati *emoji = emoji::dati_alloc();
  json_scanf(payload->event_data, sizeof(payload->event_data),
      "[user_id]%F"
      "[message_id]%F"
      "[member]%F"
      "[emoji]%F"
      "[channel_id]%F"
      "[guild_id]%F",
      &orka_strtoull, &user_id,
      &orka_strtoull, &message_id,
      &guild::member::dati_from_json, member,
      &emoji::dati_from_json, emoji,
      &orka_strtoull, &channel_id,
      &orka_strtoull, &guild_id);


  switch (code) {
  case MESSAGE_REACTION_ADD:
      if (ws->cbs.on_reaction.add)
        (*ws->cbs.on_reaction.add)(ws->p_client, ws->me, 
            channel_id, 
            message_id, 
            guild_id, 
            member, 
            emoji);
      break;
  case MESSAGE_REACTION_REMOVE:
      if (ws->cbs.on_reaction.remove)
        (*ws->cbs.on_reaction.remove)(ws->p_client, ws->me, 
            channel_id, 
            message_id, 
            guild_id, 
            emoji);
      break;
  case MESSAGE_REACTION_REMOVE_ALL:
      if (ws->cbs.on_reaction.remove_all)
        (*ws->cbs.on_reaction.remove_all)(ws->p_client, ws->me, 
            channel_id, 
            message_id, 
            guild_id);
      break;
  case MESSAGE_REACTION_REMOVE_EMOJI:
      if (ws->cbs.on_reaction.remove_emoji)
        (*ws->cbs.on_reaction.remove_emoji)(ws->p_client, ws->me, 
            channel_id, 
            message_id, 
            guild_id,
            emoji);
      break;
  default: break; // will never trigger
  }

  guild::member::dati_free(member);
  emoji::dati_free(emoji);
}

static void
on_dispatch_message(
  dati *ws, 
  enum dispatch_code code,
  struct payload_s *payload)
{
  if (MESSAGE_DELETE_BULK == code && ws->cbs.on_message.delete_bulk)
  {
    NTL_T(struct sized_buffer) buf = NULL;
    u64_snowflake_t channel_id = 0, guild_id = 0;
    json_scanf(payload->event_data, sizeof(payload->event_data),
        "[ids]%A"
        "[channel_id]%F"
        "[guild_id]%F",
        &buf,
        &orka_strtoull, &channel_id,
        &orka_strtoull, &guild_id);

    size_t nids = ntl_length((NTL_T(void)) buf);
    u64_snowflake_t *ids = (u64_snowflake_t*)malloc(nids * sizeof(u64_snowflake_t));
    for(size_t i = 0; i < nids; i++) {
      orka_strtoull(buf[i]->start, buf[i]->size, ids + i);
    }

    free(buf);

    (*ws->cbs.on_message.delete_bulk)(ws->p_client, ws->me, nids, ids, channel_id, guild_id);
    free(ids);

    return; /* EARLY RETURN */
  }

  channel::message::dati *msg = channel::message::dati_alloc();
  channel::message::dati_from_json(payload->event_data,
      sizeof(payload->event_data), msg);

  struct sized_buffer sb_msg = {
    .start = payload->event_data,
    .size = strlen(payload->event_data)
  };

  switch (code) {
  case SB_MESSAGE_CREATE: /* @todo this is temporary for wrapping JS */
  case MESSAGE_CREATE:
      if (ws->on_cmd) {
        // prefix offset if available
        size_t offset = IS_EMPTY_STRING(ws->prefix) 
                                ? 0 
                                : strlen(ws->prefix);

        message_cb *cmd_cb = NULL;
        char *cmd_str = NULL;
        for (size_t i=0; i < ws->num_cmd; ++i) 
        {
          if (ws->prefix && !STRNEQ(ws->prefix, msg->content, offset))
              continue; //prefix doesn't match msg->content

          // check if command from channel matches set command
          if (STRNEQ(ws->on_cmd[i].str, 
                msg->content + offset, 
                strlen(ws->on_cmd[i].str)))
          {
            cmd_cb = ws->on_cmd[i].cb;
            cmd_str = ws->on_cmd[i].str;
            break;
          }
        }

        if (cmd_cb && cmd_str) {
          char *tmp = msg->content; // hold original ptr

          msg->content = msg->content + offset + strlen(cmd_str);
          while (isspace(*msg->content)) { // offset blank chars
            ++msg->content;
          }

          (*cmd_cb)(ws->p_client, ws->me, msg);

          msg->content = tmp; // retrieve original ptr
        }
      }
      else if (ws->cbs.on_message.sb_create) /* @todo temporary */
        (*ws->cbs.on_message.sb_create)(
          ws->p_client, 
          ws->me, ws->sb_me,
          msg, sb_msg);
      else if (ws->cbs.on_message.create)
        (*ws->cbs.on_message.create)(ws->p_client, ws->me, msg);

      break;
  case MESSAGE_UPDATE:
      if (ws->cbs.on_message.update)
        (*ws->cbs.on_message.update)(ws->p_client, ws->me, msg);
      break;
  case MESSAGE_DELETE:
      if (ws->cbs.on_message.del)
        (*ws->cbs.on_message.del)(ws->p_client, ws->me, 
            msg->id, 
            msg->channel_id, 
            msg->guild_id);
      break;
  default: break; // will never trigger
  }

  channel::message::dati_free(msg);
}

static void
on_dispatch_guild_member(
  dati *ws, 
  enum dispatch_code code, 
  struct payload_s *payload)
{
  guild::member::dati *member = guild::member::dati_alloc();
  guild::member::dati_from_json(payload->event_data,
      sizeof(payload->event_data), member);

  u64_snowflake_t guild_id = 0;
  json_scanf(
    payload->event_data,
    sizeof(payload->event_data),
    "[guild_id]%F",
    &orka_strtoull, &guild_id);

  switch (code) {
  case GUILD_MEMBER_ADD:
      if (ws->cbs.on_guild_member.add)
        (*ws->cbs.on_guild_member.add)(
            ws->p_client, 
            ws->me, 
            guild_id, 
            member);
      break;
  case GUILD_MEMBER_UPDATE:
      if (ws->cbs.on_guild_member.update)
        (*ws->cbs.on_guild_member.update)(
            ws->p_client, 
            ws->me, 
            guild_id, 
            member);
      break;
  case GUILD_MEMBER_REMOVE:
    if (ws->cbs.on_guild_member.remove)
      (*ws->cbs.on_guild_member.remove)(
            ws->p_client, 
            ws->me, 
            guild_id, 
            member->user);
    break;
  default: break; // will never trigger
  }

  guild::member::dati_free(member);
}

static enum dispatch_code
get_dispatch_code(char event_name[])
{
  STREQ_RETURN_ENUM(READY, event_name);
  STREQ_RETURN_ENUM(RESUMED, event_name);
  STREQ_RETURN_ENUM(MESSAGE_REACTION_ADD, event_name);
  STREQ_RETURN_ENUM(MESSAGE_REACTION_REMOVE_ALL, event_name);
  STREQ_RETURN_ENUM(MESSAGE_REACTION_REMOVE_EMOJI, event_name);
  STREQ_RETURN_ENUM(MESSAGE_CREATE, event_name);
  STREQ_RETURN_ENUM(MESSAGE_UPDATE, event_name);
  STREQ_RETURN_ENUM(MESSAGE_DELETE, event_name);
  STREQ_RETURN_ENUM(MESSAGE_DELETE_BULK, event_name);
  STREQ_RETURN_ENUM(GUILD_MEMBER_ADD, event_name);
  STREQ_RETURN_ENUM(GUILD_MEMBER_UPDATE, event_name);
  STREQ_RETURN_ENUM(GUILD_MEMBER_REMOVE, event_name);
  return UNKNOWN;
}

static void
on_dispatch(void *p_ws, void *curr_iter_data)
{
  dati *ws = (dati*)p_ws;
  struct payload_s *payload = (struct payload_s*)curr_iter_data;

  /* Ratelimit check */
  pthread_mutex_lock(&ws->lock);
  if ((ws_timestamp(&ws->common) - ws->session.event_tstamp) < 60) {
    ++ws->session.event_count;
    ASSERT_S(ws->session.event_count < 120,
        "Reach event dispatch threshold (120 every 60 seconds)");
  }
  else {
    ws->session.event_tstamp = ws_timestamp(&ws->common);
    ws->session.event_count = 0;
  }
  pthread_mutex_unlock(&ws->lock);

  enum dispatch_code code = get_dispatch_code(payload->event_name);
  switch (code) {
  case READY:
      ws_set_status(&ws->common, WS_CONNECTED);
      D_PUTS("Succesfully started a Discord session!");

      json_scanf(payload->event_data, sizeof(payload->event_data),
                 "[session_id]%s", ws->session_id);
      ASSERT_S(ws->session_id, "Missing session_id from READY event");

      if (ws->cbs.on_ready)
        (*ws->cbs.on_ready)(ws->p_client, ws->me);

      break;
  case RESUMED:
      ws_set_status(&ws->common, WS_CONNECTED);
      PUTS("Succesfully resumed a Discord session!");
      break;
  case MESSAGE_REACTION_ADD: 
  case MESSAGE_REACTION_REMOVE:
  case MESSAGE_REACTION_REMOVE_ALL: 
  case MESSAGE_REACTION_REMOVE_EMOJI:
      on_dispatch_message_reaction(ws, code, payload);
      break;
  case MESSAGE_CREATE: 
  case MESSAGE_UPDATE:
  case MESSAGE_DELETE: 
  case MESSAGE_DELETE_BULK:
      on_dispatch_message(ws, code, payload);
      break;
  case GUILD_MEMBER_ADD: 
  case GUILD_MEMBER_UPDATE:
  case GUILD_MEMBER_REMOVE:
      on_dispatch_guild_member(ws, code, payload);
      break;
  default:
      PRINT("Expected not yet implemented GATEWAY DISPATCH event: %s",
          payload->event_name);
      break;
  }
}

static void
on_invalid_session(void *p_ws, void *curr_iter_data)
{
  dati *ws = (dati*)p_ws;
  struct payload_s *payload = (struct payload_s*)curr_iter_data;

  bool is_resumable = strcmp(payload->event_data, "false");
  const char *reason;
  if (is_resumable) {
    ws_set_status(&ws->common, WS_RESUME);
    reason = "Attempting to session resume";
  }
  else {
    ws_set_status(&ws->common, WS_FRESH);
    reason = "Attempting to start a fresh new session";
  }
  PUTS(reason);
  ws_close(&ws->common, CWS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

static void
on_reconnect(void *p_ws, void *curr_iter_data)
{
  dati *ws = (dati*)p_ws;

  ws_set_status(&ws->common, WS_RESUME);

  const char reason[] = "Attempting to session resume";
  PUTS(reason);
  ws_close(&ws->common, CWS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

static void
on_heartbeat_ack(void *p_ws, void *curr_iter_data)
{
  dati *ws = (dati*)p_ws;

  // get request / response interval in milliseconds
  pthread_mutex_lock(&ws->lock);
  ws->ping_ms = orka_timestamp_ms() - ws->hbeat.tstamp;
  D_PRINT("PING: %d ms", ws->ping_ms);
  pthread_mutex_unlock(&ws->lock);
}

static void
on_connect_cb(void *p_ws, const char *ws_protocols) {
  D_PRINT("Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_ws, enum cws_close_reason cwscode, const char *reason, size_t len)
{
  dati *ws = (dati*)p_ws;
  enum close_opcodes opcode = (enum close_opcodes)cwscode;
 
  switch (opcode) {
  case CLOSE_REASON_UNKNOWN_OPCODE:
  case CLOSE_REASON_DECODE_ERROR:
  case CLOSE_REASON_NOT_AUTHENTICATED:
  case CLOSE_REASON_AUTHENTICATION_FAILED:
  case CLOSE_REASON_ALREADY_AUTHENTICATED:
  case CLOSE_REASON_RATE_LIMITED:
  case CLOSE_REASON_SHARDING_REQUIRED:
  case CLOSE_REASON_INVALID_API_VERSION:
  case CLOSE_REASON_INVALID_INTENTS:
  case CLOSE_REASON_DISALLOWED_INTENTS:
      ws_set_status(&ws->common, WS_DISCONNECTED);
      break;
  case CLOSE_REASON_UNKNOWN_ERROR:
  case CLOSE_REASON_INVALID_SEQUENCE:
      ws_set_status(&ws->common, WS_RESUME);
      break;
  case CLOSE_REASON_SESSION_TIMED_OUT:
  default: //websocket/clouflare opcodes
      ws_set_status(&ws->common, WS_FRESH);
      break;
  }

  PRINT("%s (code: %4d) : %zd bytes\n\t"
          "REASON: '%s'", 
          close_opcode_print(opcode), opcode, len,
          reason);
}

static void
on_text_cb(void *p_ws, const char *text, size_t len) {
  D_NOTOP_PUTS("FALLBACK TO ON_TEXT");
}

static int
on_startup_cb(void *p_ws)
{
  dati *ws = (dati*)p_ws;

  //get session info before starting it
  get_bot(ws->p_client, &ws->session);

  if (!ws->session.remaining) {
    PRINT("Reach session starts threshold (%d)\n\t"
          "Please wait %d seconds and try again", 
          ws->session.total, ws->session.reset_after/1000);
    return 0;
  }
  return 1;
}

/* send heartbeat pulse to websockets server in order
 *  to maintain connection alive */
static void
send_heartbeat(dati *ws)
{
  char payload[64];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):1, (d):d", &ws->payload.seq_number);
  ASSERT_S(ret < (int)sizeof(payload), "Out of bounds write attempt");

  D_PRINT("HEARTBEAT_PAYLOAD:\n\t\t%s", payload);
  send_payload(ws, payload);
}

static void
on_iter_end_cb(void *p_ws)
{
  dati *ws = (dati*)p_ws;

  /*check if timespan since first pulse is greater than
   * minimum heartbeat interval required*/
  pthread_mutex_lock(&ws->lock);
  if (ws->hbeat.interval_ms < (ws_timestamp(&ws->common) - ws->hbeat.tstamp)) {
    send_heartbeat(ws);

    ws->hbeat.tstamp = ws_timestamp(&ws->common); //update heartbeat timestamp
  }
  pthread_mutex_unlock(&ws->lock);

  if (ws->cbs.on_idle) {
    (*ws->cbs.on_idle)(ws->p_client, ws->me);
  }
}

static int
on_text_event_cb(void *p_ws, const char *text, size_t len)
{
  dati *ws = (dati*)p_ws;

  D_PRINT("ON_DISPATCH:\t%s\n", text);

  struct payload_s *payloadcpy = \
        (struct payload_s*)calloc(1, sizeof(struct payload_s));

  int tmp_seq_number; //check value first, then assign
  json_scanf((char*)text, len,
              "[t]%s [s]%d [op]%d [d]%S",
               ws->payload.event_name,
               &tmp_seq_number,
               &ws->payload.opcode,
               ws->payload.event_data);

  if (tmp_seq_number) {
    ws->payload.seq_number = tmp_seq_number;
  }

  D_NOTOP_PRINT("OP:\t\t%s\n\t"
                "EVENT NAME:\t%s\n\t"
                "SEQ NUMBER:\t%d\n\t"
                "EVENT DATA:\t%s\n", 
                opcode_print(ws->payload.opcode), 
                *ws->payload.event_name //if event name exists
                   ? ws->payload.event_name //prints event name
                   : "NULL", //otherwise prints NULL
                ws->payload.seq_number,
                ws->payload.event_data);

  memcpy(payloadcpy, &ws->payload, sizeof(struct payload_s));
  ws_set_curr_iter_data(&ws->common, payloadcpy, &free);

  return ws->payload.opcode;
}

void
init(dati *ws, const char token[], const char config_file[])
{
  struct ws_callbacks cbs = {
    .data = (void*)ws,
    .on_startup = &on_startup_cb,
    .on_iter_end = &on_iter_end_cb,
    .on_text_event = &on_text_event_cb,
    .on_connect = &on_connect_cb,
    .on_text = &on_text_cb,
    .on_close = &on_close_cb
  };

  if (config_file) { 
    ws_config_init(
      &ws->common, 
      BASE_WEBSOCKETS_URL, 
      &cbs,
      "DISCORD WEBSOCKETS", 
      config_file);
    token = orka_config_get_field(&ws->common.config, "discord.token");
  }
  else {
    ws_init(&ws->common, BASE_WEBSOCKETS_URL, &cbs);
    orka_config_init(&ws->common.config, "DISCORD WEBSOCKETS", NULL);
  }
  if (!token) ERR("Missing bot token");

  ws_set_refresh_rate(&ws->common, 1);
  ws_set_max_reconnect(&ws->common, 15);
  ws_set_event(&ws->common, opcodes::HELLO, &on_hello);
  ws_set_event(&ws->common, opcodes::DISPATCH, &on_dispatch);
  ws_set_event(&ws->common, opcodes::INVALID_SESSION, &on_invalid_session);
  ws_set_event(&ws->common, opcodes::RECONNECT, &on_reconnect);
  ws_set_event(&ws->common, opcodes::HEARTBEAT_ACK, &on_heartbeat_ack);

  ws->identify = identify::dati_alloc();
  ws->identify->token = strdup(token);

  ws->me = user::dati_alloc();
  user::get_current_user::run(ws->p_client, ws->me);
  user::get_current_user::sb_run(ws->p_client, &ws->sb_me);

  if (pthread_mutex_init(&ws->lock, NULL))
    ERR("Couldn't initialize pthread mutex");
}

void
cleanup(dati *ws)
{
  user::dati_free(ws->me);
  identify::dati_free(ws->identify);
  ws_cleanup(&ws->common);
  pthread_mutex_destroy(&ws->lock);
}

namespace session {

void
dati_from_json(char *str, size_t len, void *p_session)
{
  dati *session = (dati*)p_session;

  struct sized_buffer buf = {NULL, 0};

  json_scanf(str, len,
     "[url]%s"
     "[shards]%d"
     "[session_start_limit]%T",
     session->url,
     &session->shards,
     &buf);

  json_scanf(buf.start, buf.size,
      "[total]%d"
      "[remaining]%d"
      "[reset_after]%d"
      "[max_concurrency]%d",
      &session->total,
      &session->remaining,
      &session->reset_after,
      &session->max_concurrency);

  DS_NOTOP_PUTS("Session Start Limit object loaded with API response"); 
}

void
get(client *client, dati *p_session)
{
  struct resp_handle resp_handle = \
    { .ok_cb = &dati_from_json, .ok_obj = (void*)p_session };

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway");
}

void
get_bot(client *client, dati *p_session)
{
  struct resp_handle resp_handle = \
    { .ok_cb = &dati_from_json, .ok_obj = (void*)p_session};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway/bot");
}

} // namespace session

/* connects to the discord websockets server */
void
run(dati *ws) {
  ws_run(&ws->common);
}

} // namespace websockets
} // namespace discord
