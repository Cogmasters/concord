/*****************************************************************************
 * Guild Datatypes
 * **************************************************************************/

ENUM(discord_message_notification_level)
  DESC("members will receive notifications for all messages by default")
    ENUMERATOR(DISCORD_MESSAGE_NOTIFICATION_ALL_MESSAGES, = 0)
  DESC("members will receive notifications only for messages that `@mention`"
       "them by default")
    ENUMERATOR_LAST(DISCORD_MESSAGE_NOTIFICATION_ONLY_MESSAGES, = 1)
ENUM_END

ENUM(discord_explicit_content_filter_level)
  DESC("media content will not be scanned")
    ENUMERATOR(DISCORD_EXPLICIT_CONTENT_DISABLED, = 0)
  DESC("media content sent by members without roles will be scanned")
    ENUMERATOR(DISCORD_EXPLICIT_CONTENT_MEMBERS_WITHOUT_ROLES, = 1)
  DESC("media content sent by all members will be scanned")
    ENUMERATOR_LAST(DISCORD_MESSAGE_NOTIFICATION_ALL_MEMBERS, = 2)
ENUM_END

ENUM(discord_mfa_level)
  DESC("guild has no MFA/2FA requirement for moderation actions")
    ENUMERATOR(DISCORD_MFA_NONE, = 0)
  DESC("guild has a 2FA requirement for moderation actions")
    ENUMERATOR_LAST(DISCORD_MFA_ELEVATED, = 1)
ENUM_END

ENUM(discord_verification_level)
  DESC("unrestricted")
    ENUMERATOR(DISCORD_VERIFICATION_NONE, = 0)
  DESC("must have verified email on account")
    ENUMERATOR(DISCORD_VERIFICATION_LOW, = 1)
  DESC("must be registered on Discord for longer than 5 minutes")
    ENUMERATOR(DISCORD_VERIFICATION_MEDIUM, = 2)
  DESC("must be a member of the server for longer than 10 minutes")
    ENUMERATOR(DISCORD_VERIFICATION_HIGH, = 3)
  DESC("must have a verified phone number")
    ENUMERATOR_LAST(DISCORD_VERIFICATION_VERY_HIGH, = 4)
ENUM_END

ENUM(discord_guild_nsfw_level)
    ENUMERATOR(DISCORD_GUILD_NSFW_DEFAULT, = 0)
    ENUMERATOR(DISCORD_GUILD_NSFW_EXPLICIT, = 1)
    ENUMERATOR(DISCORD_GUILD_NSFW_SAFE, = 2)
    ENUMERATOR_LAST(DISCORD_GUILD_NSFW_AGE_RESTRICTED, = 3)
ENUM_END

ENUM(discord_premium_tier)
  DESC("guild has not unlocked any Server Boost perks")
    ENUMERATOR(DISCORD_PREMIUM_TIER_NONE, = 0)
  DESC("guild has unlocked Server Boost level 1 perks")
    ENUMERATOR(DISCORD_PREMIUM_TIER_1, = 1)
  DESC("guild has unlocked Server Boost level 2 perks")
    ENUMERATOR(DISCORD_PREMIUM_TIER_2, = 2)
  DESC("guild has unlocked Server Boost level 3 perks")
    ENUMERATOR_LAST(DISCORD_PREMIUM_TIER_3, = 3)
ENUM_END

ENUM(discord_system_channel_flags)
  DESC("suppress member join notifications")
    ENUMERATOR(DISCORD_SYSTEM_SUPPRESS_JOIN_NOTIFICATIONS, = 1 << 0)
  DESC("suppress server boost notifications")
    ENUMERATOR(DISCORD_SYSTEM_SUPPRESS_PREMIUM_NOTIFICATIONS, = 1 << 1)
  DESC("suppress server setup tips")
    ENUMERATOR(DISCORD_SYSTEM_SUPPRESS_GUILD_REMINDER_NOTIFICATIONS, = 1 << 2)
  DESC("hide member join sticker reply buttons")
    ENUMERATOR_LAST(DISCORD_SYSTEM_SUPPRESS_JOIN_NOTIFICATION_REPLIES, = 1 << 3)
ENUM_END

ENUM(discord_integration_expire_behaviors)
    ENUMERATOR(DISCORD_INTEGRATION_REMOVE_ROLE, = 0)
    ENUMERATOR_LAST(DISCORD_INTEGRATION_KICK, = 1)
ENUM_END

PUB_STRUCT(discord_guild)
  DESC("guild id")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("guild name (2-100 characters, excluding trailing and leading"
       "whitespace")
    FIELD_PTR(name, char, *)
  DESC("icon hash")
    FIELD_PTR(icon, char, *)
  DESC("icon hash, returned when in the template object")
  COND_WRITE(this->icon_hash != NULL)
    FIELD_PTR(icon_hash, char, *)
  COND_END
  DESC("splash hash")
    FIELD_PTR(splash, char, *)
  DESC("discovery splash hash, only present for `DISCOVERABLE` guilds")
    FIELD_PTR(discovery_splash, char, *)
  DESC("true if the user is the owner of the guild")
    FIELD(owner, bool, false)
  DESC("id of owner")
    FIELD_PRINTF(owner_id, u64snowflake, PRIu64, SCNu64)
  DESC("total permissions for the user in the guild (exclues overwrites)")
  COND_WRITE(this->permissions != NULL)
    FIELD_PTR(permissions, char, *)
  COND_END
  DESC("id of afk channel")
    FIELD_PRINTF(afk_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("afk timeout in seconds")
    FIELD(afk_timeout, int, 0)
  DESC("true if the server widget is enabled")
    FIELD(widget_enabled, bool, false)
  DESC("the channel id the widget will generate an invite to, or NULL if set"
       "to no invite")
    FIELD_PRINTF(widget_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("verification level required for the guild")
    FIELD_ENUM(verification_level, discord_verification_level)
  DESC("default message notifications level")
    FIELD_ENUM(default_message_notifications, discord_message_notification_level)
  DESC("explicit content filter level")
    FIELD_ENUM(explicit_content_filter, discord_explicit_content_filter_level)
  DESC("roles in the guilds")
    FIELD_STRUCT_PTR(roles, discord_roles, *)
  DESC("custom guild emojis")
    FIELD_STRUCT_PTR(emojis, discord_emojis, *)
  DESC("enabled guild features")
    FIELD_STRUCT_PTR(features, json_strings, *)
  DESC("required MFA level for the guild")
    FIELD_ENUM(mfa_level, discord_mfa_level)
  DESC("application id of the guild creator if it is bot-created")
    FIELD_PRINTF(application_id, u64snowflake, PRIu64, SCNu64)
  DESC("the id of the channel where guild notices such as welcome messages and"
       "boost events are posted")
    FIELD_PRINTF(system_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("system channel flags")
    FIELD_ENUM(system_channel_flags, discord_system_channel_flags)
  DESC("the id of the channel where Community guilds can display rules and/or"
       "guidelines")
    FIELD_PRINTF(rules_channel_id, u64snowflake, PRIu64, SCNu64)
  /* TODO: implement iso8601 conv */
#if 0
  DESC("when this guild was joined at")
  COND_WRITE(this->joined_at != NULL)
    FIELD_PRINTF(joined_at, u64snowflake, PRIu64, SCNu64)
  COND_END
#endif
  DESC("true if this is considered a large guild")
    FIELD(large, bool, false)
  DESC("true if this guild is unavailable due to an outage")
    FIELD(unavailable, bool, false)
  DESC("total number of members in this guild")
    FIELD(member_count, int, 0)
  DESC("states of members currently in voice channels; lacks `guild_id`")
  COND_WRITE(this->voice_states != NULL)
    FIELD_STRUCT_PTR(voice_states, discord_voice_states, *)
  COND_END
  DESC("users in the guild")
  COND_WRITE(this->members != NULL)
    FIELD_STRUCT_PTR(members, discord_guild_members, *)
  COND_END
  DESC("channels in the guild")
  COND_WRITE(this->channels != NULL)
    FIELD_STRUCT_PTR(channels, discord_channels, *)
  COND_END
  DESC("all active threads in the guild that current user has permission to"
       "view")
  COND_WRITE(this->threads != NULL)
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  COND_END
  DESC("presences of the members in the guild, will only include non-offline"
       "members if the size is greater than `large threshold`")
  COND_WRITE(this->presences != NULL)
    FIELD_STRUCT_PTR(presences, discord_presence_updates, *)
  COND_END
  DESC("the maximum number of presences for the guild (null is always"
       "returned, apart from the largest of guilds)")
  COND_WRITE(this->max_presences != 0)
    FIELD(max_presences, int, 0)
  COND_END
  DESC("the maximum number of members for the guild")
  COND_WRITE(this->max_members != 0)
    FIELD(max_members, int, 0)
  COND_END
  DESC("the vanity url code for the guild")
    FIELD_PTR(vanity_url_code, char, *)
  DESC("the description of a Community guild")
    FIELD_PTR(description, char, *)
  DESC("banner hash")
    FIELD_PTR(banner, char, *)
  DESC("premium tier (Server Boost level)")
    FIELD_ENUM(premium_tier, discord_premium_tier)
  DESC("the number of boosts this guild currently has")
    FIELD(premium_subscription_count, int, 0)
  DESC("the preferred locale of a Community guild; used in server discovery and"
       "notices from Discord, and sent in interactions; defaults to \"en-US\"")
    FIELD_PTR(preferred_locale, char, *)
  DESC("the id of the channel where admins and moderators of Community guilds"
       "receive notices from Discord")
    FIELD_PRINTF(public_updates_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the maximum amount of users in a video channel")
  COND_WRITE(this->max_video_channel_users != 0)
    FIELD(max_video_channel_users, int, 0)
  COND_END
  DESC("approximate number of members in this guild")
  COND_WRITE(this->approximate_member_count != 0)
    FIELD(approximate_member_count, int, 0)
  COND_END
  DESC("approximate number of non-offline members in this guild")
  COND_WRITE(this->approximate_presence_count != 0)
    FIELD(approximate_presence_count, int, 0)
  COND_END
  DESC("the welcome screen of a Community guild, shown to new members, returned"
       "in an invite's guild object")
  COND_WRITE(this->welcome_screen != NULL)
    FIELD_STRUCT_PTR(welcome_screen, discord_welcome_screen, *)
  COND_END
  DESC("guild NSFW level")
    FIELD_ENUM(nsfw_level, discord_guild_nsfw_level)
  DESC("stage instances in the guild")
  COND_WRITE(this->stage_instances != NULL)
    FIELD_STRUCT_PTR(stage_instances, discord_stage_instances, *)
  COND_END
  DESC("custom guild stickers")
  COND_WRITE(this->stickers != NULL)
    FIELD_STRUCT_PTR(stickers, discord_stickers, *)
  COND_END
  DESC("the scheduled events in the guilds")
  COND_WRITE(this->guild_scheduled_events != NULL)
    FIELD_STRUCT_PTR(guild_scheduled_events, discord_guild_scheduled_events, *)
  COND_END
  DESC("whether the guild has the boost progress bar enabled")
    FIELD(premium_progress_bar_enabled, bool, false)
STRUCT_END

PUB_LIST(discord_guilds)
    LISTTYPE_STRUCT(discord_guild)
LIST_END

PUB_STRUCT(discord_guild_preview)
  DESC("guild id")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("guild name (2-100 characters)")
    FIELD_PTR(name, char, *)
  DESC("icon hash")
    FIELD_PTR(icon, char, *)
  DESC("splash hash")
    FIELD_PTR(splash, char, *)
  DESC("discovery splash hash")
    FIELD_PTR(discovery_splash, char, *)
  DESC("custom guild emojis")
    FIELD_STRUCT_PTR(emojis, discord_emojis, *)
  DESC("enabled guild features")
    FIELD_STRUCT_PTR(features, json_strings, *)
  DESC("approximate number of members in this guild")
    FIELD(approximate_member_count, int, 0)
  DESC("approximate number of online members in this guild")
    FIELD(approximate_presence_count, int, 0)
  DESC("the description for the guid, if the guild is discoverable")
    FIELD_PTR(description, char, *)
  DESC("custom guild stickers")
    FIELD_STRUCT_PTR(stickers, discord_stickers, *)
STRUCT_END

STRUCT(discord_guild_widget_setting)
  DESC("whether the widget is enabled")
    FIELD(enabled, bool, false)
  DESC("the widget channel ID")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
STRUCT_END

STRUCT(discord_get_guild_widget)
  DESC("guild id")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("guild name (2-100 characters)")
    FIELD_PTR(name, char, *)
  DESC("instant invite for the guilds specified widget invite channel")
    FIELD_PTR(instant_invite, char, *)
  DESC("voice and stage channels which are accessible by `@everyone`")
    FIELD_STRUCT_PTR(channels, discord_channels, *)
  DESC("special widget user objects that includes users presence (limit 100)")
    FIELD_STRUCT_PTR(members, discord_users, *)
  DESC("number of online members in this guild")
    FIELD(presence_count, int, 0)
STRUCT_END

PUB_STRUCT(discord_guild_member)
  DESC("the user this guild member represents")
  COND_WRITE(this->user != NULL)
    FIELD_STRUCT_PTR(user, discord_user, *)
  COND_END
  DESC("this user's guild nickname")
  COND_WRITE(this->nick != NULL)
    FIELD_PTR(nick, char, *)
  COND_END
  DESC("the member's guild avatar hash")
  COND_WRITE(this->avatar != NULL)
    FIELD_PTR(avatar, char, *)
  COND_END
  DESC("array of role object IDs")
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  /* TODO: implement iso8601 conv */
#if 0
  DESC("when the user joined the guild")
    FIELD_PRINTF(joined_at, u64snowflake, PRIu64, SCNu64)
  DESC("when the user started boosting the guild")
  COND_WRITE(this->premium_since != 0)
    FIELD_PRINTF(premium_since, u64snowflake, PRIu64, SCNu64)
  COND_END
#endif
  DESC("whether the user is deafened in voice channels")
    FIELD(deaf, bool, false)
  DESC("whether the user is muted in voice channels")
    FIELD(muted, bool, false)
  DESC("whether the user has not yet passed the guild's Membership Screening"
       "requirements")
    FIELD(pending, bool, false)
  DESC("total permission of the member in the channel, including overwrites,"
       "returned when in the interaction object")
  COND_WRITE(this->permissions != NULL)
    FIELD_PTR(permissions, char, *)
  COND_END
  /* TODO: implement iso8601 conv */
#if 0
  DESC("when the user's timeout will expire and the user will be able to"
       "communicate in the guild again, null or a time in the past if the"
       "user is not timed out")
    FIELD_PRINTF(communication_disabled_until, u64snowflake, PRIu64, SCNu64)
#endif
STRUCT_END

PUB_LIST(discord_guild_members)
    LISTTYPE_STRUCT(discord_guild_member)
LIST_END

STRUCT(discord_integration)
  DESC("integration id")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("integration name")
    FIELD_PTR(name, char, *)
  DESC("integration type (twitch, youtube, or discord)")
    FIELD_PTR(type, char, *)
  DESC("is this integration enabled")
    FIELD(enabled, bool, false)
  DESC("is this integration syncing")
    FIELD(syncing, bool, false)
  DESC("ID that this integration uses for \"subscribers\"")
    FIELD_PRINTF(role_id, u64snowflake, PRIu64, SCNu64)
  DESC("whether emoticons should be synced for this integration (twitch only"
       "currently)")
    FIELD(enable_emoticons, bool, false)
  DESC("the behavior of expiring subscribers")
    FIELD_ENUM(expire_behavior, discord_integration_expire_behaviors)
  DESC("the grace period (in days) before expiring subscribers")
    FIELD(expire_grace_period, int, 0)
  DESC("user for this integration")
    FIELD_STRUCT_PTR(user, discord_user, *)
  DESC("integration account information")
    FIELD_STRUCT_PTR(account, discord_integration_account, *)
  /* TODO: implement iso8601 conv */
#if 0
  DESC("when this integration was last synced")
    FIELD_PRINTF(synced_at, u64snowflake, PRIu64, SCNu64)
#endif
  DESC("how many subscribers this integration has")
    FIELD(subscriber_count, int, 0)
  DESC("has this integration been revoked")
    FIELD(revoked, bool, false)
  DESC("the bot/OAuth2 application for discord integrations")
    FIELD_STRUCT_PTR(application, discord_integration_application, *)
STRUCT_END

STRUCT(discord_integration_account)
  DESC("id of the account")
    FIELD_PTR(id, char, *)
  DESC("name of the account")
    FIELD_PTR(name, char, *)
STRUCT_END

STRUCT(discord_integration_application)
  DESC("the id of the app")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the name of the app")
    FIELD_PTR(name, char, *)
  DESC("the icon hash of the app")
    FIELD_PTR(icon, char, *)
  DESC("the description of the app")
    FIELD_PTR(description, char, *)
  DESC("the summary of the app")
    FIELD_PTR(summary, char, *)
  DESC("the bot associated with this application")
  COND_WRITE(this->bot != NULL)
    FIELD_STRUCT_PTR(bot, discord_user, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_ban)
  DESC("the reason for the ban")
    FIELD_PTR(reason, char, *)
  DESC("the banned user")
    FIELD_STRUCT_PTR(user, discord_user, *)
STRUCT_END

PUB_LIST(discord_bans)
    LISTTYPE_STRUCT(discord_ban)
LIST_END

PUB_STRUCT(discord_welcome_screen)
  DESC("the server description shown in the welcome screen")
    FIELD_PTR(description, char, *)
  DESC("the channels shown in the welcome screen, up to 5")
  COND_WRITE(this->welcome_channels != NULL)
    FIELD_STRUCT_PTR(welcome_channels, discord_welcome_screen_channels, *)
  COND_END
STRUCT_END

STRUCT(discord_welcome_screen_channel)
  DESC("the channel's id")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the description shown for the channel")
    FIELD_PTR(description, char, *)
  DESC("the emoji id, if the emoji is custom")
    FIELD_PRINTF(emoji_id, u64snowflake, PRIu64, SCNu64)
  DESC("the emoji name if custom, the unicode character if standard, or NULL if"
       "no emoji is set")
    FIELD_PTR(emoji_name, char, *)
STRUCT_END

/*****************************************************************************
 * Guild REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_create_guild)
  DESC("name of the guild (2-100 charaters)")
    FIELD_PTR(name, char, *)
  DESC("voice region ID @deprecated deprecated field")
  COND_WRITE(this->region != NULL)
    FIELD_PTR(region, char, *)
  COND_END
  DESC("base64 1024x1024 png/jpeg/gif image for the guild icon (can be"
       "animated gif when the server has the `ANIMATED_ICON` feature)")
  COND_WRITE(this->icon != NULL)
    FIELD_PTR(icon, char, *)
  COND_END
  DESC("verification level")
    FIELD_ENUM(verification_level, discord_verification_level)
  DESC("default message notification level")
    FIELD_ENUM(default_message_notifications, discord_message_notification_level)
  DESC("explicit content filter level")
    FIELD_ENUM(explicit_content_filter, discord_explicit_content_filter_level)
  DESC("new guild roles")
  COND_WRITE(this->roles != NULL)
    FIELD_STRUCT_PTR(roles, discord_roles, *)
  COND_END
  DESC("new guild's channels")
  COND_WRITE(this->channels != NULL)
    FIELD_STRUCT_PTR(channels, discord_channels, *)
  COND_END
  DESC("ID for afk channel")
  COND_WRITE(this->afk_channel_id != 0)
    FIELD_PRINTF(afk_channel_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("afk timeout in seconds")
    FIELD(afk_timeout, int, 0)
  DESC("the ID of the channel when guild notices such as welcome messages and"
       "boost events are posted")
    FIELD_PRINTF(system_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("system channel flags")
    FIELD_ENUM(system_channel_flags, discord_system_channel_flags)
STRUCT_END

PUB_STRUCT(discord_modify_guild)
  DESC("guild name")
    FIELD_PTR(name, char, *)
  DESC("verification level")
    FIELD_ENUM(verification_level, discord_verification_level)
  DESC("default message notification level")
    FIELD_ENUM(default_message_notifications, discord_message_notification_level)
  DESC("explicit content filter level")
    FIELD_ENUM(explicit_content_filter, discord_explicit_content_filter_level)
  DESC("ID for afk channel")
    FIELD_PRINTF(afk_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("afk timeout in seconds")
    FIELD(afk_timeout, int, 0)
  DESC("base64 1024x1024 png/jpeg/gif image for the guild icon (can be"
       "animated gif when the server has the `ANIMATED_ICON` feature)")
    FIELD_PTR(icon, char, *)
  DESC("user ID to transfer guild ownership to (must be owner)")
    FIELD_PRINTF(owner_id, u64snowflake, PRIu64, SCNu64)
  DESC("base64 1024x1024 png/jpeg/gif image for the guild splash (can be"
       "animated gif when the server has the `INVITE_SPLASH` feature)")
    FIELD_PTR(splash, char, *)
  DESC("base64 1024x1024 png/jpeg/gif image for the guild discovery splash"
       "(can be animated gif when the server has the `DISCOVERABLE` feature)")
    FIELD_PTR(discovery_splash, char, *)
  DESC("base64 1024x1024 png/jpeg/gif image for the guild banner (can be"
       "animated gif when the server has the `BANNER` feature)")
    FIELD_PTR(banner, char, *)
  DESC("the ID of the channel when guild notices such as welcome messages and"
       "boost events are posted")
    FIELD_PRINTF(system_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("system channel flags")
    FIELD_ENUM(system_channel_flags, discord_system_channel_flags)
  DESC("the ID of the channel where Community guilds display rules and/or"
       "guidelines")
    FIELD_PRINTF(rules_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the ID of the channel where admins and moderators of Community guild"
       "receive notices from Discord")
    FIELD_PRINTF(public_updates_channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("the preferred locale of a Community guild used in a server discovery"
       "and notices from Discord; defaults to \"en-US\"")
    FIELD_PTR(preferred_locale, char, *)
  DESC("enabled guild features")
    FIELD_STRUCT_PTR(features, json_strings, *)
  DESC("the description for the guild, if the guild is discoverable")
    FIELD_PTR(description, char, *)
  DESC("whether the guild's boost progress bar should be enabled")
    FIELD(premium_progress_bar_enabled, bool, false)
STRUCT_END

PUB_STRUCT(discord_create_guild_channel)
  DESC("channel name (1-100 characters)")
    FIELD_PTR(name, char, *)
  DESC("the type of channel")
    FIELD_ENUM(type, discord_channel_types)
  DESC("channel topic (0-1024 characters)")
    FIELD_PTR(topic, char, *)
  DESC("the bitrate (in bits) of the voice channel (voice only)")
  COND_WRITE(this->bitrate != 0)
    FIELD(bitrate, int, 0)
  COND_END
  DESC("the user limit of the voice channel (voice only)")
  COND_WRITE(this->user_limit != 0)
    FIELD(user_limit, int, 0)
  COND_END
  DESC("amount of seconds a user has to wait before sending another message"
       "(0-21600); bots, as well as users with the permission"
       "`MANAGE_MESSAGES` or `MANAGE_CHANNEL`, are unaffected")
    FIELD(rate_limit_per_user, int, 0)
  DESC("sorting position of the channel")
    FIELD(position, int, 0)
  DESC("the channel's permission overwrites")
    FIELD_STRUCT_PTR(permission_overwrites, discord_overwrites, *)
  DESC("ID of the parent category for a channel")
  COND_WRITE(this->parent_id != 0)
    FIELD_PRINTF(parent_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("whether the channel is nsfw")
    FIELD(nsfw, bool, false)
STRUCT_END

STRUCT(discord_modify_guild_channel_position)
  DESC("channel ID")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("sorting position of the channel")
  COND_WRITE(this->position != 0)
    FIELD(position, int, 0)
  COND_END
  DESC("syncs the permission overwrites with the new parent, if moving to a new"
       "category")
    FIELD(lock_category, bool, false)
  DESC("the new parent ID for the channel that is moved")
  COND_WRITE(this->parent_id != 0)
    FIELD_PRINTF(parent_id, u64snowflake, PRIu64, SCNu64)
  COND_END
STRUCT_END

PUB_LIST(discord_modify_guild_channel_positions)
    LISTTYPE_STRUCT(discord_modify_guild_channel_position)
LIST_END

PUB_STRUCT(discord_list_active_guild_threads)
  DESC("the active threads")
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  DESC("a thread member object for each returned thread the current user has"
       "joined")
    FIELD_STRUCT_PTR(members, discord_thread_members, *)
STRUCT_END

/* TODO: disable json encoding functions */
STRUCT(discord_list_guild_members)
  DESC("max number of members to return (1-1000)")
    FIELD(limit, int, 0)
  DESC("the highest user ID in the previous page")
    FIELD_PRINTF(after, u64snowflake, PRIu64, SCNu64)
STRUCT_END

/* TODO: disable json encoding functions */
STRUCT(discord_search_guild_members)
  DESC("query string to match username(s) and nickname(s) against")
    FIELD_PTR(query, char, *)
  DESC("max number of members to return (1-1000)")
    FIELD(limit, int, 0)
STRUCT_END

PUB_STRUCT(discord_add_guild_member)
  DESC("an oauth2 access token granted with the `guild.join` to the bot's"
       "application for the user you want to add in the guild")
    FIELD_PTR(access_token, char, *)
  DESC("value to set user's nickname to")
    FIELD_PTR(nick, char, *)
  DESC("array of role IDs the member is assigned")
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  DESC("whether the user is muted in voice channels")
    FIELD(mute, bool, false)
  DESC("whether the user is deafened in voice channels")
    FIELD(deaf, bool, false)
STRUCT_END

PUB_STRUCT(discord_modify_guild_member)
  DESC("value to set user's nickname to")
    FIELD_PTR(nick, char, *)
  DESC("array of role IDs the member is assigned")
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  DESC("whether the user is muted in voice channels. will return a"
       "@ref CCORD_HTTP_ERROR (400) if the user is not in a voice channel")
    FIELD(mute, bool, false)
  DESC("whether the user is deafened in voice channels. will return a"
       "@ref CCORD_HTTP_ERROR (400) if the user is not in a voice channel")
    FIELD(deaf, bool, false)
  DESC("ID of channel to move user to (if they are connect to voice)")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  /* TODO: implement iso8601 conversion */
  /* TODO: should be able to write `null` */
#if 0
  DESC("when the uesr's timeout will expire and the user will be able to"
       "communicate in the guild again (up to 28 days in the future), set"
       "to NULL to remove timeout. WIll throw a @ref CCORD_HTTP_ERROR (403)"
       "error if the user has the `ADMINISTRATOR` permission or is the owner"
       "of the guild")
  COND_WRITE(this->communication_disabled_until != 0)
    FIELD_PRINTF(communication_disabled_until, u64snowflake, PRIu64, SCNu64)
  COND_END
#endif
STRUCT_END

PUB_STRUCT(discord_modify_current_member)
  DESC("value to set user's nickname to")
  COND_WRITE(this->nick != NULL)
    FIELD_PTR(nick, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_modify_current_user_nick)
  DESC("value to set user's nickname to")
  COND_WRITE(this->nick != NULL)
    FIELD_PTR(nick, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_create_guild_ban)
  DESC("number of days to delete messages for (0-7)")
  COND_WRITE(this->delete_message_days >= 0 && this->delete_message_days <= 7)
    FIELD(delete_message_days, int, 0)
  COND_END
  DESC("reason for the ban @deprecated deprecated field")
  COND_WRITE(this->reason != NULL)
    FIELD_PTR(reason, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_create_guild_role)
  DESC("name of the role")
    FIELD_PTR(name, char, *)
  DESC("`@everyone` permissions in guild")
    FIELD_PRINTF(permissions, uint64_t, PRIu64, SCNu64)
  DESC("RGB color value")
    FIELD(color, int, 0)
  DESC("whether the role should be displayed separately in the sidebar")
    FIELD(hoist, bool, false)
  DESC("the role's icon image (if the guild has the `ROLE_ICONS` feature)")
    FIELD_PTR(icon, char, *)
  DESC("the role's unicode emoji as a standard emoji (if the guild has the"
       "`ROLE_ICONS` feature)")
    FIELD_PTR(unicode_emoji, char, *)
  DESC("whether the role should be mentionable")
    FIELD(mentionable, bool, false)
STRUCT_END

STRUCT(discord_modify_guild_role_position)
  DESC("role")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("sorting position of the role")
  COND_WRITE(this->position != 0)
    FIELD(position, int, 0)
  COND_END
STRUCT_END

PUB_LIST(discord_modify_guild_role_positions)
    LISTTYPE_STRUCT(discord_modify_guild_role_position)
LIST_END

PUB_STRUCT(discord_modify_guild_role)
  DESC("name of the role")
    FIELD_PTR(name, char, *)
  DESC("bitwise value of the enabled/disabled permissions")
    FIELD_PRINTF(permissions, uint64_t, PRIu64, SCNu64)
  DESC("RGB color value")
    FIELD(color, int, 0)
  DESC("whether the role should be displayed separately in the sidebar")
    FIELD(hoist, bool, false)
  DESC("the role's icon image (if the guild has the `ROLE_ICONS` feature)")
    FIELD_PTR(icon, char, *)
  DESC("the role's unicode emoji as a standard emoji (if the guild has the"
       "`ROLE_ICONS` feature)")
    FIELD_PTR(unicode_emoji, char, *)
  DESC("whether the role should be mentionable")
    FIELD(mentionable, bool, false)
STRUCT_END

/* TODO: disable json encoding functions */
STRUCT(discord_get_guild_prune_count)
  DESC("number of days to count prune for (1-30)")
  COND_WRITE(this->count != 0)
    FIELD(count, int, 7)
  COND_END
  DESC("role(s) to include")
    FIELD_STRUCT_PTR(include_roles, snowflakes, *)
STRUCT_END

PUB_STRUCT(discord_begin_guild_prune)
  DESC("number of days to prune")
  COND_WRITE(this->days != 0)
    FIELD(days, int, 7)
  COND_END
  DESC("whether 'pruned' is returned, discouraged for large guilds")
    FIELD(compute_prune_count, bool, true)
  DESC("role(s) to include")
    FIELD_STRUCT_PTR(include_roles, snowflakes, *)
  DESC("reason for the prune @deprecated deprecated field")
  COND_WRITE(this->reason != NULL)
    FIELD_PTR(reason, char, *)
  COND_END
STRUCT_END

/* TODO: disable json encoding functions */
STRUCT(discord_get_guild_widget_image)
  DESC("style of the widget image returned"
       "@see https://discord.com/developers/docs/resources/guild#membership-screening-object-widget-style-options")
  COND_WRITE(this->style != NULL)
    FIELD_PTR(style, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_modify_guild_welcome_screen)
  DESC("whether the welcome screen is enabled")
    FIELD(enabled, bool, false)
  DESC("channels linked in the welcome screen and their display options")
    FIELD_STRUCT_PTR(welcome_channels, discord_welcome_screen_channels, *)
  DESC("the server description to show in the welcome screen")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_modify_current_user_voice_state)
  DESC("the ID of the channel the user is currently in")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("toggles the user's suppress state")
    FIELD(suppress, bool, false)
  /* TODO: implement iso8601 conversion */
  /* TODO: should be able to write `null` */
#if 0
  DESC("set the user's request to speak")
  COND_WRITE(this->request_to_speak_timestamp != 0)
    FIELD_PRINTF(request_to_speak_timestamp, u64snowflake, PRIu64, SCNu64)
  COND_END
#endif
STRUCT_END

PUB_STRUCT(discord_modify_user_voice_state)
  DESC("the ID of the channel the user is currently in")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("toggles the user's suppress state")
    FIELD(suppress, bool, false)
STRUCT_END
