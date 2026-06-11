#ifdef REFLECTC_PRE_HOOKS
/*#!
#define DISCORD_APPLICATION_GATEWAY_PRESENCE (1 << 12)
#define DISCORD_APPLICATION_GATEWAY_PRESENCE_LIMITED (1 << 13)
#define DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS (1 << 14)
#define DISCORD_APPLICATION_GATEWAY_GUILD_MEMBERS_LIMITED (1 << 15)
#define DISCORD_APPLICATION_VERIFICATION_PENDING_GUILD_LIMIT (1 << 16)
#define DISCORD_APPLICATION_EMBEDDED (1 << 17)
#define DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT (1 << 18)
#define DISCORD_APPLICATION_GATEWAY_MESSAGE_CONTENT_LIMITED (1 << 19)
*/
#endif

PUBLIC(struct, discord_application, 18, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, strings, *, rpc_origins, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, bot_public, _, _, 0ul),
        (_, _, bool, _, bot_require_code_grant, _, _, 0ul),
        (_, _, char, *, terms_of_service_url, _, _, 0ul),
        (_, _, char, *, privacy_policy_url, _, _, 0ul),
        (_, struct, discord_user, *, owner, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, summary, _, _, 0ul),
        (_, _, char, *, verify_key, _, _, 0ul),
        (_, struct, discord_team, *, team, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, primary_sku_id, _, _, 0ul),
        (_, _, char, *, slug, _, _, 0ul),
        (_, _, char, *, cover_image, _, _, 0ul),
        (_, _, u64bitmask, _, flags, _, _, 0ul)
    )
)

PUBLIC(struct, discord_install_params, 2, (
        (_, struct, strings, *, scopes, _, _, 0ul),
        (_, _, u64bitmask, _, permissions, _, _, 0ul)
    )
)
