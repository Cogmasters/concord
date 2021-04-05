/* This file is generated from specs/voice-connections.json, Please don't edit it. */
#include "specs.h"
/*
(null)
*/


enum discord_voice_close_opcodes discord_voice_close_opcodes_from_string(char *s){
  if(strcasecmp("CLOSE_REASON_UNKNOWN_OPCODE", s) == 0) return DISCORD_VOICE_CLOSE_REASON_UNKNOWN_OPCODE;
  if(strcasecmp("CLOSE_REASON_DECODE_ERROR", s) == 0) return DISCORD_VOICE_CLOSE_REASON_DECODE_ERROR;
  if(strcasecmp("CLOSE_REASON_NOT_AUTHENTICATED", s) == 0) return DISCORD_VOICE_CLOSE_REASON_NOT_AUTHENTICATED;
  if(strcasecmp("CLOSE_REASON_AUTHENTICATION_FAILED", s) == 0) return DISCORD_VOICE_CLOSE_REASON_AUTHENTICATION_FAILED;
  if(strcasecmp("CLOSE_REASON_ALREADY_AUTHENTICATED", s) == 0) return DISCORD_VOICE_CLOSE_REASON_ALREADY_AUTHENTICATED;
  if(strcasecmp("CLOSE_REASON_INVALID_SESSION", s) == 0) return DISCORD_VOICE_CLOSE_REASON_INVALID_SESSION;
  if(strcasecmp("CLOSE_REASON_SESSION_TIMED_OUT", s) == 0) return DISCORD_VOICE_CLOSE_REASON_SESSION_TIMED_OUT;
  if(strcasecmp("CLOSE_REASON_SERVER_NOT_FOUND", s) == 0) return DISCORD_VOICE_CLOSE_REASON_SERVER_NOT_FOUND;
  if(strcasecmp("CLOSE_REASON_UNKNOWN_PROTOCOL", s) == 0) return DISCORD_VOICE_CLOSE_REASON_UNKNOWN_PROTOCOL;
  if(strcasecmp("CLOSE_REASON_DISCONNECTED", s) == 0) return DISCORD_VOICE_CLOSE_REASON_DISCONNECTED;
  if(strcasecmp("CLOSE_REASON_SERVER_CRASH", s) == 0) return DISCORD_VOICE_CLOSE_REASON_SERVER_CRASH;
  if(strcasecmp("CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE", s) == 0) return DISCORD_VOICE_CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE;
  abort();
}
char* discord_voice_close_opcodes_to_string(enum discord_voice_close_opcodes v){
  if (v == DISCORD_VOICE_CLOSE_REASON_UNKNOWN_OPCODE) return "CLOSE_REASON_UNKNOWN_OPCODE";
  if (v == DISCORD_VOICE_CLOSE_REASON_DECODE_ERROR) return "CLOSE_REASON_DECODE_ERROR";
  if (v == DISCORD_VOICE_CLOSE_REASON_NOT_AUTHENTICATED) return "CLOSE_REASON_NOT_AUTHENTICATED";
  if (v == DISCORD_VOICE_CLOSE_REASON_AUTHENTICATION_FAILED) return "CLOSE_REASON_AUTHENTICATION_FAILED";
  if (v == DISCORD_VOICE_CLOSE_REASON_ALREADY_AUTHENTICATED) return "CLOSE_REASON_ALREADY_AUTHENTICATED";
  if (v == DISCORD_VOICE_CLOSE_REASON_INVALID_SESSION) return "CLOSE_REASON_INVALID_SESSION";
  if (v == DISCORD_VOICE_CLOSE_REASON_SESSION_TIMED_OUT) return "CLOSE_REASON_SESSION_TIMED_OUT";
  if (v == DISCORD_VOICE_CLOSE_REASON_SERVER_NOT_FOUND) return "CLOSE_REASON_SERVER_NOT_FOUND";
  if (v == DISCORD_VOICE_CLOSE_REASON_UNKNOWN_PROTOCOL) return "CLOSE_REASON_UNKNOWN_PROTOCOL";
  if (v == DISCORD_VOICE_CLOSE_REASON_DISCONNECTED) return "CLOSE_REASON_DISCONNECTED";
  if (v == DISCORD_VOICE_CLOSE_REASON_SERVER_CRASH) return "CLOSE_REASON_SERVER_CRASH";
  if (v == DISCORD_VOICE_CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE) return "CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE";

  abort();
}
bool discord_voice_close_opcodes_has(enum discord_voice_close_opcodes v, char *s) {
  enum discord_voice_close_opcodes v1 = discord_voice_close_opcodes_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}


enum discord_voice_opcodes discord_voice_opcodes_from_string(char *s){
  if(strcasecmp("IDENTIFY", s) == 0) return DISCORD_VOICE_IDENTIFY;
  if(strcasecmp("SELECT_PROTOCOL", s) == 0) return DISCORD_VOICE_SELECT_PROTOCOL;
  if(strcasecmp("READY", s) == 0) return DISCORD_VOICE_READY;
  if(strcasecmp("HEARTBEAT", s) == 0) return DISCORD_VOICE_HEARTBEAT;
  if(strcasecmp("SESSION_DESCRIPTION", s) == 0) return DISCORD_VOICE_SESSION_DESCRIPTION;
  if(strcasecmp("SPEAKING", s) == 0) return DISCORD_VOICE_SPEAKING;
  if(strcasecmp("HEARTBEAT_ACK", s) == 0) return DISCORD_VOICE_HEARTBEAT_ACK;
  if(strcasecmp("RESUME", s) == 0) return DISCORD_VOICE_RESUME;
  if(strcasecmp("HELLO", s) == 0) return DISCORD_VOICE_HELLO;
  if(strcasecmp("RESUMED", s) == 0) return DISCORD_VOICE_RESUMED;
  if(strcasecmp("CLIENT_DISCONNECT", s) == 0) return DISCORD_VOICE_CLIENT_DISCONNECT;
  abort();
}
char* discord_voice_opcodes_to_string(enum discord_voice_opcodes v){
  if (v == DISCORD_VOICE_IDENTIFY) return "IDENTIFY";
  if (v == DISCORD_VOICE_SELECT_PROTOCOL) return "SELECT_PROTOCOL";
  if (v == DISCORD_VOICE_READY) return "READY";
  if (v == DISCORD_VOICE_HEARTBEAT) return "HEARTBEAT";
  if (v == DISCORD_VOICE_SESSION_DESCRIPTION) return "SESSION_DESCRIPTION";
  if (v == DISCORD_VOICE_SPEAKING) return "SPEAKING";
  if (v == DISCORD_VOICE_HEARTBEAT_ACK) return "HEARTBEAT_ACK";
  if (v == DISCORD_VOICE_RESUME) return "RESUME";
  if (v == DISCORD_VOICE_HELLO) return "HELLO";
  if (v == DISCORD_VOICE_RESUMED) return "RESUMED";
  if (v == DISCORD_VOICE_CLIENT_DISCONNECT) return "CLIENT_DISCONNECT";

  abort();
}
bool discord_voice_opcodes_has(enum discord_voice_opcodes v, char *s) {
  enum discord_voice_opcodes v1 = discord_voice_opcodes_from_string(s);
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  if (v == v1) return true;
  return false;
}
