#ifndef DISCORD_VOICE_CONNECTIONS_H
#define DISCORD_VOICE_CONNECTIONS_H

#include <time.h>
#include <pthread.h>

struct discord_voice; //forward

/**
 * IDLE CALLBACK
 * @note runs on every WebSockets loop iteration, no trigger required
 * @see discord_voice_set_on_idle()
 */
typedef void (voice_idle_cb)(
  struct discord *client,
  struct discord_voice *vc,
  const struct discord_user *bot);

/**
 * VOICE SPEAKING CALLBACK
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @see discord_voice_set_on_speaking()
 */
typedef void (voice_speaking_cb)(
    struct discord *client,
    struct discord_voice *vc,
    const struct discord_user *bot,
    const u64_snowflake_t user_id,
    const int speaking,
    const int delay,
    const int ssrc);

/**
 * VOICE CLIENT DISCONNECT CALLBACK
 * @see discord_voice_set_on_client_disconnect()
 */
typedef void (voice_client_disconnect_cb)(
    struct discord *client,
    struct discord_voice *vc,
    const struct discord_user *bot,
    const u64_snowflake_t user_id);

/**
 * VOICE CODEC CALLBACK
 * @see discord_voice_set_on_codec()
 */
typedef void (voice_codec_cb)(
    struct discord *client,
    struct discord_voice *vc,
    const struct discord_user *bot,
    const char audio_codec[],
    const char video_codec[]);


struct discord_voice_cbs { /* CALLBACKS STRUCTURE */
  // triggers on every event loop iteration
  voice_idle_cb  *on_idle; /** @see discord_voice_set_on_idle() */

  // triggers when a user start speaking
  voice_speaking_cb *on_speaking; /** @see discord_voice_set_on_speaking() */
  // triggers when a user has disconnected from the voice channel
  voice_client_disconnect_cb *on_client_disconnect; /** @see discord_voice_set_on_client_disconnect() */
  // ? triggers when a codec is received
  voice_codec_cb *on_codec; /** @see discord_voice_set_on_codec() */

  void (*on_ready)(struct discord_voice *vc);
  void (*on_session_descriptor)(struct discord_voice *vc);
};
/**
 * The Discord Voice Connection structure, contain information
 *        correlating to its active session.
 *
 * @note VC structs are reused on a guild basis, because there can
 *        be only one active VC session per guild.
 * @see discord_join_vc()
 * @see discord_voice_get_vc()
 */
struct discord_voice {
  /// @note obtained from discord_join_vc()
  u64_snowflake_t guild_id;   // the session guild id
  u64_snowflake_t channel_id; // the session channel id
  /// @note obtained from on_voice_server_update()

  char token[128];            // the session token
  char new_token[128];        // the new session token after a voice region change
  char new_url[512];          // the new url after a voice region change

  /// @note obtained from on_voice_state_update()
  char session_id[128];       // the session id
  u64_snowflake_t bot_id;    // the bot user id
  // the websockets handle that connects to Discord
  struct websockets *ws;
  // handle reconnect logic
  struct { /* RECONNECT STRUCTURE */
    // will attempt reconnecting if true
    bool enable;
    // current reconnect attempt (resets to 0 when succesful)
    unsigned char attempt;
    // max amount of reconnects before giving up
    unsigned char threshold;
  } reconnect;
  // will attempt to resume session if connection shutsdown
  bool is_resumable;

  // redirect to a different voice server
  bool is_redirect;
  // can start sending/receiving additional events to discord
  bool is_ready;

  /// @see https://discord.com/developers/docs/topics/voice-connections#establishing-a-voice-websocket-connection-example-voice-ready-payload
  struct { /* VOICE PAYLOAD STRUCTURE */
    enum discord_voice_opcodes opcode;   //field 'op'
    struct sized_buffer event_data;      //field 'd'
  } payload;

  struct { /* HEARTBEAT STRUCTURE */
    //fixed interval between heartbeats
    u64_unix_ms_t interval_ms;
    //start pulse timestamp in milliseconds
    u64_unix_ms_t tstamp;
  } hbeat;

  //latency between client and websockets server
  /// @note calculated by interval response between HEARTBEAT and HEARTBEAT_ACK
  int ping_ms; /** @todo implement discord_voice_ping_ms() */

  // pointer to client this struct is part of
  struct discord *p_client;

  bool shutdown;

  struct {
    int ssrc;
    int server_port;
    char server_ip[128];

    char unique_key[128];
    int audio_udp_pid;
    time_t start_time;
  } udp_service;
};

/**
 * Set a callback that triggers despite any event being detected. It
 *        is triggered every discord_connect_vs_ws() event loop iteration.
 *
 * @param vc the VC obtained with discord_join_vc()
 * @param callback the callback to run when triggered at every event loop iteration
 */
void discord_voice_set_on_idle(struct discord_voice *vc, voice_idle_cb *callback);

/**
 * The following functions can be used to assign a user-callback to
 *        execute when its corresponding events are detected.
 *  
 * @param vc the VC obtained with discord_join_vc()
 * @param callback the callback to run when triggered by event
 */
 /*
void discord_voice_set_on_speaking(struct discord_voice *vc, voice_speaking_cb *callback);
void discord_voice_set_on_client_disconnect(struct discord_voice *vc, voice_client_disconnect_cb *callback);
void discord_voice_set_on_codec(struct discord_voice *vc, voice_codec_cb *callback);
void discord_voice_set_on_ready(struct discord_voice *vc, voice_idle_cb *callback);
void discord_voice_set_on_on_session_description(struct discord_voice *vc, voice_idle_cb *callback);
  */

/**
 * Send a Voice State Update to Discord, in order to connect to the
 *        voice server. When succesful @b p_vc will be assigned a VC handle
 * 
 * @todo Assign NULL to p_vc if a certain waiting for response timeout has been reach
 *
 * @param client the client created with discord_init()
 * @param guild_id the guild that houses the voice channel
 * @param channel_id the voice channel the client wants to connect to
 * @param self_mute #true will join as mute 
 * @param self_deaf #true will join as deaf 
 * @param p_vc will receive the VC struct once its done
 */
char* discord_join_vc (
  struct discord *client,
  u64_snowflake_t guild_id,
  u64_snowflake_t channel_id,
  bool self_mute,
  bool self_deaf);

/**
 * Notify clients that you are speaking or have stopped speaking.
 * 
 * @param vc the VC obtained with discord_join_vc()
 * @param flag @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @param ssrc the source of a stream of RTP packets (a identifier carried across RTP header)
 */
void discord_send_speaking(struct discord_voice *vc, enum discord_voice_speaking_flags flag, int delay, int ssrc);

/**
 * Update the voice session with a new session_id
 * 
 * @todo move to discord-voice-connections-internal.h (make it private)
 * 
 * @param client the client created with discord_init()
 * @param the voice state that has been updated
 */
void _discord_on_voice_state_update(struct discord *client, struct discord_voice_state *vs);

/**
 * Update the voice session with a new token and url
 * 
 * @todo move to discord-voice-connections-internal.h (make it private)
 * 
 * @param client the client created with discord_init()
 * @param guild_id the guild that houses the voice channel
 * @param token the unique token identifier
 * @param endpoint unique wss url received
 *        @note will prepend it with "wss://" and append with "?v=4"
 */
void _discord_on_voice_server_update(struct discord *client, u64_snowflake_t guild_id, char token[], char endpoint[]);

/**
 * Gracefully exits a ongoing Discord Voice connection over WebSockets
 * @note Wraps around ws_set_action()
 *        @see websockets.h
 * 
 * @param vc the VC obtained with discord_join_vc()
 */
void discord_voice_shutdown(struct discord_voice *vc);

/**
 * Gracefully reconnect a ongoing Discord Voice connection over WebSockets
 * @note Wraps around ws_set_action()
 *        @see websockets.h
 * 
 * @param vc the VC obtained with discord_join_vc()
 * @param resume #TRUE to attempt to resume to previous session,
 *        #FALSE restart a fresh session
 */
void discord_voice_reconnect(struct discord_voice *vc, bool resume);

/**
 * Check if a Discord Voice connection is alive
 *
 * @return #TRUE if WebSockets status is different than
 *        WS_DISCONNECTED, #FALSE otherwise.
 */
bool discord_voice_is_alive(struct discord_voice *vc);

void discord_voice_send_select_protocol(struct discord_voice *vc, char *ip, int port);

extern void discord_init_voice_cbs(struct discord_voice_cbs *cbs);

#endif // DISCORD_VOICE_CONNECTIONS_H
