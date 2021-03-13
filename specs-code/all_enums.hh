/* This file is generated from specs/guild.membership_screening.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#membership-screening-object
*/
namespace discord {
namespace guild {
namespace membership_screening {


namespace field_type {
enum code {
  TERMS = 0,
};
} // namespace field_type
} // namespace membership_screening
} // namespace guild
} // namespace discord
/* This file is generated from specs/channel.edit-channel-permissions.json, Please don't edit it. */
/*

*/
namespace discord {
namespace channel {
namespace edit_channel_permissions {
} // namespace edit_channel_permissions
} // namespace channel
} // namespace discord
/* This file is generated from specs/channel.modify-channel.json, Please don't edit it. */
/*

*/
namespace discord {
namespace channel {
namespace modify {
} // namespace modify
} // namespace channel
} // namespace discord
/* This file is generated from specs/channel.message.json, Please don't edit it. */
/*

*/
namespace discord {
namespace channel {
namespace message {


namespace sticker {
namespace format_type {
enum code {
  PNG = 1,
  APNG = 2,
  LOTTIE = 3,
};
} // namespace format_type
} // namespace sticker


namespace flags {
enum code {
  CROSSPOSTED = 1,
  IS_CROSSPOST = 2,
  SUPRESS_EMBEDS = 4,
  SOURCE_MESSAGE_DELETED = 8,
  URGENT = 16,
};
} // namespace flags


namespace activity {
namespace types {
enum code {
  JOIN = 1,
  SPECTATE = 2,
  LISTEN = 3,
  JOIN_REQUEST = 5,
};
} // namespace types
} // namespace activity


namespace types {
enum code {
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
} // namespace types
} // namespace message
} // namespace channel
} // namespace discord
/* This file is generated from specs/template.create-guild-template.json, Please don't edit it. */
/*

*/
namespace discord {
namespace Template {
namespace create_guild_template {
} // namespace create_guild_template
} // namespace Template
} // namespace discord
/* This file is generated from specs/channel.group-dm-add-recipient.json, Please don't edit it. */
/*

*/
namespace discord {
namespace channel {
namespace group_dm_add_recipient {
} // namespace group_dm_add_recipient
} // namespace channel
} // namespace discord
/* This file is generated from specs/channel.create-channel-invite.json, Please don't edit it. */
/*

*/
namespace discord {
namespace channel {
namespace create_channel_invite {
} // namespace create_channel_invite
} // namespace channel
} // namespace discord
/* This file is generated from specs/guild.ban.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#ban-object
*/
namespace discord {
namespace guild {
} // namespace guild
} // namespace discord
/* This file is generated from specs/voice.json, Please don't edit it. */
/*
(null)
*/
namespace discord {
} // namespace discord
/* This file is generated from specs/channel.get-reactions.json, Please don't edit it. */
/*

*/
namespace discord {
namespace channel {
namespace get_reactions {
} // namespace get_reactions
} // namespace channel
} // namespace discord
/* This file is generated from specs/guild.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-object-guild-structure
*/
namespace discord {
namespace guild {
} // namespace guild
} // namespace discord
/* This file is generated from specs/user.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/user#user-object
*/
namespace discord {
namespace user {


namespace flags {
enum code {
  NONE = 0,
  DISCORD_EMPLOYEE = 1,
  PARTNERED_SERVER_OWNER = 2,
  HYPESQUAD_EVENTS = 4,
  BUG_HUNTER_LEVEL_1 = 8,
  HOUSE_BRAVERY = 32,
  HOUSE_BRILLIANCE = 64,
  HOUSE_BALANCE = 128,
  EARLY_SUPPORTER = 256,
  TEAM_USER = 512,
  SYSTEM = 4096,
  BUG_HUNTER_LEVEL_2 = 16384,
  VERIFIED_BOT = 65536,
  EARLY_VERIFIED_BOT_DEVELOPER = 131072,
};
} // namespace flags


namespace premium_types {
enum code {
};
} // namespace premium_types


namespace connection {
namespace visibility_types {
enum code {
  NONE = 0,
  EVERYONE = 1,
};
} // namespace visibility_types
} // namespace connection
} // namespace user
} // namespace discord
/* This file is generated from specs/webhook.modify-webhook.json, Please don't edit it. */
/*

*/
namespace discord {
namespace webhook {
namespace modify_webhook {
} // namespace modify_webhook
} // namespace webhook
} // namespace discord
/* This file is generated from specs/guild.integration.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/
namespace discord {
namespace guild {


namespace integration {
namespace expire_behaviors {
enum code {
  REMOVE_ROLE = 0,
  KICK = 1,
};
} // namespace expire_behaviors
} // namespace integration
} // namespace guild
} // namespace discord
/* This file is generated from specs/guild.enum.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#integration-object-integration-structure
*/
namespace discord {
namespace guild {


namespace default_message_notification_level {
enum code {
  ALL_MESSAGES = 0,
  ONLY_MENTIONS = 1,
};
} // namespace default_message_notification_level


namespace explicit_content_filter_level {
enum code {
  DISABLED = 0,
  MEMBERS_WITHOUT_ROLES = 1,
  ALL_MEMBERS = 2,
};
} // namespace explicit_content_filter_level


namespace mfa_level {
enum code {
  NONE = 0,
  ELEVATED = 1,
};
} // namespace mfa_level


namespace verification_level {
enum code {
  NONE = 0,
  LOW = 1,
  MEDIUM = 2,
  HIGH = 3,
  VERY_HIGH = 4,
};
} // namespace verification_level


namespace premium_tier {
enum code {
  NONE = 0,
  TIER_1 = 1,
  TIER_2 = 2,
  TIER_3 = 3,
};
} // namespace premium_tier


namespace system_channel_flags {
enum code {
  SUPRESS_JOIN_NOTIFICATIONS = 1,
  SUPRESS_PREMIUM_SUBSCRIPTIONS = 2,
};
} // namespace system_channel_flags


namespace guild_features {
enum code {
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
} // namespace guild_features
} // namespace guild
} // namespace discord
/* This file is generated from specs/invite.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/invite#invite-object
*/
namespace discord {
namespace invite {


namespace target_user_types {
enum code {
  STREAM = 1,
};
} // namespace target_user_types
} // namespace invite
} // namespace discord
/* This file is generated from specs/webhook.edit-webhook-message.json, Please don't edit it. */
/*

*/
namespace discord {
namespace webhook {
namespace edit_webhook_message {
} // namespace edit_webhook_message
} // namespace webhook
} // namespace discord
/* This file is generated from specs/template.create-guild-from-template.json, Please don't edit it. */
/*

*/
namespace discord {
namespace Template {
namespace create_guild_from_template {
} // namespace create_guild_from_template
} // namespace Template
} // namespace discord
/* This file is generated from specs/channel.objects.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#overwrite-object-overwrite-structure
*/
namespace discord {
namespace channel {
} // namespace channel
} // namespace discord
/* This file is generated from specs/guild.create-channel.json, Please don't edit it. */
/*

*/
namespace discord {
namespace guild {
namespace create_channel {
} // namespace create_channel
} // namespace guild
} // namespace discord
/* This file is generated from specs/emoji.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/emoji#emoji-object-emoji-structure
*/
namespace discord {
namespace emoji {
} // namespace emoji
} // namespace discord
/* This file is generated from specs/webhook.create-webhook.json, Please don't edit it. */
/*

*/
namespace discord {
namespace webhook {
namespace create_webhook {
} // namespace create_webhook
} // namespace webhook
} // namespace discord
/* This file is generated from specs/guild.welcome_screen.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#welcome-screen-object
*/
namespace discord {
namespace guild {
namespace welcome_screen {
} // namespace welcome_screen
} // namespace guild
} // namespace discord
/* This file is generated from specs/guild.member.modify.json, Please don't edit it. */
/*

*/
namespace discord {
namespace guild {
namespace member {
namespace modify {
} // namespace modify
} // namespace member
} // namespace guild
} // namespace discord
/* This file is generated from specs/guild.create-guild.json, Please don't edit it. */
/*

*/
namespace discord {
namespace guild {
namespace create_guild {
} // namespace create_guild
} // namespace guild
} // namespace discord
/* This file is generated from specs/channel.bulk-delete-messages.json, Please don't edit it. */
/*

*/
namespace discord {
namespace channel {
namespace bulk_delete_messages {
} // namespace bulk_delete_messages
} // namespace channel
} // namespace discord
/* This file is generated from specs/webhook.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-structure
*/
namespace discord {


namespace webhook {
namespace types {
enum code {
  INCOMING = 1,
  CHANNEL_FOLLOWER = 2,
};
} // namespace types
} // namespace webhook
} // namespace discord
/* This file is generated from specs/user.create-group-dm.json, Please don't edit it. */
/*

*/
namespace discord {
namespace user {
namespace create_group_dm {
} // namespace create_group_dm
} // namespace user
} // namespace discord
/* This file is generated from specs/emoji.modify-guild-emoji.json, Please don't edit it. */
/*

*/
namespace discord {
namespace emoji {
namespace modify_guild_emoji {
} // namespace modify_guild_emoji
} // namespace emoji
} // namespace discord
/* This file is generated from specs/webhook.execute-webhook.json, Please don't edit it. */
/*

*/
namespace discord {
namespace webhook {
namespace execute_webhook {
} // namespace execute_webhook
} // namespace webhook
} // namespace discord
/* This file is generated from specs/guild.role.create.json, Please don't edit it. */
/*

*/
namespace discord {
namespace guild {
namespace role {
namespace create {
} // namespace create
} // namespace role
} // namespace guild
} // namespace discord
/* This file is generated from specs/audit_log.json, Please don't edit it. */
/*
(null)
*/
namespace discord {
namespace audit_log {


namespace entry {
namespace events {
enum code {
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
} // namespace events
} // namespace entry
} // namespace audit_log
} // namespace discord
/* This file is generated from specs/guild.role.json, Please don't edit it. */
/*
https://discord.com/developers/docs/topics/permissions#role-object-role-structure
*/
namespace discord {
namespace guild {
} // namespace guild
} // namespace discord
/* This file is generated from specs/emoji.create-guild-emoji.json, Please don't edit it. */
/*

*/
namespace discord {
namespace emoji {
namespace create_guild_emoji {
} // namespace create_guild_emoji
} // namespace emoji
} // namespace discord
/* This file is generated from specs/template.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/template#template-object-template-structure
*/
namespace discord {
} // namespace discord
/* This file is generated from specs/channel.follow-news-channel.json, Please don't edit it. */
/*

*/
namespace discord {
namespace channel {
namespace follow_news_channel {
} // namespace follow_news_channel
} // namespace channel
} // namespace discord
/* This file is generated from specs/gateway.json, Please don't edit it. */
/*
(null)
*/
namespace discord {
namespace gateway {


enum close_opcodes {
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


namespace intents {
enum code {
  GUILDS = 1,
  GUILD_MEMBERS = 2,
  GUILD_BANS = 4,
  GUILD_EMOJIS = 8,
  GUILD_INTEGRATIONS = 16,
  GUILD_WEBHOOKS = 32,
  GUILD_INVITES = 64,
  GUILD_VOICE_STATES = 128,
  GUILD_PRESENCES = 256,
  GUILD_MESSAGES = 512,
  GUILD_MESSAGE_REACTIONS = 1024,
  GUILD_MESSAGE_TYPING = 2048,
  DIRECT_MESSAGES = 4096,
  DIRECT_MESSAGE_REACTIONS = 8192,
  DIRECT_MESSAGE_TYPING = 16384,
};
} // namespace intents


namespace opcodes {
enum code {
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
} // namespace opcodes


namespace activity {
namespace types {
enum code {
};
} // namespace types
} // namespace activity
} // namespace gateway
} // namespace discord
/* This file is generated from specs/template.modify-guild-template.json, Please don't edit it. */
/*

*/
namespace discord {
namespace Template {
namespace modify_guild_template {
} // namespace modify_guild_template
} // namespace Template
} // namespace discord
/* This file is generated from specs/channel.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/channel#channel-object-channel-types
*/
namespace discord {
namespace channel {


namespace types {
enum code {
  GUILD_TEXT = 0,
  DM = 1,
  GUILD_VOICE = 2,
  GROUP_DM = 3,
  GUILD_CATEGORY = 4,
  GUILD_NEWS = 5,
  GUILD_STORE = 6,
};
} // namespace types
} // namespace channel
} // namespace discord
/* This file is generated from specs/guild.member.json, Please don't edit it. */
/*
https://discord.com/developers/docs/resources/guild#guild-member-object
*/
namespace discord {
namespace guild {
} // namespace guild
} // namespace discord
/* This file is generated from specs/user.modify-curent-user.json, Please don't edit it. */
/*

*/
namespace discord {
namespace user {
namespace modify_current_user {
} // namespace modify_current_user
} // namespace user
} // namespace discord
