/*****************************************************************************
 * Channel Datatypes
 * **************************************************************************/

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

PUB_STRUCT(discord_embed)
  DESC("title of embed")
    FIELD_PTR(title, char, *)
  DESC("type of embed (always \"rich\" for webhook embeds)")
    FIELD_PTR(type, char, *)
  DESC("description of embed")
    FIELD_PTR(description, char, *)
  DESC("url of embed")
    FIELD_PTR(url, char, *)
  /* TODO: iso8601 support */
#if 0
  DESC("timestamp of embed content")
    FIELD_PRINTF(timestamp, u64snowflake, PRIu64, SCNu64)
#endif
  DESC("color code of the embed")
  COND_WRITE(this->color != 0)
    FIELD(color, int, 0)
  COND_END
  DESC("footer information")
  COND_WRITE(this->footer != NULL)
    FIELD_STRUCT_PTR(footer, discord_embed_footer, *)
  COND_END
  DESC("image information")
  COND_WRITE(this->image != NULL)
    FIELD_STRUCT_PTR(image, discord_embed_image, *)
  COND_END
  DESC("thumbnail information")
  COND_WRITE(this->thumbnail != NULL)
    FIELD_STRUCT_PTR(thumbnail, discord_embed_thumbnail, *)
  COND_END
  DESC("video information")
  COND_WRITE(this->video != NULL)
    FIELD_STRUCT_PTR(video, discord_embed_video, *)
  COND_END
  COND_WRITE(this->provider != NULL)
    FIELD_STRUCT_PTR(provider, discord_embed_provider, *)
  COND_END
  COND_WRITE(this->author != NULL)
    FIELD_STRUCT_PTR(author, discord_embed_author, *)
  COND_END
  COND_WRITE(this->fields != NULL)
    FIELD_STRUCT_PTR(fields, discord_embed_fields, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_thumbnail)
  DESC("source url of thumbnail (only supports http(s) and attachments)")
    FIELD_PTR(url, char, *)
  DESC("a proxied url of the thumbnail")
  COND_WRITE(this->proxy_url != NULL)
    FIELD_PTR(proxy_url, char, *)
  COND_END
  DESC("height of thumbnail")
  COND_WRITE(this->height != 0)
    FIELD(height, int, 0)
  COND_END
  DESC("width of thumbnail")
  COND_WRITE(this->width != 0)
    FIELD(width, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_video)
  DESC("source url of video")
  COND_WRITE(this->url != NULL)
    FIELD_PTR(url, char, *)
  COND_END
  DESC("a proxied url of the video")
  COND_WRITE(this->proxy_url != NULL)
    FIELD_PTR(proxy_url, char, *)
  COND_END
  DESC("height of video")
  COND_WRITE(this->height != 0)
    FIELD(height, int, 0)
  COND_END
  DESC("width of video")
  COND_WRITE(this->width != 0)
    FIELD(width, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_image)
  DESC("source url of image (only supports http(s) and attachments)")
    FIELD_PTR(url, char, *)
  DESC("a proxied url of the image")
  COND_WRITE(this->proxy_url != NULL)
    FIELD_PTR(proxy_url, char, *)
  COND_END
  DESC("height of image")
  COND_WRITE(this->height != 0)
    FIELD(height, int, 0)
  COND_END
  DESC("width of image")
  COND_WRITE(this->width != 0)
    FIELD(width, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_provider)
  DESC("name of provider")
  COND_WRITE(this->name != NULL)
    FIELD_PTR(name, char, *)
  COND_END
  DESC("url of provider")
  COND_WRITE(this->url != NULL)
    FIELD_PTR(url, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_author)
  DESC("name of author")
    FIELD_PTR(name, char, *)
  DESC("url of author")
  COND_WRITE(this->url != NULL)
    FIELD_PTR(url, char, *)
  COND_END
  DESC("url of author icon (only supports http(s) and attachments)")
  COND_WRITE(this->icon_url != NULL)
    FIELD_PTR(icon_url, char, *)
  COND_END
  DESC("a proxied url of author icon")
  COND_WRITE(this->proxy_icon_url != NULL)
    FIELD_PTR(proxy_icon_url, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_footer)
  DESC("footer text")
    FIELD_PTR(text, char, *)
  DESC("url of footer icon (only supports http(s) and attachments)")
  COND_WRITE(this->icon_url != NULL)
    FIELD_PTR(icon_url, char, *)
  COND_END
  DESC("a proxied url of footer icon")
  COND_WRITE(this->proxy_icon_url != NULL)
    FIELD_PTR(proxy_icon_url, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_field)
  DESC("name of the field")
    FIELD_PTR(name, char, *)
  DESC("value of the field")
    FIELD_PTR(name, char, *)
  DESC("whether or not this field should display inline")
    FIELD_CUSTOM(Inline, inline, bool, DECOR_BLANK, INIT_BLANK, CLEANUP_BLANK,
                 JSON_ENCODER_bool, JSON_DECODER_bool, false)
STRUCT_END

PUB_LIST(discord_embed_fields)
    LISTTYPE_STRUCT(discord_embed_field)
LIST_END

STRUCT(discord_channel_mention)
  DESC("ID of the channel")
    FIELD_PRINTF(id, u64snowflake, PRIu64, SCNu64)
  DESC("ID of the guild containing the channel")
    FIELD_PRINTF(guild_id, u64snowflake, PRIu64, SCNu64)
  DESC("the type of the channel")
    FIELD_ENUM(type, discord_channel_types)
  DESC("the name of the channel")
    FIELD_PTR(name, char, *)
STRUCT_END

STRUCT(discord_allowed_mention)
  DESC("An array of allowed mention tpes to parse from the content")
    FIELD_STRUCT_PTR(parse, json_strings, *)
  DESC("Array of role_ids to mention (Max size of 100)")
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  DESC("Array of user_ids to mention (Max size of 100)")
    FIELD_STRUCT_PTR(users, snowflakes, *)
  DESC("For replies, whether to mention the author of the message being"
       "replied to (default false)")
    FIELD(replied_user, bool, false)
STRUCT_END

/*****************************************************************************
 * Channel REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_modify_channel)
  DESC("1-100 character channel name")
    FIELD_PTR(name, char, *)
  /* GROUP DM */
  /* TODO: implement base64 encoder */
#if 0
  DESC("base64 encoded icon")
    FIELD_PTR(icon, char, *)
#endif
  /* GUILD CHANNEL */
  DESC("the type of channel; only conversion between text and news is"
       "supported and only in guilds with the `NEWS` feature")
    FIELD_ENUM(type, discord_channel_types)
  DESC("the position of the channel in the left-hand listing")
  COND_WRITE(this->position != 0)
    FIELD(position, int, 0)
  COND_END
  DESC("0-1024 character channel topic")
    FIELD_PTR(topic, char, *)
  DESC("whether the channel is nsfw")
    FIELD(nsfw, bool, false)
  DESC("amount of seconds a user has to wait before sending another message"
       "(0-21600); bots, as well as users with the permission"
       "`MANAGE_MESSAGES` or `MANAGE_CHANNEL`, are unaffected")
  COND_WRITE(this->rate_limit_per_user != 0)
    FIELD(rate_limit_per_user, int, 0)
  COND_END
  DESC("the user limit of the voice channel; 0 refers to no limit, 1 to 99"
       "refers to a user limit")
  COND_WRITE(this->user_limit != 0)
    FIELD(user_limit, int, 0)
  COND_END
  DESC("channel or category-specific permissions")
  COND_WRITE(this->permission_overwrites != NULL)
    FIELD_STRUCT_PTR(permission_overwrites, discord_overwrites, *)
  COND_END
  DESC("ID of the new parent category for a channel")
  COND_WRITE(this->parent_id != 0)
    FIELD_PRINTF(parent_id, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("channel voice region id, automatic when set to NULL")
    FIELD_PTR(rtc_region, char, *)
  DESC("the camera video quality mode of the voice channel")
  COND_WRITE(this->video_quality_mode != 0)
    FIELD(video_quality_mode, int, 0)
  COND_END
  DESC("the default duration that the clients use (not the API) for newly"
       "created threads in the channel, in minutes, to automatically archive"
       "the thread after recent activity")
  COND_WRITE(this->default_auto_archive_duration != 0)
    FIELD(default_auto_archive_duration, int, 0)
  COND_END
  /* THREAD */
  DESC("whether the thread is archived")
    FIELD(archived, bool, false)
  DESC("duration in minutes to automatically arhived the thread after recent"
       "activity, can be set to: 60, 1440, 4320, 10080")
  COND_WRITE(this->auto_archive_duration != 0)
    FIELD(auto_archive_duration, int, 0)
  COND_END
  DESC("whether the thread is locked; when a thread is locked, only users with"
       "`MANAGE_THREADS` can unarchive it")
    FIELD(locked, bool, false)
  DESC("whether non-moderators can add other non-moderators to a thread; only"
       "available on private threads")
    FIELD(invitable, bool, false)
  DESC("amount of seconds a user has to wait before sending another message"
       "(0-21600); bots, as well as users with the permission"
       "`MANAGE_MESSAGES`, `MANAGE_THREAD`, or `MANAGE_CHANNEL`, are"
       "unaffected")
  COND_WRITE(this->rate_limit_per_user != 0)
    FIELD(rate_limit_per_user, int, 0)
  COND_END
STRUCT_END

/* FIXME: shouldn't generate JSON functions */
/* TODO: to_query encoding */
PUB_STRUCT(discord_get_channel_messages)
  DESC("get messages around this message ID")
    FIELD_PRINTF(around, u64snowflake, PRIu64, SCNu64)
  DESC("get messages before this message ID")
    FIELD_PRINTF(before, u64snowflake, PRIu64, SCNu64)
  DESC("get messages after this message ID")
    FIELD_PRINTF(after, u64snowflake, PRIu64, SCNu64)
  DESC("max number of messages to return (1-100)")
STRUCT_END

PUB_STRUCT(discord_create_message)
  DESC("the message contents (up to 2000 characters)")
    FIELD_PTR(content, char, *)
  DESC("true if this is a TTS message")
    FIELD(tts, bool, false)
  DESC("embedded `rich` content (up to 6000 characters)")
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  DESC("allowed mentions for the message")
  COND_WRITE(this->allowed_mentions != NULL)
    FIELD_STRUCT_PTR(allowed_mentions, discord_allowed_mention, *)
  COND_END
  DESC("include to make your message a reply")
  COND_WRITE(this->message_reference != NULL)
    FIELD_STRUCT_PTR(message_reference, discord_message_reference, *)
  COND_END
  DESC("the components to include with the message")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  DESC("IDs of up to 3 stickers in the server to send in the message")
  COND_WRITE(this->sticker_ids != NULL)
    FIELD_STRUCT_PTR(sticker_ids, snowflakes, *)
  COND_END
  DESC("attachment objects with filename and description")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
  DESC("message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be"
       "set")
  COND_WRITE(this->flags != 0)
    FIELD_ENUM(flags, discord_message_flags)
  COND_END
STRUCT_END

/* FIXME: shouldn't generate JSON functions */
/* TODO: to_query encoding */
PUB_STRUCT(discord_get_reactions)
  DESC("get users after this user ID")
  COND_WRITE(this->after != 0)
    FIELD_PRINTF(after, u64snowflake, PRIu64, SCNu64)
  COND_END
  DESC("max number of users to return (1-100)")
  COND_WRITE(this->limit != 0)
    FIELD(limit, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_edit_message)
  DESC("the message contents (up to 2000 characters)")
    FIELD_PTR(content, char, *)
  DESC("embedded `rich` content (up to 6000 characters)")
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  DESC("message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be"
       "set")
  COND_WRITE(this->flags != 0)
    FIELD_ENUM(flags, discord_message_flags)
  COND_END
  DESC("allowed mentions for the message")
  COND_WRITE(this->allowed_mentions != NULL)
    FIELD_STRUCT_PTR(allowed_mentions, discord_allowed_mention, *)
  COND_END
  DESC("the components to include with the message")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  DESC("attachment objects with filename and description")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_bulk_delete_messages)
  DESC("an array of message ids to delete (2-100)")
    FIELD_STRUCT_PTR(messages, snowflakes, *)
STRUCT_END

PUB_STRUCT(discord_edit_channel_permission)
  DESC("the bitwise value of all allowed permissions (default \"0\")")
  COND_WRITE(this->allow != NULL)
    FIELD_PTR(allow, char, *)
  COND_END
  DESC("the bitwise value of all disallowed permissions (default \"0\")")
  COND_WRITE(this->deny != NULL)
    FIELD_PTR(deny, char, *)
  COND_END
  DESC("0 for a role or 1 for a member")
    FIELD(type, int, 0)
STRUCT_END

PUB_STRUCT(discord_create_channel_invite)
  DESC("duration of invite in seconds before expiry, or 0 for never. between"
       "0 and 604800 (7 days)")
  COND_WRITE(this->max_age != 0)
    FIELD(max_age, int, 86400)
  COND_END
  DESC("max number of uses or 0 for unlimited. betwee 0 and 100")
  COND_WRITE(this->max_uses != 0)
    FIELD(max_uses, int, 0)
  COND_END
  DESC("whether this invite only grants temporary membership")
  COND_WRITE(this->temporary != 0)
    FIELD(temporary, bool, false)
  COND_END
  DESC("if true, don't true to reuse a similar invite (useful for creating"
       "many unique one time use invites)")
  COND_WRITE(this->unique != 0)
    FIELD(unique, bool, false)
  COND_END
  DESC("the type of target for this voice channel invite")
  COND_WRITE(this->target_type != 0)
    FIELD_ENUM(target_type, discord_invite_target_types)
  COND_END
  DESC("the id of the user whose stream to display for this invite, required"
       "if `target_type` is 1, the user must be streaming in the channel")
  COND_WRITE(this->target_user_id != 0)
    FIELD_PRINTF(target_user_id, u64_snowflake, PRIu64, SCNu64)
  COND_END
  DESC("the id of the embedded application to open for this invite, required"
       "if `target_type` is 2, the application must have the `EMBEDDED` flag")
  COND_WRITE(this->target_application_id != 0)
    FIELD_PRINTF(target_application_id, u64_snowflake, PRIu64, SCNu64)
  COND_END
STRUCT_END

PUB_STRUCT(discord_follow_news_channel)
  DESC("id of target channel")
  COND_WRITE(this->webhook_channel_id != 0)
    FIELD_PRINTF(webhook_channel_id, u64_snowflake, PRIu64, SCNu64)
  COND_END
STRUCT_END

PUB_STRUCT(discord_group_dm_add_recipient)
  DESC("access token of a user that has granted your app the `gdm.join` scope")
    FIELD_PTR(access_token, char, *)
  DESC("nickname of the user being added")
    FIELD_PTR(nick, char, *)
STRUCT_END

PUB_STRUCT(discord_start_thread_with_message)
  DESC("1-100 character channel name")
    FIELD_PTR(name, char, *)
  DESC("duration in minutes to automatically archive the thread after recent"
       "activity, can be set to: 60, 1440, 4320, 10080")
  COND_WRITE(this->auto_archive_duration != 0)
    FIELD(auto_archive_duration, int, 0)
  COND_END
  DESC("amount of seconds a user has to wait before sending another message"
       "(0-21600)")
  COND_WRITE(this->rate_limit_per_user >= 0
             && this->rate_limit_per_user <= 21600)
    FIELD(rate_limit_per_user, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_start_thread_without_message)
  DESC("1-100 character channel name")
    FIELD_PTR(name, char, *)
  DESC("duration in minutes to automatically archive the thread after recent"
       "activity, can be set to: 60, 1440, 4320, 10080")
  COND_WRITE(this->auto_archive_duration != 0)
    FIELD(auto_archive_duration, int, 0)
  COND_END
  DESC("the type of thread to create")
    FIELD_ENUM(type, discord_channel_types)
  DESC("whether non-moderators can add other non-moderators to a thread; only"
       "available when creating a private thread")
    FIELD(invitable, bool, false)
  DESC("amount of seconds a user has to wait before sending another message"
       "(0-21600)")
  COND_WRITE(this->rate_limit_per_user >= 0
             && this->rate_limit_per_user <= 21600)
    FIELD(rate_limit_per_user, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_list_active_threads)
  DESC("the active threads")
  COND_WRITE(this->threads != NULL)
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  COND_END
  DESC("a thread member object for each returned thread the current user has"
       "joined")
  COND_WRITE(this->members != NULL)
    FIELD_STRUCT_PTR(members, discord_thread_members, *)
  COND_END
  DESC("whether there are potentially additional threads that could be returned"
       "on a subsequent call")
    FIELD(has_more, bool, false)
STRUCT_END
