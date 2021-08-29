/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */
/**
 * @file specs-code/discord/voice-connections.c
 * @see https://discord.com/developers/docs/topics/voice-connections
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"


enum discord_voice_close_opcodes discord_voice_close_opcodes_eval(char *s){
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
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_voice_close_opcodes_print(enum discord_voice_close_opcodes v){

  switch (v) {
  case DISCORD_VOICE_CLOSE_REASON_UNKNOWN_OPCODE: return "CLOSE_REASON_UNKNOWN_OPCODE";
  case DISCORD_VOICE_CLOSE_REASON_DECODE_ERROR: return "CLOSE_REASON_DECODE_ERROR";
  case DISCORD_VOICE_CLOSE_REASON_NOT_AUTHENTICATED: return "CLOSE_REASON_NOT_AUTHENTICATED";
  case DISCORD_VOICE_CLOSE_REASON_AUTHENTICATION_FAILED: return "CLOSE_REASON_AUTHENTICATION_FAILED";
  case DISCORD_VOICE_CLOSE_REASON_ALREADY_AUTHENTICATED: return "CLOSE_REASON_ALREADY_AUTHENTICATED";
  case DISCORD_VOICE_CLOSE_REASON_INVALID_SESSION: return "CLOSE_REASON_INVALID_SESSION";
  case DISCORD_VOICE_CLOSE_REASON_SESSION_TIMED_OUT: return "CLOSE_REASON_SESSION_TIMED_OUT";
  case DISCORD_VOICE_CLOSE_REASON_SERVER_NOT_FOUND: return "CLOSE_REASON_SERVER_NOT_FOUND";
  case DISCORD_VOICE_CLOSE_REASON_UNKNOWN_PROTOCOL: return "CLOSE_REASON_UNKNOWN_PROTOCOL";
  case DISCORD_VOICE_CLOSE_REASON_DISCONNECTED: return "CLOSE_REASON_DISCONNECTED";
  case DISCORD_VOICE_CLOSE_REASON_SERVER_CRASH: return "CLOSE_REASON_SERVER_CRASH";
  case DISCORD_VOICE_CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE: return "CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE";
  }

  return NULL;
}


enum discord_voice_opcodes discord_voice_opcodes_eval(char *s){
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
  if(strcasecmp("CODEC", s) == 0) return DISCORD_VOICE_CODEC;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_voice_opcodes_print(enum discord_voice_opcodes v){

  switch (v) {
  case DISCORD_VOICE_IDENTIFY: return "IDENTIFY";
  case DISCORD_VOICE_SELECT_PROTOCOL: return "SELECT_PROTOCOL";
  case DISCORD_VOICE_READY: return "READY";
  case DISCORD_VOICE_HEARTBEAT: return "HEARTBEAT";
  case DISCORD_VOICE_SESSION_DESCRIPTION: return "SESSION_DESCRIPTION";
  case DISCORD_VOICE_SPEAKING: return "SPEAKING";
  case DISCORD_VOICE_HEARTBEAT_ACK: return "HEARTBEAT_ACK";
  case DISCORD_VOICE_RESUME: return "RESUME";
  case DISCORD_VOICE_HELLO: return "HELLO";
  case DISCORD_VOICE_RESUMED: return "RESUMED";
  case DISCORD_VOICE_CLIENT_DISCONNECT: return "CLIENT_DISCONNECT";
  case DISCORD_VOICE_CODEC: return "CODEC";
  }

  return NULL;
}


enum discord_voice_speaking_flags discord_voice_speaking_flags_eval(char *s){
  if(strcasecmp("MICROPHONE", s) == 0) return DISCORD_VOICE_MICROPHONE;
  if(strcasecmp("SOUNDSHARE", s) == 0) return DISCORD_VOICE_SOUNDSHARE;
  if(strcasecmp("PRIORITY", s) == 0) return DISCORD_VOICE_PRIORITY;
  ERR("'%s' doesn't match any known enumerator.", s);
}
char* discord_voice_speaking_flags_print(enum discord_voice_speaking_flags v){

  switch (v) {
  case DISCORD_VOICE_MICROPHONE: return "MICROPHONE";
  case DISCORD_VOICE_SOUNDSHARE: return "SOUNDSHARE";
  case DISCORD_VOICE_PRIORITY: return "PRIORITY";
  }

  return NULL;
}
