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
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
                "(webhooks):F,"
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
                "(users):F,"
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
                "(audit_log_entries):F,"
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
                "(integrations):F,"
  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
                "(threads):F,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
                discord_webhook_list_from_json, &p->webhooks,
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
                discord_user_list_from_json, &p->users,
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
                discord_audit_log_entry_list_from_json, &p->audit_log_entries,
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
                discord_integration_list_from_json, &p->integrations,
  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
                discord_channel_list_from_json, &p->threads,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_use_default_inject_settings(struct discord_audit_log *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
  if (p->webhooks != NULL)
    p->__M.arg_switches[0] = p->webhooks;

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
  if (p->users != NULL)
    p->__M.arg_switches[1] = p->users;

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
  if (p->audit_log_entries != NULL)
    p->__M.arg_switches[2] = p->audit_log_entries;

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
  if (p->integrations != NULL)
    p->__M.arg_switches[3] = p->integrations;

  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
  if (p->threads != NULL)
    p->__M.arg_switches[4] = p->threads;

}

size_t discord_audit_log_to_json(char *json, size_t len, struct discord_audit_log *p)
{
  size_t r;
  discord_audit_log_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
                "(webhooks):F,"
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
                "(users):F,"
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
                "(audit_log_entries):F,"
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
                "(integrations):F,"
  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
                "(threads):F,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
                discord_webhook_list_to_json, p->webhooks,
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
                discord_user_list_to_json, p->users,
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
                discord_audit_log_entry_list_to_json, p->audit_log_entries,
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
                discord_integration_list_to_json, p->integrations,
  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
                discord_channel_list_to_json, p->threads,
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
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
  if (d->webhooks)
    discord_webhook_list_free(d->webhooks);
  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
  if (d->users)
    discord_user_list_free(d->users);
  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
  if (d->audit_log_entries)
    discord_audit_log_entry_list_free(d->audit_log_entries);
  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
  if (d->integrations)
    discord_integration_list_free(d->integrations);
  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
  if (d->threads)
    discord_channel_list_free(d->threads);
}

void discord_audit_log_init(struct discord_audit_log *p) {
  memset(p, 0, sizeof(struct discord_audit_log));
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */

  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */

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


void discord_audit_log_entry_from_json(char *json, size_t len, struct discord_audit_log_entry **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_audit_log_entry *p = *pp;
  discord_audit_log_entry_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
                "(target_id):?s,"
  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
                "(changes):F,"
  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
                "(user_id):F,"
  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
                "(id):F,"
  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
                "(action_type):d,"
  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
                "(options):F,"
  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}, "comment":"the reason for the change", "inject_if_not":"" }' */
                "(reason):s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
                &p->target_id,
  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
                discord_audit_log_change_list_from_json, &p->changes,
  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
                cee_strtoull, &p->user_id,
  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
                cee_strtoull, &p->id,
  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
                &p->action_type,
  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
                discord_optional_audit_entry_info_list_from_json, &p->options,
  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}, "comment":"the reason for the change", "inject_if_not":"" }' */
                p->reason,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_entry_use_default_inject_settings(struct discord_audit_log_entry *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
  if (p->target_id != NULL)
    p->__M.arg_switches[0] = p->target_id;

  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
  if (p->changes != NULL)
    p->__M.arg_switches[1] = p->changes;

  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
  if (p->user_id != 0)
    p->__M.arg_switches[2] = &p->user_id;

  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
  if (p->id != 0)
    p->__M.arg_switches[3] = &p->id;

  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
  if (p->action_type != 0)
    p->__M.arg_switches[4] = &p->action_type;

  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
  if (p->options != NULL)
    p->__M.arg_switches[5] = p->options;

  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}, "comment":"the reason for the change", "inject_if_not":"" }' */
  if (*p->reason)
    p->__M.arg_switches[6] = p->reason;

}

size_t discord_audit_log_entry_to_json(char *json, size_t len, struct discord_audit_log_entry *p)
{
  size_t r;
  discord_audit_log_entry_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
                "(target_id):s,"
  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
                "(changes):F,"
  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
                "(user_id):|F|,"
  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
                "(id):|F|,"
  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
                "(action_type):d,"
  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
                "(options):F,"
  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}, "comment":"the reason for the change", "inject_if_not":"" }' */
                "(reason):s,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
                p->target_id,
  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
                discord_audit_log_change_list_to_json, p->changes,
  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
                cee_ulltostr, &p->user_id,
  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
                cee_ulltostr, &p->id,
  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
                &p->action_type,
  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
                discord_optional_audit_entry_info_list_to_json, p->options,
  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}, "comment":"the reason for the change", "inject_if_not":"" }' */
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
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
  if (d->target_id)
    free(d->target_id);
  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
  if (d->changes)
    discord_audit_log_change_list_free(d->changes);
  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
  // p->user_id is a scalar
  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
  // p->id is a scalar
  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
  // p->action_type is a scalar
  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
  if (d->options)
    discord_optional_audit_entry_info_list_free(d->options);
  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}, "comment":"the reason for the change", "inject_if_not":"" }' */
  // p->reason is a scalar
}

void discord_audit_log_entry_init(struct discord_audit_log_entry *p) {
  memset(p, 0, sizeof(struct discord_audit_log_entry));
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"[DISCORD_MAX_REASON_LEN]"}, "comment":"the reason for the change", "inject_if_not":"" }' */

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
  if(strcasecmp("STAGE_INSTANCE_CREATE", s) == 0) return DISCORD_AUDIT_LOG_STAGE_INSTANCE_CREATE;
  if(strcasecmp("STAGE_INSTANCE_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_STAGE_INSTANCE_UPDATE;
  if(strcasecmp("STAGE_INSTANCE_DELETE", s) == 0) return DISCORD_AUDIT_LOG_STAGE_INSTANCE_DELETE;
  if(strcasecmp("STICKER_CREATE", s) == 0) return DISCORD_AUDIT_LOG_STICKER_CREATE;
  if(strcasecmp("STICKER_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_STICKER_UPDATE;
  if(strcasecmp("STICKER_DELETE", s) == 0) return DISCORD_AUDIT_LOG_STICKER_DELETE;
  if(strcasecmp("THREAD_CREATE", s) == 0) return DISCORD_AUDIT_LOG_THREAD_CREATE;
  if(strcasecmp("THREAD_UPDATE", s) == 0) return DISCORD_AUDIT_LOG_THREAD_UPDATE;
  if(strcasecmp("THREAD_DELETE", s) == 0) return DISCORD_AUDIT_LOG_THREAD_DELETE;
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
  case DISCORD_AUDIT_LOG_STAGE_INSTANCE_CREATE: return "STAGE_INSTANCE_CREATE";
  case DISCORD_AUDIT_LOG_STAGE_INSTANCE_UPDATE: return "STAGE_INSTANCE_UPDATE";
  case DISCORD_AUDIT_LOG_STAGE_INSTANCE_DELETE: return "STAGE_INSTANCE_DELETE";
  case DISCORD_AUDIT_LOG_STICKER_CREATE: return "STICKER_CREATE";
  case DISCORD_AUDIT_LOG_STICKER_UPDATE: return "STICKER_UPDATE";
  case DISCORD_AUDIT_LOG_STICKER_DELETE: return "STICKER_DELETE";
  case DISCORD_AUDIT_LOG_THREAD_CREATE: return "THREAD_CREATE";
  case DISCORD_AUDIT_LOG_THREAD_UPDATE: return "THREAD_UPDATE";
  case DISCORD_AUDIT_LOG_THREAD_DELETE: return "THREAD_DELETE";
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


void discord_optional_audit_entry_info_from_json(char *json, size_t len, struct discord_optional_audit_entry_info **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_optional_audit_entry_info *p = *pp;
  discord_optional_audit_entry_info_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
                "(delete_member_days):?s,"
  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
                "(members_removed):?s,"
  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
                "(channel_id):F,"
  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
                "(message_id):F,"
  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
                "(count):?s,"
  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
                "(id):F,"
  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
                "(type):?s,"
  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
                "(role_name):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
                &p->delete_member_days,
  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
                &p->members_removed,
  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
                cee_strtoull, &p->message_id,
  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
                &p->count,
  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
                cee_strtoull, &p->id,
  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
                &p->type,
  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
                &p->role_name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_optional_audit_entry_info_use_default_inject_settings(struct discord_optional_audit_entry_info *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
  if (p->delete_member_days != NULL)
    p->__M.arg_switches[0] = p->delete_member_days;

  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
  if (p->members_removed != NULL)
    p->__M.arg_switches[1] = p->members_removed;

  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
  if (p->channel_id != 0)
    p->__M.arg_switches[2] = &p->channel_id;

  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
  if (p->message_id != 0)
    p->__M.arg_switches[3] = &p->message_id;

  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
  if (p->count != NULL)
    p->__M.arg_switches[4] = p->count;

  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
  if (p->id != 0)
    p->__M.arg_switches[5] = &p->id;

  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
  if (p->type != NULL)
    p->__M.arg_switches[6] = p->type;

  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
  if (p->role_name != NULL)
    p->__M.arg_switches[7] = p->role_name;

}

size_t discord_optional_audit_entry_info_to_json(char *json, size_t len, struct discord_optional_audit_entry_info *p)
{
  size_t r;
  discord_optional_audit_entry_info_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
                "(delete_member_days):s,"
  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
                "(members_removed):s,"
  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
                "(channel_id):|F|,"
  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
                "(message_id):|F|,"
  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
                "(count):s,"
  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
                "(id):|F|,"
  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
                "(type):s,"
  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
                "(role_name):s,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
                p->delete_member_days,
  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
                p->members_removed,
  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
                cee_ulltostr, &p->message_id,
  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
                p->count,
  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
                cee_ulltostr, &p->id,
  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
                p->type,
  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
                p->role_name,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches);
  return r;
}


typedef void (*vfvp)(void *);
typedef void (*vfcpsvp)(char *, size_t, void *);
typedef size_t (*sfcpsvp)(char *, size_t, void *);
void discord_optional_audit_entry_info_cleanup_v(void *p) {
  discord_optional_audit_entry_info_cleanup((struct discord_optional_audit_entry_info *)p);
}

void discord_optional_audit_entry_info_init_v(void *p) {
  discord_optional_audit_entry_info_init((struct discord_optional_audit_entry_info *)p);
}

void discord_optional_audit_entry_info_from_json_v(char *json, size_t len, void *pp) {
 discord_optional_audit_entry_info_from_json(json, len, (struct discord_optional_audit_entry_info**)pp);
}

size_t discord_optional_audit_entry_info_to_json_v(char *json, size_t len, void *p) {
  return discord_optional_audit_entry_info_to_json(json, len, (struct discord_optional_audit_entry_info*)p);
}

void discord_optional_audit_entry_info_list_free_v(void **p) {
  discord_optional_audit_entry_info_list_free((struct discord_optional_audit_entry_info**)p);
}

void discord_optional_audit_entry_info_list_from_json_v(char *str, size_t len, void *p) {
  discord_optional_audit_entry_info_list_from_json(str, len, (struct discord_optional_audit_entry_info ***)p);
}

size_t discord_optional_audit_entry_info_list_to_json_v(char *str, size_t len, void *p){
  return discord_optional_audit_entry_info_list_to_json(str, len, (struct discord_optional_audit_entry_info **)p);
}


void discord_optional_audit_entry_info_cleanup(struct discord_optional_audit_entry_info *d) {
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
  if (d->delete_member_days)
    free(d->delete_member_days);
  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
  if (d->members_removed)
    free(d->members_removed);
  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
  // p->channel_id is a scalar
  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
  // p->message_id is a scalar
  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
  if (d->count)
    free(d->count);
  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
  // p->id is a scalar
  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
  if (d->type)
    free(d->type);
  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
  if (d->role_name)
    free(d->role_name);
}

void discord_optional_audit_entry_info_init(struct discord_optional_audit_entry_info *p) {
  memset(p, 0, sizeof(struct discord_optional_audit_entry_info));
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */

}
void discord_optional_audit_entry_info_list_free(struct discord_optional_audit_entry_info **p) {
  ntl_free((void**)p, (vfvp)discord_optional_audit_entry_info_cleanup);
}

void discord_optional_audit_entry_info_list_from_json(char *str, size_t len, struct discord_optional_audit_entry_info ***p)
{
  struct ntl_deserializer d;
  memset(&d, 0, sizeof(d));
  d.elem_size = sizeof(struct discord_optional_audit_entry_info);
  d.init_elem = NULL;
  d.elem_from_buf = discord_optional_audit_entry_info_from_json_v;
  d.ntl_recipient_p= (void***)p;
  extract_ntl_from_json2(str, len, &d);
}

size_t discord_optional_audit_entry_info_list_to_json(char *str, size_t len, struct discord_optional_audit_entry_info **p)
{
  return ntl_to_buf(str, len, (void **)p, NULL, discord_optional_audit_entry_info_to_json_v);
}


void discord_audit_log_change_from_json(char *json, size_t len, struct discord_audit_log_change **pp)
{
  static size_t ret=0; // used for debugging
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_audit_log_change *p = *pp;
  discord_audit_log_change_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}, "comment":"new value of the key", "inject_if_not":null }' */
                "(new_value):?s,"
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}, "comment":"old value of the key", "inject_if_not":null }' */
                "(old_value):?s,"
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
                "(key):?s,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}, "comment":"new value of the key", "inject_if_not":null }' */
                &p->new_value,
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}, "comment":"old value of the key", "inject_if_not":null }' */
                &p->old_value,
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
                &p->key,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_change_use_default_inject_settings(struct discord_audit_log_change *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}, "comment":"new value of the key", "inject_if_not":null }' */
  if (p->new_value != NULL)
    p->__M.arg_switches[0] = p->new_value;

  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}, "comment":"old value of the key", "inject_if_not":null }' */
  if (p->old_value != NULL)
    p->__M.arg_switches[1] = p->old_value;

  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
  if (p->key != NULL)
    p->__M.arg_switches[2] = p->key;

}

size_t discord_audit_log_change_to_json(char *json, size_t len, struct discord_audit_log_change *p)
{
  size_t r;
  discord_audit_log_change_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}, "comment":"new value of the key", "inject_if_not":null }' */
                "(new_value):s,"
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}, "comment":"old value of the key", "inject_if_not":null }' */
                "(old_value):s,"
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
                "(key):s,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}, "comment":"new value of the key", "inject_if_not":null }' */
                p->new_value,
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}, "comment":"old value of the key", "inject_if_not":null }' */
                p->old_value,
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
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
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}, "comment":"new value of the key", "inject_if_not":null }' */
  if (d->new_value)
    free(d->new_value);
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}, "comment":"old value of the key", "inject_if_not":null }' */
  if (d->old_value)
    free(d->old_value);
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
  if (d->key)
    free(d->key);
}

void discord_audit_log_change_init(struct discord_audit_log_change *p) {
  memset(p, 0, sizeof(struct discord_audit_log_change));
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*"}, "comment":"new value of the key", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*"}, "comment":"old value of the key", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */

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
  /* specs/discord/audit_log.json:123:18
     '{"name":"name", "type": {"base":"char", "dec":"*"}, "comment":"name changed", "inject_if_not":null }' */
                "(name):?s,"
  /* specs/discord/audit_log.json:124:18
     '{"name":"description", "type": {"base":"char", "dec":"*"}, "comment":"description changed", "inject_if_not":null }' */
                "(description):?s,"
  /* specs/discord/audit_log.json:125:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"icon changed", "inject_if_not":"" }' */
                "(icon_hash):s,"
  /* specs/discord/audit_log.json:126:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"invite splash page artwork changed", "inject_if_not":"" }' */
                "(splash_hash):s,"
  /* specs/discord/audit_log.json:127:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"discovery splash changed", "inject_if_not":"" }' */
                "(discovery_splash_hash):s,"
  /* specs/discord/audit_log.json:128:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"guild banned changed", "inject_if_not":"" }' */
                "(banner_hash):s,"
  /* specs/discord/audit_log.json:129:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"owner changed", "inject_if_not":0 }' */
                "(owner_id):F,"
  /* specs/discord/audit_log.json:130:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "comment":"region changed", "inject_if_not":"" }' */
                "(region):s,"
  /* specs/discord/audit_log.json:131:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "comment":"preferred locale changed", "inject_if_not":"" }' */
                "(preferred_locale):s,"
  /* specs/discord/audit_log.json:132:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"afk channel changed", "inject_if_not":0 }' */
                "(afk_channel_id):F,"
  /* specs/discord/audit_log.json:133:18
     '{"name":"afk_timeout", "type": {"base":"int"}, "comment":"afk timeout duration changed", "inject_if_not":0 }' */
                "(afk_timeout):d,"
  /* specs/discord/audit_log.json:134:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the rules channel changed", "inject_if_not":0 }' */
                "(rules_channel_id):F,"
  /* specs/discord/audit_log.json:135:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the public updates channel changed", "inject_if_not":0 }' */
                "(public_updates_channel_id):F,"
  /* specs/discord/audit_log.json:136:18
     '{"name":"mfa_level", "type": {"base":"int"}, "comment":"two-factor auth requirement changed", "inject_if_not":0 }' */
                "(mfa_level):d,"
  /* specs/discord/audit_log.json:137:18
     '{"name":"verification_level", "type": {"base":"int"}, "comment":"required verification level changed", "inject_if_not":0 }' */
                "(verification_level):d,"
  /* specs/discord/audit_log.json:138:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}, "comment":"change in whose messages are scanned and deleted for explicit content in the server", "inject_if_not":0 }' */
                "(explicit_content_filter):d,"
  /* specs/discord/audit_log.json:139:18
     '{"name":"default_message_notifications", "type": {"base":"int"}, "comment":"default message notification level changed", "inject_if_not":0 }' */
                "(default_message_notifications):d,"
  /* specs/discord/audit_log.json:140:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}, "comment":"guild invite vanity url changed", "inject_if_not":null }' */
                "(vanity_url_code):?s,"
  /* specs/discord/audit_log.json:141:18
     '{"name":"add", "json_key":"$add", "type": {"base":"struct discord_role", "dec":"ntl" }, "comment":"new role added", "inject_if_not":null }' */
                "($add):F,"
  /* specs/discord/audit_log.json:142:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"struct discord_role", "dec":"ntl"}, "comment":"role removed", "inject_if_not":null }' */
                "($remove):F,"
  /* specs/discord/audit_log.json:143:18
     '{"name":"prune_delete_days", "type": {"base":"int"}, "comment":"change in number of days after which inactive and role-unassigned members are kicked", "inject_if_not":0 }' */
                "(prune_delete_days):d,"
  /* specs/discord/audit_log.json:144:18
     '{"name":"widget_enabled", "type": {"base":"bool"}, "comment":"server widget enabled/disable"}' */
                "(widget_enabled):b,"
  /* specs/discord/audit_log.json:145:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel id of the server widget changed", "inject_if_not":0 }' */
                "(widget_channel_id):F,"
  /* specs/discord/audit_log.json:146:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the system channel changed", "inject_if_not":0 }' */
                "(system_channel_id):F,"
  /* specs/discord/audit_log.json:147:18
     '{"name":"position", "type": {"base":"int"}, "comment":"text or voice channel position changed"}' */
                "(position):d,"
  /* specs/discord/audit_log.json:148:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}, "comment":"text or voice chanenl position changed", "inject_if_not":null }' */
                "(topic):?s,"
  /* specs/discord/audit_log.json:149:18
     '{"name":"bitrate", "type": {"base":"int"}, "comment":"voice channel bitrate changed" }' */
                "(bitrate):d,"
  /* specs/discord/audit_log.json:150:18
     '{"name":"permission_overwrites", "type": {"base":"struct discord_overwrite", "dec":"ntl"}, "comment":"permissions on a channel changed" }' */
                "(permission_overwrites):F,"
  /* specs/discord/audit_log.json:151:18
     '{"name":"nsfw", "type": {"base":"bool"}, "comment":"channel nsfw restriction changed" }' */
                "(nsfw):b,"
  /* specs/discord/audit_log.json:152:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"application id of the added or removed webhook or bot", "inject_if_not":0 }' */
                "(application_id):F,"
  /* specs/discord/audit_log.json:153:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}, "comment":"amount of seconds a user has to wait before sending another message changed" }' */
                "(rate_limit_per_user):d,"
  /* specs/discord/audit_log.json:154:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}, "comment":"permissions for a role changed" }' */
                "(permissions):?s,"
  /* specs/discord/audit_log.json:155:18
     '{"name":"color", "type": {"base":"int"}, "comment":"role color changed" }' */
                "(color):d,"
  /* specs/discord/audit_log.json:156:18
     '{"name":"hoist", "type": {"base":"bool"}, "comment":"role is now diplayed/no longer displayed separate from online users" }' */
                "(hoist):b,"
  /* specs/discord/audit_log.json:157:18
     '{"name":"mentionable", "type": {"base":"bool"}, "comment":"role is now mentionable/unmentionable" }' */
                "(mentionable):b,"
  /* specs/discord/audit_log.json:158:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was allowed for a role" }' */
                "(allow):?s,"
  /* specs/discord/audit_log.json:159:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was denied for a role" }' */
                "(deny):?s,"
  /* specs/discord/audit_log.json:160:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}, "comment":"invite code changed" }' */
                "(code):?s,"
  /* specs/discord/audit_log.json:161:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel for invite code changed", "inject_if_not":0 }' */
                "(channel_id):F,"
  /* specs/discord/audit_log.json:162:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"person who created invite code changed", "inject_if_not":0 }' */
                "(inviter_id):F,"
  /* specs/discord/audit_log.json:163:18
     '{"name":"max_uses", "type": {"base":"int"}, "comment":"change to max number of times invite codes can be used" }' */
                "(max_uses):d,"
  /* specs/discord/audit_log.json:164:18
     '{"name":"uses", "type": {"base":"int"}, "comment":"number of times invite code used changed" }' */
                "(uses):d,"
  /* specs/discord/audit_log.json:165:18
     '{"name":"max_age", "type": {"base":"int"}, "comment":"how long invite code lasts changed" }' */
                "(max_age):d,"
  /* specs/discord/audit_log.json:166:18
     '{"name":"temporary", "type": {"base":"bool"}, "comment":"invite code is temporary/never expires" }' */
                "(temporary):b,"
  /* specs/discord/audit_log.json:167:18
     '{"name":"deaf", "type": {"base":"bool"}, "comment":"user server deafened/undefeaned" }' */
                "(deaf):b,"
  /* specs/discord/audit_log.json:168:18
     '{"name":"mute", "type": {"base":"bool"}, "comment":"user server muted/unmuted" }' */
                "(mute):b,"
  /* specs/discord/audit_log.json:169:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}, "comment":"user nickname/changed" }' */
                "(nick):?s,"
  /* specs/discord/audit_log.json:170:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"user avatar changed", "inject_if_not":"" }' */
                "(avatar_hash):s,"
  /* specs/discord/audit_log.json:171:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the changed entity - sometimes used in conjunction with other keys", "inject_if_not":0 }' */
                "(id):F,"
  /* specs/discord/audit_log.json:172:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, "todo":true, "comment":"type of entity created" }' */
  /* specs/discord/audit_log.json:173:18
     '{"name":"enable_emotions", "type": {"base":"bool"}, "comment":"integration emoticons enabled/disabled" }' */
                "(enable_emotions):b,"
  /* specs/discord/audit_log.json:174:18
     '{"name":"expire_behavior", "type": {"base":"int"}, "comment":"integration expiring subscriber behavior changed" }' */
                "(expire_behavior):d,"
  /* specs/discord/audit_log.json:175:18
     '{"name":"expire_grace_period", "type": {"base":"int"}, "comment":"integration expire grace period changed" }' */
                "(expire_grace_period):d,"
  /* specs/discord/audit_log.json:176:18
     '{"name":"user_limit", "type": {"base":"int" }, "comment":"new user limit in a voice channel" }' */
                "(user_limit):d,"
  /* specs/discord/audit_log.json:177:18
     '{"name":"privacy_level", "type": {"base":"int" }, "comment":"privacy level of stage instance changed" }' */
                "(privacy_level):d,"
  /* specs/discord/audit_log.json:178:18
     '{"name":"tags", "type": {"base":"char", "dec":"*" }, "comment":"related emoji of sticker changed", "inject_if_not":null }' */
                "(tags):?s,"
  /* specs/discord/audit_log.json:179:18
     '{"name":"format_type", "type": {"base":"int" }, "comment":"format type of sticker changed" }' */
                "(format_type):d,"
  /* specs/discord/audit_log.json:180:18
     '{"name":"asset", "type": {"base":"char", "dec":"*" }, "comment":"empty string", "inject_if_not":null }' */
                "(asset):?s,"
  /* specs/discord/audit_log.json:181:18
     '{"name":"available", "type": {"base":"bool" }, "comment":"availability of sticker changed" }' */
                "(available):b,"
  /* specs/discord/audit_log.json:182:18
     '{"name":"guild_id", "type": {"base":"char", "dec":"*", "converter":"snowflake" }, "comment":"guild sticker is in changed", "inject_if_not":0 }' */
                "(guild_id):F,"
  /* specs/discord/audit_log.json:183:18
     '{"name":"archived", "type": {"base":"bool" }, "comment":"thread is now archived/unarchived" }' */
                "(archived):b,"
  /* specs/discord/audit_log.json:184:18
     '{"name":"locked", "type": {"base":"bool" }, "comment":"thread is now locked/unlocked" }' */
                "(locked):b,"
  /* specs/discord/audit_log.json:185:18
     '{"name":"auto_archive_duration", "type": {"base":"int" }, "comment":"auto archive duration changed" }' */
                "(auto_archive_duration):d,"
  /* specs/discord/audit_log.json:186:18
     '{"name":"default_auto_archive_duration", "type": {"base":"int" }, "comment":"default auto archive duration for newly created threads changed" }' */
                "(default_auto_archive_duration):d,"
                "@arg_switches:b"
                "@record_defined"
                "@record_null",
  /* specs/discord/audit_log.json:123:18
     '{"name":"name", "type": {"base":"char", "dec":"*"}, "comment":"name changed", "inject_if_not":null }' */
                &p->name,
  /* specs/discord/audit_log.json:124:18
     '{"name":"description", "type": {"base":"char", "dec":"*"}, "comment":"description changed", "inject_if_not":null }' */
                &p->description,
  /* specs/discord/audit_log.json:125:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"icon changed", "inject_if_not":"" }' */
                p->icon_hash,
  /* specs/discord/audit_log.json:126:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"invite splash page artwork changed", "inject_if_not":"" }' */
                p->splash_hash,
  /* specs/discord/audit_log.json:127:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"discovery splash changed", "inject_if_not":"" }' */
                p->discovery_splash_hash,
  /* specs/discord/audit_log.json:128:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"guild banned changed", "inject_if_not":"" }' */
                p->banner_hash,
  /* specs/discord/audit_log.json:129:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"owner changed", "inject_if_not":0 }' */
                cee_strtoull, &p->owner_id,
  /* specs/discord/audit_log.json:130:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "comment":"region changed", "inject_if_not":"" }' */
                p->region,
  /* specs/discord/audit_log.json:131:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "comment":"preferred locale changed", "inject_if_not":"" }' */
                p->preferred_locale,
  /* specs/discord/audit_log.json:132:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"afk channel changed", "inject_if_not":0 }' */
                cee_strtoull, &p->afk_channel_id,
  /* specs/discord/audit_log.json:133:18
     '{"name":"afk_timeout", "type": {"base":"int"}, "comment":"afk timeout duration changed", "inject_if_not":0 }' */
                &p->afk_timeout,
  /* specs/discord/audit_log.json:134:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the rules channel changed", "inject_if_not":0 }' */
                cee_strtoull, &p->rules_channel_id,
  /* specs/discord/audit_log.json:135:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the public updates channel changed", "inject_if_not":0 }' */
                cee_strtoull, &p->public_updates_channel_id,
  /* specs/discord/audit_log.json:136:18
     '{"name":"mfa_level", "type": {"base":"int"}, "comment":"two-factor auth requirement changed", "inject_if_not":0 }' */
                &p->mfa_level,
  /* specs/discord/audit_log.json:137:18
     '{"name":"verification_level", "type": {"base":"int"}, "comment":"required verification level changed", "inject_if_not":0 }' */
                &p->verification_level,
  /* specs/discord/audit_log.json:138:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}, "comment":"change in whose messages are scanned and deleted for explicit content in the server", "inject_if_not":0 }' */
                &p->explicit_content_filter,
  /* specs/discord/audit_log.json:139:18
     '{"name":"default_message_notifications", "type": {"base":"int"}, "comment":"default message notification level changed", "inject_if_not":0 }' */
                &p->default_message_notifications,
  /* specs/discord/audit_log.json:140:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}, "comment":"guild invite vanity url changed", "inject_if_not":null }' */
                &p->vanity_url_code,
  /* specs/discord/audit_log.json:141:18
     '{"name":"add", "json_key":"$add", "type": {"base":"struct discord_role", "dec":"ntl" }, "comment":"new role added", "inject_if_not":null }' */
                discord_role_list_from_json, &p->add,
  /* specs/discord/audit_log.json:142:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"struct discord_role", "dec":"ntl"}, "comment":"role removed", "inject_if_not":null }' */
                discord_role_list_from_json, &p->remove,
  /* specs/discord/audit_log.json:143:18
     '{"name":"prune_delete_days", "type": {"base":"int"}, "comment":"change in number of days after which inactive and role-unassigned members are kicked", "inject_if_not":0 }' */
                &p->prune_delete_days,
  /* specs/discord/audit_log.json:144:18
     '{"name":"widget_enabled", "type": {"base":"bool"}, "comment":"server widget enabled/disable"}' */
                &p->widget_enabled,
  /* specs/discord/audit_log.json:145:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel id of the server widget changed", "inject_if_not":0 }' */
                cee_strtoull, &p->widget_channel_id,
  /* specs/discord/audit_log.json:146:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the system channel changed", "inject_if_not":0 }' */
                cee_strtoull, &p->system_channel_id,
  /* specs/discord/audit_log.json:147:18
     '{"name":"position", "type": {"base":"int"}, "comment":"text or voice channel position changed"}' */
                &p->position,
  /* specs/discord/audit_log.json:148:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}, "comment":"text or voice chanenl position changed", "inject_if_not":null }' */
                &p->topic,
  /* specs/discord/audit_log.json:149:18
     '{"name":"bitrate", "type": {"base":"int"}, "comment":"voice channel bitrate changed" }' */
                &p->bitrate,
  /* specs/discord/audit_log.json:150:18
     '{"name":"permission_overwrites", "type": {"base":"struct discord_overwrite", "dec":"ntl"}, "comment":"permissions on a channel changed" }' */
                discord_overwrite_list_from_json, &p->permission_overwrites,
  /* specs/discord/audit_log.json:151:18
     '{"name":"nsfw", "type": {"base":"bool"}, "comment":"channel nsfw restriction changed" }' */
                &p->nsfw,
  /* specs/discord/audit_log.json:152:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"application id of the added or removed webhook or bot", "inject_if_not":0 }' */
                cee_strtoull, &p->application_id,
  /* specs/discord/audit_log.json:153:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}, "comment":"amount of seconds a user has to wait before sending another message changed" }' */
                &p->rate_limit_per_user,
  /* specs/discord/audit_log.json:154:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}, "comment":"permissions for a role changed" }' */
                &p->permissions,
  /* specs/discord/audit_log.json:155:18
     '{"name":"color", "type": {"base":"int"}, "comment":"role color changed" }' */
                &p->color,
  /* specs/discord/audit_log.json:156:18
     '{"name":"hoist", "type": {"base":"bool"}, "comment":"role is now diplayed/no longer displayed separate from online users" }' */
                &p->hoist,
  /* specs/discord/audit_log.json:157:18
     '{"name":"mentionable", "type": {"base":"bool"}, "comment":"role is now mentionable/unmentionable" }' */
                &p->mentionable,
  /* specs/discord/audit_log.json:158:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was allowed for a role" }' */
                &p->allow,
  /* specs/discord/audit_log.json:159:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was denied for a role" }' */
                &p->deny,
  /* specs/discord/audit_log.json:160:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}, "comment":"invite code changed" }' */
                &p->code,
  /* specs/discord/audit_log.json:161:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel for invite code changed", "inject_if_not":0 }' */
                cee_strtoull, &p->channel_id,
  /* specs/discord/audit_log.json:162:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"person who created invite code changed", "inject_if_not":0 }' */
                cee_strtoull, &p->inviter_id,
  /* specs/discord/audit_log.json:163:18
     '{"name":"max_uses", "type": {"base":"int"}, "comment":"change to max number of times invite codes can be used" }' */
                &p->max_uses,
  /* specs/discord/audit_log.json:164:18
     '{"name":"uses", "type": {"base":"int"}, "comment":"number of times invite code used changed" }' */
                &p->uses,
  /* specs/discord/audit_log.json:165:18
     '{"name":"max_age", "type": {"base":"int"}, "comment":"how long invite code lasts changed" }' */
                &p->max_age,
  /* specs/discord/audit_log.json:166:18
     '{"name":"temporary", "type": {"base":"bool"}, "comment":"invite code is temporary/never expires" }' */
                &p->temporary,
  /* specs/discord/audit_log.json:167:18
     '{"name":"deaf", "type": {"base":"bool"}, "comment":"user server deafened/undefeaned" }' */
                &p->deaf,
  /* specs/discord/audit_log.json:168:18
     '{"name":"mute", "type": {"base":"bool"}, "comment":"user server muted/unmuted" }' */
                &p->mute,
  /* specs/discord/audit_log.json:169:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}, "comment":"user nickname/changed" }' */
                &p->nick,
  /* specs/discord/audit_log.json:170:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"user avatar changed", "inject_if_not":"" }' */
                p->avatar_hash,
  /* specs/discord/audit_log.json:171:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the changed entity - sometimes used in conjunction with other keys", "inject_if_not":0 }' */
                cee_strtoull, &p->id,
  /* specs/discord/audit_log.json:172:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, "todo":true, "comment":"type of entity created" }' */
  /* specs/discord/audit_log.json:173:18
     '{"name":"enable_emotions", "type": {"base":"bool"}, "comment":"integration emoticons enabled/disabled" }' */
                &p->enable_emotions,
  /* specs/discord/audit_log.json:174:18
     '{"name":"expire_behavior", "type": {"base":"int"}, "comment":"integration expiring subscriber behavior changed" }' */
                &p->expire_behavior,
  /* specs/discord/audit_log.json:175:18
     '{"name":"expire_grace_period", "type": {"base":"int"}, "comment":"integration expire grace period changed" }' */
                &p->expire_grace_period,
  /* specs/discord/audit_log.json:176:18
     '{"name":"user_limit", "type": {"base":"int" }, "comment":"new user limit in a voice channel" }' */
                &p->user_limit,
  /* specs/discord/audit_log.json:177:18
     '{"name":"privacy_level", "type": {"base":"int" }, "comment":"privacy level of stage instance changed" }' */
                &p->privacy_level,
  /* specs/discord/audit_log.json:178:18
     '{"name":"tags", "type": {"base":"char", "dec":"*" }, "comment":"related emoji of sticker changed", "inject_if_not":null }' */
                &p->tags,
  /* specs/discord/audit_log.json:179:18
     '{"name":"format_type", "type": {"base":"int" }, "comment":"format type of sticker changed" }' */
                &p->format_type,
  /* specs/discord/audit_log.json:180:18
     '{"name":"asset", "type": {"base":"char", "dec":"*" }, "comment":"empty string", "inject_if_not":null }' */
                &p->asset,
  /* specs/discord/audit_log.json:181:18
     '{"name":"available", "type": {"base":"bool" }, "comment":"availability of sticker changed" }' */
                &p->available,
  /* specs/discord/audit_log.json:182:18
     '{"name":"guild_id", "type": {"base":"char", "dec":"*", "converter":"snowflake" }, "comment":"guild sticker is in changed", "inject_if_not":0 }' */
                cee_strtoull, &p->guild_id,
  /* specs/discord/audit_log.json:183:18
     '{"name":"archived", "type": {"base":"bool" }, "comment":"thread is now archived/unarchived" }' */
                &p->archived,
  /* specs/discord/audit_log.json:184:18
     '{"name":"locked", "type": {"base":"bool" }, "comment":"thread is now locked/unlocked" }' */
                &p->locked,
  /* specs/discord/audit_log.json:185:18
     '{"name":"auto_archive_duration", "type": {"base":"int" }, "comment":"auto archive duration changed" }' */
                &p->auto_archive_duration,
  /* specs/discord/audit_log.json:186:18
     '{"name":"default_auto_archive_duration", "type": {"base":"int" }, "comment":"default auto archive duration for newly created threads changed" }' */
                &p->default_auto_archive_duration,
                p->__M.arg_switches, sizeof(p->__M.arg_switches), p->__M.enable_arg_switches,
                p->__M.record_defined, sizeof(p->__M.record_defined),
                p->__M.record_null, sizeof(p->__M.record_null));
  ret = r;
}

static void discord_audit_log_change_key_use_default_inject_settings(struct discord_audit_log_change_key *p)
{
  p->__M.enable_arg_switches = true;
  /* specs/discord/audit_log.json:123:18
     '{"name":"name", "type": {"base":"char", "dec":"*"}, "comment":"name changed", "inject_if_not":null }' */
  if (p->name != NULL)
    p->__M.arg_switches[0] = p->name;

  /* specs/discord/audit_log.json:124:18
     '{"name":"description", "type": {"base":"char", "dec":"*"}, "comment":"description changed", "inject_if_not":null }' */
  if (p->description != NULL)
    p->__M.arg_switches[1] = p->description;

  /* specs/discord/audit_log.json:125:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"icon changed", "inject_if_not":"" }' */
  if (*p->icon_hash)
    p->__M.arg_switches[2] = p->icon_hash;

  /* specs/discord/audit_log.json:126:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"invite splash page artwork changed", "inject_if_not":"" }' */
  if (*p->splash_hash)
    p->__M.arg_switches[3] = p->splash_hash;

  /* specs/discord/audit_log.json:127:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"discovery splash changed", "inject_if_not":"" }' */
  if (*p->discovery_splash_hash)
    p->__M.arg_switches[4] = p->discovery_splash_hash;

  /* specs/discord/audit_log.json:128:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"guild banned changed", "inject_if_not":"" }' */
  if (*p->banner_hash)
    p->__M.arg_switches[5] = p->banner_hash;

  /* specs/discord/audit_log.json:129:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"owner changed", "inject_if_not":0 }' */
  if (p->owner_id != 0)
    p->__M.arg_switches[6] = &p->owner_id;

  /* specs/discord/audit_log.json:130:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "comment":"region changed", "inject_if_not":"" }' */
  if (*p->region)
    p->__M.arg_switches[7] = p->region;

  /* specs/discord/audit_log.json:131:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "comment":"preferred locale changed", "inject_if_not":"" }' */
  if (*p->preferred_locale)
    p->__M.arg_switches[8] = p->preferred_locale;

  /* specs/discord/audit_log.json:132:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"afk channel changed", "inject_if_not":0 }' */
  if (p->afk_channel_id != 0)
    p->__M.arg_switches[9] = &p->afk_channel_id;

  /* specs/discord/audit_log.json:133:18
     '{"name":"afk_timeout", "type": {"base":"int"}, "comment":"afk timeout duration changed", "inject_if_not":0 }' */
  if (p->afk_timeout != 0)
    p->__M.arg_switches[10] = &p->afk_timeout;

  /* specs/discord/audit_log.json:134:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the rules channel changed", "inject_if_not":0 }' */
  if (p->rules_channel_id != 0)
    p->__M.arg_switches[11] = &p->rules_channel_id;

  /* specs/discord/audit_log.json:135:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the public updates channel changed", "inject_if_not":0 }' */
  if (p->public_updates_channel_id != 0)
    p->__M.arg_switches[12] = &p->public_updates_channel_id;

  /* specs/discord/audit_log.json:136:18
     '{"name":"mfa_level", "type": {"base":"int"}, "comment":"two-factor auth requirement changed", "inject_if_not":0 }' */
  if (p->mfa_level != 0)
    p->__M.arg_switches[13] = &p->mfa_level;

  /* specs/discord/audit_log.json:137:18
     '{"name":"verification_level", "type": {"base":"int"}, "comment":"required verification level changed", "inject_if_not":0 }' */
  if (p->verification_level != 0)
    p->__M.arg_switches[14] = &p->verification_level;

  /* specs/discord/audit_log.json:138:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}, "comment":"change in whose messages are scanned and deleted for explicit content in the server", "inject_if_not":0 }' */
  if (p->explicit_content_filter != 0)
    p->__M.arg_switches[15] = &p->explicit_content_filter;

  /* specs/discord/audit_log.json:139:18
     '{"name":"default_message_notifications", "type": {"base":"int"}, "comment":"default message notification level changed", "inject_if_not":0 }' */
  if (p->default_message_notifications != 0)
    p->__M.arg_switches[16] = &p->default_message_notifications;

  /* specs/discord/audit_log.json:140:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}, "comment":"guild invite vanity url changed", "inject_if_not":null }' */
  if (p->vanity_url_code != NULL)
    p->__M.arg_switches[17] = p->vanity_url_code;

  /* specs/discord/audit_log.json:141:18
     '{"name":"add", "json_key":"$add", "type": {"base":"struct discord_role", "dec":"ntl" }, "comment":"new role added", "inject_if_not":null }' */
  if (p->add != NULL)
    p->__M.arg_switches[18] = p->add;

  /* specs/discord/audit_log.json:142:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"struct discord_role", "dec":"ntl"}, "comment":"role removed", "inject_if_not":null }' */
  if (p->remove != NULL)
    p->__M.arg_switches[19] = p->remove;

  /* specs/discord/audit_log.json:143:18
     '{"name":"prune_delete_days", "type": {"base":"int"}, "comment":"change in number of days after which inactive and role-unassigned members are kicked", "inject_if_not":0 }' */
  if (p->prune_delete_days != 0)
    p->__M.arg_switches[20] = &p->prune_delete_days;

  /* specs/discord/audit_log.json:144:18
     '{"name":"widget_enabled", "type": {"base":"bool"}, "comment":"server widget enabled/disable"}' */
  p->__M.arg_switches[21] = &p->widget_enabled;

  /* specs/discord/audit_log.json:145:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel id of the server widget changed", "inject_if_not":0 }' */
  if (p->widget_channel_id != 0)
    p->__M.arg_switches[22] = &p->widget_channel_id;

  /* specs/discord/audit_log.json:146:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the system channel changed", "inject_if_not":0 }' */
  if (p->system_channel_id != 0)
    p->__M.arg_switches[23] = &p->system_channel_id;

  /* specs/discord/audit_log.json:147:18
     '{"name":"position", "type": {"base":"int"}, "comment":"text or voice channel position changed"}' */
  p->__M.arg_switches[24] = &p->position;

  /* specs/discord/audit_log.json:148:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}, "comment":"text or voice chanenl position changed", "inject_if_not":null }' */
  if (p->topic != NULL)
    p->__M.arg_switches[25] = p->topic;

  /* specs/discord/audit_log.json:149:18
     '{"name":"bitrate", "type": {"base":"int"}, "comment":"voice channel bitrate changed" }' */
  p->__M.arg_switches[26] = &p->bitrate;

  /* specs/discord/audit_log.json:150:18
     '{"name":"permission_overwrites", "type": {"base":"struct discord_overwrite", "dec":"ntl"}, "comment":"permissions on a channel changed" }' */
  p->__M.arg_switches[27] = p->permission_overwrites;

  /* specs/discord/audit_log.json:151:18
     '{"name":"nsfw", "type": {"base":"bool"}, "comment":"channel nsfw restriction changed" }' */
  p->__M.arg_switches[28] = &p->nsfw;

  /* specs/discord/audit_log.json:152:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"application id of the added or removed webhook or bot", "inject_if_not":0 }' */
  if (p->application_id != 0)
    p->__M.arg_switches[29] = &p->application_id;

  /* specs/discord/audit_log.json:153:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}, "comment":"amount of seconds a user has to wait before sending another message changed" }' */
  p->__M.arg_switches[30] = &p->rate_limit_per_user;

  /* specs/discord/audit_log.json:154:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}, "comment":"permissions for a role changed" }' */
  p->__M.arg_switches[31] = p->permissions;

  /* specs/discord/audit_log.json:155:18
     '{"name":"color", "type": {"base":"int"}, "comment":"role color changed" }' */
  p->__M.arg_switches[32] = &p->color;

  /* specs/discord/audit_log.json:156:18
     '{"name":"hoist", "type": {"base":"bool"}, "comment":"role is now diplayed/no longer displayed separate from online users" }' */
  p->__M.arg_switches[33] = &p->hoist;

  /* specs/discord/audit_log.json:157:18
     '{"name":"mentionable", "type": {"base":"bool"}, "comment":"role is now mentionable/unmentionable" }' */
  p->__M.arg_switches[34] = &p->mentionable;

  /* specs/discord/audit_log.json:158:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was allowed for a role" }' */
  p->__M.arg_switches[35] = p->allow;

  /* specs/discord/audit_log.json:159:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was denied for a role" }' */
  p->__M.arg_switches[36] = p->deny;

  /* specs/discord/audit_log.json:160:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}, "comment":"invite code changed" }' */
  p->__M.arg_switches[37] = p->code;

  /* specs/discord/audit_log.json:161:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel for invite code changed", "inject_if_not":0 }' */
  if (p->channel_id != 0)
    p->__M.arg_switches[38] = &p->channel_id;

  /* specs/discord/audit_log.json:162:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"person who created invite code changed", "inject_if_not":0 }' */
  if (p->inviter_id != 0)
    p->__M.arg_switches[39] = &p->inviter_id;

  /* specs/discord/audit_log.json:163:18
     '{"name":"max_uses", "type": {"base":"int"}, "comment":"change to max number of times invite codes can be used" }' */
  p->__M.arg_switches[40] = &p->max_uses;

  /* specs/discord/audit_log.json:164:18
     '{"name":"uses", "type": {"base":"int"}, "comment":"number of times invite code used changed" }' */
  p->__M.arg_switches[41] = &p->uses;

  /* specs/discord/audit_log.json:165:18
     '{"name":"max_age", "type": {"base":"int"}, "comment":"how long invite code lasts changed" }' */
  p->__M.arg_switches[42] = &p->max_age;

  /* specs/discord/audit_log.json:166:18
     '{"name":"temporary", "type": {"base":"bool"}, "comment":"invite code is temporary/never expires" }' */
  p->__M.arg_switches[43] = &p->temporary;

  /* specs/discord/audit_log.json:167:18
     '{"name":"deaf", "type": {"base":"bool"}, "comment":"user server deafened/undefeaned" }' */
  p->__M.arg_switches[44] = &p->deaf;

  /* specs/discord/audit_log.json:168:18
     '{"name":"mute", "type": {"base":"bool"}, "comment":"user server muted/unmuted" }' */
  p->__M.arg_switches[45] = &p->mute;

  /* specs/discord/audit_log.json:169:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}, "comment":"user nickname/changed" }' */
  p->__M.arg_switches[46] = p->nick;

  /* specs/discord/audit_log.json:170:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"user avatar changed", "inject_if_not":"" }' */
  if (*p->avatar_hash)
    p->__M.arg_switches[47] = p->avatar_hash;

  /* specs/discord/audit_log.json:171:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the changed entity - sometimes used in conjunction with other keys", "inject_if_not":0 }' */
  if (p->id != 0)
    p->__M.arg_switches[48] = &p->id;

  /* specs/discord/audit_log.json:172:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, "todo":true, "comment":"type of entity created" }' */

  /* specs/discord/audit_log.json:173:18
     '{"name":"enable_emotions", "type": {"base":"bool"}, "comment":"integration emoticons enabled/disabled" }' */
  p->__M.arg_switches[50] = &p->enable_emotions;

  /* specs/discord/audit_log.json:174:18
     '{"name":"expire_behavior", "type": {"base":"int"}, "comment":"integration expiring subscriber behavior changed" }' */
  p->__M.arg_switches[51] = &p->expire_behavior;

  /* specs/discord/audit_log.json:175:18
     '{"name":"expire_grace_period", "type": {"base":"int"}, "comment":"integration expire grace period changed" }' */
  p->__M.arg_switches[52] = &p->expire_grace_period;

  /* specs/discord/audit_log.json:176:18
     '{"name":"user_limit", "type": {"base":"int" }, "comment":"new user limit in a voice channel" }' */
  p->__M.arg_switches[53] = &p->user_limit;

  /* specs/discord/audit_log.json:177:18
     '{"name":"privacy_level", "type": {"base":"int" }, "comment":"privacy level of stage instance changed" }' */
  p->__M.arg_switches[54] = &p->privacy_level;

  /* specs/discord/audit_log.json:178:18
     '{"name":"tags", "type": {"base":"char", "dec":"*" }, "comment":"related emoji of sticker changed", "inject_if_not":null }' */
  if (p->tags != NULL)
    p->__M.arg_switches[55] = p->tags;

  /* specs/discord/audit_log.json:179:18
     '{"name":"format_type", "type": {"base":"int" }, "comment":"format type of sticker changed" }' */
  p->__M.arg_switches[56] = &p->format_type;

  /* specs/discord/audit_log.json:180:18
     '{"name":"asset", "type": {"base":"char", "dec":"*" }, "comment":"empty string", "inject_if_not":null }' */
  if (p->asset != NULL)
    p->__M.arg_switches[57] = p->asset;

  /* specs/discord/audit_log.json:181:18
     '{"name":"available", "type": {"base":"bool" }, "comment":"availability of sticker changed" }' */
  p->__M.arg_switches[58] = &p->available;

  /* specs/discord/audit_log.json:182:18
     '{"name":"guild_id", "type": {"base":"char", "dec":"*", "converter":"snowflake" }, "comment":"guild sticker is in changed", "inject_if_not":0 }' */
  if (p->guild_id != 0)
    p->__M.arg_switches[59] = &p->guild_id;

  /* specs/discord/audit_log.json:183:18
     '{"name":"archived", "type": {"base":"bool" }, "comment":"thread is now archived/unarchived" }' */
  p->__M.arg_switches[60] = &p->archived;

  /* specs/discord/audit_log.json:184:18
     '{"name":"locked", "type": {"base":"bool" }, "comment":"thread is now locked/unlocked" }' */
  p->__M.arg_switches[61] = &p->locked;

  /* specs/discord/audit_log.json:185:18
     '{"name":"auto_archive_duration", "type": {"base":"int" }, "comment":"auto archive duration changed" }' */
  p->__M.arg_switches[62] = &p->auto_archive_duration;

  /* specs/discord/audit_log.json:186:18
     '{"name":"default_auto_archive_duration", "type": {"base":"int" }, "comment":"default auto archive duration for newly created threads changed" }' */
  p->__M.arg_switches[63] = &p->default_auto_archive_duration;

}

size_t discord_audit_log_change_key_to_json(char *json, size_t len, struct discord_audit_log_change_key *p)
{
  size_t r;
  discord_audit_log_change_key_use_default_inject_settings(p);
  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:123:18
     '{"name":"name", "type": {"base":"char", "dec":"*"}, "comment":"name changed", "inject_if_not":null }' */
                "(name):s,"
  /* specs/discord/audit_log.json:124:18
     '{"name":"description", "type": {"base":"char", "dec":"*"}, "comment":"description changed", "inject_if_not":null }' */
                "(description):s,"
  /* specs/discord/audit_log.json:125:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"icon changed", "inject_if_not":"" }' */
                "(icon_hash):s,"
  /* specs/discord/audit_log.json:126:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"invite splash page artwork changed", "inject_if_not":"" }' */
                "(splash_hash):s,"
  /* specs/discord/audit_log.json:127:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"discovery splash changed", "inject_if_not":"" }' */
                "(discovery_splash_hash):s,"
  /* specs/discord/audit_log.json:128:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"guild banned changed", "inject_if_not":"" }' */
                "(banner_hash):s,"
  /* specs/discord/audit_log.json:129:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"owner changed", "inject_if_not":0 }' */
                "(owner_id):|F|,"
  /* specs/discord/audit_log.json:130:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "comment":"region changed", "inject_if_not":"" }' */
                "(region):s,"
  /* specs/discord/audit_log.json:131:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "comment":"preferred locale changed", "inject_if_not":"" }' */
                "(preferred_locale):s,"
  /* specs/discord/audit_log.json:132:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"afk channel changed", "inject_if_not":0 }' */
                "(afk_channel_id):|F|,"
  /* specs/discord/audit_log.json:133:18
     '{"name":"afk_timeout", "type": {"base":"int"}, "comment":"afk timeout duration changed", "inject_if_not":0 }' */
                "(afk_timeout):d,"
  /* specs/discord/audit_log.json:134:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the rules channel changed", "inject_if_not":0 }' */
                "(rules_channel_id):|F|,"
  /* specs/discord/audit_log.json:135:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the public updates channel changed", "inject_if_not":0 }' */
                "(public_updates_channel_id):|F|,"
  /* specs/discord/audit_log.json:136:18
     '{"name":"mfa_level", "type": {"base":"int"}, "comment":"two-factor auth requirement changed", "inject_if_not":0 }' */
                "(mfa_level):d,"
  /* specs/discord/audit_log.json:137:18
     '{"name":"verification_level", "type": {"base":"int"}, "comment":"required verification level changed", "inject_if_not":0 }' */
                "(verification_level):d,"
  /* specs/discord/audit_log.json:138:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}, "comment":"change in whose messages are scanned and deleted for explicit content in the server", "inject_if_not":0 }' */
                "(explicit_content_filter):d,"
  /* specs/discord/audit_log.json:139:18
     '{"name":"default_message_notifications", "type": {"base":"int"}, "comment":"default message notification level changed", "inject_if_not":0 }' */
                "(default_message_notifications):d,"
  /* specs/discord/audit_log.json:140:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}, "comment":"guild invite vanity url changed", "inject_if_not":null }' */
                "(vanity_url_code):s,"
  /* specs/discord/audit_log.json:141:18
     '{"name":"add", "json_key":"$add", "type": {"base":"struct discord_role", "dec":"ntl" }, "comment":"new role added", "inject_if_not":null }' */
                "($add):F,"
  /* specs/discord/audit_log.json:142:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"struct discord_role", "dec":"ntl"}, "comment":"role removed", "inject_if_not":null }' */
                "($remove):F,"
  /* specs/discord/audit_log.json:143:18
     '{"name":"prune_delete_days", "type": {"base":"int"}, "comment":"change in number of days after which inactive and role-unassigned members are kicked", "inject_if_not":0 }' */
                "(prune_delete_days):d,"
  /* specs/discord/audit_log.json:144:18
     '{"name":"widget_enabled", "type": {"base":"bool"}, "comment":"server widget enabled/disable"}' */
                "(widget_enabled):b,"
  /* specs/discord/audit_log.json:145:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel id of the server widget changed", "inject_if_not":0 }' */
                "(widget_channel_id):|F|,"
  /* specs/discord/audit_log.json:146:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the system channel changed", "inject_if_not":0 }' */
                "(system_channel_id):|F|,"
  /* specs/discord/audit_log.json:147:18
     '{"name":"position", "type": {"base":"int"}, "comment":"text or voice channel position changed"}' */
                "(position):d,"
  /* specs/discord/audit_log.json:148:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}, "comment":"text or voice chanenl position changed", "inject_if_not":null }' */
                "(topic):s,"
  /* specs/discord/audit_log.json:149:18
     '{"name":"bitrate", "type": {"base":"int"}, "comment":"voice channel bitrate changed" }' */
                "(bitrate):d,"
  /* specs/discord/audit_log.json:150:18
     '{"name":"permission_overwrites", "type": {"base":"struct discord_overwrite", "dec":"ntl"}, "comment":"permissions on a channel changed" }' */
                "(permission_overwrites):F,"
  /* specs/discord/audit_log.json:151:18
     '{"name":"nsfw", "type": {"base":"bool"}, "comment":"channel nsfw restriction changed" }' */
                "(nsfw):b,"
  /* specs/discord/audit_log.json:152:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"application id of the added or removed webhook or bot", "inject_if_not":0 }' */
                "(application_id):|F|,"
  /* specs/discord/audit_log.json:153:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}, "comment":"amount of seconds a user has to wait before sending another message changed" }' */
                "(rate_limit_per_user):d,"
  /* specs/discord/audit_log.json:154:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}, "comment":"permissions for a role changed" }' */
                "(permissions):s,"
  /* specs/discord/audit_log.json:155:18
     '{"name":"color", "type": {"base":"int"}, "comment":"role color changed" }' */
                "(color):d,"
  /* specs/discord/audit_log.json:156:18
     '{"name":"hoist", "type": {"base":"bool"}, "comment":"role is now diplayed/no longer displayed separate from online users" }' */
                "(hoist):b,"
  /* specs/discord/audit_log.json:157:18
     '{"name":"mentionable", "type": {"base":"bool"}, "comment":"role is now mentionable/unmentionable" }' */
                "(mentionable):b,"
  /* specs/discord/audit_log.json:158:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was allowed for a role" }' */
                "(allow):s,"
  /* specs/discord/audit_log.json:159:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was denied for a role" }' */
                "(deny):s,"
  /* specs/discord/audit_log.json:160:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}, "comment":"invite code changed" }' */
                "(code):s,"
  /* specs/discord/audit_log.json:161:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel for invite code changed", "inject_if_not":0 }' */
                "(channel_id):|F|,"
  /* specs/discord/audit_log.json:162:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"person who created invite code changed", "inject_if_not":0 }' */
                "(inviter_id):|F|,"
  /* specs/discord/audit_log.json:163:18
     '{"name":"max_uses", "type": {"base":"int"}, "comment":"change to max number of times invite codes can be used" }' */
                "(max_uses):d,"
  /* specs/discord/audit_log.json:164:18
     '{"name":"uses", "type": {"base":"int"}, "comment":"number of times invite code used changed" }' */
                "(uses):d,"
  /* specs/discord/audit_log.json:165:18
     '{"name":"max_age", "type": {"base":"int"}, "comment":"how long invite code lasts changed" }' */
                "(max_age):d,"
  /* specs/discord/audit_log.json:166:18
     '{"name":"temporary", "type": {"base":"bool"}, "comment":"invite code is temporary/never expires" }' */
                "(temporary):b,"
  /* specs/discord/audit_log.json:167:18
     '{"name":"deaf", "type": {"base":"bool"}, "comment":"user server deafened/undefeaned" }' */
                "(deaf):b,"
  /* specs/discord/audit_log.json:168:18
     '{"name":"mute", "type": {"base":"bool"}, "comment":"user server muted/unmuted" }' */
                "(mute):b,"
  /* specs/discord/audit_log.json:169:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}, "comment":"user nickname/changed" }' */
                "(nick):s,"
  /* specs/discord/audit_log.json:170:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"user avatar changed", "inject_if_not":"" }' */
                "(avatar_hash):s,"
  /* specs/discord/audit_log.json:171:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the changed entity - sometimes used in conjunction with other keys", "inject_if_not":0 }' */
                "(id):|F|,"
  /* specs/discord/audit_log.json:172:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, "todo":true, "comment":"type of entity created" }' */
  /* specs/discord/audit_log.json:173:18
     '{"name":"enable_emotions", "type": {"base":"bool"}, "comment":"integration emoticons enabled/disabled" }' */
                "(enable_emotions):b,"
  /* specs/discord/audit_log.json:174:18
     '{"name":"expire_behavior", "type": {"base":"int"}, "comment":"integration expiring subscriber behavior changed" }' */
                "(expire_behavior):d,"
  /* specs/discord/audit_log.json:175:18
     '{"name":"expire_grace_period", "type": {"base":"int"}, "comment":"integration expire grace period changed" }' */
                "(expire_grace_period):d,"
  /* specs/discord/audit_log.json:176:18
     '{"name":"user_limit", "type": {"base":"int" }, "comment":"new user limit in a voice channel" }' */
                "(user_limit):d,"
  /* specs/discord/audit_log.json:177:18
     '{"name":"privacy_level", "type": {"base":"int" }, "comment":"privacy level of stage instance changed" }' */
                "(privacy_level):d,"
  /* specs/discord/audit_log.json:178:18
     '{"name":"tags", "type": {"base":"char", "dec":"*" }, "comment":"related emoji of sticker changed", "inject_if_not":null }' */
                "(tags):s,"
  /* specs/discord/audit_log.json:179:18
     '{"name":"format_type", "type": {"base":"int" }, "comment":"format type of sticker changed" }' */
                "(format_type):d,"
  /* specs/discord/audit_log.json:180:18
     '{"name":"asset", "type": {"base":"char", "dec":"*" }, "comment":"empty string", "inject_if_not":null }' */
                "(asset):s,"
  /* specs/discord/audit_log.json:181:18
     '{"name":"available", "type": {"base":"bool" }, "comment":"availability of sticker changed" }' */
                "(available):b,"
  /* specs/discord/audit_log.json:182:18
     '{"name":"guild_id", "type": {"base":"char", "dec":"*", "converter":"snowflake" }, "comment":"guild sticker is in changed", "inject_if_not":0 }' */
                "(guild_id):|F|,"
  /* specs/discord/audit_log.json:183:18
     '{"name":"archived", "type": {"base":"bool" }, "comment":"thread is now archived/unarchived" }' */
                "(archived):b,"
  /* specs/discord/audit_log.json:184:18
     '{"name":"locked", "type": {"base":"bool" }, "comment":"thread is now locked/unlocked" }' */
                "(locked):b,"
  /* specs/discord/audit_log.json:185:18
     '{"name":"auto_archive_duration", "type": {"base":"int" }, "comment":"auto archive duration changed" }' */
                "(auto_archive_duration):d,"
  /* specs/discord/audit_log.json:186:18
     '{"name":"default_auto_archive_duration", "type": {"base":"int" }, "comment":"default auto archive duration for newly created threads changed" }' */
                "(default_auto_archive_duration):d,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:123:18
     '{"name":"name", "type": {"base":"char", "dec":"*"}, "comment":"name changed", "inject_if_not":null }' */
                p->name,
  /* specs/discord/audit_log.json:124:18
     '{"name":"description", "type": {"base":"char", "dec":"*"}, "comment":"description changed", "inject_if_not":null }' */
                p->description,
  /* specs/discord/audit_log.json:125:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"icon changed", "inject_if_not":"" }' */
                p->icon_hash,
  /* specs/discord/audit_log.json:126:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"invite splash page artwork changed", "inject_if_not":"" }' */
                p->splash_hash,
  /* specs/discord/audit_log.json:127:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"discovery splash changed", "inject_if_not":"" }' */
                p->discovery_splash_hash,
  /* specs/discord/audit_log.json:128:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"guild banned changed", "inject_if_not":"" }' */
                p->banner_hash,
  /* specs/discord/audit_log.json:129:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"owner changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->owner_id,
  /* specs/discord/audit_log.json:130:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "comment":"region changed", "inject_if_not":"" }' */
                p->region,
  /* specs/discord/audit_log.json:131:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "comment":"preferred locale changed", "inject_if_not":"" }' */
                p->preferred_locale,
  /* specs/discord/audit_log.json:132:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"afk channel changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->afk_channel_id,
  /* specs/discord/audit_log.json:133:18
     '{"name":"afk_timeout", "type": {"base":"int"}, "comment":"afk timeout duration changed", "inject_if_not":0 }' */
                &p->afk_timeout,
  /* specs/discord/audit_log.json:134:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the rules channel changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->rules_channel_id,
  /* specs/discord/audit_log.json:135:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the public updates channel changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->public_updates_channel_id,
  /* specs/discord/audit_log.json:136:18
     '{"name":"mfa_level", "type": {"base":"int"}, "comment":"two-factor auth requirement changed", "inject_if_not":0 }' */
                &p->mfa_level,
  /* specs/discord/audit_log.json:137:18
     '{"name":"verification_level", "type": {"base":"int"}, "comment":"required verification level changed", "inject_if_not":0 }' */
                &p->verification_level,
  /* specs/discord/audit_log.json:138:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}, "comment":"change in whose messages are scanned and deleted for explicit content in the server", "inject_if_not":0 }' */
                &p->explicit_content_filter,
  /* specs/discord/audit_log.json:139:18
     '{"name":"default_message_notifications", "type": {"base":"int"}, "comment":"default message notification level changed", "inject_if_not":0 }' */
                &p->default_message_notifications,
  /* specs/discord/audit_log.json:140:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}, "comment":"guild invite vanity url changed", "inject_if_not":null }' */
                p->vanity_url_code,
  /* specs/discord/audit_log.json:141:18
     '{"name":"add", "json_key":"$add", "type": {"base":"struct discord_role", "dec":"ntl" }, "comment":"new role added", "inject_if_not":null }' */
                discord_role_list_to_json, p->add,
  /* specs/discord/audit_log.json:142:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"struct discord_role", "dec":"ntl"}, "comment":"role removed", "inject_if_not":null }' */
                discord_role_list_to_json, p->remove,
  /* specs/discord/audit_log.json:143:18
     '{"name":"prune_delete_days", "type": {"base":"int"}, "comment":"change in number of days after which inactive and role-unassigned members are kicked", "inject_if_not":0 }' */
                &p->prune_delete_days,
  /* specs/discord/audit_log.json:144:18
     '{"name":"widget_enabled", "type": {"base":"bool"}, "comment":"server widget enabled/disable"}' */
                &p->widget_enabled,
  /* specs/discord/audit_log.json:145:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel id of the server widget changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->widget_channel_id,
  /* specs/discord/audit_log.json:146:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the system channel changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->system_channel_id,
  /* specs/discord/audit_log.json:147:18
     '{"name":"position", "type": {"base":"int"}, "comment":"text or voice channel position changed"}' */
                &p->position,
  /* specs/discord/audit_log.json:148:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}, "comment":"text or voice chanenl position changed", "inject_if_not":null }' */
                p->topic,
  /* specs/discord/audit_log.json:149:18
     '{"name":"bitrate", "type": {"base":"int"}, "comment":"voice channel bitrate changed" }' */
                &p->bitrate,
  /* specs/discord/audit_log.json:150:18
     '{"name":"permission_overwrites", "type": {"base":"struct discord_overwrite", "dec":"ntl"}, "comment":"permissions on a channel changed" }' */
                discord_overwrite_list_to_json, p->permission_overwrites,
  /* specs/discord/audit_log.json:151:18
     '{"name":"nsfw", "type": {"base":"bool"}, "comment":"channel nsfw restriction changed" }' */
                &p->nsfw,
  /* specs/discord/audit_log.json:152:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"application id of the added or removed webhook or bot", "inject_if_not":0 }' */
                cee_ulltostr, &p->application_id,
  /* specs/discord/audit_log.json:153:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}, "comment":"amount of seconds a user has to wait before sending another message changed" }' */
                &p->rate_limit_per_user,
  /* specs/discord/audit_log.json:154:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}, "comment":"permissions for a role changed" }' */
                p->permissions,
  /* specs/discord/audit_log.json:155:18
     '{"name":"color", "type": {"base":"int"}, "comment":"role color changed" }' */
                &p->color,
  /* specs/discord/audit_log.json:156:18
     '{"name":"hoist", "type": {"base":"bool"}, "comment":"role is now diplayed/no longer displayed separate from online users" }' */
                &p->hoist,
  /* specs/discord/audit_log.json:157:18
     '{"name":"mentionable", "type": {"base":"bool"}, "comment":"role is now mentionable/unmentionable" }' */
                &p->mentionable,
  /* specs/discord/audit_log.json:158:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was allowed for a role" }' */
                p->allow,
  /* specs/discord/audit_log.json:159:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was denied for a role" }' */
                p->deny,
  /* specs/discord/audit_log.json:160:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}, "comment":"invite code changed" }' */
                p->code,
  /* specs/discord/audit_log.json:161:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel for invite code changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->channel_id,
  /* specs/discord/audit_log.json:162:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"person who created invite code changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->inviter_id,
  /* specs/discord/audit_log.json:163:18
     '{"name":"max_uses", "type": {"base":"int"}, "comment":"change to max number of times invite codes can be used" }' */
                &p->max_uses,
  /* specs/discord/audit_log.json:164:18
     '{"name":"uses", "type": {"base":"int"}, "comment":"number of times invite code used changed" }' */
                &p->uses,
  /* specs/discord/audit_log.json:165:18
     '{"name":"max_age", "type": {"base":"int"}, "comment":"how long invite code lasts changed" }' */
                &p->max_age,
  /* specs/discord/audit_log.json:166:18
     '{"name":"temporary", "type": {"base":"bool"}, "comment":"invite code is temporary/never expires" }' */
                &p->temporary,
  /* specs/discord/audit_log.json:167:18
     '{"name":"deaf", "type": {"base":"bool"}, "comment":"user server deafened/undefeaned" }' */
                &p->deaf,
  /* specs/discord/audit_log.json:168:18
     '{"name":"mute", "type": {"base":"bool"}, "comment":"user server muted/unmuted" }' */
                &p->mute,
  /* specs/discord/audit_log.json:169:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}, "comment":"user nickname/changed" }' */
                p->nick,
  /* specs/discord/audit_log.json:170:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"user avatar changed", "inject_if_not":"" }' */
                p->avatar_hash,
  /* specs/discord/audit_log.json:171:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the changed entity - sometimes used in conjunction with other keys", "inject_if_not":0 }' */
                cee_ulltostr, &p->id,
  /* specs/discord/audit_log.json:172:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, "todo":true, "comment":"type of entity created" }' */
  /* specs/discord/audit_log.json:173:18
     '{"name":"enable_emotions", "type": {"base":"bool"}, "comment":"integration emoticons enabled/disabled" }' */
                &p->enable_emotions,
  /* specs/discord/audit_log.json:174:18
     '{"name":"expire_behavior", "type": {"base":"int"}, "comment":"integration expiring subscriber behavior changed" }' */
                &p->expire_behavior,
  /* specs/discord/audit_log.json:175:18
     '{"name":"expire_grace_period", "type": {"base":"int"}, "comment":"integration expire grace period changed" }' */
                &p->expire_grace_period,
  /* specs/discord/audit_log.json:176:18
     '{"name":"user_limit", "type": {"base":"int" }, "comment":"new user limit in a voice channel" }' */
                &p->user_limit,
  /* specs/discord/audit_log.json:177:18
     '{"name":"privacy_level", "type": {"base":"int" }, "comment":"privacy level of stage instance changed" }' */
                &p->privacy_level,
  /* specs/discord/audit_log.json:178:18
     '{"name":"tags", "type": {"base":"char", "dec":"*" }, "comment":"related emoji of sticker changed", "inject_if_not":null }' */
                p->tags,
  /* specs/discord/audit_log.json:179:18
     '{"name":"format_type", "type": {"base":"int" }, "comment":"format type of sticker changed" }' */
                &p->format_type,
  /* specs/discord/audit_log.json:180:18
     '{"name":"asset", "type": {"base":"char", "dec":"*" }, "comment":"empty string", "inject_if_not":null }' */
                p->asset,
  /* specs/discord/audit_log.json:181:18
     '{"name":"available", "type": {"base":"bool" }, "comment":"availability of sticker changed" }' */
                &p->available,
  /* specs/discord/audit_log.json:182:18
     '{"name":"guild_id", "type": {"base":"char", "dec":"*", "converter":"snowflake" }, "comment":"guild sticker is in changed", "inject_if_not":0 }' */
                cee_ulltostr, &p->guild_id,
  /* specs/discord/audit_log.json:183:18
     '{"name":"archived", "type": {"base":"bool" }, "comment":"thread is now archived/unarchived" }' */
                &p->archived,
  /* specs/discord/audit_log.json:184:18
     '{"name":"locked", "type": {"base":"bool" }, "comment":"thread is now locked/unlocked" }' */
                &p->locked,
  /* specs/discord/audit_log.json:185:18
     '{"name":"auto_archive_duration", "type": {"base":"int" }, "comment":"auto archive duration changed" }' */
                &p->auto_archive_duration,
  /* specs/discord/audit_log.json:186:18
     '{"name":"default_auto_archive_duration", "type": {"base":"int" }, "comment":"default auto archive duration for newly created threads changed" }' */
                &p->default_auto_archive_duration,
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
  /* specs/discord/audit_log.json:123:18
     '{"name":"name", "type": {"base":"char", "dec":"*"}, "comment":"name changed", "inject_if_not":null }' */
  if (d->name)
    free(d->name);
  /* specs/discord/audit_log.json:124:18
     '{"name":"description", "type": {"base":"char", "dec":"*"}, "comment":"description changed", "inject_if_not":null }' */
  if (d->description)
    free(d->description);
  /* specs/discord/audit_log.json:125:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"icon changed", "inject_if_not":"" }' */
  // p->icon_hash is a scalar
  /* specs/discord/audit_log.json:126:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"invite splash page artwork changed", "inject_if_not":"" }' */
  // p->splash_hash is a scalar
  /* specs/discord/audit_log.json:127:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"discovery splash changed", "inject_if_not":"" }' */
  // p->discovery_splash_hash is a scalar
  /* specs/discord/audit_log.json:128:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"guild banned changed", "inject_if_not":"" }' */
  // p->banner_hash is a scalar
  /* specs/discord/audit_log.json:129:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"owner changed", "inject_if_not":0 }' */
  // p->owner_id is a scalar
  /* specs/discord/audit_log.json:130:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "comment":"region changed", "inject_if_not":"" }' */
  // p->region is a scalar
  /* specs/discord/audit_log.json:131:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "comment":"preferred locale changed", "inject_if_not":"" }' */
  // p->preferred_locale is a scalar
  /* specs/discord/audit_log.json:132:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"afk channel changed", "inject_if_not":0 }' */
  // p->afk_channel_id is a scalar
  /* specs/discord/audit_log.json:133:18
     '{"name":"afk_timeout", "type": {"base":"int"}, "comment":"afk timeout duration changed", "inject_if_not":0 }' */
  // p->afk_timeout is a scalar
  /* specs/discord/audit_log.json:134:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the rules channel changed", "inject_if_not":0 }' */
  // p->rules_channel_id is a scalar
  /* specs/discord/audit_log.json:135:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the public updates channel changed", "inject_if_not":0 }' */
  // p->public_updates_channel_id is a scalar
  /* specs/discord/audit_log.json:136:18
     '{"name":"mfa_level", "type": {"base":"int"}, "comment":"two-factor auth requirement changed", "inject_if_not":0 }' */
  // p->mfa_level is a scalar
  /* specs/discord/audit_log.json:137:18
     '{"name":"verification_level", "type": {"base":"int"}, "comment":"required verification level changed", "inject_if_not":0 }' */
  // p->verification_level is a scalar
  /* specs/discord/audit_log.json:138:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}, "comment":"change in whose messages are scanned and deleted for explicit content in the server", "inject_if_not":0 }' */
  // p->explicit_content_filter is a scalar
  /* specs/discord/audit_log.json:139:18
     '{"name":"default_message_notifications", "type": {"base":"int"}, "comment":"default message notification level changed", "inject_if_not":0 }' */
  // p->default_message_notifications is a scalar
  /* specs/discord/audit_log.json:140:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}, "comment":"guild invite vanity url changed", "inject_if_not":null }' */
  if (d->vanity_url_code)
    free(d->vanity_url_code);
  /* specs/discord/audit_log.json:141:18
     '{"name":"add", "json_key":"$add", "type": {"base":"struct discord_role", "dec":"ntl" }, "comment":"new role added", "inject_if_not":null }' */
  if (d->add)
    discord_role_list_free(d->add);
  /* specs/discord/audit_log.json:142:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"struct discord_role", "dec":"ntl"}, "comment":"role removed", "inject_if_not":null }' */
  if (d->remove)
    discord_role_list_free(d->remove);
  /* specs/discord/audit_log.json:143:18
     '{"name":"prune_delete_days", "type": {"base":"int"}, "comment":"change in number of days after which inactive and role-unassigned members are kicked", "inject_if_not":0 }' */
  // p->prune_delete_days is a scalar
  /* specs/discord/audit_log.json:144:18
     '{"name":"widget_enabled", "type": {"base":"bool"}, "comment":"server widget enabled/disable"}' */
  // p->widget_enabled is a scalar
  /* specs/discord/audit_log.json:145:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel id of the server widget changed", "inject_if_not":0 }' */
  // p->widget_channel_id is a scalar
  /* specs/discord/audit_log.json:146:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the system channel changed", "inject_if_not":0 }' */
  // p->system_channel_id is a scalar
  /* specs/discord/audit_log.json:147:18
     '{"name":"position", "type": {"base":"int"}, "comment":"text or voice channel position changed"}' */
  // p->position is a scalar
  /* specs/discord/audit_log.json:148:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}, "comment":"text or voice chanenl position changed", "inject_if_not":null }' */
  if (d->topic)
    free(d->topic);
  /* specs/discord/audit_log.json:149:18
     '{"name":"bitrate", "type": {"base":"int"}, "comment":"voice channel bitrate changed" }' */
  // p->bitrate is a scalar
  /* specs/discord/audit_log.json:150:18
     '{"name":"permission_overwrites", "type": {"base":"struct discord_overwrite", "dec":"ntl"}, "comment":"permissions on a channel changed" }' */
  if (d->permission_overwrites)
    discord_overwrite_list_free(d->permission_overwrites);
  /* specs/discord/audit_log.json:151:18
     '{"name":"nsfw", "type": {"base":"bool"}, "comment":"channel nsfw restriction changed" }' */
  // p->nsfw is a scalar
  /* specs/discord/audit_log.json:152:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"application id of the added or removed webhook or bot", "inject_if_not":0 }' */
  // p->application_id is a scalar
  /* specs/discord/audit_log.json:153:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}, "comment":"amount of seconds a user has to wait before sending another message changed" }' */
  // p->rate_limit_per_user is a scalar
  /* specs/discord/audit_log.json:154:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}, "comment":"permissions for a role changed" }' */
  if (d->permissions)
    free(d->permissions);
  /* specs/discord/audit_log.json:155:18
     '{"name":"color", "type": {"base":"int"}, "comment":"role color changed" }' */
  // p->color is a scalar
  /* specs/discord/audit_log.json:156:18
     '{"name":"hoist", "type": {"base":"bool"}, "comment":"role is now diplayed/no longer displayed separate from online users" }' */
  // p->hoist is a scalar
  /* specs/discord/audit_log.json:157:18
     '{"name":"mentionable", "type": {"base":"bool"}, "comment":"role is now mentionable/unmentionable" }' */
  // p->mentionable is a scalar
  /* specs/discord/audit_log.json:158:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was allowed for a role" }' */
  if (d->allow)
    free(d->allow);
  /* specs/discord/audit_log.json:159:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was denied for a role" }' */
  if (d->deny)
    free(d->deny);
  /* specs/discord/audit_log.json:160:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}, "comment":"invite code changed" }' */
  if (d->code)
    free(d->code);
  /* specs/discord/audit_log.json:161:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel for invite code changed", "inject_if_not":0 }' */
  // p->channel_id is a scalar
  /* specs/discord/audit_log.json:162:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"person who created invite code changed", "inject_if_not":0 }' */
  // p->inviter_id is a scalar
  /* specs/discord/audit_log.json:163:18
     '{"name":"max_uses", "type": {"base":"int"}, "comment":"change to max number of times invite codes can be used" }' */
  // p->max_uses is a scalar
  /* specs/discord/audit_log.json:164:18
     '{"name":"uses", "type": {"base":"int"}, "comment":"number of times invite code used changed" }' */
  // p->uses is a scalar
  /* specs/discord/audit_log.json:165:18
     '{"name":"max_age", "type": {"base":"int"}, "comment":"how long invite code lasts changed" }' */
  // p->max_age is a scalar
  /* specs/discord/audit_log.json:166:18
     '{"name":"temporary", "type": {"base":"bool"}, "comment":"invite code is temporary/never expires" }' */
  // p->temporary is a scalar
  /* specs/discord/audit_log.json:167:18
     '{"name":"deaf", "type": {"base":"bool"}, "comment":"user server deafened/undefeaned" }' */
  // p->deaf is a scalar
  /* specs/discord/audit_log.json:168:18
     '{"name":"mute", "type": {"base":"bool"}, "comment":"user server muted/unmuted" }' */
  // p->mute is a scalar
  /* specs/discord/audit_log.json:169:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}, "comment":"user nickname/changed" }' */
  if (d->nick)
    free(d->nick);
  /* specs/discord/audit_log.json:170:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"user avatar changed", "inject_if_not":"" }' */
  // p->avatar_hash is a scalar
  /* specs/discord/audit_log.json:171:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the changed entity - sometimes used in conjunction with other keys", "inject_if_not":0 }' */
  // p->id is a scalar
  /* specs/discord/audit_log.json:172:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, "todo":true, "comment":"type of entity created" }' */
  // @todo p->(null)
  /* specs/discord/audit_log.json:173:18
     '{"name":"enable_emotions", "type": {"base":"bool"}, "comment":"integration emoticons enabled/disabled" }' */
  // p->enable_emotions is a scalar
  /* specs/discord/audit_log.json:174:18
     '{"name":"expire_behavior", "type": {"base":"int"}, "comment":"integration expiring subscriber behavior changed" }' */
  // p->expire_behavior is a scalar
  /* specs/discord/audit_log.json:175:18
     '{"name":"expire_grace_period", "type": {"base":"int"}, "comment":"integration expire grace period changed" }' */
  // p->expire_grace_period is a scalar
  /* specs/discord/audit_log.json:176:18
     '{"name":"user_limit", "type": {"base":"int" }, "comment":"new user limit in a voice channel" }' */
  // p->user_limit is a scalar
  /* specs/discord/audit_log.json:177:18
     '{"name":"privacy_level", "type": {"base":"int" }, "comment":"privacy level of stage instance changed" }' */
  // p->privacy_level is a scalar
  /* specs/discord/audit_log.json:178:18
     '{"name":"tags", "type": {"base":"char", "dec":"*" }, "comment":"related emoji of sticker changed", "inject_if_not":null }' */
  if (d->tags)
    free(d->tags);
  /* specs/discord/audit_log.json:179:18
     '{"name":"format_type", "type": {"base":"int" }, "comment":"format type of sticker changed" }' */
  // p->format_type is a scalar
  /* specs/discord/audit_log.json:180:18
     '{"name":"asset", "type": {"base":"char", "dec":"*" }, "comment":"empty string", "inject_if_not":null }' */
  if (d->asset)
    free(d->asset);
  /* specs/discord/audit_log.json:181:18
     '{"name":"available", "type": {"base":"bool" }, "comment":"availability of sticker changed" }' */
  // p->available is a scalar
  /* specs/discord/audit_log.json:182:18
     '{"name":"guild_id", "type": {"base":"char", "dec":"*", "converter":"snowflake" }, "comment":"guild sticker is in changed", "inject_if_not":0 }' */
  // p->guild_id is a scalar
  /* specs/discord/audit_log.json:183:18
     '{"name":"archived", "type": {"base":"bool" }, "comment":"thread is now archived/unarchived" }' */
  // p->archived is a scalar
  /* specs/discord/audit_log.json:184:18
     '{"name":"locked", "type": {"base":"bool" }, "comment":"thread is now locked/unlocked" }' */
  // p->locked is a scalar
  /* specs/discord/audit_log.json:185:18
     '{"name":"auto_archive_duration", "type": {"base":"int" }, "comment":"auto archive duration changed" }' */
  // p->auto_archive_duration is a scalar
  /* specs/discord/audit_log.json:186:18
     '{"name":"default_auto_archive_duration", "type": {"base":"int" }, "comment":"default auto archive duration for newly created threads changed" }' */
  // p->default_auto_archive_duration is a scalar
}

void discord_audit_log_change_key_init(struct discord_audit_log_change_key *p) {
  memset(p, 0, sizeof(struct discord_audit_log_change_key));
  /* specs/discord/audit_log.json:123:18
     '{"name":"name", "type": {"base":"char", "dec":"*"}, "comment":"name changed", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:124:18
     '{"name":"description", "type": {"base":"char", "dec":"*"}, "comment":"description changed", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:125:18
     '{"name":"icon_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"icon changed", "inject_if_not":"" }' */

  /* specs/discord/audit_log.json:126:18
     '{"name":"splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"invite splash page artwork changed", "inject_if_not":"" }' */

  /* specs/discord/audit_log.json:127:18
     '{"name":"discovery_splash_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"discovery splash changed", "inject_if_not":"" }' */

  /* specs/discord/audit_log.json:128:18
     '{"name":"banner_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"guild banned changed", "inject_if_not":"" }' */

  /* specs/discord/audit_log.json:129:18
     '{"name":"owner_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"owner changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:130:18
     '{"name":"region", "type": {"base":"char", "dec":"[ORCA_LIMITS_REGION]"}, "comment":"region changed", "inject_if_not":"" }' */

  /* specs/discord/audit_log.json:131:18
     '{"name":"preferred_locale", "type": {"base":"char", "dec":"[ORCA_LIMITS_LOCALE]"}, "comment":"preferred locale changed", "inject_if_not":"" }' */

  /* specs/discord/audit_log.json:132:18
     '{"name":"afk_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"afk channel changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:133:18
     '{"name":"afk_timeout", "type": {"base":"int"}, "comment":"afk timeout duration changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:134:18
     '{"name":"rules_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the rules channel changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:135:18
     '{"name":"public_updates_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the public updates channel changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:136:18
     '{"name":"mfa_level", "type": {"base":"int"}, "comment":"two-factor auth requirement changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:137:18
     '{"name":"verification_level", "type": {"base":"int"}, "comment":"required verification level changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:138:18
     '{"name":"explicit_content_filter", "type": {"base":"int"}, "comment":"change in whose messages are scanned and deleted for explicit content in the server", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:139:18
     '{"name":"default_message_notifications", "type": {"base":"int"}, "comment":"default message notification level changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:140:18
     '{"name":"vanity_url_code", "type": {"base":"char", "dec":"*"}, "comment":"guild invite vanity url changed", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:141:18
     '{"name":"add", "json_key":"$add", "type": {"base":"struct discord_role", "dec":"ntl" }, "comment":"new role added", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:142:18
     '{"name":"remove", "json_key":"$remove", "type": {"base":"struct discord_role", "dec":"ntl"}, "comment":"role removed", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:143:18
     '{"name":"prune_delete_days", "type": {"base":"int"}, "comment":"change in number of days after which inactive and role-unassigned members are kicked", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:144:18
     '{"name":"widget_enabled", "type": {"base":"bool"}, "comment":"server widget enabled/disable"}' */

  /* specs/discord/audit_log.json:145:18
     '{"name":"widget_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel id of the server widget changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:146:18
     '{"name":"system_channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the system channel changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:147:18
     '{"name":"position", "type": {"base":"int"}, "comment":"text or voice channel position changed"}' */

  /* specs/discord/audit_log.json:148:18
     '{"name":"topic", "type": {"base":"char", "dec":"*"}, "comment":"text or voice chanenl position changed", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:149:18
     '{"name":"bitrate", "type": {"base":"int"}, "comment":"voice channel bitrate changed" }' */

  /* specs/discord/audit_log.json:150:18
     '{"name":"permission_overwrites", "type": {"base":"struct discord_overwrite", "dec":"ntl"}, "comment":"permissions on a channel changed" }' */

  /* specs/discord/audit_log.json:151:18
     '{"name":"nsfw", "type": {"base":"bool"}, "comment":"channel nsfw restriction changed" }' */

  /* specs/discord/audit_log.json:152:18
     '{"name":"application_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"application id of the added or removed webhook or bot", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:153:18
     '{"name":"rate_limit_per_user", "type": {"base":"int"}, "comment":"amount of seconds a user has to wait before sending another message changed" }' */

  /* specs/discord/audit_log.json:154:18
     '{"name":"permissions", "type": {"base":"char", "dec":"*"}, "comment":"permissions for a role changed" }' */

  /* specs/discord/audit_log.json:155:18
     '{"name":"color", "type": {"base":"int"}, "comment":"role color changed" }' */

  /* specs/discord/audit_log.json:156:18
     '{"name":"hoist", "type": {"base":"bool"}, "comment":"role is now diplayed/no longer displayed separate from online users" }' */

  /* specs/discord/audit_log.json:157:18
     '{"name":"mentionable", "type": {"base":"bool"}, "comment":"role is now mentionable/unmentionable" }' */

  /* specs/discord/audit_log.json:158:18
     '{"name":"allow", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was allowed for a role" }' */

  /* specs/discord/audit_log.json:159:18
     '{"name":"deny", "type": {"base":"char", "dec":"*"}, "comment":"a permission on a text or voice channel was denied for a role" }' */

  /* specs/discord/audit_log.json:160:18
     '{"name":"code", "type": {"base":"char", "dec":"*"}, "comment":"invite code changed" }' */

  /* specs/discord/audit_log.json:161:18
     '{"name":"channel_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"channel for invite code changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:162:18
     '{"name":"inviter_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"person who created invite code changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:163:18
     '{"name":"max_uses", "type": {"base":"int"}, "comment":"change to max number of times invite codes can be used" }' */

  /* specs/discord/audit_log.json:164:18
     '{"name":"uses", "type": {"base":"int"}, "comment":"number of times invite code used changed" }' */

  /* specs/discord/audit_log.json:165:18
     '{"name":"max_age", "type": {"base":"int"}, "comment":"how long invite code lasts changed" }' */

  /* specs/discord/audit_log.json:166:18
     '{"name":"temporary", "type": {"base":"bool"}, "comment":"invite code is temporary/never expires" }' */

  /* specs/discord/audit_log.json:167:18
     '{"name":"deaf", "type": {"base":"bool"}, "comment":"user server deafened/undefeaned" }' */

  /* specs/discord/audit_log.json:168:18
     '{"name":"mute", "type": {"base":"bool"}, "comment":"user server muted/unmuted" }' */

  /* specs/discord/audit_log.json:169:18
     '{"name":"nick", "type": {"base":"char", "dec":"*"}, "comment":"user nickname/changed" }' */

  /* specs/discord/audit_log.json:170:18
     '{"name":"avatar_hash", "type": {"base":"char", "dec":"[ORCA_LIMITS_SHA256]"}, "comment":"user avatar changed", "inject_if_not":"" }' */

  /* specs/discord/audit_log.json:171:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the id of the changed entity - sometimes used in conjunction with other keys", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:172:18
     '{"name":"type", "type": {"base":"char", "dec":"*"}, "todo":true, "comment":"type of entity created" }' */

  /* specs/discord/audit_log.json:173:18
     '{"name":"enable_emotions", "type": {"base":"bool"}, "comment":"integration emoticons enabled/disabled" }' */

  /* specs/discord/audit_log.json:174:18
     '{"name":"expire_behavior", "type": {"base":"int"}, "comment":"integration expiring subscriber behavior changed" }' */

  /* specs/discord/audit_log.json:175:18
     '{"name":"expire_grace_period", "type": {"base":"int"}, "comment":"integration expire grace period changed" }' */

  /* specs/discord/audit_log.json:176:18
     '{"name":"user_limit", "type": {"base":"int" }, "comment":"new user limit in a voice channel" }' */

  /* specs/discord/audit_log.json:177:18
     '{"name":"privacy_level", "type": {"base":"int" }, "comment":"privacy level of stage instance changed" }' */

  /* specs/discord/audit_log.json:178:18
     '{"name":"tags", "type": {"base":"char", "dec":"*" }, "comment":"related emoji of sticker changed", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:179:18
     '{"name":"format_type", "type": {"base":"int" }, "comment":"format type of sticker changed" }' */

  /* specs/discord/audit_log.json:180:18
     '{"name":"asset", "type": {"base":"char", "dec":"*" }, "comment":"empty string", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:181:18
     '{"name":"available", "type": {"base":"bool" }, "comment":"availability of sticker changed" }' */

  /* specs/discord/audit_log.json:182:18
     '{"name":"guild_id", "type": {"base":"char", "dec":"*", "converter":"snowflake" }, "comment":"guild sticker is in changed", "inject_if_not":0 }' */

  /* specs/discord/audit_log.json:183:18
     '{"name":"archived", "type": {"base":"bool" }, "comment":"thread is now archived/unarchived" }' */

  /* specs/discord/audit_log.json:184:18
     '{"name":"locked", "type": {"base":"bool" }, "comment":"thread is now locked/unlocked" }' */

  /* specs/discord/audit_log.json:185:18
     '{"name":"auto_archive_duration", "type": {"base":"int" }, "comment":"auto archive duration changed" }' */

  /* specs/discord/audit_log.json:186:18
     '{"name":"default_auto_archive_duration", "type": {"base":"int" }, "comment":"default auto archive duration for newly created threads changed" }' */

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

