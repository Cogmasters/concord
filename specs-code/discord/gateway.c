/* This file is generated from discord/gateway.json, Please don't edit it. */
/**
 * @file specs-code/discord/gateway.c
 * @see https://discord.com/developers/docs/topics/gateway
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
void discord_gateway_close_opcodes_list_free_v(void **p) {
  discord_gateway_close_opcodes_list_free((enum discord_gateway_close_opcodes**)p);
}

void discord_gateway_close_opcodes_list_from_json_v(char *str, size_t len, void *p) {
  discord_gateway_close_opcodes_list_from_json(str, len, (enum discord_gateway_close_opcodes ***)p);
}

size_t discord_gateway_close_opcodes_list_to_json_v(char *str, size_t len, void *p){
  return discord_gateway_close_opcodes_list_to_json(str, len, (enum discord_gateway_close_opcodes **)p);
}

enum discord_gateway_close_opcodes discord_gateway_close_opcodes_eval(char *s){
  if(strcasecmp("CLOSE_REASON_UNKNOWN_ERROR", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR;
  if(strcasecmp("CLOSE_REASON_UNKNOWN_OPCODE", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE;
  if(strcasecmp("CLOSE_REASON_DECODE_ERROR", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR;
  if(strcasecmp("CLOSE_REASON_NOT_AUTHENTICATED", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED;
  if(strcasecmp("CLOSE_REASON_AUTHENTICATION_FAILED", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED;
  if(strcasecmp("CLOSE_REASON_ALREADY_AUTHENTICATED", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED;
  if(strcasecmp("CLOSE_REASON_INVALID_SEQUENCE", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE;
  if(strcasecmp("CLOSE_REASON_RATE_LIMITED", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED;
  if(strcasecmp("CLOSE_REASON_SESSION_TIMED_OUT", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT;
  if(strcasecmp("CLOSE_REASON_INVALID_SHARD", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD;
  if(strcasecmp("CLOSE_REASON_SHARDING_REQUIRED", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED;
  if(strcasecmp("CLOSE_REASON_INVALID_API_VERSION", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION;
  if(strcasecmp("CLOSE_REASON_INVALID_INTENTS", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS;
  if(strcasecmp("CLOSE_REASON_DISALLOWED_INTENTS", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS;
  if(strcasecmp("CLOSE_REASON_RECONNECT", s) == 0) return DISCORD_GATEWAY_CLOSE_REASON_RECONNECT;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_gateway_close_opcodes_print(enum discord_gateway_close_opcodes v){

  switch (v) {
  case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR: return "CLOSE_REASON_UNKNOWN_ERROR";
  case DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE: return "CLOSE_REASON_UNKNOWN_OPCODE";
  case DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR: return "CLOSE_REASON_DECODE_ERROR";
  case DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED: return "CLOSE_REASON_NOT_AUTHENTICATED";
  case DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED: return "CLOSE_REASON_AUTHENTICATION_FAILED";
  case DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED: return "CLOSE_REASON_ALREADY_AUTHENTICATED";
  case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE: return "CLOSE_REASON_INVALID_SEQUENCE";
  case DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED: return "CLOSE_REASON_RATE_LIMITED";
  case DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT: return "CLOSE_REASON_SESSION_TIMED_OUT";
  case DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD: return "CLOSE_REASON_INVALID_SHARD";
  case DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED: return "CLOSE_REASON_SHARDING_REQUIRED";
  case DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION: return "CLOSE_REASON_INVALID_API_VERSION";
  case DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS: return "CLOSE_REASON_INVALID_INTENTS";
  case DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS: return "CLOSE_REASON_DISALLOWED_INTENTS";
  case DISCORD_GATEWAY_CLOSE_REASON_RECONNECT: return "CLOSE_REASON_RECONNECT";
  }

  return NULL;
}

void discord_gateway_close_opcodes_list_free(enum discord_gateway_close_opcodes **p) {
  ntl_free((void**)p, NULL);
}

void discord_gateway_close_opcodes_list_from_json(char *str, size_t len, enum discord_gateway_close_opcodes ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_gateway_close_opcodes);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_gateway_close_opcodes_list_to_json(char *str, size_t len, enum discord_gateway_close_opcodes **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_gateway_intents_list_free_v(void **p) {
  discord_gateway_intents_list_free((enum discord_gateway_intents**)p);
}

void discord_gateway_intents_list_from_json_v(char *str, size_t len, void *p) {
  discord_gateway_intents_list_from_json(str, len, (enum discord_gateway_intents ***)p);
}

size_t discord_gateway_intents_list_to_json_v(char *str, size_t len, void *p){
  return discord_gateway_intents_list_to_json(str, len, (enum discord_gateway_intents **)p);
}

enum discord_gateway_intents discord_gateway_intents_eval(char *s){
  if(strcasecmp("GUILDS", s) == 0) return DISCORD_GATEWAY_GUILDS;
  if(strcasecmp("GUILD_MEMBERS", s) == 0) return DISCORD_GATEWAY_GUILD_MEMBERS;
  if(strcasecmp("GUILD_BANS", s) == 0) return DISCORD_GATEWAY_GUILD_BANS;
  if(strcasecmp("GUILD_EMOJIS", s) == 0) return DISCORD_GATEWAY_GUILD_EMOJIS;
  if(strcasecmp("GUILD_INTEGRATIONS", s) == 0) return DISCORD_GATEWAY_GUILD_INTEGRATIONS;
  if(strcasecmp("GUILD_WEBHOOKS", s) == 0) return DISCORD_GATEWAY_GUILD_WEBHOOKS;
  if(strcasecmp("GUILD_INVITES", s) == 0) return DISCORD_GATEWAY_GUILD_INVITES;
  if(strcasecmp("GUILD_VOICE_STATES", s) == 0) return DISCORD_GATEWAY_GUILD_VOICE_STATES;
  if(strcasecmp("GUILD_PRESENCES", s) == 0) return DISCORD_GATEWAY_GUILD_PRESENCES;
  if(strcasecmp("GUILD_MESSAGES", s) == 0) return DISCORD_GATEWAY_GUILD_MESSAGES;
  if(strcasecmp("GUILD_MESSAGE_REACTIONS", s) == 0) return DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS;
  if(strcasecmp("GUILD_MESSAGE_TYPING", s) == 0) return DISCORD_GATEWAY_GUILD_MESSAGE_TYPING;
  if(strcasecmp("DIRECT_MESSAGES", s) == 0) return DISCORD_GATEWAY_DIRECT_MESSAGES;
  if(strcasecmp("DIRECT_MESSAGE_REACTIONS", s) == 0) return DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS;
  if(strcasecmp("DIRECT_MESSAGE_TYPING", s) == 0) return DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_gateway_intents_print(enum discord_gateway_intents v){

  switch (v) {
  case DISCORD_GATEWAY_GUILDS: return "GUILDS";
  case DISCORD_GATEWAY_GUILD_MEMBERS: return "GUILD_MEMBERS";
  case DISCORD_GATEWAY_GUILD_BANS: return "GUILD_BANS";
  case DISCORD_GATEWAY_GUILD_EMOJIS: return "GUILD_EMOJIS";
  case DISCORD_GATEWAY_GUILD_INTEGRATIONS: return "GUILD_INTEGRATIONS";
  case DISCORD_GATEWAY_GUILD_WEBHOOKS: return "GUILD_WEBHOOKS";
  case DISCORD_GATEWAY_GUILD_INVITES: return "GUILD_INVITES";
  case DISCORD_GATEWAY_GUILD_VOICE_STATES: return "GUILD_VOICE_STATES";
  case DISCORD_GATEWAY_GUILD_PRESENCES: return "GUILD_PRESENCES";
  case DISCORD_GATEWAY_GUILD_MESSAGES: return "GUILD_MESSAGES";
  case DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS: return "GUILD_MESSAGE_REACTIONS";
  case DISCORD_GATEWAY_GUILD_MESSAGE_TYPING: return "GUILD_MESSAGE_TYPING";
  case DISCORD_GATEWAY_DIRECT_MESSAGES: return "DIRECT_MESSAGES";
  case DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS: return "DIRECT_MESSAGE_REACTIONS";
  case DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING: return "DIRECT_MESSAGE_TYPING";
  }

  return NULL;
}

void discord_gateway_intents_list_free(enum discord_gateway_intents **p) {
  ntl_free((void**)p, NULL);
}

void discord_gateway_intents_list_from_json(char *str, size_t len, enum discord_gateway_intents ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_gateway_intents);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_gateway_intents_list_to_json(char *str, size_t len, enum discord_gateway_intents **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_gateway_opcodes_list_free_v(void **p) {
  discord_gateway_opcodes_list_free((enum discord_gateway_opcodes**)p);
}

void discord_gateway_opcodes_list_from_json_v(char *str, size_t len, void *p) {
  discord_gateway_opcodes_list_from_json(str, len, (enum discord_gateway_opcodes ***)p);
}

size_t discord_gateway_opcodes_list_to_json_v(char *str, size_t len, void *p){
  return discord_gateway_opcodes_list_to_json(str, len, (enum discord_gateway_opcodes **)p);
}

enum discord_gateway_opcodes discord_gateway_opcodes_eval(char *s){
  if(strcasecmp("DISPATCH", s) == 0) return DISCORD_GATEWAY_DISPATCH;
  if(strcasecmp("HEARTBEAT", s) == 0) return DISCORD_GATEWAY_HEARTBEAT;
  if(strcasecmp("IDENTIFY", s) == 0) return DISCORD_GATEWAY_IDENTIFY;
  if(strcasecmp("PRESENCE_UPDATE", s) == 0) return DISCORD_GATEWAY_PRESENCE_UPDATE;
  if(strcasecmp("VOICE_STATE_UPDATE", s) == 0) return DISCORD_GATEWAY_VOICE_STATE_UPDATE;
  if(strcasecmp("RESUME", s) == 0) return DISCORD_GATEWAY_RESUME;
  if(strcasecmp("RECONNECT", s) == 0) return DISCORD_GATEWAY_RECONNECT;
  if(strcasecmp("REQUEST_GUILD_MEMBERS", s) == 0) return DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS;
  if(strcasecmp("INVALID_SESSION", s) == 0) return DISCORD_GATEWAY_INVALID_SESSION;
  if(strcasecmp("HELLO", s) == 0) return DISCORD_GATEWAY_HELLO;
  if(strcasecmp("HEARTBEAT_ACK", s) == 0) return DISCORD_GATEWAY_HEARTBEAT_ACK;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_gateway_opcodes_print(enum discord_gateway_opcodes v){

  switch (v) {
  case DISCORD_GATEWAY_DISPATCH: return "DISPATCH";
  case DISCORD_GATEWAY_HEARTBEAT: return "HEARTBEAT";
  case DISCORD_GATEWAY_IDENTIFY: return "IDENTIFY";
  case DISCORD_GATEWAY_PRESENCE_UPDATE: return "PRESENCE_UPDATE";
  case DISCORD_GATEWAY_VOICE_STATE_UPDATE: return "VOICE_STATE_UPDATE";
  case DISCORD_GATEWAY_RESUME: return "RESUME";
  case DISCORD_GATEWAY_RECONNECT: return "RECONNECT";
  case DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS: return "REQUEST_GUILD_MEMBERS";
  case DISCORD_GATEWAY_INVALID_SESSION: return "INVALID_SESSION";
  case DISCORD_GATEWAY_HELLO: return "HELLO";
  case DISCORD_GATEWAY_HEARTBEAT_ACK: return "HEARTBEAT_ACK";
  }

  return NULL;
}

void discord_gateway_opcodes_list_free(enum discord_gateway_opcodes **p) {
  ntl_free((void**)p, NULL);
}

void discord_gateway_opcodes_list_from_json(char *str, size_t len, enum discord_gateway_opcodes ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_gateway_opcodes);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_gateway_opcodes_list_to_json(char *str, size_t len, enum discord_gateway_opcodes **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_gateway_events_list_free_v(void **p) {
  discord_gateway_events_list_free((enum discord_gateway_events**)p);
}

void discord_gateway_events_list_from_json_v(char *str, size_t len, void *p) {
  discord_gateway_events_list_from_json(str, len, (enum discord_gateway_events ***)p);
}

size_t discord_gateway_events_list_to_json_v(char *str, size_t len, void *p){
  return discord_gateway_events_list_to_json(str, len, (enum discord_gateway_events **)p);
}

enum discord_gateway_events discord_gateway_events_eval(char *s){
  if(strcasecmp("EVENTS_NONE", s) == 0) return DISCORD_GATEWAY_EVENTS_NONE;
  if(strcasecmp("EVENTS_READY", s) == 0) return DISCORD_GATEWAY_EVENTS_READY;
  if(strcasecmp("EVENTS_RESUMED", s) == 0) return DISCORD_GATEWAY_EVENTS_RESUMED;
  if(strcasecmp("EVENTS_APPLICATION_COMMAND_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_CREATE;
  if(strcasecmp("EVENTS_APPLICATION_COMMAND_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_UPDATE;
  if(strcasecmp("EVENTS_APPLICATION_COMMAND_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_DELETE;
  if(strcasecmp("EVENTS_CHANNEL_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE;
  if(strcasecmp("EVENTS_CHANNEL_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE;
  if(strcasecmp("EVENTS_CHANNEL_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE;
  if(strcasecmp("EVENTS_CHANNEL_PINS_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE;
  if(strcasecmp("EVENTS_THREAD_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_THREAD_CREATE;
  if(strcasecmp("EVENTS_THREAD_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_THREAD_UPDATE;
  if(strcasecmp("EVENTS_THREAD_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_THREAD_DELETE;
  if(strcasecmp("EVENTS_THREAD_LIST_SYNC", s) == 0) return DISCORD_GATEWAY_EVENTS_THREAD_LIST_SYNC;
  if(strcasecmp("EVENTS_THREAD_MEMBER_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_THREAD_MEMBER_UPDATE;
  if(strcasecmp("EVENTS_THREAD_MEMBERS_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_THREAD_MEMBERS_UPDATE;
  if(strcasecmp("EVENTS_GUILD_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_CREATE;
  if(strcasecmp("EVENTS_GUILD_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_UPDATE;
  if(strcasecmp("EVENTS_GUILD_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_DELETE;
  if(strcasecmp("EVENTS_GUILD_BAN_ADD", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD;
  if(strcasecmp("EVENTS_GUILD_BAN_REMOVE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE;
  if(strcasecmp("EVENTS_GUILD_EMOJIS_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE;
  if(strcasecmp("EVENTS_GUILD_STICKERS_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_STICKERS_UPDATE;
  if(strcasecmp("EVENTS_GUILD_INTEGRATIONS_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE;
  if(strcasecmp("EVENTS_GUILD_MEMBER_ADD", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD;
  if(strcasecmp("EVENTS_GUILD_MEMBER_REMOVE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE;
  if(strcasecmp("EVENTS_GUILD_MEMBER_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE;
  if(strcasecmp("EVENTS_GUILD_MEMBERS_CHUNK", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_MEMBERS_CHUNK;
  if(strcasecmp("EVENTS_GUILD_ROLE_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE;
  if(strcasecmp("EVENTS_GUILD_ROLE_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE;
  if(strcasecmp("EVENTS_GUILD_ROLE_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE;
  if(strcasecmp("EVENTS_INTEGRATION_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_INTEGRATION_CREATE;
  if(strcasecmp("EVENTS_INTEGRATION_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_INTEGRATION_UPDATE;
  if(strcasecmp("EVENTS_INTEGRATION_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_INTEGRATION_DELETE;
  if(strcasecmp("EVENTS_INTERACTION_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_INTERACTION_CREATE;
  if(strcasecmp("EVENTS_INVITE_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_INVITE_CREATE;
  if(strcasecmp("EVENTS_INVITE_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_INVITE_DELETE;
  if(strcasecmp("EVENTS_MESSAGE_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE;
  if(strcasecmp("EVENTS_MESSAGE_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE;
  if(strcasecmp("EVENTS_MESSAGE_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE;
  if(strcasecmp("EVENTS_MESSAGE_DELETE_BULK", s) == 0) return DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK;
  if(strcasecmp("EVENTS_MESSAGE_REACTION_ADD", s) == 0) return DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD;
  if(strcasecmp("EVENTS_MESSAGE_REACTION_REMOVE", s) == 0) return DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE;
  if(strcasecmp("EVENTS_MESSAGE_REACTION_REMOVE_ALL", s) == 0) return DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL;
  if(strcasecmp("EVENTS_MESSAGE_REACTION_REMOVE_EMOJI", s) == 0) return DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI;
  if(strcasecmp("EVENTS_PRESENCE_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE;
  if(strcasecmp("EVENTS_STAGE_INSTANCE_CREATE", s) == 0) return DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_CREATE;
  if(strcasecmp("EVENTS_STAGE_INSTANCE_DELETE", s) == 0) return DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_DELETE;
  if(strcasecmp("EVENTS_STAGE_INSTANCE_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_UPDATE;
  if(strcasecmp("EVENTS_TYPING_START", s) == 0) return DISCORD_GATEWAY_EVENTS_TYPING_START;
  if(strcasecmp("EVENTS_USER_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_USER_UPDATE;
  if(strcasecmp("EVENTS_VOICE_STATE_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE;
  if(strcasecmp("EVENTS_VOICE_SERVER_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE;
  if(strcasecmp("EVENTS_WEBHOOKS_UPDATE", s) == 0) return DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_gateway_events_print(enum discord_gateway_events v){

  switch (v) {
  case DISCORD_GATEWAY_EVENTS_NONE: return "EVENTS_NONE";
  case DISCORD_GATEWAY_EVENTS_READY: return "EVENTS_READY";
  case DISCORD_GATEWAY_EVENTS_RESUMED: return "EVENTS_RESUMED";
  case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_CREATE: return "EVENTS_APPLICATION_COMMAND_CREATE";
  case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_UPDATE: return "EVENTS_APPLICATION_COMMAND_UPDATE";
  case DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_DELETE: return "EVENTS_APPLICATION_COMMAND_DELETE";
  case DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE: return "EVENTS_CHANNEL_CREATE";
  case DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE: return "EVENTS_CHANNEL_UPDATE";
  case DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE: return "EVENTS_CHANNEL_DELETE";
  case DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE: return "EVENTS_CHANNEL_PINS_UPDATE";
  case DISCORD_GATEWAY_EVENTS_THREAD_CREATE: return "EVENTS_THREAD_CREATE";
  case DISCORD_GATEWAY_EVENTS_THREAD_UPDATE: return "EVENTS_THREAD_UPDATE";
  case DISCORD_GATEWAY_EVENTS_THREAD_DELETE: return "EVENTS_THREAD_DELETE";
  case DISCORD_GATEWAY_EVENTS_THREAD_LIST_SYNC: return "EVENTS_THREAD_LIST_SYNC";
  case DISCORD_GATEWAY_EVENTS_THREAD_MEMBER_UPDATE: return "EVENTS_THREAD_MEMBER_UPDATE";
  case DISCORD_GATEWAY_EVENTS_THREAD_MEMBERS_UPDATE: return "EVENTS_THREAD_MEMBERS_UPDATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_CREATE: return "EVENTS_GUILD_CREATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_UPDATE: return "EVENTS_GUILD_UPDATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_DELETE: return "EVENTS_GUILD_DELETE";
  case DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD: return "EVENTS_GUILD_BAN_ADD";
  case DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE: return "EVENTS_GUILD_BAN_REMOVE";
  case DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE: return "EVENTS_GUILD_EMOJIS_UPDATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_STICKERS_UPDATE: return "EVENTS_GUILD_STICKERS_UPDATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE: return "EVENTS_GUILD_INTEGRATIONS_UPDATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD: return "EVENTS_GUILD_MEMBER_ADD";
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE: return "EVENTS_GUILD_MEMBER_REMOVE";
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE: return "EVENTS_GUILD_MEMBER_UPDATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_MEMBERS_CHUNK: return "EVENTS_GUILD_MEMBERS_CHUNK";
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE: return "EVENTS_GUILD_ROLE_CREATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE: return "EVENTS_GUILD_ROLE_UPDATE";
  case DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE: return "EVENTS_GUILD_ROLE_DELETE";
  case DISCORD_GATEWAY_EVENTS_INTEGRATION_CREATE: return "EVENTS_INTEGRATION_CREATE";
  case DISCORD_GATEWAY_EVENTS_INTEGRATION_UPDATE: return "EVENTS_INTEGRATION_UPDATE";
  case DISCORD_GATEWAY_EVENTS_INTEGRATION_DELETE: return "EVENTS_INTEGRATION_DELETE";
  case DISCORD_GATEWAY_EVENTS_INTERACTION_CREATE: return "EVENTS_INTERACTION_CREATE";
  case DISCORD_GATEWAY_EVENTS_INVITE_CREATE: return "EVENTS_INVITE_CREATE";
  case DISCORD_GATEWAY_EVENTS_INVITE_DELETE: return "EVENTS_INVITE_DELETE";
  case DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE: return "EVENTS_MESSAGE_CREATE";
  case DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE: return "EVENTS_MESSAGE_UPDATE";
  case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE: return "EVENTS_MESSAGE_DELETE";
  case DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK: return "EVENTS_MESSAGE_DELETE_BULK";
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD: return "EVENTS_MESSAGE_REACTION_ADD";
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE: return "EVENTS_MESSAGE_REACTION_REMOVE";
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL: return "EVENTS_MESSAGE_REACTION_REMOVE_ALL";
  case DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI: return "EVENTS_MESSAGE_REACTION_REMOVE_EMOJI";
  case DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE: return "EVENTS_PRESENCE_UPDATE";
  case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_CREATE: return "EVENTS_STAGE_INSTANCE_CREATE";
  case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_DELETE: return "EVENTS_STAGE_INSTANCE_DELETE";
  case DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_UPDATE: return "EVENTS_STAGE_INSTANCE_UPDATE";
  case DISCORD_GATEWAY_EVENTS_TYPING_START: return "EVENTS_TYPING_START";
  case DISCORD_GATEWAY_EVENTS_USER_UPDATE: return "EVENTS_USER_UPDATE";
  case DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE: return "EVENTS_VOICE_STATE_UPDATE";
  case DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE: return "EVENTS_VOICE_SERVER_UPDATE";
  case DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE: return "EVENTS_WEBHOOKS_UPDATE";
  }

  return NULL;
}

void discord_gateway_events_list_free(enum discord_gateway_events **p) {
  ntl_free((void**)p, NULL);
}

void discord_gateway_events_list_from_json(char *str, size_t len, enum discord_gateway_events ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_gateway_events);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_gateway_events_list_to_json(char *str, size_t len, enum discord_gateway_events **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_identify_from_json_p(char *json, size_t len, struct discord_identify **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_identify_from_json(json, len, *pp);
}
void discord_identify_from_json(char *json, size_t len, struct discord_identify *p)
{
  discord_identify_init(p);
  json_extract(json, len, 
  /* discord/gateway.json:143:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
                "(token):?s,"
  /* discord/gateway.json:144:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */
                "(properties):F,"
  /* discord/gateway.json:145:19
     '{ "name":"compress","type":{"base":"bool"}}' */
                "(compress):b,"
  /* discord/gateway.json:146:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
                "(large_threshold):d,"
  /* discord/gateway.json:147:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
                "(guild_subscriptions):b,"
  /* discord/gateway.json:148:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  /* discord/gateway.json:149:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */
                "(presence):F,"
  /* discord/gateway.json:150:19
     '{ "name":"intents","type":{"base":"int"}}' */
                "(intents):d,",
  /* discord/gateway.json:143:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
                &p->token,
  /* discord/gateway.json:144:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */
                discord_identify_connection_from_json_p, &p->properties,
  /* discord/gateway.json:145:19
     '{ "name":"compress","type":{"base":"bool"}}' */
                &p->compress,
  /* discord/gateway.json:146:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
                &p->large_threshold,
  /* discord/gateway.json:147:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
                &p->guild_subscriptions,
  /* discord/gateway.json:148:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  /* discord/gateway.json:149:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */
                discord_presence_status_from_json_p, &p->presence,
  /* discord/gateway.json:150:19
     '{ "name":"intents","type":{"base":"int"}}' */
                &p->intents);
}

size_t discord_identify_to_json(char *json, size_t len, struct discord_identify *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* discord/gateway.json:143:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
  arg_switches[0] = p->token;

  /* discord/gateway.json:144:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */
  arg_switches[1] = p->properties;

  /* discord/gateway.json:145:19
     '{ "name":"compress","type":{"base":"bool"}}' */
  arg_switches[2] = &p->compress;

  /* discord/gateway.json:146:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
  arg_switches[3] = &p->large_threshold;

  /* discord/gateway.json:147:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
  arg_switches[4] = &p->guild_subscriptions;

  /* discord/gateway.json:148:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */

  /* discord/gateway.json:149:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */
  arg_switches[6] = p->presence;

  /* discord/gateway.json:150:19
     '{ "name":"intents","type":{"base":"int"}}' */
  arg_switches[7] = &p->intents;

  r=json_inject(json, len, 
  /* discord/gateway.json:143:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
                "(token):s,"
  /* discord/gateway.json:144:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */
                "(properties):F,"
  /* discord/gateway.json:145:19
     '{ "name":"compress","type":{"base":"bool"}}' */
                "(compress):b,"
  /* discord/gateway.json:146:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
                "(large_threshold):d,"
  /* discord/gateway.json:147:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
                "(guild_subscriptions):b,"
  /* discord/gateway.json:148:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  /* discord/gateway.json:149:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */
                "(presence):F,"
  /* discord/gateway.json:150:19
     '{ "name":"intents","type":{"base":"int"}}' */
                "(intents):d,"
                "@arg_switches:b",
  /* discord/gateway.json:143:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
                p->token,
  /* discord/gateway.json:144:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */
                discord_identify_connection_to_json, p->properties,
  /* discord/gateway.json:145:19
     '{ "name":"compress","type":{"base":"bool"}}' */
                &p->compress,
  /* discord/gateway.json:146:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
                &p->large_threshold,
  /* discord/gateway.json:147:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
                &p->guild_subscriptions,
  /* discord/gateway.json:148:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  /* discord/gateway.json:149:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */
                discord_presence_status_to_json, p->presence,
  /* discord/gateway.json:150:19
     '{ "name":"intents","type":{"base":"int"}}' */
                &p->intents,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_identify_cleanup_v(void *p) {
  discord_identify_cleanup((struct discord_identify *)p);
}

void discord_identify_init_v(void *p) {
  discord_identify_init((struct discord_identify *)p);
}

void discord_identify_from_json_v(char *json, size_t len, void *p) {
 discord_identify_from_json(json, len, (struct discord_identify*)p);
}

size_t discord_identify_to_json_v(char *json, size_t len, void *p) {
  return discord_identify_to_json(json, len, (struct discord_identify*)p);
}

void discord_identify_list_free_v(void **p) {
  discord_identify_list_free((struct discord_identify**)p);
}

void discord_identify_list_from_json_v(char *str, size_t len, void *p) {
  discord_identify_list_from_json(str, len, (struct discord_identify ***)p);
}

size_t discord_identify_list_to_json_v(char *str, size_t len, void *p){
  return discord_identify_list_to_json(str, len, (struct discord_identify **)p);
}


void discord_identify_cleanup(struct discord_identify *d) {
  /* discord/gateway.json:143:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */
  if (d->token)
    free(d->token);
  /* discord/gateway.json:144:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */
  if (d->properties) {
    discord_identify_connection_cleanup(d->properties);
    free(d->properties);
  }
  /* discord/gateway.json:145:19
     '{ "name":"compress","type":{"base":"bool"}}' */
  /* p->compress is a scalar */
  /* discord/gateway.json:146:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */
  /* p->large_threshold is a scalar */
  /* discord/gateway.json:147:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */
  /* p->guild_subscriptions is a scalar */
  /* discord/gateway.json:148:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */
  /* @todo p->(null) */
  /* discord/gateway.json:149:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */
  if (d->presence) {
    discord_presence_status_cleanup(d->presence);
    free(d->presence);
  }
  /* discord/gateway.json:150:19
     '{ "name":"intents","type":{"base":"int"}}' */
  /* p->intents is a scalar */
}

void discord_identify_init(struct discord_identify *p) {
  memset(p, 0, sizeof(struct discord_identify));
  /* discord/gateway.json:143:19
     '{ "name":"token","type":{"base":"char", "dec":"*"}}' */

  /* discord/gateway.json:144:19
     '{ "name":"properties","type":{"base":"struct discord_identify_connection", "dec":"*"}}' */

  /* discord/gateway.json:145:19
     '{ "name":"compress","type":{"base":"bool"}}' */

  /* discord/gateway.json:146:19
     '{ "name":"large_threshold","type":{"base":"int"}}' */

  /* discord/gateway.json:147:19
     '{ "name":"guild_subscriptions","type":{"base":"bool"}}' */

  /* discord/gateway.json:148:19
     '{ "name":"shard","type":{"base":"int", "dec":"*"}, "todo":true}' */

  /* discord/gateway.json:149:19
     '{ "name":"presence","type":{"base":"struct discord_presence_status", "dec":"*"}}' */

  /* discord/gateway.json:150:19
     '{ "name":"intents","type":{"base":"int"}}' */

}
void discord_identify_list_free(struct discord_identify **p) {
  ntl_free((void**)p, (vfvp)discord_identify_cleanup);
}

void discord_identify_list_from_json(char *str, size_t len, struct discord_identify ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_identify);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_identify_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_identify_list_to_json(char *str, size_t len, struct discord_identify **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_identify_to_json);
}


void discord_voice_state_status_from_json_p(char *json, size_t len, struct discord_voice_state_status **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_voice_state_status_from_json(json, len, *pp);
}
void discord_voice_state_status_from_json(char *json, size_t len, struct discord_voice_state_status *p)
{
  discord_voice_state_status_init(p);
  json_extract(json, len, 
  /* discord/gateway.json:160:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */
                "(guild_id):F,"
  /* discord/gateway.json:161:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */
                "(channel_id):F,"
  /* discord/gateway.json:162:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */
                "(self_mute):b,"
  /* discord/gateway.json:163:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */
                "(self_deaf):b,",
  /* discord/gateway.json:160:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */
                cee_strtou64, &p->guild_id,
  /* discord/gateway.json:161:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */
                cee_strtou64, &p->channel_id,
  /* discord/gateway.json:162:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */
                &p->self_mute,
  /* discord/gateway.json:163:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */
                &p->self_deaf);
}

size_t discord_voice_state_status_to_json(char *json, size_t len, struct discord_voice_state_status *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/gateway.json:160:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */
  if (p->guild_id != 0)
    arg_switches[0] = &p->guild_id;

  /* discord/gateway.json:161:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */
  if (p->channel_id != 0)
    arg_switches[1] = &p->channel_id;

  /* discord/gateway.json:162:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */
  arg_switches[2] = &p->self_mute;

  /* discord/gateway.json:163:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */
  arg_switches[3] = &p->self_deaf;

  r=json_inject(json, len, 
  /* discord/gateway.json:160:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */
                "(guild_id):|F|,"
  /* discord/gateway.json:161:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */
                "(channel_id):|F|,"
  /* discord/gateway.json:162:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */
                "(self_mute):b,"
  /* discord/gateway.json:163:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */
                "(self_deaf):b,"
                "@arg_switches:b",
  /* discord/gateway.json:160:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */
                cee_u64tostr, &p->guild_id,
  /* discord/gateway.json:161:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */
                cee_u64tostr, &p->channel_id,
  /* discord/gateway.json:162:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */
                &p->self_mute,
  /* discord/gateway.json:163:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */
                &p->self_deaf,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_voice_state_status_cleanup_v(void *p) {
  discord_voice_state_status_cleanup((struct discord_voice_state_status *)p);
}

void discord_voice_state_status_init_v(void *p) {
  discord_voice_state_status_init((struct discord_voice_state_status *)p);
}

void discord_voice_state_status_from_json_v(char *json, size_t len, void *p) {
 discord_voice_state_status_from_json(json, len, (struct discord_voice_state_status*)p);
}

size_t discord_voice_state_status_to_json_v(char *json, size_t len, void *p) {
  return discord_voice_state_status_to_json(json, len, (struct discord_voice_state_status*)p);
}

void discord_voice_state_status_list_free_v(void **p) {
  discord_voice_state_status_list_free((struct discord_voice_state_status**)p);
}

void discord_voice_state_status_list_from_json_v(char *str, size_t len, void *p) {
  discord_voice_state_status_list_from_json(str, len, (struct discord_voice_state_status ***)p);
}

size_t discord_voice_state_status_list_to_json_v(char *str, size_t len, void *p){
  return discord_voice_state_status_list_to_json(str, len, (struct discord_voice_state_status **)p);
}


void discord_voice_state_status_cleanup(struct discord_voice_state_status *d) {
  /* discord/gateway.json:160:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */
  /* p->guild_id is a scalar */
  /* discord/gateway.json:161:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */
  /* p->channel_id is a scalar */
  /* discord/gateway.json:162:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */
  /* p->self_mute is a scalar */
  /* discord/gateway.json:163:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */
  /* p->self_deaf is a scalar */
}

void discord_voice_state_status_init(struct discord_voice_state_status *p) {
  memset(p, 0, sizeof(struct discord_voice_state_status));
  /* discord/gateway.json:160:19
     '{ "name":"guild_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the guild", "inject_if_not":0 }' */

  /* discord/gateway.json:161:19
     '{ "name":"channel_id","type":{"base":"char", "dec":"*", "converter":"snowflake"}, "option":true, "comment":"id of the voice channel client wants to join (null if disconnecting)", "inject_if_not":0 }' */

  /* discord/gateway.json:162:19
     '{ "name":"self_mute","type":{"base":"bool"}, "comment":"is the client muted"}' */

  /* discord/gateway.json:163:19
     '{ "name":"self_deaf","type":{"base":"bool"}, "comment":"is the client deafened"}' */

}
void discord_voice_state_status_list_free(struct discord_voice_state_status **p) {
  ntl_free((void**)p, (vfvp)discord_voice_state_status_cleanup);
}

void discord_voice_state_status_list_from_json(char *str, size_t len, struct discord_voice_state_status ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_voice_state_status);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_voice_state_status_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_voice_state_status_list_to_json(char *str, size_t len, struct discord_voice_state_status **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_voice_state_status_to_json);
}


void discord_presence_status_from_json_p(char *json, size_t len, struct discord_presence_status **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_presence_status_from_json(json, len, *pp);
}
void discord_presence_status_from_json(char *json, size_t len, struct discord_presence_status *p)
{
  discord_presence_status_init(p);
  json_extract(json, len, 
  /* discord/gateway.json:173:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */
                "(since):F,"
  /* discord/gateway.json:174:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */
                "(activities):F,"
  /* discord/gateway.json:175:19
     '{ "name":"status","type":{"base":"char", "dec":"*"}, "comment":"the user's new status", "inject_if_not":null }' */
                "(status):?s,"
  /* discord/gateway.json:176:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */
                "(afk):b,",
  /* discord/gateway.json:173:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */
                cee_iso8601_to_unix_ms, &p->since,
  /* discord/gateway.json:174:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */
                discord_activity_list_from_json, &p->activities,
  /* discord/gateway.json:175:19
     '{ "name":"status","type":{"base":"char", "dec":"*"}, "comment":"the user's new status", "inject_if_not":null }' */
                &p->status,
  /* discord/gateway.json:176:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */
                &p->afk);
}

size_t discord_presence_status_to_json(char *json, size_t len, struct discord_presence_status *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/gateway.json:173:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */
  if (p->since != 0)
    arg_switches[0] = &p->since;

  /* discord/gateway.json:174:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */
  if (p->activities != NULL)
    arg_switches[1] = p->activities;

  /* discord/gateway.json:175:19
     '{ "name":"status","type":{"base":"char", "dec":"*"}, "comment":"the user's new status", "inject_if_not":null }' */
  if (p->status != NULL)
    arg_switches[2] = p->status;

  /* discord/gateway.json:176:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */
  arg_switches[3] = &p->afk;

  r=json_inject(json, len, 
  /* discord/gateway.json:173:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */
                "(since):|F|,"
  /* discord/gateway.json:174:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */
                "(activities):F,"
  /* discord/gateway.json:175:19
     '{ "name":"status","type":{"base":"char", "dec":"*"}, "comment":"the user's new status", "inject_if_not":null }' */
                "(status):s,"
  /* discord/gateway.json:176:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */
                "(afk):b,"
                "@arg_switches:b",
  /* discord/gateway.json:173:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */
                cee_unix_ms_to_iso8601, &p->since,
  /* discord/gateway.json:174:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */
                discord_activity_list_to_json, p->activities,
  /* discord/gateway.json:175:19
     '{ "name":"status","type":{"base":"char", "dec":"*"}, "comment":"the user's new status", "inject_if_not":null }' */
                p->status,
  /* discord/gateway.json:176:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */
                &p->afk,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_presence_status_cleanup_v(void *p) {
  discord_presence_status_cleanup((struct discord_presence_status *)p);
}

void discord_presence_status_init_v(void *p) {
  discord_presence_status_init((struct discord_presence_status *)p);
}

void discord_presence_status_from_json_v(char *json, size_t len, void *p) {
 discord_presence_status_from_json(json, len, (struct discord_presence_status*)p);
}

size_t discord_presence_status_to_json_v(char *json, size_t len, void *p) {
  return discord_presence_status_to_json(json, len, (struct discord_presence_status*)p);
}

void discord_presence_status_list_free_v(void **p) {
  discord_presence_status_list_free((struct discord_presence_status**)p);
}

void discord_presence_status_list_from_json_v(char *str, size_t len, void *p) {
  discord_presence_status_list_from_json(str, len, (struct discord_presence_status ***)p);
}

size_t discord_presence_status_list_to_json_v(char *str, size_t len, void *p){
  return discord_presence_status_list_to_json(str, len, (struct discord_presence_status **)p);
}


void discord_presence_status_cleanup(struct discord_presence_status *d) {
  /* discord/gateway.json:173:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */
  /* p->since is a scalar */
  /* discord/gateway.json:174:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */
  if (d->activities)
    discord_activity_list_free(d->activities);
  /* discord/gateway.json:175:19
     '{ "name":"status","type":{"base":"char", "dec":"*"}, "comment":"the user's new status", "inject_if_not":null }' */
  if (d->status)
    free(d->status);
  /* discord/gateway.json:176:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */
  /* p->afk is a scalar */
}

void discord_presence_status_init(struct discord_presence_status *p) {
  memset(p, 0, sizeof(struct discord_presence_status));
  /* discord/gateway.json:173:19
     '{ "name":"since","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "comment":"unix time (in milliseconds) of when the client went idle, or null if the client is not idle", "inject_if_not":0 }' */

  /* discord/gateway.json:174:19
     '{ "name":"activities","type":{"base":"struct discord_activity", "dec":"ntl"}, "option":true, "comment":"the user's activities", "inject_if_not":null}' */

  /* discord/gateway.json:175:19
     '{ "name":"status","type":{"base":"char", "dec":"*"}, "comment":"the user's new status", "inject_if_not":null }' */

  /* discord/gateway.json:176:19
     '{ "name":"afk","type":{"base":"bool"}, "comment":"whether or not the client is afk"}' */

}
void discord_presence_status_list_free(struct discord_presence_status **p) {
  ntl_free((void**)p, (vfvp)discord_presence_status_cleanup);
}

void discord_presence_status_list_from_json(char *str, size_t len, struct discord_presence_status ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_presence_status);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_presence_status_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_presence_status_list_to_json(char *str, size_t len, struct discord_presence_status **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_presence_status_to_json);
}


void discord_identify_connection_from_json_p(char *json, size_t len, struct discord_identify_connection **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_identify_connection_from_json(json, len, *pp);
}
void discord_identify_connection_from_json(char *json, size_t len, struct discord_identify_connection *p)
{
  discord_identify_connection_init(p);
  json_extract(json, len, 
  /* discord/gateway.json:186:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */
                "($os):?s,"
  /* discord/gateway.json:187:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
                "($browser):?s,"
  /* discord/gateway.json:188:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
                "($device):?s,",
  /* discord/gateway.json:186:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */
                &p->os,
  /* discord/gateway.json:187:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
                &p->browser,
  /* discord/gateway.json:188:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
                &p->device);
}

size_t discord_identify_connection_to_json(char *json, size_t len, struct discord_identify_connection *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* discord/gateway.json:186:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */
  if (p->os != NULL)
    arg_switches[0] = p->os;

  /* discord/gateway.json:187:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
  if (p->browser != NULL)
    arg_switches[1] = p->browser;

  /* discord/gateway.json:188:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
  if (p->device != NULL)
    arg_switches[2] = p->device;

  r=json_inject(json, len, 
  /* discord/gateway.json:186:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */
                "($os):s,"
  /* discord/gateway.json:187:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
                "($browser):s,"
  /* discord/gateway.json:188:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
                "($device):s,"
                "@arg_switches:b",
  /* discord/gateway.json:186:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */
                p->os,
  /* discord/gateway.json:187:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
                p->browser,
  /* discord/gateway.json:188:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
                p->device,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_identify_connection_cleanup_v(void *p) {
  discord_identify_connection_cleanup((struct discord_identify_connection *)p);
}

void discord_identify_connection_init_v(void *p) {
  discord_identify_connection_init((struct discord_identify_connection *)p);
}

void discord_identify_connection_from_json_v(char *json, size_t len, void *p) {
 discord_identify_connection_from_json(json, len, (struct discord_identify_connection*)p);
}

size_t discord_identify_connection_to_json_v(char *json, size_t len, void *p) {
  return discord_identify_connection_to_json(json, len, (struct discord_identify_connection*)p);
}

void discord_identify_connection_list_free_v(void **p) {
  discord_identify_connection_list_free((struct discord_identify_connection**)p);
}

void discord_identify_connection_list_from_json_v(char *str, size_t len, void *p) {
  discord_identify_connection_list_from_json(str, len, (struct discord_identify_connection ***)p);
}

size_t discord_identify_connection_list_to_json_v(char *str, size_t len, void *p){
  return discord_identify_connection_list_to_json(str, len, (struct discord_identify_connection **)p);
}


void discord_identify_connection_cleanup(struct discord_identify_connection *d) {
  /* discord/gateway.json:186:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */
  if (d->os)
    free(d->os);
  /* discord/gateway.json:187:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
  if (d->browser)
    free(d->browser);
  /* discord/gateway.json:188:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */
  if (d->device)
    free(d->device);
}

void discord_identify_connection_init(struct discord_identify_connection *p) {
  memset(p, 0, sizeof(struct discord_identify_connection));
  /* discord/gateway.json:186:19
     '{ "name":"os", "json_key":"$os", "type":{"base":"char", "dec":"*"}, "comment":"your operating system", "inject_if_not":null }' */

  /* discord/gateway.json:187:19
     '{ "name":"browser", "json_key":"$browser", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */

  /* discord/gateway.json:188:19
     '{ "name":"device", "json_key":"$device", "type":{"base":"char", "dec":"*"}, "comment":"your library name", "inject_if_not":null }' */

}
void discord_identify_connection_list_free(struct discord_identify_connection **p) {
  ntl_free((void**)p, (vfvp)discord_identify_connection_cleanup);
}

void discord_identify_connection_list_from_json(char *str, size_t len, struct discord_identify_connection ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_identify_connection);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_identify_connection_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_identify_connection_list_to_json(char *str, size_t len, struct discord_identify_connection **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_identify_connection_to_json);
}


void discord_activity_from_json_p(char *json, size_t len, struct discord_activity **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_activity_from_json(json, len, *pp);
}
void discord_activity_from_json(char *json, size_t len, struct discord_activity *p)
{
  discord_activity_init(p);
  json_extract(json, len, 
  /* discord/gateway.json:197:19
     '{ "name":"name","type":{"base":"char", "dec":"*"}}' */
                "(name):?s,"
  /* discord/gateway.json:198:19
     '{ "name":"type","type":{"base":"int"}}' */
                "(type):d,"
  /* discord/gateway.json:199:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */
                "(url):?s,"
  /* discord/gateway.json:200:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */
                "(created_at):F,"
  /* discord/gateway.json:201:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */
                "(application_id):F,"
  /* discord/gateway.json:202:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(details):?s,"
  /* discord/gateway.json:203:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(state):?s,"
  /* discord/gateway.json:204:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                "(instance):b,",
  /* discord/gateway.json:197:19
     '{ "name":"name","type":{"base":"char", "dec":"*"}}' */
                &p->name,
  /* discord/gateway.json:198:19
     '{ "name":"type","type":{"base":"int"}}' */
                &p->type,
  /* discord/gateway.json:199:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */
                &p->url,
  /* discord/gateway.json:200:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */
                cee_iso8601_to_unix_ms, &p->created_at,
  /* discord/gateway.json:201:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */
                cee_strtou64, &p->application_id,
  /* discord/gateway.json:202:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->details,
  /* discord/gateway.json:203:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                &p->state,
  /* discord/gateway.json:204:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                &p->instance);
}

size_t discord_activity_to_json(char *json, size_t len, struct discord_activity *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* discord/gateway.json:197:19
     '{ "name":"name","type":{"base":"char", "dec":"*"}}' */
  arg_switches[0] = p->name;

  /* discord/gateway.json:198:19
     '{ "name":"type","type":{"base":"int"}}' */
  arg_switches[1] = &p->type;

  /* discord/gateway.json:199:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */
  if (p->url && *p->url)
    arg_switches[2] = p->url;

  /* discord/gateway.json:200:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */
  if (p->created_at != 0)
    arg_switches[3] = &p->created_at;

  /* discord/gateway.json:201:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */
  if (p->application_id != 0)
    arg_switches[4] = &p->application_id;

  /* discord/gateway.json:202:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->details != NULL)
    arg_switches[5] = p->details;

  /* discord/gateway.json:203:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (p->state != NULL)
    arg_switches[6] = p->state;

  /* discord/gateway.json:204:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  if (p->instance != false)
    arg_switches[7] = &p->instance;

  r=json_inject(json, len, 
  /* discord/gateway.json:197:19
     '{ "name":"name","type":{"base":"char", "dec":"*"}}' */
                "(name):s,"
  /* discord/gateway.json:198:19
     '{ "name":"type","type":{"base":"int"}}' */
                "(type):d,"
  /* discord/gateway.json:199:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */
                "(url):s,"
  /* discord/gateway.json:200:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */
                "(created_at):|F|,"
  /* discord/gateway.json:201:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */
                "(application_id):|F|,"
  /* discord/gateway.json:202:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(details):s,"
  /* discord/gateway.json:203:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                "(state):s,"
  /* discord/gateway.json:204:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                "(instance):b,"
                "@arg_switches:b",
  /* discord/gateway.json:197:19
     '{ "name":"name","type":{"base":"char", "dec":"*"}}' */
                p->name,
  /* discord/gateway.json:198:19
     '{ "name":"type","type":{"base":"int"}}' */
                &p->type,
  /* discord/gateway.json:199:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */
                p->url,
  /* discord/gateway.json:200:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */
                cee_unix_ms_to_iso8601, &p->created_at,
  /* discord/gateway.json:201:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */
                cee_u64tostr, &p->application_id,
  /* discord/gateway.json:202:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->details,
  /* discord/gateway.json:203:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
                p->state,
  /* discord/gateway.json:204:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
                &p->instance,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_activity_cleanup_v(void *p) {
  discord_activity_cleanup((struct discord_activity *)p);
}

void discord_activity_init_v(void *p) {
  discord_activity_init((struct discord_activity *)p);
}

void discord_activity_from_json_v(char *json, size_t len, void *p) {
 discord_activity_from_json(json, len, (struct discord_activity*)p);
}

size_t discord_activity_to_json_v(char *json, size_t len, void *p) {
  return discord_activity_to_json(json, len, (struct discord_activity*)p);
}

void discord_activity_list_free_v(void **p) {
  discord_activity_list_free((struct discord_activity**)p);
}

void discord_activity_list_from_json_v(char *str, size_t len, void *p) {
  discord_activity_list_from_json(str, len, (struct discord_activity ***)p);
}

size_t discord_activity_list_to_json_v(char *str, size_t len, void *p){
  return discord_activity_list_to_json(str, len, (struct discord_activity **)p);
}


void discord_activity_cleanup(struct discord_activity *d) {
  /* discord/gateway.json:197:19
     '{ "name":"name","type":{"base":"char", "dec":"*"}}' */
  if (d->name)
    free(d->name);
  /* discord/gateway.json:198:19
     '{ "name":"type","type":{"base":"int"}}' */
  /* p->type is a scalar */
  /* discord/gateway.json:199:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */
  if (d->url)
    free(d->url);
  /* discord/gateway.json:200:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */
  /* p->created_at is a scalar */
  /* discord/gateway.json:201:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */
  /* p->application_id is a scalar */
  /* discord/gateway.json:202:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->details)
    free(d->details);
  /* discord/gateway.json:203:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */
  if (d->state)
    free(d->state);
  /* discord/gateway.json:204:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */
  /* p->instance is a scalar */
}

void discord_activity_init(struct discord_activity *p) {
  memset(p, 0, sizeof(struct discord_activity));
  /* discord/gateway.json:197:19
     '{ "name":"name","type":{"base":"char", "dec":"*"}}' */

  /* discord/gateway.json:198:19
     '{ "name":"type","type":{"base":"int"}}' */

  /* discord/gateway.json:199:19
     '{ "name":"url","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":""}' */

  /* discord/gateway.json:200:19
     '{ "name":"created_at","type":{"base":"char", "dec":"*", "converter":"iso8601"}, "option":true, "inject_if_not":0 }' */

  /* discord/gateway.json:201:19
     '{ "name":"application_id","type":{"base":"char", "dec":"*", "converter":"snowflake" }, "option":true, "inject_if_not":0 }' */

  /* discord/gateway.json:202:19
     '{ "name":"details","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* discord/gateway.json:203:19
     '{ "name":"state","type":{"base":"char", "dec":"*"}, "option":true, "inject_if_not":null}' */

  /* discord/gateway.json:204:19
     '{ "name":"instance","type":{"base":"bool"}, "option":true, "inject_if_not":false}' */

}
void discord_activity_list_free(struct discord_activity **p) {
  ntl_free((void**)p, (vfvp)discord_activity_cleanup);
}

void discord_activity_list_from_json(char *str, size_t len, struct discord_activity ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_activity);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_activity_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_activity_list_to_json(char *str, size_t len, struct discord_activity **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_activity_to_json);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_activity_types_list_free_v(void **p) {
  discord_activity_types_list_free((enum discord_activity_types**)p);
}

void discord_activity_types_list_from_json_v(char *str, size_t len, void *p) {
  discord_activity_types_list_from_json(str, len, (enum discord_activity_types ***)p);
}

size_t discord_activity_types_list_to_json_v(char *str, size_t len, void *p){
  return discord_activity_types_list_to_json(str, len, (enum discord_activity_types **)p);
}

enum discord_activity_types discord_activity_types_eval(char *s){
  if(strcasecmp("GAME", s) == 0) return DISCORD_ACTIVITY_GAME;
  if(strcasecmp("STREAMING", s) == 0) return DISCORD_ACTIVITY_STREAMING;
  if(strcasecmp("LISTENING", s) == 0) return DISCORD_ACTIVITY_LISTENING;
  if(strcasecmp("CUSTOM", s) == 0) return DISCORD_ACTIVITY_CUSTOM;
  if(strcasecmp("COMPETING", s) == 0) return DISCORD_ACTIVITY_COMPETING;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_activity_types_print(enum discord_activity_types v){

  switch (v) {
  case DISCORD_ACTIVITY_GAME: return "GAME";
  case DISCORD_ACTIVITY_STREAMING: return "STREAMING";
  case DISCORD_ACTIVITY_LISTENING: return "LISTENING";
  case DISCORD_ACTIVITY_CUSTOM: return "CUSTOM";
  case DISCORD_ACTIVITY_COMPETING: return "COMPETING";
  }

  return NULL;
}

void discord_activity_types_list_free(enum discord_activity_types **p) {
  ntl_free((void**)p, NULL);
}

void discord_activity_types_list_from_json(char *str, size_t len, enum discord_activity_types ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_activity_types);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_activity_types_list_to_json(char *str, size_t len, enum discord_activity_types **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_session_start_limit_from_json_p(char *json, size_t len, struct discord_session_start_limit **pp)
{
  if (!*pp) *pp = malloc(sizeof **pp);
  discord_session_start_limit_from_json(json, len, *pp);
}
void discord_session_start_limit_from_json(char *json, size_t len, struct discord_session_start_limit *p)
{
  discord_session_start_limit_init(p);
  json_extract(json, len, 
  /* discord/gateway.json:228:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */
                "(total):d,"
  /* discord/gateway.json:229:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */
                "(remaining):d,"
  /* discord/gateway.json:230:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */
                "(reset_after):d,"
  /* discord/gateway.json:231:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */
                "(max_concurrency):d,",
  /* discord/gateway.json:228:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */
                &p->total,
  /* discord/gateway.json:229:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */
                &p->remaining,
  /* discord/gateway.json:230:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */
                &p->reset_after,
  /* discord/gateway.json:231:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */
                &p->max_concurrency);
}

size_t discord_session_start_limit_to_json(char *json, size_t len, struct discord_session_start_limit *p)
{
  size_t r;
  void *arg_switches[4]={NULL};
  /* discord/gateway.json:228:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */
  if (p->total != 0)
    arg_switches[0] = &p->total;

  /* discord/gateway.json:229:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */
  if (p->remaining != 0)
    arg_switches[1] = &p->remaining;

  /* discord/gateway.json:230:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */
  if (p->reset_after != 0)
    arg_switches[2] = &p->reset_after;

  /* discord/gateway.json:231:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */
  if (p->max_concurrency != 0)
    arg_switches[3] = &p->max_concurrency;

  r=json_inject(json, len, 
  /* discord/gateway.json:228:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */
                "(total):d,"
  /* discord/gateway.json:229:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */
                "(remaining):d,"
  /* discord/gateway.json:230:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */
                "(reset_after):d,"
  /* discord/gateway.json:231:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */
                "(max_concurrency):d,"
                "@arg_switches:b",
  /* discord/gateway.json:228:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */
                &p->total,
  /* discord/gateway.json:229:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */
                &p->remaining,
  /* discord/gateway.json:230:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */
                &p->reset_after,
  /* discord/gateway.json:231:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */
                &p->max_concurrency,
                arg_switches, sizeof(arg_switches), true);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_session_start_limit_cleanup_v(void *p) {
  discord_session_start_limit_cleanup((struct discord_session_start_limit *)p);
}

void discord_session_start_limit_init_v(void *p) {
  discord_session_start_limit_init((struct discord_session_start_limit *)p);
}

void discord_session_start_limit_from_json_v(char *json, size_t len, void *p) {
 discord_session_start_limit_from_json(json, len, (struct discord_session_start_limit*)p);
}

size_t discord_session_start_limit_to_json_v(char *json, size_t len, void *p) {
  return discord_session_start_limit_to_json(json, len, (struct discord_session_start_limit*)p);
}

void discord_session_start_limit_list_free_v(void **p) {
  discord_session_start_limit_list_free((struct discord_session_start_limit**)p);
}

void discord_session_start_limit_list_from_json_v(char *str, size_t len, void *p) {
  discord_session_start_limit_list_from_json(str, len, (struct discord_session_start_limit ***)p);
}

size_t discord_session_start_limit_list_to_json_v(char *str, size_t len, void *p){
  return discord_session_start_limit_list_to_json(str, len, (struct discord_session_start_limit **)p);
}


void discord_session_start_limit_cleanup(struct discord_session_start_limit *d) {
  /* discord/gateway.json:228:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */
  /* p->total is a scalar */
  /* discord/gateway.json:229:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */
  /* p->remaining is a scalar */
  /* discord/gateway.json:230:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */
  /* p->reset_after is a scalar */
  /* discord/gateway.json:231:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */
  /* p->max_concurrency is a scalar */
}

void discord_session_start_limit_init(struct discord_session_start_limit *p) {
  memset(p, 0, sizeof(struct discord_session_start_limit));
  /* discord/gateway.json:228:19
     '{ "name":"total","type":{"base":"int"}, "comment":"the total number of session starts the current user is allowed", "inject_if_not":0 }' */

  /* discord/gateway.json:229:19
     '{ "name":"remaining","type":{"base":"int"}, "comment":"the remaining number of session starts the current user is allowed", "inject_if_not":0 }' */

  /* discord/gateway.json:230:19
     '{ "name":"reset_after","type":{"base":"int"}, "comment":"the number of milliseconds after which the limit resets", "inject_if_not":0 }' */

  /* discord/gateway.json:231:19
     '{ "name":"max_concurrency","type":{"base":"int"}, "comment":"the number of identify requests allowed per 5 seconds", "inject_if_not":0 }' */

}
void discord_session_start_limit_list_free(struct discord_session_start_limit **p) {
  ntl_free((void**)p, (vfvp)discord_session_start_limit_cleanup);
}

void discord_session_start_limit_list_from_json(char *str, size_t len, struct discord_session_start_limit ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_session_start_limit);
  d.init_elem = NULL;
  d.elem_from_buf = (vfcpsvp)discord_session_start_limit_from_json_p;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_session_start_limit_list_to_json(char *str, size_t len, struct discord_session_start_limit **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, (sfcpsvp)discord_session_start_limit_to_json);
}

