#include <stdio.h>
#include <stdlib.h>

#include <libdiscord.h>
#include "curl-websocket.h"

#include "orka-utils.h"


#define BASE_WEBSOCKETS_URL "wss://gateway.discord.gg/?v=6&encoding=json"

namespace discord {
namespace websockets {

static char*
ws_opcode_print(int opcode)
{
  switch (opcode) {
      CASE_RETURN_STR(opcodes::DISPATCH);
      CASE_RETURN_STR(opcodes::HEARTBEAT);
      CASE_RETURN_STR(opcodes::IDENTIFY);
      CASE_RETURN_STR(opcodes::PRESENCE_UPDATE);
      CASE_RETURN_STR(opcodes::VOICE_STATE_UPDATE);
      CASE_RETURN_STR(opcodes::RESUME);
      CASE_RETURN_STR(opcodes::RECONNECT);
      CASE_RETURN_STR(opcodes::REQUEST_GUILD_MEMBERS);
      CASE_RETURN_STR(opcodes::INVALID_SESSION);
      CASE_RETURN_STR(opcodes::HELLO);
      CASE_RETURN_STR(opcodes::HEARTBEAT_ACK);
  default:
      ERR("Invalid Gateway opcode (code: %d)", opcode);
  }
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
}

static void
ws_send_payload(websockets::dati *ws, char payload[])
{
  json_dump("SEND PAYLOAD", &ws->p_client->settings, payload);

  bool ret = cws_send_text(ws->ehandle, payload);
  ASSERT_S(true == ret, "Couldn't send payload");
}

static void
ws_send_resume(websockets::dati *ws)
{
  char fmt_payload[] = \
    "{\"op\":6,\"d\":{\"token\":\"%s\",\"session_id\":\"%s\",\"seq\":%d}}";
  char payload[MAX_PAYLOAD_LEN];
  int ret = snprintf(payload, MAX_PAYLOAD_LEN, fmt_payload,
      ws->p_client->settings.token, ws->session_id, ws->payload.seq_number);
  ASSERT_S(ret < (int)sizeof(payload), "Out of bounds write attempt");

  D_NOTOP_PRINT("RESUME PAYLOAD:\n\t%s", payload);
  ws_send_payload(ws, payload);
}

static void
ws_send_identify(websockets::dati *ws)
{
  /* Ratelimit check */
  if ( (ws->now_tstamp - ws->session.identify_tstamp) < 5 ) {
    if (++ws->session.concurrent >= ws->session.max_concurrency)
      ERR("Reach identify requests threshold (%d every 5 seconds)",
                ws->session.max_concurrency);
  }
  else {
    ws->session.concurrent = 0;
  }

  D_PRINT("IDENTIFY PAYLOAD:\n\t%s", ws->identify);
  ws_send_payload(ws, ws->identify);

  //get timestamp for this identify
  ws->session.identify_tstamp = ws->now_tstamp;
}

static void
on_hello(websockets::dati *ws)
{
  ws->hbeat.interval_ms = 0;
  ws->hbeat.tstamp = orka_timestamp_ms();

  json_scanf(ws->payload.event_data, sizeof(ws->payload.event_data),
             "[heartbeat_interval]%ld", &ws->hbeat.interval_ms);
  ASSERT_S(ws->hbeat.interval_ms > 0, "Invalid heartbeat_ms");

  if (status::RESUME == ws->status)
    ws_send_resume(ws);
  else // status::FRESH || status::DISCONNECTED
    ws_send_identify(ws);
}

static void
on_dispatch_message(websockets::dati *ws, int offset)
{
  if (STREQ("DELETE_BULK", ws->payload.event_name + offset)) {
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
      uint64_t *ids = (uint64_t*) malloc(nids * sizeof(uint64_t));
      ASSERT_S(NULL != ids, "Out of memory");

      size_t i;
      for(i = 0; i < nids; i++)
      {
        orka_strtoull(buf[i]->start, buf[i]->size, ids + i);
      }

      free(buf);

      (*ws->cbs.on_message.delete_bulk)(ws->p_client, ws->me, nids, ids, channel_id, guild_id);
      free(ids);
    }
    return;
  }

  channel::message::dati *message = channel::message::init();
  ASSERT_S(NULL != message, "Out of memory");

  channel::message::json_load(ws->payload.event_data,
      sizeof(ws->payload.event_data), (void*)message);

  if (STREQ("CREATE", ws->payload.event_name + offset)) {
    if (ws->cbs.on_message.create)
      (*ws->cbs.on_message.create)(ws->p_client, ws->me, message);
  }
  else if (STREQ("UPDATE", ws->payload.event_name + offset)) {
    if (ws->cbs.on_message.update)
      (*ws->cbs.on_message.update)(ws->p_client, ws->me, message);
  }
  else if (STREQ("DELETE", ws->payload.event_name + offset)) {
    if (ws->cbs.on_message.del)
      (*ws->cbs.on_message.del)(ws->p_client, ws->me, message->id, message->channel_id, message->guild_id);
  }

  channel::message::cleanup(message);
}

static void
on_dispatch_guild_member(websockets::dati *ws, int offset)
{
  guild::member::dati *member = guild::member::init();
  ASSERT_S(NULL != member, "Out of memory");

  guild::member::json_load(ws->payload.event_data,
      sizeof(ws->payload.event_data), (void*)member);
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

  guild::member::cleanup(member);
}

static void
on_dispatch(websockets::dati *ws)
{
  user::json_load(ws->payload.event_data,
      sizeof(ws->payload.event_data), (void*)ws->me);

  /* Ratelimit check */
  if ( (ws->now_tstamp - ws->session.event_tstamp) < 60 ) {
    if (++ws->session.event_count >= 120)
      ERR("Reach event dispatch threshold (120 every 60 seconds)");
  }
  else {
    ws->session.event_tstamp = ws->now_tstamp;
    ws->session.event_count = 0;
  }

  if (STREQ("READY", ws->payload.event_name))
  {
    ws->status = status::CONNECTED;
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
    ws->status = status::CONNECTED;
    ws->reconnect_attempts = 0; // resets
    PUTS("Succesfully resumed a Discord session!");

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
on_invalid_session(websockets::dati *ws)
{
  const char *reason;

  bool is_resumable = strcmp(ws->payload.event_data, "false");
  if (is_resumable) {
    ws->status = status::RESUME;
    reason = "Attempting to session resume";
  }
  else {
    ws->status = status::FRESH;
    reason = "Attempting to start a fresh new session";
  }
  PUTS(reason);
  cws_close(ws->ehandle, CWS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

static void
on_reconnect(websockets::dati *ws)
{
  ws->status = status::RESUME;

  const char reason[] = "Attempting to session resume";
  PUTS(reason);
  cws_close(ws->ehandle, CWS_CLOSE_REASON_NORMAL, reason, sizeof(reason));
}

static void
ws_on_connect_cb(void *p_ws, CURL *ehandle, const char *ws_protocols)
{
  D_PRINT("Connected, WS-Protocols: '%s'", ws_protocols);

  (void)p_ws;
  (void)ehandle;
}

static void
ws_on_close_cb(void *p_ws, CURL *ehandle, enum cws_close_reason cwscode, const char *reason, size_t len)
{
  websockets::dati *ws = (websockets::dati*)p_ws;
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
      ws->status = status::DISCONNECTED;
      break;
  case CLOSE_REASON_UNKNOWN_ERROR:
  case CLOSE_REASON_INVALID_SEQUENCE:
      ws->status = status::RESUME;
      break;
  case CLOSE_REASON_SESSION_TIMED_OUT:
  default: //websocket/clouflare opcodes
      ws->status = status::FRESH;
      break;
  }

  PRINT("%s (code: %4d) : %zd bytes\n\t"
          "REASON: '%s'", 
          ws_close_opcode_print(opcode), opcode, len,
          reason);

  (void)ehandle;
}

static void
ws_on_text_cb(void *p_ws, CURL *ehandle, const char *text, size_t len)
{
  websockets::dati *ws = (websockets::dati*)p_ws;
  
  D_PRINT("ON_TEXT:\n\t\t%s", text);

  json_dump("RECEIVE PAYLOAD", &ws->p_client->settings, text);

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
                "EVENT_NAME:\t%s\n\t"
                "SEQ_NUMBER:\t%d\n\t"
                "EVENT_DATA:\t%s", 
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
  (void)ehandle;
}

/* init easy handle with some default opt */
static CURL*
custom_cws_new(websockets::dati *ws)
{
  //missing on_binary, on_ping, on_pong
  struct cws_callbacks cws_cbs = {
    .on_connect = &ws_on_connect_cb,
    .on_text = &ws_on_text_cb,
    .on_close = &ws_on_close_cb,
    .data = ws,
  };

  CURL *new_ehandle = cws_new(BASE_WEBSOCKETS_URL, NULL, &cws_cbs);
  ASSERT_S(NULL != new_ehandle, "Out of memory");

  CURLcode ecode;
  /* DEBUG ONLY FUNCTIONS */
  //set debug callback
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGFUNCTION, &curl_debug_cb));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //set ptr to settings containing dump files
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_DEBUGDATA, &ws->p_client->settings));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  //enable verbose
  D_ONLY(ecode = curl_easy_setopt(new_ehandle, CURLOPT_VERBOSE, 1L));
  D_ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));
  /* * * * * * * * * * * */

  //enable follow redirections
  ecode = curl_easy_setopt(new_ehandle, CURLOPT_FOLLOWLOCATION, 2L);
  ASSERT_S(CURLE_OK == ecode, curl_easy_strerror(ecode));

  return new_ehandle;
}

static CURLM*
custom_multi_init()
{
  CURLM *new_mhandle = curl_multi_init();
  ASSERT_S(NULL != new_mhandle, "Out of memory");

  return new_mhandle;
}

//@todo allow for user input
static char*
identify_init(int intents, char token[])
{
  const char fmt_properties[] = \
    "{\"$os\":\"%s\",\"$browser\":\"orca\",\"$device\":\"orca\"}";
  const char fmt_presence[] = \
    "{\"since\":%s,\"activities\":%s,\"status\":\"%s\",\"afk\":%s}";
  const char fmt_event_data[] = \
    "{\"token\":\"%s\",\"intents\":%d,\"properties\":%s,\"presence\":%s}";
  const char fmt_identify[] = \
    "{\"op\":2,\"d\":%s}"; //op:2 means IDENTIFY

  int ret; //check snprintf return value

  //https://discord.com/developers/docs/topics/gateway#identify-identify-connection-properties
  char properties[512];
  ret = snprintf(properties, sizeof(properties), fmt_properties, "Linux");
  ASSERT_S(ret < (int)sizeof(properties), "Out of bounds write attempt");

  //https://discord.com/developers/docs/topics/gateway#sharding
  /* @todo */

  //https://discord.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure
  char presence[512];
  ret = snprintf(presence, sizeof(presence), fmt_presence, 
           "null", "null", "online", "false");
  ASSERT_S(ret < (int)sizeof(presence), "Out of bounds write attempt");

  //https://discord.com/developers/docs/topics/gateway#identify-identify-structure
  char event_data[512];
  ret = snprintf(event_data, sizeof(event_data), fmt_event_data,
                  token, intents, properties, presence);
  ASSERT_S(ret < (int)sizeof(presence), "Out of bounds write attempt");

  int len = sizeof(fmt_identify);
  len += ret;

  char *identify = (char*)malloc(len);
  ASSERT_S(NULL != identify, "Out of memory");

  ret = snprintf(identify, len-1, fmt_identify, event_data);
  ASSERT_S(ret < len, "Out of bounds write attempt");

  return identify;
}

void
init(websockets::dati *ws, char token[])
{
  ws->status = status::DISCONNECTED;

  ws->ehandle = custom_cws_new(ws);
  ws->mhandle = custom_multi_init();

  ws->me = user::init();
  user::me::get(ws->p_client, ws->me);
}

void
cleanup(websockets::dati *ws)
{
  if (ws->identify)
    free(ws->identify);

  user::cleanup(ws->me);

  curl_multi_cleanup(ws->mhandle);
  cws_free(ws->ehandle);
}

/* send heartbeat pulse to websockets server in order
 *  to maintain connection alive */
static void
ws_send_heartbeat(websockets::dati *ws)
{
  char payload[64];
  int ret = snprintf(payload, sizeof(payload), "{\"op\":1,\"d\":%d}", ws->payload.seq_number);
  ASSERT_S(ret < (int)sizeof(payload), "Out of bounds write attempt");

  D_PRINT("HEARTBEAT_PAYLOAD:\n\t\t%s", payload);
  ws_send_payload(ws, payload);
}

static void
json_load(char *str, size_t len, void *p_ws)
{
  dati *ws = (dati*)p_ws;

  struct sized_buffer buf = {NULL, 0};

  json_scanf(str, len,
     "[url]%s"
     "[shards]%d"
     "[session_start_limit]%T",
     ws->session.url,
     &ws->session.shards,
     &buf);

  json_scanf(buf.start, buf.size,
      "[total]%d"
      "[remaining]%d"
      "[reset_after]%d"
      "[max_concurrency]%d",
      &ws->session.total,
      &ws->session.remaining,
      &ws->session.reset_after,
      &ws->session.max_concurrency);

  D_NOTOP_PUTS("Session Start Limit object loaded with API response"); 
}

static void
get_bot(client *client)
{
  struct resp_handle resp_handle = {&json_load, (void*)&client->ws};

  user_agent::run( 
    &client->ua,
    &resp_handle,
    NULL,
    HTTP_GET,
    "/gateway/bot");
}

/* main websockets event loop */
static void
ws_main_loop(websockets::dati *ws)
{
  //get session info before starting it
  get_bot(ws->p_client);

  if (!ws->session.remaining)
    ERR("Reach session starts threshold (%d)\n\t"
              "Please wait %d seconds and try again", 
        ws->session.total, ws->session.reset_after/1000);

  int is_running = 0;

  curl_multi_perform(ws->mhandle, &is_running);

  CURLMcode mcode;
  do {
    int numfds;

    ws->now_tstamp = orka_timestamp_ms(); // updates our concept of 'now'

    mcode = curl_multi_perform(ws->mhandle, &is_running);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

    //wait for activity or timeout
    mcode = curl_multi_wait(ws->mhandle, NULL, 0, 1000, &numfds);
    ASSERT_S(CURLM_OK == mcode, curl_multi_strerror(mcode));

    if (ws->status != status::CONNECTED) continue; // wait until connection is established

    /* CONNECTION IS ESTABLISHED */

    /*check if timespan since first pulse is greater than
     * minimum heartbeat interval required*/
    if (ws->hbeat.interval_ms < (ws->now_tstamp - ws->hbeat.tstamp)) {
      ws_send_heartbeat(ws);

      ws->hbeat.tstamp = ws->now_tstamp; //update heartbeat timestamp
    }

    if (ws->cbs.on_idle) {
      (*ws->cbs.on_idle)(ws->p_client, ws->me);
    }

    cws_ping(ws->ehandle, NULL, 0);

  } while(is_running);
}

/* connects to the discord websockets server */
void
run(websockets::dati *ws)
{
  ASSERT_S(status::CONNECTED != ws->status, "Can't have recursive connections");
  if (NULL != ws->identify) {
    free(ws->identify);
  }

  char *token = ws->p_client->settings.token;
  ws->identify = identify_init(ws->intents, token);

  do {
    curl_multi_add_handle(ws->mhandle, ws->ehandle);
    ws_main_loop(ws);
    curl_multi_remove_handle(ws->mhandle, ws->ehandle);

    if (status::DISCONNECTED == ws->status) break;
    if (ws->reconnect_attempts >= 5) break;

    // full shutdown of old connection before reconnecting
    cws_free(ws->ehandle);
    ws->ehandle = custom_cws_new(ws);

    ++ws->reconnect_attempts;
  } while (1);

  if (status::DISCONNECTED != ws->status) {
    PRINT("Failed all reconnect attempts (%d)", ws->reconnect_attempts);
    ws->status = status::DISCONNECTED;
  }
}

} // namespace websockets
} // namespace discord
