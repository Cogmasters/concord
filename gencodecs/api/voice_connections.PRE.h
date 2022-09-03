/*****************************************************************************
 * Voice Connections Datatypes
 * **************************************************************************/

/** @defgroup DiscordVoiceSpeakingFlags Voice speaking flags
 * @ingroup DiscordConstants
 *  @{ */

/** Normal transmission of voice audio */
PP_DEFINE(DISCORD_VOICE_MICROPHONE 1 << 0)
/** Transmission of context audio for video, no speaking indicators */
PP_DEFINE(DISCORD_VOICE_SOUNDSHARE 1 << 1)
/** Priority speaker, lowering audio of other speakers */
PP_DEFINE(DISCORD_VOICE_PRIORITY 1 << 2)

/** @} DiscordVoiceSpeakingFlags */

#if GENCODECS_RECIPE == DATA
ENUM(discord_voice_close_opcodes)
  /** You sent an invalid opcode */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_UNKNOWN_OPCODE, = 4001)
  /** You sent a invalid payload in your identifying to the Gateway */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_DECODE_ERROR, = 4002)
  /** You sent a payload before identifying with the gateway */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_NOT_AUTHENTICATED, = 4003)
  /** The token you sent in your identify payload is incorrect */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_AUTHENTICATION_FAILED, = 4004)
  /** You sent more than one identify payload */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_ALREADY_AUTHENTICATED, = 4005)
  /** Your session is no longer validd */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_INVALID_SESSION, = 4006)
  /** Your session has timed out */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_SESSION_TIMED_OUT, = 4009)
  /** Discord can't find the server you're trying to connect to */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_SERVER_NOT_FOUND, = 4011)
  /** Discord didn't recognize the protocol you sent */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_UNKNOWN_PROTOCOL, = 4012)
  /** Channel was deleted, you were kicked, voice server changed, or the main
       gateway session was dropped; should not reconnect */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_DISCONNECTED, = 4014)
  /** The server crashed, try resuming */
    ENUMERATOR(DISCORD_VOICE_CLOSE_REASON_SERVER_CRASH, = 4015)
  /** Discord didn't recognize the encryption */
    ENUMERATOR_LAST(DISCORD_VOICE_CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE, = 4016)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_voice_opcodes)
  /** Begin a voice websocket connection */
    ENUMERATOR(DISCORD_VOICE_IDENTIFY, = 0)
  /** Select the voice protocol */
    ENUMERATOR(DISCORD_VOICE_SELECT_PROTOCOL, = 1)
  /** Complete the websocket handshake */
    ENUMERATOR(DISCORD_VOICE_READY, = 2)
  /** Keep the websocket connection alive */
    ENUMERATOR(DISCORD_VOICE_HEARTBEAT, = 3)
  /** Describe the session */
    ENUMERATOR(DISCORD_VOICE_SESSION_DESCRIPTION, = 4)
  /** Indicate which users are speaking */
    ENUMERATOR(DISCORD_VOICE_SPEAKING, = 5)
  /** Sent to acknowledge a received client heartbeat */
    ENUMERATOR(DISCORD_VOICE_HEARTBEAT_ACK, = 6)
  /** Resume a connection */
    ENUMERATOR(DISCORD_VOICE_RESUME, = 7)
  /** Time to wait between sending heartbeats in milliseconds */
    ENUMERATOR(DISCORD_VOICE_HELLO, = 8)
  /** Acknowledge a successful session resume */
    ENUMERATOR(DISCORD_VOICE_RESUMED, = 9)
  /** A client has disconnected from the voice channel */
    ENUMERATOR(DISCORD_VOICE_CLIENT_DISCONNECT, = 13)
    ENUMERATOR_LAST(DISCORD_VOICE_CODEC, = 14)
ENUM_END
#endif
