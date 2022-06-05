/**
 * @file discord-voice.h
 * @author Cogmasters
 * @brief Internal functions and datatypes for Voice Connections
 */

#ifndef DISCORD_VOICE_CONNECTIONS_H
#define DISCORD_VOICE_CONNECTIONS_H

#include <time.h>
#include <pthread.h>
#include <curl/curl.h>

struct discord_voice; /* forward declaration */

#define DISCORD_VCS_URL_SUFFIX "?v=4"

/* TODO: add to DiscordLimitsGeneral group */
#define DISCORD_MAX_VCS 512

/**
 * @brief Idle callback
 *
 * Runs on every WebSockets loop iteration, no trigger required
 * @see discord_set_voice_cbs()
 */
typedef void (*discord_ev_voice_idle)(struct discord *client,
                                      struct discord_voice *vc);

/**
 * @brief Voice Speaking callback
 *
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @see discord_set_voice_cbs()
 */
typedef void (*discord_ev_voice_speaking)(struct discord *client,
                                          struct discord_voice *vc,
                                          u64snowflake user_id,
                                          int speaking,
                                          int delay,
                                          int ssrc);

/**
 * @brief Voice Client Disconnect callback
 *
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @see discord_set_voice_cbs()
 */
typedef void (*discord_ev_voice_client_disconnect)(struct discord *client,
                                                   struct discord_voice *vc,
                                                   u64snowflake user_id);

/**
 * @brief Voice Codec callback
 *
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @see discord_set_voice_cbs()
 */
typedef void (*discord_ev_voice_codec)(struct discord *client,
                                       struct discord_voice *vc,
                                       const char audio_codec[],
                                       const char video_codec[]);

/* CALLBACKS STRUCTURE */
struct discord_voice_evcallbacks {
    /** triggers on every event loop iteration */
    discord_ev_voice_idle on_idle;
    /** triggers when a user start speaking */
    discord_ev_voice_speaking on_speaking;
    /** triggers when a user has disconnected from the voice channel */
    discord_ev_voice_client_disconnect on_client_disconnect;
    /** triggers when a codec is received */
    discord_ev_voice_codec on_codec;

    void (*on_ready)(struct discord_voice *vc);
    void (*on_session_descriptor)(struct discord_voice *vc);
    void (*on_udp_server_connected)(struct discord_voice *vc);
};
/**
 * @brief Discord Voice Connection handle, contain information
 *        about its active session.
 *
 * @note struct discord_voice are reused on a guild basis, because there can
 *        be only one active struct discord_voice session per guild.
 * @see discord_voice_join()
 * @see discord_voice_get_vc()
 */
struct discord_voice {
    /** `DISCORD_VOICE` logging module */
    struct logconf conf;
    /** the session guild id @note obtained from discord_voice_join() */
    u64snowflake guild_id;
    /** the session channel id @note obtained from discord_voice_join() */
    u64snowflake channel_id;
    /** @note obtained from on_voice_server_update() */
    /** the session token @note obtained from on_voice_server_update() */
    char token[128];
    /** the new session token after a voice region change @note obtained from
     * on_voice_server_update() */
    char new_token[128];
    /** the new url after a voice region change @note obtained from
     * on_voice_server_update() */
    char new_url[512];
    /** @note obtained from on_voice_state_update()
     * the session id @note obtained from on_voice_state_update() */
    char session_id[128];
    CURLM *mhandle;
    /** the websockets handle that binds to Discord Voice Connections */
    struct websockets *ws;

    /** @brief handle reconnect logic */
    /* reconnect structure */
    struct {
        /** will attempt reconnecting if true */
        bool enable;
        /** current reconnect attempt (resets to 0 when succesful) */
        unsigned char attempt;
        /** max amount of reconnects before giving up */
        unsigned char threshold;
    } reconnect;

    /** will attempt to resume session if connection shutsdown */
    bool is_resumable;
    /** redirect to a different voice server */
    bool is_redirect;
    /** can start sending/receiving additional events to discord */
    bool is_ready;

    /** current iteration JSON string data */
    char *json;
    /** current iteration JSON string data length */
    size_t length;

    /** parse JSON tokens into a `jsmnf_pairs` key/value pairs hashtable */
    struct {
        /** current iteration JSON key/value pairs */
        jsmnf_pair *pairs;
        /** current iteration number of JSON key/value pairs */
        unsigned npairs;
        /** current iteration JSON tokens (fed to `jsmnf_pair`) */
        jsmntok_t *tokens;
        /** current iteration number of JSON tokens */
        unsigned ntokens;
    } parse;

    /** voice payload structure */
    struct {
        /** field 'op' */
        enum discord_voice_opcodes opcode;
        /** field 'd' */
        jsmnf_pair *data;
    } payload;

    /** heartbeat structure */
    struct {
        /** fixed interval between heartbeats */
        u64unix_ms interval_ms;
        /** start pulse timestamp in milliseconds */
        u64unix_ms tstamp;
    } hbeat;

    /** latency between client and websockets server, calculated by the
     * interval between HEARTBEAT and HEARTBEAT_ACK */
    int ping_ms;

    /** if true shutdown websockets connection as soon as possible */
    bool shutdown;

    struct {
        int ssrc;
        int server_port;
        char server_ip[256];
        char digest[256];
        char unique_key[128];
        int audio_udp_pid;
        uintmax_t start_time;
    } udp_service;

    struct discord_voice_evcallbacks *p_voice_cbs;

    /**
     * @brief Interval to divide the received packets
     *
     * 0 store in one file
     * n store packets received every n minutes in a new file
     */
    int recv_interval;

    /** pointer to client this struct is part of */
    struct discord *p_client;
};

/**
 * @brief Set a callback that triggers at every event-loop iteration.
 *
 * @param vc the voice connection obtained with discord_voice_join()
 * @param callback the callback that will be executed
 */
void discord_voice_set_on_idle(struct discord_voice *vc,
                               discord_ev_voice_idle *callback);

enum discord_voice_status {
    DISCORD_VOICE_ERROR = 0,
    DISCORD_VOICE_JOINED,
    DISCORD_VOICE_EXHAUST_CAPACITY,
    DISCORD_VOICE_ALREADY_JOINED
};

/**
 * @brief Send a Voice State Update to Discord
 *
 * Necessary to connect to the voice server. When succesful a new voice
 * connection instance will start
 * @param client the client created with discord_init()
 * @param guild_id the guild that houses the voice channel
 * @param channel_id the voice channel the client wants to connect to
 * @param self_mute true will join as mute
 * @param self_deaf true will join as deaf
 * @return enum discord_voice_status value
 */
enum discord_voice_status discord_voice_join(struct discord *client,
                                             u64snowflake guild_id,
                                             u64snowflake channel_id,
                                             bool self_mute,
                                             bool self_deaf);

/**
 * @brief Notify clients that you are speaking or have stopped speaking.
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 * @see
 * https://github.com/discord/discord-api-docs/issues/859#issuecomment-466602485
 *
 * @param vc the voice client created at discord_voice_join()
 * @param flags @ref DiscordVoiceSpeakingFlags
 * @param delay should be set to 0.
 */
void discord_send_speaking(struct discord_voice *vc,
                           u64bitmask flags,
                           int delay);

/**
 * @brief Update the voice session with a new session_id
 *
 * @param client the client created with discord_init()
 * @param event the voice state that has been updated
 * @todo move to discord-internal.h
 */
void _discord_on_voice_state_update(struct discord *client,
                                    struct discord_voice_state *event);

/**
 * @brief Update the voice session with a new token and url
 *
 * @param client the client created with discord_init()
 * @param event the event contents for server update
 * @note will prepend with "wss://" and append with "?v=4"
 */
void _discord_on_voice_server_update(
    struct discord *client, struct discord_voice_server_update *event);

/**
 * @brief Gracefully exits a ongoing Discord Voice connection
 *
 * @param vc the voice connection obtained with discord_voice_join()
 * @note Wraps around ws_set_action()
 * @see websockets.h
 */
void discord_voice_shutdown(struct discord_voice *vc);

/**
 * @brief Gracefully reconnect a ongoing Discord Voice connection
 *
 * @param vc the voice connection obtained with discord_voice_join()
 * @param resume true to attempt to resume to previous session,
 *        false reconnect to a fresh session
 * @note Helper around ws_set_action()
 * @see websockets.h
 */
void discord_voice_reconnect(struct discord_voice *vc, bool resume);

/**
 * @brief Helper to quickly set voice callbacks
 *
 * @param client the client created with discord_init()
 * @param callbacks the voice callbacks that will be executed
 */
void discord_set_voice_cbs(struct discord *client,
                           struct discord_voice_evcallbacks *callbacks);

/**
 * @brief Check if a Discord Voice connection is alive
 *
 * @param vc the voice connection obtained with discord_voice_join()
 * @return true if WebSockets status is different than
 *        WS_DISCONNECTED, false otherwise.
 */
bool discord_voice_is_alive(struct discord_voice *vc);

/**
 * @brief Initialize the fields of a Discord Voice Connections handle
 *
 * @param client the client created with discord_init()
 */
void discord_voice_connections_init(struct discord *client);

/**
 * @brief Cleanup the fields of a Discord Voice Connections handle
 *
 * @param client the client created with discord_init()
 */
void discord_voice_connections_cleanup(struct discord *client);

#endif /* DISCORD_VOICE_CONNECTIONS_H */
