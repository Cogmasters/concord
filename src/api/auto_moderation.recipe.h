PUBLIC(enum, discord_auto_moderation_trigger_types, 4, (
        (DISCORD_AUTO_MODERATION_KEYWORD, =, 1),
        (DISCORD_AUTO_MODERATION_HARMFUL_LINK, =, 2),
        (DISCORD_AUTO_MODERATION_SPAM, =, 3),
        (DISCORD_AUTO_MODERATION_KEYWORD_PRESET, =, 4)
    )
)

PUBLIC(enum, discord_auto_moderation_keyword_preset_types, 3, (
        (DISCORD_AUTO_MODERATION_PROFANITY, =, 1),
        (DISCORD_AUTO_MODERATION_SEXUAL_CONTENT, =, 2),
        (DISCORD_AUTO_MODERATION_SLURS, =, 3)
    )
)

PUBLIC(enum, discord_auto_moderation_event_types, 1, (
        (DISCORD_AUTO_MODERATION_MESSAGE_SEND, =, 1)
    )
)

PUBLIC(enum, discord_auto_moderation_action_types, 3, (
        (DISCORD_AUTO_MODERATION_ACTION_BLOCK_MESSAGE, =, 1),
        (DISCORD_AUTO_MODERATION_ACTION_SEND_ALERT_MESSAGE, =, 2),
        (DISCORD_AUTO_MODERATION_ACTION_TIMEOUT, =, 3)
    )
)

PRIVATE(struct, discord_auto_moderation_trigger_metadata, 2, (
        (_, struct, strings, *, keyword_filter, _, _, 0ul),
        (_, struct, integers, *, presets, _, _, 0ul)
    )
)

PRIVATE(struct, discord_auto_moderation_action, 2, (
        (_, enum, discord_auto_moderation_action_types, _, type, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_auto_moderation_action_metadata, *, metadata, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_auto_moderation_actions, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_auto_moderation_action, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_auto_moderation_action_metadata, 2, (
        (_, _, u64snowflake, _, channel_id, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, duration_seconds, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_auto_moderation_rule, 11, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, u64snowflake, _, creator_id, _, _, 0ul),
        (_, enum, discord_auto_moderation_event_types, _, event_type, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_auto_moderation_trigger_types, _, trigger_type, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_auto_moderation_actions, *, actions, _, _, 0ul),
        (_, struct, discord_auto_moderation_trigger_metadata, *, trigger_metadata, _, _, 0ul),
        (_, _, bool, _, enabled, _, _, 0ul),
        (_, struct, snowflakes, *, exempt_roles, _, _, 0ul),
        (_, struct, snowflakes, *, exempt_channels, _, _, 0ul)
    )
)

PUBLIC(struct, discord_auto_moderation_rules, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_auto_moderation_rule, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_create_auto_moderation_rule, 9, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, enum, discord_auto_moderation_event_types, _, event_type, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_auto_moderation_trigger_types, _, trigger_type, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_auto_moderation_actions, *, actions, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_auto_moderation_trigger_metadata, *, trigger_metadata, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, enabled, _, _, 0ul),
        (_, struct, snowflakes, *, exempt_roles, _, _, CONCORD_OPTIONAL),
        (_, struct, snowflakes, *, exempt_channels, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_auto_moderation_rule, 8, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_auto_moderation_event_types, _, event_type, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_auto_moderation_trigger_metadata, *, trigger_metadata, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_auto_moderation_actions, *, actions, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, enabled, _, _, 0ul),
        (_, struct, snowflakes, *, exempt_roles, _, _, CONCORD_OPTIONAL),
        (_, struct, snowflakes, *, exempt_channels, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_delete_auto_moderation_rule, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)
