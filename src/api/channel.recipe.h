#ifdef REFLECTC_PRE_HOOKS
/*#!
#define DISCORD_CHANNEL_PINNED (1 << 1)
#define DISCORD_CHANNEL_REQUIRE_TAG (1 << 4)
#define DISCORD_CHANNEL_HIDE_MEDIA_DOWNLOAD_OPTIONS (1 << 5)
#define DISCORD_MESSAGE_CROSSPOSTED (1 << 0)
#define DISCORD_MESSAGE_IS_CROSSPOST (1 << 1)
#define DISCORD_MESSAGE_SUPPRESS_EMBEDS (1 << 2)
#define DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED (1 << 3)
#define DISCORD_MESSAGE_URGENT (1 << 4)
#define DISCORD_MESSAGE_HAS_THREAD (1 << 5)
#define DISCORD_MESSAGE_EPHEMERAL (1 << 6)
#define DISCORD_MESSAGE_LOADING (1 << 7)
#define DISCORD_MESSAGE_FAILED_TO_MENTION_SOME_ROLES_IN_THREAD (1 << 8)
#define DISCORD_MESSAGE_SUPPRESS_NOTIFICATIONS (1 << 12)
#define DISCORD_MESSAGE_IS_VOICE_MESSAGE (1 << 13)
#define DISCORD_MESSAGE_HAS_COMPONENTS_V2 (1 << 15)
#define DISCORD_ATTACHMENT_IS_REMIX (1 << 2)
*/
#endif

PUBLIC(enum, discord_channel_types, 16, (
        (DISCORD_CHANNEL_GUILD_TEXT, =, 0),
        (DISCORD_CHANNEL_DM, =, 1),
        (DISCORD_CHANNEL_GUILD_VOICE, =, 2),
        (DISCORD_CHANNEL_GROUP_DM, =, 3),
        (DISCORD_CHANNEL_GUILD_CATEGORY, =, 4),
        (DISCORD_CHANNEL_GUILD_ANNOUNCEMENT, =, 5),
        (DISCORD_CHANNEL_GUILD_NEWS, =, DISCORD_CHANNEL_GUILD_ANNOUNCEMENT),
        (DISCORD_CHANNEL_GUILD_STORE, =, 6),
        (DISCORD_CHANNEL_ANNOUNCEMENT_THREAD, =, 10),
        (DISCORD_CHANNEL_GUILD_NEWS_THREAD, =, DISCORD_CHANNEL_ANNOUNCEMENT_THREAD),
        (DISCORD_CHANNEL_GUILD_PUBLIC_THREAD, =, 11),
        (DISCORD_CHANNEL_GUILD_PRIVATE_THREAD, =, 12),
        (DISCORD_CHANNEL_GUILD_STAGE_VOICE, =, 13),
        (DISCORD_CHANNEL_GUILD_DIRECTORY, =, 14),
        (DISCORD_CHANNEL_GUILD_FORUM, =, 15),
        (DISCORD_CHANNEL_GUILD_MEDIA, =, 16)
    )
)

PUBLIC(enum, discord_video_quality_modes, 2, (
        (DISCORD_VIDEO_QUALITY_AUTO, =, 1),
        (DISCORD_VIDEO_QUALITY_FULL, =, 2)
    )
)

PUBLIC(enum, discord_sort_order_types, 2, (
        (DISCORD_SORT_ORDER_LATEST_ACTIVITY, =, 0),
        (DISCORD_SORT_ORDER_CREATION_DATE, =, 1)
    )
)

PUBLIC(enum, discord_forum_layout_types, 3, (
        (DISCORD_FORUM_LAYOUT_NOT_SET, =, 0),
        (DISCORD_FORUM_LAYOUT_LIST_VIEW, =, 1),
        (DISCORD_FORUM_LAYOUT_GALLERY_VIEW, =, 1)
    )
)

PUBLIC(enum, discord_message_types, 31, (
        (DISCORD_MESSAGE_DEFAULT, =, 0),
        (DISCORD_MESSAGE_RECIPIENT_ADD, =, 1),
        (DISCORD_MESSAGE_RECIPIENT_REMOVE, =, 2),
        (DISCORD_MESSAGE_CALL, =, 3),
        (DISCORD_MESSAGE_CHANNEL_NAME_CHANGE, =, 4),
        (DISCORD_MESSAGE_CHANNEL_ICON_CHANGE, =, 5),
        (DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE, =, 6),
        (DISCORD_MESSAGE_GUILD_MEMBER_JOIN, =, 7),
        (DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION, =, 8),
        (DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1, =, 9),
        (DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2, =, 10),
        (DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3, =, 11),
        (DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD, =, 12),
        (DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED, =, 14),
        (DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED, =, 15),
        (DISCORD_MESSAGE_GUILD_DISCOVERY_GRACE_PERIOD_INITIAL_WARNING, =, 16),
        (DISCORD_MESSAGE_GUILD_DISCOVERY_GRACE_PERIOD_FINAL_WARNING, =, 17),
        (DISCORD_MESSAGE_THREAD_CREATED, =, 18),
        (DISCORD_MESSAGE_REPLY, =, 19),
        (DISCORD_MESSAGE_CHAT_INPUT_COMMAND, =, 20),
        (DISCORD_MESSAGE_THREAD_STARTER_MESSAGE, =, 21),
        (DISCORD_MESSAGE_GUILD_INVITE_REMINDER, =, 22),
        (DISCORD_MESSAGE_CONTEXT_MENU_COMMAND, =, 23),
        (DISCORD_MESSAGE_AUTO_MODERATION_ACTION, =, 24),
        (DISCORD_MESSAGE_ROLE_SUBSCRIPTION_PURCHASE, =, 25),
        (DISCORD_MESSAGE_INTERACTION_PREMIUM_UPSELL, =, 26),
        (DISCORD_MESSAGE_STAGE_START, =, 27),
        (DISCORD_MESSAGE_STAGE_END, =, 28),
        (DISCORD_MESSAGE_STAGE_SPEAKER, =, 29),
        (DISCORD_MESSAGE_STAGE_TOPIC, =, 31),
        (DISCORD_MESSAGE_GUILD_APPLICATION_PREMIUM_SUBSCRIPTION, =, 32)
    )
)

PUBLIC(enum, discord_message_activity_types, 4, (
        (DISCORD_MESSAGE_ACTIVITY_JOIN, =, 1),
        (DISCORD_MESSAGE_ACTIVITY_SPECTATE, =, 2),
        (DISCORD_MESSAGE_ACTIVITY_LISTEN, =, 3),
        (DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST, =, 5)
    )
)

PUBLIC(struct, discord_channel, 35, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, enum, discord_channel_types, _, type, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, position, _, _, 0ul),
        (_, struct, discord_overwrites, *, permission_overwrites, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, topic, _, _, 0ul),
        (_, _, bool, _, nsfw, _, _, 0ul),
        (_, _, u64snowflake, _, last_message_id, _, _, 0ul),
        (_, _, int, _, bitrate, _, _, 0ul),
        (_, _, int, _, user_limit, _, _, 0ul),
        (_, _, int, _, rate_limit_per_user, _, _, 0ul),
        (_, struct, discord_users, *, recipients, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, _, u64snowflake, _, owner_id, _, _, 0ul),
        (_, _, u64snowflake, _, application_id, _, _, 0ul),
        (_, _, bool, _, managed, _, _, 0ul),
        (_, _, u64snowflake, _, parent_id, _, _, 0ul),
        (_, _, u64unix_ms, _, last_pin_timestamp, _, _, 0ul),
        (_, _, char, *, rtc_region, _, _, 0ul),
        (_, _, int, _, voice_quality_mode, video_quality_mode, _, 0ul),
        (_, _, int, _, message_count, _, _, 0ul),
        (_, _, int, _, member_count, _, _, 0ul),
        (_, struct, discord_thread_metadata, *, thread_metadata, _, _, 0ul),
        (_, struct, discord_thread_member, *, member, _, _, 0ul),
        (_, _, int, _, default_auto_archive_duration, _, _, 0ul),
        (_, _, u64bitmask, _, permissions, _, _, 0ul),
        (_, _, u64bitmask, _, flags, _, _, 0ul),
        (_, _, int, _, total_message_sent, _, _, 0ul),
        (_, struct, discord_thread_tags, *, available_tags, _, _, 0ul),
        (_, struct, snowflakes, *, applied_tags, _, _, 0ul),
        (_, struct, discord_thread_default_reaction, *, default_reaction_emoji, _, _, 0ul),
        (_, _, int, _, default_thread_rate_limit_per_user, _, _, 0ul),
        (_, enum, discord_sort_order_types, _, default_sort_order, _, _, 0ul),
        (_, enum, discord_forum_layout_types, _, default_forum_layout, _, _, 0ul)
    )
)

PUBLIC(struct, discord_channels, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_channel, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_message_activity, 2, (
        (_, enum, discord_message_activity_types, _, type, _, _, 0ul),
        (_, _, char, *, party_id, _, _, 0ul)
    )
)

PRIVATE(struct, discord_message_reference, 4, (
        (_, _, u64snowflake, _, message_id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, _, bool, _, fail_if_not_exists, _, _, 0ul)
    )
)

PUBLIC(struct, discord_message, 34, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, struct, discord_user, *, author, _, _, 0ul),
        (_, struct, discord_guild_member, *, member, _, _, 0ul),
        (_, _, char, *, content, _, _, 0ul),
        (_, _, u64unix_ms, _, timestamp, _, _, 0ul),
        (_, _, u64unix_ms, _, edited_timestamp, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, tts, _, _, 0ul),
        (_, _, bool, _, mention_everyone, _, _, 0ul),
        (_, struct, discord_users, *, mentions, _, _, 0ul),
        (_, struct, snowflakes, *, mention_roles, _, _, 0ul),
        (_, struct, discord_channels, *, mention_channels, _, _, 0ul),
        (_, struct, discord_attachments, *, attachments, _, _, 0ul),
        (_, struct, discord_embeds, *, embeds, _, _, 0ul),
        (_, struct, discord_reactions, *, reactions, _, _, 0ul),
        (_, _, json_char, *, nonce, _, _, 0ul),
        (_, _, bool, _, pinned, _, _, 0ul),
        (_, _, u64snowflake, _, webhook_id, _, _, 0ul),
        (_, enum, discord_message_types, _, type, _, _, 0ul),
        (_, struct, discord_message_activity, *, activity, _, _, 0ul),
        (_, struct, discord_application, *, application, _, _, 0ul),
        (_, _, u64snowflake, _, application_id, _, _, 0ul),
        (_, struct, discord_message_reference, *, message_reference, _, _, 0ul),
        (_, _, u64bitmask, _, flags, _, _, 0ul),
        (_, struct, discord_message, *, referenced_message, _, _, 0ul),
        (_, struct, discord_message_interaction, *, interaction, _, _, 0ul),
        (_, struct, discord_channel, *, thread, _, _, 0ul),
        (_, struct, discord_components, *, components, _, _, 0ul),
        (_, struct, discord_sticker_items, *, sticker_items, _, _, 0ul),
        (_, struct, discord_stickers, *, stickers, _, _, 0ul),
        (_, _, int, _, position, _, _, 0ul),
        (_, struct, discord_role_subscription_data, *, role_subscription_data, _, _, 0ul),
        (_, struct, discord_resolved_data, *, resolved, _, _, 0ul)
    )
)

PUBLIC(struct, discord_messages, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_message, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_followed_channel, 2, (
        (_, _, u64snowflake, _, channel_id, _, _, 0ul),
        (_, _, u64snowflake, _, webhook_id, _, _, 0ul)
    )
)

PRIVATE(struct, discord_reaction_count_details, 2, (
        (_, _, int, _, burst, _, _, 0ul),
        (_, _, int, _, normal, _, _, 0ul)
    )
)

PRIVATE(struct, discord_reaction, 6, (
        (_, _, int, _, count, _, _, 0ul),
        (_, struct, discord_reaction_count_details, *, count_details, _, _, 0ul),
        (_, _, bool, _, me, _, _, 0ul),
        (_, _, bool, _, me_burst, _, _, 0ul),
        (_, struct, discord_emoji, *, emoji, _, _, 0ul),
        (_, _, char, *, burst_colors, _, _, 0ul)
    )
)

PRIVATE(struct, discord_reactions, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_reaction, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_overwrite, 4, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, int, _, type, _, _, 0ul),
        (_, _, u64bitmask, _, allow, _, _, 0ul),
        (_, _, u64bitmask, _, deny, _, _, 0ul)
    )
)

PRIVATE(struct, discord_overwrites, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_overwrite, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_thread_metadata, 6, (
        (_, _, bool, _, archived, _, _, 0ul),
        (_, _, int, _, auto_archive_duration, _, _, 0ul),
        (_, _, u64unix_ms, _, archive_timestamp, _, _, 0ul),
        (_, _, bool, _, locked, _, _, 0ul),
        (_, _, bool, _, invitable, _, _, 0ul),
        (_, _, u64unix_ms, _, create_timestamp, _, _, 0ul)
    )
)

PUBLIC(struct, discord_thread_member, 6, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, user_id, _, _, 0ul),
        (_, _, u64unix_ms, _, join_timestamp, _, _, 0ul),
        (_, _, u64bitmask, _, flags, _, _, 0ul),
        (_, struct, discord_guild_member, *, member, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul)
    )
)

PUBLIC(struct, discord_thread_members, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_thread_member, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_thread_default_reaction, 2, (
        (_, _, u64snowflake, _, emoji_id, _, _, 0ul),
        (_, _, char, *, emoji_name, _, _, 0ul)
    )
)

PRIVATE(struct, discord_thread_tag, 5, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, bool, _, moderated, _, _, 0ul),
        (_, _, u64snowflake, _, emoji_id, _, _, 0ul),
        (_, _, char, *, emoji_name, _, _, 0ul)
    )
)

PUBLIC(struct, discord_thread_tags, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_thread_tag, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_embed_thumbnail, 4, (
        (_, _, char, *, url, _, _, 0ul),
        (_, _, char, *, proxy_url, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, height, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, width, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_embed_video, 4, (
        (_, _, char, *, url, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, proxy_url, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, height, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, width, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_embed_image, 4, (
        (_, _, char, *, url, _, _, 0ul),
        (_, _, char, *, proxy_url, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, height, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, width, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_embed_provider, 2, (
        (_, _, char, *, name, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, url, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_embed_author, 4, (
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, url, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, icon_url, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, proxy_icon_url, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_embed_footer, 3, (
        (_, _, char, *, text, _, _, 0ul),
        (_, _, char, *, icon_url, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, proxy_icon_url, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_embed_field, 3, (
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, value, _, _, 0ul),
        (_, _, bool, _, Inline, inline, _, 0ul)
    )
)

PUBLIC(struct, discord_embed_fields, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_embed_field, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PUBLIC(struct, discord_embed, 13, (
        (_, _, char, *, title, _, _, 0ul),
        (_, _, char, *, type, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, char, *, url, _, _, 0ul),
        (_, _, u64unix_ms, _, timestamp, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, color, _, _, 0ul),
        (_, struct, discord_embed_footer, *, footer, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_embed_image, *, image, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_embed_thumbnail, *, thumbnail, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_embed_video, *, video, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_embed_provider, *, provider, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_embed_author, *, author, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_embed_fields, *, fields, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_embeds, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_embed, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_attachment, 14, (
        (_, _, char, *, content, _, _, 0ul),
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, char, *, filename, _, _, 0ul),
        (_, _, char, *, description, _, _, 0ul),
        (_, _, char, *, content_type, _, _, CONCORD_OPTIONAL),
        (_, _, size_t, _, size, _, _, 0ul),
        (_, _, char, *, url, _, _, 0ul),
        (_, _, char, *, proxy_url, _, _, 0ul),
        (_, _, int, _, height, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, width, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, ephemeral, _, _, 0ul),
        (_, _, int, _, duration_secs, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, waveform, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, flags, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_attachments, 3, (
        (_, _, int, _, size, _, _, 0ul),
        (_, struct, discord_attachment, *, array, _, _, 0ul),
        (_, _, int, _, realsize, _, _, 0ul)
    )
)

PRIVATE(struct, discord_channel_mention, 4, (
        (_, _, u64snowflake, _, id, _, _, 0ul),
        (_, _, u64snowflake, _, guild_id, _, _, 0ul),
        (_, enum, discord_channel_types, _, type, _, _, 0ul),
        (_, _, char, *, name, _, _, 0ul)
    )
)

PRIVATE(struct, discord_allowed_mention, 4, (
        (_, struct, strings, *, parse, _, _, 0ul),
        (_, struct, snowflakes, *, roles, _, _, 0ul),
        (_, struct, snowflakes, *, users, _, _, 0ul),
        (_, _, bool, _, replied_user, _, _, 0ul)
    )
)

PRIVATE(struct, discord_role_subscription_data, 4, (
        (_, _, u64snowflake, _, role_subscription_listing_id, _, _, 0ul),
        (_, _, char, *, tier_name, _, _, 0ul),
        (_, _, int, _, total_months_subscribed, _, _, 0ul),
        (_, _, bool, _, is_renewal, _, _, 0ul)
    )
)

PUBLIC(struct, discord_thread_response_body, 3, (
        (_, struct, discord_channels, *, threads, _, _, 0ul),
        (_, struct, discord_thread_members, *, members, _, _, 0ul),
        (_, _, bool, _, has_more, _, _, 0ul)
    )
)

PUBLIC(struct, discord_modify_channel, 18, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, char, *, icon, _, _, 0ul),
        (_, enum, discord_channel_types, _, type, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, position, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, topic, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, nsfw, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, rate_limit_per_user, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, user_limit, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_overwrites, *, permission_overwrites, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, parent_id, _, _, CONCORD_OPTIONAL),
        (_, _, char, *, rtc_region, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, video_quality_mode, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, default_auto_archive_duration, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, archived, _, _, 0ul),
        (_, _, int, _, auto_archive_duration, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, locked, _, _, 0ul),
        (_, _, bool, _, invitable, _, _, 0ul)
    )
)

PRIVATE(struct, discord_delete_channel, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PRIVATE(struct, discord_get_channel_messages, 4, (
        (_, _, u64snowflake, _, around, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, before, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, after, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, limit, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_create_message, 10, (
        (_, _, char, *, content, _, _, 0ul),
        (_, _, bool, _, tts, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_embeds, *, embeds, _, _, 0ul),
        (_, struct, discord_allowed_mention, *, allowed_mentions, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_message_reference, *, message_reference, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_components, *, components, _, _, CONCORD_OPTIONAL),
        (_, struct, snowflakes, *, sticker_ids, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_attachments, *, attachments, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, flags, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, enforce_nonce, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_get_reactions, 2, (
        (_, _, u64snowflake, _, after, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, limit, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_edit_message, 6, (
        (_, _, char, *, content, _, _, 0ul),
        (_, struct, discord_embeds, *, embeds, _, _, 0ul),
        (_, _, u64bitmask, _, flags, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_allowed_mention, *, allowed_mentions, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_components, *, components, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_attachments, *, attachments, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_delete_message, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PUBLIC(struct, discord_bulk_delete_messages, 2, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, struct, snowflakes, *, messages, _, _, 0ul)
    )
)

PUBLIC(struct, discord_edit_channel_permissions, 4, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, u64bitmask, _, allow, _, _, CONCORD_OPTIONAL),
        (_, _, u64bitmask, _, deny, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, type, _, _, 0ul)
    )
)

PUBLIC(struct, discord_create_channel_invite, 8, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, int, _, max_age, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, max_uses, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, temporary, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, unique, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_invite_target_types, _, target_type, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, target_user_id, _, _, CONCORD_OPTIONAL),
        (_, _, u64snowflake, _, target_application_id, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_delete_channel_permission, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PUBLIC(struct, discord_follow_news_channel, 1, (
        (_, _, u64snowflake, _, webhook_channel_id, _, _, CONCORD_OPTIONAL)
    )
)

PRIVATE(struct, discord_pin_message, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PRIVATE(struct, discord_unpin_message, 1, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON)
    )
)

PUBLIC(struct, discord_group_dm_add_recipient, 2, (
        (_, _, char, *, access_token, _, _, 0ul),
        (_, _, char, *, nick, _, _, 0ul)
    )
)

PUBLIC(struct, discord_start_thread_with_message, 4, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, int, _, auto_archive_duration, _, _, CONCORD_OPTIONAL),
        (_, _, int, _, rate_limit_per_user, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_start_thread_without_message, 6, (
        (_, _, char, *, reason, _, _, CONCORD_NO_JSON),
        (_, _, char, *, name, _, _, 0ul),
        (_, _, int, _, auto_archive_duration, _, _, CONCORD_OPTIONAL),
        (_, enum, discord_channel_types, _, type, _, _, 0ul),
        (_, _, bool, _, invitable, _, _, 0ul),
        (_, _, int, _, rate_limit_per_user, _, _, CONCORD_OPTIONAL)
    )
)

PUBLIC(struct, discord_list_active_threads, 3, (
        (_, struct, discord_channels, *, threads, _, _, CONCORD_OPTIONAL),
        (_, struct, discord_thread_members, *, members, _, _, CONCORD_OPTIONAL),
        (_, _, bool, _, has_more, _, _, 0ul)
    )
)
