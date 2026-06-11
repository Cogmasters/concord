PUBLIC(enum, discord_invite_target_types, 2, (
        (DISCORD_INVITE_TARGET_STREAM, =, 1),
        (DISCORD_INVITE_TARGET_EMBEDDED_APPLICATION, =, 2)
    )
)

PUBLIC(struct, discord_invite, 12, (
        (_, _, char, *, code, _, _, 0ul),
        (_, struct, discord_guild, *, guild, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_channel, *, channel, _, _, 0ul),
        (_, struct, discord_user, *, inviter, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_invite_target_types, _, target_type, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_user, *, target_user, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_application, *, target_application, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, approximate_presence_count, _, _, 0ul),
        (_, _, int, _, approximate_member_count, _, _, 0ul),
        (_, _, u64unix_ms, _, expires_at, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_invite_stage_instance, *, stage_instance, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_guild_scheduled_event, *, guild_scheduled_event, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_invites, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_invite, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_invite_metadata, 5, (
        (_, _, int, _, uses, _, _, 0ul),
        (_, _, int, _, max_uses, _, _, 0ul),
        (_, _, int, _, max_age, _, _, 0ul),
        (_, _, bool, _, temporary, _, _, 0ul),
        (_, _, u64unix_ms, _, created_at, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_invite_stage_instance, 4, (
        (_, struct, discord_guild_members, *, members, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, participant_count, _, _, 0ul),
        (_, _, int, _, speaker_count, _, _, 0ul),
        (_, _, char, *, topic, _, _, 0ul)
    )
)

PUBLIC(struct, discord_get_invite, 3, (
        (_, _, bool, _, with_counts, _, _, 0ul),
        (_, _, bool, _, with_expiration, _, _, 0ul),
        (_, _, u64snowflake, _, guild_scheduled_event_id, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_delete_invite, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)
