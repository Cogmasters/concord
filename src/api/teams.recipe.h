PUBLIC(enum, discord_membership_state, 2, (
        (DISCORD_MEMBERSHIP_INVITED, =, 1),
        (DISCORD_MEMBERSHIP_ACCEPTED, =, 2)
    )
)

PUBLIC(struct, discord_team, 5, (
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, struct, discord_team_members, *, members, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, u64snowflake, _, owner_user_id, _, _, 0ul)
    )
)

PRIVATE(struct, discord_team_member, 4, (
        (_, enum, discord_membership_state, _, membership_state, _, _, 0ul),
        (_, struct, bitmasks, *, permissions, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, team_id, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_team_members, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_team_member, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)
