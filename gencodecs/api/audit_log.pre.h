/*****************************************************************************
 * Audit Logs Datatypes
 * **************************************************************************/

ENUM(discord_audit_log_events)
    ENUMERATOR(DISCORD_AUDIT_LOG_GUILD_UPDATE, = 1)
    ENUMERATOR(DISCORD_AUDIT_LOG_CHANNEL_CREATE, = 10)
    ENUMERATOR(DISCORD_AUDIT_LOG_CHANNEL_UPDATE, = 11)
    ENUMERATOR(DISCORD_AUDIT_LOG_CHANNEL_DELETE, = 12)
    ENUMERATOR(DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_CREATE, = 13)
    ENUMERATOR(DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_UPDATE, = 14)
    ENUMERATOR(DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_DELETE, = 15)
    ENUMERATOR(DISCORD_AUDIT_LOG_MEMBER_KICK, = 20)
    ENUMERATOR(DISCORD_AUDIT_LOG_MEMBER_PRUNE, = 21)
    ENUMERATOR(DISCORD_AUDIT_LOG_MEMBER_BAN_ADD, = 22)
    ENUMERATOR(DISCORD_AUDIT_LOG_MEMBER_BAN_REMOVE, = 23)
    ENUMERATOR(DISCORD_AUDIT_LOG_MEMBER_UPDATE, = 24)
    ENUMERATOR(DISCORD_AUDIT_LOG_MEMBER_ROLE_UPDATE, = 25)
    ENUMERATOR(DISCORD_AUDIT_LOG_MEMBER_MOVE, = 26)
    ENUMERATOR(DISCORD_AUDIT_LOG_MEMBER_DISCONNECT, = 27)
    ENUMERATOR(DISCORD_AUDIT_LOG_BOT_ADD, = 28)
    ENUMERATOR(DISCORD_AUDIT_LOG_ROLE_CREATE, = 30)
    ENUMERATOR(DISCORD_AUDIT_LOG_ROLE_UPDATE, = 31)
    ENUMERATOR(DISCORD_AUDIT_LOG_ROLE_DELETE, = 32)
    ENUMERATOR(DISCORD_AUDIT_LOG_INVITE_CREATE, = 40)
    ENUMERATOR(DISCORD_AUDIT_LOG_INVITE_UPDATE, = 41)
    ENUMERATOR(DISCORD_AUDIT_LOG_INVITE_DELETE, = 42)
    ENUMERATOR(DISCORD_AUDIT_LOG_WEBHOOK_CREATE, = 50)
    ENUMERATOR(DISCORD_AUDIT_LOG_WEBHOOK_UPDATE, = 51)
    ENUMERATOR(DISCORD_AUDIT_LOG_WEBHOOK_DELETE, = 52)
    ENUMERATOR(DISCORD_AUDIT_LOG_EMOJI_CREATE, = 60)
    ENUMERATOR(DISCORD_AUDIT_LOG_EMOJI_UPDATE, = 61)
    ENUMERATOR(DISCORD_AUDIT_LOG_EMOJI_DELETE, = 62)
    ENUMERATOR(DISCORD_AUDIT_LOG_MESSAGE_DELETE, = 72)
    ENUMERATOR(DISCORD_AUDIT_LOG_MESSAGE_BULK_DELETE, = 73)
    ENUMERATOR(DISCORD_AUDIT_LOG_MESSAGE_PIN, = 74)
    ENUMERATOR(DISCORD_AUDIT_LOG_MESSAGE_UNPIN, = 75)
    ENUMERATOR(DISCORD_AUDIT_LOG_INTEGRATION_CREATE, = 80)
    ENUMERATOR(DISCORD_AUDIT_LOG_INTEGRATION_UPDATE, = 81)
    ENUMERATOR(DISCORD_AUDIT_LOG_INTEGRATION_DELETE, = 82)
    ENUMERATOR(DISCORD_AUDIT_LOG_STAGE_INSTANCE_CREATE, = 83)
    ENUMERATOR(DISCORD_AUDIT_LOG_STAGE_INSTANCE_UPDATE, = 84)
    ENUMERATOR(DISCORD_AUDIT_LOG_STAGE_INSTANCE_DELETE, = 85)
    ENUMERATOR(DISCORD_AUDIT_LOG_STICKER_CREATE, = 90)
    ENUMERATOR(DISCORD_AUDIT_LOG_STICKER_UPDATE, = 91)
    ENUMERATOR(DISCORD_AUDIT_LOG_STICKER_DELETE, = 92)
    ENUMERATOR(DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_CREATE, = 100)
    ENUMERATOR(DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_UPDATE, = 101)
    ENUMERATOR(DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_DELETE, = 102)
    ENUMERATOR(DISCORD_AUDIT_LOG_THREAD_CREATE, = 110)
    ENUMERATOR(DISCORD_AUDIT_LOG_THREAD_UPDATE, = 111)
    ENUMERATOR_LAST(DISCORD_AUDIT_LOG_THREAD_DELETE, = 112)
ENUM_END

/** @CCORD_pub_struct{discord_audit_log} */
PUB_STRUCT(discord_audit_log)
  PP("list of audit log entries")
  COND_WRITE(this->audit_log_entries != NULL)
    FIELD_STRUCT_PTR(audit_log_entries, discord_audit_log_entries, *)
  COND_END
  PP("list of guild scheduled events found in the audit log")
  COND_WRITE(this->guild_scheduled_events != NULL)
    FIELD_STRUCT_PTR(guild_scheduled_events, discord_guild_scheduled_events, *)
  COND_END
  PP("list of partial integration objects")
  COND_WRITE(this->integrations != NULL)
    FIELD_STRUCT_PTR(integrations, discord_integrations, *)
  COND_END
  PP("list of threads found in the audit log")
  COND_WRITE(this->threads != NULL)
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  COND_END
  PP("list of users found in the audit log")
  COND_WRITE(this->users != NULL)
    FIELD_STRUCT_PTR(users, discord_users, *)
  COND_END
  PP("list of webhooks found in the audit log")
  COND_WRITE(this->webhooks != NULL)
    FIELD_STRUCT_PTR(webhooks, discord_webhooks, *)
  COND_END
STRUCT_END

STRUCT(discord_audit_log_entry)
  PP("ID of the affected entity (webhook, user, role, etc.)")
    FIELD_SNOWFLAKE(target_id)
  PP("changes made to the target_id")
  COND_WRITE(this->changes != NULL)
    FIELD_STRUCT_PTR(changes, discord_audit_log_changes, *)
  COND_END
  PP("the user who made the changes")
    FIELD_SNOWFLAKE(user_id)
  PP("id of the entry")
    FIELD_SNOWFLAKE(id)
  PP("type of action that occurred")
  COND_WRITE(this->action_type != 0)
    FIELD_ENUM(action_type, discord_audit_log_events)
  COND_END
  PP("additional info for certain action types")
  COND_WRITE(this->options != NULL)
    FIELD_STRUCT_PTR(options, discord_optional_audit_entry_infos, *)
  COND_END
  PP("the reason for the change (0-512) characters")
    FIELD_PTR(reason, char, *)
STRUCT_END

LIST(discord_audit_log_entries)
    LISTTYPE_STRUCT(discord_audit_log_entry)
LIST_END

STRUCT(discord_optional_audit_entry_info)
  PP("channel in which the entities were targeted")
    FIELD_SNOWFLAKE(channel_id)
  PP("number of entities that were targeted")
    FIELD_PTR(count, char, *)
  PP("number of days after which inactive members were kicked")
    FIELD_PTR(delete_member_days, char, *)
  PP("id of the overwritten entity")
    FIELD_SNOWFLAKE(id)
  PP("number of members removed by prune")
    FIELD_PTR(members_removed, char, *)
  PP("ID of the message that was targeted")
    FIELD_SNOWFLAKE(message_id)
  PP("name of the role if type is \"0\" (not present if type is \"1\")")
    FIELD_PTR(role_name, char, *)
  PP("type of overwritten entity - 0 for role or 1 for \"member\"")
    FIELD_PTR(type, char, *)
STRUCT_END

LIST(discord_optional_audit_entry_infos)
    LISTTYPE_STRUCT(discord_optional_audit_entry_info)
LIST_END

STRUCT(discord_audit_log_change)
  PP("new value of the key")
    FIELD_PTR(new_value, json_char, *)
  PP("old value of the key")
    FIELD_PTR(old_value, json_char, *)
  PP("name of audit log change key")
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
  PP("filter the log for actions made by a user")
    FIELD_SNOWFLAKE(user_id)
  PP("the type of audit log event")
    FIELD(action_type, int, 0)
  PP("filter the log before a certain entry ID")
    FIELD_SNOWFLAKE(before)
  PP("how many entries are returned (default 50, minimum 1, maximum 100)")
  COND_WRITE(this->limit >= 1 && this->limit <= 100)
    FIELD(limit, int, 50)
  COND_END
STRUCT_END
