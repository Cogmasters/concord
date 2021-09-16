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


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_voice_close_event_codes_list_free_v(void **p) {
  discord_voice_close_event_codes_list_free((enum discord_voice_close_event_codes**)p);
}

void discord_voice_close_event_codes_list_from_json_v(char *str, size_t len, void *p) {
  discord_voice_close_event_codes_list_from_json(str, len, (enum discord_voice_close_event_codes ***)p);
}

size_t discord_voice_close_event_codes_list_to_json_v(char *str, size_t len, void *p){
  return discord_voice_close_event_codes_list_to_json(str, len, (enum discord_voice_close_event_codes **)p);
}

enum discord_voice_close_event_codes discord_voice_close_event_codes_eval(char *s){
  if(strcasecmp("UNKNOWN_OPCODE", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_OPCODE;
  if(strcasecmp("DECODE_ERROR", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_DECODE_ERROR;
  if(strcasecmp("NOT_AUTHENTICATED", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_NOT_AUTHENTICATED;
  if(strcasecmp("AUTHENTICATION_FAILED", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_AUTHENTICATION_FAILED;
  if(strcasecmp("ALREADY_AUTHENTICATED", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_ALREADY_AUTHENTICATED;
  if(strcasecmp("INVALID_SESSION", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_INVALID_SESSION;
  if(strcasecmp("SESSION_TIMED_OUT", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_SESSION_TIMED_OUT;
  if(strcasecmp("SERVER_NOT_FOUND", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_SERVER_NOT_FOUND;
  if(strcasecmp("UNKNOWN_PROTOCOL", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_PROTOCOL;
  if(strcasecmp("DISCONNECTED", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_DISCONNECTED;
  if(strcasecmp("SERVER_CRASH", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_SERVER_CRASH;
  if(strcasecmp("UNKNOWN_ENCRYPTION_MODE", s) == 0) return DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_ENCRYPTION_MODE;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_voice_close_event_codes_print(enum discord_voice_close_event_codes v){

  switch (v) {
  case DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_OPCODE: return "UNKNOWN_OPCODE";
  case DISCORD_VOICE_CLOSE_EVENT_DECODE_ERROR: return "DECODE_ERROR";
  case DISCORD_VOICE_CLOSE_EVENT_NOT_AUTHENTICATED: return "NOT_AUTHENTICATED";
  case DISCORD_VOICE_CLOSE_EVENT_AUTHENTICATION_FAILED: return "AUTHENTICATION_FAILED";
  case DISCORD_VOICE_CLOSE_EVENT_ALREADY_AUTHENTICATED: return "ALREADY_AUTHENTICATED";
  case DISCORD_VOICE_CLOSE_EVENT_INVALID_SESSION: return "INVALID_SESSION";
  case DISCORD_VOICE_CLOSE_EVENT_SESSION_TIMED_OUT: return "SESSION_TIMED_OUT";
  case DISCORD_VOICE_CLOSE_EVENT_SERVER_NOT_FOUND: return "SERVER_NOT_FOUND";
  case DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_PROTOCOL: return "UNKNOWN_PROTOCOL";
  case DISCORD_VOICE_CLOSE_EVENT_DISCONNECTED: return "DISCONNECTED";
  case DISCORD_VOICE_CLOSE_EVENT_SERVER_CRASH: return "SERVER_CRASH";
  case DISCORD_VOICE_CLOSE_EVENT_UNKNOWN_ENCRYPTION_MODE: return "UNKNOWN_ENCRYPTION_MODE";
  }

  return NULL;
}

void discord_voice_close_event_codes_list_free(enum discord_voice_close_event_codes **p) {
  ntl_free((void**)p, NULL);
}

void discord_voice_close_event_codes_list_from_json(char *str, size_t len, enum discord_voice_close_event_codes ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_voice_close_event_codes);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_voice_close_event_codes_list_to_json(char *str, size_t len, enum discord_voice_close_event_codes **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_voice_opcodes_list_free_v(void **p) {
  discord_voice_opcodes_list_free((enum discord_voice_opcodes**)p);
}

void discord_voice_opcodes_list_from_json_v(char *str, size_t len, void *p) {
  discord_voice_opcodes_list_from_json(str, len, (enum discord_voice_opcodes ***)p);
}

size_t discord_voice_opcodes_list_to_json_v(char *str, size_t len, void *p){
  return discord_voice_opcodes_list_to_json(str, len, (enum discord_voice_opcodes **)p);
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

void discord_voice_opcodes_list_free(enum discord_voice_opcodes **p) {
  ntl_free((void**)p, NULL);
}

void discord_voice_opcodes_list_from_json(char *str, size_t len, enum discord_voice_opcodes ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_voice_opcodes);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_voice_opcodes_list_to_json(char *str, size_t len, enum discord_voice_opcodes **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_voice_speaking_flags_list_free_v(void **p) {
  discord_voice_speaking_flags_list_free((enum discord_voice_speaking_flags**)p);
}

void discord_voice_speaking_flags_list_from_json_v(char *str, size_t len, void *p) {
  discord_voice_speaking_flags_list_from_json(str, len, (enum discord_voice_speaking_flags ***)p);
}

size_t discord_voice_speaking_flags_list_to_json_v(char *str, size_t len, void *p){
  return discord_voice_speaking_flags_list_to_json(str, len, (enum discord_voice_speaking_flags **)p);
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

void discord_voice_speaking_flags_list_free(enum discord_voice_speaking_flags **p) {
  ntl_free((void**)p, NULL);
}

void discord_voice_speaking_flags_list_from_json(char *str, size_t len, enum discord_voice_speaking_flags ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_voice_speaking_flags);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_voice_speaking_flags_list_to_json(char *str, size_t len, enum discord_voice_speaking_flags **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}

