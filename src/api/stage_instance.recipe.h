PUBLIC(enum, discord_privacy_level, 2, (
        (DISCORD_PRIVACY_PUBLIC, =, 1),
        (DISCORD_PRIVACY_GUILD_ONLY, =, 2)
    )
)

PUBLIC(struct, discord_stage_instance, 6, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, char, *, topic, _, _, 0ul),
        (_, enum, discord_privacy_level, _, privacy_level, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, discoverable_disabled, _, _, 0ul)
    )
)

PRIVATE(struct, discord_stage_instances, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_stage_instance, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_create_stage_instance, 4, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, char, *, topic, _, _, 0ul),
        (_, enum, discord_privacy_level, _, privacy_level, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_stage_instance, 3, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, topic, _, _, 0ul),
        (_, enum, discord_privacy_level, _, privacy_level, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_delete_stage_instance, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)
