/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */
/**
 * @file specs-code/discord/voice-connections.h
 * @author cee-studio
 * @date Jul 27 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/voice-connections
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
  DISCORD_VOICE_CODEC = 14,
};
extern char* discord_voice_opcodes_to_string(enum discord_voice_opcodes);
extern enum discord_voice_opcodes discord_voice_opcodes_from_string(char*);
extern bool discord_voice_opcodes_has(enum discord_voice_opcodes, char*);


enum discord_voice_speaking_flags {
  DISCORD_VOICE_MICROPHONE = 1, // 1 << 0
  DISCORD_VOICE_SOUNDSHARE = 2, // 1 << 1
  DISCORD_VOICE_PRIORITY = 4, // 1 << 2
};
extern char* discord_voice_speaking_flags_to_string(enum discord_voice_speaking_flags);
extern enum discord_voice_speaking_flags discord_voice_speaking_flags_from_string(char*);
extern bool discord_voice_speaking_flags_has(enum discord_voice_speaking_flags, char*);
