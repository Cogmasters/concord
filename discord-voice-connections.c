#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-voice-connections.h"
#include "cee-utils.h"

static pthread_mutex_t client_lock = PTHREAD_MUTEX_INITIALIZER;

static const char*
opcode_print(enum discord_voice_opcodes opcode)
{
  const char *str = discord_voice_opcodes_print(opcode);
  if (NULL == str) {
    log_warn("Invalid Voice opcode (code: %d)", opcode);
    str = "Invalid Voice opcode";
  }
  return str;
}

static const char*
close_opcode_print(enum discord_voice_close_opcodes opcode)
{
  const char *str = discord_voice_close_opcodes_print(opcode);
  if (str) return str;
  str = ws_close_opcode_print((enum ws_close_reason)opcode);
  if (str) return str;
  log_warn("Unknown WebSockets close opcode (code: %d)", opcode);
  return "Unknown WebSockets close opcode";
}

static void
send_resume(struct discord_voice *vc)
{
  vc->is_resumable = false; // reset

  char payload[DISCORD_MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):7" // RESUME OPCODE
              "(d):{"
                "(server_id):s_as_u64"
                "(session_id):s"
                "(token):s"
              "}",
              &vc->guild_id,
              vc->session_id, 
              vc->token);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  log_debug("Sending VOICE_RESUME:\n\t%s", payload);
  ws_send_text(vc->ws, NULL, payload, ret);
}

static void
send_identify(struct discord_voice *vc)
{
  char payload[DISCORD_MAX_PAYLOAD_LEN];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):0" // IDENTIFY OPCODE
              "(d):{"
                "(server_id):s_as_u64"
                "(user_id):s_as_u64"
                "(session_id):s"
                "(token):s"
              "}",
              &vc->guild_id,
              &vc->bot_id,
              vc->session_id,
              vc->token);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  log_info("sending VOICE_IDENTIFY:\n\t%s", payload);
  ws_send_text(vc->ws, NULL, payload, ret);
}

static void
on_hello(struct discord_voice *vc)
{
  vc->hbeat.tstamp = cee_timestamp_ms();

  float hbeat_interval = 0.0;
  json_extract(vc->payload.event_data.start, vc->payload.event_data.size,
             "(heartbeat_interval):f", &hbeat_interval);
  ASSERT_S(hbeat_interval > 0.0, "Invalid heartbeat_ms");
  log_info("on_hello:%.*s", vc->payload.event_data.size,
           vc->payload.event_data.start);
  log_debug("vc hearbeat_interval:%f", hbeat_interval);

  vc->hbeat.interval_ms = (u64_unix_ms_t)fmin(hbeat_interval, 5000);

  if (vc->is_resumable)
    send_resume(vc);
  else
    send_identify(vc);
}

static void
on_ready(struct discord_voice *vc)
{
  vc->is_ready = true;
  vc->reconnect.attempt = 0;
  log_info("Succesfully started a Discord Voice session!");

  struct discord *client = vc->p_client;
  if (client->voice_cbs.on_ready) {
    client->voice_cbs.on_ready(vc);
  }
}

static void
on_session_description(struct discord_voice *vc)
{
  struct discord *client = vc->p_client;
  if (client->voice_cbs.on_session_descriptor) {
    client->voice_cbs.on_session_descriptor(vc);
  }
}

static void
on_speaking(struct discord_voice *vc)
{
  struct discord *client = vc->p_client;
  if (!client->voice_cbs.on_speaking) return;

  u64_snowflake_t user_id;
  int speaking=0,delay=0,ssrc=0;
  json_extract(vc->payload.event_data.start, vc->payload.event_data.size,
              "(user_id):s_as_u64"
              "(speaking):d"
              "(delay):d"
              "(ssrc):d", 
              &user_id, &speaking, &delay, &ssrc);

  log_debug("receiving VOICE_SPEAKING:%.*s",
            vc->payload.event_data.size, vc->payload.event_data.start);

  (*client->voice_cbs.on_speaking) (
      client,
      vc,
      &vc->p_client->gw.bot,
      user_id,
      speaking,
      delay,
      ssrc);
}

static void
on_resumed(struct discord_voice *vc)
{
  vc->is_ready = true;
  vc->reconnect.attempt = 0;
  log_info("Successfully resumed a Discord Voice session!");
}

static void
on_client_disconnect(struct discord_voice *vc)
{
  struct discord *client = vc->p_client;

  log_info("on_client_disconnect:%.*s",
           vc->payload.event_data.size, vc->payload.event_data.start);

  if (!client->voice_cbs.on_client_disconnect) return;

  u64_snowflake_t user_id=0;
  json_extract(vc->payload.event_data.start, vc->payload.event_data.size,
              "(user_id):s_as_u64", &user_id);

  (*client->voice_cbs.on_client_disconnect)(
      client,
      vc,
      &client->gw.bot,
      user_id);
}

static void
on_codec(struct discord_voice *vc)
{
  struct discord *client = vc->p_client;
  log_info("on_codec:%.*s", vc->payload.event_data.size, vc->payload.event_data.start);

  if (!client->voice_cbs.on_codec) return;

  char audio_codec[64]={0}, video_codec[64]={0};
  json_extract(vc->payload.event_data.start, vc->payload.event_data.size,
              "(audio_codec):s, (video_codec):s", &audio_codec, &video_codec);

  (*client->voice_cbs.on_codec)(
      client,
      vc,
      &client->gw.bot,
      audio_codec,
      video_codec);
}

static void
on_heartbeat_ack(struct discord_voice *vc)
{
  // get request / response interval in milliseconds
  vc->ping_ms = cee_timestamp_ms() - vc->hbeat.tstamp;
  log_trace("PING: %d ms", vc->ping_ms);
}

static void
on_connect_cb(void *p_vc, struct websockets *ws, struct ws_info *info, const char *ws_protocols) {
  log_info("Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_vc, struct websockets *ws, struct ws_info *info, enum ws_close_reason wscode, const char *reason, size_t len)
{
  struct discord_voice *vc = p_vc;
  enum discord_voice_close_opcodes opcode = (enum discord_voice_close_opcodes)wscode;

  log_warn("on_close_cb:" ANSICOLOR("%s",ANSI_FG_RED)" (code: %4d) : %zd bytes,"
                                                     "REASON: '%s'",
           close_opcode_print(opcode), opcode, len, reason);

  if (vc->shutdown) {
    log_info(ANSICOLOR("Voice ws was asked to close, don't reconnect/resume.", ANSI_BG_BLUE));
    vc->is_resumable = false;
    vc->reconnect.enable = false;
    return;
  }

  switch (opcode) {
  case DISCORD_VOICE_CLOSE_REASON_SERVER_CRASH:
      vc->is_resumable = true;
      vc->reconnect.enable = true;
      break;
  case DISCORD_VOICE_CLOSE_REASON_UNKNOWN_OPCODE:
  case DISCORD_VOICE_CLOSE_REASON_DECODE_ERROR:
  case DISCORD_VOICE_CLOSE_REASON_NOT_AUTHENTICATED:
  case DISCORD_VOICE_CLOSE_REASON_AUTHENTICATION_FAILED:
  case DISCORD_VOICE_CLOSE_REASON_ALREADY_AUTHENTICATED:
  case DISCORD_VOICE_CLOSE_REASON_SERVER_NOT_FOUND:
  case DISCORD_VOICE_CLOSE_REASON_UNKNOWN_PROTOCOL:
  case DISCORD_VOICE_CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE:
      vc->is_resumable = false;
      vc->reconnect.enable = false;
      break;
  case DISCORD_VOICE_CLOSE_REASON_DISCONNECTED:
      vc->is_resumable = false;
      vc->reconnect.enable = true;
      break;
  default: //websocket/clouflare opcodes
      if (WS_CLOSE_REASON_NORMAL == (enum ws_close_reason)opcode) {
        vc->is_resumable = true;
        vc->reconnect.enable = true;
      }
      else {
        vc->is_resumable = false;
        vc->reconnect.enable = false;
      }
      break;
  case DISCORD_VOICE_CLOSE_REASON_SESSION_TIMED_OUT:
  case DISCORD_VOICE_CLOSE_REASON_INVALID_SESSION:
      vc->is_resumable = false;
      vc->reconnect.enable = true;
      break;
  }
}

static void
on_text_cb(void *p_vc, struct websockets *ws, struct ws_info *info, const char *text, size_t len) 
{
  struct discord_voice *vc = p_vc;

  json_extract((char*)text, len,
              "(op):d (d):T",
               &vc->payload.opcode,
               &vc->payload.event_data);

  log_trace("on_text_cb:" ANSICOLOR("VOICE_%s", ANSI_FG_BRIGHT_YELLOW)", %.*s",
            opcode_print(vc->payload.opcode), 
            (int)vc->payload.event_data.size,
            vc->payload.event_data.start);

  switch (vc->payload.opcode) {
  case DISCORD_VOICE_READY:
      on_ready(vc);
      break;
  case DISCORD_VOICE_SESSION_DESCRIPTION:
      on_session_description(vc);
      break;
  case DISCORD_VOICE_SPEAKING:
      on_speaking(vc);
      break;
  case DISCORD_VOICE_HEARTBEAT_ACK:
      on_heartbeat_ack(vc);
      break;
  case DISCORD_VOICE_HELLO:
      on_hello(vc);
      break;
  case DISCORD_VOICE_RESUMED:
      on_resumed(vc);
      break;
  case DISCORD_VOICE_CLIENT_DISCONNECT:
      on_client_disconnect(vc);
      break;
  case DISCORD_VOICE_CODEC:
      on_codec(vc);
      break;
  default:
      log_error("Not yet implemented Voice Event(code: %d)", vc->payload.opcode);
      log_error("payload:%.*s", vc->payload.event_data.size, vc->payload.event_data.start);
      break;
  }
}

/* send heartbeat pulse to websockets server in order
 *  to maintain connection alive */
static void
send_heartbeat(struct discord_voice *vc)
{
  char payload[64];
  int ret = json_inject(payload, sizeof(payload), 
              "(op):3, (d):ld", &vc->hbeat.interval_ms);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  log_trace("Sending VOICE_HEARTBEAT(%d bytes)", ret);
  ws_send_text(vc->ws, NULL, payload, ret);
}

static void
_discord_voice_cleanup(struct discord_voice *vc)
{
  // close the descriptor
  // kill the child process
  if (vc->ws)
    ws_cleanup(vc->ws);
  free(vc);
}

static void
reset_vc(struct discord_voice *vc) {
  vc->reconnect.attempt = 0;
  vc->shutdown = false;
}

static void
_discord_voice_init(
  struct discord_voice *new_vc,
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t channel_id)
{
  new_vc->p_client = client;
  new_vc->guild_id = guild_id;
  new_vc->channel_id = channel_id;
  new_vc->bot_id = client->gw.bot.id;
  if (NULL == new_vc->ws) {
    struct ws_callbacks cbs = {
      .data = new_vc,
      .on_connect = &on_connect_cb,
      .on_text = &on_text_cb,
      .on_close = &on_close_cb
    };
    new_vc->ws = ws_init(&cbs, new_vc->p_client->config);
    new_vc->reconnect.threshold = 5; /** hard limit for now */
    new_vc->reconnect.enable = true;
  }
  reset_vc(new_vc);
}

void
discord_send_speaking(struct discord_voice *vc, enum discord_voice_speaking_flags flag,
                      int delay)
{
  ASSERT_S(WS_CONNECTED == ws_get_status(vc->ws), "Action requires an active connection to Discord");

  char payload[128];
  int ret = json_inject(payload, sizeof(payload),
                        "(op):5," // VOICE SPEAKING OPCODE
                        "(d):{"
                          "(speaking):d"
                          "(delay):d"
                          "(ssrc):d"
                        "}",
                        &flag, 
                        &delay,
                        &vc->udp_service.ssrc);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  log_info("Sending VOICE_SPEAKING(%d bytes)", ret);
  ws_send_text(vc->ws, NULL, payload, ret);
}

static void
recycle_active_vc(
  struct discord_voice *vc,
  u64_snowflake_t guild_id, 
  u64_snowflake_t channel_id)
{
  if (ws_is_alive(vc->ws)) {
    log_info(ANSICOLOR("shutting down an active vcs %"PRIu64, ANSI_FG_RED), vc->channel_id);
    discord_voice_shutdown(vc);
    log_info(ANSICOLOR("the active vcs has been shutted down", ANSI_FG_RED));
    log_info(ANSICOLOR("the active vcs is reused for %"PRIu64, ANSI_FG_RED), channel_id);
  }
  vc->channel_id = channel_id;
  vc->guild_id = guild_id;
  vc->shutdown = false;

  char tag[64];
  snprintf(tag, sizeof tag, "VC_%"PRIu64, guild_id);
  logconf_add_id(vc->p_client->config, vc->ws, tag);
}

static void
send_voice_state_update(
  struct discord_gateway *gw,
  u64_snowflake_t guild_id,
  u64_snowflake_t channel_id,
  bool self_mute,
  bool self_deaf)
{
  char payload[256];
  int ret;
  char *msg;
  if (channel_id) {
    ret = json_inject(payload, sizeof(payload),
                      "(op):4," // VOICE STATE UPDATE OPCODE
                      "(d):{"
                        "(guild_id):s_as_u64,"
                        "(channel_id):s_as_u64,"
                        "(self_mute):b,"
                        "(self_deaf):b"
                      "}",
                      &guild_id,
                      &channel_id,
                      &self_mute,
                      &self_deaf);
    msg = "Sending VOICE_STATE_UPDATE to join a channel:\n\t%s";
  }
  else {
    ret = json_inject(payload, sizeof(payload),
                      "(op):4," // VOICE STATE UPDATE OPCODE
                      "(d):{"
                        "(guild_id):s_as_u64,"
                        "(channel_id):null,"
                        "(self_mute):b,"
                        "(self_deaf):b"
                      "}",
                      &guild_id,
                      &self_mute,
                      &self_deaf);
    msg = "Sending VOICE_STATE_UPDATE to leave a channel:\n\t%s";
  }
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");
  log_info(msg, payload);
  ws_send_text(gw->ws, NULL, payload, ret);
}

enum discord_join_vc_status
discord_join_vc(
  struct discord *client,
  struct discord_message *msg,
  u64_snowflake_t guild_id,
  u64_snowflake_t voice_channel_id,
  bool self_mute,
  bool self_deaf)
{
  if (!ws_is_functional(client->gw.ws))
    return DISCORD_JOIN_VC_ERROR;

  bool found_a_running_vcs = false;
  pthread_mutex_lock(&client_lock);
  struct discord_voice *vc=NULL;
  for (size_t i=0; i < DISCORD_MAX_VOICE_CONNECTIONS; ++i) {
    if (0 == client->vcs[i].guild_id) {
      log_debug("found an unused vcs at %d", i);
      vc = client->vcs+i;
      _discord_voice_init(vc, client, guild_id, voice_channel_id);
      break;
    }
    if (guild_id == client->vcs[i].guild_id) {
      if (voice_channel_id == client->vcs[i].channel_id) {
        log_warn("found an active vcs at %d, ignore the command", i);
        found_a_running_vcs = true;
      }
      vc = client->vcs+i;
      break;
    }
  }
  pthread_mutex_unlock(&client_lock);

  if (!vc) {
    log_error("exhaust all vcs, cannot send VOICE_STATE_UPDATE");
    // run out of vcs connections, report error to users
    return DISCORD_JOIN_VC_EXHAUST_CAPACITY;
  }
  if (found_a_running_vcs) {
    return DISCORD_JOIN_VC_ALREADY_JOINED;
  }

  recycle_active_vc(vc, guild_id, voice_channel_id);
  vc->message_channel_id = msg->channel_id;
  send_voice_state_update(&client->gw, guild_id, voice_channel_id, self_mute, self_deaf);
  return DISCORD_JOIN_VC_JOINED;
}

/*
 * The normal situations that we expect:
 * 1. join a vc
 * 2. leave a vc
 * 3. Discord just kicks the bot out of a vc.
 */
void
_discord_on_voice_state_update(struct discord *client, struct discord_voice_state *vs)
{
  log_info("on_voice_state_update");
  pthread_mutex_lock(&client_lock);
  struct discord_voice *vc=NULL;
  for (int i=0; i < DISCORD_MAX_VOICE_CONNECTIONS; ++i) {
    if (vs->guild_id == client->vcs[i].guild_id) {
      vc = client->vcs+i;
      if (vs->channel_id) {
        int ret = snprintf(vc->session_id, sizeof(vc->session_id), "%s",
                           vs->session_id);
        ASSERT_S(ret < sizeof(vc->session_id), "Out of bounds write attempt");
        log_info("start a new voice session-id " ANSICOLOR("%s", ANSI_FG_YELLOW),
                 vc->session_id);
      }
      break;
    }
  }
  pthread_mutex_unlock(&client_lock);

  if (!vc) {
    if (vs->channel_id) {
      log_fatal("This should not happen, cannot find a discord_voice object");
      // report this
    }
    return;
  }

  if (vs->channel_id == 0) {
    log_info(ANSICOLOR("Bot is leaving the current vc", ANSI_BG_BRIGHT_BLUE));
    if (vc->ws && ws_is_alive(vc->ws))
      log_warn("Voice ws is still alive");
    return;
  }
}

static void
event_loop(struct discord_voice *vc)
{
  struct discord *client = vc->p_client;
  ws_start(vc->ws);

  bool is_running=false;

  // everything goes well, ws event_loop to serve
  // the ws server side events
  while (1) {
    ws_perform(vc->ws, &is_running, 100);
    if (!is_running) break; // exit event loop
    if (!vc->is_ready) continue; // wait until on_ready()

    // connection is established
    /*check if timespan since first pulse is greater than
     * minimum heartbeat interval required*/
    if (vc->hbeat.interval_ms < (ws_timestamp(vc->ws) - vc->hbeat.tstamp)) {
      send_heartbeat(vc);
      vc->hbeat.tstamp = ws_timestamp(vc->ws); //update heartbeat timestamp
    }
    if (client->voice_cbs.on_idle)
      (*client->voice_cbs.on_idle)(client, vc, &vc->p_client->gw.bot);
  }
  vc->is_ready = false;
}

static void*
start_voice_ws_thread(void *p_vc) 
{
  log_info("new voice ws thread");
  struct discord_voice *vc = p_vc;

  // handle ws reconnect/resume/redirect logic
  while (vc->reconnect.attempt < vc->reconnect.threshold) 
  {
    event_loop(vc);

    log_debug("after event_loop "
              "reconnect.attempt:%d, reconnect.enable:%d, is_resumable:%d, "
              "redirect:%d",
              vc->reconnect.attempt, vc->reconnect.enable, vc->is_resumable,
              vc->is_redirect);

    if (vc->is_redirect) {
      log_info("update the token and url");
      memcpy(vc->token, vc->new_token, sizeof(vc->token));
      ws_set_url(vc->ws, vc->new_url, NULL);
      vc->is_redirect = false;
      vc->reconnect.attempt = 0;
      vc->reconnect.enable = true;
      vc->is_resumable = false;
      continue;
    }

    if (!vc->reconnect.enable) {
      log_warn("Discord Voice Shutdown");
      goto _end;
    }

    ++vc->reconnect.attempt;
    log_info("Reconnect attempt #%d", vc->reconnect.attempt);
  }

  if (!vc->shutdown)
    log_error("Could not reconnect to Discord Voice after %d tries", vc->reconnect.threshold);

  // exit from the event loop;
  _end:
  if (vc->shutdown)
    log_info(ANSICOLOR("Voice ws was closed per request",ANSI_BG_BLUE));
  log_debug("exiting %"PRIu64":%"PRIu64, vc->guild_id, vc->channel_id);
  reset_vc(vc);
  vc->guild_id = 0; // put this back to the pool
  log_info("exit voice ws thread");
  return NULL;
}

/*
 * 1. join a vc -> create a new ws connection
 * 2. change voice region -> redirect an existing ws connection
 */
void 
_discord_on_voice_server_update(struct discord *client, u64_snowflake_t guild_id, char *token, char *endpoint)
{
  log_info("on_voice_server_update is called");
  struct discord_voice *vc = NULL;
  pthread_mutex_lock(&client_lock);
  for (size_t i=0; i < DISCORD_MAX_VOICE_CONNECTIONS; ++i) {
    if (guild_id == client->vcs[i].guild_id) {
      vc = client->vcs+i;
      break;
    }
  }
  pthread_mutex_unlock(&client_lock);
  if (!vc) {
    log_fatal("This should not happen, couldn't match voice-server update to client");
    return;
  }

  int ret;
  ret = snprintf(vc->new_token, sizeof(vc->new_token), "%s", token);
  ASSERT_S(ret < sizeof(vc->new_token), "Out of bounds write attempt");
  //char base_url[MAX_URL_LEN]; // the session base url
  ret = snprintf(vc->new_url, sizeof(vc->new_url), \
      "wss://%s"DISCORD_VOICE_CONNECTIONS_URL_SUFFIX, endpoint);
  ASSERT_S(ret < sizeof(vc->new_url), "Out of bounds write attempt");

  // @todo: replace with the more reliable thread alive check
  if (ws_is_alive(vc->ws)) {
    // shutdown and restart
    log_info("Voice ws switches to " ANSICOLOR("%s", ANSI_FG_RED), vc->new_url);
    log_info("Voice ws uses token %s", vc->new_token);
    // exits the current event_loop to redirect
    vc->is_redirect = true;
    ws_close(vc->ws, WS_CLOSE_REASON_NORMAL, "", 0);
  }
  else {
    log_info("Voice ws uses " ANSICOLOR("%s", ANSI_FG_RED), vc->new_url);
    log_info("Voice ws uses token %s", vc->new_token);

    memcpy(vc->token, vc->new_token, sizeof(vc->new_token));
    ws_set_url(vc->ws, vc->new_url, NULL);
    /*
     * spawn a new thread
     */
    pthread_t tid;
    if (pthread_create(&tid, NULL, &start_voice_ws_thread, vc))
      ERR("Couldn't create thread");
    if (pthread_detach(tid))
      ERR("Couldn't detach thread");
  }
}

static void noop_voice_state_update_cb(struct discord *a, const struct discord_user *b, const struct discord_voice_state *c) {return;}
static void noop_voice_server_update_cb(struct discord *a, const struct discord_user *b, const char *c, const u64_snowflake_t d, const char *endpoint) {return;}
static void noop_idle_cb(struct discord *a, struct discord_voice *b, const struct discord_user *c) { return; }
static void noop_on_speaking(struct discord *a, struct discord_voice *b, const struct discord_user *c, const u64_snowflake_t d, const int e, const int f, const int g) { return; }
static void noop_on_voice_client_disconnect(struct discord *a, struct discord_voice *b, const struct discord_user *c, const u64_snowflake_t d) { return; }
static void noop_on_voice_codec(struct discord *a, struct discord_voice *b, const struct discord_user *c, const char d[], const char e[]) { return; }
static void noop_on_ready(struct discord_voice *a) { return; }
static void noop_on_session_descriptor(struct discord_voice *a) { return; }
static void noop_on_udp_server_connected(struct discord_voice *a) { return; }

void 
discord_voice_connections_init(struct discord *client) 
{
  client->gw.cbs.on_voice_state_update = noop_voice_state_update_cb;
  client->gw.cbs.on_voice_server_update = noop_voice_server_update_cb;

  client->voice_cbs.on_idle = noop_idle_cb;
  client->voice_cbs.on_ready = noop_on_ready;
  client->voice_cbs.on_client_disconnect = noop_on_voice_client_disconnect;
  client->voice_cbs.on_session_descriptor = noop_on_session_descriptor;
  client->voice_cbs.on_codec = noop_on_voice_codec;
  client->voice_cbs.on_speaking = noop_on_speaking;
  client->voice_cbs.on_udp_server_connected = noop_on_udp_server_connected;

  for (int i=0; i < DISCORD_MAX_VOICE_CONNECTIONS; ++i) {
    client->vcs[i].p_voice_cbs = &client->voice_cbs;
  }
}

void
discord_voice_shutdown(struct discord_voice *vc) 
{
  log_warn("Notify gateway ws that the bot is leaving a vc");
  vc->reconnect.enable = false;
  vc->is_resumable = false;
  vc->shutdown = true;
  ws_close(vc->ws, WS_CLOSE_REASON_NORMAL, "", 0);

  send_voice_state_update(
    &vc->p_client->gw, 
    vc->guild_id, 
    0, 
    false, 
    false);
}

void
discord_voice_reconnect(struct discord_voice *vc, bool resume) 
{
  vc->reconnect.enable = true;
  vc->is_resumable = resume;
  ws_close(vc->ws, WS_CLOSE_REASON_NORMAL, "", 0);
}

bool
discord_voice_is_alive(struct discord_voice *vc) {
  return vc->guild_id && ws_is_alive(vc->ws);
}
