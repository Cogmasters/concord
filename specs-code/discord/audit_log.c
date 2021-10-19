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
  static size_t ret=0; /**< used for debugging */
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
                "(threads):F,",
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
                discord_channel_list_from_json, &p->threads);
  ret = r;
}

size_t discord_audit_log_to_json(char *json, size_t len, struct discord_audit_log *p)
{
  size_t r;
  void *arg_switches[5]={NULL};
  /* specs/discord/audit_log.json:12:18
     '{"name":"webhooks", "type": { "base":"struct discord_webhook", "dec":"ntl" }, "comment":"list of webhooks found in the audit log", "inject_if_not":null }' */
  if (p->webhooks != NULL)
    arg_switches[0] = p->webhooks;

  /* specs/discord/audit_log.json:13:18
     '{"name":"users", "type": { "base":"struct discord_user", "dec":"ntl"}, "comment":"list of users found in the audit log", "inject_if_not":null}' */
  if (p->users != NULL)
    arg_switches[1] = p->users;

  /* specs/discord/audit_log.json:14:18
     '{"name":"audit_log_entries", "type": { "base":"struct discord_audit_log_entry", "dec":"ntl"}, "comment":"list of audit log entries", "inject_if_not":null}' */
  if (p->audit_log_entries != NULL)
    arg_switches[2] = p->audit_log_entries;

  /* specs/discord/audit_log.json:15:18
     '{"name":"integrations", "type": { "base":"struct discord_integration", "dec":"ntl"}, "comment":"list of partial integration objects", "inject_if_not":null}' */
  if (p->integrations != NULL)
    arg_switches[3] = p->integrations;

  /* specs/discord/audit_log.json:16:18
     '{"name":"threads", "type": { "base":"struct discord_channel", "dec":"ntl"}, "comment":"list of threads found in the audit log", "inject_if_not":null}' */
  if (p->threads != NULL)
    arg_switches[4] = p->threads;

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
                arg_switches, sizeof(arg_switches), true);
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
  static size_t ret=0; /**< used for debugging */
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
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */
                "(reason):?s,",
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
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */
                &p->reason);
  ret = r;
}

size_t discord_audit_log_entry_to_json(char *json, size_t len, struct discord_audit_log_entry *p)
{
  size_t r;
  void *arg_switches[7]={NULL};
  /* specs/discord/audit_log.json:26:18
     '{"name":"target_id", "type": {"base":"char", "dec":"*"}, "comment":"id of the affected entity (webhook,user,role,etc.)", "inject_if_not":null }' */
  if (p->target_id != NULL)
    arg_switches[0] = p->target_id;

  /* specs/discord/audit_log.json:27:18
     '{"name":"changes", "type": {"base":"struct discord_audit_log_change", "dec":"ntl"}, "comment":"changes made to the target_id", "inject_if_not":null }' */
  if (p->changes != NULL)
    arg_switches[1] = p->changes;

  /* specs/discord/audit_log.json:28:18
     '{"name":"user_id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"the user who made the changes", "inject_if_not":0 }' */
  if (p->user_id != 0)
    arg_switches[2] = &p->user_id;

  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
  if (p->id != 0)
    arg_switches[3] = &p->id;

  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
  if (p->action_type != 0)
    arg_switches[4] = &p->action_type;

  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
  if (p->options != NULL)
    arg_switches[5] = p->options;

  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */
  if (p->reason != NULL)
    arg_switches[6] = p->reason;

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
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */
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
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */
                p->reason,
                arg_switches, sizeof(arg_switches), true);
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
  /* p->user_id is a scalar */
  /* specs/discord/audit_log.json:29:18
     '{"name":"id", "type": {"base":"char", "dec":"*", "converter":"snowflake"}, "comment":"id of the entry", "inject_if_not":0 }' */
  /* p->id is a scalar */
  /* specs/discord/audit_log.json:30:18
     '{"name":"action_type", "type": {"base":"int", "c_base":"enum discord_audit_log_events"}, "comment":"type of action that occured", "inject_if_not":0 }' */
  /* p->action_type is a scalar */
  /* specs/discord/audit_log.json:31:18
     '{"name":"options", "type": {"base":"struct discord_optional_audit_entry_info", "dec":"ntl"}, "comment":"additional info for certain action types", "inject_if_not":null }' */
  if (d->options)
    discord_optional_audit_entry_info_list_free(d->options);
  /* specs/discord/audit_log.json:32:18
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */
  if (d->reason)
    free(d->reason);
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
     '{"name":"reason", "type": {"base":"char", "dec":"*"}, "comment":"the reason for the change", "inject_if_not":null }' */

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
  static size_t ret=0; /**< used for debugging */
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
                "(role_name):?s,",
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
                &p->role_name);
  ret = r;
}

size_t discord_optional_audit_entry_info_to_json(char *json, size_t len, struct discord_optional_audit_entry_info *p)
{
  size_t r;
  void *arg_switches[8]={NULL};
  /* specs/discord/audit_log.json:94:20
     '{ "name": "delete_member_days", "type":{ "base":"char", "dec":"*"}, "comment":"number of days after which inactive members were kicked", "inject_if_not":null }' */
  if (p->delete_member_days != NULL)
    arg_switches[0] = p->delete_member_days;

  /* specs/discord/audit_log.json:95:20
     '{ "name": "members_removed", "type":{ "base":"char", "dec":"*"}, "comment":"number of members removed by the prune", "inject_if_not":null }' */
  if (p->members_removed != NULL)
    arg_switches[1] = p->members_removed;

  /* specs/discord/audit_log.json:96:20
     '{ "name": "channel_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"channel in which the entities were targeted", "inject_if_not":0 }' */
  if (p->channel_id != 0)
    arg_switches[2] = &p->channel_id;

  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
  if (p->message_id != 0)
    arg_switches[3] = &p->message_id;

  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
  if (p->count != NULL)
    arg_switches[4] = p->count;

  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
  if (p->id != 0)
    arg_switches[5] = &p->id;

  /* specs/discord/audit_log.json:100:20
     '{ "name": "type", "type":{ "base":"char", "dec":"*" }, "comment":"type of overwritten entity - '0' for role or '1' for member", "inject_if_not":null }' */
  if (p->type != NULL)
    arg_switches[6] = p->type;

  /* specs/discord/audit_log.json:101:20
     '{ "name": "role_name", "type":{ "base":"char", "dec":"*" }, "comment":"name of the role if type is '0' (not present if type is '1')", "inject_if_not":null }' */
  if (p->role_name != NULL)
    arg_switches[7] = p->role_name;

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
                arg_switches, sizeof(arg_switches), true);
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
  /* p->channel_id is a scalar */
  /* specs/discord/audit_log.json:97:20
     '{ "name": "message_id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the message that was targeted", "inject_if_not":0 }' */
  /* p->message_id is a scalar */
  /* specs/discord/audit_log.json:98:20
     '{ "name": "count", "type":{ "base":"char", "dec":"*" }, "comment":"number of entities that were targeted", "inject_if_not":null }' */
  if (d->count)
    free(d->count);
  /* specs/discord/audit_log.json:99:20
     '{ "name": "id", "type":{ "base":"char", "dec":"*", "converter":"snowflake" }, "comment":"id of the ovewritten entity", "inject_if_not":0 }' */
  /* p->id is a scalar */
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
  static size_t ret=0; /**< used for debugging */
  size_t r=0;
  if (!*pp) *pp = malloc(sizeof **pp);
  struct discord_audit_log_change *p = *pp;
  discord_audit_log_change_init(p);
  r=json_extract(json, len, 
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */
                "(new_value):F,"
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */
                "(old_value):F,"
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
                "(key):?s,",
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */
                cee_strndup, &p->new_value,
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */
                cee_strndup, &p->old_value,
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
                &p->key);
  ret = r;
}

size_t discord_audit_log_change_to_json(char *json, size_t len, struct discord_audit_log_change *p)
{
  size_t r;
  void *arg_switches[3]={NULL};
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */
  if (p->new_value != NULL)
    arg_switches[0] = p->new_value;

  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */
  if (p->old_value != NULL)
    arg_switches[1] = p->old_value;

  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
  if (p->key != NULL)
    arg_switches[2] = p->key;

  r=json_inject(json, len, 
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */
                "(new_value):s,"
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */
                "(old_value):s,"
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
                "(key):s,"
                "@arg_switches:b",
  /* specs/discord/audit_log.json:111:18
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */
                p->new_value,
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */
                p->old_value,
  /* specs/discord/audit_log.json:113:18
     '{"name":"key", "type":{"base":"char", "dec":"*"}, "comment":"name of audit log change key", "inject_if_not":null }' */
                p->key,
                arg_switches, sizeof(arg_switches), true);
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
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */
  if (d->new_value)
    free(d->new_value);
  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */
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
     '{"name":"new_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"new value of the key", "inject_if_not":null }' */

  /* specs/discord/audit_log.json:112:18
     '{"name":"old_value", "type": {"base":"char", "dec":"*", "converter":"mixed"}, "comment":"old value of the key", "inject_if_not":null }' */

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

