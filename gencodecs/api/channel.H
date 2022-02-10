ENUM(discord_channel_types)
  DESC("a text channel within a server")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_TEXT, = 0)
  DESC("a direct message between users")
    ENUMERATOR(DISCORD_CHANNEL_DM, = 1)
  DESC("a voice channel within a server")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_VOICE, = 2)
  DESC("a direct message between multiple users")
    ENUMERATOR(DISCORD_CHANNEL_GROUP_DM, = 3)
  DESC("an organization category that contains up to 50 channels")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_CATEGORY, = 4)
  DESC("a channel that users can follow and crosspost into their own server")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_NEWS, = 5)
  DESC("a channel in which game developers can seel their game on Discord")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_STORE, = 6)
  DESC("a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_NEWS"
       "channel")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_NEWS_THREAD, = 10)
  DESC("a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_TEXT"
       "channel")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_PUBLIC_THREAD, = 11)
  DESC("a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_TEXT"
       "channel that is only viewable by those invited and those with the"
       "`MANAGE_THREADS` permission")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_PRIVATE_THREAD, = 12)
  DESC("a voice channel for hosting events with an audience")
    ENUMERATOR_LAST(DISCORD_CHANNEL_GUILD_STAGE_VOICE, = 13)
ENUM_END

ENUM(discord_video_quality_modes)
  DESC("Discord chooses the quality for optimal performance")
    ENUMERATOR(DISCORD_VIDEO_QUALITY_AUTO, = 1)
  DESC("720p")
    ENUMERATOR_LAST(DISCORD_VIDEO_QUALITY_FULL, = 2)
ENUM_END

ENUM(discord_message_types)
    ENUMERATOR(DISCORD_MESSAGE_DEFAULT, = 0)
    ENUMERATOR(DISCORD_MESSAGE_RECIPIENT_ADD, = 1)
    ENUMERATOR(DISCORD_MESSAGE_RECIPIENT_REMOVE, = 2)
    ENUMERATOR(DISCORD_MESSAGE_CALL, = 3)
    ENUMERATOR(DISCORD_MESSAGE_CHANNEL_NAME_CHANGE, = 4)
    ENUMERATOR(DISCORD_MESSAGE_CHANNEL_ICON_CHANGE, = 5)
    ENUMERATOR(DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE, = 6)
    ENUMERATOR(DISCORD_MESSAGE_GUILD_MEMBER_JOIN, = 7)
    ENUMERATOR(DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION, = 8)
    ENUMERATOR(DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1, = 9)
    ENUMERATOR(DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2, = 10)
    ENUMERATOR(DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3, = 11)
    ENUMERATOR(DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD, = 12)
    ENUMERATOR(DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED, = 14)
    ENUMERATOR(DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED, = 15)
    ENUMERATOR(DISCORD_MESSAGE_GUILD_DISCOVERY_GRACE_PERIOD_INITIAL_WARNING, = 16)
    ENUMERATOR(DISCORD_MESSAGE_GUILD_DISCOVERY_GRACE_PERIOD_FINAL_WARNING, = 17)
    ENUMERATOR(DISCORD_MESSAGE_THREAD_CREATED, = 18)
    ENUMERATOR(DISCORD_MESSAGE_REPLY, = 19)
    ENUMERATOR(DISCORD_MESSAGE_CHAT_INPUT_COMMAND, = 20)
    ENUMERATOR(DISCORD_MESSAGE_THREAD_STARTER_MESSAGE, = 21)
    ENUMERATOR(DISCORD_MESSAGE_GUILD_INVITE_REMINDER, = 22)
    ENUMERATOR_LAST(DISCORD_MESSAGE_CONTEXT_MENU_COMMAND, = 22)
ENUM_END

ENUM(discord_message_activity_types)
    ENUMERATOR(DISCORD_MESSAGE_ACTIVITY_JOIN, = 1)
    ENUMERATOR(DISCORD_MESSAGE_ACTIVITY_SPECTATE, = 2)
    ENUMERATOR(DISCORD_MESSAGE_ACTIVITY_LISTEN, = 3)
    ENUMERATOR_LAST(DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST, = 5)
ENUM_END

ENUM(discord_message_flags)
  DESC("this message has been published to subscribed channels (via Channel"
       "Following)")
    ENUMERATOR(DISCORD_MESSAGE_CROSSPOSTED, = 1 << 0)
  DESC("this message originated from a message in another channel (via Channel"
       "Following)")
    ENUMERATOR(DISCORD_MESSAGE_IS_CROSSPOST, = 1 << 1)
  DESC("do not include any embed when serializing this message")
    ENUMERATOR(DISCORD_MESSAGE_SUPRPRESS_EMBEDS, = 1 << 2)
  DESC("the source message for this crosspost has been deleted (via Channel"
       "Following)")
    ENUMERATOR(DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED, = 1 << 3)
  DESC("this message came from the urgent message system")
    ENUMERATOR(DISCORD_MESSAGE_URGENT, = 1 << 4)
  DESC("this message has an associated thread, with the same ID as the message")
    ENUMERATOR(DISCORD_MESSAGE_HAS_THREAD, = 1 << 5)
  DESC("this message is only visible to the user who invoked the interaction")
    ENUMERATOR(DISCORD_MESSAGE_EPHEMERAL, = 1 << 6)
  DESC("this message is an interaction response and the bot is thinking")
    ENUMERATOR(DISCORD_MESSAGE_LOADING, = 1 << 7)
  DESC("this message failed to mention some roles and add the members to the"
       "thread")
    ENUMERATOR_LAST(DISCORD_MESSAGE_FAILED_TO_MENTION_SOME_ROLES_IN_THREAD,
                    = 1 << 8)
ENUM_END

PUB_STRUCT(discord_channel)
  DESC("the ID of this channel")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the type of channel")
    FIELD_ENUM(type, discord_channel_types)
  DESC("the ID of the guild (may be missing for some channel objects received"
       "over gateway guild dispatches)")
  COND_WRITE(this->guild_id != 0)
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("sorting position of the channel")
    FIELD(position, int, 0)
  DESC("explicit permission overwrites for members and roles")
    FIELD_STRUCT_PTR(permission_overwrites, discord_overwrites, *)
  DESC("the name of the channel (0-1024 characters)")
    FIELD_PTR(name, char, *)
  DESC("the channel topic (0-1024 characters)")
    FIELD_PTR(topic, char, *)
  DESC("whether the channel is nsfw")
    FIELD(nsfw, bool, false)
  DESC("the id of the last message sent in this channel (may not point to an"
       "existing or valid message)")
    FIELD_PRINTF(last_message_id, u64snowflake, PRIu64, SCNu64)
  DESC("the bitrate (in bits) of the voice channel")
    FIELD(bitrate, int, 0)
  DESC("the user limit of the voice channel")
    FIELD(user_limit, int, 0)
  DESC("amount of seconds a user has to wait before sending another message"
       " (0-21600). bots, as well as users with the permission"
       "`MANAGE_MESSAGES` or `MANAGE_CHANNEL` are unaffected")
    FIELD(rate_limit_per_user, int, 0)
  DESC("array of user objects")
    FIELD_STRUCT_PTR(recipients, discord_users, *)
  DESC("icon hash of the group DM")
    FIELD_PTR(icon, char, *)
  DESC("id of the creator of the group DM or thread")
    FIELD_PRINTF(owner_id, u64snowflake, PRIu64, SCNu64)
  DESC("application ID of the group DM creator if its bot-created")
    FIELD_PRINTF(application_id, u64snowflake, PRIu64, SCNu64)
  DESC("for guild channels: ID of the parent category for a channel (each"
       "parent category can contain up to 50 channels), for threads: id of"
       "the text channel this thread was created")
    FIELD_PRINTF(parent_id, u64snowflake, PRIu64, SCNu64)
  /* TODO: iso8601 support */
#if 0
  DESC("when the last pinned message was pinned. This may be `NULL` in events"
       "such as `GUILD_CREATE` when a message is not pinned")
    FIELD_PRINTF(last_pin_timestamp, u64snowflake, PRIu64, SCNu64)
#endif
  DESC("voice region ID for the voice channel, automatic when set to null")
    FIELD_PTR(rtc_region, char, *)
  DESC("the camera video quality mode of the voice channel, 1 when not present")
    FIELD(voice_quality_mode, int, 0)
  DESC("an approximate count of messages in a thread, stops counting at 50")
    FIELD(message_count, int, 0)
  DESC("an approximate count of users in a thread, stops counting at 50")
    FIELD(member_count, int, 0)
  DESC("thread-specific fields not needed by other channels")
    FIELD_STRUCT_PTR(thread_metadata, discord_thread_metadata, *)
  DESC("thread member object for the current user, if they have joined the"
       "thread, only included on certain API endpoints")
    FIELD_STRUCT_PTR(member, discord_thread_member, *)
  DESC("default duration that the clients (not the API) will use for newly"
       "created threads, in minutes, to automatically archive the thread"
       "after recent activity, can be set to: 60, 1440, 4320, 10080")
    FIELD(default_auto_archive_duration, int, 0)
  DESC("computed permissions for the invoking user in the channel, including"
       "overwrites, only included when part of the `resolved` data received"
       "on a application command interaction")
    FIELD_PTR(permissions, char, *)
STRUCT_END

PUB_LIST(discord_channels)
    LISTTYPE_STRUCT(discord_channel)
LIST_END

PUB_STRUCT(discord_message)
  DESC("ID of the message")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("ID of the channel the message was sent in")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("ID of the guild the message was sent in")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("the author of this message (not guaranteed to be a valid user)")
    FIELD_STRUCT_PTR(author, discord_user, *)
  DESC("partial guild member")
    FIELD_STRUCT_PTR(member, discord_guild_member, *)
  DESC("contents of the message")
    FIELD_PTR(contents, char, *)
  /* TODO: iso8601 support */
#if 0
  DESC("when this message was sent")
    FIELD_PRINTF(timestamp, u64snowflake, PRIu64, SCNu64)
  DESC("when this message was edited (or null if never)")
    FIELD_PRINTF(edited_timestamp, u64snowflake, PRIu64, SCNu64)
#endif
  DESC("whether this was a TTS message")
    FIELD(tts, bool, false)
  DESC("whether this message mentions everyone")
    FIELD(mention_everyone, bool, false)
  /** FIXME: expects additional member field */
  DESC("users specifically mentioned in the message")
    FIELD_STRUCT_PTR(mentions, discord_users, *)
  DESC("roles specifically mentioned in this message")
    FIELD_STRUCT_PTR(mention_roles, discord_roles, *)
  DESC("channels specifically mentioned in this message")
    FIELD_STRUCT_PTR(mention_channels, discord_channels, *)
  DESC("any attached files")
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  DESC("any embedded content")
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  DESC("reactions to the message")
    FIELD_STRUCT_PTR(reactions, discord_reactions, *)
  /** FIXME: expects raw json (can be integer or string) */
  DESC("used for validating a message was sent")
    FIELD_PTR(nonce, char, *)
  DESC("whether this message is pinned")
    FIELD(pinned, bool, false)
  DESC("if the message is generated by a webhook, this is the webhook's ID")
    FIELD_PRINTF(webhook_id, u64snowflake, PRIu64, SCNu64)
  DESC("type of message")
    FIELD_ENUM(type, discord_message_types)
  DESC("sent with Rich Presence-related chat embeds")
    FIELD_STRUCT_PTR(activity, discord_message_activity, *)
  DESC("sent with Rich Presence-related chat embeds")
    FIELD_STRUCT_PTR(application, discord_application, *)
  DESC("if the message is an interaction or an application-owned webhook, this"
       "is the ID of the application")
    FIELD_PRINTF(application_id, u64snowflake, PRIu64, SCNu64)
  DESC("data showing the source of a crosspost, channel follow add, pin, or"
       "reply message")
    FIELD_STRUCT_PTR(message_reference, discord_message_reference, *)
  DESC("message flags combined as a bitfield")
    FIELD_ENUM(flags, discord_message_flags)
  DESC("the message associated with the message_reference")
    FIELD_STRUCT_PTR(referenced_message, discord_message, *)
  DESC("sent if the message is a response to an interaction")
    FIELD_STRUCT_PTR(interaction, discord_message_interaction, *)
  DESC("the thread that was started from this message, includes"
       "@ref discord_thread_member")
    FIELD_STRUCT_PTR(thread, discord_channel, *)
  DESC("sent if the message contains components like buttons, action rows, or"
       "other interactive components")
    FIELD_STRUCT_PTR(components, discord_components, *)
  DESC("sent if the message contains stickers")
    FIELD_STRUCT_PTR(sticker_items, discord_sticker_items, *)
STRUCT_END

PUB_LIST(discord_messages)
    LISTTYPE_STRUCT(discord_message)
LIST_END

STRUCT(discord_message_activity)
  DESC("type of message activity")
    FIELD_ENUM(type, discord_message_activity_types)
  DESC("party_id from a Rich Presence event")
    FIELD_PTR(party_id, char, *)
STRUCT_END

STRUCT(discord_message_reference)
  DESC("id of the originating message")
    FIELD_PRINTF(message_id, u64snowflake, PRIu64, SCNu64)
  DESC("id of the originating message's channel")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("id of the originating message's guild")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("when sending, whether to error if the referenced message doesn't exist"
       "instead of sending as normal (non-reply) message, default true")
    FIELD(fail_if_not_exists, bool, true)
STRUCT_END

PUB_STRUCT(discord_followed_channel)
  DESC("source channel id")
    FIELD_PRINTF(channel_id, u64snowflake, PRIu64, SCNu64)
  DESC("created target webhook id")
    FIELD_PRINTF(webhook_id, u64snowflake, PRIu64, SCNu64)
STRUCT_END

STRUCT(discord_reaction)
  DESC("times this emoji has been used to react")
    FIELD(count, int, 0)
  DESC("whether the current user reacted using this emoji")
    FIELD(me, bool, false)
  DESC("emoji information")
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
STRUCT_END

STRUCT(discord_overwrite)
  DESC("role or user id")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("either 0 (role) or 1 (member)")
    FIELD(count, int, 0)
  DESC("permission bit set")
    FIELD_PRINTF(allow, uint64_t, PRIu64, SCNu64)
  DESC("permission bit set")
    FIELD_PRINTF(deny, uint64_t, PRIu64, SCNu64)
STRUCT_END

LIST(discord_overwrites)
    LISTTYPE_STRUCT(discord_overwrite)
LIST_END

STRUCT(discord_thread_metadata)
  DESC("whether the thread is archived")
    FIELD(archived, bool, false)
  DESC("duration in minutes to automatically archive the thread after recent"
       "activity, can be set to: 60, 1440, 3320, 10080")
    FIELD(auto_archive_duration, int, 0)
  /* TODO: iso8601 support */
#if 0
  DESC("timestamp when the thread's archive status was last changed, used for"
       "calculating recent activity")
    FIELD_PRINTF(archive_timestamp, u64snowflake, PRIu64, SCNu64)
#endif
  DESC("whether the thread is locked; when a thread is locked only users with"
       "`MANAGE_THREADS` can unarchive it")
    FIELD(locked, bool, false)
  DESC("whether non-moderators cana dd other non-moderators to a thread; only"
       "available on private threads")
    FIELD(invitable, bool, false)
  /* TODO: iso8601 support */
#if 0
  DESC("timestamp when the thread was created; only populated for threads"
       "created after 2022-01-09")
    FIELD_PRINTF(create_timestamp, u64snowflake, PRIu64, SCNu64)
#endif
STRUCT_END

STRUCT(discord_thread_member)
  DESC("the id of the thread")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("the id of the user")
    FIELD_PRINTF(user_id, u64snowflake, PRIu64, SCNu64)
  /* TODO: iso8601 support */
#if 0
  DESC("the time the current user last joined the thread")
    FIELD_PRINTF(join_timestamp, u64snowflake, PRIu64, SCNu64)
#endif
  DESC("anyuser-thread settings, currently only used for notifications")
    FIELD(flags, int, 0)
STRUCT_END

PUB_LIST(discord_thread_members)
    LISTTYPE_STRUCT(discord_thread_member)
LIST_END

STRUCT(discord_attachment)
  /* FIXME: content shouldn't be included at from_json and to_json */
  DESC("the file contents")
    FIELD_PTR(content, char, *)
  DESC("attachment ID")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("name of file attached")
  COND_WRITE(this->filename != NULL)
    FIELD_PTR(filename, char, *)
  COND_END
  DESC("description for the file")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
  DESC("the attachment media type")
  COND_WRITE(this->content_type != NULL)
    FIELD_PTR(content_type, char, *)
  COND_END
  /* TODO: make it size_t */
  DESC("size of file in bytes")
    FIELD(size, int, 0)
  DESC("source url of file")
    FIELD_PTR(url, char, *)
  DESC("proxied url of file")
    FIELD_PTR(proxy_url, char, *)
  DESC("height of file (if image)")
  COND_WRITE(this->height != 0)
    FIELD(height, int, 0)
  COND_END
  DESC("width of file (if image)")
  COND_WRITE(this->width != 0)
    FIELD(width, int, 0)
  COND_END
  DESC("whether this attachment is ephemeral")
    FIELD(ephemeral, bool, false)
STRUCT_END

PUB_LIST(discord_attachments)
    LISTTYPE_STRUCT(discord_attachment)
LIST_END
