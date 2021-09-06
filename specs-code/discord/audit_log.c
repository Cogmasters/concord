/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/**
 * @file specs-code/discord/audit_log.c
 * @see https://discord.com/developers/docs/resources/audit-log
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "json-actor.h"
#include "json-actor-boxed.h"
#include "cee-utils.h"
#include "discord.h"

void discord_audit_log_from_json(char *json, size_t len, struct discord_audit_log **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_audit_log *p = *pp;
  discord_audit_log_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" } }' */
                "(webhooks):F,"
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}}' */
                "(users):F,"
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}}' */
                "(audit_log_entries):F,"
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}' */
                "(integrations):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" } }' */
                discord_webhook_list_from_json, &p->webhooks,
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}}' */
                discord_user_list_from_json, &p->users,
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}}' */
                discord_audit_log_entry_list_from_json, &p->audit_log_entries,
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}' */
                discord_guild_integration_list_from_json, &p->integrations,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_use_default_inject_settings(struct discord_audit_log *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" } }' */
  p->__M.arg_switches[0] = p->webhooks;

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}}' */
  p->__M.arg_switches[1] = p->users;

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}}' */
  p->__M.arg_switches[2] = p->audit_log_entries;

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}' */
  p->__M.arg_switches[3] = p->integrations;

}

size_t discord_audit_log_to_json(char *json, size_t len, struct discord_audit_log *p)
{
  size_t r;
  discord_audit_log_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" } }' */
                "(webhooks):F,"
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}}' */
                "(users):F,"
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}}' */
                "(audit_log_entries):F,"
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}' */
                "(integrations):F,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" } }' */
                discord_webhook_list_to_json, p->webhooks,
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}}' */
                discord_user_list_to_json, p->users,
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}}' */
                discord_audit_log_entry_list_to_json, p->audit_log_entries,
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}' */
                discord_guild_integration_list_to_json, p->integrations,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_cleanup_v(void *p) {
  discord_audit_log_cleanup((struct discord_audit_log *)p);
}

void discord_audit_log_init_v(void *p) {
  discord_audit_log_init((struct discord_audit_log *)p);
}

void discord_audit_log_from_json_v(char *json, size_t len, void *pp) {
 discord_audit_log_from_json(json, len, (struct discord_audit_log**)pp);
}

size_t discord_audit_log_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_to_json(json, len, (struct discord_audit_log*)p);
}

void discord_audit_log_list_free_v(void **p) {
  discord_audit_log_list_free((struct discord_audit_log**)p);
}

void discord_audit_log_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_list_from_json(str, len, (struct discord_audit_log ***)p);
}

size_t discord_audit_log_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_list_to_json(str, len, (struct discord_audit_log **)p);
}


void discord_audit_log_cleanup(struct discord_audit_log *d) {
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" } }' */
  if (d->webhooks)
    discord_webhook_list_free(d->webhooks);
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}}' */
  if (d->users)
    discord_user_list_free(d->users);
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}}' */
  if (d->audit_log_entries)
    discord_audit_log_entry_list_free(d->audit_log_entries);
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}' */
  if (d->integrations)
    discord_guild_integration_list_free(d->integrations);
}

void discord_audit_log_init(struct discord_audit_log *p) {
  memset(p, 0, sizeof(struct discord_audit_log));
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" } }' */

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}}' */

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}}' */

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_guild_integration", "dec":"ntl"}}' */

}
void discord_audit_log_list_free(struct discord_audit_log **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_cleanup);
}

void discord_audit_log_list_from_json(char *str, size_t len, struct discord_audit_log ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log);
  d.init_elem = NULL;
  d.elem_from_buf = discord_audit_log_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_audit_log_list_to_json(char *str, size_t len, struct discord_audit_log **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_to_json_v);
}



typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_events_list_free_v(void **p) {
  discord_audit_log_events_list_free((enum discord_audit_log_events**)p);
}

void discord_audit_log_events_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_events_list_from_json(str, len, (enum discord_audit_log_events ***)p);
}

size_t discord_audit_log_events_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_events_list_to_json(str, len, (enum discord_audit_log_events **)p);
}

enum discord_audit_log_events discord_audit_log_events_eval(char *s){
  if(strcasecmp("GUILD_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_GUILD_UPDATE;
  if(strcasecmp("CHANNEL_CREATE", s) == 0) return DISCORD_AUDIT_LOG_CHANNEL_CREATE;
  if(strcasecmp("CHANNEL_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_CHANNEL_UPDATE;
  if(strcasecmp("CHANNEL_DELETE", s) == 0) return DISCORD_AUDIT_LOG_CHANNEL_DELETE;
  if(strcasecmp("CHANNEL_OVERWRITE_CREATE", s) == 0) return DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_CREATE;
  if(strcasecmp("CHANNEL_OVERWRITE_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_UPDATE;
  if(strcasecmp("CHANNEL_OVERWRITE_DELETE", s) == 0) return DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_DELETE;
  if(strcasecmp("MEMBER_KICK", s) == 0) return DISCORD_AUDIT_LOG_MEMBER_KICK;
  if(strcasecmp("MEMBER_PRUNE", s) == 0) return DISCORD_AUDIT_LOG_MEMBER_PRUNE;
  if(strcasecmp("MEMBER_BAN_ADD", s) == 0) return DISCORD_AUDIT_LOG_MEMBER_BAN_ADD;
  if(strcasecmp("MEMBER_BAN_REMOVE", s) == 0) return DISCORD_AUDIT_LOG_MEMBER_BAN_REMOVE;
  if(strcasecmp("MEMBER_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_MEMBER_UPDATE;
  if(strcasecmp("MEMBER_ROLE_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_MEMBER_ROLE_UPDATE;
  if(strcasecmp("MEMBER_MOVE", s) == 0) return DISCORD_AUDIT_LOG_MEMBER_MOVE;
  if(strcasecmp("MEMBER_DISCONNECT", s) == 0) return DISCORD_AUDIT_LOG_MEMBER_DISCONNECT;
  if(strcasecmp("BOT_ADD", s) == 0) return DISCORD_AUDIT_LOG_BOT_ADD;
  if(strcasecmp("ROLE_CREATE", s) == 0) return DISCORD_AUDIT_LOG_ROLE_CREATE;
  if(strcasecmp("ROLE_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_ROLE_UPDATE;
  if(strcasecmp("ROLE_DELETE", s) == 0) return DISCORD_AUDIT_LOG_ROLE_DELETE;
  if(strcasecmp("INVITE_CREATE", s) == 0) return DISCORD_AUDIT_LOG_INVITE_CREATE;
  if(strcasecmp("INVITE_DELETE", s) == 0) return DISCORD_AUDIT_LOG_INVITE_DELETE;
  if(strcasecmp("WEBHOOK_CREATE", s) == 0) return DISCORD_AUDIT_LOG_WEBHOOK_CREATE;
  if(strcasecmp("WEBHOOK_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_WEBHOOK_UPDATE;
  if(strcasecmp("WEBHOOK_DELETE", s) == 0) return DISCORD_AUDIT_LOG_WEBHOOK_DELETE;
  if(strcasecmp("EMOJI_CREATE", s) == 0) return DISCORD_AUDIT_LOG_EMOJI_CREATE;
  if(strcasecmp("EMOJI_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_EMOJI_UPDATE;
  if(strcasecmp("EMOJI_DELETE", s) == 0) return DISCORD_AUDIT_LOG_EMOJI_DELETE;
  if(strcasecmp("MESSAGE_DELETE", s) == 0) return DISCORD_AUDIT_LOG_MESSAGE_DELETE;
  if(strcasecmp("MESSAGE_BULK_DELETE", s) == 0) return DISCORD_AUDIT_LOG_MESSAGE_BULK_DELETE;
  if(strcasecmp("MESSAGE_PIN", s) == 0) return DISCORD_AUDIT_LOG_MESSAGE_PIN;
  if(strcasecmp("MESSAGE_UNPIN", s) == 0) return DISCORD_AUDIT_LOG_MESSAGE_UNPIN;
  if(strcasecmp("INTEGRATION_CREATE", s) == 0) return DISCORD_AUDIT_LOG_INTEGRATION_CREATE;
  if(strcasecmp("INTEGRATION_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_INTEGRATION_UPDATE;
  if(strcasecmp("INTEGRATION_DELETE", s) == 0) return DISCORD_AUDIT_LOG_INTEGRATION_DELETE;
  ERR("'%s' doesn't match any known enumerator.", s);
}

char* discord_audit_log_events_print(enum discord_audit_log_events v){

  switch (v) {
  case DISCORD_AUDIT_LOG_GUILD_UPDATE: return "GUILD_UPDATE";
  case DISCORD_AUDIT_LOG_CHANNEL_CREATE: return "CHANNEL_CREATE";
  case DISCORD_AUDIT_LOG_CHANNEL_UPDATE: return "CHANNEL_UPDATE";
  case DISCORD_AUDIT_LOG_CHANNEL_DELETE: return "CHANNEL_DELETE";
  case DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_CREATE: return "CHANNEL_OVERWRITE_CREATE";
  case DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_UPDATE: return "CHANNEL_OVERWRITE_UPDATE";
  case DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_DELETE: return "CHANNEL_OVERWRITE_DELETE";
  case DISCORD_AUDIT_LOG_MEMBER_KICK: return "MEMBER_KICK";
  case DISCORD_AUDIT_LOG_MEMBER_PRUNE: return "MEMBER_PRUNE";
  case DISCORD_AUDIT_LOG_MEMBER_BAN_ADD: return "MEMBER_BAN_ADD";
  case DISCORD_AUDIT_LOG_MEMBER_BAN_REMOVE: return "MEMBER_BAN_REMOVE";
  case DISCORD_AUDIT_LOG_MEMBER_UPDATE: return "MEMBER_UPDATE";
  case DISCORD_AUDIT_LOG_MEMBER_ROLE_UPDATE: return "MEMBER_ROLE_UPDATE";
  case DISCORD_AUDIT_LOG_MEMBER_MOVE: return "MEMBER_MOVE";
  case DISCORD_AUDIT_LOG_MEMBER_DISCONNECT: return "MEMBER_DISCONNECT";
  case DISCORD_AUDIT_LOG_BOT_ADD: return "BOT_ADD";
  case DISCORD_AUDIT_LOG_ROLE_CREATE: return "ROLE_CREATE";
  case DISCORD_AUDIT_LOG_ROLE_UPDATE: return "ROLE_UPDATE";
  case DISCORD_AUDIT_LOG_ROLE_DELETE: return "ROLE_DELETE";
  case DISCORD_AUDIT_LOG_INVITE_CREATE: return "INVITE_CREATE";
  case DISCORD_AUDIT_LOG_INVITE_DELETE: return "INVITE_DELETE";
  case DISCORD_AUDIT_LOG_WEBHOOK_CREATE: return "WEBHOOK_CREATE";
  case DISCORD_AUDIT_LOG_WEBHOOK_UPDATE: return "WEBHOOK_UPDATE";
  case DISCORD_AUDIT_LOG_WEBHOOK_DELETE: return "WEBHOOK_DELETE";
  case DISCORD_AUDIT_LOG_EMOJI_CREATE: return "EMOJI_CREATE";
  case DISCORD_AUDIT_LOG_EMOJI_UPDATE: return "EMOJI_UPDATE";
  case DISCORD_AUDIT_LOG_EMOJI_DELETE: return "EMOJI_DELETE";
  case DISCORD_AUDIT_LOG_MESSAGE_DELETE: return "MESSAGE_DELETE";
  case DISCORD_AUDIT_LOG_MESSAGE_BULK_DELETE: return "MESSAGE_BULK_DELETE";
  case DISCORD_AUDIT_LOG_MESSAGE_PIN: return "MESSAGE_PIN";
  case DISCORD_AUDIT_LOG_MESSAGE_UNPIN: return "MESSAGE_UNPIN";
  case DISCORD_AUDIT_LOG_INTEGRATION_CREATE: return "INTEGRATION_CREATE";
  case DISCORD_AUDIT_LOG_INTEGRATION_UPDATE: return "INTEGRATION_UPDATE";
  case DISCORD_AUDIT_LOG_INTEGRATION_DELETE: return "INTEGRATION_DELETE";
  }

  return NULL;
}

void discord_audit_log_events_list_free(enum discord_audit_log_events **p) {
  ntl_free((void**)p, NULL);
}

void discord_audit_log_events_list_from_json(char *str, size_t len, enum discord_audit_log_events ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(enum discord_audit_log_events);
  d.init_elem = NULL;
  d.elem_from_buf = ja_u64_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_audit_log_events_list_to_json(char *str, size_t len, enum discord_audit_log_events **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, ja_u64_to_json_v);
}


void discord_audit_log_entry_from_json(char *json, size_t len, struct discord_audit_log_entry **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_audit_log_entry *p = *pp;
  discord_audit_log_entry_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:68:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}' */
                "(target_id):?s,"
  /* specs/discord/audit_log.json:69:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}}' */
                "(changes):F,"
  /* specs/discord/audit_log.json:70:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(user_id):F,"
  /* specs/discord/audit_log.json:71:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* specs/discord/audit_log.json:72:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}' */
                "(action_type):d,"
  /* specs/discord/audit_log.json:73:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"ntl"}}' */
                "(options):F,"
  /* specs/discord/audit_log.json:74:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}}' */
                "(reason):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:68:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}' */
                &p->target_id,
  /* specs/discord/audit_log.json:69:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}}' */
                discord_audit_log_change_list_from_json, &p->changes,
  /* specs/discord/audit_log.json:70:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->user_id,
  /* specs/discord/audit_log.json:71:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->id,
  /* specs/discord/audit_log.json:72:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}' */
                &p->action_type,
  /* specs/discord/audit_log.json:73:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"ntl"}}' */
                discord_audit_log_entry_optional_info_list_from_json, &p->options,
  /* specs/discord/audit_log.json:74:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}}' */
                p->reason,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_entry_use_default_inject_settings(struct discord_audit_log_entry *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:68:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[0] = p->target_id;

  /* specs/discord/audit_log.json:69:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}}' */
  p->__M.arg_switches[1] = p->changes;

  /* specs/discord/audit_log.json:70:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[2] = &p->user_id;

  /* specs/discord/audit_log.json:71:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[3] = &p->id;

  /* specs/discord/audit_log.json:72:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}' */
  p->__M.arg_switches[4] = &p->action_type;

  /* specs/discord/audit_log.json:73:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"ntl"}}' */
  p->__M.arg_switches[5] = p->options;

  /* specs/discord/audit_log.json:74:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}}' */
  p->__M.arg_switches[6] = p->reason;

}

size_t discord_audit_log_entry_to_json(char *json, size_t len, struct discord_audit_log_entry *p)
{
  size_t r;
  discord_audit_log_entry_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:68:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}' */
                "(target_id):s,"
  /* specs/discord/audit_log.json:69:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}}' */
                "(changes):F,"
  /* specs/discord/audit_log.json:70:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(user_id):|F|,"
  /* specs/discord/audit_log.json:71:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* specs/discord/audit_log.json:72:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}' */
                "(action_type):d,"
  /* specs/discord/audit_log.json:73:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"ntl"}}' */
                "(options):F,"
  /* specs/discord/audit_log.json:74:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}}' */
                "(reason):s,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:68:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}' */
                p->target_id,
  /* specs/discord/audit_log.json:69:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}}' */
                discord_audit_log_change_list_to_json, p->changes,
  /* specs/discord/audit_log.json:70:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->user_id,
  /* specs/discord/audit_log.json:71:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->id,
  /* specs/discord/audit_log.json:72:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}' */
                &p->action_type,
  /* specs/discord/audit_log.json:73:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"ntl"}}' */
                discord_audit_log_entry_optional_info_list_to_json, p->options,
  /* specs/discord/audit_log.json:74:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}}' */
                p->reason,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_entry_cleanup_v(void *p) {
  discord_audit_log_entry_cleanup((struct discord_audit_log_entry *)p);
}

void discord_audit_log_entry_init_v(void *p) {
  discord_audit_log_entry_init((struct discord_audit_log_entry *)p);
}

void discord_audit_log_entry_from_json_v(char *json, size_t len, void *pp) {
 discord_audit_log_entry_from_json(json, len, (struct discord_audit_log_entry**)pp);
}

size_t discord_audit_log_entry_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_entry_to_json(json, len, (struct discord_audit_log_entry*)p);
}

void discord_audit_log_entry_list_free_v(void **p) {
  discord_audit_log_entry_list_free((struct discord_audit_log_entry**)p);
}

void discord_audit_log_entry_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_entry_list_from_json(str, len, (struct discord_audit_log_entry ***)p);
}

size_t discord_audit_log_entry_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_entry_list_to_json(str, len, (struct discord_audit_log_entry **)p);
}


void discord_audit_log_entry_cleanup(struct discord_audit_log_entry *d) {
  /* specs/discord/audit_log.json:68:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}' */
  if (d->target_id)
    free(d->target_id);
  /* specs/discord/audit_log.json:69:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}}' */
  if (d->changes)
    discord_audit_log_change_list_free(d->changes);
  /* specs/discord/audit_log.json:70:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->user_id is a scalar
  /* specs/discord/audit_log.json:71:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->id is a scalar
  /* specs/discord/audit_log.json:72:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}' */
  // p->action_type is a scalar
  /* specs/discord/audit_log.json:73:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"ntl"}}' */
  if (d->options)
    discord_audit_log_entry_optional_info_list_free(d->options);
  /* specs/discord/audit_log.json:74:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}}' */
  // p->reason is a scalar
}

void discord_audit_log_entry_init(struct discord_audit_log_entry *p) {
  memset(p, 0, sizeof(struct discord_audit_log_entry));
  /* specs/discord/audit_log.json:68:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:69:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}}' */

  /* specs/discord/audit_log.json:70:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:71:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:72:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}}' */

  /* specs/discord/audit_log.json:73:18
     '{"name":"options", "type": {"base":"struct discord_audit_log_entry_optional_info", "dec":"ntl"}}' */

  /* specs/discord/audit_log.json:74:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}}' */

}
void discord_audit_log_entry_list_free(struct discord_audit_log_entry **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_entry_cleanup);
}

void discord_audit_log_entry_list_from_json(char *str, size_t len, struct discord_audit_log_entry ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_entry);
  d.init_elem = NULL;
  d.elem_from_buf = discord_audit_log_entry_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_audit_log_entry_list_to_json(char *str, size_t len, struct discord_audit_log_entry **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_entry_to_json_v);
}


void discord_audit_log_entry_optional_info_from_json(char *json, size_t len, struct discord_audit_log_entry_optional_info **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_audit_log_entry_optional_info *p = *pp;
  discord_audit_log_entry_optional_info_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:84:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
                "(delete_member_days):?s,"
  /* specs/discord/audit_log.json:85:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
                "(members_removed):?s,"
  /* specs/discord/audit_log.json:86:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
                "(channel_id):F,"
  /* specs/discord/audit_log.json:87:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
                "(message_id):F,"
  /* specs/discord/audit_log.json:88:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                "(count):?s,"
  /* specs/discord/audit_log.json:89:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):F,"
  /* specs/discord/audit_log.json:90:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                "(type):?s,"
  /* specs/discord/audit_log.json:91:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                "(role):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:84:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
                &p->delete_member_days,
  /* specs/discord/audit_log.json:85:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
                &p->members_removed,
  /* specs/discord/audit_log.json:86:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/audit_log.json:87:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
                cee_strtoull, &p->message_id,
  /* specs/discord/audit_log.json:88:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                &p->count,
  /* specs/discord/audit_log.json:89:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_strtoull, &p->id,
  /* specs/discord/audit_log.json:90:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                &p->type,
  /* specs/discord/audit_log.json:91:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                &p->role,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_entry_optional_info_use_default_inject_settings(struct discord_audit_log_entry_optional_info *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:84:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
  p->__M.arg_switches[0] = p->delete_member_days;

  /* specs/discord/audit_log.json:85:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
  p->__M.arg_switches[1] = p->members_removed;

  /* specs/discord/audit_log.json:86:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
  p->__M.arg_switches[2] = &p->channel_id;

  /* specs/discord/audit_log.json:87:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
  p->__M.arg_switches[3] = &p->message_id;

  /* specs/discord/audit_log.json:88:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  p->__M.arg_switches[4] = p->count;

  /* specs/discord/audit_log.json:89:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  p->__M.arg_switches[5] = &p->id;

  /* specs/discord/audit_log.json:90:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  p->__M.arg_switches[6] = p->type;

  /* specs/discord/audit_log.json:91:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  p->__M.arg_switches[7] = p->role;

}

size_t discord_audit_log_entry_optional_info_to_json(char *json, size_t len, struct discord_audit_log_entry_optional_info *p)
{
  size_t r;
  discord_audit_log_entry_optional_info_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:84:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
                "(delete_member_days):s,"
  /* specs/discord/audit_log.json:85:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
                "(members_removed):s,"
  /* specs/discord/audit_log.json:86:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
                "(channel_id):|F|,"
  /* specs/discord/audit_log.json:87:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
                "(message_id):|F|,"
  /* specs/discord/audit_log.json:88:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                "(count):s,"
  /* specs/discord/audit_log.json:89:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                "(id):|F|,"
  /* specs/discord/audit_log.json:90:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                "(type):s,"
  /* specs/discord/audit_log.json:91:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                "(role):s,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:84:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
                p->delete_member_days,
  /* specs/discord/audit_log.json:85:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
                p->members_removed,
  /* specs/discord/audit_log.json:86:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/audit_log.json:87:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
                cee_ulltostr, &p->message_id,
  /* specs/discord/audit_log.json:88:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                p->count,
  /* specs/discord/audit_log.json:89:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
                cee_ulltostr, &p->id,
  /* specs/discord/audit_log.json:90:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                p->type,
  /* specs/discord/audit_log.json:91:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
                p->role,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_entry_optional_info_cleanup_v(void *p) {
  discord_audit_log_entry_optional_info_cleanup((struct discord_audit_log_entry_optional_info *)p);
}

void discord_audit_log_entry_optional_info_init_v(void *p) {
  discord_audit_log_entry_optional_info_init((struct discord_audit_log_entry_optional_info *)p);
}

void discord_audit_log_entry_optional_info_from_json_v(char *json, size_t len, void *pp) {
 discord_audit_log_entry_optional_info_from_json(json, len, (struct discord_audit_log_entry_optional_info**)pp);
}

size_t discord_audit_log_entry_optional_info_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_entry_optional_info_to_json(json, len, (struct discord_audit_log_entry_optional_info*)p);
}

void discord_audit_log_entry_optional_info_list_free_v(void **p) {
  discord_audit_log_entry_optional_info_list_free((struct discord_audit_log_entry_optional_info**)p);
}

void discord_audit_log_entry_optional_info_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_entry_optional_info_list_from_json(str, len, (struct discord_audit_log_entry_optional_info ***)p);
}

size_t discord_audit_log_entry_optional_info_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_entry_optional_info_list_to_json(str, len, (struct discord_audit_log_entry_optional_info **)p);
}


void discord_audit_log_entry_optional_info_cleanup(struct discord_audit_log_entry_optional_info *d) {
  /* specs/discord/audit_log.json:84:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
  if (d->delete_member_days)
    free(d->delete_member_days);
  /* specs/discord/audit_log.json:85:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */
  if (d->members_removed)
    free(d->members_removed);
  /* specs/discord/audit_log.json:86:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
  // p->channel_id is a scalar
  /* specs/discord/audit_log.json:87:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */
  // p->message_id is a scalar
  /* specs/discord/audit_log.json:88:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  if (d->count)
    free(d->count);
  /* specs/discord/audit_log.json:89:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */
  // p->id is a scalar
  /* specs/discord/audit_log.json:90:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  if (d->type)
    free(d->type);
  /* specs/discord/audit_log.json:91:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */
  if (d->role)
    free(d->role);
}

void discord_audit_log_entry_optional_info_init(struct discord_audit_log_entry_optional_info *p) {
  memset(p, 0, sizeof(struct discord_audit_log_entry_optional_info));
  /* specs/discord/audit_log.json:84:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */

  /* specs/discord/audit_log.json:85:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"@todo find fixed size limit"}' */

  /* specs/discord/audit_log.json:86:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */

  /* specs/discord/audit_log.json:87:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" } }' */

  /* specs/discord/audit_log.json:88:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */

  /* specs/discord/audit_log.json:89:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }}' */

  /* specs/discord/audit_log.json:90:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */

  /* specs/discord/audit_log.json:91:20
     '{ "name": "role", "type":{ "base":"char", "dec":"*" }, "comment":"@todo find fixed size limit"}' */

}
void discord_audit_log_entry_optional_info_list_free(struct discord_audit_log_entry_optional_info **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_entry_optional_info_cleanup);
}

void discord_audit_log_entry_optional_info_list_from_json(char *str, size_t len, struct discord_audit_log_entry_optional_info ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_entry_optional_info);
  d.init_elem = NULL;
  d.elem_from_buf = discord_audit_log_entry_optional_info_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_audit_log_entry_optional_info_list_to_json(char *str, size_t len, struct discord_audit_log_entry_optional_info **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_entry_optional_info_to_json_v);
}


void discord_audit_log_change_from_json(char *json, size_t len, struct discord_audit_log_change **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_audit_log_change *p = *pp;
  discord_audit_log_change_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:101:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}' */
                "(new_value):?s,"
  /* specs/discord/audit_log.json:102:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}' */
                "(old_value):?s,"
  /* specs/discord/audit_log.json:103:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}' */
                "(key):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:101:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}' */
                &p->new_value,
  /* specs/discord/audit_log.json:102:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}' */
                &p->old_value,
  /* specs/discord/audit_log.json:103:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}' */
                p->key,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_change_use_default_inject_settings(struct discord_audit_log_change *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:101:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[0] = p->new_value;

  /* specs/discord/audit_log.json:102:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[1] = p->old_value;

  /* specs/discord/audit_log.json:103:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}' */
  p->__M.arg_switches[2] = p->key;

}

size_t discord_audit_log_change_to_json(char *json, size_t len, struct discord_audit_log_change *p)
{
  size_t r;
  discord_audit_log_change_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:101:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}' */
                "(new_value):s,"
  /* specs/discord/audit_log.json:102:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}' */
                "(old_value):s,"
  /* specs/discord/audit_log.json:103:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}' */
                "(key):s,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:101:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}' */
                p->new_value,
  /* specs/discord/audit_log.json:102:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}' */
                p->old_value,
  /* specs/discord/audit_log.json:103:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}' */
                p->key,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_change_cleanup_v(void *p) {
  discord_audit_log_change_cleanup((struct discord_audit_log_change *)p);
}

void discord_audit_log_change_init_v(void *p) {
  discord_audit_log_change_init((struct discord_audit_log_change *)p);
}

void discord_audit_log_change_from_json_v(char *json, size_t len, void *pp) {
 discord_audit_log_change_from_json(json, len, (struct discord_audit_log_change**)pp);
}

size_t discord_audit_log_change_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_change_to_json(json, len, (struct discord_audit_log_change*)p);
}

void discord_audit_log_change_list_free_v(void **p) {
  discord_audit_log_change_list_free((struct discord_audit_log_change**)p);
}

void discord_audit_log_change_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_change_list_from_json(str, len, (struct discord_audit_log_change ***)p);
}

size_t discord_audit_log_change_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_change_list_to_json(str, len, (struct discord_audit_log_change **)p);
}


void discord_audit_log_change_cleanup(struct discord_audit_log_change *d) {
  /* specs/discord/audit_log.json:101:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}' */
  if (d->new_value)
    free(d->new_value);
  /* specs/discord/audit_log.json:102:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}' */
  if (d->old_value)
    free(d->old_value);
  /* specs/discord/audit_log.json:103:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}' */
  // p->key is a scalar
}

void discord_audit_log_change_init(struct discord_audit_log_change *p) {
  memset(p, 0, sizeof(struct discord_audit_log_change));
  /* specs/discord/audit_log.json:101:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:102:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:103:18
     '{"name":"key", "type":{"base":"char", "dec":"[64]"}}' */

}
void discord_audit_log_change_list_free(struct discord_audit_log_change **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_change_cleanup);
}

void discord_audit_log_change_list_from_json(char *str, size_t len, struct discord_audit_log_change ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_change);
  d.init_elem = NULL;
  d.elem_from_buf = discord_audit_log_change_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_audit_log_change_list_to_json(char *str, size_t len, struct discord_audit_log_change **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_change_to_json_v);
}


void discord_audit_log_change_key_from_json(char *json, size_t len, struct discord_audit_log_change_key **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_audit_log_change_key *p = *pp;
  discord_audit_log_change_key_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:113:18
     '{"name":"name", "type": {"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
                "(name):s,"
  /* specs/discord/audit_log.json:114:18
     '{"name":"description", "type": {"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
                "(description):s,"
  /* specs/discord/audit_log.json:115:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "comment":"icon changed" }' */
                "(icon_hash):s,"
  /* specs/discord/audit_log.json:117:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"},
         "comment":"invite splash page artwork changed"}' */
                "(splash_hash):s,"
  /* specs/discord/audit_log.json:119:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */
                "(discovery_splash_hash):s,"
  /* specs/discord/audit_log.json:120:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(banner_hash):F,"
  /* specs/discord/audit_log.json:121:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(owner_id):F,"
  /* specs/discord/audit_log.json:122:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}}' */
                "(region):s,"
  /* specs/discord/audit_log.json:123:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}}' */
                "(preferred_locale):s,"
  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(afk_channel_id):F,"
  /* specs/discord/audit_log.json:125:18
     '{"name":"afk_timeout", "type": {"base":"int"}}' */
                "(afk_timeout):d,"
  /* specs/discord/audit_log.json:126:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(rules_channel_id):F,"
  /* specs/discord/audit_log.json:127:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(public_updates_channel_id):F,"
  /* specs/discord/audit_log.json:128:18
     '{"name":"mfa_level", "type": {"base":"int"}}' */
                "(mfa_level):d,"
  /* specs/discord/audit_log.json:129:18
     '{"name":"verification_level", "type": {"base":"int"}}' */
                "(verification_level):d,"
  /* specs/discord/audit_log.json:130:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}' */
                "(explicit_content_filter):d,"
  /* specs/discord/audit_log.json:131:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}' */
                "(default_message_notifications):d,"
  /* specs/discord/audit_log.json:132:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}' */
                "(vanity_url):?s,"
  /* specs/discord/audit_log.json:133:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:135:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:137:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}' */
                "(prune_delete_days):d,"
  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}' */
                "(widget_enabled):b,"
  /* specs/discord/audit_log.json:139:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(widget_channel_id):F,"
  /* specs/discord/audit_log.json:140:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(system_channel_id):F,"
  /* specs/discord/audit_log.json:141:18
     '{"name":"position", "type": {"base":"int"}}' */
                "(position):d,"
  /* specs/discord/audit_log.json:142:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}' */
                "(topic):?s,"
  /* specs/discord/audit_log.json:143:18
     '{"name":"bitrate", "type": {"base":"int"}}' */
                "(bitrate):d,"
  /* specs/discord/audit_log.json:144:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:146:18
     '{"name":"nsfw", "type": {"base":"bool"}}' */
                "(nsfw):b,"
  /* specs/discord/audit_log.json:147:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(application_id):F,"
  /* specs/discord/audit_log.json:148:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}' */
                "(rate_limit_per_user):d,"
  /* specs/discord/audit_log.json:149:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}' */
                "(permissions):?s,"
  /* specs/discord/audit_log.json:150:18
     '{"name":"color", "type": {"base":"int"}}' */
                "(color):d,"
  /* specs/discord/audit_log.json:151:18
     '{"name":"hoist", "type": {"base":"bool"}}' */
                "(hoist):b,"
  /* specs/discord/audit_log.json:152:18
     '{"name":"mentionable", "type": {"base":"bool"}}' */
                "(mentionable):b,"
  /* specs/discord/audit_log.json:153:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}' */
                "(allow):?s,"
  /* specs/discord/audit_log.json:154:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}' */
                "(deny):?s,"
  /* specs/discord/audit_log.json:155:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}' */
                "(code):?s,"
  /* specs/discord/audit_log.json:156:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}' */
                "(channel_id):?s,"
  /* specs/discord/audit_log.json:157:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}' */
                "(inviter_id):?s,"
  /* specs/discord/audit_log.json:158:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}' */
                "(max_uses):?s,"
  /* specs/discord/audit_log.json:159:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}' */
                "(uses):?s,"
  /* specs/discord/audit_log.json:160:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}' */
                "(max_age):?s,"
  /* specs/discord/audit_log.json:161:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}' */
                "(temporary):?s,"
  /* specs/discord/audit_log.json:162:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}' */
                "(deaf):?s,"
  /* specs/discord/audit_log.json:163:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}' */
                "(mute):?s,"
  /* specs/discord/audit_log.json:164:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}' */
                "(nick):?s,"
  /* specs/discord/audit_log.json:165:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}' */
                "(avatar_hash):?s,"
  /* specs/discord/audit_log.json:166:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):F,"
  /* specs/discord/audit_log.json:167:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}' */
  /* specs/discord/audit_log.json:169:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}' */
                "(enable_emotions):b,"
  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_behavior", "type": {"base":"int"}}' */
                "(expire_behavior):d,"
  /* specs/discord/audit_log.json:171:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}' */
                "(expire_grace_period):d,"
  /* specs/discord/audit_log.json:172:18
     '{"name":"user_limit", "type": {"base":"int" }}' */
                "(user_limit):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:113:18
     '{"name":"name", "type": {"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
                p->name,
  /* specs/discord/audit_log.json:114:18
     '{"name":"description", "type": {"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
                p->description,
  /* specs/discord/audit_log.json:115:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "comment":"icon changed" }' */
                p->icon_hash,
  /* specs/discord/audit_log.json:117:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"},
         "comment":"invite splash page artwork changed"}' */
                p->splash_hash,
  /* specs/discord/audit_log.json:119:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */
                p->discovery_splash_hash,
  /* specs/discord/audit_log.json:120:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->banner_hash,
  /* specs/discord/audit_log.json:121:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->owner_id,
  /* specs/discord/audit_log.json:122:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}}' */
                p->region,
  /* specs/discord/audit_log.json:123:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}}' */
                p->preferred_locale,
  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->afk_channel_id,
  /* specs/discord/audit_log.json:125:18
     '{"name":"afk_timeout", "type": {"base":"int"}}' */
                &p->afk_timeout,
  /* specs/discord/audit_log.json:126:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->rules_channel_id,
  /* specs/discord/audit_log.json:127:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->public_updates_channel_id,
  /* specs/discord/audit_log.json:128:18
     '{"name":"mfa_level", "type": {"base":"int"}}' */
                &p->mfa_level,
  /* specs/discord/audit_log.json:129:18
     '{"name":"verification_level", "type": {"base":"int"}}' */
                &p->verification_level,
  /* specs/discord/audit_log.json:130:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}' */
                &p->explicit_content_filter,
  /* specs/discord/audit_log.json:131:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}' */
                &p->default_message_notifications,
  /* specs/discord/audit_log.json:132:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}' */
                &p->vanity_url,
  /* specs/discord/audit_log.json:133:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:135:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:137:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}' */
                &p->prune_delete_days,
  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}' */
                &p->widget_enabled,
  /* specs/discord/audit_log.json:139:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->widget_channel_id,
  /* specs/discord/audit_log.json:140:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->system_channel_id,
  /* specs/discord/audit_log.json:141:18
     '{"name":"position", "type": {"base":"int"}}' */
                &p->position,
  /* specs/discord/audit_log.json:142:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}' */
                &p->topic,
  /* specs/discord/audit_log.json:143:18
     '{"name":"bitrate", "type": {"base":"int"}}' */
                &p->bitrate,
  /* specs/discord/audit_log.json:144:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:146:18
     '{"name":"nsfw", "type": {"base":"bool"}}' */
                &p->nsfw,
  /* specs/discord/audit_log.json:147:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->application_id,
  /* specs/discord/audit_log.json:148:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}' */
                &p->rate_limit_per_user,
  /* specs/discord/audit_log.json:149:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}' */
                &p->permissions,
  /* specs/discord/audit_log.json:150:18
     '{"name":"color", "type": {"base":"int"}}' */
                &p->color,
  /* specs/discord/audit_log.json:151:18
     '{"name":"hoist", "type": {"base":"bool"}}' */
                &p->hoist,
  /* specs/discord/audit_log.json:152:18
     '{"name":"mentionable", "type": {"base":"bool"}}' */
                &p->mentionable,
  /* specs/discord/audit_log.json:153:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}' */
                &p->allow,
  /* specs/discord/audit_log.json:154:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}' */
                &p->deny,
  /* specs/discord/audit_log.json:155:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}' */
                &p->code,
  /* specs/discord/audit_log.json:156:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}' */
                &p->channel_id,
  /* specs/discord/audit_log.json:157:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}' */
                &p->inviter_id,
  /* specs/discord/audit_log.json:158:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}' */
                &p->max_uses,
  /* specs/discord/audit_log.json:159:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}' */
                &p->uses,
  /* specs/discord/audit_log.json:160:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}' */
                &p->max_age,
  /* specs/discord/audit_log.json:161:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}' */
                &p->temporary,
  /* specs/discord/audit_log.json:162:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}' */
                &p->deaf,
  /* specs/discord/audit_log.json:163:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}' */
                &p->mute,
  /* specs/discord/audit_log.json:164:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}' */
                &p->nick,
  /* specs/discord/audit_log.json:165:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}' */
                &p->avatar_hash,
  /* specs/discord/audit_log.json:166:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_strtoull, &p->id,
  /* specs/discord/audit_log.json:167:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}' */
  /* specs/discord/audit_log.json:169:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}' */
                &p->enable_emotions,
  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_behavior", "type": {"base":"int"}}' */
                &p->expire_behavior,
  /* specs/discord/audit_log.json:171:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}' */
                &p->expire_grace_period,
  /* specs/discord/audit_log.json:172:18
     '{"name":"user_limit", "type": {"base":"int" }}' */
                &p->user_limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_change_key_use_default_inject_settings(struct discord_audit_log_change_key *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:113:18
     '{"name":"name", "type": {"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
  p->__M.arg_switches[0] = p->name;

  /* specs/discord/audit_log.json:114:18
     '{"name":"description", "type": {"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
  p->__M.arg_switches[1] = p->description;

  /* specs/discord/audit_log.json:115:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "comment":"icon changed" }' */
  p->__M.arg_switches[2] = p->icon_hash;

  /* specs/discord/audit_log.json:117:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"},
         "comment":"invite splash page artwork changed"}' */
  p->__M.arg_switches[3] = p->splash_hash;

  /* specs/discord/audit_log.json:119:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */
  p->__M.arg_switches[4] = p->discovery_splash_hash;

  /* specs/discord/audit_log.json:120:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[5] = &p->banner_hash;

  /* specs/discord/audit_log.json:121:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[6] = &p->owner_id;

  /* specs/discord/audit_log.json:122:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}}' */
  p->__M.arg_switches[7] = p->region;

  /* specs/discord/audit_log.json:123:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}}' */
  p->__M.arg_switches[8] = p->preferred_locale;

  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[9] = &p->afk_channel_id;

  /* specs/discord/audit_log.json:125:18
     '{"name":"afk_timeout", "type": {"base":"int"}}' */
  p->__M.arg_switches[10] = &p->afk_timeout;

  /* specs/discord/audit_log.json:126:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[11] = &p->rules_channel_id;

  /* specs/discord/audit_log.json:127:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[12] = &p->public_updates_channel_id;

  /* specs/discord/audit_log.json:128:18
     '{"name":"mfa_level", "type": {"base":"int"}}' */
  p->__M.arg_switches[13] = &p->mfa_level;

  /* specs/discord/audit_log.json:129:18
     '{"name":"verification_level", "type": {"base":"int"}}' */
  p->__M.arg_switches[14] = &p->verification_level;

  /* specs/discord/audit_log.json:130:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}' */
  p->__M.arg_switches[15] = &p->explicit_content_filter;

  /* specs/discord/audit_log.json:131:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}' */
  p->__M.arg_switches[16] = &p->default_message_notifications;

  /* specs/discord/audit_log.json:132:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[17] = p->vanity_url;

  /* specs/discord/audit_log.json:133:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }' */

  /* specs/discord/audit_log.json:135:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }' */

  /* specs/discord/audit_log.json:137:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}' */
  p->__M.arg_switches[20] = &p->prune_delete_days;

  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}' */
  p->__M.arg_switches[21] = &p->widget_enabled;

  /* specs/discord/audit_log.json:139:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[22] = &p->widget_channel_id;

  /* specs/discord/audit_log.json:140:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[23] = &p->system_channel_id;

  /* specs/discord/audit_log.json:141:18
     '{"name":"position", "type": {"base":"int"}}' */
  p->__M.arg_switches[24] = &p->position;

  /* specs/discord/audit_log.json:142:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[25] = p->topic;

  /* specs/discord/audit_log.json:143:18
     '{"name":"bitrate", "type": {"base":"int"}}' */
  p->__M.arg_switches[26] = &p->bitrate;

  /* specs/discord/audit_log.json:144:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }' */

  /* specs/discord/audit_log.json:146:18
     '{"name":"nsfw", "type": {"base":"bool"}}' */
  p->__M.arg_switches[28] = &p->nsfw;

  /* specs/discord/audit_log.json:147:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[29] = &p->application_id;

  /* specs/discord/audit_log.json:148:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}' */
  p->__M.arg_switches[30] = &p->rate_limit_per_user;

  /* specs/discord/audit_log.json:149:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[31] = p->permissions;

  /* specs/discord/audit_log.json:150:18
     '{"name":"color", "type": {"base":"int"}}' */
  p->__M.arg_switches[32] = &p->color;

  /* specs/discord/audit_log.json:151:18
     '{"name":"hoist", "type": {"base":"bool"}}' */
  p->__M.arg_switches[33] = &p->hoist;

  /* specs/discord/audit_log.json:152:18
     '{"name":"mentionable", "type": {"base":"bool"}}' */
  p->__M.arg_switches[34] = &p->mentionable;

  /* specs/discord/audit_log.json:153:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[35] = p->allow;

  /* specs/discord/audit_log.json:154:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[36] = p->deny;

  /* specs/discord/audit_log.json:155:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[37] = p->code;

  /* specs/discord/audit_log.json:156:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[38] = p->channel_id;

  /* specs/discord/audit_log.json:157:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[39] = p->inviter_id;

  /* specs/discord/audit_log.json:158:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[40] = p->max_uses;

  /* specs/discord/audit_log.json:159:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[41] = p->uses;

  /* specs/discord/audit_log.json:160:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[42] = p->max_age;

  /* specs/discord/audit_log.json:161:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[43] = p->temporary;

  /* specs/discord/audit_log.json:162:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[44] = p->deaf;

  /* specs/discord/audit_log.json:163:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[45] = p->mute;

  /* specs/discord/audit_log.json:164:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[46] = p->nick;

  /* specs/discord/audit_log.json:165:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}' */
  p->__M.arg_switches[47] = p->avatar_hash;

  /* specs/discord/audit_log.json:166:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  p->__M.arg_switches[48] = &p->id;

  /* specs/discord/audit_log.json:167:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}' */

  /* specs/discord/audit_log.json:169:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}' */
  p->__M.arg_switches[50] = &p->enable_emotions;

  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_behavior", "type": {"base":"int"}}' */
  p->__M.arg_switches[51] = &p->expire_behavior;

  /* specs/discord/audit_log.json:171:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}' */
  p->__M.arg_switches[52] = &p->expire_grace_period;

  /* specs/discord/audit_log.json:172:18
     '{"name":"user_limit", "type": {"base":"int" }}' */
  p->__M.arg_switches[53] = &p->user_limit;

}

size_t discord_audit_log_change_key_to_json(char *json, size_t len, struct discord_audit_log_change_key *p)
{
  size_t r;
  discord_audit_log_change_key_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:113:18
     '{"name":"name", "type": {"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
                "(name):s,"
  /* specs/discord/audit_log.json:114:18
     '{"name":"description", "type": {"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
                "(description):s,"
  /* specs/discord/audit_log.json:115:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "comment":"icon changed" }' */
                "(icon_hash):s,"
  /* specs/discord/audit_log.json:117:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"},
         "comment":"invite splash page artwork changed"}' */
                "(splash_hash):s,"
  /* specs/discord/audit_log.json:119:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */
                "(discovery_splash_hash):s,"
  /* specs/discord/audit_log.json:120:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(banner_hash):|F|,"
  /* specs/discord/audit_log.json:121:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(owner_id):|F|,"
  /* specs/discord/audit_log.json:122:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}}' */
                "(region):s,"
  /* specs/discord/audit_log.json:123:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}}' */
                "(preferred_locale):s,"
  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(afk_channel_id):|F|,"
  /* specs/discord/audit_log.json:125:18
     '{"name":"afk_timeout", "type": {"base":"int"}}' */
                "(afk_timeout):d,"
  /* specs/discord/audit_log.json:126:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(rules_channel_id):|F|,"
  /* specs/discord/audit_log.json:127:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(public_updates_channel_id):|F|,"
  /* specs/discord/audit_log.json:128:18
     '{"name":"mfa_level", "type": {"base":"int"}}' */
                "(mfa_level):d,"
  /* specs/discord/audit_log.json:129:18
     '{"name":"verification_level", "type": {"base":"int"}}' */
                "(verification_level):d,"
  /* specs/discord/audit_log.json:130:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}' */
                "(explicit_content_filter):d,"
  /* specs/discord/audit_log.json:131:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}' */
                "(default_message_notifications):d,"
  /* specs/discord/audit_log.json:132:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}' */
                "(vanity_url):s,"
  /* specs/discord/audit_log.json:133:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:135:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:137:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}' */
                "(prune_delete_days):d,"
  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}' */
                "(widget_enabled):b,"
  /* specs/discord/audit_log.json:139:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(widget_channel_id):|F|,"
  /* specs/discord/audit_log.json:140:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(system_channel_id):|F|,"
  /* specs/discord/audit_log.json:141:18
     '{"name":"position", "type": {"base":"int"}}' */
                "(position):d,"
  /* specs/discord/audit_log.json:142:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}' */
                "(topic):s,"
  /* specs/discord/audit_log.json:143:18
     '{"name":"bitrate", "type": {"base":"int"}}' */
                "(bitrate):d,"
  /* specs/discord/audit_log.json:144:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:146:18
     '{"name":"nsfw", "type": {"base":"bool"}}' */
                "(nsfw):b,"
  /* specs/discord/audit_log.json:147:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(application_id):|F|,"
  /* specs/discord/audit_log.json:148:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}' */
                "(rate_limit_per_user):d,"
  /* specs/discord/audit_log.json:149:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}' */
                "(permissions):s,"
  /* specs/discord/audit_log.json:150:18
     '{"name":"color", "type": {"base":"int"}}' */
                "(color):d,"
  /* specs/discord/audit_log.json:151:18
     '{"name":"hoist", "type": {"base":"bool"}}' */
                "(hoist):b,"
  /* specs/discord/audit_log.json:152:18
     '{"name":"mentionable", "type": {"base":"bool"}}' */
                "(mentionable):b,"
  /* specs/discord/audit_log.json:153:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}' */
                "(allow):s,"
  /* specs/discord/audit_log.json:154:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}' */
                "(deny):s,"
  /* specs/discord/audit_log.json:155:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}' */
                "(code):s,"
  /* specs/discord/audit_log.json:156:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}' */
                "(channel_id):s,"
  /* specs/discord/audit_log.json:157:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}' */
                "(inviter_id):s,"
  /* specs/discord/audit_log.json:158:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}' */
                "(max_uses):s,"
  /* specs/discord/audit_log.json:159:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}' */
                "(uses):s,"
  /* specs/discord/audit_log.json:160:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}' */
                "(max_age):s,"
  /* specs/discord/audit_log.json:161:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}' */
                "(temporary):s,"
  /* specs/discord/audit_log.json:162:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}' */
                "(deaf):s,"
  /* specs/discord/audit_log.json:163:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}' */
                "(mute):s,"
  /* specs/discord/audit_log.json:164:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}' */
                "(nick):s,"
  /* specs/discord/audit_log.json:165:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}' */
                "(avatar_hash):s,"
  /* specs/discord/audit_log.json:166:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                "(id):|F|,"
  /* specs/discord/audit_log.json:167:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}' */
  /* specs/discord/audit_log.json:169:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}' */
                "(enable_emotions):b,"
  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_behavior", "type": {"base":"int"}}' */
                "(expire_behavior):d,"
  /* specs/discord/audit_log.json:171:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}' */
                "(expire_grace_period):d,"
  /* specs/discord/audit_log.json:172:18
     '{"name":"user_limit", "type": {"base":"int" }}' */
                "(user_limit):d,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:113:18
     '{"name":"name", "type": {"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
                p->name,
  /* specs/discord/audit_log.json:114:18
     '{"name":"description", "type": {"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
                p->description,
  /* specs/discord/audit_log.json:115:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "comment":"icon changed" }' */
                p->icon_hash,
  /* specs/discord/audit_log.json:117:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"},
         "comment":"invite splash page artwork changed"}' */
                p->splash_hash,
  /* specs/discord/audit_log.json:119:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */
                p->discovery_splash_hash,
  /* specs/discord/audit_log.json:120:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->banner_hash,
  /* specs/discord/audit_log.json:121:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->owner_id,
  /* specs/discord/audit_log.json:122:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}}' */
                p->region,
  /* specs/discord/audit_log.json:123:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}}' */
                p->preferred_locale,
  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->afk_channel_id,
  /* specs/discord/audit_log.json:125:18
     '{"name":"afk_timeout", "type": {"base":"int"}}' */
                &p->afk_timeout,
  /* specs/discord/audit_log.json:126:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->rules_channel_id,
  /* specs/discord/audit_log.json:127:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->public_updates_channel_id,
  /* specs/discord/audit_log.json:128:18
     '{"name":"mfa_level", "type": {"base":"int"}}' */
                &p->mfa_level,
  /* specs/discord/audit_log.json:129:18
     '{"name":"verification_level", "type": {"base":"int"}}' */
                &p->verification_level,
  /* specs/discord/audit_log.json:130:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}' */
                &p->explicit_content_filter,
  /* specs/discord/audit_log.json:131:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}' */
                &p->default_message_notifications,
  /* specs/discord/audit_log.json:132:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}' */
                p->vanity_url,
  /* specs/discord/audit_log.json:133:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:135:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:137:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}' */
                &p->prune_delete_days,
  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}' */
                &p->widget_enabled,
  /* specs/discord/audit_log.json:139:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->widget_channel_id,
  /* specs/discord/audit_log.json:140:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->system_channel_id,
  /* specs/discord/audit_log.json:141:18
     '{"name":"position", "type": {"base":"int"}}' */
                &p->position,
  /* specs/discord/audit_log.json:142:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}' */
                p->topic,
  /* specs/discord/audit_log.json:143:18
     '{"name":"bitrate", "type": {"base":"int"}}' */
                &p->bitrate,
  /* specs/discord/audit_log.json:144:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  /* specs/discord/audit_log.json:146:18
     '{"name":"nsfw", "type": {"base":"bool"}}' */
                &p->nsfw,
  /* specs/discord/audit_log.json:147:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/audit_log.json:148:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}' */
                &p->rate_limit_per_user,
  /* specs/discord/audit_log.json:149:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}' */
                p->permissions,
  /* specs/discord/audit_log.json:150:18
     '{"name":"color", "type": {"base":"int"}}' */
                &p->color,
  /* specs/discord/audit_log.json:151:18
     '{"name":"hoist", "type": {"base":"bool"}}' */
                &p->hoist,
  /* specs/discord/audit_log.json:152:18
     '{"name":"mentionable", "type": {"base":"bool"}}' */
                &p->mentionable,
  /* specs/discord/audit_log.json:153:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}' */
                p->allow,
  /* specs/discord/audit_log.json:154:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}' */
                p->deny,
  /* specs/discord/audit_log.json:155:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}' */
                p->code,
  /* specs/discord/audit_log.json:156:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}' */
                p->channel_id,
  /* specs/discord/audit_log.json:157:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}' */
                p->inviter_id,
  /* specs/discord/audit_log.json:158:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}' */
                p->max_uses,
  /* specs/discord/audit_log.json:159:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}' */
                p->uses,
  /* specs/discord/audit_log.json:160:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}' */
                p->max_age,
  /* specs/discord/audit_log.json:161:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}' */
                p->temporary,
  /* specs/discord/audit_log.json:162:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}' */
                p->deaf,
  /* specs/discord/audit_log.json:163:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}' */
                p->mute,
  /* specs/discord/audit_log.json:164:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}' */
                p->nick,
  /* specs/discord/audit_log.json:165:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}' */
                p->avatar_hash,
  /* specs/discord/audit_log.json:166:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
                cee_ulltostr, &p->id,
  /* specs/discord/audit_log.json:167:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}' */
  /* specs/discord/audit_log.json:169:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}' */
                &p->enable_emotions,
  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_behavior", "type": {"base":"int"}}' */
                &p->expire_behavior,
  /* specs/discord/audit_log.json:171:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}' */
                &p->expire_grace_period,
  /* specs/discord/audit_log.json:172:18
     '{"name":"user_limit", "type": {"base":"int" }}' */
                &p->user_limit,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_audit_log_change_key_cleanup_v(void *p) {
  discord_audit_log_change_key_cleanup((struct discord_audit_log_change_key *)p);
}

void discord_audit_log_change_key_init_v(void *p) {
  discord_audit_log_change_key_init((struct discord_audit_log_change_key *)p);
}

void discord_audit_log_change_key_from_json_v(char *json, size_t len, void *pp) {
 discord_audit_log_change_key_from_json(json, len, (struct discord_audit_log_change_key**)pp);
}

size_t discord_audit_log_change_key_to_json_v(char *json, size_t len, void *p) {
  return discord_audit_log_change_key_to_json(json, len, (struct discord_audit_log_change_key*)p);
}

void discord_audit_log_change_key_list_free_v(void **p) {
  discord_audit_log_change_key_list_free((struct discord_audit_log_change_key**)p);
}

void discord_audit_log_change_key_list_from_json_v(char *str, size_t len, void *p) {
  discord_audit_log_change_key_list_from_json(str, len, (struct discord_audit_log_change_key ***)p);
}

size_t discord_audit_log_change_key_list_to_json_v(char *str, size_t len, void *p){
  return discord_audit_log_change_key_list_to_json(str, len, (struct discord_audit_log_change_key **)p);
}


void discord_audit_log_change_key_cleanup(struct discord_audit_log_change_key *d) {
  /* specs/discord/audit_log.json:113:18
     '{"name":"name", "type": {"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */
  // p->name is a scalar
  /* specs/discord/audit_log.json:114:18
     '{"name":"description", "type": {"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */
  // p->description is a scalar
  /* specs/discord/audit_log.json:115:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "comment":"icon changed" }' */
  // p->icon_hash is a scalar
  /* specs/discord/audit_log.json:117:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"},
         "comment":"invite splash page artwork changed"}' */
  // p->splash_hash is a scalar
  /* specs/discord/audit_log.json:119:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */
  // p->discovery_splash_hash is a scalar
  /* specs/discord/audit_log.json:120:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->banner_hash is a scalar
  /* specs/discord/audit_log.json:121:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->owner_id is a scalar
  /* specs/discord/audit_log.json:122:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}}' */
  // p->region is a scalar
  /* specs/discord/audit_log.json:123:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}}' */
  // p->preferred_locale is a scalar
  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->afk_channel_id is a scalar
  /* specs/discord/audit_log.json:125:18
     '{"name":"afk_timeout", "type": {"base":"int"}}' */
  // p->afk_timeout is a scalar
  /* specs/discord/audit_log.json:126:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->rules_channel_id is a scalar
  /* specs/discord/audit_log.json:127:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->public_updates_channel_id is a scalar
  /* specs/discord/audit_log.json:128:18
     '{"name":"mfa_level", "type": {"base":"int"}}' */
  // p->mfa_level is a scalar
  /* specs/discord/audit_log.json:129:18
     '{"name":"verification_level", "type": {"base":"int"}}' */
  // p->verification_level is a scalar
  /* specs/discord/audit_log.json:130:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}' */
  // p->explicit_content_filter is a scalar
  /* specs/discord/audit_log.json:131:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}' */
  // p->default_message_notifications is a scalar
  /* specs/discord/audit_log.json:132:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}' */
  if (d->vanity_url)
    free(d->vanity_url);
  /* specs/discord/audit_log.json:133:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  // @todo p->(null)
  /* specs/discord/audit_log.json:135:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  // @todo p->(null)
  /* specs/discord/audit_log.json:137:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}' */
  // p->prune_delete_days is a scalar
  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}' */
  // p->widget_enabled is a scalar
  /* specs/discord/audit_log.json:139:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->widget_channel_id is a scalar
  /* specs/discord/audit_log.json:140:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->system_channel_id is a scalar
  /* specs/discord/audit_log.json:141:18
     '{"name":"position", "type": {"base":"int"}}' */
  // p->position is a scalar
  /* specs/discord/audit_log.json:142:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}' */
  if (d->topic)
    free(d->topic);
  /* specs/discord/audit_log.json:143:18
     '{"name":"bitrate", "type": {"base":"int"}}' */
  // p->bitrate is a scalar
  /* specs/discord/audit_log.json:144:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }' */
  // @todo p->(null)
  /* specs/discord/audit_log.json:146:18
     '{"name":"nsfw", "type": {"base":"bool"}}' */
  // p->nsfw is a scalar
  /* specs/discord/audit_log.json:147:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->application_id is a scalar
  /* specs/discord/audit_log.json:148:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}' */
  // p->rate_limit_per_user is a scalar
  /* specs/discord/audit_log.json:149:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}' */
  if (d->permissions)
    free(d->permissions);
  /* specs/discord/audit_log.json:150:18
     '{"name":"color", "type": {"base":"int"}}' */
  // p->color is a scalar
  /* specs/discord/audit_log.json:151:18
     '{"name":"hoist", "type": {"base":"bool"}}' */
  // p->hoist is a scalar
  /* specs/discord/audit_log.json:152:18
     '{"name":"mentionable", "type": {"base":"bool"}}' */
  // p->mentionable is a scalar
  /* specs/discord/audit_log.json:153:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}' */
  if (d->allow)
    free(d->allow);
  /* specs/discord/audit_log.json:154:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}' */
  if (d->deny)
    free(d->deny);
  /* specs/discord/audit_log.json:155:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}' */
  if (d->code)
    free(d->code);
  /* specs/discord/audit_log.json:156:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}' */
  if (d->channel_id)
    free(d->channel_id);
  /* specs/discord/audit_log.json:157:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}' */
  if (d->inviter_id)
    free(d->inviter_id);
  /* specs/discord/audit_log.json:158:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}' */
  if (d->max_uses)
    free(d->max_uses);
  /* specs/discord/audit_log.json:159:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}' */
  if (d->uses)
    free(d->uses);
  /* specs/discord/audit_log.json:160:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}' */
  if (d->max_age)
    free(d->max_age);
  /* specs/discord/audit_log.json:161:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}' */
  if (d->temporary)
    free(d->temporary);
  /* specs/discord/audit_log.json:162:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}' */
  if (d->deaf)
    free(d->deaf);
  /* specs/discord/audit_log.json:163:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}' */
  if (d->mute)
    free(d->mute);
  /* specs/discord/audit_log.json:164:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}' */
  if (d->nick)
    free(d->nick);
  /* specs/discord/audit_log.json:165:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}' */
  if (d->avatar_hash)
    free(d->avatar_hash);
  /* specs/discord/audit_log.json:166:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */
  // p->id is a scalar
  /* specs/discord/audit_log.json:167:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}' */
  // @todo p->(null)
  /* specs/discord/audit_log.json:169:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}' */
  // p->enable_emotions is a scalar
  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_behavior", "type": {"base":"int"}}' */
  // p->expire_behavior is a scalar
  /* specs/discord/audit_log.json:171:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}' */
  // p->expire_grace_period is a scalar
  /* specs/discord/audit_log.json:172:18
     '{"name":"user_limit", "type": {"base":"int" }}' */
  // p->user_limit is a scalar
}

void discord_audit_log_change_key_init(struct discord_audit_log_change_key *p) {
  memset(p, 0, sizeof(struct discord_audit_log_change_key));
  /* specs/discord/audit_log.json:113:18
     '{"name":"name", "type": {"base":"char", "dec":"[DISCORD_MAX_NAME_LEN]"}}' */

  /* specs/discord/audit_log.json:114:18
     '{"name":"description", "type": {"base":"char", "dec":"[DISCORD_MAX_DESCRIPTION_LEN]"}}' */

  /* specs/discord/audit_log.json:115:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, 
         "comment":"icon changed" }' */

  /* specs/discord/audit_log.json:117:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"},
         "comment":"invite splash page artwork changed"}' */

  /* specs/discord/audit_log.json:119:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}}' */

  /* specs/discord/audit_log.json:120:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:121:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:122:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}}' */

  /* specs/discord/audit_log.json:123:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}}' */

  /* specs/discord/audit_log.json:124:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:125:18
     '{"name":"afk_timeout", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:126:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:127:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:128:18
     '{"name":"mfa_level", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:129:18
     '{"name":"verification_level", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:130:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:131:18
     '{"name":"default_message_notifications", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:132:18
     '{"name":"vanity_url", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:133:18
     '{"name":"add", "json_key":"$add", "type": {"base":"char", "dec":"*"},
         "todo":true }' */

  /* specs/discord/audit_log.json:135:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"char", "dec":"*"},
         "todo":true }' */

  /* specs/discord/audit_log.json:137:18
     '{"name":"prune_delete_days", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:138:18
     '{"name":"widget_enabled", "type": {"base":"bool"}}' */

  /* specs/discord/audit_log.json:139:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:140:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:141:18
     '{"name":"position", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:142:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:143:18
     '{"name":"bitrate", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:144:18
     '{"name":"permission_overwrites", "type": {"base":"char", "dec":"*"},
         "todo":true }' */

  /* specs/discord/audit_log.json:146:18
     '{"name":"nsfw", "type": {"base":"bool"}}' */

  /* specs/discord/audit_log.json:147:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:148:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:149:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:150:18
     '{"name":"color", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:151:18
     '{"name":"hoist", "type": {"base":"bool"}}' */

  /* specs/discord/audit_log.json:152:18
     '{"name":"mentionable", "type": {"base":"bool"}}' */

  /* specs/discord/audit_log.json:153:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:154:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:155:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:156:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:157:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:158:18
     '{"name":"max_uses", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:159:18
     '{"name":"uses", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:160:18
     '{"name":"max_age", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:161:18
     '{"name":"temporary", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:162:18
     '{"name":"deaf", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:163:18
     '{"name":"mute", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:164:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:165:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"*"}}' */

  /* specs/discord/audit_log.json:166:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}}' */

  /* specs/discord/audit_log.json:167:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, 
         "todo":true, "comment":"integer or string"}' */

  /* specs/discord/audit_log.json:169:18
     '{"name":"enable_emotions", "type": {"base":"bool"}}' */

  /* specs/discord/audit_log.json:170:18
     '{"name":"expire_behavior", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:171:18
     '{"name":"expire_grace_period", "type": {"base":"int"}}' */

  /* specs/discord/audit_log.json:172:18
     '{"name":"user_limit", "type": {"base":"int" }}' */

}
void discord_audit_log_change_key_list_free(struct discord_audit_log_change_key **p) {
  ntl_free((void**)p, (vfvp)discord_audit_log_change_key_cleanup);
}

void discord_audit_log_change_key_list_from_json(char *str, size_t len, struct discord_audit_log_change_key ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_audit_log_change_key);
  d.init_elem = NULL;
  d.elem_from_buf = discord_audit_log_change_key_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_audit_log_change_key_list_to_json(char *str, size_t len, struct discord_audit_log_change_key **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_audit_log_change_key_to_json_v);
}

