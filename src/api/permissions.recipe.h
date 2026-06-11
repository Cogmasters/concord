#ifdef REFLECTC_PRE_HOOKS
/*#!
#define DISCORD_PERM_CREATE_INSTANT_INVITE (1 << 0)
#define DISCORD_PERM_KICK_MEMBERS (1 << 1)
#define DISCORD_PERM_BAN_MEMBERS (1 << 2)
#define DISCORD_PERM_ADMINISTRATOR (1 << 3)
#define DISCORD_PERM_MANAGE_CHANNELS (1 << 4)
#define DISCORD_PERM_MANAGE_GUILD (1 << 5)
#define DISCORD_PERM_ADD_REACTIONS (1 << 6)
#define DISCORD_PERM_VIEW_AUDIT_LOG (1 << 7)
#define DISCORD_PERM_PRIORITY_SPEAKER (1 << 8)
#define DISCORD_PERM_STREAM (1 << 9)
#define DISCORD_PERM_VIEW_CHANNEL (1 << 10)
#define DISCORD_PERM_SEND_MESSAGES (1 << 11)
#define DISCORD_PERM_SEND_TTS_MESSAGES (1 << 12)
#define DISCORD_PERM_MANAGE_MESSAGES (1 << 13)
#define DISCORD_PERM_EMBED_LINKS (1 << 14)
#define DISCORD_PERM_ATTACH_FILES (1 << 15)
#define DISCORD_PERM_READ_MESSAGE_HISTORY (1 << 16)
#define DISCORD_PERM_MENTION_EVERYONE (1 << 17)
#define DISCORD_PERM_USE_EXTERNAL_EMOJIS (1 << 18)
#define DISCORD_PERM_VIEW_GUILD_INSIGHTS (1 << 19)
#define DISCORD_PERM_CONNECT (1 << 20)
#define DISCORD_PERM_SPEAK (1 << 21)
#define DISCORD_PERM_MUTE_MEMBERS (1 << 22)
#define DISCORD_PERM_DEAFEN_MEMBERS (1 << 23)
#define DISCORD_PERM_MOVE_MEMBERS (1 << 24)
#define DISCORD_PERM_USE_VAD (1 << 25)
#define DISCORD_PERM_CHANGE_NICKNAME (1 << 26)
#define DISCORD_PERM_MANAGE_NICKNAMES (1 << 27)
#define DISCORD_PERM_MANAGE_ROLES (1 << 28)
#define DISCORD_PERM_MANAGE_WEBHOOKS (1 << 29)
#define DISCORD_PERM_MANAGE_EMOJIS_AND_STICKERS (1 << 30)
#define DISCORD_PERM_USE_APPLICATION_COMMANDS (1 << 31)
#define DISCORD_PERM_REQUEST_TO_SPEAK (1 << 32)
#define DISCORD_PERM_MANAGE_EVENTS (1 << 33)
#define DISCORD_PERM_MANAGE_THREADS (1 << 34)
#define DISCORD_PERM_CREATE_PUBLIC_THREADS (1 << 35)
#define DISCORD_PERM_CREATE_PRIVATE_THREADS (1 << 36)
#define DISCORD_PERM_USE_EXTERNAL_STICKERS (1 << 37)
#define DISCORD_PERM_SEND_MESSAGES_IN_THREADS (1 << 38)
#define DISCORD_PERM_START_EMBEDDED_ACTIVITIES (1 << 39)
#define DISCORD_PERM_MODERATE_MEMBERS (1 << 40)
*/
#endif

PUBLIC(struct, discord_role, 11, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, int, _, color, _, _, 0ul),
        (_, _, bool, _, hoist, _, _, 0ul),
        (_, _, char, *, icon, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, unicode_emoji, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, position, _, _, 0ul),
        (_, _, u64bitmask, _, permissions, _, _, 0ul),
        (_, _, bool, _, managed, _, _, 0ul),
        (_, _, bool, _, mentionable, _, _, 0ul),
        (_, struct, discord_role_tag, *, tags, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_roles, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_role, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_role_tag, 3, (
        (_, _, u64snowflake, _, bot_id, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, integration_id, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, premium_subscribe, premium_subscriber, _, 0ul)
    )
)
