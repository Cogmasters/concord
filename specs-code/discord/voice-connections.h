/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */
/**
 * @file specs-code/discord/voice-connections.h
 * @see https://discord.com/developers/docs/topics/voice-connections
 */



/* Voice Close Event Codes */
/* defined at specs/discord/voice-connections.json:6:5 */
/**
 * @see https://discord.com/developers/docs/topics/opcodes-and-status-codes#voice-voice-close-event-codes
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_voice_close_event_codes_print(enum discord_voice_close_event_codes code)`
 *   * :code:`enum discord_voice_close_event_codes discord_voice_close_event_codes_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_voice_close_event_codes {
  DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_OPCODE = 4001,
  DISCORD_VOICE_CLOSE_EVENT_DECODE_ERROR = 4002,
  DISCORD_VOICE_CLOSE_EVENT_NOT_AUTHENTICATED = 4003,
  DISCORD_VOICE_CLOSE_EVENT_AUTHENTICATION_FAILED = 4004,
  DISCORD_VOICE_CLOSE_EVENT_ALREADY_AUTHENTICATED = 4005,
  DISCORD_VOICE_CLOSE_EVENT_INVALID_SESSION = 4006,
  DISCORD_VOICE_CLOSE_EVENT_SESSION_TIMED_OUT = 4009,
  DISCORD_VOICE_CLOSE_EVENT_SERVER_NOT_FOUND = 4011,
  DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_PROTOCOL = 4012,
  DISCORD_VOICE_CLOSE_EVENT_DISCONNECTED = 4014,
  DISCORD_VOICE_CLOSE_EVENT_SERVER_CRASH = 4015,
  DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_ENCRYPTION_MODE = 4016,
};
extern char* discord_voice_close_event_codes_print(enum discord_voice_close_event_codes);
extern enum discord_voice_close_event_codes discord_voice_close_event_codes_eval(char*);
extern void discord_voice_close_event_codes_list_free_v(void **p);
extern void discord_voice_close_event_codes_list_free(enum discord_voice_close_event_codes **p);
extern void discord_voice_close_event_codes_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_close_event_codes_list_from_json(char *str, size_t len, enum discord_voice_close_event_codes ***p);
extern size_t discord_voice_close_event_codes_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_close_event_codes_list_to_json(char *str, size_t len, enum discord_voice_close_event_codes **p);


/* Voice Opcodes */
/* defined at specs/discord/voice-connections.json:27:5 */
/**
 * @see https://discord.com/developers/docs/topics/opcodes-and-status-codes#voice-voice-opcodes
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_voice_opcodes_print(enum discord_voice_opcodes code)`
 *   * :code:`enum discord_voice_opcodes discord_voice_opcodes_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_voice_opcodes {
  DISCORD_VOICE_IDENTIFY = 0,
  DISCORD_VOICE_SELECT_PROTOCOL = 1,
  DISCORD_VOICE_READY = 2,
  DISCORD_VOICE_HEARTBEAT = 3,
  DISCORD_VOICE_SESSION_DESCRIPTION = 4,
  DISCORD_VOICE_SPEAKING = 5,
  DISCORD_VOICE_HEARTBEAT_ACK = 6,
  DISCORD_VOICE_RESUME = 7,
  DISCORD_VOICE_HELLO = 8,
  DISCORD_VOICE_RESUMED = 9,
  DISCORD_VOICE_CLIENT_DISCONNECT = 13,
  DISCORD_VOICE_CODEC = 14,
};
extern char* discord_voice_opcodes_print(enum discord_voice_opcodes);
extern enum discord_voice_opcodes discord_voice_opcodes_eval(char*);
extern void discord_voice_opcodes_list_free_v(void **p);
extern void discord_voice_opcodes_list_free(enum discord_voice_opcodes **p);
extern void discord_voice_opcodes_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_opcodes_list_from_json(char *str, size_t len, enum discord_voice_opcodes ***p);
extern size_t discord_voice_opcodes_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_opcodes_list_to_json(char *str, size_t len, enum discord_voice_opcodes **p);


/* Voice Speaking Flags */
/* defined at specs/discord/voice-connections.json:48:5 */
/**
 * @see https://discord.com/developers/docs/topics/voice-connections#speaking
 *
 * @verbatim embed:rst:leading-asterisk
 * .. container:: toggle

 *   .. container:: header

 *     **Methods**

 *   * :code:`char* discord_voice_speaking_flags_print(enum discord_voice_speaking_flags code)`
 *   * :code:`enum discord_voice_speaking_flags discord_voice_speaking_flags_eval(char *code_as_str)`
 * @endverbatim
 */
enum discord_voice_speaking_flags {
  DISCORD_VOICE_MICROPHONE = 1, /**< 1 << 0 */
  DISCORD_VOICE_SOUNDSHARE = 2, /**< 1 << 1 */
  DISCORD_VOICE_PRIORITY = 4, /**< 1 << 2 */
};
extern char* discord_voice_speaking_flags_print(enum discord_voice_speaking_flags);
extern enum discord_voice_speaking_flags discord_voice_speaking_flags_eval(char*);
extern void discord_voice_speaking_flags_list_free_v(void **p);
extern void discord_voice_speaking_flags_list_free(enum discord_voice_speaking_flags **p);
extern void discord_voice_speaking_flags_list_from_json_v(char *str, size_t len, void *p);
extern void discord_voice_speaking_flags_list_from_json(char *str, size_t len, enum discord_voice_speaking_flags ***p);
extern size_t discord_voice_speaking_flags_list_to_json_v(char *str, size_t len, void *p);
extern size_t discord_voice_speaking_flags_list_to_json(char *str, size_t len, enum discord_voice_speaking_flags **p);
