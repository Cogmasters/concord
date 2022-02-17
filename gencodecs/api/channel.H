/*****************************************************************************
 * Channel Datatypes
 * **************************************************************************/

ENUM(discord_channel_types)
  PP("a text channel within a server")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_TEXT, = 0)
  PP("a direct message between users")
    ENUMERATOR(DISCORD_CHANNEL_DM, = 1)
  PP("a voice channel within a server")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_VOICE, = 2)
  PP("a direct message between multiple users")
    ENUMERATOR(DISCORD_CHANNEL_GROUP_DM, = 3)
  PP("an organization category that contains up to 50 channels")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_CATEGORY, = 4)
  PP("a channel that users can follow and crosspost into their own server")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_NEWS, = 5)
  PP("a channel in which game developers can seel their game on Discord")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_STORE, = 6)
  PP("a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_NEWS"
       "channel")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_NEWS_THREAD, = 10)
  PP("a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_TEXT"
       "channel")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_PUBLIC_THREAD, = 11)
  PP("a temporary sub-channel within a @ref DISCORD_CHANNEL_GUILD_TEXT"
       "channel that is only viewable by those invited and those with the"
       "`MANAGE_THREADS` permission")
    ENUMERATOR(DISCORD_CHANNEL_GUILD_PRIVATE_THREAD, = 12)
  PP("a voice channel for hosting events with an audience")
    ENUMERATOR_LAST(DISCORD_CHANNEL_GUILD_STAGE_VOICE, = 13)
ENUM_END

ENUM(discord_video_quality_modes)
  PP("Discord chooses the quality for optimal performance")
    ENUMERATOR(DISCORD_VIDEO_QUALITY_AUTO, = 1)
  PP("720p")
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
  PP("this message has been published to subscribed channels (via Channel"
       "Following)")
    ENUMERATOR(DISCORD_MESSAGE_CROSSPOSTED, = 1 << 0)
  PP("this message originated from a message in another channel (via Channel"
       "Following)")
    ENUMERATOR(DISCORD_MESSAGE_IS_CROSSPOST, = 1 << 1)
  PP("do not include any embed when serializing this message")
    ENUMERATOR(DISCORD_MESSAGE_SUPRPRESS_EMBEDS, = 1 << 2)
  PP("the source message for this crosspost has been deleted (via Channel"
       "Following)")
    ENUMERATOR(DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED, = 1 << 3)
  PP("this message came from the urgent message system")
    ENUMERATOR(DISCORD_MESSAGE_URGENT, = 1 << 4)
  PP("this message has an associated thread, with the same ID as the message")
    ENUMERATOR(DISCORD_MESSAGE_HAS_THREAD, = 1 << 5)
  PP("this message is only visible to the user who invoked the interaction")
    ENUMERATOR(DISCORD_MESSAGE_EPHEMERAL, = 1 << 6)
  PP("this message is an interaction response and the bot is thinking")
    ENUMERATOR(DISCORD_MESSAGE_LOADING, = 1 << 7)
  PP("this message failed to mention some roles and add the members to the"
       "thread")
    ENUMERATOR_LAST(DISCORD_MESSAGE_FAILED_TO_MENTION_SOME_ROLES_IN_THREAD,
                    = 1 << 8)
ENUM_END

PUB_STRUCT(discord_channel)
  PP("the ID of this channel")
    FIELD_SNOWFLAKE(id)
  PP("the type of channel")
    FIELD_ENUM(type, discord_channel_types)
  PP("the ID of the guild (may be missing for some channel objects received"
       "over gateway guild dispatches)")
  COND_WRITE(this->guild_id != 0)
    FIELD_SNOWFLAKE(guild_id)
  COND_END
  PP("sorting position of the channel")
    FIELD(position, int, 0)
  PP("explicit permission overwrites for members and roles")
    FIELD_STRUCT_PTR(permission_overwrites, discord_overwrites, *)
  PP("the name of the channel (0-1024 characters)")
    FIELD_PTR(name, char, *)
  PP("the channel topic (0-1024 characters)")
    FIELD_PTR(topic, char, *)
  PP("whether the channel is nsfw")
    FIELD(nsfw, bool, false)
  PP("the id of the last message sent in this channel (may not point to an"
       "existing or valid message)")
    FIELD_SNOWFLAKE(last_message_id)
  PP("the bitrate (in bits) of the voice channel")
    FIELD(bitrate, int, 0)
  PP("the user limit of the voice channel")
    FIELD(user_limit, int, 0)
  PP("amount of seconds a user has to wait before sending another message"
       " (0-21600). bots, as well as users with the permission"
       "`MANAGE_MESSAGES` or `MANAGE_CHANNEL` are unaffected")
    FIELD(rate_limit_per_user, int, 0)
  PP("array of user objects")
    FIELD_STRUCT_PTR(recipients, discord_users, *)
  PP("icon hash of the group DM")
    FIELD_PTR(icon, char, *)
  PP("id of the creator of the group DM or thread")
    FIELD_SNOWFLAKE(owner_id)
  PP("application ID of the group DM creator if its bot-created")
    FIELD_SNOWFLAKE(application_id)
  PP("for guild channels: ID of the parent category for a channel (each"
       "parent category can contain up to 50 channels), for threads: id of"
       "the text channel this thread was created")
    FIELD_SNOWFLAKE(parent_id)
  PP("when the last pinned message was pinned. This may be `NULL` in events"
       "such as `GUILD_CREATE` when a message is not pinned")
    FIELD_TIMESTAMP(last_pin_timestamp)
  PP("voice region ID for the voice channel, automatic when set to null")
    FIELD_PTR(rtc_region, char, *)
  PP("the camera video quality mode of the voice channel, 1 when not present")
    FIELD(voice_quality_mode, int, 0)
  PP("an approximate count of messages in a thread, stops counting at 50")
    FIELD(message_count, int, 0)
  PP("an approximate count of users in a thread, stops counting at 50")
    FIELD(member_count, int, 0)
  PP("thread-specific fields not needed by other channels")
    FIELD_STRUCT_PTR(thread_metadata, discord_thread_metadata, *)
  PP("thread member object for the current user, if they have joined the"
       "thread, only included on certain API endpoints")
    FIELD_STRUCT_PTR(member, discord_thread_member, *)
  PP("default duration that the clients (not the API) will use for newly"
       "created threads, in minutes, to automatically archive the thread"
       "after recent activity, can be set to: 60, 1440, 4320, 10080")
    FIELD(default_auto_archive_duration, int, 0)
  PP("computed permissions for the invoking user in the channel, including"
       "overwrites, only included when part of the `resolved` data received"
       "on a application command interaction")
    FIELD_PTR(permissions, char, *)
STRUCT_END

PUB_LIST(discord_channels)
    LISTTYPE_STRUCT(discord_channel)
LIST_END

PUB_STRUCT(discord_message)
  PP("ID of the message")
    FIELD_SNOWFLAKE(id)
  PP("ID of the channel the message was sent in")
    FIELD_SNOWFLAKE(channel_id)
  PP("ID of the guild the message was sent in")
    FIELD_SNOWFLAKE(guild_id)
  PP("the author of this message (not guaranteed to be a valid user)")
    FIELD_STRUCT_PTR(author, discord_user, *)
  PP("partial guild member")
    FIELD_STRUCT_PTR(member, discord_guild_member, *)
  PP("contents of the message")
    FIELD_PTR(content, char, *)
  PP("when this message was sent")
    FIELD_TIMESTAMP(timestamp)
  PP("when this message was edited (or null if never)")
    FIELD_TIMESTAMP(edited_timestamp)
  PP("whether this was a TTS message")
    FIELD(tts, bool, false)
  PP("whether this message mentions everyone")
    FIELD(mention_everyone, bool, false)
  /** FIXME: expects additional member field */
  PP("users specifically mentioned in the message")
    FIELD_STRUCT_PTR(mentions, discord_users, *)
  PP("roles specifically mentioned in this message")
    FIELD_STRUCT_PTR(mention_roles, discord_roles, *)
  PP("channels specifically mentioned in this message")
    FIELD_STRUCT_PTR(mention_channels, discord_channels, *)
  PP("any attached files")
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  PP("any embedded content")
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  PP("reactions to the message")
    FIELD_STRUCT_PTR(reactions, discord_reactions, *)
  /** FIXME: expects raw json (can be integer or string) */
  PP("used for validating a message was sent")
    FIELD_PTR(nonce, char, *)
  PP("whether this message is pinned")
    FIELD(pinned, bool, false)
  PP("if the message is generated by a webhook, this is the webhook's ID")
    FIELD_SNOWFLAKE(webhook_id)
  PP("type of message")
    FIELD_ENUM(type, discord_message_types)
  PP("sent with Rich Presence-related chat embeds")
    FIELD_STRUCT_PTR(activity, discord_message_activity, *)
  PP("sent with Rich Presence-related chat embeds")
    FIELD_STRUCT_PTR(application, discord_application, *)
  PP("if the message is an interaction or an application-owned webhook, this"
       "is the ID of the application")
    FIELD_SNOWFLAKE(application_id)
  PP("data showing the source of a crosspost, channel follow add, pin, or"
       "reply message")
    FIELD_STRUCT_PTR(message_reference, discord_message_reference, *)
  PP("message flags combined as a bitfield")
    FIELD_ENUM(flags, discord_message_flags)
  PP("the message associated with the message_reference")
    FIELD_STRUCT_PTR(referenced_message, discord_message, *)
  PP("sent if the message is a response to an interaction")
    FIELD_STRUCT_PTR(interaction, discord_message_interaction, *)
  PP("the thread that was started from this message, includes"
       "@ref discord_thread_member")
    FIELD_STRUCT_PTR(thread, discord_channel, *)
  PP("sent if the message contains components like buttons, action rows, or"
       "other interactive components")
    FIELD_STRUCT_PTR(components, discord_components, *)
  PP("sent if the message contains stickers")
    FIELD_STRUCT_PTR(sticker_items, discord_sticker_items, *)
STRUCT_END

PUB_LIST(discord_messages)
    LISTTYPE_STRUCT(discord_message)
LIST_END

STRUCT(discord_message_activity)
  PP("type of message activity")
    FIELD_ENUM(type, discord_message_activity_types)
  PP("party_id from a Rich Presence event")
    FIELD_PTR(party_id, char, *)
STRUCT_END

STRUCT(discord_message_reference)
  PP("id of the originating message")
    FIELD_SNOWFLAKE(message_id)
  PP("id of the originating message's channel")
    FIELD_SNOWFLAKE(channel_id)
  PP("id of the originating message's guild")
    FIELD_SNOWFLAKE(guild_id)
  PP("when sending, whether to error if the referenced message doesn't exist"
       "instead of sending as normal (non-reply) message, default true")
    FIELD(fail_if_not_exists, bool, true)
STRUCT_END

PUB_STRUCT(discord_followed_channel)
  PP("source channel id")
    FIELD_SNOWFLAKE(channel_id)
  PP("created target webhook id")
    FIELD_SNOWFLAKE(webhook_id)
STRUCT_END

STRUCT(discord_reaction)
  PP("times this emoji has been used to react")
    FIELD(count, int, 0)
  PP("whether the current user reacted using this emoji")
    FIELD(me, bool, false)
  PP("emoji information")
    FIELD_STRUCT_PTR(emoji, discord_emoji, *)
STRUCT_END

LIST(discord_reactions)
    LISTTYPE_STRUCT(discord_reaction)
LIST_END

STRUCT(discord_overwrite)
  PP("role or user id")
    FIELD_SNOWFLAKE(id)
  PP("either 0 (role) or 1 (member)")
    FIELD(type, int, 0)
  PP("permission bit set")
    FIELD_SNOWFLAKE(allow)
  PP("permission bit set")
    FIELD_SNOWFLAKE(deny)
STRUCT_END

LIST(discord_overwrites)
    LISTTYPE_STRUCT(discord_overwrite)
LIST_END

STRUCT(discord_thread_metadata)
  PP("whether the thread is archived")
    FIELD(archived, bool, false)
  PP("duration in minutes to automatically archive the thread after recent"
       "activity, can be set to: 60, 1440, 3320, 10080")
    FIELD(auto_archive_duration, int, 0)
  PP("timestamp when the thread's archive status was last changed, used for"
       "calculating recent activity")
    FIELD_TIMESTAMP(archive_timestamp)
  PP("whether the thread is locked; when a thread is locked only users with"
       "`MANAGE_THREADS` can unarchive it")
    FIELD(locked, bool, false)
  PP("whether non-moderators cana dd other non-moderators to a thread; only"
       "available on private threads")
    FIELD(invitable, bool, false)
  PP("timestamp when the thread was created; only populated for threads"
       "created after 2022-01-09")
    FIELD_TIMESTAMP(create_timestamp)
STRUCT_END

STRUCT(discord_thread_member)
  PP("the id of the thread")
    FIELD_SNOWFLAKE(id)
  PP("the id of the user")
    FIELD_SNOWFLAKE(user_id)
  PP("the time the current user last joined the thread")
    FIELD_TIMESTAMP(join_timestamp)
  PP("any user-thread settings, currently only used for notifications")
    FIELD(flags, int, 0)
STRUCT_END

PUB_LIST(discord_thread_members)
    LISTTYPE_STRUCT(discord_thread_member)
LIST_END

STRUCT(discord_attachment)
  /* FIXME: content shouldn't be included at from_json and to_json */
  PP("the file contents")
    FIELD_PTR(content, char, *)
  PP("attachment ID")
    FIELD_SNOWFLAKE(id)
  PP("name of file attached")
  COND_WRITE(this->filename != NULL)
    FIELD_PTR(filename, char, *)
  COND_END
  PP("description for the file")
  COND_WRITE(this->description != NULL)
    FIELD_PTR(description, char, *)
  COND_END
  PP("the attachment media type")
  COND_WRITE(this->content_type != NULL)
    FIELD_PTR(content_type, char, *)
  COND_END
  /* TODO: make it size_t */
  PP("size of file in bytes")
    FIELD(size, int, 0)
  PP("source url of file")
    FIELD_PTR(url, char, *)
  PP("proxied url of file")
    FIELD_PTR(proxy_url, char, *)
  PP("height of file (if image)")
  COND_WRITE(this->height != 0)
    FIELD(height, int, 0)
  COND_END
  PP("width of file (if image)")
  COND_WRITE(this->width != 0)
    FIELD(width, int, 0)
  COND_END
  PP("whether this attachment is ephemeral")
    FIELD(ephemeral, bool, false)
STRUCT_END

PUB_LIST(discord_attachments)
    LISTTYPE_STRUCT(discord_attachment)
LIST_END

PUB_STRUCT(discord_embed)
  PP("title of embed")
    FIELD_PTR(title, char, *)
  PP("type of embed (always \"rich\" for webhook embeds)")
    FIELD_PTR(type, char, *)
  PP("description of embed")
    FIELD_PTR(description, char, *)
  PP("url of embed")
    FIELD_PTR(url, char, *)
  PP("timestamp of embed content")
    FIELD_TIMESTAMP(timestamp)
  PP("color code of the embed")
  COND_WRITE(this->color != 0)
    FIELD(color, int, 0)
  COND_END
  PP("footer information")
  COND_WRITE(this->footer != NULL)
    FIELD_STRUCT_PTR(footer, discord_embed_footer, *)
  COND_END
  PP("image information")
  COND_WRITE(this->image != NULL)
    FIELD_STRUCT_PTR(image, discord_embed_image, *)
  COND_END
  PP("thumbnail information")
  COND_WRITE(this->thumbnail != NULL)
    FIELD_STRUCT_PTR(thumbnail, discord_embed_thumbnail, *)
  COND_END
  PP("video information")
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

PUB_LIST(discord_embeds)
    LISTTYPE_STRUCT(discord_embed)
LIST_END

PUB_STRUCT(discord_embed_thumbnail)
  PP("source url of thumbnail (only supports http(s) and attachments)")
    FIELD_PTR(url, char, *)
  PP("a proxied url of the thumbnail")
  COND_WRITE(this->proxy_url != NULL)
    FIELD_PTR(proxy_url, char, *)
  COND_END
  PP("height of thumbnail")
  COND_WRITE(this->height != 0)
    FIELD(height, int, 0)
  COND_END
  PP("width of thumbnail")
  COND_WRITE(this->width != 0)
    FIELD(width, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_video)
  PP("source url of video")
  COND_WRITE(this->url != NULL)
    FIELD_PTR(url, char, *)
  COND_END
  PP("a proxied url of the video")
  COND_WRITE(this->proxy_url != NULL)
    FIELD_PTR(proxy_url, char, *)
  COND_END
  PP("height of video")
  COND_WRITE(this->height != 0)
    FIELD(height, int, 0)
  COND_END
  PP("width of video")
  COND_WRITE(this->width != 0)
    FIELD(width, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_image)
  PP("source url of image (only supports http(s) and attachments)")
    FIELD_PTR(url, char, *)
  PP("a proxied url of the image")
  COND_WRITE(this->proxy_url != NULL)
    FIELD_PTR(proxy_url, char, *)
  COND_END
  PP("height of image")
  COND_WRITE(this->height != 0)
    FIELD(height, int, 0)
  COND_END
  PP("width of image")
  COND_WRITE(this->width != 0)
    FIELD(width, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_provider)
  PP("name of provider")
  COND_WRITE(this->name != NULL)
    FIELD_PTR(name, char, *)
  COND_END
  PP("url of provider")
  COND_WRITE(this->url != NULL)
    FIELD_PTR(url, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_author)
  PP("name of author")
    FIELD_PTR(name, char, *)
  PP("url of author")
  COND_WRITE(this->url != NULL)
    FIELD_PTR(url, char, *)
  COND_END
  PP("url of author icon (only supports http(s) and attachments)")
  COND_WRITE(this->icon_url != NULL)
    FIELD_PTR(icon_url, char, *)
  COND_END
  PP("a proxied url of author icon")
  COND_WRITE(this->proxy_icon_url != NULL)
    FIELD_PTR(proxy_icon_url, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_footer)
  PP("footer text")
    FIELD_PTR(text, char, *)
  PP("url of footer icon (only supports http(s) and attachments)")
  COND_WRITE(this->icon_url != NULL)
    FIELD_PTR(icon_url, char, *)
  COND_END
  PP("a proxied url of footer icon")
  COND_WRITE(this->proxy_icon_url != NULL)
    FIELD_PTR(proxy_icon_url, char, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_embed_field)
  PP("name of the field")
    FIELD_PTR(name, char, *)
  PP("value of the field")
    FIELD_PTR(value, char, *)
  PP("whether or not this field should display inline")
    FIELD_CUSTOM(Inline, "inline", bool, DECOR_BLANK, INIT_BLANK, CLEANUP_BLANK,
                 JSON_ENCODER_bool, JSON_DECODER_bool, false)
STRUCT_END

PUB_LIST(discord_embed_fields)
    LISTTYPE_STRUCT(discord_embed_field)
LIST_END

STRUCT(discord_channel_mention)
  PP("ID of the channel")
    FIELD_SNOWFLAKE(id)
  PP("ID of the guild containing the channel")
    FIELD_SNOWFLAKE(guild_id)
  PP("the type of the channel")
    FIELD_ENUM(type, discord_channel_types)
  PP("the name of the channel")
    FIELD_PTR(name, char, *)
STRUCT_END

STRUCT(discord_allowed_mention)
  PP("An array of allowed mention tpes to parse from the content")
    FIELD_STRUCT_PTR(parse, strings, *)
  PP("Array of role_ids to mention (Max size of 100)")
    FIELD_STRUCT_PTR(roles, snowflakes, *)
  PP("Array of user_ids to mention (Max size of 100)")
    FIELD_STRUCT_PTR(users, snowflakes, *)
  PP("For replies, whether to mention the author of the message being"
       "replied to (default false)")
    FIELD(replied_user, bool, false)
STRUCT_END

PUB_STRUCT(discord_thread_response_body)
  PP("the archived threads")
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  PP("a thread member object for each returned thread the current user has"
       "joined")
    FIELD_STRUCT_PTR(members, discord_thread_members, *)
  PP("whether there are potentially additional threads that could be returned"
       "on a subsequent call")
    FIELD(has_more, bool, false)
STRUCT_END

/*****************************************************************************
 * Channel REST parameters
 * **************************************************************************/

PUB_STRUCT(discord_modify_channel)
  PP("1-100 character channel name")
    FIELD_PTR(name, char, *)
  /* GROUP DM */
  /* TODO: implement base64 encoder */
#if 0
  PP("base64 encoded icon")
    FIELD_PTR(icon, char, *)
#endif
  /* GUILD CHANNEL */
  PP("the type of channel; only conversion between text and news is"
       "supported and only in guilds with the `NEWS` feature")
    FIELD_ENUM(type, discord_channel_types)
  PP("the position of the channel in the left-hand listing")
  COND_WRITE(this->position != 0)
    FIELD(position, int, 0)
  COND_END
  PP("0-1024 character channel topic")
    FIELD_PTR(topic, char, *)
  PP("whether the channel is nsfw")
    FIELD(nsfw, bool, false)
  PP("amount of seconds a user has to wait before sending another message"
       "(0-21600); bots, as well as users with the permission"
       "`MANAGE_MESSAGES` or `MANAGE_CHANNEL`, are unaffected")
  COND_WRITE(this->rate_limit_per_user != 0)
    FIELD(rate_limit_per_user, int, 0)
  COND_END
  PP("the user limit of the voice channel; 0 refers to no limit, 1 to 99"
       "refers to a user limit")
  COND_WRITE(this->user_limit != 0)
    FIELD(user_limit, int, 0)
  COND_END
  PP("channel or category-specific permissions")
  COND_WRITE(this->permission_overwrites != NULL)
    FIELD_STRUCT_PTR(permission_overwrites, discord_overwrites, *)
  COND_END
  PP("ID of the new parent category for a channel")
  COND_WRITE(this->parent_id != 0)
    FIELD_SNOWFLAKE(parent_id)
  COND_END
  PP("channel voice region id, automatic when set to NULL")
    FIELD_PTR(rtc_region, char, *)
  PP("the camera video quality mode of the voice channel")
  COND_WRITE(this->video_quality_mode != 0)
    FIELD(video_quality_mode, int, 0)
  COND_END
  PP("the default duration that the clients use (not the API) for newly"
       "created threads in the channel, in minutes, to automatically archive"
       "the thread after recent activity")
  COND_WRITE(this->default_auto_archive_duration != 0)
    FIELD(default_auto_archive_duration, int, 0)
  COND_END
  /* THREAD */
  PP("whether the thread is archived")
    FIELD(archived, bool, false)
  PP("duration in minutes to automatically arhived the thread after recent"
       "activity, can be set to: 60, 1440, 4320, 10080")
  COND_WRITE(this->auto_archive_duration != 0)
    FIELD(auto_archive_duration, int, 0)
  COND_END
  PP("whether the thread is locked; when a thread is locked, only users with"
       "`MANAGE_THREADS` can unarchive it")
    FIELD(locked, bool, false)
  PP("whether non-moderators can add other non-moderators to a thread; only"
       "available on private threads")
    FIELD(invitable, bool, false)
STRUCT_END

/* FIXME: shouldn't generate JSON functions */
/* TODO: to_query encoding */
PUB_STRUCT(discord_get_channel_messages)
  PP("get messages around this message ID")
  COND_WRITE(this->around != 0)
    FIELD_SNOWFLAKE(around)
  COND_END
  PP("get messages before this message ID")
  COND_WRITE(this->before != 0)
    FIELD_SNOWFLAKE(before)
  COND_END
  PP("get messages after this message ID")
  COND_WRITE(this->after != 0)
    FIELD_SNOWFLAKE(after)
  COND_END
  PP("max number of messages to return (1-100)")
  COND_WRITE(this->limit != 0)
    FIELD(limit, int, 50)
  COND_END
STRUCT_END

PUB_STRUCT(discord_create_message)
  PP("the message contents (up to 2000 characters)")
    FIELD_PTR(content, char, *)
  PP("true if this is a TTS message")
    FIELD(tts, bool, false)
  PP("embedded `rich` content (up to 6000 characters)")
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  PP("allowed mentions for the message")
  COND_WRITE(this->allowed_mentions != NULL)
    FIELD_STRUCT_PTR(allowed_mentions, discord_allowed_mention, *)
  COND_END
  PP("include to make your message a reply")
  COND_WRITE(this->message_reference != NULL)
    FIELD_STRUCT_PTR(message_reference, discord_message_reference, *)
  COND_END
  PP("the components to include with the message")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  PP("IDs of up to 3 stickers in the server to send in the message")
  COND_WRITE(this->sticker_ids != NULL)
    FIELD_STRUCT_PTR(sticker_ids, snowflakes, *)
  COND_END
  PP("attachment objects with filename and description")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
  PP("message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be"
       "set")
  COND_WRITE(this->flags != 0)
    FIELD_ENUM(flags, discord_message_flags)
  COND_END
STRUCT_END

/* FIXME: shouldn't generate JSON functions */
/* TODO: to_query encoding */
PUB_STRUCT(discord_get_reactions)
  PP("get users after this user ID")
  COND_WRITE(this->after != 0)
    FIELD_SNOWFLAKE(after)
  COND_END
  PP("max number of users to return (1-100)")
  COND_WRITE(this->limit != 0)
    FIELD(limit, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_edit_message)
  PP("the message contents (up to 2000 characters)")
    FIELD_PTR(content, char, *)
  PP("embedded `rich` content (up to 6000 characters)")
    FIELD_STRUCT_PTR(embeds, discord_embeds, *)
  PP("message flags combined as a bitfield (only `SUPPRESS_EMBEDS` can be"
       "set")
  COND_WRITE(this->flags != 0)
    FIELD_ENUM(flags, discord_message_flags)
  COND_END
  PP("allowed mentions for the message")
  COND_WRITE(this->allowed_mentions != NULL)
    FIELD_STRUCT_PTR(allowed_mentions, discord_allowed_mention, *)
  COND_END
  PP("the components to include with the message")
  COND_WRITE(this->components != NULL)
    FIELD_STRUCT_PTR(components, discord_components, *)
  COND_END
  PP("attachment objects with filename and description")
  COND_WRITE(this->attachments != NULL)
    FIELD_STRUCT_PTR(attachments, discord_attachments, *)
  COND_END
STRUCT_END

PUB_STRUCT(discord_bulk_delete_messages)
  PP("an array of message ids to delete (2-100)")
    FIELD_STRUCT_PTR(messages, snowflakes, *)
STRUCT_END

PUB_STRUCT(discord_edit_channel_permissions)
  PP("the bitwise value of all allowed permissions (default \"0\")")
  COND_WRITE(this->allow != 0)
    FIELD_PRINTF(allow, u64bitmask, "%" PRIu64, "%" SCNu64)
  COND_END
  PP("the bitwise value of all disallowed permissions (default \"0\")")
  COND_WRITE(this->deny != 0)
    FIELD_PRINTF(deny, u64bitmask, "%" PRIu64, "%" SCNu64)
  COND_END
  PP("0 for a role or 1 for a member")
    FIELD(type, int, 0)
STRUCT_END

PUB_STRUCT(discord_create_channel_invite)
  PP("duration of invite in seconds before expiry, or 0 for never. between"
       "0 and 604800 (7 days)")
  COND_WRITE(this->max_age != 0)
    FIELD(max_age, int, 86400)
  COND_END
  PP("max number of uses or 0 for unlimited. betwee 0 and 100")
  COND_WRITE(this->max_uses != 0)
    FIELD(max_uses, int, 0)
  COND_END
  PP("whether this invite only grants temporary membership")
  COND_WRITE(this->temporary != 0)
    FIELD(temporary, bool, false)
  COND_END
  PP("if true, don't true to reuse a similar invite (useful for creating"
       "many unique one time use invites)")
  COND_WRITE(this->unique != 0)
    FIELD(unique, bool, false)
  COND_END
  PP("the type of target for this voice channel invite")
  COND_WRITE(this->target_type != 0)
    FIELD_ENUM(target_type, discord_invite_target_types)
  COND_END
  PP("the id of the user whose stream to display for this invite, required"
       "if `target_type` is 1, the user must be streaming in the channel")
  COND_WRITE(this->target_user_id != 0)
    FIELD_SNOWFLAKE(target_user_id)
  COND_END
  PP("the id of the embedded application to open for this invite, required"
       "if `target_type` is 2, the application must have the `EMBEDDED` flag")
  COND_WRITE(this->target_application_id != 0)
    FIELD_SNOWFLAKE(target_application_id)
  COND_END
STRUCT_END

PUB_STRUCT(discord_follow_news_channel)
  PP("id of target channel")
  COND_WRITE(this->webhook_channel_id != 0)
    FIELD_SNOWFLAKE(webhook_channel_id)
  COND_END
STRUCT_END

PUB_STRUCT(discord_group_dm_add_recipient)
  PP("access token of a user that has granted your app the `gdm.join` scope")
    FIELD_PTR(access_token, char, *)
  PP("nickname of the user being added")
    FIELD_PTR(nick, char, *)
STRUCT_END

PUB_STRUCT(discord_start_thread_with_message)
  PP("1-100 character channel name")
    FIELD_PTR(name, char, *)
  PP("duration in minutes to automatically archive the thread after recent"
       "activity, can be set to: 60, 1440, 4320, 10080")
  COND_WRITE(this->auto_archive_duration != 0)
    FIELD(auto_archive_duration, int, 0)
  COND_END
  PP("amount of seconds a user has to wait before sending another message"
       "(0-21600)")
  COND_WRITE(this->rate_limit_per_user >= 0
             && this->rate_limit_per_user <= 21600)
    FIELD(rate_limit_per_user, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_start_thread_without_message)
  PP("1-100 character channel name")
    FIELD_PTR(name, char, *)
  PP("duration in minutes to automatically archive the thread after recent"
       "activity, can be set to: 60, 1440, 4320, 10080")
  COND_WRITE(this->auto_archive_duration != 0)
    FIELD(auto_archive_duration, int, 0)
  COND_END
  PP("the type of thread to create")
    FIELD_ENUM(type, discord_channel_types)
  PP("whether non-moderators can add other non-moderators to a thread; only"
       "available when creating a private thread")
    FIELD(invitable, bool, false)
  PP("amount of seconds a user has to wait before sending another message"
       "(0-21600)")
  COND_WRITE(this->rate_limit_per_user >= 0
             && this->rate_limit_per_user <= 21600)
    FIELD(rate_limit_per_user, int, 0)
  COND_END
STRUCT_END

PUB_STRUCT(discord_list_active_threads)
  PP("the active threads")
  COND_WRITE(this->threads != NULL)
    FIELD_STRUCT_PTR(threads, discord_channels, *)
  COND_END
  PP("a thread member object for each returned thread the current user has"
       "joined")
  COND_WRITE(this->members != NULL)
    FIELD_STRUCT_PTR(members, discord_thread_members, *)
  COND_END
  PP("whether there are potentially additional threads that could be returned"
       "on a subsequent call")
    FIELD(has_more, bool, false)
STRUCT_END
