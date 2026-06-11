PUBLIC(enum, discord_audit_log_events, 52, (
        (DISCORD_AUDIT_LOG_GUILD_UPDATE, =, 1),
        (DISCORD_AUDIT_LOG_CHANNEL_CREATE, =, 10),
        (DISCORD_AUDIT_LOG_CHANNEL_UPDATE, =, 11),
        (DISCORD_AUDIT_LOG_CHANNEL_DELETE, =, 12),
        (DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_CREATE, =, 13),
        (DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_UPDATE, =, 14),
        (DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_DELETE, =, 15),
        (DISCORD_AUDIT_LOG_MEMBER_KICK, =, 20),
        (DISCORD_AUDIT_LOG_MEMBER_PRUNE, =, 21),
        (DISCORD_AUDIT_LOG_MEMBER_BAN_ADD, =, 22),
        (DISCORD_AUDIT_LOG_MEMBER_BAN_REMOVE, =, 23),
        (DISCORD_AUDIT_LOG_MEMBER_UPDATE, =, 24),
        (DISCORD_AUDIT_LOG_MEMBER_ROLE_UPDATE, =, 25),
        (DISCORD_AUDIT_LOG_MEMBER_MOVE, =, 26),
        (DISCORD_AUDIT_LOG_MEMBER_DISCONNECT, =, 27),
        (DISCORD_AUDIT_LOG_BOT_ADD, =, 28),
        (DISCORD_AUDIT_LOG_ROLE_CREATE, =, 30),
        (DISCORD_AUDIT_LOG_ROLE_UPDATE, =, 31),
        (DISCORD_AUDIT_LOG_ROLE_DELETE, =, 32),
        (DISCORD_AUDIT_LOG_INVITE_CREATE, =, 40),
        (DISCORD_AUDIT_LOG_INVITE_UPDATE, =, 41),
        (DISCORD_AUDIT_LOG_INVITE_DELETE, =, 42),
        (DISCORD_AUDIT_LOG_WEBHOOK_CREATE, =, 50),
        (DISCORD_AUDIT_LOG_WEBHOOK_UPDATE, =, 51),
        (DISCORD_AUDIT_LOG_WEBHOOK_DELETE, =, 52),
        (DISCORD_AUDIT_LOG_EMOJI_CREATE, =, 60),
        (DISCORD_AUDIT_LOG_EMOJI_UPDATE, =, 61),
        (DISCORD_AUDIT_LOG_EMOJI_DELETE, =, 62),
        (DISCORD_AUDIT_LOG_MESSAGE_DELETE, =, 72),
        (DISCORD_AUDIT_LOG_MESSAGE_BULK_DELETE, =, 73),
        (DISCORD_AUDIT_LOG_MESSAGE_PIN, =, 74),
        (DISCORD_AUDIT_LOG_MESSAGE_UNPIN, =, 75),
        (DISCORD_AUDIT_LOG_INTEGRATION_CREATE, =, 80),
        (DISCORD_AUDIT_LOG_INTEGRATION_UPDATE, =, 81),
        (DISCORD_AUDIT_LOG_INTEGRATION_DELETE, =, 82),
        (DISCORD_AUDIT_LOG_STAGE_INSTANCE_CREATE, =, 83),
        (DISCORD_AUDIT_LOG_STAGE_INSTANCE_UPDATE, =, 84),
        (DISCORD_AUDIT_LOG_STAGE_INSTANCE_DELETE, =, 85),
        (DISCORD_AUDIT_LOG_STICKER_CREATE, =, 90),
        (DISCORD_AUDIT_LOG_STICKER_UPDATE, =, 91),
        (DISCORD_AUDIT_LOG_STICKER_DELETE, =, 92),
        (DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_CREATE, =, 100),
        (DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_UPDATE, =, 101),
        (DISCORD_AUDIT_LOG_GUILD_SCHEDULED_EVENT_DELETE, =, 102),
        (DISCORD_AUDIT_LOG_THREAD_CREATE, =, 110),
        (DISCORD_AUDIT_LOG_THREAD_UPDATE, =, 111),
        (DISCORD_AUDIT_LOG_THREAD_DELETE, =, 112),
        (DISCORD_AUDIT_LOG_APPLICATION_COMMAND_PERMISSION_UPDATE, =, 121),
        (DISCORD_AUDIT_LOG_AUTO_MODERATION_RULE_CREATE, =, 140),
        (DISCORD_AUDIT_LOG_AUTO_MODERATION_RULE_UPDATE, =, 141),
        (DISCORD_AUDIT_LOG_AUTO_MODERATION_RULE_DELETE, =, 142),
        (DISCORD_AUDIT_LOG_AUTO_MODERATION_BLOCK_MESSAGE, =, 143)
    )
)

PUBLIC(struct, discord_audit_log, 6, (
        (_, struct, discord_audit_log_entries, *, audit_log_entries, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_guild_scheduled_events, *, guild_scheduled_events, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_integrations, *, integrations, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_channels, *, threads, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_users, *, users, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_webhooks, *, webhooks, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_audit_log_entry, 7, (
        (_, _, u64snowflake, _, target_id, _, _, 0ul),
        (_, struct, discord_audit_log_changes, *, changes, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, enum, discord_audit_log_events, _, action_type, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_optional_audit_entry_infos, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, reason, _, _, 0ul)
    )
)

PRIVATE(struct, discord_audit_log_entries, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_audit_log_entry, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_optional_audit_entry_info, 8, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, char, *, count, _, _, 0ul),
        (_, _, char, *, delete_member_days, _, _, 0ul),
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, members_removed, _, _, 0ul),
        (_, _, u64snowflake, _, message_id, _, _, 0ul),
        (_, _, char, *, role_name, _, _, 0ul),
        (_, _, char, *, type, _, _, 0ul)
    )
)

PRIVATE(struct, discord_optional_audit_entry_infos, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_optional_audit_entry_info, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_audit_log_change, 3, (
        (_, _, json_char, *, new_value, _, _, 0ul),
        (_, _, json_char, *, old_value, _, _, 0ul),
        (_, _, char, *, key, _, _, 0ul)
    )
)

PRIVATE(struct, discord_audit_log_changes, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_audit_log_change, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_get_guild_audit_log, 4, (
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, int, _, action_type, _, _, 0ul),
        (_, _, u64snowflake, _, before, _, _, 0ul),
        (_, _, int, _, limit, _, _, CONCORD_OPTIONAL)
    )
)
