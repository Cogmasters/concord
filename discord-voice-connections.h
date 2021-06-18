#ifndef DISCORD_VOICE_CONNECTIONS_H
#define DISCORD_VOICE_CONNECTIONS_H

#include <time.h>
#include <pthread.h>
#include "cee-data-sizes.h"

struct discord_voice; //forward

/**
 * @brief Idle callback
 *
 * Runs on every WebSockets loop iteration, no trigger required
 * @see discord_set_voice_cbs()
 */
typedef void (voice_idle_cb)(
  struct discord *client,
  struct discord_voice *vc,
  const struct discord_user *bot);

/**
 * @brief Voice Speaking callback
 *
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @see discord_set_voice_cbs()
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
 * @brief Voice Client Disconnect callback
 *
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @see discord_set_voice_cbs()
 */
typedef void (voice_client_disconnect_cb)(
    struct discord *client,
    struct discord_voice *vc,
    const struct discord_user *bot,
    const u64_snowflake_t user_id);

/**
 * @brief Voice Codec callback
 *
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @see discord_set_voice_cbs()
 */
typedef void (voice_codec_cb)(
    struct discord *client,
    struct discord_voice *vc,
    const struct discord_user *bot,
    const char audio_codec[],
    const char video_codec[]);


struct discord_voice_cbs { /* CALLBACKS STRUCTURE */
  voice_idle_cb  *on_idle; /**< triggers on every event loop iteration */
  voice_speaking_cb *on_speaking; /**< triggers when a user start speaking */
  voice_client_disconnect_cb *on_client_disconnect; /**< triggers when a user has disconnected from the voice channel */
  voice_codec_cb *on_codec; /**< triggers when a codec is received */

  void (*on_ready)(struct discord_voice *vc);
  void (*on_session_descriptor)(struct discord_voice *vc);
  void (*on_udp_server_connected)(struct discord_voice *vc);
};
/**
 * @brief Discord Voice Connection handle, contain information
 *        about its active session.
 *
 * @note @var discord_voice are reused on a guild basis, because there can
 *        be only one active @var discord_voice session per guild.
 * @see discord_join_vc()
 * @see discord_voice_get_vc()
 */
struct discord_voice {
  u64_snowflake_t guild_id; /**< the session guild id @note obtained from discord_join_vc() */
  u64_snowflake_t channel_id; /**< the session channel id @note obtained from discord_join_vc() */
  /// @note obtained from on_voice_server_update()
  char token[128]; /**< the session token @note obtained from on_voice_server_update() */
  char new_token[128]; /**< the new session token after a voice region change @note obtained from on_voice_server_update() */
  char new_url[512]; /**< the new url after a voice region change @note obtained from on_voice_server_update() */

  /// @note obtained from on_voice_state_update()
  char session_id[128]; /**< the session id @note obtained from on_voice_state_update() */
  u64_snowflake_t bot_id; /**< the bot user id @note obtained from on_voice_state_update() */
  struct websockets *ws; /**< the websockets handle that binds to Discord Voice Connections */
  /// @brief handle reconnect logic
  struct { /* RECONNECT STRUCTURE */
    bool enable; /**< will attempt reconnecting if true */
    unsigned char attempt; /**< current reconnect attempt (resets to 0 when succesful) */
    unsigned char threshold; /**< max amount of reconnects before giving up */
  } reconnect;
  bool is_resumable; /**< will attempt to resume session if connection shutsdown */

  bool is_redirect; /**< redirect to a different voice server */
  bool is_ready; /**< can start sending/receiving additional events to discord */

  /**
   * @see https://discord.com/developers/docs/topics/voice-connections#establishing-a-voice-websocket-connection-example-voice-ready-payload
   */
  struct { /* VOICE PAYLOAD STRUCTURE */
    enum discord_voice_opcodes opcode; /**<field 'op' */
    struct sized_buffer event_data; /**<field 'd' */
  } payload;

  struct { /* HEARTBEAT STRUCTURE */
    u64_unix_ms_t interval_ms; /**<fixed interval between heartbeats */
    u64_unix_ms_t tstamp; /**<start pulse timestamp in milliseconds */
  } hbeat;

  int ping_ms; /**< latency between client and websockets server, calculated by the interval between HEARTBEAT and HEARTBEAT_ACK */

  struct discord *p_client; /**< pointer to client this struct is part of */

  bool shutdown; /**< if #true shutdown websockets connection as soon as possible */

  struct {
    int ssrc;
    int server_port;
    char server_ip[CEE_MAX_IP_ADDR_STR_LEN];
    char digest[CEE_SHA1_STR_LEN];
    char unique_key[128];
    int audio_udp_pid;
    uintmax_t start_time;
  } udp_service;

  struct discord_voice_cbs *p_voice_cbs;

  uint64_t  message_channel_id; /**< used to communicate the status of the bot state changes */

  /**
   * @brief Interval to divide the received packets
   *
   * 0 store in one file
   * n store packets received every n minutes in a new file
   */
  int recv_interval;
};

/**
 * @brief Set a callback that triggers at every event-loop iteration.
 *
 * @param vc the VC obtained with discord_join_vc()
 * @param callback the callback that will be executed
 */
void discord_voice_set_on_idle(struct discord_voice *vc, voice_idle_cb *callback);

enum discord_join_vc_status {
  DISCORD_JOIN_VC_ERROR = 0,
  DISCORD_JOIN_VC_JOINED = 1,
  DISCORD_JOIN_VC_EXHAUST_CAPACITY,
  DISCORD_JOIN_VC_ALREADY_JOINED
};

/**
 * @brief Send a Voice State Update to Discord
 *
 * Necessary to connect to the voice server. When succesful a new voice connection instance will start
 * @param client the client created with discord_init()
 * @param guild_id the guild that houses the voice channel
 * @param channel_id the voice channel the client wants to connect to
 * @param self_mute #true will join as mute 
 * @param self_deaf #true will join as deaf 
 * @return a enum value of how the connection went
 */
enum discord_join_vc_status discord_join_vc(
  struct discord *client,
  struct discord_message *msg,
  u64_snowflake_t guild_id,
  u64_snowflake_t channel_id,
  bool self_mute,
  bool self_deaf);

/**
 * @brief Notify clients that you are speaking or have stopped speaking.
 * @param vc the VC obtained with discord_join_vc()
 * @param flag @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @param delay Should be set to 0. https://github.com/discord/discord-api-docs/issues/859#issuecomment-466602485
 */
void discord_send_speaking(struct discord_voice *vc, enum discord_voice_speaking_flags flag, int delay);

/**
 * @brief Update the voice session with a new session_id
 * 
 * @param client the client created with discord_init()
 * @param the voice state that has been updated
 * @todo move to discord-internal.h
 */
void _discord_on_voice_state_update(struct discord *client, struct discord_voice_state *vs);

/**
 * @brief Update the voice session with a new token and url
 * 
 * @param client the client created with discord_init()
 * @param guild_id the guild that houses the voice channel
 * @param token the unique token identifier
 * @param endpoint unique wss url received
 *        @note will prepend it with "wss://" and append with "?v=4"
 * @todo move to discord-internal.h
 */
void _discord_on_voice_server_update(struct discord *client, u64_snowflake_t guild_id, char token[], char endpoint[]);

/**
 * @brief Gracefully exits a ongoing Discord Voice connection
 * 
 * @param vc the VC obtained with discord_join_vc()
 * @note Wraps around ws_set_action()
 * @see websockets.h
 */
void discord_voice_shutdown(struct discord_voice *vc);

/**
 * @brief Gracefully reconnect a ongoing Discord Voice connection
 * 
 * @param vc the VC obtained with discord_join_vc()
 * @param resume #TRUE to attempt to resume to previous session,
 *        #FALSE restart a fresh session
 * @note Wraps around ws_set_action()
 * @see websockets.h
 */
void discord_voice_reconnect(struct discord_voice *vc, bool resume);

/**
 * Check if a Discord Voice connection is alive
 *
 * @return #TRUE if WebSockets status is different than
 *        WS_DISCONNECTED, #FALSE otherwise.
 */
bool discord_voice_is_alive(struct discord_voice *vc);

/**
 * @brief Initialize the fields of a Discord Voice Connections handle
 *
 * @param client the client created with discord_init()
 */
void discord_voice_connections_init(struct discord *client);

#endif // DISCORD_VOICE_CONNECTIONS_H
