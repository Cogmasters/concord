#ifdef REFLECTC_PRE_HOOKS
/*#!
#define DISCORD_SYSTEM_SUPPRESS_JOIN_NOTIFICATIONS (1 << 0)
#define DISCORD_SYSTEM_SUPPRESS_PREMIUM_NOTIFICATIONS (1 << 1)
#define DISCORD_SYSTEM_SUPPRESS_GUILD_REMINDER_NOTIFICATIONS (1 << 2)
#define DISCORD_SYSTEM_SUPPRESS_JOIN_NOTIFICATION_REPLIES (1 << 3)
*/
#endif

PUBLIC(enum, discord_message_notification_level, 2, (
        (DISCORD_MESSAGE_NOTIFICATION_ALL_MESSAGES, =, 0),
        (DISCORD_MESSAGE_NOTIFICATION_ONLY_MESSAGES, =, 1)
    )
)

PUBLIC(enum, discord_explicit_content_filter_level, 3, (
        (DISCORD_EXPLICIT_CONTENT_DISABLED, =, 0),
        (DISCORD_EXPLICIT_CONTENT_MEMBERS_WITHOUT_ROLES, =, 1),
        (DISCORD_MESSAGE_NOTIFICATION_ALL_MEMBERS, =, 2)
    )
)

PUBLIC(enum, discord_mfa_level, 2, (
        (DISCORD_MFA_NONE, =, 0),
        (DISCORD_MFA_ELEVATED, =, 1)
    )
)

PUBLIC(enum, discord_verification_level, 5, (
        (DISCORD_VERIFICATION_NONE, =, 0),
        (DISCORD_VERIFICATION_LOW, =, 1),
        (DISCORD_VERIFICATION_MEDIUM, =, 2),
        (DISCORD_VERIFICATION_HIGH, =, 3),
        (DISCORD_VERIFICATION_VERY_HIGH, =, 4)
    )
)

PUBLIC(enum, discord_guild_nsfw_level, 4, (
        (DISCORD_GUILD_NSFW_DEFAULT, =, 0),
        (DISCORD_GUILD_NSFW_EXPLICIT, =, 1),
        (DISCORD_GUILD_NSFW_SAFE, =, 2),
        (DISCORD_GUILD_NSFW_AGE_RESTRICTED, =, 3)
    )
)

PUBLIC(enum, discord_premium_tier, 4, (
        (DISCORD_PREMIUM_TIER_NONE, =, 0),
        (DISCORD_PREMIUM_TIER_1, =, 1),
        (DISCORD_PREMIUM_TIER_2, =, 2),
        (DISCORD_PREMIUM_TIER_3, =, 3)
    )
)

PUBLIC(enum, discord_integration_expire_behaviors, 2, (
        (DISCORD_INTEGRATION_REMOVE_ROLE, =, 0),
        (DISCORD_INTEGRATION_KICK, =, 1)
    )
)

PUBLIC(struct, discord_guild, 51, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, char, *, icon_hash, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, splash, _, _, 0ul),
        (_, _, char, *, discovery_splash, _, _, 0ul),
        (_, _, bool, _, owner, _, _, 0ul),
        (_, _, u64snowflake, _, owner_id, _, _, 0ul),
        (_, _, u64bitmask, _, permissions, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, afk_channel_id, _, _, 0ul),
        (_, _, int, _, afk_timeout, _, _, 0ul),
        (_, _, bool, _, widget_enabled, _, _, 0ul),
        (_, _, u64snowflake, _, widget_channel_id, _, _, 0ul),
        (_, enum, discord_verification_level, _, verification_level, _, _, 0ul),
        (_, enum, discord_message_notification_level, _, default_message_notifications, _, _, 0ul),
        (_, enum, discord_explicit_content_filter_level, _, explicit_content_filter, _, _, 0ul),
        (_, struct, discord_roles, *, roles, _, _, 0ul),
        (_, struct, discord_emojis, *, emojis, _, _, 0ul),
        (_, struct, strings, *, features, _, _, 0ul),
        (_, enum, discord_mfa_level, _, mfa_level, _, _, 0ul),
        (_, _, u64snowflake, _, application_id, _, _, 0ul),
        (_, _, u64snowflake, _, system_channel_id, _, _, 0ul),
        (_, _, u64bitmask, _, system_channel_flags, _, _, 0ul),
        (_, _, u64snowflake, _, rules_channel_id, _, _, 0ul),
        (_, _, u64unix_ms, _, joined_at, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, large, _, _, 0ul),
        (_, _, bool, _, unavailable, _, _, 0ul),
        (_, _, int, _, member_count, _, _, 0ul),
        (_, struct, discord_voice_states, *, voice_states, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_guild_members, *, members, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_channels, *, channels, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_channels, *, threads, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_presence_updates, *, presences, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, max_presences, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, max_members, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, vanity_url_code, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, char, *, banner, _, _, 0ul),
        (_, enum, discord_premium_tier, _, premium_tier, _, _, 0ul),
        (_, _, int, _, premium_subscription_count, _, _, 0ul),
        (_, _, char, *, preferred_locale, _, _, 0ul),
        (_, _, u64snowflake, _, public_updates_channel_id, _, _, 0ul),
        (_, _, int, _, max_video_channel_users, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, approximate_member_count, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, approximate_presence_count, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_welcome_screen, *, welcome_screen, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_guild_nsfw_level, _, nsfw_level, _, _, 0ul),
        (_, struct, discord_stage_instances, *, stage_instances, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_stickers, *, stickers, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_guild_scheduled_events, *, guild_scheduled_events, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, premium_progress_bar_enabled, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guilds, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_guild, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_preview, 11, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, char, *, splash, _, _, 0ul),
        (_, _, char, *, discovery_splash, _, _, 0ul),
        (_, struct, discord_emojis, *, emojis, _, _, 0ul),
        (_, struct, strings, *, features, _, _, 0ul),
        (_, _, int, _, approximate_member_count, _, _, 0ul),
        (_, _, int, _, approximate_presence_count, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, discord_stickers, *, stickers, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_widget_settings, 3, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, bool, _, enabled, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_widget, 6, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, instant_invite, _, _, 0ul),
        (_, struct, discord_channels, *, channels, _, _, 0ul),
        (_, struct, discord_users, *, members, _, _, 0ul),
        (_, _, int, _, presence_count, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_member, 12, (
        (_, struct, discord_user, *, user, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, nick, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, avatar, _, _, CONCORD_OPTIONAL),
        (_, struct, snowflakes, *, roles, _, _, 0ul),
        (_, _, u64unix_ms, _, joined_at, _, _, 0ul),
        (_, _, u64unix_ms, _, premium_since, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, deaf, _, _, 0ul),
        (_, _, bool, _, muted, mute, _, 0ul),
        (_, _, bool, _, pending, _, _, 0ul),
        (_, _, u64bitmask, _, permissions, _, _, CONCORD_OPTIONAL),
        (_, _, u64unix_ms, _, communication_disabled_until, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_guild_members, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_guild_member, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_integration, 16, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, type, _, _, 0ul),
        (_, _, bool, _, enabled, _, _, 0ul),
        (_, _, bool, _, syncing, _, _, 0ul),
        (_, _, u64snowflake, _, role_id, _, _, 0ul),
        (_, _, bool, _, enable_emoticons, _, _, 0ul),
        (_, enum, discord_integration_expire_behaviors, _, expire_behavior, _, _, 0ul),
        (_, _, int, _, expire_grace_period, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, 0ul),
        (_, struct, discord_integration_account, *, account, _, _, 0ul),
        (_, _, u64unix_ms, _, synced_at, _, _, 0ul),
        (_, _, int, _, subscriber_count, _, _, 0ul),
        (_, _, bool, _, revoked, _, _, 0ul),
        (_, struct, discord_integration_application, *, application, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_integrations, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_integration, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_integration_account, 2, (
        (_, _, char, *, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul)
    )
)

PRIVATE(struct, discord_integration_application, 6, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, char, *, summary, _, _, 0ul),
        (_, struct, discord_user, *, bot, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_ban, 2, (
        (_, _, char, *, reason, _, _, 0ul),
        (_, struct, discord_user, *, user, _, _, 0ul)
    )
)

PUBLIC(struct, discord_bans, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_ban, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_welcome_screen, 2, (
        (_, _, char, *, description, _, _, 0ul),
        (_, struct, discord_welcome_screen_channels, *, welcome_channels, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_welcome_screen_channel, 4, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, u64snowflake, _, emoji_id, _, _, 0ul),
        (_, _, char, *, emoji_name, _, _, 0ul)
    )
)

PRIVATE(struct, discord_welcome_screen_channels, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_welcome_screen_channel, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_prune_count, 1, (
        (_, _, int, _, pruned, _, _, 0ul)
    )
)

PUBLIC(struct, discord_create_guild, 13, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, region, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, icon, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_verification_level, _, verification_level, _, _, 0ul),
        (_, enum, discord_message_notification_level, _, default_message_notifications, _, _, 0ul),
        (_, enum, discord_explicit_content_filter_level, _, explicit_content_filter, _, _, 0ul),
        (_, struct, discord_roles, *, roles, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_channels, *, channels, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, afk_channel_id, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, afk_timeout, _, _, 0ul),
        (_, _, u64snowflake, _, system_channel_id, _, _, 0ul),
        (_, _, u64bitmask, _, system_channel_flags, _, _, 0ul)
    )
)

PUBLIC(struct, discord_modify_guild, 20, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, enum, discord_verification_level, _, verification_level, _, _, 0ul),
        (_, enum, discord_message_notification_level, _, default_message_notifications, _, _, 0ul),
        (_, enum, discord_explicit_content_filter_level, _, explicit_content_filter, _, _, 0ul),
        (_, _, u64snowflake, _, afk_channel_id, _, _, 0ul),
        (_, _, int, _, afk_timeout, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, u64snowflake, _, owner_id, _, _, 0ul),
        (_, _, char, *, splash, _, _, 0ul),
        (_, _, char, *, discovery_splash, _, _, 0ul),
        (_, _, char, *, banner, _, _, 0ul),
        (_, _, u64snowflake, _, system_channel_id, _, _, 0ul),
        (_, _, u64bitmask, _, system_channel_flags, _, _, 0ul),
        (_, _, u64snowflake, _, rules_channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, public_updates_channel_id, _, _, 0ul),
        (_, _, char, *, preferred_locale, _, _, 0ul),
        (_, struct, strings, *, features, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, bool, _, premium_progress_bar_enabled, _, _, 0ul)
    )
)

PUBLIC(struct, discord_create_guild_channel, 11, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, enum, discord_channel_types, _, type, _, _, 0ul),
        (_, _, char, *, topic, _, _, 0ul),
        (_, _, int, _, bitrate, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, user_limit, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, rate_limit_per_user, _, _, 0ul),
        (_, _, int, _, position, _, _, 0ul),
        (_, struct, discord_overwrites, *, permission_overwrites, _, _, 0ul),
        (_, _, u64snowflake, _, parent_id, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, nsfw, _, _, 0ul)
    )
)

PRIVATE(struct, discord_modify_guild_channel_position, 4, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, int, _, position, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, lock_category, _, _, 0ul),
        (_, _, u64snowflake, _, parent_id, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_guild_channel_positions, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_modify_guild_channel_position, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_list_active_guild_threads, 2, (
        (_, struct, discord_channels, *, threads, _, _, 0ul),
        (_, struct, discord_thread_members, *, members, _, _, 0ul)
    )
)

PRIVATE(struct, discord_list_guild_members, 2, (
        (_, _, int, _, limit, _, _, 0ul),
        (_, _, u64snowflake, _, after, _, _, 0ul)
    )
)

PRIVATE(struct, discord_search_guild_members, 2, (
        (_, _, char, *, query, _, _, 0ul),
        (_, _, int, _, limit, _, _, 0ul)
    )
)

PUBLIC(struct, discord_add_guild_member, 5, (
        (_, _, char, *, access_token, _, _, 0ul),
        (_, _, char, *, nick, _, _, 0ul),
        (_, struct, snowflakes, *, roles, _, _, 0ul),
        (_, _, bool, _, mute, _, _, 0ul),
        (_, _, bool, _, deaf, _, _, 0ul)
    )
)

PUBLIC(struct, discord_modify_guild_member, 7, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, nick, _, _, CONCORD_OPTIONAL),
        (_, struct, snowflakes, *, roles, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, mute, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, deaf, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, channel_id, _, _, CONCORD_OPTIONAL),
        (_, _, u64unix_ms, _, communication_disabled_until, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_current_member, 2, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, nick, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_current_user_nick, 2, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, nick, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_add_guild_member_role, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PRIVATE(struct, discord_remove_guild_member_role, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PRIVATE(struct, discord_remove_guild_member, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PUBLIC(struct, discord_create_guild_ban, 2, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, int, _, delete_message_days, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_remove_guild_ban, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PUBLIC(struct, discord_create_guild_role, 8, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, u64bitmask, _, permissions, _, _, 0ul),
        (_, _, int, _, color, _, _, 0ul),
        (_, _, bool, _, hoist, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, char, *, unicode_emoji, _, _, 0ul),
        (_, _, bool, _, mentionable, _, _, 0ul)
    )
)

PRIVATE(struct, discord_modify_guild_role_position, 2, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, int, _, position, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_guild_role_positions, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_modify_guild_role_position, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_modify_guild_role, 8, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, u64bitmask, _, permissions, _, _, 0ul),
        (_, _, int, _, color, _, _, 0ul),
        (_, _, bool, _, hoist, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, char, *, unicode_emoji, _, _, 0ul),
        (_, _, bool, _, mentionable, _, _, 0ul)
    )
)

PRIVATE(struct, discord_delete_guild_role, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PRIVATE(struct, discord_get_guild_prune_count, 2, (
        (_, _, int, _, days, _, _, CONCORD_OPTIONAL),
        (_, struct, snowflakes, *, include_roles, _, _, 0ul)
    )
)

PUBLIC(struct, discord_begin_guild_prune, 4, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, int, _, days, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, compute_prune_count, _, _, 0ul),
        (_, struct, snowflakes, *, include_roles, _, _, 0ul)
    )
)

PRIVATE(struct, discord_delete_guild_integrations, 3, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, int, _, days, _, _, CONCORD_OPTIONAL),
        (_, struct, snowflakes, *, include_roles, _, _, 0ul)
    )
)

PRIVATE(struct, discord_get_guild_widget_image, 1, (
        (_, _, char, *, style, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_guild_welcome_screen, 4, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, bool, _, enabled, _, _, 0ul),
        (_, struct, discord_welcome_screen_channels, *, welcome_channels, _, _, 0ul),
        (_, _, char, *, description, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_current_user_voice_state, 3, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, bool, _, suppress, _, _, 0ul),
        (_, _, u64unix_ms, _, request_to_speak_timestamp, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_modify_user_voice_state, 2, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, bool, _, suppress, _, _, 0ul)
    )
)
