/*****************************************************************************
 * Guild Datatypes
 * **************************************************************************/

/** @defgroup DiscordAPIGuildSystemChannelFlags System channel flags
 * @ingroup DiscordAPIGuild
 *  @{ */

/** suppress member join notifications */
PP_DEFINE(DISCORD_SYSTEM_SUPPRESS_JOIN_NOTIFICATIONS 1 << 0)
/** suppress server boost notifications */
PP_DEFINE(DISCORD_SYSTEM_SUPPRESS_PREMIUM_NOTIFICATIONS 1 << 1)
/** suppress server setup tips */
PP_DEFINE(DISCORD_SYSTEM_SUPPRESS_GUILD_REMINDER_NOTIFICATIONS 1 << 2)
/** hide member join sticker reply buttons */
PP_DEFINE(DISCORD_SYSTEM_SUPPRESS_JOIN_NOTIFICATION_REPLIES 1 << 3)

/** @} DiscordAPIGuildSystemChannelFlags */

#if GENCODECS_RECIPE == DATA
ENUM(discord_message_notification_level)
  /** members will receive notifications for all messages by default */
    ENUMERATOR(DISCORD_MESSAGE_NOTIFICATION_ALL_MESSAGES, = 0)
  /** members will receive notifications only for messages that `@mention`
       them by default */
    ENUMERATOR_LAST(DISCORD_MESSAGE_NOTIFICATION_ONLY_MESSAGES, = 1)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_explicit_content_filter_level)
  /** media content will not be scanned */
    ENUMERATOR(DISCORD_EXPLICIT_CONTENT_DISABLED, = 0)
  /** media content sent by members without roles will be scanned */
    ENUMERATOR(DISCORD_EXPLICIT_CONTENT_MEMBERS_WITHOUT_ROLES, = 1)
  /** media content sent by all members will be scanned */
    ENUMERATOR_LAST(DISCORD_MESSAGE_NOTIFICATION_ALL_MEMBERS, = 2)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_mfa_level)
  /** guild has no MFA/2FA requirement for moderation actions */
    ENUMERATOR(DISCORD_MFA_NONE, = 0)
  /** guild has a 2FA requirement for moderation actions */
    ENUMERATOR_LAST(DISCORD_MFA_ELEVATED, = 1)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_verification_level)
  /** unrestricted */
    ENUMERATOR(DISCORD_VERIFICATION_NONE, = 0)
  /** must have verified email on account */
    ENUMERATOR(DISCORD_VERIFICATION_LOW, = 1)
  /** must be registered on Discord for longer than 5 minutes */
    ENUMERATOR(DISCORD_VERIFICATION_MEDIUM, = 2)
  /** must be a member of the server for longer than 10 minutes */
    ENUMERATOR(DISCORD_VERIFICATION_HIGH, = 3)
  /** must have a verified phone number */
    ENUMERATOR_LAST(DISCORD_VERIFICATION_VERY_HIGH, = 4)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_guild_nsfw_level)
    ENUMERATOR(DISCORD_GUILD_NSFW_DEFAULT, = 0)
    ENUMERATOR(DISCORD_GUILD_NSFW_EXPLICIT, = 1)
    ENUMERATOR(DISCORD_GUILD_NSFW_SAFE, = 2)
    ENUMERATOR_LAST(DISCORD_GUILD_NSFW_AGE_RESTRICTED, = 3)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_premium_tier)
  /** guild has not unlocked any Server Boost perks */
    ENUMERATOR(DISCORD_PREMIUM_TIER_NONE, = 0)
  /** guild has unlocked Server Boost level 1 perks */
    ENUMERATOR(DISCORD_PREMIUM_TIER_1, = 1)
  /** guild has unlocked Server Boost level 2 perks */
    ENUMERATOR(DISCORD_PREMIUM_TIER_2, = 2)
  /** guild has unlocked Server Boost level 3 perks */
    ENUMERATOR_LAST(DISCORD_PREMIUM_TIER_3, = 3)
ENUM_END
#endif

#if GENCODECS_RECIPE == DATA
ENUM(discord_integration_expire_behaviors)
    ENUMERATOR(DISCORD_INTEGRATION_REMOVE_ROLE, = 0)
    ENUMERATOR_LAST(DISCORD_INTEGRATION_KICK, = 1)
ENUM_END
#endif

/** @CCORD_pub_struct{discord_guild} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_guild)
  /** guild id */
    FIELD_SNOWFLAKE(id)
  /** guild name (2-100 characters, excluding trailing and leading
       whitespace */
    FIELD_PTR(name, char, *)
  /** icon hash */
    FIELD_PTR(icon, char, *)
  /** icon hash, returned when in the template object */
  COND_WRITE(self->icon_hash != NULL)
    FIELD_PTR(icon_hash, char, *)
  COND_END
  /** splash hash */
    FIELD_PTR(splash, char, *)
  /** discovery splash hash, only present for `DISCOVERABLE` guilds */
    FIELD_PTR(discovery_splash, char, *)
  /** true if the user is the owner of the guild */
    FIELD(owner, bool, false)
  /** id of owner */
    FIELD_SNOWFLAKE(owner_id)
  /** total permissions for the user in the guild (excludes overwrites) */
  COND_WRITE(self->permissions != 0)
    FIELD_BITMASK(permissions)
  COND_END
  /** id of afk channel */
    FIELD_SNOWFLAKE(afk_channel_id)
  /** afk timeout in seconds */
    FIELD(afk_timeout, int, 0)
  /** true if the server widget is enabled */
    FIELD(widget_enabled, bool, false)
  /** the channel id the widget will generate an invite to, or NULL if set
       to no invite */
    FIELD_SNOWFLAKE(widget_channel_id)
  /** verification level required for the guild */
    FIELD_ENUM(verification_level, discord_verification_level)
  /** default message notifications level */
    FIELD_ENUM(default_message_notifications, discord_message_notification_level)
  /** explicit content filter level */
    FIELD_ENUM(explicit_content_filter, discord_explicit_content_filter_level)
  /** roles in the guilds */
    FIELD_STRUCT_PTR(roles, discord_roles, *)
  /** custom guild emojis */
    FIELD_STRUCT_PTR(emojis, discord_emojis, *)
  /** enabled guild features */
    FIELD_STRUCT_PTR(features, strings, *)
  /** required MFA level for the guild */
    FIELD_ENUM(mfa_level, discord_mfa_level)
  /** application id of the guild creator if it is bot-created */
    FIELD_SNOWFLAKE(application_id)
  /** the id of the channel where guild notices such as welcome messages and
       boost events are posted */
    FIELD_SNOWFLAKE(system_channel_id)
  /** @ref DiscordAPIGuildSystemChannelFlags */
    FIELD_BITMASK(system_channel_flags)
  /** the id of the channel where Community guilds can display rules and/or
       guidelines */
    FIELD_SNOWFLAKE(rules_channel_id)
  /** when this guild was joined at */
  COND_WRITE(self->joined_at != 0)
    FIELD_TIMESTAMP(joined_at)
  COND_END
  /** true if this is considered a large guild */
    FIELD(large, bool, false)
  /** true if this guild is unavailable due to an outage */
    FIELD(unavailable, bool, false)
  /** total number of members in this guild */
    FIELD(member_count, int, 0)
  /** states of members currently in voice channels; lacks `guild_id` */
  COND_WRITE(self->voice_states != NULL)
    FIELD_STRUCT_PTR(voice_states, discord_voice_states, *)
  COND_END
  /** users in the guild */
  COND_WRITE(self->members != NULL)
    FIELD_STRUCT_PTR(members, discord_guild_members, *)
  COND_END
  /** channels in the guild */
  COND_WRITE(self->channels != NULL)
    FIELD_STRUCT_PTR(channels, discord_channels, *)
  COND_END
  /** all active threads in the guild that current user has permission to
       view */
  COND_WRITE(self->threads != NULL)
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  COND_END
  /** presences of the members in the guild, will only include non-offline
       members if the size is greater than `large threshold` */
  COND_WRITE(self->presences != NULL)
    FIELD_STRUCT_PTR(presences, discord_presence_updates, *)
  COND_END
  /** the maximum number of presences for the guild (null is always
       returned, apart from the largest of guilds) */
  COND_WRITE(self->max_presences != 0)
    FIELD(max_presences, int, 0)
  COND_END
  /** the maximum number of members for the guild */
  COND_WRITE(self->max_members != 0)
    FIELD(max_members, int, 0)
  COND_END
  /** the vanity url code for the guild */
    FIELD_PTR(vanity_url_code, char, *)
  /** the description of a Community guild */
    FIELD_PTR(description, char, *)
  /** banner hash */
    FIELD_PTR(banner, char, *)
  /** premium tier (Server Boost level) */
    FIELD_ENUM(premium_tier, discord_premium_tier)
  /** the number of boosts this guild currently has */
    FIELD(premium_subscription_count, int, 0)
  /** the preferred locale of a Community guild; used in server discovery and
       notices from Discord, and sent in interactions; defaults to \"en-US\" */
    FIELD_PTR(preferred_locale, char, *)
  /** the id of the channel where admins and moderators of Community guilds
       receive notices from Discord */
    FIELD_SNOWFLAKE(public_updates_channel_id)
  /** the maximum amount of users in a video channel */
  COND_WRITE(self->max_video_channel_users != 0)
    FIELD(max_video_channel_users, int, 0)
  COND_END
  /** approximate number of members in this guild */
  COND_WRITE(self->approximate_member_count != 0)
    FIELD(approximate_member_count, int, 0)
  COND_END
  /** approximate number of non-offline members in this guild */
  COND_WRITE(self->approximate_presence_count != 0)
    FIELD(approximate_presence_count, int, 0)
  COND_END
  /** the welcome screen of a Community guild, shown to new members, returned
       in an invite's guild object */
  COND_WRITE(self->welcome_screen != NULL)
    FIELD_STRUCT_PTR(welcome_screen, discord_welcome_screen, *)
  COND_END
  /** guild NSFW level */
    FIELD_ENUM(nsfw_level, discord_guild_nsfw_level)
  /** stage instances in the guild */
  COND_WRITE(self->stage_instances != NULL)
    FIELD_STRUCT_PTR(stage_instances, discord_stage_instances, *)
  COND_END
  /** custom guild stickers */
  COND_WRITE(self->stickers != NULL)
    FIELD_STRUCT_PTR(stickers, discord_stickers, *)
  COND_END
  /** the scheduled events in the guilds */
  COND_WRITE(self->guild_scheduled_events != NULL)
    FIELD_STRUCT_PTR(guild_scheduled_events, discord_guild_scheduled_events, *)
  COND_END
  /** whether the guild has the boost progress bar enabled */
    FIELD(premium_progress_bar_enabled, bool, false)
STRUCT_END
#endif

/** @CCORD_pub_list{discord_guilds} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_guilds)
    LISTTYPE_STRUCT(discord_guild)
LIST_END
#endif

/** @CCORD_pub_struct{discord_guild_preview} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_guild_preview)
  /** guild id */
    FIELD_SNOWFLAKE(id)
  /** guild name (2-100 characters) */
    FIELD_PTR(name, char, *)
  /** icon hash */
    FIELD_PTR(icon, char, *)
  /** splash hash */
    FIELD_PTR(splash, char, *)
  /** discovery splash hash */
    FIELD_PTR(discovery_splash, char, *)
  /** custom guild emojis */
    FIELD_STRUCT_PTR(emojis, discord_emojis, *)
  /** enabled guild features */
    FIELD_STRUCT_PTR(features, strings, *)
  /** approximate number of members in this guild */
    FIELD(approximate_member_count, int, 0)
  /** approximate number of online members in this guild */
    FIELD(approximate_presence_count, int, 0)
  /** the description for the guid, if the guild is discoverable */
    FIELD_PTR(description, char, *)
  /** custom guild stickers */
    FIELD_STRUCT_PTR(stickers, discord_stickers, *)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_guild_widget_settings} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_guild_widget_settings)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** whether the widget is enabled */
    FIELD(enabled, bool, false)
  /** the widget channel ID */
    FIELD_SNOWFLAKE(channel_id)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_guild_widget} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_guild_widget)
  /** guild id */
    FIELD_SNOWFLAKE(id)
  /** guild name (2-100 characters) */
    FIELD_PTR(name, char, *)
  /** instant invite for the guilds specified widget invite channel */
    FIELD_PTR(instant_invite, char, *)
  /** voice and stage channels which are accessible by `@everyone` */
    FIELD_STRUCT_PTR(channels, discord_channels, *)
  /** special widget user objects that includes users presence (limit 100) */
    FIELD_STRUCT_PTR(members, discord_users, *)
  /** number of online members in this guild */
    FIELD(presence_count, int, 0)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_guild_member} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_guild_member)
  /** the user this guild member represents */
  COND_WRITE(self->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
  /** this user's guild nickname */
  COND_WRITE(self->nick != NULL)
    FIELD_PTR(nick, char, *)
  COND_END
  /** the member's guild avatar hash */
  COND_WRITE(self->avatar != NULL)
    FIELD_PTR(avatar, char, *)
  COND_END
  /** array of role object IDs */
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  /** when the user joined the guild */
    FIELD_TIMESTAMP(joined_at)
  /** when the user started boosting the guild */
  COND_WRITE(self->premium_since != 0)
    FIELD_TIMESTAMP(premium_since)
  COND_END
  /** whether the user is deafened in voice channels */
    FIELD(deaf, bool, false)
  /** whether the user is muted in voice channels */
    FIELD(muted, bool, false)
  /** whether the user has not yet passed the guild's Membership Screening
       requirements */
    FIELD(pending, bool, false)
  /** total permission of the member in the channel, including overwrites,
       returned when in the interaction object */
  COND_WRITE(self->permissions != 0)
    FIELD_BITMASK(permissions)
  COND_END
  /** when the user's timeout will expire and the user will be able to
       communicate in the guild again, null or a time in the past if the
       user is not timed out */
    FIELD_TIMESTAMP(communication_disabled_until)
  /** the guild id @note extra field for `Guild Member Add` event */
    FIELD_SNOWFLAKE(guild_id)
STRUCT_END
#endif

/** @CCORD_pub_list{discord_guild_members} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_guild_members)
    LISTTYPE_STRUCT(discord_guild_member)
LIST_END
#endif

/** @CCORD_pub_struct{discord_integration} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_integration)
  /** integration id */
    FIELD_SNOWFLAKE(id)
  /** integration name */
    FIELD_PTR(name, char, *)
  /** integration type (twitch, youtube, or discord) */
    FIELD_PTR(type, char, *)
  /** is this integration enabled */
    FIELD(enabled, bool, false)
  /** is this integration syncing */
    FIELD(syncing, bool, false)
  /** ID that this integration uses for \"subscribers\" */
    FIELD_SNOWFLAKE(role_id)
  /** whether emoticons should be synced for this integration (twitch only
       currently) */
    FIELD(enable_emoticons, bool, false)
  /** the behavior of expiring subscribers */
    FIELD_ENUM(expire_behavior, discord_integration_expire_behaviors)
  /** the grace period (in days) before expiring subscribers */
    FIELD(expire_grace_period, int, 0)
  /** user for this integration */
    FIELD_STRUCT_PTR(user, discord_user, *)
  /** integration account information */
    FIELD_STRUCT_PTR(account, discord_integration_account, *)
  /** when this integration was last synced */
    FIELD_TIMESTAMP(synced_at)
  /** how many subscribers this integration has */
    FIELD(subscriber_count, int, 0)
  /** has this integration been revoked */
    FIELD(revoked, bool, false)
  /** the bot/OAuth2 application for discord integrations */
    FIELD_STRUCT_PTR(application, discord_integration_application, *)
  /** id of the guild @note extra field that may be included at
   *    `Integration Create` or `Integration Update` */
    FIELD_SNOWFLAKE(guild_id)
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_integrations)
    LISTTYPE_STRUCT(discord_integration)
LIST_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_integration_account)
  /** id of the account */
    FIELD_PTR(id, char, *)
  /** name of the account */
    FIELD_PTR(name, char, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_integration_application)
  /** the id of the app */
    FIELD_SNOWFLAKE(id)
  /** the name of the app */
    FIELD_PTR(name, char, *)
  /** the icon hash of the app */
    FIELD_PTR(icon, char, *)
  /** the description of the app */
    FIELD_PTR(description, char, *)
  /** the summary of the app */
    FIELD_PTR(summary, char, *)
  /** the bot associated with this application */
  COND_WRITE(self->bot != NULL)
    FIELD_STRUCT_PTR(bot, discord_user, *)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_ban} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_ban)
  /** the reason for the ban */
    FIELD_PTR(reason, char, *)
  /** the banned user */
    FIELD_STRUCT_PTR(user, discord_user, *)
STRUCT_END
#endif

/** @CCORD_pub_list{discord_bans} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_bans)
    LISTTYPE_STRUCT(discord_ban)
LIST_END
#endif

/** @CCORD_pub_struct{discord_welcome_screen} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_welcome_screen)
  /** the server description shown in the welcome screen */
    FIELD_PTR(description, char, *)
  /** the channels shown in the welcome screen, up to 5 */
  COND_WRITE(self->welcome_channels != NULL)
    FIELD_STRUCT_PTR(welcome_channels, discord_welcome_screen_channels, *)
  COND_END
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_welcome_screen_channel)
  /** the channel's id */
    FIELD_SNOWFLAKE(channel_id)
  /** the description shown for the channel */
    FIELD_PTR(description, char, *)
  /** the emoji id, if the emoji is custom */
    FIELD_SNOWFLAKE(emoji_id)
  /** the emoji name if custom, the unicode character if standard, or NULL if
       no emoji is set */
    FIELD_PTR(emoji_name, char, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
LIST(discord_welcome_screen_channels)
    LISTTYPE_STRUCT(discord_welcome_screen_channel)
LIST_END
#endif

/** @CCORD_pub_struct{discord_prune_count} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_prune_count)
    FIELD(pruned, int, 0)
STRUCT_END
#endif

/*****************************************************************************
 * Guild REST parameters
 * **************************************************************************/

/** @CCORD_pub_struct{discord_create_guild} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_create_guild)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** name of the guild (2-100 charaters) */
    FIELD_PTR(name, char, *)
  /** voice region ID @deprecated deprecated field */
  COND_WRITE(self->region != NULL)
    FIELD_PTR(region, char, *)
  COND_END
  /** base64 1024x1024 png/jpeg/gif image for the guild icon (can be
       animated gif when the server has the `ANIMATED_ICON` feature) */
  COND_WRITE(self->icon != NULL)
    FIELD_PTR(icon, char, *)
  COND_END
  /** verification level */
    FIELD_ENUM(verification_level, discord_verification_level)
  /** default message notification level */
    FIELD_ENUM(default_message_notifications, discord_message_notification_level)
  /** explicit content filter level */
    FIELD_ENUM(explicit_content_filter, discord_explicit_content_filter_level)
  /** new guild roles */
  COND_WRITE(self->roles != NULL)
    FIELD_STRUCT_PTR(roles, discord_roles, *)
  COND_END
  /** new guild's channels */
  COND_WRITE(self->channels != NULL)
    FIELD_STRUCT_PTR(channels, discord_channels, *)
  COND_END
  /** ID for afk channel */
  COND_WRITE(self->afk_channel_id != 0)
    FIELD_SNOWFLAKE(afk_channel_id)
  COND_END
  /** afk timeout in seconds */
    FIELD(afk_timeout, int, 0)
  /** the ID of the channel when guild notices such as welcome messages and
       boost events are posted */
    FIELD_SNOWFLAKE(system_channel_id)
  /** @ref DiscordAPIGuildSystemChannelFlags */
    FIELD_BITMASK(system_channel_flags)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_guild} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_guild)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** guild name */
    FIELD_PTR(name, char, *)
  /** verification level */
    FIELD_ENUM(verification_level, discord_verification_level)
  /** default message notification level */
    FIELD_ENUM(default_message_notifications, discord_message_notification_level)
  /** explicit content filter level */
    FIELD_ENUM(explicit_content_filter, discord_explicit_content_filter_level)
  /** ID for afk channel */
    FIELD_SNOWFLAKE(afk_channel_id)
  /** afk timeout in seconds */
    FIELD(afk_timeout, int, 0)
  /** base64 1024x1024 png/jpeg/gif image for the guild icon (can be
       animated gif when the server has the `ANIMATED_ICON` feature) */
    FIELD_PTR(icon, char, *)
  /** user ID to transfer guild ownership to (must be owner) */
    FIELD_SNOWFLAKE(owner_id)
  /** base64 1024x1024 png/jpeg/gif image for the guild splash (can be
       animated gif when the server has the `INVITE_SPLASH` feature) */
    FIELD_PTR(splash, char, *)
  /** base64 1024x1024 png/jpeg/gif image for the guild discovery splash
       (can be animated gif when the server has the `DISCOVERABLE` feature) */
    FIELD_PTR(discovery_splash, char, *)
  /** base64 1024x1024 png/jpeg/gif image for the guild banner (can be
       animated gif when the server has the `BANNER` feature) */
    FIELD_PTR(banner, char, *)
  /** the ID of the channel when guild notices such as welcome messages and
       boost events are posted */
    FIELD_SNOWFLAKE(system_channel_id)
  /** @ref DiscordAPIGuildSystemChannelFlags */
    FIELD_BITMASK(system_channel_flags)
  /** the ID of the channel where Community guilds display rules and/or
       guidelines */
    FIELD_SNOWFLAKE(rules_channel_id)
  /** the ID of the channel where admins and moderators of Community guild
       receive notices from Discord */
    FIELD_SNOWFLAKE(public_updates_channel_id)
  /** the preferred locale of a Community guild used in a server discovery
       and notices from Discord; defaults to \"en-US\" */
    FIELD_PTR(preferred_locale, char, *)
  /** enabled guild features */
    FIELD_STRUCT_PTR(features, strings, *)
  /** the description for the guild, if the guild is discoverable */
    FIELD_PTR(description, char, *)
  /** whether the guild's boost progress bar should be enabled */
    FIELD(premium_progress_bar_enabled, bool, false)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_create_guild_channel} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_create_guild_channel)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** channel name (1-100 characters) */
    FIELD_PTR(name, char, *)
  /** the type of channel */
    FIELD_ENUM(type, discord_channel_types)
  /** channel topic (0-1024 characters) */
    FIELD_PTR(topic, char, *)
  /** the bitrate (in bits) of the voice channel (voice only) */
  COND_WRITE(self->bitrate != 0)
    FIELD(bitrate, int, 0)
  COND_END
  /** the user limit of the voice channel (voice only) */
  COND_WRITE(self->user_limit != 0)
    FIELD(user_limit, int, 0)
  COND_END
  /** amount of seconds a user has to wait before sending another message
       (0-21600); bots, as well as users with the permission
       `MANAGE_MESSAGES` or `MANAGE_CHANNEL`, are unaffected */
    FIELD(rate_limit_per_user, int, 0)
  /** sorting position of the channel */
    FIELD(position, int, 0)
  /** the channel's permission overwrites */
    FIELD_STRUCT_PTR(permission_overwrites, discord_overwrites, *)
  /** ID of the parent category for a channel */
  COND_WRITE(self->parent_id != 0)
    FIELD_SNOWFLAKE(parent_id)
  COND_END
  /** whether the channel is nsfw */
    FIELD(nsfw, bool, false)
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_modify_guild_channel_position)
  /** channel ID */
    FIELD_SNOWFLAKE(id)
  /** sorting position of the channel */
  COND_WRITE(self->position != 0)
    FIELD(position, int, 0)
  COND_END
  /** syncs the permission overwrites with the new parent, if moving to a new
       category */
    FIELD(lock_category, bool, false)
  /** the new parent ID for the channel that is moved */
  COND_WRITE(self->parent_id != 0)
    FIELD_SNOWFLAKE(parent_id)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_list{discord_modify_guild_channel_positions} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_modify_guild_channel_positions)
    LISTTYPE_STRUCT(discord_modify_guild_channel_position)
LIST_END
#endif

/** @CCORD_pub_struct{discord_list_active_guild_threads} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_list_active_guild_threads)
  /** the active threads */
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  /** a thread member object for each returned thread the current user has
       joined */
    FIELD_STRUCT_PTR(members, discord_thread_members, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_list_guild_members)
  /** max number of members to return (1-1000) */
    FIELD(limit, int, 0)
  /** the highest user ID in the previous page */
    FIELD_SNOWFLAKE(after)
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_search_guild_members)
  /** query string to match username(s) and nickname(s) against */
    FIELD_PTR(query, char, *)
  /** max number of members to return (1-1000) */
    FIELD(limit, int, 0)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_add_guild_member} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_add_guild_member)
  /** an oauth2 access token granted with the `guild.join` to the bot's
       application for the user you want to add in the guild */
    FIELD_PTR(access_token, char, *)
  /** value to set user's nickname to */
    FIELD_PTR(nick, char, *)
  /** array of role IDs the member is assigned */
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  /** whether the user is muted in voice channels */
    FIELD(mute, bool, false)
  /** whether the user is deafened in voice channels */
    FIELD(deaf, bool, false)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_guild_member} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_guild_member)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** value to set user's nickname to */
  COND_WRITE(self->nick != NULL)
    FIELD_PTR(nick, char, *)
  COND_END
  /** array of role IDs the member is assigned */
  COND_WRITE(self->roles != NULL)
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  COND_END
  /** whether the user is muted in voice channels. will return a
       @ref CCORD_HTTP_ERROR (400) if the user is not in a voice channel */
  COND_WRITE(self->channel_id != 0)
    FIELD(mute, bool, false)
  COND_END
  /** whether the user is deafened in voice channels. will return a
       @ref CCORD_HTTP_ERROR (400) if the user is not in a voice channel */
  COND_WRITE(self->channel_id != 0)
    FIELD(deaf, bool, false)
  COND_END
  /** ID of channel to move user to (if they are connect to voice) */
  COND_WRITE(self->channel_id != 0)
    FIELD_SNOWFLAKE(channel_id)
  COND_END
  /** 
    @todo should be able to write `null`

    when the user's timeout will expire and the user will be able to
      communicate in the guild again (up to 28 days in the future), set
      to NULL to remove timeout. Will throw a @ref CCORD_HTTP_ERROR (403)
      error if the user has the `ADMINISTRATOR` permission or is the owner
      of the guild
  */
  COND_WRITE(self->communication_disabled_until != 0)
    FIELD_TIMESTAMP(communication_disabled_until)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_current_member} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_current_member)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** value to set user's nickname to */
  COND_WRITE(self->nick != NULL)
    FIELD_PTR(nick, char, *)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_current_user_nick} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_current_user_nick)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** value to set user's nickname to */
  COND_WRITE(self->nick != NULL)
    FIELD_PTR(nick, char, *)
  COND_END
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_add_guild_member_role)
  /** @CCORD_reason{reason} */
    FIELD_PTR(reason, char, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_remove_guild_member_role)
  /** @CCORD_reason{reason} */
    FIELD_PTR(reason, char, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_remove_guild_member)
  /** @CCORD_reason{reason} */
    FIELD_PTR(reason, char, *)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_create_guild_ban} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_create_guild_ban)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** number of days to delete messages for (0-7) */
  COND_WRITE(self->delete_message_days >= 0 && self->delete_message_days <= 7)
    FIELD(delete_message_days, int, 0)
  COND_END
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_remove_guild_ban)
  /** @CCORD_reason{reason} */
    FIELD_PTR(reason, char, *)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_create_guild_role} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_create_guild_role)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** name of the role */
    FIELD_PTR(name, char, *)
  /** `@everyone` permissions in guild */
    FIELD_BITMASK(permissions)
  /** RGB color value */
    FIELD(color, int, 0)
  /** whether the role should be displayed separately in the sidebar */
    FIELD(hoist, bool, false)
  /** the role's icon image (if the guild has the `ROLE_ICONS` feature) */
    FIELD_PTR(icon, char, *)
  /** the role's unicode emoji as a standard emoji (if the guild has the
       `ROLE_ICONS` feature) */
    FIELD_PTR(unicode_emoji, char, *)
  /** whether the role should be mentionable */
    FIELD(mentionable, bool, false)
STRUCT_END
#endif

#if GENCODECS_RECIPE & (DATA | JSON)
STRUCT(discord_modify_guild_role_position)
  /** role */
    FIELD_SNOWFLAKE(id)
  /** sorting position of the role */
  COND_WRITE(self->position != 0)
    FIELD(position, int, 0)
  COND_END
STRUCT_END
#endif

/** TODO: support X-Audit-Log-Reason */
/** @CCORD_pub_list{discord_modify_guild_role_positions} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_LIST(discord_modify_guild_role_positions)
    LISTTYPE_STRUCT(discord_modify_guild_role_position)
LIST_END
#endif

/** @CCORD_pub_struct{discord_modify_guild_role} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_guild_role)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** name of the role */
    FIELD_PTR(name, char, *)
  /** bitwise value of the enabled/disabled permissions */
    FIELD_BITMASK(permissions)
  /** RGB color value */
    FIELD(color, int, 0)
  /** whether the role should be displayed separately in the sidebar */
    FIELD(hoist, bool, false)
  /** the role's icon image (if the guild has the `ROLE_ICONS` feature) */
    FIELD_PTR(icon, char, *)
  /** the role's unicode emoji as a standard emoji (if the guild has the
       `ROLE_ICONS` feature) */
    FIELD_PTR(unicode_emoji, char, *)
  /** whether the role should be mentionable */
    FIELD(mentionable, bool, false)
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_delete_guild_role)
  /** @CCORD_reason{reason} */
    FIELD_PTR(reason, char, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_get_guild_prune_count)
  /** number of days to count prune for (1-30) */
  COND_WRITE(self->days >= 1 && self->days <= 30)
    FIELD(days, int, 7)
  COND_END
  /** role(s) to include */
    FIELD_STRUCT_PTR(include_roles, snowflakes, *)
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_begin_guild_prune} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_begin_guild_prune)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** number of days to prune */
  COND_WRITE(self->days != 0)
    FIELD(days, int, 7)
  COND_END
  /** whether 'pruned' is returned, discouraged for large guilds */
    FIELD(compute_prune_count, bool, true)
  /** role(s) to include */
    FIELD_STRUCT_PTR(include_roles, snowflakes, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_delete_guild_integrations)
  /** @CCORD_reason{reason} */
    FIELD_PTR(reason, char, *)
  /** number of days to count prune for (1-30) */
  COND_WRITE(self->days >= 1 && self->days <= 30)
    FIELD(days, int, 7)
  COND_END
  /** role(s) to include */
    FIELD_STRUCT_PTR(include_roles, snowflakes, *)
STRUCT_END
#endif

#if GENCODECS_RECIPE == DATA
STRUCT(discord_get_guild_widget_image)
  /** style of the widget image returned
       @see https://discord.com/developers/docs/resources/guild#membership-screening-object-widget-style-options */
  COND_WRITE(self->style != NULL)
    FIELD_PTR(style, char, *)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_guild_welcome_screen} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_guild_welcome_screen)
  /** @CCORD_reason{reason} */
#if GENCODECS_RECIPE == DATA
    FIELD_PTR(reason, char, *)
#endif
  /** whether the welcome screen is enabled */
    FIELD(enabled, bool, false)
  /** channels linked in the welcome screen and their display options */
    FIELD_STRUCT_PTR(welcome_channels, discord_welcome_screen_channels, *)
  /** the server description to show in the welcome screen */
  COND_WRITE(self->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_current_user_voice_state} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_current_user_voice_state)
  /** the ID of the channel the user is currently in */
    FIELD_SNOWFLAKE(channel_id)
  /** toggles the user's suppress state */
    FIELD(suppress, bool, false)
  /* TODO: should be able to write `null` */
  /** set the user's request to speak */
  COND_WRITE(self->request_to_speak_timestamp != 0)
    FIELD_TIMESTAMP(request_to_speak_timestamp)
  COND_END
STRUCT_END
#endif

/** @CCORD_pub_struct{discord_modify_user_voice_state} */
#if GENCODECS_RECIPE & (DATA | JSON)
PUB_STRUCT(discord_modify_user_voice_state)
  /** the ID of the channel the user is currently in */
    FIELD_SNOWFLAKE(channel_id)
  /** toggles the user's suppress state */
    FIELD(suppress, bool, false)
STRUCT_END
#endif
