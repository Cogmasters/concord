/* This file is generated from specs/voice-connections.json, Please don't edit it. */
/*
(null)
*/


enum discord_voice_close_opcodes {
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_OPCODE = 4001,
  DISCORD_VOICE_CLOSE_REASON_DECODE_ERROR = 4002,
  DISCORD_VOICE_CLOSE_REASON_NOT_AUTHENTICATED = 4003,
  DISCORD_VOICE_CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  DISCORD_VOICE_CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  DISCORD_VOICE_CLOSE_REASON_INVALID_SESSION = 4006,
  DISCORD_VOICE_CLOSE_REASON_SESSION_TIMED_OUT = 4009,
  DISCORD_VOICE_CLOSE_REASON_SERVER_NOT_FOUND = 4011,
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_PROTOCOL = 4012,
  DISCORD_VOICE_CLOSE_REASON_DISCONNECTED = 4014,
  DISCORD_VOICE_CLOSE_REASON_SERVER_CRASH = 4015,
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE = 4016,
};
extern char* discord_voice_close_opcodes_to_string(enum discord_voice_close_opcodes);
extern enum discord_voice_close_opcodes discord_voice_close_opcodes_from_string(char*);
extern bool discord_voice_close_opcodes_has(enum discord_voice_close_opcodes, char*);


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
};
extern char* discord_voice_opcodes_to_string(enum discord_voice_opcodes);
extern enum discord_voice_opcodes discord_voice_opcodes_from_string(char*);
extern bool discord_voice_opcodes_has(enum discord_voice_opcodes, char*);
