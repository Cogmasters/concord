#ifdef REFLECTC_PRE_HOOKS
/*#!
#define DISCORD_USER_NONE (0)
#define DISCORD_USER_STAFF (1 << 0)
#define DISCORD_USER_PARTNER (1 << 1)
#define DISCORD_USER_HYPESQUAD (1 << 2)
#define DISCORD_USER_BUG_HUNTER_LEVEL_1 (1 << 3)
#define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_1 (1 << 6)
#define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_2 (1 << 7)
#define DISCORD_USER_HYPESQUAD_ONLINE_HOUSE_3 (1 << 8)
#define DISCORD_USER_PREMIUM_EARLY_SUPPORTER (1 << 9)
#define DISCORD_USER_TEAM_PSEUDO_USER (1 << 10)
#define DISCORD_USER_BUG_HUNTER_LEVEL_2 (1 << 14)
#define DISCORD_USER_VERIFIED_BOT (1 << 16)
#define DISCORD_USER_VERIFIED_DEVELOPER (1 << 17)
#define DISCORD_USER_CERTIFIED_MODERATOR (1 << 18)
#define DISCORD_USER_BOT_HTTP_INTERACTIONS (1 << 19)
*/
#endif

PUBLIC(enum, discord_premium_types, 3, (
        (DISCORD_PREMIUM_NONE, =, 0),
        (DISCORD_PREMIUM_NITRO_CLASSIC, =, 1),
        (DISCORD_PREMIUM_NITRO, =, 2)
    )
)

PUBLIC(enum, discord_visibility_types, 2, (
        (DISCORD_VISIBILITY_NONE, =, 0),
        (DISCORD_VISIBILITY_EVERYONE, =, 1)
    )
)

PUBLIC(struct, discord_user, 15, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, username, _, _, 0ul),
        (_, _, char, *, discriminator, _, _, 0ul),
        (_, _, char, *, avatar, _, _, 0ul),
        (_, _, bool, _, bot, _, _, 0ul),
        (_, _, bool, _, System, system, _, 0ul),
        (_, _, bool, _, mfa_enabled, _, _, 0ul),
        (_, _, char, *, banner, _, _, 0ul),
        (_, _, int, _, accent_color, _, _, 0ul),
        (_, _, char, *, locale, _, _, 0ul),
        (_, _, bool, _, verified, _, _, 0ul),
        (_, _, char, *, email, _, _, 0ul),
        (_, _, u64bitmask, _, flags, _, _, 0ul),
        (_, enum, discord_premium_types, _, premium_type, _, _, 0ul),
        (_, _, u64bitmask, _, public_flags, _, _, 0ul)
    )
)

PUBLIC(struct, discord_users, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_user, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_connection, 9, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, type, _, _, 0ul),
        (_, _, bool, _, revoked, _, _, 0ul),
        (_, struct, discord_integrations, *, integrations, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, verified, _, _, 0ul),
        (_, _, bool, _, friend_sync, _, _, 0ul),
        (_, _, bool, _, show_activity, _, _, 0ul),
        (_, enum, discord_visibility_types, _, visibility, _, _, 0ul)
    )
)

PUBLIC(struct, discord_connections, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_connection, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_modify_current_user, 2, (
        (_, _, char, *, username, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, avatar, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_get_current_user_guilds, 3, (
        (_, _, u64snowflake, _, before, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, after, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, limit, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_create_dm, 1, (
        (_, _, u64snowflake, _, recipient_id, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_create_group_dm, 2, (
        (_, struct, snowflakes, *, access_tokens, _, _, CONCORD_OPTIONAL),
        (_, struct, strings, *, nicks, _, _, CONCORD_OPTIONAL)
    )
)
