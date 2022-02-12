/*****************************************************************************
 * Audit Logs Datatypes
 * **************************************************************************/

PUB_STRUCT(discord_audit_log)
  DESC("list of audit log entries")
  COND_WRITE(this->audit_log_entries != NULL)
    FIELD_STRUCT_PTR(audit_log_entries, discord_audit_log_entries, *)
  COND_END
  DESC("list of guild scheduled events found in the audit log")
  COND_WRITE(this->guild_scheduled_events != NULL)
    FIELD_STRUCT_PTR(guild_scheduled_events, discord_guild_scheduled_events, *)
  COND_END
  DESC("list of partial integration objects")
  COND_WRITE(this->integrations != NULL)
    FIELD_STRUCT_PTR(integrations, discord_integrations, *)
  COND_END
  DESC("list of threads found in the audit log")
  COND_WRITE(this->threads != NULL)
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  COND_END
  DESC("list of users found in the audit log")
  COND_WRITE(this->users != NULL)
    FIELD_STRUCT_PTR(users, discord_users, *)
  COND_END
  DESC("list of webhooks found in the audit log")
  COND_WRITE(this->webhooks != NULL)
    FIELD_STRUCT_PTR(webhooks, discord_webhooks, *)
  COND_END
STRUCT_END

STRUCT(discord_audit_log_entry)
  DESC("ID of the affected entity (webhook, user, role, etc.)")
    FIELD_PRINTF(target_id, u64snowflake, PRIu64, SCNu64)
  DESC("changes made to the target_id")
  COND_WRITE(this->changes != NULL)
    FIELD_STRUCT_PTR(changes, discord_audit_log_changes, *)
  COND_END
  DESC("the user who made the changes")
    FIELD_PRINTF(user_id, u64snowflake, PRIu64, SCNu64)
  DESC("id of the entry")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("type of action that occurred")
  COND_WRITE(this->action_type != 0)
    FIELD_ENUM(action_type, discord_audit_log_events)
  COND_END
  DESC("additional info for certain action types")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_optional_audit_entry_infos, *)
  COND_END
  DESC("the reason for the change (0-512) characters")
    FIELD_PTR(reason, char, *)
STRUCT_END

LIST(discord_audit_log_entries)
    LISTTYPE_STRUCT(discord_audit_log_entry)
LIST_END

STRUCT(discord_optional_audit_entry_info)
  DESC("channel in which the entities were targeted")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("number of entities that were targeted")
    FIELD_PTR(count, char, *)
  DESC("number of days after which inactive members were kicked")
    FIELD_PTR(delete_member_days, char, *)
  DESC("id of the overwritten entity")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("number of members removed by prune")
    FIELD_PTR(members_removed, char, *)
  DESC("ID of the message that was targeted")
    FIELD_PRINTF(message_id, u64snowflake, PRIu64, SCNu64)
  DESC("name of the role if type is \"0\" (not present if type is \"1\")")
    FIELD_PTR(role_name, char, *)
  DESC("type of overwritten entity - 0 for role or 1 for \"member\"")
    FIELD_PTR(type, char, *)
STRUCT_END

LIST(discord_optional_audit_entry_infos)
    LISTTYPE_STRUCT(discord_optional_audit_entry_info)
LIST_END

STRUCT(discord_audit_log_change)
  DESC("new value of the key")
    FIELD_PTR(new_value, json_char, *)
  DESC("old value of the key")
    FIELD_PTR(old_value, json_char, *)
  DESC("name of audit log change key")
    FIELD_PTR(key, char, *)
STRUCT_END

LIST(discord_audit_log_changes)
    LISTTYPE_STRUCT(discord_audit_log_change)
LIST_END

/*****************************************************************************
 * Audit Logs REST parameters
 * **************************************************************************/

/* TODO: disable JSON encoding functions */
STRUCT(discord_get_guild_audit_log)
  DESC("filter the log for actions made by a user")
    FIELD_PRINTF(user_id, u64snowflake, PRIu64, SCNu64)
  DESC("the type of audit log event")
    FIELD(action_type, int, 0)
  DESC("filter the log before a certain entry ID")
    FIELD_PRINTF(before, u64snowflake, PRIu64, SCNu64)
  DESC("how many entries are returned (default 50, minimum 1, maximum 100)")
  COND_WRITE(this->limit >= 1 && this->limit <= 100)
    FIELD(limit, int, 50)
  COND_END
STRUCT_END
