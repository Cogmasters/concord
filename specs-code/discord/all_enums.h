/* This file is generated from specs/discord/audit_log.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/audit-log
 */

/* This file is generated from specs/discord/audit_log.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/audit-log
 */



enum discord_audit_log_events {
  DISCORD_AUDIT_LOG_GUILD_UPDATE = 1,
  DISCORD_AUDIT_LOG_CHANNEL_CREATE = 10,
  DISCORD_AUDIT_LOG_CHANNEL_UPDATE = 11,
  DISCORD_AUDIT_LOG_CHANNEL_DELETE = 12,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_CREATE = 13,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_UPDATE = 14,
  DISCORD_AUDIT_LOG_CHANNEL_OVERWRITE_DELETE = 15,
  DISCORD_AUDIT_LOG_MEMBER_KICK = 20,
  DISCORD_AUDIT_LOG_MEMBER_PRUNE = 21,
  DISCORD_AUDIT_LOG_MEMBER_BAN_ADD = 22,
  DISCORD_AUDIT_LOG_MEMBER_BAN_REMOVE = 23,
  DISCORD_AUDIT_LOG_MEMBER_UPDATE = 24,
  DISCORD_AUDIT_LOG_MEMBER_ROLE_UPDATE = 25,
  DISCORD_AUDIT_LOG_MEMBER_MOVE = 26,
  DISCORD_AUDIT_LOG_MEMBER_DISCONNECT = 27,
  DISCORD_AUDIT_LOG_BOT_ADD = 28,
  DISCORD_AUDIT_LOG_ROLE_CREATE = 30,
  DISCORD_AUDIT_LOG_ROLE_UPDATE = 31,
  DISCORD_AUDIT_LOG_ROLE_DELETE = 32,
  DISCORD_AUDIT_LOG_INVITE_CREATE = 40,
  DISCORD_AUDIT_LOG_INVITE_DELETE = 42,
  DISCORD_AUDIT_LOG_WEBHOOK_CREATE = 50,
  DISCORD_AUDIT_LOG_WEBHOOK_UPDATE = 51,
  DISCORD_AUDIT_LOG_WEBHOOK_DELETE = 52,
  DISCORD_AUDIT_LOG_EMOJI_CREATE = 60,
  DISCORD_AUDIT_LOG_EMOJI_UPDATE = 61,
  DISCORD_AUDIT_LOG_EMOJI_DELETE = 62,
  DISCORD_AUDIT_LOG_MESSAGE_DELETE = 72,
  DISCORD_AUDIT_LOG_MESSAGE_BULK_DELETE = 73,
  DISCORD_AUDIT_LOG_MESSAGE_PIN = 74,
  DISCORD_AUDIT_LOG_MESSAGE_UNPIN = 75,
  DISCORD_AUDIT_LOG_INTEGRATION_CREATE = 80,
  DISCORD_AUDIT_LOG_INTEGRATION_UPDATE = 81,
  DISCORD_AUDIT_LOG_INTEGRATION_DELETE = 82,
};
extern char* discord_audit_log_events_to_string(enum discord_audit_log_events);
extern enum discord_audit_log_events discord_audit_log_events_from_string(char*);
extern bool discord_audit_log_events_has(enum discord_audit_log_events, char*);
/* This file is generated from specs/discord/channel.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */

/* This file is generated from specs/discord/channel.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/channel
 */



enum discord_channel_types {
  DISCORD_CHANNEL_GUILD_TEXT = 0,
  DISCORD_CHANNEL_DM = 1,
  DISCORD_CHANNEL_GUILD_VOICE = 2,
  DISCORD_CHANNEL_GROUP_DM = 3,
  DISCORD_CHANNEL_GUILD_CATEGORY = 4,
  DISCORD_CHANNEL_GUILD_NEWS = 5,
  DISCORD_CHANNEL_GUILD_STORE = 6,
  DISCORD_CHANNEL_GUILD_NEWS_THREAD = 10,
  DISCORD_CHANNEL_GUILD_PUBLIC_THREAD = 11,
  DISCORD_CHANNEL_GUILD_PRIVATE_THREAD = 12,
  DISCORD_CHANNEL_GUILD_STAGE_VOICE = 13,
};
extern char* discord_channel_types_to_string(enum discord_channel_types);
extern enum discord_channel_types discord_channel_types_from_string(char*);
extern bool discord_channel_types_has(enum discord_channel_types, char*);


enum discord_message_sticker_format_types {
  DISCORD_MESSAGE_STICKER_PNG = 1,
  DISCORD_MESSAGE_STICKER_APNG = 2,
  DISCORD_MESSAGE_STICKER_LOTTIE = 3,
};
extern char* discord_message_sticker_format_types_to_string(enum discord_message_sticker_format_types);
extern enum discord_message_sticker_format_types discord_message_sticker_format_types_from_string(char*);
extern bool discord_message_sticker_format_types_has(enum discord_message_sticker_format_types, char*);


enum discord_message_flags {
  DISCORD_MESSAGE_CROSSPOSTED = 1, // 1<<0
  DISCORD_MESSAGE_IS_CROSSPOST = 2, // 1<<1
  DISCORD_MESSAGE_SUPRESS_EMBEDS = 4, // 1<<2
  DISCORD_MESSAGE_SOURCE_MESSAGE_DELETED = 8, // 1<<3
  DISCORD_MESSAGE_URGENT = 16, // 1<<4
};
extern char* discord_message_flags_to_string(enum discord_message_flags);
extern enum discord_message_flags discord_message_flags_from_string(char*);
extern bool discord_message_flags_has(enum discord_message_flags, char*);


enum discord_message_activity_types {
  DISCORD_MESSAGE_ACTIVITY_JOIN = 1,
  DISCORD_MESSAGE_ACTIVITY_SPECTATE = 2,
  DISCORD_MESSAGE_ACTIVITY_LISTEN = 3,
  DISCORD_MESSAGE_ACTIVITY_JOIN_REQUEST = 5,
};
extern char* discord_message_activity_types_to_string(enum discord_message_activity_types);
extern enum discord_message_activity_types discord_message_activity_types_from_string(char*);
extern bool discord_message_activity_types_has(enum discord_message_activity_types, char*);


enum discord_message_types {
  DISCORD_MESSAGE_DEFAULT = 0,
  DISCORD_MESSAGE_RECIPIENT_ADD = 1,
  DISCORD_MESSAGE_RECIPIENT_REMOVE = 3,
  DISCORD_MESSAGE_CALL = 5,
  DISCORD_MESSAGE_CHANNEL_NAME_CHANGE = 5,
  DISCORD_MESSAGE_CHANNEL_ICON_CHANGE = 5,
  DISCORD_MESSAGE_CHANNEL_PINNED_MESSAGE = 5,
  DISCORD_MESSAGE_GUILD_MEMBER_JOIN = 5,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION = 5,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
  DISCORD_MESSAGE_USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
  DISCORD_MESSAGE_CHANNEL_FOLLOW_ADD = 12,
  DISCORD_MESSAGE_GUILD_DISCOVERY_DISQUALIFIED = 14,
  DISCORD_MESSAGE_GUILD_DISCOVERY_REQUALIFIED = 15,
  DISCORD_MESSAGE_REPLY = 19,
  DISCORD_MESSAGE_APPLICATION_COMMAND = 20,
};
extern char* discord_message_types_to_string(enum discord_message_types);
extern enum discord_message_types discord_message_types_from_string(char*);
extern bool discord_message_types_has(enum discord_message_types, char*);
/* This file is generated from specs/discord/emoji.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see 
 */

/* This file is generated from specs/discord/emoji.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/emoji
 */

/* This file is generated from specs/discord/gateway.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/gateway
 */



enum discord_gateway_close_opcodes {
  DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_ERROR = 4000,
  DISCORD_GATEWAY_CLOSE_REASON_UNKNOWN_OPCODE = 4001,
  DISCORD_GATEWAY_CLOSE_REASON_DECODE_ERROR = 4002,
  DISCORD_GATEWAY_CLOSE_REASON_NOT_AUTHENTICATED = 4003,
  DISCORD_GATEWAY_CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  DISCORD_GATEWAY_CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_SEQUENCE = 4007,
  DISCORD_GATEWAY_CLOSE_REASON_RATE_LIMITED = 4008,
  DISCORD_GATEWAY_CLOSE_REASON_SESSION_TIMED_OUT = 4009,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_SHARD = 4010,
  DISCORD_GATEWAY_CLOSE_REASON_SHARDING_REQUIRED = 4011,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_API_VERSION = 4012,
  DISCORD_GATEWAY_CLOSE_REASON_INVALID_INTENTS = 4013,
  DISCORD_GATEWAY_CLOSE_REASON_DISALLOWED_INTENTS = 4014,
};
extern char* discord_gateway_close_opcodes_to_string(enum discord_gateway_close_opcodes);
extern enum discord_gateway_close_opcodes discord_gateway_close_opcodes_from_string(char*);
extern bool discord_gateway_close_opcodes_has(enum discord_gateway_close_opcodes, char*);


enum discord_gateway_intents {
  DISCORD_GATEWAY_GUILDS = 1, // 1 << 0
  DISCORD_GATEWAY_GUILD_MEMBERS = 2, // 1 << 1
  DISCORD_GATEWAY_GUILD_BANS = 4, // 1 << 2
  DISCORD_GATEWAY_GUILD_EMOJIS = 8, // 1 << 3
  DISCORD_GATEWAY_GUILD_INTEGRATIONS = 16, // 1 << 4
  DISCORD_GATEWAY_GUILD_WEBHOOKS = 32, // 1 << 5
  DISCORD_GATEWAY_GUILD_INVITES = 64, // 1 << 6
  DISCORD_GATEWAY_GUILD_VOICE_STATES = 128, // 1 << 7
  DISCORD_GATEWAY_GUILD_PRESENCES = 256, // 1 << 8
  DISCORD_GATEWAY_GUILD_MESSAGES = 512, // 1 << 9
  DISCORD_GATEWAY_GUILD_MESSAGE_REACTIONS = 1024, // 1 << 10
  DISCORD_GATEWAY_GUILD_MESSAGE_TYPING = 2048, // 1 << 11
  DISCORD_GATEWAY_DIRECT_MESSAGES = 4096, // 1 << 12
  DISCORD_GATEWAY_DIRECT_MESSAGE_REACTIONS = 8192, // 1 << 13
  DISCORD_GATEWAY_DIRECT_MESSAGE_TYPING = 16384, // 1 << 14
};
extern char* discord_gateway_intents_to_string(enum discord_gateway_intents);
extern enum discord_gateway_intents discord_gateway_intents_from_string(char*);
extern bool discord_gateway_intents_has(enum discord_gateway_intents, char*);


enum discord_gateway_opcodes {
  DISCORD_GATEWAY_DISPATCH = 0,
  DISCORD_GATEWAY_HEARTBEAT = 1,
  DISCORD_GATEWAY_IDENTIFY = 2,
  DISCORD_GATEWAY_PRESENCE_UPDATE = 3,
  DISCORD_GATEWAY_VOICE_STATE_UPDATE = 4,
  DISCORD_GATEWAY_RESUME = 6,
  DISCORD_GATEWAY_RECONNECT = 7,
  DISCORD_GATEWAY_REQUEST_GUILD_MEMBERS = 8,
  DISCORD_GATEWAY_INVALID_SESSION = 9,
  DISCORD_GATEWAY_HELLO = 10,
  DISCORD_GATEWAY_HEARTBEAT_ACK = 11,
};
extern char* discord_gateway_opcodes_to_string(enum discord_gateway_opcodes);
extern enum discord_gateway_opcodes discord_gateway_opcodes_from_string(char*);
extern bool discord_gateway_opcodes_has(enum discord_gateway_opcodes, char*);


enum discord_gateway_events {
  DISCORD_GATEWAY_EVENTS_NONE = 0,
  DISCORD_GATEWAY_EVENTS_GUILD_CREATE = 1,
  DISCORD_GATEWAY_EVENTS_GUILD_UPDATE = 2,
  DISCORD_GATEWAY_EVENTS_GUILD_DELETE = 3,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_CREATE = 4,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_UPDATE = 5,
  DISCORD_GATEWAY_EVENTS_GUILD_ROLE_DELETE = 6,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_ADD = 7,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_UPDATE = 8,
  DISCORD_GATEWAY_EVENTS_GUILD_MEMBER_REMOVE = 9,
  DISCORD_GATEWAY_EVENTS_GUILD_BAN_ADD = 10,
  DISCORD_GATEWAY_EVENTS_GUILD_BAN_REMOVE = 11,
  DISCORD_GATEWAY_EVENTS_GUILD_EMOJIS_UPDATE = 12,
  DISCORD_GATEWAY_EVENTS_GUILD_INTEGRATIONS_UPDATE = 13,
  DISCORD_GATEWAY_EVENTS_CHANNEL_CREATE = 14,
  DISCORD_GATEWAY_EVENTS_CHANNEL_UPDATE = 15,
  DISCORD_GATEWAY_EVENTS_CHANNEL_DELETE = 16,
  DISCORD_GATEWAY_EVENTS_CHANNEL_PINS_UPDATE = 17,
  DISCORD_GATEWAY_EVENTS_INVITE_CREATE = 18,
  DISCORD_GATEWAY_EVENTS_INVITE_DELETE = 19,
  DISCORD_GATEWAY_EVENTS_MESSAGE_CREATE = 20,
  DISCORD_GATEWAY_EVENTS_MESSAGE_UPDATE = 21,
  DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE = 22,
  DISCORD_GATEWAY_EVENTS_MESSAGE_DELETE_BULK = 23,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_ADD = 24,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE = 25,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_ALL = 26,
  DISCORD_GATEWAY_EVENTS_MESSAGE_REACTION_REMOVE_EMOJI = 27,
  DISCORD_GATEWAY_EVENTS_WEBHOOKS_UPDATE = 28,
  DISCORD_GATEWAY_EVENTS_VOICE_STATE_UPDATE = 29,
  DISCORD_GATEWAY_EVENTS_VOICE_SERVER_UPDATE = 30,
  DISCORD_GATEWAY_EVENTS_PRESENCE_UPDATE = 31,
  DISCORD_GATEWAY_EVENTS_TYPING_START = 32,
  DISCORD_GATEWAY_EVENTS_READY = 33,
  DISCORD_GATEWAY_EVENTS_RESUMED = 34,
};
extern char* discord_gateway_events_to_string(enum discord_gateway_events);
extern enum discord_gateway_events discord_gateway_events_from_string(char*);
extern bool discord_gateway_events_has(enum discord_gateway_events, char*);


enum discord_gateway_activity_types {
  DISCORD_GATEWAY_ACTIVITY_GAME = 0,
  DISCORD_GATEWAY_ACTIVITY_STREAMING = 1,
  DISCORD_GATEWAY_ACTIVITY_LISTENING = 2,
  DISCORD_GATEWAY_ACTIVITY_CUSTOM = 4,
  DISCORD_GATEWAY_ACTIVITY_COMPETING = 5,
};
extern char* discord_gateway_activity_types_to_string(enum discord_gateway_activity_types);
extern enum discord_gateway_activity_types discord_gateway_activity_types_from_string(char*);
extern bool discord_gateway_activity_types_has(enum discord_gateway_activity_types, char*);
/* This file is generated from specs/discord/guild-template.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild-template
 */

/* This file is generated from specs/discord/guild-template.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild-template
 */

/* This file is generated from specs/discord/guild.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild
 */

/* This file is generated from specs/discord/guild.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/guild
 */



enum discord_guild_default_message_notification_level {
  DISCORD_GUILD_ALL_MESSAGES = 0,
  DISCORD_GUILD_ONLY_MENTIONS = 1,
};
extern char* discord_guild_default_message_notification_level_to_string(enum discord_guild_default_message_notification_level);
extern enum discord_guild_default_message_notification_level discord_guild_default_message_notification_level_from_string(char*);
extern bool discord_guild_default_message_notification_level_has(enum discord_guild_default_message_notification_level, char*);


enum discord_guild_explicit_content_filter_level {
  DISCORD_GUILD_DISABLED = 0,
  DISCORD_GUILD_MEMBERS_WITHOUT_ROLES = 1,
  DISCORD_GUILD_ALL_MEMBERS = 2,
};
extern char* discord_guild_explicit_content_filter_level_to_string(enum discord_guild_explicit_content_filter_level);
extern enum discord_guild_explicit_content_filter_level discord_guild_explicit_content_filter_level_from_string(char*);
extern bool discord_guild_explicit_content_filter_level_has(enum discord_guild_explicit_content_filter_level, char*);


enum discord_guild_mfa_level {
  DISCORD_GUILD_DISCORD_MFA_NONE = 0,
  DISCORD_GUILD_ELEVATED = 1,
};
extern char* discord_guild_mfa_level_to_string(enum discord_guild_mfa_level);
extern enum discord_guild_mfa_level discord_guild_mfa_level_from_string(char*);
extern bool discord_guild_mfa_level_has(enum discord_guild_mfa_level, char*);


enum discord_guild_verification_level {
  DISCORD_GUILD_DISCORD_VL_NONE = 0,
  DISCORD_GUILD_LOW = 1,
  DISCORD_GUILD_MEDIUM = 2,
  DISCORD_GUILD_HIGH = 3,
  DISCORD_GUILD_VERY_HIGH = 4,
};
extern char* discord_guild_verification_level_to_string(enum discord_guild_verification_level);
extern enum discord_guild_verification_level discord_guild_verification_level_from_string(char*);
extern bool discord_guild_verification_level_has(enum discord_guild_verification_level, char*);


enum discord_guild_premium_tier {
  DISCORD_GUILD_DISCORD_PREMIUM_NONE = 0,
  DISCORD_GUILD_TIER_1 = 1,
  DISCORD_GUILD_TIER_2 = 2,
  DISCORD_GUILD_TIER_3 = 3,
};
extern char* discord_guild_premium_tier_to_string(enum discord_guild_premium_tier);
extern enum discord_guild_premium_tier discord_guild_premium_tier_from_string(char*);
extern bool discord_guild_premium_tier_has(enum discord_guild_premium_tier, char*);


enum discord_guild_system_channel_flags {
  DISCORD_GUILD_SUPRESS_JOIN_NOTIFICATIONS = 1, // 1<<0
  DISCORD_GUILD_SUPRESS_PREMIUM_SUBSCRIPTIONS = 2, // 1<<1
};
extern char* discord_guild_system_channel_flags_to_string(enum discord_guild_system_channel_flags);
extern enum discord_guild_system_channel_flags discord_guild_system_channel_flags_from_string(char*);
extern bool discord_guild_system_channel_flags_has(enum discord_guild_system_channel_flags, char*);


enum discord_guild_features {
  DISCORD_GUILD_INVITE_SPLASH = 0,
  DISCORD_GUILD_VIP_REGIONS = 1,
  DISCORD_GUILD_VANITY_URL = 2,
  DISCORD_GUILD_VERIFIED = 3,
  DISCORD_GUILD_PARTNERED = 4,
  DISCORD_GUILD_COMMUNITY = 5,
  DISCORD_GUILD_COMMERCE = 6,
  DISCORD_GUILD_NEWS = 7,
  DISCORD_GUILD_DISCOVERABLE = 8,
  DISCORD_GUILD_FEATURABLE = 9,
  DISCORD_GUILD_ANIMATED_ICON = 10,
  DISCORD_GUILD_BANNER = 11,
  DISCORD_GUILD_WELCOME_SCREEN_ENABLED = 12,
  DISCORD_GUILD_MEMBER_VERIFICATION_GATE_ENABLED = 13,
  DISCORD_GUILD_PREVIEW_ENABLED = 14,
};
extern char* discord_guild_features_to_string(enum discord_guild_features);
extern enum discord_guild_features discord_guild_features_from_string(char*);
extern bool discord_guild_features_has(enum discord_guild_features, char*);


enum discord_guild_integration_expire_behaviors {
  DISCORD_GUILD_INTEGRATION_REMOVE_ROLE = 0,
  DISCORD_GUILD_INTEGRATION_KICK = 1,
};
extern char* discord_guild_integration_expire_behaviors_to_string(enum discord_guild_integration_expire_behaviors);
extern enum discord_guild_integration_expire_behaviors discord_guild_integration_expire_behaviors_from_string(char*);
extern bool discord_guild_integration_expire_behaviors_has(enum discord_guild_integration_expire_behaviors, char*);
/* This file is generated from specs/discord/invite.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/invite
 */

/* This file is generated from specs/discord/invite.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/invite
 */



enum discord_invite_target_user_types {
  DISCORD_INVITE_STREAM = 1,
};
extern char* discord_invite_target_user_types_to_string(enum discord_invite_target_user_types);
extern enum discord_invite_target_user_types discord_invite_target_user_types_from_string(char*);
extern bool discord_invite_target_user_types_has(enum discord_invite_target_user_types, char*);
/* This file is generated from specs/discord/message_components.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/interactions/message-components#message-components
 */



enum discord_component_types {
  DISCORD_COMPONENT_ACTION_ROW = 1,
  DISCORD_COMPONENT_BUTTON = 2,
  DISCORD_COMPONENT_SELECT_MENU = 3,
};
extern char* discord_component_types_to_string(enum discord_component_types);
extern enum discord_component_types discord_component_types_from_string(char*);
extern bool discord_component_types_has(enum discord_component_types, char*);


enum discord_button_styles {
  DISCORD_BUTTON_PRIMARY = 1, // blurple, requires custom_id
  DISCORD_BUTTON_SECONDARY = 2, // grey, requires custom_id
  DISCORD_BUTTON_SUCCESS = 3, // green, requires custom_id
  DISCORD_BUTTON_DANGER = 4, // red, requires custom_id
  DISCORD_BUTTON_LINK = 5, // grey, requires url
};
extern char* discord_button_styles_to_string(enum discord_button_styles);
extern enum discord_button_styles discord_button_styles_from_string(char*);
extern bool discord_button_styles_has(enum discord_button_styles, char*);
/* This file is generated from specs/discord/permissions.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/permissions
 */



enum discord_permissions_bitwise_flags {
  DISCORD_PERMISSIONS_ZERO = 0, // No permission bits
  DISCORD_PERMISSIONS_CREATE_INSTANT_INVITE = 1, // Allows creation of instant invites  T, V
  DISCORD_PERMISSIONS_KICK_MEMBERS = 2, // Allows kicking members
  DISCORD_PERMISSIONS_BAN_MEMBERS = 4, // Allows banning members
  DISCORD_PERMISSIONS_ADMINISTRATOR = 8, // Allows all permissions and bypasses channel permission overwrites   
  DISCORD_PERMISSIONS_MANAGE_CHANNELS = 16, // Allows management and editing of channels   T, V
  DISCORD_PERMISSIONS_MANAGE_GUILD = 32, // Allows management and editing of the guild  
  DISCORD_PERMISSIONS_ADD_REACTIONS = 64, // Allows for the addition of reactions to messages    T
  DISCORD_PERMISSIONS_VIEW_AUDIT_LOG = 128, // Allows for viewing of audit logs    
  DISCORD_PERMISSIONS_PRIORITY_SPEAKER = 256, // Allows for using priority speaker in a voice channel    V
  DISCORD_PERMISSIONS_STREAM = 512, // Allows the user to go live  V
  DISCORD_PERMISSIONS_VIEW_CHANNEL = 1024, // Allows guild members to view a channel, which includes reading messages in text channels    T, V
  DISCORD_PERMISSIONS_SEND_MESSAGES = 2048, // Allows for sending messages in a channel    T
  DISCORD_PERMISSIONS_SEND_TTS_MESSAGES = 4096, // Allows for sending of /tts messages T
  DISCORD_PERMISSIONS_MANAGE_MESSAGES = 8192, // Allows for deletion of other users messages T
  DISCORD_PERMISSIONS_EMBED_LINKS = 16384, // Links sent by users with this permission will be auto-embedded  T
  DISCORD_PERMISSIONS_ATTACH_FILES = 32768, // Allows for uploading images and files   T
  DISCORD_PERMISSIONS_READ_MESSAGE_HISTORY = 65536, // Allows for reading of message history   T
  DISCORD_PERMISSIONS_MENTION_EVERYONE = 131072, // Allows for using the @everyone tag to notify all users in a channel, and the @here tag to notify all online users in a channel  T
  DISCORD_PERMISSIONS_USE_EXTERNAL_EMOJIS = 262144, // Allows the usage of custom emojis from other servers    T
  DISCORD_PERMISSIONS_VIEW_GUILD_INSIGHTS = 524288, // Allows for viewing guild insights   
  DISCORD_PERMISSIONS_CONNECT = 1048576, // Allows for joining of a voice channel   V
  DISCORD_PERMISSIONS_SPEAK = 2097152, // Allows for speaking in a voice channel  V
  DISCORD_PERMISSIONS_MUTE_MEMBERS = 4194304, // Allows for muting members in a voice channel    V
  DISCORD_PERMISSIONS_DEAFEN_MEMBERS = 8388608, // Allows for deafening of members in a voice channel  V
  DISCORD_PERMISSIONS_MOVE_MEMBERS = 16777216, // Allows for moving of members between voice channels V
  DISCORD_PERMISSIONS_USE_VAD = 33554432, // Allows for using voice-activity-detection in a voice channel    V
  DISCORD_PERMISSIONS_CHANGE_NICKNAME = 67108864, // Allows for modification of own nickname 
  DISCORD_PERMISSIONS_MANAGE_NICKNAMES = 134217728, // Allows for modification of other users nicknames    
  DISCORD_PERMISSIONS_MANAGE_ROLES = 268435456, // Allows management and editing of roles  T, V
  DISCORD_PERMISSIONS_MANAGE_WEBHOOKS = 536870912, // Allows management and editing of webhooks   T, V
  DISCORD_PERMISSIONS_MANAGE_EMOJIS = 1073741824, // Allows management and editing of emojis
};
extern char* discord_permissions_bitwise_flags_to_string(enum discord_permissions_bitwise_flags);
extern enum discord_permissions_bitwise_flags discord_permissions_bitwise_flags_from_string(char*);
extern bool discord_permissions_bitwise_flags_has(enum discord_permissions_bitwise_flags, char*);
/* This file is generated from specs/discord/slash_commands.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/interactions/slash-commands#data-models-and-types
 */



enum discord_application_command_option_types {
  DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND = 1,
  DISCORD_APPLICATION_COMMAND_OPTION_SUB_COMMAND_GROUP = 2,
  DISCORD_APPLICATION_COMMAND_OPTION_STRING = 3,
  DISCORD_APPLICATION_COMMAND_OPTION_INTEGER = 4,
  DISCORD_APPLICATION_COMMAND_OPTION_BOOLEAN = 5,
  DISCORD_APPLICATION_COMMAND_OPTION_USER = 6,
  DISCORD_APPLICATION_COMMAND_OPTION_CHANNEL = 7,
  DISCORD_APPLICATION_COMMAND_OPTION_ROLE = 8,
  DISCORD_APPLICATION_COMMAND_OPTION_MENTIONABLE = 9,
};
extern char* discord_application_command_option_types_to_string(enum discord_application_command_option_types);
extern enum discord_application_command_option_types discord_application_command_option_types_from_string(char*);
extern bool discord_application_command_option_types_has(enum discord_application_command_option_types, char*);


enum discord_application_command_permission_types {
  DISCORD_APPLICATION_COMMAND_PERMISSION_ROLE = 1,
  DISCORD_APPLICATION_COMMAND_PERMISSION_USER = 2,
};
extern char* discord_application_command_permission_types_to_string(enum discord_application_command_permission_types);
extern enum discord_application_command_permission_types discord_application_command_permission_types_from_string(char*);
extern bool discord_application_command_permission_types_has(enum discord_application_command_permission_types, char*);


enum discord_interaction_request_types {
  DISCORD_INTERACTION_PING = 1,
  DISCORD_INTERACTION_APPLICATION_COMMAND = 2,
  DISCORD_INTERACTION_MESSAGE_COMPONENT = 3,
};
extern char* discord_interaction_request_types_to_string(enum discord_interaction_request_types);
extern enum discord_interaction_request_types discord_interaction_request_types_from_string(char*);
extern bool discord_interaction_request_types_has(enum discord_interaction_request_types, char*);


enum discord_interaction_callback_types {
  DISCORD_INTERACTION_CALLBACK_PONG = 1, // ACK a Ping
  DISCORD_INTERACTION_CALLBACK_CHANNEL_MESSAGE_WITH_SOURCE = 4, // respond to a interaction with a message
  DISCORD_INTERACTION_CALLBACK_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE = 5, // ACK an interaction and edit a response later, the user sees a loading state
  DISCORD_INTERACTION_CALLBACK_DEFERRED_UPDATE_MESSAGE = 6, // for components, ACK an interaction and edit the original message later; the user does not see a loading state
  DISCORD_INTERACTION_CALLBACK_UPDATE_MESSAGE = 7, // for components, edit the message the component was attached to
};
extern char* discord_interaction_callback_types_to_string(enum discord_interaction_callback_types);
extern enum discord_interaction_callback_types discord_interaction_callback_types_from_string(char*);
extern bool discord_interaction_callback_types_has(enum discord_interaction_callback_types, char*);


enum discord_interaction_application_command_callback_data_flags {
  DISCORD_INTERACTION_APPLICATION_COMMAND_CALLBACK_DATA_EPHEMERAL = 64, // only the user receiving the message can see it
};
extern char* discord_interaction_application_command_callback_data_flags_to_string(enum discord_interaction_application_command_callback_data_flags);
extern enum discord_interaction_application_command_callback_data_flags discord_interaction_application_command_callback_data_flags_from_string(char*);
extern bool discord_interaction_application_command_callback_data_flags_has(enum discord_interaction_application_command_callback_data_flags, char*);
/* This file is generated from specs/discord/user.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/user
 */

/* This file is generated from specs/discord/user.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/user
 */



enum discord_user_flags {
  DISCORD_USER_DISCORD_EMPLOYEE = 1, // 1 << 0
  DISCORD_USER_PARTNERED_SERVER_OWNER = 2, // 1 << 2
  DISCORD_USER_HYPESQUAD_EVENTS = 4, // 1 << 3
  DISCORD_USER_BUG_HUNTER_LEVEL_1 = 8, // 1 << 4
  DISCORD_USER_HOUSE_BRAVERY = 32, // 1 << 6
  DISCORD_USER_HOUSE_BRILLIANCE = 64, // 1 << 7
  DISCORD_USER_HOUSE_BALANCE = 128, // 1 << 8
  DISCORD_USER_EARLY_SUPPORTER = 256, // 1 << 9
  DISCORD_USER_TEAM_USER = 512, // 1 << 10
  DISCORD_USER_SYSTEM = 4096, // 1 << 12
  DISCORD_USER_BUG_HUNTER_LEVEL_2 = 16384, // 1 << 14
  DISCORD_USER_VERIFIED_BOT = 65536, // 1 << 16
  DISCORD_USER_EARLY_VERIFIED_BOT_DEVELOPER = 131072, // 1 << 17
};
extern char* discord_user_flags_to_string(enum discord_user_flags);
extern enum discord_user_flags discord_user_flags_from_string(char*);
extern bool discord_user_flags_has(enum discord_user_flags, char*);


enum discord_user_premium_types {
  DISCORD_USER_NITRO_CLASSIC = 0,
  DISCORD_USER_NITRO = 1,
};
extern char* discord_user_premium_types_to_string(enum discord_user_premium_types);
extern enum discord_user_premium_types discord_user_premium_types_from_string(char*);
extern bool discord_user_premium_types_has(enum discord_user_premium_types, char*);


enum discord_user_connection_visibility_types {
  DISCORD_USER_CONNECTION_NONE = 0,
  DISCORD_USER_CONNECTION_EVERYONE = 1,
};
extern char* discord_user_connection_visibility_types_to_string(enum discord_user_connection_visibility_types);
extern enum discord_user_connection_visibility_types discord_user_connection_visibility_types_from_string(char*);
extern bool discord_user_connection_visibility_types_has(enum discord_user_connection_visibility_types, char*);
/* This file is generated from specs/discord/voice-connections.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/topics/voice-connections
 */



enum discord_voice_close_opcodes {
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_OPCODE = 4001,
  DISCORD_VOICE_CLOSE_REASON_DECODE_ERROR = 4002,
  DISCORD_VOICE_CLOSE_REASON_NOT_AUTHENTICATED = 4003,
  DISCORD_VOICE_CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  DISCORD_VOICE_CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  DISCORD_VOICE_CLOSE_REASON_INVALID_SESSION = 4006,
  DISCORD_VOICE_CLOSE_REASON_SESSION_TIMED_OUT = 4009,
  DISCORD_VOICE_CLOSE_REASON_SERVER_NOT_FOUND = 4011,
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_PROTOCOL = 4012,
  DISCORD_VOICE_CLOSE_REASON_DISCONNECTED = 4014,
  DISCORD_VOICE_CLOSE_REASON_SERVER_CRASH = 4015,
  DISCORD_VOICE_CLOSE_REASON_UNKNOWN_ENCRYPTION_MODE = 4016,
};
extern char* discord_voice_close_opcodes_to_string(enum discord_voice_close_opcodes);
extern enum discord_voice_close_opcodes discord_voice_close_opcodes_from_string(char*);
extern bool discord_voice_close_opcodes_has(enum discord_voice_close_opcodes, char*);


enum discord_voice_opcodes {
  DISCORD_VOICE_IDENTIFY = 0,
  DISCORD_VOICE_SELECT_PROTOCOL = 1,
  DISCORD_VOICE_READY = 2,
  DISCORD_VOICE_HEARTBEAT = 3,
  DISCORD_VOICE_SESSION_DESCRIPTION = 4,
  DISCORD_VOICE_SPEAKING = 5,
  DISCORD_VOICE_HEARTBEAT_ACK = 6,
  DISCORD_VOICE_RESUME = 7,
  DISCORD_VOICE_HELLO = 8,
  DISCORD_VOICE_RESUMED = 9,
  DISCORD_VOICE_CLIENT_DISCONNECT = 13,
  DISCORD_VOICE_CODEC = 14,
};
extern char* discord_voice_opcodes_to_string(enum discord_voice_opcodes);
extern enum discord_voice_opcodes discord_voice_opcodes_from_string(char*);
extern bool discord_voice_opcodes_has(enum discord_voice_opcodes, char*);


enum discord_voice_speaking_flags {
  DISCORD_VOICE_MICROPHONE = 1, // 1 << 0
  DISCORD_VOICE_SOUNDSHARE = 2, // 1 << 1
  DISCORD_VOICE_PRIORITY = 4, // 1 << 2
};
extern char* discord_voice_speaking_flags_to_string(enum discord_voice_speaking_flags);
extern enum discord_voice_speaking_flags discord_voice_speaking_flags_from_string(char*);
extern bool discord_voice_speaking_flags_has(enum discord_voice_speaking_flags, char*);
/* This file is generated from specs/discord/voice.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/voice
 */

/* This file is generated from specs/discord/webhook.endpoints-params.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/webhook
 */

/* This file is generated from specs/discord/webhook.json, Please don't edit it. */
/**
 * @file specs-code/discord/all_enums.h
 * @author cee-studio
 * @date Jul 28 2021
 * @brief Specs generated file
 * @see https://discord.com/developers/docs/resources/webhook
 */



enum discord_webhook_types {
  DISCORD_WEBHOOK_INCOMING = 1,
  DISCORD_WEBHOOK_CHANNEL_FOLLOWER = 2,
};
extern char* discord_webhook_types_to_string(enum discord_webhook_types);
extern enum discord_webhook_types discord_webhook_types_from_string(char*);
extern bool discord_webhook_types_has(enum discord_webhook_types, char*);
