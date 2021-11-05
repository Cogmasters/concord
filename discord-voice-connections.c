#define _GNU_SOURCE /* asprintf() */
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "discord.h"
#include "discord-internal.h"
#include "discord-voice-connections.h"
#include "cee-utils.h"

static pthread_mutex_t client_lock = PTHREAD_MUTEX_INITIALIZER;

static const char *
opcode_print(enum discord_voice_opcodes opcode)
{
  const char *str = discord_voice_opcodes_print(opcode);
  if (NULL == str) str = "Invalid Voice opcode";
  return str;
}

static const char *
close_opcode_print(enum discord_voice_close_event_codes opcode)
{
  const char *str = discord_voice_close_event_codes_print(opcode);
  if (str) return str;
  str = ws_close_opcode_print((enum ws_close_reason)opcode);
  if (str) return str;
  return "Unknown WebSockets close opcode";
}

static void
send_resume(struct discord_voice *vc)
{
  vc->is_resumable = false; /* reset */

  char payload[1024];
  int ret = json_inject(payload, sizeof(payload),
                        "(op):7" /* RESUME OPCODE */
                        "(d):{"
                        "(server_id):s_as_u64"
                        "(session_id):s"
                        "(token):s"
                        "}",
                        &vc->guild_id, vc->session_id, vc->token);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  logconf_info(
    &vc->conf,
    ANSICOLOR("SEND", ANSI_FG_BRIGHT_GREEN) " VOICE_RESUME (%d bytes)", ret);
  ws_send_text(vc->ws, NULL, payload, ret);
}

static void
send_identify(struct discord_voice *vc)
{
  char payload[1024];
  int ret = json_inject(payload, sizeof(payload),
                        "(op):0" /* IDENTIFY OPCODE */
                        "(d):{"
                        "(server_id):s_as_u64"
                        "(user_id):s_as_u64"
                        "(session_id):s"
                        "(token):s"
                        "}",
                        &vc->guild_id, &vc->bot_id, vc->session_id, vc->token);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  logconf_info(
    &vc->conf,
    ANSICOLOR("SEND", ANSI_FG_BRIGHT_GREEN) " VOICE_IDENTIFY (%d bytes)", ret);
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

  vc->hbeat.interval_ms = (u64_unix_ms_t)fmin(hbeat_interval, 5000);

  if (vc->is_resumable)
    send_resume(vc);
  else
    send_identify(vc);
}

static void
on_ready(struct discord_voice *vc)
{
  logconf_info(&vc->conf, "Succesfully started a Discord Voice session!");
  vc->is_ready = true;
  vc->reconnect.attempt = 0;

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
  int speaking = 0, delay = 0, ssrc = 0;
  json_extract(vc->payload.event_data.start, vc->payload.event_data.size,
               "(user_id):s_as_u64"
               "(speaking):d"
               "(delay):d"
               "(ssrc):d",
               &user_id, &speaking, &delay, &ssrc);

  (*client->voice_cbs.on_speaking)(client, vc, &vc->p_client->gw.bot, user_id,
                                   speaking, delay, ssrc);
}

static void
on_resumed(struct discord_voice *vc)
{
  vc->is_ready = true;
  vc->reconnect.attempt = 0;
  logconf_info(&vc->conf, "Successfully resumed a Discord Voice session!");
}

static void
on_client_disconnect(struct discord_voice *vc)
{
  struct discord *client = vc->p_client;

  if (!client->voice_cbs.on_client_disconnect) return;

  u64_snowflake_t user_id = 0;
  json_extract(vc->payload.event_data.start, vc->payload.event_data.size,
               "(user_id):s_as_u64", &user_id);

  (*client->voice_cbs.on_client_disconnect)(client, vc, &client->gw.bot,
                                            user_id);
}

static void
on_codec(struct discord_voice *vc)
{
  struct discord *client = vc->p_client;

  if (!client->voice_cbs.on_codec) return;

  char audio_codec[64] = { 0 }, video_codec[64] = { 0 };
  json_extract(vc->payload.event_data.start, vc->payload.event_data.size,
               "(audio_codec):s, (video_codec):s", &audio_codec, &video_codec);

  (*client->voice_cbs.on_codec)(client, vc, &client->gw.bot, audio_codec,
                                video_codec);
}

static void
on_heartbeat_ack(struct discord_voice *vc)
{
  /* get request / response interval in milliseconds */
  vc->ping_ms = cee_timestamp_ms() - vc->hbeat.tstamp;
  logconf_trace(&vc->conf, "PING: %d ms", vc->ping_ms);
}

static void
on_connect_cb(void *p_vc,
              struct websockets *ws,
              struct ws_info *info,
              const char *ws_protocols)
{
  struct discord_voice *vc = p_vc;
  logconf_info(&vc->conf, "Connected, WS-Protocols: '%s'", ws_protocols);
}

static void
on_close_cb(void *p_vc,
            struct websockets *ws,
            struct ws_info *info,
            enum ws_close_reason wscode,
            const char *reason,
            size_t len)
{
  struct discord_voice *vc = p_vc;
  enum discord_voice_close_event_codes opcode =
    (enum discord_voice_close_event_codes)wscode;

  logconf_warn(
    &vc->conf,
    ANSICOLOR("CLOSE %s", ANSI_FG_RED) " (code: %4d, %zu bytes): '%.*s'",
    close_opcode_print(opcode), opcode, len, (int)len, reason);

  if (vc->shutdown) {
    logconf_info(&vc->conf, "Voice was shutdown");
    vc->is_resumable = false;
    vc->reconnect.enable = false;
    return;
  }

  switch (opcode) {
  case DISCORD_VOICE_CLOSE_EVENT_SERVER_CRASH:
    vc->is_resumable = true;
    vc->reconnect.enable = true;
    break;
  case DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_OPCODE:
  case DISCORD_VOICE_CLOSE_EVENT_DECODE_ERROR:
  case DISCORD_VOICE_CLOSE_EVENT_NOT_AUTHENTICATED:
  case DISCORD_VOICE_CLOSE_EVENT_AUTHENTICATION_FAILED:
  case DISCORD_VOICE_CLOSE_EVENT_ALREADY_AUTHENTICATED:
  case DISCORD_VOICE_CLOSE_EVENT_SERVER_NOT_FOUND:
  case DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_PROTOCOL:
  case DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_ENCRYPTION_MODE:
    vc->is_resumable = false;
    vc->reconnect.enable = false;
    break;
  case DISCORD_VOICE_CLOSE_EVENT_DISCONNECTED:
    vc->is_resumable = false;
    vc->reconnect.enable = true;
    break;
  default: /*websocket/clouflare opcodes */
    if (WS_CLOSE_REASON_NORMAL == (enum ws_close_reason)opcode) {
      vc->is_resumable = true;
      vc->reconnect.enable = true;
    }
    else {
      vc->is_resumable = false;
      vc->reconnect.enable = false;
    }
    break;
  case DISCORD_VOICE_CLOSE_EVENT_SESSION_TIMED_OUT:
  case DISCORD_VOICE_CLOSE_EVENT_INVALID_SESSION:
    vc->is_resumable = false;
    vc->reconnect.enable = true;
    break;
  }
}

static void
on_text_cb(void *p_vc,
           struct websockets *ws,
           struct ws_info *info,
           const char *text,
           size_t len)
{
  struct discord_voice *vc = p_vc;

  json_extract((char *)text, len, "(op):d (d):T", &vc->payload.opcode,
               &vc->payload.event_data);

  logconf_trace(
    &vc->conf, ANSICOLOR("RCV", ANSI_FG_BRIGHT_YELLOW) " VOICE_%s (%zu bytes)",
    opcode_print(vc->payload.opcode), len);

  switch (vc->payload.opcode) {
  case DISCORD_VOICE_READY: on_ready(vc); break;
  case DISCORD_VOICE_SESSION_DESCRIPTION: on_session_description(vc); break;
  case DISCORD_VOICE_SPEAKING: on_speaking(vc); break;
  case DISCORD_VOICE_HEARTBEAT_ACK: on_heartbeat_ack(vc); break;
  case DISCORD_VOICE_HELLO: on_hello(vc); break;
  case DISCORD_VOICE_RESUMED: on_resumed(vc); break;
  case DISCORD_VOICE_CLIENT_DISCONNECT: on_client_disconnect(vc); break;
  case DISCORD_VOICE_CODEC: on_codec(vc); break;
  default:
    logconf_error(&vc->conf, "Not yet implemented Voice Event(code: %d)",
                  vc->payload.opcode);
    break;
  }
}

/* send heartbeat pulse to websockets server in order
 *  to maintain connection alive */
static void
send_heartbeat(struct discord_voice *vc)
{
  char payload[64];
  int ret = json_inject(payload, sizeof(payload), "(op):3, (d):ld",
                        &vc->hbeat.interval_ms);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  logconf_info(
    &vc->conf,
    ANSICOLOR("SEND", ANSI_FG_BRIGHT_GREEN) " VOICE_HEARTBEAT (%d bytes)",
    ret);
  ws_send_text(vc->ws, NULL, payload, ret);
}

static void
_discord_voice_cleanup(struct discord_voice *vc)
{
  /* close the descriptor */
  /* kill the child process */
  if (vc->ws) ws_cleanup(vc->ws);
  free(vc);
}

static void
reset_vc(struct discord_voice *vc)
{
  vc->reconnect.attempt = 0;
  vc->shutdown = false;
}

static void
_discord_voice_init(struct discord_voice *new_vc,
                    struct discord *client,
                    u64_snowflake_t guild_id,
                    u64_snowflake_t channel_id)
{
  new_vc->p_client = client;
  new_vc->guild_id = guild_id;
  new_vc->channel_id = channel_id;
  new_vc->bot_id = client->gw.bot.id;
  if (NULL == new_vc->ws) {
    struct ws_callbacks cbs = { .data = new_vc,
                                .on_connect = &on_connect_cb,
                                .on_text = &on_text_cb,
                                .on_close = &on_close_cb };
    new_vc->ws = ws_init(&cbs, new_vc->p_client->conf);
    new_vc->reconnect.threshold = 5; /** hard limit for now */
    new_vc->reconnect.enable = true;

    logconf_branch(&new_vc->conf, client->conf, "DISCORD_VOICE");
  }
  reset_vc(new_vc);
}

void
discord_send_speaking(struct discord_voice *vc,
                      enum discord_voice_speaking_flags flag,
                      int delay)
{
  ASSERT_S(WS_CONNECTED == ws_get_status(vc->ws),
           "Action requires an active connection to Discord");

  char payload[128];
  int ret = json_inject(payload, sizeof(payload),
                        "(op):5," /* VOICE SPEAKING OPCODE */
                        "(d):{"
                        "(speaking):d"
                        "(delay):d"
                        "(ssrc):d"
                        "}",
                        &flag, &delay, &vc->udp_service.ssrc);
  ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");

  logconf_info(
    &vc->conf,
    ANSICOLOR("SEND", ANSI_FG_BRIGHT_GREEN) " VOICE_SPEAKING (%d bytes)", ret);
  ws_send_text(vc->ws, NULL, payload, ret);
}

static void
recycle_active_vc(struct discord_voice *vc,
                  u64_snowflake_t guild_id,
                  u64_snowflake_t channel_id)
{
  if (ws_is_alive(vc->ws)) {
    discord_voice_shutdown(vc);
  }
  vc->channel_id = channel_id;
  vc->guild_id = guild_id;
  vc->shutdown = false;
}

static void
send_voice_state_update(struct discord_voice *vc,
                        u64_snowflake_t guild_id,
                        u64_snowflake_t channel_id,
                        bool self_mute,
                        bool self_deaf)
{
  struct discord_gateway *gw = &vc->p_client->gw;
  char payload[256];
  int ret;

  if (channel_id) {
    ret = json_inject(payload, sizeof(payload),
                      "(op):4," /* VOICE STATE UPDATE OPCODE */
                      "(d):{"
                      "(guild_id):s_as_u64,"
                      "(channel_id):s_as_u64,"
                      "(self_mute):b,"
                      "(self_deaf):b"
                      "}",
                      &guild_id, &channel_id, &self_mute, &self_deaf);
    ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");
    logconf_info(
      &vc->conf,
      ANSICOLOR(
        "SEND",
        ANSI_FG_BRIGHT_GREEN) " VOICE_STATE_UPDATE (%d bytes): join channel",
      ret);
  }
  else {
    ret = json_inject(payload, sizeof(payload),
                      "(op):4," /* VOICE STATE UPDATE OPCODE */
                      "(d):{"
                      "(guild_id):s_as_u64,"
                      "(channel_id):null,"
                      "(self_mute):b,"
                      "(self_deaf):b"
                      "}",
                      &guild_id, &self_mute, &self_deaf);
    ASSERT_S(ret < sizeof(payload), "Out of bounds write attempt");
    logconf_info(
      &vc->conf,
      ANSICOLOR(
        "SEND",
        ANSI_FG_BRIGHT_GREEN) " VOICE_STATE_UPDATE (%d bytes): leave channel",
      ret);
  }
  ws_send_text(gw->ws, NULL, payload, ret);
}

enum discord_voice_status
discord_voice_join(struct discord *client,
                   u64_snowflake_t guild_id,
                   u64_snowflake_t vchannel_id,
                   bool self_mute,
                   bool self_deaf)
{
  if (!ws_is_functional(client->gw.ws)) return DISCORD_VOICE_ERROR;

  bool found_a_running_vcs = false;
  pthread_mutex_lock(&client_lock);
  struct discord_voice *vc = NULL;

  int i;
  for (i = 0; i < DISCORD_MAX_VOICE_CONNECTIONS; ++i) {
    if (0 == client->vcs[i].guild_id) {
      vc = client->vcs + i;
      _discord_voice_init(vc, client, guild_id, vchannel_id);
      break;
    }
    if (guild_id == client->vcs[i].guild_id) {
      if (vchannel_id == client->vcs[i].channel_id) {
        found_a_running_vcs = true;
      }
      vc = client->vcs + i;
      break;
    }
  }
  pthread_mutex_unlock(&client_lock);

  if (!vc) {
    logconf_error(client->conf,
                  "All VC are busy, cannot send VOICE_STATE_UPDATE");
    /* run out of vcs connections, report error to users */
    return DISCORD_VOICE_EXHAUST_CAPACITY;
  }
  if (found_a_running_vcs) {
    return DISCORD_VOICE_ALREADY_JOINED;
  }

  recycle_active_vc(vc, guild_id, vchannel_id);
  send_voice_state_update(vc, guild_id, vchannel_id, self_mute, self_deaf);
  return DISCORD_VOICE_JOINED;
}

/*
 * The normal situations that we expect:
 * 1. join a vc
 * 2. leave a vc
 * 3. Discord just kicks the bot out of a vc.
 */
void
_discord_on_voice_state_update(struct discord *client,
                               struct discord_voice_state *vs)
{
  pthread_mutex_lock(&client_lock);
  struct discord_voice *vc = NULL;

  int i;
  for (i = 0; i < DISCORD_MAX_VOICE_CONNECTIONS; ++i) {
    if (vs->guild_id == client->vcs[i].guild_id) {
      vc = client->vcs + i;
      if (vs->channel_id) {
        int ret = snprintf(vc->session_id, sizeof(vc->session_id), "%s",
                           vs->session_id);
        ASSERT_S(ret < sizeof(vc->session_id), "Out of bounds write attempt");
        logconf_info(&vc->conf,
                     "Starting a new voice session (id: " ANSICOLOR(
                       "%s", ANSI_FG_YELLOW) ")",
                     vc->session_id);
      }
      break;
    }
  }
  pthread_mutex_unlock(&client_lock);

  if (!vc) {
    if (vs->channel_id) {
      logconf_fatal(
        client->conf,
        "This should not happen, cannot find a discord_voice object");
      /* report this */
    }
    return;
  }

  if (vs->channel_id == 0) {
    logconf_info(&vc->conf, ANSICOLOR("Bot is leaving the current vc",
                                      ANSI_BG_BRIGHT_BLUE));
    if (vc->ws && ws_is_alive(vc->ws))
      logconf_warn(&vc->conf, "Voice ws is still alive");
    return;
  }
}

static void
event_loop(struct discord_voice *vc)
{
  struct discord *client = vc->p_client;
  ws_start(vc->ws);

  bool is_running = false;

  /* everything goes well, ws event_loop to serve */
  /* the ws server side events */
  while (1) {
    ws_perform(vc->ws, &is_running, 100);
    if (!is_running) break; /* exit event loop */
    if (!vc->is_ready) continue; /* wait until on_ready() */

    /* connection is established */
    /*check if timespan since first pulse is greater than
     * minimum heartbeat interval required*/
    if (vc->hbeat.interval_ms < (ws_timestamp(vc->ws) - vc->hbeat.tstamp)) {
      send_heartbeat(vc);
      vc->hbeat.tstamp = ws_timestamp(vc->ws); /*update heartbeat timestamp */
    }
    if (client->voice_cbs.on_idle)
      (*client->voice_cbs.on_idle)(client, vc, &vc->p_client->gw.bot);
  }
  vc->is_ready = false;
}

static void *
start_voice_ws_thread(void *p_vc)
{
  struct discord_voice *vc = p_vc;

  /* handle ws reconnect/resume/redirect logic */
  while (vc->reconnect.attempt < vc->reconnect.threshold) {
    event_loop(vc);

    if (vc->is_redirect) {
      memcpy(vc->token, vc->new_token, sizeof(vc->token));
      ws_set_url(vc->ws, vc->new_url, NULL);
      vc->is_redirect = false;
      vc->reconnect.attempt = 0;
      vc->reconnect.enable = true;
      vc->is_resumable = false;
      continue;
    }

    if (!vc->reconnect.enable) {
      logconf_warn(&vc->conf, "Discord VC shutdown is complete");
      goto _end;
    }

    ++vc->reconnect.attempt;
    logconf_info(&vc->conf, "Reconnect attempt #%d", vc->reconnect.attempt);
  }

  if (!vc->shutdown)
    logconf_error(&vc->conf,
                  "Could not reconnect to Discord Voice after %d tries",
                  vc->reconnect.threshold);

  /* exit from the event loop; */
_end:
  reset_vc(vc);
  vc->guild_id = 0; /* put this back to the pool */
  return NULL;
}

/*
 * 1. join a vc -> create a new ws connection
 * 2. change voice region -> redirect an existing ws connection
 */
void
_discord_on_voice_server_update(struct discord *client,
                                u64_snowflake_t guild_id,
                                char *token,
                                char *endpoint)
{
  struct discord_voice *vc = NULL;
  pthread_mutex_lock(&client_lock);

  int i;
  for (i = 0; i < DISCORD_MAX_VOICE_CONNECTIONS; ++i) {
    if (guild_id == client->vcs[i].guild_id) {
      vc = client->vcs + i;
      break;
    }
  }

  pthread_mutex_unlock(&client_lock);
  if (!vc) {
    logconf_fatal(client->conf, "Couldn't match voice server to client");
    return;
  }

  int ret;
  ret = snprintf(vc->new_token, sizeof(vc->new_token), "%s", token);
  ASSERT_S(ret < sizeof(vc->new_token), "Out of bounds write attempt");
  ret = snprintf(vc->new_url, sizeof(vc->new_url),
                 "wss://%s" DISCORD_VOICE_CONNECTIONS_URL_SUFFIX, endpoint);
  ASSERT_S(ret < sizeof(vc->new_url), "Out of bounds write attempt");

  /* @todo: replace with the more reliable thread alive check */
  if (ws_is_alive(vc->ws)) {
    /* exits the current event_loop to redirect */
    vc->is_redirect = true;
    ws_close(vc->ws, WS_CLOSE_REASON_NORMAL, "", 0);
  }
  else {
    memcpy(vc->token, vc->new_token, sizeof(vc->new_token));
    ws_set_url(vc->ws, vc->new_url, NULL);

    /** @todo replace with a threadpool */
    pthread_t tid;
    if (pthread_create(&tid, NULL, &start_voice_ws_thread, vc))
      ERR("Couldn't create thread");
    if (pthread_detach(tid)) ERR("Couldn't detach thread");
  }
}

static void
noop_voice_state_update_cb(struct discord *a,
                           const struct discord_user *b,
                           const struct discord_voice_state *c)
{
  return;
}
static void
noop_voice_server_update_cb(struct discord *a,
                            const struct discord_user *b,
                            const char *c,
                            const u64_snowflake_t d,
                            const char *endpoint)
{
  return;
}
static void
noop_idle_cb(struct discord *a,
             struct discord_voice *b,
             const struct discord_user *c)
{
  return;
}
static void
noop_on_speaking(struct discord *a,
                 struct discord_voice *b,
                 const struct discord_user *c,
                 const u64_snowflake_t d,
                 const int e,
                 const int f,
                 const int g)
{
  return;
}
static void
noop_on_voice_client_disconnect(struct discord *a,
                                struct discord_voice *b,
                                const struct discord_user *c,
                                const u64_snowflake_t d)
{
  return;
}
static void
noop_on_voice_codec(struct discord *a,
                    struct discord_voice *b,
                    const struct discord_user *c,
                    const char d[],
                    const char e[])
{
  return;
}
static void
noop_on_ready(struct discord_voice *a)
{
  return;
}
static void
noop_on_session_descriptor(struct discord_voice *a)
{
  return;
}
static void
noop_on_udp_server_connected(struct discord_voice *a)
{
  return;
}

void
discord_voice_connections_init(struct discord *client)
{
  client->gw.user_cmd->cbs.on_voice_state_update = noop_voice_state_update_cb;
  client->gw.user_cmd->cbs.on_voice_server_update =
    noop_voice_server_update_cb;

  client->voice_cbs.on_idle = noop_idle_cb;
  client->voice_cbs.on_ready = noop_on_ready;
  client->voice_cbs.on_client_disconnect = noop_on_voice_client_disconnect;
  client->voice_cbs.on_session_descriptor = noop_on_session_descriptor;
  client->voice_cbs.on_codec = noop_on_voice_codec;
  client->voice_cbs.on_speaking = noop_on_speaking;
  client->voice_cbs.on_udp_server_connected = noop_on_udp_server_connected;

  int i;
  for (i = 0; i < DISCORD_MAX_VOICE_CONNECTIONS; ++i) {
    client->vcs[i].p_voice_cbs = &client->voice_cbs;
  }
}

void
discord_voice_shutdown(struct discord_voice *vc)
{
  vc->reconnect.enable = false;
  vc->is_resumable = false;
  vc->shutdown = true;
  ws_close(vc->ws, WS_CLOSE_REASON_NORMAL, "", 0);

  send_voice_state_update(vc, vc->guild_id, 0, false, false);
}

void
discord_voice_reconnect(struct discord_voice *vc, bool resume)
{
  vc->reconnect.enable = true;
  vc->is_resumable = resume;
  ws_close(vc->ws, WS_CLOSE_REASON_NORMAL, "", 0);
}

bool
discord_voice_is_alive(struct discord_voice *vc)
{
  return vc->guild_id && ws_is_alive(vc->ws);
}
