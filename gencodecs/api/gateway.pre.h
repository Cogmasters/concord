/*****************************************************************************
 * Gateway Datatypes
 * **************************************************************************/

PP_DEFINE(DISCORD_GATEWAY_GUILDS 1 << 0)
PP_DEFINE(DISCORD_GATEWAY_GUILD_MEMBERS 1 << 1)
PP_DEFINE(DISCORD_GATEWAY_GUILD_BANS 1 << 2)
PP_DEFINE(DISCORD_GATEWAY_GUILD_EMOJIS 1 << 3)
PP_DEFINE(DISCORD_GATEWAY_GUILD_INTEGRATIONS 1 << 4)
PP_DEFINE(DISCORD_GATEWAY_GUILD_WEBHOOKS 1 << 5)
PP_DEFINE(DISCORD_GATEWAY_GUILD_INVITES 1 << 6)
PP_DEFINE(DISCORD_GATEWAY_GUILD_VOICE_STATES 1 << 7)
PP_DEFINE(DISCORD_GATEWAY_GUILD_PRESENCES 1 << 8)
PP_DEFINE(DISCORD_GATEWAY_GUILD_MESSAGES 1 << 9)
PP_DEFINE(DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS 1 << 10)
PP_DEFINE(DISCORD_GATEWAY_GUILD_MESSAGE_TYPING 1 << 11)
PP_DEFINE(DISCORD_GATEWAY_DIRECT_MESSAGES 1 << 12)
PP_DEFINE(DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS 1 << 13)
PP_DEFINE(DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING 1 << 14)

PP_DEFINE(DISCORD_ACTIVITY_INSTANCE 1 << 0)
PP_DEFINE(DISCORD_ACTIVITY_JOIN 1 << 1)
PP_DEFINE(DISCORD_ACTIVITY_SPECTATE 1 << 2)
PP_DEFINE(DISCORD_ACTIVITY_JOIN_REQUEST 1 << 3)
PP_DEFINE(DISCORD_ACTIVITY_SYNC 1 << 4)
PP_DEFINE(DISCORD_ACTIVITY_PLAY 1 << 5)
PP_DEFINE(DISCORD_ACTIVITY_PARTY_PRIVACY_FRIENDS 1 << 6)
PP_DEFINE(DISCORD_ACTIVITY_PARTY_PRIVACY_VOICE_CHANNEL 1 << 7)
PP_DEFINE(DISCORD_ACTIVITY_EMBEDDED 1 << 8)

ENUM(discord_gateway_close_opcodes)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR, = 4000)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE, = 4001)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR, = 4002)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED, = 4003)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED, = 4004)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED, = 4005)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE, = 4007)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED, = 4008)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT, = 4009)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD, = 4010)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED, = 4011)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION, = 4012)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS, = 4013)
    ENUMERATOR(DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS, = 4014)
    ENUMERATOR_LAST(DISCORD_GATEWAY_CLOSE_REASON_RECONNECT, = 4900)
ENUM_END

ENUM(discord_gateway_opcodes)
    ENUMERATOR(DISCORD_GATEWAY_DISPATCH, = 0)
    ENUMERATOR(DISCORD_GATEWAY_HEARTBEAT, = 1)
    ENUMERATOR(DISCORD_GATEWAY_IDENTIFY, = 2)
    ENUMERATOR(DISCORD_GATEWAY_PRESENCE_UPDATE, = 3)
    ENUMERATOR(DISCORD_GATEWAY_VOICE_STATE_UPDATE, = 4)
    ENUMERATOR(DISCORD_GATEWAY_RESUME, = 6)
    ENUMERATOR(DISCORD_GATEWAY_RECONNECT, = 7)
    ENUMERATOR(DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS, = 8)
    ENUMERATOR(DISCORD_GATEWAY_INVALID_SESSION, = 9)
    ENUMERATOR(DISCORD_GATEWAY_HELLO, = 10)
    ENUMERATOR_LAST(DISCORD_GATEWAY_HEARTBEAT_ACK, = 11)
ENUM_END

ENUM(discord_gateway_events)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_NONE, = 0)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_READY, = 1)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_RESUMED, = 2)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_CREATE, = 3)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_UPDATE, = 4)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_APPLICATION_COMMAND_DELETE, = 5)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE, = 6)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE, = 7)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE, = 8)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE, = 9)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_THREAD_CREATE, = 10)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_THREAD_UPDATE, = 11)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_THREAD_DELETE, = 12)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_THREAD_LIST_SYNC, = 13)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_THREAD_MEMBER_UPDATE, = 14)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_THREAD_MEMBERS_UPDATE, = 15)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_CREATE, = 16)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_UPDATE, = 17)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_DELETE, = 18)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD, = 19)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE, = 20)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE, = 21)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_STICKERS_UPDATE, = 22)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE, = 23)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD, = 24)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE, = 25)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE, = 26)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_MEMBERS_CHUNK, = 27)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE, = 28)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE, = 29)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE, = 30)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_INTEGRATION_CREATE, = 31)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_INTEGRATION_UPDATE, = 32)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_INTEGRATION_DELETE, = 33)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_INTERACTION_CREATE, = 34)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_INVITE_CREATE, = 35)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_INVITE_DELETE, = 36)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE, = 37)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE, = 38)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE, = 39)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK, = 40)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD, = 41)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE, = 42)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL, = 43)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI, = 44)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE, = 45)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_CREATE, = 46)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_DELETE, = 47)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_STAGE_INSTANCE_UPDATE, = 48)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_TYPING_START, = 49)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_USER_UPDATE, = 50)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE, = 51)
    ENUMERATOR(DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE, = 52)
    ENUMERATOR_LAST(DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE, = 53)
ENUM_END

ENUM(discord_activity_types)
  /** Format: \"Playing {name}\" */
    ENUMERATOR(DISCORD_ACTIVITY_GAME, = 0)
  /** Format: \"Streaming {details}\" */
    ENUMERATOR(DISCORD_ACTIVITY_STREAMING, = 1)
  /** Format: \"Listening to {name}\" */
    ENUMERATOR(DISCORD_ACTIVITY_LISTENING, = 2)
  /** Format: \"Watching {name}\" */
    ENUMERATOR(DISCORD_ACTIVITY_WATCHING, = 3)
  /** Format: \"{emoji} {name}\" */
    ENUMERATOR(DISCORD_ACTIVITY_CUSTOM, = 4)
  /** Format: \"Competing in {name}\" */
    ENUMERATOR_LAST(DISCORD_ACTIVITY_COMPETING, = 5)
ENUM_END

/** @CCORD_pub_struct{discord_identify} */
PUB_STRUCT(discord_identify)
  /** authentication token */
    FIELD_PTR(token, char, *)
  /** connection properties */
    FIELD_STRUCT_PTR(properties, discord_identify_connection, *)
  /** whether this connection supports compression packets */
    FIELD(compress, bool, false)
  /** value between 50 and 250, total number of members where the gateway
       will stop sending offline members in the guild member list */
    FIELD(large_threshold, int, 50)
#if 0
  /** array of two integers (shard_id, num_shards) */
    FIELD_STRUCT_PTR(shard, integers, *)
#endif
  /** presence structure for initial presence information */
    FIELD_STRUCT_PTR(presence, discord_presence_update, *)
  /** the gateway intents you wish to receive */
    FIELD_BITMASK(intents)
STRUCT_END

STRUCT(discord_identify_connection)
  /** your operating system */
    FIELD_CUSTOM(os, "$os", char, *, INIT_BLANK, CLEANUP_PTR,
                 GENCODECS_JSON_ENCODER_PTR_char, 
                 GENCODECS_JSON_DECODER_PTR_char, NULL)
  /** your library name */
    FIELD_CUSTOM(browser, "$browser", char, *, INIT_BLANK, CLEANUP_PTR,
                 GENCODECS_JSON_ENCODER_PTR_char,
                 GENCODECS_JSON_DECODER_PTR_char, NULL)
  /** your library name */
    FIELD_CUSTOM(device, "$device", char, *, INIT_BLANK, CLEANUP_PTR,
                 GENCODECS_JSON_ENCODER_PTR_char,
                 GENCODECS_JSON_DECODER_PTR_char, NULL)
STRUCT_END

/** @CCORD_pub_struct{discord_voice_state_status} */
PUB_STRUCT(discord_voice_state_status)
  /** ID of the guild */
    FIELD_SNOWFLAKE(guild_id)
  /** ID of the voice channel client wants to join (null if disconnecting) */
    FIELD_SNOWFLAKE(channel_id)
  /** is the client muted */
    FIELD(self_mute, bool, false)
  /** is the client deafened */
    FIELD(self_deaf, bool, false)
STRUCT_END

/** @CCORD_pub_struct{discord_presence_update} */
PUB_STRUCT(discord_presence_update)
  /** unix time (in milliseconds) of when the client went idle, or null if
       the client is not idle */
    FIELD_TIMESTAMP(since)
  /** the user's activities */
    FIELD_STRUCT_PTR(activities, discord_activities, *)
  /** the user's new status */
    FIELD_PTR(status, char, *)
  /** whether or not the client is afk */
    FIELD(afk, bool, false)
STRUCT_END

LIST(discord_presence_updates)
    LISTTYPE_STRUCT(discord_presence_update)
LIST_END

STRUCT(discord_activity)
  /** the activity's name */
  COND_WRITE(this->name != NULL)
    FIELD_PTR(name, char, *)
  COND_END
  /** activity type */
    FIELD_ENUM(type, discord_activity_types)
  /** stream url, is validated when type is 1 */
  COND_WRITE(this->url != NULL)
    FIELD_PTR(url, char, *)
  COND_END
  /** unix timestamp (in milliseconds)of when the activity was added to the
       user's session */
  COND_WRITE(this->created_at != 0)
    FIELD_TIMESTAMP(created_at)
  COND_END
  /** unix timestamps for start and/or end of the game */
  COND_WRITE(this->timestamps != NULL)
    FIELD_STRUCT_PTR(timestamps, discord_activity_timestamps, *)
  COND_END
  /** application ID for the game */
  COND_WRITE(this->application_id != 0)
    FIELD_SNOWFLAKE(application_id)
  COND_END
  /** what the player is currently doing */
  COND_WRITE(this->details != NULL)
    FIELD_PTR(details, char, *)
  COND_END
  /** the user's current party status */
  COND_WRITE(this->state != NULL)
    FIELD_PTR(state, char, *)
  COND_END
  /** the emoji used for a custom status */
  COND_WRITE(this->emoji != NULL)
    FIELD_STRUCT_PTR(emoji, discord_activity_emoji, *)
  COND_END
  /** information for the current party of the player */
  COND_WRITE(this->party != NULL)
    FIELD_STRUCT_PTR(party, discord_activity_party, *)
  COND_END
  /** images for the presence and their hover texts */
  COND_WRITE(this->assets != NULL)
    FIELD_STRUCT_PTR(assets, discord_activity_assets, *)
  COND_END
  /** secrets for Rich Presence joining and spectating */
  COND_WRITE(this->secrets != NULL)
    FIELD_STRUCT_PTR(secrets, discord_activity_secrets, *)
  COND_END
  /** whether or not the activity is an instanced game session */
    FIELD(instance, bool, false)
  /** activity flags bitwise mask, describes what they payload includes */
    FIELD_SNOWFLAKE(flags)
  /** the custom buttons shown in the Rich Presence (max 2) */
  COND_WRITE(this->buttons != NULL)
    FIELD_STRUCT_PTR(buttons, discord_activity_buttons, *)
  COND_END
STRUCT_END

LIST(discord_activities)
    LISTTYPE_STRUCT(discord_activity)
LIST_END

STRUCT(discord_activity_timestamps)
  /** unix timestamp (in milliseconds)of when the activity started */
    FIELD_TIMESTAMP(start)
  /** unix timestamp (in milliseconds)of when the activity ends */
    FIELD_TIMESTAMP(end)
STRUCT_END

STRUCT(discord_activity_emoji)
  /** the name of the emoji */
    FIELD_PTR(name, char, *)
  /** the ID of the emoji */
  COND_WRITE(this->id != 0)
    FIELD_SNOWFLAKE(id)
  COND_END
  /** whether this emoji is animated */
    FIELD(animated, bool, false)
STRUCT_END

STRUCT(discord_activity_party)
  /** the ID of the party */
    FIELD_PTR(id, char, *)
  /** used to show the party's current and maximum size @note array of two
       integers (current_size, max_size) */
    FIELD_STRUCT_PTR(size, integers, *)
STRUCT_END

STRUCT(discord_activity_assets)
  /** activity large asset image */
    FIELD_PTR(large_image, char, *)
  /** text displayed when hovering over the large image of the activity */
    FIELD_PTR(large_text, char, *)
  /** activity small asset image */
    FIELD_PTR(small_image, char, *)
  /** text displayed when hovering over the small image of the activity */
    FIELD_PTR(small_text, char, *)
STRUCT_END

STRUCT(discord_activity_secrets)
  /** the secret for joining a party */
    FIELD_PTR(join, char, *)
  /** the secret for spectating a game */
    FIELD_PTR(spectate, char, *)
  /** the secret for a specific instanced match */
    FIELD_PTR(match, char, *)
STRUCT_END

STRUCT(discord_activity_button)
  /** the text shown on the button (1-32 characters) */
    FIELD_PTR(label, char, *)
  /** the url opened when clicking the button (1-512 characters) */
    FIELD_PTR(url, char, *)
STRUCT_END

LIST(discord_activity_buttons)
    LISTTYPE_STRUCT(discord_activity_button)
LIST_END

/** @CCORD_pub_struct{discord_session_start_limit} */
PUB_STRUCT(discord_session_start_limit)
  /** the total number of session starts the current user is allowed */
    FIELD(total, int, 0)
  /** the remaining number of session starts the current user is allowed */
    FIELD(remaining, int, 0)
  /** the number of milliseconds after which the limit resets */
    FIELD(reset_after, int, 0)
  /** the number of identify requests allowed per 5 seconds */
    FIELD(max_concurrency, int, 0)
STRUCT_END
