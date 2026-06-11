#ifdef REFLECTC_PRE_HOOKS
/*#!
#define DISCORD_GATEWAY_GUILDS (1 << 0)
#define DISCORD_GATEWAY_GUILD_MEMBERS (1 << 1)
#define DISCORD_GATEWAY_GUILD_BANS (1 << 2)
#define DISCORD_GATEWAY_GUILD_EMOJIS_AND_STICKERS (1 << 3)
#define DISCORD_GATEWAY_GUILD_INTEGRATIONS (1 << 4)
#define DISCORD_GATEWAY_GUILD_WEBHOOKS (1 << 5)
#define DISCORD_GATEWAY_GUILD_INVITES (1 << 6)
#define DISCORD_GATEWAY_GUILD_VOICE_STATES (1 << 7)
#define DISCORD_GATEWAY_GUILD_PRESENCES (1 << 8)
#define DISCORD_GATEWAY_GUILD_MESSAGES (1 << 9)
#define DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS (1 << 10)
#define DISCORD_GATEWAY_GUILD_MESSAGE_TYPING (1 << 11)
#define DISCORD_GATEWAY_DIRECT_MESSAGES (1 << 12)
#define DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS (1 << 13)
#define DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING (1 << 14)
#define DISCORD_GATEWAY_MESSAGE_CONTENT (1 << 15)
#define DISCORD_GATEWAY_GUILD_SCHEDULED_EVENTS (1 << 16)
#define DISCORD_GATEWAY_AUTO_MODERATION_CONFIGURATION (1 << 20)
#define DISCORD_GATEWAY_AUTO_MODERATION_EXECUTION (1 << 21)
#define DISCORD_ACTIVITY_INSTANCE (1 << 0)
#define DISCORD_ACTIVITY_JOIN (1 << 1)
#define DISCORD_ACTIVITY_SPECTATE (1 << 2)
#define DISCORD_ACTIVITY_JOIN_REQUEST (1 << 3)
#define DISCORD_ACTIVITY_SYNC (1 << 4)
#define DISCORD_ACTIVITY_PLAY (1 << 5)
#define DISCORD_ACTIVITY_PARTY_PRIVACY_FRIENDS (1 << 6)
#define DISCORD_ACTIVITY_PARTY_PRIVACY_VOICE_CHANNEL (1 << 7)
#define DISCORD_ACTIVITY_EMBEDDED (1 << 8)
*/
#endif

PUBLIC(enum, discord_gateway_close_opcodes, 15, (
        (DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR, =, 4000),
        (DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE, =, 4001),
        (DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR, =, 4002),
        (DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED, =, 4003),
        (DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED, =, 4004),
        (DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED, =, 4005),
        (DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE, =, 4007),
        (DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED, =, 4008),
        (DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT, =, 4009),
        (DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD, =, 4010),
        (DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED, =, 4011),
        (DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION, =, 4012),
        (DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS, =, 4013),
        (DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS, =, 4014),
        (DISCORD_GATEWAY_CLOSE_REASON_RECONNECT, =, 4900)
    )
)

PUBLIC(enum, discord_gateway_opcodes, 11, (
        (DISCORD_GATEWAY_DISPATCH, =, 0),
        (DISCORD_GATEWAY_HEARTBEAT, =, 1),
        (DISCORD_GATEWAY_IDENTIFY, =, 2),
        (DISCORD_GATEWAY_PRESENCE_UPDATE, =, 3),
        (DISCORD_GATEWAY_VOICE_STATE_UPDATE, =, 4),
        (DISCORD_GATEWAY_RESUME, =, 6),
        (DISCORD_GATEWAY_RECONNECT, =, 7),
        (DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS, =, 8),
        (DISCORD_GATEWAY_INVALID_SESSION, =, 9),
        (DISCORD_GATEWAY_HELLO, =, 10),
        (DISCORD_GATEWAY_HEARTBEAT_ACK, =, 11)
    )
)

PUBLIC(enum, discord_activity_types, 6, (
        (DISCORD_ACTIVITY_GAME, =, 0),
        (DISCORD_ACTIVITY_STREAMING, =, 1),
        (DISCORD_ACTIVITY_LISTENING, =, 2),
        (DISCORD_ACTIVITY_WATCHING, =, 3),
        (DISCORD_ACTIVITY_CUSTOM, =, 4),
        (DISCORD_ACTIVITY_COMPETING, =, 5)
    )
)

PRIVATE(struct, discord_activity, 15, (
        (_, _, char, *, name, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_activity_types, _, type, _, _, 0ul),
        (_, _, char, *, url, _, _, CONCORD_OPTIONAL),
        (_, _, u64unix_ms, _, created_at, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_activity_timestamps, *, timestamps, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, application_id, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, details, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, state, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_activity_emoji, *, emoji, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_activity_party, *, party, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_activity_assets, *, assets, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_activity_secrets, *, secrets, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, instance, _, _, 0ul),
        (_, _, u64bitmask, _, flags, _, _, 0ul),
        (_, struct, discord_activity_buttons, *, buttons, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_activities, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_activity, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_activity_timestamps, 2, (
        (_, _, u64unix_ms, _, start, _, _, 0ul),
        (_, _, u64unix_ms, _, end, _, _, 0ul)
    )
)

PRIVATE(struct, discord_activity_emoji, 3, (
        (_, _, char, *, name, _, _, 0ul),
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, bool, _, animated, _, _, 0ul)
    )
)

PRIVATE(struct, discord_activity_party, 2, (
        (_, _, char, *, id, _, _, 0ul),
        (_, struct, integers, *, size, _, _, 0ul)
    )
)

PRIVATE(struct, discord_activity_assets, 4, (
        (_, _, char, *, large_image, _, _, 0ul),
        (_, _, char, *, large_text, _, _, 0ul),
        (_, _, char, *, small_image, _, _, 0ul),
        (_, _, char, *, small_text, _, _, 0ul)
    )
)

PRIVATE(struct, discord_activity_secrets, 3, (
        (_, _, char, *, join, _, _, 0ul),
        (_, _, char, *, spectate, _, _, 0ul),
        (_, _, char, *, match, _, _, 0ul)
    )
)

PRIVATE(struct, discord_activity_button, 2, (
        (_, _, char, *, label, _, _, 0ul),
        (_, _, char, *, url, _, _, 0ul)
    )
)

PRIVATE(struct, discord_activity_buttons, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_activity_button, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_presence_update, 7, (
        (_, struct, discord_user, *, user, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, guild_id, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, status, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_client_status, *, client_status, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_activities, *, activities, _, _, CONCORD_OPTIONAL),
        (_, _, u64unix_ms, _, since, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, afk, _, _, 0ul)
    )
)

PRIVATE(struct, discord_client_status, 3, (
        (_, _, char, *, desktop, _, _, 0ul),
        (_, _, char, *, mobile, _, _, 0ul),
        (_, _, char, *, web, _, _, 0ul)
    )
)

PRIVATE(struct, discord_presence_updates, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_presence_update, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_identify, 7, (
        (_, _, char, *, token, _, _, 0ul),
        (_, struct, discord_identify_connection, *, properties, _, _, 0ul),
        (_, _, bool, _, compress, _, _, 0ul),
        (_, _, int, _, large_threshold, _, _, 0ul),
        (_, struct, integers, *, shard, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_presence_update, *, presence, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, intents, _, _, 0ul)
    )
)

PRIVATE(struct, discord_identify_connection, 3, (
        (_, _, char, *, os, _, _, 0ul),
        (_, _, char, *, browser, _, _, 0ul),
        (_, _, char, *, device, _, _, 0ul)
    )
)

PUBLIC(struct, discord_resume, 3, (
        (_, _, char, *, token, _, _, 0ul),
        (_, _, char, *, session_id, _, _, 0ul),
        (_, _, int, _, seq, _, _, 0ul)
    )
)

PUBLIC(struct, discord_request_guild_members, 6, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, char, *, query, _, _, 0ul),
        (_, _, int, _, limit, _, _, 0ul),
        (_, _, bool, _, presences, _, _, 0ul),
        (_, struct, snowflakes, *, user_ids, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, nonce, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_update_voice_state, 4, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, bool, _, self_mute, _, _, 0ul),
        (_, _, bool, _, self_deaf, _, _, 0ul)
    )
)

PUBLIC(struct, discord_ready, 6, (
        (_, _, int, _, v, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, 0ul),
        (_, struct, discord_guilds, *, guilds, _, _, 0ul),
        (_, _, char, *, session_id, _, _, 0ul),
        (_, struct, integers, *, shard, _, _, 0ul),
        (_, struct, discord_application, *, application, _, _, 0ul)
    )
)

PUBLIC(struct, discord_auto_moderation_action_execution, 10, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_auto_moderation_action, *, action, _, _, 0ul),
        (_, enum, discord_auto_moderation_trigger_types, _, rule_trigger_type, _, _, 0ul),
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, message_id, _, _, 0ul),
        (_, _, u64snowflake, _, alert_system_message_id, _, _, 0ul),
        (_, _, char, *, content, _, _, 0ul),
        (_, _, char, *, matched_keyword, _, _, 0ul),
        (_, _, char, *, matched_content, _, _, 0ul)
    )
)

PUBLIC(struct, discord_thread_list_sync, 4, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, snowflakes, *, channel_ids, _, _, 0ul),
        (_, struct, discord_channels, *, threads, _, _, 0ul),
        (_, struct, discord_thread_members, *, members, _, _, 0ul)
    )
)

PUBLIC(struct, discord_thread_members_update, 5, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, int, _, member_count, _, _, 0ul),
        (_, struct, discord_thread_members, *, added_members, _, _, 0ul),
        (_, struct, snowflakes, *, removed_member_ids, _, _, 0ul)
    )
)

PUBLIC(struct, discord_channel_pins_update, 3, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64unix_ms, _, last_pin_timestamp, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_ban_add, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_ban_remove, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_emojis_update, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_emojis, *, emojis, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_stickers_update, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_stickers, *, stickers, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_integrations_update, 1, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_member_remove, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_member_update, 11, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, snowflakes, *, roles, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, 0ul),
        (_, _, char, *, nick, _, _, 0ul),
        (_, _, char, *, avatar, _, _, 0ul),
        (_, _, u64unix_ms, _, joined_at, _, _, 0ul),
        (_, _, u64unix_ms, _, premium_since, _, _, 0ul),
        (_, _, bool, _, deaf, _, _, 0ul),
        (_, _, bool, _, mute, _, _, 0ul),
        (_, _, bool, _, pending, _, _, 0ul),
        (_, _, u64unix_ms, _, communication_disabled_until, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_members_chunk, 7, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_guild_members, *, members, _, _, 0ul),
        (_, _, int, _, chunk_index, _, _, 0ul),
        (_, _, int, _, chunk_count, _, _, 0ul),
        (_, struct, snowflakes, *, not_found, _, _, 0ul),
        (_, struct, discord_presence_updates, *, presences, _, _, 0ul),
        (_, _, char, *, nonce, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_role_create, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_role, *, role, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_role_update, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_role, *, role, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_role_delete, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, role_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_scheduled_event_user_add, 3, (
        (_, _, u64snowflake, _, guild_scheduled_event_id, _, _, 0ul),
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_scheduled_event_user_remove, 3, (
        (_, _, u64snowflake, _, guild_scheduled_event_id, _, _, 0ul),
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_integration_delete, 3, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, application_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_invite_create, 12, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, char, *, code, _, _, 0ul),
        (_, _, u64unix_ms, _, created_at, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_user, *, inviter, _, _, 0ul),
        (_, _, int, _, max_age, _, _, 0ul),
        (_, _, int, _, max_uses, _, _, 0ul),
        (_, enum, discord_invite_target_types, _, target_type, _, _, 0ul),
        (_, struct, discord_user, *, target_user, _, _, 0ul),
        (_, struct, discord_application, *, target_application, _, _, 0ul),
        (_, _, bool, _, temporary, _, _, 0ul),
        (_, _, int, _, uses, _, _, 0ul)
    )
)

PUBLIC(struct, discord_invite_delete, 3, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, char, *, code, _, _, 0ul)
    )
)

PUBLIC(struct, discord_message_delete, 3, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_message_delete_bulk, 3, (
        (_, struct, snowflakes, *, ids, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_message_reaction_add, 6, (
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, message_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_guild_member, *, member, _, _, 0ul),
        (_, struct, discord_emoji, *, emoji, _, _, 0ul)
    )
)

PUBLIC(struct, discord_message_reaction_remove, 5, (
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, message_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_emoji, *, emoji, _, _, 0ul)
    )
)

PUBLIC(struct, discord_message_reaction_remove_all, 3, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, message_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_message_reaction_remove_emoji, 4, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, message_id, _, _, 0ul),
        (_, struct, discord_emoji, *, emoji, _, _, 0ul)
    )
)

PUBLIC(struct, discord_typing_start, 5, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, u64unix_ms, _, timestamp, _, _, 0ul),
        (_, struct, discord_guild_member, *, member, _, _, 0ul)
    )
)

PUBLIC(struct, discord_voice_server_update, 3, (
        (_, _, char, *, token, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, char, *, endpoint, _, _, 0ul)
    )
)

PUBLIC(struct, discord_webhooks_update, 2, (
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_session_start_limit, 4, (
        (_, _, int, _, total, _, _, 0ul),
        (_, _, int, _, remaining, _, _, 0ul),
        (_, _, int, _, reset_after, _, _, 0ul),
        (_, _, int, _, max_concurrency, _, _, 0ul)
    )
)
