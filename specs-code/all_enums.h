/* This file is generated from specs/guild.membership_screening.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/


enum discord_guild_membership_screening_field_type_code {
  TERMS = 0,
};
/* This file is generated from specs/channel.edit-channel-permissions.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/channel.modify-channel.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/channel.message.json, Please don't edit it. */
/*

*/


enum discord_channel_message_sticker_format_type_code {
  PNG = 1,
  APNG = 2,
  LOTTIE = 3,
};


enum discord_channel_message_flags_code {
  CROSSPOSTED = 1, // 1<<0
  IS_CROSSPOST = 2, // 1<<1
  SUPRESS_EMBEDS = 4, // 1<<2
  SOURCE_MESSAGE_DELETED = 8, // 1<<3
  URGENT = 16, // 1<<4
};


enum discord_channel_message_activity_types_code {
  JOIN = 1,
  SPECTATE = 2,
  LISTEN = 3,
  JOIN_REQUEST = 5,
};


enum discord_channel_message_types_code {
  DEFAULT = 0,
  RECIPIENT_ADD = 1,
  RECIPIENT_REMOVE = 3,
  CALL = 5,
  CHANNEL_NAME_CHANGE = 5,
  CHANNEL_ICON_CHANGE = 5,
  CHANNEL_PINNED_MESSAGE = 5,
  GUILD_MEMBER_JOIN = 5,
  USER_PREMIUM_GUILD_SUBSCRIPTION = 5,
  USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
  USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
  USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
  CHANNEL_FOLLOW_ADD = 12,
  GUILD_DISCOVERY_DISQUALIFIED = 14,
  GUILD_DISCOVERY_REQUALIFIED = 15,
  REPLY = 19,
  APPLICATION_COMMAND = 20,
};
/* This file is generated from specs/webhook.edit-webhook-message.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/template.create-guild-template.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/channel.group-dm-add-recipient.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/channel.create-channel-invite.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/guild.ban.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/
/* This file is generated from specs/voice.json, Please don't edit it. */
/*
(null)
*/
/* This file is generated from specs/channel.get-reactions.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/guild.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
*/
/* This file is generated from specs/user.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/user#user-object
*/


enum discord_user_flags_code {
  NONE = 0, // 0
  DISCORD_EMPLOYEE = 1, // 1 << 0
  PARTNERED_SERVER_OWNER = 2, // 1 << 2
  HYPESQUAD_EVENTS = 4, // 1 << 3
  BUG_HUNTER_LEVEL_1 = 8, // 1 << 4
  HOUSE_BRAVERY = 32, // 1 << 6
  HOUSE_BRILLIANCE = 64, // 1 << 7
  HOUSE_BALANCE = 128, // 1 << 8
  EARLY_SUPPORTER = 256, // 1 << 9
  TEAM_USER = 512, // 1 << 10
  SYSTEM = 4096, // 1 << 12
  BUG_HUNTER_LEVEL_2 = 16384, // 1 << 14
  VERIFIED_BOT = 65536, // 1 << 16
  EARLY_VERIFIED_BOT_DEVELOPER = 131072, // 1 << 17
};


enum discord_user_premium_types_code {
};


enum discord_user_connection_visibility_types_code {
  NONE = 0,
  EVERYONE = 1,
};
/* This file is generated from specs/guild.modify-guild-member.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/guild.integration.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/


enum discord_guild_integration_expire_behaviors_code {
  REMOVE_ROLE = 0,
  KICK = 1,
};
/* This file is generated from specs/guild.enum.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/


enum discord_guild_default_message_notification_level_code {
  ALL_MESSAGES = 0,
  ONLY_MENTIONS = 1,
};


enum discord_guild_explicit_content_filter_level_code {
  DISABLED = 0,
  MEMBERS_WITHOUT_ROLES = 1,
  ALL_MEMBERS = 2,
};


enum discord_guild_mfa_level_code {
  NONE = 0,
  ELEVATED = 1,
};


enum discord_guild_verification_level_code {
  NONE = 0,
  LOW = 1,
  MEDIUM = 2,
  HIGH = 3,
  VERY_HIGH = 4,
};


enum discord_guild_premium_tier_code {
  NONE = 0,
  TIER_1 = 1,
  TIER_2 = 2,
  TIER_3 = 3,
};


enum discord_guild_system_channel_flags_code {
  SUPRESS_JOIN_NOTIFICATIONS = 1, // 1<<0
  SUPRESS_PREMIUM_SUBSCRIPTIONS = 2, // 1<<1
};


enum discord_guild_guild_features_code {
  INVITE_SPLASH = 0,
  VIP_REGIONS = 1,
  VANITY_URL = 2,
  VERIFIED = 3,
  PARTNERED = 4,
  COMMUNITY = 5,
  COMMERCE = 6,
  NEWS = 7,
  DISCOVERABLE = 8,
  FEATURABLE = 9,
  ANIMATED_ICON = 10,
  BANNER = 11,
  WELCOME_SCREEN_ENABLED = 12,
  MEMBER_VERIFICATION_GATE_ENABLED = 13,
  PREVIEW_ENABLED = 14,
};
/* This file is generated from specs/invite.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/invite#invite-object
*/


enum discord_invite_target_user_types_code {
  STREAM = 1,
};
/* This file is generated from specs/webhook.modify-webhook.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/template.create-guild-from-template.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/channel.objects.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/
/* This file is generated from specs/guild.create-channel.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/emoji.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
*/
/* This file is generated from specs/webhook.create-webhook.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/guild.welcome_screen.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#welcome-screen-object
*/
/* This file is generated from specs/guild.create-guild.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/channel.bulk-delete-messages.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/webhook.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
*/


enum discord_webhook_types_code {
  INCOMING = 1,
  CHANNEL_FOLLOWER = 2,
};
/* This file is generated from specs/user.create-group-dm.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/emoji.modify-guild-emoji.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/webhook.execute-webhook.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/guild.role.create.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/permissions.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions
*/


enum discord_permissions_bitwise_flags {
  ZERO = 0, // No permission bits
  CREATE_INSTANT_INVITE = 1, // Allows creation of instant invites  T, V
  KICK_MEMBERS = 2, // Allows kicking members
  BAN_MEMBERS = 4, // Allows banning members
  ADMINISTRATOR = 8, // Allows all permissions and bypasses channel permission overwrites   
  MANAGE_CHANNELS = 16, // Allows management and editing of channels   T, V
  MANAGE_GUILD = 32, // Allows management and editing of the guild  
  ADD_REACTIONS = 64, // Allows for the addition of reactions to messages    T
  VIEW_AUDIT_LOG = 128, // Allows for viewing of audit logs    
  PRIORITY_SPEAKER = 256, // Allows for using priority speaker in a voice channel    V
  STREAM = 512, // Allows the user to go live  V
  VIEW_CHANNEL = 1024, // Allows guild members to view a channel, which includes reading messages in text channels    T, V
  SEND_MESSAGES = 2048, // Allows for sending messages in a channel    T
  SEND_TTS_MESSAGES = 4096, // Allows for sending of /tts messages T
  MANAGE_MESSAGES = 8192, // Allows for deletion of other users messages T
  EMBED_LINKS = 16384, // Links sent by users with this permission will be auto-embedded  T
  ATTACH_FILES = 32768, // Allows for uploading images and files   T
  READ_MESSAGE_HISTORY = 65536, // Allows for reading of message history   T
  MENTION_EVERYONE = 131072, // Allows for using the @everyone tag to notify all users in a channel, and the @here tag to notify all online users in a channel  T
  USE_EXTERNAL_EMOJIS = 262144, // Allows the usage of custom emojis from other servers    T
  VIEW_GUILD_INSIGHTS = 524288, // Allows for viewing guild insights   
  CONNECT = 1048576, // Allows for joining of a voice channel   V
  SPEAK = 2097152, // Allows for speaking in a voice channel  V
  MUTE_MEMBERS = 4194304, // Allows for muting members in a voice channel    V
  DEAFEN_MEMBERS = 8388608, // Allows for deafening of members in a voice channel  V
  MOVE_MEMBERS = 16777216, // Allows for moving of members between voice channels V
  USE_VAD = 33554432, // Allows for using voice-activity-detection in a voice channel    V
  CHANGE_NICKNAME = 67108864, // Allows for modification of own nickname 
  MANAGE_NICKNAMES = 134217728, // Allows for modification of other users nicknames    
  MANAGE_ROLES = 268435456, // Allows management and editing of roles  T, V
  MANAGE_WEBHOOKS = 536870912, // Allows management and editing of webhooks   T, V
  MANAGE_EMOJIS = 1073741824, // Allows management and editing of emojis
};
/* This file is generated from specs/audit_log.json, Please don't edit it. */
/*
(null)
*/


enum discord_audit_log_entry_events_code {
  GUILD_UPDATE = 1,
  CHANNEL_CREATE = 10,
  CHANNEL_UPDATE = 11,
  CHANNEL_DELETE = 12,
  CHANNEL_OVERWRITE_CREATE = 13,
  CHANNEL_OVERWRITE_UPDATE = 14,
  CHANNEL_OVERWRITE_DELETE = 15,
  MEMBER_KICK = 20,
  MEMBER_PRUNE = 21,
  MEMBER_BAN_ADD = 22,
  MEMBER_BAN_REMOVE = 23,
  MEMBER_UPDATE = 24,
  MEMBER_ROLE_UPDATE = 25,
  MEMBER_MOVE = 26,
  MEMBER_DISCONNECT = 27,
  BOT_ADD = 28,
  ROLE_CREATE = 30,
  ROLE_UPDATE = 31,
  ROLE_DELETE = 32,
  INVITE_CREATE = 40,
  INVITE_DELETE = 42,
  WEBHOOK_CREATE = 50,
  WEBHOOK_UPDATE = 51,
  WEBHOOK_DELETE = 52,
  EMOJI_CREATE = 60,
  EMOJI_UPDATE = 61,
  EMOJI_DELETE = 62,
  MESSAGE_DELETE = 72,
  MESSAGE_BULK_DELETE = 73,
  MESSAGE_PIN = 74,
  MESSAGE_UNPIN = 75,
  INTEGRATION_CREATE = 80,
  INTEGRATION_UPDATE = 81,
  INTEGRATION_DELETE = 82,
};
/* This file is generated from specs/guild.role.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/
/* This file is generated from specs/emoji.create-guild-emoji.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/template.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/template#template-object-template-structure
*/
/* This file is generated from specs/channel.follow-news-channel.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/gateway.json, Please don't edit it. */
/*
(null)
*/


enum discord_gateway_close_opcodes {
  CLOSE_REASON_UNKNOWN_ERROR = 4000,
  CLOSE_REASON_UNKNOWN_OPCODE = 4001,
  CLOSE_REASON_DECODE_ERROR = 4002,
  CLOSE_REASON_NOT_AUTHENTICATED = 4003,
  CLOSE_REASON_AUTHENTICATION_FAILED = 4004,
  CLOSE_REASON_ALREADY_AUTHENTICATED = 4005,
  CLOSE_REASON_INVALID_SEQUENCE = 4007,
  CLOSE_REASON_RATE_LIMITED = 4008,
  CLOSE_REASON_SESSION_TIMED_OUT = 4009,
  CLOSE_REASON_INVALID_SHARD = 4010,
  CLOSE_REASON_SHARDING_REQUIRED = 4011,
  CLOSE_REASON_INVALID_API_VERSION = 4012,
  CLOSE_REASON_INVALID_INTENTS = 4013,
  CLOSE_REASON_DISALLOWED_INTENTS = 4014,
};


enum discord_gateway_intents_code {
  GUILDS = 1, // 1 << 0
  GUILD_MEMBERS = 2, // 1 << 1
  GUILD_BANS = 4, // 1 << 2
  GUILD_EMOJIS = 8, // 1 << 3
  GUILD_INTEGRATIONS = 16, // 1 << 4
  GUILD_WEBHOOKS = 32, // 1 << 5
  GUILD_INVITES = 64, // 1 << 6
  GUILD_VOICE_STATES = 128, // 1 << 7
  GUILD_PRESENCES = 256, // 1 << 8
  GUILD_MESSAGES = 512, // 1 << 9
  GUILD_MESSAGE_REACTIONS = 1024, // 1 << 10
  GUILD_MESSAGE_TYPING = 2048, // 1 << 11
  DIRECT_MESSAGES = 4096, // 1 << 12
  DIRECT_MESSAGE_REACTIONS = 8192, // 1 << 13
  DIRECT_MESSAGE_TYPING = 16384, // 1 << 14
};


enum discord_gateway_opcodes_code {
  DISPATCH = 0,
  HEARTBEAT = 1,
  IDENTIFY = 2,
  PRESENCE_UPDATE = 3,
  VOICE_STATE_UPDATE = 4,
  RESUME = 6,
  RECONNECT = 7,
  REQUEST_GUILD_MEMBERS = 8,
  INVALID_SESSION = 9,
  HELLO = 10,
  HEARTBEAT_ACK = 11,
};


enum discord_gateway_identify_status_update_activity_types_code {
};


enum discord_gateway_presence_code {
};
/* This file is generated from specs/template.modify-guild-template.json, Please don't edit it. */
/*

*/
/* This file is generated from specs/channel.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#channel-object-channel-types
*/


enum discord_channel_types_code {
  GUILD_TEXT = 0,
  DM = 1,
  GUILD_VOICE = 2,
  GROUP_DM = 3,
  GUILD_CATEGORY = 4,
  GUILD_NEWS = 5,
  GUILD_STORE = 6,
};
/* This file is generated from specs/guild.member.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-member-object
*/
/* This file is generated from specs/user.modify-curent-user.json, Please don't edit it. */
/*

*/
