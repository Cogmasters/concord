PUBLIC(enum, discord_application_command_types, 3, (
        (DISCORD_APPLICATION_CHAT_INPUT, =, 1),
        (DISCORD_APPLICATION_USER, =, 2),
        (DISCORD_APPLICATION_MESSAGE, =, 3)
    )
)

PUBLIC(enum, discord_application_command_option_types, 11, (
        (DISCORD_APPLICATION_OPTION_SUB_COMMAND, =, 1),
        (DISCORD_APPLICATION_OPTION_SUB_COMMAND_GROUP, =, 2),
        (DISCORD_APPLICATION_OPTION_STRING, =, 3),
        (DISCORD_APPLICATION_OPTION_INTEGER, =, 4),
        (DISCORD_APPLICATION_OPTION_BOOLEAN, =, 5),
        (DISCORD_APPLICATION_OPTION_USER, =, 6),
        (DISCORD_APPLICATION_OPTION_CHANNEL, =, 7),
        (DISCORD_APPLICATION_OPTION_ROLE, =, 8),
        (DISCORD_APPLICATION_OPTION_MENTIONABLE, =, 9),
        (DISCORD_APPLICATION_OPTION_NUMBER, =, 10),
        (DISCORD_APPLICATION_OPTION_ATTACHMENT, =, 11)
    )
)

PUBLIC(enum, discord_application_command_permission_types, 3, (
        (DISCORD_APPLICATION_PERMISSION_ROLE, =, 1),
        (DISCORD_APPLICATION_PERMISSION_USER, =, 2),
        (DISCORD_APPLICATION_PERMISSION_CHANNEL, =, 3)
    )
)

PUBLIC(struct, discord_application_command, 11, (
        (_, _, u64snowflake, _, id, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_application_command_types, _, type, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, application_id, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, guild_id, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, name, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, description, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_application_command_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, default_member_permissions, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, dm_permission, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, default_permission, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, version, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_application_commands, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_application_command, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_application_command_option, 10, (
        (_, enum, discord_application_command_option_types, _, type, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, bool, _, required, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_application_command_option_choices, *, choices, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_application_command_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, struct, integers, *, channel_types, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, min_value, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, max_value, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, autocomplete, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_application_command_options, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_application_command_option, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_application_command_option_choice, 2, (
        (_, _, char, *, name, _, _, 0ul),
        (_, _, json_char, *, value, _, _, 0ul)
    )
)

PRIVATE(struct, discord_application_command_option_choices, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_application_command_option_choice, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_application_command_interaction_data_option, 5, (
        (_, _, char, *, name, _, _, 0ul),
        (_, enum, discord_application_command_option_types, _, type, _, _, 0ul),
        (_, _, json_char, *, value, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_application_command_interaction_data_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, focused, _, _, 0ul)
    )
)

PRIVATE(struct, discord_application_command_interaction_data_options, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_application_command_interaction_data_option, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_guild_application_command_permission, 4, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, application_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_application_command_permissions, *, permissions, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_application_command_permissions, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_guild_application_command_permission, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_application_command_permission, 3, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, enum, discord_application_command_permission_types, _, type, _, _, 0ul),
        (_, _, bool, _, permission, _, _, 0ul)
    )
)

PUBLIC(struct, discord_application_command_permissions, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_application_command_permission, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_create_global_application_command, 7, (
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, discord_application_command_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, default_member_permissions, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, dm_permission, _, _, 0ul),
        (_, _, bool, _, default_permission, _, _, 0ul),
        (_, enum, discord_application_command_types, _, type, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_edit_global_application_command, 6, (
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, discord_application_command_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, default_member_permissions, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, dm_permission, _, _, 0ul),
        (_, _, bool, _, default_permission, _, _, 0ul)
    )
)

PUBLIC(struct, discord_create_guild_application_command, 7, (
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, discord_application_command_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, default_member_permissions, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, dm_permission, _, _, 0ul),
        (_, _, bool, _, default_permission, _, _, 0ul),
        (_, enum, discord_application_command_types, _, type, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_edit_guild_application_command, 5, (
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, discord_application_command_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, default_member_permissions, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, default_permission, _, _, 0ul)
    )
)

PUBLIC(struct, discord_bulk_overwrite_guild_application_command, 9, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, struct, strings, *, name_localizations, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, strings, *, description_localizations, _, _, 0ul),
        (_, struct, discord_application_command_options, *, options, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, default_member_permissions, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, dm_permission, _, _, 0ul),
        (_, enum, discord_application_command_types, _, type, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_bulk_overwrite_guild_application_commands, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_bulk_overwrite_guild_application_command, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)
