#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for isspace()

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
    ntl_free((void**)status_update->activities, &activity::dati_cleanup);

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
ws_opcode_print(int opcode)
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
ws_close_opcode_print(enum close_opcodes gateway_opcode)
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
ws_send_payload(dati *ws, char payload[])
{
  (*ws->common.config.json_cb)(
    false, 
    0, "SEND", 
    &ws->common.config, 
    BASE_WEBSOCKETS_URL, 
    payload);

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
  ws_send_payload(ws, payload);
}

static void
ws_send_identify(dati *ws)
{
  /* Ratelimit check */
  if ( (ws->common.now_tstamp - ws->session.identify_tstamp) < 5 ) {
    ++ws->session.concurrent;
    VASSERT_S(ws->session.concurrent < ws->session.max_concurrency,
        "Reach identify request threshold (%d every 5 seconds)", ws->session.max_concurrency);
  }
  else {
    ws->session.concurrent = 0;
  }

  char payload[MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):2" // IDENTIFY OPCODE
              "(d):F",
              &identify::dati_to_json, ws->identify);

  ASSERT_S(ret < (int)sizeof(payload), "Out of bounds write attempt");

  // contain token (sensitive data), enable _ORKA_DEBUG_STRICT to print it
  DS_PRINT("IDENTIFY PAYLOAD:\n\t%s", payload);
  ws_send_payload(ws, payload);

  //get timestamp for this identify
  ws->session.identify_tstamp = ws->common.now_tstamp;
}

static void
on_hello(dati *ws)
{
  ws->hbeat.interval_ms = 0;
  ws->hbeat.tstamp = orka_timestamp_ms();

  json_scanf(ws->payload.event_data, sizeof(ws->payload.event_data),
             "[heartbeat_interval]%ld", &ws->hbeat.interval_ms);
  ASSERT_S(ws->hbeat.interval_ms > 0, "Invalid heartbeat_ms");

  if (WS_RESUME == ws->common.status)
    ws_send_resume(ws);
  else // WS_FRESH || WS_DISCONNECTED
    ws_send_identify(ws);
}

static void
on_dispatch_reaction(dati *ws, int offset)
{
  uint64_t user_id=0, message_id=0, channel_id=0, guild_id=0;
  guild::member::dati *member = guild::member::dati_alloc();
  emoji::dati *emoji = emoji::dati_alloc();
  json_scanf(ws->payload.event_data, sizeof(ws->payload.event_data),
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


  if (STREQ("ADD", ws->payload.event_name + offset)) {
    if (ws->cbs.on_reaction.add)
      (*ws->cbs.on_reaction.add)(ws->p_client, ws->me, 
          channel_id, 
          message_id, 
          guild_id, 
          member, 
          emoji);
  }
  else if (STREQ("REMOVE", ws->payload.event_name + offset)) {
    if (ws->cbs.on_reaction.remove)
      (*ws->cbs.on_reaction.remove)(ws->p_client, ws->me, 
          channel_id, 
          message_id, 
          guild_id, 
          emoji);
  }
  else if (STREQ("REMOVE_ALL", ws->payload.event_name + offset)) {
    if (ws->cbs.on_reaction.remove_all)
      (*ws->cbs.on_reaction.remove_all)(ws->p_client, ws->me, 
          channel_id, 
          message_id, 
          guild_id);
  }
  else if (STREQ("REMOVE_EMOJI", ws->payload.event_name + offset)) {
    if (ws->cbs.on_reaction.remove_emoji)
      (*ws->cbs.on_reaction.remove_emoji)(ws->p_client, ws->me, 
          channel_id, 
          message_id, 
          guild_id,
          emoji);
  }

  guild::member::dati_free(member);
  emoji::dati_free(emoji);
}

static void
on_dispatch_message(dati *ws, int offset)
{
  if (STREQ("DELETE_BULK", ws->payload.event_name + offset)) 
  {
    if (ws->cbs.on_message.delete_bulk)
    {
      struct sized_buffer **buf = NULL;
      uint64_t channel_id = 0, guild_id = 0;
      json_scanf(ws->payload.event_data, sizeof(ws->payload.event_data),
          "[ids]%A"
          "[channel_id]%F"
          "[guild_id]%F",
          &buf,
          &orka_strtoull, &channel_id,
          &orka_strtoull, &guild_id);

      size_t nids = ntl_length((void**) buf);
      uint64_t *ids = (uint64_t*)malloc(nids * sizeof(uint64_t));
      ASSERT_S(NULL != ids, "Out of memory");

      for(size_t i = 0; i < nids; i++) {
        orka_strtoull(buf[i]->start, buf[i]->size, ids + i);
      }

      free(buf);

      (*ws->cbs.on_message.delete_bulk)(ws->p_client, ws->me, nids, ids, channel_id, guild_id);
      free(ids);
    }

    return; /* EARLY RETURN */
  }

  channel::message::dati *message = channel::message::dati_alloc();
  ASSERT_S(NULL != message, "Out of memory");

  channel::message::dati_from_json(ws->payload.event_data,
      sizeof(ws->payload.event_data), message);

  if (STREQ("CREATE", ws->payload.event_name + offset)) {
    if (ws->on_cmd) {
      size_t prefix_offset = IS_EMPTY_STRING(ws->prefix) ? 0 : strlen(ws->prefix);

      message_cb *cmd_cb = NULL;
      char *cmd_str = NULL;
      for (size_t i=0; i < ws->num_cmd; ++i) 
      {
        if (ws->prefix && !STRNEQ(ws->prefix, message->content, prefix_offset))
            continue; //prefix doesn't match message->content

        if ( STRNEQ(ws->on_cmd[i].str, 
                message->content + prefix_offset, 
                strlen(ws->on_cmd[i].str)) )
        {
          cmd_cb = ws->on_cmd[i].cb;
          cmd_str = ws->on_cmd[i].str;
          break;
        }
      }

      if (cmd_cb && cmd_str) {
        char *tmp = message->content; // hold original ptr

        message->content = message->content + prefix_offset + strlen(cmd_str); //offsets from prefix+command
        while (isspace(*message->content)) { // offsets from blank characters
          ++message->content;
        }

        (*cmd_cb)(ws->p_client, ws->me, message);

        message->content = tmp; // retrieve original ptr
      }
    }
    else if (ws->cbs.on_message.create)
      (*ws->cbs.on_message.create)(ws->p_client, ws->me, message);
  }
  else if (STREQ("UPDATE", ws->payload.event_name + offset)) {
    if (ws->cbs.on_message.update)
      (*ws->cbs.on_message.update)(ws->p_client, ws->me, message);
  }
  else if (STREQ("DELETE", ws->payload.event_name + offset)) {
    if (ws->cbs.on_message.del)
      (*ws->cbs.on_message.del)(ws->p_client, ws->me, 
          message->id, 
          message->channel_id, 
          message->guild_id);
  }

  channel::message::dati_free(message);
}

static void
on_dispatch_guild_member(dati *ws, int offset)
{
  guild::member::dati *member = guild::member::dati_alloc();
  ASSERT_S(NULL != member, "Out of memory");

  guild::member::dati_from_json(ws->payload.event_data,
      sizeof(ws->payload.event_data), member);
  uint64_t guild_id = 0;
  json_scanf(
      ws->payload.event_data,
      sizeof(ws->payload.event_data),
      "[guild_id]%F",
      &orka_strtoull, &guild_id);

  if (STREQ("ADD", ws->payload.event_name + offset)) {
    if (ws->cbs.on_guild_member.add)
      (*ws->cbs.on_guild_member.add)(ws->p_client, ws->me, guild_id, member);
  }
  else if (STREQ("UPDATE", ws->payload.event_name + offset)) {
    if (ws->cbs.on_guild_member.update)
      (*ws->cbs.on_guild_member.update)(ws->p_client, ws->me, guild_id, member);
  }
  else if (STREQ("REMOVE", ws->payload.event_name + offset)) {
    if (ws->cbs.on_guild_member.remove)
      (*ws->cbs.on_guild_member.remove)(ws->p_client, ws->me, guild_id, member->user);
  }

  guild::member::dati_free(member);
}

static void
on_dispatch(dati *ws)
{
  user::dati_from_json(ws->payload.event_data,
      sizeof(ws->payload.event_data), ws->me);

  /* Ratelimit check */
  if ( (ws->common.now_tstamp - ws->session.event_tstamp) < 60 ) {
    ++ws->session.event_count;
    ASSERT_S(ws->session.event_count < 120,
        "Reach event dispatch threshold (120 every 60 seconds)");
  }
  else {
    ws->session.event_tstamp = ws->common.now_tstamp;
    ws->session.event_count = 0;
  }

  if (STREQ("READY", ws->payload.event_name))
  {
    ws->common.status = WS_CONNECTED;
    ws->reconnect_attempts = 0; // resets
    D_PUTS("Succesfully started a Discord session!");

    json_scanf(ws->payload.event_data, sizeof(ws->payload.event_data),
               "[session_id]%s", ws->session_id);
    ASSERT_S(ws->session_id, "Couldn't fetch session_id from READY event");

    if (ws->cbs.on_ready)
      (*ws->cbs.on_ready)(ws->p_client, ws->me);

    return;
  }
  if (STREQ("RESUMED", ws->payload.event_name))
  {
    ws->common.status = WS_CONNECTED;
    ws->reconnect_attempts = 0; // resets
    PUTS("Succesfully resumed a Discord session!");

    return;
  }
  if (STRNEQ("MESSAGE_REACTION_", ws->payload.event_name, 17)) {
    on_dispatch_reaction(ws, 17);
    return;
  }
  if (STRNEQ("MESSAGE_", ws->payload.event_name, 8)) {
    on_dispatch_message(ws, 8);
    return;
  }
  if (STRNEQ("GUILD_MEMBER_", ws->payload.event_name, 13)) {
    on_dispatch_guild_member(ws, 13);
    return;
  }

  PRINT("Expected not yet implemented GATEWAY DISPATCH event: %s",
      ws->payload.event_name);
}

static void
on_invalid_session(dati *ws)
{
  const char *reason;

  bool is_resumable = strcmp(ws->payload.event_data, "false");
  if (is_resumable) {
    ws->common.status = WS_RESUME;
    reason = "Attempting to session resume";
  }
  else {
    ws->common.status = WS_FRESH;
    reason = "Attempting to start a fresh new session";
  }
  PUTS(reason);
  ws_close(&ws->common, CWS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

static void
on_reconnect(dati *ws)
{
  ws->common.status = WS_RESUME;

  const char reason[] = "Attempting to session resume";
  PUTS(reason);
  ws_close(&ws->common, CWS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

static void
ws_on_connect_cb(void *p_ws, const char *ws_protocols)
{
  D_PRINT("Connected, WS-Protocols: '%s'", ws_protocols);

  (void)p_ws;
}

static void
ws_on_close_cb(void *p_ws, enum cws_close_reason cwscode, const char *reason, size_t len)
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
      ws->common.status = WS_DISCONNECTED;
      break;
  case CLOSE_REASON_UNKNOWN_ERROR:
  case CLOSE_REASON_INVALID_SEQUENCE:
      ws->common.status = WS_RESUME;
      break;
  case CLOSE_REASON_SESSION_TIMED_OUT:
  default: //websocket/clouflare opcodes
      ws->common.status = WS_FRESH;
      break;
  }

  PRINT("%s (code: %4d) : %zd bytes\n\t"
          "REASON: '%s'", 
          ws_close_opcode_print(opcode), opcode, len,
          reason);
}

static void
ws_on_text_cb(void *p_ws, const char *text, size_t len)
{
  dati *ws = (dati*)p_ws;
  
  (*ws->common.config.json_cb)(
    true, 
    ws->payload.opcode, ws_opcode_print(ws->payload.opcode),
    &ws->common.config, 
    BASE_WEBSOCKETS_URL, 
    (char*)text);

  D_PRINT("ON_TEXT:\t%s\n", text);

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
                ws_opcode_print(ws->payload.opcode), 
                *ws->payload.event_name //if event name exists
                   ? ws->payload.event_name //prints event name
                   : "NULL", //otherwise prints NULL
                ws->payload.seq_number,
                ws->payload.event_data);

  switch (ws->payload.opcode){
  case opcodes::HELLO:
      on_hello(ws);
      break;
  case opcodes::DISPATCH:
      on_dispatch(ws);
      break;
  case opcodes::INVALID_SESSION:
      on_invalid_session(ws);
      break;
  case opcodes::RECONNECT:
      on_reconnect(ws);
      break;
  case opcodes::HEARTBEAT_ACK:
      // get request / response interval in milliseconds
      ws->ping_ms = orka_timestamp_ms() - ws->hbeat.tstamp;
      D_PRINT("PING: %d ms", ws->ping_ms);
      break;
  default:
      ERR("Not yet implemented WebSockets opcode (code: %d)", ws->payload.opcode);
  }

  (void)len;
}

static int
ws_on_start_cb(void *p_ws)
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
ws_send_heartbeat(dati *ws)
{
  char payload[64];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):1, (d):d", &ws->payload.seq_number);
  ASSERT_S(ret < (int)sizeof(payload), "Out of bounds write attempt");

  D_PRINT("HEARTBEAT_PAYLOAD:\n\t\t%s", payload);
  ws_send_payload(ws, payload);
}


static void
ws_on_idle_cb(void *p_ws)
{
  dati *ws = (dati*)p_ws;

  /*check if timespan since first pulse is greater than
   * minimum heartbeat interval required*/
  if (ws->hbeat.interval_ms < (ws->common.now_tstamp - ws->hbeat.tstamp)) {
    ws_send_heartbeat(ws);

    ws->hbeat.tstamp = ws->common.now_tstamp; //update heartbeat timestamp
  }

  if (ws->cbs.on_idle) {
    (*ws->cbs.on_idle)(ws->p_client, ws->me);
  }
}

void
init(dati *ws, const char token[], const char config_file[])
{
  struct ws_callbacks cbs = {
    .data = (void*)ws,
    .on_connect = &ws_on_connect_cb,
    .on_text = &ws_on_text_cb,
    .on_close = &ws_on_close_cb,
    .on_idle = &ws_on_idle_cb,
    .on_start = &ws_on_start_cb
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

  ws->identify = identify::dati_alloc();
  ws->identify->token = strdup(token);

  ws->me = user::dati_alloc();
  user::me::get(ws->p_client, ws->me);
}

void
cleanup(dati *ws)
{
  user::dati_free(ws->me);
  identify::dati_free(ws->identify);
  ws_cleanup(&ws->common);
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
  struct resp_handle resp_handle = {&dati_from_json, (void*)p_session};

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
  struct resp_handle resp_handle = {&dati_from_json, (void*)p_session};

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
run(dati *ws)
{
  ws_run(&ws->common);

  if (WS_DISCONNECTED != ws->common.status) {
    PRINT("Failed all reconnect attempts (%d)", ws->reconnect_attempts);
    ws->common.status = WS_DISCONNECTED;
  }
}

} // namespace websockets
} // namespace discord
